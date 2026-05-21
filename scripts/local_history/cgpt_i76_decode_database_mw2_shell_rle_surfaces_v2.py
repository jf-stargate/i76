#!/usr/bin/env python3
"""
Decode Interstate '76 i76shell.dll simple RLE shell surface records from DATABASE.MW2.

Important correction in v2:
  mpack_database_get_item_alloc_or_alias (i76shell.dll 10008320) does not return raw
  DATABASE.MW2 record bytes. Each packed record begins with a uint32 uncompressed
  size, followed by a 4 KiB-window LZSS-like stream. The shell decodes that stream
  first, then passes the decompressed buffer to the shell bitmap/palette routines.

Based on i76shell.dll routines:
  10008320 mpack_database_get_item_alloc_or_alias
  10039230 load_shell_rle_bitmap_surface_from_database_record
  1003ea06 extract_shell_bitmap_palette_from_buffer
  1003ea31 get_shell_bitmap_dimensions_packed
  1003e984 decode_simple_rle_bitmap_to_shell_surface
"""
from __future__ import annotations

import argparse
import csv
import json
import struct
import sys
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import List, Optional, Tuple

try:
    from PIL import Image
except Exception:  # pragma: no cover
    Image = None


@dataclass
class RecordInfo:
    record_id: int
    offset: int
    packed_size: int


@dataclass
class DecodeInfo:
    record_id: int
    packed_size: int
    unpacked_size: int
    unpack_status: str
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


def u32le(b: bytes, off: int) -> int:
    if off + 4 > len(b):
        raise ValueError("short read")
    return struct.unpack_from("<I", b, off)[0]


def read_database(path: Path) -> Tuple[bytes, List[RecordInfo]]:
    data = path.read_bytes()
    if len(data) < 8:
        raise ValueError("file too small")
    count = u32le(data, 0)
    if count <= 0 or count > 100000:
        raise ValueError(f"implausible record count: {count}")
    table_end = 4 + 4 * count
    if table_end > len(data):
        raise ValueError("offset table exceeds file size")
    offs = [u32le(data, 4 + 4 * i) for i in range(count)]
    recs: List[RecordInfo] = []
    for i, off in enumerate(offs):
        end = offs[i + 1] if i + 1 < count else len(data)
        if not (0 <= off <= end <= len(data)):
            raise ValueError(f"bad offset range for record {i+1}: {off:#x}..{end:#x}")
        recs.append(RecordInfo(i + 1, off, end - off))
    return data, recs


def parse_record_spec(spec: str) -> List[int]:
    out: List[int] = []
    for part in spec.split(','):
        part = part.strip()
        if not part:
            continue
        if '-' in part:
            a, b = part.split('-', 1)
            aa, bb = int(a, 0), int(b, 0)
            if bb < aa:
                aa, bb = bb, aa
            out.extend(range(aa, bb + 1))
        else:
            out.append(int(part, 0))
    return sorted(set(out))


def decompress_mpack_record(raw: bytes) -> Tuple[Optional[bytes], str]:
    """Return decompressed DATABASE.MW2 record payload per i76shell.dll 10008320.

    Raw record layout:
      uint32_t unpacked_size;
      uint8_t  lz_stream[];

    LZ stream:
      4 KiB zero-initialized ring buffer.
      Flags are consumed LSB-first from bytes ORed with 0x100.
      flag bit 1 => literal byte
      flag bit 0 => 2-byte copy token: low 12 bits offset, high 4 bits length-3
    """
    if len(raw) < 4:
        return None, "too_small_for_unpacked_size"
    expected = u32le(raw, 0)
    if expected > 64 * 1024 * 1024:
        return None, f"implausible_unpacked_size_{expected}"
    src = 4
    flags = 2
    ring = bytearray(0x1000)
    rp = 0
    out = bytearray()

    try:
        while len(out) < expected:
            flags >>= 1
            if flags == 1:
                if src >= len(raw):
                    return bytes(out), f"truncated_flags_at_{src}_expected_{expected}_got_{len(out)}"
                flags = raw[src] | 0x100
                src += 1
            if (flags & 1) == 0:
                if src + 2 > len(raw):
                    return bytes(out), f"truncated_copy_token_at_{src}_expected_{expected}_got_{len(out)}"
                token = raw[src] | (raw[src + 1] << 8)
                src += 2
                length = ((token >> 12) & 0x0F) + 3
                cp = token & 0x0FFF
                for _ in range(length):
                    if len(out) >= expected:
                        break
                    v = ring[cp]
                    out.append(v)
                    ring[rp] = v
                    rp = (rp + 1) & 0x0FFF
                    cp = (cp + 1) & 0x0FFF
            else:
                if src >= len(raw):
                    return bytes(out), f"truncated_literal_at_{src}_expected_{expected}_got_{len(out)}"
                v = raw[src]
                src += 1
                out.append(v)
                ring[rp] = v
                rp = (rp + 1) & 0x0FFF
    except Exception as e:
        return bytes(out), f"decompress_exception_{type(e).__name__}_{e}"

    extra = len(raw) - src
    return bytes(out), "ok" if extra >= 0 else "ok_overread_impossible"


def decode_shell_rle(buf: bytes, packed_size: int, unpack_status: str, *, max_pixels: int = 2_000_000) -> Tuple[Optional[bytes], DecodeInfo]:
    size = len(buf)
    base = DecodeInfo(0, packed_size, size, unpack_status, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, max(size - 0x300, 0), "raw8_shift_right_2_then_left_2", 0, "skip", "")
    if unpack_status != "ok":
        base.warning = unpack_status
        return None, base
    if size < 0x380:
        base.warning = "too small after decompression"
        return None, base
    try:
        min_x = u16le(buf, 4)
        min_y = u16le(buf, 6)
        max_x = u16le(buf, 8)
        max_y = u16le(buf, 10)
        line_width = u16le(buf, 0x42)
    except Exception as e:
        base.warning = str(e)
        return None, base

    width = max_x - min_x + 1
    height = max_y - min_y + 1
    info = DecodeInfo(0, packed_size, size, unpack_status, min_x, min_y, max_x, max_y, width, height, line_width, 0, 0x80, size - 0x300, "raw8_shift_right_2_then_left_2", 0, "skip", "")
    if width <= 0 or height <= 0 or line_width <= 0:
        info.warning = "non-positive dimensions"
        return None, info
    if width > 4096 or height > 4096 or line_width > 4096 or height * line_width > max_pixels:
        info.warning = "implausible dimensions"
        return None, info

    src = 0x80
    palette_off = size - 0x300
    if palette_off <= src:
        info.warning = "no room before trailing palette"
        return None, info

    pixels = bytearray(height * line_width)
    warn: List[str] = []
    for y in range(height):
        x = 0
        while x < line_width:
            if src >= palette_off:
                warn.append(f"ran into palette at row {y}, x {x}")
                info.rows_decoded = y
                info.consumed_bytes = src - 0x80
                info.status = "partial"
                info.warning = "; ".join(warn)
                return bytes(pixels), info
            control = buf[src]
            src += 1
            if (control & 0xC0) == 0xC0:
                count = control & 0x3F
                if count == 0:
                    warn.append(f"zero-length run at row {y}, x {x}")
                    continue
                if src >= palette_off:
                    warn.append(f"run missing value at row {y}, x {x}")
                    info.rows_decoded = y
                    info.consumed_bytes = src - 0x80
                    info.status = "partial"
                    info.warning = "; ".join(warn)
                    return bytes(pixels), info
                value = buf[src]
                src += 1
                n = min(count, line_width - x)
                pixels[y * line_width + x:y * line_width + x + n] = bytes([value]) * n
                x += n
                if n != count:
                    warn.append(f"run clipped at row {y}")
            else:
                pixels[y * line_width + x] = control
                x += 1

    info.rows_decoded = height
    info.consumed_bytes = src - 0x80
    info.status = "ok" if not warn else "ok_with_warnings"
    info.warning = "; ".join(warn)
    return bytes(pixels), info


def palette_from_trailing_rgb8(buf: bytes) -> List[Tuple[int, int, int]]:
    raw = buf[-0x300:]
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
    raw_dir = out / "decompressed_records"
    png_dir.mkdir(parents=True, exist_ok=True)
    pal_dir.mkdir(parents=True, exist_ok=True)
    raw_dir.mkdir(parents=True, exist_ok=True)

    infos: List[DecodeInfo] = []
    decoded = 0
    for rec in recs:
        if rec.record_id not in wanted:
            continue
        raw = data[rec.offset:rec.offset + rec.packed_size]
        unpacked, unpack_status = decompress_mpack_record(raw)
        if unpacked is None:
            unpacked = b""
        # Save decompressed payloads for records that the caller explicitly requested.
        if args.records:
            (raw_dir / f"rec{rec.record_id:03d}_unpacked_{len(unpacked)}_{unpack_status}.bin").write_bytes(unpacked)
        pixels, info = decode_shell_rle(unpacked, rec.packed_size, unpack_status, max_pixels=args.max_pixels)
        info.record_id = rec.record_id
        infos.append(info)
        if pixels is None or not info.status.startswith("ok"):
            continue
        decoded += 1
        crop_w = info.width_from_bounds if args.crop_to_bounds_width else None
        modes = ["rgb8_trailing", "rgb6_trailing"] if args.palette_mode == "both" else [args.palette_mode]
        for mode in modes:
            pal = palette_from_trailing_rgb8(unpacked) if mode == "rgb8_trailing" else palette_from_trailing_rgb6(unpacked)
            write_pal(pal_dir / f"rec{rec.record_id:03d}_{mode}.pal", pal)
            save_png(
                png_dir / f"rec{rec.record_id:03d}_{mode}_{info.line_width}x{info.height_from_bounds}.png",
                pixels,
                info.line_width,
                info.height_from_bounds,
                pal,
                crop_w,
            )

    fields = list(asdict(infos[0]).keys()) if infos else ["record_id"]
    with (out / "surface_records.tsv").open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fields, delimiter="\t")
        writer.writeheader()
        for info in infos:
            writer.writerow(asdict(info))
    (out / "summary.json").write_text(json.dumps({
        "database": str(args.database),
        "records_considered": len(wanted),
        "records_scanned": len(infos),
        "records_decoded_ok": decoded,
        "palette_modes": args.palette_mode,
        "record_processing": "DATABASE.MW2 offset table -> mpack LZ decompression -> shell RLE surface decode",
    }, indent=2))
    print(f"[+] decoded {decoded} shell RLE surface record(s) into {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
