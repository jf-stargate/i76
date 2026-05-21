#!/usr/bin/env python3
"""
cgpt_i76_reconstruct_database_mw2_shell_screens.py

Interstate '76 DATABASE.MW2 shell UI extraction / reconstruction helper.

This script is intentionally standalone.  It does not require Ghidra.  It uses
binary-derived format notes from the i76shell.dll DATABASE.MW2 pass:

  * records 1-32: mpack-compressed shell RLE surfaces with trailing RGB8 palette
  * records 36-64: "1.10" multi-subresource indexed UI overlays
  * record 64: final-mission special overlay, palette-paired with surface 27

Outputs:
  * decoded shell background/surface PNGs
  * decoded 1.10 overlay subresource PNGs and contact sheets
  * a direct-surface-load contact sheet from shell_screen_surface_map_v2.tsv
  * final mission special candidate composites: surface 27 + record 64 variants
  * JSON summary with dimensions, decode warnings, and generated paths
"""

import argparse
import csv
import json
import math
import os
import struct
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple

MAX_WARNINGS_PER_ITEM = 20

def add_warning(warnings: List[str], message: str) -> None:
    if len(warnings) < MAX_WARNINGS_PER_ITEM:
        warnings.append(message)
    elif len(warnings) == MAX_WARNINGS_PER_ITEM:
        warnings.append("additional warnings suppressed")

try:
    from PIL import Image, ImageDraw, ImageFont
except ImportError as exc:
    raise SystemExit("This script requires Pillow: python3 -m pip install Pillow") from exc


@dataclass
class DbRecord:
    record_id: int
    offset: int
    size: int
    data: bytes


@dataclass
class DecodedSurface:
    record_id: int
    width: int
    height: int
    rgba: Image.Image
    palette: List[Tuple[int, int, int]]
    warnings: List[str]


@dataclass
class DecodedOverlaySubresource:
    record_id: int
    sub_index: int
    width: int
    height: int
    rgba: Image.Image
    warnings: List[str]


def read_database(path: Path) -> Dict[int, DbRecord]:
    blob = path.read_bytes()
    if len(blob) < 8:
        raise ValueError(f"{path} is too small to be DATABASE.MW2")
    count = struct.unpack_from("<I", blob, 0)[0]
    if count <= 0 or 4 + 4 * count > len(blob):
        raise ValueError(f"implausible record count {count}")
    offsets = list(struct.unpack_from(f"<{count}I", blob, 4))
    records: Dict[int, DbRecord] = {}
    for i, start in enumerate(offsets):
        end = offsets[i + 1] if i + 1 < count else len(blob)
        if not (0 <= start <= end <= len(blob)):
            raise ValueError(f"record {i+1} has invalid offset range {start:#x}..{end:#x}")
        records[i + 1] = DbRecord(i + 1, start, end - start, blob[start:end])
    return records


def mpack_decompress(record_data: bytes) -> Tuple[bytes, List[str]]:
    warnings: List[str] = []
    if len(record_data) < 4:
        return b"", ["record too short for mpack decompressed-size prefix"]
    out_len = struct.unpack_from("<I", record_data, 0)[0]
    src = 4
    out = bytearray()
    ring = bytearray(0x1000)  # i76shell clears DAT_10052178..DAT_10053178 to zero.
    ring_pos = 0
    flags = 2

    while len(out) < out_len:
        flags >>= 1
        if flags == 1:
            if src >= len(record_data):
                add_warning(warnings, "mpack input ended while reading flag byte")
                break
            flags = record_data[src] | 0x100
            src += 1

        if flags & 1:
            if src >= len(record_data):
                add_warning(warnings, "mpack input ended while reading literal byte")
                break
            value = record_data[src]
            src += 1
            ring[ring_pos] = value
            ring_pos = (ring_pos + 1) & 0xFFF
            out.append(value)
        else:
            if src + 2 > len(record_data):
                add_warning(warnings, "mpack input ended while reading back-reference")
                break
            lo = record_data[src]
            hi = record_data[src + 1]
            src += 2
            token = lo | (hi << 8)
            copy_pos = token & 0x0FFF
            count = ((token >> 12) & 0x0F) + 3
            for _ in range(count):
                value = ring[copy_pos]
                copy_pos = (copy_pos + 1) & 0xFFF
                ring[ring_pos] = value
                ring_pos = (ring_pos + 1) & 0xFFF
                out.append(value)
                if len(out) >= out_len:
                    break

    if len(out) != out_len:
        add_warning(warnings, f"mpack decompressed {len(out)} bytes, expected {out_len}")
    return bytes(out[:out_len]), warnings


def palette_from_rgb8_tail(payload: bytes) -> List[Tuple[int, int, int]]:
    if len(payload) < 0x300:
        return [(0, 0, 0)] * 256
    tail = payload[-0x300:]
    return [(tail[i], tail[i + 1], tail[i + 2]) for i in range(0, 0x300, 3)]


def decode_shell_surface(record: DbRecord) -> DecodedSurface:
    payload, warnings = mpack_decompress(record.data)
    if len(payload) < 0x80 + 0x300:
        img = Image.new("RGBA", (1, 1), (255, 0, 255, 255))
        add_warning(warnings, "payload too short for shell surface header/RLE/palette")
        return DecodedSurface(record.record_id, 1, 1, img, [], warnings)

    # Header interpretation from shell surface pass.  These are max inclusive
    # coordinates in the decoded surface header for normal 640x480 shell screens.
    max_x = struct.unpack_from("<H", payload, 8)[0]
    max_y = struct.unpack_from("<H", payload, 10)[0]
    width = max_x + 1 if 0 < max_x < 4096 else 640
    height = max_y + 1 if 0 < max_y < 4096 else 480
    palette = palette_from_rgb8_tail(payload)

    rle = payload[0x80:-0x300]
    pixels = bytearray(width * height)
    pos = 0
    src = 0
    for y in range(height):
        x = 0
        while x < width and src < len(rle):
            control = rle[src]
            src += 1
            if (control & 0xC0) == 0xC0:
                count = control & 0x3F
                if count == 0:
                    count = 0x40
                if src >= len(rle):
                    add_warning(warnings, f"surface RLE ended after run control at line {y}")
                    break
                value = rle[src]
                src += 1
                n = min(count, width - x)
                pixels[pos:pos + n] = bytes([value]) * n
                pos += n
                x += n
            else:
                pixels[pos] = control
                pos += 1
                x += 1
        if x != width:
            add_warning(warnings, f"surface line {y} decoded {x}/{width} pixels")
            pos += max(0, width - x)

    pal_img = Image.frombytes("P", (width, height), bytes(pixels))
    flat_palette = []
    for r, g, b in palette:
        flat_palette.extend([r, g, b])
    pal_img.putpalette(flat_palette)
    rgba = pal_img.convert("RGBA")
    return DecodedSurface(record.record_id, width, height, rgba, palette, warnings)


def decode_110_subresource(record_id: int, sub_index: int, chunk: bytes,
                           palette: List[Tuple[int, int, int]]) -> DecodedOverlaySubresource:
    warnings: List[str] = []
    if len(chunk) < 24:
        img = Image.new("RGBA", (1, 1), (255, 0, 255, 255))
        return DecodedOverlaySubresource(record_id, sub_index, 1, 1, img, ["subresource too short"])

    height_a, width_a = struct.unpack_from("<HH", chunk, 0)
    width_b = struct.unpack_from("<I", chunk, 16)[0]
    height_b = struct.unpack_from("<I", chunk, 20)[0]
    width = int(width_b or width_a)
    height = int(height_b or height_a)
    if width <= 0 or height <= 0 or width > 4096 or height > 4096:
        add_warning(warnings, f"implausible dimensions width={width} height={height}; using 1x1")
        width, height = 1, 1

    pixels = bytearray(width * height)
    alpha = bytearray(width * height)
    src = 24
    y = 0
    x = 0

    while y < height and src < len(chunk):
        control = chunk[src]
        src += 1
        flag = control & 1
        count = control >> 1

        if flag == 0 and count == 0:
            # End of line.
            y += 1
            x = 0
            continue

        if flag == 0:
            if src >= len(chunk):
                add_warning(warnings, f"1.10 fill missing value at y={y} x={x}")
                break
            value = chunk[src]
            src += 1
            n = min(count, max(0, width - x))
            base = y * width + x
            pixels[base:base + n] = bytes([value]) * n
            alpha[base:base + n] = b"\xff" * n
            x += count
        elif count == 0:
            if src >= len(chunk):
                add_warning(warnings, f"1.10 extended skip missing count at y={y} x={x}")
                break
            skip = chunk[src]
            src += 1
            x += skip
        else:
            n = min(count, max(0, width - x), max(0, len(chunk) - src))
            base = y * width + x
            pixels[base:base + n] = chunk[src:src + n]
            alpha[base:base + n] = b"\xff" * n
            src += count
            x += count

        while x >= width and y < height:
            # Some streams are exact and use EOL controls; this recovery prevents
            # a malformed stream from smearing into a single long row.
            if x > width:
                add_warning(warnings, f"1.10 operation crossed line y={y}: x={x}, width={width}")
            y += 1
            x = 0

    if y < height:
        # This is common for sparse images if the stream terminates immediately
        # after the last useful line; keep it as a warning for diagnostics only.
        add_warning(warnings, f"1.10 decoded through line {y}/{height}")

    pal_img = Image.frombytes("P", (width, height), bytes(pixels))
    flat_palette = []
    for r, g, b in palette:
        flat_palette.extend([r, g, b])
    pal_img.putpalette(flat_palette)
    img = pal_img.convert("RGBA")
    img.putalpha(Image.frombytes("L", (width, height), bytes(alpha)))
    return DecodedOverlaySubresource(record_id, sub_index, width, height, img, warnings)


def iter_110_chunks(record: DbRecord) -> List[bytes]:
    data = record.data
    if len(data) < 16 or data[:4] != b"1.10":
        return []
    count, data_start, _reserved = struct.unpack_from("<III", data, 4)
    if count <= 0 or count > 10000:
        return []
    end_offsets: List[int] = []
    for i in range(count - 1):
        off_pos = 16 + i * 8
        if off_pos + 8 > len(data):
            return []
        end_offsets.append(struct.unpack_from("<Q", data, off_pos)[0])
    starts = [data_start] + end_offsets[:-1]
    ends = end_offsets + [len(data)]
    chunks = []
    for start, end in zip(starts, ends):
        if 0 <= start <= end <= len(data):
            chunks.append(data[start:end])
    return chunks


def ensure_dir(path: Path) -> None:
    path.mkdir(parents=True, exist_ok=True)


def label_image(img: Image.Image, label: str, label_height: int = 18) -> Image.Image:
    out = Image.new("RGBA", (img.width, img.height + label_height), (32, 32, 32, 255))
    out.alpha_composite(img.convert("RGBA"), (0, label_height))
    draw = ImageDraw.Draw(out)
    draw.text((3, 2), label, fill=(255, 255, 255, 255))
    return out


def make_contact_sheet(items: Sequence[Tuple[str, Image.Image]], thumb_w: int, thumb_h: int,
                       columns: int = 4) -> Image.Image:
    if not items:
        return Image.new("RGBA", (1, 1), (0, 0, 0, 0))
    cells: List[Image.Image] = []
    for label, img in items:
        thumb = img.copy().convert("RGBA")
        thumb.thumbnail((thumb_w, thumb_h), Image.Resampling.NEAREST)
        cell = Image.new("RGBA", (thumb_w, thumb_h), (16, 16, 16, 255))
        cell.alpha_composite(thumb, ((thumb_w - thumb.width) // 2, (thumb_h - thumb.height) // 2))
        cells.append(label_image(cell, label))
    rows = math.ceil(len(cells) / columns)
    sheet = Image.new("RGBA", (columns * thumb_w, rows * (thumb_h + 18)), (0, 0, 0, 255))
    for idx, cell in enumerate(cells):
        x = (idx % columns) * thumb_w
        y = (idx // columns) * (thumb_h + 18)
        sheet.alpha_composite(cell, (x, y))
    return sheet


def save_png(img: Image.Image, path: Path) -> str:
    ensure_dir(path.parent)
    img.save(path, compress_level=1, optimize=False)
    return str(path)


def parse_surface_map(path: Optional[Path]) -> List[dict]:
    if not path or not path.exists():
        return []
    with path.open(newline="", encoding="utf-8", errors="replace") as f:
        return list(csv.DictReader(f, delimiter="\t"))


def load_palette_policy(resource_map_path: Optional[Path]) -> Dict[int, int]:
    # Returns overlay record -> surface palette record.  Defaults are conservative:
    # ordinary 1.10 overlays use record 1, final special record 64 uses record 27.
    policy = {rid: 1 for rid in range(36, 65)}
    policy[64] = 27
    if resource_map_path and resource_map_path.exists():
        try:
            data = json.loads(resource_map_path.read_text(encoding="utf-8", errors="replace"))
            for rec in data.get("records", []):
                rid = rec.get("record_id")
                src = rec.get("palette_source_record")
                if isinstance(rid, int) and isinstance(src, int) and 36 <= rid <= 64:
                    policy[rid] = src
        except Exception:
            pass
    return policy


def make_final_mission_variants(surface27: DecodedSurface,
                                record64_subs: Sequence[DecodedOverlaySubresource]) -> List[Tuple[str, Image.Image]]:
    # From 10031b20: clear_text_rect(..., x=0x145, y=0x70, w=0x40, h=0x5c),
    # then draw_mw2_image_subresource_to_shell_surface(record_ptr, dynamic_subidx,
    # x=0x145, y=0x70, w=0x40, h=0x5c).  The overlay itself is larger than that
    # nominal rect, so this produces diagnostic full-paste variants at the draw origin.
    x = 0x145
    y = 0x70
    variants: List[Tuple[str, Image.Image]] = []
    for sub in record64_subs:
        bg = surface27.rgba.copy().convert("RGBA")
        bg.alpha_composite(sub.rgba, (x, y))
        variants.append((f"surface27_plus_record64_sub{sub.sub_index}_at_{x}_{y}", bg))
    return variants


def tar_output_folder(folder: Path) -> Optional[Path]:
    tar_path = folder.with_suffix(".tar")
    try:
        subprocess.run(["tar", "-cf", str(tar_path), "-C", str(folder.parent), folder.name], check=True)
        return tar_path
    except Exception:
        return None


def main(argv: Optional[Sequence[str]] = None) -> int:
    parser = argparse.ArgumentParser(description="Decode/reconstruct Interstate '76 DATABASE.MW2 shell UI assets.")
    parser.add_argument("database", type=Path, help="Path to DATABASE.MW2")
    parser.add_argument("--resource-map-json", type=Path, default=None,
                        help="database_mw2_resource_map_v2.json, used for palette policy")
    parser.add_argument("--surface-map-tsv", type=Path, default=None,
                        help="shell_screen_surface_map_v2.tsv, used for direct surface-load contact sheet")
    parser.add_argument("--output-dir", type=Path, default=Path("i76_database_mw2_screen_reconstruction"))
    parser.add_argument("--no-tar", action="store_true", help="Do not create a tar archive of the output folder")
    args = parser.parse_args(argv)

    out_root = args.output_dir
    ensure_dir(out_root)
    records = read_database(args.database)
    palette_policy = load_palette_policy(args.resource_map_json)

    summary = {
        "schema": "i76.database_mw2.screen_reconstruction.v1",
        "database": str(args.database),
        "outputs": {},
        "surfaces": {},
        "overlays": {},
        "warnings": [],
    }

    decoded_surfaces: Dict[int, DecodedSurface] = {}
    surface_items: List[Tuple[str, Image.Image]] = []
    for rid in range(1, 33):
        if rid not in records:
            continue
        surf = decode_shell_surface(records[rid])
        decoded_surfaces[rid] = surf
        path = out_root / "shell_surfaces" / f"record_{rid:02d}_surface.png"
        save_png(surf.rgba, path)
        surface_items.append((f"{rid:02d}", surf.rgba))
        summary["surfaces"][str(rid)] = {
            "width": surf.width,
            "height": surf.height,
            "png": str(path),
            "warnings": surf.warnings,
        }

    if surface_items:
        path = out_root / "contact_sheets" / "shell_surfaces_01_32.png"
        save_png(make_contact_sheet(surface_items, 320, 240, columns=4), path)
        summary["outputs"]["shell_surface_contact_sheet"] = str(path)

    decoded_overlays: Dict[int, List[DecodedOverlaySubresource]] = {}
    for rid in range(36, 65):
        if rid not in records:
            continue
        palette_record = palette_policy.get(rid, 1)
        palette = decoded_surfaces.get(palette_record, decoded_surfaces.get(1)).palette
        chunks = iter_110_chunks(records[rid])
        subs: List[DecodedOverlaySubresource] = []
        items: List[Tuple[str, Image.Image]] = []
        for idx, chunk in enumerate(chunks):
            sub = decode_110_subresource(rid, idx, chunk, palette)
            subs.append(sub)
            path = out_root / "ui_overlays_110" / f"record_{rid:02d}" / f"record_{rid:02d}_sub_{idx:03d}.png"
            save_png(sub.rgba, path)
            items.append((f"{rid:02d}:{idx}", sub.rgba))
        decoded_overlays[rid] = subs
        contact_path = None
        if items:
            contact_path = out_root / "ui_overlays_110" / f"record_{rid:02d}" / f"record_{rid:02d}_contact_sheet.png"
            save_png(make_contact_sheet(items, 180, 140, columns=5), contact_path)
        summary["overlays"][str(rid)] = {
            "palette_source_record": palette_record,
            "subresource_count": len(subs),
            "contact_sheet": str(contact_path) if contact_path else None,
            "subresources": [
                {"sub_index": s.sub_index, "width": s.width, "height": s.height, "warnings": s.warnings}
                for s in subs
            ],
        }

    # Evidence-oriented contact sheet of backgrounds by state handler.
    surface_map_rows = parse_surface_map(args.surface_map_tsv)
    direct_items: List[Tuple[str, Image.Image]] = []
    seen = set()
    for row in surface_map_rows:
        try:
            rid = int(row.get("surface_record_id") or "0")
        except ValueError:
            continue
        key = (row.get("state_function_entry", ""), rid)
        if key in seen or rid not in decoded_surfaces:
            continue
        seen.add(key)
        label = f"{row.get('state_function_entry','')} r{rid:02d}"
        direct_items.append((label, decoded_surfaces[rid].rgba))
    if direct_items:
        path = out_root / "contact_sheets" / "direct_surface_loads_by_state_function.png"
        save_png(make_contact_sheet(direct_items, 320, 240, columns=3), path)
        summary["outputs"]["direct_surface_load_contact_sheet"] = str(path)

    # Confirmed semantic anchor: final mission special, record 64 over surface/palette 27.
    if 27 in decoded_surfaces and 64 in decoded_overlays:
        variants = make_final_mission_variants(decoded_surfaces[27], decoded_overlays[64])
        variant_paths = []
        for label, img in variants:
            p = out_root / "screen_candidates" / "final_mission_special" / f"{label}.png"
            save_png(img, p)
            variant_paths.append(str(p))
        if variants:
            p = out_root / "screen_candidates" / "final_mission_special" / "final_mission_special_variants_contact_sheet.png"
            save_png(make_contact_sheet(variants, 320, 240, columns=2), p)
            summary["outputs"]["final_mission_special_contact_sheet"] = str(p)
        summary["outputs"]["final_mission_special_variants"] = variant_paths

    summary_path = out_root / "reconstruction_summary.json"
    summary_path.write_text(json.dumps(summary, indent=2), encoding="utf-8")

    if not args.no_tar:
        tar_path = tar_output_folder(out_root)
        if tar_path:
            summary["outputs"]["tar_archive"] = str(tar_path)
            summary_path.write_text(json.dumps(summary, indent=2), encoding="utf-8")

    print(f"Wrote {out_root}")
    if not args.no_tar and summary["outputs"].get("tar_archive"):
        print(f"Wrote {summary['outputs']['tar_archive']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
