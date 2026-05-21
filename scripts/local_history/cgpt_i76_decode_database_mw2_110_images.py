#!/usr/bin/env python3
# Decode Interstate '76 / MechWarrior-2-style DATABASE.MW2 "1.10" shell image records.
#
# Current target: DATABASE.MW2 records 0x24..0x40, as used by i76shell.dll preload/draw paths.
# This is a first-pass diagnostic decoder based on the i76shell.dll routines:
#   10039390 draw_mw2_image_subresource_to_shell_surface
#   1003a8f4 blit_mw2_image_subresource_rle_clipped
#   1003ad68 blit_mw2_image_subresource_rle_unclipped
#   1003ae8a blit_mw2_image_subresource_rle_transparent

from __future__ import annotations

import argparse
import csv
import json
import struct
import sys
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

try:
    from PIL import Image
except Exception:  # pragma: no cover - this is a user environment dependency.
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
    png_path: str = ""


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
                # Do not trust this yet, but record when it looks end-like.
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

    Command byte:
      bit 0 == 0, count > 0: fill next byte for count pixels
      bit 0 == 1, count > 0: copy count literal bytes
      bit 0 == 1, count == 0: extended skip; next byte is skip count, then another command
      bit 0 == 0, count == 0: end-of-line

    The game blitter writes into an already-sized destination surface. For standalone decoding, writes and skips
    are clipped to [0,width) so malformed/partially understood streams still produce diagnostic images.
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
        # This is normal when the inferred subresource end is not exact, but worth reporting.
        warnings.append(f"{len(payload) - src} trailing byte(s) after decoded rows")
    return out, stats, warnings


def save_indexed_png(path: Path, pixels: bytearray, width: int, height: int) -> None:
    if Image is None:
        raise DecodeError("Pillow is not installed; cannot write PNGs")
    img = Image.frombytes("P", (width, height), bytes(pixels))
    # Diagnostic grayscale palette. Values remain original palette indices in the pixel data.
    palette: List[int] = []
    for i in range(256):
        palette.extend([i, i, i])
    img.putpalette(palette)
    img.save(path)


def decode_records(database_path: Path, out_dir: Path, first: int, last: int, strict: bool = False) -> None:
    data, spans = read_database_mw2(database_path)
    out_dir.mkdir(parents=True, exist_ok=True)
    png_dir = out_dir / "png"
    png_dir.mkdir(parents=True, exist_ok=True)

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
                    png_path = png_dir / f"record_{rid:02d}_0x{rid:02x}_sub_{entry.subresource_index:03d}_{sub.width}x{sub.height}.png"
                    save_indexed_png(png_path, pixels, sub.width, sub.height)
                    sub.png_path = str(png_path.relative_to(out_dir))
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
        "png_count": sum(1 for s in sub_rows if s.png_path),
        "notes": [
            "PNG files use a diagnostic grayscale palette; pixel values are preserved as palette indices.",
            "This implements the current interpretation of i76shell.dll function 1003ad68.",
            "The second dword in each 1.10 table entry is recorded but not yet trusted as size/end metadata.",
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


def main(argv: Optional[List[str]] = None) -> int:
    p = argparse.ArgumentParser(description="Decode i76 DATABASE.MW2 1.10 shell image records")
    p.add_argument("database_mw2", type=Path, help="Path to DATABASE.MW2")
    p.add_argument("out_dir", type=Path, help="Output directory")
    p.add_argument("--records", default=f"0x{DEFAULT_FIRST_RECORD:x}-0x{DEFAULT_LAST_RECORD:x}",
                   help="1-based record id range to scan, default: 0x24-0x40")
    p.add_argument("--strict", action="store_true", help="Abort a subresource decode on first RLE warning")
    args = p.parse_args(argv)

    first, last = parse_record_range(args.records)
    if first > last:
        first, last = last, first
    try:
        decode_records(args.database_mw2, args.out_dir, first, last, strict=args.strict)
    except Exception as e:
        print(f"error: {e}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
