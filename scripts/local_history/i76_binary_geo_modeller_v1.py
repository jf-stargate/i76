#!/usr/bin/env python3
"""
i76_binary_geo_modeller_v1.py

First-pass Interstate '76 binary-faithful vehicle GEO modeller.

This is deliberately separate from the older ad-hoc OBJ exporter.  It reuses
validated resource/parsing helpers from i76_vehicle_geo_obj_export_v20.py, but
constructs an explicit runtime-like intermediate model before writing OBJ/MTL.

Binary evidence implemented from cgpt_i76exe_export_geo_binary_modeller_deeptrace_v1:
  * construct_geometry_from_geo_buffer builds a compact runtime GEO object:
      +0x04 vertex_count, +0x08 normal_count, +0x0c vertices,
      +0x10 normals, +0x14 first_section.
  * Runtime section records have section metadata at +0x04..+0x3f and 0x10-byte
    corner records beginning at +0x40.
  * Runtime corner layout is:
      +0x00 vertex_index
      +0x04 normal_or_lighting_index
      +0x08 raw_u
      +0x0c raw_v
  * build_lit_geo_render_records_from_sections walks section corners in reverse
    order when filling 0x18-byte render vertices.
  * Render vertex layout is treated as:
      x, y, z, raw_u, raw_v, lighting_value
  * The game submits the whole polygon vertex list to submit_lit_textured_polygon_to_renderer;
    it does not pre-triangulate GEO n-gons in the construction/build path.

OBJ export is only a view of the runtime-equivalent structure.  Debug JSON/TSV
are the primary output for validation.
"""

from __future__ import annotations

import argparse
import importlib.util
import json
import math
import shutil
import subprocess
import sys
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple


@dataclass
class RuntimeCorner:
    source_corner_index: int
    vertex_index: int
    normal_index: int
    raw_u: float
    raw_v: float


@dataclass
class RuntimeSection:
    runtime_section_index: int
    source_face_index: int
    corner_count: int
    raw_rgb: Tuple[int, int, int]
    palette_index: Optional[int]
    plane: Tuple[float, float, float, float]
    flags: Tuple[int, int, int]
    texture_slot_raw: str
    texture_slot_normalized: str
    texture_resource_name: str
    material_name: str
    corners_original_order: List[RuntimeCorner]
    corners_render_order: List[RuntimeCorner]
    centroid_local: Tuple[float, float, float]


@dataclass
class RenderVertex:
    render_corner_index: int
    source_corner_index: int
    vertex_index: int
    normal_index: int
    x: float
    y: float
    z: float
    raw_u: float
    raw_v: float
    lighting_source: str


@dataclass
class RenderRecord:
    part: str
    geo: str
    runtime_section_index: int
    source_face_index: int
    material_name: str
    texture_resource_name: str
    corner_count: int
    submitted_as_polygon: bool
    vertices: List[RenderVertex]


def load_module(path: Path, module_name: str):
    spec = importlib.util.spec_from_file_location(module_name, str(path))
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not import {module_name} from {path}")
    mod = importlib.util.module_from_spec(spec)
    sys.modules[module_name] = mod
    spec.loader.exec_module(mod)
    return mod


def clean_tsv(v) -> str:
    return str(v).replace("\t", " ").replace("\n", " ").replace("\r", " ")


def write_tsv(path: Path, rows: List[Dict[str, object]], fields: List[str]) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(fields) + "\n")
        for row in rows:
            f.write("\t".join(clean_tsv(row.get(field, "")) for field in fields) + "\n")


def safe_float_tuple(v):
    return tuple(float(x) for x in v)


def centroid_for_refs(vertices: List[Tuple[float, float, float]], refs) -> Tuple[float, float, float]:
    if not refs:
        return (0.0, 0.0, 0.0)
    sx = sy = sz = 0.0
    n = 0
    for ref in refs:
        if 0 <= ref.vertex_index < len(vertices):
            x, y, z = vertices[ref.vertex_index]
            sx += x
            sy += y
            sz += z
            n += 1
    if n == 0:
        return (0.0, 0.0, 0.0)
    return (sx / n, sy / n, sz / n)


def resolve_face_material(helper, resolver, idx, geo_asset, face, tmt_assets, map_assets, map_ref_stems,
                          direct_map_prefer: str, normalized_slot_swap: Dict[str, str]):
    raw_slot = face.texture_name or f"COLOR_{face.color[0]:02x}{face.color[1]:02x}{face.color[2]:02x}"
    resolved, kind, confidence, evidence, norm = helper.resolve_material_asset(
        resolver, idx, geo_asset, raw_slot, tmt_assets, map_assets, map_ref_stems,
        direct_map_prefer, normalized_slot_swap,
    )
    texture_asset = None
    if resolved:
        if resolved.ext == "tmt":
            texture_asset = helper.first_texture_from_tmt(resolver, idx, resolved)
            mat_name = f"TMT_{helper.safe_name(resolved.name)}"
        else:
            texture_asset = resolved
            mat_name = f"TEX_{helper.safe_name(resolved.name)}"
    else:
        mat_name = f"UNRES_{helper.safe_name(norm or raw_slot)}"
    return {
        "raw_slot": raw_slot,
        "normalized_slot": norm,
        "resolved": resolved,
        "resolved_kind": kind if resolved else "unresolved",
        "resolved_name": resolved.name if resolved else "",
        "resolved_asset_id": resolved.asset_id if resolved else "",
        "texture_asset": texture_asset,
        "texture_resource_name": texture_asset.name if texture_asset else "",
        "texture_asset_id": texture_asset.asset_id if texture_asset else "",
        "material_name": mat_name,
        "confidence": confidence if resolved else "none",
        "evidence": evidence if resolved else "unresolved",
    }


def build_runtime_sections(helper, resolver, idx, geo_asset, mesh, tmt_assets, map_assets, map_ref_stems,
                           direct_map_prefer: str, normalized_slot_swap: Dict[str, str], palette_rgb: Optional[bytes]):
    sections: List[RuntimeSection] = []
    material_infos: Dict[int, Dict[str, object]] = {}
    for si, face in enumerate(mesh.faces):
        mat = resolve_face_material(
            helper, resolver, idx, geo_asset, face, tmt_assets, map_assets, map_ref_stems,
            direct_map_prefer, normalized_slot_swap,
        )
        material_infos[si] = mat
        corners = [
            RuntimeCorner(
                source_corner_index=ci,
                vertex_index=int(ref.vertex_index),
                normal_index=int(ref.normal_index),
                raw_u=float(ref.u),
                raw_v=float(ref.v),
            )
            for ci, ref in enumerate(face.refs)
        ]
        pal_idx = helper.nearest_palette_index_rgb(palette_rgb, face.color) if palette_rgb else None
        sections.append(RuntimeSection(
            runtime_section_index=si,
            source_face_index=int(face.index),
            corner_count=len(corners),
            raw_rgb=tuple(int(x) for x in face.color),
            palette_index=pal_idx,
            plane=safe_float_tuple(face.surface_normal),
            flags=tuple(int(x) for x in face.surface_flags),
            texture_slot_raw=str(mat["raw_slot"]),
            texture_slot_normalized=str(mat["normalized_slot"]),
            texture_resource_name=str(mat["texture_resource_name"]),
            material_name=str(mat["material_name"]),
            corners_original_order=corners,
            corners_render_order=list(reversed(corners)),
            centroid_local=centroid_for_refs(mesh.vertices, face.refs),
        ))
    return sections, material_infos


def build_render_records(helper, part_transform, geo_asset, mesh, sections: List[RuntimeSection]):
    records: List[RenderRecord] = []
    transformed_positions = [helper.transform_point(part_transform, p) for p in mesh.vertices]
    # Keep transformed normals for future lighting validation.  The build path indexes
    # lighting by corner.normal_index; it does not substitute vertex_index.
    _transformed_normals = [helper.transform_normal(part_transform, n) for n in mesh.normals]

    for sec in sections:
        rv: List[RenderVertex] = []
        for ri, corner in enumerate(sec.corners_render_order):
            if 0 <= corner.vertex_index < len(transformed_positions):
                x, y, z = transformed_positions[corner.vertex_index]
            else:
                x = y = z = 0.0
            rv.append(RenderVertex(
                render_corner_index=ri,
                source_corner_index=corner.source_corner_index,
                vertex_index=corner.vertex_index,
                normal_index=corner.normal_index,
                x=float(x), y=float(y), z=float(z),
                raw_u=corner.raw_u,
                raw_v=corner.raw_v,
                lighting_source="normal_index",
            ))
        records.append(RenderRecord(
            part=part_transform.name,
            geo=geo_asset.name,
            runtime_section_index=sec.runtime_section_index,
            source_face_index=sec.source_face_index,
            material_name=sec.material_name,
            texture_resource_name=sec.texture_resource_name,
            corner_count=sec.corner_count,
            submitted_as_polygon=True,
            vertices=rv,
        ))
    return records


def determinant_basis(t) -> float:
    r = t.world_right
    u = t.world_up
    f = t.world_forward
    return (
        r[0] * (u[1] * f[2] - u[2] * f[1]) -
        u[0] * (r[1] * f[2] - r[2] * f[1]) +
        f[0] * (r[1] * u[2] - r[2] * u[1])
    )


def add_material(helper, resolver, idx, tex_dir: Path, materials: Dict[str, Dict[str, object]], mat_info,
                 face_color, palette_rgb, export_textures: bool, vqm_layout: str, texture_written: Dict[str, str],
                 textured_kd_mode: str, flat_color_mode: str):
    name = str(mat_info["material_name"])
    if name in materials:
        return
    texture_asset = mat_info.get("texture_asset")
    is_textured = texture_asset is not None
    geo_face_color = tuple(int(x) for x in face_color)
    diffuse = geo_face_color
    diffuse_source = "geo_face_rgb_direct"
    palette_index = None

    if is_textured:
        if textured_kd_mode == "white":
            diffuse = (255, 255, 255)
            diffuse_source = "textured_kd_white_preserve_geo_color"
        elif textured_kd_mode == "palette-nearest":
            palette_index = helper.nearest_palette_index_rgb(palette_rgb, geo_face_color) if palette_rgb else None
            pal = helper.palette_rgb_at(palette_rgb, palette_index)
            if pal:
                diffuse = pal
                diffuse_source = "textured_palette_nearest_to_geo_face_rgb"
    elif str(mat_info["raw_slot"]).startswith("COLOR_") and flat_color_mode in {"auto", "palette-nearest"}:
        palette_index = helper.nearest_palette_index_rgb(palette_rgb, geo_face_color) if palette_rgb else None
        pal = helper.palette_rgb_at(palette_rgb, palette_index)
        if pal:
            diffuse = pal
            diffuse_source = "palette_nearest_to_geo_face_rgb"

    map_kd = ""
    if export_textures and texture_asset:
        map_kd = helper.export_texture_for_asset(resolver, idx, texture_asset, tex_dir, texture_written, palette_rgb, vqm_layout)

    materials[name] = {
        "name": name,
        "raw_slot": mat_info["raw_slot"],
        "normalized_slot": mat_info["normalized_slot"],
        "resolved_kind": mat_info["resolved_kind"],
        "resolved_name": mat_info["resolved_name"],
        "resolved_asset_id": mat_info["resolved_asset_id"],
        "texture_asset_name": mat_info["texture_resource_name"],
        "texture_asset_id": mat_info["texture_asset_id"],
        "confidence": mat_info["confidence"],
        "evidence": mat_info["evidence"],
        "geo_face_color": geo_face_color,
        "diffuse_color": diffuse,
        "diffuse_source": diffuse_source,
        "palette_index": "" if palette_index is None else palette_index,
        "map_kd": map_kd,
    }


def write_runtime_obj_mtl(helper, resolver, idx, vehicle_dir: Path, vehicle_name: str, part_models: List[Dict[str, object]],
                          palette_rgb: Optional[bytes], export_textures: bool, vqm_layout: str,
                          textured_kd_mode: str, flat_color_mode: str, obj_v_mode: str):
    obj_path = vehicle_dir / f"{helper.safe_name(vehicle_name)}.obj"
    mtl_path = vehicle_dir / f"{helper.safe_name(vehicle_name)}.mtl"
    tex_dir = vehicle_dir / "textures"
    if export_textures:
        tex_dir.mkdir(exist_ok=True)

    materials: Dict[str, Dict[str, object]] = {}
    texture_written: Dict[str, str] = {}
    face_rows = []
    corner_rows = []

    v_base = 1
    vt_base = 1
    vn_base = 1

    with obj_path.open("w", encoding="utf-8") as obj:
        obj.write(f"# Interstate '76 binary runtime GEO model view: {vehicle_name}\n")
        obj.write("# Face corner order follows build_lit_geo_render_records_from_sections: reversed runtime corner order.\n")
        obj.write("# Runtime UVs are raw_u/raw_v; OBJ vt may convert V for Blender display depending on --obj-v-mode.\n")
        obj.write(f"mtllib {mtl_path.name}\n\n")

        for pm in part_models:
            mesh = pm["mesh"]
            part_transform = pm["part_transform"]
            geo_asset = pm["geo_asset"]
            sections: List[RuntimeSection] = pm["sections"]
            material_infos = pm["material_infos"]

            obj.write(f"o {helper.safe_name(part_transform.name)}_{helper.safe_name(geo_asset.name)}\n")
            obj.write(f"# determinant(world_basis)={determinant_basis(part_transform):.9g}\n")
            obj.write(f"# source={part_transform.source} parent={part_transform.parent_name}\n")

            for p in mesh.vertices:
                x, y, z = helper.transform_point(part_transform, p)
                obj.write(f"v {x:.8g} {y:.8g} {z:.8g}\n")
            for n in mesh.normals:
                nx, ny, nz = helper.transform_normal(part_transform, n)
                obj.write(f"vn {nx:.8g} {ny:.8g} {nz:.8g}\n")

            vt_indices_by_section: Dict[int, List[int]] = {}
            for sec in sections:
                vt_row = []
                for corner in sec.corners_render_order:
                    vt_v = corner.raw_v if obj_v_mode == "raw" else 1.0 - corner.raw_v
                    obj.write(f"vt {corner.raw_u:.8g} {vt_v:.8g}\n")
                    vt_row.append(vt_base)
                    vt_base += 1
                vt_indices_by_section[sec.runtime_section_index] = vt_row

            for sec in sections:
                face = mesh.faces[sec.runtime_section_index]
                mat_info = material_infos[sec.runtime_section_index]
                add_material(helper, resolver, idx, tex_dir, materials, mat_info, face.color, palette_rgb,
                             export_textures, vqm_layout, texture_written, textured_kd_mode, flat_color_mode)
                obj.write(f"usemtl {sec.material_name}\n")
                refs = []
                for ri, corner in enumerate(sec.corners_render_order):
                    vi = v_base + corner.vertex_index
                    ni = vn_base + corner.normal_index if 0 <= corner.normal_index < len(mesh.normals) else vn_base
                    vti = vt_indices_by_section[sec.runtime_section_index][ri]
                    refs.append(f"{vi}/{vti}/{ni}")
                    corner_rows.append({
                        "vehicle": vehicle_name,
                        "part": part_transform.name,
                        "geo": geo_asset.name,
                        "runtime_section_index": sec.runtime_section_index,
                        "source_face_index": sec.source_face_index,
                        "render_corner_index": ri,
                        "source_corner_index": corner.source_corner_index,
                        "vertex_index": corner.vertex_index,
                        "normal_index": corner.normal_index,
                        "raw_u": corner.raw_u,
                        "raw_v": corner.raw_v,
                        "obj_v": corner.raw_v if obj_v_mode == "raw" else 1.0 - corner.raw_v,
                        "order_rule": "reversed_from_runtime_section_corner_order",
                    })
                obj.write("f " + " ".join(refs) + "\n")
                face_rows.append({
                    "vehicle": vehicle_name,
                    "part": part_transform.name,
                    "geo": geo_asset.name,
                    "runtime_section_index": sec.runtime_section_index,
                    "source_face_index": sec.source_face_index,
                    "corner_count": sec.corner_count,
                    "material": sec.material_name,
                    "raw_slot": sec.texture_slot_raw,
                    "normalized_slot": sec.texture_slot_normalized,
                    "texture_resource": sec.texture_resource_name,
                    "palette_index": "" if sec.palette_index is None else sec.palette_index,
                    "raw_rgb": sec.raw_rgb,
                    "centroid_local": sec.centroid_local,
                    "determinant_world_basis": determinant_basis(part_transform),
                    "polygon_submission": "whole_n_gon_no_pretriangulation",
                    "corner_order": "runtime_reversed",
                })
            v_base += len(mesh.vertices)
            vn_base += len(mesh.normals)
            obj.write("\n")

    with mtl_path.open("w", encoding="utf-8") as mtl:
        mtl.write(f"# Interstate '76 binary runtime material view: {vehicle_name}\n")
        for name, mat in materials.items():
            r, g, b = mat["diffuse_color"]
            mtl.write(f"\nnewmtl {name}\n")
            mtl.write(f"Kd {r/255.0:.6f} {g/255.0:.6f} {b/255.0:.6f}\n")
            mtl.write("Ka 0.000000 0.000000 0.000000\n")
            mtl.write("Ks 0.000000 0.000000 0.000000\n")
            mtl.write("d 1.0\n")
            if mat.get("map_kd"):
                mtl.write(f"map_Kd {mat['map_kd']}\n")

    return obj_path, mtl_path, materials, face_rows, corner_rows


def write_debug_outputs(vehicle_dir: Path, vehicle_name: str, part_models: List[Dict[str, object]], render_records: List[RenderRecord],
                        materials: Dict[str, Dict[str, object]], face_rows, corner_rows, obj_path: Path, mtl_path: Path):
    runtime_parts = []
    section_json = []
    for pm in part_models:
        pt = pm["part_transform"]
        mesh = pm["mesh"]
        geo_asset = pm["geo_asset"]
        runtime_parts.append({
            "part": pt.name,
            "parent": pt.parent_name,
            "source": pt.source,
            "geo": geo_asset.name,
            "vertex_count": len(mesh.vertices),
            "normal_count": len(mesh.normals),
            "section_count": len(pm["sections"]),
            "world_right": pt.world_right,
            "world_up": pt.world_up,
            "world_forward": pt.world_forward,
            "world_position": pt.world_position,
            "world_basis_determinant": determinant_basis(pt),
        })
        for sec in pm["sections"]:
            d = asdict(sec)
            d["part"] = pt.name
            d["geo"] = geo_asset.name
            section_json.append(d)

    (vehicle_dir / "vehicle_model_runtime.json").write_text(json.dumps({
        "vehicle": vehicle_name,
        "obj": obj_path.name,
        "mtl": mtl_path.name,
        "binary_rules": {
            "runtime_corner_stride": "0x10",
            "runtime_corner_layout": ["vertex_index", "normal_index", "raw_u", "raw_v"],
            "render_corner_order": "reverse section corner order",
            "render_vertex_stride": "0x18",
            "render_vertex_layout": ["x", "y", "z", "raw_u", "raw_v", "lighting"],
            "polygon_submission": "whole polygon to submit_lit_textured_polygon_to_renderer",
            "normal_lighting_index": "corner.normal_index",
        },
        "parts": runtime_parts,
    }, indent=2, sort_keys=True), encoding="utf-8")

    (vehicle_dir / "geo_runtime_sections.json").write_text(json.dumps(section_json, indent=2, sort_keys=True), encoding="utf-8")
    (vehicle_dir / "render_records.json").write_text(json.dumps([asdict(r) for r in render_records], indent=2, sort_keys=True), encoding="utf-8")

    write_tsv(vehicle_dir / "face_mapping.tsv", face_rows, [
        "vehicle", "part", "geo", "runtime_section_index", "source_face_index", "corner_count",
        "material", "raw_slot", "normalized_slot", "texture_resource", "palette_index", "raw_rgb",
        "centroid_local", "determinant_world_basis", "polygon_submission", "corner_order",
    ])
    write_tsv(vehicle_dir / "corner_mapping.tsv", corner_rows, [
        "vehicle", "part", "geo", "runtime_section_index", "source_face_index", "render_corner_index",
        "source_corner_index", "vertex_index", "normal_index", "raw_u", "raw_v", "obj_v", "order_rule",
    ])
    write_tsv(vehicle_dir / "material_binding.tsv", list(materials.values()), [
        "name", "raw_slot", "normalized_slot", "resolved_kind", "resolved_name", "resolved_asset_id",
        "texture_asset_name", "texture_asset_id", "confidence", "evidence", "geo_face_color",
        "diffuse_color", "diffuse_source", "palette_index", "map_kd",
    ])


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--zfs", required=True, type=Path)
    ap.add_argument("--zix", type=Path)
    ap.add_argument("--resolver", required=True, type=Path, help="Path to i76_vehicle_texture_slot_resolver_v5.py")
    ap.add_argument("--helper-exporter", type=Path, default=Path("scripts/i76_vehicle_geo_obj_export_v20.py"), help="Path to i76_vehicle_geo_obj_export_v20.py for validated parsers/helpers")
    ap.add_argument("--out", required=True, type=Path)
    ap.add_argument("--overwrite", action="store_true")
    ap.add_argument("--vehicle", action="append", default=[])
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--damage-state", type=int, default=0, choices=[0, 1, 2, 3])
    ap.add_argument("--export-textures", action="store_true")
    ap.add_argument("--palette-file", type=Path, default=None)
    ap.add_argument("--palette-scale", choices=["auto", "raw", "x4"], default="auto")
    ap.add_argument("--flat-color-mode", choices=["auto", "direct", "palette-nearest"], default="auto")
    ap.add_argument("--vqm-layout", choices=["yx", "yx_flipx", "yx_flipy", "yx_flipx_flipy", "xy", "xy_flipx", "xy_flipy", "xy_flipx_flipy"], default="yx")
    ap.add_argument("--direct-map-prefer", choices=["current", "vqm", "m16"], default="vqm")
    ap.add_argument("--textured-kd-mode", choices=["white", "geo-direct", "palette-nearest"], default="white")
    ap.add_argument("--obj-v-mode", choices=["blender", "raw"], default="blender", help="blender writes OBJ vt V as 1-raw_v; raw writes raw_v")
    ap.add_argument("--vdf-sobj-mode", choices=["skip", "separate", "include"], default="separate")
    ap.add_argument("--swap-normalized-slot", action="append", default=[])
    ap.add_argument("--tar", action="store_true")
    ap.add_argument("--tar-out-dir", type=Path, default=None)
    args = ap.parse_args()

    if not args.all and not args.vehicle:
        raise SystemExit("Specify --vehicle <name> or --all")

    helper = load_module(args.helper_exporter, "i76_vehicle_geo_obj_export_v20_helper")
    resolver = helper.load_resolver(args.resolver)
    normalized_slot_swap = helper.parse_slot_swap_specs(args.swap_normalized_slot)
    palette_rgb = helper.load_palette_file(args.palette_file, args.palette_scale)

    if args.out.exists():
        if not args.overwrite:
            raise FileExistsError(f"output exists: {args.out}; use --overwrite")
        shutil.rmtree(args.out)
    args.out.mkdir(parents=True, exist_ok=True)

    wanted_exts = {"vcf", "vdf", "vtf", "wdf", "gdf", "pix", "pak", "tmt", "map", "m16", "vqm", "cbk", "geo"}
    header, records = resolver.parse_zfs_records(args.zfs)
    payloads, errors = resolver.decompress_records(args.zfs, records, wanted_exts)
    idx, warnings = resolver.build_asset_index(records, payloads, None)

    vcf_assets = sorted([a for a in idx.assets if a.ext == "vcf" and a.source == "top_level"], key=lambda a: a.name.lower())
    filters = [v.lower().replace(".vcf", "") for v in args.vehicle]
    if not args.all:
        vcf_assets = [a for a in vcf_assets if any(f in a.name.lower().replace(".vcf", "") for f in filters)]

    summary_rows = []
    for vcf in vcf_assets:
        vcf_data = idx.payloads.get(vcf.asset_id, b"")
        vdf, vtf, _wdfs, _gdfs, raw_vdf_ref, raw_vtf_ref, vcf_ref_notes = helper.parse_vcf_refs_with_vtf_aliases(resolver, vcf, vcf_data, idx)
        if not vdf or not vtf:
            summary_rows.append({"vehicle": vcf.name, "status": "missing_vdf_or_vtf", "vdf": raw_vdf_ref, "vtf": raw_vtf_ref, "parts": 0, "sections": 0, "render_records": 0, "notes": vcf_ref_notes})
            continue

        transforms, transform_warnings = helper.parse_vdf_geometry_transforms(idx.payloads.get(vdf.asset_id, b""), args.damage_state)
        tmt_assets, map_assets = resolver.parse_vtf_slots(vtf, idx.payloads.get(vtf.asset_id, b""), idx)
        map_ref_stems = resolver.parse_vtf_map_ref_stems(vtf, idx.payloads.get(vtf.asset_id, b""), idx)

        part_models = []
        render_records: List[RenderRecord] = []
        parse_errors = []
        separated_sobj = 0
        skipped_sobj = 0
        seen = set()

        for pt in transforms:
            if pt.name.upper() in {"WORLD", "NULL"}:
                continue
            geo_asset = idx.resolve(pt.name, "geo", source=vdf)
            if not geo_asset:
                if pt.source != "SOBJ":
                    parse_errors.append(f"missing GEO for {pt.name}")
                continue
            key = (pt.name.upper(), geo_asset.asset_id)
            if key in seen:
                continue
            seen.add(key)
            mesh = helper.parse_geo(idx.payloads.get(geo_asset.asset_id, b""))
            is_aux = (pt.source == "SOBJ") or helper.is_shadow_object_name(pt.name) or helper.is_shadow_object_name(geo_asset.name) or helper.is_shadow_object_name(mesh.name)
            if is_aux and args.vdf_sobj_mode == "skip":
                skipped_sobj += 1
                continue
            if is_aux and args.vdf_sobj_mode == "separate":
                separated_sobj += 1
                continue
            sections, material_infos = build_runtime_sections(
                helper, resolver, idx, geo_asset, mesh, tmt_assets, map_assets, map_ref_stems,
                args.direct_map_prefer, normalized_slot_swap, palette_rgb,
            )
            rr = build_render_records(helper, pt, geo_asset, mesh, sections)
            render_records.extend(rr)
            part_models.append({
                "geo_asset": geo_asset,
                "mesh": mesh,
                "part_transform": pt,
                "sections": sections,
                "material_infos": material_infos,
            })

        vdir = args.out / helper.safe_name(vcf.name)
        vdir.mkdir(parents=True, exist_ok=True)
        if part_models:
            obj_path, mtl_path, materials, face_rows, corner_rows = write_runtime_obj_mtl(
                helper, resolver, idx, vdir, vcf.name, part_models, palette_rgb,
                args.export_textures, args.vqm_layout, args.textured_kd_mode,
                args.flat_color_mode, args.obj_v_mode,
            )
            write_debug_outputs(vdir, vcf.name, part_models, render_records, materials, face_rows, corner_rows, obj_path, mtl_path)
            status = "ok" if not parse_errors else "partial"
        else:
            obj_path = mtl_path = Path("")
            status = "no_geo_parts"

        summary_rows.append({
            "vehicle": vcf.name,
            "status": status,
            "vdf": vdf.name,
            "vtf": vtf.name,
            "parts": len(part_models),
            "sections": sum(len(pm["sections"]) for pm in part_models),
            "render_records": len(render_records),
            "separated_sobj_parts": separated_sobj,
            "skipped_sobj_parts": skipped_sobj,
            "obj": obj_path.relative_to(args.out).as_posix() if obj_path else "",
            "mtl": mtl_path.relative_to(args.out).as_posix() if mtl_path else "",
            "notes": "; ".join(([vcf_ref_notes] if vcf_ref_notes else []) + transform_warnings[:20] + parse_errors[:20]),
        })

    write_tsv(args.out / "vehicle_model_summary.tsv", summary_rows, [
        "vehicle", "status", "vdf", "vtf", "parts", "sections", "render_records",
        "separated_sobj_parts", "skipped_sobj_parts", "obj", "mtl", "notes",
    ])
    (args.out / "summary.json").write_text(json.dumps({
        "zfs_header": header,
        "vehicles_requested": len(vcf_assets),
        "vehicles_modelled": sum(1 for r in summary_rows if r["status"] in {"ok", "partial"}),
        "damage_state": args.damage_state,
        "vqm_layout": args.vqm_layout,
        "direct_map_prefer": args.direct_map_prefer,
        "textured_kd_mode": args.textured_kd_mode,
        "obj_v_mode": args.obj_v_mode,
        "vdf_sobj_mode": args.vdf_sobj_mode,
        "zfs_errors": len(errors),
        "pix_pak_warnings": len(warnings),
        "binary_runtime_rules": {
            "corner_order": "reversed during build_lit_geo_render_records_from_sections",
            "uv_storage": "raw GEO u/v copied to render vertices",
            "normal_lighting_index": "corner normal_index",
            "polygon_submission": "whole n-gon submitted; no construction-stage triangulation",
        },
    }, indent=2, sort_keys=True), encoding="utf-8")
    (args.out / "README.txt").write_text("""i76_binary_geo_modeller_v1 outputs a runtime-equivalent intermediate model before OBJ/MTL export.

Key outputs per vehicle:
  vehicle_model_runtime.json   Runtime-level part/model structure and binary rule summary.
  geo_runtime_sections.json    Runtime section records, original corners, and reversed render corners.
  render_records.json          0x18-byte-render-vertex equivalent records: x,y,z,raw_u,raw_v,lighting source.
  face_mapping.tsv             Source GEO face -> runtime section -> OBJ face mapping.
  corner_mapping.tsv           Source corner order -> reversed render order mapping.
  material_binding.tsv         Resolver/material/texture binding evidence.

OBJ/MTL is a view of render_records, not the source of truth.
""", encoding="utf-8")

    if args.tar:
        tar_dir = args.tar_out_dir or args.out.parent
        tar_dir.mkdir(parents=True, exist_ok=True)
        tar_path = tar_dir / (args.out.name + ".tar")
        if tar_path.exists():
            tar_path.unlink()
        subprocess.run(["tar", "-cf", str(tar_path), "-C", str(args.out.parent), args.out.name], check=True)
        print(f"Archive: {tar_path}")

    print(json.dumps({"out": str(args.out), "vehicles": len(summary_rows)}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
