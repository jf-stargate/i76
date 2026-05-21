#!/usr/bin/env python3
"""
Interstate '76 runtime mission locator.

Purpose:
  Find files that can feed the Open76-aligned Blender exporter:
    - .MSN / .LVL BWD2 mission streams
    - .TER / sidecar terrain pages
    - hidden BWD2 streams by magic, regardless of extension
    - likely mission directories such as MISSIONS, MISS8, ADDON

Why this exists:
  Retail I76.ZFS commonly contains terrain-adjacent resources such as TAB/LUM/TBL/HZD,
  but the Open76-compatible terrain path needs BWD2 mission streams containing
  TDEF/ZMAP/ZONE and the matching terrain sidecar named by ZONE.

Usage:
  python3 i76_find_runtime_missions.py /path/to/i76/install/or/cd \
    --out-json scratch_data/i76_runtime_mission_scan.json

  python3 i76_find_runtime_missions.py /media/cdrom /media/neon-remote/prj/i76/orig \
    --out-json scratch_data/i76_runtime_mission_scan.json
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import struct
from pathlib import Path
from typing import Iterable, List, Optional, Tuple


MISSION_EXTS = {".msn", ".lvl", ".spc"}
TERRAIN_EXTS = {".ter", ".tab"}
SUPPORT_EXTS = {".hzd", ".npt", ".rtm", ".lum", ".tbl", ".fsi"}
PREFERRED_DIR_NAMES = {"missions", "miss8", "addon", "trip", "scenario", "scenarios"}


def u32(data: bytes, off: int) -> int:
    if off + 4 > len(data):
        raise ValueError("u32 out of range")
    return struct.unpack_from("<I", data, off)[0]


def fourcc(data: bytes, off: int) -> str:
    return data[off:off + 4].decode("ascii", errors="replace")


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


def parse_flat_chunks(data: bytes, start: int = 0, end: Optional[int] = None, parent: str = "") -> List[Chunk]:
    if end is None:
        end = len(data)
    out = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        size = u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        out.append(Chunk(tag, off, size, off + 8, size - 8, parent))
        off += size
    return out


def walk_bwd2_chunks(data: bytes) -> List[Chunk]:
    roots = parse_flat_chunks(data)
    out = []

    def rec(chunks: List[Chunk]):
        for c in chunks:
            out.append(c)
            if c.tag in {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}:
                kids = parse_flat_chunks(data, c.payload_offset, c.end, c.tag)
                if kids:
                    rec(kids)

    rec(roots)
    return out


def decode_zone_name(data: bytes, chunks: List[Chunk]) -> str:
    for c in chunks:
        if c.tag != "ZONE":
            continue
        payload = data[c.payload_offset:c.end]
        candidates = []
        if len(payload) > 1:
            candidates.append(payload[1:].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip())
        if len(payload) > 9:
            candidates.append(payload[9:].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip())
        for s in candidates:
            if s and "." in s:
                return s
        for s in candidates:
            if s:
                return s
    return ""


def decode_zmap_count(data: bytes, chunks: List[Chunk]) -> Optional[int]:
    for c in chunks:
        if c.tag == "ZMAP" and c.payload_size >= 1:
            return data[c.payload_offset]
    return None


def looks_like_bwd2(data: bytes) -> bool:
    if len(data) < 8:
        return False
    if data[:4] != b"BWD2":
        return False
    size = u32(data, 4)
    return 8 <= size <= len(data)


def file_head(path: Path, n: int = 65536) -> bytes:
    try:
        with path.open("rb") as f:
            return f.read(n)
    except Exception:
        return b""


def scan_file(path: Path) -> dict:
    suffix = path.suffix.lower()
    size = path.stat().st_size
    head = file_head(path, min(size, 1024 * 1024))
    is_bwd2 = looks_like_bwd2(head)

    result = {
        "path": str(path),
        "name": path.name,
        "suffix": suffix,
        "size": size,
        "parent": str(path.parent),
        "is_bwd2": is_bwd2,
        "kind": None,
        "tags": [],
        "has_tdef": False,
        "has_zmap": False,
        "has_zone": False,
        "zmap_active_count": None,
        "zone_sidecar_name": "",
    }

    if suffix in MISSION_EXTS:
        result["kind"] = "mission_ext"
    elif suffix in TERRAIN_EXTS:
        result["kind"] = "terrain_sidecar_ext"
    elif suffix in SUPPORT_EXTS:
        result["kind"] = "support_resource_ext"
    elif is_bwd2:
        result["kind"] = "hidden_bwd2"
    else:
        return result

    if is_bwd2:
        data = path.read_bytes()
        chunks = walk_bwd2_chunks(data)
        tags = [c.tag for c in chunks]
        result["tags"] = tags
        result["has_tdef"] = "TDEF" in tags
        result["has_zmap"] = "ZMAP" in tags
        result["has_zone"] = "ZONE" in tags
        result["zmap_active_count"] = decode_zmap_count(data, chunks)
        result["zone_sidecar_name"] = decode_zone_name(data, chunks)

    return result


def find_sidecar(mission: dict, all_files_by_name_lower: dict) -> Optional[str]:
    zone = mission.get("zone_sidecar_name") or ""
    path = Path(mission["path"])
    candidates = []
    if zone:
        candidates.extend([
            path.parent / zone,
            path.parent / zone.upper(),
            path.parent / zone.lower(),
            all_files_by_name_lower.get(zone.lower()),
        ])
    for ext in (".ter", ".tab"):
        candidates.extend([
            path.with_suffix(ext),
            path.with_suffix(ext.upper()),
            all_files_by_name_lower.get(path.stem.lower() + ext),
        ])
    for c in candidates:
        if c and Path(c).exists():
            return str(c)
    return None


def iter_files(roots: Iterable[Path]) -> Iterable[Path]:
    seen = set()
    for root in roots:
        if not root.exists():
            continue
        if root.is_file():
            rp = root.resolve()
            if rp not in seen:
                seen.add(rp)
                yield root
            continue
        for p in root.rglob("*"):
            if p.is_file():
                rp = p.resolve()
                if rp not in seen:
                    seen.add(rp)
                    yield p


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("paths", nargs="+", type=Path, help="Install/CD/resource directories to scan")
    ap.add_argument("--out-json", type=Path, default=Path("i76_runtime_mission_scan.json"))
    ap.add_argument("--max-noninteresting-size", type=int, default=16 * 1024 * 1024,
                    help="Skip extensionless/non-interesting files larger than this unless extension is known")
    args = ap.parse_args()

    files = list(iter_files(args.paths))
    by_name = {p.name.lower(): p for p in files}

    results = []
    skipped_large = 0

    for p in files:
        suffix = p.suffix.lower()
        known = suffix in (MISSION_EXTS | TERRAIN_EXTS | SUPPORT_EXTS)
        if not known and p.stat().st_size > args.max_noninteresting_size:
            skipped_large += 1
            continue
        r = scan_file(p)
        if r["kind"] is not None or r["is_bwd2"]:
            results.append(r)

    missions = [r for r in results if r["is_bwd2"] or r["suffix"] in MISSION_EXTS]
    for m in missions:
        m["matched_sidecar"] = find_sidecar(m, by_name)

    terrain_sidecars = [r for r in results if r["suffix"] in TERRAIN_EXTS]
    support = [r for r in results if r["suffix"] in SUPPORT_EXTS]
    preferred_dirs = sorted({str(Path(r["path"]).parent) for r in results if Path(r["path"]).parent.name.lower() in PREFERRED_DIR_NAMES})

    output = {
        "scan_roots": [str(p) for p in args.paths],
        "file_count_seen": len(files),
        "skipped_large_noninteresting": skipped_large,
        "mission_candidates": missions,
        "terrain_sidecars": terrain_sidecars,
        "support_resources": support,
        "preferred_dirs_seen": preferred_dirs,
        "summary": {
            "mission_candidate_count": len(missions),
            "bwd2_candidate_count": sum(1 for r in results if r["is_bwd2"]),
            "terrain_sidecar_count": len(terrain_sidecars),
            "support_resource_count": len(support),
            "missions_with_tdef_zmap_zone": sum(1 for m in missions if m.get("has_tdef") and m.get("has_zmap") and m.get("has_zone")),
            "missions_with_matched_sidecar": sum(1 for m in missions if m.get("matched_sidecar")),
        },
    }

    args.out_json.parent.mkdir(parents=True, exist_ok=True)
    args.out_json.write_text(json.dumps(output, indent=2), encoding="utf-8")
    print(json.dumps({
        "out_json": str(args.out_json),
        **output["summary"],
        "preferred_dirs_seen": preferred_dirs,
    }, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
