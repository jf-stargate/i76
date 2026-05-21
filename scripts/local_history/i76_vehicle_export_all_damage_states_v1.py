#!/usr/bin/env python3
"""
i76_vehicle_export_all_damage_states_v1.py

Wrapper/validator for the existing Interstate '76 vehicle OBJ exporter.

Purpose:
  - Run i76_vehicle_geo_obj_export_v8.py for damage states 0, 1, 2, and 3.
  - Keep each state in a separate output folder.
  - Generate corpus-level and per-vehicle delta reports from the emitted OBJ/MTL files.
  - Avoid changing the proven v8 exporter/resolver logic.

Example:
  python3 scripts/i76_vehicle_export_all_damage_states_v1.py \
    --exporter scripts/i76_vehicle_geo_obj_export_v8.py \
    --zfs orig/I76.ZFS \
    --zix orig/I76.ZIX \
    --resolver scripts/i76_vehicle_texture_slot_resolver_v5.py \
    --out scratch/i76_vehicle_geo_obj_v9_all_damage \
    --export-textures \
    --overwrite \
    --tar \
    --tar-out-dir scratch/tars

Notes:
  - This script assumes v8 already accepts --damage-state 0|1|2|3.
  - It intentionally does not add aliases or FTFT fallback rules.
  - It parses generated OBJ/MTL files directly, so it remains useful even if
    v8 report filenames change.
"""

from __future__ import annotations

import argparse
import csv
import gzip
import hashlib
import json
import os
import shlex
import subprocess
import sys
import tarfile
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Set, Tuple


DAMAGE_STATES = (0, 1, 2, 3)


@dataclass
class ObjStats:
    vehicle: str
    damage_state: int
    obj_path: str
    mtl_path: str
    obj_sha1: str
    vertex_count: int
    normal_count: int
    texcoord_count: int
    face_count: int
    object_count: int
    group_count: int
    usemtl_count: int
    unique_material_count: int
    mtl_material_count: int
    mtl_texture_count: int
    color_material_count: int
    unresolved_like_material_count: int
    objects: List[str]
    groups: List[str]
    materials: List[str]
    textures: List[str]


@dataclass
class DeltaStats:
    vehicle: str
    compare: str
    base_damage_state: int
    other_damage_state: int
    base_present: bool
    other_present: bool
    face_delta: int
    vertex_delta: int
    material_added_count: int
    material_removed_count: int
    object_added_count: int
    object_removed_count: int
    group_added_count: int
    group_removed_count: int
    texture_added_count: int
    texture_removed_count: int
    materials_added: List[str]
    materials_removed: List[str]
    objects_added: List[str]
    objects_removed: List[str]
    groups_added: List[str]
    groups_removed: List[str]
    textures_added: List[str]
    textures_removed: List[str]


def eprint(*args: object) -> None:
    print(*args, file=sys.stderr)


def shell_join(args: Sequence[str]) -> str:
    return " ".join(shlex.quote(a) for a in args)


def stable_vehicle_name(obj_path: Path, state_root: Path) -> str:
    rel = obj_path.relative_to(state_root)
    if len(rel.parts) >= 2 and rel.parent.name.lower().startswith(("damage_", "state_")):
        return rel.stem
    return obj_path.stem


def read_text_lossy(path: Path) -> Iterable[str]:
    with path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            yield line.rstrip("\n\r")


def sha1_file(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        while True:
            b = f.read(1024 * 1024)
            if not b:
                break
            h.update(b)
    return h.hexdigest()


def resolve_mtl_path(obj_path: Path) -> Optional[Path]:
    for line in read_text_lossy(obj_path):
        if line.startswith("mtllib "):
            name = line.split(None, 1)[1].strip()
            candidate = (obj_path.parent / name).resolve()
            if candidate.exists():
                return candidate
    fallback = obj_path.with_suffix(".mtl")
    if fallback.exists():
        return fallback
    return None


def parse_mtl(mtl_path: Optional[Path]) -> Tuple[Set[str], Set[str], int]:
    materials: Set[str] = set()
    textures: Set[str] = set()
    color_material_count = 0

    if mtl_path is None or not mtl_path.exists():
        return materials, textures, color_material_count

    current_material = ""
    for line in read_text_lossy(mtl_path):
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        if s.startswith("newmtl "):
            current_material = s.split(None, 1)[1].strip()
            materials.add(current_material)
            if current_material.upper().startswith("COLOR_"):
                color_material_count += 1
        elif s.startswith("map_Kd "):
            tex = s.split(None, 1)[1].strip()
            textures.add(tex)
    return materials, textures, color_material_count


def parse_obj(obj_path: Path, state_root: Path, damage_state: int) -> ObjStats:
    vertex_count = 0
    normal_count = 0
    texcoord_count = 0
    face_count = 0

    objects: Set[str] = set()
    groups: Set[str] = set()
    materials: Set[str] = set()

    for line in read_text_lossy(obj_path):
        if line.startswith("v "):
            vertex_count += 1
        elif line.startswith("vn "):
            normal_count += 1
        elif line.startswith("vt "):
            texcoord_count += 1
        elif line.startswith("f "):
            face_count += 1
        elif line.startswith("o "):
            name = line.split(None, 1)[1].strip() if len(line.split(None, 1)) > 1 else ""
            if name:
                objects.add(name)
        elif line.startswith("g "):
            name = line.split(None, 1)[1].strip() if len(line.split(None, 1)) > 1 else ""
            if name:
                groups.add(name)
        elif line.startswith("usemtl "):
            name = line.split(None, 1)[1].strip() if len(line.split(None, 1)) > 1 else ""
            if name:
                materials.add(name)

    mtl_path = resolve_mtl_path(obj_path)
    mtl_materials, textures, color_material_count = parse_mtl(mtl_path)

    all_materials = set(materials) | set(mtl_materials)
    unresolved_like_materials = [
        m for m in all_materials
        if "UNRESOLVED" in m.upper()
        or "MISSING" in m.upper()
        or m.upper().startswith("UNRES_")
    ]

    return ObjStats(
        vehicle=stable_vehicle_name(obj_path, state_root),
        damage_state=damage_state,
        obj_path=str(obj_path),
        mtl_path=str(mtl_path) if mtl_path else "",
        obj_sha1=sha1_file(obj_path),
        vertex_count=vertex_count,
        normal_count=normal_count,
        texcoord_count=texcoord_count,
        face_count=face_count,
        object_count=len(objects),
        group_count=len(groups),
        usemtl_count=len(materials),
        unique_material_count=len(all_materials),
        mtl_material_count=len(mtl_materials),
        mtl_texture_count=len(textures),
        color_material_count=color_material_count,
        unresolved_like_material_count=len(unresolved_like_materials),
        objects=sorted(objects),
        groups=sorted(groups),
        materials=sorted(all_materials),
        textures=sorted(textures),
    )


def find_obj_files(state_root: Path) -> List[Path]:
    return sorted(p for p in state_root.rglob("*.obj") if p.is_file())


def summarize_state(state_root: Path, damage_state: int) -> Dict[str, ObjStats]:
    stats: Dict[str, ObjStats] = {}
    for obj_path in find_obj_files(state_root):
        st = parse_obj(obj_path, state_root, damage_state)
        stats[st.vehicle] = st
    return stats


def diff_list(a: Iterable[str], b: Iterable[str]) -> Tuple[List[str], List[str]]:
    sa = set(a)
    sb = set(b)
    return sorted(sb - sa), sorted(sa - sb)


def compare_against_base(
    all_stats: Dict[int, Dict[str, ObjStats]],
    base_state: int = 0,
) -> List[DeltaStats]:
    base = all_stats.get(base_state, {})
    vehicles: Set[str] = set(base.keys())
    for d in all_stats:
        vehicles.update(all_stats[d].keys())

    deltas: List[DeltaStats] = []
    for vehicle in sorted(vehicles):
        b = base.get(vehicle)
        for d in sorted(all_stats.keys()):
            if d == base_state:
                continue
            o = all_stats[d].get(vehicle)

            if b and o:
                mat_added, mat_removed = diff_list(b.materials, o.materials)
                obj_added, obj_removed = diff_list(b.objects, o.objects)
                grp_added, grp_removed = diff_list(b.groups, o.groups)
                tex_added, tex_removed = diff_list(b.textures, o.textures)
                face_delta = o.face_count - b.face_count
                vertex_delta = o.vertex_count - b.vertex_count
            elif o and not b:
                mat_added, mat_removed = sorted(o.materials), []
                obj_added, obj_removed = sorted(o.objects), []
                grp_added, grp_removed = sorted(o.groups), []
                tex_added, tex_removed = sorted(o.textures), []
                face_delta = o.face_count
                vertex_delta = o.vertex_count
            elif b and not o:
                mat_added, mat_removed = [], sorted(b.materials)
                obj_added, obj_removed = [], sorted(b.objects)
                grp_added, grp_removed = [], sorted(b.groups)
                tex_added, tex_removed = [], sorted(b.textures)
                face_delta = -b.face_count
                vertex_delta = -b.vertex_count
            else:
                continue

            deltas.append(DeltaStats(
                vehicle=vehicle,
                compare=f"{base_state}->{d}",
                base_damage_state=base_state,
                other_damage_state=d,
                base_present=b is not None,
                other_present=o is not None,
                face_delta=face_delta,
                vertex_delta=vertex_delta,
                material_added_count=len(mat_added),
                material_removed_count=len(mat_removed),
                object_added_count=len(obj_added),
                object_removed_count=len(obj_removed),
                group_added_count=len(grp_added),
                group_removed_count=len(grp_removed),
                texture_added_count=len(tex_added),
                texture_removed_count=len(tex_removed),
                materials_added=mat_added,
                materials_removed=mat_removed,
                objects_added=obj_added,
                objects_removed=obj_removed,
                groups_added=grp_added,
                groups_removed=grp_removed,
                textures_added=tex_added,
                textures_removed=tex_removed,
            ))
    return deltas


def write_csv(path: Path, rows: List[dict], list_fields_as_joined: bool = True) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        path.write_text("", encoding="utf-8")
        return

    fieldnames = list(rows[0].keys())
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        for row in rows:
            out = dict(row)
            if list_fields_as_joined:
                for k, v in list(out.items()):
                    if isinstance(v, list):
                        out[k] = ";".join(str(x) for x in v)
            w.writerow(out)


def write_json(path: Path, obj: object) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(obj, indent=2, sort_keys=True), encoding="utf-8")


def make_tar_gz(src_dir: Path, tar_path: Path) -> None:
    tar_path.parent.mkdir(parents=True, exist_ok=True)
    with tarfile.open(tar_path, "w:gz") as tf:
        tf.add(src_dir, arcname=src_dir.name)


def run_exporter_for_state(args: argparse.Namespace, damage_state: int) -> Path:
    state_root = Path(args.out).resolve() / f"damage_{damage_state}"
    state_root.mkdir(parents=True, exist_ok=True)

    cmd = [
        sys.executable,
        str(Path(args.exporter)),
        "--zfs", str(Path(args.zfs)),
        "--zix", str(Path(args.zix)),
        "--resolver", str(Path(args.resolver)),
        "--out", str(state_root),
        "--all",
        "--damage-state", str(damage_state),
    ]

    if args.export_textures:
        cmd.append("--export-textures")
    if args.overwrite:
        cmd.append("--overwrite")
    if args.tar_each_state:
        cmd.append("--tar")
        if args.tar_out_dir:
            cmd.extend(["--tar-out-dir", str(Path(args.tar_out_dir))])

    for extra in args.exporter_arg:
        cmd.append(extra)

    eprint(f"[run] damage_state={damage_state}: {shell_join(cmd)}")
    if not args.skip_export:
        subprocess.run(cmd, check=True)

    return state_root


def aggregate_totals(all_stats: Dict[int, Dict[str, ObjStats]]) -> List[dict]:
    rows: List[dict] = []
    for d in sorted(all_stats.keys()):
        vals = list(all_stats[d].values())
        rows.append({
            "damage_state": d,
            "vehicle_count": len(vals),
            "total_faces": sum(v.face_count for v in vals),
            "total_vertices": sum(v.vertex_count for v in vals),
            "total_objects": sum(v.object_count for v in vals),
            "total_groups": sum(v.group_count for v in vals),
            "total_unique_materials_per_vehicle_sum": sum(v.unique_material_count for v in vals),
            "total_mtl_textures_per_vehicle_sum": sum(v.mtl_texture_count for v in vals),
            "total_color_materials": sum(v.color_material_count for v in vals),
            "total_unresolved_like_materials": sum(v.unresolved_like_material_count for v in vals),
        })
    return rows


def build_part_presence_rows(all_stats: Dict[int, Dict[str, ObjStats]]) -> List[dict]:
    vehicles: Set[str] = set()
    for state_stats in all_stats.values():
        vehicles.update(state_stats.keys())

    rows: List[dict] = []
    for vehicle in sorted(vehicles):
        part_names: Set[str] = set()
        for d in all_stats:
            st = all_stats[d].get(vehicle)
            if st:
                part_names.update(st.objects)
                part_names.update(st.groups)

        for part in sorted(part_names):
            row = {"vehicle": vehicle, "part": part}
            for d in sorted(all_stats.keys()):
                st = all_stats[d].get(vehicle)
                present = False
                if st:
                    present = part in set(st.objects) or part in set(st.groups)
                row[f"damage_{d}"] = 1 if present else 0
            rows.append(row)
    return rows


def parse_args(argv: Optional[Sequence[str]] = None) -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="Run i76 vehicle OBJ exporter for all damage states and generate delta reports."
    )
    p.add_argument("--exporter", required=True, help="Path to i76_vehicle_geo_obj_export_v8.py")
    p.add_argument("--zfs", required=True, help="Path to I76.ZFS")
    p.add_argument("--zix", required=True, help="Path to I76.ZIX")
    p.add_argument("--resolver", required=True, help="Path to i76_vehicle_texture_slot_resolver_v5.py")
    p.add_argument("--out", required=True, help="Output root for all damage state folders and reports")
    p.add_argument("--export-textures", action="store_true", help="Pass --export-textures to the exporter")
    p.add_argument("--overwrite", action="store_true", help="Pass --overwrite to the exporter")
    p.add_argument("--skip-export", action="store_true", help="Only parse existing damage_0..damage_3 outputs")
    p.add_argument("--tar-each-state", action="store_true", help="Pass --tar to each v8 exporter invocation")
    p.add_argument("--tar", action="store_true", help="Create a tar.gz of the combined output root after reports")
    p.add_argument("--tar-out-dir", default="", help="Directory for tar outputs")
    p.add_argument(
        "--exporter-arg",
        action="append",
        default=[],
        help="Extra single argument to pass through to exporter. Repeat as needed.",
    )
    return p.parse_args(argv)


def main(argv: Optional[Sequence[str]] = None) -> int:
    args = parse_args(argv)
    out_root = Path(args.out).resolve()
    out_root.mkdir(parents=True, exist_ok=True)

    state_roots: Dict[int, Path] = {}
    for d in DAMAGE_STATES:
        state_roots[d] = run_exporter_for_state(args, d)

    all_stats: Dict[int, Dict[str, ObjStats]] = {}
    for d, root in state_roots.items():
        eprint(f"[scan] damage_state={d}: {root}")
        all_stats[d] = summarize_state(root, d)
        eprint(f"[scan] damage_state={d}: {len(all_stats[d])} OBJ vehicles")

    reports_dir = out_root / "_damage_reports"
    reports_dir.mkdir(parents=True, exist_ok=True)

    flat_rows: List[dict] = []
    for d in sorted(all_stats.keys()):
        for vehicle in sorted(all_stats[d].keys()):
            flat_rows.append(asdict(all_stats[d][vehicle]))

    delta_rows = [asdict(d) for d in compare_against_base(all_stats, 0)]
    totals_rows = aggregate_totals(all_stats)
    part_rows = build_part_presence_rows(all_stats)

    write_csv(reports_dir / "vehicle_damage_state_summary.csv", flat_rows)
    write_csv(reports_dir / "vehicle_damage_state_delta_vs_0.csv", delta_rows)
    write_csv(reports_dir / "vehicle_damage_state_totals.csv", totals_rows)
    write_csv(reports_dir / "vehicle_part_presence_matrix.csv", part_rows)

    write_json(reports_dir / "vehicle_damage_state_summary.json", flat_rows)
    write_json(reports_dir / "vehicle_damage_state_delta_vs_0.json", delta_rows)
    write_json(reports_dir / "vehicle_damage_state_totals.json", totals_rows)

    if args.tar:
        tar_dir = Path(args.tar_out_dir).resolve() if args.tar_out_dir else out_root.parent
        tar_path = tar_dir / f"{out_root.name}.tar.gz"
        eprint(f"[tar] {tar_path}")
        make_tar_gz(out_root, tar_path)

    print(json.dumps({
        "out_root": str(out_root),
        "reports_dir": str(reports_dir),
        "damage_states": list(DAMAGE_STATES),
        "vehicles_by_state": {str(d): len(all_stats[d]) for d in sorted(all_stats.keys())},
        "total_faces_by_state": {str(d): sum(v.face_count for v in all_stats[d].values()) for d in sorted(all_stats.keys())},
        "reports": [
            str(reports_dir / "vehicle_damage_state_summary.csv"),
            str(reports_dir / "vehicle_damage_state_delta_vs_0.csv"),
            str(reports_dir / "vehicle_damage_state_totals.csv"),
            str(reports_dir / "vehicle_part_presence_matrix.csv"),
        ],
    }, indent=2, sort_keys=True))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
