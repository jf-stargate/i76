#!/usr/bin/env python3
"""
Build a durable Interstate '76 DATABASE.MW2 shell resource map from Ghidra trace outputs.

Primary input:
  cgpt_i76shell_precise_screen_callsite_map_YYYYMMDD_HHMMSS/
or its extracted folder containing:
  surface_load_calls.tsv
  database_record_get_calls.tsv
  overlay_draw_calls.tsv
  screen_state_resource_summary.tsv
  special_record64_context.tsv

The script emits:
  database_mw2_resource_map.json
  database_mw2_resource_map.tsv
  shell_screen_surface_map.tsv
  shell_overlay_usage_map.tsv
  shell_state_function_map.tsv
  summary.txt

The map includes both:
  - static/manual classification knowledge accumulated during the reverse-engineering pass
  - callsite evidence extracted from the supplied Ghidra trace

No binary parsing is required here; this script only normalizes trace artifacts.
"""

from __future__ import annotations

import argparse
import csv
import json
import re
from collections import defaultdict
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Set, Tuple


# -----------------------------
# TSV helpers
# -----------------------------

def read_tsv(path: Path) -> List[Dict[str, str]]:
    if not path.exists():
        return []
    with path.open("r", encoding="utf-8", errors="replace", newline="") as f:
        reader = csv.DictReader(f, delimiter="\t")
        return [dict(row) for row in reader]


def write_tsv(path: Path, rows: List[Dict[str, Any]], fieldnames: List[str]) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t", extrasaction="ignore")
        writer.writeheader()
        for row in rows:
            writer.writerow({k: to_tsv_cell(row.get(k, "")) for k in fieldnames})


def to_tsv_cell(v: Any) -> str:
    if v is None:
        return ""
    if isinstance(v, (list, tuple, set)):
        return ",".join(str(x) for x in v)
    if isinstance(v, dict):
        return json.dumps(v, sort_keys=True)
    return str(v)


def parse_int_maybe(s: Any) -> Optional[int]:
    if s is None:
        return None
    text = str(s).strip()
    if not text:
        return None
    try:
        return int(text, 0)
    except Exception:
        pass
    m = re.search(r"\b(0x[0-9a-fA-F]+|\d+)\b", text)
    if m:
        try:
            return int(m.group(1), 0)
        except Exception:
            return None
    return None


def parse_int_list(s: Any) -> List[int]:
    if s is None:
        return []
    text = str(s).strip()
    if not text:
        return []
    out: List[int] = []
    for part in re.split(r"[,\s;]+", text):
        part = part.strip()
        if not part:
            continue
        try:
            out.append(int(part, 0))
        except Exception:
            continue
    seen = set()
    uniq = []
    for v in out:
        if v not in seen:
            uniq.append(v)
            seen.add(v)
    return uniq


def add_unique_list(dst: List[Any], value: Any) -> None:
    if value is None or value == "":
        return
    if value not in dst:
        dst.append(value)


# -----------------------------
# Core static classification
# -----------------------------

def initial_record_map() -> Dict[int, Dict[str, Any]]:
    records: Dict[int, Dict[str, Any]] = {}

    def ensure(rid: int) -> Dict[str, Any]:
        if rid not in records:
            records[rid] = {
                "record_id": rid,
                "hex_id": f"0x{rid:02x}",
                "class": "unknown",
                "subclass": "",
                "status": "unclassified",
                "description": "",
                "palette_source_record": None,
                "palette_group": "",
                "format": "",
                "encoding": "",
                "known_loader_functions": [],
                "known_user_functions": [],
                "evidence": [],
                "notes": [],
            }
        return records[rid]

    for rid in range(1, 84):
        ensure(rid)

    # Records 1-32: confirmed compressed shell RLE surfaces.
    for rid in range(1, 33):
        r = ensure(rid)
        r["class"] = "shell_surface"
        r["subclass"] = "compressed_rle_screen_surface"
        r["status"] = "decoded"
        r["format"] = "mpack-compressed shell RLE surface"
        r["encoding"] = "mpack LZSS -> shell simple RLE at +0x80; trailing RGB8 palette"
        r["description"] = "Compressed shell screen/background surface with trailing 768-byte RGB8 palette."
        r["palette_source_record"] = rid
        r["evidence"].append("Decoded by cgpt_i76_decode_database_mw2_shell_rle_surfaces_v3.py / broad v2 scan.")

    # Palette groups from broad scan.
    group_a = [1,2,3,4,6,7,8,9,10,11,12,13,16,18,19,20,21,22,23,24,25,26,28,29,30,31,32]
    for rid in group_a:
        ensure(rid)["palette_group"] = "A_common_shell_ui_palette_record1"
    ensure(5)["palette_group"] = "B_record5"
    ensure(14)["palette_group"] = "C_record14"
    ensure(15)["palette_group"] = "D_records15_17"
    ensure(17)["palette_group"] = "D_records15_17"
    ensure(27)["palette_group"] = "E_record27_final_mission_special"

    # Records 33-35: unresolved randomized shell resources.
    for rid in range(33, 36):
        r = ensure(rid)
        r["class"] = "shell_resource"
        r["subclass"] = "randomized_shell_resource"
        r["status"] = "format_unresolved"
        r["description"] = "Random-selection shell resource loaded by 100196b0; exact format unresolved."
        r["evidence"].append("100196b0 loads records 33, 34, 35 and seeds three rand()%5 globals.")

    # Records 36-63: 1.10 UI overlays.
    for rid in range(36, 64):
        r = ensure(rid)
        r["class"] = "ui_overlay"
        r["subclass"] = "mw2_1_10_multi_image"
        r["status"] = "decoded_indexed"
        r["format"] = "1.10 multi-subresource image"
        r["encoding"] = "custom byte-oriented RLE, direct indexed blit"
        r["description"] = "Ordinary shell/menu 1.10 overlay/sprite/panel resource."
        r["palette_source_record"] = 1
        r["palette_group"] = "A_common_shell_ui_palette_record1"
        r["evidence"].append("Decoded by cgpt_i76_decode_database_mw2_110_images*.py and broad palette bridge.")

    # Record 64: special final mission menu.
    r = ensure(64)
    r["class"] = "ui_overlay"
    r["subclass"] = "mw2_1_10_final_mission_special_menu"
    r["status"] = "decoded_indexed_palette_paired"
    r["format"] = "1.10 multi-subresource image"
    r["encoding"] = "custom byte-oriented RLE, direct indexed blit"
    r["description"] = "Special menu selection screen resource shown before the final mission."
    r["palette_source_record"] = 27
    r["palette_group"] = "E_record27_final_mission_special"
    r["known_loader_functions"].append("10023b60 preload_final_mission_special_menu_record_0x40")
    r["evidence"].append("10023b60 loads DATABASE.MW2 record 0x40 and applies surface record 0x1b / 27.")
    r["evidence"].append("User visually confirmed record 64 colors correctly with palette from surface record 27.")
    r["notes"].append("Not part of ordinary vehicle/menu overlay palette context.")

    # Glyph sheets.
    glyph_info = {
        65: ("localized/DBCS glyph sheet", "1bpp bitpacked rows; 8896 entries; height 12"),
        66: ("ASCII glyph sheet", "8bpp row-major glyphs; 256 entries; height 15"),
        67: ("ASCII glyph sheet", "8bpp row-major glyphs; 256 entries; height 15"),
        68: ("ASCII glyph sheet", "8bpp row-major glyphs; 144 entries; height 12"),
        69: ("ASCII glyph sheet", "8bpp row-major glyphs; 256 entries; height 15"),
        70: ("ASCII glyph sheet", "8bpp row-major glyphs; 256 entries; height 15"),
        71: ("ASCII glyph sheet", "8bpp row-major glyphs; 144 entries; height 10"),
    }
    for rid, (desc, enc) in glyph_info.items():
        r = ensure(rid)
        r["class"] = "glyph_sheet"
        r["subclass"] = desc
        r["status"] = "decoded_structural"
        r["format"] = "mw2_glyph_sheet"
        r["encoding"] = enc
        r["description"] = desc
        r["evidence"].append("Validated by glyph analyzer and manual inspection.")

    # Audio-ish.
    for rid in range(72, 83):
        r = ensure(rid)
        r["class"] = "audio"
        r["subclass"] = "wave_or_piff_wave"
        r["status"] = "classified"
        r["description"] = "WAVE or PIFF/WAVE-like audio record."
        if 72 <= rid <= 80:
            r["format"] = "RIFF/WAVE"
        else:
            r["format"] = "PIFF/WAVE-like"
        r["evidence"].append("Classified by DATABASE.MW2 record analyzer.")

    # Credits.
    r = ensure(83)
    r["class"] = "text"
    r["subclass"] = "credits_text"
    r["status"] = "decoded_text"
    r["format"] = "text"
    r["description"] = "Credits text record."
    r["evidence"].append("Classified by DATABASE.MW2 record analyzer.")

    return records


# -----------------------------
# Trace ingestion
# -----------------------------

def ingest_surface_load_calls(records: Dict[int, Dict[str, Any]], rows: List[Dict[str, str]]) -> List[Dict[str, Any]]:
    surface_map: List[Dict[str, Any]] = []

    for row in rows:
        rec = parse_int_maybe(row.get("likely_surface_record_id", ""))
        caller = row.get("caller_name", "")
        caller_entry = row.get("caller_entry", "")
        callsite = row.get("callsite", "")
        target = row.get("target", "")
        group = row.get("palette_group_observed", "")

        if rec is None:
            continue

        surface_map.append({
            "state_function_entry": caller_entry,
            "state_function": caller,
            "callsite": callsite,
            "surface_record_id": rec,
            "surface_record_hex": f"0x{rec:02x}",
            "palette_group": group,
            "target": target,
        })

        r = records.get(rec)
        if r:
            add_unique_list(r["known_user_functions"], f"{caller_entry} {caller}".strip())
            add_unique_list(r["evidence"], f"{target} call at {callsite} in {caller}.")

    return surface_map


def ingest_database_get_calls(records: Dict[int, Dict[str, Any]], rows: List[Dict[str, str]]) -> None:
    for row in rows:
        rec = parse_int_maybe(row.get("likely_record_id", ""))
        if rec is None or rec not in records:
            continue

        caller = row.get("caller_name", "")
        caller_entry = row.get("caller_entry", "")
        callsite = row.get("callsite", "")
        target = row.get("target", "")

        r = records[rec]
        add_unique_list(r["known_loader_functions"], f"{caller_entry} {caller}".strip())
        add_unique_list(r["evidence"], f"{target} loads record at {callsite} in {caller}.")


def ingest_overlay_draw_calls(records: Dict[int, Dict[str, Any]], rows: List[Dict[str, str]]) -> List[Dict[str, Any]]:
    overlay_rows: List[Dict[str, Any]] = []

    for row in rows:
        caller = row.get("caller_name", "")
        caller_entry = row.get("caller_entry", "")
        callsite = row.get("callsite", "")
        target = row.get("target", "")
        source = row.get("likely_110_record_or_global", "")
        subarg = row.get("likely_subresource_or_small_arg", "")
        globals_nearby = row.get("globals_nearby", "")

        overlay_rows.append({
            "state_function_entry": caller_entry,
            "state_function": caller,
            "callsite": callsite,
            "draw_target": target,
            "source_or_global": source,
            "subresource_or_small_args": subarg,
            "globals_nearby": globals_nearby,
        })

        # If the source directly says recordNN, attach evidence.
        m = re.search(r"record(\d+)", source)
        if m:
            rec = int(m.group(1))
            if rec in records:
                add_unique_list(records[rec]["known_user_functions"], f"{caller_entry} {caller}".strip())
                add_unique_list(records[rec]["evidence"], f"{target} draw call at {callsite} in {caller}.")

    return overlay_rows


def ingest_state_summary(records: Dict[int, Dict[str, Any]], rows: List[Dict[str, str]]) -> List[Dict[str, Any]]:
    out: List[Dict[str, Any]] = []

    for row in rows:
        fn = row.get("function_name", "")
        entry = row.get("function_entry", "")
        surface_records = parse_int_list(row.get("surface_records_seen", ""))
        db_records = parse_int_list(row.get("database_records_seen", ""))
        overlay_globals = row.get("overlay_globals_seen", "")
        notes = row.get("notes", "")

        out.append({
            "function_entry": entry,
            "function_name": fn,
            "surface_records_seen": surface_records,
            "database_records_seen": db_records,
            "overlay_globals_seen": overlay_globals,
            "notes": notes,
        })

        for rec in db_records:
            if rec in records:
                add_unique_list(records[rec]["known_user_functions"], f"{entry} {fn}".strip())
        for rec in surface_records:
            if rec in records:
                add_unique_list(records[rec]["known_user_functions"], f"{entry} {fn}".strip())

    return out


# -----------------------------
# Output shaping
# -----------------------------

def record_map_tsv_rows(records: Dict[int, Dict[str, Any]]) -> List[Dict[str, Any]]:
    rows: List[Dict[str, Any]] = []
    for rid in sorted(records):
        r = records[rid]
        rows.append({
            "record_id": rid,
            "hex_id": r["hex_id"],
            "class": r["class"],
            "subclass": r["subclass"],
            "status": r["status"],
            "description": r["description"],
            "palette_source_record": r["palette_source_record"] if r["palette_source_record"] is not None else "",
            "palette_group": r["palette_group"],
            "format": r["format"],
            "encoding": r["encoding"],
            "known_loader_functions": r["known_loader_functions"],
            "known_user_functions": r["known_user_functions"],
            "notes": r["notes"],
            "evidence": r["evidence"],
        })
    return rows


def build_summary(records: Dict[int, Dict[str, Any]], trace_dir: Path, out_dir: Path) -> str:
    by_class: Dict[str, int] = defaultdict(int)
    by_status: Dict[str, int] = defaultdict(int)
    for r in records.values():
        by_class[r["class"]] += 1
        by_status[r["status"]] += 1

    lines = []
    lines.append("Interstate '76 DATABASE.MW2 shell resource map")
    lines.append("=" * 56)
    lines.append("")
    lines.append(f"Input trace directory: {trace_dir}")
    lines.append(f"Output directory: {out_dir}")
    lines.append("")
    lines.append("Record class counts:")
    for k in sorted(by_class):
        lines.append(f"  {k}: {by_class[k]}")
    lines.append("")
    lines.append("Status counts:")
    for k in sorted(by_status):
        lines.append(f"  {k}: {by_status[k]}")
    lines.append("")
    lines.append("High-confidence classifications:")
    lines.append("  Records 1-32: mpack-compressed shell RLE surfaces with trailing RGB8 palettes.")
    lines.append("  Records 33-35: randomized shell resources loaded by 100196b0; exact format unresolved.")
    lines.append("  Records 36-63: ordinary 1.10 UI overlay resources.")
    lines.append("  Record 64: final-mission special 1.10 menu resource paired with surface/palette record 27.")
    lines.append("  Records 65-71: glyph sheets.")
    lines.append("  Records 72-82: WAVE/PIFF audio-ish records.")
    lines.append("  Record 83: credits text.")
    lines.append("")
    lines.append("Important semantic anchor:")
    lines.append("  Function 10023b60 loads DATABASE.MW2 record 0x40 / 64 and applies surface record 0x1b / 27.")
    lines.append("  User confirmed record 64 is a special menu selection screen shown only before the final mission.")
    lines.append("")
    return "\n".join(lines)


def main() -> None:
    ap = argparse.ArgumentParser(description="Build durable I76 DATABASE.MW2 resource map from shell Ghidra trace outputs")
    ap.add_argument("trace_dir", type=Path, help="Extracted Ghidra trace output folder")
    ap.add_argument("output_dir", type=Path, help="Destination folder for normalized resource map")
    args = ap.parse_args()

    trace_dir = args.trace_dir
    out_dir = args.output_dir
    out_dir.mkdir(parents=True, exist_ok=True)

    records = initial_record_map()

    surface_load_rows = read_tsv(trace_dir / "surface_load_calls.tsv")
    db_get_rows = read_tsv(trace_dir / "database_record_get_calls.tsv")
    overlay_draw_rows = read_tsv(trace_dir / "overlay_draw_calls.tsv")
    state_summary_rows = read_tsv(trace_dir / "screen_state_resource_summary.tsv")

    surface_map = ingest_surface_load_calls(records, surface_load_rows)
    ingest_database_get_calls(records, db_get_rows)
    overlay_map = ingest_overlay_draw_calls(records, overlay_draw_rows)
    state_map = ingest_state_summary(records, state_summary_rows)

    # Add hard semantic evidence for special record 64 even if the input trace is missing files.
    add_unique_list(records[64]["evidence"], "Manual semantic observation: final mission pre-launch special menu selection screen.")
    add_unique_list(records[64]["notes"], "Palette pairing: use surface record 27.")
    add_unique_list(records[27]["evidence"], "Palette/surface paired with special record 64 via 10023b60.")
    add_unique_list(records[27]["notes"], "Final-mission special screen palette group.")

    # JSON.
    json_obj = {
        "schema": "i76.database_mw2_resource_map.v1",
        "source_trace_dir": str(trace_dir),
        "records": [records[rid] for rid in sorted(records)],
        "surface_load_map": surface_map,
        "overlay_draw_map": overlay_map,
        "state_function_map": state_map,
        "known_special_pairings": [
            {
                "overlay_record_id": 64,
                "overlay_record_hex": "0x40",
                "surface_palette_record_id": 27,
                "surface_palette_record_hex": "0x1b",
                "function": "10023b60 preload_final_mission_special_menu_record_0x40",
                "meaning": "special menu selection screen before final mission",
                "confidence": "high",
            }
        ],
    }
    (out_dir / "database_mw2_resource_map.json").write_text(json.dumps(json_obj, indent=2), encoding="utf-8")

    # TSVs.
    write_tsv(
        out_dir / "database_mw2_resource_map.tsv",
        record_map_tsv_rows(records),
        [
            "record_id",
            "hex_id",
            "class",
            "subclass",
            "status",
            "description",
            "palette_source_record",
            "palette_group",
            "format",
            "encoding",
            "known_loader_functions",
            "known_user_functions",
            "notes",
            "evidence",
        ],
    )

    write_tsv(
        out_dir / "shell_screen_surface_map.tsv",
        surface_map,
        [
            "state_function_entry",
            "state_function",
            "callsite",
            "surface_record_id",
            "surface_record_hex",
            "palette_group",
            "target",
        ],
    )

    write_tsv(
        out_dir / "shell_overlay_usage_map.tsv",
        overlay_map,
        [
            "state_function_entry",
            "state_function",
            "callsite",
            "draw_target",
            "source_or_global",
            "subresource_or_small_args",
            "globals_nearby",
        ],
    )

    write_tsv(
        out_dir / "shell_state_function_map.tsv",
        state_map,
        [
            "function_entry",
            "function_name",
            "surface_records_seen",
            "database_records_seen",
            "overlay_globals_seen",
            "notes",
        ],
    )

    summary = build_summary(records, trace_dir, out_dir)
    (out_dir / "summary.txt").write_text(summary, encoding="utf-8")

    print(f"[+] wrote resource map to {out_dir}")
    print("[+] records:", len(records))
    print("[+] surface map rows:", len(surface_map))
    print("[+] overlay map rows:", len(overlay_map))
    print("[+] state function rows:", len(state_map))


if __name__ == "__main__":
    main()
