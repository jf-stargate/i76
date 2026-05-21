#!/usr/bin/env python3
"""
Interstate '76 object geometry/resource resolution probe, v2.

Scans miss8/miss16 BWD2 mission files for ODEF/OBJ and LDEF/OBJ placement/resource
records, then resolves the short resource names against one or more extracted asset
roots. This is a corpus-side companion to the object geometry reconstruction traces.

v2 changes:
  - Treats missing/placeholder asset roots explicitly in manifest warnings.
  - Builds a case-insensitive recursive filename index over asset roots.
  - Emits per-record candidate suffixes based on current binary evidence.
  - Emits all tried candidate names, not just successful matches.
  - Classifies spawn/regen records separately.
  - Adds mission-filter support that is actually applied to both miss8 and miss16.

This script does not parse PAK/PIX archive internals. Point --asset-root at an extracted
resource tree, not only the raw miss8/miss16 mission directories.
"""
from __future__ import annotations

import argparse
import dataclasses
import json
import os
import struct
import tarfile
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
OBJ_TAGS = {"OBJ\x00", "OBJ"}

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

def f32(data: bytes, off: int) -> float:
    return struct.unpack_from("<f", data, off)[0]

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode("latin1", errors="replace")

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
        out: List[Chunk] = []
        for c in chunks:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    out.extend(rec(kids))
        return out
    return rec(roots)

def cstr8(buf: bytes) -> str:
    return buf[:8].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip()

def find_files(root: Path) -> List[Path]:
    if not root.exists():
        return []
    if root.is_file():
        return [root]
    out = []
    for p in root.rglob("*"):
        if p.is_file():
            out.append(p)
    return out

def build_asset_index(roots: List[Path]) -> Tuple[Dict[str, List[Path]], List[str]]:
    index: Dict[str, List[Path]] = defaultdict(list)
    warnings: List[str] = []
    for root in roots:
        if not root.exists():
            warnings.append(f"asset root does not exist: {root}")
            continue
        if "YOUR_EXTRACTED" in str(root):
            warnings.append(f"asset root appears to be placeholder: {root}")
        for p in find_files(root):
            index[p.name.lower()].append(p)
    return index, warnings

def candidate_suffixes(section: str, class_byte: Optional[int], name: str) -> List[str]:
    lower = name.lower()
    if not lower or lower in {"spawn", "regen"}:
        return []
    # Binary evidence:
    # - ODEF class-dispatch path formats basename+.vcf before load_vehicle_config_for_world_object.
    # - LDEF/OBJ uses .sdf before parse_scene_object_descriptor_resource.
    # - SOBJ child handler loads .geo.
    suffixes: List[str] = []
    if section == "ODEF":
        if class_byte == 0x01:
            suffixes += [".sdf", ".vcf"]
        elif class_byte in {0x02, 0x03, 0x04, 0x07, 0x0A, 0x0B, 0x0C, 0x50, 0x52, 0x53}:
            suffixes += [".vcf", ".sdf", ".geo"]
        else:
            suffixes += [".vcf", ".sdf", ".geo"]
    elif section == "LDEF":
        suffixes += [".sdf", ".geo", ".vcf"]
    else:
        suffixes += [".vcf", ".sdf", ".geo"]
    # Useful supporting resource extensions seen in traces / asset work.
    suffixes += [".sobj", ".sgeo", ".sfc", ".vdf", ".wdf", ".tmt", ".map"]
    seen = set()
    out = []
    for s in suffixes:
        if s not in seen:
            seen.add(s); out.append(s)
    return out

def read_odef_record(mission_set: str, mission: Path, idx: int, payload: bytes) -> Optional[dict]:
    if len(payload) < 0x64:
        return None
    name = cstr8(payload[0:8])
    basis = [f32(payload, 0x08 + i*4) for i in range(9)]
    pos = [f32(payload, 0x2c), f32(payload, 0x30), f32(payload, 0x34)]
    tail_dwords = []
    for off in range(0x38, 0x64, 4):
        tail_dwords.append(u32(payload, off))
    class_byte = payload[0x5c]
    return {
        "mission_set": mission_set,
        "mission": mission.name,
        "section": "ODEF",
        "record_index": idx,
        "name": name,
        "class_byte": class_byte,
        "class_hex": f"0x{class_byte:02x}",
        "pos_x": pos[0], "pos_y": pos[1], "pos_z": pos[2],
        "basis_00": basis[0], "basis_01": basis[1], "basis_02": basis[2],
        "basis_10": basis[3], "basis_11": basis[4], "basis_12": basis[5],
        "basis_20": basis[6], "basis_21": basis[7], "basis_22": basis[8],
        "tail_dwords_hex": " ".join(f"{x:08x}" for x in tail_dwords),
        "raw_hex": payload[:0x64].hex(),
    }

def read_ldef_record(mission_set: str, mission: Path, idx: int, payload: bytes) -> dict:
    name = cstr8(payload[0:8])
    return {
        "mission_set": mission_set,
        "mission": mission.name,
        "section": "LDEF",
        "record_index": idx,
        "name": name,
        "class_byte": None,
        "class_hex": "LDEF",
        "payload_size": len(payload),
        "raw_prefix_hex": payload[:96].hex(),
    }

def scan_missions(root: Path, mission_set: str, mission_filter: str) -> List[dict]:
    rows: List[dict] = []
    if not root.exists():
        return rows
    files = [p for p in root.rglob("*") if p.is_file() and p.suffix.lower() in {".msn", ".lvl", ".spc"}]
    if mission_filter:
        mf = mission_filter.lower()
        files = [p for p in files if mf in p.name.lower() or mf in p.stem.lower()]
    for mission in sorted(files):
        data = mission.read_bytes()
        chunks = parse_tree(data)
        oidx = 0; lidx = 0
        for c in chunks:
            tag_clean = c.tag.rstrip("\x00")
            if tag_clean == "OBJ" and c.parent == "ODEF":
                row = read_odef_record(mission_set, mission, oidx, data[c.payload_offset:c.end])
                if row:
                    rows.append(row)
                oidx += 1
            elif tag_clean == "OBJ" and c.parent == "LDEF":
                rows.append(read_ldef_record(mission_set, mission, lidx, data[c.payload_offset:c.end]))
                lidx += 1
    return rows

def write_tsv(path: Path, rows: List[dict], fields: List[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(fields) + "\n")
        for r in rows:
            vals = []
            for k in fields:
                v = r.get(k, "")
                if isinstance(v, float):
                    vals.append(f"{v:.6f}")
                elif v is None:
                    vals.append("")
                else:
                    vals.append(str(v).replace("\t", " ").replace("\n", " "))
            f.write("\t".join(vals) + "\n")

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path, required=True)
    ap.add_argument("--miss16", type=Path, required=True)
    ap.add_argument("--asset-root", type=Path, action="append", default=[], help="Extracted resource tree. Repeatable.")
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--make-tar", action="store_true")
    args = ap.parse_args()

    out = args.out_dir
    out.mkdir(parents=True, exist_ok=True)
    asset_roots = list(args.asset_root)
    asset_index, warnings = build_asset_index(asset_roots)

    rows = []
    rows += scan_missions(args.miss8, "miss8", args.mission_filter)
    rows += scan_missions(args.miss16, "miss16", args.mission_filter)

    candidates = []
    unresolved = []
    tried = []
    for r in rows:
        name = r.get("name", "")
        class_byte = r.get("class_byte") if r.get("section") == "ODEF" else None
        suffixes = candidate_suffixes(r.get("section", ""), class_byte, name)
        if not suffixes:
            # spawn/regen or blank/special rows.
            unresolved.append({**r, "reason": "no suffix candidates for blank/spawn/regen/special"})
            continue
        found_any = False
        for suf in suffixes:
            cand_name = (name + suf).lower()
            matches = asset_index.get(cand_name, [])
            tried.append({
                "mission_set": r["mission_set"], "mission": r["mission"], "section": r["section"],
                "record_index": r["record_index"], "name": name, "class_hex": r.get("class_hex", ""),
                "candidate_name": cand_name, "match_count": len(matches),
            })
            for p in matches:
                found_any = True
                candidates.append({
                    "mission_set": r["mission_set"], "mission": r["mission"], "section": r["section"],
                    "record_index": r["record_index"], "name": name, "class_hex": r.get("class_hex", ""),
                    "candidate_name": cand_name, "matched_ext": p.suffix.lower(), "path": str(p),
                })
        if not found_any:
            unresolved.append({**r, "reason": "no matching file in indexed asset roots"})

    write_tsv(out / "object_records.tsv", rows, [
        "mission_set","mission","section","record_index","name","class_hex","pos_x","pos_y","pos_z",
        "basis_00","basis_01","basis_02","basis_10","basis_11","basis_12","basis_20","basis_21","basis_22",
        "tail_dwords_hex","payload_size","raw_prefix_hex","raw_hex"
    ])
    write_tsv(out / "object_resource_candidates.tsv", candidates, [
        "mission_set","mission","section","record_index","name","class_hex","candidate_name","matched_ext","path"
    ])
    write_tsv(out / "object_resource_candidate_attempts.tsv", tried, [
        "mission_set","mission","section","record_index","name","class_hex","candidate_name","match_count"
    ])
    write_tsv(out / "unresolved_object_resources.tsv", unresolved, [
        "mission_set","mission","section","record_index","name","class_hex","pos_x","pos_y","pos_z","reason"
    ])

    # Summaries.
    name_counts = Counter((r.get("section",""), r.get("name",""), r.get("class_hex","")) for r in rows)
    summary = [{"section": s, "name": n, "class_hex": c, "count": cnt} for (s,n,c),cnt in name_counts.most_common()]
    write_tsv(out / "object_name_summary.tsv", summary, ["section","name","class_hex","count"])
    class_counts = Counter((r.get("section",""), r.get("class_hex","")) for r in rows)
    class_summary = [{"section": s, "class_hex": c, "count": cnt} for (s,c),cnt in sorted(class_counts.items())]
    write_tsv(out / "object_class_summary.tsv", class_summary, ["section","class_hex","count"])

    manifest = {
        "format": "i76_object_geometry_resolution_probe",
        "version": 2,
        "miss8": str(args.miss8),
        "miss16": str(args.miss16),
        "asset_roots": [str(x) for x in asset_roots],
        "mission_filter": args.mission_filter,
        "asset_index_file_count": sum(len(v) for v in asset_index.values()),
        "unique_asset_filenames": len(asset_index),
        "object_records": len(rows),
        "candidate_matches": len(candidates),
        "candidate_attempts": len(tried),
        "unresolved_rows": len(unresolved),
        "warnings": warnings,
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
