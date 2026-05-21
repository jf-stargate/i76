#!/usr/bin/env python3
"""
Apply palettes extracted from compressed shell RLE surface records in DATABASE.MW2
(records such as 6-13,16,32) to decoded DATABASE.MW2 1.10 image resources
(records such as 0x24-0x40 / decimal 36-64).

This bridges the confirmed shell surface palette path with the previously
decoded 1.10 menu/UI sprite path.

Outputs per selected shell surface palette:
  - extracted palette (.pal RGB768)
  - decoded 1.10 indexed PNGs
  - decoded 1.10 RGB PNGs using that palette
  - TSV/JSON manifests
"""

from __future__ import annotations

import argparse
import csv
import json
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional

try:
    from PIL import Image
except Exception as e:
    raise SystemExit(f"This script requires Pillow: pip install pillow\n{e}")


def read_u32le(b: bytes, off: int) -> int:
    return struct.unpack_from("<I", b, off)[0]


def parse_record_spec(spec: str) -> List[int]:
    out: List[int] = []
    for part in spec.split(","):
        part = part.strip()
        if not part:
            continue
        if "-" in part:
            a, b = part.split("-", 1)
            start = int(a, 0)
            end = int(b, 0)
            step = 1 if end >= start else -1
            out.extend(range(start, end + step, step))
        else:
            out.append(int(part, 0))

    seen = set()
    uniq = []
    for x in out:
        if x not in seen:
            uniq.append(x)
            seen.add(x)
    return uniq


class DatabaseMW2:
    def __init__(self, path: Path):
        self.path = path
        self.data = path.read_bytes()
        if len(self.data) < 8:
            raise ValueError("file too small")

        self.record_count = read_u32le(self.data, 0)
        table_end = 4 + self.record_count * 4
        if self.record_count <= 0 or table_end > len(self.data):
            raise ValueError(f"invalid DATABASE.MW2 record table: count={self.record_count}")

        self.offsets = [read_u32le(self.data, 4 + 4 * i) for i in range(self.record_count)]

    def get_raw_record(self, record_id: int) -> bytes:
        if record_id < 1 or record_id > self.record_count:
            raise IndexError(f"record id {record_id} out of range 1..{self.record_count}")

        idx = record_id - 1
        start = self.offsets[idx]
        end = self.offsets[idx + 1] if idx + 1 < self.record_count else len(self.data)

        if not (0 <= start <= end <= len(self.data)):
            raise ValueError(f"invalid record range for record {record_id}: {start:#x}-{end:#x}")

        return self.data[start:end]


def mpack_lz_decompress(raw_record: bytes) -> bytes:
    """
    DATABASE.MW2 shell mpack record decompression.

    Format inferred from i76shell.dll:
      uint32_le uncompressed_size
      LZSS-like stream with 4 KiB ring window
    """
    if len(raw_record) < 4:
        raise ValueError("compressed record too small")

    out_size = read_u32le(raw_record, 0)
    src = memoryview(raw_record)[4:]
    src_pos = 0

    window = bytearray([0] * 0x1000)
    win_pos = 0x0FEE

    out = bytearray()
    flags = 0
    bits_left = 0

    while len(out) < out_size:
        if bits_left == 0:
            if src_pos >= len(src):
                raise ValueError(f"compressed stream ended early at {len(out)}/{out_size}")
            flags = src[src_pos]
            src_pos += 1
            bits_left = 8

        bit = flags & 1
        flags >>= 1
        bits_left -= 1

        if bit:
            if src_pos >= len(src):
                raise ValueError("compressed stream ended during literal")
            c = src[src_pos]
            src_pos += 1
            out.append(c)
            window[win_pos] = c
            win_pos = (win_pos + 1) & 0x0FFF
        else:
            if src_pos + 1 >= len(src):
                raise ValueError("compressed stream ended during backref")
            b1 = src[src_pos]
            b2 = src[src_pos + 1]
            src_pos += 2

            ref = b1 | ((b2 & 0xF0) << 4)
            count = (b2 & 0x0F) + 3

            for _ in range(count):
                c = window[ref]
                ref = (ref + 1) & 0x0FFF
                out.append(c)
                window[win_pos] = c
                win_pos = (win_pos + 1) & 0x0FFF
                if len(out) >= out_size:
                    break

    return bytes(out)


def extract_shell_surface_palette_rgb8(decompressed_payload: bytes) -> bytes:
    """
    Shell RLE surface records carry a trailing RGB8 palette.

    i76shell.dll internally stores this as RGB6 via src_byte >> 2,
    but for PNG/export display the trailing RGB8 bytes are the correct
    visual interpretation.
    """
    if len(decompressed_payload) < 0x300:
        raise ValueError("shell surface payload too small for trailing palette")
    return decompressed_payload[-0x300:]


@dataclass
class Decoded110Subresource:
    record_id: int
    sub_index: int
    origin_x: int
    origin_y: int
    max_x: int
    max_y: int
    width: int
    height: int
    image: Image.Image
    decode_warnings: List[str]


def make_indexed_image(width: int, height: int, pixels: bytes) -> Image.Image:
    img = Image.frombytes("P", (width, height), pixels)
    pal = []
    for i in range(256):
        pal.extend([i, i, i])
    img.putpalette(pal)
    return img


def apply_rgb_palette(indexed_img: Image.Image, palette_rgb768: bytes, transparent_index: Optional[int] = None) -> Image.Image:
    if len(palette_rgb768) != 768:
        raise ValueError("palette must be exactly 768 bytes RGB")

    src = indexed_img.convert("P")
    idx = src.tobytes()
    rgba = bytearray(len(idx) * 4)

    for i, px in enumerate(idx):
        base = px * 3
        rgba[i * 4 + 0] = palette_rgb768[base + 0]
        rgba[i * 4 + 1] = palette_rgb768[base + 1]
        rgba[i * 4 + 2] = palette_rgb768[base + 2]
        rgba[i * 4 + 3] = 0 if transparent_index is not None and px == transparent_index else 255

    return Image.frombytes("RGBA", src.size, bytes(rgba))


def decode_110_subresource(record_id: int, record_payload: bytes, sub_index: int) -> Decoded110Subresource:
    warnings: List[str] = []

    if len(record_payload) < 16:
        raise ValueError("1.10 record too small")
    if record_payload[:4] != b"1.10":
        raise ValueError("record does not start with '1.10'")

    count = read_u32le(record_payload, 4)
    if sub_index < 0 or sub_index >= count:
        raise IndexError(f"sub_index {sub_index} out of range 0..{count - 1}")

    entry_off = 8 + sub_index * 8
    if entry_off + 8 > len(record_payload):
        raise ValueError("subresource table truncated")

    sub_off = read_u32le(record_payload, entry_off)
    if sub_off + 0x18 > len(record_payload):
        raise ValueError(f"subresource offset {sub_off:#x} invalid")

    origin_x = struct.unpack_from("<i", record_payload, sub_off + 0x08)[0]
    origin_y = struct.unpack_from("<i", record_payload, sub_off + 0x0C)[0]
    max_x = struct.unpack_from("<i", record_payload, sub_off + 0x10)[0]
    max_y = struct.unpack_from("<i", record_payload, sub_off + 0x14)[0]

    width = max_x - origin_x + 1
    height = max_y - origin_y + 1

    if width <= 0 or height <= 0 or width > 4096 or height > 4096:
        raise ValueError(f"invalid dimensions {width}x{height}")

    stream = memoryview(record_payload)[sub_off + 0x18:]
    src_pos = 0
    out = bytearray(width * height)

    x = 0
    y = 0

    while y < height:
        if src_pos >= len(stream):
            warnings.append(f"stream ended early at row {y}")
            break

        control = stream[src_pos]
        src_pos += 1

        count = control >> 1
        flag = control & 1

        if flag == 0 and count == 0:
            x = 0
            y += 1
            continue

        if flag == 0 and count > 0:
            if src_pos >= len(stream):
                warnings.append("stream ended during fill command")
                break
            value = stream[src_pos]
            src_pos += 1
            for _ in range(count):
                if y >= height:
                    break
                if x < width:
                    out[y * width + x] = value
                x += 1
            continue

        if flag == 1 and count == 0:
            if src_pos >= len(stream):
                warnings.append("stream ended during skip command")
                break
            skip = stream[src_pos]
            src_pos += 1
            x += skip
            continue

        lit_count = count
        if src_pos + lit_count > len(stream):
            warnings.append("stream ended during literal command")
            lit_count = max(0, len(stream) - src_pos)

        for _ in range(lit_count):
            value = stream[src_pos]
            src_pos += 1
            if y >= height:
                break
            if x < width:
                out[y * width + x] = value
            x += 1

        if x > width + 4096:
            warnings.append(f"excessive x advance detected on row {y}")
            x = 0
            y += 1

    img = make_indexed_image(width, height, bytes(out))

    return Decoded110Subresource(
        record_id=record_id,
        sub_index=sub_index,
        origin_x=origin_x,
        origin_y=origin_y,
        max_x=max_x,
        max_y=max_y,
        width=width,
        height=height,
        image=img,
        decode_warnings=warnings,
    )


def ensure_dir(p: Path) -> None:
    p.mkdir(parents=True, exist_ok=True)


def main() -> None:
    ap = argparse.ArgumentParser(description="Apply shell surface palettes to DATABASE.MW2 1.10 UI images")
    ap.add_argument("database_mw2", type=Path)
    ap.add_argument("output_root", type=Path)
    ap.add_argument("--surface-records", default="6-13,16,32", help="shell surface palette source record IDs; default: 6-13,16,32")
    ap.add_argument("--image-records", default="0x24-0x40", help="1.10 image record IDs; default: 0x24-0x40")
    ap.add_argument("--transparent-index", type=lambda s: int(s, 0), default=None, help="optional transparent index for RGBA outputs")
    ap.add_argument("--skip-indexed", action="store_true", help="do not write grayscale indexed reference PNGs")
    args = ap.parse_args()

    db = DatabaseMW2(args.database_mw2)
    out_root = args.output_root
    ensure_dir(out_root)

    surface_records = parse_record_spec(args.surface_records)
    image_records = parse_record_spec(args.image_records)

    palettes_dir = out_root / "extracted_surface_palettes"
    indexed_root = out_root / "indexed_reference"
    applied_root = out_root / "applied_palettes"

    ensure_dir(palettes_dir)
    ensure_dir(applied_root)
    if not args.skip_indexed:
        ensure_dir(indexed_root)

    palette_map: Dict[int, bytes] = {}
    surface_rows: List[dict] = []

    for rec_id in surface_records:
        try:
            raw = db.get_raw_record(rec_id)
            decomp = mpack_lz_decompress(raw)
            pal = extract_shell_surface_palette_rgb8(decomp)
            palette_map[rec_id] = pal

            pal_path = palettes_dir / f"rec{rec_id:03d}_shell_surface_palette_rgb768.pal"
            pal_path.write_bytes(pal)

            surface_rows.append({
                "record_id": rec_id,
                "raw_size": len(raw),
                "decompressed_size": len(decomp),
                "palette_path": str(pal_path.relative_to(out_root)),
                "status": "ok",
            })
        except Exception as e:
            surface_rows.append({
                "record_id": rec_id,
                "raw_size": "",
                "decompressed_size": "",
                "palette_path": "",
                "status": f"error: {e}",
            })

    decoded_110: List[Decoded110Subresource] = []
    image_rows: List[dict] = []

    for rec_id in image_records:
        try:
            raw = db.get_raw_record(rec_id)
        except Exception as e:
            image_rows.append({"record_id": rec_id, "sub_index": "", "width": "", "height": "", "warnings": "", "status": f"record error: {e}"})
            continue

        if len(raw) < 8 or raw[:4] != b"1.10":
            image_rows.append({"record_id": rec_id, "sub_index": "", "width": "", "height": "", "warnings": "", "status": "not_1.10"})
            continue

        try:
            count = read_u32le(raw, 4)
        except Exception as e:
            image_rows.append({"record_id": rec_id, "sub_index": "", "width": "", "height": "", "warnings": "", "status": f"header error: {e}"})
            continue

        for sub_idx in range(count):
            try:
                item = decode_110_subresource(rec_id, raw, sub_idx)
                decoded_110.append(item)

                image_rows.append({
                    "record_id": rec_id,
                    "sub_index": sub_idx,
                    "width": item.width,
                    "height": item.height,
                    "warnings": "; ".join(item.decode_warnings),
                    "status": "ok",
                })

                if not args.skip_indexed:
                    idx_dir = indexed_root / f"rec{rec_id:03d}"
                    ensure_dir(idx_dir)
                    idx_path = idx_dir / f"rec{rec_id:03d}_sub{sub_idx:03d}_indexed.png"
                    item.image.save(idx_path)

            except Exception as e:
                image_rows.append({
                    "record_id": rec_id,
                    "sub_index": sub_idx,
                    "width": "",
                    "height": "",
                    "warnings": "",
                    "status": f"decode_error: {e}",
                })

    applied_rows: List[dict] = []

    for surface_rec, pal in palette_map.items():
        pal_out_dir = applied_root / f"palette_from_surface_rec{surface_rec:03d}"
        ensure_dir(pal_out_dir)

        for item in decoded_110:
            rgb_dir = pal_out_dir / f"rec{item.record_id:03d}"
            ensure_dir(rgb_dir)

            rgb_path = rgb_dir / (
                f"rec{item.record_id:03d}_sub{item.sub_index:03d}"
                f"_palette_surface_rec{surface_rec:03d}.png"
            )

            try:
                rgba = apply_rgb_palette(item.image, pal, transparent_index=args.transparent_index)
                rgba.save(rgb_path)

                applied_rows.append({
                    "surface_palette_record_id": surface_rec,
                    "image_record_id": item.record_id,
                    "sub_index": item.sub_index,
                    "width": item.width,
                    "height": item.height,
                    "output_path": str(rgb_path.relative_to(out_root)),
                    "status": "ok",
                })
            except Exception as e:
                applied_rows.append({
                    "surface_palette_record_id": surface_rec,
                    "image_record_id": item.record_id,
                    "sub_index": item.sub_index,
                    "width": item.width,
                    "height": item.height,
                    "output_path": "",
                    "status": f"error: {e}",
                })

    with (out_root / "surface_palette_sources.tsv").open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["record_id", "raw_size", "decompressed_size", "palette_path", "status"], delimiter="\t")
        writer.writeheader()
        writer.writerows(surface_rows)

    with (out_root / "decoded_110_subresources.tsv").open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["record_id", "sub_index", "width", "height", "warnings", "status"], delimiter="\t")
        writer.writeheader()
        writer.writerows(image_rows)

    with (out_root / "applied_palette_outputs.tsv").open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["surface_palette_record_id", "image_record_id", "sub_index", "width", "height", "output_path", "status"],
            delimiter="\t",
        )
        writer.writeheader()
        writer.writerows(applied_rows)

    summary = {
        "database_mw2": str(args.database_mw2),
        "surface_records_requested": surface_records,
        "surface_palettes_extracted": sorted(palette_map.keys()),
        "image_records_requested": image_records,
        "decoded_110_subresource_count": sum(1 for r in image_rows if r.get("status") == "ok"),
        "applied_output_count": sum(1 for r in applied_rows if r.get("status") == "ok"),
        "transparent_index": args.transparent_index,
        "notes": [
            "Surface palettes are extracted from compressed shell RLE surface records after mpack decompression.",
            "1.10 records are read directly because the validated 1.10 menu records decode from raw DATABASE.MW2 record contents.",
            "The script generates the cross-product of surface palettes and 1.10 overlays for manual review.",
        ],
    }
    (out_root / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    print(f"[+] extracted {len(palette_map)} shell surface palette(s)")
    print(f"[+] decoded {sum(1 for r in image_rows if r.get('status') == 'ok')} 1.10 subresource(s)")
    print(f"[+] wrote {sum(1 for r in applied_rows if r.get('status') == 'ok')} palette-applied 1.10 image(s) into {out_root}")


if __name__ == "__main__":
    main()
