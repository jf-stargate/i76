#!/usr/bin/env python3
"""
Interstate '76 resource acquisition index probe, v12 root VCF audit.

Purpose:
  Correct the prior negative result when .vcf files are present directly in the
  extracted ZFS root. This pass explicitly inventories root-level VCF files,
  recursively indexes asset roots, and audits every binary-truth ODEF label.vcf
  candidate against:
    - exact lower-case filename match
    - root-level filename match
    - stem-only alternatives
    - same stem with different extension
    - near root candidates for diagnostic review

This script intentionally keeps the binary-truth policy:
  ODEF dispatch-valid object records -> label.vcf
  ODEF spawn/regen -> special marker
  ODEF blank/class-0 -> special/invalid diagnostic
  LDEF object records -> label.sdf
"""

from __future__ import annotations

import argparse
import csv
import dataclasses
import json
import struct
import tarfile
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
EXTS_OF_INTEREST = {".vcf", ".sdf", ".vdf", ".vtf", ".wdf", ".geo", ".tmt", ".map", ".m16", ".vqm", ".cbk", ".pix", ".pak"}


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

    def rec(chunks: List[Chunk]) -> List[Chunk]:
        all_chunks: List[Chunk] = []
        for c in chunks:
            all_chunks.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    all_chunks.extend(rec(kids))
        return all_chunks

    return rec(roots)


def clean_label(raw: bytes) -> Tuple[str, int]:
    chars: List[str] = []
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


def iter_mission_files(root: Optional[Path], mission_filter: str) -> Iterable[Path]:
    if root is None or not root.exists():
        return []
    files = [p for p in root.rglob("*") if p.is_file() and p.suffix.lower() in {".msn", ".spc", ".lvl"}]
    if mission_filter:
        mf = mission_filter.lower()
        files = [p for p in files if mf in p.name.lower() or mf in p.stem.lower()]
    return sorted(files)


def collect_object_records(miss8: Optional[Path], miss16: Optional[Path], mission_filter: str) -> List[ObjRecord]:
    roots: List[Tuple[str, Optional[Path]]] = [("miss8", miss8), ("miss16", miss16)]
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
                        corpus, msn.name, f"0x{c.offset:08x}", c.parent, label, highbits, cls,
                        f32(payload, 0x2c), f32(payload, 0x30), f32(payload, 0x34), payload[0:8].hex()
                    ))
                elif c.parent == "LDEF" and tag_clean == "OBJ" and c.payload_size >= 8:
                    payload = data[c.payload_offset:c.end]
                    label, highbits = clean_label(payload[0:8])
                    rows.append(ObjRecord(
                        corpus, msn.name, f"0x{c.offset:08x}", c.parent, label, highbits, -1,
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


def index_files(roots: List[Path]) -> Tuple[Dict[str, List[Path]], Dict[str, List[Path]], List[Path], List[Path]]:
    by_name: Dict[str, List[Path]] = {}
    by_stem: Dict[str, List[Path]] = {}
    all_files: List[Path] = []
    root_level_vcfs: List[Path] = []

    for root in roots:
        if not root or not root.exists():
            continue

        if root.is_file():
            files = [root]
            root_dir = root.parent
        else:
            files = [p for p in root.rglob("*") if p.is_file()]
            root_dir = root

        for p in files:
            all_files.append(p)
            by_name.setdefault(p.name.lower(), []).append(p)
            by_stem.setdefault(p.stem.lower(), []).append(p)
            try:
                if p.parent.resolve() == root_dir.resolve() and p.suffix.lower() == ".vcf":
                    root_level_vcfs.append(p)
            except Exception:
                if p.parent == root_dir and p.suffix.lower() == ".vcf":
                    root_level_vcfs.append(p)

    return by_name, by_stem, all_files, sorted(root_level_vcfs)


def file_info(p: Path) -> dict:
    try:
        st = p.stat()
        return {
            "path": str(p),
            "name": p.name,
            "stem": p.stem,
            "ext": p.suffix.lower(),
            "size": str(st.st_size),
            "parent": str(p.parent),
        }
    except Exception:
        return {"path": str(p), "name": p.name, "stem": p.stem, "ext": p.suffix.lower(), "size": "", "parent": str(p.parent)}


def write_tsv(path: Path, rows: List[dict], fields: List[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, delimiter="\t", fieldnames=fields, extrasaction="ignore")
        w.writeheader()
        for r in rows:
            w.writerow(r)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path)
    ap.add_argument("--miss16", type=Path)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--asset-root", type=Path, action="append", default=[])
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--make-tar", action="store_true")
    args = ap.parse_args()

    out = args.out_dir
    out.mkdir(parents=True, exist_ok=True)

    records = collect_object_records(args.miss8, args.miss16, args.mission_filter)
    by_name, by_stem, all_files, root_vcfs = index_files(args.asset_root)

    object_rows: List[dict] = []
    exact_matches: List[dict] = []
    unresolved: List[dict] = []
    stem_alternatives: List[dict] = []
    open76_comparison: List[dict] = []

    for r in records:
        policy, cand = classify_candidate(r)
        base = {
            "corpus": r.corpus,
            "mission": r.mission,
            "chunk_offset_hex": r.chunk_offset_hex,
            "parent": r.parent,
            "label": r.label,
            "raw_name_hex": r.raw_name_hex,
            "label_highbits": str(r.label_highbits),
            "class_hex": "LDEF" if r.class_value < 0 else f"0x{r.class_value:02x}",
            "policy": policy,
            "candidate_name": cand or "",
            "pos_x": f"{r.pos_x:.6f}",
            "pos_y": f"{r.pos_y:.6f}",
            "pos_z": f"{r.pos_z:.6f}",
        }
        object_rows.append(base)

        if policy == "binary_odef_vcf" and r.label:
            sdf = f"{r.label.lower()}.sdf"
            sdf_matches = by_name.get(sdf, [])
            open76_comparison.append({
                **base,
                "comparison_candidate": sdf,
                "found_count": str(len(sdf_matches)),
                "matched_paths": ";".join(str(p) for p in sdf_matches),
            })

        if not cand:
            unresolved.append(base)
            continue

        exact = by_name.get(cand.lower(), [])
        if exact:
            for p in exact:
                exact_matches.append({**base, **{f"matched_{k}": v for k, v in file_info(p).items()}})
            continue

        unresolved.append(base)

        stem = Path(cand).stem.lower()
        for p in by_stem.get(stem, []):
            stem_alternatives.append({
                **base,
                "alternative_name": p.name,
                "alternative_ext": p.suffix.lower(),
                "alternative_path": str(p),
                "alternative_size": str(p.stat().st_size) if p.exists() else "",
                "diagnostic_only": "true",
            })

    root_vcf_rows = [file_info(p) for p in root_vcfs]

    ext_inventory: Dict[str, int] = {}
    for p in all_files:
        ext_inventory[p.suffix.lower()] = ext_inventory.get(p.suffix.lower(), 0) + 1
    ext_rows = [{"ext": k or "<none>", "count": str(v)} for k, v in sorted(ext_inventory.items(), key=lambda kv: (-kv[1], kv[0]))]

    fields_obj = ["corpus", "mission", "chunk_offset_hex", "parent", "label", "raw_name_hex", "label_highbits", "class_hex", "policy", "candidate_name", "pos_x", "pos_y", "pos_z"]
    write_tsv(out / "object_records_binarytruth.tsv", object_rows, fields_obj)
    write_tsv(out / "binary_resource_exact_matches.tsv", exact_matches, fields_obj + ["matched_path", "matched_name", "matched_stem", "matched_ext", "matched_size", "matched_parent"])
    write_tsv(out / "binary_resource_unresolved.tsv", unresolved, fields_obj)
    write_tsv(out / "stem_alternative_matches.tsv", stem_alternatives, fields_obj + ["alternative_name", "alternative_ext", "alternative_path", "alternative_size", "diagnostic_only"])
    write_tsv(out / "open76_comparison_odef_sdf.tsv", open76_comparison, fields_obj + ["comparison_candidate", "found_count", "matched_paths"])
    write_tsv(out / "root_level_vcf_inventory.tsv", root_vcf_rows, ["path", "name", "stem", "ext", "size", "parent"])
    write_tsv(out / "asset_extension_inventory.tsv", ext_rows, ["ext", "count"])

    summary = {
        "format": "i76_resource_acquisition_index_probe_v12_root_vcf_audit",
        "mission_filter": args.mission_filter,
        "asset_roots": [str(p) for p in args.asset_root],
        "indexed_files": len(all_files),
        "root_level_vcf_count": len(root_vcfs),
        "object_records": len(object_rows),
        "binary_exact_matches": len(exact_matches),
        "binary_unresolved": len(unresolved),
        "stem_alternatives": len(stem_alternatives),
        "open76_comparison_rows": len(open76_comparison),
        "outputs": [
            "object_records_binarytruth.tsv",
            "binary_resource_exact_matches.tsv",
            "binary_resource_unresolved.tsv",
            "stem_alternative_matches.tsv",
            "open76_comparison_odef_sdf.tsv",
            "root_level_vcf_inventory.tsv",
            "asset_extension_inventory.tsv",
        ],
    }
    (out / "manifest.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    if args.make_tar:
        tar_path = out.with_suffix(".tar")
        with tarfile.open(tar_path, "w") as tf:
            tf.add(out, arcname=out.name)
        summary["tar_path"] = str(tar_path)
        (out / "manifest.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
        with tarfile.open(tar_path, "w") as tf:
            tf.add(out, arcname=out.name)

    print(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
