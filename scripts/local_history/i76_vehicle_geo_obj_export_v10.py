#!/usr/bin/env python3
"""
i76_vehicle_geo_obj_export_v10.py

Vehicle GEO OBJ/MTL exporter using resolved texture slots and binary-style damage-state hierarchy binding.

This script is intentionally downstream of:
  i76_vehicle_texture_slot_resolver_v5.py

It uses the same in-memory ZFS/PIX/PAK indexing and vehicle texture-slot
resolution code, then exports vehicle GEO parts as OBJ/MTL with material names
bound to resolved TMT/M16/VQM assets where possible.

Open76 reference points used:
  * GeoParser.cs: GEO header, vertices, normals, faces, 13-byte texture name,
    and per-face vertex refs: vertex index, normal index, U, V.
  * VtfParser.cs: VTFC contains 78 TMT filenames and 13 MAP entries; TMT
    texture names are read as packed 8-byte CString entries.

This exporter is a geometry/material validation tool, not yet a final scene
assembler:
  * It applies VDF VGEO/SOBJ part transforms where available.
  * It applies the VDF VGEO state-0 hierarchy and binds alternate damage-state GEO names by VGEO index.
  * It writes debug grayscale PNG/PGM textures for M16/VQM where requested,
    using palette indices as luminance unless a real palette pipeline is added.

Usage:
  python3 i76_vehicle_geo_obj_export_v10.py \
      --zfs I76.ZFS \
      --zix I76.ZIX \
      --resolver i76_vehicle_texture_slot_resolver_v5.py \
      --out i76_vehicle_geo_obj_v9 \
      --vehicle vcpolic1 \
      --export-textures \
      --overwrite

Export all vehicles with VDF/VTF:
  python3 i76_vehicle_geo_obj_export_v10.py --zfs I76.ZFS --zix I76.ZIX \
      --resolver i76_vehicle_texture_slot_resolver_v5.py \
      --out i76_vehicle_geo_obj_v9 --all --overwrite
"""

from __future__ import annotations

import argparse
import importlib.util
import json
import math
import re
import shutil
import struct
import sys
import tarfile
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


@dataclass
class GeoVertexRef:
    vertex_index: int
    normal_index: int
    u: float
    v: float


@dataclass
class GeoFace:
    index: int
    color: Tuple[int, int, int]
    surface_normal: Tuple[float, float, float, float]
    surface_flags: Tuple[int, int, int]
    texture_name: str
    unk3: int
    unk4: int
    unk5: int
    refs: List[GeoVertexRef]


@dataclass
class GeoMesh:
    name: str
    vertices: List[Tuple[float, float, float]]
    normals: List[Tuple[float, float, float]]
    faces: List[GeoFace]
    magic: str
    unk1: int
    unk2: int


@dataclass
class PartTransform:
    name: str
    parent_name: str
    right: Tuple[float, float, float]
    up: Tuple[float, float, float]
    forward: Tuple[float, float, float]
    position: Tuple[float, float, float]
    world_right: Tuple[float, float, float]
    world_up: Tuple[float, float, float]
    world_forward: Tuple[float, float, float]
    world_position: Tuple[float, float, float]
    source: str




# Conservative retail aliases validated from asset-side probes.
# These are exact file-level corrections only; do not generalize them into
# broader fuzzy matching rules.
EXPLICIT_RETAIL_RESOURCE_ALIASES = {
    "VALEPRE.VDF": "VALEPREC.VDF",
    "VCROYAL.VDF": "VCROYALE.VDF",
    "SKTVAN2.VTF": "STVAN2.VTF",
}

def load_resolver(path: Path):
    spec = importlib.util.spec_from_file_location("i76_resolver_v5", str(path))
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not import resolver script: {path}")
    mod = importlib.util.module_from_spec(spec)
    sys.modules["i76_resolver_v5"] = mod
    spec.loader.exec_module(mod)
    return mod


def ensure_clean_dir(path: Path, overwrite: bool) -> None:
    if path.exists():
        if not overwrite:
            raise FileExistsError(f"output exists: {path}; use --overwrite")
        shutil.rmtree(path)
    path.mkdir(parents=True, exist_ok=True)


def cstring(data: bytes) -> str:
    return data.split(b"\x00", 1)[0].decode("ascii", "replace").strip()


def safe_name(name: str) -> str:
    base = name.replace("\\", "/").split("/")[-1]
    return re.sub(r"[^A-Za-z0-9._+\-]+", "_", base) or "unnamed"



def read_vec3(data: bytes, off: int) -> Tuple[Tuple[float, float, float], int]:
    return struct.unpack_from("<fff", data, off), off + 12


def parse_bwd2_chunks(data: bytes) -> List[Tuple[str, int, bytes]]:
    """Parse BWD2-style tagged chunks.

    Open76 Bwd2Reader reads a 4-byte CString tag, then uint32 chunk size where
    dataLength = size - 8. This helper returns (tag, data_offset, payload).
    """
    out: List[Tuple[str, int, bytes]] = []
    off = 0
    while off + 8 <= len(data):
        tag = cstring(data[off:off+4])
        size = struct.unpack_from("<I", data, off + 4)[0]
        if size < 8 or off + size > len(data):
            break
        payload = data[off + 8 : off + size]
        out.append((tag, off + 8, payload))
        off += size
    return out


def compose_basis(parent: PartTransform, local: PartTransform) -> PartTransform:
    """Compose child basis/position through parent basis.

    Vector convention follows Open76 fields:
      world_point = position + right*x + up*y + forward*z.
    """
    def transform_vec(v: Tuple[float, float, float]) -> Tuple[float, float, float]:
        x, y, z = v
        return (
            parent.world_right[0] * x + parent.world_up[0] * y + parent.world_forward[0] * z,
            parent.world_right[1] * x + parent.world_up[1] * y + parent.world_forward[1] * z,
            parent.world_right[2] * x + parent.world_up[2] * y + parent.world_forward[2] * z,
        )

    def transform_pos(v: Tuple[float, float, float]) -> Tuple[float, float, float]:
        tv = transform_vec(v)
        return (
            parent.world_position[0] + tv[0],
            parent.world_position[1] + tv[1],
            parent.world_position[2] + tv[2],
        )

    wr = transform_vec(local.right)
    wu = transform_vec(local.up)
    wf = transform_vec(local.forward)
    wp = transform_pos(local.position)
    return PartTransform(
        local.name, local.parent_name, local.right, local.up, local.forward, local.position,
        wr, wu, wf, wp, local.source
    )


def identity_part(name: str, source: str = "identity") -> PartTransform:
    return PartTransform(
        name=name,
        parent_name="",
        right=(1.0, 0.0, 0.0),
        up=(0.0, 1.0, 0.0),
        forward=(0.0, 0.0, 1.0),
        position=(0.0, 0.0, 0.0),
        world_right=(1.0, 0.0, 0.0),
        world_up=(0.0, 1.0, 0.0),
        world_forward=(0.0, 0.0, 1.0),
        world_position=(0.0, 0.0, 0.0),
        source=source,
    )


def parse_vdf_geometry_transforms(data: bytes, damage_state: int = 0) -> Tuple[List[PartTransform], List[str]]:
    """Parse SOBJ + VGEO transforms using the runtime-style damage model.

    Open76 VdfParser confirms the on-disk VGEO layout:
      SOBJ: base 8-byte GEO name
      VGEO: uint32 numParts
            for each of 4 third-person damage states:
              repeated numParts:
                name[8], right/up/forward/position vec3, parent[8], skip 36
            skip 100 * numParts * 12
            first-person part set follows

    Binary tracing of the retail loader indicates that object parentage is built
    once, then later damage/variant geometry is attached to existing object slots
    by record index.  Therefore this exporter composes transforms from state 0
    only.  For damage_state N, it uses state N's part name as the GEO resource
    basename for the same VGEO slot index, but keeps the state-0 world transform
    and parent relationship.  It deliberately does not repair state-N parent
    strings such as SV11BDYF -> SV13BDYF.

    Diagnostics beginning with "alternate_" describe differences in the selected
    damage-state records but are not parse errors.
    """
    chunks = parse_bwd2_chunks(data)
    warnings: List[str] = []
    sobj_name = ""
    vgeo_payload: Optional[bytes] = None

    for tag, _off, payload in chunks:
        if tag == "SOBJ" and not sobj_name:
            sobj_name = cstring(payload[:8])
        elif tag == "VGEO" and vgeo_payload is None:
            vgeo_payload = payload

    # WORLD and NULL appear as root/sentinel parent names in retail VDFs.
    world_root = identity_part("WORLD", "implicit_WORLD")
    base_order: List[str] = ["WORLD"]
    base_locals_by_name: Dict[str, PartTransform] = {"WORLD": world_root}

    if sobj_name:
        root = identity_part(sobj_name, "SOBJ")
        base_locals_by_name[sobj_name.upper()] = root
        base_order.append(sobj_name.upper())

    if vgeo_payload is None or len(vgeo_payload) < 4:
        warnings.append("missing VGEO chunk")
        return [base_locals_by_name[k] for k in base_order if k in base_locals_by_name], warnings

    def read_vgeo_record(buf: bytes, off: int, state: int, slot_index: int) -> Tuple[PartTransform, int]:
        name = cstring(buf[off:off+8]); off += 8
        right, off = read_vec3(buf, off)
        up, off = read_vec3(buf, off)
        forward, off = read_vec3(buf, off)
        position, off = read_vec3(buf, off)
        parent = cstring(buf[off:off+8]); off += 8
        off += 36
        return PartTransform(
            name=name,
            parent_name=parent,
            right=right,
            up=up,
            forward=forward,
            position=position,
            world_right=right,
            world_up=up,
            world_forward=forward,
            world_position=position,
            source=f"VGEO_state{state}_slot{slot_index}",
        ), off

    try:
        num_parts = struct.unpack_from("<I", vgeo_payload, 0)[0]
        if num_parts > 10000:
            warnings.append(f"unreasonable VGEO num_parts={num_parts}")
            return [base_locals_by_name[k] for k in base_order if k in base_locals_by_name], warnings

        record_size = 8 + 12*4 + 8 + 36
        third_person_bytes = 4 * num_parts * record_size
        if len(vgeo_payload) < 4 + third_person_bytes:
            warnings.append(
                f"VGEO too small for four third-person states: num_parts={num_parts} len={len(vgeo_payload)} need={4 + third_person_bytes}"
            )
            return [base_locals_by_name[k] for k in base_order if k in base_locals_by_name], warnings

        if damage_state < 0 or damage_state > 3:
            damage_state = 0

        state_records: List[List[PartTransform]] = []
        off = 4
        for state in range(4):
            rows: List[PartTransform] = []
            for i in range(num_parts):
                rec, off = read_vgeo_record(vgeo_payload, off, state, i)
                rows.append(rec)
            state_records.append(rows)
    except Exception as e:
        warnings.append(f"VGEO parse failed: {e}")
        return [base_locals_by_name[k] for k in base_order if k in base_locals_by_name], warnings

    # Build the runtime object hierarchy from state 0 only.
    base_slot_keys: List[str] = []
    for i, rec in enumerate(state_records[0]):
        if not rec.name or rec.name.upper() == "NULL":
            base_slot_keys.append("")
            continue
        key = rec.name.upper()
        base_slot_keys.append(key)
        base_locals_by_name[key] = rec
        if key not in base_order:
            base_order.append(key)

    resolved: Dict[str, PartTransform] = {}

    def resolve_key(key: str, stack: Optional[List[str]] = None) -> PartTransform:
        if key in resolved:
            return resolved[key]
        if stack is None:
            stack = []
        if key in stack:
            warnings.append("VGEO parent cycle: " + "->".join(stack + [key]))
            resolved[key] = base_locals_by_name[key]
            return resolved[key]

        local = base_locals_by_name[key]
        parent_key = local.parent_name.upper()
        if parent_key == "NULL":
            parent_key = ""
        if not parent_key or parent_key not in base_locals_by_name:
            if parent_key and parent_key not in base_locals_by_name:
                warnings.append(f"missing parent {local.parent_name!r} for {local.name!r}; using local as world")
            resolved[key] = local
            return local

        parent_world = resolve_key(parent_key, stack + [key])
        resolved[key] = compose_basis(parent_world, local)
        return resolved[key]

    for key in base_order:
        resolve_key(key)

    if damage_state == 0:
        return [resolved[k] for k in base_order if k in resolved], warnings

    # For alternate states, export selected-state GEO names through state-0 slots.
    # This matches the observed binary pattern better than resolving the selected
    # state's parent names as an independent tree.
    out: List[PartTransform] = []
    selected_names = {
        rec.name.upper()
        for rec in state_records[damage_state]
        if rec.name and rec.name.upper() != "NULL"
    }

    for key in base_order:
        if key in {"WORLD", sobj_name.upper()}:
            if key in resolved:
                out.append(resolved[key])
            continue

    for slot_index, base_key in enumerate(base_slot_keys):
        if not base_key or base_key not in resolved:
            continue
        base_world = resolved[base_key]
        alt = state_records[damage_state][slot_index]
        if not alt.name or alt.name.upper() == "NULL":
            warnings.append(
                f"alternate_null_slot damage_state={damage_state} slot={slot_index} base_object={base_world.name!r}"
            )
            continue

        alt_parent_key = alt.parent_name.upper()
        if alt_parent_key == "NULL":
            alt_parent_key = ""
        if alt_parent_key and alt_parent_key not in {"WORLD", sobj_name.upper()} and alt_parent_key not in selected_names:
            warnings.append(
                f"alternate_parent_missing_in_selected_state damage_state={damage_state} slot={slot_index} "
                f"base_object={base_world.name!r} export_geo={alt.name!r} alternate_parent={alt.parent_name!r}"
            )
        if alt.parent_name.upper() != base_world.parent_name.upper():
            warnings.append(
                f"alternate_parent_differs_from_base damage_state={damage_state} slot={slot_index} "
                f"base_object={base_world.name!r} export_geo={alt.name!r} "
                f"base_parent={base_world.parent_name!r} alternate_parent={alt.parent_name!r}"
            )

        out.append(PartTransform(
            name=alt.name,
            parent_name=base_world.parent_name,
            right=base_world.right,
            up=base_world.up,
            forward=base_world.forward,
            position=base_world.position,
            world_right=base_world.world_right,
            world_up=base_world.world_up,
            world_forward=base_world.world_forward,
            world_position=base_world.world_position,
            source=f"VGEO_state{damage_state}_slot{slot_index}_geo_on_state0_hierarchy:{base_world.name}",
        ))

    return out, warnings

def transform_point(t: PartTransform, p: Tuple[float, float, float]) -> Tuple[float, float, float]:
    x, y, z = p
    return (
        t.world_position[0] + t.world_right[0] * x + t.world_up[0] * y + t.world_forward[0] * z,
        t.world_position[1] + t.world_right[1] * x + t.world_up[1] * y + t.world_forward[1] * z,
        t.world_position[2] + t.world_right[2] * x + t.world_up[2] * y + t.world_forward[2] * z,
    )


def transform_normal(t: PartTransform, n: Tuple[float, float, float]) -> Tuple[float, float, float]:
    x, y, z = n
    out = (
        t.world_right[0] * x + t.world_up[0] * y + t.world_forward[0] * z,
        t.world_right[1] * x + t.world_up[1] * y + t.world_forward[1] * z,
        t.world_right[2] * x + t.world_up[2] * y + t.world_forward[2] * z,
    )
    mag = math.sqrt(out[0]*out[0] + out[1]*out[1] + out[2]*out[2])
    if mag > 1e-8:
        return (out[0]/mag, out[1]/mag, out[2]/mag)
    return out


def parse_geo(data: bytes) -> GeoMesh:
    off = 0
    if len(data) < 0x28:
        raise ValueError("GEO too small")
    magic = cstring(data[off:off+4]); off += 4
    unk1 = struct.unpack_from("<I", data, off)[0]; off += 4
    name = cstring(data[off:off+16]); off += 16
    vertex_count = struct.unpack_from("<I", data, off)[0]; off += 4
    face_count = struct.unpack_from("<I", data, off)[0]; off += 4
    unk2 = struct.unpack_from("<I", data, off)[0]; off += 4

    if vertex_count > 200000 or face_count > 200000:
        raise ValueError(f"unreasonable GEO counts vertex={vertex_count} face={face_count}")

    vertices = []
    for _ in range(vertex_count):
        vertices.append(struct.unpack_from("<fff", data, off))
        off += 12

    # Open76 reads normal count == vertex_count. Our Ghidra runtime work suggests
    # this is a normal/secondary vector table consumed by normal_index, and the
    # retail assets parsed cleanly with this layout in prior passes.
    normals = []
    for _ in range(vertex_count):
        normals.append(struct.unpack_from("<fff", data, off))
        off += 12

    faces: List[GeoFace] = []
    for _ in range(face_count):
        face_index = struct.unpack_from("<I", data, off)[0]; off += 4
        nverts = struct.unpack_from("<I", data, off)[0]; off += 4
        if nverts > 1024:
            raise ValueError(f"unreasonable face vertex count {nverts} at face {len(faces)}")
        color = (data[off], data[off+1], data[off+2]); off += 3
        surf = struct.unpack_from("<ffff", data, off); off += 16
        unk3 = struct.unpack_from("<I", data, off)[0]; off += 4
        flags = (data[off], data[off+1], data[off+2]); off += 3
        tex = cstring(data[off:off+13]); off += 13
        unk4 = struct.unpack_from("<I", data, off)[0]; off += 4
        unk5 = struct.unpack_from("<I", data, off)[0]; off += 4
        refs = []
        for _j in range(nverts):
            vi, ni, u, v = struct.unpack_from("<IIff", data, off)
            off += 16
            refs.append(GeoVertexRef(vi, ni, u, v))
        faces.append(GeoFace(face_index, color, surf, flags, tex, unk3, unk4, unk5, refs))

    return GeoMesh(name, vertices, normals, faces, magic, unk1, unk2)


def parse_m16_pixels(data: bytes) -> Optional[Tuple[int, int, bytes]]:
    if len(data) < 8:
        return None
    w, hf = struct.unpack_from("<II", data, 0)
    h = hf & 0x1FFFFFFF
    if not (0 < w <= 4096 and 0 < h <= 4096):
        return None
    need = 8 + w * h
    if len(data) < need:
        return None
    return w, h, data[8:need]


def decode_vqm_pixels(data: bytes, cbk_data: bytes) -> Optional[Tuple[int, int, bytes]]:
    if len(data) < 0x18 or len(cbk_data) < 4:
        return None
    w, hf = struct.unpack_from("<II", data, 0)
    h = hf & 0x1FFFFFFF
    if not (0 < w <= 4096 and 0 < h <= 4096):
        return None
    tiles_x = (w + 3) // 4
    tiles_y = (h + 3) // 4
    token_count = tiles_x * tiles_y
    if len(data) < 0x18 + 2 * token_count:
        return None
    pixels = bytearray(w * h)
    pos = 0x18
    for by in range(tiles_y):
        for bx in range(tiles_x):
            tok = struct.unpack_from("<H", data, pos)[0]
            pos += 2
            if tok & 0x8000:
                tile = bytes([tok & 0xff]) * 16
            else:
                tile_off = 4 + tok * 16
                if tile_off + 16 > len(cbk_data):
                    tile = bytes([0]) * 16
                else:
                    tile = cbk_data[tile_off:tile_off+16]
            for sy in range(4):
                py = by * 4 + sy
                if py >= h:
                    continue
                for sx in range(4):
                    px = bx * 4 + sx
                    if px >= w:
                        continue
                    # Open76 indexes cbkData[sx * 4 + sy], so preserve that order.
                    pixels[py * w + px] = tile[sx * 4 + sy]
    return w, h, bytes(pixels)


def load_palette_file(path: Optional[Path], scale_mode: str = "auto") -> Optional[bytes]:
    """Load a 256*3 RGB palette from ACT/raw file.

    I76's runtime palette at 004fa170 is stored as 0..63 RGB triplets. Many
    mission ACT files are already 0..255. For external PNGs, auto mode scales
    low-range palettes by 4 while leaving 0..255 palettes unchanged.
    """
    if path is None:
        return None
    data = path.read_bytes()
    if len(data) < 768:
        raise ValueError(f"palette file is too small: {path} ({len(data)} bytes)")
    pal = data[:768]
    if scale_mode == "raw":
        return pal
    if scale_mode == "x4":
        return bytes(min(255, v * 4) for v in pal)
    if scale_mode == "auto":
        return bytes(min(255, v * 4) for v in pal) if max(pal) <= 63 else pal
    raise ValueError(f"unknown palette scale mode: {scale_mode}")


def write_indexed_image(path_no_ext: Path, width: int, height: int, pixels: bytes, palette_rgb: Optional[bytes]) -> str:
    """Write indexed pixels as RGB PNG if palette is provided, else grayscale debug image."""
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

    # Try PNG via Pillow if available; fall back to binary PGM.
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


def resolve_material_asset(resolver, idx, geo_asset, raw_slot: str, tmt_assets, map_assets, map_ref_stems):
    norm = resolver.normalize_geo_slot(raw_slot)

    resolved = resolver.slot_to_tmt(norm, tmt_assets)
    kind = "tmt"
    confidence = "high"
    evidence = "GEO slot normalized and matched VTF TMT suffix"

    if not resolved and norm == "BODY":
        resolved = resolver.resolve_body_slot_from_vtf_map_refs(map_ref_stems, idx, geo_asset)
        kind = "vtf_map_image"
        confidence = "high"
        evidence = "GEO BODY slot resolved through VTF MAP image basename"

    if not resolved:
        resolved = resolver.resolve_slot_as_direct_texture(raw_slot, norm, idx, geo_asset)
        kind = "direct_texture"
        confidence = "medium"
        evidence = "GEO slot literal stem resolved directly"

    if not resolved:
        resolved = resolver.slot_to_map(norm, map_assets)
        kind = "map"
        confidence = "medium"
        evidence = "GEO slot normalized and matched VTF MAP slot"

    return resolved, kind, confidence, evidence, norm


def first_texture_from_tmt(resolver, idx, tmt_asset):
    data = idx.payloads.get(tmt_asset.asset_id, b"")
    if not data:
        return None
    tokens = resolver.parse_tmt_frame_tokens(data)
    for tok in tokens:
        vqm = idx.resolve(tok, "vqm", source=tmt_asset)
        if vqm:
            return vqm
        m16 = idx.resolve(tok, "m16", source=tmt_asset)
        if m16:
            return m16
    return None


def export_texture_for_asset(resolver, idx, texture_asset, tex_dir: Path, written: Dict[str, str], palette_rgb: Optional[bytes]) -> str:
    if texture_asset.asset_id in written:
        return written[texture_asset.asset_id]

    data = idx.payloads.get(texture_asset.asset_id, b"")
    out_name = safe_name(texture_asset.name).rsplit(".", 1)[0]
    out_base = tex_dir / out_name

    image_name = ""
    if texture_asset.ext == "m16":
        parsed = parse_m16_pixels(data)
        if parsed:
            image_name = write_indexed_image(out_base, parsed[0], parsed[1], parsed[2], palette_rgb)
    elif texture_asset.ext == "vqm":
        # VQM header at +0x08 stores CBK name.
        cbk_ref = cstring(data[0x08:0x14]).upper() if len(data) >= 0x14 else ""
        if cbk_ref and "." not in cbk_ref:
            cbk_ref += ".CBK"
        cbk = idx.resolve(cbk_ref, "cbk", source=texture_asset) if cbk_ref else None
        if cbk:
            parsed = decode_vqm_pixels(data, idx.payloads.get(cbk.asset_id, b""))
            if parsed:
                image_name = write_indexed_image(out_base, parsed[0], parsed[1], parsed[2], palette_rgb)

    if not image_name:
        # Keep a raw payload for debugging if image decode was not possible.
        raw_name = out_name + "." + texture_asset.ext + ".bin"
        (tex_dir / raw_name).write_bytes(data)
        image_name = raw_name

    written[texture_asset.asset_id] = "textures/" + image_name
    return written[texture_asset.asset_id]


def write_obj_mtl(vehicle_dir: Path, vehicle_name: str, part_rows: List[Tuple], export_textures: bool, resolver, idx, palette_rgb: Optional[bytes] = None):
    obj_path = vehicle_dir / f"{safe_name(vehicle_name)}.obj"
    mtl_path = vehicle_dir / f"{safe_name(vehicle_name)}.mtl"
    tex_dir = vehicle_dir / "textures"
    if export_textures:
        tex_dir.mkdir(exist_ok=True)

    materials: Dict[str, Dict[str, object]] = {}
    texture_written: Dict[str, str] = {}
    face_report = []

    v_base = 1
    vt_base = 1
    vn_base = 1

    with obj_path.open("w", encoding="utf-8") as obj:
        obj.write(f"# Interstate '76 vehicle GEO export: {vehicle_name}\n")
        obj.write(f"# VDF transforms are applied. Damage states use state-0 hierarchy with state-N GEO names by VGEO slot index.\n")
        obj.write(f"mtllib {mtl_path.name}\n\n")

        for item in part_rows:
            geo_asset, geo_mesh, part_transform, tmt_assets, map_assets, map_ref_stems, vdf_name, vtf_name = item
            obj.write(f"o {safe_name(part_transform.name)}_{safe_name(geo_asset.name)}\n")
            obj.write(f"# GEO asset {geo_asset.asset_id}\n")
            obj.write(f"# VDF part {part_transform.name} parent={part_transform.parent_name} source={part_transform.source}\n")

            for p in geo_mesh.vertices:
                x, y, z = transform_point(part_transform, p)
                obj.write(f"v {x:.8g} {y:.8g} {z:.8g}\n")
            for n in geo_mesh.normals:
                nx, ny, nz = transform_normal(part_transform, n)
                obj.write(f"vn {nx:.8g} {ny:.8g} {nz:.8g}\n")

            # OBJ UVs are per-face-corner, so write all corner UVs just before faces.
            local_vt_indices: List[List[int]] = []
            for face in geo_mesh.faces:
                vt_row = []
                for ref in face.refs:
                    obj.write(f"vt {ref.u:.8g} {1.0 - ref.v:.8g}\n")
                    vt_row.append(vt_base)
                    vt_base += 1
                local_vt_indices.append(vt_row)

            for face_idx, face in enumerate(geo_mesh.faces):
                raw_slot = face.texture_name or f"COLOR_{face.color[0]:02x}{face.color[1]:02x}{face.color[2]:02x}"
                resolved, kind, confidence, evidence, norm = resolve_material_asset(
                    resolver, idx, geo_asset, raw_slot, tmt_assets, map_assets, map_ref_stems
                )
                texture_asset = None
                material_key = ""
                if resolved:
                    if resolved.ext == "tmt":
                        texture_asset = first_texture_from_tmt(resolver, idx, resolved)
                        material_key = f"TMT_{safe_name(resolved.name)}"
                    else:
                        texture_asset = resolved
                        material_key = f"TEX_{safe_name(resolved.name)}"
                else:
                    material_key = f"UNRES_{safe_name(norm or raw_slot)}"

                if material_key not in materials:
                    mat = {
                        "name": material_key,
                        "raw_slot": raw_slot,
                        "normalized_slot": norm,
                        "resolved_kind": kind if resolved else "unresolved",
                        "resolved_name": resolved.name if resolved else "",
                        "resolved_asset_id": resolved.asset_id if resolved else "",
                        "texture_asset_name": texture_asset.name if texture_asset else "",
                        "texture_asset_id": texture_asset.asset_id if texture_asset else "",
                        "confidence": confidence if resolved else "none",
                        "evidence": evidence if resolved else "unresolved",
                        "color": face.color,
                        "map_kd": "",
                    }
                    if export_textures and texture_asset:
                        mat["map_kd"] = export_texture_for_asset(resolver, idx, texture_asset, tex_dir, texture_written, palette_rgb)
                    materials[material_key] = mat

                obj.write(f"usemtl {material_key}\n")
                refs = []
                for j, ref in enumerate(face.refs):
                    vi = v_base + ref.vertex_index
                    # GEO normal indices refer to the normal/secondary table.
                    ni = vn_base + ref.normal_index if ref.normal_index < len(geo_mesh.normals) else vn_base
                    vti = local_vt_indices[face_idx][j]
                    refs.append(f"{vi}/{vti}/{ni}")
                # Keep original winding. If visual output is inverted, flip at importer level later.
                obj.write("f " + " ".join(refs) + "\n")

                face_report.append({
                    "vehicle": vehicle_name,
                    "vdf": vdf_name,
                    "vtf": vtf_name,
                    "geo": geo_asset.name,
                    "part": part_transform.name,
                    "parent": part_transform.parent_name,
                    "face_index": face.index,
                    "raw_slot": raw_slot,
                    "normalized_slot": norm,
                    "material": material_key,
                    "resolved_kind": kind if resolved else "unresolved",
                    "resolved_name": resolved.name if resolved else "",
                    "texture_asset": texture_asset.name if texture_asset else "",
                    "confidence": confidence if resolved else "none",
                    "evidence": evidence if resolved else "unresolved",
                })

            v_base += len(geo_mesh.vertices)
            vn_base += len(geo_mesh.normals)
            obj.write("\n")

    with mtl_path.open("w", encoding="utf-8") as mtl:
        mtl.write(f"# Interstate '76 vehicle material export: {vehicle_name}\n")
        for name, mat in materials.items():
            r, g, b = mat["color"]
            mtl.write(f"\nnewmtl {name}\n")
            mtl.write(f"Kd {r/255.0:.6f} {g/255.0:.6f} {b/255.0:.6f}\n")
            mtl.write("Ka 0.000000 0.000000 0.000000\n")
            mtl.write("Ks 0.000000 0.000000 0.000000\n")
            mtl.write("d 1.0\n")
            if mat.get("map_kd"):
                mtl.write(f"map_Kd {mat['map_kd']}\n")

    return obj_path, mtl_path, materials, face_report




def find_bwd2_chunk_payload_by_tag(data: bytes, tag_wanted: str) -> Optional[bytes]:
    """Return BWD2 chunk payload by 4-byte tag, if present.

    Most I76 definition files use BWD2 chunks. VCF roots have a VCFC chunk with
    fixed-width resource refs. This helper is intentionally local and tolerant:
    if the data is not chunked as expected, it simply returns None.
    """
    try:
        for tag, _payload_off, payload in parse_bwd2_chunks(data):
            if tag.upper() == tag_wanted.upper():
                return payload
    except Exception:
        return None
    return None


def read_fixed_resource_name(payload: bytes, off: int, size: int = 13) -> str:
    if off < 0 or off >= len(payload):
        return ""
    raw = payload[off : min(len(payload), off + size)]
    return cstring(raw).strip()


def resolve_resource_ref_with_prefix_fallback(resolver, idx, ref: str, ext: str, source):
    """Resolve fixed-width refs with known leading-prefix contamination.

    VCF/VCFC sometimes contains variant prefixes before the actual resource
    basename, e.g. GUAMBAMZ1.VTF -> AMBAMZ1.VTF or IGUSKTVAN1.VTF -> SKTVAN1.VTF.
    Try exact, three explicit retail aliases, resolver's leading-byte trim,
    then a few known game prefixes.
    """
    if not ref:
        return None
    if "." not in ref:
        ref = ref + "." + ext.upper()

    a = idx.resolve(ref, ext, source=source, prefer_embedded=False)
    if a:
        return a

    rn = resolver.norm_name(ref)
    alias_ref = EXPLICIT_RETAIL_RESOURCE_ALIASES.get(rn)
    if alias_ref:
        a = idx.resolve(alias_ref, ext, source=source, prefer_embedded=False)
        if a:
            return a

    try:
        a = resolver.resolve_with_leading_byte_trim(idx, ref, ext, source=source, prefer_embedded=False)
        if a:
            return a
    except Exception:
        pass

    stem = rn.rsplit(".", 1)[0] if "." in rn else rn
    suffix = "." + ext.upper()
    prefixes = ["IGUSK", "IGU", "GUSK", "GU", "ULEP", "UROY", "U", "I", "G"]
    for pref in prefixes:
        if stem.startswith(pref) and len(stem) > len(pref) + 2:
            cand = stem[len(pref):] + suffix
            a = idx.resolve(cand, ext, source=source, prefer_embedded=False)
            if a:
                return a
            try:
                a = resolver.resolve_with_leading_byte_trim(idx, cand, ext, source=source, prefer_embedded=False)
                if a:
                    return a
            except Exception:
                pass

    # Last resort: try every leading trim up to 8 chars. This is only used for
    # VCF fixed fields, not general texture refs.
    for n in range(1, min(9, len(stem) - 2)):
        cand = stem[n:] + suffix
        a = idx.resolve(cand, ext, source=source, prefer_embedded=False)
        if a:
            return a

    return None


def parse_vcfc_fixed_refs(resolver, vcf_asset, vcf_data: bytes, idx):
    """Parse VCF root refs from VCFC fixed offsets.

    Recovered binary layout:
      VCFC payload +0x10 -> VDF ref
      VCFC payload +0x1d -> VTF ref
      VCFC payload +0x36/+0x43/+0x50 -> three WDF refs
      VCFC payload +0x2a/+0x2e/+0x32 -> component selectors, not resource names

    Returns:
      (vdf, vtf, wdfs, raw_vdf_ref, raw_vtf_ref, raw_wdf_refs, notes)
    """
    payload = find_bwd2_chunk_payload_by_tag(vcf_data, "VCFC")
    notes = []
    if payload is None:
        notes.append("no_vcfc_chunk")
        return None, None, [], "", "", [], ";".join(notes)

    raw_vdf = read_fixed_resource_name(payload, 0x10, 13)
    raw_vtf = read_fixed_resource_name(payload, 0x1d, 13)
    raw_wdfs = [
        read_fixed_resource_name(payload, 0x36, 13),
        read_fixed_resource_name(payload, 0x43, 13),
        read_fixed_resource_name(payload, 0x50, 13),
    ]

    vdf = resolve_resource_ref_with_prefix_fallback(resolver, idx, raw_vdf, "vdf", vcf_asset)
    vtf = resolve_resource_ref_with_prefix_fallback(resolver, idx, raw_vtf, "vtf", vcf_asset)
    wdfs = []
    for w in raw_wdfs:
        a = resolve_resource_ref_with_prefix_fallback(resolver, idx, w, "wdf", vcf_asset)
        if a and a.asset_id not in {x.asset_id for x in wdfs}:
            wdfs.append(a)

    if raw_vdf and not vdf:
        notes.append("raw_vdf_unresolved=" + raw_vdf)
    if raw_vtf and not vtf:
        notes.append("raw_vtf_unresolved=" + raw_vtf)

    return vdf, vtf, wdfs, raw_vdf, raw_vtf, raw_wdfs, ";".join(notes)


def parse_vcf_refs_with_vtf_aliases(resolver, vcf_asset, vcf_data: bytes, idx):
    """Parse VCF refs with direct VCFC offsets first, regex fallback second.

    v6 behavior:
      1. Parse VCFC fixed offsets directly.
      2. If VDF/VTF are still missing, fall back to resolver.parse_vcf_refs().
      3. For VTF, apply leading-prefix fallback to refs like GUAMBAMZ1.VTF.

    Returns:
      (vdf, vtf, wdfs, gdfs, raw_vdf_ref, raw_vtf_ref, notes)
    """
    fixed_vdf, fixed_vtf, fixed_wdfs, raw_vdf, raw_vtf, raw_wdfs, fixed_notes = parse_vcfc_fixed_refs(
        resolver, vcf_asset, vcf_data, idx
    )

    regex_vdf, regex_vtf, regex_wdfs, gdfs = resolver.parse_vcf_refs(vcf_asset, vcf_data, idx)

    vdf = fixed_vdf or regex_vdf
    vtf = fixed_vtf or regex_vtf
    wdfs = fixed_wdfs if fixed_wdfs else regex_wdfs

    notes = []
    if fixed_notes:
        notes.append("vcfc:" + fixed_notes)
    if fixed_vdf:
        notes.append("vdf_from_vcfc=" + fixed_vdf.name)
    elif regex_vdf:
        notes.append("vdf_from_regex=" + regex_vdf.name)
    if fixed_vtf:
        notes.append("vtf_from_vcfc=" + fixed_vtf.name)
    elif regex_vtf:
        notes.append("vtf_from_regex=" + regex_vtf.name)

    # Regex fallback for VTF aliases if neither fixed nor regex resolved.
    vtf_alias_ref = raw_vtf or ""
    if vtf is None:
        for ref in resolver.explicit_file_refs(vcf_data):
            if resolver.ext_of(ref) == "vtf":
                vtf_alias_ref = ref
                break
        if vtf_alias_ref:
            vtf = resolve_resource_ref_with_prefix_fallback(resolver, idx, vtf_alias_ref, "vtf", vcf_asset)
            if vtf:
                notes.append("vtf_from_alias_fallback=" + vtf.name)

    return vdf, vtf, wdfs, gdfs, raw_vdf, raw_vtf or vtf_alias_ref, ";".join(notes)


def write_tsv(path: Path, rows: Iterable[Dict[str, object]], fields: List[str]) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(fields) + "\n")
        for row in rows:
            vals = []
            for field in fields:
                vals.append(str(row.get(field, "")).replace("\t", " ").replace("\n", " ").replace("\r", " "))
            f.write("\t".join(vals) + "\n")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--zfs", required=True, type=Path)
    ap.add_argument("--zix", type=Path)
    ap.add_argument("--resolver", required=True, type=Path, help="Path to i76_vehicle_texture_slot_resolver_v5.py")
    ap.add_argument("--out", required=True, type=Path)
    ap.add_argument("--overwrite", action="store_true")
    ap.add_argument("--vehicle", action="append", default=[], help="Vehicle VCF stem/name filter, e.g. vcpolic1. Can be repeated.")
    ap.add_argument("--all", action="store_true", help="Export all VCF vehicles with VDF/VTF")
    ap.add_argument("--export-textures", action="store_true", help="Write PNG/PGM textures for resolved M16/VQM")
    ap.add_argument("--palette-file", type=Path, default=None, help="Optional 768-byte RGB palette/ACT file for color-correct M16/VQM PNG export")
    ap.add_argument("--palette-scale", choices=["auto", "raw", "x4"], default="auto", help="Palette scaling for --palette-file: auto scales 0..63 palettes by 4")
    ap.add_argument("--damage-state", type=int, default=0, choices=[0, 1, 2, 3], help="VGEO third-person damage-state part set to export")
    ap.add_argument("--tar", action="store_true", help="Also create a .tar.gz archive")
    ap.add_argument("--tar-out-dir", type=Path, default=None, help="Optional output directory for the .tar.gz archive. Defaults to beside --out.")
    args = ap.parse_args()

    if not args.all and not args.vehicle:
        raise SystemExit("Specify --vehicle <name> or --all")

    resolver = load_resolver(args.resolver)
    ensure_clean_dir(args.out, args.overwrite)
    palette_rgb = load_palette_file(args.palette_file, args.palette_scale)

    wanted_exts = {"vcf", "vdf", "vtf", "wdf", "gdf", "pix", "pak", "tmt", "map", "m16", "vqm", "cbk", "geo"}
    header, records = resolver.parse_zfs_records(args.zfs)
    payloads, errors = resolver.decompress_records(args.zfs, records, wanted_exts)
    idx, warnings = resolver.build_asset_index(records, payloads, None)

    vcf_assets = sorted([a for a in idx.assets if a.ext == "vcf" and a.source == "top_level"], key=lambda a: a.name.lower())
    filters = [v.lower().replace(".vcf", "") for v in args.vehicle]
    if not args.all:
        vcf_assets = [a for a in vcf_assets if any(f in a.name.lower().replace(".vcf", "") for f in filters)]

    vehicle_rows = []
    face_rows = []
    material_rows = []

    for vcf in vcf_assets:
        vcf_data = idx.payloads.get(vcf.asset_id, b"")
        vdf, vtf, _wdfs, _gdfs, raw_vdf_ref, raw_vtf_ref, vcf_ref_notes = parse_vcf_refs_with_vtf_aliases(resolver, vcf, vcf_data, idx)
        if not vdf or not vtf:
            vehicle_rows.append({"vehicle": vcf.name, "status": "missing_vdf_or_vtf", "vdf": vdf.name if vdf else raw_vdf_ref, "vtf": vtf.name if vtf else raw_vtf_ref, "parts": 0, "faces": 0, "materials": 0, "parse_errors": "could not resolve VDF or VTF via VCFC fixed offsets or regex fallback; " + vcf_ref_notes})
            continue

        vdf_data = idx.payloads.get(vdf.asset_id, b"")
        vtf_data = idx.payloads.get(vtf.asset_id, b"")
        transforms, transform_warnings = parse_vdf_geometry_transforms(vdf_data, args.damage_state)
        alternate_state_notes = [w for w in transform_warnings if w.startswith("alternate_")]
        transform_errors = [w for w in transform_warnings if not w.startswith("alternate_")]
        tmt_assets, map_assets = resolver.parse_vtf_slots(vtf, vtf_data, idx)
        map_ref_stems = resolver.parse_vtf_map_ref_stems(vtf, vtf_data, idx)

        part_rows = []
        parse_errors = list(transform_errors)
        seen_part_assets = set()
        for part_transform in transforms:
            if part_transform.name.upper() in {"WORLD", "NULL"}:
                continue
            geo_asset = idx.resolve(part_transform.name, "geo", source=vdf)
            if not geo_asset:
                # SOBJ can occasionally name a scene/root object that has no direct
                # embedded GEO in the vehicle package; report other misses.
                if part_transform.source != "SOBJ":
                    parse_errors.append(f"missing GEO for VDF part {part_transform.name}")
                continue
            key = (part_transform.name.upper(), geo_asset.asset_id)
            if key in seen_part_assets:
                continue
            seen_part_assets.add(key)
            data = idx.payloads.get(geo_asset.asset_id, b"")
            try:
                mesh = parse_geo(data)
                part_rows.append((geo_asset, mesh, part_transform, tmt_assets, map_assets, map_ref_stems, vdf.name, vtf.name))
            except Exception as e:
                parse_errors.append(f"{geo_asset.name}: {e}")

        vdir = args.out / safe_name(vcf.name)
        vdir.mkdir(parents=True, exist_ok=True)
        if part_rows:
            obj_path, mtl_path, materials, report = write_obj_mtl(vdir, vcf.name, part_rows, args.export_textures, resolver, idx, palette_rgb)
            face_rows.extend(report)
            for mname, mat in materials.items():
                material_rows.append({"vehicle": vcf.name, "material": mname, **mat})
            faces = sum(len(p[1].faces) for p in part_rows)
            vehicle_rows.append({
                "vehicle": vcf.name,
                "status": "ok" if not parse_errors else "partial",
                "vdf": vdf.name,
                "vtf": vtf.name,
                "parts": len(part_rows),
                "faces": faces,
                "materials": len(materials),
                "obj": obj_path.relative_to(args.out).as_posix(),
                "mtl": mtl_path.relative_to(args.out).as_posix(),
                "alternate_state_note_count": len(alternate_state_notes),
                "alternate_state_notes": "; ".join(alternate_state_notes[:60]),
                "parse_errors": "; ".join((([vcf_ref_notes] if vcf_ref_notes else []) + parse_errors)[:20]),
            })
        else:
            vehicle_rows.append({"vehicle": vcf.name, "status": "no_geo_parts", "vdf": vdf.name, "vtf": vtf.name, "parts": 0, "faces": 0, "materials": 0, "alternate_state_note_count": len(alternate_state_notes), "alternate_state_notes": "; ".join(alternate_state_notes[:60]), "parse_errors": "; ".join(parse_errors[:20])})

    write_tsv(args.out / "vehicle_export_summary.tsv", vehicle_rows, ["vehicle", "status", "vdf", "vtf", "parts", "faces", "materials", "obj", "mtl", "alternate_state_note_count", "alternate_state_notes", "parse_errors"])
    if face_rows:
        write_tsv(args.out / "face_material_resolution.tsv", face_rows, ["vehicle", "vdf", "vtf", "geo", "part", "parent", "face_index", "raw_slot", "normalized_slot", "material", "resolved_kind", "resolved_name", "texture_asset", "confidence", "evidence"])
    if material_rows:
        write_tsv(args.out / "materials.tsv", material_rows, ["vehicle", "material", "name", "raw_slot", "normalized_slot", "resolved_kind", "resolved_name", "resolved_asset_id", "texture_asset_name", "texture_asset_id", "confidence", "evidence", "color", "map_kd"])

    summary = {
        "zfs_header": header,
        "damage_state": args.damage_state,
        "vehicles_requested": len(vcf_assets),
        "vehicles_exported": sum(1 for r in vehicle_rows if r.get("status") in {"ok", "partial"}),
        "faces": len(face_rows),
        "materials": len(material_rows),
        "alternate_state_notes": sum(int(r.get("alternate_state_note_count", 0) or 0) for r in vehicle_rows),
        "zfs_errors": len(errors),
        "pix_pak_warnings": len(warnings),
        "notes": "VDF SOBJ/VGEO state-0 hierarchy is applied; alternate damage GEOs are bound by VGEO slot index; VTF refs use exact plus leading-prefix fallback.",
    }
    (args.out / "summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True), encoding="utf-8")
    (args.out / "README.txt").write_text("""I76 vehicle GEO OBJ exporter v9

Outputs:
  summary.json
  vehicle_export_summary.tsv
  face_material_resolution.tsv
  materials.tsv
  <vehicle>/<vehicle>.obj
  <vehicle>/<vehicle>.mtl
  <vehicle>/textures/*    when --export-textures is used

Archive option:
  --tar creates <out>.tar.gz by default.
  --tar-out-dir DIR writes the archive to DIR/<out-name>.tar.gz instead.

Important:
  * GEO parser follows Open76's GeoParser layout.
  * VTF/TMT texture list interpretation follows Open76 VtfParser:
    78 TMT filenames and 13 MAP entries; TMT texture names are packed
    8-byte strings.
  * Parts are transformed through VDF SOBJ/VGEO hierarchy.
  * Damage states 1-3 use the state-0 VGEO hierarchy and bind alternate GEO names by VGEO slot index; state-N parent strings are diagnostic only.
  * Exported M16/VQM textures are grayscale palette-index previews unless
    --palette-file is supplied. With --palette-file, texture PNGs are RGB using
    the selected 256-color palette.
""", encoding="utf-8")

    if args.tar:
        if args.tar_out_dir is not None:
            args.tar_out_dir.mkdir(parents=True, exist_ok=True)
            tar_path = args.tar_out_dir / (args.out.name + ".tar.gz")
        else:
            tar_path = args.out.with_suffix(".tar.gz")
        if tar_path.exists():
            tar_path.unlink()
        with tarfile.open(tar_path, "w:gz") as tf:
            tf.add(args.out, arcname=args.out.name)
        print(f"Archive: {tar_path}")

    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
