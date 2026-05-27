#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
i76_level_reconstruction_export_v6.py

Interstate '76 level reconstruction exporter, v6.

Purpose
-------
This version extends the dense-terrain / RSEG / ODEF diagnostic baseline with
binary-backed class-specific ODEF resource resolution:

    * ODEF class 0x01 + spawn/regen labels: marker-only special cases
    * ODEF class 0x01 ordinary labels:     label.vcf
    * ODEF class 0x08 / 0x09 labels:       label.vcf
    * ODEF static classes:                 label.sdf
    * LDEF records, when supplied:          label.sdf
    * SDF child candidates:                 childName.geo

The script is intentionally conservative.  It does not pretend that all SDF
layout details are fully solved.  Instead it resolves what can be grounded from
resource names and emits detailed TSV/JSON manifests for every object, attempted
resource, SDF child candidate, GEO hit, and unresolved edge.

The exporter accepts already-extracted resources.  It can be used as a direct
v6 diagnostic pass now, and as a drop-in scaffold for importing v4's exact TER,
ZMAP, RSEG, and GEO mesh helpers later.

Expected directory shape
------------------------
The script recursively indexes --resources-root.  It does not require a specific
layout, but typical usage is:

    zfs/resources/...
    pix_pak_extracted/...
    level/*.obj or level/*.odef or level/*.ldef

Examples
--------
    python3 i76_level_reconstruction_export_v6.py \
        --resources-root /path/to/zfs/resources \
        --level-root /path/to/extracted/m06 \
        --level-name m06 \
        --out-dir /media/neon-remote/prj/i76/scratch_data

    python3 i76_level_reconstruction_export_v6.py \
        --resources-root /path/to/all/extracted/resources \
        --odef-file /path/to/M06.OBJ \
        --out-dir /tmp/i76_v5

Outputs
-------
A timestamped folder plus a sibling .tar archive unless --no-tar is used.

    manifest.json
    object_records.tsv
    object_resource_resolution.tsv
    sdf_child_candidates.tsv
    unresolved_resources.tsv
    scene_axes.obj
    scene_resource_markers.obj
    notes.txt

If --copy-resolved is enabled, resolved .sdf/.vcf/.geo resources are also copied
under resolved_resources/ for convenient inspection.
"""

from __future__ import annotations

import argparse
import dataclasses
import datetime as _dt
import json
import math
import os
import re
import shutil
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path
from typing import Dict, Iterable, Iterator, List, Optional, Sequence, Tuple


SCRIPT_VERSION = "v6"
DEFAULT_OUTPUT_ROOT = Path("/media/neon-remote/prj/i76/scratch_data")

ODEF_RECORD_SIZE = 0x64
NAME_LEN = 8

# Binary-backed v42 class policy from Ghidra trace.
VCF_CLASSES = {0x01, 0x08, 0x09}
SDF_CLASSES = {
    0x02, 0x03, 0x04,
    0x07, 0x0A, 0x0B, 0x0C,
    0x50, 0x52, 0x53,
}
NULLISH_OR_SPECIAL_CLASSES = set(range(0x0D, 0x50)) | {0x05, 0x06, 0x51}

# Candidate resource-token scanner.  I76 resource names are commonly DOS-ish
# short names, but texture/material paths can be wider.  Keep this permissive
# and filter against the resource index afterward.
TOKEN_RE = re.compile(rb"[A-Za-z0-9_#$@!~\-]{2,16}")
KNOWN_RESOURCE_EXTS = {
    ".sdf", ".vcf", ".vdf", ".vtf", ".wdf", ".geo", ".tmt", ".map",
    ".m16", ".vqm", ".cbk", ".pix", ".pak", ".ter", ".zmap", ".zone",
    ".rdef", ".rseg", ".obj", ".odef", ".ldef", ".msn", ".cbt",
    ".cf2", ".cf3", ".cf4", ".rac",
}

# Retail install mission-side containers visible under miss8/miss16.  These are
# not missions directories; they are color-depth trees containing per-mission
# payload files such as M06.MSN and M06.TER.
MISSION_CONTAINER_EXTS = {".msn", ".cbt", ".cf2", ".cf3", ".cf4", ".rac"}
LEVEL_RECORD_EXTS = {".odef", ".ldef", ".obj"}


@dataclasses.dataclass
class ResourceHit:
    key: str
    path: Path
    size: int


@dataclasses.dataclass
class OdefRecord:
    source_path: Path
    record_index: int
    file_offset: int
    label_raw: bytes
    label: str
    basis: Tuple[Tuple[float, float, float], Tuple[float, float, float], Tuple[float, float, float]]
    position: Tuple[float, float, float]
    class_id: int
    valid_transform: bool


@dataclasses.dataclass
class Resolution:
    source_kind: str
    source_path: str
    record_index: int
    label: str
    class_id: int
    policy: str
    expected_resource: str
    status: str
    hit_path: str = ""
    note: str = ""


@dataclasses.dataclass
class SdfChildCandidate:
    sdf_label: str
    sdf_path: str
    source: str
    child_name: str
    expected_geo: str
    status: str
    geo_path: str = ""
    confidence: str = "low"
    note: str = ""


class ResourceIndex:
    def __init__(self) -> None:
        self.by_full_name: Dict[str, List[ResourceHit]] = defaultdict(list)
        self.by_stem_ext: Dict[Tuple[str, str], List[ResourceHit]] = defaultdict(list)
        self.by_stem: Dict[str, List[ResourceHit]] = defaultdict(list)
        self.all_files: List[ResourceHit] = []

    @staticmethod
    def norm_name(s: str) -> str:
        return s.replace("\\", "/").split("/")[-1].lower()

    @staticmethod
    def norm_stem(s: str) -> str:
        return Path(s).stem.lower()

    def add(self, path: Path) -> None:
        try:
            st = path.stat()
        except OSError:
            return
        if not path.is_file():
            return
        name = self.norm_name(path.name)
        stem = path.stem.lower()
        ext = path.suffix.lower()
        hit = ResourceHit(key=name, path=path, size=st.st_size)
        self.all_files.append(hit)
        self.by_full_name[name].append(hit)
        self.by_stem_ext[(stem, ext)].append(hit)
        self.by_stem[stem].append(hit)

    def find_exact(self, resource_name: str) -> List[ResourceHit]:
        return list(self.by_full_name.get(self.norm_name(resource_name), []))

    def find_stem_ext(self, stem: str, ext: str) -> List[ResourceHit]:
        if not ext.startswith("."):
            ext = "." + ext
        return list(self.by_stem_ext.get((stem.lower(), ext.lower()), []))

    def best(self, resource_name: str) -> Optional[ResourceHit]:
        hits = self.find_exact(resource_name)
        if hits:
            return sorted(hits, key=lambda h: (len(str(h.path)), str(h.path).lower()))[0]
        p = Path(resource_name)
        if p.suffix:
            hits = self.find_stem_ext(p.stem, p.suffix)
            if hits:
                return sorted(hits, key=lambda h: (len(str(h.path)), str(h.path).lower()))[0]
        return None

    def summary(self) -> Dict[str, object]:
        ext_counts: Dict[str, int] = defaultdict(int)
        for hit in self.all_files:
            ext_counts[hit.path.suffix.lower() or "<none>"] += 1
        return {
            "file_count": len(self.all_files),
            "extension_counts": dict(sorted(ext_counts.items())),
        }


def decode_i76_label(raw: bytes) -> str:
    """Decode fixed-width labels; high-bit masking is important for ODEF names."""
    chars: List[str] = []
    for b in raw[:NAME_LEN]:
        b &= 0x7F
        if b == 0:
            break
        if 32 <= b < 127:
            chars.append(chr(b))
    return "".join(chars).strip().lower()


def is_probably_float_tuple(values: Sequence[float]) -> bool:
    for v in values:
        if not math.isfinite(v):
            return False
        if abs(v) > 1.0e8:
            return False
    return True


def is_label_text(label: str) -> bool:
    return bool(label) and all((c.isalnum() or c in "_-$#@!~") for c in label)


def unpack_odef_record_at(data: bytes, path: Path, idx: int, off: int) -> Optional[OdefRecord]:
    if off < 0 or off + ODEF_RECORD_SIZE > len(data):
        return None
    rec = data[off:off + ODEF_RECORD_SIZE]
    raw_label = rec[0:8]
    label = decode_i76_label(raw_label)
    try:
        floats = struct.unpack_from("<12f", rec, 0x08)
        basis = (
            (floats[0], floats[1], floats[2]),
            (floats[3], floats[4], floats[5]),
            (floats[6], floats[7], floats[8]),
        )
        pos = struct.unpack_from("<3f", rec, 0x2C)
        cls = rec[0x5C]
    except Exception:
        return None
    valid = bool(label) and is_probably_float_tuple(floats) and is_probably_float_tuple(pos)
    return OdefRecord(path, idx, off, raw_label, label, basis, pos, cls, valid)


def strict_record_score(rec: OdefRecord) -> int:
    """Score a candidate record for embedded-container discovery."""
    score = 0
    if is_label_text(rec.label):
        score += 5
    else:
        return -100

    if rec.class_id in VCF_CLASSES or rec.class_id in SDF_CLASSES:
        score += 4
    elif rec.class_id in NULLISH_OR_SPECIAL_CLASSES:
        score += 1
    elif rec.class_id == 0:
        score -= 3
    else:
        score -= 4

    flat_basis = [v for row in rec.basis for v in row]
    if is_probably_float_tuple(flat_basis) and all(abs(v) <= 16.0 for v in flat_basis):
        score += 3
    else:
        score -= 8

    if is_probably_float_tuple(rec.position) and all(abs(v) <= 1.0e7 for v in rec.position):
        score += 2
    else:
        score -= 8

    # Typical transform bases should not be all-zero.  Allow partial/weird rows,
    # but reject obvious string/table noise when scanning .MSN-like containers.
    if sum(abs(v) for v in flat_basis) > 0.001:
        score += 1
    else:
        score -= 4
    return score


def parse_aligned_odef_records(path: Path) -> List[OdefRecord]:
    data = path.read_bytes()
    records: List[OdefRecord] = []

    # Primary mode: aligned 0x64 records.  If the file has a small header before
    # records, test common alignments and choose the one with the most sane rows.
    candidates = [0]
    candidates.extend([off for off in range(4, min(0x80, len(data)), 4)])

    def score_offset(start: int) -> int:
        score = 0
        count = 0
        for off in range(start, len(data) - ODEF_RECORD_SIZE + 1, ODEF_RECORD_SIZE):
            rec = unpack_odef_record_at(data, path, count, off)
            if rec is None:
                continue
            s = strict_record_score(rec)
            # Aligned dumps may include blank rows, so do not require strict pass.
            score += max(0, s)
            count += 1
            if count >= 64:
                break
        return score

    best_start = max(candidates, key=score_offset) if len(data) >= ODEF_RECORD_SIZE else 0

    idx = 0
    for off in range(best_start, len(data) - ODEF_RECORD_SIZE + 1, ODEF_RECORD_SIZE):
        rec = unpack_odef_record_at(data, path, idx, off)
        if rec is not None:
            records.append(rec)
            idx += 1
    return records


def parse_embedded_odef_records(path: Path, min_score: int = 9) -> List[OdefRecord]:
    """Scan retail mission containers for embedded 0x64 ODEF-like records.

    The visible install tree contains Mxx.MSN/Mxx.TER files rather than already
    extracted ODEF blobs.  Until the exact MSN section directory is pinned down,
    this scanner searches for plausible 0x64 records on 4-byte boundaries and
    keeps only strict candidates.  The resulting TSV file includes byte offsets,
    so false positives can be checked in a hex viewer or with a Ghidra trace.
    """
    data = path.read_bytes()
    out: List[OdefRecord] = []
    idx = 0
    if len(data) < ODEF_RECORD_SIZE:
        return out
    for off in range(0, len(data) - ODEF_RECORD_SIZE + 1, 4):
        rec = unpack_odef_record_at(data, path, idx, off)
        if rec is None:
            continue
        if strict_record_score(rec) >= min_score:
            out.append(dataclasses.replace(rec, record_index=idx))
            idx += 1
    return out


def parse_odef_records(path: Path) -> List[OdefRecord]:
    ext = path.suffix.lower()
    if ext in MISSION_CONTAINER_EXTS:
        return parse_embedded_odef_records(path)
    return parse_aligned_odef_records(path)

def object_policy(label: str, class_id: int, source_kind: str) -> Tuple[str, str, str]:
    """Return (policy, expected_resource, note)."""
    label_l = (label or "").lower()
    if source_kind.lower() == "ldef":
        return "ldef_sdf", f"{label_l}.sdf", "LDEF normal records resolve as SDF."

    if class_id == 0 or not label_l:
        return "invalid_or_blank", "", "Class 0 or blank label; diagnostic row only."

    if class_id == 0x01 and label_l == "spawn":
        return "spawn_marker", "", "Special spawn marker table path; not ordinary geometry."
    if class_id == 0x01 and label_l == "regen":
        return "regen_marker", "", "Special regen marker table path; not ordinary geometry."

    if class_id in VCF_CLASSES:
        return "odef_vcf", f"{label_l}.vcf", "Class-specific VCF object path."
    if class_id in SDF_CLASSES:
        return "odef_sdf", f"{label_l}.sdf", "Class-specific SDF static object path."
    if class_id in NULLISH_OR_SPECIAL_CLASSES:
        return "fallback_nullish", "", "Fallback/null-ish/special class; not treated as ordinary geometry."
    return "unknown_class", "", "Class not in current v42 policy table."


def scan_resource_index(roots: Sequence[Path]) -> ResourceIndex:
    idx = ResourceIndex()
    for root in roots:
        if not root:
            continue
        root = root.expanduser().resolve()
        if not root.exists():
            continue
        if root.is_file():
            idx.add(root)
            continue
        for p in root.rglob("*"):
            if p.is_file():
                idx.add(p)
    return idx


def find_level_record_files(level_root: Optional[Path], explicit_files: Sequence[Path]) -> List[Path]:
    files: List[Path] = []
    for p in explicit_files:
        if p and p.exists() and p.is_file():
            files.append(p.resolve())
    if level_root and level_root.exists():
        for p in level_root.rglob("*"):
            if not p.is_file():
                continue
            ext = p.suffix.lower()
            nm = p.name.lower()
            # v6: retail miss8/miss16 trees contain mission containers directly
            # as .MSN/.CBT/.CF2/.CF3/.CF4/.RAC, not per-mission ODEF folders.
            if ext in MISSION_CONTAINER_EXTS:
                files.append(p.resolve())
                continue
            # Already-extracted object-definition dumps remain supported.
            if ext in {".odef", ".ldef"} or nm.endswith(".obj"):
                if ext == ".obj":
                    try:
                        head = p.read_bytes()[:128]
                    except OSError:
                        continue
                    if head.startswith(b"#") or b"\nv " in head or b"\nf " in head:
                        continue
                files.append(p.resolve())
    # stable unique order
    out: List[Path] = []
    seen = set()
    for p in sorted(files, key=lambda x: str(x).lower()):
        if p not in seen:
            seen.add(p)
            out.append(p)
    return out

def source_kind_for_path(path: Path) -> str:
    nm = path.name.lower()
    ext = path.suffix.lower()
    if nm.endswith(".ldef") or "ldef" in nm:
        return "ldef"
    if ext in MISSION_CONTAINER_EXTS:
        return "mission_container"
    return "odef"


def ascii_tokens(buf: bytes, min_len: int = 2, max_len: int = 16) -> Iterator[Tuple[int, str]]:
    for m in TOKEN_RE.finditer(buf):
        tok = m.group(0).decode("ascii", errors="ignore")
        if min_len <= len(tok) <= max_len:
            yield m.start(), tok.lower()


def scan_sdf_child_candidates(sdf_path: Path, sdf_label: str, idx: ResourceIndex) -> List[SdfChildCandidate]:
    """Conservative SDF child scan.

    The exact SDFC/SOBJ descriptor parser is still a target for deepening.  This
    function gives useful grounded output today:

      1. Direct embedded '.geo' string/name references.
      2. Tokens near SOBJ/SGEO/SCHK/LOBJ chunk markers that match existing GEOs.
      3. Whole-file token scan filtered against the GEO index, marked low confidence.
    """
    try:
        data = sdf_path.read_bytes()
    except OSError as e:
        return [SdfChildCandidate(sdf_label, str(sdf_path), "error", "", "", "error", note=str(e))]

    out: List[SdfChildCandidate] = []
    seen: set[Tuple[str, str]] = set()

    def add(source: str, child: str, confidence: str, note: str = "") -> None:
        child_l = child.strip().lower().strip(".\x00")
        if not child_l or len(child_l) < 2:
            return
        if child_l.endswith(".geo"):
            geo_name = child_l
            child_stem = Path(child_l).stem.lower()
        else:
            child_stem = child_l
            geo_name = f"{child_l}.geo"
        hit = idx.best(geo_name)
        status = "resolved" if hit else "missing_geo"
        key = (source, geo_name)
        if key in seen:
            return
        seen.add(key)
        out.append(SdfChildCandidate(
            sdf_label=sdf_label,
            sdf_path=str(sdf_path),
            source=source,
            child_name=child_stem,
            expected_geo=geo_name,
            status=status,
            geo_path=str(hit.path) if hit else "",
            confidence=confidence,
            note=note,
        ))

    # 1. Direct references like foo.geo in the binary.
    for m in re.finditer(rb"([A-Za-z0-9_#$@!~\-]{2,16})\.geo", data, flags=re.IGNORECASE):
        add("embedded_geo_string", m.group(1).decode("ascii", errors="ignore"), "high")

    # 2. Tokens near known child/chunk markers.
    marker_re = re.compile(rb"SOBJ|SGEO|SCHK|LOBJ|SDFC", re.IGNORECASE)
    for mm in marker_re.finditer(data):
        lo = max(0, mm.start() - 64)
        hi = min(len(data), mm.end() + 256)
        window = data[lo:hi]
        marker = mm.group(0).decode("ascii", errors="ignore").upper()
        for _, tok in ascii_tokens(window):
            if tok.upper() in {"SOBJ", "SGEO", "SCHK", "LOBJ", "SDFC"}:
                continue
            if idx.best(tok + ".geo"):
                add(f"near_{marker}", tok, "medium", f"Token appears near {marker} marker and resolves to GEO.")

    # 3. Whole-file fallback filtered by known GEO stems.
    for _, tok in ascii_tokens(data):
        if idx.best(tok + ".geo"):
            add("whole_sdf_token_scan", tok, "low", "Token appears in SDF and resolves to a GEO; descriptor role not yet proven.")

    return out


def write_tsv(path: Path, rows: Sequence[object], field_names: Sequence[str]) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(field_names) + "\n")
        for row in rows:
            vals = []
            for name in field_names:
                v = getattr(row, name)
                if isinstance(v, bytes):
                    s = v.hex()
                elif isinstance(v, (tuple, list)):
                    s = json.dumps(v)
                else:
                    s = str(v)
                s = s.replace("\t", " ").replace("\r", " ").replace("\n", " ")
                vals.append(s)
            f.write("\t".join(vals) + "\n")


def copy_hit(hit: ResourceHit, dst_root: Path, prefix: str = "") -> Optional[Path]:
    try:
        dst_dir = dst_root / prefix / hit.path.suffix.lower().lstrip(".")
        dst_dir.mkdir(parents=True, exist_ok=True)
        dst = dst_dir / hit.path.name
        if dst.exists():
            # Preserve both if duplicate basenames appear in different archives.
            stem = dst.stem
            suf = dst.suffix
            n = 2
            while True:
                alt = dst_dir / f"{stem}_{n}{suf}"
                if not alt.exists():
                    dst = alt
                    break
                n += 1
        shutil.copy2(hit.path, dst)
        return dst
    except OSError:
        return None


def obj_escape_name(s: str) -> str:
    return re.sub(r"[^A-Za-z0-9_\-.]+", "_", s or "unnamed")


def add_axis_obj_lines(lines: List[str], rec: OdefRecord, scale: float) -> None:
    """Write three basis axes as OBJ line segments.

    OBJ has no per-line color, so this is purely structural.  The companion TSV
    identifies labels/classes and can be used by Blender import scripts.
    """
    x, y, z = rec.position
    b = rec.basis
    base_index = 1 + sum(1 for ln in lines if ln.startswith("v "))
    lines.append(f"o {obj_escape_name(rec.label)}_{rec.record_index:04d}_class_{rec.class_id:02x}")
    lines.append(f"v {x:.6f} {y:.6f} {z:.6f}")
    for axis in range(3):
        ax = b[axis]
        lines.append(f"v {x + ax[0] * scale:.6f} {y + ax[1] * scale:.6f} {z + ax[2] * scale:.6f}")
    lines.append(f"l {base_index} {base_index + 1}")
    lines.append(f"l {base_index} {base_index + 2}")
    lines.append(f"l {base_index} {base_index + 3}")


def add_marker_cube(lines: List[str], name: str, pos: Tuple[float, float, float], radius: float) -> None:
    x, y, z = pos
    base = 1 + sum(1 for ln in lines if ln.startswith("v "))
    verts = [
        (x - radius, y - radius, z - radius),
        (x + radius, y - radius, z - radius),
        (x + radius, y + radius, z - radius),
        (x - radius, y + radius, z - radius),
        (x - radius, y - radius, z + radius),
        (x + radius, y - radius, z + radius),
        (x + radius, y + radius, z + radius),
        (x - radius, y + radius, z + radius),
    ]
    edges = [(1,2),(2,3),(3,4),(4,1),(5,6),(6,7),(7,8),(8,5),(1,5),(2,6),(3,7),(4,8)]
    lines.append(f"o {obj_escape_name(name)}")
    for v in verts:
        lines.append(f"v {v[0]:.6f} {v[1]:.6f} {v[2]:.6f}")
    for a, b in edges:
        lines.append(f"l {base + a - 1} {base + b - 1}")


def make_output_dir(root: Path, level_name: str) -> Path:
    now = _dt.datetime.now().strftime("%Y%m%d_%H%M%S")
    safe_level = obj_escape_name(level_name or "level")
    out = root.expanduser().resolve() / f"i76_level_reconstruction_{SCRIPT_VERSION}_{safe_level}_{now}"
    out.mkdir(parents=True, exist_ok=False)
    return out


def create_tar(out_dir: Path) -> Optional[Path]:
    tar_path = out_dir.with_suffix(".tar")
    try:
        subprocess.run(
            ["tar", "-cf", str(tar_path), "-C", str(out_dir.parent), out_dir.name],
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        return tar_path
    except Exception:
        return None


def parse_args(argv: Optional[Sequence[str]] = None) -> argparse.Namespace:
    ap = argparse.ArgumentParser(description="Interstate '76 level reconstruction exporter v6")
    ap.add_argument("--resources-root", action="append", type=Path, default=[],
                    help="Root containing extracted ZFS/PIX/PAK resources. May be repeated.")
    ap.add_argument("--level-root", type=Path, default=None,
                    help="Directory containing extracted level record files.")
    ap.add_argument("--odef-file", action="append", type=Path, default=[],
                    help="Explicit ODEF/OBJ binary record file or retail mission container. May be repeated.")
    ap.add_argument("--mission-file", action="append", type=Path, default=[],
                    help="Explicit retail mission container such as M06.MSN/CBT/CF2/RAC. Alias input for --odef-file parsing path.")
    ap.add_argument("--ldef-file", action="append", type=Path, default=[],
                    help="Explicit LDEF binary record file. May be repeated.")
    ap.add_argument("--level-name", default="level", help="Level/mission name used in output folder naming.")
    ap.add_argument("--out-dir", type=Path, default=DEFAULT_OUTPUT_ROOT,
                    help=f"Output root. Default: {DEFAULT_OUTPUT_ROOT}")
    ap.add_argument("--axis-scale", type=float, default=128.0, help="ODEF axis line length in output OBJ units.")
    ap.add_argument("--marker-radius", type=float, default=32.0, help="Resolved-resource marker cube radius.")
    ap.add_argument("--copy-resolved", action="store_true", help="Copy resolved resources into output folder.")
    ap.add_argument("--no-tar", action="store_true", help="Do not create sibling .tar archive.")
    ap.add_argument("--include-invalid-records", action="store_true",
                    help="Keep invalid-looking aligned rows in OBJ marker outputs. TSVs always include them.")
    return ap.parse_args(argv)


def main(argv: Optional[Sequence[str]] = None) -> int:
    args = parse_args(argv)
    out_dir = make_output_dir(args.out_dir, args.level_name)

    resource_roots = list(args.resources_root)
    if args.level_root:
        resource_roots.append(args.level_root)
    resource_index = scan_resource_index(resource_roots)

    record_files = find_level_record_files(args.level_root, list(args.odef_file) + list(args.mission_file) + list(args.ldef_file))
    # Explicit LDEF files may not contain "ldef" in path; track them here.
    explicit_ldef = {p.resolve() for p in args.ldef_file if p.exists()}

    all_records: List[OdefRecord] = []
    resolutions: List[Resolution] = []
    sdf_children: List[SdfChildCandidate] = []
    unresolved: List[Resolution] = []

    copied_root = out_dir / "resolved_resources"

    for f in record_files:
        try:
            records = parse_odef_records(f)
        except Exception as e:
            (out_dir / "parse_errors.txt").open("a", encoding="utf-8").write(f"{f}\t{e}\n")
            continue
        all_records.extend(records)
        source_kind = "ldef" if f.resolve() in explicit_ldef else source_kind_for_path(f)
        for rec in records:
            policy, expected, note = object_policy(rec.label, rec.class_id, source_kind)
            if not rec.valid_transform and policy not in {"invalid_or_blank"}:
                note = (note + " Invalid-looking transform/label row; verify record alignment.").strip()
            hit = resource_index.best(expected) if expected else None
            status = "resolved" if hit else ("not_applicable" if not expected else "missing")
            res = Resolution(
                source_kind=source_kind,
                source_path=str(f),
                record_index=rec.record_index,
                label=rec.label,
                class_id=rec.class_id,
                policy=policy,
                expected_resource=expected,
                status=status,
                hit_path=str(hit.path) if hit else "",
                note=note,
            )
            resolutions.append(res)
            if hit and args.copy_resolved:
                copy_hit(hit, copied_root, "object_roots")
            if not hit and expected:
                unresolved.append(res)
            if hit and expected.lower().endswith(".sdf"):
                children = scan_sdf_child_candidates(hit.path, rec.label, resource_index)
                sdf_children.extend(children)
                if args.copy_resolved:
                    for ch in children:
                        if ch.geo_path:
                            copy_hit(ResourceHit(Path(ch.geo_path).name.lower(), Path(ch.geo_path), Path(ch.geo_path).stat().st_size), copied_root, "sdf_geo")
                for ch in children:
                    if ch.status != "resolved":
                        unresolved.append(Resolution(
                            source_kind="sdf_child",
                            source_path=ch.sdf_path,
                            record_index=rec.record_index,
                            label=ch.child_name,
                            class_id=rec.class_id,
                            policy="sdf_child_geo",
                            expected_resource=ch.expected_geo,
                            status=ch.status,
                            hit_path=ch.geo_path,
                            note=f"SDF={rec.label}; source={ch.source}; confidence={ch.confidence}; {ch.note}",
                        ))

    # TSV outputs.
    write_tsv(out_dir / "object_records.tsv", all_records, [
        "source_path", "record_index", "file_offset", "label_raw", "label",
        "basis", "position", "class_id", "valid_transform",
    ])
    write_tsv(out_dir / "object_resource_resolution.tsv", resolutions, [
        "source_kind", "source_path", "record_index", "label", "class_id", "policy",
        "expected_resource", "status", "hit_path", "note",
    ])
    write_tsv(out_dir / "sdf_child_candidates.tsv", sdf_children, [
        "sdf_label", "sdf_path", "source", "child_name", "expected_geo", "status",
        "geo_path", "confidence", "note",
    ])
    write_tsv(out_dir / "unresolved_resources.tsv", unresolved, [
        "source_kind", "source_path", "record_index", "label", "class_id", "policy",
        "expected_resource", "status", "hit_path", "note",
    ])

    # Diagnostic OBJ outputs.
    axis_lines = ["# Interstate '76 ODEF/LDEF axes diagnostic", f"# generated by {Path(__file__).name} {SCRIPT_VERSION}"]
    marker_lines = ["# Interstate '76 resolved object-resource markers", f"# generated by {Path(__file__).name} {SCRIPT_VERSION}"]
    rec_by_key = {(str(r.source_path), r.record_index): r for r in all_records}
    for rec in all_records:
        if rec.valid_transform or args.include_invalid_records:
            add_axis_obj_lines(axis_lines, rec, args.axis_scale)
    for res in resolutions:
        if res.status != "resolved":
            continue
        rec = rec_by_key.get((res.source_path, res.record_index))
        if not rec:
            continue
        if rec.valid_transform or args.include_invalid_records:
            add_marker_cube(marker_lines, f"{res.label}_{res.policy}_{Path(res.expected_resource).suffix.lower().lstrip('.')}", rec.position, args.marker_radius)
    (out_dir / "scene_axes.obj").write_text("\n".join(axis_lines) + "\n", encoding="utf-8")
    (out_dir / "scene_resource_markers.obj").write_text("\n".join(marker_lines) + "\n", encoding="utf-8")

    policy_counts: Dict[str, int] = defaultdict(int)
    status_counts: Dict[str, int] = defaultdict(int)
    class_counts: Dict[str, int] = defaultdict(int)
    for r in resolutions:
        policy_counts[r.policy] += 1
        status_counts[r.status] += 1
        class_counts[f"0x{r.class_id:02x}"] += 1
    sdf_status_counts: Dict[str, int] = defaultdict(int)
    for ch in sdf_children:
        sdf_status_counts[ch.status] += 1

    manifest = {
        "script": Path(__file__).name,
        "script_version": SCRIPT_VERSION,
        "generated_at": _dt.datetime.now().isoformat(timespec="seconds"),
        "level_name": args.level_name,
        "output_dir": str(out_dir),
        "resource_roots": [str(p) for p in resource_roots],
        "record_files": [str(p) for p in record_files],
        "resource_index": resource_index.summary(),
        "record_count": len(all_records),
        "resolution_count": len(resolutions),
        "sdf_child_candidate_count": len(sdf_children),
        "unresolved_count": len(unresolved),
        "policy_counts": dict(sorted(policy_counts.items())),
        "status_counts": dict(sorted(status_counts.items())),
        "class_counts": dict(sorted(class_counts.items())),
        "sdf_child_status_counts": dict(sorted(sdf_status_counts.items())),
        "v42_policy": {
            "vcf_classes": [f"0x{x:02x}" for x in sorted(VCF_CLASSES)],
            "sdf_classes": [f"0x{x:02x}" for x in sorted(SDF_CLASSES)],
            "spawn_regen_special_class": "0x01",
            "nullish_or_special_classes": [f"0x{x:02x}" for x in sorted(NULLISH_OR_SPECIAL_CLASSES)],
        },
    }
    (out_dir / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")

    notes = f"""
Interstate '76 level reconstruction export {SCRIPT_VERSION}

This pass implements the corrected class-specific ODEF policy from the v42/v43
Ghidra evidence.  It intentionally does not collapse all ODEF records to .vcf or
all ODEF records to .sdf.

Key outputs:

    object_records.tsv              Raw aligned or embedded ODEF/LDEF-style records.
    object_resource_resolution.tsv  Per-record policy and .vcf/.sdf lookup result.
    sdf_child_candidates.tsv        SDF-derived candidate child GEOs.
    unresolved_resources.tsv        Missing root resources and missing child GEOs.
    scene_axes.obj                  Transform-axis diagnostic OBJ.
    scene_resource_markers.obj      Resolved-root-resource marker diagnostic OBJ.

SDF child parsing status:

    Current SDF child detection uses embedded .geo strings, tokens near SOBJ/SGEO/
    SCHK/LOBJ/SDFC markers, and a whole-SDF token scan filtered by the GEO index.
    Rows are confidence-labeled.  The next deepening step is to replace the low
    confidence token scan with a strict SDFC/SOBJ descriptor-table parser.

Counts:

    records:              {len(all_records)}
    record files scanned: {len(record_files)}
    root resolutions:     {len(resolutions)}
    SDF child candidates: {len(sdf_children)}
    unresolved rows:      {len(unresolved)}
""".lstrip()
    (out_dir / "notes.txt").write_text(notes, encoding="utf-8")

    tar_path = None if args.no_tar else create_tar(out_dir)
    print(f"wrote: {out_dir}")
    if tar_path:
        print(f"tar:   {tar_path}")
    elif not args.no_tar:
        print("tar:   <failed; output folder still written>")
    print(f"records={len(all_records)} resolutions={len(resolutions)} sdf_children={len(sdf_children)} unresolved={len(unresolved)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
