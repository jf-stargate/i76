#!/usr/bin/env python3
"""
Interstate '76 runtime dense terrain OBJ exporter, v5.

Purpose:
  This is the mesh-quality baseline exporter after the adaptive v1-v4 experiments.
  It intentionally does NOT use the approximate runtime LOD predicate.

What is runtime-aligned here:
  - BWD2 mission chunk parsing.
  - TDEF / ZMAP / ZONE extraction.
  - .TER sidecar pages: 0x8000 bytes each, 128x128 little-endian uint16.
  - Runtime-style 128x128 page-pointer grid with ZMAP copied at +24,+24.
  - Height lookup through the +0x0c00 sample bias and 0x7f local masks.
  - Surface class decode as word >> 13.

What is intentionally not modeled here:
  - Adaptive runtime tessellation from 00490a00 / 004911e0.
  - Terrain primitive node / edge-record emission.
  - Hardware/software polygon work-record submission.

The output mesh is dense and welded, matching the useful density of the prior
Open76-aligned v7 exporter: one quad per terrain sample interval, with shared
vertices across page seams.
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import math
import os
import shutil
import struct
import subprocess
import tarfile
import time
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


PAGE_W = 128
PAGE_H = 128
PAGE_SIZE = PAGE_W * PAGE_H * 2
ZMAP_W = 80
ZMAP_H = 80
RUNTIME_GRID_W = 128
RUNTIME_GRID_H = 128
ZMAP_RUNTIME_OFFSET = 24
LOOKUP_BIAS_SAMPLES = 0x0C00
PATCH_SIZE_WORLD = 640.0
SAMPLE_SIZE_WORLD = PATCH_SIZE_WORLD / PAGE_W
DEFAULT_VERTICAL_SCALE = 409.5 / 4096.0
DEFAULT_ROOT = Path("/media/neon-remote/prj/i76/scratch_data")


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


@dataclasses.dataclass
class ZMap:
    active_count: int
    cells: List[int]

    def get(self, x: int, z: int) -> int:
        if x < 0 or z < 0 or x >= ZMAP_W or z >= ZMAP_H:
            return 0xFF
        return self.cells[z * ZMAP_W + x]

    def used_cells(self) -> List[Tuple[int, int, int]]:
        out: List[Tuple[int, int, int]] = []
        for z in range(ZMAP_H):
            for x in range(ZMAP_W):
                page = self.get(x, z)
                if page != 0xFF:
                    out.append((x, z, page))
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
        return (min_x + max_x + 1) * 0.5, (min_z + max_z + 1) * 0.5

    def summary(self) -> dict:
        used = self.used_cells()
        hist: Dict[int, int] = {}
        for _, _, page in used:
            hist[page] = hist.get(page, 0) + 1
        b = self.bounds()
        return {
            "active_count": self.active_count,
            "used_cell_count": len(used),
            "bounds": list(b) if b else None,
            "middle_cells": list(self.middle()),
            "unique_page_indices_in_zmap": sorted(hist.keys()),
            "page_histogram": {str(k): v for k, v in sorted(hist.items())},
            "used_cells": [{"x": x, "z": z, "page": p} for x, z, p in used],
        }


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
        out: List[Chunk] = []
        for c in chunks:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                out.extend(rec(parse_flat(data, c.payload_offset, c.end, c.tag)))
        return out

    return rec(roots)


def first_chunk(chunks: List[Chunk], tag: str, parent: Optional[str] = None) -> Optional[Chunk]:
    for c in chunks:
        if c.tag == tag and (parent is None or c.parent == parent):
            return c
    return None


def decode_zmap(data: bytes, chunks: List[Chunk]) -> Optional[ZMap]:
    c = first_chunk(chunks, "ZMAP", "TDEF") or first_chunk(chunks, "ZMAP")
    if c is None:
        return None
    if c.payload_size < 1 + ZMAP_W * ZMAP_H:
        raise ValueError(f"ZMAP too small at 0x{c.offset:x}: payload_size={c.payload_size}")
    return ZMap(
        active_count=data[c.payload_offset],
        cells=list(data[c.payload_offset + 1:c.payload_offset + 1 + ZMAP_W * ZMAP_H]),
    )


def decode_zone_sidecar_name(data: bytes, chunks: List[Chunk]) -> str:
    c = first_chunk(chunks, "ZONE", "TDEF") or first_chunk(chunks, "ZONE")
    if c is None:
        return ""
    payload = data[c.payload_offset:c.end]
    candidates: List[str] = []
    for start in (0, 1, 4, 8, 9):
        if len(payload) > start:
            s = payload[start:].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip()
            if s:
                candidates.append(s)
    for s in candidates:
        if "." in s:
            return s
    return candidates[0] if candidates else ""


def find_files(root: Path) -> List[Path]:
    if root.is_file():
        return [root]
    return [p for p in root.rglob("*") if p.is_file()]


def find_sidecar(msn: Path, sidecar_name: str, by_name: Dict[str, Path]) -> Optional[Path]:
    candidates: List[Optional[Path]] = []
    if sidecar_name:
        candidates.extend([
            msn.parent / sidecar_name,
            msn.parent / sidecar_name.upper(),
            msn.parent / sidecar_name.lower(),
            by_name.get(sidecar_name.lower()),
        ])
    candidates.extend([
        msn.with_suffix(".ter"),
        msn.with_suffix(".TER"),
        by_name.get(msn.stem.lower() + ".ter"),
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
    fmt = "<" + "H" * (PAGE_W * PAGE_H)
    return [struct.unpack_from(fmt, data, i * PAGE_SIZE) for i in range(count)]


def build_runtime_page_grid(zmap: ZMap, default_page: int = 0) -> List[int]:
    # Mirrors the observed 00493080 shape: initialize all slots to a default page
    # and copy active ZMAP cells into the 128x128 grid at +24,+24.
    grid = [default_page] * (RUNTIME_GRID_W * RUNTIME_GRID_H)
    for z in range(ZMAP_H):
        for x in range(ZMAP_W):
            page = zmap.get(x, z)
            if page == 0xFF:
                continue
            gx = x + ZMAP_RUNTIME_OFFSET
            gz = z + ZMAP_RUNTIME_OFFSET
            if 0 <= gx < RUNTIME_GRID_W and 0 <= gz < RUNTIME_GRID_H:
                grid[gz * RUNTIME_GRID_W + gx] = page
    return grid


def page_grid_summary(grid: List[int], zmap: ZMap) -> dict:
    hist: Dict[int, int] = {}
    for page in grid:
        hist[page] = hist.get(page, 0) + 1

    active_slots = []
    for x, z, page in zmap.used_cells():
        active_slots.append({
            "zmap_x": x,
            "zmap_z": z,
            "grid_x": x + ZMAP_RUNTIME_OFFSET,
            "grid_z": z + ZMAP_RUNTIME_OFFSET,
            "page": page,
        })

    return {
        "grid_w": RUNTIME_GRID_W,
        "grid_h": RUNTIME_GRID_H,
        "zmap_offset": ZMAP_RUNTIME_OFFSET,
        "lookup_bias_samples": LOOKUP_BIAS_SAMPLES,
        "page_index_histogram": {str(k): v for k, v in sorted(hist.items())},
        "active_slot_count": len(active_slots),
        "active_slots": active_slots,
    }


def sample_page_word(pages: List[Tuple[int, ...]], page: int, lx: int, lz: int) -> int:
    if page < 0 or page >= len(pages):
        return 0
    lx = max(0, min(PAGE_W - 1, lx))
    lz = max(0, min(PAGE_H - 1, lz))
    return pages[page][lz * PAGE_W + lx]


def runtime_lookup_word(pages: List[Tuple[int, ...]], page_grid: List[int], sample_x: int, sample_z: int) -> int:
    bx = sample_x + LOOKUP_BIAS_SAMPLES
    bz = sample_z + LOOKUP_BIAS_SAMPLES
    grid_x = (bx >> 7) & 0x7F
    grid_z = (bz >> 7) & 0x7F
    local_x = bx & 0x7F
    local_z = bz & 0x7F
    page = page_grid[grid_z * RUNTIME_GRID_W + grid_x]
    return sample_page_word(pages, page, local_x, local_z)


def stitched_boundary_word(
    pages: List[Tuple[int, ...]],
    zmap: ZMap,
    page_grid: List[int],
    sample_x: int,
    sample_z: int,
    bounds: Tuple[int, int, int, int],
    mode: str,
) -> int:
    if mode == "runtime-strict":
        return runtime_lookup_word(pages, page_grid, sample_x, sample_z)

    min_cx, min_cz, max_cx, max_cz = bounds
    min_sample_x = min_cx * PAGE_W
    min_sample_z = min_cz * PAGE_H
    max_sample_x = (max_cx + 1) * PAGE_W
    max_sample_z = (max_cz + 1) * PAGE_H

    # Dense mesh needs the final seam coordinate to close the region. The runtime
    # lookup at exactly max_sample_x/max_sample_z advances into the next page slot.
    # For OBJ export, clamp only the outer active-region border back to the last
    # valid sample. Interior seams remain true runtime samples and weld correctly.
    lookup_x = sample_x
    lookup_z = sample_z
    if mode in {"clamp-outer-active-edge", "average-outer-active-edge"}:
        if sample_x == max_sample_x:
            lookup_x = sample_x - 1
        if sample_z == max_sample_z:
            lookup_z = sample_z - 1

    word = runtime_lookup_word(pages, page_grid, lookup_x, lookup_z)

    if mode != "average-outer-active-edge":
        return word

    # Average only the height component with the strict lookup at the border.
    # Preserve the clamped word's surface bits, which avoids introducing default-page
    # materials at the mesh border.
    if sample_x == max_sample_x or sample_z == max_sample_z:
        strict = runtime_lookup_word(pages, page_grid, sample_x, sample_z)
        h = int(round(((word & 0x0FFF) + (strict & 0x0FFF)) * 0.5)) & 0x0FFF
        return (word & 0xF000) | h

    return word


def world_offset_for_origin(zmap: ZMap, origin: str) -> Tuple[float, float]:
    b = zmap.bounds()
    if b is None:
        return 0.0, 0.0
    min_x, min_z, max_x, max_z = b
    if origin == "absolute":
        return 0.0, 0.0
    if origin == "min-corner":
        return min_x * PATCH_SIZE_WORLD, min_z * PATCH_SIZE_WORLD
    if origin == "open76-centered":
        mid_x, mid_z = zmap.middle()
        return mid_x * PATCH_SIZE_WORLD, mid_z * PATCH_SIZE_WORLD
    raise ValueError(f"unknown origin mode: {origin}")


def convert_vertex(wx: float, wz: float, h: float, mode: str) -> Tuple[float, float, float]:
    if mode == "blender":
        return wx, wz, h
    if mode == "y-up":
        return wx, h, wz
    raise ValueError(f"unknown OBJ coordinate mode: {mode}")


def convert_normal(nx: float, nz: float, nh: float, mode: str) -> Tuple[float, float, float]:
    if mode == "blender":
        return nx, nz, nh
    if mode == "y-up":
        return nx, nh, nz
    raise ValueError(f"unknown OBJ coordinate mode: {mode}")


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


def build_dense_welded_mesh(
    pages: List[Tuple[int, ...]],
    zmap: ZMap,
    page_grid: List[int],
    origin: str,
    boundary_sampling: str,
    vertical_scale: float,
) -> Tuple[List[Tuple[float, float, float]], List[Tuple[int, int, int, int]], dict]:
    b = zmap.bounds()
    if b is None:
        return [], [], {"empty": True}

    min_cx, min_cz, max_cx, max_cz = b
    min_sx = min_cx * PAGE_W
    min_sz = min_cz * PAGE_H
    max_sx = (max_cx + 1) * PAGE_W
    max_sz = (max_cz + 1) * PAGE_H

    offset_x, offset_z = world_offset_for_origin(zmap, origin)

    vertex_index: Dict[Tuple[int, int], int] = {}
    vertices: List[Tuple[float, float, float]] = []
    faces: List[Tuple[int, int, int, int]] = []

    surface_hist: Dict[int, int] = {}

    def get_vertex(sx: int, sz: int) -> int:
        key = (sx, sz)
        idx = vertex_index.get(key)
        if idx is not None:
            return idx

        word = stitched_boundary_word(pages, zmap, page_grid, sx, sz, b, boundary_sampling)
        h = (word & 0x0FFF) * vertical_scale
        wx = sx * SAMPLE_SIZE_WORLD - offset_x
        wz = sz * SAMPLE_SIZE_WORLD - offset_z
        vertices.append((wx, wz, h))
        idx = len(vertices)  # OBJ is 1-based.
        vertex_index[key] = idx
        return idx

    # Emit dense quads only for active ZMAP cells. Non-rectangular terrain remains
    # hole-preserving, while adjacent active cells share seam vertices.
    for cell_x, cell_z, _page in zmap.used_cells():
        base_x = cell_x * PAGE_W
        base_z = cell_z * PAGE_H
        for lz in range(PAGE_H):
            sz = base_z + lz
            for lx in range(PAGE_W):
                sx = base_x + lx
                v0 = get_vertex(sx, sz)
                v1 = get_vertex(sx + 1, sz)
                v2 = get_vertex(sx + 1, sz + 1)
                v3 = get_vertex(sx, sz + 1)
                faces.append((v0, v1, v2, v3))

                word = runtime_lookup_word(pages, page_grid, sx, sz)
                surf = word >> 13
                surface_hist[surf] = surface_hist.get(surf, 0) + 1

    stats = {
        "mesh_mode": "dense-welded-runtime-lookup",
        "bounds_zmap_cells": [min_cx, min_cz, max_cx, max_cz],
        "bounds_sample_coords": [min_sx, min_sz, max_sx, max_sz],
        "vertices": len(vertices),
        "faces": len(faces),
        "expected_faces_for_active_pages": len(zmap.used_cells()) * PAGE_W * PAGE_H,
        "surface_histogram_by_quad_origin": {str(k): v for k, v in sorted(surface_hist.items())},
        "origin_world_offset": [offset_x, offset_z],
        "boundary_sampling": boundary_sampling,
    }
    return vertices, faces, stats


def compute_vertex_normals(vertices: List[Tuple[float, float, float]], faces: List[Tuple[int, int, int, int]]) -> List[Tuple[float, float, float]]:
    acc = [[0.0, 0.0, 0.0] for _ in vertices]
    for face in faces:
        p0 = vertices[face[0] - 1]
        p1 = vertices[face[1] - 1]
        p2 = vertices[face[2] - 1]
        p3 = vertices[face[3] - 1]
        n1 = cross(vsub(p1, p0), vsub(p2, p0))
        n2 = cross(vsub(p2, p0), vsub(p3, p0))
        n = (n1[0] + n2[0], n1[1] + n2[1], n1[2] + n2[2])
        for vi in face:
            acc[vi - 1][0] += n[0]
            acc[vi - 1][1] += n[1]
            acc[vi - 1][2] += n[2]
    return [normalize((x, y, z)) for x, y, z in acc]


def write_obj(
    obj_path: Path,
    vertices: List[Tuple[float, float, float]],
    faces: List[Tuple[int, int, int, int]],
    obj_coordinates: str,
    write_normals: bool,
    header: Iterable[str],
) -> None:
    obj_path.parent.mkdir(parents=True, exist_ok=True)
    normals = compute_vertex_normals(vertices, faces) if write_normals else []
    with obj_path.open("w", encoding="utf-8") as f:
        for line in header:
            f.write(f"# {line}\n")
        f.write("o terrain\n")
        f.write("g terrain\n")
        for wx, wz, h in vertices:
            vx, vy, vz = convert_vertex(wx, wz, h, obj_coordinates)
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")
        if write_normals:
            for nx, nz, nh in normals:
                vx, vy, vz = convert_normal(nx, nz, nh, obj_coordinates)
                f.write(f"vn {vx:.8f} {vy:.8f} {vz:.8f}\n")
            for a, b, c, d in faces:
                f.write(f"f {a}//{a} {b}//{b} {c}//{c} {d}//{d}\n")
        else:
            for a, b, c, d in faces:
                f.write(f"f {a} {b} {c} {d}\n")


def write_debug(debug_dir: Path, mission_stem: str, chunks: List[Chunk], zmap: ZMap, page_grid: List[int], manifest_entry: dict) -> None:
    mdir = debug_dir / mission_stem.lower()
    mdir.mkdir(parents=True, exist_ok=True)
    (mdir / f"{mission_stem.lower()}.chunks.json").write_text(json.dumps([
        dataclasses.asdict(c) | {"end": c.end, "offset_hex": f"0x{c.offset:08x}"}
        for c in chunks
    ], indent=2), encoding="utf-8")
    (mdir / f"{mission_stem.lower()}.zmap.json").write_text(json.dumps(zmap.summary(), indent=2), encoding="utf-8")
    (mdir / f"{mission_stem.lower()}.page_grid.json").write_text(json.dumps(page_grid_summary(page_grid, zmap), indent=2), encoding="utf-8")
    (mdir / f"{mission_stem.lower()}.mesh_stats.json").write_text(json.dumps(manifest_entry.get("mesh_stats", {}), indent=2), encoding="utf-8")


def make_tar_archive(out_dir: Path) -> Optional[str]:
    tar_path = out_dir.with_suffix(".tar")
    if tar_path.exists():
        tar_path.unlink()
    # Use system tar when available because that matches the project convention.
    system_tar = shutil.which("tar")
    if system_tar:
        subprocess.run([system_tar, "-cf", str(tar_path), "-C", str(out_dir.parent), out_dir.name], check=True)
    else:
        with tarfile.open(tar_path, "w") as tf:
            tf.add(out_dir, arcname=out_dir.name)
    return str(tar_path)


def choose_out_dir(base: Optional[Path], explicit: Optional[Path]) -> Path:
    if explicit is not None:
        return explicit
    root = base if base is not None else DEFAULT_ROOT
    stamp = time.strftime("i76_runtime_dense_terrain_v5_%Y%m%d_%H%M%S")
    return root / stamp


def export(args: argparse.Namespace) -> dict:
    input_path: Path = args.input
    out_dir = choose_out_dir(args.default_root, args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    files = find_files(input_path)
    by_name = {p.name.lower(): p for p in files}
    missions = [p for p in files if p.suffix.lower() in {".msn", ".lvl", ".spc"}]
    if args.mission_filter:
        filt = args.mission_filter.lower()
        missions = [p for p in missions if filt in p.stem.lower() or filt in p.name.lower()]

    manifest = {
        "format": "i76_runtime_dense_terrain_export_manifest",
        "version": 5,
        "source": str(input_path),
        "out_dir": str(out_dir),
        "runtime_confirmed": [
            "BWD2 nested chunk scan",
            "TDEF/ZMAP/ZONE extraction",
            "TER page size 0x8000, 128x128 uint16 little-endian",
            "128x128 runtime page pointer grid with ZMAP +24/+24 offset",
            "height lookup through biased page grid using +0xc00 and 0x7f masks",
            "surface class word >> 13",
        ],
        "intentionally_not_modeled": [
            "adaptive runtime tessellation / LOD predicate from 00490a00 and 004911e0",
            "terrain primitive node and edge-record emission",
            "hardware/software polygon work-record contents",
        ],
        "options": {
            "mission_filter": args.mission_filter,
            "origin": args.origin,
            "obj_coordinates": args.obj_coordinates,
            "vertical_scale": args.vertical_scale,
            "boundary_sampling": args.boundary_sampling,
            "write_normals": args.write_normals,
            "write_debug": args.write_debug,
            "make_tar": args.make_tar,
        },
        "missions_seen": len(missions),
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
                manifest["warnings"].append(f"{msn}: no .TER sidecar found for {sidecar_name!r}")
                continue

            pages = load_ter_pages(ter, zmap.active_count)
            page_grid = build_runtime_page_grid(zmap, default_page=0)
            vertices, faces, mesh_stats = build_dense_welded_mesh(
                pages,
                zmap,
                page_grid,
                args.origin,
                args.boundary_sampling,
                args.vertical_scale,
            )

            obj_path = out_dir / "terrain_obj" / f"{msn.stem.lower()}.runtime_dense_v5.obj"
            write_obj(
                obj_path,
                vertices,
                faces,
                args.obj_coordinates,
                args.write_normals,
                [
                    "Interstate '76 runtime dense welded terrain OBJ v5",
                    f"mission={msn}",
                    f"sidecar={ter}",
                    "dense mesh baseline; adaptive LOD intentionally not modeled",
                    f"boundary_sampling={args.boundary_sampling}",
                ],
            )

            entry = {
                "mission": str(msn),
                "sidecar": str(ter),
                "zone_sidecar_name": sidecar_name,
                "obj_path": str(obj_path),
                "zmap_summary": zmap.summary(),
                "page_grid_summary": page_grid_summary(page_grid, zmap),
                "mesh_stats": mesh_stats,
            }
            manifest["terrain"].append(entry)

            if args.write_debug:
                write_debug(out_dir / "debug", msn.stem, chunks, zmap, page_grid, entry)

        except Exception as e:
            manifest["warnings"].append(f"{msn}: {type(e).__name__}: {e}")

    manifest_path = out_dir / "i76_runtime_dense_terrain_export_manifest_v5.json"
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    if args.make_tar:
        try:
            manifest["tar_path"] = make_tar_archive(out_dir)
            manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")
        except Exception as e:
            manifest["warnings"].append(f"tar creation failed: {type(e).__name__}: {e}")
            manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    print(json.dumps({
        "manifest": str(manifest_path),
        "out_dir": str(out_dir),
        "terrain_objs": len(manifest["terrain"]),
        "warnings": len(manifest["warnings"]),
        "tar_path": manifest.get("tar_path"),
    }, indent=2))

    if args.fail_empty and not manifest["terrain"]:
        raise SystemExit("no terrain OBJs generated")

    return manifest


def main() -> int:
    ap = argparse.ArgumentParser(description="Export I76 runtime-aligned dense welded terrain OBJ.")
    ap.add_argument("input", type=Path, help="Directory/file containing .MSN/.LVL/.SPC and .TER sidecars")
    ap.add_argument("--out-dir", type=Path, default=None)
    ap.add_argument("--default-root", type=Path, default=DEFAULT_ROOT)
    ap.add_argument("--mission-filter", default="", help="Substring filter, e.g. m06, s05, t05")
    ap.add_argument("--origin", choices=["open76-centered", "min-corner", "absolute"], default="open76-centered")
    ap.add_argument("--obj-coordinates", choices=["blender", "y-up"], default="blender")
    ap.add_argument("--vertical-scale", type=float, default=DEFAULT_VERTICAL_SCALE)
    ap.add_argument(
        "--boundary-sampling",
        choices=["clamp-outer-active-edge", "average-outer-active-edge", "runtime-strict"],
        default="clamp-outer-active-edge",
        help="How to close the outer dense mesh border. runtime-strict is diagnostic and may sample the default page at the edge.",
    )
    ap.add_argument("--write-normals", action="store_true")
    ap.add_argument("--write-debug", action="store_true")
    ap.add_argument("--make-tar", action="store_true")
    ap.add_argument("--fail-empty", action="store_true")
    args = ap.parse_args()
    export(args)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
