#!/usr/bin/env python3
"""
i76_binary_geo_modeller_v9.py

Eighth-pass Interstate '76 binary-faithful vehicle GEO modeller with validated mirror-X OBJ view and source-truth-safe textured material handling.

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

Validation note:
  mirror-x and mirror-z both corrected mirrored decals/text on Piranha, proving the
  missing convention is a final handedness conversion rather than texture decode,
  material binding, or global UV flip.  v8 defaults to the validated mirror-X
  negative-determinant OBJ view transform while leaving the runtime model in
  original game coordinates.  Textured materials default to white Kd because
  Piranha source GEO face RGB is demonstrably asymmetric across some textured
  left/right slots; treating those bytes as a texture tint is not source-truth-safe.
  Untextured/color-only polygons still use GEO face color via palette-nearest.
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



def texture_alpha_enabled_for_surface_flags(flags: Tuple[int, int, int]) -> bool:
    """Return true for faces that should use transparent texture alpha.

    Open76 treats SurfaceFlags2 values 5 and 7 as transparent.  The GEO parser
    stores the three one-byte surface flags in on-disk order; SurfaceFlags2 is
    therefore flags[1].  This is a per-face/material decision, not a global
    texture decision, because the same VQM/M16 can be used by both opaque and
    transparent polygons.
    """
    try:
        return int(flags[1]) in (5, 7)
    except Exception:
        return False

def looks_like_light_alpha_candidate(mat_info: Dict[str, object]) -> bool:
    """Return true for transparent-flagged light/decal geometry only.

    Some opaque body textures contain palette index 0xff, so alpha cannot be
    enabled globally per texture or merely by GEO transparency flag.  Vehicle
    light overlays are explicit separate GEO parts such as PP11HLGT, PP11BLGT,
    and PP11TLGT; those are safe candidates for 0xff alpha in the OBJ view.
    """
    part = str(mat_info.get("part_name", "")).upper()
    geo = str(mat_info.get("geo_name", "")).upper()
    raw = str(mat_info.get("raw_slot", "")).upper()
    norm = str(mat_info.get("normalized_slot", "")).upper()
    tex = str(mat_info.get("texture_resource_name", "")).upper()
    resolved = str(mat_info.get("resolved_name", "")).upper()
    joined = " ".join([part, geo, raw, norm, tex, resolved])
    if any(k in joined for k in ["HLGT", "BLGT", "TLGT", "LAMP", "LIGHT"]):
        return True
    return ("LGT" in part) or ("LGT" in geo)


def alpha_enabled_for_material_policy(mat_info: Dict[str, object], texture_alpha_mode: str) -> bool:
    if texture_alpha_mode == "opaque":
        return False
    if texture_alpha_mode == "index-ff":
        return True
    if texture_alpha_mode == "transparent-flags":
        return bool(mat_info.get("texture_transparency_enabled", False))
    if texture_alpha_mode == "light-flags":
        return bool(mat_info.get("texture_transparency_enabled", False)) and looks_like_light_alpha_candidate(mat_info)
    return False



def load_module(path: Path, module_name: str):
    spec = importlib.util.spec_from_file_location(module_name, str(path))
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not import {module_name} from {path}")
    mod = importlib.util.module_from_spec(spec)
    sys.modules[module_name] = mod
    spec.loader.exec_module(mod)
    return mod



def apply_obj_geometry_transform(p: Tuple[float, float, float], mode: str) -> Tuple[float, float, float]:
    """Apply a final OBJ-view coordinate transform.

    This is deliberately an export/view probe. The runtime model remains in I76
    coordinates. Mirrored text with otherwise correct UVs is consistent with
    viewing backfaces after a missing handedness conversion, so these modes test
    whole-geometry reflections without changing source UVs or texture images.
    """
    x, y, z = p
    if mode == "identity":
        return (x, y, z)
    if mode == "mirror-x":
        return (-x, y, z)
    if mode == "mirror-y":
        return (x, -y, z)
    if mode == "mirror-z":
        return (x, y, -z)
    if mode in {"blender-xzy", "i76-yup-to-blender-zup"}:
        return (x, z, y)
    if mode == "blender-xzy-rh":
        return (x, z, -y)
    raise ValueError(f"unknown OBJ geometry transform: {mode}")

def geometry_transform_determinant_sign(mode: str) -> int:
    if mode in {"identity", "blender-xzy-rh"}:
        return 1
    if mode in {"mirror-x", "mirror-y", "mirror-z", "blender-xzy", "i76-yup-to-blender-zup"}:
        return -1
    return 1

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


def resolve_vqm_sibling_for_asset(idx, asset):
    """Return a same-stem VQM sibling for an M16/MAP-like asset when present."""
    if asset is None:
        return None
    try:
        stem = str(asset.name).rsplit(".", 1)[0]
        for cand in (stem + ".VQM", stem + ".vqm", stem):
            a = idx.resolve(cand, "vqm", source=asset)
            if a:
                return a
    except Exception:
        return None
    return None


def resolve_face_material(helper, resolver, idx, geo_asset, face, tmt_assets, map_assets, map_ref_stems,
                          direct_map_prefer: str, normalized_slot_swap: Dict[str, str]):
    raw_slot = face.texture_name or f"COLOR_{face.color[0]:02x}{face.color[1]:02x}{face.color[2]:02x}"
    resolved, kind, confidence, evidence, norm = helper.resolve_material_asset(
        resolver, idx, geo_asset, raw_slot, tmt_assets, map_assets, map_ref_stems,
        direct_map_prefer, normalized_slot_swap,
    )

    # Open76 resolves VTF BODY through vtf.Maps[12], then GetTexture() prefers
    # same-stem .vqm before .map.  The helper exporter historically resolved
    # BODY to the literal M16/MAP entry first, which can select tiny placeholder
    # M16 payloads such as pp11bdy1.M16 even when pp11bdy1.vqm exists.
    # Keep this override narrow: only BODY/vtf_map_image and only when the
    # caller requested --direct-map-prefer vqm.
    if (resolved is not None and direct_map_prefer == "vqm" and str(norm).upper() == "BODY"
            and kind == "vtf_map_image" and str(getattr(resolved, "ext", "")).lower() != "vqm"):
        sib = resolve_vqm_sibling_for_asset(idx, resolved)
        if sib is not None:
            resolved = sib
            kind = "vtf_map_image_vqm_preferred"
            confidence = "high"
            evidence = str(evidence) + "; BODY same-stem VQM preferred to match Open76 GetTexture lookup"

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
        "material_base_name": mat_name,
        "material_name": mat_name,
        "confidence": confidence if resolved else "none",
        "evidence": evidence if resolved else "unresolved",
    }


def color_key_for_material(face_color, palette_rgb: Optional[bytes], helper, textured_kd_mode: str, flat_color_mode: str, is_textured: bool) -> str:
    """Return a stable suffix for per-polygon material colors.

    OBJ/MTL stores Kd per material, not per face. If a texture/material name is
    shared by faces with different GEO face RGB values, using only the texture
    name collapses those colors to whichever face created the material first.
    This suffix preserves the binary/runtime section color as a material split.
    """
    r, g, b = (int(face_color[0]), int(face_color[1]), int(face_color[2]))
    if is_textured:
        if textured_kd_mode == "white":
            return "KD_white"
        if textured_kd_mode == "palette-nearest" and palette_rgb:
            pi = helper.nearest_palette_index_rgb(palette_rgb, (r, g, b))
            return "PAL_%03d" % (0 if pi is None else int(pi))
        return "RGB_%02x%02x%02x" % (r, g, b)
    if flat_color_mode in {"auto", "palette-nearest"} and palette_rgb:
        pi = helper.nearest_palette_index_rgb(palette_rgb, (r, g, b))
        return "PAL_%03d" % (0 if pi is None else int(pi))
    return "RGB_%02x%02x%02x" % (r, g, b)


def apply_material_color_granularity(helper, mat: Dict[str, object], face_color, palette_rgb: Optional[bytes],
                                     textured_kd_mode: str, flat_color_mode: str, material_color_granularity: str) -> None:
    base = str(mat.get("material_base_name") or mat.get("material_name") or "MAT")
    tex = mat.get("texture_asset") is not None
    if material_color_granularity == "shared":
        if tex and bool(mat.get("texture_transparency_enabled", False)):
            mat["material_name"] = base + "__ALPHA"
        else:
            mat["material_name"] = base
        mat["material_color_granularity"] = "shared"
        return
    suffix = color_key_for_material(face_color, palette_rgb, helper, textured_kd_mode, flat_color_mode, tex)
    if tex and bool(mat.get("texture_transparency_enabled", False)):
        suffix += "__ALPHA"
    mat["material_name"] = base + "__" + suffix
    mat["material_color_granularity"] = "per_color"


def build_runtime_sections(helper, resolver, idx, geo_asset, mesh, tmt_assets, map_assets, map_ref_stems,
                           direct_map_prefer: str, normalized_slot_swap: Dict[str, str], palette_rgb: Optional[bytes],
                           textured_kd_mode: str, flat_color_mode: str, material_color_granularity: str):
    sections: List[RuntimeSection] = []
    material_infos: Dict[int, Dict[str, object]] = {}
    for si, face in enumerate(mesh.faces):
        mat = resolve_face_material(
            helper, resolver, idx, geo_asset, face, tmt_assets, map_assets, map_ref_stems,
            direct_map_prefer, normalized_slot_swap,
        )
        face_flags = tuple(int(x) for x in face.surface_flags)
        mat["surface_flags"] = face_flags
        mat["texture_transparency_enabled"] = bool(mat.get("texture_asset") is not None and texture_alpha_enabled_for_surface_flags(face_flags))
        apply_material_color_granularity(
            helper, mat, face.color, palette_rgb, textured_kd_mode, flat_color_mode, material_color_granularity
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
            flags=face_flags,
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




def transform_indexed_pixels(width: int, height: int, pixels: bytes, mode: str) -> bytes:
    """Apply a final image-space transform after M16/VQM decode.

    This is intentionally distinct from --vqm-layout.  --vqm-layout controls the
    intra-4x4 CBK tile byte order during VQM decode.  This option mirrors the
    final decoded texture image, which is the right probe when geometry/corner
    order matches the binary but decals/text still appear mirrored in Blender.
    """
    if mode == "none":
        return pixels
    out = bytearray(width * height)
    for y in range(height):
        for x in range(width):
            sx = width - 1 - x if "flipx" in mode else x
            sy = height - 1 - y if "flipy" in mode else y
            out[y * width + x] = pixels[sy * width + sx]
    return bytes(out)


def write_indexed_image_rgba_open76(path_no_ext: Path, width: int, height: int, pixels: bytes,
                                   palette_rgb: Optional[bytes], texture_alpha_mode: str,
                                   alpha_enabled_for_material: bool) -> Tuple[str, bool]:
    """Write indexed texture pixels with Open76-style alpha handling.

    Open76 maps palette index 0xff to transparent RGBA in both MAP and VQM readers.
    For source-truth validation, preserve that as PNG alpha when a palette is supplied.
    """
    has_alpha = (texture_alpha_mode in {"index-ff", "transparent-flags", "light-flags"}) and alpha_enabled_for_material and any(px == 0xff for px in pixels)
    if palette_rgb is not None and len(palette_rgb) >= 768:
        if has_alpha:
            rgba = bytearray(width * height * 4)
            for i, px in enumerate(pixels):
                ro = i * 4
                if px == 0xff:
                    rgba[ro:ro+4] = bytes((0, 0, 0, 0))
                else:
                    po = int(px) * 3
                    rgba[ro:ro+3] = palette_rgb[po:po+3]
                    rgba[ro+3] = 255
            try:
                from PIL import Image  # type: ignore
                img = Image.frombytes("RGBA", (width, height), bytes(rgba))
                out = path_no_ext.with_suffix(".png")
                img.save(out)
                return out.name, True
            except Exception:
                # Fallback cannot preserve alpha, but keep export usable.
                pass
        return helper_write_rgb_or_gray(path_no_ext, width, height, pixels, palette_rgb), has_alpha
    return helper_write_rgb_or_gray(path_no_ext, width, height, pixels, palette_rgb), has_alpha


def helper_write_rgb_or_gray(path_no_ext: Path, width: int, height: int, pixels: bytes, palette_rgb: Optional[bytes]) -> str:
    if palette_rgb is not None and len(palette_rgb) >= 768:
        rgb = bytearray(width * height * 3)
        for i, px in enumerate(pixels):
            po = int(px) * 3
            ro = i * 3
            rgb[ro:ro+3] = palette_rgb[po:po+3]
        try:
            from PIL import Image  # type: ignore
            img = Image.frombytes("RGB", (width, height), bytes(rgb))
            out = path_no_ext.with_suffix(".png")
            img.save(out)
            return out.name
        except Exception:
            out = path_no_ext.with_suffix(".ppm")
            with out.open("wb") as f:
                f.write(("P6\n%d %d\n255\n" % (width, height)).encode("ascii"))
                f.write(rgb)
            return out.name
    try:
        from PIL import Image  # type: ignore
        img = Image.frombytes("L", (width, height), pixels)
        out = path_no_ext.with_suffix(".png")
        img.save(out)
        return out.name
    except Exception:
        out = path_no_ext.with_suffix(".pgm")
        with out.open("wb") as f:
            f.write(("P5\n%d %d\n255\n" % (width, height)).encode("ascii"))
            f.write(pixels)
        return out.name


def export_texture_for_asset_oriented(helper, resolver, idx, texture_asset, tex_dir: Path, written: Dict[str, Dict[str, object]],
                                      palette_rgb: Optional[bytes], vqm_layout: str, texture_image_transform: str,
                                      texture_alpha_mode: str, alpha_enabled_for_material: bool) -> Dict[str, object]:
    """Export decoded M16/VQM texture with optional final image-space flip and alpha.

    Returns metadata rather than only a path so MTL/debug outputs can track alpha.
    """
    cache_key = texture_asset.asset_id + "|image_transform=" + texture_image_transform + "|vqm_layout=" + vqm_layout + "|alpha=" + texture_alpha_mode + "|alpha_enabled=" + str(bool(alpha_enabled_for_material))
    if cache_key in written:
        return written[cache_key]

    data = idx.payloads.get(texture_asset.asset_id, b"")
    out_name = helper.safe_name(texture_asset.name).rsplit(".", 1)[0]
    if texture_image_transform != "none":
        out_name += "_" + texture_image_transform
    if alpha_enabled_for_material and texture_alpha_mode in {"index-ff", "transparent-flags", "light-flags"}:
        out_name += "_alpha"
    out_base = tex_dir / out_name
    image_name = ""
    has_alpha = False

    if texture_asset.ext == "m16":
        parsed = helper.parse_m16_pixels(data)
        if parsed:
            w, h, pix = parsed
            pix = transform_indexed_pixels(w, h, pix, texture_image_transform)
            image_name, has_alpha = write_indexed_image_rgba_open76(out_base, w, h, pix, palette_rgb, texture_alpha_mode, alpha_enabled_for_material)
    elif texture_asset.ext == "vqm":
        cbk_ref = helper.cstring(data[0x08:0x14]).upper() if len(data) >= 0x14 else ""
        if cbk_ref and "." not in cbk_ref:
            cbk_ref += ".CBK"
        cbk = idx.resolve(cbk_ref, "cbk", source=texture_asset) if cbk_ref else None
        if cbk:
            parsed = helper.decode_vqm_pixels(data, idx.payloads.get(cbk.asset_id, b""), vqm_layout)
            if parsed:
                w, h, pix = parsed
                pix = transform_indexed_pixels(w, h, pix, texture_image_transform)
                image_name, has_alpha = write_indexed_image_rgba_open76(out_base, w, h, pix, palette_rgb, texture_alpha_mode, alpha_enabled_for_material)

    if not image_name:
        raw_name = out_name + "." + texture_asset.ext + ".bin"
        (tex_dir / raw_name).write_bytes(data)
        image_name = raw_name
        has_alpha = False

    meta = {"map_kd": "textures/" + image_name, "has_alpha": has_alpha}
    written[cache_key] = meta
    return meta

def add_material(helper, resolver, idx, tex_dir: Path, materials: Dict[str, Dict[str, object]], mat_info,
                 face_color, palette_rgb, export_textures: bool, vqm_layout: str, texture_written: Dict[str, str],
                 textured_kd_mode: str, flat_color_mode: str, texture_image_transform: str, texture_alpha_mode: str):
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
    texture_has_alpha = False
    if export_textures and texture_asset:
        alpha_enabled_for_material = alpha_enabled_for_material_policy(mat_info, texture_alpha_mode)
        tex_meta = export_texture_for_asset_oriented(helper, resolver, idx, texture_asset, tex_dir, texture_written, palette_rgb, vqm_layout, texture_image_transform, texture_alpha_mode, alpha_enabled_for_material)
        map_kd = str(tex_meta.get("map_kd", ""))
        texture_has_alpha = bool(tex_meta.get("has_alpha", False))

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
        "material_base_name": mat_info.get("material_base_name", name),
        "material_color_granularity": mat_info.get("material_color_granularity", "shared"),
        "geo_face_color": geo_face_color,
        "diffuse_color": diffuse,
        "diffuse_source": diffuse_source,
        "palette_index": "" if palette_index is None else palette_index,
        "map_kd": map_kd,
        "texture_has_alpha": texture_has_alpha,
        "texture_alpha_mode": texture_alpha_mode,
        "texture_transparency_enabled": bool(mat_info.get("texture_transparency_enabled", False)),
        "surface_flags": mat_info.get("surface_flags", ""),
    }


def write_runtime_obj_mtl(helper, resolver, idx, vehicle_dir: Path, vehicle_name: str, part_models: List[Dict[str, object]],
                          palette_rgb: Optional[bytes], export_textures: bool, vqm_layout: str,
                          textured_kd_mode: str, flat_color_mode: str, obj_v_mode: str, obj_u_mode: str,
                          render_corner_order: str, texture_image_transform: str, obj_geometry_transform: str, texture_alpha_mode: str):
    obj_path = vehicle_dir / f"{helper.safe_name(vehicle_name)}.obj"
    mtl_path = vehicle_dir / f"{helper.safe_name(vehicle_name)}.mtl"
    tex_dir = vehicle_dir / "textures"
    if export_textures:
        tex_dir.mkdir(exist_ok=True)

    materials: Dict[str, Dict[str, object]] = {}
    texture_written: Dict[str, Dict[str, object]] = {}
    face_rows = []
    corner_rows = []

    v_base = 1
    vt_base = 1
    vn_base = 1

    with obj_path.open("w", encoding="utf-8") as obj:
        obj.write(f"# Interstate '76 binary runtime GEO model view: {vehicle_name}\n")
        obj.write("# Face corner order is configurable; binary evidence indicates reversed runtime corner order.\n")
        obj.write("# Runtime UVs are raw_u/raw_v; OBJ vt may convert U/V for Blender display depending on --obj-u-mode/--obj-v-mode.\n")
        obj.write(f"# OBJ geometry transform: {obj_geometry_transform}\n")
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
                x, y, z = apply_obj_geometry_transform((x, y, z), obj_geometry_transform)
                obj.write(f"v {x:.8g} {y:.8g} {z:.8g}\n")
            for n in mesh.normals:
                nx, ny, nz = helper.transform_normal(part_transform, n)
                nx, ny, nz = apply_obj_geometry_transform((nx, ny, nz), obj_geometry_transform)
                obj.write(f"vn {nx:.8g} {ny:.8g} {nz:.8g}\n")

            corner_order_by_section: Dict[int, List[RuntimeCorner]] = {}
            vt_indices_by_section: Dict[int, List[int]] = {}
            for sec in sections:
                corner_order = sec.corners_original_order if render_corner_order == "source" else sec.corners_render_order
                corner_order_by_section[sec.runtime_section_index] = corner_order
                vt_row = []
                for corner in corner_order:
                    vt_u = 1.0 - corner.raw_u if obj_u_mode == "flipped" else corner.raw_u
                    vt_v = corner.raw_v if obj_v_mode == "raw" else 1.0 - corner.raw_v
                    obj.write(f"vt {vt_u:.8g} {vt_v:.8g}\n")
                    vt_row.append(vt_base)
                    vt_base += 1
                vt_indices_by_section[sec.runtime_section_index] = vt_row

            for sec in sections:
                face = mesh.faces[sec.runtime_section_index]
                mat_info = material_infos[sec.runtime_section_index]
                mat_info["part_name"] = part_transform.name
                mat_info["geo_name"] = geo_asset.name
                add_material(helper, resolver, idx, tex_dir, materials, mat_info, face.color, palette_rgb,
                             export_textures, vqm_layout, texture_written, textured_kd_mode, flat_color_mode, texture_image_transform, texture_alpha_mode)
                obj.write(f"usemtl {sec.material_name}\n")
                refs = []
                for ri, corner in enumerate(corner_order_by_section[sec.runtime_section_index]):
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
                        "obj_u": 1.0 - corner.raw_u if obj_u_mode == "flipped" else corner.raw_u,
                        "obj_v": corner.raw_v if obj_v_mode == "raw" else 1.0 - corner.raw_v,
                        "order_rule": "source_order" if render_corner_order == "source" else "reversed_from_runtime_section_corner_order",
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
                    "surface_flags": sec.flags,
                    "texture_transparency_enabled": texture_alpha_enabled_for_surface_flags(sec.flags),
                    "centroid_local": sec.centroid_local,
                    "determinant_world_basis": determinant_basis(part_transform),
                    "obj_geometry_transform": obj_geometry_transform,
                    "obj_geometry_transform_determinant_sign": geometry_transform_determinant_sign(obj_geometry_transform),
                    "polygon_submission": "whole_n_gon_no_pretriangulation",
                    "corner_order": render_corner_order,
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
                if mat.get("texture_has_alpha"):
                    mtl.write(f"map_d {mat['map_kd']}\n")
                    mtl.write("d 1.0\n")

    write_blender_material_helper(vehicle_dir, materials)
    return obj_path, mtl_path, materials, face_rows, corner_rows


def write_blender_material_helper(vehicle_dir: Path, materials: Dict[str, Dict[str, object]]) -> None:
    """Emit a Blender helper for source-truth material display.

    OBJ/MTL cannot reliably express Blender alpha settings or texture interpolation.
    Running this after OBJ import sets image nodes to Closest interpolation and enables alpha clipping
    for textures whose indexed source used palette index 0xff.
    """
    alpha_names = sorted([name for name, mat in materials.items() if mat.get("texture_has_alpha")])
    script = vehicle_dir / "blender_apply_i76_material_settings.py"
    script.write_text("""import bpy

ALPHA_MATERIALS = set(%r)

for mat in bpy.data.materials:
    if not mat.name.startswith(tuple(ALPHA_MATERIALS)) and mat.name not in ALPHA_MATERIALS:
        pass
    mat.use_nodes = True
    for node in mat.node_tree.nodes:
        if node.bl_idname == 'ShaderNodeTexImage':
            node.interpolation = 'Closest'
            node.extension = 'REPEAT'
    if mat.name in ALPHA_MATERIALS or any(mat.name.startswith(a + '.') for a in ALPHA_MATERIALS):
        mat.blend_method = 'CLIP'
        mat.use_screen_refraction = False
        mat.show_transparent_back = True
        mat.alpha_threshold = 0.5
        bsdf = next((n for n in mat.node_tree.nodes if n.bl_idname == 'ShaderNodeBsdfPrincipled'), None)
        tex = next((n for n in mat.node_tree.nodes if n.bl_idname == 'ShaderNodeTexImage'), None)
        if bsdf is not None and tex is not None:
            mat.node_tree.links.new(tex.outputs.get('Alpha'), bsdf.inputs.get('Alpha'))
""" % (alpha_names,), encoding="utf-8")


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
        "surface_flags", "texture_transparency_enabled", "centroid_local", "determinant_world_basis", "polygon_submission", "corner_order",
    ])
    write_tsv(vehicle_dir / "corner_mapping.tsv", corner_rows, [
        "vehicle", "part", "geo", "runtime_section_index", "source_face_index", "render_corner_index",
        "source_corner_index", "vertex_index", "normal_index", "raw_u", "raw_v", "obj_u", "obj_v", "order_rule",
    ])
    write_tsv(vehicle_dir / "material_binding.tsv", list(materials.values()), [
        "name", "material_base_name", "material_color_granularity", "raw_slot", "normalized_slot", "resolved_kind", "resolved_name", "resolved_asset_id",
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
    ap.add_argument("--textured-kd-mode", choices=["white", "geo-direct", "palette-nearest"], default="white", help="Diffuse Kd for textured OBJ/MTL materials. Default white is the current source-truth-safe baseline: GEO face RGB is preserved in debug outputs but not multiplied into textured maps. Use geo-direct only as a diagnostic.")
    ap.add_argument("--material-color-granularity", choices=["per-color", "shared"], default="per-color", help="OBJ/MTL Kd is material-level, so per-color splits material names by GEO face color/palette index. shared preserves old v6 behavior.")
    ap.add_argument("--obj-v-mode", choices=["blender", "raw"], default="blender", help="blender writes OBJ vt V as 1-raw_v; raw writes raw_v")
    ap.add_argument("--obj-u-mode", choices=["raw", "flipped"], default="raw", help="Diagnostic OBJ view option: raw writes U as raw_u; flipped writes 1-raw_u")
    ap.add_argument("--render-corner-order", choices=["binary-reversed", "source"], default="binary-reversed", help="OBJ view order. binary-reversed follows current binary evidence; source preserves GEO/source order for comparison.")
    ap.add_argument("--texture-image-transform", choices=["none", "flipx", "flipy", "flipx_flipy"], default="none", help="Final decoded texture image-space transform applied to M16 and VQM PNG/PPM export.")
    ap.add_argument("--texture-alpha-mode", choices=["light-flags", "transparent-flags", "index-ff", "opaque"], default="light-flags", help="PNG alpha export policy. Default light-flags maps palette index 0xff to alpha only for transparent-flagged light overlay geometry such as *HLGT/*BLGT/*TLGT. transparent-flags applies alpha to every textured face whose GEO SurfaceFlags2 is 5 or 7; index-ff applies alpha globally; opaque disables texture alpha.")
    ap.add_argument("--obj-geometry-transform", choices=["identity", "mirror-x", "mirror-y", "mirror-z", "blender-xzy", "blender-xzy-rh", "i76-yup-to-blender-zup"], default="mirror-x", help="Final OBJ-view coordinate transform. Default mirror-x is the validated negative-determinant OBJ view that fixes mirrored decals/text without swapping axes.")
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
                args.textured_kd_mode, args.flat_color_mode, args.material_color_granularity,
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
                args.flat_color_mode, args.obj_v_mode, args.obj_u_mode, args.render_corner_order,
                args.texture_image_transform, args.obj_geometry_transform, args.texture_alpha_mode,
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
        "material_color_granularity": args.material_color_granularity,
        "obj_v_mode": args.obj_v_mode,
        "obj_u_mode": args.obj_u_mode,
        "render_corner_order": args.render_corner_order,
        "texture_image_transform": args.texture_image_transform,
        "texture_alpha_mode": args.texture_alpha_mode,
        "obj_geometry_transform": args.obj_geometry_transform,
        "obj_geometry_transform_determinant_sign": geometry_transform_determinant_sign(args.obj_geometry_transform),
        "vdf_sobj_mode": args.vdf_sobj_mode,
        "zfs_errors": len(errors),
        "pix_pak_warnings": len(warnings),
        "binary_runtime_rules": {
            "corner_order": "reversed during build_lit_geo_render_records_from_sections",
            "uv_storage": "raw GEO u/v copied to render vertices",
            "diagnostic_note": "OBJ U/V modes and texture-image-transform are view/export probes, not new binary conclusions",
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

Material-color policy:
  By default, textured materials use white Kd and keep GEO face RGB in the debug TSV/JSON.
  V12 defaults to opaque texture export, preserves transparency flags in debug output, and prefers same-stem BODY VQM over BODY M16 when --direct-map-prefer vqm is used.
  Untextured/color-only faces use GEO face RGB through palette-nearest.
  --textured-kd-mode geo-direct remains available only as a diagnostic textured-face tint mode.

Orientation probes:
  --obj-v-mode raw|blender controls OBJ V only.
  --obj-u-mode raw|flipped controls OBJ U only.
  --render-corner-order binary-reversed|source controls OBJ polygon corner order only.
  --texture-image-transform none|flipx|flipy|flipx_flipy mirrors final decoded M16/VQM image output; this is distinct from --vqm-layout intra-tile order.
  --obj-geometry-transform identity|mirror-x|mirror-y|mirror-z|blender-xzy|blender-xzy-rh|i76-yup-to-blender-zup changes only the final OBJ coordinate view. v8 defaults to mirror-x, preserving the runtime model while applying the validated negative-determinant OBJ view without swapping axes. Use mirror-z if it matches your preferred vehicle facing direction better.
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
