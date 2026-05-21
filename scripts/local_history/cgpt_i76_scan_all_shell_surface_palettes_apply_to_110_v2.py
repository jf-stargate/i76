#!/usr/bin/env python3
"""
Scan all DATABASE.MW2 records for compressed shell RLE bitmap surfaces, extract
their trailing RGB8 palettes, and apply the complete discovered palette set to
DATABASE.MW2 "1.10" UI image subresources.

Version 2: uses the corrected mpack LZSS ring initialization from the validated v3 shell-surface decoder. This is the broader follow-up to the confirmed records 6-13,16,32 pass. It is
intended to find shell surface/context palettes we have not manually identified
yet.

Outputs:
  summary.json
  candidate_surface_records.tsv
  decoded_110_subresources.tsv
  applied_palette_outputs.tsv
  palettes/*.pal
  shell_surfaces/*.png
  indexed_110_reference/*.png
  applied_110_palettes/palette_from_recNNN/...
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

try:
    from PIL import Image, ImageDraw
except Exception as e:
    raise SystemExit(f"This script requires Pillow: pip install pillow\n{e}")


def read_u16le(b: bytes, off: int) -> int:
    return struct.unpack_from("<H", b, off)[0]


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
    uniq: List[int] = []
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

        if any(o < table_end or o > len(self.data) for o in self.offsets):
            # Some edge cases could theoretically violate this, but not this file format.
            raise ValueError("DATABASE.MW2 offset table contains invalid offsets")

    def get_raw_record(self, record_id: int) -> bytes:
        if record_id < 1 or record_id > self.record_count:
            raise IndexError(f"record id {record_id} out of range 1..{self.record_count}")

        idx = record_id - 1
        start = self.offsets[idx]
        end = self.offsets[idx + 1] if idx + 1 < self.record_count else len(self.data)

        if not (0 <= start <= end <= len(self.data)):
            raise ValueError(f"invalid record range for record {record_id}: {start:#x}-{end:#x}")

        return self.data[start:end]


def mpack_lz_decompress(raw_record: bytes, max_output: int = 64 * 1024 * 1024) -> bytes:
    """
    DATABASE.MW2 shell mpack record decompression.

    This matches the validated i76shell.dll path used by
    cgpt_i76_decode_database_mw2_shell_rle_surfaces_v3.py.

    Format:
      uint32_le uncompressed_size
      LZSS-like stream with a 4 KiB zero-initialized ring buffer
      ring write position starts at 0
      flags are consumed LSB-first from bytes ORed with 0x100
    """
    if len(raw_record) < 4:
        raise ValueError("compressed record too small")

    expected = read_u32le(raw_record, 0)
    if expected == 0 or expected > max_output:
        raise ValueError(f"implausible decompressed size {expected}")

    src = 4
    flags = 2
    ring = bytearray(0x1000)
    rp = 0
    out = bytearray()

    while len(out) < expected:
        flags >>= 1
        if flags == 1:
            if src >= len(raw_record):
                raise ValueError(f"truncated flags at {src}, expected {expected}, got {len(out)}")
            flags = raw_record[src] | 0x100
            src += 1

        if (flags & 1) == 0:
            if src + 2 > len(raw_record):
                raise ValueError(f"truncated copy token at {src}, expected {expected}, got {len(out)}")

            token = raw_record[src] | (raw_record[src + 1] << 8)
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
            if src >= len(raw_record):
                raise ValueError(f"truncated literal at {src}, expected {expected}, got {len(out)}")

            v = raw_record[src]
            src += 1

            out.append(v)
            ring[rp] = v
            rp = (rp + 1) & 0x0FFF

    return bytes(out)

@dataclass
class ShellSurfaceCandidate:
    record_id: int
    raw_size: int
    decompressed_size: int
    min_x: int
    min_y: int
    max_x: int
    max_y: int
    width: int
    height: int
    line_width: int
    score: int
    warnings: List[str]
    pixels: bytes
    palette_rgb8: bytes


def try_decode_shell_surface(record_id: int, raw_record: bytes) -> ShellSurfaceCandidate:
    decomp = mpack_lz_decompress(raw_record)

    if len(decomp) < 0x80 + 0x300:
        raise ValueError("decompressed payload too small for shell surface")

    # Header fields inferred from shell path:
    # +0x04 min_x, +0x06 min_y, +0x08 max_x, +0x0a max_y, +0x42 line_width.
    min_x = read_u16le(decomp, 0x04)
    min_y = read_u16le(decomp, 0x06)
    max_x = read_u16le(decomp, 0x08)
    max_y = read_u16le(decomp, 0x0A)
    line_width = read_u16le(decomp, 0x42)

    width = max_x - min_x + 1
    height = max_y - min_y + 1

    warnings: List[str] = []
    score = 0

    if 1 <= width <= 2048:
        score += 20
    else:
        raise ValueError(f"invalid width {width}")

    if 1 <= height <= 2048:
        score += 20
    else:
        raise ValueError(f"invalid height {height}")

    if 1 <= line_width <= 4096:
        score += 10
    else:
        warnings.append(f"implausible line_width={line_width}")

    # Most shell surfaces are 640-wide or close; do not require it, but score it.
    if width in (320, 640, 800):
        score += 15
    if height in (200, 240, 400, 480, 600):
        score += 15
    if line_width in (width, 320, 640, 800):
        score += 10

    # Last 0x300 bytes are palette RGB8 source.
    palette = decomp[-0x300:]

    # Palette sanity: nontrivial and not all one color.
    distinct_colors = len(set(palette[i:i+3] for i in range(0, 768, 3)))
    if distinct_colors >= 16:
        score += 10
    else:
        warnings.append(f"low distinct palette colors={distinct_colors}")

    # Decode simple shell RLE from +0x80 to before trailing palette.
    #
    # Important: the validated decoder uses line_width as the row pitch/target
    # for the RLE stream, not width_from_bounds. For the confirmed shell surfaces
    # these are both 640, but using line_width keeps this scanner aligned with
    # i76shell.dll and the v3 standalone surface decoder.
    stream = memoryview(decomp)[0x80:len(decomp) - 0x300]
    src_pos = 0
    output_width = line_width if line_width > 0 else width
    pixels = bytearray(output_width * height)

    for y in range(height):
        x = 0
        while x < output_width:
            if src_pos >= len(stream):
                raise ValueError(f"RLE stream ended early at row {y}, x {x}")

            control = stream[src_pos]
            src_pos += 1

            if (control & 0xC0) == 0xC0:
                count = control & 0x3F
                if count == 0:
                    warnings.append(f"zero-length repeat at row {y}")
                    continue
                if src_pos >= len(stream):
                    raise ValueError("RLE stream ended during repeat value")
                value = stream[src_pos]
                src_pos += 1
                n = min(count, output_width - x)
                pixels[y * output_width + x:y * output_width + x + n] = bytes([value]) * n
                x += n
                if n != count:
                    warnings.append(f"run clipped at row {y}")
            else:
                pixels[y * output_width + x] = control
                x += 1

            if x > output_width + 4096:
                raise ValueError(f"RLE x advanced too far on row {y}")

    # If stream was mostly consumed before the palette, that is stronger.
    remaining = len(stream) - src_pos
    if remaining >= 0:
        if remaining < 64:
            score += 10
        elif remaining < 1024:
            score += 5
        else:
            warnings.append(f"{remaining} RLE bytes remain before trailing palette")

    return ShellSurfaceCandidate(
        record_id=record_id,
        raw_size=len(raw_record),
        decompressed_size=len(decomp),
        min_x=min_x,
        min_y=min_y,
        max_x=max_x,
        max_y=max_y,
        width=width,
        height=height,
        line_width=line_width,
        score=score,
        warnings=warnings,
        pixels=bytes(pixels),
        palette_rgb8=palette,
    )


def make_shell_surface_image(c: ShellSurfaceCandidate) -> Image.Image:
    output_width = c.line_width if c.line_width > 0 else c.width
    idx = Image.frombytes("P", (output_width, c.height), c.pixels)
    idx.putpalette(list(c.palette_rgb8))
    return idx.convert("RGBA")


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


def apply_rgb_palette(
    indexed_img: Image.Image,
    palette_rgb768: bytes,
    transparent_index: Optional[int] = None,
) -> Image.Image:
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


def write_tsv(path: Path, rows: List[dict], fieldnames: List[str]) -> None:
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t")
        w.writeheader()
        w.writerows(rows)


def make_contact_sheet(
    image_paths: List[Path],
    out_path: Path,
    thumb_size: Tuple[int, int] = (160, 120),
    columns: int = 5,
    max_items: int = 50,
) -> None:
    paths = image_paths[:max_items]
    if not paths:
        return

    rows = (len(paths) + columns - 1) // columns
    cell_w = thumb_size[0]
    cell_h = thumb_size[1] + 18

    sheet = Image.new("RGB", (columns * cell_w, rows * cell_h), (32, 32, 32))
    draw = ImageDraw.Draw(sheet)

    for i, path in enumerate(paths):
        try:
            img = Image.open(path).convert("RGBA")
        except Exception:
            continue

        img.thumbnail(thumb_size, Image.Resampling.LANCZOS)
        x = (i % columns) * cell_w + (cell_w - img.width) // 2
        y = (i // columns) * cell_h
        bg = Image.new("RGBA", img.size, (32, 32, 32, 255))
        bg.alpha_composite(img)
        sheet.paste(bg.convert("RGB"), (x, y))
        draw.text(((i % columns) * cell_w + 2, y + thumb_size[1] + 2), path.stem[:24], fill=(230, 230, 230))

    sheet.save(out_path)


def main() -> None:
    ap = argparse.ArgumentParser(
        description="Scan all DATABASE.MW2 shell surface palettes and apply them to 1.10 UI images"
    )
    ap.add_argument("database_mw2", type=Path)
    ap.add_argument("output_root", type=Path)
    ap.add_argument(
        "--image-records",
        default="0x24-0x40",
        help="1.10 image record IDs; default: 0x24-0x40",
    )
    ap.add_argument(
        "--surface-records",
        default="all",
        help="surface records to scan; default all. Example: 1-32 or 6-13,16,32",
    )
    ap.add_argument(
        "--min-surface-score",
        type=int,
        default=55,
        help="minimum shell surface candidate score to use/apply; default 55",
    )
    ap.add_argument(
        "--transparent-index",
        type=lambda s: int(s, 0),
        default=None,
        help="optional transparent index for RGBA 1.10 outputs",
    )
    ap.add_argument(
        "--skip-apply",
        action="store_true",
        help="only scan/decode surfaces and palettes; do not apply to 1.10 images",
    )
    ap.add_argument(
        "--skip-indexed",
        action="store_true",
        help="do not write grayscale indexed 1.10 reference PNGs",
    )
    ap.add_argument(
        "--contact-sheets",
        action="store_true",
        help="make small per-palette contact sheets for manual review",
    )
    args = ap.parse_args()

    db = DatabaseMW2(args.database_mw2)
    out_root = args.output_root
    ensure_dir(out_root)

    image_records = parse_record_spec(args.image_records)
    if args.surface_records.strip().lower() == "all":
        surface_records = list(range(1, db.record_count + 1))
    else:
        surface_records = parse_record_spec(args.surface_records)

    palettes_dir = out_root / "palettes"
    shell_surfaces_dir = out_root / "shell_surfaces"
    indexed_root = out_root / "indexed_110_reference"
    applied_root = out_root / "applied_110_palettes"
    contact_dir = out_root / "contact_sheets"

    ensure_dir(palettes_dir)
    ensure_dir(shell_surfaces_dir)
    if not args.skip_indexed:
        ensure_dir(indexed_root)
    if not args.skip_apply:
        ensure_dir(applied_root)
    if args.contact_sheets:
        ensure_dir(contact_dir)

    # Step 1: scan shell surface candidates across selected records.
    candidate_rows: List[dict] = []
    accepted_surfaces: List[ShellSurfaceCandidate] = []
    palette_hash_to_first_rec: Dict[str, int] = {}

    for rec_id in surface_records:
        try:
            raw = db.get_raw_record(rec_id)
            cand = try_decode_shell_surface(rec_id, raw)
            pal_hash = hashlib.sha1(cand.palette_rgb8).hexdigest()

            status = "accepted" if cand.score >= args.min_surface_score else "low_score"
            if status == "accepted":
                accepted_surfaces.append(cand)
                pal_path = palettes_dir / f"rec{rec_id:03d}_shell_surface_rgb8.pal"
                pal_path.write_bytes(cand.palette_rgb8)

                img = make_shell_surface_image(cand)
                img.save(shell_surfaces_dir / f"rec{rec_id:03d}_shell_surface_{cand.width}x{cand.height}.png")

                palette_hash_to_first_rec.setdefault(pal_hash, rec_id)
            else:
                pal_path = ""

            candidate_rows.append(
                {
                    "record_id": rec_id,
                    "raw_size": cand.raw_size,
                    "decompressed_size": cand.decompressed_size,
                    "min_x": cand.min_x,
                    "min_y": cand.min_y,
                    "max_x": cand.max_x,
                    "max_y": cand.max_y,
                    "width": cand.width,
                    "height": cand.height,
                    "line_width": cand.line_width,
                    "score": cand.score,
                    "palette_sha1": pal_hash,
                    "first_record_for_palette": palette_hash_to_first_rec.get(pal_hash, ""),
                    "status": status,
                    "warnings": "; ".join(cand.warnings),
                }
            )
        except Exception as e:
            candidate_rows.append(
                {
                    "record_id": rec_id,
                    "raw_size": "",
                    "decompressed_size": "",
                    "min_x": "",
                    "min_y": "",
                    "max_x": "",
                    "max_y": "",
                    "width": "",
                    "height": "",
                    "line_width": "",
                    "score": "",
                    "palette_sha1": "",
                    "first_record_for_palette": "",
                    "status": f"reject: {e}",
                    "warnings": "",
                }
            )

    write_tsv(
        out_root / "candidate_surface_records.tsv",
        candidate_rows,
        [
            "record_id",
            "raw_size",
            "decompressed_size",
            "min_x",
            "min_y",
            "max_x",
            "max_y",
            "width",
            "height",
            "line_width",
            "score",
            "palette_sha1",
            "first_record_for_palette",
            "status",
            "warnings",
        ],
    )

    # Step 2: decode 1.10 subresources.
    decoded_110: List[Decoded110Subresource] = []
    image_rows: List[dict] = []

    if not args.skip_apply:
        for rec_id in image_records:
            try:
                raw = db.get_raw_record(rec_id)
            except Exception as e:
                image_rows.append(
                    {
                        "record_id": rec_id,
                        "sub_index": "",
                        "width": "",
                        "height": "",
                        "warnings": "",
                        "status": f"record error: {e}",
                    }
                )
                continue

            if len(raw) < 8 or raw[:4] != b"1.10":
                image_rows.append(
                    {
                        "record_id": rec_id,
                        "sub_index": "",
                        "width": "",
                        "height": "",
                        "warnings": "",
                        "status": "not_1.10",
                    }
                )
                continue

            try:
                count = read_u32le(raw, 4)
            except Exception as e:
                image_rows.append(
                    {
                        "record_id": rec_id,
                        "sub_index": "",
                        "width": "",
                        "height": "",
                        "warnings": "",
                        "status": f"header error: {e}",
                    }
                )
                continue

            for sub_idx in range(count):
                try:
                    item = decode_110_subresource(rec_id, raw, sub_idx)
                    decoded_110.append(item)
                    image_rows.append(
                        {
                            "record_id": rec_id,
                            "sub_index": sub_idx,
                            "width": item.width,
                            "height": item.height,
                            "warnings": "; ".join(item.decode_warnings),
                            "status": "ok",
                        }
                    )

                    if not args.skip_indexed:
                        idx_dir = indexed_root / f"rec{rec_id:03d}"
                        ensure_dir(idx_dir)
                        item.image.save(idx_dir / f"rec{rec_id:03d}_sub{sub_idx:03d}_indexed.png")

                except Exception as e:
                    image_rows.append(
                        {
                            "record_id": rec_id,
                            "sub_index": sub_idx,
                            "width": "",
                            "height": "",
                            "warnings": "",
                            "status": f"decode_error: {e}",
                        }
                    )

    write_tsv(
        out_root / "decoded_110_subresources.tsv",
        image_rows,
        ["record_id", "sub_index", "width", "height", "warnings", "status"],
    )

    # Step 3: apply accepted palettes to 1.10 images. Use unique palettes only by default
    # to avoid redundant output when multiple surface records share a palette.
    applied_rows: List[dict] = []
    seen_palette_hashes = set()

    if not args.skip_apply:
        for cand in accepted_surfaces:
            pal_hash = hashlib.sha1(cand.palette_rgb8).hexdigest()
            if pal_hash in seen_palette_hashes:
                continue
            seen_palette_hashes.add(pal_hash)

            pal_out_dir = applied_root / f"palette_from_surface_rec{cand.record_id:03d}"
            ensure_dir(pal_out_dir)
            contact_paths: List[Path] = []

            for item in decoded_110:
                rgb_dir = pal_out_dir / f"rec{item.record_id:03d}"
                ensure_dir(rgb_dir)

                rgb_path = rgb_dir / (
                    f"rec{item.record_id:03d}_sub{item.sub_index:03d}"
                    f"_palette_surface_rec{cand.record_id:03d}.png"
                )

                try:
                    rgba = apply_rgb_palette(
                        item.image,
                        cand.palette_rgb8,
                        transparent_index=args.transparent_index,
                    )
                    rgba.save(rgb_path)
                    contact_paths.append(rgb_path)

                    applied_rows.append(
                        {
                            "surface_palette_record_id": cand.record_id,
                            "surface_palette_sha1": pal_hash,
                            "image_record_id": item.record_id,
                            "sub_index": item.sub_index,
                            "width": item.width,
                            "height": item.height,
                            "output_path": str(rgb_path.relative_to(out_root)),
                            "status": "ok",
                        }
                    )
                except Exception as e:
                    applied_rows.append(
                        {
                            "surface_palette_record_id": cand.record_id,
                            "surface_palette_sha1": pal_hash,
                            "image_record_id": item.record_id,
                            "sub_index": item.sub_index,
                            "width": item.width,
                            "height": item.height,
                            "output_path": "",
                            "status": f"error: {e}",
                        }
                    )

            if args.contact_sheets:
                make_contact_sheet(
                    contact_paths,
                    contact_dir / f"palette_from_surface_rec{cand.record_id:03d}_contact.jpg",
                )

    write_tsv(
        out_root / "applied_palette_outputs.tsv",
        applied_rows,
        [
            "surface_palette_record_id",
            "surface_palette_sha1",
            "image_record_id",
            "sub_index",
            "width",
            "height",
            "output_path",
            "status",
        ],
    )

    unique_accepted_palette_count = len(set(hashlib.sha1(c.palette_rgb8).hexdigest() for c in accepted_surfaces))

    summary = {
        "database_mw2": str(args.database_mw2),
        "record_count": db.record_count,
        "surface_records_scanned": surface_records,
        "min_surface_score": args.min_surface_score,
        "accepted_surface_record_count": len(accepted_surfaces),
        "unique_accepted_palette_count": unique_accepted_palette_count,
        "accepted_surface_records": [c.record_id for c in accepted_surfaces],
        "image_records_requested": image_records,
        "decoded_110_subresource_count": sum(1 for r in image_rows if r.get("status") == "ok"),
        "applied_output_count": sum(1 for r in applied_rows if r.get("status") == "ok"),
        "transparent_index": args.transparent_index,
        "notes": [
            "Accepted shell surfaces are mpack-decompressed records with plausible shell RLE bitmap headers and valid trailing RGB8 palettes.",
            "The script applies unique accepted surface palettes to 1.10 subresources for manual review.",
            "If these still do not color 1.10 assets correctly, the palette source is likely a different shell context or non-DATABASE.MW2 resource path.",
        ],
    }

    (out_root / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    print(f"[+] scanned {len(surface_records)} DATABASE.MW2 record(s)")
    print(f"[+] accepted {len(accepted_surfaces)} shell surface record(s)")
    print(f"[+] unique accepted palettes: {unique_accepted_palette_count}")
    if not args.skip_apply:
        print(f"[+] decoded {summary['decoded_110_subresource_count']} 1.10 subresource(s)")
        print(f"[+] wrote {summary['applied_output_count']} palette-applied 1.10 image(s)")
    print(f"[+] output: {out_root}")


if __name__ == "__main__":
    main()
