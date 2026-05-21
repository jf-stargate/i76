#!/usr/bin/env python3
"""
Interstate '76 I76EDIT exported level parser, v1.

This is intentionally conservative. It parses the .LVL BWD2 chunk stream and,
when a .TER sidecar is supplied, summarizes 128x128 packed terrain-zone rasters.

Known from I76EDIT.EXE:
- .LVL begins with BWD2 chunk stream.
- Chunk header is 8 bytes: 4-byte ASCII tag + uint32 total_size.
- TDEF contains TREV, ZMAP, ZONE, and EXIT chunks.
- ZMAP total size is 0x1909: header + uint8 active_zone_count + 80*80 zone map.
- ZONE total size is 0x16: header + uint8 active_zone_count + char ter_filename[13].
- .TER stores active_zone_count blocks of 0x8000 bytes.
- Each .TER block is 128*128 little-endian uint16.
- uint16 bits: 0..11 height, bit 12 surface flag, bits 13..15 surface class.
"""

from __future__ import annotations

import argparse
import json
import struct
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import List, Dict, Any, Optional, Tuple


CONTAINER_TAGS = {"WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
REVISION_TAGS = {"VER\x00", "VER", "WREV", "TREV", "RREV", "OREV", "LREV", "AREV"}


@dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    children: Optional[List["Chunk"]] = None
    decoded: Optional[Dict[str, Any]] = None


def read_tag(raw: bytes) -> str:
    # Keep printable text, trim NULs for display.
    return raw.decode("latin1", "replace").rstrip("\x00")


def parse_chunks(buf: bytes, start: int, end: int, depth: int = 0) -> List[Chunk]:
    chunks: List[Chunk] = []
    off = start
    while off + 8 <= end:
        raw_tag = buf[off:off + 4]
        tag = read_tag(raw_tag)
        size = struct.unpack_from("<I", buf, off + 4)[0]
        if size < 8:
            chunks.append(Chunk(tag=tag, offset=off, size=size, payload_offset=off + 8, payload_size=0,
                                decoded={"error": "invalid chunk size < 8"}))
            break
        if off + size > end:
            chunks.append(Chunk(tag=tag, offset=off, size=size, payload_offset=off + 8, payload_size=max(0, end - (off + 8)),
                                decoded={"error": f"chunk extends past parse range end=0x{end:x}"}))
            break

        payload_off = off + 8
        payload_size = size - 8
        decoded: Dict[str, Any] = {}

        if tag in {"VER", "WREV", "TREV", "RREV", "OREV", "LREV", "AREV"} and size == 12:
            decoded["revision"] = struct.unpack_from("<I", buf, payload_off)[0]
        elif tag == "ZMAP" and size == 0x1909:
            active = buf[payload_off]
            zmap = buf[payload_off + 1: payload_off + 1 + 80 * 80]
            decoded["active_zone_count"] = active
            decoded["zone_map_width"] = 80
            decoded["zone_map_height"] = 80
            decoded["non_ff_cells"] = sum(1 for b in zmap if b != 0xff)
            decoded["unique_zone_ids"] = sorted(set(int(b) for b in zmap if b != 0xff))
        elif tag == "ZONE" and size == 0x16:
            active = buf[payload_off]
            name_raw = buf[payload_off + 1: payload_off + 14]
            ter_name = name_raw.split(b"\0", 1)[0].decode("latin1", "replace")
            decoded["active_zone_count"] = active
            decoded["ter_filename"] = ter_name
        elif tag == "WRLD":
            decoded["payload_size"] = payload_size
        elif tag == "OBJ":
            decoded["payload_size"] = payload_size
        elif tag == "RSEG":
            decoded["payload_size"] = payload_size
        elif tag == "EXIT":
            decoded["terminator"] = True

        children = None
        if tag in CONTAINER_TAGS and payload_size >= 8:
            children = parse_chunks(buf, payload_off, payload_off + payload_size, depth + 1)

        chunks.append(Chunk(tag=tag, offset=off, size=size, payload_offset=payload_off,
                            payload_size=payload_size, children=children, decoded=decoded or None))
        off += size

        # EXIT is normally a terminator within a container. Continue at top-level,
        # but callers can treat this as a logical end marker.
    return chunks


def chunk_to_dict(c: Chunk) -> Dict[str, Any]:
    d = asdict(c)
    if c.children is not None:
        d["children"] = [chunk_to_dict(x) for x in c.children]
    return d


def find_chunks(chunks: List[Chunk], tag: str) -> List[Chunk]:
    out: List[Chunk] = []
    for c in chunks:
        if c.tag == tag:
            out.append(c)
        if c.children:
            out.extend(find_chunks(c.children, tag))
    return out


def summarize_ter(path: Path, active_zone_count: Optional[int]) -> Dict[str, Any]:
    buf = path.read_bytes()
    block_size = 0x8000
    blocks = len(buf) // block_size
    trailing = len(buf) % block_size
    summaries = []
    for i in range(blocks):
        block = buf[i * block_size:(i + 1) * block_size]
        vals = struct.unpack_from("<" + "H" * (128 * 128), block, 0)
        heights = [v & 0x0fff for v in vals]
        surf_flag = [(v >> 12) & 1 for v in vals]
        surf_class = [(v >> 13) & 0x7 for v in vals]
        summaries.append({
            "zone_index": i,
            "height_min": min(heights),
            "height_max": max(heights),
            "height_avg": sum(heights) / len(heights),
            "surface_flag_count": sum(surf_flag),
            "surface_classes": sorted(set(surf_class)),
        })
    return {
        "path": str(path),
        "size": len(buf),
        "block_size": block_size,
        "blocks": blocks,
        "trailing_bytes": trailing,
        "matches_active_zone_count": (active_zone_count is None or blocks == active_zone_count),
        "zones": summaries,
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("lvl", type=Path, help="Exported .LVL file from I76EDIT")
    ap.add_argument("--ter", type=Path, help="Optional exported .TER sidecar")
    ap.add_argument("--json-out", type=Path, default=None)
    args = ap.parse_args()

    buf = args.lvl.read_bytes()
    chunks = parse_chunks(buf, 0, len(buf))

    zmap_chunks = find_chunks(chunks, "ZMAP")
    zone_descs = find_chunks(chunks, "ZONE")
    active_count = None
    if zmap_chunks and zmap_chunks[0].decoded:
        active_count = zmap_chunks[0].decoded.get("active_zone_count")

    result: Dict[str, Any] = {
        "lvl": str(args.lvl),
        "lvl_size": len(buf),
        "chunks": [chunk_to_dict(c) for c in chunks],
        "zmap": zmap_chunks[0].decoded if zmap_chunks else None,
        "zone_descriptor": zone_descs[0].decoded if zone_descs else None,
    }

    if args.ter:
        result["ter"] = summarize_ter(args.ter, active_count)

    text = json.dumps(result, indent=2)
    if args.json_out:
        args.json_out.write_text(text, encoding="utf-8")
    else:
        print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
