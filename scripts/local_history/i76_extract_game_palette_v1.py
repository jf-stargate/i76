#!/usr/bin/env python3
"""
i76_extract_game_palette_v1.py

Stable extractor for Interstate '76's runtime game palette at VA 004fa170.

This is intentionally simpler and more stable than the broader palette census.
It reads i76.exe, maps VA 0x004fa170 through the PE section table, extracts
256 RGB triplets, and writes a canonical palette path suitable for vehicle
exporter scripts.

Default output:
  scratch_data/palettes/i76_game_palette_004fa170_x4.act
  scratch_data/palettes/i76_game_palette_004fa170_raw.act
  scratch_data/palettes/i76_game_palette_004fa170.tsv

Usage:
  python3 scripts/i76_extract_game_palette_v1.py \
    --exe orig/i76.exe \
    --out-dir scratch_data/palettes

Then use:
  --exporter-arg=--palette-file
  --exporter-arg=scratch_data/palettes/i76_game_palette_004fa170_x4.act
  --exporter-arg=--palette-scale
  --exporter-arg=raw

Why --palette-scale raw?
  The x4 ACT output is already expanded from the game's 0..63-ish RGB range
  to normal external 0..255 RGB.
"""

from __future__ import annotations

import argparse
import csv
import json
import struct
from pathlib import Path
from typing import List, Tuple


GAME_PALETTE_VA = 0x004FA170
PALETTE_SIZE = 256 * 3


def read_u16(data: bytes, off: int) -> int:
    return struct.unpack_from("<H", data, off)[0]


def read_u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def map_va_to_file_offset(pe: bytes, va: int) -> int:
    if pe[:2] != b"MZ":
        raise ValueError("not an MZ executable")

    pe_off = read_u32(pe, 0x3C)
    if pe[pe_off:pe_off + 4] != b"PE\x00\x00":
        raise ValueError("not a PE executable")

    coff = pe_off + 4
    num_sections = read_u16(pe, coff + 2)
    opt_size = read_u16(pe, coff + 16)
    opt = coff + 20

    magic = read_u16(pe, opt)
    if magic == 0x10B:  # PE32
        image_base = read_u32(pe, opt + 28)
    elif magic == 0x20B:  # PE32+
        image_base = struct.unpack_from("<Q", pe, opt + 24)[0]
    else:
        raise ValueError(f"unknown PE optional-header magic: 0x{magic:x}")

    rva = va - image_base
    if rva < 0:
        raise ValueError(f"VA 0x{va:x} is below image base 0x{image_base:x}")

    sec_off = opt + opt_size
    sections = []
    for i in range(num_sections):
        off = sec_off + i * 40
        name = pe[off:off + 8].split(b"\x00", 1)[0].decode("ascii", "replace")
        virtual_size = read_u32(pe, off + 8)
        virtual_address = read_u32(pe, off + 12)
        raw_size = read_u32(pe, off + 16)
        raw_ptr = read_u32(pe, off + 20)
        span = max(virtual_size, raw_size)
        sections.append({
            "name": name,
            "virtual_address": virtual_address,
            "virtual_size": virtual_size,
            "raw_size": raw_size,
            "raw_ptr": raw_ptr,
        })
        if virtual_address <= rva < virtual_address + span:
            file_off = raw_ptr + (rva - virtual_address)
            if file_off < 0 or file_off + PALETTE_SIZE > len(pe):
                raise ValueError(f"mapped file offset 0x{file_off:x} outside executable")
            return file_off

    raise ValueError(
        f"RVA 0x{rva:x} for VA 0x{va:x} was not found in any PE section. "
        f"Sections: {sections}"
    )


def scale_x4(v: int) -> int:
    return max(0, min(255, v * 4))


def write_act(path: Path, entries: List[Tuple[int, int, int]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("wb") as f:
        for r, g, b in entries:
            f.write(bytes([r & 0xFF, g & 0xFF, b & 0xFF]))


def write_tsv(path: Path, raw: List[Tuple[int, int, int]], x4: List[Tuple[int, int, int]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.writer(f, delimiter="\t")
        w.writerow(["index", "raw_r", "raw_g", "raw_b", "x4_r", "x4_g", "x4_b"])
        for i, (rv, xv) in enumerate(zip(raw, x4)):
            w.writerow([i, rv[0], rv[1], rv[2], xv[0], xv[1], xv[2]])


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--exe", required=True, type=Path, help="Path to i76.exe")
    ap.add_argument("--out-dir", default=Path("scratch_data/palettes"), type=Path)
    ap.add_argument("--va", default=f"0x{GAME_PALETTE_VA:x}", help="Palette VA, default 0x004fa170")
    args = ap.parse_args()

    va = int(str(args.va), 0)
    pe = args.exe.read_bytes()
    file_off = map_va_to_file_offset(pe, va)
    pal = pe[file_off:file_off + PALETTE_SIZE]
    if len(pal) != PALETTE_SIZE:
        raise ValueError(f"short palette read: {len(pal)} bytes")

    raw = [(pal[i * 3], pal[i * 3 + 1], pal[i * 3 + 2]) for i in range(256)]
    x4 = [(scale_x4(r), scale_x4(g), scale_x4(b)) for r, g, b in raw]

    out_dir = args.out_dir
    raw_path = out_dir / "i76_game_palette_004fa170_raw.act"
    x4_path = out_dir / "i76_game_palette_004fa170_x4.act"
    tsv_path = out_dir / "i76_game_palette_004fa170.tsv"
    json_path = out_dir / "i76_game_palette_004fa170.json"

    write_act(raw_path, raw)
    write_act(x4_path, x4)
    write_tsv(tsv_path, raw, x4)

    summary = {
        "exe": str(args.exe),
        "va": f"0x{va:08x}",
        "file_offset": f"0x{file_off:x}",
        "raw_act": str(raw_path),
        "x4_act": str(x4_path),
        "tsv": str(tsv_path),
        "raw_min": min(min(c) for c in raw),
        "raw_max": max(max(c) for c in raw),
        "x4_min": min(min(c) for c in x4),
        "x4_max": max(max(c) for c in x4),
    }
    json_path.write_text(json.dumps(summary, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
