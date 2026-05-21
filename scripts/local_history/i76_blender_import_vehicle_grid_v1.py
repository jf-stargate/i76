"""
i76_blender_import_vehicle_grid_v1.py

Blender utility script for importing many Interstate '76 vehicle OBJ exports and
placing them in a spaced inspection grid.

Expected input directory shape from i76_binary_geo_modeller_v13.py:

  scratch_data/i76_binary_geo_modeller_v13_piranha_light_alpha/
    vehicle_export_summary.tsv
    vppirna1.vcf/
      vppirna1.vcf.obj
      vppirna1.vcf.mtl
      blender_apply_i76_material_settings.py
      textures/
    ...

This script searches recursively for vehicle OBJ files, imports them, places each
vehicle at one grid cell, and optionally adds labels. It skips OBJ files under
sobj_auxiliary by default.

Usage in Blender:
  1. Open Blender.
  2. Scripting tab -> Open this file.
  3. Set ROOT_DIR below to the export directory containing all vehicle folders.
  4. Run Script.

Notes:
  * Blender 4.x uses bpy.ops.wm.obj_import.
  * Blender 2.8/3.x usually uses bpy.ops.import_scene.obj.
  * The script tries both.
"""

from __future__ import annotations

import math
import os
import re
from pathlib import Path
from typing import Iterable, List, Optional, Sequence, Tuple

import bpy
from mathutils import Vector


# -----------------------------------------------------------------------------
# User configuration
# -----------------------------------------------------------------------------

# Change this to the output directory containing all exported vehicle folders.
ROOT_DIR = "/media/stargate-remote/prj/i76/scratch_data/i76_binary_geo_modeller_v13_all_vehicles"

# Import every OBJ found recursively. If False, only imports OBJ files whose
# parent folder looks like a vehicle folder, e.g. *.vcf.
RECURSIVE = True

# Skip VDF SOBJ auxiliary exports so the grid shows only main vehicle bodies.
SKIP_SOBJ_AUXILIARY = True

# Grid layout. If COLUMNS is None, the script chooses ceil(sqrt(vehicle_count)).
COLUMNS: Optional[int] = None

# Distance between vehicle origins. Use a large value because I76 units are not
# normalized to Blender meters.
GRID_SPACING_X = 900.0
GRID_SPACING_Y = 650.0

# Optional per-object scale after import.
IMPORT_SCALE = 1.0

# Rotate imported vehicle roots if desired. Leave zero if the exporter orientation
# is already suitable.
ROTATION_EULER_DEGREES = (0.0, 0.0, 0.0)

# Add text labels above/near vehicles.
ADD_LABELS = True
LABEL_SIZE = 36.0
LABEL_Z_OFFSET = 120.0

# Apply per-vehicle generated material settings script if present. This is useful
# for alpha-clipped light overlays from v13.
RUN_VEHICLE_MATERIAL_SCRIPT = True

# Set image texture interpolation to Closest globally after import. This avoids
# bilinear bleed on low-resolution indexed textures.
FORCE_CLOSEST_TEXTURES = True

# Set material blend/clipping options for any material that has an alpha texture.
FORCE_ALPHA_CLIP_FOR_ALPHA_IMAGES = True

# Clear existing scene before importing.
CLEAR_SCENE = True

# Create one collection per vehicle plus a top-level collection.
CREATE_COLLECTIONS = True

# Save the file after import. Leave empty to avoid saving.
SAVE_AS_BLEND = ""


# -----------------------------------------------------------------------------
# Helpers
# -----------------------------------------------------------------------------

def safe_name(s: str) -> str:
    base = s.replace("\\", "/").split("/")[-1]
    return re.sub(r"[^A-Za-z0-9._+\-]+", "_", base) or "unnamed"


def find_vehicle_objs(root: Path) -> List[Path]:
    if not root.exists():
        raise FileNotFoundError(f"ROOT_DIR does not exist: {root}")

    if RECURSIVE:
        candidates = sorted(root.rglob("*.obj"), key=lambda p: str(p).lower())
    else:
        candidates = sorted(root.glob("*.vcf/*.obj"), key=lambda p: str(p).lower())

    out: List[Path] = []
    for obj in candidates:
        parts_lower = [p.lower() for p in obj.parts]
        if SKIP_SOBJ_AUXILIARY and "sobj_auxiliary" in parts_lower:
            continue
        # Avoid importing random diagnostic OBJ files if any exist. Vehicle exports
        # normally live directly inside a *.vcf folder and have a matching MTL.
        if obj.name.startswith("."):
            continue
        out.append(obj)
    return out


def clear_scene() -> None:
    bpy.ops.object.select_all(action="SELECT")
    bpy.ops.object.delete()

    # Remove orphan collections except master scene collection children are removed
    # by unlinking below.
    for coll in list(bpy.data.collections):
        if coll.users == 0:
            bpy.data.collections.remove(coll)


def ensure_collection(name: str, parent: Optional[bpy.types.Collection] = None) -> bpy.types.Collection:
    coll = bpy.data.collections.get(name)
    if coll is None:
        coll = bpy.data.collections.new(name)
    if parent is None:
        if coll.name not in bpy.context.scene.collection.children:
            try:
                bpy.context.scene.collection.children.link(coll)
            except RuntimeError:
                pass
    else:
        if coll.name not in parent.children:
            try:
                parent.children.link(coll)
            except RuntimeError:
                pass
    return coll


def move_objects_to_collection(objects: Sequence[bpy.types.Object], coll: bpy.types.Collection) -> None:
    for obj in objects:
        for old in list(obj.users_collection):
            try:
                old.objects.unlink(obj)
            except RuntimeError:
                pass
        try:
            coll.objects.link(obj)
        except RuntimeError:
            pass


def import_obj(path: Path) -> List[bpy.types.Object]:
    before = set(bpy.context.scene.objects)

    # Blender 4.x built-in OBJ importer.
    try:
        bpy.ops.wm.obj_import(filepath=str(path), forward_axis="Y", up_axis="Z")
    except Exception:
        # Blender 2.8/3.x add-on OBJ importer.
        try:
            bpy.ops.import_scene.obj(filepath=str(path), axis_forward="Y", axis_up="Z")
        except Exception as ex:
            raise RuntimeError(f"OBJ import failed for {path}: {ex}") from ex

    after = set(bpy.context.scene.objects)
    imported = list(after - before)
    imported.sort(key=lambda o: o.name.lower())
    return imported


def get_bounds(objects: Sequence[bpy.types.Object]) -> Optional[Tuple[Vector, Vector]]:
    mins = Vector((float("inf"), float("inf"), float("inf")))
    maxs = Vector((float("-inf"), float("-inf"), float("-inf")))
    any_bounds = False

    depsgraph = bpy.context.evaluated_depsgraph_get()
    for obj in objects:
        if obj.type not in {"MESH", "CURVE", "FONT"}:
            continue
        eval_obj = obj.evaluated_get(depsgraph)
        for corner in eval_obj.bound_box:
            w = eval_obj.matrix_world @ Vector(corner)
            mins.x = min(mins.x, w.x)
            mins.y = min(mins.y, w.y)
            mins.z = min(mins.z, w.z)
            maxs.x = max(maxs.x, w.x)
            maxs.y = max(maxs.y, w.y)
            maxs.z = max(maxs.z, w.z)
            any_bounds = True

    if not any_bounds:
        return None
    return mins, maxs


def translate_objects(objects: Sequence[bpy.types.Object], delta: Vector) -> None:
    for obj in objects:
        obj.location += delta


def set_object_roots_transform(objects: Sequence[bpy.types.Object]) -> None:
    rx, ry, rz = [math.radians(v) for v in ROTATION_EULER_DEGREES]
    for obj in objects:
        obj.scale = (obj.scale.x * IMPORT_SCALE, obj.scale.y * IMPORT_SCALE, obj.scale.z * IMPORT_SCALE)
        obj.rotation_euler.rotate_axis("X", rx)
        obj.rotation_euler.rotate_axis("Y", ry)
        obj.rotation_euler.rotate_axis("Z", rz)


def add_label(label: str, location: Vector, collection: Optional[bpy.types.Collection]) -> bpy.types.Object:
    bpy.ops.object.text_add(location=location)
    obj = bpy.context.object
    obj.name = "label_" + safe_name(label)
    obj.data.name = obj.name + "_curve"
    obj.data.body = label
    obj.data.align_x = "CENTER"
    obj.data.align_y = "CENTER"
    obj.data.size = LABEL_SIZE
    obj.rotation_euler[0] = math.radians(90.0)
    if collection is not None:
        move_objects_to_collection([obj], collection)
    return obj


def apply_generated_material_script(vehicle_dir: Path) -> None:
    script = vehicle_dir / "blender_apply_i76_material_settings.py"
    if not script.exists():
        return
    ns = {"bpy": bpy, "__file__": str(script)}
    code = script.read_text(encoding="utf-8", errors="replace")
    exec(compile(code, str(script), "exec"), ns, ns)


def image_has_alpha(image: bpy.types.Image) -> bool:
    # Fast metadata-level check. Blender loads PNG alpha as depth 32 or channels 4.
    try:
        if image.depth in {32, 64, 128}:
            return True
    except Exception:
        pass
    try:
        return image.channels == 4
    except Exception:
        return False


def fix_material_display() -> None:
    for mat in bpy.data.materials:
        if not mat.use_nodes:
            continue
        alpha_candidate = False
        for node in mat.node_tree.nodes:
            if node.bl_idname == "ShaderNodeTexImage" and getattr(node, "image", None) is not None:
                if FORCE_CLOSEST_TEXTURES:
                    node.interpolation = "Closest"
                    node.extension = "CLIP"
                if image_has_alpha(node.image):
                    alpha_candidate = True
        if FORCE_ALPHA_CLIP_FOR_ALPHA_IMAGES and alpha_candidate:
            mat.blend_method = "CLIP"
            mat.use_screen_refraction = False
            mat.show_transparent_back = True
            try:
                mat.alpha_threshold = 0.5
            except Exception:
                pass


def make_camera_and_light(imported_objects: Sequence[bpy.types.Object]) -> None:
    bounds = get_bounds(imported_objects)
    if bounds is None:
        return
    mins, maxs = bounds
    center = (mins + maxs) * 0.5
    extent = max(maxs.x - mins.x, maxs.y - mins.y, maxs.z - mins.z, 1.0)

    bpy.ops.object.light_add(type="SUN", location=(center.x, center.y, center.z + extent))
    sun = bpy.context.object
    sun.name = "inspection_sun"
    sun.data.energy = 3.0
    sun.rotation_euler = (math.radians(45.0), 0.0, math.radians(35.0))

    bpy.ops.object.camera_add(location=(center.x - extent * 0.8, center.y - extent * 1.4, center.z + extent * 0.85))
    cam = bpy.context.object
    cam.name = "inspection_camera"
    direction = center - cam.location
    cam.rotation_euler = direction.to_track_quat("-Z", "Y").to_euler()
    cam.data.lens = 35
    bpy.context.scene.camera = cam


def main() -> None:
    root = Path(ROOT_DIR).expanduser().resolve()
    objs = find_vehicle_objs(root)
    if not objs:
        raise RuntimeError(f"No OBJ files found under {root}")

    if CLEAR_SCENE:
        clear_scene()

    top_collection = ensure_collection("I76 Vehicle Inspection Grid") if CREATE_COLLECTIONS else None
    columns = COLUMNS or int(math.ceil(math.sqrt(len(objs))))

    all_imported: List[bpy.types.Object] = []
    print(f"Importing {len(objs)} vehicle OBJ files from {root}")

    for i, obj_path in enumerate(objs):
        vehicle_name = obj_path.parent.name
        row = i // columns
        col = i % columns
        target_origin = Vector((col * GRID_SPACING_X, -row * GRID_SPACING_Y, 0.0))

        print(f"[{i + 1}/{len(objs)}] {obj_path}")
        imported = import_obj(obj_path)
        if not imported:
            print(f"  warning: no objects imported for {obj_path}")
            continue

        set_object_roots_transform(imported)

        # Move imported object bounds center to the grid cell, keeping bottom near Z=0.
        bounds = get_bounds(imported)
        if bounds is not None:
            mins, maxs = bounds
            center_xy = Vector(((mins.x + maxs.x) * 0.5, (mins.y + maxs.y) * 0.5, 0.0))
            delta = Vector((target_origin.x - center_xy.x, target_origin.y - center_xy.y, -mins.z))
            translate_objects(imported, delta)

        vehicle_collection = None
        if CREATE_COLLECTIONS and top_collection is not None:
            vehicle_collection = ensure_collection(safe_name(vehicle_name), top_collection)
            move_objects_to_collection(imported, vehicle_collection)

        if RUN_VEHICLE_MATERIAL_SCRIPT:
            apply_generated_material_script(obj_path.parent)

        if ADD_LABELS:
            bounds = get_bounds(imported)
            if bounds is not None:
                mins, maxs = bounds
                label_loc = Vector(((mins.x + maxs.x) * 0.5, mins.y - GRID_SPACING_Y * 0.25, maxs.z + LABEL_Z_OFFSET))
            else:
                label_loc = target_origin + Vector((0.0, -GRID_SPACING_Y * 0.25, LABEL_Z_OFFSET))
            label_obj = add_label(vehicle_name, label_loc, vehicle_collection)
            all_imported.append(label_obj)

        all_imported.extend(imported)

    fix_material_display()
    make_camera_and_light(all_imported)

    bpy.context.scene.render.engine = "BLENDER_EEVEE_NEXT" if "BLENDER_EEVEE_NEXT" in [e.identifier for e in bpy.types.RenderSettings.bl_rna.properties["engine"].enum_items] else "BLENDER_EEVEE"
    bpy.context.scene.unit_settings.system = "METRIC"

    if SAVE_AS_BLEND:
        save_path = Path(SAVE_AS_BLEND).expanduser().resolve()
        save_path.parent.mkdir(parents=True, exist_ok=True)
        bpy.ops.wm.save_as_mainfile(filepath=str(save_path))
        print(f"Saved {save_path}")

    print(f"Done. Imported {len(objs)} vehicle OBJ files.")


if __name__ == "__main__":
    main()
