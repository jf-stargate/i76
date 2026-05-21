#!/usr/bin/env python3
"""
Interstate '76 Open76-aligned terrain OBJ exporter, v6.

Fix over v5:
  v5 removed geometric gaps by emitting 129x129 vertices per patch, but each patch
  still owned duplicate seam vertices. In Blender, those duplicate coincident vertices
  cause visible lighting ridges at 128/640 patch boundaries because normals are split.

v6 exports a welded global mesh:
  - one shared vertex per world grid coordinate
  - no duplicate seam vertices between adjacent patches
  - one OBJ object/group by mission, not one split object per patch
  - optional OBJ vertex normals computed from the welded mesh
  - still uses Open76-compatible patch placement and height decode

Coordinate modes:
  blender: v X Z HEIGHT  and vn nx nz nh  (Blender-native Z-up when imported as-is)
  y-up:    v X HEIGHT Z  and vn nx nh nz  (traditional OBJ/Y-up)

Example:
  python3 i76_level_blender_export_open76_v6.py "game/interstate 76/miss16" \
    --out-dir scratch_data/i76_blender_pkg_open76_v6 \
    --mission-filter m06 \
    --origin open76-centered \
    --obj-coordinates blender \
    --write-normals \
    --fail-empty
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import math
import struct
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


PAGE_W = 128
PAGE_H = 128
PATCH_SIZE_WORLD = 640.0
PAGE_SIZE = PAGE_W * PAGE_H * 2
DEFAULT_SAMPLE_SCALE = PATCH_SIZE_WORLD / PAGE_W
DEFAULT_VERTICAL_SCALE = 409.5 / 4096.0


@dataclasses.dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ""

    @property
    def end(self) -> int:
        return self.offset + self.size


CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def fourcc(data: bytes, off: int) -> str:
    return data[off:off + 4].decode("ascii", errors="replace")


def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out: List[Chunk] = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        size = u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        out.append(Chunk(tag, off, size, off + 8, size - 8, parent))
        off += size
    return out


def parse_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat(data, 0, len(data), "")

    def rec(chunks: List[Chunk]) -> List[Chunk]:
        all_chunks: List[Chunk] = []
        for c in chunks:
            all_chunks.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    all_chunks.extend(rec(kids))
        return all_chunks

    return rec(roots)


def first_chunk(chunks: List[Chunk], tag: str) -> Optional[Chunk]:
    for c in chunks:
        if c.tag == tag:
            return c
    return None


@dataclasses.dataclass
class ZMap:
    active_count: int
    cells: List[int]

    def used_cells(self) -> List[Tuple[int, int, int]]:
        out = []
        for z in range(80):
            for x in range(80):
                idx = self.cells[z * 80 + x]
                if idx != 0xFF:
                    out.append((x, z, idx))
        return out

    def bounds(self) -> Optional[Tuple[int, int, int, int]]:
        used = self.used_cells()
        if not used:
            return None
        xs = [u[0] for u in used]
        zs = [u[1] for u in used]
        return min(xs), min(zs), max(xs), max(zs)

    def middle(self) -> Tuple[float, float]:
        b = self.bounds()
        if b is None:
            return 0.0, 0.0
        min_x, min_z, max_x, max_z = b
        return (min_x + max_x) / 2.0, (min_z + max_z) / 2.0

    def get(self, x: int, z: int) -> int:
        if x < 0 or z < 0 or x >= 80 or z >= 80:
            return 0xFF
        return self.cells[z * 80 + x]

    def to_dict(self) -> dict:
        b = self.bounds()
        return {
            "active_count": self.active_count,
            "used_patch_count": len(self.used_cells()),
            "bounds": list(b) if b else None,
            "middle": list(self.middle()),
            "used_cells": [{"x": x, "z": z, "page": p} for x, z, p in self.used_cells()],
        }


def decode_zmap(data: bytes, chunks: List[Chunk]) -> Optional[ZMap]:
    c = first_chunk(chunks, "ZMAP")
    if c is None:
        return None
    if c.payload_size < 1 + 80 * 80:
        raise ValueError(f"ZMAP too small at 0x{c.offset:x}")
    return ZMap(data[c.payload_offset], list(data[c.payload_offset + 1:c.payload_offset + 1 + 80 * 80]))


def decode_zone_sidecar_name(data: bytes, chunks: List[Chunk]) -> str:
    c = first_chunk(chunks, "ZONE")
    if c is None:
        return ""
    payload = data[c.payload_offset:c.end]
    candidates = []
    if len(payload) > 1:
        candidates.append(payload[1:].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip())
    if len(payload) > 9:
        candidates.append(payload[9:].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip())
    for s in candidates:
        if s and "." in s:
            return s
    for s in candidates:
        if s:
            return s
    return ""


def find_files(root: Path) -> List[Path]:
    if root.is_file():
        return [root]
    return [p for p in root.rglob("*") if p.is_file()]


def find_sidecar(msn: Path, sidecar_name: str, by_name: Dict[str, Path]) -> Optional[Path]:
    candidates = []
    if sidecar_name:
        candidates.extend([
            msn.parent / sidecar_name,
            msn.parent / sidecar_name.upper(),
            msn.parent / sidecar_name.lower(),
            by_name.get(sidecar_name.lower()),
        ])
    for ext in (".ter", ".tab"):
        candidates.extend([
            msn.with_suffix(ext),
            msn.with_suffix(ext.upper()),
            by_name.get(msn.stem.lower() + ext),
        ])
    for c in candidates:
        if c is not None and Path(c).exists():
            return Path(c)
    return None


def load_ter_pages(path: Path, expected_count: int) -> List[Tuple[int, ...]]:
    data = path.read_bytes()
    if len(data) % PAGE_SIZE != 0:
        raise ValueError(f"{path} size 0x{len(data):x} is not a multiple of 0x{PAGE_SIZE:x}")
    count = len(data) // PAGE_SIZE
    if expected_count and count < expected_count:
        raise ValueError(f"{path} has {count} pages but ZMAP expects {expected_count}")
    return [
        struct.unpack_from("<" + "H" * (PAGE_W * PAGE_H), data, i * PAGE_SIZE)
        for i in range(count)
    ]


def sample_page(pages: List[Tuple[int, ...]], page_idx: int, x: int, z: int) -> int:
    if page_idx == 0xFF or page_idx < 0 or page_idx >= len(pages):
        return 0
    x = max(0, min(PAGE_W - 1, x))
    z = max(0, min(PAGE_H - 1, z))
    return pages[page_idx][z * PAGE_W + x]


def stitched_sample(
    pages: List[Tuple[int, ...]],
    zmap: ZMap,
    cell_x: int,
    cell_z: int,
    local_x: int,
    local_z: int,
    edge_mode: str,
) -> int:
    own = zmap.get(cell_x, cell_z)

    if local_x < PAGE_W and local_z < PAGE_H:
        return sample_page(pages, own, local_x, local_z)

    if local_x == PAGE_W and local_z < PAGE_H:
        right = zmap.get(cell_x + 1, cell_z)
        if right != 0xFF:
            return sample_page(pages, right, 0, local_z)

    if local_z == PAGE_H and local_x < PAGE_W:
        bottom = zmap.get(cell_x, cell_z + 1)
        if bottom != 0xFF:
            return sample_page(pages, bottom, local_x, 0)

    if local_x == PAGE_W and local_z == PAGE_H:
        br = zmap.get(cell_x + 1, cell_z + 1)
        if br != 0xFF:
            return sample_page(pages, br, 0, 0)

    if edge_mode == "zero":
        return 0
    if edge_mode == "clamp":
        return sample_page(pages, own, min(local_x, PAGE_W - 1), min(local_z, PAGE_H - 1))

    raise ValueError(f"unknown edge mode: {edge_mode}")


def world_offset_for_origin(zmap: ZMap, origin_mode: str) -> Tuple[float, float]:
    if origin_mode == "absolute":
        return 0.0, 0.0

    b = zmap.bounds()
    if b is None:
        return 0.0, 0.0
    min_x, min_z, max_x, max_z = b

    if origin_mode == "min-corner":
        return min_x * PATCH_SIZE_WORLD, min_z * PATCH_SIZE_WORLD

    if origin_mode == "open76-centered":
        mid_x, mid_z = zmap.middle()
        return mid_x * PATCH_SIZE_WORLD, mid_z * PATCH_SIZE_WORLD

    raise ValueError(f"unknown origin mode: {origin_mode}")


def convert_vertex(wx: float, wz: float, h: float, obj_coordinates: str) -> Tuple[float, float, float]:
    if obj_coordinates == "blender":
        return wx, wz, h
    if obj_coordinates == "y-up":
        return wx, h, wz
    raise ValueError(f"unknown OBJ coordinate mode: {obj_coordinates}")


def convert_normal(nx: float, nz: float, nh: float, obj_coordinates: str) -> Tuple[float, float, float]:
    if obj_coordinates == "blender":
        return nx, nz, nh
    if obj_coordinates == "y-up":
        return nx, nh, nz
    raise ValueError(f"unknown OBJ coordinate mode: {obj_coordinates}")


def vsub(a, b):
    return (a[0] - b[0], a[1] - b[1], a[2] - b[2])


def cross(a, b):
    return (
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    )


def normalize(v):
    length = math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
    if length <= 1e-12:
        return (0.0, 0.0, 1.0)
    return (v[0] / length, v[1] / length, v[2] / length)


def build_welded_mesh(
    pages: List[Tuple[int, ...]],
    zmap: ZMap,
    origin_mode: str,
    edge_mode: str,
    vertical_scale: float,
) -> Tuple[List[Tuple[float, float, float]], List[Tuple[int, int, int, int]], Dict[str, int]]:
    offset_x, offset_z = world_offset_for_origin(zmap, origin_mode)

    vertex_index_by_grid: Dict[Tuple[int, int], int] = {}
    vertices_world: List[Tuple[float, float, float]] = []
    faces: List[Tuple[int, int, int, int]] = []

    def get_vertex(cell_x: int, cell_z: int, local_x: int, local_z: int) -> int:
        # Global integer sample coordinate. Adjacent patches share the same key at seams.
        gx = cell_x * PAGE_W + local_x
        gz = cell_z * PAGE_H + local_z
        key = (gx, gz)
        idx = vertex_index_by_grid.get(key)
        if idx is not None:
            return idx

        word = stitched_sample(pages, zmap, cell_x, cell_z, local_x, local_z, edge_mode)
        h = (word & 0x0FFF) * vertical_scale
        wx = gx * DEFAULT_SAMPLE_SCALE - offset_x
        wz = gz * DEFAULT_SAMPLE_SCALE - offset_z
        vertices_world.append((wx, wz, h))
        idx = len(vertices_world)  # 1-based OBJ index
        vertex_index_by_grid[key] = idx
        return idx

    for cell_x, cell_z, page_idx in zmap.used_cells():
        for local_z in range(PAGE_H):
            for local_x in range(PAGE_W):
                v0 = get_vertex(cell_x, cell_z, local_x, local_z)
                v1 = get_vertex(cell_x, cell_z, local_x + 1, local_z)
                v2 = get_vertex(cell_x, cell_z, local_x + 1, local_z + 1)
                v3 = get_vertex(cell_x, cell_z, local_x, local_z + 1)
                faces.append((v0, v1, v2, v3))

    stats = {
        "unique_vertices": len(vertices_world),
        "faces": len(faces),
        "duplicate_seam_vertices_removed_estimate": len(zmap.used_cells()) * (PAGE_W + 1) * (PAGE_H + 1) - len(vertices_world),
    }
    return vertices_world, faces, stats


def compute_vertex_normals(vertices_world: List[Tuple[float, float, float]], faces: List[Tuple[int, int, int, int]]) -> List[Tuple[float, float, float]]:
    acc = [[0.0, 0.0, 0.0] for _ in vertices_world]

    for face in faces:
        # Convert 1-based to 0-based.
        p0 = vertices_world[face[0] - 1]
        p1 = vertices_world[face[1] - 1]
        p2 = vertices_world[face[2] - 1]
        p3 = vertices_world[face[3] - 1]

        # Two triangles for robust normal accumulation.
        for a, b, c in ((p0, p1, p2), (p0, p2, p3)):
            n = cross(vsub(b, a), vsub(c, a))
            for p in (a, b, c):
                # Need corresponding index; easiest below with explicit face vertices.
                pass

        # Accumulate quad normal uniformly. This is sufficient for smoothing.
        n1 = cross(vsub(p1, p0), vsub(p2, p0))
        n2 = cross(vsub(p2, p0), vsub(p3, p0))
        n = (n1[0] + n2[0], n1[1] + n2[1], n1[2] + n2[2])
        for vi in face:
            acc[vi - 1][0] += n[0]
            acc[vi - 1][1] += n[1]
            acc[vi - 1][2] += n[2]

    return [normalize((v[0], v[1], v[2])) for v in acc]


def write_mission_obj(
    obj_path: Path,
    msn_path: Path,
    ter_path: Path,
    zmap: ZMap,
    pages: List[Tuple[int, ...]],
    *,
    origin_mode: str,
    obj_coordinates: str,
    edge_mode: str,
    vertical_scale: float,
    write_normals: bool,
) -> dict:
    obj_path.parent.mkdir(parents=True, exist_ok=True)

    vertices_world, faces, stats = build_welded_mesh(pages, zmap, origin_mode, edge_mode, vertical_scale)
    normals_world = compute_vertex_normals(vertices_world, faces) if write_normals else []

    with obj_path.open("w", encoding="utf-8") as f:
        f.write("# Interstate '76 Open76-aligned welded terrain OBJ v6\n")
        f.write(f"# msn={msn_path.name} ter={ter_path.name}\n")
        f.write(f"# origin_mode={origin_mode} obj_coordinates={obj_coordinates} edge_mode={edge_mode}\n")
        f.write("# one shared vertex per global terrain sample coordinate; seams are welded\n")
        f.write(f"o {msn_path.stem}_terrain\n")
        f.write(f"g {msn_path.stem}_terrain\n")

        for wx, wz, h in vertices_world:
            vx, vy, vz = convert_vertex(wx, wz, h, obj_coordinates)
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")

        if write_normals:
            for nx, nz, nh in normals_world:
                vx, vy, vz = convert_normal(nx, nz, nh, obj_coordinates)
                f.write(f"vn {vx:.8f} {vy:.8f} {vz:.8f}\n")

        if write_normals:
            for a, b, c, d in faces:
                f.write(f"f {a}//{a} {b}//{b} {c}//{c} {d}//{d}\n")
        else:
            for a, b, c, d in faces:
                f.write(f"f {a} {b} {c} {d}\n")

    return {
        "obj_path": str(obj_path),
        "vertices": len(vertices_world),
        "faces": len(faces),
        "origin_mode": origin_mode,
        "obj_coordinates": obj_coordinates,
        "edge_mode": edge_mode,
        "write_normals": write_normals,
        **stats,
    }


def export(input_path: Path, out_dir: Path, mission_filter: str, origin_mode: str, obj_coordinates: str, edge_mode: str, vertical_scale: float, write_normals: bool, fail_empty: bool) -> dict:
    files = find_files(input_path)
    by_name = {p.name.lower(): p for p in files}
    missions = [p for p in files if p.suffix.lower() in {".msn", ".lvl", ".spc"}]
    if mission_filter:
        missions = [p for p in missions if mission_filter.lower() in p.stem.lower() or mission_filter.lower() in p.name.lower()]

    out_dir.mkdir(parents=True, exist_ok=True)
    obj_dir = out_dir / "terrain_obj"

    manifest = {
        "format": "i76_open76_welded_terrain_obj_manifest",
        "version": 6,
        "source": str(input_path),
        "mission_filter": mission_filter,
        "origin_mode": origin_mode,
        "obj_coordinates": obj_coordinates,
        "edge_mode": edge_mode,
        "vertical_scale": vertical_scale,
        "write_normals": write_normals,
        "terrain": [],
        "warnings": [],
    }

    for msn in sorted(missions):
        try:
            data = msn.read_bytes()
            chunks = parse_tree(data)
            zmap = decode_zmap(data, chunks)
            if zmap is None:
                manifest["warnings"].append(f"{msn}: no ZMAP")
                continue

            sidecar_name = decode_zone_sidecar_name(data, chunks)
            ter = find_sidecar(msn, sidecar_name, by_name)
            if ter is None:
                manifest["warnings"].append(f"{msn}: no sidecar found for {sidecar_name!r}")
                continue

            pages = load_ter_pages(ter, zmap.active_count)
            obj_path = obj_dir / f"{msn.stem.lower()}.terrain.obj"
            obj_info = write_mission_obj(
                obj_path,
                msn,
                ter,
                zmap,
                pages,
                origin_mode=origin_mode,
                obj_coordinates=obj_coordinates,
                edge_mode=edge_mode,
                vertical_scale=vertical_scale,
                write_normals=write_normals,
            )
            manifest["terrain"].append({
                "mission": str(msn),
                "sidecar": str(ter),
                "zone_sidecar_name": sidecar_name,
                "zmap": zmap.to_dict(),
                **obj_info,
            })
        except Exception as e:
            manifest["warnings"].append(f"{msn}: {type(e).__name__}: {e}")

    manifest_path = out_dir / "i76_open76_welded_terrain_obj_manifest_v6.json"
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    print(json.dumps({
        "manifest": str(manifest_path),
        "missions_seen": len(missions),
        "terrain_objs": len(manifest["terrain"]),
        "warnings": len(manifest["warnings"]),
    }, indent=2))

    if fail_empty and not manifest["terrain"]:
        raise SystemExit("no terrain OBJs generated")

    return manifest


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("input", type=Path, help="Directory containing .MSN/.LVL/.SPC and .TER sidecars")
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--mission-filter", default="", help="Substring filter, e.g. m06, s05, t05")
    ap.add_argument("--origin", choices=["open76-centered", "min-corner", "absolute"], default="open76-centered")
    ap.add_argument("--obj-coordinates", choices=["blender", "y-up"], default="blender")
    ap.add_argument("--edge-mode", choices=["clamp", "zero"], default="clamp")
    ap.add_argument("--vertical-scale", type=float, default=DEFAULT_VERTICAL_SCALE)
    ap.add_argument("--write-normals", action="store_true", help="Write welded vertex normals into OBJ")
    ap.add_argument("--fail-empty", action="store_true")
    args = ap.parse_args()

    export(
        args.input,
        args.out_dir,
        args.mission_filter,
        args.origin,
        args.obj_coordinates,
        args.edge_mode,
        args.vertical_scale,
        args.write_normals,
        args.fail_empty,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
