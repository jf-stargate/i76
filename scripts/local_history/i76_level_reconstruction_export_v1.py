#!/usr/bin/env python3
"""
Interstate '76 level reconstruction exporter, v1.

Purpose:
  Practical Blender/OBJ reconstruction baseline using the geometry findings from the
  runtime mission/terrain traces.

This is intentionally not a final game-renderer clone. It emits:
  - Dense welded terrain mesh, one quad per terrain sample interval.
  - Optional corrected adaptive terrain overlay, using the confirmed hard split floor
    and special-surface forced-split scan, but still approximate for projection/error.
  - ODEF/OBJ placement axes from the confirmed 3x3 basis + position record.
  - RDEF/RSEG road/corridor probes: centerline, left edge, right edge, crossbars.

Confirmed runtime-aligned pieces:
  - BWD2/TDEF/ZMAP/ZONE parsing.
  - .TER pages are 0x8000 bytes, 128x128 little-endian uint16 samples.
  - Runtime page grid is 128x128 with ZMAP copied at +24/+24.
  - Height lookup uses +0xc00 bias and page-grid indirection.
  - Height = sample_word & 0x0fff.
  - Surface class = sample_word >> 13.
  - Special-surface split condition:
        word >= 0x4000 && (word & 0xe000) != 0xa000
  - ODEF/OBJ basis is payload +0x08..+0x28 and position is +0x2c/+0x30/+0x34.
  - ODEF class discriminator is payload +0x5c, valid runtime dispatch range 1..0x53.
  - RSEG serialized layout is u32 kind, u32 count, count * 0x18 byte records.

Approximate/debug pieces:
  - Adaptive overlay uses the confirmed hard split floor, center/quarter height error,
    and special-surface scan, but not the exact screen/projection predicate yet.
  - RSEG field names are still probes; the six floats are exported as paired edges.

Example:
  python3 i76_level_reconstruction_export_v1.py \
    "/media/neon-remote/prj/i76/game/interstate 76/miss16" \
    --mission-filter m06 \
    --out-dir /media/neon-remote/prj/i76/scratch_data/i76_level_reconstruct_v1_m06 \
    --write-terrain --write-odef-axes --write-rseg --write-adaptive-overlay \
    --make-tar --fail-empty
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import math
import os
import struct
import subprocess
import sys
import time
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple


PAGE_W = 128
PAGE_H = 128
PAGE_SIZE_BYTES = PAGE_W * PAGE_H * 2
ZMAP_W = 80
ZMAP_H = 80
RUNTIME_GRID_W = 128
RUNTIME_GRID_H = 128
ZMAP_RUNTIME_OFFSET = 24
LOOKUP_BIAS_SAMPLES = 0x0C00
PATCH_WORLD_SIZE = 640.0
SAMPLE_WORLD_SCALE = PATCH_WORLD_SIZE / PAGE_W
DEFAULT_VERTICAL_SCALE = 409.5 / 4096.0
DEFAULT_ROOT = Path("/media/neon-remote/prj/i76/scratch_data")


CONTAINER_TAGS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
MISSION_EXTS = {".msn", ".spc", ".lvl"}


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
            row = z * ZMAP_W
            for x in range(ZMAP_W):
                v = self.cells[row + x]
                if v != 0xFF:
                    out.append((x, z, v))
        return out

    def bounds(self) -> Optional[Tuple[int, int, int, int]]:
        used = self.used_cells()
        if not used:
            return None
        xs = [u[0] for u in used]
        zs = [u[1] for u in used]
        return min(xs), min(zs), max(xs), max(zs)

    def center_cell(self) -> Tuple[float, float]:
        b = self.bounds()
        if b is None:
            return 0.0, 0.0
        min_x, min_z, max_x, max_z = b
        return (min_x + max_x + 1) * 0.5, (min_z + max_z + 1) * 0.5

    def to_dict(self) -> dict:
        used = self.used_cells()
        hist: Dict[int, int] = {}
        for _, _, p in used:
            hist[p] = hist.get(p, 0) + 1
        return {
            "active_count": self.active_count,
            "used_cell_count": len(used),
            "bounds": list(self.bounds()) if self.bounds() else None,
            "center_cell": list(self.center_cell()),
            "page_histogram": {str(k): v for k, v in sorted(hist.items())},
        }


@dataclasses.dataclass
class MissionData:
    path: Path
    data: bytes
    chunks: List[Chunk]
    zmap: Optional[ZMap]
    zone_sidecar_name: str


@dataclasses.dataclass
class RuntimeTerrain:
    zmap: ZMap
    pages: List[Tuple[int, ...]]
    page_grid: List[int]
    origin_sample_x: float
    origin_sample_z: float
    vertical_scale: float

    def sample_word_runtime(self, sample_x: int, sample_z: int) -> int:
        gx = (sample_x + LOOKUP_BIAS_SAMPLES) >> 7
        gz = (sample_z + LOOKUP_BIAS_SAMPLES) >> 7
        lx = (sample_x + LOOKUP_BIAS_SAMPLES) & 0x7F
        lz = (sample_z + LOOKUP_BIAS_SAMPLES) & 0x7F
        if gx < 0 or gz < 0 or gx >= RUNTIME_GRID_W or gz >= RUNTIME_GRID_H:
            page = 0
        else:
            page = self.page_grid[gz * RUNTIME_GRID_W + gx]
        if page < 0 or page >= len(self.pages):
            return 0
        return self.pages[page][lz * PAGE_W + lx]

    def height_low12(self, sample_x: int, sample_z: int) -> int:
        return self.sample_word_runtime(sample_x, sample_z) & 0x0FFF

    def height_world(self, sample_x: int, sample_z: int) -> float:
        return self.height_low12(sample_x, sample_z) * self.vertical_scale

    def surface_class(self, sample_x: int, sample_z: int) -> int:
        return self.sample_word_runtime(sample_x, sample_z) >> 13

    def world_xz(self, sample_x: int, sample_z: int) -> Tuple[float, float]:
        return (
            (sample_x - self.origin_sample_x) * SAMPLE_WORLD_SCALE,
            (sample_z - self.origin_sample_z) * SAMPLE_WORLD_SCALE,
        )

    def special_surface_inclusive_scan(self, x0: int, z0: int, x1: int, z1: int, step: int = 1) -> bool:
        if x1 < x0:
            x0, x1 = x1, x0
        if z1 < z0:
            z0, z1 = z1, z0
        # Exact binary step remains to be transcribed. Use sparse scan for large quads
        # to keep debug overlay practical while preserving the confirmed predicate.
        step = max(1, step)
        for z in range(z0, z1 + 1, step):
            for x in range(x0, x1 + 1, step):
                w = self.sample_word_runtime(x, z)
                if w >= 0x4000 and (w & 0xE000) != 0xA000:
                    return True
        return False


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def f32(data: bytes, off: int) -> float:
    return struct.unpack_from("<f", data, off)[0]


def fourcc(data: bytes, off: int) -> str:
    return data[off:off + 4].decode("ascii", errors="replace")


def clean_tag(tag: str) -> str:
    return tag.replace("\x00", "\\0")


def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    chunks: List[Chunk] = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        size = u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        c = Chunk(tag, off, size, off + 8, size - 8, parent)
        chunks.append(c)
        off += size
        # Do not break on EXIT here; some parent payloads in the corpus include
        # consecutive EXIT chunks and top-level parsing is descriptor-driven.
    return chunks


def parse_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat(data, 0, len(data), "")

    def rec(items: List[Chunk]) -> List[Chunk]:
        out: List[Chunk] = []
        for c in items:
            out.append(c)
            if c.tag in CONTAINER_TAGS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    out.extend(rec(kids))
        return out

    return rec(roots)


def first_chunk(chunks: Sequence[Chunk], tag: str, parent: Optional[str] = None) -> Optional[Chunk]:
    for c in chunks:
        if c.tag == tag and (parent is None or c.parent == parent):
            return c
    return None


def chunks_by_tag(chunks: Sequence[Chunk], tag: str, parent: Optional[str] = None) -> List[Chunk]:
    return [c for c in chunks if c.tag == tag and (parent is None or c.parent == parent)]


def decode_zmap(data: bytes, chunks: Sequence[Chunk]) -> Optional[ZMap]:
    c = first_chunk(chunks, "ZMAP", "TDEF") or first_chunk(chunks, "ZMAP")
    if c is None:
        return None
    if c.payload_size < 1 + ZMAP_W * ZMAP_H:
        raise ValueError(f"ZMAP too small at 0x{c.offset:x}")
    return ZMap(data[c.payload_offset], list(data[c.payload_offset + 1:c.payload_offset + 1 + ZMAP_W * ZMAP_H]))


def decode_zone_sidecar_name(data: bytes, chunks: Sequence[Chunk]) -> str:
    c = first_chunk(chunks, "ZONE", "TDEF") or first_chunk(chunks, "ZONE")
    if c is None:
        return ""
    payload = data[c.payload_offset:c.end]
    candidates: List[str] = []
    for start in (0, 1, 4, 8, 9):
        if start < len(payload):
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
        msn.with_suffix(".TER"),
        msn.with_suffix(".ter"),
        by_name.get(msn.stem.lower() + ".ter"),
    ])
    for p in candidates:
        if p is not None and Path(p).exists():
            return Path(p)
    return None


def load_ter_pages(path: Path, expected_count: int) -> List[Tuple[int, ...]]:
    data = path.read_bytes()
    if len(data) % PAGE_SIZE_BYTES != 0:
        raise ValueError(f"{path}: size 0x{len(data):x} is not a multiple of 0x{PAGE_SIZE_BYTES:x}")
    count = len(data) // PAGE_SIZE_BYTES
    if expected_count and count < expected_count:
        raise ValueError(f"{path}: has {count} pages but ZMAP active_count is {expected_count}")
    fmt = "<" + "H" * (PAGE_W * PAGE_H)
    return [struct.unpack_from(fmt, data, i * PAGE_SIZE_BYTES) for i in range(count)]


def build_page_grid(zmap: ZMap) -> List[int]:
    # Runtime initializes the page pointer grid to a default page and then copies
    # active ZMAP cells into grid[(z+24)*128 + (x+24)].
    grid = [0 for _ in range(RUNTIME_GRID_W * RUNTIME_GRID_H)]
    for x, z, page in zmap.used_cells():
        gx = x + ZMAP_RUNTIME_OFFSET
        gz = z + ZMAP_RUNTIME_OFFSET
        if 0 <= gx < RUNTIME_GRID_W and 0 <= gz < RUNTIME_GRID_H:
            grid[gz * RUNTIME_GRID_W + gx] = page
    return grid


def origin_samples_for_zmap(zmap: ZMap, origin_mode: str) -> Tuple[float, float]:
    if origin_mode == "absolute":
        return 0.0, 0.0
    b = zmap.bounds()
    if b is None:
        return 0.0, 0.0
    min_x, min_z, max_x, max_z = b
    if origin_mode == "min-corner":
        return min_x * PAGE_W, min_z * PAGE_H
    if origin_mode == "open76-centered":
        cx, cz = zmap.center_cell()
        return cx * PAGE_W, cz * PAGE_H
    raise ValueError(f"unknown origin mode: {origin_mode}")


def obj_vertex_coords(x: float, z: float, h: float, mode: str) -> Tuple[float, float, float]:
    if mode == "blender":
        return x, z, h
    if mode == "y-up":
        return x, h, z
    raise ValueError(mode)


def vec_sub(a, b):
    return (a[0] - b[0], a[1] - b[1], a[2] - b[2])


def vec_cross(a, b):
    return (
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    )


def vec_normalize(v):
    n = math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
    if n <= 1e-12:
        return (0.0, 0.0, 1.0)
    return (v[0] / n, v[1] / n, v[2] / n)


def compute_normals(vertices: List[Tuple[float, float, float]], faces: List[Tuple[int, ...]]) -> List[Tuple[float, float, float]]:
    acc = [[0.0, 0.0, 0.0] for _ in vertices]
    for face in faces:
        if len(face) < 3:
            continue
        p0 = vertices[face[0] - 1]
        for i in range(1, len(face) - 1):
            p1 = vertices[face[i] - 1]
            p2 = vertices[face[i + 1] - 1]
            n = vec_cross(vec_sub(p1, p0), vec_sub(p2, p0))
            for vi in (face[0], face[i], face[i + 1]):
                acc[vi - 1][0] += n[0]
                acc[vi - 1][1] += n[1]
                acc[vi - 1][2] += n[2]
    return [vec_normalize(tuple(v)) for v in acc]


def write_obj(path: Path, vertices: List[Tuple[float, float, float]], faces: List[Tuple[int, ...]],
              obj_coordinates: str, write_normals: bool, header: str = "") -> dict:
    path.parent.mkdir(parents=True, exist_ok=True)
    normals = compute_normals(vertices, faces) if write_normals and faces else []
    with path.open("w", encoding="utf-8") as f:
        f.write(header)
        for x, z, h in vertices:
            vx, vy, vz = obj_vertex_coords(x, z, h, obj_coordinates)
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")
        if normals:
            for nx, nz, nh in normals:
                vx, vy, vz = obj_vertex_coords(nx, nz, nh, obj_coordinates)
                f.write(f"vn {vx:.8f} {vy:.8f} {vz:.8f}\n")
        if normals:
            for face in faces:
                f.write("f " + " ".join(f"{i}//{i}" for i in face) + "\n")
        else:
            for face in faces:
                f.write("f " + " ".join(str(i) for i in face) + "\n")
    return {"path": str(path), "vertices": len(vertices), "faces": len(faces), "write_normals": bool(normals)}


def build_dense_terrain_mesh(rt: RuntimeTerrain, boundary_sampling: str) -> Tuple[List[Tuple[float, float, float]], List[Tuple[int, int, int, int]]]:
    vertices: List[Tuple[float, float, float]] = []
    faces: List[Tuple[int, int, int, int]] = []
    index_by_sample: Dict[Tuple[int, int], int] = {}

    used = set((x, z) for x, z, _ in rt.zmap.used_cells())

    def sample_for_vertex(cell_x: int, cell_z: int, local_x: int, local_z: int) -> Tuple[int, int]:
        sx = cell_x * PAGE_W + local_x
        sz = cell_z * PAGE_H + local_z
        if boundary_sampling == "runtime-strict":
            return sx, sz

        # For a visually useful dense mesh, clamp only outer active-page edges so
        # the mesh does not sample the runtime default page at the outside border.
        if boundary_sampling == "clamp-outer-active-edge":
            if local_x == PAGE_W and (cell_x + 1, cell_z) not in used:
                sx -= 1
            if local_z == PAGE_H and (cell_x, cell_z + 1) not in used:
                sz -= 1
            return sx, sz

        raise ValueError(f"unknown boundary sampling: {boundary_sampling}")

    def get_vertex(cell_x: int, cell_z: int, local_x: int, local_z: int) -> int:
        sx, sz = sample_for_vertex(cell_x, cell_z, local_x, local_z)
        # Weld by emitted/world coordinate sample key, not by active-cell ownership.
        key = (sx, sz)
        old = index_by_sample.get(key)
        if old is not None:
            return old
        wx, wz = rt.world_xz(sx, sz)
        h = rt.height_world(sx, sz)
        vertices.append((wx, wz, h))
        idx = len(vertices)
        index_by_sample[key] = idx
        return idx

    for cell_x, cell_z, page in rt.zmap.used_cells():
        for lz in range(PAGE_H):
            for lx in range(PAGE_W):
                v0 = get_vertex(cell_x, cell_z, lx, lz)
                v1 = get_vertex(cell_x, cell_z, lx + 1, lz)
                v2 = get_vertex(cell_x, cell_z, lx + 1, lz + 1)
                v3 = get_vertex(cell_x, cell_z, lx, lz + 1)
                faces.append((v0, v1, v2, v3))
    return vertices, faces


def should_split_adaptive(rt: RuntimeTerrain, x0: int, z0: int, size: int,
                          max_depth: int, depth: int, split_error: float,
                          force_surface_splits: bool) -> Tuple[bool, str]:
    half = size >> 1
    if depth >= max_depth or half <= 0:
        return False, "max_depth_or_zero_half"

    # Confirmed hard split floor from 004911e0: if half_scale >= 0x20,
    # it goes directly to the split path.
    if half >= 0x20:
        return True, "hard_half_scale_ge_0x20"

    x1 = x0 + size
    z1 = z0 + size
    cx = x0 + half
    cz = z0 + half

    h00 = rt.height_low12(x0, z0)
    h10 = rt.height_low12(x1, z0)
    h11 = rt.height_low12(x1, z1)
    h01 = rt.height_low12(x0, z1)
    hc = rt.height_low12(cx, cz)
    interp_center = (h00 + h10 + h11 + h01) * 0.25
    center_err = abs(hc - interp_center)

    quarter_err = 0.0
    for qx, qz, a, b in [
        (x0 + half // 2, z0 + half // 2, h00, hc),
        (x0 + half + half // 2, z0 + half // 2, h10, hc),
        (x0 + half + half // 2, z0 + half + half // 2, h11, hc),
        (x0 + half // 2, z0 + half + half // 2, h01, hc),
    ]:
        if half >= 2:
            hq = rt.height_low12(qx, qz)
            quarter_err = max(quarter_err, abs(hq - ((a + b) * 0.5)))

    if center_err > split_error:
        return True, f"center_error_{center_err:.3f}"
    if quarter_err > split_error:
        return True, f"quarter_error_{quarter_err:.3f}"

    if force_surface_splits:
        step = max(1, size // 16)
        if rt.special_surface_inclusive_scan(x0, z0, x1, z1, step=step):
            return True, "special_surface_scan"

    return False, "leaf"


def build_adaptive_overlay_mesh(rt: RuntimeTerrain, max_depth: int, split_error: float,
                                force_surface_splits: bool) -> Tuple[List[Tuple[float, float, float]], List[Tuple[int, int, int, int]], dict]:
    vertices: List[Tuple[float, float, float]] = []
    faces: List[Tuple[int, int, int, int]] = []
    index_by_sample: Dict[Tuple[int, int], int] = {}
    stats = {
        "quad_tests": 0,
        "quad_splits": 0,
        "leaf_count": 0,
        "split_reasons": {},
        "leaf_depth_histogram": {},
    }

    def add_reason(reason: str) -> None:
        stats["split_reasons"][reason] = stats["split_reasons"].get(reason, 0) + 1

    def get_vertex(sx: int, sz: int) -> int:
        key = (sx, sz)
        old = index_by_sample.get(key)
        if old is not None:
            return old
        wx, wz = rt.world_xz(sx, sz)
        h = rt.height_world(sx, sz)
        vertices.append((wx, wz, h))
        idx = len(vertices)
        index_by_sample[key] = idx
        return idx

    def rec(x0: int, z0: int, size: int, depth: int) -> None:
        stats["quad_tests"] += 1
        do_split, reason = should_split_adaptive(rt, x0, z0, size, max_depth, depth, split_error, force_surface_splits)
        if do_split:
            stats["quad_splits"] += 1
            add_reason(reason)
            h = size >> 1
            rec(x0, z0, h, depth + 1)
            rec(x0 + h, z0, h, depth + 1)
            rec(x0 + h, z0 + h, h, depth + 1)
            rec(x0, z0 + h, h, depth + 1)
        else:
            v0 = get_vertex(x0, z0)
            v1 = get_vertex(x0 + size, z0)
            v2 = get_vertex(x0 + size, z0 + size)
            v3 = get_vertex(x0, z0 + size)
            faces.append((v0, v1, v2, v3))
            stats["leaf_count"] += 1
            key = str(depth)
            stats["leaf_depth_histogram"][key] = stats["leaf_depth_histogram"].get(key, 0) + 1

    for cell_x, cell_z, _page in rt.zmap.used_cells():
        rec(cell_x * PAGE_W, cell_z * PAGE_H, PAGE_W, 0)

    return vertices, faces, stats


def read_c_string_from_payload(payload: bytes, max_len: int = 8) -> str:
    return payload[:max_len].split(b"\0", 1)[0].decode("ascii", errors="ignore").strip()


def parse_odef_obj_records(mission: MissionData) -> List[dict]:
    out: List[dict] = []
    for index, c in enumerate(chunks_by_tag(mission.chunks, "OBJ\x00", "ODEF")):
        payload = mission.data[c.payload_offset:c.end]
        if len(payload) < 0x64:
            continue
        basis = [f32(payload, 0x08 + i * 4) for i in range(9)]
        pos = [f32(payload, 0x2C), f32(payload, 0x30), f32(payload, 0x34)]
        tail = [u32(payload, 0x38 + i * 4) for i in range((0x64 - 0x38) // 4)]
        class_raw = u32(payload, 0x5C)
        name = read_c_string_from_payload(payload, 8)
        valid = 1 <= class_raw <= 0x53
        out.append({
            "index": index,
            "chunk_offset": c.offset,
            "name": name,
            "basis": basis,
            "pos": pos,
            "tail_dwords": tail,
            "class_raw": class_raw,
            "class_hex": f"0x{class_raw:08x}",
            "dispatch_valid": valid,
            "raw_hex": payload[:0x64].hex(),
        })
    return out


def write_odef_axes_obj(path: Path, records: List[dict], obj_coordinates: str,
                        include_invalid: bool, axis_len: float = 25.0) -> dict:
    path.parent.mkdir(parents=True, exist_ok=True)
    vertices: List[Tuple[float, float, float]] = []
    lines: List[Tuple[int, int]] = []

    def add_line(a, b):
        vertices.append(a)
        ia = len(vertices)
        vertices.append(b)
        ib = len(vertices)
        lines.append((ia, ib))

    for rec in records:
        if not include_invalid and not rec["dispatch_valid"]:
            continue
        px, py, pz = rec["pos"]
        b = rec["basis"]
        origin = (px, pz, py)
        xaxis = (px + b[0] * axis_len, pz + b[1] * axis_len, py + b[2] * axis_len)
        yaxis = (px + b[3] * axis_len, pz + b[4] * axis_len, py + b[5] * axis_len)
        zaxis = (px + b[6] * axis_len, pz + b[7] * axis_len, py + b[8] * axis_len)
        add_line(origin, xaxis)
        add_line(origin, yaxis)
        add_line(origin, zaxis)

    with path.open("w", encoding="utf-8") as f:
        f.write("# ODEF OBJ basis/position axes probe\n")
        f.write("# For Blender Z-up: OBJ v = x z y\n")
        for x, z, h in vertices:
            vx, vy, vz = obj_vertex_coords(x, z, h, obj_coordinates)
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")
        for a, b in lines:
            f.write(f"l {a} {b}\n")
    return {"path": str(path), "records_total": len(records), "lines": len(lines), "include_invalid": include_invalid}


def parse_rseg_records(mission: MissionData) -> Tuple[List[dict], List[dict]]:
    records: List[dict] = []
    points: List[dict] = []
    for rseg_index, c in enumerate(chunks_by_tag(mission.chunks, "RSEG", "RDEF")):
        payload = mission.data[c.payload_offset:c.end]
        if len(payload) < 8:
            continue
        kind = u32(payload, 0)
        count = u32(payload, 4)
        expected = 8 + count * 0x18
        records.append({
            "rseg_index": rseg_index,
            "chunk_offset": c.offset,
            "kind": kind,
            "count": count,
            "payload_size": len(payload),
            "expected_payload_size": expected,
            "size_matches": len(payload) == expected,
        })
        max_count = min(count, max(0, (len(payload) - 8) // 0x18))
        for i in range(max_count):
            off = 8 + i * 0x18
            vals = [f32(payload, off + j * 4) for j in range(6)]
            lx, lz, auxz, rx, hy, rz = vals
            cx = (lx + rx) * 0.5
            cz = (lz + rz) * 0.5
            width = math.hypot(rx - lx, rz - lz)
            points.append({
                "rseg_index": rseg_index,
                "point_index": i,
                "kind": kind,
                "left_x": lx,
                "left_z": lz,
                "aux_z_or_mid": auxz,
                "right_x": rx,
                "height_or_y": hy,
                "right_z": rz,
                "center_x": cx,
                "center_z": cz,
                "width": width,
            })
    return records, points


def write_rseg_obj(path: Path, points: List[dict], mode: str, obj_coordinates: str) -> dict:
    path.parent.mkdir(parents=True, exist_ok=True)
    vertices: List[Tuple[float, float, float]] = []
    lines: List[Tuple[int, int]] = []

    by_seg: Dict[int, List[dict]] = {}
    for p in points:
        by_seg.setdefault(p["rseg_index"], []).append(p)

    def add_vertex(x, z, h=0.0) -> int:
        vertices.append((x, z, h))
        return len(vertices)

    if mode in {"centerline", "left_edge", "right_edge"}:
        for seg, rows in sorted(by_seg.items()):
            rows = sorted(rows, key=lambda r: r["point_index"])
            prev = None
            for r in rows:
                if mode == "centerline":
                    idx = add_vertex(r["center_x"], r["center_z"], r["height_or_y"])
                elif mode == "left_edge":
                    idx = add_vertex(r["left_x"], r["left_z"], r["height_or_y"])
                else:
                    idx = add_vertex(r["right_x"], r["right_z"], r["height_or_y"])
                if prev is not None:
                    lines.append((prev, idx))
                prev = idx
    elif mode == "crossbars":
        for r in points:
            a = add_vertex(r["left_x"], r["left_z"], r["height_or_y"])
            b = add_vertex(r["right_x"], r["right_z"], r["height_or_y"])
            lines.append((a, b))
    else:
        raise ValueError(mode)

    with path.open("w", encoding="utf-8") as f:
        f.write(f"# RSEG {mode} probe\n")
        for x, z, h in vertices:
            vx, vy, vz = obj_vertex_coords(x, z, h, obj_coordinates)
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")
        for a, b in lines:
            f.write(f"l {a} {b}\n")
    return {"path": str(path), "mode": mode, "vertices": len(vertices), "lines": len(lines)}


def write_tsv(path: Path, rows: List[dict], columns: Sequence[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(columns) + "\n")
        for r in rows:
            f.write("\t".join(str(r.get(c, "")) for c in columns) + "\n")


def load_mission(path: Path) -> MissionData:
    data = path.read_bytes()
    chunks = parse_tree(data)
    zmap = decode_zmap(data, chunks)
    sidecar = decode_zone_sidecar_name(data, chunks)
    return MissionData(path, data, chunks, zmap, sidecar)


def timestamped_out_dir(base: Optional[Path], prefix: str) -> Path:
    if base is None:
        base = DEFAULT_ROOT
    ts = time.strftime("%Y%m%d_%H%M%S")
    if base.name.startswith(prefix):
        return base
    return base / f"{prefix}_{ts}"


def make_tar(out_dir: Path) -> Optional[Path]:
    tar_path = out_dir.with_suffix(".tar")
    try:
        subprocess.run(["tar", "-cf", str(tar_path), "-C", str(out_dir.parent), out_dir.name], check=True)
        return tar_path
    except Exception:
        return None


def export(args: argparse.Namespace) -> dict:
    input_path = Path(args.input)
    out_dir = timestamped_out_dir(args.out_dir, "i76_level_reconstruction_export_v1")
    out_dir.mkdir(parents=True, exist_ok=True)

    files = find_files(input_path)
    by_name = {p.name.lower(): p for p in files}
    missions = [p for p in files if p.suffix.lower() in MISSION_EXTS]
    if input_path.is_file() and input_path.suffix.lower() in MISSION_EXTS:
        missions = [input_path]
    if args.mission_filter:
        filt = args.mission_filter.lower()
        missions = [p for p in missions if filt in p.stem.lower() or filt in p.name.lower()]

    manifest = {
        "format": "i76_level_reconstruction_export",
        "version": 1,
        "source": str(input_path),
        "out_dir": str(out_dir),
        "options": vars(args) | {"out_dir": str(out_dir)},
        "runtime_confirmed": [
            "BWD2/TDEF/ZMAP/ZONE parsing",
            "TER 128x128 uint16 pages",
            "128x128 runtime page grid with ZMAP +24/+24",
            "height lookup through +0xc00-biased runtime page grid",
            "height low12 and surface class word>>13",
            "ODEF basis +0x08..+0x28 and position +0x2c/+0x30/+0x34",
            "ODEF class discriminator at +0x5c",
            "RSEG u32 kind, u32 count, count*0x18 records",
            "terrain LOD hard split floor: half_scale >= 0x20",
            "terrain special-surface split predicate",
        ],
        "runtime_approximate": [
            "adaptive overlay projection/error predicate",
            "RSEG semantic field names",
            "ODEF class-0/invalid special record interpretation",
        ],
        "missions": [],
        "warnings": [],
    }

    all_odef_rows: List[dict] = []
    all_rseg_record_rows: List[dict] = []
    all_rseg_point_rows: List[dict] = []

    for msn in sorted(missions):
        try:
            mission = load_mission(msn)
            info = {
                "mission": str(msn),
                "stem": msn.stem.lower(),
                "chunk_count": len(mission.chunks),
                "zone_sidecar_name": mission.zone_sidecar_name,
            }

            if mission.zmap:
                info["zmap"] = mission.zmap.to_dict()
            else:
                info["zmap"] = None

            rt: Optional[RuntimeTerrain] = None
            if mission.zmap is not None:
                ter = find_sidecar(msn, mission.zone_sidecar_name, by_name)
                if ter is None:
                    manifest["warnings"].append(f"{msn}: no TER sidecar for {mission.zone_sidecar_name!r}")
                else:
                    pages = load_ter_pages(ter, mission.zmap.active_count)
                    ox, oz = origin_samples_for_zmap(mission.zmap, args.origin)
                    rt = RuntimeTerrain(
                        mission.zmap,
                        pages,
                        build_page_grid(mission.zmap),
                        ox,
                        oz,
                        args.vertical_scale,
                    )
                    info["ter_sidecar"] = str(ter)

                    if args.write_terrain:
                        verts, faces = build_dense_terrain_mesh(rt, args.boundary_sampling)
                        obj_info = write_obj(
                            out_dir / "terrain_obj" / f"{msn.stem.lower()}.terrain_dense.obj",
                            verts,
                            faces,
                            args.obj_coordinates,
                            args.write_normals,
                            header="# I76 dense welded runtime-page-grid terrain baseline\n",
                        )
                        info["dense_terrain_obj"] = obj_info

                    if args.write_adaptive_overlay:
                        verts, faces, astats = build_adaptive_overlay_mesh(
                            rt,
                            args.adaptive_max_depth,
                            args.adaptive_split_error,
                            args.adaptive_force_surface_splits,
                        )
                        obj_info = write_obj(
                            out_dir / "terrain_obj" / f"{msn.stem.lower()}.terrain_adaptive_overlay.obj",
                            verts,
                            faces,
                            args.obj_coordinates,
                            args.write_normals,
                            header="# I76 corrected adaptive terrain overlay; projection predicate still approximate\n",
                        )
                        obj_info["stats"] = astats
                        info["adaptive_overlay_obj"] = obj_info

            odef_records = parse_odef_obj_records(mission)
            info["odef_obj_count"] = len(odef_records)
            for r in odef_records:
                all_odef_rows.append({
                    "mission": msn.stem.lower(),
                    "path": str(msn),
                    "index": r["index"],
                    "chunk_offset_hex": f"0x{r['chunk_offset']:08x}",
                    "name": r["name"],
                    "class_raw": r["class_raw"],
                    "class_hex": r["class_hex"],
                    "dispatch_valid": r["dispatch_valid"],
                    "pos_x": r["pos"][0],
                    "pos_y": r["pos"][1],
                    "pos_z": r["pos"][2],
                    "basis": ",".join(f"{v:.9g}" for v in r["basis"]),
                    "tail_dwords_hex": ",".join(f"0x{v:08x}" for v in r["tail_dwords"]),
                })
            if args.write_odef_axes:
                axes_info = write_odef_axes_obj(
                    out_dir / "object_obj" / f"{msn.stem.lower()}.odef_axes.obj",
                    odef_records,
                    args.obj_coordinates,
                    args.include_invalid_odef,
                    args.odef_axis_length,
                )
                info["odef_axes_obj"] = axes_info

            rseg_records, rseg_points = parse_rseg_records(mission)
            info["rseg_count"] = len(rseg_records)
            info["rseg_point_count"] = len(rseg_points)
            for r in rseg_records:
                all_rseg_record_rows.append({"mission": msn.stem.lower(), "path": str(msn), **r})
            for p in rseg_points:
                all_rseg_point_rows.append({"mission": msn.stem.lower(), "path": str(msn), **p})

            if args.write_rseg and rseg_points:
                info["rseg_objs"] = []
                for mode in ("centerline", "left_edge", "right_edge", "crossbars"):
                    obj_info = write_rseg_obj(
                        out_dir / "rseg_obj" / f"{msn.stem.lower()}.rseg_{mode}.obj",
                        rseg_points,
                        mode,
                        args.obj_coordinates,
                    )
                    info["rseg_objs"].append(obj_info)

            manifest["missions"].append(info)
        except Exception as e:
            manifest["warnings"].append(f"{msn}: {type(e).__name__}: {e}")

    write_tsv(
        out_dir / "tables" / "odef_obj_records.tsv",
        all_odef_rows,
        ["mission", "path", "index", "chunk_offset_hex", "name", "class_raw", "class_hex",
         "dispatch_valid", "pos_x", "pos_y", "pos_z", "basis", "tail_dwords_hex"],
    )
    write_tsv(
        out_dir / "tables" / "rdef_rseg_records.tsv",
        all_rseg_record_rows,
        ["mission", "path", "rseg_index", "chunk_offset", "kind", "count",
         "payload_size", "expected_payload_size", "size_matches"],
    )
    write_tsv(
        out_dir / "tables" / "rdef_rseg_points.tsv",
        all_rseg_point_rows,
        ["mission", "path", "rseg_index", "point_index", "kind",
         "left_x", "left_z", "aux_z_or_mid", "right_x", "height_or_y", "right_z",
         "center_x", "center_z", "width"],
    )

    if args.make_tar:
        tar_path = make_tar(out_dir)
        manifest["tar_path"] = str(tar_path) if tar_path else None

    manifest_path = out_dir / "manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    print(json.dumps({
        "manifest": str(manifest_path),
        "tar_path": manifest.get("tar_path"),
        "missions_seen": len(missions),
        "missions_exported": len(manifest["missions"]),
        "warnings": len(manifest["warnings"]),
    }, indent=2))

    if args.fail_empty and not manifest["missions"]:
        raise SystemExit("no missions exported")
    return manifest


def main(argv: Optional[Sequence[str]] = None) -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("input", help="Directory containing .MSN/.SPC/.LVL and .TER sidecars, or a single mission file")
    ap.add_argument("--out-dir", type=Path, default=None, help=f"Output root or final output dir. Default: {DEFAULT_ROOT}")
    ap.add_argument("--mission-filter", default="", help="Substring filter, e.g. m06, s01, t03")
    ap.add_argument("--origin", choices=["open76-centered", "min-corner", "absolute"], default="open76-centered")
    ap.add_argument("--obj-coordinates", choices=["blender", "y-up"], default="blender")
    ap.add_argument("--vertical-scale", type=float, default=DEFAULT_VERTICAL_SCALE)
    ap.add_argument("--boundary-sampling", choices=["clamp-outer-active-edge", "runtime-strict"], default="clamp-outer-active-edge")

    ap.add_argument("--write-terrain", action="store_true", help="Write dense welded terrain OBJ")
    ap.add_argument("--write-normals", action="store_true", help="Write OBJ vertex normals for terrain")
    ap.add_argument("--write-adaptive-overlay", action="store_true", help="Write corrected but still approximate adaptive overlay OBJ")
    ap.add_argument("--adaptive-max-depth", type=int, default=8)
    ap.add_argument("--adaptive-split-error", type=float, default=8.0)
    ap.add_argument("--adaptive-force-surface-splits", action="store_true")

    ap.add_argument("--write-odef-axes", action="store_true", help="Write ODEF object basis/position axes OBJ")
    ap.add_argument("--include-invalid-odef", action="store_true", help="Include dispatch-invalid ODEF rows in axes OBJ")
    ap.add_argument("--odef-axis-length", type=float, default=25.0)

    ap.add_argument("--write-rseg", action="store_true", help="Write RSEG centerline/edge/crossbar OBJ probes")
    ap.add_argument("--make-tar", action="store_true")
    ap.add_argument("--fail-empty", action="store_true")
    args = ap.parse_args(argv)

    # If no geometry class was requested, produce the practical baseline outputs.
    if not (args.write_terrain or args.write_adaptive_overlay or args.write_odef_axes or args.write_rseg):
        args.write_terrain = True
        args.write_odef_axes = True
        args.write_rseg = True

    export(args)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
