#!/usr/bin/env python3
"""
Interstate '76 object geometry resolution probe v4, binary-source-of-truth policy.

This supersedes the earlier Open76-aligned/alias-heavy object resolver for durable
reconstruction work.  The retail i76.exe binary validation pass showed:

  * ODEF/OBJ uses spawn/regen special handling, otherwise label + ".vcf".
  * LDEF/OBJ uses label + ".sdf".
  * SDF child SOBJ uses partName + ".geo" (handled by the SDF/GEO probe).

Open76-style ODEF label + ".sdf" resolution is still emitted as a comparison aid,
but it is not treated as the binary-backed match.
"""
from __future__ import annotations

import argparse
import dataclasses
import json
import struct
import tarfile
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}

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


def fourcc(data: bytes, off: int) -> str:
    return data[off:off + 4].decode("ascii", errors="replace")


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def f32(data: bytes, off: int) -> float:
    return struct.unpack_from("<f", data, off)[0]


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
    out: List[Chunk] = []

    def rec(chunks: List[Chunk]) -> None:
        for c in chunks:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    rec(kids)

    rec(roots)
    return out


def parse_odef_label(raw: bytes) -> Tuple[str, int, str]:
    """Parse Open76-style 8-byte ODEF label: low 7 bits form chars, high bits are an id mask."""
    chars: List[str] = []
    hi_mask = 0
    raw_hex = raw.hex()
    for i, b in enumerate(raw[:8]):
        if b & 0x80:
            hi_mask |= (1 << i)
        c = b & 0x7f
        if c == 0:
            break
        if 0x20 <= c <= 0x7e:
            chars.append(chr(c))
    return "".join(chars).strip().lower(), hi_mask, raw_hex


def parse_simple_name(raw: bytes) -> str:
    return raw.split(b"\0", 1)[0].decode("ascii", errors="ignore").strip().lower()


def is_spawn_regen(name: str) -> bool:
    return name in {"spawn", "regen"}


def is_invalid_or_special_odef(name: str, cls: int) -> bool:
    return (not name) or cls == 0


def find_files(root: Path) -> List[Path]:
    if root.is_file():
        return [root]
    if not root.exists():
        return []
    return [p for p in root.rglob("*") if p.is_file()]


def index_assets(roots: List[Path]) -> Tuple[Dict[str, List[Path]], List[Path], List[str]]:
    exact: Dict[str, List[Path]] = defaultdict(list)
    files: List[Path] = []
    warnings: List[str] = []
    for root in roots:
        if not root.exists():
            warnings.append(f"asset root does not exist: {root}")
            continue
        for p in find_files(root):
            files.append(p)
            exact[p.name.lower()].append(p)
    return exact, files, warnings


def parse_object_records(msn: Path) -> List[dict]:
    data = msn.read_bytes()
    chunks = parse_tree(data)
    records: List[dict] = []
    odef_idx = 0
    ldef_idx = 0
    for c in chunks:
        if c.parent == "ODEF" and c.tag.startswith("OBJ") and c.payload_size >= 0x64:
            p = c.payload_offset
            label, label_hi_mask, raw_label_hex = parse_odef_label(data[p:p + 8])
            cls = u32(data, p + 0x5c) & 0xff
            tail_words = []
            for i in range(0x38, 0x64, 4):
                tail_words.append(f"0x{u32(data, p + i):08x}")
            records.append({
                "section": "ODEF",
                "record_index": odef_idx,
                "chunk_offset_hex": f"0x{c.offset:08x}",
                "name": label,
                "raw_label_hex": raw_label_hex,
                "label_hi_mask_hex": f"0x{label_hi_mask:02x}",
                "class_hex": f"0x{cls:02x}",
                "class_int": cls,
                "pos_x": f32(data, p + 0x2c),
                "pos_y": f32(data, p + 0x30),
                "pos_z": f32(data, p + 0x34),
                "tail_words": ",".join(tail_words),
                "payload_size": c.payload_size,
            })
            odef_idx += 1
        elif c.parent == "LDEF" and c.tag.startswith("OBJ") and c.payload_size >= 8:
            p = c.payload_offset
            label = parse_simple_name(data[p:p + min(c.payload_size, 32)])
            records.append({
                "section": "LDEF",
                "record_index": ldef_idx,
                "chunk_offset_hex": f"0x{c.offset:08x}",
                "name": label,
                "raw_label_hex": data[p:p + min(c.payload_size, 16)].hex(),
                "label_hi_mask_hex": "",
                "class_hex": "LDEF",
                "class_int": -1,
                "pos_x": "",
                "pos_y": "",
                "pos_z": "",
                "tail_words": "",
                "payload_size": c.payload_size,
            })
            ldef_idx += 1
    return records


def binary_candidate_for_record(rec: dict) -> Tuple[str, str, str]:
    name = str(rec.get("name", ""))
    section = str(rec.get("section", ""))
    cls = int(rec.get("class_int", -1))
    if section == "ODEF":
        if is_spawn_regen(name):
            return "special_marker", "", "spawn_or_regen_no_file"
        if is_invalid_or_special_odef(name, cls):
            return "special_or_invalid", "", "blank_or_class0_no_file"
        return "binary_odef_vcf", f"{name}.vcf", "binary_validated_odef_label_plus_vcf"
    if section == "LDEF":
        if not name:
            return "special_or_invalid", "", "blank_ldef_name"
        return "binary_ldef_sdf", f"{name}.sdf", "binary_validated_ldef_label_plus_sdf"
    return "unknown", "", "unknown_section"


def open76_compat_candidate_for_record(rec: dict) -> Tuple[str, str, str]:
    name = str(rec.get("name", ""))
    section = str(rec.get("section", ""))
    cls = int(rec.get("class_int", -1))
    if section == "ODEF":
        if is_spawn_regen(name):
            return "open76_special_marker", "", "spawn_or_regen_no_file"
        if is_invalid_or_special_odef(name, cls):
            return "open76_special_or_invalid", "", "blank_or_class0_no_file"
        # This is intentionally comparison-only after the binary v31 validation.
        return "open76_compat_odef_sdf", f"{name}.sdf", "comparison_only_open76_noncar_label_plus_sdf"
    if section == "LDEF":
        if not name:
            return "open76_special_or_invalid", "", "blank_ldef_name"
        return "open76_ldef_sdf", f"{name}.sdf", "open76_and_binary_ldef_label_plus_sdf"
    return "unknown", "", "unknown_section"


def write_tsv(path: Path, rows: List[dict], cols: List[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        f.write("\t".join(cols) + "\n")
        for row in rows:
            f.write("\t".join(str(row.get(c, "")) for c in cols) + "\n")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path, required=True)
    ap.add_argument("--miss16", type=Path, required=True)
    ap.add_argument("--asset-root", type=Path, action="append", default=[])
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--make-tar", action="store_true")
    args = ap.parse_args()

    args.out_dir.mkdir(parents=True, exist_ok=True)
    exact, asset_files, warnings = index_assets(args.asset_root)

    records: List[dict] = []
    binary_matches: List[dict] = []
    binary_unresolved: List[dict] = []
    open76_matches: List[dict] = []
    open76_unresolved: List[dict] = []
    attempts: List[dict] = []

    for mission_set, root in [("miss8", args.miss8), ("miss16", args.miss16)]:
        missions = [p for p in find_files(root) if p.suffix.lower() in {".msn", ".spc", ".lvl"}]
        if args.mission_filter:
            flt = args.mission_filter.lower()
            missions = [p for p in missions if flt in p.name.lower() or flt in p.stem.lower()]
        for msn in sorted(missions):
            for rec in parse_object_records(msn):
                rec2 = {"mission_set": mission_set, "mission": msn.name, **rec}
                records.append(rec2)

                policy, cand, reason = binary_candidate_for_record(rec)
                base = {**rec2, "policy": policy, "candidate_name": cand, "policy_reason": reason}
                if cand:
                    matches = exact.get(cand.lower(), [])
                    attempts.append({**base, "candidate_kind": "binary", "match_count": len(matches)})
                    if matches:
                        for p in matches:
                            binary_matches.append({**base, "matched_ext": p.suffix.lower(), "path": str(p)})
                    else:
                        binary_unresolved.append({**base, "unresolved_reason": "binary_candidate_not_found_in_indexed_asset_roots"})
                else:
                    binary_unresolved.append({**base, "unresolved_reason": reason})

                opolicy, ocand, oreason = open76_compat_candidate_for_record(rec)
                obase = {**rec2, "policy": opolicy, "candidate_name": ocand, "policy_reason": oreason}
                if ocand:
                    omatches = exact.get(ocand.lower(), [])
                    attempts.append({**obase, "candidate_kind": "open76_compat", "match_count": len(omatches)})
                    if omatches:
                        for p in omatches:
                            open76_matches.append({**obase, "matched_ext": p.suffix.lower(), "path": str(p)})
                    else:
                        open76_unresolved.append({**obase, "unresolved_reason": "open76_candidate_not_found_in_indexed_asset_roots"})
                else:
                    open76_unresolved.append({**obase, "unresolved_reason": oreason})

    record_cols = ["mission_set", "mission", "section", "record_index", "chunk_offset_hex", "name", "raw_label_hex", "label_hi_mask_hex", "class_hex", "pos_x", "pos_y", "pos_z", "payload_size", "tail_words"]
    match_cols = record_cols + ["policy", "candidate_name", "policy_reason", "matched_ext", "path"]
    unresolved_cols = record_cols + ["policy", "candidate_name", "policy_reason", "unresolved_reason"]

    write_tsv(args.out_dir / "object_records_binarytruth.tsv", records, record_cols)
    write_tsv(args.out_dir / "binary_resource_matches.tsv", binary_matches, match_cols)
    write_tsv(args.out_dir / "binary_resource_unresolved.tsv", binary_unresolved, unresolved_cols)
    write_tsv(args.out_dir / "open76_compat_resource_matches.tsv", open76_matches, match_cols)
    write_tsv(args.out_dir / "open76_compat_resource_unresolved.tsv", open76_unresolved, unresolved_cols)
    write_tsv(args.out_dir / "resource_candidate_attempts.tsv", attempts, record_cols + ["policy", "candidate_name", "policy_reason", "candidate_kind", "match_count"])

    class_counts = Counter((r["section"], r["class_hex"]) for r in records)
    class_rows = [{"section": k[0], "class_hex": k[1], "count": v} for k, v in sorted(class_counts.items())]
    write_tsv(args.out_dir / "object_class_summary.tsv", class_rows, ["section", "class_hex", "count"])

    policy_rows = []
    for name, rows in [
        ("binary_matches", binary_matches),
        ("binary_unresolved", binary_unresolved),
        ("open76_compat_matches", open76_matches),
        ("open76_compat_unresolved", open76_unresolved),
    ]:
        c = Counter(r.get("policy", "") for r in rows)
        for policy, count in sorted(c.items()):
            policy_rows.append({"bucket": name, "policy": policy, "count": count})
    write_tsv(args.out_dir / "resource_policy_summary.tsv", policy_rows, ["bucket", "policy", "count"])

    manifest = {
        "format": "i76_object_geometry_resolution_probe_binarytruth",
        "version": 4,
        "asset_roots": [str(p) for p in args.asset_root],
        "asset_index_file_count": len(asset_files),
        "mission_filter": args.mission_filter,
        "object_records": len(records),
        "binary_matches": len(binary_matches),
        "binary_unresolved": len(binary_unresolved),
        "open76_compat_matches": len(open76_matches),
        "open76_compat_unresolved": len(open76_unresolved),
        "warnings": warnings,
        "policy": {
            "source_of_truth": "retail i76.exe v31 validation",
            "odef": "spawn/regen special; otherwise label + .vcf",
            "ldef": "label + .sdf",
            "sdf_child_sobj": "partName + .geo, handled by SDF/GEO probe",
            "open76_odef_sdf": "comparison-only diagnostic, not binary-backed baseline",
        },
        "outputs": [
            "object_records_binarytruth.tsv",
            "binary_resource_matches.tsv",
            "binary_resource_unresolved.tsv",
            "open76_compat_resource_matches.tsv",
            "open76_compat_resource_unresolved.tsv",
            "resource_candidate_attempts.tsv",
            "object_class_summary.tsv",
            "resource_policy_summary.tsv",
        ],
    }
    (args.out_dir / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    if args.make_tar:
        tar_path = args.out_dir.with_suffix(".tar")
        with tarfile.open(tar_path, "w") as tar:
            tar.add(args.out_dir, arcname=args.out_dir.name)
        manifest["tar_path"] = str(tar_path)
        (args.out_dir / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    print(json.dumps(manifest, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
