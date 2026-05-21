#!/usr/bin/env python3
"""
Interstate '76 runtime-shaped adaptive terrain OBJ exporter, v1.

This first runtime-line exporter implements the confirmed BWD2/TDEF/ZMAP/ZONE
and .TER page-grid lookup behavior, then emits an instrumented adaptive mesh.
The adaptive split predicate is intentionally marked approximate until the exact
00490a00/004911e0 camera/projection tests are fully reproduced.
"""
from __future__ import annotations

import argparse, dataclasses, json, math, struct, tarfile, time
from collections import Counter
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

PAGE_W = 128
PAGE_H = 128
PAGE_SAMPLES = PAGE_W * PAGE_H
PAGE_SIZE_BYTES = PAGE_SAMPLES * 2
ZMAP_W = 80
ZMAP_H = 80
RUNTIME_GRID_W = 128
RUNTIME_GRID_H = 128
RUNTIME_ZMAP_OFFSET = 24
RUNTIME_LOOKUP_BIAS = RUNTIME_ZMAP_OFFSET * PAGE_W  # 0x0c00
PATCH_SIZE_WORLD = 640.0
SAMPLE_SIZE_WORLD = PATCH_SIZE_WORLD / PAGE_W
DEFAULT_VERTICAL_SCALE = 409.5 / 4096.0
DEFAULT_ROOT = Path('/media/neon-remote/prj/i76/scratch_data')
CONTAINER_TAGS = {'BWD2', 'WDEF', 'TDEF', 'RDEF', 'ODEF', 'LDEF', 'ADEF'}
MISSION_SUFFIXES = {'.msn', '.spc', '.lvl'}


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from('<I', data, off)[0]


def fourcc(data: bytes, off: int) -> str:
    return data[off:off + 4].decode('ascii', errors='replace')


@dataclasses.dataclass(frozen=True)
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ''

    @property
    def end(self) -> int:
        return self.offset + self.size

    def to_dict(self) -> dict:
        return {
            'tag': self.tag, 'parent': self.parent,
            'offset': self.offset, 'offset_hex': f'0x{self.offset:08x}',
            'size': self.size, 'payload_offset': self.payload_offset,
            'payload_size': self.payload_size,
        }


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
    all_chunks: List[Chunk] = []
    def walk(items: Sequence[Chunk]) -> None:
        for c in items:
            all_chunks.append(c)
            if c.tag in CONTAINER_TAGS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    walk(kids)
    walk(parse_flat(data, 0, len(data), ''))
    return all_chunks


def first_chunk(chunks: Sequence[Chunk], tag: str, parent: Optional[str] = None) -> Optional[Chunk]:
    for c in chunks:
        if c.tag == tag and (parent is None or c.parent == parent):
            return c
    return None


@dataclasses.dataclass
class ZMap:
    active_count: int
    cells: List[int]

    def get_cell(self, x: int, z: int) -> int:
        if x < 0 or z < 0 or x >= ZMAP_W or z >= ZMAP_H:
            return 0xff
        return self.cells[z * ZMAP_W + x]

    def used_cells(self) -> List[Tuple[int, int, int]]:
        out: List[Tuple[int, int, int]] = []
        for z in range(ZMAP_H):
            for x in range(ZMAP_W):
                page = self.cells[z * ZMAP_W + x]
                if page != 0xff:
                    out.append((x, z, page))
        return out

    def bounds(self) -> Optional[Tuple[int, int, int, int]]:
        used = self.used_cells()
        if not used:
            return None
        xs = [x for x, _, _ in used]
        zs = [z for _, z, _ in used]
        return min(xs), min(zs), max(xs), max(zs)

    def to_dict(self, include_cells: bool = True) -> dict:
        used = self.used_cells()
        hist = Counter(page for _, _, page in used)
        d = {
            'active_count': self.active_count,
            'used_cell_count': len(used),
            'bounds': list(self.bounds()) if self.bounds() else None,
            'unique_page_indices_in_zmap': sorted(hist),
            'page_histogram': {str(k): v for k, v in sorted(hist.items())},
        }
        if include_cells:
            d['used_cells'] = [{'x': x, 'z': z, 'page': p} for x, z, p in used]
        return d


def decode_zmap(data: bytes, chunks: Sequence[Chunk]) -> ZMap:
    c = first_chunk(chunks, 'ZMAP', 'TDEF') or first_chunk(chunks, 'ZMAP')
    if c is None:
        raise ValueError('mission has no ZMAP chunk')
    need = 1 + ZMAP_W * ZMAP_H
    if c.payload_size < need:
        raise ValueError(f'ZMAP at 0x{c.offset:x} too small: {c.payload_size} < {need}')
    return ZMap(data[c.payload_offset], list(data[c.payload_offset + 1:c.payload_offset + need]))


def decode_zone_name(data: bytes, chunks: Sequence[Chunk]) -> str:
    c = first_chunk(chunks, 'ZONE', 'TDEF') or first_chunk(chunks, 'ZONE')
    if c is None:
        return ''
    payload = data[c.payload_offset:c.end]
    candidates: List[str] = []
    for start in (0, 1, 4, 8, 9, 12, 16):
        if start < len(payload):
            s = payload[start:].split(b'\0', 1)[0].decode('ascii', errors='ignore').strip()
            if s:
                candidates.append(s)
    for s in candidates:
        if s.lower().endswith(('.ter', '.tab', '.lvl')):
            return s
    for s in candidates:
        if '.' in s:
            return s
    return candidates[0] if candidates else ''


def find_files(root: Path) -> List[Path]:
    if root.is_file():
        return [root]
    return [p for p in root.rglob('*') if p.is_file()]


def find_sidecar(msn: Path, sidecar_name: str, by_name: Dict[str, Path]) -> Optional[Path]:
    candidates: List[Optional[Path]] = []
    if sidecar_name:
        candidates += [msn.parent / sidecar_name, msn.parent / sidecar_name.upper(), msn.parent / sidecar_name.lower(), by_name.get(sidecar_name.lower())]
    for ext in ('.ter', '.TER'):
        candidates += [msn.with_suffix(ext), by_name.get(msn.stem.lower() + ext.lower())]
    for c in candidates:
        if c is not None and Path(c).exists():
            return Path(c)
    return None


def load_ter_pages(path: Path, expected_count: int) -> List[Tuple[int, ...]]:
    data = path.read_bytes()
    if len(data) % PAGE_SIZE_BYTES:
        raise ValueError(f'{path} size 0x{len(data):x} is not a multiple of 0x{PAGE_SIZE_BYTES:x}')
    count = len(data) // PAGE_SIZE_BYTES
    if expected_count and count < expected_count:
        raise ValueError(f'{path} has {count} pages but ZMAP active_count is {expected_count}')
    fmt = '<' + 'H' * PAGE_SAMPLES
    return [struct.unpack_from(fmt, data, i * PAGE_SIZE_BYTES) for i in range(count)]


@dataclasses.dataclass(frozen=True)
class PageRef:
    page_index: int
    page: Optional[Tuple[int, ...]]


class RuntimeTerrain:
    def __init__(self, zmap: ZMap, pages: Sequence[Tuple[int, ...]]):
        self.zmap = zmap
        self.pages = list(pages)
        self.default_page = PageRef(0, self.pages[0] if self.pages else None)
        self.page_grid: List[PageRef] = [self.default_page for _ in range(RUNTIME_GRID_W * RUNTIME_GRID_H)]
        self.build_page_grid()

    def build_page_grid(self) -> None:
        for zx, zz, page_idx in self.zmap.used_cells():
            gx, gz = zx + RUNTIME_ZMAP_OFFSET, zz + RUNTIME_ZMAP_OFFSET
            if 0 <= gx < RUNTIME_GRID_W and 0 <= gz < RUNTIME_GRID_H:
                page = self.pages[page_idx] if 0 <= page_idx < len(self.pages) else None
                self.page_grid[gz * RUNTIME_GRID_W + gx] = PageRef(page_idx, page)

    def page_ref_for_sample(self, sx: int, sz: int) -> PageRef:
        bx, bz = sx + RUNTIME_LOOKUP_BIAS, sz + RUNTIME_LOOKUP_BIAS
        gx, gz = (bx >> 7) & 0x7f, (bz >> 7) & 0x7f
        return self.page_grid[gz * RUNTIME_GRID_W + gx]

    def word_at(self, sx: int, sz: int) -> int:
        ref = self.page_ref_for_sample(sx, sz)
        if ref.page is None:
            return 0
        bx, bz = sx + RUNTIME_LOOKUP_BIAS, sz + RUNTIME_LOOKUP_BIAS
        lx, lz = bx & 0x7f, bz & 0x7f
        return ref.page[lz * PAGE_W + lx]

    def height_low12(self, sx: int, sz: int) -> int:
        return self.word_at(sx, sz) & 0x0fff

    def surface_class(self, sx: int, sz: int) -> int:
        return self.word_at(sx, sz) >> 13

    @staticmethod
    def surface_split_condition(word: int) -> bool:
        return word > 0x3fff and (word & 0xe000) != 0xa000

    def page_grid_summary(self) -> dict:
        hist = Counter(ref.page_index for ref in self.page_grid)
        active = []
        for gz in range(RUNTIME_GRID_H):
            for gx in range(RUNTIME_GRID_W):
                ref = self.page_grid[gz * RUNTIME_GRID_W + gx]
                if ref.page_index != 0 or ref is not self.default_page:
                    active.append({'grid_x': gx, 'grid_z': gz, 'page': ref.page_index})
        return {
            'grid_w': RUNTIME_GRID_W, 'grid_h': RUNTIME_GRID_H,
            'zmap_offset': RUNTIME_ZMAP_OFFSET,
            'lookup_bias_samples': RUNTIME_LOOKUP_BIAS,
            'page_index_histogram': {str(k): v for k, v in sorted(hist.items())},
            'active_slot_count': len(active), 'active_slots': active,
        }


@dataclasses.dataclass
class Vertex:
    sx: int
    sz: int
    height: int
    word: int
    surface: int


@dataclasses.dataclass
class EdgeRecord:
    vertex_a: int
    vertex_b: int
    child_edge_a: Optional[int] = None
    child_edge_b: Optional[int] = None


@dataclasses.dataclass
class PrimitiveNode:
    screen_or_bucket_start: int
    screen_or_bucket_end: int
    range_delta: int
    next_index: Optional[int]
    edge_ref_0: int
    edge_ref_1: int
    edge_ref_2: int
    edge_ref_3: int
    depth: int
    sample_x0: int
    sample_z0: int
    sample_x1: int
    sample_z1: int
    material_or_surface: int


class AdaptiveBuilder:
    def __init__(self, terrain: RuntimeTerrain, args: argparse.Namespace):
        self.t = terrain
        self.args = args
        self.vertices: List[Vertex] = []
        self.vertex_by_sample: Dict[Tuple[int, int], int] = {}
        self.edges: List[EdgeRecord] = []
        self.edge_by_key: Dict[Tuple[int, int], int] = {}
        self.primitives: List[PrimitiveNode] = []
        self.faces: List[List[int]] = []
        self.stats = Counter()
        self.depth_hist = Counter()
        self.surface_hist = Counter()

    def get_vertex(self, sx: int, sz: int) -> int:
        key = (sx, sz)
        old = self.vertex_by_sample.get(key)
        if old is not None:
            return old
        word = self.t.word_at(sx, sz)
        self.vertices.append(Vertex(sx, sz, word & 0x0fff, word, word >> 13))
        idx = len(self.vertices) - 1
        self.vertex_by_sample[key] = idx
        return idx

    def get_edge(self, va: int, vb: int) -> int:
        key = (min(va, vb), max(va, vb))
        old = self.edge_by_key.get(key)
        if old is not None:
            return old
        self.edges.append(EdgeRecord(va, vb))
        idx = len(self.edges) - 1
        self.edge_by_key[key] = idx
        return idx

    def link_split_edge(self, edge_idx: int, mid: int) -> None:
        e = self.edges[edge_idx]
        if e.child_edge_a is not None:
            return
        e.child_edge_a = self.get_edge(e.vertex_a, mid)
        e.child_edge_b = self.get_edge(mid, e.vertex_b)

    def flatten_forward(self, edge_idx: int, out: List[int]) -> None:
        e = self.edges[edge_idx]
        if e.child_edge_a is not None and e.child_edge_b is not None:
            self.flatten_forward(e.child_edge_a, out)
            self.flatten_forward(e.child_edge_b, out)
        else:
            out.append(e.vertex_a)

    def flatten_reverse(self, edge_idx: int, out: List[int]) -> None:
        e = self.edges[edge_idx]
        if e.child_edge_a is not None and e.child_edge_b is not None:
            self.flatten_reverse(e.child_edge_b, out)
            self.flatten_reverse(e.child_edge_a, out)
        else:
            out.append(e.vertex_b)

    def quad_error(self, x0: int, z0: int, x1: int, z1: int) -> Tuple[float, bool, int]:
        xm, zm = (x0 + x1) // 2, (z0 + z1) // 2
        h00, h10 = self.t.height_low12(x0, z0), self.t.height_low12(x1, z0)
        h11, h01 = self.t.height_low12(x1, z1), self.t.height_low12(x0, z1)
        hc = self.t.height_low12(xm, zm)
        err = abs(hc - ((h00 + h10 + h11 + h01) * 0.25))
        surf_trigger = False
        surf_votes = Counter()
        probes = [(x0, z0), (x1, z0), (x1, z1), (x0, z1), (xm, zm),
                  ((x0 + xm) // 2, (z0 + zm) // 2), ((xm + x1) // 2, (z0 + zm) // 2),
                  ((xm + x1) // 2, (zm + z1) // 2), ((x0 + xm) // 2, (zm + z1) // 2)]
        for px, pz in probes:
            word = self.t.word_at(px, pz)
            surf_trigger = surf_trigger or RuntimeTerrain.surface_split_condition(word)
            surf_votes[word >> 13] += 1
        return err, surf_trigger, surf_votes.most_common(1)[0][0] if surf_votes else 0

    def should_split(self, x0: int, z0: int, x1: int, z1: int, depth: int) -> Tuple[bool, int]:
        size = max(x1 - x0, z1 - z0)
        err, surf, material = self.quad_error(x0, z0, x1, z1)
        if surf:
            self.stats['surface_trigger_tests'] += 1
        if depth >= self.args.max_depth or size <= self.args.min_quad_samples:
            return False, material
        cx = ((x0 + x1) * 0.5) * SAMPLE_SIZE_WORLD
        cz = ((z0 + z1) * 0.5) * SAMPLE_SIZE_WORLD
        dist = math.hypot(cx - self.args.camera_x, cz - self.args.camera_z)
        scaled_err = err * (size / PAGE_W) / (1.0 + dist / max(1.0, self.args.distance_scale))
        if self.args.force_surface_splits and surf:
            return True, material
        return scaled_err >= self.args.split_error, material

    def prelink_split_edges(self, x0: int, z0: int, x1: int, z1: int) -> None:
        xm, zm = (x0 + x1) // 2, (z0 + z1) // 2
        v00, v10 = self.get_vertex(x0, z0), self.get_vertex(x1, z0)
        v11, v01 = self.get_vertex(x1, z1), self.get_vertex(x0, z1)
        vt, vr = self.get_vertex(xm, z0), self.get_vertex(x1, zm)
        vb, vl = self.get_vertex(xm, z1), self.get_vertex(x0, zm)
        self.link_split_edge(self.get_edge(v00, v10), vt)
        self.link_split_edge(self.get_edge(v10, v11), vr)
        self.link_split_edge(self.get_edge(v01, v11), vb)
        self.link_split_edge(self.get_edge(v00, v01), vl)
        self.get_vertex(xm, zm)

    def emit_leaf(self, x0: int, z0: int, x1: int, z1: int, depth: int, material: int) -> None:
        v00, v10 = self.get_vertex(x0, z0), self.get_vertex(x1, z0)
        v11, v01 = self.get_vertex(x1, z1), self.get_vertex(x0, z1)
        edge_ref_2 = self.get_edge(v00, v10)  # top
        edge_ref_1 = self.get_edge(v10, v11)  # right
        edge_ref_3 = self.get_edge(v01, v11)  # bottom, reverse
        edge_ref_0 = self.get_edge(v00, v01)  # left, reverse
        out: List[int] = []
        self.flatten_forward(edge_ref_2, out)
        self.flatten_forward(edge_ref_1, out)
        self.flatten_reverse(edge_ref_3, out)
        self.flatten_reverse(edge_ref_0, out)
        cleaned: List[int] = []
        for vi in out:
            if not cleaned or cleaned[-1] != vi:
                cleaned.append(vi)
        if len(cleaned) > 1 and cleaned[0] == cleaned[-1]:
            cleaned.pop()
        if len(cleaned) >= 3:
            self.faces.append(cleaned)
        if self.primitives:
            self.primitives[-1].next_index = len(self.primitives)
        self.primitives.append(PrimitiveNode(0, 0, max(x1 - x0, z1 - z0), None,
                                             edge_ref_0, edge_ref_1, edge_ref_2, edge_ref_3,
                                             depth, x0, z0, x1, z1, material))
        self.depth_hist[depth] += 1
        self.surface_hist[material] += 1

    def subdivide(self, x0: int, z0: int, x1: int, z1: int, depth: int = 0) -> None:
        self.stats['quad_tests'] += 1
        split, material = self.should_split(x0, z0, x1, z1, depth)
        if not split:
            self.emit_leaf(x0, z0, x1, z1, depth, material)
            return
        self.stats['quad_splits'] += 1
        self.prelink_split_edges(x0, z0, x1, z1)
        xm, zm = (x0 + x1) // 2, (z0 + z1) // 2
        self.subdivide(x0, z0, xm, zm, depth + 1)
        self.subdivide(xm, z0, x1, zm, depth + 1)
        self.subdivide(xm, zm, x1, z1, depth + 1)
        self.subdivide(x0, zm, xm, z1, depth + 1)

    def build(self) -> None:
        for cell_x, cell_z, _ in self.t.zmap.used_cells():
            x0, z0 = cell_x * PAGE_W, cell_z * PAGE_H
            self.subdivide(x0, z0, x0 + PAGE_W, z0 + PAGE_H, 0)

    def stats_dict(self) -> dict:
        sides = Counter(len(f) for f in self.faces)
        return {
            'vertices': len(self.vertices), 'edges': len(self.edges),
            'primitive_nodes': len(self.primitives), 'faces': len(self.faces),
            'quad_tests': self.stats['quad_tests'], 'quad_splits': self.stats['quad_splits'],
            'surface_trigger_tests': self.stats['surface_trigger_tests'],
            'leaf_depth_histogram': {str(k): v for k, v in sorted(self.depth_hist.items())},
            'surface_histogram': {str(k): v for k, v in sorted(self.surface_hist.items())},
            'face_vertex_count_histogram': {str(k): v for k, v in sorted(sides.items())},
        }

def origin_for_zmap(zmap: ZMap, mode: str) -> Tuple[float, float]:
    b = zmap.bounds()
    if b is None or mode == 'absolute':
        return 0.0, 0.0
    min_x, min_z, max_x, max_z = b
    if mode == 'min-corner':
        return min_x * PATCH_SIZE_WORLD, min_z * PATCH_SIZE_WORLD
    if mode == 'open76-centered':
        return (min_x + max_x) * 0.5 * PATCH_SIZE_WORLD, (min_z + max_z) * 0.5 * PATCH_SIZE_WORLD
    raise ValueError(f'unknown origin mode {mode}')


def vertex_coord(v: Vertex, origin_x: float, origin_z: float, vertical_scale: float, mode: str) -> Tuple[float, float, float]:
    wx = v.sx * SAMPLE_SIZE_WORLD - origin_x
    wz = v.sz * SAMPLE_SIZE_WORLD - origin_z
    h = v.height * vertical_scale
    if mode == 'blender':
        return wx, wz, h
    if mode == 'y-up':
        return wx, h, wz
    raise ValueError(f'unknown OBJ coordinate mode {mode}')


def sub3(a, b): return a[0] - b[0], a[1] - b[1], a[2] - b[2]
def cross3(a, b): return (a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0])
def norm3(v):
    n = math.sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2])
    return (0.0, 0.0, 1.0) if n <= 1e-12 else (v[0]/n, v[1]/n, v[2]/n)


def compute_normals(coords: Sequence[Tuple[float, float, float]], faces: Sequence[Sequence[int]]) -> List[Tuple[float, float, float]]:
    acc = [[0.0, 0.0, 0.0] for _ in coords]
    for face in faces:
        if len(face) < 3:
            continue
        p0 = coords[face[0]]
        for i in range(1, len(face) - 1):
            n = cross3(sub3(coords[face[i]], p0), sub3(coords[face[i + 1]], p0))
            for vi in (face[0], face[i], face[i + 1]):
                acc[vi][0] += n[0]; acc[vi][1] += n[1]; acc[vi][2] += n[2]
    return [norm3((x, y, z)) for x, y, z in acc]


def write_obj(path: Path, mission: Path, ter: Path, zmap: ZMap, b: AdaptiveBuilder, args: argparse.Namespace) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    ox, oz = origin_for_zmap(zmap, args.origin)
    coords = [vertex_coord(v, ox, oz, args.vertical_scale, args.obj_coordinates) for v in b.vertices]
    normals = compute_normals(coords, b.faces) if args.write_normals else []
    with path.open('w', encoding='utf-8') as f:
        f.write("# Interstate '76 runtime-shaped adaptive terrain OBJ v1\n")
        f.write('# Confirmed: BWD2/TDEF/ZMAP/ZONE parsing, TER pages, runtime page-grid lookup.\n')
        f.write('# Approximate: adaptive split predicate pending exact 00490a00/004911e0 parity.\n')
        f.write(f'# mission={mission}\n# ter={ter}\n')
        f.write(f'# origin={args.origin} obj_coordinates={args.obj_coordinates}\n')
        f.write(f'o {mission.stem.lower()}_runtime_adaptive_terrain\n')
        f.write(f'g {mission.stem.lower()}_runtime_adaptive_terrain\n')
        for x, y, z in coords:
            f.write(f'v {x:.6f} {y:.6f} {z:.6f}\n')
        if args.write_normals:
            for nx, ny, nz in normals:
                f.write(f'vn {nx:.8f} {ny:.8f} {nz:.8f}\n')
        for face in b.faces:
            one = [vi + 1 for vi in face]
            if args.write_normals:
                f.write('f ' + ' '.join(f'{vi}//{vi}' for vi in one) + '\n')
            else:
                f.write('f ' + ' '.join(str(vi) for vi in one) + '\n')


def write_debug(debug_dir: Path, mission: Path, chunks: Sequence[Chunk], zmap: ZMap, terrain: RuntimeTerrain, b: AdaptiveBuilder) -> None:
    debug_dir.mkdir(parents=True, exist_ok=True)
    (debug_dir / f'{mission.stem.lower()}.chunks.json').write_text(json.dumps([c.to_dict() for c in chunks], indent=2), encoding='utf-8')
    (debug_dir / f'{mission.stem.lower()}.zmap.json').write_text(json.dumps(zmap.to_dict(True), indent=2), encoding='utf-8')
    (debug_dir / f'{mission.stem.lower()}.page_grid.json').write_text(json.dumps(terrain.page_grid_summary(), indent=2), encoding='utf-8')
    (debug_dir / f'{mission.stem.lower()}.adaptive_primitives_sample.json').write_text(
        json.dumps({'count_total': len(b.primitives), 'items': [dataclasses.asdict(p) for p in b.primitives[:200000]]}, indent=2), encoding='utf-8')
    (debug_dir / f'{mission.stem.lower()}.edge_records_sample.json').write_text(
        json.dumps({'count_total': len(b.edges), 'items': [dataclasses.asdict(e) for e in b.edges[:200000]]}, indent=2), encoding='utf-8')
    with (debug_dir / f'{mission.stem.lower()}.height_probes.tsv').open('w', encoding='utf-8') as f:
        f.write('sample_x\tsample_z\tpage_index\tlocal_x\tlocal_z\tword_hex\theight_low12\tsurface_class\tspecial_flag\n')
        probes: List[Tuple[int, int]] = []
        bounds = zmap.bounds()
        if bounds:
            min_x, min_z, max_x, max_z = bounds
            for cz in (min_z, (min_z + max_z)//2, max_z):
                for cx in (min_x, (min_x + max_x)//2, max_x):
                    probes += [(cx*PAGE_W, cz*PAGE_H), (cx*PAGE_W+64, cz*PAGE_H+64), (cx*PAGE_W+127, cz*PAGE_H+127)]
        seen = set()
        for sx, sz in probes:
            if (sx, sz) in seen:
                continue
            seen.add((sx, sz))
            ref = terrain.page_ref_for_sample(sx, sz)
            bx, bz = sx + RUNTIME_LOOKUP_BIAS, sz + RUNTIME_LOOKUP_BIAS
            word = terrain.word_at(sx, sz)
            f.write(f'{sx}\t{sz}\t{ref.page_index}\t{bx & 0x7f}\t{bz & 0x7f}\t0x{word:04x}\t{word & 0x0fff}\t{word >> 13}\t{(word >> 12) & 1}\n')


def out_dir_for(args: argparse.Namespace) -> Path:
    if args.out_dir is not None:
        return args.out_dir
    return args.default_root / time.strftime('i76_runtime_adaptive_terrain_v1_%Y%m%d_%H%M%S')


def make_tar(out_dir: Path) -> Optional[Path]:
    tar_path = out_dir.with_suffix('.tar')
    try:
        with tarfile.open(tar_path, 'w') as tf:
            tf.add(out_dir, arcname=out_dir.name)
        return tar_path
    except Exception:
        return None


def export(args: argparse.Namespace) -> dict:
    files = find_files(args.input)
    by_name = {p.name.lower(): p for p in files}
    missions = [p for p in files if p.suffix.lower() in MISSION_SUFFIXES]
    if args.mission_filter:
        mf = args.mission_filter.lower()
        missions = [p for p in missions if mf in p.name.lower() or mf in p.stem.lower()]
    out_dir = out_dir_for(args)
    obj_dir = out_dir / 'terrain_obj'
    debug_root = out_dir / 'debug'
    out_dir.mkdir(parents=True, exist_ok=True)
    manifest = {
        'format': 'i76_runtime_adaptive_terrain_export_manifest', 'version': 1,
        'source': str(args.input), 'missions_seen': len(missions),
        'runtime_confirmed': [
            'BWD2 nested chunk scan', 'TDEF/ZMAP/ZONE extraction',
            'TER page size 0x8000, 128x128 uint16 little-endian',
            '128x128 runtime page pointer grid with ZMAP +24/+24 offset',
            'height lookup through biased page grid using +0xc00 and 0x7f masks',
            'surface class word >> 13',
            'surface split condition: (word > 0x3fff) && ((word & 0xe000) != 0xa000)',
            'edge flatten diagnostic order: edge_ref_2 forward, edge_ref_1 forward, edge_ref_3 reverse, edge_ref_0 reverse',
        ],
        'runtime_approximate': [
            'exact 00490a00/004911e0 projected-error and camera predicate',
            'exact primitive screen/bucket fields',
            'exact hardware/software terrain polygon work-record contents',
        ],
        'options': vars(args) | {'input': str(args.input), 'out_dir': str(out_dir), 'default_root': str(args.default_root)},
        'terrain': [], 'warnings': [],
    }
    for mission in sorted(missions):
        try:
            data = mission.read_bytes()
            chunks = parse_tree(data)
            zmap = decode_zmap(data, chunks)
            zone_name = decode_zone_name(data, chunks)
            ter = find_sidecar(mission, zone_name, by_name)
            if ter is None:
                manifest['warnings'].append(f'{mission}: no TER sidecar found for ZONE name {zone_name!r}')
                continue
            pages = load_ter_pages(ter, zmap.active_count)
            terrain = RuntimeTerrain(zmap, pages)
            builder = AdaptiveBuilder(terrain, args)
            builder.build()
            obj_path = obj_dir / f'{mission.stem.lower()}.runtime_adaptive_v1.obj'
            write_obj(obj_path, mission, ter, zmap, builder, args)
            if args.write_debug:
                write_debug(debug_root / mission.stem.lower(), mission, chunks, zmap, terrain, builder)
            manifest['terrain'].append({
                'mission': str(mission), 'sidecar': str(ter), 'zone_sidecar_name': zone_name,
                'obj_path': str(obj_path), 'zmap_summary': zmap.to_dict(False),
                'builder_stats': builder.stats_dict(),
            })
        except Exception as exc:
            manifest['warnings'].append(f'{mission}: {type(exc).__name__}: {exc}')
    manifest_path = out_dir / 'i76_runtime_adaptive_terrain_export_manifest_v1.json'
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding='utf-8')
    tar_path = make_tar(out_dir) if args.make_tar else None
    result = {'out_dir': str(out_dir), 'manifest': str(manifest_path), 'tar': str(tar_path) if tar_path else None,
              'missions_seen': len(missions), 'terrain_objs': len(manifest['terrain']), 'warnings': len(manifest['warnings'])}
    print(json.dumps(result, indent=2))
    if args.fail_empty and not manifest['terrain']:
        raise SystemExit('no terrain OBJs generated')
    return result


def parser() -> argparse.ArgumentParser:
    ap = argparse.ArgumentParser(description="Export Interstate '76 runtime-shaped adaptive terrain OBJ diagnostics from miss8/miss16 missions.")
    ap.add_argument('input', type=Path, help='Mission directory or single .MSN/.SPC/.LVL file')
    ap.add_argument('--out-dir', type=Path, default=None)
    ap.add_argument('--default-root', type=Path, default=DEFAULT_ROOT)
    ap.add_argument('--mission-filter', default='', help='Substring filter such as m06, s05, t01')
    ap.add_argument('--origin', choices=['open76-centered', 'min-corner', 'absolute'], default='open76-centered')
    ap.add_argument('--obj-coordinates', choices=['blender', 'y-up'], default='blender')
    ap.add_argument('--vertical-scale', type=float, default=DEFAULT_VERTICAL_SCALE)
    ap.add_argument('--camera-x', type=float, default=0.0, help='Camera X in world units for approximate adaptive split heuristic')
    ap.add_argument('--camera-z', type=float, default=0.0, help='Camera Z in world units for approximate adaptive split heuristic')
    ap.add_argument('--max-depth', type=int, default=5)
    ap.add_argument('--min-quad-samples', type=int, default=4)
    ap.add_argument('--split-error', type=float, default=8.0)
    ap.add_argument('--distance-scale', type=float, default=5000.0)
    ap.add_argument('--force-surface-splits', action='store_true')
    ap.add_argument('--write-normals', action='store_true')
    ap.add_argument('--write-debug', action='store_true')
    ap.add_argument('--make-tar', action='store_true', default=True)
    ap.add_argument('--no-tar', dest='make_tar', action='store_false')
    ap.add_argument('--fail-empty', action='store_true')
    return ap


def main() -> int:
    export(parser().parse_args())
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
