#!/usr/bin/env python3
"""
i76_black_plane_probe_v1.py

Diagnose black planes in Interstate '76 vehicle OBJ exports.

The current suspicion is that many black planes are not collision geometry.
This probe searches exported OBJ/MTL/report data for:
  - parts/geos ending in _SOR, likely shadow/underlay objects
  - COLOR_000000 material faces
  - large flat untextured polygons
  - non-color unresolved black-looking material slots

It writes CSV reports and a markdown summary.

Example:
  python3 scripts/i76_black_plane_probe_v1.py \
    --export-root scratch_data/i76_vehicle_geo_obj_v12_all_damage_v10_palette \
    --out scratch_data/i76_black_plane_probe_v1
"""

from __future__ import annotations

import argparse
import csv
import json
import math
import re
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


def safe_float_triplet(parts: List[str]) -> Tuple[float, float, float]:
    return float(parts[1]), float(parts[2]), float(parts[3])


def polygon_area(points: List[Tuple[float, float, float]]) -> float:
    if len(points) < 3:
        return 0.0
    # Newell vector magnitude / 2.
    nx = ny = nz = 0.0
    n = len(points)
    for i in range(n):
        x1, y1, z1 = points[i]
        x2, y2, z2 = points[(i + 1) % n]
        nx += (y1 - y2) * (z1 + z2)
        ny += (z1 - z2) * (x1 + x2)
        nz += (x1 - x2) * (y1 + y2)
    return 0.5 * math.sqrt(nx * nx + ny * ny + nz * nz)


def parse_obj_faces(obj_path: Path) -> List[dict]:
    verts: List[Tuple[float, float, float]] = []
    rows: List[dict] = []
    obj_name = ""
    cur_mtl = ""

    with obj_path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            s = line.strip()
            if not s:
                continue
            if s.startswith("o "):
                obj_name = s[2:].strip()
            elif s.startswith("usemtl "):
                cur_mtl = s.split(None, 1)[1].strip()
            elif s.startswith("v "):
                parts = s.split()
                if len(parts) >= 4:
                    verts.append(safe_float_triplet(parts))
            elif s.startswith("f "):
                idxs = []
                for tok in s.split()[1:]:
                    vi_s = tok.split("/", 1)[0]
                    try:
                        vi = int(vi_s)
                        if vi < 0:
                            vi = len(verts) + vi + 1
                        idxs.append(vi - 1)
                    except Exception:
                        pass
                pts = [verts[i] for i in idxs if 0 <= i < len(verts)]
                if pts:
                    xs = [p[0] for p in pts]; ys = [p[1] for p in pts]; zs = [p[2] for p in pts]
                    rows.append({
                        "object": obj_name,
                        "material": cur_mtl,
                        "vertex_count": len(pts),
                        "area": polygon_area(pts),
                        "min_x": min(xs), "max_x": max(xs),
                        "min_y": min(ys), "max_y": max(ys),
                        "min_z": min(zs), "max_z": max(zs),
                        "span_x": max(xs)-min(xs),
                        "span_y": max(ys)-min(ys),
                        "span_z": max(zs)-min(zs),
                    })
    return rows


def collect_report_side(export_root: Path) -> Tuple[List[dict], List[dict], List[dict]]:
    black_by_geo = Counter()
    black_by_part = Counter()
    black_by_vehicle = Counter()
    black_by_state = Counter()
    sor_by_geo = Counter()
    sor_by_vehicle = Counter()
    non_color_unresolved = Counter()

    examples = []

    for fmr in sorted(export_root.glob("damage_*/face_material_resolution.tsv")):
        state = fmr.parent.name.replace("damage_", "")
        for row in read_tsv(fmr):
            raw = row.get("raw_slot", "")
            part = row.get("part", "")
            geo = row.get("geo", "")
            vehicle = row.get("vehicle", "")
            kind = row.get("resolved_kind", "")
            is_sor = "_SOR" in part.upper() or "_SOR" in geo.upper()
            if is_sor:
                sor_by_geo[geo] += 1
                sor_by_vehicle[vehicle] += 1
            if raw == "COLOR_000000":
                black_by_geo[geo] += 1
                black_by_part[part] += 1
                black_by_vehicle[vehicle] += 1
                black_by_state[state] += 1
                if len(examples) < 200:
                    examples.append({
                        "state": state, "vehicle": vehicle, "part": part, "geo": geo,
                        "raw_slot": raw, "material": row.get("material", ""),
                        "resolved_kind": kind, "face_index": row.get("face_index", "")
                    })
            elif kind == "unresolved" and raw and not raw.startswith("COLOR_"):
                non_color_unresolved[raw] += 1

    black_rows = [
        {"geo": k, "black_face_count": v, "is_sor": int("_SOR" in k.upper())}
        for k, v in black_by_geo.most_common()
    ]
    sor_rows = [
        {"geo": k, "face_count": v}
        for k, v in sor_by_geo.most_common()
    ]
    unresolved_rows = [
        {"raw_slot": k, "face_count": v}
        for k, v in non_color_unresolved.most_common()
    ]

    return black_rows, sor_rows, unresolved_rows, examples, black_by_state, black_by_vehicle, black_by_part


def collect_obj_side(export_root: Path, max_objs: int = 20000) -> List[dict]:
    rows = []
    n = 0
    for obj_path in sorted(export_root.glob("damage_*/*/*.obj")):
        state = obj_path.parts[-3].replace("damage_", "")
        vehicle = obj_path.stem
        try:
            faces = parse_obj_faces(obj_path)
        except Exception:
            continue
        for fr in faces:
            mat = fr.get("material", "")
            obj = fr.get("object", "")
            is_black = mat == "UNRES_COLOR_000000" or mat == "COLOR_000000" or mat.endswith("COLOR_000000") or mat.startswith("UNRES_COLOR_000000")
            is_sor = "_SOR" in str(obj).upper()
            if is_black or is_sor:
                row = {"state": state, "vehicle": vehicle, **fr, "is_black_material": int(is_black), "is_sor_object": int(is_sor)}
                rows.append(row)
        n += 1
        if n >= max_objs:
            break
    rows.sort(key=lambda r: (r["is_sor_object"], r["is_black_material"], float(r["area"])), reverse=True)
    return rows[:5000]


def write_md(path: Path, black_rows: List[dict], sor_rows: List[dict], unresolved_rows: List[dict], obj_rows: List[dict], black_by_state: Counter, black_by_vehicle: Counter, black_by_part: Counter) -> None:
    lines = []
    lines.append("# I76 black plane probe")
    lines.append("")
    lines.append("## Summary")
    lines.append("")
    lines.append(f"Unique GEOs with COLOR_000000 faces: {len(black_rows)}")
    lines.append(f"Unique SOR-like GEOs: {len(sor_rows)}")
    lines.append(f"OBJ-side sampled black/SOR faces: {len(obj_rows)}")
    lines.append("")
    lines.append("## COLOR_000000 faces by damage state")
    lines.append("")
    lines.append("| state | faces |")
    lines.append("|---:|---:|")
    for k, v in sorted(black_by_state.items(), key=lambda kv: kv[0]):
        lines.append(f"| {k} | {v} |")
    lines.append("")
    lines.append("## Top COLOR_000000 GEOs")
    lines.append("")
    lines.append("| geo | black faces | SOR-like |")
    lines.append("|---|---:|---:|")
    for r in black_rows[:40]:
        lines.append(f"| {r['geo']} | {r['black_face_count']} | {r['is_sor']} |")
    lines.append("")
    lines.append("## Top SOR-like GEOs")
    lines.append("")
    lines.append("| geo | faces |")
    lines.append("|---|---:|")
    for r in sor_rows[:40]:
        lines.append(f"| {r['geo']} | {r['face_count']} |")
    lines.append("")
    lines.append("## Top vehicles with COLOR_000000 faces")
    lines.append("")
    lines.append("| vehicle | faces |")
    lines.append("|---|---:|")
    for k, v in black_by_vehicle.most_common(40):
        lines.append(f"| {k} | {v} |")
    lines.append("")
    lines.append("## Top parts with COLOR_000000 faces")
    lines.append("")
    lines.append("| part | faces |")
    lines.append("|---|---:|")
    for k, v in black_by_part.most_common(40):
        lines.append(f"| {k} | {v} |")
    lines.append("")
    lines.append("## Non-color unresolved slots")
    lines.append("")
    lines.append("| raw slot | faces |")
    lines.append("|---|---:|")
    for r in unresolved_rows[:40]:
        lines.append(f"| {r['raw_slot']} | {r['face_count']} |")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--export-root", required=True, type=Path)
    ap.add_argument("--out", required=True, type=Path)
    ap.add_argument("--max-objs", type=int, default=20000)
    args = ap.parse_args()

    args.out.mkdir(parents=True, exist_ok=True)

    black_rows, sor_rows, unresolved_rows, examples, black_by_state, black_by_vehicle, black_by_part = collect_report_side(args.export_root)
    obj_rows = collect_obj_side(args.export_root, args.max_objs)

    write_csv(args.out / "black_color_by_geo.csv", black_rows)
    write_csv(args.out / "sor_like_by_geo.csv", sor_rows)
    write_csv(args.out / "non_color_unresolved.csv", unresolved_rows)
    write_csv(args.out / "black_color_examples.csv", examples)
    write_csv(args.out / "obj_black_sor_face_geometry_sample.csv", obj_rows)

    write_md(args.out / "README.md", black_rows, sor_rows, unresolved_rows, obj_rows, black_by_state, black_by_vehicle, black_by_part)

    summary = {
        "export_root": str(args.export_root),
        "unique_black_geos": len(black_rows),
        "unique_sor_like_geos": len(sor_rows),
        "black_faces_by_state": dict(sorted(black_by_state.items())),
        "top_black_geos": black_rows[:20],
        "top_sor_geos": sor_rows[:20],
        "obj_sample_rows": len(obj_rows),
    }
    (args.out / "summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
