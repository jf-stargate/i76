#!/usr/bin/env python3
"""
Analyze cgpt_i76shell_export_semantic_gap_evidence.java output and build
ranked semantic rename candidates for i76shell.dll.

Inputs:
  python cgpt_i76shell_analyze_semantic_gap_evidence.py <semantic_gap_export_dir> [--resource-map-v2 database_mw2_resource_map_v2.json]

Outputs inside <semantic_gap_export_dir>/semantic_gap_analysis_v1:
  rename_candidates.tsv
  rename_candidates.md
  naming_coverage_summary.txt
  high_confidence_apply.tsv
"""
from __future__ import annotations

import argparse
import csv
import json
import re
from collections import defaultdict, Counter
from pathlib import Path
from typing import Dict, List, Tuple, Any

KNOWN_NAMES: Dict[str, str] = {
    "10007fd0": "open_mpack_database",
    "10008240": "mpack_database_get_item",
    "10008320": "mpack_database_get_item_alloc_or_alias",
    "10015530": "construct_shell_glyph_sheet",
    "10015580": "measure_string_width_from_glyph_sheet",
    "100155d0": "get_wrapped_glyph_width",
    "100157a0": "draw_string_from_glyph_sheet_object",
    "100157d0": "draw_glyph_from_glyph_sheet_object",
    "10015800": "draw_edit_buffer_glyph_or_control",
    "100196b0": "preload_randomized_shell_resources_0x21_0x23",
    "1001da10": "ShellWindowProc",
    "1001e260": "ShellMain",
    "10023b60": "preload_final_mission_special_menu_record_0x40",
    "10031a30": "draw_ui_image_subrect_with_optional_restore",
    "10031b20": "draw_vehicle_config_component_ui_overlays",
    "10037a50": "construct_shell_surface_context",
    "10037d60": "mark_shell_surface_dirty_rect",
    "10037e60": "apply_shell_surface_palette_to_backend",
    "10037e80": "flush_or_repaint_shell_surface_context",
    "100382e0": "shell_surface_repaint_or_flip_with_palette_update",
    "10038530": "copy_shell_surface_palette_out",
    "10038550": "set_shell_surface_palette_from_rgb6",
    "10038630": "load_shell_rle_bitmap_surface_from_buffer",
    "100387d0": "load_or_apply_shell_surface_record_by_id_candidate",
    "10038fd0": "clear_text_rect",
    "10039230": "load_shell_rle_bitmap_surface_from_database_record",
    "10039390": "draw_mw2_image_subresource_to_shell_surface",
    "100395b0": "measure_and_draw_string_from_glyph_sheet",
    "10039750": "draw_single_glyph_to_shell_surfaces",
    "100398b0": "prepare_or_clear_text_draw_context",
    "10039960": "shell_shared_ui_helper",
    "10039a10": "lock_shell_surface_for_draw",
    "1003a8f4": "blit_mw2_image_subresource_rle_clipped",
    "1003ae6b": "set_shell_image_palette_remap_table",
    "1003b3e6": "blit_mw2_image_subresource_transformed_or_masked",
    "1003c38d": "remap_mw2_image_record_rle_stream_in_place",
    "1003c888": "blit_or_fill_rect_clipped",
    "1003e419": "get_shell_glyph_sheet_height",
    "1003e42c": "get_glyph_width",
    "1003e44c": "blit_glyph_to_surface",
    "1003e5d7": "draw_ascii_string_from_glyph_sheet",
    "1003e60e": "write_decoded_image_scanline_to_shell_surface",
    "1003e984": "decode_simple_rle_bitmap_to_shell_surface",
    "1003ea06": "extract_shell_bitmap_palette_from_buffer",
    "1003ea31": "get_shell_bitmap_dimensions_packed",
    "1003eeed": "get_mw2_image_subresource_origin",
    "1003f5d0": "get_localized_glyph_width_and_set_stride",
    "1003f620": "blit_localized_glyph_to_surface",
    "1003f7e5": "draw_localized_string_to_surface",
}

STRING_PATTERNS: List[Tuple[re.Pattern, str, str, int]] = [
    (re.compile(r"input[_ -]?map|throttle|joystick|keyboard|mouse|controller", re.I), "input_mapping", "input/device mapping strings", 35),
    (re.compile(r"vehicle|chassis|armor|weapon|turret|hardpoint|melee|repair", re.I), "vehicle_config", "vehicle configuration strings", 30),
    (re.compile(r"mission|campaign|trip|scenario|t%02d\.msn|\.msn", re.I), "mission_selection", "mission/campaign strings", 30),
    (re.compile(r"multi.?player|modem|serial|tcp|ipx|network|server|client|host|join", re.I), "multiplayer_setup", "network/multiplayer strings", 35),
    (re.compile(r"sound|music|volume|audio|midi|cd", re.I), "audio_options", "audio settings strings", 25),
    (re.compile(r"video|display|resolution|graphics|renderer|raster|directdraw", re.I), "video_options", "video/display strings", 25),
    (re.compile(r"save|load|profile|pilot|player", re.I), "profile_or_save", "profile/save/player strings", 20),
    (re.compile(r"credits|quit|exit|cancel|ok|yes|no", re.I), "dialog_or_menu", "dialog/menu strings", 15),
]

CALL_PATTERNS: List[Tuple[str, str, str, int]] = [
    ("mpack_database_get_item", "database_record_loader", "direct database record access", 30),
    ("mpack_database_get_item_alloc_or_alias", "database_record_loader", "database record load/decompress path", 30),
    ("load_shell_rle_bitmap_surface_from_database_record", "shell_screen_surface_loader", "shell surface load", 35),
    ("load_or_apply_shell_surface_record_by_id_candidate", "shell_screen_surface_loader", "shell surface apply/load", 35),
    ("draw_ui_image_subrect_with_optional_restore", "ui_overlay_draw_client", "1.10 UI overlay draw", 30),
    ("draw_mw2_image_subresource_to_shell_surface", "ui_overlay_draw_client", "1.10 subresource draw", 30),
    ("draw_vehicle_config_component_ui_overlays", "vehicle_config_screen", "vehicle config overlay draw", 45),
    ("construct_shell_glyph_sheet", "glyph_sheet_user", "glyph sheet construction", 30),
    ("draw_ascii_string_from_glyph_sheet", "text_render_client", "ASCII glyph rendering", 20),
    ("draw_localized_string_to_surface", "localized_text_render_client", "localized glyph rendering", 25),
    ("ShellMain", "shell_entry_or_dispatch", "ShellMain participation", 10),
]


def read_tsv(path: Path) -> List[Dict[str, str]]:
    if not path.exists():
        return []
    with path.open("r", encoding="utf-8", errors="replace", newline="") as f:
        return list(csv.DictReader(f, delimiter="\t"))


def norm_addr(s: str) -> str:
    s = (s or "").strip().lower()
    if s.startswith("0x"):
        s = s[2:]
    return s.zfill(8) if s else ""


def is_generic(name: str) -> bool:
    return name.startswith("FUN_") or name.startswith("Unwind_")


def safe_name(s: str) -> str:
    s = re.sub(r"[^a-zA-Z0-9_]+", "_", s.strip())
    s = re.sub(r"_+", "_", s).strip("_")
    if not s:
        s = "unnamed"
    if s[0].isdigit():
        s = "fn_" + s
    return s[:80]


def load_resource_map(path: Path | None) -> Dict[str, Any]:
    if not path:
        return {}
    try:
        return json.loads(path.read_text(encoding="utf-8", errors="replace"))
    except Exception:
        return {}


def build_resource_evidence(resource_map: Dict[str, Any]) -> Dict[str, List[str]]:
    out: Dict[str, List[str]] = defaultdict(list)
    for rec in resource_map.get("records", []) if isinstance(resource_map, dict) else []:
        rid = rec.get("record_id")
        cls = rec.get("class", "")
        sub = rec.get("subclass", "")
        desc = f"record {rid} {cls}/{sub}".strip()
        for k in ("direct_loader_functions", "direct_surface_user_functions", "direct_draw_functions"):
            for item in rec.get(k, []) or []:
                m = re.match(r"([0-9a-fA-F]{8})\s+(.*)", item)
                if m:
                    out[norm_addr(m.group(1))].append(f"{k}: {desc}")
    return out


def propose_from_bucket(addr: str, current: str, buckets: Counter, evidence: List[str]) -> Tuple[str, str, int, str]:
    # Purposefully conservative. Specific known addresses beat heuristic buckets.
    if addr in KNOWN_NAMES:
        return KNOWN_NAMES[addr], "known_baseline", 100, "already established durable name"

    if buckets["vehicle_config_screen"]:
        return f"handle_vehicle_config_screen_{addr}", "high", min(95, 55 + buckets["vehicle_config_screen"] * 10), "vehicle config draw path"
    if buckets["shell_screen_surface_loader"] and buckets["mission_selection"]:
        return f"handle_mission_shell_screen_{addr}", "medium", 75, "surface loader plus mission strings"
    if buckets["shell_screen_surface_loader"] and buckets["input_mapping"]:
        return f"handle_input_mapping_screen_{addr}", "medium", 75, "surface loader plus input mapping strings"
    if buckets["database_record_loader"] and buckets["multiplayer_setup"]:
        return f"load_multiplayer_shell_resources_{addr}", "medium", 70, "database loads plus multiplayer strings"
    if buckets["ui_overlay_draw_client"] and buckets["vehicle_config"]:
        return f"draw_vehicle_config_ui_{addr}", "medium", 70, "overlay drawing plus vehicle strings"
    if buckets["ui_overlay_draw_client"] and buckets["mission_selection"]:
        return f"draw_mission_selection_ui_{addr}", "medium", 68, "overlay drawing plus mission strings"
    if buckets["input_mapping"]:
        return f"input_mapping_ui_handler_{addr}", "medium", 62, "input mapping strings"
    if buckets["multiplayer_setup"]:
        return f"multiplayer_setup_ui_handler_{addr}", "medium", 62, "multiplayer/network strings"
    if buckets["video_options"]:
        return f"video_options_ui_handler_{addr}", "medium", 58, "video/display strings"
    if buckets["audio_options"]:
        return f"audio_options_ui_handler_{addr}", "medium", 58, "audio settings strings"
    if buckets["profile_or_save"]:
        return f"profile_or_save_ui_handler_{addr}", "low", 50, "profile/save strings"
    if buckets["text_render_client"] or buckets["localized_text_render_client"]:
        return f"text_render_client_{addr}", "low", 48, "text rendering calls"
    if buckets["database_record_loader"]:
        return f"load_shell_database_resources_{addr}", "low", 45, "database record access"
    if buckets["shell_screen_surface_loader"]:
        return f"load_or_show_shell_surface_screen_{addr}", "low", 45, "shell surface load"
    if buckets["ui_overlay_draw_client"]:
        return f"draw_shell_ui_overlays_{addr}", "low", 44, "1.10 overlay draw client"
    return "", "none", 0, "insufficient evidence"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("export_dir", type=Path)
    ap.add_argument("--resource-map-v2", type=Path, default=None)
    args = ap.parse_args()

    export_dir = args.export_dir
    out_dir = export_dir / "semantic_gap_analysis_v1"
    out_dir.mkdir(parents=True, exist_ok=True)

    functions = read_tsv(export_dir / "functions.tsv")
    calls = read_tsv(export_dir / "calls.tsv")
    strings = read_tsv(export_dir / "strings_by_function.tsv")
    resource_evidence = build_resource_evidence(load_resource_map(args.resource_map_v2))

    by_addr: Dict[str, Dict[str, str]] = {norm_addr(r.get("entry")): r for r in functions}
    calls_by_func: Dict[str, List[Dict[str, str]]] = defaultdict(list)
    strings_by_func: Dict[str, List[str]] = defaultdict(list)

    for r in calls:
        calls_by_func[norm_addr(r.get("caller_entry"))].append(r)
    for r in strings:
        a = norm_addr(r.get("function_entry"))
        s = r.get("string_value", "")
        if s:
            strings_by_func[a].append(s)

    candidates: List[Dict[str, Any]] = []
    total = len(functions)
    currently_named = 0
    generic = 0

    for addr, f in sorted(by_addr.items()):
        if not addr:
            continue
        current = f.get("name", "")
        if is_generic(current):
            generic += 1
        else:
            currently_named += 1

        buckets: Counter = Counter()
        evidence: List[str] = []

        for c in calls_by_func.get(addr, []):
            callee = c.get("callee_name", "")
            for needle, bucket, why, score in CALL_PATTERNS:
                if needle and needle in callee:
                    buckets[bucket] += 1
                    evidence.append(f"calls {callee}: {why}")

        joined_strings = "\n".join(strings_by_func.get(addr, []))
        for rx, bucket, why, score in STRING_PATTERNS:
            hits = rx.findall(joined_strings)
            if hits:
                buckets[bucket] += len(hits)
                sample = "; ".join(strings_by_func.get(addr, [])[:6])
                evidence.append(f"strings match {why}: {sample[:240]}")

        for ev in resource_evidence.get(addr, []):
            evidence.append(ev)
            if "direct_surface_user_functions" in ev:
                buckets["shell_screen_surface_loader"] += 2
            if "direct_draw_functions" in ev:
                buckets["ui_overlay_draw_client"] += 2
            if "direct_loader_functions" in ev:
                buckets["database_record_loader"] += 2

        proposed, conf, score, rationale = propose_from_bucket(addr, current, buckets, evidence)
        if not proposed:
            continue
        proposed = safe_name(proposed)
        apply = "yes" if (conf in ("known_baseline", "high") and (is_generic(current) or current != proposed)) else "review"
        if conf == "known_baseline" and current == proposed:
            apply = "already_named"

        candidates.append({
            "address": addr,
            "current_name": current,
            "proposed_name": proposed,
            "confidence": conf,
            "score": score,
            "apply": apply,
            "rationale": rationale,
            "evidence": " | ".join(dict.fromkeys(evidence))[:3000],
            "buckets": ",".join(f"{k}:{v}" for k, v in buckets.most_common()),
        })

    candidates.sort(key=lambda r: (-int(r["score"]), r["address"]))

    fieldnames = ["address", "current_name", "proposed_name", "confidence", "score", "apply", "rationale", "buckets", "evidence"]
    with (out_dir / "rename_candidates.tsv").open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t")
        w.writeheader()
        w.writerows(candidates)

    with (out_dir / "high_confidence_apply.tsv").open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t")
        w.writeheader()
        for r in candidates:
            if r["apply"] == "yes":
                w.writerow(r)

    with (out_dir / "rename_candidates.md").open("w", encoding="utf-8") as f:
        f.write("# i76shell semantic rename candidates\n\n")
        f.write("Generated from semantic-gap evidence export. Apply only high-confidence rows automatically; review medium/low rows manually.\n\n")
        for r in candidates[:250]:
            f.write(f"## {r['address']} `{r['current_name']}` → `{r['proposed_name']}`\n\n")
            f.write(f"Confidence: **{r['confidence']}**; score: {r['score']}; apply: `{r['apply']}`.\n\n")
            f.write(f"Rationale: {r['rationale']}.\n\n")
            if r["evidence"]:
                f.write(f"Evidence: {r['evidence']}\n\n")

    with (out_dir / "naming_coverage_summary.txt").open("w", encoding="utf-8") as f:
        f.write("Interstate '76 i76shell semantic naming coverage analysis\n")
        f.write("=======================================================\n")
        f.write(f"input_dir: {export_dir}\n")
        f.write(f"total_functions: {total}\n")
        f.write(f"currently_semantic_or_system_named: {currently_named}\n")
        f.write(f"currently_generic_FUN_or_Unwind: {generic}\n")
        if total:
            f.write(f"current_named_percent: {currently_named * 100.0 / total:.2f}%\n")
        auto = sum(1 for r in candidates if r["apply"] == "yes")
        review = sum(1 for r in candidates if r["apply"] == "review")
        f.write(f"rename_candidates_total: {len(candidates)}\n")
        f.write(f"high_confidence_apply_rows: {auto}\n")
        f.write(f"review_rows: {review}\n")
        projected = currently_named + auto
        if total:
            f.write(f"projected_named_after_high_confidence: {projected}\n")
            f.write(f"projected_named_percent_after_high_confidence: {projected * 100.0 / total:.2f}%\n")
        f.write("\nConfidence policy:\n")
        f.write("  known_baseline/high: safe to apply if current name is generic.\n")
        f.write("  medium: useful working name, but inspect function/decompile first.\n")
        f.write("  low: category label only; do not apply without manual review.\n")

    print(f"Wrote analysis to {out_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
