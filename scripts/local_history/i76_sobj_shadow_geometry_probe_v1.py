#!/usr/bin/env python3
"""
i76_sobj_shadow_geometry_probe_v1.py

Probe SOBJ/_SOR placement and candidate projection behavior from exported OBJs.

This does not prove runtime behavior, but it summarizes whether the raw exported
SOBJ geometry is above/below/around the visible vehicle geometry under several
axis interpretations.

Example:
  python3 scripts/i76_sobj_shadow_geometry_probe_v1.py \
    --export-root scratch_data/i76_vehicle_geo_obj_v14_all_damage_v12_palette \
    --out scratch_data/i76_sobj_shadow_geometry_probe_v1
"""

from __future__ import annotations

import argparse
import csv
import json
import math
from pathlib import Path
from typing import Dict, Iterable, List, Tuple


def read_obj_objects(path: Path) -> Dict[str, List[Tuple[float, float, float]]]:
    objs: Dict[str, List[Tuple[float, float, float]]] = {}
    cur = ""
    with path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            s = line.strip()
            if s.startswith("o "):
                cur = s[2:].strip()
                objs.setdefault(cur, [])
            elif s.startswith("v ") and cur:
                parts = s.split()
                if len(parts) >= 4:
                    try:
                        objs[cur].append((float(parts[1]), float(parts[2]), float(parts[3])))
                    except Exception:
                        pass
    return objs


def bounds(points: List[Tuple[float, float, float]]) -> Tuple[float, float, float, float, float, float]:
    xs = [p[0] for p in points]; ys = [p[1] for p in points]; zs = [p[2] for p in points]
    return min(xs), max(xs), min(ys), max(ys), min(zs), max(zs)


def mean(vals: List[float]) -> float:
    return sum(vals) / len(vals) if vals else 0.0


def write_csv(path: Path, rows: List[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        path.write_text("", encoding="utf-8")
        return
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0].keys()))
        w.writeheader()
        w.writerows(rows)


def collect(export_root: Path) -> List[dict]:
    rows: List[dict] = []
    for obj_path in sorted(export_root.glob("damage_*/*/*.obj")):
        state = obj_path.parts[-3].replace("damage_", "")
        vehicle = obj_path.stem
        objs = read_obj_objects(obj_path)
        if not objs:
            continue

        shadow_pts = []
        visible_pts = []
        shadow_names = []
        for name, pts in objs.items():
            if not pts:
                continue
            if "_SOR" in name.upper():
                shadow_pts.extend(pts)
                shadow_names.append(name)
            else:
                visible_pts.extend(pts)

        if not shadow_pts or not visible_pts:
            continue

        sx0, sx1, sy0, sy1, sz0, sz1 = bounds(shadow_pts)
        vx0, vx1, vy0, vy1, vz0, vz1 = bounds(visible_pts)
        row = {
            "state": state,
            "vehicle": vehicle,
            "shadow_object_count": len(shadow_names),
            "shadow_names": ";".join(shadow_names[:10]),
            "shadow_min_x": sx0, "shadow_max_x": sx1,
            "shadow_min_y": sy0, "shadow_max_y": sy1,
            "shadow_min_z": sz0, "shadow_max_z": sz1,
            "visible_min_x": vx0, "visible_max_x": vx1,
            "visible_min_y": vy0, "visible_max_y": vy1,
            "visible_min_z": vz0, "visible_max_z": vz1,
            "shadow_centroid_x": mean([p[0] for p in shadow_pts]),
            "shadow_centroid_y": mean([p[1] for p in shadow_pts]),
            "shadow_centroid_z": mean([p[2] for p in shadow_pts]),
            "visible_centroid_x": mean([p[0] for p in visible_pts]),
            "visible_centroid_y": mean([p[1] for p in visible_pts]),
            "visible_centroid_z": mean([p[2] for p in visible_pts]),
            "shadow_y_vs_visible": "above" if sy0 > vy1 else ("below" if sy1 < vy0 else "overlap"),
            "shadow_z_vs_visible": "above" if sz0 > vz1 else ("below" if sz1 < vz0 else "overlap"),
            "shadow_x_span": sx1 - sx0,
            "shadow_y_span": sy1 - sy0,
            "shadow_z_span": sz1 - sz0,
            "visible_x_span": vx1 - vx0,
            "visible_y_span": vy1 - vy0,
            "visible_z_span": vz1 - vz0,
        }
        rows.append(row)
    return rows


def write_md(path: Path, rows: List[dict]) -> None:
    by_y = {}
    by_z = {}
    for r in rows:
        by_y[r["shadow_y_vs_visible"]] = by_y.get(r["shadow_y_vs_visible"], 0) + 1
        by_z[r["shadow_z_vs_visible"]] = by_z.get(r["shadow_z_vs_visible"], 0) + 1

    lines = []
    lines.append("# I76 SOBJ/_SOR geometry placement probe")
    lines.append("")
    lines.append(f"Vehicles/states with SOBJ/_SOR geometry: {len(rows)}")
    lines.append("")
    lines.append("## Classification if Y is vertical")
    lines.append("")
    for k, v in sorted(by_y.items()):
        lines.append(f"- {k}: {v}")
    lines.append("")
    lines.append("## Classification if Z is vertical")
    lines.append("")
    for k, v in sorted(by_z.items()):
        lines.append(f"- {k}: {v}")
    lines.append("")
    lines.append("## Largest raw SOBJ spans")
    lines.append("")
    lines.append("| vehicle | state | shadow names | x span | y span | z span | y relation | z relation |")
    lines.append("|---|---:|---|---:|---:|---:|---|---|")
    for r in sorted(rows, key=lambda x: max(float(x["shadow_x_span"]), float(x["shadow_y_span"]), float(x["shadow_z_span"])), reverse=True)[:60]:
        lines.append(f"| {r['vehicle']} | {r['state']} | {r['shadow_names']} | {float(r['shadow_x_span']):.3f} | {float(r['shadow_y_span']):.3f} | {float(r['shadow_z_span']):.3f} | {r['shadow_y_vs_visible']} | {r['shadow_z_vs_visible']} |")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--export-root", required=True, type=Path)
    ap.add_argument("--out", required=True, type=Path)
    args = ap.parse_args()

    args.out.mkdir(parents=True, exist_ok=True)
    rows = collect(args.export_root)
    write_csv(args.out / "sobj_shadow_geometry_bounds.csv", rows)
    write_md(args.out / "README.md", rows)
    (args.out / "summary.json").write_text(json.dumps({"rows": len(rows)}, indent=2), encoding="utf-8")
    print(json.dumps({"out": str(args.out), "rows": len(rows)}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
