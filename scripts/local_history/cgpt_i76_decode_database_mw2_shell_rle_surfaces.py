#!/usr/bin/env python3
"""
Decode Interstate '76 i76shell.dll simple RLE shell surface records from DATABASE.MW2.

Based on i76shell.dll routines:
  10039230 load_shell_rle_bitmap_surface_from_database_record
  1003ea06 extract_shell_bitmap_palette_from_buffer
  1003ea31 get_shell_bitmap_dimensions_packed
  1003e984 decode_simple_rle_bitmap_to_shell_surface

DATABASE.MW2 records are 1-based. This decoder scans records by default and writes
PNG/contact-friendly outputs for records that look like this shell bitmap format.
"""
from __future__ import annotations

import argparse
import csv
import json
import struct
import sys
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Iterable, List, Optional, Tuple

try:
    from PIL import Image
except Exception as e:  # pragma: no cover
    Image = None


@dataclass
class RecordInfo:
    record_id: int
    offset: int
    size: int


@dataclass
class DecodeInfo:
    record_id: int
    size: int
    min_x: int
    min_y: int
    max_x: int
    max_y: int
    width_from_bounds: int
    height_from_bounds: int
    line_width: int
    rows_decoded: int
    compressed_start: int
    palette_offset: int
    palette_mode: str
    consumed_bytes: int
    status: str
    warning: str = ""


def u16le(b: bytes, off: int) -> int:
    if off + 2 > len(b):
        raise ValueError("short read")
    return struct.unpack_from("<H", b, off)[0]


def read_database(path: Path) -> Tuple[bytes, List[RecordInfo]]:
    data = path.read_bytes()
    if len(data) < 8:
        raise ValueError("file too small")
    count = struct.unpack_from("<I", data, 0)[0]
    if count <= 0 or count > 100000:
        raise ValueError(f"implausible record count: {count}")
    table_end = 4 + 4 * count
    if table_end > len(data):
        raise ValueError("offset table exceeds file size")
    offs = list(struct.unpack_from("<" + "I" * count, data, 4))
    recs: List[RecordInfo] = []
    for i, off in enumerate(offs):
        end = offs[i + 1] if i + 1 < count else len(data)
        if not (0 <= off <= end <= len(data)):
            # Keep parsing strict because corrupt offsets make record IDs unreliable.
            raise ValueError(f"bad offset range for record {i+1}: {off:#x}..{end:#x}")
        recs.append(RecordInfo(i + 1, off, end - off))
    return data, recs


def parse_record_spec(spec: str) -> List[int]:
    out: List[int] = []
    for part in spec.split(","):
        part = part.strip()
        if not part:
            continue
        if "-" in part:
            a, b = part.split("-", 1)
            aa = int(a, 0)
            bb = int(b, 0)
            if bb < aa:
                aa, bb = bb, aa
            out.extend(range(aa, bb + 1))
        else:
            out.append(int(part, 0))
    return sorted(set(out))


def decode_shell_rle(buf: bytes, *, max_pixels: int = 2_000_000) -> Tuple[Optional[bytes], DecodeInfo]:
    size = len(buf)
    if size < 0x380:
        return None, DecodeInfo(0, size, 0, 0, 0, 0, 0, 0, 0, 0, max(size - 0x300, 0), "raw8_shift_right_2_then_left_2", 0, "skip", "too small")
    try:
        min_x = u16le(buf, 4)
        min_y = u16le(buf, 6)
        max_x = u16le(buf, 8)
        max_y = u16le(buf, 10)
        line_width = u16le(buf, 0x42)
    except Exception as e:
        return None, DecodeInfo(0, size, 0, 0, 0, 0, 0, 0, 0, 0, max(size - 0x300, 0), "raw8_shift_right_2_then_left_2", 0, "skip", str(e))

    width = max_x - min_x + 1
    height = max_y - min_y + 1
    if width <= 0 or height <= 0 or line_width <= 0:
        return None, DecodeInfo(0, size, min_x, min_y, max_x, max_y, width, height, line_width, 0, 0x80, size - 0x300, "raw8_shift_right_2_then_left_2", 0, "skip", "non-positive dimensions")
    if width > 4096 or height > 4096 or line_width > 4096 or height * line_width > max_pixels:
        return None, DecodeInfo(0, size, min_x, min_y, max_x, max_y, width, height, line_width, 0, 0x80, size - 0x300, "raw8_shift_right_2_then_left_2", 0, "skip", "implausible dimensions")

    src = 0x80
    palette_off = size - 0x300
    if palette_off <= src:
        return None, DecodeInfo(0, size, min_x, min_y, max_x, max_y, width, height, line_width, 0, src, palette_off, "raw8_shift_right_2_then_left_2", 0, "skip", "no room before trailing palette")

    pixels = bytearray(height * line_width)
    warn = []
    for y in range(height):
        x = 0
        while x < line_width:
            if src >= palette_off:
                warn.append(f"ran into palette at row {y}, x {x}")
                return bytes(pixels), DecodeInfo(0, size, min_x, min_y, max_x, max_y, width, height, line_width, y, 0x80, palette_off, "raw8_shift_right_2_then_left_2", src - 0x80, "partial", "; ".join(warn))
            control = buf[src]
            src += 1
            if (control & 0xC0) == 0xC0:
                count = control & 0x3F
                if count == 0:
                    warn.append(f"zero-length run at row {y}, x {x}")
                    continue
                if src >= palette_off:
                    warn.append(f"run missing value at row {y}, x {x}")
                    return bytes(pixels), DecodeInfo(0, size, min_x, min_y, max_x, max_y, width, height, line_width, y, 0x80, palette_off, "raw8_shift_right_2_then_left_2", src - 0x80, "partial", "; ".join(warn))
                value = buf[src]
                src += 1
                n = min(count, line_width - x)
                pixels[y * line_width + x : y * line_width + x + n] = bytes([value]) * n
                x += n
                if n != count:
                    warn.append(f"run clipped at row {y}")
            else:
                pixels[y * line_width + x] = control
                x += 1
    status = "ok" if not warn else "ok_with_warnings"
    return bytes(pixels), DecodeInfo(0, size, min_x, min_y, max_x, max_y, width, height, line_width, height, 0x80, palette_off, "raw8_shift_right_2_then_left_2", src - 0x80, status, "; ".join(warn))


def palette_from_trailing_rgb8(buf: bytes) -> List[Tuple[int, int, int]]:
    raw = buf[-0x300:]
    # 1003ea06 stores raw >> 2 into surface palette; backend later shifts left by 2.
    # This reproduces that quantized RGB8 result.
    return [((raw[i] >> 2) << 2, (raw[i+1] >> 2) << 2, (raw[i+2] >> 2) << 2) for i in range(0, 0x300, 3)]


def palette_from_trailing_rgb6(buf: bytes) -> List[Tuple[int, int, int]]:
    raw = buf[-0x300:]
    return [(min(raw[i] << 2, 255), min(raw[i+1] << 2, 255), min(raw[i+2] << 2, 255)) for i in range(0, 0x300, 3)]


def write_pal(path: Path, pal: List[Tuple[int, int, int]]) -> None:
    path.write_bytes(bytes([c for rgb in pal for c in rgb]))


def save_png(path: Path, pixels: bytes, w: int, h: int, palette: List[Tuple[int, int, int]], crop_w: Optional[int]) -> None:
    if Image is None:
        raise RuntimeError("Pillow is required to write PNGs: pip install pillow")
    img = Image.frombytes("P", (w, h), pixels)
    flat = [c for rgb in palette for c in rgb]
    flat.extend([0] * (768 - len(flat)))
    img.putpalette(flat[:768])
    if crop_w is not None and 0 < crop_w <= w and crop_w != w:
        img = img.crop((0, 0, crop_w, h))
    img.save(path)


def main() -> int:
    ap = argparse.ArgumentParser(description="Decode i76shell simple RLE surface records from DATABASE.MW2")
    ap.add_argument("database", type=Path)
    ap.add_argument("out_dir", type=Path)
    ap.add_argument("--records", default="", help="Comma/range list of 1-based record IDs. Default: scan all records.")
    ap.add_argument("--palette-mode", choices=["rgb8_trailing", "rgb6_trailing", "both"], default="both")
    ap.add_argument("--crop-to-bounds-width", action="store_true", help="Crop output width to max_x-min_x+1 when line_width is wider.")
    ap.add_argument("--max-pixels", type=int, default=2_000_000)
    args = ap.parse_args()

    if Image is None:
        print("error: Pillow is required to write PNGs. Install with: pip install pillow", file=sys.stderr)
        return 2

    data, recs = read_database(args.database)
    wanted = set(parse_record_spec(args.records)) if args.records else {r.record_id for r in recs}

    out = args.out_dir
    png_dir = out / "png"
    pal_dir = out / "palettes"
    png_dir.mkdir(parents=True, exist_ok=True)
    pal_dir.mkdir(parents=True, exist_ok=True)

    infos: List[DecodeInfo] = []
    decoded = 0
    for rec in recs:
        if rec.record_id not in wanted:
            continue
        buf = data[rec.offset : rec.offset + rec.size]
        pixels, info = decode_shell_rle(buf, max_pixels=args.max_pixels)
        info.record_id = rec.record_id
        infos.append(info)
        if pixels is None or not info.status.startswith("ok"):
            continue
        decoded += 1
        crop_w = info.width_from_bounds if args.crop_to_bounds_width else None
        modes = ["rgb8_trailing", "rgb6_trailing"] if args.palette_mode == "both" else [args.palette_mode]
        for mode in modes:
            pal = palette_from_trailing_rgb8(buf) if mode == "rgb8_trailing" else palette_from_trailing_rgb6(buf)
            write_pal(pal_dir / f"rec{rec.record_id:03d}_{mode}.pal", pal)
            save_png(
                png_dir / f"rec{rec.record_id:03d}_{mode}_{info.line_width}x{info.height_from_bounds}.png",
                pixels,
                info.line_width,
                info.height_from_bounds,
                pal,
                crop_w,
            )

    with (out / "surface_records.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(asdict(infos[0]).keys()) if infos else ["record_id"] , delimiter="\t")
        writer.writeheader()
        for info in infos:
            writer.writerow(asdict(info))
    (out / "summary.json").write_text(json.dumps({
        "database": str(args.database),
        "records_considered": len(wanted),
        "records_scanned": len(infos),
        "records_decoded_ok": decoded,
        "palette_modes": args.palette_mode,
    }, indent=2))
    print(f"[+] decoded {decoded} shell RLE surface record(s) into {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
