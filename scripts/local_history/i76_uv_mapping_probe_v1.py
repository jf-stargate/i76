#!/usr/bin/env python3
"""
i76_uv_mapping_probe_v1.py

Probe UV mapping issues in an Interstate '76 OBJ export, focused on identifying
faces/materials whose rendered decals appear mirrored. This script does not need
Ghidra. It reads exported OBJ/MTL files and reports UV orientation statistics by
object/material/texture.

It is intended to answer:
  - Which material/texture is used on the Piranha rear "432" decal?
  - Are those faces using mirrored UV winding relative to other faces?
  - Are left/right/back variants using negative UV area or flipped U/V ranges?
  - Which texture asset should be targeted by a decode-orientation probe?

Usage:
  python3 scripts/i76_uv_mapping_probe_v1.py \
    --export-root scratch_data/i76_vehicle_geo_obj_v17_piranha_whitekd \
    --vehicle vppirna1 \
    --out scratch_data/i76_uv_probe_piranha_v1

For all Piranha variants:
  python3 scripts/i76_uv_mapping_probe_v1.py \
    --export-root scratch_data/i76_vehicle_geo_obj_v17_piranha_whitekd \
    --vehicle vppirna \
    --out scratch_data/i76_uv_probe_piranha_all
"""

from __future__ import annotations

import argparse
import csv
import json
import math
import re
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


def read_mtl_maps(mtl_path: Path) -> Dict[str, str]:
    maps: Dict[str, str] = {}
    cur = ""
    if not mtl_path.exists():
        return maps
    with mtl_path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            s = line.strip()
            if not s or s.startswith("#"):
                continue
            if s.startswith("newmtl "):
                cur = s.split(None, 1)[1]
            elif s.startswith("map_Kd ") and cur:
                maps[cur] = s.split(None, 1)[1]
    return maps


def signed_uv_area(uvs: List[Tuple[float, float]]) -> float:
    if len(uvs) < 3:
        return 0.0
    s = 0.0
    n = len(uvs)
    for i in range(n):
        u1, v1 = uvs[i]
        u2, v2 = uvs[(i + 1) % n]
        s += u1 * v2 - u2 * v1
    return 0.5 * s


def signed_xyz_area_vector(points: List[Tuple[float, float, float]]) -> Tuple[float, float, float]:
    # Newell vector, not normalized.
    nx = ny = nz = 0.0
    n = len(points)
    for i in range(n):
        x1, y1, z1 = points[i]
        x2, y2, z2 = points[(i + 1) % n]
        nx += (y1 - y2) * (z1 + z2)
        ny += (z1 - z2) * (x1 + x2)
        nz += (x1 - x2) * (y1 + y2)
    return nx, ny, nz


def parse_face_token(tok: str) -> Tuple[Optional[int], Optional[int], Optional[int]]:
    parts = tok.split("/")
    vi = int(parts[0]) if parts and parts[0] else None
    vti = int(parts[1]) if len(parts) > 1 and parts[1] else None
    vni = int(parts[2]) if len(parts) > 2 and parts[2] else None
    return vi, vti, vni


def resolve_index(idx: Optional[int], count: int) -> Optional[int]:
    if idx is None:
        return None
    if idx < 0:
        return count + idx
    return idx - 1


def parse_obj(obj_path: Path) -> Tuple[List[dict], List[str]]:
    verts: List[Tuple[float, float, float]] = []
    uvs: List[Tuple[float, float]] = []
    normals: List[Tuple[float, float, float]] = []
    rows: List[dict] = []
    mtllibs: List[str] = []
    cur_obj = ""
    cur_mat = ""
    face_no = 0

    with obj_path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            s = line.strip()
            if not s:
                continue
            if s.startswith("mtllib "):
                mtllibs.append(s.split(None, 1)[1])
            elif s.startswith("o "):
                cur_obj = s[2:].strip()
            elif s.startswith("usemtl "):
                cur_mat = s.split(None, 1)[1].strip()
            elif s.startswith("v "):
                p = s.split()
                verts.append((float(p[1]), float(p[2]), float(p[3])))
            elif s.startswith("vt "):
                p = s.split()
                uvs.append((float(p[1]), float(p[2])))
            elif s.startswith("vn "):
                p = s.split()
                normals.append((float(p[1]), float(p[2]), float(p[3])))
            elif s.startswith("f "):
                face_no += 1
                face_tokens = s.split()[1:]
                vis = []
                vtis = []
                vnis = []
                for tok in face_tokens:
                    vi, vti, vni = parse_face_token(tok)
                    ri = resolve_index(vi, len(verts))
                    rti = resolve_index(vti, len(uvs))
                    rni = resolve_index(vni, len(normals))
                    if ri is not None:
                        vis.append(ri)
                    if rti is not None:
                        vtis.append(rti)
                    if rni is not None:
                        vnis.append(rni)

                face_pts = [verts[i] for i in vis if 0 <= i < len(verts)]
                face_uvs = [uvs[i] for i in vtis if 0 <= i < len(uvs)]
                uv_area = signed_uv_area(face_uvs) if face_uvs else 0.0
                nx, ny, nz = signed_xyz_area_vector(face_pts) if face_pts else (0.0, 0.0, 0.0)
                us = [u for u, v in face_uvs]
                vs = [v for u, v in face_uvs]
                xs = [p[0] for p in face_pts]
                ys = [p[1] for p in face_pts]
                zs = [p[2] for p in face_pts]
                rows.append({
                    "obj_file": obj_path.name,
                    "object": cur_obj,
                    "face_no": face_no,
                    "material": cur_mat,
                    "vertex_count": len(face_pts),
                    "uv_count": len(face_uvs),
                    "uv_area_signed": uv_area,
                    "uv_area_abs": abs(uv_area),
                    "uv_orientation": "positive" if uv_area > 1e-10 else ("negative" if uv_area < -1e-10 else "zero"),
                    "u_min": min(us) if us else "",
                    "u_max": max(us) if us else "",
                    "v_min": min(vs) if vs else "",
                    "v_max": max(vs) if vs else "",
                    "u_span": (max(us)-min(us)) if us else "",
                    "v_span": (max(vs)-min(vs)) if vs else "",
                    "xyz_area_nx": nx,
                    "xyz_area_ny": ny,
                    "xyz_area_nz": nz,
                    "x_min": min(xs) if xs else "",
                    "x_max": max(xs) if xs else "",
                    "y_min": min(ys) if ys else "",
                    "y_max": max(ys) if ys else "",
                    "z_min": min(zs) if zs else "",
                    "z_max": max(zs) if zs else "",
                    "x_center": sum(xs)/len(xs) if xs else "",
                    "y_center": sum(ys)/len(ys) if ys else "",
                    "z_center": sum(zs)/len(zs) if zs else "",
                    "face_tokens": " ".join(face_tokens),
                })
    return rows, mtllibs


def write_csv(path: Path, rows: List[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        path.write_text("", encoding="utf-8")
        return
    fields = list(rows[0].keys())
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        w.writeheader()
        w.writerows(rows)


def find_vehicle_dirs(root: Path, vehicle_filter: str) -> List[Path]:
    vf = vehicle_filter.lower().strip()
    dirs = []
    # single-export layout: root/<vehicle>.vcf/<vehicle>.obj
    for p in root.rglob("*.obj"):
        if "sobj_auxiliary" in p.parts:
            continue
        if vf and vf not in p.name.lower() and vf not in str(p.parent.name).lower():
            continue
        dirs.append(p)
    return sorted(set(dirs))


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--export-root", required=True, type=Path)
    ap.add_argument("--vehicle", default="")
    ap.add_argument("--out", required=True, type=Path)
    ap.add_argument("--rear-threshold", type=float, default=0.35, help="Fraction of max Y/Z/X used for rough rear-region grouping diagnostics")
    args = ap.parse_args()

    args.out.mkdir(parents=True, exist_ok=True)

    obj_paths = find_vehicle_dirs(args.export_root, args.vehicle)
    all_faces: List[dict] = []
    group_counter = Counter()
    grouped = {}

    for obj_path in obj_paths:
        faces, mtllibs = parse_obj(obj_path)
        # merge mtl maps
        maps: Dict[str, str] = {}
        for ml in mtllibs:
            maps.update(read_mtl_maps(obj_path.parent / ml))
        vehicle = obj_path.parent.name
        state = "single"
        for part in obj_path.parts:
            if part.startswith("damage_"):
                state = part.replace("damage_", "")
        for r in faces:
            r["vehicle"] = vehicle
            r["state"] = state
            r["obj_path"] = str(obj_path)
            r["map_kd"] = maps.get(r["material"], "")
            all_faces.append(r)

    # Group by material/object/map/uv orientation.
    for r in all_faces:
        k = (r["state"], r["vehicle"], r["object"], r["material"], r["map_kd"], r["uv_orientation"])
        group_counter[k] += 1
        if k not in grouped:
            grouped[k] = {
                "state": r["state"],
                "vehicle": r["vehicle"],
                "object": r["object"],
                "material": r["material"],
                "map_kd": r["map_kd"],
                "uv_orientation": r["uv_orientation"],
                "face_count": 0,
                "u_min": r["u_min"], "u_max": r["u_max"],
                "v_min": r["v_min"], "v_max": r["v_max"],
                "x_min": r["x_min"], "x_max": r["x_max"],
                "y_min": r["y_min"], "y_max": r["y_max"],
                "z_min": r["z_min"], "z_max": r["z_max"],
            }
        g = grouped[k]
        g["face_count"] += 1
        for fld in ["u_min", "v_min", "x_min", "y_min", "z_min"]:
            if r[fld] != "" and (g[fld] == "" or r[fld] < g[fld]):
                g[fld] = r[fld]
        for fld in ["u_max", "v_max", "x_max", "y_max", "z_max"]:
            if r[fld] != "" and (g[fld] == "" or r[fld] > g[fld]):
                g[fld] = r[fld]

    grouped_rows = sorted(grouped.values(), key=lambda x: (x["vehicle"], x["object"], x["material"], x["uv_orientation"]))

    # Candidate decal/text groups: maps/materials likely to contain rear numbering.
    decal_rows = []
    for r in all_faces:
        hay = " ".join([r.get("object",""), r.get("material",""), r.get("map_kd","")]).lower()
        if any(s in hay for s in ["bk", "back", "rear", "bkb", "bkl", "bkr", "bkt", "432", "pp11bk", "pp12bk", "pp13bk"]):
            decal_rows.append(r)

    write_csv(args.out / "uv_faces.csv", all_faces)
    write_csv(args.out / "uv_grouped_by_object_material.csv", grouped_rows)
    write_csv(args.out / "uv_candidate_rear_decal_faces.csv", decal_rows)

    lines = []
    lines.append("# I76 UV mapping probe")
    lines.append("")
    lines.append(f"Export root: `{args.export_root}`")
    lines.append(f"Vehicle filter: `{args.vehicle}`")
    lines.append(f"OBJ files: {len(obj_paths)}")
    lines.append(f"Faces inspected: {len(all_faces)}")
    lines.append(f"Candidate rear/decal faces: {len(decal_rows)}")
    lines.append("")
    lines.append("## Top candidate rear/decal groups")
    lines.append("")
    lines.append("| vehicle | object | material | map_Kd | uv orientation | faces | u range | v range |")
    lines.append("|---|---|---|---|---|---:|---|---|")
    dc = Counter((r["vehicle"], r["object"], r["material"], r["map_kd"], r["uv_orientation"]) for r in decal_rows)
    for (veh, obj, mat, mkd, orient), cnt in dc.most_common(80):
        subset = [r for r in decal_rows if (r["vehicle"], r["object"], r["material"], r["map_kd"], r["uv_orientation"]) == (veh,obj,mat,mkd,orient)]
        umin = min(float(r["u_min"]) for r in subset if r["u_min"] != "")
        umax = max(float(r["u_max"]) for r in subset if r["u_max"] != "")
        vmin = min(float(r["v_min"]) for r in subset if r["v_min"] != "")
        vmax = max(float(r["v_max"]) for r in subset if r["v_max"] != "")
        lines.append(f"| {veh} | {obj} | {mat} | {mkd} | {orient} | {cnt} | {umin:.4f}..{umax:.4f} | {vmin:.4f}..{vmax:.4f} |")
    (args.out / "README.md").write_text("\n".join(lines) + "\n", encoding="utf-8")

    summary = {
        "export_root": str(args.export_root),
        "vehicle_filter": args.vehicle,
        "obj_files": len(obj_paths),
        "faces": len(all_faces),
        "candidate_rear_decal_faces": len(decal_rows),
        "orientation_counts": dict(Counter(r["uv_orientation"] for r in all_faces)),
        "candidate_orientation_counts": dict(Counter(r["uv_orientation"] for r in decal_rows)),
    }
    (args.out / "summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
