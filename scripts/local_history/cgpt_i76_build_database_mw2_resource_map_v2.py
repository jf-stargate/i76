#!/usr/bin/env python3
"""
Build a stricter Interstate '76 DATABASE.MW2 shell resource map from Ghidra trace outputs.

This v2 builder is intentionally less noisy than v1:
  - direct_loader_functions: only direct mpack/database-get evidence
  - direct_surface_user_functions: only direct surface-loader callsite evidence
  - direct_draw_functions: only direct 1.10 draw call evidence
  - context_functions: broader state-summary/callgraph context, kept separate
  - evidence: high-confidence direct evidence and manually confirmed observations
  - context_evidence: broad, lower-confidence context evidence

Primary input:
  cgpt_i76shell_precise_screen_callsite_map_YYYYMMDD_HHMMSS/

Expected input files when available:
  surface_load_calls.tsv
  database_record_get_calls.tsv
  overlay_draw_calls.tsv
  screen_state_resource_summary.tsv
  special_record64_context.tsv

Outputs:
  database_mw2_resource_map_v2.json
  database_mw2_resource_map_v2.tsv
  shell_screen_surface_map_v2.tsv
  shell_overlay_usage_map_v2.tsv
  shell_state_context_map_v2.tsv
  summary_v2.txt
"""

from __future__ import annotations

import argparse
import csv
import json
import re
from collections import defaultdict
from pathlib import Path
from typing import Any, Dict, List, Optional, Set


# -----------------------------
# Generic helpers
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
    if not m:
        return None
    try:
        return int(m.group(1), 0)
    except Exception:
        return None


def parse_int_list(s: Any) -> List[int]:
    if s is None:
        return []
    text = str(s).strip()
    if not text:
        return []

    vals: List[int] = []
    for part in re.split(r"[,\s;]+", text):
        part = part.strip()
        if not part:
            continue
        try:
            vals.append(int(part, 0))
        except Exception:
            continue

    seen = set()
    out = []
    for v in vals:
        if v not in seen:
            out.append(v)
            seen.add(v)
    return out


def add_unique(dst: List[Any], value: Any) -> None:
    if value is None or value == "":
        return
    if value not in dst:
        dst.append(value)


def fn_label(entry: str, name: str) -> str:
    entry = (entry or "").strip()
    name = (name or "").strip()
    if entry and name:
        return f"{entry} {name}"
    return entry or name


# -----------------------------
# Static classification
# -----------------------------

def new_record(rid: int) -> Dict[str, Any]:
    return {
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
        "direct_loader_functions": [],
        "direct_surface_user_functions": [],
        "direct_draw_functions": [],
        "context_functions": [],
        "evidence": [],
        "context_evidence": [],
        "notes": [],
        "confidence": "unknown",
    }


def initial_record_map() -> Dict[int, Dict[str, Any]]:
    records = {rid: new_record(rid) for rid in range(1, 84)}

    # Records 1-32: confirmed shell surfaces.
    for rid in range(1, 33):
        r = records[rid]
        r["class"] = "shell_surface"
        r["subclass"] = "compressed_rle_screen_surface"
        r["status"] = "decoded"
        r["description"] = "Compressed shell screen/background surface with trailing 768-byte RGB8 palette."
        r["palette_source_record"] = rid
        r["format"] = "mpack-compressed shell RLE surface"
        r["encoding"] = "mpack LZSS -> shell simple RLE at +0x80; trailing RGB8 palette"
        r["confidence"] = "high"
        r["evidence"].append("Decoded by shell RLE surface decoder and confirmed by broad DATABASE.MW2 surface scan.")

    # Palette groups from validated broad scan.
    group_a = [1,2,3,4,6,7,8,9,10,11,12,13,16,18,19,20,21,22,23,24,25,26,28,29,30,31,32]
    for rid in group_a:
        records[rid]["palette_group"] = "A_common_shell_ui_palette_record1"
    records[5]["palette_group"] = "B_record5"
    records[14]["palette_group"] = "C_record14"
    records[15]["palette_group"] = "D_records15_17"
    records[17]["palette_group"] = "D_records15_17"
    records[27]["palette_group"] = "E_record27_final_mission_special"

    # Records 33-35.
    for rid in range(33, 36):
        r = records[rid]
        r["class"] = "shell_resource"
        r["subclass"] = "randomized_shell_resource"
        r["status"] = "format_unresolved"
        r["description"] = "Random-selection shell resource loaded by 100196b0; exact format unresolved."
        r["confidence"] = "medium"
        r["evidence"].append("100196b0 loads records 33, 34, 35 and seeds three rand()%5 globals.")

    # Records 36-63.
    for rid in range(36, 64):
        r = records[rid]
        r["class"] = "ui_overlay"
        r["subclass"] = "mw2_1_10_multi_image"
        r["status"] = "decoded_indexed"
        r["description"] = "Ordinary shell/menu 1.10 overlay/sprite/panel resource."
        r["palette_source_record"] = 1
        r["palette_group"] = "A_common_shell_ui_palette_record1"
        r["format"] = "1.10 multi-subresource image"
        r["encoding"] = "custom byte-oriented RLE, direct indexed blit"
        r["confidence"] = "high"
        r["evidence"].append("Decoded by 1.10 image decoder; ordinary overlays visually match common shell palette group A unless otherwise noted.")

    # Record 64.
    r = records[64]
    r["class"] = "ui_overlay"
    r["subclass"] = "mw2_1_10_final_mission_special_menu"
    r["status"] = "decoded_indexed_palette_paired"
    r["description"] = "Special menu selection screen resource shown before the final mission."
    r["palette_source_record"] = 27
    r["palette_group"] = "E_record27_final_mission_special"
    r["format"] = "1.10 multi-subresource image"
    r["encoding"] = "custom byte-oriented RLE, direct indexed blit"
    r["confidence"] = "high"
    r["evidence"].append("10023b60 loads DATABASE.MW2 record 0x40 / 64 and applies surface record 0x1b / 27.")
    r["evidence"].append("User visually confirmed record 64 colors correctly with palette from surface record 27.")
    r["notes"].append("Special screen appears only before the final mission; not part of ordinary shell/menu overlay palette context.")

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
        r = records[rid]
        r["class"] = "glyph_sheet"
        r["subclass"] = desc
        r["status"] = "decoded_structural"
        r["description"] = desc
        r["format"] = "mw2_glyph_sheet"
        r["encoding"] = enc
        r["confidence"] = "high"
        r["evidence"].append("Validated by glyph analyzer and manual inspection.")

    # Audio.
    for rid in range(72, 83):
        r = records[rid]
        r["class"] = "audio"
        r["subclass"] = "wave_or_piff_wave"
        r["status"] = "classified"
        r["description"] = "WAVE or PIFF/WAVE-like audio record."
        r["format"] = "RIFF/WAVE" if rid <= 80 else "PIFF/WAVE-like"
        r["confidence"] = "medium"
        r["evidence"].append("Classified by DATABASE.MW2 record analyzer.")

    # Credits.
    r = records[83]
    r["class"] = "text"
    r["subclass"] = "credits_text"
    r["status"] = "decoded_text"
    r["description"] = "Credits text record."
    r["format"] = "text"
    r["confidence"] = "high"
    r["evidence"].append("Classified by DATABASE.MW2 record analyzer as credits text.")

    return records


# -----------------------------
# Ingestion
# -----------------------------

def ingest_surface_load_calls(records: Dict[int, Dict[str, Any]], rows: List[Dict[str, str]]) -> List[Dict[str, Any]]:
    out: List[Dict[str, Any]] = []

    for row in rows:
        rec = parse_int_maybe(row.get("likely_surface_record_id", ""))
        if rec is None or rec not in records:
            continue

        caller_entry = row.get("caller_entry", "")
        caller_name = row.get("caller_name", "")
        target = row.get("target", "")
        callsite = row.get("callsite", "")
        group = row.get("palette_group_observed", "") or records[rec].get("palette_group", "")

        label = fn_label(caller_entry, caller_name)
        add_unique(records[rec]["direct_surface_user_functions"], label)
        add_unique(records[rec]["evidence"], f"Direct surface load: {target} at {callsite} in {label}.")

        if rec == 27:
            add_unique(records[rec]["notes"], "Directly paired with final-mission special overlay record 64.")

        out.append({
            "surface_record_id": rec,
            "surface_record_hex": f"0x{rec:02x}",
            "state_function_entry": caller_entry,
            "state_function": caller_name,
            "callsite": callsite,
            "target": target,
            "palette_group": group,
            "evidence_tier": "direct_surface_load",
        })

    return out


def ingest_database_get_calls(records: Dict[int, Dict[str, Any]], rows: List[Dict[str, str]]) -> None:
    for row in rows:
        rec = parse_int_maybe(row.get("likely_record_id", ""))
        if rec is None or rec not in records:
            continue

        caller_entry = row.get("caller_entry", "")
        caller_name = row.get("caller_name", "")
        target = row.get("target", "")
        callsite = row.get("callsite", "")
        label = fn_label(caller_entry, caller_name)

        add_unique(records[rec]["direct_loader_functions"], label)
        add_unique(records[rec]["evidence"], f"Direct DATABASE.MW2 get: {target} loads record at {callsite} in {label}.")


def infer_record_from_overlay_source(source: str) -> Optional[int]:
    if not source:
        return None
    # Supports strings such as:
    #   record64_0x40_final_mission_special
    #   record39_1.10
    m = re.search(r"record(\d+)", source)
    if m:
        return int(m.group(1))
    return None


def ingest_overlay_draw_calls(records: Dict[int, Dict[str, Any]], rows: List[Dict[str, str]]) -> List[Dict[str, Any]]:
    out: List[Dict[str, Any]] = []

    for row in rows:
        caller_entry = row.get("caller_entry", "")
        caller_name = row.get("caller_name", "")
        callsite = row.get("callsite", "")
        target = row.get("target", "")
        source = row.get("likely_110_record_or_global", "")
        subarg = row.get("likely_subresource_or_small_arg", "")
        globals_nearby = row.get("globals_nearby", "")

        rec = infer_record_from_overlay_source(source)
        label = fn_label(caller_entry, caller_name)

        if rec is not None and rec in records:
            add_unique(records[rec]["direct_draw_functions"], label)
            add_unique(records[rec]["evidence"], f"Direct 1.10 draw: {target} at {callsite} in {label}.")
            if rec == 64:
                add_unique(records[rec]["notes"], "Directly drawn in vehicle/config overlay renderer path for final mission special screen.")

        out.append({
            "source_record_id": rec if rec is not None else "",
            "source_record_hex": f"0x{rec:02x}" if rec is not None else "",
            "source_or_global": source,
            "state_function_entry": caller_entry,
            "state_function": caller_name,
            "callsite": callsite,
            "draw_target": target,
            "subresource_or_small_args": subarg,
            "globals_nearby": globals_nearby,
            "evidence_tier": "direct_draw_call" if rec is not None else "draw_call_global_or_unresolved",
        })

    return out


def ingest_state_context(records: Dict[int, Dict[str, Any]], rows: List[Dict[str, str]]) -> List[Dict[str, Any]]:
    out: List[Dict[str, Any]] = []

    for row in rows:
        entry = row.get("function_entry", "")
        name = row.get("function_name", "")
        label = fn_label(entry, name)
        surface_records = parse_int_list(row.get("surface_records_seen", ""))
        db_records = parse_int_list(row.get("database_records_seen", ""))
        overlay_globals = row.get("overlay_globals_seen", "")
        notes = row.get("notes", "")

        # Keep only as context, not direct user/loader evidence.
        for rec in set(surface_records + db_records):
            if rec in records:
                add_unique(records[rec]["context_functions"], label)
                add_unique(records[rec]["context_evidence"], f"Broad context mention in {label}; not necessarily direct record use.")

        out.append({
            "function_entry": entry,
            "function_name": name,
            "surface_records_seen": surface_records,
            "database_records_seen": db_records,
            "overlay_globals_seen": overlay_globals,
            "notes": notes,
            "evidence_tier": "broad_context_only",
        })

    return out


# -----------------------------
# Output
# -----------------------------

def make_record_rows(records: Dict[int, Dict[str, Any]]) -> List[Dict[str, Any]]:
    rows = []
    for rid in sorted(records):
        r = records[rid]
        rows.append({
            "record_id": rid,
            "hex_id": r["hex_id"],
            "class": r["class"],
            "subclass": r["subclass"],
            "status": r["status"],
            "confidence": r["confidence"],
            "description": r["description"],
            "palette_source_record": r["palette_source_record"] if r["palette_source_record"] is not None else "",
            "palette_group": r["palette_group"],
            "format": r["format"],
            "encoding": r["encoding"],
            "direct_loader_functions": r["direct_loader_functions"],
            "direct_surface_user_functions": r["direct_surface_user_functions"],
            "direct_draw_functions": r["direct_draw_functions"],
            "context_functions": r["context_functions"],
            "notes": r["notes"],
            "evidence": r["evidence"],
            "context_evidence": r["context_evidence"],
        })
    return rows


def write_summary(path: Path, records: Dict[int, Dict[str, Any]], trace_dir: Path, out_dir: Path) -> None:
    class_counts = defaultdict(int)
    status_counts = defaultdict(int)
    for r in records.values():
        class_counts[r["class"]] += 1
        status_counts[r["status"]] += 1

    lines = []
    lines.append("Interstate '76 DATABASE.MW2 shell resource map v2")
    lines.append("=" * 59)
    lines.append("")
    lines.append(f"Input trace directory: {trace_dir}")
    lines.append(f"Output directory: {out_dir}")
    lines.append("")
    lines.append("Record class counts:")
    for k in sorted(class_counts):
        lines.append(f"  {k}: {class_counts[k]}")
    lines.append("")
    lines.append("Status counts:")
    for k in sorted(status_counts):
        lines.append(f"  {k}: {status_counts[k]}")
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
    lines.append("v2 evidence-tiering behavior:")
    lines.append("  direct_loader_functions: direct mpack/database-get call evidence only.")
    lines.append("  direct_surface_user_functions: direct surface-loader callsite evidence only.")
    lines.append("  direct_draw_functions: direct 1.10 draw call evidence only.")
    lines.append("  context_functions: broad state-summary/callgraph context only; lower confidence.")
    lines.append("")
    path.write_text("\n".join(lines), encoding="utf-8")


def main() -> None:
    ap = argparse.ArgumentParser(description="Build strict v2 I76 DATABASE.MW2 resource map from shell Ghidra trace outputs")
    ap.add_argument("trace_dir", type=Path, help="Extracted precise Ghidra trace output folder")
    ap.add_argument("output_dir", type=Path, help="Destination folder for normalized v2 resource map")
    args = ap.parse_args()

    trace_dir = args.trace_dir
    out_dir = args.output_dir
    out_dir.mkdir(parents=True, exist_ok=True)

    records = initial_record_map()

    surface_rows_in = read_tsv(trace_dir / "surface_load_calls.tsv")
    db_rows_in = read_tsv(trace_dir / "database_record_get_calls.tsv")
    overlay_rows_in = read_tsv(trace_dir / "overlay_draw_calls.tsv")
    context_rows_in = read_tsv(trace_dir / "screen_state_resource_summary.tsv")

    surface_map = ingest_surface_load_calls(records, surface_rows_in)
    ingest_database_get_calls(records, db_rows_in)
    overlay_map = ingest_overlay_draw_calls(records, overlay_rows_in)
    context_map = ingest_state_context(records, context_rows_in)

    # Reassert special pairing in both involved records.
    add_unique(records[64]["direct_loader_functions"], "10023b60 preload_final_mission_special_menu_record_0x40")
    add_unique(records[64]["direct_draw_functions"], "10031b20 draw_vehicle_config_component_ui_overlays")
    add_unique(records[64]["evidence"], "Manual semantic observation: final mission pre-launch special menu selection screen.")
    add_unique(records[64]["notes"], "Palette pairing: use shell surface record 27.")
    add_unique(records[27]["direct_surface_user_functions"], "10023b60 preload_final_mission_special_menu_record_0x40")
    add_unique(records[27]["evidence"], "Palette/surface paired with special record 64 via 10023b60.")
    add_unique(records[27]["notes"], "Final-mission special screen palette group.")

    json_obj = {
        "schema": "i76.database_mw2_resource_map.v2",
        "source_trace_dir": str(trace_dir),
        "evidence_model": {
            "direct_loader_functions": "Direct mpack/database-get call evidence only.",
            "direct_surface_user_functions": "Direct shell-surface-loader callsite evidence only.",
            "direct_draw_functions": "Direct 1.10 draw call evidence only.",
            "context_functions": "Broad state-summary/callgraph context only; lower confidence.",
        },
        "records": [records[rid] for rid in sorted(records)],
        "surface_load_map": surface_map,
        "overlay_draw_map": overlay_map,
        "state_context_map": context_map,
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

    (out_dir / "database_mw2_resource_map_v2.json").write_text(json.dumps(json_obj, indent=2), encoding="utf-8")

    write_tsv(
        out_dir / "database_mw2_resource_map_v2.tsv",
        make_record_rows(records),
        [
            "record_id",
            "hex_id",
            "class",
            "subclass",
            "status",
            "confidence",
            "description",
            "palette_source_record",
            "palette_group",
            "format",
            "encoding",
            "direct_loader_functions",
            "direct_surface_user_functions",
            "direct_draw_functions",
            "context_functions",
            "notes",
            "evidence",
            "context_evidence",
        ],
    )

    write_tsv(
        out_dir / "shell_screen_surface_map_v2.tsv",
        surface_map,
        [
            "surface_record_id",
            "surface_record_hex",
            "state_function_entry",
            "state_function",
            "callsite",
            "target",
            "palette_group",
            "evidence_tier",
        ],
    )

    write_tsv(
        out_dir / "shell_overlay_usage_map_v2.tsv",
        overlay_map,
        [
            "source_record_id",
            "source_record_hex",
            "source_or_global",
            "state_function_entry",
            "state_function",
            "callsite",
            "draw_target",
            "subresource_or_small_args",
            "globals_nearby",
            "evidence_tier",
        ],
    )

    write_tsv(
        out_dir / "shell_state_context_map_v2.tsv",
        context_map,
        [
            "function_entry",
            "function_name",
            "surface_records_seen",
            "database_records_seen",
            "overlay_globals_seen",
            "notes",
            "evidence_tier",
        ],
    )

    write_summary(out_dir / "summary_v2.txt", records, trace_dir, out_dir)

    print(f"[+] wrote strict v2 resource map to {out_dir}")
    print(f"[+] records: {len(records)}")
    print(f"[+] direct surface rows: {len(surface_map)}")
    print(f"[+] overlay draw rows: {len(overlay_map)}")
    print(f"[+] context rows: {len(context_map)}")


if __name__ == "__main__":
    main()
