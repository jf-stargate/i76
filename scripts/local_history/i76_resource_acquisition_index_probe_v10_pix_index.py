#!/usr/bin/env python3
"""
Interstate '76 resource acquisition index probe, v10.

Purpose:
  Validate missing binary-truth ODEF .vcf candidates against loose files,
  ZFS record metadata, and PIX/PAK index files.

Binary-truth policy:
  ODEF dispatch-valid object records -> label.vcf
  ODEF spawn/regen -> special markers
  ODEF blank/class-0 -> diagnostic/special
  LDEF object records -> label.sdf
  Open76 ODEF label.sdf -> comparison-only

v10 additions over v9:
  - Excludes .tar/.json/.tsv/.md report artifacts from binary container scans.
  - Parses .pix text indexes, based on binary evidence from 00470660:
      first count + rows parsed with "%s %d %d"-style fields.
  - Matches missing candidates against PIX index keys without requiring the
    candidate name to appear as raw text in .pak payloads.
"""

from __future__ import annotations

import argparse
import csv
import dataclasses
import hashlib
import json
import os
import re
import struct
import tarfile
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
PAGE_W = 128


@dataclasses.dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ""

    @property
    def end(self) -> int:
        return self.offset + self.size


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def fourcc(data: bytes, off: int) -> str:
    return data[off:off + 4].decode("ascii", errors="replace")


def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out: List[Chunk] = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        size = u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        out.append(Chunk(tag, off, size, off + 8, size - 8, parent))
        off += size
    return out


def parse_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat(data, 0, len(data), "")
    all_chunks: List[Chunk] = []

    def rec(chunks: List[Chunk]) -> None:
        for c in chunks:
            all_chunks.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    rec(kids)

    rec(roots)
    return all_chunks


def clean_label(raw: bytes) -> Tuple[str, int]:
    chars = []
    highbits = 0
    for i, b in enumerate(raw[:8]):
        if b == 0:
            break
        if b & 0x80:
            highbits |= (1 << i)
        chars.append(chr(b & 0x7f))
    return "".join(chars).strip(), highbits


def f32(data: bytes, off: int) -> float:
    if off + 4 > len(data):
        return 0.0
    return struct.unpack_from("<f", data, off)[0]


@dataclasses.dataclass
class ObjRecord:
    corpus: str
    mission: str
    chunk_offset_hex: str
    parent: str
    label: str
    label_highbits: int
    class_value: int
    pos_x: float
    pos_y: float
    pos_z: float
    raw_name_hex: str


def iter_mission_files(root: Path, mission_filter: str) -> Iterable[Path]:
    if not root.exists():
        return []
    files = [p for p in root.rglob("*") if p.is_file() and p.suffix.lower() in {".msn", ".spc", ".lvl"}]
    if mission_filter:
        mf = mission_filter.lower()
        files = [p for p in files if mf in p.name.lower() or mf in p.stem.lower()]
    return sorted(files)


def collect_object_records(miss8: Optional[Path], miss16: Optional[Path], mission_filter: str) -> List[ObjRecord]:
    roots: List[Tuple[str, Path]] = []
    if miss8:
        roots.append(("miss8", miss8))
    if miss16:
        roots.append(("miss16", miss16))

    rows: List[ObjRecord] = []
    for corpus, root in roots:
        for msn in iter_mission_files(root, mission_filter):
            try:
                data = msn.read_bytes()
                chunks = parse_tree(data)
            except Exception:
                continue
            for c in chunks:
                tag_clean = c.tag.rstrip("\x00")
                if c.parent == "ODEF" and tag_clean == "OBJ" and c.payload_size >= 0x64:
                    payload = data[c.payload_offset:c.end]
                    label, highbits = clean_label(payload[0:8])
                    cls = payload[0x5c] if len(payload) > 0x5c else 0
                    rows.append(ObjRecord(
                        corpus, msn.name, f"0x{c.offset:08x}", c.parent,
                        label, highbits, cls,
                        f32(payload, 0x2c), f32(payload, 0x30), f32(payload, 0x34),
                        payload[0:8].hex()
                    ))
                elif c.parent == "LDEF" and tag_clean == "OBJ" and c.payload_size >= 8:
                    payload = data[c.payload_offset:c.end]
                    label, highbits = clean_label(payload[0:8])
                    rows.append(ObjRecord(
                        corpus, msn.name, f"0x{c.offset:08x}", c.parent,
                        label, highbits, -1,
                        f32(payload, 0x2c) if len(payload) >= 0x30 else 0.0,
                        f32(payload, 0x30) if len(payload) >= 0x34 else 0.0,
                        f32(payload, 0x34) if len(payload) >= 0x38 else 0.0,
                        payload[0:8].hex()
                    ))
    return rows


def classify_candidate(r: ObjRecord) -> Tuple[str, Optional[str]]:
    label = r.label.lower()
    if r.parent == "LDEF":
        if not label:
            return "ldef_blank", None
        return "binary_ldef_sdf", f"{label}.sdf"
    if r.parent == "ODEF":
        if not label or r.class_value == 0:
            return "odef_invalid_or_special_blank_class0", None
        if label == "spawn":
            return "odef_spawn_marker", None
        if label == "regen":
            return "odef_regen_marker", None
        return "binary_odef_vcf", f"{label}.vcf"
    return "unknown", None


def sha1_64k(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        h.update(f.read(65536))
    return h.hexdigest()[:16]


def index_files(roots: List[Path]) -> Tuple[Dict[str, List[Path]], Dict[str, List[Path]], List[Path]]:
    by_name: Dict[str, List[Path]] = {}
    by_base: Dict[str, List[Path]] = {}
    all_files: List[Path] = []
    for root in roots:
        if not root or not root.exists():
            continue
        for p in root.rglob("*"):
            if not p.is_file():
                continue
            all_files.append(p)
            by_name.setdefault(p.name.lower(), []).append(p)
            by_base.setdefault(p.stem.lower(), []).append(p)
    return by_name, by_base, all_files


def parse_zfs_record_names(all_files: List[Path]) -> Dict[str, List[str]]:
    out: Dict[str, List[str]] = {}
    for p in all_files:
        name = p.name.lower()
        if name not in {"zfs_records.tsv", "zfs_extract_manifest.json"}:
            continue
        try:
            if name.endswith(".tsv"):
                with p.open("r", encoding="utf-8", errors="replace", newline="") as f:
                    reader = csv.DictReader(f, delimiter="\t")
                    for row in reader:
                        rn = (row.get("name") or row.get("record_name") or row.get("filename") or "").strip().lower()
                        if rn:
                            out.setdefault(rn, []).append(str(p))
            else:
                obj = json.loads(p.read_text(encoding="utf-8", errors="replace"))
                stack = [obj]
                while stack:
                    x = stack.pop()
                    if isinstance(x, dict):
                        for k, v in x.items():
                            if k.lower() in {"name", "record_name", "filename"} and isinstance(v, str):
                                rn = Path(v).name.lower()
                                if rn:
                                    out.setdefault(rn, []).append(str(p))
                            else:
                                stack.append(v)
                    elif isinstance(x, list):
                        stack.extend(x)
        except Exception:
            pass
    return out


def parse_pix_index(path: Path) -> List[dict]:
    """Best-effort PIX text index parser.

    Binary 00470660 references:
      "*.pix", ".pak", "%d", "%s %d %d"
    so this parser handles text files with a leading count and rows containing
    name offset size in whitespace-separated form. It also tolerates comments and
    extra columns by taking the first token as name and the first two integer tokens.
    """
    try:
        data = path.read_bytes()
    except Exception:
        return []

    # PIX indexes in I76 are expected to be text-ish. Avoid decoding arbitrary huge binary blobs.
    if b"\x00" in data[:256]:
        return []

    text = data.decode("ascii", errors="ignore")
    lines = [ln.strip() for ln in text.splitlines() if ln.strip()]
    if not lines:
        return []

    expected_count = None
    start = 0
    m = re.search(r"[-+]?\d+", lines[0])
    if m and len(lines[0].split()) <= 2:
        try:
            expected_count = int(m.group(0), 10)
            start = 1
        except Exception:
            pass

    rows: List[dict] = []
    for line_no, ln in enumerate(lines[start:], start + 1):
        if ln.startswith("#") or ln.startswith("//"):
            continue
        parts = re.split(r"\s+", ln)
        if not parts:
            continue
        rec_name = parts[0].strip().strip('"').lower()
        if not rec_name or "." not in rec_name:
            continue

        ints = []
        for part in parts[1:]:
            try:
                ints.append(int(part, 0))
            except Exception:
                pass
        offset = ints[0] if len(ints) >= 1 else None
        size = ints[1] if len(ints) >= 2 else None
        rows.append({
            "pix_path": str(path),
            "pak_path": str(path.with_suffix(".pak")),
            "record_name": rec_name,
            "offset": "" if offset is None else str(offset),
            "size": "" if size is None else str(size),
            "line_no": str(line_no),
        })

    if expected_count is not None and rows and abs(len(rows) - expected_count) > max(10, expected_count // 2):
        # Probably not a matching format; keep rows but mark through manifest stats.
        pass
    return rows


def index_pix_records(all_files: List[Path]) -> Dict[str, List[dict]]:
    by_name: Dict[str, List[dict]] = {}
    for p in all_files:
        if p.suffix.lower() != ".pix":
            continue
        for row in parse_pix_index(p):
            by_name.setdefault(row["record_name"], []).append(row)
    return by_name


def write_tsv(path: Path, rows: List[dict], fields: List[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fields, delimiter="\t", extrasaction="ignore")
        w.writeheader()
        for r in rows:
            w.writerow(r)


def should_scan_container(path: Path) -> bool:
    # Avoid report/archive artifacts that caused v8/v9 false positives.
    ext = path.suffix.lower()
    if ext in {".json", ".tsv", ".md", ".txt", ".csv", ".log", ".tar", ".gz", ".zip"}:
        return False
    # Scan only actual resource-ish binaries, not every loose vcf/sdf file.
    return ext in {".pak", ".zfs", ".dat", ".pix"}


def scan_containers(all_files: List[Path], candidates: List[str]) -> List[dict]:
    wanted = sorted(set(c.lower() for c in candidates if c))
    basenames = sorted(set(Path(c).stem.lower() for c in wanted))
    needles = [(c, c.encode("ascii", errors="ignore")) for c in wanted]
    needles += [(b, b.encode("ascii", errors="ignore")) for b in basenames]
    rows: List[dict] = []
    for p in all_files:
        if not should_scan_container(p):
            continue
        try:
            data = p.read_bytes()
        except Exception:
            continue
        lower = data.lower()
        for key, needle in needles:
            if not needle:
                continue
            off = lower.find(needle)
            if off >= 0:
                rows.append({
                    "candidate": key,
                    "container": str(p),
                    "offset": str(off),
                    "offset_hex": f"0x{off:x}",
                    "container_size": str(len(data)),
                    "scan_kind": "filtered_binary_container_scan",
                })
    return rows


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path)
    ap.add_argument("--miss16", type=Path)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--asset-root", type=Path, action="append", default=[])
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--scan-containers", action="store_true")
    ap.add_argument("--make-tar", action="store_true")
    args = ap.parse_args()

    out = args.out_dir
    out.mkdir(parents=True, exist_ok=True)

    records = collect_object_records(args.miss8, args.miss16, args.mission_filter)
    by_name, by_base, all_files = index_files(args.asset_root)
    zfs_names = parse_zfs_record_names(all_files)
    pix_names = index_pix_records(all_files)

    candidate_rows: List[dict] = []
    matches: List[dict] = []
    zfs_matches: List[dict] = []
    pix_matches: List[dict] = []
    unresolved: List[dict] = []
    alternatives: List[dict] = []
    open76_rows: List[dict] = []

    candidate_names: List[str] = []
    for r in records:
        policy, cand = classify_candidate(r)
        base = {
            "corpus": r.corpus,
            "mission": r.mission,
            "chunk_offset_hex": r.chunk_offset_hex,
            "parent": r.parent,
            "label": r.label,
            "label_highbits": str(r.label_highbits),
            "class_hex": "LDEF" if r.class_value < 0 else f"0x{r.class_value:02x}",
            "policy": policy,
            "candidate_name": cand or "",
            "pos_x": f"{r.pos_x:.6f}",
            "pos_y": f"{r.pos_y:.6f}",
            "pos_z": f"{r.pos_z:.6f}",
        }
        candidate_rows.append(base)
        if cand:
            candidate_names.append(cand.lower())

        if policy == "binary_odef_vcf" and r.label:
            odf_sdf = f"{r.label.lower()}.sdf"
            found = by_name.get(odf_sdf, [])
            open76_rows.append({
                **{k: base[k] for k in ["corpus", "mission", "chunk_offset_hex", "label", "class_hex"]},
                "comparison_policy": "open76_odef_sdf_comparison_only",
                "open76_candidate_name": odf_sdf,
                "found_count": str(len(found)),
                "matched_paths": ";".join(str(p) for p in found),
            })

        if not cand:
            unresolved.append(base)
            continue

        loose = by_name.get(cand.lower(), [])
        if loose:
            for p in loose:
                matches.append({
                    **base,
                    "matched_path": str(p),
                    "matched_ext": p.suffix.lower(),
                    "size": str(p.stat().st_size),
                    "sha1_64k": sha1_64k(p),
                    "match_kind": "loose_file",
                })
            continue

        zn = zfs_names.get(cand.lower(), [])
        if zn:
            zfs_matches.append({
                **base,
                "record_name": cand.lower(),
                "record_sources": ";".join(sorted(set(zn))),
                "match_kind": "zfs_record_metadata",
            })
            continue

        pn = pix_names.get(cand.lower(), [])
        if pn:
            for row in pn:
                pix_matches.append({
                    **base,
                    "record_name": cand.lower(),
                    "pix_path": row["pix_path"],
                    "pak_path": row["pak_path"],
                    "pak_exists": str(Path(row["pak_path"]).exists()).lower(),
                    "offset": row["offset"],
                    "size": row["size"],
                    "line_no": row["line_no"],
                    "match_kind": "pix_index_record",
                })
            continue

        unresolved.append(base)

        # Same basename alternatives are diagnostic only.
        for p in by_base.get(Path(cand).stem.lower(), []):
            if p.name.lower() == cand.lower():
                continue
            alternatives.append({
                **base,
                "alternative_name": p.name,
                "alternative_path": str(p),
                "alternative_ext": p.suffix.lower(),
                "alternative_size": str(p.stat().st_size),
                "diagnostic_only": "true",
            })

    container_hits = scan_containers(all_files, candidate_names) if args.scan_containers else []

    write_tsv(out / "binary_candidate_names.tsv", candidate_rows,
              ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","pos_x","pos_y","pos_z"])
    write_tsv(out / "binary_resource_matches.tsv", matches,
              ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","matched_path","matched_ext","size","sha1_64k","match_kind"])
    write_tsv(out / "binary_zfs_record_index_matches.tsv", zfs_matches,
              ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","record_name","record_sources","match_kind"])
    write_tsv(out / "binary_pix_index_matches.tsv", pix_matches,
              ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","record_name","pix_path","pak_path","pak_exists","offset","size","line_no","match_kind"])
    write_tsv(out / "binary_resource_unresolved.tsv", unresolved,
              ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","pos_x","pos_y","pos_z"])
    write_tsv(out / "basename_alternative_matches.tsv", alternatives,
              ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","alternative_name","alternative_path","alternative_ext","alternative_size","diagnostic_only"])
    write_tsv(out / "open76_comparison_odef_sdf.tsv", open76_rows,
              ["corpus","mission","chunk_offset_hex","label","class_hex","comparison_policy","open76_candidate_name","found_count","matched_paths"])
    write_tsv(out / "container_name_hits.tsv", container_hits,
              ["candidate","container","offset","offset_hex","container_size","scan_kind"])

    pix_inventory_rows = []
    for name, rows in sorted(pix_names.items()):
        pix_inventory_rows.append({
            "record_name": name,
            "row_count": str(len(rows)),
            "pix_paths": ";".join(sorted(set(r["pix_path"] for r in rows))[:20]),
        })
    write_tsv(out / "pix_index_inventory.tsv", pix_inventory_rows,
              ["record_name","row_count","pix_paths"])

    ext_counts: Dict[str, int] = {}
    for p in all_files:
        ext_counts[p.suffix.lower() or "<none>"] = ext_counts.get(p.suffix.lower() or "<none>", 0) + 1
    write_tsv(out / "asset_extension_inventory.tsv",
              [{"extension": k, "count": str(v)} for k, v in sorted(ext_counts.items())],
              ["extension", "count"])

    manifest = {
        "format": "i76_resource_acquisition_index_probe",
        "version": 10,
        "mission_filter": args.mission_filter,
        "asset_roots": [str(p) for p in args.asset_root],
        "indexed_files": len(all_files),
        "zfs_record_names_indexed": len(zfs_names),
        "pix_record_names_indexed": len(pix_names),
        "object_records": len(records),
        "binary_candidates": len(candidate_rows),
        "binary_loose_file_matches": len(matches),
        "binary_zfs_record_index_matches": len(zfs_matches),
        "binary_pix_index_matches": len(pix_matches),
        "binary_unresolved": len(unresolved),
        "basename_alternatives": len(alternatives),
        "open76_comparison_rows": len(open76_rows),
        "container_hits": len(container_hits),
        "policy": "ODEF label.vcf; LDEF label.sdf; spawn/regen special; Open76 ODEF label.sdf comparison-only",
        "pix_index_note": "PIX parser is based on 00470660 strings: '*.pix', '.pak', '%d', '%s %d %d'.",
        "container_scan_note": "v10 excludes .tar/.json/.tsv/.md/.txt/.csv/.log report artifacts from byte scans.",
    }
    (out / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    if args.make_tar:
        tar_path = out.with_suffix(".tar")
        with tarfile.open(tar_path, "w") as tf:
            tf.add(out, arcname=out.name)
        manifest["tar_path"] = str(tar_path)
        (out / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    print(json.dumps(manifest, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
