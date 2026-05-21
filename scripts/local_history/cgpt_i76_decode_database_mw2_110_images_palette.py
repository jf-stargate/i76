#!/usr/bin/env python3
# Decode Interstate '76 / MechWarrior-2-style DATABASE.MW2 "1.10" shell image records.
#
# Target: DATABASE.MW2 records 0x24..0x40, as used by i76shell.dll preload/draw paths.
# This version preserves the validated RLE/index decode and adds optional external palette/remap output.
#
# Relevant i76shell.dll routines:
#   10039390 draw_mw2_image_subresource_to_shell_surface
#   1003a8f4 blit_mw2_image_subresource_rle_clipped
#   1003ad68 blit_mw2_image_subresource_rle_unclipped
#   1003ae8a blit_mw2_image_subresource_rle_transparent_remap
#   1003ae6b set_shell_image_palette_remap_table

from __future__ import annotations

import argparse
import csv
import json
import struct
import sys
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple

try:
    from PIL import Image
except Exception:  # pragma: no cover - user environment dependency.
    Image = None


DEFAULT_FIRST_RECORD = 0x24
DEFAULT_LAST_RECORD = 0x40


class DecodeError(Exception):
    pass


def u16le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<H", buf, off)[0]


def u32le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<I", buf, off)[0]


def s32le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<i", buf, off)[0]


@dataclass
class RecordInfo:
    record_id_1based: int
    offset: int
    size: int
    magic: str
    subresource_count: Optional[int] = None
    note: str = ""


@dataclass
class EntryInfo:
    record_id_1based: int
    subresource_index: int
    entry_offset: int
    subresource_offset: int
    entry_second_dword: int
    inferred_end_offset: int
    inferred_size: int
    valid: bool
    note: str = ""


@dataclass
class SubresourceInfo:
    record_id_1based: int
    subresource_index: int
    subresource_offset: int
    subresource_size: int
    raw_00_u16: int
    raw_02_u16: int
    raw_04_u32: int
    origin_x: int
    origin_y: int
    max_x: int
    max_y: int
    width: int
    height: int
    payload_offset: int
    payload_size: int
    decoded: bool
    consumed_bytes: int = 0
    rows_completed: int = 0
    pixels_written: int = 0
    pixels_skipped: int = 0
    fill_ops: int = 0
    literal_ops: int = 0
    skip_ops: int = 0
    eol_ops: int = 0
    warnings: str = ""
    indexed_png_path: str = ""
    rgb_png_path: str = ""
    alpha_png_path: str = ""


def read_database_mw2(path: Path) -> Tuple[bytes, List[Tuple[int, int]]]:
    data = path.read_bytes()
    if len(data) < 8:
        raise DecodeError(f"{path} is too small to be DATABASE.MW2")

    record_count = u32le(data, 0)
    table_end = 4 + record_count * 4
    if record_count == 0 or record_count > 100000:
        raise DecodeError(f"implausible record count: {record_count}")
    if table_end > len(data):
        raise DecodeError(f"offset table extends past EOF: table_end=0x{table_end:x}, size=0x{len(data):x}")

    offsets = [u32le(data, 4 + i * 4) for i in range(record_count)]
    if any(o >= len(data) for o in offsets):
        bad = [(i + 1, o) for i, o in enumerate(offsets) if o >= len(data)][:8]
        raise DecodeError(f"record offset(s) past EOF: {bad}")
    if any(offsets[i] > offsets[i + 1] for i in range(len(offsets) - 1)):
        raise DecodeError("record offsets are not monotonic")

    spans: List[Tuple[int, int]] = []
    for i, start in enumerate(offsets):
        end = offsets[i + 1] if i + 1 < len(offsets) else len(data)
        spans.append((start, end - start))
    return data, spans


def iter_record_ids(first: int, last: int, max_record: int) -> Iterable[int]:
    for rid in range(first, last + 1):
        if 1 <= rid <= max_record:
            yield rid


def parse_110_entries(record: bytes, rid: int) -> Tuple[RecordInfo, List[EntryInfo]]:
    if len(record) < 16:
        return RecordInfo(rid, 0, len(record), record[:4].decode("latin1", "replace"), None, "too small"), []

    magic_bytes = record[:4]
    magic = magic_bytes.decode("latin1", "replace")
    count = u32le(record, 4)
    info = RecordInfo(rid, 0, len(record), magic, count)

    if magic_bytes != b"1.10":
        info.note = "not 1.10"
        return info, []
    if count == 0 or count > 4096:
        info.note = f"implausible subresource count {count}"
        return info, []

    table_end = 8 + count * 8
    if table_end > len(record):
        info.note = f"entry table past record end: table_end=0x{table_end:x}"
        return info, []

    raw_offsets: List[int] = []
    raw_second: List[int] = []
    for i in range(count):
        eoff = 8 + i * 8
        raw_offsets.append(u32le(record, eoff))
        raw_second.append(u32le(record, eoff + 4))

    sorted_valid_starts = sorted(set(o for o in raw_offsets if table_end <= o < len(record)))
    entries: List[EntryInfo] = []
    for i, off in enumerate(raw_offsets):
        note = ""
        valid = table_end <= off < len(record)
        if not valid:
            note = f"subresource offset outside record/table: 0x{off:x}"
            end = off
        else:
            following = [x for x in sorted_valid_starts if x > off]
            end = following[0] if following else len(record)
            if raw_second[i] != 0 and raw_second[i] <= len(record):
                if raw_second[i] > off and raw_second[i] <= end:
                    note = "second dword could be local end/size metadata"
        entries.append(
            EntryInfo(
                record_id_1based=rid,
                subresource_index=i,
                entry_offset=8 + i * 8,
                subresource_offset=off,
                entry_second_dword=raw_second[i],
                inferred_end_offset=end,
                inferred_size=max(0, end - off),
                valid=valid,
                note=note,
            )
        )
    return info, entries


def read_subresource_header(record: bytes, entry: EntryInfo) -> Optional[SubresourceInfo]:
    off = entry.subresource_offset
    end = entry.inferred_end_offset
    if not entry.valid or off + 0x18 > len(record) or end <= off:
        return None

    origin_x = s32le(record, off + 0x08)
    origin_y = s32le(record, off + 0x0c)
    max_x = s32le(record, off + 0x10)
    max_y = s32le(record, off + 0x14)
    width = max_x - origin_x + 1
    height = max_y - origin_y + 1
    payload_off = off + 0x18
    payload_size = max(0, end - payload_off)

    return SubresourceInfo(
        record_id_1based=entry.record_id_1based,
        subresource_index=entry.subresource_index,
        subresource_offset=off,
        subresource_size=end - off,
        raw_00_u16=u16le(record, off + 0x00),
        raw_02_u16=u16le(record, off + 0x02),
        raw_04_u32=u32le(record, off + 0x04),
        origin_x=origin_x,
        origin_y=origin_y,
        max_x=max_x,
        max_y=max_y,
        width=width,
        height=height,
        payload_offset=payload_off,
        payload_size=payload_size,
        decoded=False,
    )


def decode_unclipped_rle(payload: bytes, width: int, height: int, strict: bool = False) -> Tuple[bytearray, Dict[str, int], List[str]]:
    """Decode the byte-oriented row RLE used by i76shell 1003ad68.

    Current command interpretation, validated visually against records 0x24..0x40:
      bit 0 == 0, count > 0: fill next byte for count pixels
      bit 0 == 1, count > 0: copy count literal bytes
      bit 0 == 1, count == 0: extended skip; next byte is skip count, then another command
      bit 0 == 0, count == 0: end-of-line
    """
    if width <= 0 or height <= 0 or width > 8192 or height > 8192:
        raise DecodeError(f"implausible image dimensions {width}x{height}")

    out = bytearray(width * height)
    src = 0
    stats = {
        "consumed_bytes": 0,
        "rows_completed": 0,
        "pixels_written": 0,
        "pixels_skipped": 0,
        "fill_ops": 0,
        "literal_ops": 0,
        "skip_ops": 0,
        "eol_ops": 0,
        "overflow_writes": 0,
        "truncated_commands": 0,
    }
    warnings: List[str] = []

    def get_byte() -> int:
        nonlocal src
        if src >= len(payload):
            stats["truncated_commands"] += 1
            raise DecodeError("RLE stream ended unexpectedly")
        b = payload[src]
        src += 1
        return b

    for y in range(height):
        x = 0
        try:
            ctrl = get_byte()
            while True:
                count = ctrl >> 1
                mode = ctrl & 1
                if mode == 0:
                    if count == 0:
                        stats["eol_ops"] += 1
                        stats["rows_completed"] += 1
                        break
                    value = get_byte()
                    stats["fill_ops"] += 1
                    for _ in range(count):
                        if 0 <= x < width:
                            out[y * width + x] = value
                            stats["pixels_written"] += 1
                        else:
                            stats["overflow_writes"] += 1
                        x += 1
                    ctrl = get_byte()
                else:
                    if count == 0:
                        skip = get_byte()
                        x += skip
                        stats["pixels_skipped"] += skip
                        stats["skip_ops"] += 1
                        ctrl = get_byte()
                    else:
                        stats["literal_ops"] += 1
                        for _ in range(count):
                            value = get_byte()
                            if 0 <= x < width:
                                out[y * width + x] = value
                                stats["pixels_written"] += 1
                            else:
                                stats["overflow_writes"] += 1
                            x += 1
                        ctrl = get_byte()
        except DecodeError as e:
            msg = f"row {y}: {e}"
            warnings.append(msg)
            if strict:
                raise
            break

    stats["consumed_bytes"] = src
    if src < len(payload):
        warnings.append(f"{len(payload) - src} trailing byte(s) after decoded rows")
    return out, stats, warnings


def grayscale_palette() -> List[int]:
    palette: List[int] = []
    for i in range(256):
        palette.extend([i, i, i])
    return palette


def normalize_palette(palette: Sequence[Tuple[int, int, int]]) -> List[int]:
    flat: List[int] = []
    for i in range(256):
        if i < len(palette):
            r, g, b = palette[i]
        else:
            r = g = b = i
        flat.extend([clamp8(r), clamp8(g), clamp8(b)])
    return flat


def clamp8(v: int) -> int:
    return max(0, min(255, int(v)))


def parse_jasc_pal(text: str) -> List[Tuple[int, int, int]]:
    lines = [ln.strip() for ln in text.splitlines() if ln.strip()]
    if len(lines) < 3 or lines[0].upper() != "JASC-PAL":
        raise DecodeError("not a JASC-PAL file")
    count = int(lines[2], 10)
    out: List[Tuple[int, int, int]] = []
    for ln in lines[3:3 + count]:
        parts = ln.split()
        if len(parts) < 3:
            continue
        out.append((int(parts[0]), int(parts[1]), int(parts[2])))
    return out


def parse_gimp_gpl(text: str) -> List[Tuple[int, int, int]]:
    lines = text.splitlines()
    if not lines or not lines[0].startswith("GIMP Palette"):
        raise DecodeError("not a GIMP GPL palette")
    out: List[Tuple[int, int, int]] = []
    for ln in lines[1:]:
        ln = ln.strip()
        if not ln or ln.startswith("#") or ":" in ln:
            continue
        parts = ln.split()
        if len(parts) >= 3 and all(p.lstrip("+-").isdigit() for p in parts[:3]):
            out.append((int(parts[0]), int(parts[1]), int(parts[2])))
    return out


def parse_riff_pal(data: bytes) -> List[Tuple[int, int, int]]:
    # Windows RIFF PAL usually stores entries as B,G,R,flags in a "data" chunk.
    if len(data) < 24 or data[:4] != b"RIFF" or data[8:12] != b"PAL ":
        raise DecodeError("not a RIFF PAL file")
    pos = 12
    while pos + 8 <= len(data):
        fourcc = data[pos:pos + 4]
        size = u32le(data, pos + 4)
        chunk = data[pos + 8:pos + 8 + size]
        if fourcc == b"data" and len(chunk) >= 4:
            # WORD version, WORD count, then PALETTEENTRY[count]
            count = u16le(chunk, 2)
            out: List[Tuple[int, int, int]] = []
            base = 4
            for i in range(min(count, (len(chunk) - base) // 4)):
                b, g, r, _flags = chunk[base + i * 4:base + i * 4 + 4]
                out.append((r, g, b))
            return out
        pos += 8 + size + (size & 1)
    raise DecodeError("RIFF PAL data chunk not found")


def load_palette(path: Path, vga6bit: bool = False, raw_bgr: bool = False, raw_rgba: bool = False, raw_bgra: bool = False) -> List[Tuple[int, int, int]]:
    data = path.read_bytes()

    # Text formats first.
    try:
        text = data.decode("utf-8")
        if text.startswith("JASC-PAL"):
            pal = parse_jasc_pal(text)
        elif text.startswith("GIMP Palette"):
            pal = parse_gimp_gpl(text)
        else:
            pal = []
        if pal:
            return scale_palette_if_needed(pal, vga6bit)
    except UnicodeDecodeError:
        pass

    # RIFF PAL.
    if data[:4] == b"RIFF" and data[8:12] == b"PAL ":
        return scale_palette_if_needed(parse_riff_pal(data), vga6bit)

    # Raw 256-color formats.
    if len(data) >= 1024 or raw_rgba or raw_bgra:
        step = 4
        count = min(256, len(data) // step)
        pal = []
        for i in range(count):
            a, b, c, _d = data[i * 4:i * 4 + 4]
            if raw_bgra:
                pal.append((c, b, a))
            else:
                pal.append((a, b, c))
        return scale_palette_if_needed(pal, vga6bit)

    if len(data) >= 768:
        step = 3
        count = min(256, len(data) // step)
        pal = []
        for i in range(count):
            a, b, c = data[i * 3:i * 3 + 3]
            if raw_bgr:
                pal.append((c, b, a))
            else:
                pal.append((a, b, c))
        return scale_palette_if_needed(pal, vga6bit)

    raise DecodeError(f"unsupported palette format or too small: {path} ({len(data)} bytes)")


def scale_palette_if_needed(pal: List[Tuple[int, int, int]], vga6bit: bool) -> List[Tuple[int, int, int]]:
    if not vga6bit:
        return [(clamp8(r), clamp8(g), clamp8(b)) for r, g, b in pal]
    # VGA DAC palettes often store 0..63 channel values. Use bit replication rather than plain *4.
    return [((r & 0x3f) * 255 // 63, (g & 0x3f) * 255 // 63, (b & 0x3f) * 255 // 63) for r, g, b in pal]


def load_remap(path: Path) -> List[int]:
    data = path.read_bytes()
    if len(data) < 256:
        raise DecodeError(f"remap table must contain at least 256 bytes: {path}")
    return list(data[:256])


def apply_remap(pixels: bytearray, remap: Optional[List[int]]) -> bytearray:
    if remap is None:
        return pixels
    return bytearray(remap[p] for p in pixels)


def save_indexed_png(path: Path, pixels: bytearray, width: int, height: int, palette_flat: List[int]) -> None:
    if Image is None:
        raise DecodeError("Pillow is not installed; cannot write PNGs")
    img = Image.frombytes("P", (width, height), bytes(pixels))
    img.putpalette(palette_flat[:768])
    img.save(path)


def save_rgb_png(path: Path, pixels: bytearray, width: int, height: int, palette: Sequence[Tuple[int, int, int]], transparent_index: Optional[int]) -> None:
    if Image is None:
        raise DecodeError("Pillow is not installed; cannot write PNGs")
    rgba = bytearray(width * height * 4)
    for i, idx in enumerate(pixels):
        if idx < len(palette):
            r, g, b = palette[idx]
        else:
            r = g = b = idx
        a = 0 if transparent_index is not None and idx == transparent_index else 255
        j = i * 4
        rgba[j:j + 4] = bytes((clamp8(r), clamp8(g), clamp8(b), a))
    img = Image.frombytes("RGBA", (width, height), bytes(rgba))
    img.save(path)


def decode_records(
    database_path: Path,
    out_dir: Path,
    first: int,
    last: int,
    strict: bool = False,
    palette_path: Optional[Path] = None,
    palette_vga6bit: bool = False,
    raw_bgr: bool = False,
    raw_rgba: bool = False,
    raw_bgra: bool = False,
    remap_path: Optional[Path] = None,
    transparent_index: Optional[int] = None,
    write_indexed: bool = True,
    write_rgb: bool = True,
) -> None:
    data, spans = read_database_mw2(database_path)
    out_dir.mkdir(parents=True, exist_ok=True)
    indexed_dir = out_dir / "png_indexed"
    rgb_dir = out_dir / "png_rgb"
    if write_indexed:
        indexed_dir.mkdir(parents=True, exist_ok=True)
    if write_rgb:
        rgb_dir.mkdir(parents=True, exist_ok=True)

    loaded_palette: Optional[List[Tuple[int, int, int]]] = None
    if palette_path is not None:
        loaded_palette = load_palette(palette_path, vga6bit=palette_vga6bit, raw_bgr=raw_bgr, raw_rgba=raw_rgba, raw_bgra=raw_bgra)
        if len(loaded_palette) < 256:
            loaded_palette = loaded_palette + [(i, i, i) for i in range(len(loaded_palette), 256)]
        (out_dir / "palette_loaded.tsv").write_text(
            "index\tr\tg\tb\n" + "".join(f"{i}\t{r}\t{g}\t{b}\n" for i, (r, g, b) in enumerate(loaded_palette[:256])),
            encoding="utf-8",
        )
    diagnostic_palette: List[Tuple[int, int, int]] = [(i, i, i) for i in range(256)]
    active_palette = loaded_palette if loaded_palette is not None else diagnostic_palette
    active_palette_flat = normalize_palette(active_palette)

    remap: Optional[List[int]] = load_remap(remap_path) if remap_path is not None else None
    if remap is not None:
        (out_dir / "remap_loaded.tsv").write_text(
            "source_index\tdest_index\n" + "".join(f"{i}\t{v}\n" for i, v in enumerate(remap)),
            encoding="utf-8",
        )

    record_rows: List[RecordInfo] = []
    entry_rows: List[EntryInfo] = []
    sub_rows: List[SubresourceInfo] = []

    for rid in iter_record_ids(first, last, len(spans)):
        start, size = spans[rid - 1]
        record = data[start:start + size]
        rec_info, entries = parse_110_entries(record, rid)
        rec_info.offset = start
        rec_info.size = size
        record_rows.append(rec_info)
        entry_rows.extend(entries)

        for entry in entries:
            sub = read_subresource_header(record, entry)
            if sub is None:
                continue

            warnings: List[str] = []
            if sub.width <= 0 or sub.height <= 0:
                warnings.append("non-positive dimensions from bounds")
            elif sub.width > 2048 or sub.height > 2048:
                warnings.append("very large dimensions from bounds; skipped PNG decode")
            elif sub.payload_size <= 0:
                warnings.append("empty payload")
            else:
                payload = record[sub.payload_offset:entry.inferred_end_offset]
                try:
                    pixels, stats, rle_warnings = decode_unclipped_rle(payload, sub.width, sub.height, strict=strict)
                    for k, v in stats.items():
                        if hasattr(sub, k):
                            setattr(sub, k, v)
                    warnings.extend(rle_warnings)
                    pixels_for_output = apply_remap(pixels, remap)

                    stem = f"record_{rid:02d}_0x{rid:02x}_sub_{entry.subresource_index:03d}_{sub.width}x{sub.height}"
                    if write_indexed:
                        ipath = indexed_dir / f"{stem}.png"
                        save_indexed_png(ipath, pixels_for_output, sub.width, sub.height, active_palette_flat)
                        sub.indexed_png_path = str(ipath.relative_to(out_dir))
                    if write_rgb:
                        rpath = rgb_dir / f"{stem}.png"
                        save_rgb_png(rpath, pixels_for_output, sub.width, sub.height, active_palette, transparent_index)
                        sub.rgb_png_path = str(rpath.relative_to(out_dir))
                    sub.decoded = True
                except Exception as e:
                    warnings.append(f"decode failed: {e}")
            sub.warnings = " | ".join(warnings)
            sub_rows.append(sub)

    write_tsv(out_dir / "records.tsv", record_rows)
    write_tsv(out_dir / "entries.tsv", entry_rows)
    write_tsv(out_dir / "subresources.tsv", sub_rows)

    summary = {
        "database_path": str(database_path),
        "output_dir": str(out_dir),
        "record_range_1based": [first, last],
        "records_scanned": len(record_rows),
        "entries_seen": len(entry_rows),
        "subresources_seen": len(sub_rows),
        "subresources_decoded": sum(1 for s in sub_rows if s.decoded),
        "indexed_png_count": sum(1 for s in sub_rows if s.indexed_png_path),
        "rgb_png_count": sum(1 for s in sub_rows if s.rgb_png_path),
        "palette_path": str(palette_path) if palette_path else None,
        "palette_vga6bit": palette_vga6bit,
        "remap_path": str(remap_path) if remap_path else None,
        "transparent_index": transparent_index,
        "notes": [
            "RLE/index decode is the validated i76shell 1003ad68 interpretation.",
            "Without --palette, PNGs use diagnostic grayscale while preserving palette indices.",
            "With --palette, png_indexed files retain indexed pixels with the supplied palette; png_rgb files are expanded RGBA for easy viewing.",
            "Use --remap-table to test a 256-byte DAT_1004ee3c-style index translation before palette application.",
        ],
    }
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    print(json.dumps(summary, indent=2))


def write_tsv(path: Path, rows: List[object]) -> None:
    if not rows:
        path.write_text("", encoding="utf-8")
        return
    fields = list(asdict(rows[0]).keys())
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fields, delimiter="\t")
        writer.writeheader()
        for row in rows:
            writer.writerow(asdict(row))


def parse_record_range(text: str) -> Tuple[int, int]:
    if "-" in text:
        a, b = text.split("-", 1)
    elif ":" in text:
        a, b = text.split(":", 1)
    else:
        a = b = text
    return int(a, 0), int(b, 0)


def parse_optional_index(text: Optional[str]) -> Optional[int]:
    if text is None or text == "":
        return None
    v = int(text, 0)
    if not 0 <= v <= 255:
        raise argparse.ArgumentTypeError("index must be 0..255")
    return v


def main(argv: Optional[List[str]] = None) -> int:
    p = argparse.ArgumentParser(description="Decode i76 DATABASE.MW2 1.10 shell image records with optional palette/remap application")
    p.add_argument("database_mw2", type=Path, help="Path to DATABASE.MW2")
    p.add_argument("out_dir", type=Path, help="Output directory")
    p.add_argument("--records", default=f"0x{DEFAULT_FIRST_RECORD:x}-0x{DEFAULT_LAST_RECORD:x}",
                   help="1-based record id range to scan, default: 0x24-0x40")
    p.add_argument("--strict", action="store_true", help="Abort a subresource decode on first RLE warning")
    p.add_argument("--palette", type=Path, help="Optional 256-color palette: raw 768 RGB, raw 1024 RGBA, RIFF PAL, JASC PAL, or GIMP GPL")
    p.add_argument("--palette-vga6bit", action="store_true", help="Scale palette channels from 0..63 VGA DAC values to 0..255")
    p.add_argument("--palette-raw-bgr", action="store_true", help="Interpret raw 768-byte palettes as BGR instead of RGB")
    p.add_argument("--palette-raw-rgba", action="store_true", help="Force raw 1024-byte palettes as RGBA")
    p.add_argument("--palette-raw-bgra", action="store_true", help="Force raw 1024-byte palettes as BGRA")
    p.add_argument("--remap-table", type=Path, help="Optional 256-byte index remap table applied before palette lookup")
    p.add_argument("--transparent-index", type=parse_optional_index, help="Optional palette index to make transparent in RGB/RGBA output, e.g. 0")
    p.add_argument("--no-indexed", action="store_true", help="Do not write indexed PNGs")
    p.add_argument("--no-rgb", action="store_true", help="Do not write RGBA PNGs")
    args = p.parse_args(argv)

    first, last = parse_record_range(args.records)
    if first > last:
        first, last = last, first
    try:
        decode_records(
            args.database_mw2,
            args.out_dir,
            first,
            last,
            strict=args.strict,
            palette_path=args.palette,
            palette_vga6bit=args.palette_vga6bit,
            raw_bgr=args.palette_raw_bgr,
            raw_rgba=args.palette_raw_rgba,
            raw_bgra=args.palette_raw_bgra,
            remap_path=args.remap_table,
            transparent_index=args.transparent_index,
            write_indexed=not args.no_indexed,
            write_rgb=not args.no_rgb,
        )
    except Exception as e:
        print(f"error: {e}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
