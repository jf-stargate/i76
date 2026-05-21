# Blender Python script: Interstate '76 level terrain manifest importer.
#
# Usage from command line:
#   blender --python i76_blender_import_level_v1.py -- --manifest /path/i76_level_blender_manifest.json
#
# Or inside Blender:
#   exec(open("/path/i76_blender_import_level_v1.py").read())
#   import_i76_manifest("/path/i76_level_blender_manifest.json")
#
# Current import support:
#   - terrain_raw *.TAB/*.TER pages from i76_level_blender_export_v1.py manifest
#   - per-surface material assignment from packed TER word high bits
#
# Coordinate convention:
#   Blender X = I76 world X
#   Blender Y = I76 world Z
#   Blender Z = height
#
# This swaps manifest height axis from Y to Blender Z, which is the natural Blender up axis.

from __future__ import annotations

import argparse
import json
import struct
from pathlib import Path
from typing import Dict, List, Tuple

import bpy


PAGE_W = 128
PAGE_H = 128
PAGE_SIZE = 0x8000


def clear_collection(name: str):
    col = bpy.data.collections.get(name)
    if col is None:
        col = bpy.data.collections.new(name)
        bpy.context.scene.collection.children.link(col)
        return col

    # Clear existing objects owned by this collection.
    for obj in list(col.objects):
        bpy.data.objects.remove(obj, do_unlink=True)
    return col


def get_materials():
    mats = []
    # Simple neutral materials; colors can be changed after import.
    colors = [
        (0.18, 0.15, 0.10, 1.0),  # dirt
        (0.28, 0.28, 0.28, 1.0),  # rock/asphalt
        (0.12, 0.30, 0.12, 1.0),  # vegetation
        (0.45, 0.38, 0.22, 1.0),
        (0.20, 0.35, 0.30, 1.0),
        (0.50, 0.50, 0.42, 1.0),
        (0.30, 0.22, 0.18, 1.0),
        (0.12, 0.12, 0.12, 1.0),
    ]
    for i, color in enumerate(colors):
        name = f"I76_surface_{i}"
        mat = bpy.data.materials.get(name)
        if mat is None:
            mat = bpy.data.materials.new(name)
            mat.diffuse_color = color
        mats.append(mat)
    return mats


def read_page_words(raw_path: Path, page_index: int) -> Tuple[int, ...]:
    with raw_path.open("rb") as f:
        f.seek(page_index * PAGE_SIZE)
        raw = f.read(PAGE_SIZE)
    if len(raw) != PAGE_SIZE:
        raise ValueError(f"{raw_path} page {page_index} short read")
    return struct.unpack("<" + "H" * (PAGE_W * PAGE_H), raw)


def make_page_mesh(
    *,
    terrain_name: str,
    raw_path: Path,
    page_index: int,
    origin_cell: Tuple[int, int],
    horizontal_scale: float,
    vertical_scale: float,
    collection,
    materials,
):
    words = read_page_words(raw_path, page_index)
    ox, oz = origin_cell
    base_x = ox * PAGE_W * horizontal_scale
    base_y = oz * PAGE_H * horizontal_scale

    verts: List[Tuple[float, float, float]] = []
    faces: List[Tuple[int, int, int, int]] = []
    face_surfaces: List[int] = []

    for y in range(PAGE_H):
        for x in range(PAGE_W):
            w = words[y * PAGE_W + x]
            h = w & 0x0FFF
            # Blender uses Z up: (X, Y, Z) = (world x, world z, height)
            verts.append((
                base_x + x * horizontal_scale,
                base_y + y * horizontal_scale,
                h * vertical_scale,
            ))

    for y in range(PAGE_H - 1):
        for x in range(PAGE_W - 1):
            v0 = y * PAGE_W + x
            faces.append((v0, v0 + 1, v0 + PAGE_W + 1, v0 + PAGE_W))

            # Use the top-left sample's surface class for the quad material.
            w = words[y * PAGE_W + x]
            face_surfaces.append((w >> 13) & 7)

    mesh = bpy.data.meshes.new(f"{terrain_name}_page_{page_index:02d}_mesh")
    mesh.from_pydata(verts, [], faces)
    mesh.update()

    obj = bpy.data.objects.new(f"{terrain_name}_page_{page_index:02d}", mesh)
    collection.objects.link(obj)

    for mat in materials:
        mesh.materials.append(mat)
    for poly, surface in zip(mesh.polygons, face_surfaces):
        poly.material_index = surface if surface < len(materials) else 0

    return obj


def import_i76_manifest(
    manifest_path: str,
    *,
    terrain_filter: str = "",
    horizontal_scale_override=None,
    vertical_scale_override=None,
    clear_existing: bool = True,
):
    manifest_file = Path(manifest_path)
    manifest = json.loads(manifest_file.read_text(encoding="utf-8"))
    root = manifest_file.parent

    collection = clear_collection("I76_Level") if clear_existing else bpy.data.collections.new("I76_Level")
    if collection.name not in bpy.context.scene.collection.children:
        try:
            bpy.context.scene.collection.children.link(collection)
        except Exception:
            pass

    terrain_col = bpy.data.collections.get("I76_Terrain")
    if terrain_col is None:
        terrain_col = bpy.data.collections.new("I76_Terrain")
        collection.children.link(terrain_col)
    elif clear_existing:
        for obj in list(terrain_col.objects):
            bpy.data.objects.remove(obj, do_unlink=True)

    materials = get_materials()
    imported = []

    for terrain in manifest.get("terrain", []):
        name = terrain.get("name", "terrain")
        if terrain_filter and terrain_filter.lower() not in name.lower():
            continue

        raw_path = Path(terrain["raw_path"])
        if not raw_path.is_absolute():
            raw_path = root / raw_path
        if not raw_path.exists():
            # Manifest may contain paths relative to package root via terrain_raw/...
            raw_path = root / "terrain_raw" / Path(terrain["raw_path"]).name
        if not raw_path.exists():
            print(f"WARNING: missing terrain raw file: {terrain.get('raw_path')}")
            continue

        hscale = horizontal_scale_override
        if hscale is None:
            hscale = terrain.get("horizontal_sample_scale", manifest.get("coordinate_system", {}).get("horizontal_sample_scale_default", 5.0))

        vscale = vertical_scale_override
        if vscale is None:
            vscale = manifest.get("coordinate_system", {}).get("vertical_scale_default", 1.0)

        origins_raw: Dict[str, List[int]] = terrain.get("page_origins", {})
        page_count = int(terrain.get("page_count", 0))

        for page_index in range(page_count):
            origin = origins_raw.get(str(page_index), [page_index, 0])
            obj = make_page_mesh(
                terrain_name=name,
                raw_path=raw_path,
                page_index=page_index,
                origin_cell=(int(origin[0]), int(origin[1])),
                horizontal_scale=float(hscale),
                vertical_scale=float(vscale),
                collection=terrain_col,
                materials=materials,
            )
            imported.append(obj)

    print(f"Imported {len(imported)} I76 terrain page objects from {manifest_file}")
    return imported


def parse_blender_args():
    import sys
    argv = sys.argv
    if "--" not in argv:
        return None
    args = argv[argv.index("--") + 1:]
    ap = argparse.ArgumentParser()
    ap.add_argument("--manifest", required=True)
    ap.add_argument("--terrain-filter", default="")
    ap.add_argument("--horizontal-scale", type=float, default=None)
    ap.add_argument("--vertical-scale", type=float, default=None)
    ap.add_argument("--keep-existing", action="store_true")
    return ap.parse_args(args)


_cli_args = parse_blender_args()
if _cli_args is not None:
    import_i76_manifest(
        _cli_args.manifest,
        terrain_filter=_cli_args.terrain_filter,
        horizontal_scale_override=_cli_args.horizontal_scale,
        vertical_scale_override=_cli_args.vertical_scale,
        clear_existing=not _cli_args.keep_existing,
    )
