#!/usr/bin/env python3

import argparse
import json
import math
import struct
import tarfile
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    Image = None


CONFIRMED_LOCALIZED_1BPP_GLYPH_RECORDS = {65}
CONFIRMED_ASCII_8BPP_GLYPH_RECORDS = {66, 67, 68, 69, 70, 71}


def u32le(data, off):
    if off < 0 or off + 4 > len(data):
        return None
    return struct.unpack_from("<I", data, off)[0]


def parse_database(path):
    data = path.read_bytes()
    if len(data) < 4:
        raise ValueError("File too small")

    count = u32le(data, 0)
    if count is None or count <= 0 or count > 100000:
        raise ValueError(f"Implausible record count: {count}")

    table_end = 4 + count * 4
    if table_end > len(data):
        raise ValueError("Offset table extends beyond file")

    offsets = [u32le(data, 4 + i * 4) for i in range(count)]

    records = []
    for i, off in enumerate(offsets):
        next_off = offsets[i + 1] if i + 1 < len(offsets) else len(data)

        if off is None or next_off is None or off > len(data) or next_off > len(data) or next_off < off:
            blob = b""
            size = 0
        else:
            blob = data[off:next_off]
            size = len(blob)

        records.append({
            "id_1based": i + 1,
            "id_hex": f"0x{i + 1:02x}",
            "offset": off,
            "size": size,
            "data": blob,
        })

    return {
        "source": str(path),
        "file_size": len(data),
        "record_count": count,
        "table_end": table_end,
        "records": records,
    }


def classify_record(record):
    rid = record["id_1based"]
    blob = record["data"]

    if rid in CONFIRMED_LOCALIZED_1BPP_GLYPH_RECORDS:
        return "glyph_sheet_localized_dbcs_1bpp"

    if rid in CONFIRMED_ASCII_8BPP_GLYPH_RECORDS:
        return "glyph_sheet_ascii_8bpp"

    if len(blob) >= 12 and blob[:4] == b"RIFF" and blob[8:12] == b"WAVE":
        return "riff_wave"

    if len(blob) >= 12 and blob[:4] == b"PIFF" and blob[8:12] == b"WAVE":
        return "piff_wave_like"

    if blob.startswith(b"1.\x00\x00"):
        return "mw2_glyph_or_bitmap_table_v1"

    if blob.startswith(b"1.10"):
        return "mw2_multi_bitmap_v1_10"

    if b"PRODUCTION TEAM" in blob[:4096]:
        return "credits_text"

    return "mw2_binary_resource_candidate" if blob else "empty_or_unknown"


def glyph_encoding_for_record(record_id):
    if record_id in CONFIRMED_LOCALIZED_1BPP_GLYPH_RECORDS:
        return "1bpp_bitpacked_rows"

    if record_id in CONFIRMED_ASCII_8BPP_GLYPH_RECORDS:
        return "8bpp_row_major"

    return "unknown"


def parse_glyph_sheet(record):
    blob = record["data"]

    if len(blob) < 20 or not blob.startswith(b"1.\x00\x00"):
        return None

    entry_count = u32le(blob, 4)
    glyph_height = u32le(blob, 8)
    flags = u32le(blob, 12)

    if entry_count is None or glyph_height is None or flags is None:
        return None

    if entry_count <= 0 or entry_count > 20000:
        return None

    table_start = 16
    table_end = table_start + entry_count * 4

    if table_end > len(blob):
        return None

    offsets = [u32le(blob, table_start + i * 4) for i in range(entry_count)]

    if any(o is None for o in offsets):
        return None

    encoding = glyph_encoding_for_record(record["id_1based"])

    entries = []
    offsets_monotonic = True
    first_offset = offsets[0] if offsets else None

    for i, start in enumerate(offsets):
        end = offsets[i + 1] if i + 1 < entry_count else len(blob)

        if i + 1 < entry_count and offsets[i] > offsets[i + 1]:
            offsets_monotonic = False

        valid = True
        if start is None or end is None or start > end or start < table_end or end > len(blob):
            valid = False

        payload_size = (end - start) if valid else 0
        width = u32le(blob, start) if valid and payload_size >= 4 else None
        bitmap_size = max(0, payload_size - 4)

        if width is not None:
            expected_8bpp = width * glyph_height
            expected_1bpp = ((width + 7) // 8) * glyph_height
        else:
            expected_8bpp = None
            expected_1bpp = None

        if encoding == "8bpp_row_major":
            looks_expected = width is not None and bitmap_size == expected_8bpp
        elif encoding == "1bpp_bitpacked_rows":
            looks_expected = width is not None and bitmap_size == expected_1bpp
        else:
            looks_expected = False

        if record["id_1based"] in CONFIRMED_ASCII_8BPP_GLYPH_RECORDS:
            codepoint_guess = i
            char_guess = chr(i) if 32 <= i <= 126 else None
            mapping_note = "ascii_index_guess"
        elif record["id_1based"] in CONFIRMED_LOCALIZED_1BPP_GLYPH_RECORDS:
            codepoint_guess = i
            char_guess = None
            mapping_note = "localized_dbcs_mapping_via_DAT_1004ef9c"
        else:
            codepoint_guess = i
            char_guess = chr(i) if 32 <= i <= 126 else None
            mapping_note = "unconfirmed_index_guess"

        entries.append({
            "index": i,
            "codepoint_guess": codepoint_guess,
            "char_guess": char_guess,
            "mapping_note": mapping_note,
            "absolute_start": start,
            "absolute_end": end,
            "payload_size": payload_size,
            "width": width,
            "glyph_height": glyph_height,
            "bitmap_size": bitmap_size,
            "encoding": encoding,
            "expected_8bpp_bitmap_size": expected_8bpp,
            "expected_1bpp_bitmap_size": expected_1bpp,
            "matches_expected_encoding_size": looks_expected,
            "valid_entry_bounds": valid,
        })

    return {
        "format": "mw2_glyph_sheet_v1_absolute_offsets",
        "magic": "1.\\0\\0",
        "entry_count": entry_count,
        "glyph_height": glyph_height,
        "flags": flags,
        "encoding": encoding,
        "table_start": table_start,
        "table_end": table_end,
        "first_offset": first_offset,
        "first_offset_equals_table_end": first_offset == table_end,
        "offsets_are_absolute_starts": True,
        "offsets_monotonic": offsets_monotonic,
        "entries": entries,
    }


def decode_8bpp(record, entry):
    blob = record["data"]
    start = entry["absolute_start"]
    end = entry["absolute_end"]
    width = entry["width"]
    height = entry["glyph_height"]

    if width is None or width <= 0 or width > 4096:
        return None

    if start is None or end is None or start + 4 > end or end > len(blob):
        return None

    pixels = blob[start + 4:end]
    expected = width * height

    if len(pixels) < expected:
        return None

    return width, height, list(pixels[:expected])


def decode_1bpp(record, entry):
    blob = record["data"]
    start = entry["absolute_start"]
    end = entry["absolute_end"]
    width = entry["width"]
    height = entry["glyph_height"]

    if width is None or width <= 0 or width > 4096:
        return None

    if start is None or end is None or start + 4 > end or end > len(blob):
        return None

    packed = blob[start + 4:end]
    row_bytes = (width + 7) // 8
    expected = row_bytes * height

    if len(packed) < expected:
        return None

    pixels = []

    # Matches the shell interpretation closely enough for visualization:
    # walk bits left-to-right in each row, MSB first per byte.
    for y in range(height):
        row_base = y * row_bytes
        for x in range(width):
            b = packed[row_base + (x // 8)]
            bit = 7 - (x & 7)
            on = (b >> bit) & 1
            pixels.append(255 if on else 0)

    return width, height, pixels


def decode_glyph(record, entry):
    encoding = entry.get("encoding")

    if encoding == "1bpp_bitpacked_rows":
        return decode_1bpp(record, entry)

    if encoding == "8bpp_row_major":
        return decode_8bpp(record, entry)

    # Fallback: try 8bpp first.
    decoded = decode_8bpp(record, entry)
    if decoded is not None:
        return decoded

    return decode_1bpp(record, entry)


def write_glyph_png(record, entry, out_path):
    if Image is None:
        return False

    decoded = decode_glyph(record, entry)
    if decoded is None:
        return False

    width, height, pixels = decoded
    img = Image.new("L", (width, height), 0)
    img.putdata(pixels)
    img.save(out_path)
    return True


def render_sheet_preview(record, glyph_info, out_path):
    if Image is None:
        return False

    entries = glyph_info["entries"]
    height = glyph_info["glyph_height"]
    encoding = glyph_info["encoding"]

    # Record 65 is huge. Make a useful preview without producing an enormous sheet.
    if encoding == "1bpp_bitpacked_rows":
        preview_entries = entries[:1024]
        cols = 32
    else:
        preview_entries = entries
        cols = 16

    max_width = 0
    for e in preview_entries:
        w = e.get("width")
        if w is not None and 0 < w < 512:
            max_width = max(max_width, w)

    cell_w = max(16, min(64, max_width + 4))
    cell_h = max(16, height + 4)
    rows = int(math.ceil(len(preview_entries) / cols))

    img = Image.new("L", (cols * cell_w, rows * cell_h), 0)

    for local_idx, e in enumerate(preview_entries):
        decoded = decode_glyph(record, e)
        if decoded is None:
            continue

        width, glyph_h, pixels = decoded
        x0 = (local_idx % cols) * cell_w
        y0 = (local_idx // cols) * cell_h

        for y in range(glyph_h):
            for x in range(width):
                v = pixels[y * width + x]
                if v:
                    px = x0 + x
                    py = y0 + y
                    if 0 <= px < img.width and 0 <= py < img.height:
                        img.putpixel((px, py), v)

    img.save(out_path)
    return True


def dump_raw_record(record, out_dir):
    rid = record["id_1based"]
    category = classify_record(record)
    blob = record["data"]

    suffix = ".bin"
    if category == "riff_wave":
        suffix = ".wav"
    elif category == "piff_wave_like":
        suffix = ".piff"
    elif category == "credits_text":
        suffix = ".txt"

    path = out_dir / f"record_{rid:03d}_{category}{suffix}"
    path.write_bytes(blob)

    if category == "piff_wave_like" and len(blob) >= 4:
        patched = b"R" + blob[1:]
        patched_path = out_dir / f"record_{rid:03d}_piff_patched_to_riff.wav"
        patched_path.write_bytes(patched)

    return path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("database", type=Path)
    parser.add_argument("--out", type=Path, default=Path("DATABASE_MW2_glyphs_pass005"))
    parser.add_argument("--make-tar", action="store_true")
    parser.add_argument("--record65-glyph-png-limit", type=int, default=1024)
    args = parser.parse_args()

    db = parse_database(args.database)

    out_dir = args.out
    out_dir.mkdir(parents=True, exist_ok=True)

    records_dir = out_dir / "records"
    glyph_json_dir = out_dir / "glyph_json"
    glyph_png_dir = out_dir / "glyph_png"
    preview_dir = out_dir / "previews"

    records_dir.mkdir(exist_ok=True)
    glyph_json_dir.mkdir(exist_ok=True)
    glyph_png_dir.mkdir(exist_ok=True)
    preview_dir.mkdir(exist_ok=True)

    manifest = {
        "source": str(args.database),
        "file_size": db["file_size"],
        "record_count": db["record_count"],
        "table_end": db["table_end"],
        "confirmed_glyph_sheets": {
            "localized_dbcs_1bpp": sorted(CONFIRMED_LOCALIZED_1BPP_GLYPH_RECORDS),
            "ascii_8bpp": sorted(CONFIRMED_ASCII_8BPP_GLYPH_RECORDS),
        },
        "records": [],
        "class_counts": {},
    }

    for rec in db["records"]:
        rid = rec["id_1based"]
        category = classify_record(rec)
        manifest["class_counts"][category] = manifest["class_counts"].get(category, 0) + 1

        raw_path = dump_raw_record(rec, records_dir)
        glyph_info = parse_glyph_sheet(rec)

        record_entry = {
            "id_1based": rid,
            "id_hex": rec["id_hex"],
            "offset": rec["offset"],
            "size": rec["size"],
            "category": category,
            "raw_file": str(raw_path.relative_to(out_dir)),
            "header_hex": rec["data"][:32].hex(" "),
        }

        if glyph_info is not None:
            glyph_json_path = glyph_json_dir / f"record_{rid:03d}_{category}.json"
            glyph_manifest = {
                "id_1based": rid,
                "category": category,
                "offset": rec["offset"],
                "size": rec["size"],
                "glyph_sheet": glyph_info,
            }
            glyph_json_path.write_text(json.dumps(glyph_manifest, indent=2), encoding="utf-8")

            record_glyph_png_dir = glyph_png_dir / f"record_{rid:03d}_{category}"
            record_glyph_png_dir.mkdir(exist_ok=True)

            if rid in CONFIRMED_LOCALIZED_1BPP_GLYPH_RECORDS:
                max_individual = args.record65_glyph_png_limit
            else:
                max_individual = len(glyph_info["entries"])

            glyph_png_count = 0
            for ge in glyph_info["entries"][:max_individual]:
                png_path = record_glyph_png_dir / f"glyph_{ge['index']:04d}.png"
                if write_glyph_png(rec, ge, png_path):
                    glyph_png_count += 1

            preview_path = preview_dir / f"record_{rid:03d}_{category}_preview.png"
            preview_ok = render_sheet_preview(rec, glyph_info, preview_path)

            # Collect sanity stats.
            entry_count = len(glyph_info["entries"])
            matching_entries = 0
            valid_entries = 0
            nonempty_entries = 0

            for ge in glyph_info["entries"]:
                if ge.get("valid_entry_bounds"):
                    valid_entries += 1
                if ge.get("matches_expected_encoding_size"):
                    matching_entries += 1
                if ge.get("width") is not None and ge.get("width") > 0 and ge.get("bitmap_size", 0) > 0:
                    nonempty_entries += 1

            record_entry.update({
                "glyph_info_file": str(glyph_json_path.relative_to(out_dir)),
                "glyph_preview_file": str(preview_path.relative_to(out_dir)) if preview_ok else None,
                "glyph_png_dir": str(record_glyph_png_dir.relative_to(out_dir)),
                "glyph_png_count": glyph_png_count,
                "glyph_entry_count": glyph_info["entry_count"],
                "glyph_height": glyph_info["glyph_height"],
                "flags": glyph_info["flags"],
                "encoding": glyph_info["encoding"],
                "table_end": glyph_info["table_end"],
                "first_offset": glyph_info["first_offset"],
                "first_offset_equals_table_end": glyph_info["first_offset_equals_table_end"],
                "offset_model": "absolute_start_offsets_from_record_start",
                "valid_entries": valid_entries,
                "nonempty_entries": nonempty_entries,
                "entries_matching_expected_encoding_size": matching_entries,
                "entry_count_for_stats": entry_count,
            })

        manifest["records"].append(record_entry)

    (out_dir / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    summary = {
        "source": str(args.database),
        "file_size": db["file_size"],
        "record_count": db["record_count"],
        "class_counts": manifest["class_counts"],
        "confirmed_glyph_sheets": manifest["confirmed_glyph_sheets"],
        "glyph_encoding_model": {
            "record_65": "localized/DBCS glyph sheet, 1bpp bit-packed rows",
            "records_66_to_71": "ASCII glyph sheets, 8bpp row-major glyph pixels",
        },
        "offset_model": "glyph sheet entry_offsets are absolute start offsets from record start",
    }

    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")

    if args.make_tar:
        tar_path = out_dir.with_suffix(".tar.gz")
        with tarfile.open(tar_path, "w:gz") as tf:
            tf.add(out_dir, arcname=out_dir.name)
        print(f"Wrote {tar_path}")

    print(json.dumps(summary, indent=2))


if __name__ == "__main__":
    main()
