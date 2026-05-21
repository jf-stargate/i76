#!/usr/bin/env python3
"""
Interstate '76 SDF/SOBJ/GEO resolution probe, v4.

Purpose:
  Continue from the ODEF/LDEF placement baseline by resolving placed .sdf resources
  into their child descriptor chunks and likely .geo resources.

This is intentionally a probe, not a final format decoder. It records exact/alias
resource matches, chunk layouts, child payload string candidates, and likely GEO
candidate matches while keeping unresolved or ambiguous rows explicit.
"""
from __future__ import annotations

import argparse
import dataclasses
import hashlib
import json
import os
import re
import struct
import subprocess
import tarfile
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple

PAGE_W = 128
PAGE_H = 128
OBJ_RECORD_PAYLOAD = 100

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF", "SDFC", "VDFC", "GDFC", "WDFC", "VTFC", "VCST"}
KNOWN_TAGS = {
    "BWD2", "VER\x00", "REV\x00", "EXIT",
    "WDEF", "WREV", "WRLD", "TDEF", "TREV", "ZMAP", "ZONE",
    "RDEF", "RREV", "RSEG", "ISEG", "TSEG",
    "ODEF", "OREV", "OBJ\x00", "LDEF", "LREV", "ADEF", "AREV", "FSM\x00",
    "SDFC", "SOBJ", "SGEO", "SCHK", "LOBJ",
    "VDFC", "VSHL", "VLOC", "VGEO", "VCHK", "COLP", "WLOC", "HLOC", "SPCS",
    "GDFC", "GPOF", "GGEO", "ORDF", "OGEO", "WDFC", "WGEO", "VCST", "WLST", "WPST", "SALV",
}

PREFERRED_EXTS_BY_SECTION = {
    "ODEF": [".sdf", ".vcf", ".vdf", ".geo", ".sobj"],
    "LDEF": [".sdf", ".geo", ".sobj"],
}

ASCII_RE = re.compile(rb"[A-Za-z0-9_./\\-]{3,32}")


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def f32(data: bytes, off: int) -> float:
    return struct.unpack_from("<f", data, off)[0]


def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode("latin1", errors="replace")


def clean_tag(tag: str) -> str:
    return tag.replace("\x00", "")


def hexdump(data: bytes, max_len: int = 64) -> str:
    return " ".join(f"{b:02x}" for b in data[:max_len])


def safe_ascii(data: bytes) -> str:
    return "".join(chr(b) if 32 <= b < 127 else "." for b in data)


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


def parse_flat(data: bytes, start: int, end: int, parent: str = "") -> List[Chunk]:
    out: List[Chunk] = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        size = u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        # Do not require known tags; still record plausible chunks.
        out.append(Chunk(tag, off, size, off + 8, size - 8, parent))
        off += size
    return out


def parse_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat(data, 0, len(data), "")
    if not roots:
        return []

    def rec(chunks: List[Chunk]) -> List[Chunk]:
        all_chunks: List[Chunk] = []
        for c in chunks:
            all_chunks.append(c)
            if clean_tag(c.tag) in {clean_tag(x) for x in CONTAINERS} and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, clean_tag(c.tag))
                if kids:
                    all_chunks.extend(rec(kids))
        return all_chunks

    return rec(roots)


def scan_plausible_chunks(data: bytes) -> List[Chunk]:
    """Fallback scanner for resources that are not rooted at offset 0."""
    out: List[Chunk] = []
    for off in range(0, max(0, len(data) - 8)):
        tag = fourcc(data, off)
        if tag not in KNOWN_TAGS:
            continue
        size = u32(data, off + 4)
        if 8 <= size <= len(data) - off:
            out.append(Chunk(tag, off, size, off + 8, size - 8, "SCAN"))
    return out


def extract_ascii_tokens(data: bytes) -> List[str]:
    seen = []
    for m in ASCII_RE.finditer(data):
        s = m.group(0).decode("ascii", errors="ignore").strip("\x00")
        if s and s not in seen:
            seen.append(s)
    return seen


def normalize_name(s: str) -> str:
    s = (s or "").lower().strip()
    s = s.replace("\\", "/").split("/")[-1]
    return s


def alias_keys_for_basename(name: str, ext: str) -> List[str]:
    n = normalize_name(name)
    if "." in n:
        stem = n.rsplit(".", 1)[0]
    else:
        stem = n
    ext = ext.lower()
    keys = []
    def add(k: str):
        k = k.lower()
        if k and k not in keys:
            keys.append(k)
    add(stem + ext)
    add(stem.rstrip("_") + ext)
    if not stem.endswith("1"):
        add(stem + "1" + ext)
        add(stem.rstrip("_") + "1" + ext)
    if "_" in stem:
        add(stem.replace("_", "") + ext)
    # 8-byte truncation common case: foo -> foo1, foo_ -> foo_1 / foo1
    if len(stem) <= 7:
        add((stem + "1") + ext)
    return keys


def index_assets(roots: Sequence[Path]) -> Tuple[Dict[str, List[Path]], Dict[str, List[Path]]]:
    exact: Dict[str, List[Path]] = defaultdict(list)
    alias: Dict[str, List[Path]] = defaultdict(list)
    for root in roots:
        if not root or not root.exists():
            continue
        for p in root.rglob("*"):
            if not p.is_file():
                continue
            key = p.name.lower()
            exact[key].append(p)
            stem = p.stem.lower()
            ext = p.suffix.lower()
            for ak in alias_keys_for_basename(stem, ext):
                alias[ak].append(p)
    return dict(exact), dict(alias)


def resolve_asset(name: str, exts: Sequence[str], exact: Dict[str, List[Path]], alias: Dict[str, List[Path]]):
    attempts = []
    for ext in exts:
        ext = ext.lower()
        raw = normalize_name(name)
        if not raw:
            continue
        candidates = []
        if raw.endswith(ext):
            candidates.append(raw)
        else:
            candidates.append(raw + ext)
        for cand in candidates:
            attempts.append(cand)
            if cand in exact:
                return "exact", cand, exact[cand][0], attempts
        for ak in alias_keys_for_basename(raw, ext):
            attempts.append(ak)
            if ak in alias:
                return "alias", ak, alias[ak][0], attempts
    return "", "", None, attempts


def read_files(root: Path) -> List[Path]:
    if root.is_file():
        return [root]
    return [p for p in root.rglob("*") if p.is_file()]


def first_chunk(chunks: List[Chunk], tag: str) -> Optional[Chunk]:
    for c in chunks:
        if c.tag == tag:
            return c
    return None


def parse_odef_records(data: bytes, chunks: List[Chunk]) -> List[dict]:
    rows = []
    for c in chunks:
        if c.parent == "ODEF" and c.tag == "OBJ\x00" and c.payload_size >= OBJ_RECORD_PAYLOAD:
            p = c.payload_offset
            payload = data[p:p+OBJ_RECORD_PAYLOAD]
            name = payload[:8].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip()
            pos_x = f32(data, p + 0x2c)
            pos_y = f32(data, p + 0x30)
            pos_z = f32(data, p + 0x34)
            cls = payload[0x5c]
            rows.append({
                "section": "ODEF", "record_index": len(rows), "name": name,
                "class_hex": f"0x{cls:02x}", "class_dec": cls,
                "pos_x": pos_x, "pos_y": pos_y, "pos_z": pos_z,
                "payload_size": c.payload_size,
            })
    return rows


def parse_ldef_records(data: bytes, chunks: List[Chunk]) -> List[dict]:
    rows = []
    for c in chunks:
        if c.parent == "LDEF" and c.tag == "OBJ\x00":
            payload = data[c.payload_offset:c.end]
            name = payload[:16].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip()
            rows.append({
                "section": "LDEF", "record_index": len(rows), "name": name,
                "class_hex": "", "class_dec": "",
                "pos_x": "", "pos_y": "", "pos_z": "",
                "payload_size": c.payload_size,
            })
    return rows


def parse_sdf_resource(path: Path, exact: Dict[str, List[Path]], alias: Dict[str, List[Path]]) -> Tuple[List[dict], List[dict], List[dict]]:
    data = path.read_bytes()
    chunks = parse_tree(data)
    if not chunks:
        chunks = scan_plausible_chunks(data)
    chunk_rows = []
    child_rows = []
    geo_rows = []
    for c in chunks:
        payload = data[c.payload_offset:c.end]
        tokens = extract_ascii_tokens(payload)
        u32s = []
        f32s = []
        for i in range(0, min(c.payload_size, 32), 4):
            if c.payload_offset + i + 4 <= len(data):
                u32s.append(f"0x{u32(data, c.payload_offset+i):08x}")
                try:
                    val = f32(data, c.payload_offset+i)
                    if abs(val) < 1e8:
                        f32s.append(f"{val:.6g}")
                except Exception:
                    pass
        chunk_rows.append({
            "sdf_path": str(path), "sdf_name": path.name, "tag": c.tag.replace("\x00", "\\0"),
            "parent": c.parent, "offset_hex": f"0x{c.offset:08x}", "size": c.size,
            "payload_size": c.payload_size, "tokens": ";".join(tokens[:12]),
            "u32_probe": ";".join(u32s), "f32_probe": ";".join(f32s),
            "payload_hex": hexdump(payload, 64), "payload_ascii": safe_ascii(payload[:64]),
        })
        if clean_tag(c.tag) in {"SOBJ", "SGEO", "SDFC", "SCHK", "LOBJ", "VGEO", "GGEO", "OGEO", "WGEO"}:
            child_rows.append(chunk_rows[-1].copy())
        for tok in tokens:
            for ext in [".geo", ".sdf", ".tmt", ".map", ".vdf", ".vcf"]:
                method, key, match, attempts = resolve_asset(tok, [ext], exact, alias)
                if match:
                    geo_rows.append({
                        "sdf_path": str(path), "sdf_name": path.name,
                        "source_tag": c.tag.replace("\x00", "\\0"), "token": tok,
                        "resolved_ext": ext, "method": method, "key": key,
                        "matched_path": str(match),
                    })
    return chunk_rows, child_rows, geo_rows


def write_tsv(path: Path, rows: List[dict], columns: Optional[List[str]] = None):
    path.parent.mkdir(parents=True, exist_ok=True)
    if columns is None:
        cols = []
        for r in rows:
            for k in r.keys():
                if k not in cols:
                    cols.append(k)
    else:
        cols = columns
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(cols) + "\n")
        for r in rows:
            vals = []
            for c in cols:
                v = r.get(c, "")
                s = str(v).replace("\t", " ").replace("\r", " ").replace("\n", " ")
                vals.append(s)
            f.write("\t".join(vals) + "\n")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path)
    ap.add_argument("--miss16", type=Path)
    ap.add_argument("--asset-root", type=Path, action="append", default=[])
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--make-tar", action="store_true")
    args = ap.parse_args()

    out = args.out_dir
    out.mkdir(parents=True, exist_ok=True)

    exact, alias = index_assets(args.asset_root)
    files_by_set = []
    if args.miss8:
        files_by_set.append(("miss8", read_files(args.miss8)))
    if args.miss16:
        files_by_set.append(("miss16", read_files(args.miss16)))

    object_rows = []
    resource_rows = []
    unresolved_rows = []
    sdf_paths: Dict[str, Path] = {}

    for mission_set, files in files_by_set:
        missions = [p for p in files if p.suffix.lower() in {".msn", ".spc", ".lvl"}]
        if args.mission_filter:
            missions = [p for p in missions if args.mission_filter.lower() in p.name.lower()]
        for m in sorted(missions):
            data = m.read_bytes()
            chunks = parse_tree(data)
            recs = parse_odef_records(data, chunks) + parse_ldef_records(data, chunks)
            for r in recs:
                rr = {"mission_set": mission_set, "mission": m.name, **r}
                object_rows.append(rr)
                name = r.get("name", "")
                if not name or name.lower() in {"spawn", "regen"} or r.get("class_hex") == "0x00":
                    unresolved_rows.append({**rr, "reason": "special/blank/class0"})
                    continue
                exts = PREFERRED_EXTS_BY_SECTION.get(r["section"], [".sdf", ".geo"])
                method, key, match, attempts = resolve_asset(name, exts, exact, alias)
                if match:
                    row = {**rr, "method": method, "resolved_key": key, "matched_path": str(match), "matched_ext": match.suffix.lower()}
                    resource_rows.append(row)
                    if match.suffix.lower() == ".sdf":
                        sdf_paths[str(match)] = match
                else:
                    unresolved_rows.append({**rr, "reason": "no resource match", "attempts": ";".join(attempts[:30])})

    sdf_chunk_rows = []
    sdf_child_rows = []
    sdf_geo_rows = []
    for sp in sorted(sdf_paths.values(), key=lambda p: p.name.lower()):
        try:
            cr, chr_, gr = parse_sdf_resource(sp, exact, alias)
            sdf_chunk_rows.extend(cr)
            sdf_child_rows.extend(chr_)
            sdf_geo_rows.extend(gr)
        except Exception as e:
            sdf_chunk_rows.append({"sdf_path": str(sp), "sdf_name": sp.name, "tag": "ERROR", "parent": "", "offset_hex": "", "size": "", "payload_size": "", "tokens": f"{type(e).__name__}: {e}"})

    write_tsv(out / "placement_object_records.tsv", object_rows)
    write_tsv(out / "placement_resource_matches.tsv", resource_rows)
    write_tsv(out / "placement_unresolved.tsv", unresolved_rows)
    write_tsv(out / "sdf_chunk_inventory.tsv", sdf_chunk_rows)
    write_tsv(out / "sdf_child_descriptor_chunks.tsv", sdf_child_rows)
    write_tsv(out / "sdf_geo_resource_candidates.tsv", sdf_geo_rows)

    manifest = {
        "format": "i76_sdf_geo_resolution_probe",
        "version": 4,
        "asset_roots": [str(p) for p in args.asset_root],
        "asset_index_file_count": sum(len(v) for v in exact.values()),
        "object_records": len(object_rows),
        "resource_matches": len(resource_rows),
        "unresolved_rows": len(unresolved_rows),
        "unique_sdf_files": len(sdf_paths),
        "sdf_chunk_rows": len(sdf_chunk_rows),
        "sdf_child_rows": len(sdf_child_rows),
        "sdf_geo_candidate_rows": len(sdf_geo_rows),
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
