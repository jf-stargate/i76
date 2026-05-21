#!/usr/bin/env python3
"""
i76_untextured_material_probe_v1.py

Probe an Interstate '76 vehicle OBJ export for faces/materials that have no
texture map. This helps distinguish intentional flat COLOR_* materials from
resolver misses where a non-color GEO slot did not get a map_Kd texture.

Usage:
  python3 scripts/i76_untextured_material_probe_v1.py \
    --export-root scratch_data/i76_vehicle_geo_obj_v17_piranha_whitekd \
    --vehicle vppirna \
    --out scratch_data/i76_untextured_probe_piranha

Or for an all-damage wrapper output:
  python3 scripts/i76_untextured_material_probe_v1.py \
    --export-root scratch_data/i76_vehicle_geo_obj_v19_all_damage_v17 \
    --vehicle vppirna \
    --out scratch_data/i76_untextured_probe_piranha
"""

from __future__ import annotations

import argparse
import csv
import json
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Tuple


def read_tsv(path: Path) -> Iterable[dict]:
    with path.open("r", encoding="utf-8", errors="replace", newline="") as f:
        yield from csv.DictReader(f, delimiter="\t")


def write_csv(path: Path, rows: List[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        path.write_text("", encoding="utf-8")
        return
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0].keys()))
        w.writeheader()
        w.writerows(rows)


def find_report_files(root: Path) -> Tuple[List[Path], List[Path]]:
    fmr = []
    mats = []
    if (root / "face_material_resolution.tsv").exists():
        fmr.append(root / "face_material_resolution.tsv")
    if (root / "materials.tsv").exists():
        mats.append(root / "materials.tsv")

    for p in sorted(root.glob("damage_*/face_material_resolution.tsv")):
        fmr.append(p)
    for p in sorted(root.glob("damage_*/materials.tsv")):
        mats.append(p)
    return fmr, mats


def state_from_path(root: Path, path: Path) -> str:
    try:
        rel = path.relative_to(root)
        if rel.parts and rel.parts[0].startswith("damage_"):
            return rel.parts[0].replace("damage_", "")
    except Exception:
        pass
    return "single"


def material_has_map(material_rows: List[dict]) -> Dict[Tuple[str, str, str], bool]:
    out = {}
    for row in material_rows:
        state = row.get("_state", "single")
        vehicle = row.get("vehicle", "")
        material = row.get("material", "")
        out[(state, vehicle, material)] = bool(row.get("map_kd", ""))
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--export-root", required=True, type=Path)
    ap.add_argument("--vehicle", default="", help="Case-insensitive vehicle substring, e.g. vppirna")
    ap.add_argument("--out", required=True, type=Path)
    args = ap.parse_args()

    args.out.mkdir(parents=True, exist_ok=True)

    fmr_files, mat_files = find_report_files(args.export_root)
    material_rows = []
    for mp in mat_files:
        st = state_from_path(args.export_root, mp)
        for row in read_tsv(mp):
            row["_state"] = st
            material_rows.append(row)

    has_map = material_has_map(material_rows)
    vehicle_filter = args.vehicle.lower().strip()

    face_rows = []
    for fp in fmr_files:
        st = state_from_path(args.export_root, fp)
        for row in read_tsv(fp):
            row["_state"] = st
            if vehicle_filter and vehicle_filter not in row.get("vehicle", "").lower():
                continue
            face_rows.append(row)

    untex = []
    suspicious = []
    grouped = Counter()
    grouped_parts = defaultdict(set)
    grouped_geos = defaultdict(set)
    grouped_examples = {}

    for row in face_rows:
        key = (row["_state"], row.get("vehicle", ""), row.get("material", ""))
        mapped = has_map.get(key, False)
        raw = row.get("raw_slot", "")
        kind = row.get("resolved_kind", "")
        resolved = row.get("resolved_name", "")
        if mapped:
            continue
        out_row = dict(row)
        out_row["has_map_kd"] = "0"
        untex.append(out_row)

        gkey = (row["_state"], row.get("vehicle", ""), raw, row.get("normalized_slot", ""), kind, resolved, row.get("material", ""))
        grouped[gkey] += 1
        grouped_parts[gkey].add(row.get("part", ""))
        grouped_geos[gkey].add(row.get("geo", ""))
        grouped_examples.setdefault(gkey, row)

        # Suspicious: not a literal COLOR slot and not blank, but has no texture map.
        raw_u = (raw or "").upper()
        if raw and not raw_u.startswith("COLOR_") and kind not in {"unresolved"}:
            suspicious.append(out_row)
        elif raw and not raw_u.startswith("COLOR_") and kind == "unresolved":
            suspicious.append(out_row)

    grouped_rows = []
    for gkey, count in grouped.most_common():
        st, veh, raw, norm, kind, resolved, material = gkey
        grouped_rows.append({
            "state": st,
            "vehicle": veh,
            "raw_slot": raw,
            "normalized_slot": norm,
            "resolved_kind": kind,
            "resolved_name": resolved,
            "material": material,
            "face_count": count,
            "parts": ";".join(sorted(p for p in grouped_parts[gkey] if p)[:40]),
            "geos": ";".join(sorted(g for g in grouped_geos[gkey] if g)[:40]),
        })

    suspicious_grouped = [r for r in grouped_rows if r["raw_slot"] and not r["raw_slot"].upper().startswith("COLOR_")]

    write_csv(args.out / "untextured_faces.csv", untex)
    write_csv(args.out / "untextured_grouped.csv", grouped_rows)
    write_csv(args.out / "suspicious_untextured_grouped.csv", suspicious_grouped)

    lines = []
    lines.append("# I76 untextured material probe")
    lines.append("")
    lines.append(f"Export root: `{args.export_root}`")
    lines.append(f"Vehicle filter: `{args.vehicle}`")
    lines.append(f"Face rows inspected: {len(face_rows)}")
    lines.append(f"Untextured face rows: {len(untex)}")
    lines.append(f"Suspicious non-COLOR untextured groups: {len(suspicious_grouped)}")
    lines.append("")
    lines.append("## Top untextured groups")
    lines.append("")
    lines.append("| state | vehicle | raw slot | kind | resolved | faces | parts | geos |")
    lines.append("|---|---|---|---|---|---:|---|---|")
    for r in grouped_rows[:80]:
        lines.append(f"| {r['state']} | {r['vehicle']} | {r['raw_slot']} | {r['resolved_kind']} | {r['resolved_name']} | {r['face_count']} | {r['parts']} | {r['geos']} |")
    lines.append("")
    lines.append("## Suspicious non-COLOR untextured groups")
    lines.append("")
    lines.append("| state | vehicle | raw slot | kind | resolved | faces | parts | geos |")
    lines.append("|---|---|---|---|---|---:|---|---|")
    for r in suspicious_grouped[:80]:
        lines.append(f"| {r['state']} | {r['vehicle']} | {r['raw_slot']} | {r['resolved_kind']} | {r['resolved_name']} | {r['face_count']} | {r['parts']} | {r['geos']} |")
    (args.out / "README.md").write_text("\n".join(lines) + "\n", encoding="utf-8")

    summary = {
        "export_root": str(args.export_root),
        "vehicle_filter": args.vehicle,
        "face_rows_inspected": len(face_rows),
        "untextured_face_rows": len(untex),
        "untextured_groups": len(grouped_rows),
        "suspicious_non_color_untextured_groups": len(suspicious_grouped),
        "top_untextured_groups": grouped_rows[:20],
        "top_suspicious_groups": suspicious_grouped[:20],
    }
    (args.out / "summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
