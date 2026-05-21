#!/usr/bin/env python3
"""
i76_obj_open76_parity_rewrite_v1.py

Rewrite exported OBJ files into an Open76-like mesh convention for validation:
  - raw UV V: converts exporter vt.y from (1-v) back to v
  - inverted normals: multiplies vn by -1
  - Open76 triangle fan: n-gons become triangles (t,0,t+1)

This is only a diagnostic rewrite of existing OBJ/MTL output. It does not change
asset resolution, transforms, or texture decode.

Usage:
  python3 scripts/i76_obj_open76_parity_rewrite_v1.py \
    --export-root scratch_data/i76_vehicle_geo_obj_v17_piranha_whitekd \
    --vehicle vppirna \
    --out scratch_data/i76_obj_open76_parity_piranha
"""

from __future__ import annotations

import argparse
import csv
import json
import shutil
from pathlib import Path
from typing import List


def rewrite_obj(src: Path, dst: Path) -> dict:
    dst.parent.mkdir(parents=True, exist_ok=True)
    face_count = 0
    tri_count = 0
    ngon_count = 0
    with src.open("r", encoding="utf-8", errors="replace") as inp, dst.open("w", encoding="utf-8") as out:
        for line in inp:
            s = line.strip()
            if s.startswith("vt "):
                p = s.split()
                if len(p) >= 3:
                    u = float(p[1])
                    v = float(p[2])
                    out.write(f"vt {u:.8g} {1.0 - v:.8g}\n")
                else:
                    out.write(line)
            elif s.startswith("vn "):
                p = s.split()
                if len(p) >= 4:
                    x = -float(p[1]); y = -float(p[2]); z = -float(p[3])
                    out.write(f"vn {x:.8g} {y:.8g} {z:.8g}\n")
                else:
                    out.write(line)
            elif s.startswith("f "):
                toks = s.split()[1:]
                face_count += 1
                if len(toks) == 3:
                    out.write("f " + " ".join([toks[1], toks[0], toks[2]]) + "\n")
                    tri_count += 1
                elif len(toks) > 3:
                    ngon_count += 1
                    for t in range(1, len(toks) - 1):
                        out.write("f " + " ".join([toks[t], toks[0], toks[t + 1]]) + "\n")
                        tri_count += 1
                else:
                    out.write(line)
            else:
                out.write(line)
    return {"source": str(src), "out": str(dst), "faces_in": face_count, "tris_out": tri_count, "ngons_in": ngon_count}


def find_objs(root: Path, vehicle: str) -> List[Path]:
    vf = vehicle.lower().strip()
    out = []
    for p in sorted(root.rglob("*.obj")):
        if "sobj_auxiliary" in p.parts:
            continue
        if vf and vf not in p.name.lower() and vf not in p.parent.name.lower():
            continue
        out.append(p)
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--export-root", required=True, type=Path)
    ap.add_argument("--vehicle", default="")
    ap.add_argument("--out", required=True, type=Path)
    args = ap.parse_args()

    args.out.mkdir(parents=True, exist_ok=True)
    rows = []
    for obj in find_objs(args.export_root, args.vehicle):
        rel_parent = obj.parent.relative_to(args.export_root)
        dst_dir = args.out / rel_parent
        dst_dir.mkdir(parents=True, exist_ok=True)
        rows.append(rewrite_obj(obj, dst_dir / obj.name))
        # copy MTL and textures as-is
        for mtl in obj.parent.glob("*.mtl"):
            shutil.copy2(mtl, dst_dir / mtl.name)
        if (obj.parent / "textures").exists():
            shutil.copytree(obj.parent / "textures", dst_dir / "textures", dirs_exist_ok=True)

    with (args.out / "rewrite_manifest.csv").open("w", encoding="utf-8", newline="") as f:
        if rows:
            w = csv.DictWriter(f, fieldnames=list(rows[0].keys()))
            w.writeheader()
            w.writerows(rows)
    summary = {"export_root": str(args.export_root), "vehicle": args.vehicle, "objects_rewritten": len(rows), "rows": rows}
    (args.out / "summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
