#!/usr/bin/env python3
"""
Interstate '76 level reconstruction exporter, v19.

Baseline intent:
  - Return to the repo/local_history v4 mission parser model: parse retail .MSN/.SPC/.LVL
    as BWD2-style chunk containers instead of raw sliding-window ODEF scans.
  - Preserve the practical v4 terrain / ODEF axes / RSEG probe outputs.
  - Add v42/v43 class-specific ODEF/LDEF resource policy diagnostics:
        ODEF class 0x01 ordinary, 0x08, 0x09 -> label.vcf
        ODEF class 0x01 spawn/regen             -> special marker
        ODEF static classes                     -> label.sdf
        LDEF OBJ records                        -> label.sdf
  - Add strict Open76-aligned SGEO SdfPart parsing for SDF -> GEO child resolution.
  - Optionally import the historical texture/resource resolver to see embedded PIX/PAK/ZFS assets.
  - Add v15 validation outputs: static bounds, transform diagnostics, and combined mission scene OBJ assembly.
  - Add v16/v17 static GEO face material diagnostics and grouped summaries.
  - Add v18 static texture PNG extraction/binding for resolved M16/VQM assets.
  - Add v18 first-pass terrain surface-class materials for dense ground mesh.
  - Add v19 explicit terrain-code legend fields so diagnostic ground colors are easier to interpret.

This is still a reconstruction/probe script, not a final renderer clone.  It is intentionally
conservative: unresolved resources are emitted to TSV/JSON rather than guessed.
"""
from __future__ import annotations

import argparse
import csv
import importlib.util
import dataclasses
import json
import math
import os
import re
import shutil
import struct
import subprocess
import sys
import time
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple, Any

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
SDF_PART_SIZE = 0x78
SAMPLE_WORLD_SCALE = PATCH_WORLD_SIZE / PAGE_W
DEFAULT_VERTICAL_SCALE = 409.5 / 4096.0
DEFAULT_ROOT = Path("/media/neon-remote/prj/i76/scratch_data")

CONTAINER_TAGS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF", "SDFC"}
MISSION_EXTS = {".msn", ".spc", ".lvl"}
RESOURCE_EXTS = {".sdf", ".vcf", ".geo", ".tmt", ".map", ".m16", ".vqm", ".cbk", ".vdf", ".vtf", ".wdf"}

VCF_CLASSES = {0x01, 0x08, 0x09}
SDF_CLASSES = set([0x02, 0x03, 0x04, 0x07, 0x0A, 0x0B, 0x0C, 0x50, 0x52, 0x53])
FALLBACK_CLASSES = set(range(0x05, 0x07)) | set(range(0x0D, 0x50)) | {0x51}
STATIC_SDF_LDEF = "sdf_lDEF_all_normal_records"

ASCII_TOKEN_RE = re.compile(rb"[A-Za-z0-9_][A-Za-z0-9_.$@#\-]{1,31}")


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


def safe_name(s: str) -> str:
    s = s.strip().replace("\x00", "")
    return re.sub(r"[^A-Za-z0-9_.@#\-]+", "_", s) or "unnamed"


def lower_ext_name(path: Path) -> str:
    return path.name.lower()


def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    chunks: List[Chunk] = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        try:
            size = u32(data, off + 4)
        except struct.error:
            break
        if size < 8 or off + size > end:
            break
        chunks.append(Chunk(tag, off, size, off + 8, size - 8, parent))
        off += size
    return chunks



def load_optional_resolver_module(path: Optional[Path]):
    if path is None:
        return None
    if not path.exists():
        raise FileNotFoundError(f"resolver script does not exist: {path}")
    spec = importlib.util.spec_from_file_location("i76_embedded_resolver", str(path))
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not load resolver script: {path}")
    mod = importlib.util.module_from_spec(spec)
    sys.modules["i76_embedded_resolver"] = mod
    spec.loader.exec_module(mod)  # type: ignore[union-attr]
    return mod


@dataclasses.dataclass
class EmbeddedAssetRef:
    name: str
    ext: str
    asset_id: str
    source: str


@dataclasses.dataclass
class EmbeddedAssetIndex:
    names: Dict[str, List[EmbeddedAssetRef]]
    warnings: List[str]
    payloads: Dict[str, bytes] = dataclasses.field(default_factory=dict)
    resolver_index: Any = None
    resolver_module: Any = None

    def all_hits(self, name: str) -> List[EmbeddedAssetRef]:
        return list(self.names.get((name or "").lower()) or [])

    def first_hit(self, name: str) -> Optional[EmbeddedAssetRef]:
        hits = self.all_hits(name)
        return hits[0] if hits else None

    def first_payload(self, name: str) -> Optional[bytes]:
        hit = self.first_hit(name)
        if hit is None:
            return None
        return self.payloads.get(hit.asset_id)

    def summary(self) -> dict:
        by_ext: Dict[str, int] = {}
        total = 0
        for refs in self.names.values():
            total += len(refs)
            for r in refs:
                by_ext[r.ext] = by_ext.get(r.ext, 0) + 1
        return {"unique_names": len(self.names), "total_assets": total, "by_ext": dict(sorted(by_ext.items()))}


def build_embedded_asset_index(args, manifest_warnings: Optional[List[str]] = None) -> EmbeddedAssetIndex:
    """Optionally build an in-memory embedded asset-name index via the historical resolver.

    v9 only indexed ordinary files under --resource-root.  That is enough for root SDF/VCF files,
    but most GEO/TMT/M16/VQM/MAP payloads are embedded behind the PIX/PAK/ZFS resource stack.
    The older vehicle exporter already delegates this to i76_vehicle_texture_slot_resolver_v5.py;
    this hook reuses that module when --resolver and --zfs are supplied.

    This index is currently name/identity only.  It proves that SDF child partName.geo rows resolve
    into the embedded resource stack, but it does not yet extract GEO bytes into static OBJ meshes.
    """
    warnings: List[str] = []
    def warn(msg: str) -> None:
        warnings.append(msg)
        if manifest_warnings is not None:
            manifest_warnings.append(msg)

    resolver_path = getattr(args, "resolver", None)
    zfs_path = getattr(args, "zfs", None)
    if resolver_path is None or zfs_path is None:
        return EmbeddedAssetIndex({}, warnings)
    try:
        resolver = load_optional_resolver_module(Path(resolver_path))
        wanted_exts = {"sdf", "vcf", "vdf", "vtf", "wdf", "gdf", "pix", "pak", "tmt", "map", "m16", "vqm", "cbk", "geo"}
        header, records = resolver.parse_zfs_records(Path(zfs_path))
        payloads, errors = resolver.decompress_records(Path(zfs_path), records, wanted_exts)
        for e in errors or []:
            warn(f"embedded resolver decompress warning: {e}")
        idx, idx_warnings = resolver.build_asset_index(records, payloads, None)
        for w in idx_warnings or []:
            warn(f"embedded resolver index warning: {w}")
        names: Dict[str, List[EmbeddedAssetRef]] = {}
        asset_payloads: Dict[str, bytes] = {}
        for a in getattr(idx, "assets", []) or []:
            name = str(getattr(a, "name", "") or "")
            ext = str(getattr(a, "ext", "") or "").lower().lstrip(".")
            if not name:
                continue
            asset_id = str(getattr(a, "asset_id", name) or name)
            source = str(getattr(a, "source", "embedded") or "embedded")
            ref = EmbeddedAssetRef(name=name, ext=ext, asset_id=asset_id, source=source)
            names.setdefault(name.lower(), []).append(ref)
            payload = getattr(idx, "payloads", {}).get(asset_id)
            if payload is not None:
                asset_payloads[asset_id] = payload
        for k in names:
            names[k].sort(key=lambda r: (r.ext, r.source, r.name.lower(), r.asset_id))
        return EmbeddedAssetIndex(names, warnings, asset_payloads, idx, resolver)
    except Exception as e:
        warn(f"embedded resolver unavailable: {e}")
        return EmbeddedAssetIndex({}, warnings)


def load_optional_geo_exporter_module(path: Optional[Path]):
    if path is None:
        return None
    if not path.exists():
        raise FileNotFoundError(f"geo exporter script does not exist: {path}")
    spec = importlib.util.spec_from_file_location("i76_geo_exporter_v20", str(path))
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not load geo exporter script: {path}")
    mod = importlib.util.module_from_spec(spec)
    sys.modules["i76_geo_exporter_v20"] = mod
    spec.loader.exec_module(mod)  # type: ignore[union-attr]
    if not hasattr(mod, "parse_geo"):
        raise RuntimeError(f"geo exporter script lacks parse_geo(): {path}")
    return mod


def default_geo_exporter_from_args(args: argparse.Namespace) -> Optional[Path]:
    explicit = getattr(args, "geo_exporter", None)
    if explicit:
        return Path(explicit)
    resolver = getattr(args, "resolver", None)
    if resolver:
        candidate = Path(resolver).with_name("i76_vehicle_geo_obj_export_v20.py")
        if candidate.exists():
            return candidate
    return None


def frow(row: dict, key: str, default: float = 0.0) -> float:
    try:
        v = row.get(key, default)
        if v == "" or v is None:
            return default
        return float(v)
    except Exception:
        return default


@dataclasses.dataclass
class SimpleTransform:
    name: str
    parent_name: str
    right: Tuple[float, float, float]
    up: Tuple[float, float, float]
    forward: Tuple[float, float, float]
    position: Tuple[float, float, float]
    source: str = ""


def transform_vec3(t: SimpleTransform, v: Sequence[float]) -> Tuple[float, float, float]:
    x, y, z = float(v[0]), float(v[1]), float(v[2])
    return (
        t.right[0] * x + t.up[0] * y + t.forward[0] * z,
        t.right[1] * x + t.up[1] * y + t.forward[1] * z,
        t.right[2] * x + t.up[2] * y + t.forward[2] * z,
    )


def transform_point3(t: SimpleTransform, p: Sequence[float]) -> Tuple[float, float, float]:
    v = transform_vec3(t, p)
    return (t.position[0] + v[0], t.position[1] + v[1], t.position[2] + v[2])


def compose_simple_transform(parent: SimpleTransform, local: SimpleTransform) -> SimpleTransform:
    return SimpleTransform(
        name=local.name,
        parent_name=local.parent_name,
        right=transform_vec3(parent, local.right),
        up=transform_vec3(parent, local.up),
        forward=transform_vec3(parent, local.forward),
        position=transform_point3(parent, local.position),
        source=local.source,
    )


def object_transform_from_static_row(row: dict) -> SimpleTransform:
    basis = parse_basis_csv(row.get("object_basis", ""))
    m = mat3_from_basis_tuple(basis)
    return SimpleTransform(
        name=str(row.get("object_label", "object")),
        parent_name="WORLD",
        right=(m[0][0], m[0][1], m[0][2]),
        up=(m[1][0], m[1][1], m[1][2]),
        forward=(m[2][0], m[2][1], m[2][2]),
        position=(frow(row, "object_pos_x"), frow(row, "object_pos_y"), frow(row, "object_pos_z")),
        source="ODEF_LDEF_object_basis",
    )


def local_transform_from_static_row(row: dict) -> SimpleTransform:
    return SimpleTransform(
        name=str(row.get("token", "part")),
        parent_name=str(row.get("parent_name", "")),
        right=(frow(row, "right_x", 1.0), frow(row, "right_y"), frow(row, "right_z")),
        up=(frow(row, "up_x"), frow(row, "up_y", 1.0), frow(row, "up_z")),
        forward=(frow(row, "forward_x"), frow(row, "forward_y"), frow(row, "forward_z", 1.0)),
        position=(frow(row, "pos_x"), frow(row, "pos_y"), frow(row, "pos_z")),
        source="SDF_SGEO_declared_part",
    )


def resolve_static_part_hierarchy(rows: List[dict]) -> Tuple[Dict[int, SimpleTransform], List[dict]]:
    """Resolve SGEO parent hierarchy for one ODEF/LDEF object instance.

    Rows are expected to be declared SGEO part rows belonging to the same mission/object/sdf.
    The returned dict maps id(row) to the composed world transform.  Parent strings WORLD/NULL/empty
    are attached directly to the object transform.  Missing parents are reported and treated as root.
    """
    if not rows:
        return {}, []
    object_t = object_transform_from_static_row(rows[0])
    by_name: Dict[str, dict] = {}
    for r in rows:
        name = str(r.get("token", "")).upper()
        if name and name not in by_name:
            by_name[name] = r
    resolved: Dict[str, SimpleTransform] = {}
    out_by_id: Dict[int, SimpleTransform] = {}
    warnings: List[dict] = []

    def resolve_name(name: str, stack: Optional[List[str]] = None) -> SimpleTransform:
        key = name.upper()
        if key in resolved:
            return resolved[key]
        if stack is None:
            stack = []
        row = by_name.get(key)
        if row is None:
            return object_t
        if key in stack:
            warnings.append({
                "mission": row.get("mission", ""),
                "object_label": row.get("object_label", ""),
                "object_index": row.get("object_index", ""),
                "sdf_path": row.get("sdf_path", ""),
                "part": row.get("token", ""),
                "parent": row.get("parent_name", ""),
                "warning": "sgeo_parent_cycle:" + "->".join(stack + [key]),
            })
            resolved[key] = compose_simple_transform(object_t, local_transform_from_static_row(row))
            return resolved[key]
        local = local_transform_from_static_row(row)
        parent_key = (local.parent_name or "").upper()
        if parent_key in {"", "WORLD", "NULL"}:
            parent_t = object_t
        elif parent_key in by_name:
            parent_t = resolve_name(parent_key, stack + [key])
        else:
            warnings.append({
                "mission": row.get("mission", ""),
                "object_label": row.get("object_label", ""),
                "object_index": row.get("object_index", ""),
                "sdf_path": row.get("sdf_path", ""),
                "part": row.get("token", ""),
                "parent": row.get("parent_name", ""),
                "warning": "missing_sgeo_parent_treated_as_world",
            })
            parent_t = object_t
        resolved[key] = compose_simple_transform(parent_t, local)
        return resolved[key]

    for r in rows:
        key = str(r.get("token", "")).upper()
        if not key:
            continue
        t = resolve_name(key)
        out_by_id[id(r)] = t
    return out_by_id, warnings


def static_row_groups(rows: List[dict]) -> Dict[Tuple[str, str, str, str], List[dict]]:
    groups: Dict[Tuple[str, str, str, str], List[dict]] = {}
    for r in rows:
        key = (
            str(r.get("mission", "")),
            str(r.get("object_label", "")),
            str(r.get("object_index", "")),
            str(r.get("sdf_path", "")),
        )
        groups.setdefault(key, []).append(r)
    return groups


def geo_payload_for_static_row(row: dict, embedded_index: EmbeddedAssetIndex) -> Tuple[Optional[bytes], str]:
    source = str(row.get("geo_source", ""))
    geo_name = str(row.get("geo_name", ""))
    geo_path = str(row.get("geo_path", ""))
    if source == "file" and geo_path:
        try:
            return Path(geo_path).read_bytes(), "file"
        except Exception as e:
            return None, f"file_read_error:{e}"
    if source == "embedded" and geo_name:
        payload = embedded_index.first_payload(geo_name)
        if payload is not None:
            return payload, "embedded"
        return None, "embedded_payload_missing"
    return None, "no_geo_payload_source"


def clean_geo_texture_name(value: str) -> str:
    s = (value or "").replace("\x00", "").strip()
    s = s.replace("\\", "/").split("/")[-1]
    return s.strip()


def material_key_for_face(texture_name: str, color: Tuple[int, int, int]) -> str:
    tex = clean_geo_texture_name(texture_name)
    if tex:
        return "mat_" + safe_name(tex)
    return "mat_rgb_%02x%02x%02x" % (int(color[0]) & 0xff, int(color[1]) & 0xff, int(color[2]) & 0xff)


def texture_lookup_candidates(texture_name: str) -> List[str]:
    tex = clean_geo_texture_name(texture_name)
    if not tex:
        return []
    out: List[str] = []
    def add(x: str) -> None:
        x = clean_geo_texture_name(x)
        if x and x.lower() not in {v.lower() for v in out}:
            out.append(x)
    add(tex)
    stem = tex.rsplit('.', 1)[0] if '.' in tex else tex
    ext = tex.rsplit('.', 1)[1].lower() if '.' in tex else ''
    if not ext:
        for e in ("map", "m16", "vqm", "tmt", "cbk"):
            add(stem + "." + e)
    elif ext == "map":
        add(stem + ".m16")
        add(stem + ".vqm")
    elif ext in {"m16", "vqm"}:
        add(stem + ".map")
    return out


def resolve_texture_name_in_embedded_index(texture_name: str, embedded_index: EmbeddedAssetIndex) -> Tuple[str, str, str, int, str]:
    candidates = texture_lookup_candidates(texture_name)
    for cand in candidates:
        hits = embedded_index.all_hits(cand)
        if hits:
            hit = hits[0]
            return cand, "True", hit.source, len(hits), f"embedded:{hit.asset_id}"
    return (candidates[0] if candidates else "", "False", "", 0, "")


def face_uv_bounds(face: Any) -> Tuple[str, str, str, str]:
    refs = list(getattr(face, "refs", []) or [])
    if not refs:
        return "", "", "", ""
    us = [float(getattr(r, "u", 0.0)) for r in refs]
    vs = [float(getattr(r, "v", 0.0)) for r in refs]
    return (f"{min(us):.9g}", f"{max(us):.9g}", f"{min(vs):.9g}", f"{max(vs):.9g}")



@dataclasses.dataclass
class Bounds3:
    min_x: float = math.inf
    min_y: float = math.inf
    min_z: float = math.inf
    max_x: float = -math.inf
    max_y: float = -math.inf
    max_z: float = -math.inf
    count: int = 0

    def add(self, p: Sequence[float]) -> None:
        x, y, z = float(p[0]), float(p[1]), float(p[2])
        self.min_x = min(self.min_x, x)
        self.min_y = min(self.min_y, y)
        self.min_z = min(self.min_z, z)
        self.max_x = max(self.max_x, x)
        self.max_y = max(self.max_y, y)
        self.max_z = max(self.max_z, z)
        self.count += 1

    def add_bounds(self, b: "Bounds3") -> None:
        if b.count <= 0:
            return
        self.add((b.min_x, b.min_y, b.min_z))
        self.add((b.max_x, b.max_y, b.max_z))
        self.count += max(0, b.count - 2)

    def valid(self) -> bool:
        return self.count > 0

    def dims(self) -> Tuple[float, float, float]:
        if not self.valid():
            return 0.0, 0.0, 0.0
        return self.max_x - self.min_x, self.max_y - self.min_y, self.max_z - self.min_z

    def center(self) -> Tuple[float, float, float]:
        if not self.valid():
            return 0.0, 0.0, 0.0
        return (self.min_x + self.max_x) * 0.5, (self.min_y + self.max_y) * 0.5, (self.min_z + self.max_z) * 0.5


def bounds_row(prefix: dict, b: Bounds3) -> dict:
    dx, dy, dz = b.dims()
    cx, cy, cz = b.center()
    return {
        **prefix,
        "vertex_count": b.count,
        "min_x": b.min_x if b.valid() else "",
        "min_y": b.min_y if b.valid() else "",
        "min_z": b.min_z if b.valid() else "",
        "max_x": b.max_x if b.valid() else "",
        "max_y": b.max_y if b.valid() else "",
        "max_z": b.max_z if b.valid() else "",
        "center_x": cx,
        "center_y": cy,
        "center_z": cz,
        "size_x": dx,
        "size_y": dy,
        "size_z": dz,
    }


def adjust_obj_ref_token(tok: str, v_offset: int, vt_offset: int, vn_offset: int) -> str:
    # Supports v, v/vt, v//vn, v/vt/vn.  Negative OBJ-relative indices are left as-is.
    parts = tok.split("/")
    out: List[str] = []
    offsets = [v_offset, vt_offset, vn_offset]
    for i, part in enumerate(parts):
        if part == "":
            out.append(part)
            continue
        try:
            n = int(part)
            if n > 0 and i < len(offsets):
                n += offsets[i]
            out.append(str(n))
        except Exception:
            out.append(part)
    return "/".join(out)


def count_obj_records(path: Path) -> Tuple[int, int, int]:
    v = vt = vn = 0
    try:
        with path.open("r", encoding="utf-8", errors="replace") as f:
            for line in f:
                if line.startswith("v "):
                    v += 1
                elif line.startswith("vt "):
                    vt += 1
                elif line.startswith("vn "):
                    vn += 1
    except Exception:
        pass
    return v, vt, vn


def write_combined_scene_obj(path: Path, components: List[Tuple[str, Path]]) -> dict:
    """Combine already-emitted OBJ components into one per-mission scene OBJ.

    The writer adjusts positive f/l vertex/texture/normal references as it appends components.
    It intentionally does not deduplicate geometry; it is a validation/inspection assembly layer.
    """
    path.parent.mkdir(parents=True, exist_ok=True)
    v_offset = vt_offset = vn_offset = 0
    used_components = 0
    total_v = total_vt = total_vn = 0
    face_lines = 0
    line_lines = 0
    missing: List[str] = []
    with path.open("w", encoding="utf-8") as out:
        out.write("# Interstate '76 combined mission scene OBJ v15\n")
        out.write("# Concatenates selected terrain/static/RSEG/axis/resource-marker OBJ outputs with adjusted indices.\n\n")
        for label, comp in components:
            if not comp or not comp.exists():
                missing.append(str(comp))
                continue
            used_components += 1
            out.write(f"\n# --- component: {label} path={comp} ---\n")
            local_v, local_vt, local_vn = count_obj_records(comp)
            with comp.open("r", encoding="utf-8", errors="replace") as src:
                for line in src:
                    stripped = line.rstrip("\n")
                    if stripped.startswith("f ") or stripped.startswith("l "):
                        head, *refs = stripped.split()
                        adj = [adjust_obj_ref_token(tok, v_offset, vt_offset, vn_offset) for tok in refs]
                        out.write(head + " " + " ".join(adj) + "\n")
                        if head == "f":
                            face_lines += 1
                        elif head == "l":
                            line_lines += 1
                    elif stripped.startswith("mtllib "):
                        # Preserve component materials in the validation composite by rewriting
                        # mtllib paths relative to scene_obj/.  This is still a simple OBJ
                        # concatenation layer, not a final renderer asset pack.
                        parts = stripped.split(maxsplit=1)
                        if len(parts) == 2:
                            mats = []
                            for m in parts[1].split():
                                rel = os.path.relpath(comp.parent / m, path.parent).replace(os.sep, "/")
                                mats.append(rel)
                            out.write("mtllib " + " ".join(mats) + "\n")
                        else:
                            out.write(line)
                    elif stripped.startswith("usemtl "):
                        out.write(line)
                    else:
                        out.write(line)
            v_offset += local_v
            vt_offset += local_vt
            vn_offset += local_vn
            total_v += local_v
            total_vt += local_vt
            total_vn += local_vn
    return {
        "path": str(path),
        "components_requested": len(components),
        "components_written": used_components,
        "missing_components": missing,
        "vertices": total_v,
        "texcoords": total_vt,
        "normals": total_vn,
        "faces": face_lines,
        "lines": line_lines,
    }


def write_static_objects_obj(
    path: Path,
    rows: List[dict],
    embedded_index: EmbeddedAssetIndex,
    geo_module: Any,
    obj_coordinates: str,
    origin_world_x: float,
    origin_world_z: float,
    max_parts: int = 0,
) -> Tuple[dict, List[dict], List[dict], List[dict], List[dict], List[dict], List[dict]]:
    """Write a first-pass static SDF-part OBJ for one mission.

    v16 also emits validation-ready transform/bounds rows plus per-GEO-face material diagnostics.
    Bounds are in mission-world coordinates, while transform rows include both mission-world and OBJ-local positions.
    """
    path.parent.mkdir(parents=True, exist_ok=True)
    errors: List[dict] = []
    transform_rows: List[dict] = []
    part_bounds_rows: List[dict] = []
    object_bounds: Dict[Tuple[str, str, str], Bounds3] = {}
    mission_bounds = Bounds3()
    material_rows: List[dict] = []
    material_defs: Dict[str, Tuple[int, int, int]] = {}
    if geo_module is None or not hasattr(geo_module, "parse_geo"):
        return {"path": str(path), "written": False, "reason": "geo_exporter_unavailable"}, [], [], [], [], [], []

    rows = [r for r in rows if str(r.get("part_kind", "declared_part")) == "declared_part" and str(r.get("geo_found", "")).lower() in {"true", "1", "yes"}]
    if max_parts and max_parts > 0:
        rows = rows[:max_parts]

    mesh_cache: Dict[str, Any] = {}
    v_base = 1
    part_count = 0
    face_count = 0
    vertex_count = 0
    groups = static_row_groups(rows)

    with path.open("w", encoding="utf-8") as obj:
        obj.write("# Interstate '76 static SDF/SGEO object assembly v19\n")
        obj.write("# Geometry plus placeholder material identity: ODEF/LDEF object transform * SGEO hierarchy * GEO vertices/faces\n")
        obj.write("# Texture binding is diagnostic only; see tables/static_material_slots.tsv and static_material_texture_summary.tsv.\n")
        obj.write(f"mtllib {path.with_suffix('.mtl').name}\n\n")
        for _group_key, group_rows in sorted(groups.items(), key=lambda kv: kv[0]):
            transforms, hwarns = resolve_static_part_hierarchy(group_rows)
            errors.extend(hwarns)
            for row in sorted(group_rows, key=lambda r: int(r.get("part_index") or 0)):
                t = transforms.get(id(row))
                if t is None:
                    continue
                geo_name = str(row.get("geo_name", ""))
                cache_key = geo_name.lower()
                try:
                    if cache_key in mesh_cache:
                        mesh = mesh_cache[cache_key]
                    else:
                        payload, payload_source = geo_payload_for_static_row(row, embedded_index)
                        if payload is None:
                            errors.append({
                                "mission": row.get("mission", ""),
                                "object_label": row.get("object_label", ""),
                                "object_index": row.get("object_index", ""),
                                "part": row.get("token", ""),
                                "geo_name": geo_name,
                                "warning": payload_source,
                            })
                            continue
                        mesh = geo_module.parse_geo(payload)
                        mesh_cache[cache_key] = mesh
                    obj.write(f"o {safe_name(str(row.get('mission','')))}_{safe_name(str(row.get('object_label','')))}_{row.get('object_index','')}_{safe_name(str(row.get('token','')))}_{safe_name(geo_name)}\n")
                    obj.write(f"# sdf {row.get('sdf_path','')}\n")
                    obj.write(f"# parent {row.get('parent_name','')} geo_source {row.get('geo_source','')} geo_path {row.get('geo_path','')}\n")
                    transformed_vertices: List[Tuple[float, float, float]] = []
                    for p in getattr(mesh, "vertices", []):
                        wx, wy, wz = transform_point3(t, p)
                        transformed_vertices.append((wx, wy, wz))
                        ox, oz = mission_world_to_obj_xz(wx, wz, origin_world_x, origin_world_z)
                        vx, vy, vz = obj_vertex_coords(ox, oz, wy, obj_coordinates)
                        obj.write(f"v {vx:.8g} {vy:.8g} {vz:.8g}\n")
                    local_faces = 0
                    last_mtl = ""
                    for face in getattr(mesh, "faces", []):
                        refs = getattr(face, "refs", [])
                        if len(refs) < 3:
                            continue
                        texture_name = clean_geo_texture_name(str(getattr(face, "texture_name", "") or ""))
                        color = tuple(getattr(face, "color", (192, 192, 192)) or (192, 192, 192))
                        if len(color) < 3:
                            color = (192, 192, 192)
                        color3 = (int(color[0]) & 0xff, int(color[1]) & 0xff, int(color[2]) & 0xff)
                        mkey = material_key_for_face(texture_name, color3)
                        material_defs.setdefault(mkey, color3)
                        if mkey != last_mtl:
                            obj.write(f"usemtl {mkey}\n")
                            last_mtl = mkey
                        vi = []
                        for ref in refs:
                            idx = int(getattr(ref, "vertex_index", 0))
                            vi.append(str(v_base + idx))
                        obj.write("f " + " ".join(vi) + "\n")
                        local_faces += 1
                        cand, found, src, hit_count, hit_path = resolve_texture_name_in_embedded_index(texture_name, embedded_index)
                        umin, umax, vmin, vmax = face_uv_bounds(face)
                        material_rows.append({
                            "mission": row.get("mission", ""), "object_label": row.get("object_label", ""),
                            "object_index": row.get("object_index", ""), "part_index": row.get("part_index", ""),
                            "token": row.get("token", ""), "parent_name": row.get("parent_name", ""),
                            "geo_name": geo_name, "face_index": getattr(face, "index", local_faces - 1),
                            "texture_name": texture_name, "material_key": mkey, "texture_probe_name": cand,
                            "texture_found": found, "texture_source": src, "texture_hit_count": hit_count, "texture_path": hit_path,
                            "color_r": color3[0], "color_g": color3[1], "color_b": color3[2],
                            "surface_flags": ",".join(str(x) for x in (getattr(face, "surface_flags", ()) or ())),
                            "vertex_count": len(refs), "u_min": umin, "u_max": umax, "v_min": vmin, "v_max": vmax,
                        })

                    pb = Bounds3()
                    for tv in transformed_vertices:
                        pb.add(tv)
                    obj_key = (str(row.get("mission", "")), str(row.get("object_label", "")), str(row.get("object_index", "")))
                    object_bounds.setdefault(obj_key, Bounds3()).add_bounds(pb)
                    mission_bounds.add_bounds(pb)
                    ox, oz = mission_world_to_obj_xz(t.position[0], t.position[2], origin_world_x, origin_world_z)
                    transform_rows.append({
                        "mission": row.get("mission", ""),
                        "object_label": row.get("object_label", ""),
                        "object_index": row.get("object_index", ""),
                        "part_index": row.get("part_index", ""),
                        "token": row.get("token", ""),
                        "parent_name": row.get("parent_name", ""),
                        "geo_name": geo_name,
                        "world_pos_x": t.position[0],
                        "world_pos_y": t.position[1],
                        "world_pos_z": t.position[2],
                        "obj_local_pos_x": ox,
                        "obj_local_pos_y": t.position[1],
                        "obj_local_pos_z": oz,
                        "world_right": ",".join(f"{v:.9g}" for v in t.right),
                        "world_up": ",".join(f"{v:.9g}" for v in t.up),
                        "world_forward": ",".join(f"{v:.9g}" for v in t.forward),
                        "geo_vertices": len(getattr(mesh, "vertices", [])),
                        "geo_faces": local_faces,
                    })
                    part_bounds_rows.append(bounds_row({
                        "mission": row.get("mission", ""),
                        "object_label": row.get("object_label", ""),
                        "object_index": row.get("object_index", ""),
                        "part_index": row.get("part_index", ""),
                        "token": row.get("token", ""),
                        "parent_name": row.get("parent_name", ""),
                        "geo_name": geo_name,
                    }, pb))
                    v_base += len(getattr(mesh, "vertices", []))
                    part_count += 1
                    face_count += local_faces
                    vertex_count += len(getattr(mesh, "vertices", []))
                except Exception as e:
                    errors.append({
                        "mission": row.get("mission", ""),
                        "object_label": row.get("object_label", ""),
                        "object_index": row.get("object_index", ""),
                        "part": row.get("token", ""),
                        "geo_name": geo_name,
                        "warning": f"geo_parse_or_write_error:{type(e).__name__}:{e}",
                    })
    object_bounds_rows: List[dict] = []
    for (mission, label, obj_index), b in sorted(object_bounds.items()):
        object_bounds_rows.append(bounds_row({"mission": mission, "object_label": label, "object_index": obj_index}, b))
    mission_bounds_rows: List[dict] = []
    if mission_bounds.valid():
        mission_name = str(rows[0].get("mission", "")) if rows else ""
        mission_bounds_rows.append(bounds_row({"mission": mission_name}, mission_bounds))
    mtl_path = path.with_suffix(".mtl")
    if material_defs:
        with mtl_path.open("w", encoding="utf-8") as mtl:
            mtl.write("# Interstate '76 static material identity placeholders v19\n")
            mtl.write("# Texture binding is diagnostic; see tables/static_material_slots.tsv and static_material_texture_summary.tsv.\n\n")
            for name, rgb in sorted(material_defs.items()):
                r, g, b = [max(0.0, min(1.0, float(c) / 255.0)) for c in rgb]
                mtl.write(f"newmtl {name}\nKd {r:.6f} {g:.6f} {b:.6f}\nKa 0 0 0\nKs 0 0 0\n\n")
    return {
        "path": str(path),
        "written": True,
        "parts_considered": len(rows),
        "parts_written": part_count,
        "unique_geo_meshes": len(mesh_cache),
        "vertices": vertex_count,
        "faces": face_count,
        "errors": len(errors),
        "part_bounds_rows": len(part_bounds_rows),
        "object_bounds_rows": len(object_bounds_rows),
        "mission_bounds_rows": len(mission_bounds_rows),
        "material_rows": len(material_rows),
        "mtl_path": str(path.with_suffix(".mtl")) if material_defs else "",
    }, errors, transform_rows, part_bounds_rows, object_bounds_rows, mission_bounds_rows, material_rows




def embedded_asset_object_by_id(embedded_index: EmbeddedAssetIndex, asset_id: str) -> Any:
    idx = embedded_index.resolver_index
    if idx is None:
        return None
    for a in getattr(idx, 'assets', []) or []:
        if str(getattr(a, 'asset_id', '')) == str(asset_id):
            return a
    return None


def resolve_texture_asset_object(texture_name: str, embedded_index: EmbeddedAssetIndex) -> Tuple[Any, str, str]:
    """Resolve a GEO face texture reference to an embedded Asset object usable by the historical exporter.

    Prefer image payloads (M16/VQM) over MAP placeholders.  MAP names in static GEO often resolve
    directly to sibling M16 assets in the retail PIX/PAK index.
    """
    idx = embedded_index.resolver_index
    if idx is None:
        return None, '', 'no_resolver_index'
    candidates = texture_lookup_candidates(texture_name)
    # Prefer directly decodable texture payloads first.
    ordered: List[str] = []
    for ext in ('.m16', '.vqm'):
        for c in candidates:
            if c.lower().endswith(ext) and c not in ordered:
                ordered.append(c)
    for c in candidates:
        if c not in ordered:
            ordered.append(c)
    for cand in ordered:
        hits = embedded_index.all_hits(cand)
        for h in hits:
            asset = embedded_asset_object_by_id(embedded_index, h.asset_id)
            if asset is None:
                continue
            ext = str(getattr(asset, 'ext', '')).lower()
            if ext == 'tmt' and hasattr(sys.modules.get('i76_geo_exporter_v20'), 'first_texture_from_tmt'):
                # This branch is normally handled below by geo_module, but leave it safe.
                pass
            if ext in {'m16', 'vqm', 'tmt', 'map'}:
                return asset, cand, 'resolved_by_candidate'
    return None, (ordered[0] if ordered else ''), 'not_found'


def extract_static_textures(out_dir: Path, rows: List[dict], embedded_index: EmbeddedAssetIndex, geo_module: Any, palette_file: Optional[Path], palette_scale: str, vqm_layout: str) -> Tuple[List[dict], Dict[Tuple[str, str], str], List[str]]:
    """Extract unique static texture usages to static_obj/textures and return material map_Kd bindings."""
    warnings: List[str] = []
    bindings: Dict[Tuple[str, str], str] = {}
    export_rows: List[dict] = []
    if geo_module is None:
        return export_rows, bindings, ['geo_exporter_unavailable_for_texture_export']
    if embedded_index.resolver_index is None or embedded_index.resolver_module is None:
        return export_rows, bindings, ['embedded_resolver_unavailable_for_texture_export']
    if not hasattr(geo_module, 'export_texture_for_asset'):
        return export_rows, bindings, ['geo_exporter_lacks_export_texture_for_asset']
    tex_dir = out_dir / 'static_obj' / 'textures'
    tex_dir.mkdir(parents=True, exist_ok=True)
    palette_rgb = None
    if palette_file is not None:
        try:
            palette_rgb = geo_module.load_palette_file(palette_file, palette_scale) if hasattr(geo_module, 'load_palette_file') else None
        except Exception as e:
            warnings.append(f'palette_load_failed:{palette_file}:{e}')
            palette_rgb = None
    written: Dict[str, str] = {}
    seen = set()
    for r in rows:
        tex = str(r.get('texture_name', '') or '')
        if not tex:
            continue
        mission = str(r.get('mission', '') or '')
        mkey = str(r.get('material_key', '') or '')
        key = (mission, mkey, tex)
        if key in seen:
            continue
        seen.add(key)
        asset, probe, evidence = resolve_texture_asset_object(tex, embedded_index)
        # If a MAP asset was selected, prefer same-stem M16/VQM because MAP appears to be an indirection/name carrier.
        if asset is not None and str(getattr(asset, 'ext', '')).lower() == 'map':
            stem = str(getattr(asset, 'stem', '') or '').upper()
            idx = embedded_index.resolver_index
            for ext in ('m16', 'vqm'):
                alt = idx.resolve(stem, ext, source=asset) if idx is not None else None
                if alt is not None:
                    asset = alt
                    evidence += f';map_to_{ext}'
                    break
        if asset is not None and str(getattr(asset, 'ext', '')).lower() == 'tmt' and hasattr(geo_module, 'first_texture_from_tmt'):
            alt = geo_module.first_texture_from_tmt(embedded_index.resolver_module, embedded_index.resolver_index, asset)
            if alt is not None:
                asset = alt
                evidence += ';tmt_first_frame'
        out_rel = ''
        status = 'not_exported'
        err = ''
        if asset is not None:
            try:
                out_rel = geo_module.export_texture_for_asset(embedded_index.resolver_module, embedded_index.resolver_index, asset, tex_dir, written, palette_rgb, vqm_layout)
                # geo exporter returns textures/foo.png; relative to static_obj/*.mtl this is correct.
                bindings[(mission, mkey)] = out_rel
                status = 'exported'
            except Exception as e:
                err = f'{type(e).__name__}:{e}'
                warnings.append(f'texture_export_failed:{tex}:{err}')
        export_rows.append({
            'mission': mission,
            'material_key': mkey,
            'texture_name': tex,
            'texture_probe_name': probe,
            'asset_name': str(getattr(asset, 'name', '') or '') if asset is not None else '',
            'asset_id': str(getattr(asset, 'asset_id', '') or '') if asset is not None else '',
            'asset_ext': str(getattr(asset, 'ext', '') or '') if asset is not None else '',
            'status': status,
            'output_relpath': out_rel,
            'evidence': evidence,
            'error': err,
        })
    return export_rows, bindings, warnings


def rewrite_static_mtls_with_textures(out_dir: Path, bindings: Dict[Tuple[str, str], str]) -> int:
    """Inject map_Kd lines into existing static OBJ MTL files."""
    by_mission: Dict[str, Dict[str, str]] = {}
    for (mission, mat), rel in bindings.items():
        if not mission or not mat or not rel:
            continue
        by_mission.setdefault(mission.lower(), {})[mat] = rel
    changed = 0
    for mission, mats in by_mission.items():
        mtl_path = out_dir / 'static_obj' / f'{mission}.static_objects.mtl'
        if not mtl_path.exists():
            continue
        lines = mtl_path.read_text(encoding='utf-8').splitlines()
        out: List[str] = []
        current = ''
        for line in lines:
            if line.startswith('newmtl '):
                current = line.split(None, 1)[1].strip()
            out.append(line)
            if line.startswith('Kd ') and current in mats:
                # Avoid duplicate map_Kd if rerun on an already-patched MTL.
                out.append(f'map_Kd {mats[current]}')
        mtl_path.write_text('\n'.join(out) + '\n', encoding='utf-8')
        changed += 1
    return changed

def build_static_material_texture_summary(rows: List[dict]) -> Tuple[List[dict], List[dict]]:
    """Group per-face static material rows into reconstruction-oriented texture usage summaries.

    The per-face table is intentionally verbose.  These grouped tables are meant to answer:
      * which texture assets are used by a mission/object/part corpus?
      * which references are actual texture-backed faces vs intentional solid-color faces?
      * which embedded/top-level assets should a future texture extraction pass decode first?
    """
    grouped: Dict[Tuple[str, str, str, str, str], dict] = {}
    missing_or_solid: Dict[Tuple[str, str, str, str, str], dict] = {}
    for r in rows:
        mission = str(r.get("mission", ""))
        texture_name = str(r.get("texture_name", "") or "")
        probe = str(r.get("texture_probe_name", "") or "")
        source = str(r.get("texture_source", "") or "")
        found = str(r.get("texture_found", "")).lower() in {"true", "1", "yes"}
        tex_path = str(r.get("texture_path", "") or "")
        key = (mission, texture_name, probe, source, tex_path)
        target = grouped if texture_name else missing_or_solid
        d = target.setdefault(key, {
            "mission": mission,
            "texture_name": texture_name,
            "texture_probe_name": probe,
            "texture_found": found,
            "texture_source": source,
            "texture_path": tex_path,
            "face_count": 0,
            "object_count": 0,
            "part_count": 0,
            "geo_count": 0,
            "objects": set(),
            "parts": set(),
            "geos": set(),
            "material_keys": set(),
            "color_keys": set(),
            "u_min": None, "u_max": None, "v_min": None, "v_max": None,
        })
        d["face_count"] += 1
        d["objects"].add(str(r.get("object_label", "")))
        d["parts"].add(str(r.get("token", "")))
        d["geos"].add(str(r.get("geo_name", "")))
        d["material_keys"].add(str(r.get("material_key", "")))
        d["color_keys"].add("%02x%02x%02x" % (int(float(r.get("color_r", 0) or 0)) & 255, int(float(r.get("color_g", 0) or 0)) & 255, int(float(r.get("color_b", 0) or 0)) & 255))
        for src_key, agg_key, fn in (("u_min", "u_min", min), ("u_max", "u_max", max), ("v_min", "v_min", min), ("v_max", "v_max", max)):
            try:
                val = float(r.get(src_key, ""))
            except Exception:
                continue
            if d[agg_key] is None:
                d[agg_key] = val
            else:
                d[agg_key] = fn(d[agg_key], val)
    def finish(items: Dict[Tuple[str, str, str, str, str], dict]) -> List[dict]:
        out: List[dict] = []
        for d in items.values():
            d["object_count"] = len([x for x in d.pop("objects") if x])
            d["part_count"] = len([x for x in d.pop("parts") if x])
            d["geo_count"] = len([x for x in d.pop("geos") if x])
            d["material_keys"] = ";".join(sorted(x for x in d["material_keys"] if x))
            d["color_keys"] = ";".join(sorted(x for x in d["color_keys"] if x))
            for k in ("u_min", "u_max", "v_min", "v_max"):
                if d[k] is None:
                    d[k] = ""
            # A deterministic future texture-export destination.  The file may not exist yet; this is an extraction plan.
            tex_name = d.get("texture_probe_name") or d.get("texture_name") or ""
            if tex_name:
                stem = safe_name(Path(tex_name).stem.lower())
                d["planned_png"] = f"textures/{stem}.png"
            else:
                d["planned_png"] = ""
            out.append(d)
        return sorted(out, key=lambda x: (str(x.get("mission", "")), str(x.get("texture_name", "")), str(x.get("texture_probe_name", "")), str(x.get("texture_path", ""))))
    return finish(grouped), finish(missing_or_solid)


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


def build_file_index(roots: Sequence[Path]) -> Dict[str, List[Path]]:
    idx: Dict[str, List[Path]] = {}
    for root in roots:
        if not root.exists():
            continue
        for p in find_files(root):
            idx.setdefault(p.name.lower(), []).append(p)
    for k in list(idx.keys()):
        idx[k].sort(key=lambda p: (len(str(p)), str(p).lower()))
    return idx


def find_sidecar(msn: Path, sidecar_name: str, by_name: Dict[str, List[Path]]) -> Optional[Path]:
    candidates: List[Optional[Path]] = []
    if sidecar_name:
        candidates.extend([
            msn.parent / sidecar_name,
            msn.parent / sidecar_name.upper(),
            msn.parent / sidecar_name.lower(),
            (by_name.get(sidecar_name.lower()) or [None])[0],
        ])
    candidates.extend([
        msn.with_suffix(".TER"),
        msn.with_suffix(".ter"),
        (by_name.get(msn.stem.lower() + ".ter") or [None])[0],
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


def mission_world_to_obj_xz(x: float, z: float, origin_world_x: float, origin_world_z: float) -> Tuple[float, float]:
    return x - origin_world_x, z - origin_world_z


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


def write_obj(path: Path, vertices: List[Tuple[float, float, float]], faces: List[Tuple[int, ...]], obj_coordinates: str, write_normals: bool, header: str = "") -> dict:
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
        for face in faces:
            if normals:
                f.write("f " + " ".join(f"{i}//{i}" for i in face) + "\n")
            else:
                f.write("f " + " ".join(str(i) for i in face) + "\n")
    return {"path": str(path), "vertices": len(vertices), "faces": len(faces), "write_normals": bool(normals)}




def terrain_surface_material_name(surface_class: int) -> str:
    return f"terrain_surface_{int(surface_class) & 0x7}"




def terrain_surface_runtime_forced_split(surface_class: int) -> bool:
    # Runtime adaptive-terrain evidence from 004911e0: special split when
    # (word >= 0x4000) && ((word & 0xe000) != 0xa000).  Since the
    # surface code is word >> 13, this is true for classes 2, 3, 4, 6, 7
    # and false for 0, 1, 5.
    sc = int(surface_class) & 0x7
    return sc >= 2 and sc != 5


def terrain_surface_diagnostic_role(surface_class: int) -> str:
    # Conservative labels only.  These are diagnostic code buckets derived
    # from the TER high bits, not final texture/material names.
    sc = int(surface_class) & 0x7
    if sc == 0:
        return "terrain_code_0_default_or_low_priority"
    if sc == 1:
        return "terrain_code_1_dominant_base_ground"
    if sc == 5:
        return "terrain_code_5_distinct_non_forced_split_ground"
    if terrain_surface_runtime_forced_split(sc):
        return f"terrain_code_{sc}_runtime_forced_split_special_surface"
    return f"terrain_code_{sc}_unknown"


def terrain_surface_notes(surface_class: int) -> str:
    sc = int(surface_class) & 0x7
    if terrain_surface_runtime_forced_split(sc):
        return "TER word>>13 diagnostic class; runtime adaptive terrain treats this as a special-surface forced split class"
    if sc == 5:
        return "TER word>>13 diagnostic class; high bits are 0xa000, explicitly excluded from the known forced-split predicate"
    return "TER word>>13 diagnostic class; not final DIVER/PAL texture binding"

def terrain_surface_rgb(surface_class: int) -> Tuple[float, float, float]:
    # Diagnostic material colors only.  The runtime encodes the terrain surface
    # class as TER word >> 13; this is not yet a literal ground texture binding.
    palette = {
        0: (0.48, 0.42, 0.30),
        1: (0.36, 0.31, 0.22),
        2: (0.62, 0.55, 0.38),
        3: (0.30, 0.30, 0.30),
        4: (0.55, 0.47, 0.33),
        5: (0.22, 0.28, 0.18),
        6: (0.18, 0.22, 0.26),
        7: (0.70, 0.66, 0.50),
    }
    return palette.get(int(surface_class) & 0x7, (0.5, 0.5, 0.5))


def build_dense_terrain_mesh_with_surface_materials(rt: RuntimeTerrain, boundary_sampling: str) -> Tuple[List[Tuple[float, float, float]], List[Tuple[int, int, int, int]], List[int]]:
    vertices: List[Tuple[float, float, float]] = []
    faces: List[Tuple[int, int, int, int]] = []
    face_surfaces: List[int] = []
    index_by_sample: Dict[Tuple[int, int], int] = {}
    used = set((x, z) for x, z, _ in rt.zmap.used_cells())

    def sample_for_vertex(cell_x: int, cell_z: int, local_x: int, local_z: int) -> Tuple[int, int]:
        sx = cell_x * PAGE_W + local_x
        sz = cell_z * PAGE_H + local_z
        if boundary_sampling == "runtime-strict":
            return sx, sz
        if boundary_sampling == "clamp-outer-active-edge":
            if local_x == PAGE_W and (cell_x + 1, cell_z) not in used:
                sx -= 1
            if local_z == PAGE_H and (cell_x, cell_z + 1) not in used:
                sz -= 1
            return sx, sz
        raise ValueError(f"unknown boundary sampling: {boundary_sampling}")

    def get_vertex(cell_x: int, cell_z: int, local_x: int, local_z: int) -> int:
        sx, sz = sample_for_vertex(cell_x, cell_z, local_x, local_z)
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

    for cell_x, cell_z, _page in rt.zmap.used_cells():
        for lz in range(PAGE_H):
            for lx in range(PAGE_W):
                v0 = get_vertex(cell_x, cell_z, lx, lz)
                v1 = get_vertex(cell_x, cell_z, lx + 1, lz)
                v2 = get_vertex(cell_x, cell_z, lx + 1, lz + 1)
                v3 = get_vertex(cell_x, cell_z, lx, lz + 1)
                faces.append((v0, v1, v2, v3))
                # Sample center/near-center of this quad for the material class.
                face_surfaces.append(rt.surface_class(cell_x * PAGE_W + lx, cell_z * PAGE_H + lz))
    return vertices, faces, face_surfaces


def write_terrain_obj_with_surface_materials(path: Path, vertices: List[Tuple[float, float, float]], faces: List[Tuple[int, ...]], face_surfaces: List[int], obj_coordinates: str, write_normals: bool, header: str = "") -> Tuple[dict, List[dict]]:
    path.parent.mkdir(parents=True, exist_ok=True)
    normals = compute_normals(vertices, faces) if write_normals and faces else []
    mtl_path = path.with_suffix('.mtl')
    counts: Dict[int, int] = {}
    for sc in face_surfaces:
        counts[int(sc) & 0x7] = counts.get(int(sc) & 0x7, 0) + 1
    with mtl_path.open('w', encoding='utf-8') as mtl:
        mtl.write('# Interstate 76 terrain surface-class diagnostic materials v19\n')
        mtl.write('# These are TER word>>13 surface classes, not final DIVER/PAL texture bindings yet.\n\n')
        for sc in sorted(counts):
            r, g, b = terrain_surface_rgb(sc)
            mtl.write(f"newmtl {terrain_surface_material_name(sc)}\nKd {r:.6f} {g:.6f} {b:.6f}\nKa 0 0 0\nKs 0 0 0\n\n")
    with path.open('w', encoding='utf-8') as f:
        f.write(header)
        f.write(f"mtllib {mtl_path.name}\n")
        for x, z, h in vertices:
            vx, vy, vz = obj_vertex_coords(x, z, h, obj_coordinates)
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")
        if normals:
            for nx, nz, nh in normals:
                vx, vy, vz = obj_vertex_coords(nx, nz, nh, obj_coordinates)
                f.write(f"vn {vx:.8f} {vy:.8f} {vz:.8f}\n")
        last = None
        for i, face in enumerate(faces):
            sc = int(face_surfaces[i]) & 0x7 if i < len(face_surfaces) else 0
            mtl = terrain_surface_material_name(sc)
            if mtl != last:
                f.write(f"usemtl {mtl}\n")
                last = mtl
            if normals:
                f.write("f " + " ".join(f"{idx}//{idx}" for idx in face) + "\n")
            else:
                f.write("f " + " ".join(str(idx) for idx in face) + "\n")
    rows = []
    for sc, count in sorted(counts.items()):
        rows.append({
            'mission': path.name.split('.')[0],
            'surface_class': sc,
            'material_key': terrain_surface_material_name(sc),
            'face_count': count,
            'mtl_path': str(mtl_path),
            'high_bits_hex': f"0x{(sc & 0x7) << 13:04x}",
            'binary_code': format(sc & 0x7, '03b'),
            'runtime_forced_split': terrain_surface_runtime_forced_split(sc),
            'diagnostic_role': terrain_surface_diagnostic_role(sc),
            'note': terrain_surface_notes(sc),
        })
    return {"path": str(path), "vertices": len(vertices), "faces": len(faces), "write_normals": bool(normals), "mtl_path": str(mtl_path), "surface_materials": len(counts)}, rows

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
        if boundary_sampling == "clamp-outer-active-edge":
            if local_x == PAGE_W and (cell_x + 1, cell_z) not in used:
                sx -= 1
            if local_z == PAGE_H and (cell_x, cell_z + 1) not in used:
                sz -= 1
            return sx, sz
        raise ValueError(f"unknown boundary sampling: {boundary_sampling}")

    def get_vertex(cell_x: int, cell_z: int, local_x: int, local_z: int) -> int:
        sx, sz = sample_for_vertex(cell_x, cell_z, local_x, local_z)
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

    for cell_x, cell_z, _page in rt.zmap.used_cells():
        for lz in range(PAGE_H):
            for lx in range(PAGE_W):
                v0 = get_vertex(cell_x, cell_z, lx, lz)
                v1 = get_vertex(cell_x, cell_z, lx + 1, lz)
                v2 = get_vertex(cell_x, cell_z, lx + 1, lz + 1)
                v3 = get_vertex(cell_x, cell_z, lx, lz + 1)
                faces.append((v0, v1, v2, v3))
    return vertices, faces


def should_split_adaptive(rt: RuntimeTerrain, x0: int, z0: int, size: int, max_depth: int, depth: int, split_error: float, force_surface_splits: bool) -> Tuple[bool, str]:
    half = size >> 1
    if depth >= max_depth or half <= 0:
        return False, "max_depth_or_zero_half"
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


def build_adaptive_overlay_mesh(rt: RuntimeTerrain, max_depth: int, split_error: float, force_surface_splits: bool) -> Tuple[List[Tuple[float, float, float]], List[Tuple[int, int, int, int]], dict]:
    vertices: List[Tuple[float, float, float]] = []
    faces: List[Tuple[int, int, int, int]] = []
    index_by_sample: Dict[Tuple[int, int], int] = {}
    stats = {"quad_tests": 0, "quad_splits": 0, "leaf_count": 0, "split_reasons": {}, "leaf_depth_histogram": {}}

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
    raw = bytes((b & 0x7F) for b in payload[:max_len])
    return raw.split(b"\0", 1)[0].decode("ascii", errors="ignore").strip()


def parse_obj_records(mission: MissionData, parent_tag: str) -> List[dict]:
    out: List[dict] = []
    for index, c in enumerate(chunks_by_tag(mission.chunks, "OBJ\x00", parent_tag)):
        payload = mission.data[c.payload_offset:c.end]
        if len(payload) < 0x64:
            continue
        try:
            basis = [f32(payload, 0x08 + i * 4) for i in range(9)]
            pos = [f32(payload, 0x2C), f32(payload, 0x30), f32(payload, 0x34)]
            tail = [u32(payload, 0x38 + i * 4) for i in range((0x64 - 0x38) // 4)]
            class_raw = u32(payload, 0x5C)
        except struct.error:
            continue
        name = read_c_string_from_payload(payload, 8)
        valid = 1 <= class_raw <= 0x53
        out.append({
            "index": index,
            "parent_tag": parent_tag,
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


def classify_obj_resource(parent_tag: str, name: str, class_raw: int, dispatch_valid: bool) -> dict:
    lname = name.lower()
    if parent_tag == "LDEF":
        if not name:
            return {"policy": "ldef_blank", "expected_ext": "", "expected_name": "", "kind": "diagnostic"}
        return {"policy": "ldef_obj_to_sdf", "expected_ext": ".sdf", "expected_name": f"{lname}.sdf", "kind": "sdf"}

    if parent_tag != "ODEF":
        return {"policy": "unknown_parent", "expected_ext": "", "expected_name": "", "kind": "diagnostic"}
    if not dispatch_valid:
        return {"policy": "invalid_or_special", "expected_ext": "", "expected_name": "", "kind": "diagnostic"}
    if class_raw == 0x01 and lname == "spawn":
        return {"policy": "odef_class_01_spawn_marker", "expected_ext": "", "expected_name": "", "kind": "special_spawn"}
    if class_raw == 0x01 and lname == "regen":
        return {"policy": "odef_class_01_regen_marker", "expected_ext": "", "expected_name": "", "kind": "special_regen"}
    if class_raw in VCF_CLASSES:
        return {"policy": f"odef_class_0x{class_raw:02x}_to_vcf", "expected_ext": ".vcf", "expected_name": f"{lname}.vcf", "kind": "vcf"}
    if class_raw in SDF_CLASSES:
        return {"policy": f"odef_class_0x{class_raw:02x}_to_sdf", "expected_ext": ".sdf", "expected_name": f"{lname}.sdf", "kind": "sdf"}
    if class_raw in FALLBACK_CLASSES:
        return {"policy": f"odef_class_0x{class_raw:02x}_fallback_nullish", "expected_ext": "", "expected_name": "", "kind": "fallback"}
    return {"policy": f"odef_class_0x{class_raw:02x}_unknown", "expected_ext": "", "expected_name": "", "kind": "diagnostic"}


def first_index_hit(file_index: Dict[str, List[Path]], name: str) -> Optional[Path]:
    if not name:
        return None
    hits = file_index.get(name.lower()) or []
    return hits[0] if hits else None


def all_index_hits(file_index: Dict[str, List[Path]], name: str) -> List[Path]:
    return list(file_index.get(name.lower()) or [])


def token_to_geo_name(token: str) -> str:
    t = token.strip().strip(".\0")
    if not t:
        return ""
    if t.lower().endswith(".geo"):
        return t.lower()
    return f"{t.lower()}.geo"


def extract_ascii_tokens(data: bytes) -> List[Tuple[int, str]]:
    out: List[Tuple[int, str]] = []
    for m in ASCII_TOKEN_RE.finditer(data):
        try:
            s = m.group(0).decode("ascii", errors="ignore")
        except Exception:
            continue
        if len(s) >= 2:
            out.append((m.start(), s))
    return out


def score_sdf_token(token: str, off: int, data: bytes, file_index: Dict[str, List[Path]]) -> Tuple[int, str, str]:
    reasons: List[str] = []
    score = 0
    lower = token.lower()
    geo_name = token_to_geo_name(lower)
    if lower.endswith(".geo"):
        score += 80
        reasons.append("explicit_geo_suffix")
        geo_name = lower
    if first_index_hit(file_index, geo_name):
        score += 60
        reasons.append("geo_exists")
    # Nearby descriptor tags are useful but only as confidence, not proof.
    start = max(0, off - 48)
    end = min(len(data), off + 64)
    nearby = data[start:end]
    for tag in (b"SOBJ", b"SGEO", b"SCHK", b"LOBJ", b"SDFC"):
        if tag in nearby:
            score += 12
            reasons.append(f"near_{tag.decode('ascii')}")
    if re.fullmatch(r"[A-Za-z][A-Za-z0-9_.$@#\-]{1,11}(\.geo)?", token):
        score += 10
        reasons.append("short_resource_like_token")
    if not reasons:
        reasons.append("low_confidence_token")
    return score, geo_name, ",".join(reasons)


def parse_sdf_sgeo_parts(sdf_path: Path, file_index: Dict[str, List[Path]], embedded_index: Optional[EmbeddedAssetIndex] = None, include_extra_records: bool = True) -> List[dict]:
    """Parse SDF SGEO part records using the Open76 SdfObjectParser layout.

    SGEO payload:
        uint32 numParts
        repeated SdfPart records, 0x78 bytes each:
            char  name[8]
            float right[3]
            float up[3]
            float forward[3]
            float position[3]
            char  parentName[8]
            uint8 reserved_or_runtime[56]

    Some retail SDFs contain additional 0x78-byte records after the declared part
    count.  Older probes treated these as optional wreck/destroyed records.  v9
    reports them separately instead of using them as primary geometry evidence.
    """
    try:
        data = sdf_path.read_bytes()
    except Exception as e:
        return [{
            "sdf_path": str(sdf_path),
            "offset_hex": "",
            "token": "",
            "geo_name": "",
            "geo_found": False,
            "geo_path": "",
            "score": 0,
            "reasons": f"read_error:{e}",
            "parser": "sgeo_open76",
            "part_kind": "error",
            "part_index": "",
            "parent_name": "",
        }]

    chunks = parse_tree(data)
    sgeo = first_chunk(chunks, "SGEO")
    sdfc = first_chunk(chunks, "SDFC")
    object_name = ""
    if sdfc is not None:
        object_name = read_c_string_from_payload(data[sdfc.payload_offset:min(sdfc.end, sdfc.payload_offset + 16)], 16)

    if sgeo is None:
        return []
    payload = data[sgeo.payload_offset:sgeo.end]
    if len(payload) < 4:
        return []

    try:
        declared_count = u32(payload, 0)
    except struct.error:
        return []

    max_full_records = max(0, (len(payload) - 4) // SDF_PART_SIZE)
    if declared_count > max_full_records:
        # Invalid SGEO shape; do not try to invent child records from this file.
        return [{
            "sdf_path": str(sdf_path),
            "offset_hex": f"0x{sgeo.payload_offset:08x}",
            "token": "",
            "geo_name": "",
            "geo_found": False,
            "geo_path": "",
            "score": 0,
            "reasons": f"invalid_sgeo_declared_count:{declared_count}>max:{max_full_records}",
            "parser": "sgeo_open76",
            "part_kind": "error",
            "part_index": "",
            "parent_name": "",
            "sdf_object_name": object_name,
        }]

    rows: List[dict] = []

    def read_part(kind: str, idx: int, rec_off: int) -> Optional[dict]:
        if rec_off + SDF_PART_SIZE > len(payload):
            return None
        name = read_c_string_from_payload(payload[rec_off:rec_off + 8], 8)
        parent_name = read_c_string_from_payload(payload[rec_off + 56:rec_off + 64], 8)
        if not name:
            return None
        try:
            right = struct.unpack_from("<fff", payload, rec_off + 8)
            up = struct.unpack_from("<fff", payload, rec_off + 20)
            forward = struct.unpack_from("<fff", payload, rec_off + 32)
            pos = struct.unpack_from("<fff", payload, rec_off + 44)
        except struct.error:
            return None
        geo_name = token_to_geo_name(name)
        hit = first_index_hit(file_index, geo_name)
        embedded_hit = None if hit else (embedded_index.first_hit(geo_name) if embedded_index is not None else None)
        absolute_off = sgeo.payload_offset + rec_off
        score = 150 if kind == "declared_part" else 95
        reasons = ["sgeo_open76_0x78_part"]
        if hit:
            score += 50
            reasons.append("geo_exists_file")
        elif embedded_hit:
            score += 45
            reasons.append("geo_exists_embedded")
        if kind != "declared_part":
            reasons.append("extra_or_wreck_record")
        return {
            "sdf_path": str(sdf_path),
            "sdf_object_name": object_name,
            "sgeo_chunk_offset_hex": f"0x{sgeo.offset:08x}",
            "declared_part_count": declared_count,
            "offset_hex": f"0x{absolute_off:08x}",
            "token": name,
            "geo_name": geo_name,
            "geo_found": bool(hit or embedded_hit),
            "geo_path": str(hit) if hit else (f"embedded:{embedded_hit.source}:{embedded_hit.asset_id}:{embedded_hit.name}" if embedded_hit else ""),
            "geo_source": "file" if hit else ("embedded" if embedded_hit else "missing"),
            "score": score,
            "reasons": ",".join(reasons),
            "parser": "sgeo_open76",
            "part_kind": kind,
            "part_index": idx,
            "parent_name": parent_name,
            "right_x": right[0], "right_y": right[1], "right_z": right[2],
            "up_x": up[0], "up_y": up[1], "up_z": up[2],
            "forward_x": forward[0], "forward_y": forward[1], "forward_z": forward[2],
            "pos_x": pos[0], "pos_y": pos[1], "pos_z": pos[2],
        }

    for i in range(declared_count):
        row = read_part("declared_part", i, 4 + i * SDF_PART_SIZE)
        if row is not None:
            rows.append(row)

    if include_extra_records:
        for j, rec_index in enumerate(range(declared_count, max_full_records)):
            row = read_part("extra_or_wreck", j, 4 + rec_index * SDF_PART_SIZE)
            if row is not None:
                rows.append(row)

    return rows


def sdf_child_candidates(sdf_path: Path, file_index: Dict[str, List[Path]], embedded_index: Optional[EmbeddedAssetIndex] = None, max_rows: int = 2048, include_extra_sgeo_records: bool = False) -> List[dict]:
    # Strict SGEO parsing is the primary v9+ path.  Declared SGEO parts are the
    # reconstruction-grade rows.  Extra/wreck records are useful diagnostics but
    # are intentionally opt-in because they introduce a large number of null/noisy
    # rows and should not drive normal object instantiation.
    rows = parse_sdf_sgeo_parts(sdf_path, file_index, embedded_index=embedded_index, include_extra_records=include_extra_sgeo_records)
    if rows:
        return rows[:max_rows]

    # Fallback only for malformed/non-SGEO files: retain the old token/resource scan
    # as a diagnostic, clearly marked as heuristic.
    try:
        data = sdf_path.read_bytes()
    except Exception as e:
        return [{"sdf_path": str(sdf_path), "offset_hex": "", "token": "", "geo_name": "", "geo_found": False, "score": 0, "reasons": f"read_error:{e}", "parser": "token_fallback"}]
    fallback_rows: List[dict] = []
    seen = set()
    for off, tok in extract_ascii_tokens(data):
        lower = tok.lower()
        if lower in {"sobj", "sgeo", "schk", "lobj", "sdfc", "bwd2", "exit"}:
            continue
        score, geo_name, reasons = score_sdf_token(tok, off, data, file_index)
        if score < 60 and not lower.endswith(".geo"):
            continue
        key = (lower, geo_name)
        if key in seen:
            continue
        seen.add(key)
        hit = first_index_hit(file_index, geo_name)
        embedded_hit = None if hit else (embedded_index.first_hit(geo_name) if embedded_index is not None else None)
        fallback_rows.append({
            "sdf_path": str(sdf_path),
            "offset_hex": f"0x{off:08x}",
            "token": tok,
            "geo_name": geo_name,
            "geo_found": bool(hit or embedded_hit),
            "geo_path": str(hit) if hit else (f"embedded:{embedded_hit.source}:{embedded_hit.asset_id}:{embedded_hit.name}" if embedded_hit else ""),
            "geo_source": "file" if hit else ("embedded" if embedded_hit else "missing"),
            "score": score,
            "reasons": reasons + ",token_fallback",
            "parser": "token_fallback",
            "part_kind": "heuristic_token",
            "part_index": "",
            "parent_name": "",
        })
    fallback_rows.sort(key=lambda r: (-int(r["score"]), r["geo_name"], r["offset_hex"]))
    return fallback_rows[:max_rows]

def write_odef_axes_obj(path: Path, records: List[dict], obj_coordinates: str, include_invalid: bool, axis_len: float = 25.0, origin_world_x: float = 0.0, origin_world_z: float = 0.0) -> dict:
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
        ox, oz = mission_world_to_obj_xz(px, pz, origin_world_x, origin_world_z)
        origin = (ox, oz, py)
        x2, z2 = mission_world_to_obj_xz(px + b[0] * axis_len, pz + b[1] * axis_len, origin_world_x, origin_world_z)
        y2, z3 = mission_world_to_obj_xz(px + b[3] * axis_len, pz + b[4] * axis_len, origin_world_x, origin_world_z)
        z4, z5 = mission_world_to_obj_xz(px + b[6] * axis_len, pz + b[7] * axis_len, origin_world_x, origin_world_z)
        xaxis = (x2, z2, py + b[2] * axis_len)
        yaxis = (y2, z3, py + b[5] * axis_len)
        zaxis = (z4, z5, py + b[8] * axis_len)
        add_line(origin, xaxis)
        add_line(origin, yaxis)
        add_line(origin, zaxis)

    with path.open("w", encoding="utf-8") as f:
        f.write("# ODEF/LDEF OBJ basis/position axes probe\n")
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


def write_rseg_obj(path: Path, points: List[dict], mode: str, obj_coordinates: str, origin_world_x: float = 0.0, origin_world_z: float = 0.0, rt: Optional[RuntimeTerrain] = None, height_mode: str = "terrain", height_offset: float = 1.0) -> dict:
    path.parent.mkdir(parents=True, exist_ok=True)
    vertices: List[Tuple[float, float, float]] = []
    lines: List[Tuple[int, int]] = []
    by_seg: Dict[int, List[dict]] = {}
    for p in points:
        by_seg.setdefault(p["rseg_index"], []).append(p)

    def road_height(x: float, z: float, serialized_h: float = 0.0) -> float:
        if height_mode == "serialized":
            return serialized_h
        if height_mode == "zero":
            return height_offset
        if height_mode == "terrain":
            if rt is None:
                return height_offset
            sx = int(round(x / SAMPLE_WORLD_SCALE))
            sz = int(round(z / SAMPLE_WORLD_SCALE))
            return rt.height_world(sx, sz) + height_offset
        raise ValueError(f"unknown RSEG height mode: {height_mode}")

    def add_vertex(x, z, serialized_h=0.0) -> int:
        ox, oz = mission_world_to_obj_xz(x, z, origin_world_x, origin_world_z)
        h = road_height(x, z, serialized_h)
        vertices.append((ox, oz, h))
        return len(vertices)

    if mode in {"centerline", "left_edge", "right_edge"}:
        for _seg, rows in sorted(by_seg.items()):
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
    return {"path": str(path), "mode": mode, "vertices": len(vertices), "lines": len(lines), "height_mode": height_mode, "height_offset": height_offset}


def write_marker_obj(path: Path, resolution_rows: List[dict], obj_coordinates: str, origin_world_x: float = 0.0, origin_world_z: float = 0.0, marker_size: float = 10.0) -> dict:
    path.parent.mkdir(parents=True, exist_ok=True)
    vertices: List[Tuple[float, float, float]] = []
    lines: List[Tuple[int, int]] = []
    for r in resolution_rows:
        if not r.get("resolved"):
            continue
        try:
            px = float(r.get("pos_x", 0.0))
            py = float(r.get("pos_y", 0.0))
            pz = float(r.get("pos_z", 0.0))
        except Exception:
            continue
        ox, oz = mission_world_to_obj_xz(px, pz, origin_world_x, origin_world_z)
        vertices.append((ox - marker_size, oz, py)); a = len(vertices)
        vertices.append((ox + marker_size, oz, py)); b = len(vertices)
        lines.append((a, b))
        vertices.append((ox, oz - marker_size, py)); c = len(vertices)
        vertices.append((ox, oz + marker_size, py)); d = len(vertices)
        lines.append((c, d))
        vertices.append((ox, oz, py)); e = len(vertices)
        vertices.append((ox, oz, py + marker_size)); f = len(vertices)
        lines.append((e, f))
    with path.open("w", encoding="utf-8") as f:
        f.write("# resolved SDF/VCF placement markers\n")
        for x, z, h in vertices:
            vx, vy, vz = obj_vertex_coords(x, z, h, obj_coordinates)
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")
        for a, b in lines:
            f.write(f"l {a} {b}\n")
    return {"path": str(path), "markers": len(lines) // 3, "lines": len(lines)}


def write_tsv(path: Path, rows: List[dict], columns: Sequence[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f, delimiter="\t", lineterminator="\n", quoting=csv.QUOTE_MINIMAL)
        writer.writerow(list(columns))
        for r in rows:
            writer.writerow([r.get(c, "") for c in columns])


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


def copy_unique(src: Path, dst_dir: Path) -> Optional[Path]:
    try:
        dst_dir.mkdir(parents=True, exist_ok=True)
        dst = dst_dir / src.name
        if dst.exists() and dst.resolve() != src.resolve():
            dst = dst_dir / f"{src.stem}_{abs(hash(str(src))) & 0xfffffff:07x}{src.suffix}"
        if not dst.exists():
            shutil.copy2(src, dst)
        return dst
    except Exception:
        return None


def inventory_summary(file_index: Dict[str, List[Path]]) -> dict:
    by_ext: Dict[str, int] = {}
    total_paths = 0
    for _name, paths in file_index.items():
        total_paths += len(paths)
        for p in paths:
            ext = p.suffix.lower()
            by_ext[ext] = by_ext.get(ext, 0) + 1
    return {"unique_names": len(file_index), "total_paths": total_paths, "by_ext": dict(sorted(by_ext.items()))}



def parse_basis_csv(value: str) -> List[float]:
    try:
        vals = [float(x) for x in str(value).split(",") if str(x).strip() != ""]
    except Exception:
        return []
    return vals if len(vals) == 9 else []


def mat3_from_basis_tuple(vals: Sequence[float]) -> List[List[float]]:
    # ODEF basis is carried as three 3-float vectors from the confirmed +0x08..+0x28
    # runtime copy.  This helper treats them as row vectors for an approximate
    # parent*object transform; the raw fields are also emitted so this remains
    # auditable if the convention is later corrected.
    if len(vals) != 9:
        return [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
    return [
        [float(vals[0]), float(vals[1]), float(vals[2])],
        [float(vals[3]), float(vals[4]), float(vals[5])],
        [float(vals[6]), float(vals[7]), float(vals[8])],
    ]


def row_mat3_mul_vec3(m: List[List[float]], v: Sequence[float]) -> Tuple[float, float, float]:
    return (
        m[0][0] * float(v[0]) + m[1][0] * float(v[1]) + m[2][0] * float(v[2]),
        m[0][1] * float(v[0]) + m[1][1] * float(v[1]) + m[2][1] * float(v[2]),
        m[0][2] * float(v[0]) + m[1][2] * float(v[1]) + m[2][2] * float(v[2]),
    )


def approx_child_world_position(object_pos: Sequence[float], object_basis: Sequence[float], child_pos: Sequence[float]) -> Tuple[float, float, float]:
    m = mat3_from_basis_tuple(object_basis)
    dx, dy, dz = row_mat3_mul_vec3(m, child_pos)
    return (float(object_pos[0]) + dx, float(object_pos[1]) + dy, float(object_pos[2]) + dz)


def build_resolution_rows(mission_stem: str, mission_path: Path, records: List[dict], file_index: Dict[str, List[Path]], embedded_index: Optional[EmbeddedAssetIndex], parent_tag: str, include_extra_sgeo_records: bool = False) -> Tuple[List[dict], List[dict], List[dict], List[dict]]:
    res_rows: List[dict] = []
    sdf_rows: List[dict] = []
    unresolved: List[dict] = []
    sdf_cache: Dict[str, List[dict]] = {}
    for r in records:
        cls = classify_obj_resource(parent_tag, r["name"], r["class_raw"], r["dispatch_valid"])
        expected = cls["expected_name"]
        hits = all_index_hits(file_index, expected) if expected else []
        hit = hits[0] if hits else None
        row = {
            "mission": mission_stem,
            "path": str(mission_path),
            "parent_tag": parent_tag,
            "index": r["index"],
            "chunk_offset_hex": f"0x{r['chunk_offset']:08x}",
            "label": r["name"],
            "class_raw": r["class_raw"],
            "class_hex": r["class_hex"],
            "dispatch_valid": r["dispatch_valid"],
            "policy": cls["policy"],
            "resource_kind": cls["kind"],
            "expected_name": expected,
            "resolved": bool(hit),
            "resolved_path": str(hit) if hit else "",
            "hit_count": len(hits),
            "pos_x": r["pos"][0],
            "pos_y": r["pos"][1],
            "pos_z": r["pos"][2],
        }
        res_rows.append(row)
        if expected and not hit:
            unresolved.append(row.copy())
        if hit and cls["kind"] == "sdf":
            key = str(hit)
            if key not in sdf_cache:
                sdf_cache[key] = sdf_child_candidates(hit, file_index, embedded_index=embedded_index, include_extra_sgeo_records=include_extra_sgeo_records)
            for c in sdf_cache[key]:
                c2 = c.copy()
                try:
                    child_pos = (float(c2.get("pos_x", 0.0)), float(c2.get("pos_y", 0.0)), float(c2.get("pos_z", 0.0)))
                    awx, awy, awz = approx_child_world_position(r["pos"], r["basis"], child_pos)
                except Exception:
                    awx, awy, awz = (0.0, 0.0, 0.0)
                c2.update({
                    "mission": mission_stem,
                    "object_label": r["name"],
                    "object_index": r["index"],
                    "object_class_hex": r["class_hex"],
                    "object_pos_x": r["pos"][0],
                    "object_pos_y": r["pos"][1],
                    "object_pos_z": r["pos"][2],
                    "object_basis": ",".join(f"{v:.9g}" for v in r["basis"]),
                    "approx_world_x": awx,
                    "approx_world_y": awy,
                    "approx_world_z": awz,
                })
                sdf_rows.append(c2)
    instance_rows = [r for r in sdf_rows if r.get("part_kind") == "declared_part"]
    return res_rows, sdf_rows, unresolved, instance_rows


def export(args: argparse.Namespace) -> dict:
    input_path = Path(args.input)
    out_dir = timestamped_out_dir(args.out_dir, "i76_level_reconstruction_export_v15")
    out_dir.mkdir(parents=True, exist_ok=True)

    roots = [Path(r) for r in args.resource_root]
    if args.include_input_as_resource_root:
        roots.append(input_path if input_path.is_dir() else input_path.parent)
    file_index = build_file_index(roots)

    files = find_files(input_path)
    by_name = build_file_index([input_path if input_path.is_dir() else input_path.parent])
    missions = [p for p in files if p.suffix.lower() in MISSION_EXTS]
    if input_path.is_file() and input_path.suffix.lower() in MISSION_EXTS:
        missions = [input_path]
    if args.mission_filter:
        filt = args.mission_filter.lower()
        missions = [p for p in missions if filt in p.stem.lower() or filt in p.name.lower()]

    manifest = {
        "format": "i76_level_reconstruction_export",
        "version": 19,
        "source": str(input_path),
        "out_dir": str(out_dir),
        "resource_roots": [str(r) for r in roots],
        "resource_inventory": inventory_summary(file_index),
        "options": {k: (str(v) if isinstance(v, Path) else v) for k, v in vars(args).items()} | {"out_dir": str(out_dir)},
        "runtime_confirmed": [
            "BWD2/TDEF/ZMAP/ZONE parsing from v4 baseline",
            "TER 128x128 uint16 pages",
            "128x128 runtime page grid with ZMAP +24/+24",
            "height lookup through +0xc00-biased runtime page grid",
            "height low12 and surface class word>>13",
            "ODEF basis +0x08..+0x28 and position +0x2c/+0x30/+0x34",
            "ODEF class discriminator at +0x5c",
            "RSEG u32 kind, u32 count, count*0x18 records",
            "v42 class-specific ODEF resource policy",
            "LDEF normal object records resolve as label.sdf",
        ],
        "runtime_approximate": [
            "adaptive overlay projection/error predicate",
            "adaptive overlay edge sharing/T-junction behavior",
            "SDF child extraction uses Open76-aligned SGEO uint32 count + 0x78-byte SdfPart records",
            "Optional embedded asset-name resolution uses the historical ZFS/PIX/PAK resolver",
            "v15 can optionally instantiate declared static SGEO parts into first-pass untextured mission OBJ files",
            "static_part_instances.tsv emits declared SGEO rows plus approximate object*part world positions; static_part_world_transforms.tsv emits hierarchy-composed positions",
        ],
        "missions": [],
        "warnings": [],
    }

    embedded_index = build_embedded_asset_index(args, manifest.get("warnings"))
    manifest["embedded_resource_inventory"] = embedded_index.summary()
    geo_module = None
    geo_exporter_path = default_geo_exporter_from_args(args)
    if geo_exporter_path is not None:
        try:
            geo_module = load_optional_geo_exporter_module(geo_exporter_path)
            manifest["geo_exporter"] = str(geo_exporter_path)
        except Exception as e:
            manifest["warnings"].append(f"geo exporter unavailable: {e}")
            manifest["geo_exporter"] = str(geo_exporter_path)
    else:
        manifest["geo_exporter"] = ""

    all_obj_rows: List[dict] = []
    all_res_rows: List[dict] = []
    all_sdf_rows: List[dict] = []
    all_static_instance_rows: List[dict] = []
    all_unresolved: List[dict] = []
    all_rseg_record_rows: List[dict] = []
    all_rseg_point_rows: List[dict] = []
    all_static_mesh_error_rows: List[dict] = []
    all_static_part_world_transform_rows: List[dict] = []
    all_static_part_bounds_rows: List[dict] = []
    all_static_object_bounds_rows: List[dict] = []
    all_static_mission_bounds_rows: List[dict] = []
    all_static_material_rows: List[dict] = []
    all_terrain_material_rows: List[dict] = []

    for msn in sorted(missions):
        try:
            mission = load_mission(msn)
            info = {
                "mission": str(msn),
                "stem": msn.stem.lower(),
                "chunk_count": len(mission.chunks),
                "chunk_tags": {t: sum(1 for c in mission.chunks if c.tag == t) for t in sorted(set(c.tag for c in mission.chunks))},
                "zone_sidecar_name": mission.zone_sidecar_name,
            }
            rt: Optional[RuntimeTerrain] = None
            origin_world_x = 0.0
            origin_world_z = 0.0
            if mission.zmap is not None:
                info["zmap"] = mission.zmap.to_dict()
                origin_sample_x, origin_sample_z = origin_samples_for_zmap(mission.zmap, args.origin)
                origin_world_x = origin_sample_x * SAMPLE_WORLD_SCALE
                origin_world_z = origin_sample_z * SAMPLE_WORLD_SCALE
                info["origin"] = {
                    "mode": args.origin,
                    "origin_sample_x": origin_sample_x,
                    "origin_sample_z": origin_sample_z,
                    "origin_world_x": origin_world_x,
                    "origin_world_z": origin_world_z,
                }
                ter = find_sidecar(msn, mission.zone_sidecar_name, by_name)
                if ter is None:
                    manifest["warnings"].append(f"{msn}: no TER sidecar for {mission.zone_sidecar_name!r}")
                else:
                    pages = load_ter_pages(ter, mission.zmap.active_count)
                    rt = RuntimeTerrain(mission.zmap, pages, build_page_grid(mission.zmap), origin_sample_x, origin_sample_z, args.vertical_scale)
                    info["ter_sidecar"] = str(ter)
                    if args.write_terrain:
                        if args.write_terrain_materials:
                            verts, faces, surf = build_dense_terrain_mesh_with_surface_materials(rt, args.boundary_sampling)
                            terrain_info, terrain_rows = write_terrain_obj_with_surface_materials(
                                out_dir / "terrain_obj" / f"{msn.stem.lower()}.terrain_dense.obj",
                                verts, faces, surf, args.obj_coordinates, args.write_normals,
                                header="# I76 dense welded runtime-page-grid terrain baseline with diagnostic surface-class materials\n",
                            )
                            info["dense_terrain_obj"] = terrain_info
                            all_terrain_material_rows.extend(terrain_rows)
                        else:
                            verts, faces = build_dense_terrain_mesh(rt, args.boundary_sampling)
                            info["dense_terrain_obj"] = write_obj(
                                out_dir / "terrain_obj" / f"{msn.stem.lower()}.terrain_dense.obj",
                                verts, faces, args.obj_coordinates, args.write_normals,
                                header="# I76 dense welded runtime-page-grid terrain baseline\n",
                            )
                    if args.write_adaptive_overlay:
                        verts, faces, astats = build_adaptive_overlay_mesh(rt, args.adaptive_max_depth, args.adaptive_split_error, args.adaptive_force_surface_splits)
                        obj_info = write_obj(
                            out_dir / "terrain_obj" / f"{msn.stem.lower()}.terrain_adaptive_overlay.obj",
                            verts, faces, args.obj_coordinates, args.write_normals,
                            header="# I76 corrected adaptive terrain overlay; projection predicate still approximate\n",
                        )
                        obj_info["stats"] = astats
                        info["adaptive_overlay_obj"] = obj_info
            else:
                info["zmap"] = None

            odef_records = parse_obj_records(mission, "ODEF")
            ldef_records = parse_obj_records(mission, "LDEF")
            info["odef_obj_count"] = len(odef_records)
            info["ldef_obj_count"] = len(ldef_records)

            mission_static_instance_rows: List[dict] = []

            combined_for_axes = odef_records + ldef_records if args.include_ldef_axes else odef_records
            if args.write_odef_axes:
                info["odef_axes_obj"] = write_odef_axes_obj(
                    out_dir / "object_obj" / f"{msn.stem.lower()}.odef_axes.obj",
                    combined_for_axes, args.obj_coordinates, args.include_invalid_odef, args.odef_axis_length,
                    origin_world_x, origin_world_z,
                )

            for parent_tag, recs in (("ODEF", odef_records), ("LDEF", ldef_records)):
                for r in recs:
                    all_obj_rows.append({
                        "mission": msn.stem.lower(),
                        "path": str(msn),
                        "parent_tag": parent_tag,
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
                res_rows, sdf_rows, unresolved, instance_rows = build_resolution_rows(msn.stem.lower(), msn, recs, file_index, embedded_index, parent_tag, args.include_extra_sgeo_records)
                all_res_rows.extend(res_rows)
                all_sdf_rows.extend(sdf_rows)
                all_unresolved.extend(unresolved)
                all_static_instance_rows.extend(instance_rows)
                mission_static_instance_rows.extend(instance_rows)

            if args.copy_resolved:
                copied_roots = set()
                copied_geo = set()
                for row in all_res_rows:
                    rp = row.get("resolved_path")
                    if rp and rp not in copied_roots:
                        copy_unique(Path(rp), out_dir / "resolved_roots")
                        copied_roots.add(rp)
                for row in all_sdf_rows:
                    gp = row.get("geo_path")
                    if gp and not str(gp).startswith("embedded:") and gp not in copied_geo:
                        copy_unique(Path(gp), out_dir / "resolved_geo")
                        copied_geo.add(gp)


            if args.write_static_objects:
                obj_info, mesh_errors, transform_rows, part_bounds_rows, object_bounds_rows, mission_bounds_rows, material_rows = write_static_objects_obj(
                    out_dir / "static_obj" / f"{msn.stem.lower()}.static_objects.obj",
                    mission_static_instance_rows,
                    embedded_index,
                    geo_module,
                    args.obj_coordinates,
                    origin_world_x,
                    origin_world_z,
                    args.static_object_max_parts,
                )
                info["static_objects_obj"] = obj_info
                all_static_mesh_error_rows.extend(mesh_errors)
                all_static_part_world_transform_rows.extend(transform_rows)
                all_static_part_bounds_rows.extend(part_bounds_rows)
                all_static_object_bounds_rows.extend(object_bounds_rows)
                all_static_mission_bounds_rows.extend(mission_bounds_rows)
                all_static_material_rows.extend(material_rows)

            if args.write_resource_markers:
                info["resource_markers_obj"] = write_marker_obj(
                    out_dir / "object_obj" / f"{msn.stem.lower()}.resolved_resource_markers.obj",
                    [r for r in all_res_rows if r.get("mission") == msn.stem.lower()],
                    args.obj_coordinates, origin_world_x, origin_world_z, args.resource_marker_size,
                )

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
                    info["rseg_objs"].append(write_rseg_obj(
                        out_dir / "rseg_obj" / f"{msn.stem.lower()}.rseg_{mode}.obj",
                        rseg_points, mode, args.obj_coordinates, origin_world_x, origin_world_z,
                        rt, args.rseg_height_mode, args.rseg_height_offset,
                    ))

            if args.write_combined_scene:
                components: List[Tuple[str, Path]] = []
                if isinstance(info.get("dense_terrain_obj"), dict) and info["dense_terrain_obj"].get("path"):
                    components.append(("terrain_dense", Path(info["dense_terrain_obj"]["path"])))
                if isinstance(info.get("static_objects_obj"), dict) and info["static_objects_obj"].get("path"):
                    components.append(("static_objects", Path(info["static_objects_obj"]["path"])))
                for ro in info.get("rseg_objs", []) or []:
                    if isinstance(ro, dict) and ro.get("path"):
                        components.append(("rseg", Path(ro["path"])))
                if isinstance(info.get("odef_axes_obj"), dict) and info["odef_axes_obj"].get("path"):
                    components.append(("odef_axes", Path(info["odef_axes_obj"]["path"])))
                if isinstance(info.get("resource_markers_obj"), dict) and info["resource_markers_obj"].get("path"):
                    components.append(("resource_markers", Path(info["resource_markers_obj"]["path"])))
                info["combined_scene_obj"] = write_combined_scene_obj(
                    out_dir / "scene_obj" / f"{msn.stem.lower()}.combined_scene.obj",
                    components,
                )

            manifest["missions"].append(info)
        except Exception as e:
            manifest["warnings"].append(f"{msn}: {type(e).__name__}: {e}")

    write_tsv(
        out_dir / "tables" / "obj_records.tsv",
        all_obj_rows,
        ["mission", "path", "parent_tag", "index", "chunk_offset_hex", "name", "class_raw", "class_hex", "dispatch_valid", "pos_x", "pos_y", "pos_z", "basis", "tail_dwords_hex"],
    )
    # Compatibility alias for v4 consumers.
    write_tsv(
        out_dir / "tables" / "odef_obj_records.tsv",
        [r for r in all_obj_rows if r.get("parent_tag") == "ODEF"],
        ["mission", "path", "parent_tag", "index", "chunk_offset_hex", "name", "class_raw", "class_hex", "dispatch_valid", "pos_x", "pos_y", "pos_z", "basis", "tail_dwords_hex"],
    )
    write_tsv(
        out_dir / "tables" / "object_resource_resolution.tsv",
        all_res_rows,
        ["mission", "path", "parent_tag", "index", "chunk_offset_hex", "label", "class_raw", "class_hex", "dispatch_valid", "policy", "resource_kind", "expected_name", "resolved", "resolved_path", "hit_count", "pos_x", "pos_y", "pos_z"],
    )
    write_tsv(
        out_dir / "tables" / "sdf_child_candidates.tsv",
        all_sdf_rows,
        ["mission", "object_label", "object_index", "object_class_hex", "object_pos_x", "object_pos_y", "object_pos_z", "object_basis", "sdf_path", "sdf_object_name", "sgeo_chunk_offset_hex", "declared_part_count", "offset_hex", "parser", "part_kind", "part_index", "token", "parent_name", "geo_name", "geo_found", "geo_source", "geo_path", "score", "reasons", "right_x", "right_y", "right_z", "up_x", "up_y", "up_z", "forward_x", "forward_y", "forward_z", "pos_x", "pos_y", "pos_z", "approx_world_x", "approx_world_y", "approx_world_z"],
    )
    write_tsv(
        out_dir / "tables" / "static_part_instances.tsv",
        all_static_instance_rows,
        ["mission", "object_label", "object_index", "object_class_hex", "object_pos_x", "object_pos_y", "object_pos_z", "object_basis", "sdf_path", "sdf_object_name", "declared_part_count", "part_index", "token", "parent_name", "geo_name", "geo_found", "geo_source", "geo_path", "right_x", "right_y", "right_z", "up_x", "up_y", "up_z", "forward_x", "forward_y", "forward_z", "pos_x", "pos_y", "pos_z", "approx_world_x", "approx_world_y", "approx_world_z"],
    )
    write_tsv(
        out_dir / "tables" / "static_part_world_transforms.tsv",
        all_static_part_world_transform_rows,
        ["mission", "object_label", "object_index", "part_index", "token", "parent_name", "geo_name", "world_pos_x", "world_pos_y", "world_pos_z", "obj_local_pos_x", "obj_local_pos_y", "obj_local_pos_z", "world_right", "world_up", "world_forward", "geo_vertices", "geo_faces"],
    )
    write_tsv(
        out_dir / "tables" / "static_material_slots.tsv",
        all_static_material_rows,
        ["mission", "object_label", "object_index", "part_index", "token", "parent_name", "geo_name", "face_index", "texture_name", "material_key", "texture_probe_name", "texture_found", "texture_source", "texture_hit_count", "texture_path", "color_r", "color_g", "color_b", "surface_flags", "vertex_count", "u_min", "u_max", "v_min", "v_max"],
    )
    write_tsv(
        out_dir / "tables" / "terrain_material_surface_classes.tsv",
        all_terrain_material_rows,
        ["mission", "surface_class", "high_bits_hex", "binary_code", "material_key", "face_count", "runtime_forced_split", "diagnostic_role", "mtl_path", "note"],
    )
    static_texture_export_rows: List[dict] = []
    texture_export_warnings: List[str] = []
    texture_mtls_rewritten = 0
    if args.export_static_textures:
        static_texture_export_rows, static_texture_bindings, texture_export_warnings = extract_static_textures(
            out_dir, all_static_material_rows, embedded_index, geo_module, args.palette_file, args.palette_scale, args.vqm_layout
        )
        texture_mtls_rewritten = rewrite_static_mtls_with_textures(out_dir, static_texture_bindings)
        manifest["warnings"].extend(texture_export_warnings)
    write_tsv(
        out_dir / "tables" / "static_texture_exports.tsv",
        static_texture_export_rows,
        ["mission", "material_key", "texture_name", "texture_probe_name", "asset_name", "asset_id", "asset_ext", "status", "output_relpath", "evidence", "error"],
    )
    static_material_texture_summary_rows, static_material_solid_color_rows = build_static_material_texture_summary(all_static_material_rows)
    write_tsv(
        out_dir / "tables" / "static_material_texture_summary.tsv",
        static_material_texture_summary_rows,
        ["mission", "texture_name", "texture_probe_name", "texture_found", "texture_source", "texture_path", "planned_png", "face_count", "object_count", "part_count", "geo_count", "material_keys", "color_keys", "u_min", "u_max", "v_min", "v_max"],
    )
    write_tsv(
        out_dir / "tables" / "static_material_solid_color_faces.tsv",
        static_material_solid_color_rows,
        ["mission", "texture_name", "texture_probe_name", "texture_found", "texture_source", "texture_path", "planned_png", "face_count", "object_count", "part_count", "geo_count", "material_keys", "color_keys", "u_min", "u_max", "v_min", "v_max"],
    )
    write_tsv(
        out_dir / "tables" / "static_part_bounds.tsv",
        all_static_part_bounds_rows,
        ["mission", "object_label", "object_index", "part_index", "token", "parent_name", "geo_name", "vertex_count", "min_x", "min_y", "min_z", "max_x", "max_y", "max_z", "center_x", "center_y", "center_z", "size_x", "size_y", "size_z"],
    )
    write_tsv(
        out_dir / "tables" / "static_object_bounds.tsv",
        all_static_object_bounds_rows,
        ["mission", "object_label", "object_index", "vertex_count", "min_x", "min_y", "min_z", "max_x", "max_y", "max_z", "center_x", "center_y", "center_z", "size_x", "size_y", "size_z"],
    )
    write_tsv(
        out_dir / "tables" / "static_mission_bounds.tsv",
        all_static_mission_bounds_rows,
        ["mission", "vertex_count", "min_x", "min_y", "min_z", "max_x", "max_y", "max_z", "center_x", "center_y", "center_z", "size_x", "size_y", "size_z"],
    )
    write_tsv(
        out_dir / "tables" / "static_mesh_errors.tsv",
        all_static_mesh_error_rows,
        ["mission", "object_label", "object_index", "sdf_path", "part", "parent", "geo_name", "warning"],
    )
    write_tsv(
        out_dir / "tables" / "unresolved_resources.tsv",
        all_unresolved,
        ["mission", "path", "parent_tag", "index", "chunk_offset_hex", "label", "class_raw", "class_hex", "policy", "resource_kind", "expected_name", "pos_x", "pos_y", "pos_z"],
    )
    write_tsv(
        out_dir / "tables" / "rdef_rseg_records.tsv",
        all_rseg_record_rows,
        ["mission", "path", "rseg_index", "chunk_offset", "kind", "count", "payload_size", "expected_payload_size", "size_matches"],
    )
    write_tsv(
        out_dir / "tables" / "rdef_rseg_points.tsv",
        all_rseg_point_rows,
        ["mission", "path", "rseg_index", "point_index", "kind", "left_x", "left_z", "aux_z_or_mid", "right_x", "height_or_y", "right_z", "center_x", "center_z", "width"],
    )

    manifest["totals"] = {
        "missions_seen": len(missions),
        "missions_exported": len(manifest["missions"]),
        "obj_records": len(all_obj_rows),
        "resource_resolution_rows": len(all_res_rows),
        "resolved_resource_rows": sum(1 for r in all_res_rows if r.get("resolved")),
        "sdf_child_candidate_rows": len(all_sdf_rows),
        "static_part_instance_rows": len(all_static_instance_rows),
        "static_part_world_transform_rows": len(all_static_part_world_transform_rows),
        "static_mesh_error_rows": len(all_static_mesh_error_rows),
        "static_part_bounds_rows": len(all_static_part_bounds_rows),
        "static_object_bounds_rows": len(all_static_object_bounds_rows),
        "static_mission_bounds_rows": len(all_static_mission_bounds_rows),
        "static_material_slot_rows": len(all_static_material_rows),
        "static_material_texture_hits": sum(1 for r in all_static_material_rows if str(r.get("texture_found", "")).lower() in {"true", "1", "yes"}),
        "static_texture_export_rows": len(static_texture_export_rows),
        "static_texture_export_success_rows": sum(1 for r in static_texture_export_rows if str(r.get("status", "")) == "exported"),
        "static_texture_mtls_rewritten": texture_mtls_rewritten,
        "terrain_material_surface_class_rows": len(all_terrain_material_rows),
        "terrain_material_runtime_forced_split_rows": sum(1 for r in all_terrain_material_rows if str(r.get("runtime_forced_split", "")).lower() in {"true", "1", "yes"}),
        "static_material_unique_textures": len([r for r in static_material_texture_summary_rows if r.get("texture_name")]),
        "static_material_solid_color_groups": len(static_material_solid_color_rows),
        "combined_scene_objs": sum(1 for m in manifest["missions"] if isinstance(m.get("combined_scene_obj"), dict) and m["combined_scene_obj"].get("components_written", 0) > 0),
        "unresolved_resource_rows": len(all_unresolved),
        "rseg_records": len(all_rseg_record_rows),
        "rseg_points": len(all_rseg_point_rows),
    }

    notes = [
        "i76_level_reconstruction_export_v19 notes",
        "",
        "This revision is based on the repo/local_history v4 BWD2 mission-parser workflow and extends v18 with explicit terrain-code legend fields for diagnostic ground materials.",
        "It deliberately avoids raw .MSN sliding-window ODEF scans.",
        "",
        "Primary tables:",
        "  tables/obj_records.tsv                  parsed ODEF/LDEF OBJ chunks from mission containers",
        "  tables/object_resource_resolution.tsv   v42/v43 class-specific SDF/VCF root resolution",
        "  tables/sdf_child_candidates.tsv         SGEO SdfPart -> GEO candidate links",
        "  tables/static_part_instances.tsv        declared SGEO parts with embedded GEO links",
        "  tables/static_part_world_transforms.tsv hierarchy-composed static part transforms",
        "  tables/static_part_bounds.tsv          per SGEO/GEO part world-space bounds",
        "  tables/static_object_bounds.tsv        per ODEF/LDEF root object world-space bounds",
        "  tables/static_mission_bounds.tsv       per mission static-object world-space bounds",
        "  scene_obj/*.combined_scene.obj         optional combined terrain/static/RSEG/marker validation OBJ",
        "  tables/static_mesh_errors.tsv           GEO parse/write diagnostics from static OBJ assembly",
        "  tables/unresolved_resources.tsv         labels expected by policy but not found in resource index",
        "",
        "Static OBJ assembly is a first-pass geometry-only export.  It composes ODEF/LDEF object transforms",
        "with SGEO parent hierarchy and parses GEO through the historical vehicle_geo_obj_export_v20 parser.",
        "Texture decoding/binding, lighting, collision, and exact render-record semantics remain downstream work. v16 preserves GEO face material identity and writes placeholder MTL colors for visual debugging.",
    ]
    (out_dir / "notes.txt").write_text("\n".join(notes) + "\n", encoding="utf-8")

    manifest_path = out_dir / "manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    if args.make_tar:
        tar_path = make_tar(out_dir)
        manifest["tar_path"] = str(tar_path) if tar_path else None
        manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    print(json.dumps({
        "manifest": str(manifest_path),
        "tar_path": manifest.get("tar_path"),
        **manifest["totals"],
        "warnings": len(manifest["warnings"]),
    }, indent=2))

    if args.fail_empty and not manifest["missions"]:
        raise SystemExit("no missions exported")
    return manifest


def main(argv: Optional[Sequence[str]] = None) -> int:
    ap = argparse.ArgumentParser(description="Interstate '76 level reconstruction exporter with v42 class-specific object resource resolution, static SGEO/GEO assembly, bounds, combined scene validation, and material diagnostics")
    ap.add_argument("input", help="Directory containing .MSN/.SPC/.LVL and .TER sidecars, or a single mission file")
    ap.add_argument("--resource-root", action="append", default=[], help="Additional resource root(s), e.g. extracted zfs and/or retail install root. Repeatable.")
    ap.add_argument("--resolver", type=Path, default=None, help="Optional historical resolver script, usually scripts/local_history/i76_vehicle_texture_slot_resolver_v5.py, for embedded ZFS/PIX/PAK asset names")
    ap.add_argument("--zfs", type=Path, default=None, help="Optional I76.ZFS path used with --resolver to index embedded GEO/TMT/MAP/M16/VQM/CBK assets")
    ap.add_argument("--zix", type=Path, default=None, help="Reserved for compatibility with older commands; current resolver hook uses --zfs")
    ap.add_argument("--geo-exporter", type=Path, default=None, help="Optional historical GEO exporter/parser script, usually scripts/local_history/i76_vehicle_geo_obj_export_v20.py. Defaults to sibling of --resolver when present.")
    ap.add_argument("--export-static-textures", action="store_true", help="Decode/export unique M16/VQM texture payloads used by static SGEO/GEO materials and bind them into static_objects.mtl")
    ap.add_argument("--palette-file", type=Path, default=None, help="Optional 256*3 RGB palette/ACT file for indexed texture PNG export; without this, grayscale debug PNGs are written")
    ap.add_argument("--palette-scale", choices=["auto", "raw", "x4"], default="auto", help="Palette scaling mode passed to the historical GEO texture exporter")
    ap.add_argument("--vqm-layout", default="yx", help="VQM/CBK 4x4 tile layout for texture export; yx is the current validated default")
    ap.add_argument("--write-terrain-materials", action="store_true", help="When writing dense terrain, emit diagnostic TER surface-class materials on the ground mesh")
    ap.add_argument("--include-input-as-resource-root", action="store_true", default=True, help="Include input directory/parent in resource index; default true")
    ap.add_argument("--no-include-input-as-resource-root", dest="include_input_as_resource_root", action="store_false")
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
    ap.add_argument("--include-ldef-axes", action="store_true", help="Include LDEF OBJ records in object axes output")
    ap.add_argument("--include-invalid-odef", action="store_true", help="Include dispatch-invalid ODEF rows in axes OBJ")
    ap.add_argument("--odef-axis-length", type=float, default=25.0)
    ap.add_argument("--write-resource-markers", action="store_true", help="Write placement markers for resolved root SDF/VCF objects")
    ap.add_argument("--write-static-objects", action="store_true", help="Write first-pass untextured static_objects.obj per mission using declared SGEO parts and GEO parser")
    ap.add_argument("--write-combined-scene", action="store_true", help="Write combined per-mission validation OBJ that concatenates terrain/static/RSEG/axes/resource marker OBJs")
    ap.add_argument("--static-object-max-parts", type=int, default=0, help="Optional cap on static SGEO parts written per mission; 0 means no cap")
    ap.add_argument("--resource-marker-size", type=float, default=10.0)
    ap.add_argument("--write-rseg", action="store_true", help="Write RSEG centerline/edge/crossbar OBJ probes")
    ap.add_argument("--rseg-height-mode", choices=["terrain", "zero", "serialized"], default="terrain", help="Vertical coordinate for RSEG probes. 'terrain' samples .TER height; 'serialized' uses RSEG float +0x10 and is diagnostic only.")
    ap.add_argument("--rseg-height-offset", type=float, default=1.0, help="Vertical lift applied to RSEG probes in terrain/zero height modes so lines sit above terrain.")
    ap.add_argument("--copy-resolved", action="store_true", help="Copy resolved root SDF/VCF and SGEO child GEO files into output folders")
    ap.add_argument("--include-extra-sgeo-records", action="store_true", help="Include SGEO records after declared count as diagnostic extra_or_wreck rows; off by default")
    ap.add_argument("--make-tar", action="store_true")
    ap.add_argument("--fail-empty", action="store_true")
    args = ap.parse_args(argv)

    if not (args.write_terrain or args.write_adaptive_overlay or args.write_odef_axes or args.write_rseg or args.write_resource_markers or args.write_static_objects or args.write_combined_scene):
        args.write_terrain = True
        args.write_odef_axes = True
        args.write_rseg = True
        args.write_resource_markers = True
        args.write_static_objects = True
        args.write_combined_scene = True

    export(args)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
