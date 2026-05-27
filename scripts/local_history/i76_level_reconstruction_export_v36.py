#!/usr/bin/env python3
"""
Interstate '76 level reconstruction exporter, v36.

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
  - Add v16/v17 static GEO face material diagnostics and visible terrain surface-code diagnostics and grouped summaries.
  - Add v18 static texture PNG extraction/binding for resolved M16/VQM assets.
  - Add v18 first-pass terrain surface-class materials for dense ground mesh.
  - Add v19 explicit terrain-code legend fields so diagnostic ground colors are easier to interpret.
  - Add v23 terrain surface attribution probes: connected regions/bounds plus mission sidecar candidate inventory.
  - Add v23 mission resource string inventory and RSEG/terrain surface overlap probes.
  - Add v24 terrain surface adjacency and road-context attribution labels.
  - Add v31 terrain MAP structure probe for miss8/miss16 terrain texture candidates.
  - Add v32 direct 128x128 MAP image decode for terrain/sky MAP payloads.
  - Add v33 terrain UV emission for candidate texture validation.
  - Add v36 static GEO UV emission so non-terrain meshes can display bound MAP/M16/VQM textures.

This is still a reconstruction/probe script, not a final renderer clone.  It is intentionally
conservative: unresolved resources are emitted to TSV/JSON rather than guessed.
"""
from __future__ import annotations

import argparse
import csv
import fnmatch
import hashlib
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

try:
    from PIL import Image
except Exception:
    Image = None

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
    write_static_uvs: bool = True,
    static_uv_v_flip: bool = True,
) -> Tuple[dict, List[dict], List[dict], List[dict], List[dict], List[dict], List[dict]]:
    """Write a first-pass static SDF-part OBJ for one mission.

    v16 also emits validation-ready transform/bounds rows plus per-GEO-face material diagnostics and visible terrain surface-code diagnostics.
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
    texcoord_count = 0
    if geo_module is None or not hasattr(geo_module, "parse_geo"):
        return {"path": str(path), "written": False, "reason": "geo_exporter_unavailable"}, [], [], [], [], [], []

    rows = [r for r in rows if str(r.get("part_kind", "declared_part")) == "declared_part" and str(r.get("geo_found", "")).lower() in {"true", "1", "yes"}]
    if max_parts and max_parts > 0:
        rows = rows[:max_parts]

    mesh_cache: Dict[str, Any] = {}
    v_base = 1
    vt_base = 1
    part_count = 0
    face_count = 0
    vertex_count = 0
    groups = static_row_groups(rows)

    with path.open("w", encoding="utf-8") as obj:
        obj.write("# Interstate '76 static SDF/SGEO object assembly v35\n")
        obj.write("# Geometry plus material identity: ODEF/LDEF object transform * SGEO hierarchy * GEO vertices/faces.\n")
        obj.write("# v36 emits GEO face UVs as OBJ vt records so bound static MAP/M16/VQM textures are visible.\n")
        obj.write("# Texture binding remains diagnostic; see tables/static_material_slots.tsv and static_material_texture_summary.tsv.\n")
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
                        face_tokens = []
                        vt_indices: List[int] = []
                        if write_static_uvs:
                            for ref in refs:
                                u = float(getattr(ref, "u", 0.0) or 0.0)
                                v = float(getattr(ref, "v", 0.0) or 0.0)
                                if static_uv_v_flip:
                                    v = 1.0 - v
                                obj.write(f"vt {u:.8g} {v:.8g}\n")
                                vt_indices.append(vt_base)
                                vt_base += 1
                                texcoord_count += 1
                        for ref_i, ref in enumerate(refs):
                            idx = int(getattr(ref, "vertex_index", 0))
                            v_idx = v_base + idx
                            if write_static_uvs and ref_i < len(vt_indices):
                                face_tokens.append(f"{v_idx}/{vt_indices[ref_i]}")
                            else:
                                face_tokens.append(str(v_idx))
                        obj.write("f " + " ".join(face_tokens) + "\n")
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
            mtl.write("# Interstate '76 static material identity placeholders v35\n")
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
        "texcoords": texcoord_count,
        "faces": face_count,
        "write_static_uvs": bool(write_static_uvs),
        "static_uv_v_flip": bool(static_uv_v_flip),
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


def extract_static_textures(out_dir: Path, rows: List[dict], embedded_index: EmbeddedAssetIndex, geo_module: Any, palette_file: Optional[Path], palette_scale: str, vqm_layout: str, static_palette_rows: Optional[List[dict]] = None) -> Tuple[List[dict], Dict[Tuple[str, str], str], List[str]]:
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
    palette_cache: Dict[str, Any] = {}
    static_palette_by_mission: Dict[str, dict] = {}
    for pr in static_palette_rows or []:
        static_palette_by_mission[str(pr.get('mission', '') or '').lower()] = pr

    def palette_for_mission(mission: str):
        mission_key = (mission or '').lower()
        pr = static_palette_by_mission.get(mission_key, {})
        pth_s = str(pr.get('palette_path', '') or '')
        scale = str(pr.get('palette_scale', '') or '') or palette_scale
        if not pth_s and palette_file is not None:
            pth_s = str(palette_file)
            scale = palette_scale
        if not pth_s:
            return None, '', '', ''
        cache_key = pth_s + '|' + scale
        if cache_key in palette_cache:
            return palette_cache[cache_key], pth_s, scale, str(pr.get('palette_source', '') or 'fallback_global_palette_file')
        try:
            pal = geo_module.load_palette_file(Path(pth_s), scale) if hasattr(geo_module, 'load_palette_file') else None
            palette_cache[cache_key] = pal
            return pal, pth_s, scale, str(pr.get('palette_source', '') or 'fallback_global_palette_file')
        except Exception as e:
            warnings.append(f'palette_load_failed:{pth_s}:{e}')
            palette_cache[cache_key] = None
            return None, pth_s, scale, str(pr.get('palette_source', '') or 'palette_load_failed')
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
        used_palette_path = ''
        used_palette_scale = ''
        used_palette_source = ''
        if asset is not None:
            try:
                palette_rgb, used_palette_path, used_palette_scale, used_palette_source = palette_for_mission(mission)
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
            'palette_path': used_palette_path,
            'palette_scale': used_palette_scale,
            'palette_source': used_palette_source,
            'error': err,
        })
    return export_rows, bindings, warnings



def select_static_palette_rows(resource_rows: List[dict], static_palette_mode: str, static_palette_file: Optional[Path], static_palette_scale: str, fallback_palette_file: Optional[Path], fallback_palette_scale: str) -> List[dict]:
    """Select a palette for static object texture export per mission.

    Static SDF/GEO textures can use a mission-local ACT context rather than the global/vehicle
    palette.  This mirrors the terrain palette selector but keeps a separate diagnostic table so
    the static/object palette choice is explicit.
    """
    base_rows = select_terrain_palette_rows(
        resource_rows,
        "mission-act" if static_palette_mode == "mission-act" else ("explicit" if static_palette_mode == "explicit" else "global"),
        static_palette_file,
        static_palette_scale,
        fallback_palette_file,
        fallback_palette_scale,
    )
    out: List[dict] = []
    for r in base_rows:
        source = str(r.get("palette_source", "") or "")
        if static_palette_mode == "global" and fallback_palette_file is not None:
            source = "global_static_palette_file"
        elif static_palette_mode == "explicit" and static_palette_file is not None:
            source = "explicit_static_palette_file"
        elif static_palette_mode == "mission-act":
            source = source or "mission_literal_act"
        out.append({
            "mission": r.get("mission", ""),
            "static_palette_mode": static_palette_mode,
            "palette_name": r.get("palette_name", ""),
            "palette_path": r.get("palette_path", ""),
            "palette_source": source,
            "palette_scale": r.get("palette_scale", ""),
            "note": ("static textures use mission ACT when available; global --palette-file is fallback" if static_palette_mode == "mission-act" else r.get("note", "")),
        })
    return out

def terrain_candidate_priority(role: str, name: str) -> int:
    """Lower is better.  This is attribution priority, not a binding claim."""
    role_l = (role or "").lower()
    name_l = (name or "").lower()
    if "terrain_surface_texture" in role_l:
        return 0
    if name_l.startswith("tp") and name_l.endswith(".map"):
        return 1
    if "sky_or_environment" in role_l:
        return 20
    if name_l.startswith("nk") and name_l.endswith(".map"):
        return 21
    if "palette_or_color" in role_l:
        return 40
    if "lighting_luma" in role_l:
        return 50
    if name_l.endswith((".map", ".m16", ".vqm", ".tmt")):
        return 10
    return 99


def select_terrain_palette_rows(resource_rows: List[dict], terrain_palette_mode: str, terrain_palette_file: Optional[Path], terrain_palette_scale: str, fallback_palette_file: Optional[Path], fallback_palette_scale: str) -> List[dict]:
    """Pick the palette context to use for terrain/environment texture previews.

    Static-object textures can look correct with the current vehicle/reference ACT, but mission-level
    terrain texture candidates often carry their own palette context in the mission header.  For M06,
    the mission contains t09_16.ACT, so the conservative default is to use that ACT for terrain
    candidate exports while leaving static textures on --palette-file.
    """
    by_mission: Dict[str, List[dict]] = {}
    for r in resource_rows:
        mission = str(r.get("mission", "") or "")
        if mission:
            by_mission.setdefault(mission, []).append(r)
    rows: List[dict] = []
    for mission, rr in sorted(by_mission.items()):
        chosen_path = ""
        chosen_name = ""
        source = "none"
        mode = terrain_palette_mode
        note = ""
        if terrain_palette_mode == "mission-act":
            act_rows = [r for r in rr if str(r.get("resource_role", "")) == "palette_or_color_context_candidate" and str(r.get("ext", "")).lower() == "act" and str(r.get("found_file", "")).lower() == "true" and str(r.get("first_file_path", ""))]
            act_rows.sort(key=lambda r: (int(str(r.get("offset_hex", "0x0")), 16) if str(r.get("offset_hex", "")).startswith("0x") else 0, str(r.get("normalized_name", ""))))
            if act_rows:
                chosen_path = str(act_rows[0].get("first_file_path", "") or "")
                chosen_name = str(act_rows[0].get("normalized_name", "") or Path(chosen_path).name)
                source = "mission_literal_act"
                note = "selected from literal ACT reference in mission payload"
        if not chosen_path and terrain_palette_file is not None:
            chosen_path = str(terrain_palette_file)
            chosen_name = Path(chosen_path).name
            source = "explicit_terrain_palette_file"
            note = "selected from --terrain-palette-file"
        if not chosen_path and fallback_palette_file is not None:
            chosen_path = str(fallback_palette_file)
            chosen_name = Path(chosen_path).name
            source = "fallback_global_palette_file"
            note = "fallback to --palette-file"
        if not chosen_path:
            note = "no terrain palette selected; texture export will use grayscale/debug palette if exporter does so"
        rows.append({
            "mission": mission,
            "terrain_palette_mode": mode,
            "palette_name": chosen_name,
            "palette_path": chosen_path,
            "palette_source": source,
            "palette_scale": terrain_palette_scale if source in {"mission_literal_act", "explicit_terrain_palette_file"} else fallback_palette_scale,
            "note": note,
        })
    return rows


def _palette_selection_by_mission(rows: List[dict]) -> Dict[str, dict]:
    return {str(r.get("mission", "") or ""): r for r in rows if str(r.get("mission", "") or "")}



def _palette_to_flat_rgb(palette_rgb: Any) -> Optional[List[int]]:
    """Normalize the historical exporter palette representation to a flat RGB list."""
    if palette_rgb is None:
        return None
    if isinstance(palette_rgb, (bytes, bytearray)):
        vals = list(palette_rgb)
        if len(vals) >= 768:
            return vals[:768]
        return None
    flat: List[int] = []
    try:
        for item in palette_rgb:
            if isinstance(item, (tuple, list)) and len(item) >= 3:
                flat.extend([int(item[0]) & 0xff, int(item[1]) & 0xff, int(item[2]) & 0xff])
            else:
                flat.append(int(item) & 0xff)
    except Exception:
        return None
    if len(flat) >= 768:
        return flat[:768]
    return None


def decode_direct_map_payload_info(payload: Optional[bytes]) -> Optional[Tuple[int, int, int, bytes]]:
    """Return (w, h, pixel_offset, pixels) for direct 8-bit MAP payloads.

    M06 miss8 terrain/environment MAPs such as TT181SD_.MAP and NK_1CLD2.MAP have
    a simple direct-image shape in the probe table: payload size 16392, u32 width 128,
    u32 height 128, followed by 128*128 indexed pixels.  This is distinct from MAP names
    that are merely indirections to sibling M16/VQM payloads.
    """
    if not payload or len(payload) < 16:
        return None
    candidates: List[Tuple[int, int, int]] = []
    try:
        w0 = struct.unpack_from('<I', payload, 0)[0]
        h0 = struct.unpack_from('<I', payload, 4)[0]
        candidates.append((w0, h0, 8))
    except Exception:
        pass
    try:
        w1 = struct.unpack_from('<H', payload, 0)[0]
        h1 = struct.unpack_from('<H', payload, 2)[0]
        candidates.append((w1, h1, 4))
    except Exception:
        pass
    for w, h, off in candidates:
        if w <= 0 or h <= 0 or w > 2048 or h > 2048:
            continue
        need = int(w) * int(h)
        if need <= 0:
            continue
        if len(payload) >= off + need:
            # Prefer the exact 128x128 direct terrain/environment case, but keep the helper generic.
            return int(w), int(h), int(off), payload[off:off + need]
    return None


def export_direct_map_payload_png(payload: bytes, out_path: Path, palette_rgb: Any) -> Tuple[bool, str, str]:
    """Export a direct indexed MAP payload as PNG.

    Returns (success, decode_kind, error).  The image is written as palette-indexed PNG when a
    palette is available, otherwise grayscale debug PNG.  This path is intentionally separate from
    the historical M16/VQM exporter because direct terrain MAP payloads are not decoded by that helper.
    """
    info = decode_direct_map_payload_info(payload)
    if info is None:
        return False, '', 'not_direct_indexed_map_payload'
    if Image is None:
        return False, 'direct_map_indexed', 'Pillow_not_available'
    w, h, off, pixels = info
    try:
        img = Image.frombytes('P', (w, h), pixels)
        pal = _palette_to_flat_rgb(palette_rgb)
        if pal is not None:
            img.putpalette(pal)
            decode_kind = f'direct_map_indexed_{w}x{h}_palette'
        else:
            # Leave P mode with a grayscale palette to make raw index gradients visible.
            img.putpalette([v for i in range(256) for v in (i, i, i)])
            decode_kind = f'direct_map_indexed_{w}x{h}_grayscale_debug'
        out_path.parent.mkdir(parents=True, exist_ok=True)
        img.save(out_path)
        return True, decode_kind, ''
    except Exception as e:
        return False, f'direct_map_indexed_{w}x{h}', f'{type(e).__name__}:{e}'


def terrain_asset_payload(asset: Any, embedded_index: EmbeddedAssetIndex) -> Optional[bytes]:
    if asset is None:
        return None
    aid = str(getattr(asset, 'asset_id', '') or '')
    if aid and aid in embedded_index.payloads:
        return embedded_index.payloads.get(aid)
    return None

def export_terrain_candidate_textures(out_dir: Path, resource_rows: List[dict], embedded_index: EmbeddedAssetIndex, geo_module: Any, palette_selection_rows: List[dict], vqm_layout: str) -> Tuple[List[dict], List[str]]:
    """Decode mission-level terrain/environment texture candidates for visual inspection.

    This deliberately does not prove the TER surface-class -> texture lookup.  v27 does, however,
    use mission ACT palette context for these terrain/environment previews when available, because
    M06 advertises t09_16.ACT in its mission payload and the vehicle/static palette can decode the
    right texture with the wrong colors.
    """
    warnings: List[str] = []
    rows: List[dict] = []
    if geo_module is None:
        return rows, ["geo_exporter_unavailable_for_terrain_candidate_texture_export"]
    if embedded_index.resolver_index is None or embedded_index.resolver_module is None:
        return rows, ["embedded_resolver_unavailable_for_terrain_candidate_texture_export"]
    if not hasattr(geo_module, "export_texture_for_asset"):
        return rows, ["geo_exporter_lacks_export_texture_for_asset"]

    tex_dir = out_dir / "terrain_obj" / "textures"
    tex_dir.mkdir(parents=True, exist_ok=True)
    palette_by_mission = _palette_selection_by_mission(palette_selection_rows)
    palette_cache: Dict[Tuple[str, str], Any] = {}

    def load_palette_for_mission(mission: str):
        sel = palette_by_mission.get(mission, {})
        palette_path = str(sel.get("palette_path", "") or "")
        palette_scale = str(sel.get("palette_scale", "auto") or "auto")
        if not palette_path:
            return None
        key = (palette_path, palette_scale)
        if key in palette_cache:
            return palette_cache[key]
        try:
            pal = geo_module.load_palette_file(Path(palette_path), palette_scale) if hasattr(geo_module, "load_palette_file") else None
            palette_cache[key] = pal
            return pal
        except Exception as e:
            warnings.append(f"terrain_palette_load_failed:{palette_path}:{e}")
            palette_cache[key] = None
            return None

    # Keep texture-like mission strings, but include environment/sky candidates too because some
    # level pages distinguish sky/scrounge/surface/level-map resources.
    wanted_roles = {
        "terrain_surface_texture_candidate",
        "sky_or_environment_texture_candidate",
        "texture_or_material_candidate",
    }
    seen = set()
    written: Dict[str, str] = {}
    candidate_rows = []
    for r in resource_rows:
        mission = str(r.get("mission", "") or "")
        name = str(r.get("normalized_name", "") or "")
        ext = str(r.get("ext", "") or "").lower()
        role = str(r.get("resource_role", "") or "")
        if not mission or not name:
            continue
        if ext not in {"map", "m16", "vqm", "tmt"}:
            continue
        if role not in wanted_roles and not name.lower().startswith(("tp", "nk")):
            continue
        key = (mission, name)
        if key in seen:
            continue
        seen.add(key)
        candidate_rows.append(r)

    candidate_rows.sort(key=lambda r: (str(r.get("mission", "")), terrain_candidate_priority(str(r.get("resource_role", "")), str(r.get("normalized_name", ""))), str(r.get("normalized_name", ""))))

    for r in candidate_rows:
        mission = str(r.get("mission", "") or "")
        name = str(r.get("normalized_name", "") or "")
        role = str(r.get("resource_role", "") or "")
        asset, probe, evidence = resolve_texture_asset_object(name, embedded_index)
        # MAP references frequently name a sibling M16/VQM payload.  resolve_texture_asset_object
        # already prefers M16/VQM, but keep a second explicit fallback for mission-string MAP names.
        if asset is not None and str(getattr(asset, "ext", "")).lower() == "map":
            stem = str(getattr(asset, "stem", "") or Path(name).stem).upper()
            idx = embedded_index.resolver_index
            for ext in ("m16", "vqm"):
                alt = idx.resolve(stem, ext, source=asset) if idx is not None else None
                if alt is not None:
                    asset = alt
                    evidence += f";map_to_{ext}"
                    break
        if asset is not None and str(getattr(asset, "ext", "")).lower() == "tmt" and hasattr(geo_module, "first_texture_from_tmt"):
            alt = geo_module.first_texture_from_tmt(embedded_index.resolver_module, embedded_index.resolver_index, asset)
            if alt is not None:
                asset = alt
                evidence += ";tmt_first_frame"
        status = "not_exported"
        out_rel = ""
        err = ""
        if asset is not None:
            try:
                palette_rgb = load_palette_for_mission(mission)
                # v32: Some mission terrain/environment MAPs are direct indexed images
                # (u32 width, u32 height, followed by w*h palette indices) rather than
                # MAP -> sibling M16/VQM indirections.  Decode those before falling back
                # to the historical M16/VQM exporter.
                if str(getattr(asset, "ext", "")).lower() == "map":
                    payload = terrain_asset_payload(asset, embedded_index)
                    out_name = safe_name(Path(name).stem.upper()) + ".png"
                    out_path = tex_dir / out_name
                    ok, decode_kind, direct_err = export_direct_map_payload_png(payload or b"", out_path, palette_rgb)
                    if ok:
                        out_rel = "terrain_obj/textures/" + out_name
                        status = "exported"
                        evidence += ";" + decode_kind
                    else:
                        err = direct_err
                        # Keep a raw copy for diagnostic parity with older runs.
                        raw_name = safe_name(Path(name).stem) + ".map.bin"
                        raw_path = tex_dir / raw_name
                        if payload:
                            raw_path.write_bytes(payload)
                            out_rel = "terrain_obj/textures/" + raw_name
                            status = "exported_raw"
                            evidence += ";direct_map_decode_failed_raw_copy"
                        else:
                            status = "not_exported"
                else:
                    out_rel = geo_module.export_texture_for_asset(embedded_index.resolver_module, embedded_index.resolver_index, asset, tex_dir, written, palette_rgb, vqm_layout)
                    # export_texture_for_asset returns textures/foo.png relative to its tex_dir parent.
                    out_rel = "terrain_obj/" + out_rel if not out_rel.startswith("terrain_obj/") else out_rel
                    status = "exported"
            except Exception as e:
                err = f"{type(e).__name__}:{e}"
                warnings.append(f"terrain_candidate_texture_export_failed:{name}:{err}")
        rows.append({
            "mission": mission,
            "token": str(r.get("token", "") or name),
            "normalized_name": name,
            "resource_role": role,
            "candidate_priority": terrain_candidate_priority(role, name),
            "asset_name": str(getattr(asset, "name", "") or "") if asset is not None else "",
            "asset_id": str(getattr(asset, "asset_id", "") or "") if asset is not None else "",
            "asset_ext": str(getattr(asset, "ext", "") or "") if asset is not None else "",
            "texture_probe_name": probe,
            "palette_name": str(palette_by_mission.get(mission, {}).get("palette_name", "") or ""),
            "palette_path": str(palette_by_mission.get(mission, {}).get("palette_path", "") or ""),
            "palette_source": str(palette_by_mission.get(mission, {}).get("palette_source", "") or ""),
            "palette_scale": str(palette_by_mission.get(mission, {}).get("palette_scale", "") or ""),
            "status": status,
            "output_relpath": out_rel,
            "evidence": evidence,
            "error": err,
            "note": "Mission-level terrain/environment texture candidate exported for visual inspection only; not yet bound to TER surface class.",
        })
    return rows, warnings



def export_terrain_palette_variants(out_dir: Path, terrain_texture_rows: List[dict], resource_rows: List[dict], file_index: Dict[str, List[Path]], embedded_index: EmbeddedAssetIndex, geo_module: Any, palette_selection_rows: List[dict], global_palette_file: Optional[Path], global_palette_scale: str, terrain_palette_file: Optional[Path], terrain_palette_scale: str, vqm_layout: str, palette_sweep: str = "all-act", palette_sweep_globs: Optional[List[str]] = None, palette_sweep_limit: int = 256) -> Tuple[List[dict], List[str]]:
    """Export side-by-side palette variants for terrain/environment candidates.

    This is intentionally diagnostic.  v27 could select the mission ACT, but visual output can still
    look identical/wrong if the candidate texture needs a different palette family, if the ACT is not
    actually the texture palette, or if the decoded payload is not the true terrain texel source.  This
    function writes comparison PNGs using every plausible palette context we can identify so the user can
    visually pick the correct palette before we encode another assumption. v31 expands this to an optional sweep across ACT files in the resource index, because terrain/environment textures may use palette contexts that are not literal mission ACT references.
    """
    warnings: List[str] = []
    rows: List[dict] = []
    if geo_module is None:
        return rows, ["geo_exporter_unavailable_for_terrain_palette_variants"]
    if embedded_index.resolver_index is None or embedded_index.resolver_module is None:
        return rows, ["embedded_resolver_unavailable_for_terrain_palette_variants"]
    if not hasattr(geo_module, "export_texture_for_asset"):
        return rows, ["geo_exporter_lacks_export_texture_for_asset"]

    palette_by_mission = _palette_selection_by_mission(palette_selection_rows)
    palette_cache: Dict[Tuple[str, str], Any] = {}

    def load_palette(path_s: str, scale: str):
        if not path_s:
            return None
        key = (path_s, scale or "auto")
        if key in palette_cache:
            return palette_cache[key]
        try:
            pal = geo_module.load_palette_file(Path(path_s), scale or "auto") if hasattr(geo_module, "load_palette_file") else None
            palette_cache[key] = pal
            return pal
        except Exception as e:
            warnings.append(f"terrain_palette_variant_load_failed:{path_s}:{e}")
            palette_cache[key] = None
            return None

    def add_variant(variants: List[dict], seen: set, source: str, name: str, path_s: str, scale: str, note: str):
        key = (source, path_s or "", scale or "auto", name or "")
        if key in seen:
            return
        seen.add(key)
        variants.append({
            "palette_variant_source": source,
            "palette_name": name or (Path(path_s).name if path_s else "none"),
            "palette_path": path_s or "",
            "palette_scale": scale or "auto",
            "note": note,
        })

    def all_act_palette_paths_for_sweep() -> List[Path]:
        out: List[Path] = []
        if palette_sweep == "none":
            return out
        globs = palette_sweep_globs or []
        if palette_sweep == "glob" and not globs:
            globs = ["*.act"]
        for key, paths in sorted(file_index.items()):
            if not key.lower().endswith(".act"):
                continue
            if palette_sweep == "glob":
                if not any(fnmatch.fnmatch(key.lower(), g.lower()) for g in globs):
                    continue
            for p in paths:
                if p not in out:
                    out.append(p)
                    if len(out) >= max(0, palette_sweep_limit):
                        return out
        return out

    act_sweep_paths = all_act_palette_paths_for_sweep()

    # Texture rows are already resolved by export_terrain_candidate_textures; rerun the asset resolver
    # so variants are independent of the primary export path.
    primary_rows = [r for r in terrain_texture_rows if str(r.get("status", "")) == "exported" and str(r.get("asset_name", ""))]
    primary_rows.sort(key=lambda r: (str(r.get("mission", "")), int(str(r.get("candidate_priority", "99")) or 99), str(r.get("normalized_name", ""))))

    for tr in primary_rows:
        mission = str(tr.get("mission", "") or "")
        name = str(tr.get("normalized_name", "") or "")
        role = str(tr.get("resource_role", "") or "")
        if not mission or not name:
            continue
        asset, probe, evidence = resolve_texture_asset_object(name, embedded_index)
        if asset is not None and str(getattr(asset, "ext", "")).lower() == "map":
            stem = str(getattr(asset, "stem", "") or Path(name).stem).upper()
            idx = embedded_index.resolver_index
            for ext in ("m16", "vqm"):
                alt = idx.resolve(stem, ext, source=asset) if idx is not None else None
                if alt is not None:
                    asset = alt
                    evidence += f";map_to_{ext}"
                    break
        if asset is None:
            continue

        variants: List[dict] = []
        seen_variants: set = set()
        sel = palette_by_mission.get(mission, {})
        add_variant(variants, seen_variants, "selected_terrain_palette", str(sel.get("palette_name", "") or ""), str(sel.get("palette_path", "") or ""), str(sel.get("palette_scale", "auto") or "auto"), "palette selected by terrain palette mode")
        if global_palette_file is not None:
            add_variant(variants, seen_variants, "global_static_palette", global_palette_file.name, str(global_palette_file), global_palette_scale, "current --palette-file used for static/object textures")
        if terrain_palette_file is not None:
            add_variant(variants, seen_variants, "explicit_terrain_palette", terrain_palette_file.name, str(terrain_palette_file), terrain_palette_scale, "explicit --terrain-palette-file")
        # Add every literal ACT reference in this mission, not just the selected one.  This catches cases
        # where the first ACT in the mission header is a color context but not the terrain texture palette.
        act_rows = [r for r in resource_rows if str(r.get("mission", "")) == mission and str(r.get("ext", "")).lower() == "act" and str(r.get("found_file", "")).lower() == "true" and str(r.get("first_file_path", ""))]
        act_rows.sort(key=lambda r: (int(str(r.get("offset_hex", "0x0")), 16) if str(r.get("offset_hex", "")).startswith("0x") else 0, str(r.get("normalized_name", ""))))
        for ar in act_rows:
            add_variant(variants, seen_variants, "mission_literal_act", str(ar.get("normalized_name", "") or Path(str(ar.get("first_file_path", ""))).name), str(ar.get("first_file_path", "") or ""), terrain_palette_scale, f"literal ACT at {ar.get('offset_hex','')}")
        for p in act_sweep_paths:
            add_variant(variants, seen_variants, "resource_act_sweep", p.name, str(p), terrain_palette_scale, f"ACT palette from resource index sweep mode={palette_sweep}")
        add_variant(variants, seen_variants, "no_palette_debug", "no_palette", "", "auto", "decoder fallback/no palette variant")

        for v in variants:
            source = str(v.get("palette_variant_source", ""))
            palette_name = str(v.get("palette_name", "") or "none")
            palette_path = str(v.get("palette_path", "") or "")
            palette_scale = str(v.get("palette_scale", "auto") or "auto")
            texture_stem = safe_name(Path(name).stem.upper())
            variant_slug = safe_name(source + "_" + palette_name).lower()
            tex_dir = out_dir / "terrain_obj" / "palette_variants" / texture_stem / variant_slug
            tex_dir.mkdir(parents=True, exist_ok=True)
            status = "not_exported"
            out_rel = ""
            err = ""
            try:
                palette_rgb = load_palette(palette_path, palette_scale) if palette_path else None
                if str(getattr(asset, "ext", "")).lower() == "map":
                    payload = terrain_asset_payload(asset, embedded_index)
                    out_name = safe_name(Path(name).stem.upper()) + ".png"
                    out_path = tex_dir / out_name
                    ok, decode_kind, direct_err = export_direct_map_payload_png(payload or b"", out_path, palette_rgb)
                    if ok:
                        out_rel = str((Path("terrain_obj") / "palette_variants" / texture_stem / variant_slug / out_name).as_posix())
                        status = "exported"
                        evidence += ";" + decode_kind
                    else:
                        err = direct_err
                        if payload:
                            raw_name = safe_name(Path(name).stem) + ".map.bin"
                            (tex_dir / raw_name).write_bytes(payload)
                            out_rel = str((Path("terrain_obj") / "palette_variants" / texture_stem / variant_slug / raw_name).as_posix())
                            status = "exported_raw"
                else:
                    local_written: Dict[str, str] = {}
                    rel = geo_module.export_texture_for_asset(embedded_index.resolver_module, embedded_index.resolver_index, asset, tex_dir, local_written, palette_rgb, vqm_layout)
                    out_rel = str((Path("terrain_obj") / "palette_variants" / texture_stem / variant_slug / Path(rel).name).as_posix())
                    status = "exported"
            except Exception as e:
                err = f"{type(e).__name__}:{e}"
                warnings.append(f"terrain_palette_variant_export_failed:{mission}:{name}:{palette_name}:{err}")
            rows.append({
                "mission": mission,
                "texture_name": name,
                "resource_role": role,
                "asset_name": str(getattr(asset, "name", "") or ""),
                "asset_id": str(getattr(asset, "asset_id", "") or ""),
                "asset_ext": str(getattr(asset, "ext", "") or ""),
                "texture_probe_name": probe,
                "palette_variant_source": source,
                "palette_name": palette_name,
                "palette_path": palette_path,
                "palette_scale": palette_scale,
                "status": status,
                "output_relpath": out_rel,
                "evidence": evidence,
                "error": err,
                "note": str(v.get("note", "")),
            })
    return rows, warnings


def _safe_read_small_file(path_text: str, limit: int = 65536) -> Optional[bytes]:
    if not path_text:
        return None
    try:
        p = Path(path_text)
        if not p.exists() or not p.is_file():
            return None
        with p.open('rb') as f:
            return f.read(limit)
    except Exception:
        return None


def _payload_ascii_tokens(payload: Optional[bytes], max_tokens: int = 16) -> str:
    if not payload:
        return ""
    toks = []
    for m in ASCII_TOKEN_RE.finditer(payload[:4096]):
        try:
            t = m.group(0).decode('ascii', errors='ignore')
        except Exception:
            continue
        if t and t not in toks:
            toks.append(t)
        if len(toks) >= max_tokens:
            break
    return ";".join(toks)


def _payload_header_summary(payload: Optional[bytes]) -> dict:
    if payload is None:
        return {
            "payload_size": 0,
            "payload_sha256_12": "",
            "first32_hex": "",
            "first4_ascii": "",
            "u16_0": "",
            "u16_2": "",
            "u32_0": "",
            "u32_4": "",
            "ascii_tokens": "",
            "contains_resource_strings": "false",
        }
    first = payload[:32]
    def u16_at(off: int) -> str:
        return str(struct.unpack_from('<H', payload, off)[0]) if len(payload) >= off + 2 else ""
    def u32_at(off: int) -> str:
        return str(struct.unpack_from('<I', payload, off)[0]) if len(payload) >= off + 4 else ""
    toks = _payload_ascii_tokens(payload)
    contains_resource = any(tok.lower().endswith(('.m16', '.vqm', '.tmt', '.map', '.cbk', '.act', '.tbl', '.lum')) for tok in toks.split(';') if tok)
    first4 = ''.join(chr(b) if 32 <= b < 127 else '.' for b in payload[:4])
    return {
        "payload_size": len(payload),
        "payload_sha256_12": hashlib.sha256(payload).hexdigest()[:12],
        "first32_hex": first.hex(),
        "first4_ascii": first4,
        "u16_0": u16_at(0),
        "u16_2": u16_at(2),
        "u32_0": u32_at(0),
        "u32_4": u32_at(4),
        "ascii_tokens": toks,
        "contains_resource_strings": "true" if contains_resource else "false",
    }


def _embedded_payload_for_hit(embedded_index: EmbeddedAssetIndex, hit: EmbeddedAssetRef) -> Optional[bytes]:
    if hit is None:
        return None
    return embedded_index.payloads.get(hit.asset_id)


def _first_embedded_hit_for_name(embedded_index: EmbeddedAssetIndex, name: str, wanted_ext: Optional[str] = None) -> Optional[EmbeddedAssetRef]:
    hits = embedded_index.all_hits(name)
    if wanted_ext:
        wanted_ext = wanted_ext.lower().lstrip('.')
        hits = [h for h in hits if h.ext.lower().lstrip('.') == wanted_ext]
    return hits[0] if hits else None


def _file_payload_for_name(file_index: Dict[str, List[Path]], name: str) -> Tuple[Optional[bytes], str]:
    hits = file_index.get((name or '').lower()) or []
    for h in hits:
        payload = _safe_read_small_file(str(h))
        if payload is not None:
            return payload, str(h)
    return None, ""


def infer_map_probe_kind(row: dict) -> str:
    ext = str(row.get('direct_ext', '') or '').lower()
    direct_size = int(row.get('direct_payload_size', 0) or 0)
    m16_found = str(row.get('sibling_m16_found', '')).lower() == 'true'
    vqm_found = str(row.get('sibling_vqm_found', '')).lower() == 'true'
    tmt_found = str(row.get('sibling_tmt_found', '')).lower() == 'true'
    contains_strings = str(row.get('direct_contains_resource_strings', '')).lower() == 'true'
    if ext != 'map':
        return 'not_direct_map_asset'
    if m16_found or vqm_found:
        return 'map_with_decodable_sibling_image'
    if tmt_found:
        return 'map_with_sibling_tmt_material_table'
    if contains_strings:
        return 'map_wrapper_or_descriptor_with_strings'
    if 0 < direct_size <= 512:
        return 'small_map_descriptor_or_index'
    if direct_size > 512:
        return 'raw_map_payload_or_unknown_table'
    return 'map_missing_payload'


def build_terrain_map_probe_rows(resource_rows: List[dict], file_index: Dict[str, List[Path]], embedded_index: EmbeddedAssetIndex) -> List[dict]:
    """Probe literal mission MAP candidates without assuming they are directly decodable textures.

    miss8 M06 points at TT181SD_.MAP/NK_1CLD2.MAP, while miss16 M06 points at
    TP051DR6.MAP/NK_6CLDE.MAP.  Some MAP names resolve cleanly to sibling M16/VQM assets;
    others appear to be MAP payloads that need a dedicated terrain/map decoder.  This table
    captures enough header/payload/sibling evidence to choose the next parser target.
    """
    rows: List[dict] = []
    seen = set()
    for rr in resource_rows:
        mission = str(rr.get('mission', '') or '')
        name = str(rr.get('normalized_name', '') or '')
        ext = str(rr.get('ext', '') or '').lower()
        role = str(rr.get('resource_role', '') or '')
        if not mission or not name or ext != 'map':
            continue
        # Keep all literal MAP references, but prioritize terrain/environment roles in the row fields.
        key = (mission, name.lower(), str(rr.get('offset_hex', '') or ''))
        if key in seen:
            continue
        seen.add(key)
        stem = Path(name).stem
        lower_name = name.lower()
        direct_hit = _first_embedded_hit_for_name(embedded_index, name, 'map')
        direct_payload = _embedded_payload_for_hit(embedded_index, direct_hit) if direct_hit else None
        direct_source = 'embedded' if direct_payload is not None else ''
        direct_asset_id = direct_hit.asset_id if direct_hit else ''
        direct_asset_name = direct_hit.name if direct_hit else ''
        direct_ext = direct_hit.ext if direct_hit else ''
        if direct_payload is None:
            direct_payload, file_path = _file_payload_for_name(file_index, name)
            if direct_payload is not None:
                direct_source = 'filesystem'
                direct_asset_name = name
                direct_ext = 'map'
                direct_asset_id = file_path
        direct_summary = _payload_header_summary(direct_payload)

        sibling_bits: Dict[str, Any] = {}
        sibling_notes: List[str] = []
        for sib_ext in ('m16', 'vqm', 'tmt', 'cbk', 'map'):
            sib_name = f"{stem}.{sib_ext}"
            sib_hit = _first_embedded_hit_for_name(embedded_index, sib_name, sib_ext)
            sib_payload = _embedded_payload_for_hit(embedded_index, sib_hit) if sib_hit else None
            sib_source = 'embedded' if sib_payload is not None else ''
            sib_asset_id = sib_hit.asset_id if sib_hit else ''
            sib_asset_name = sib_hit.name if sib_hit else ''
            if sib_payload is None:
                fp, fpath = _file_payload_for_name(file_index, sib_name)
                if fp is not None:
                    sib_payload = fp
                    sib_source = 'filesystem'
                    sib_asset_id = fpath
                    sib_asset_name = sib_name
            summ = _payload_header_summary(sib_payload)
            prefix = f'sibling_{sib_ext}'
            found = sib_payload is not None
            sibling_bits[f'{prefix}_found'] = 'true' if found else 'false'
            sibling_bits[f'{prefix}_source'] = sib_source
            sibling_bits[f'{prefix}_asset_name'] = sib_asset_name
            sibling_bits[f'{prefix}_asset_id'] = sib_asset_id
            sibling_bits[f'{prefix}_payload_size'] = summ['payload_size']
            sibling_bits[f'{prefix}_sha256_12'] = summ['payload_sha256_12']
            sibling_bits[f'{prefix}_first4_ascii'] = summ['first4_ascii']
            if found:
                sibling_notes.append(f'{sib_ext}:{sib_source}:{summ["payload_size"]}')

        row = {
            'mission': mission,
            'offset_hex': str(rr.get('offset_hex', '') or ''),
            'token': str(rr.get('token', '') or name),
            'normalized_name': name,
            'stem': stem,
            'resource_role': role,
            'found_file': str(rr.get('found_file', '') or ''),
            'found_embedded': str(rr.get('found_embedded', '') or ''),
            'direct_asset_name': direct_asset_name,
            'direct_asset_id': direct_asset_id,
            'direct_source': direct_source,
            'direct_ext': direct_ext,
            'direct_payload_size': direct_summary['payload_size'],
            'direct_sha256_12': direct_summary['payload_sha256_12'],
            'direct_first32_hex': direct_summary['first32_hex'],
            'direct_first4_ascii': direct_summary['first4_ascii'],
            'direct_u16_0': direct_summary['u16_0'],
            'direct_u16_2': direct_summary['u16_2'],
            'direct_u32_0': direct_summary['u32_0'],
            'direct_u32_4': direct_summary['u32_4'],
            'direct_ascii_tokens': direct_summary['ascii_tokens'],
            'direct_contains_resource_strings': direct_summary['contains_resource_strings'],
            **sibling_bits,
            'sibling_summary': ';'.join(sibling_notes),
            'inferred_map_kind': '',
            'note': 'MAP probe row; use to determine whether terrain MAP is a direct image, sibling image indirection, or wrapper/table',
        }
        row['inferred_map_kind'] = infer_map_probe_kind(row)
        rows.append(row)
    rows.sort(key=lambda r: (str(r.get('mission', '')), terrain_candidate_priority(str(r.get('resource_role', '')), str(r.get('normalized_name', ''))), str(r.get('normalized_name', '')), str(r.get('offset_hex', ''))))
    return rows

def build_terrain_surface_texture_hypotheses(surface_inference_rows: List[dict], terrain_texture_rows: List[dict]) -> List[dict]:
    """Join inferred TER classes to mission-level texture candidates without asserting final binding."""
    textures_by_mission: Dict[str, List[dict]] = {}
    for r in terrain_texture_rows:
        textures_by_mission.setdefault(str(r.get("mission", "")), []).append(r)
    rows: List[dict] = []
    for s in surface_inference_rows:
        mission = str(s.get("mission", ""))
        sc = int(s.get("surface_class", 0) or 0)
        role = str(s.get("inferred_surface_role", "") or "")
        candidates = textures_by_mission.get(mission, [])
        terrain_candidates = [c for c in candidates if str(c.get("resource_role", "")) == "terrain_surface_texture_candidate"]
        env_candidates = [c for c in candidates if str(c.get("resource_role", "")) == "sky_or_environment_texture_candidate"]
        # Conservative ranking: road-like classes get terrain surface candidates, base gets no direct claim,
        # environment candidates remain listed separately for sky/backdrop work.
        if role in {"road_surface_candidate", "roadbed_or_shoulder_candidate", "secondary_ground_or_pad_candidate"}:
            selected = terrain_candidates[:3]
        elif role == "base_ground_candidate":
            selected = terrain_candidates[:3]
        else:
            selected = terrain_candidates[:3]
        if not selected:
            selected = candidates[:3]
        rows.append({
            "mission": mission,
            "surface_class": sc,
            "inferred_surface_role": role,
            "surface_confidence": str(s.get("confidence", "")),
            "runtime_forced_split": str(s.get("runtime_forced_split", "")),
            "rseg_centerline_percent": str(s.get("rseg_centerline_percent", "")),
            "rseg_edge_average_percent": str(s.get("rseg_edge_average_percent", "")),
            "candidate_texture_names": ";".join(str(c.get("normalized_name", "")) for c in selected),
            "candidate_texture_outputs": ";".join(str(c.get("output_relpath", "")) for c in selected),
            "environment_texture_names": ";".join(str(c.get("normalized_name", "")) for c in env_candidates[:3]),
            "binding_confidence": "evidence_only_unproven_runtime_binding",
            "note": "Hypothesis table only: TER surface class roles are inferred; texture candidates are mission-level strings/previews, not proven per-class bindings.",
        })
    return rows


def rewrite_terrain_mtls_with_candidate_comments(out_dir: Path, terrain_texture_rows: List[dict], hypothesis_rows: List[dict]) -> int:
    """Append candidate texture comments to terrain MTL files; does not add map_Kd."""
    by_mission: Dict[str, List[dict]] = {}
    for r in hypothesis_rows:
        by_mission.setdefault(str(r.get("mission", "")).lower(), []).append(r)
    changed = 0
    for mission, rows in by_mission.items():
        mtl_path = out_dir / "terrain_obj" / f"{mission}.terrain_dense.mtl"
        if not mtl_path.exists():
            continue
        text = mtl_path.read_text(encoding="utf-8")
        if "# v26 terrain texture candidate notes" in text:
            continue
        lines = text.rstrip().splitlines()
        lines.append("")
        lines.append("# v26 terrain texture candidate notes")
        lines.append("# These are NOT final map_Kd bindings; they preserve mission-level texture evidence.")
        for r in rows:
            lines.append(f"# surface_class {r.get('surface_class')} role={r.get('inferred_surface_role')} candidates={r.get('candidate_texture_names')} outputs={r.get('candidate_texture_outputs')}")
        mtl_path.write_text("\n".join(lines) + "\n", encoding="utf-8")
        changed += 1
    return changed



def _terrain_texture_rel_for_mtl(output_relpath: str) -> str:
    """Convert terrain_obj/textures/foo.png to a map_Kd path relative to terrain_obj/*.mtl."""
    rel = str(output_relpath or "").replace('\\', '/')
    if rel.startswith('terrain_obj/'):
        return rel[len('terrain_obj/'):]
    return rel


def bind_terrain_candidate_textures(out_dir: Path,
                                    terrain_texture_rows: List[dict],
                                    hypothesis_rows: List[dict],
                                    mode: str = "evidence-single") -> Tuple[int, List[dict]]:
    """Experimentally inject map_Kd for mission-level terrain texture candidates.

    This deliberately preserves the existing terrain_surface_N material names and Kd
    diagnostic colors.  It only adds map_Kd lines, and records that the binding is
    experimental/evidence-single, not runtime-proven per-surface attribution.
    """
    by_mission_all: Dict[str, List[dict]] = {}
    by_mission_terrain: Dict[str, List[dict]] = {}
    for r in terrain_texture_rows:
        mission = str(r.get('mission', '') or '').lower()
        if not mission:
            continue
        if str(r.get('status', '')) not in {'exported', 'exported_raw'}:
            continue
        if not str(r.get('output_relpath', '') or ''):
            continue
        role = str(r.get('resource_role', ''))
        by_mission_all.setdefault(mission, []).append(r)
        if role == 'terrain_surface_texture_candidate':
            by_mission_terrain.setdefault(mission, []).append(r)
    # v32: miss8 M06's TT181SD_.MAP is a direct MAP image but is only classified as
    # texture_or_material_candidate by the broad mission-string classifier.  If a mission has no
    # explicit terrain_surface_texture_candidate, fall back to the lowest-priority non-sky MAP/M16/VQM
    # candidate so it can be visually bound for inspection.
    by_mission: Dict[str, List[dict]] = {}
    for mission, rows in by_mission_all.items():
        terrain_rows = by_mission_terrain.get(mission, [])
        if terrain_rows:
            by_mission[mission] = terrain_rows
        else:
            by_mission[mission] = [r for r in rows if str(r.get('resource_role','')) != 'sky_or_environment_texture_candidate']

    hyp_by_mission: Dict[str, List[dict]] = {}
    for h in hypothesis_rows:
        mission = str(h.get('mission', '') or '').lower()
        if mission:
            hyp_by_mission.setdefault(mission, []).append(h)

    changed = 0
    binding_rows: List[dict] = []
    for mission, candidates in sorted(by_mission.items()):
        candidates = sorted(candidates, key=lambda r: (int(r.get('candidate_priority', 999) or 999), str(r.get('normalized_name',''))))
        if not candidates:
            continue
        chosen = candidates[0]
        map_kd = _terrain_texture_rel_for_mtl(str(chosen.get('output_relpath', '') or ''))
        if not map_kd:
            continue
        mtl_path = out_dir / 'terrain_obj' / f'{mission}.terrain_dense.mtl'
        if not mtl_path.exists():
            continue

        surface_classes: List[int] = []
        for h in hyp_by_mission.get(mission, []):
            try:
                sc = int(h.get('surface_class', 0) or 0) & 0x7
            except Exception:
                continue
            role = str(h.get('inferred_surface_role', '') or '')
            if mode == 'road-surfaces-only' and role not in {'road_surface_candidate', 'roadbed_or_shoulder_candidate'}:
                continue
            surface_classes.append(sc)
        if not surface_classes:
            # Fall back to all material declarations present in the MTL.
            txt = mtl_path.read_text(encoding='utf-8')
            for line in txt.splitlines():
                if line.startswith('newmtl terrain_surface_'):
                    try:
                        surface_classes.append(int(line.rsplit('_', 1)[1]) & 0x7)
                    except Exception:
                        pass
        surface_set = set(surface_classes)

        old_lines = mtl_path.read_text(encoding='utf-8').splitlines()
        new_lines: List[str] = []
        current_surface = None
        saw_map_for_current = False
        inserted_any = False
        for line in old_lines:
            if line.startswith('newmtl '):
                # finalize previous material before starting next if needed after Ks/etc is not reliable,
                # so insertion is done immediately after Ks below.
                current_surface = None
                saw_map_for_current = False
                if line.startswith('newmtl terrain_surface_'):
                    try:
                        current_surface = int(line.rsplit('_', 1)[1]) & 0x7
                    except Exception:
                        current_surface = None
            if current_surface is not None and line.strip().startswith('map_Kd '):
                saw_map_for_current = True
            new_lines.append(line)
            if current_surface in surface_set and line.startswith('Ks ') and not saw_map_for_current:
                new_lines.append(f'# v26 experimental terrain candidate binding: {chosen.get("normalized_name")} -> {chosen.get("asset_name")}')
                new_lines.append(f'map_Kd {map_kd}')
                inserted_any = True
                saw_map_for_current = True
        if inserted_any:
            mtl_path.write_text('\n'.join(new_lines) + '\n', encoding='utf-8')
            changed += 1
        for sc in sorted(surface_set):
            binding_rows.append({
                'mission': mission,
                'surface_class': sc,
                'material_key': terrain_surface_material_name(sc),
                'binding_mode': mode,
                'texture_name': str(chosen.get('normalized_name','')),
                'asset_name': str(chosen.get('asset_name','')),
                'texture_probe_name': str(chosen.get('texture_probe_name','')),
                'map_kd': map_kd,
                'mtl_path': str(mtl_path),
                'status': 'bound' if inserted_any else 'already_bound_or_no_change',
                'confidence': 'experimental_evidence_single_not_runtime_proven',
                'note': 'map_Kd binding is for visual validation only; TER surface-class to texture rule is not yet proven.',
            })
    return changed, binding_rows

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

def terrain_surface_rgb(surface_class: int, style: str = "natural") -> Tuple[float, float, float]:
    # Diagnostic material colors only.  The runtime encodes the terrain surface
    # class as TER word >> 13; this is not yet a literal ground texture binding.
    #
    # v23 adds a high-contrast option because the natural/brown palette can be
    # too subtle in Blender and can look as though no material was applied.
    natural = {
        0: (0.48, 0.42, 0.30),
        1: (0.36, 0.31, 0.22),
        2: (0.62, 0.55, 0.38),
        3: (0.30, 0.30, 0.30),
        4: (0.55, 0.47, 0.33),
        5: (0.22, 0.28, 0.18),
        6: (0.18, 0.22, 0.26),
        7: (0.70, 0.66, 0.50),
    }
    high_contrast = {
        0: (0.85, 0.85, 0.85),  # default/low-priority
        1: (0.45, 0.30, 0.12),  # dominant ground
        2: (1.00, 0.80, 0.00),
        3: (0.90, 0.10, 0.10),  # runtime forced split
        4: (0.80, 0.00, 0.80),
        5: (0.05, 0.75, 0.10),  # distinct non-forced bucket
        6: (0.00, 0.60, 1.00),
        7: (0.05, 0.05, 1.00),  # runtime forced split
    }
    palette = high_contrast if style == "high-contrast" else natural
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


def write_terrain_obj_with_surface_materials(path: Path, vertices: List[Tuple[float, float, float]], faces: List[Tuple[int, ...]], face_surfaces: List[int], obj_coordinates: str, write_normals: bool, terrain_material_style: str = "natural", header: str = "", write_uvs: bool = False, uv_mode: str = "whole-terrain", uv_repeat: float = 1.0) -> Tuple[dict, List[dict]]:
    path.parent.mkdir(parents=True, exist_ok=True)
    normals = compute_normals(vertices, faces) if write_normals and faces else []
    mtl_path = path.with_suffix('.mtl')
    counts: Dict[int, int] = {}
    for sc in face_surfaces:
        counts[int(sc) & 0x7] = counts.get(int(sc) & 0x7, 0) + 1
    with mtl_path.open('w', encoding='utf-8') as mtl:
        mtl.write('# Interstate 76 terrain surface-class diagnostic materials v23\n')
        mtl.write('# These are TER word>>13 surface classes, not final DIVER/PAL texture bindings yet.\n\n')
        for sc in sorted(counts):
            r, g, b = terrain_surface_rgb(sc, terrain_material_style)
            mtl.write(f"newmtl {terrain_surface_material_name(sc)}\nKd {r:.6f} {g:.6f} {b:.6f}\nKa 0 0 0\nKs 0 0 0\n\n")
    texcoords: List[Tuple[float, float]] = []
    if write_uvs and vertices:
        xs = [float(v[0]) for v in vertices]
        zs = [float(v[1]) for v in vertices]
        min_x, max_x = min(xs), max(xs)
        min_z, max_z = min(zs), max(zs)
        span_x = max(max_x - min_x, 1.0)
        span_z = max(max_z - min_z, 1.0)
        rep = float(uv_repeat) if uv_repeat else 1.0
        for x, z, _h in vertices:
            if uv_mode == "world-repeat":
                # Repeat once per 128 terrain sample units by default.  This is
                # diagnostic, but useful for seeing whether a candidate tile is
                # plausible without stretching it across the entire mission.
                u = (float(x) / 128.0) * rep
                v = (float(z) / 128.0) * rep
            else:
                # Whole-terrain mode maps the candidate image once over the
                # emitted dense terrain bounds.  For direct 128x128 MAP payloads
                # this is currently the most conservative validation UV model.
                u = ((float(x) - min_x) / span_x) * rep
                v = ((float(z) - min_z) / span_z) * rep
            texcoords.append((u, 1.0 - v))
    with path.open('w', encoding='utf-8') as f:
        f.write(header)
        f.write(f"mtllib {mtl_path.name}\n")
        for x, z, h in vertices:
            vx, vy, vz = obj_vertex_coords(x, z, h, obj_coordinates)
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")
        for u, v in texcoords:
            f.write(f"vt {u:.8f} {v:.8f}\n")
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
            if normals and texcoords:
                f.write("f " + " ".join(f"{idx}/{idx}/{idx}" for idx in face) + "\n")
            elif normals:
                f.write("f " + " ".join(f"{idx}//{idx}" for idx in face) + "\n")
            elif texcoords:
                f.write("f " + " ".join(f"{idx}/{idx}" for idx in face) + "\n")
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
    return {"path": str(path), "vertices": len(vertices), "faces": len(faces), "write_normals": bool(normals), "texcoords": len(texcoords), "write_uvs": bool(write_uvs), "uv_mode": uv_mode if write_uvs else "", "uv_repeat": float(uv_repeat) if write_uvs else 0.0, "mtl_path": str(mtl_path), "surface_materials": len(counts), "terrain_material_style": terrain_material_style}, rows



def terrain_surface_candidate_role(surface_class: int, face_count: int, total_faces: int) -> str:
    """Best-effort terrain attribution label.

    This deliberately stays conservative: these labels describe the encoded terrain
    bucket and runtime behavior, not final art texture names.
    """
    sc = int(surface_class) & 0x7
    pct = (float(face_count) / float(total_faces)) if total_faces else 0.0
    if sc == 1 and pct > 0.50:
        return "dominant_base_ground_candidate"
    if sc == 0:
        return "low_or_default_ground_candidate"
    if sc == 5:
        return "distinct_non_forced_ground_candidate"
    if terrain_surface_runtime_forced_split(sc):
        return "runtime_special_surface_candidate"
    return "unclassified_terrain_surface_candidate"


def build_terrain_surface_region_rows(rt: RuntimeTerrain, mission_name: str, boundary_sampling: str) -> List[dict]:
    """Build 4-connected terrain surface-class regions over dense terrain faces.

    Coordinates are face/sample based; world bounds use the same origin and sample scale as
    dense terrain export.  This is intended to help determine whether TER high-bit classes
    correspond to roads, shoulders, rock, water/hazard, or other logical regions.
    """
    used = set((x, z) for x, z, _ in rt.zmap.used_cells())
    if not used:
        return []

    # Build face surface map for all active ZMAP pages.
    face_surface: Dict[Tuple[int, int], int] = {}
    for cell_x, cell_z, _page in rt.zmap.used_cells():
        base_x = cell_x * PAGE_W
        base_z = cell_z * PAGE_H
        for lz in range(PAGE_H):
            for lx in range(PAGE_W):
                sx = base_x + lx
                sz = base_z + lz
                face_surface[(sx, sz)] = int(rt.surface_class(sx, sz)) & 0x7

    total_faces = len(face_surface)
    visited = set()
    rows: List[dict] = []
    region_seq_by_surface: Dict[int, int] = {}

    for start, sc in sorted(face_surface.items(), key=lambda kv: (kv[1], kv[0][1], kv[0][0])):
        if start in visited:
            continue
        region_seq_by_surface[sc] = region_seq_by_surface.get(sc, 0) + 1
        region_id = region_seq_by_surface[sc]

        q = [start]
        visited.add(start)
        qi = 0
        count = 0
        sx_min = sx_max = start[0]
        sz_min = sz_max = start[1]
        h_min = 1e30
        h_max = -1e30
        h_sum = 0.0
        while qi < len(q):
            sx, sz = q[qi]
            qi += 1
            count += 1
            sx_min = min(sx_min, sx)
            sx_max = max(sx_max, sx)
            sz_min = min(sz_min, sz)
            sz_max = max(sz_max, sz)
            h = rt.height_world(sx, sz)
            h_min = min(h_min, h)
            h_max = max(h_max, h)
            h_sum += h
            for nx, nz in ((sx - 1, sz), (sx + 1, sz), (sx, sz - 1), (sx, sz + 1)):
                key = (nx, nz)
                if key in visited:
                    continue
                if face_surface.get(key) != sc:
                    continue
                visited.add(key)
                q.append(key)

        wx_min, wz_min = rt.world_xz(sx_min, sz_min)
        wx_max, wz_max = rt.world_xz(sx_max + 1, sz_max + 1)
        if wx_min > wx_max:
            wx_min, wx_max = wx_max, wx_min
        if wz_min > wz_max:
            wz_min, wz_max = wz_max, wz_min
        wx_center = (wx_min + wx_max) * 0.5
        wz_center = (wz_min + wz_max) * 0.5
        pct = (100.0 * count / total_faces) if total_faces else 0.0
        rows.append({
            "mission": mission_name,
            "surface_class": sc,
            "region_id": region_id,
            "face_count": count,
            "percent_of_mission_faces": f"{pct:.6f}",
            "sample_x_min": sx_min,
            "sample_x_max": sx_max,
            "sample_z_min": sz_min,
            "sample_z_max": sz_max,
            "world_x_min": f"{wx_min:.6f}",
            "world_x_max": f"{wx_max:.6f}",
            "world_z_min": f"{wz_min:.6f}",
            "world_z_max": f"{wz_max:.6f}",
            "world_x_center": f"{wx_center:.6f}",
            "world_z_center": f"{wz_center:.6f}",
            "height_min": f"{h_min:.6f}",
            "height_max": f"{h_max:.6f}",
            "height_avg": f"{(h_sum / count) if count else 0.0:.6f}",
            "runtime_forced_split": terrain_surface_runtime_forced_split(sc),
            "diagnostic_role": terrain_surface_diagnostic_role(sc),
            "candidate_role": terrain_surface_candidate_role(sc, count, total_faces),
            "note": terrain_surface_notes(sc),
        })
    return rows


def terrain_surface_role_from_evidence(sc: int, face_pct: float, center_pct: float, edge_pct: float, forced: bool,
                                       dominant_adjacent_surface: str = "", dominant_adjacent_percent: float = 0.0) -> Tuple[str, str, str]:
    """Evidence-ranked human role labels for diagnostic terrain surface classes.

    These are not final material names.  They are deliberately phrased as candidates.
    """
    if center_pct >= 50.0:
        return (
            "road_surface_candidate",
            "high_rseg_centerline_and_edge_overlap",
            "Surface class is sampled under the overwhelming majority of RSEG center/edge points; likely the actual road/corridor surface."
        )
    if forced and center_pct >= 1.0 and edge_pct >= 1.0 and float(face_pct) < 1.0:
        # M06 surface 7 falls here: small area, forced split, consistently but sparsely sampled by RSEG.
        if str(dominant_adjacent_surface) == "3" or dominant_adjacent_percent >= 25.0:
            return (
                "roadbed_or_shoulder_candidate",
                "forced_split_rseg_correlated_and_adjacent_to_road",
                "Small forced-split surface also appears on RSEG samples and is adjacent to the road-like class; plausible shoulder/roadbed/edge treatment."
            )
        return (
            "road_edge_or_special_patch_candidate",
            "forced_split_low_area_rseg_correlated",
            "Small forced-split surface appears near RSEG samples; may be a road-edge, transition, trigger, or special terrain patch."
        )
    if face_pct >= 50.0:
        return (
            "base_ground_candidate",
            "dominant_area",
            "Surface dominates total terrain area and has little or no RSEG overlap."
        )
    if sc == 5 and not forced:
        return (
            "secondary_ground_or_pad_candidate",
            "distinct_non_forced_surface",
            "Distinct encoded surface class excluded from the runtime forced-split predicate; likely a secondary ground/material/driving bucket."
        )
    if forced:
        return (
            "runtime_special_surface_candidate",
            "runtime_forced_split",
            "Encoded class participates in the runtime forced-split predicate but lacks strong RSEG centerline evidence."
        )
    if sc == 0:
        return (
            "minor_default_or_boundary_candidate",
            "encoded_low_priority_surface",
            "Small/default encoded bucket; may include boundary, filler, or low-priority terrain."
        )
    return (
        "unclassified_surface_candidate",
        "encoded_surface_only",
        "Surface class is encoded in TER high bits but currently lacks stronger role evidence."
    )


def build_terrain_surface_adjacency_rows(rt: RuntimeTerrain, mission_name: str, boundary_sampling: str) -> List[dict]:
    """Count 4-neighbor shared edges between terrain surface classes.

    This helps distinguish a class that lies inside/next to the road corridor from a
    class that is unrelated to RSEG.  Counts are based on dense face/sample cells.
    """
    face_surface: Dict[Tuple[int, int], int] = {}
    for cell_x, cell_z, _page in rt.zmap.used_cells():
        base_x = cell_x * PAGE_W
        base_z = cell_z * PAGE_H
        for lz in range(PAGE_H):
            for lx in range(PAGE_W):
                sx = base_x + lx
                sz = base_z + lz
                face_surface[(sx, sz)] = int(rt.surface_class(sx, sz)) & 0x7

    directed: Dict[Tuple[int, int], int] = {}
    same: Dict[int, int] = {}
    for (sx, sz), sc in face_surface.items():
        for nx, nz in ((sx + 1, sz), (sx, sz + 1)):
            osc = face_surface.get((nx, nz))
            if osc is None:
                continue
            if osc == sc:
                same[sc] = same.get(sc, 0) + 1
            else:
                directed[(sc, osc)] = directed.get((sc, osc), 0) + 1
                directed[(osc, sc)] = directed.get((osc, sc), 0) + 1

    totals: Dict[int, int] = {}
    for (a, b), c in directed.items():
        totals[a] = totals.get(a, 0) + c
    for a, c in same.items():
        totals[a] = totals.get(a, 0) + c

    rows: List[dict] = []
    for (a, b), c in sorted(directed.items(), key=lambda kv: (kv[0][0], -kv[1], kv[0][1])):
        total = totals.get(a, 0)
        rows.append({
            "mission": mission_name,
            "surface_class": a,
            "adjacent_surface_class": b,
            "shared_edge_count": c,
            "percent_of_surface_boundary_edges": f"{(100.0 * c / total) if total else 0.0:.6f}",
            "surface_runtime_forced_split": terrain_surface_runtime_forced_split(a),
            "adjacent_runtime_forced_split": terrain_surface_runtime_forced_split(b),
            "surface_diagnostic_role": terrain_surface_diagnostic_role(a),
            "adjacent_diagnostic_role": terrain_surface_diagnostic_role(b),
            "note": "4-neighbor adjacency between TER high-bit surface classes; role evidence only, not final material binding.",
        })
    return rows


def build_terrain_material_attribution_rows(surface_rows: List[dict], region_rows: List[dict]) -> List[dict]:
    """Mission/surface-level summary joining class totals with region statistics."""
    by_surface_regions: Dict[Tuple[str, int], List[dict]] = {}
    for r in region_rows:
        key = (str(r.get("mission", "")), int(r.get("surface_class", 0)))
        by_surface_regions.setdefault(key, []).append(r)

    rows: List[dict] = []
    for srow in surface_rows:
        mission = str(srow.get("mission", ""))
        sc = int(srow.get("surface_class", 0))
        regs = by_surface_regions.get((mission, sc), [])
        if regs:
            largest = max(regs, key=lambda r: int(r.get("face_count", 0)))
            region_count = len(regs)
            largest_faces = int(largest.get("face_count", 0))
            largest_pct = largest.get("percent_of_mission_faces", "")
            bounds = f"x={largest.get('world_x_min')}..{largest.get('world_x_max')} z={largest.get('world_z_min')}..{largest.get('world_z_max')}"
        else:
            region_count = 0
            largest_faces = 0
            largest_pct = "0.000000"
            bounds = ""
        face_count = int(srow.get("face_count", 0) or 0)
        rows.append({
            "mission": mission,
            "surface_class": sc,
            "high_bits_hex": srow.get("high_bits_hex", ""),
            "binary_code": srow.get("binary_code", ""),
            "face_count": face_count,
            "region_count": region_count,
            "largest_region_faces": largest_faces,
            "largest_region_percent_of_mission_faces": largest_pct,
            "largest_region_world_bounds": bounds,
            "runtime_forced_split": srow.get("runtime_forced_split", ""),
            "diagnostic_role": srow.get("diagnostic_role", ""),
            "candidate_role": terrain_surface_candidate_role(sc, face_count, sum(int(x.get("face_count", 0) or 0) for x in surface_rows if str(x.get("mission", "")) == mission)),
            "candidate_texture": "",
            "candidate_palette_or_pcf": "",
            "confidence": "encoded_surface_class_only",
            "note": "Derived from TER word>>13 plus spatial connected regions; not a final visible ground texture binding.",
        })
    return rows



def resource_role_from_name(name: str, offset_hex: str = "") -> str:
    """Best-effort semantic role for literal resource references.

    This is intentionally attribution-only.  It does not mean the resource has been proven
    to bind to a particular terrain surface class.
    """
    n = (name or "").lower()
    ext = n.rsplit(".", 1)[-1] if "." in n else ""
    stem = n.rsplit(".", 1)[0] if "." in n else n
    if ext in {"act", "pal", "pcf"}:
        return "palette_or_color_context_candidate"
    if ext in {"lum", "tbl", "tab"}:
        return "lighting_luma_translucency_table_candidate"
    if ext == "ter":
        return "terrain_height_surface_sidecar"
    if ext == "npt":
        return "navigation_or_path_sidecar_candidate"
    if ext == "sdf":
        return "static_scene_object_candidate"
    if ext in {"map", "m16", "vqm", "tmt", "cbk"}:
        if stem.startswith("zmap"):
            return "level_map_or_minimap_texture_candidate"
        if stem.startswith("tp"):
            return "terrain_surface_texture_candidate"
        if stem.startswith("nk"):
            return "sky_or_environment_texture_candidate"
        return "texture_or_material_candidate"
    if ext in {"gdf", "fsi", "rtm", "gpw"}:
        return "terrain_or_mission_metadata_candidate"
    return "resource_reference_candidate"


def lookup_resource_name(name: str, file_index: Dict[str, List[Path]], embedded_index: Optional[EmbeddedAssetIndex] = None) -> dict:
    """Lookup a resource name in both filesystem and embedded PIX/PAK/ZFS indexes."""
    key = (name or "").lower()
    file_hits = file_index.get(key, []) or []
    embedded_hits = embedded_index.all_hits(key) if embedded_index is not None else []
    found_file = bool(file_hits)
    found_embedded = bool(embedded_hits)
    first_file = str(file_hits[0]) if file_hits else ""
    first_embedded = ""
    embedded_source = ""
    if embedded_hits:
        h = embedded_hits[0]
        embedded_source = h.source
        first_embedded = f"embedded:{h.source}:{h.asset_id}:{h.name}"
    all_files = ";".join(str(h) for h in file_hits[:20])
    all_embedded = ";".join(f"embedded:{h.source}:{h.asset_id}:{h.name}" for h in embedded_hits[:20])
    return {
        "found": bool(found_file or found_embedded),
        "found_file": found_file,
        "found_embedded": found_embedded,
        "file_hit_count": len(file_hits),
        "embedded_hit_count": len(embedded_hits),
        "hit_count": len(file_hits) + len(embedded_hits),
        "first_file_path": first_file,
        "first_embedded_path": first_embedded,
        "embedded_source": embedded_source,
        "all_file_paths": all_files,
        "all_embedded_paths": all_embedded,
        "first_path": first_file or first_embedded,
        "all_paths": ";".join(x for x in (all_files, all_embedded) if x),
    }


def build_mission_sidecar_candidate_rows(msn: Path, file_index: Dict[str, List[Path]], embedded_index: Optional[EmbeddedAssetIndex] = None) -> List[dict]:
    """Inventory nearby/known sidecars that may help later terrain palette/material binding."""
    stem = msn.stem.lower()
    names = []
    for ext in (".pcf", ".pal", ".act", ".lum", ".tbl", ".tab", ".map", ".tmt", ".m16", ".vqm", ".cbk", ".gdf", ".fsi", ".rtm", ".npt"):
        names.append(stem + ext)
        names.append(stem + "_16" + ext)
    rows: List[dict] = []
    for name in names:
        lu = lookup_resource_name(name, file_index, embedded_index)
        note = "candidate sidecar/resource for future terrain palette/material attribution" if lu["found"] else "not present in indexed filesystem or embedded resource indexes"
        rows.append({
            "mission": stem,
            "candidate_name": name,
            "candidate_ext": Path(name).suffix.lower().lstrip('.'),
            "resource_role": resource_role_from_name(name),
            **lu,
            "note": note,
        })
    return rows


RESOURCE_STRING_EXTS = {"act", "pal", "pcf", "lum", "tbl", "tab", "map", "m16", "vqm", "cbk", "tmt", "gpw", "gdf", "fsi", "rtm", "npt", "sdf", "vcf", "geo", "ter", "msk", "cdf"}

def build_mission_resource_string_rows(mission: MissionData, file_index: Dict[str, List[Path]], embedded_index: Optional[EmbeddedAssetIndex] = None) -> List[dict]:
    """Scan a mission container for embedded resource-looking ASCII tokens.

    This is intentionally a provenance/attribution aid, not a parser.  It helps locate
    PCF/LUM/TBL/MAP/etc references that may explain terrain or palette choices when
    those references are not simply named after the mission stem.
    """
    rows: List[dict] = []
    seen = set()
    for m in ASCII_TOKEN_RE.finditer(mission.data):
        raw = m.group(0).decode("ascii", errors="ignore").strip("\x00")
        token = raw.strip()
        if not token or "." not in token:
            continue
        clean = safe_name(token).lower()
        if "." not in clean:
            continue
        ext = clean.rsplit(".", 1)[-1]
        if ext not in RESOURCE_STRING_EXTS:
            continue
        key = (m.start(), clean)
        if key in seen:
            continue
        seen.add(key)
        lu = lookup_resource_name(clean, file_index, embedded_index)
        role = resource_role_from_name(clean, f"0x{m.start():08x}")
        rows.append({
            "mission": mission.path.stem.lower(),
            "path": str(mission.path),
            "offset_hex": f"0x{m.start():08x}",
            "token": token,
            "normalized_name": clean,
            "ext": ext,
            "resource_role": role,
            **lu,
            "note": "literal resource-looking string in mission payload; use as attribution evidence only",
        })
    rows.sort(key=lambda r: (r["mission"], r["ext"], r["normalized_name"], r["offset_hex"]))
    return rows


def build_terrain_surface_inference_rows(surface_rows: List[dict], region_rows: List[dict], rseg_overlap_rows: List[dict], resource_string_rows: List[dict], adjacency_rows: List[dict]) -> List[dict]:
    """Join surface classes, region stats, RSEG overlap, and mission resource strings into evidence-ranked attributions."""
    # Surface totals/region stats.
    regions_by_key: Dict[Tuple[str, int], List[dict]] = {}
    for r in region_rows:
        regions_by_key.setdefault((str(r.get("mission","")), int(r.get("surface_class", 0))), []).append(r)

    rseg_by_key_role: Dict[Tuple[str, int, str], dict] = {}
    for r in rseg_overlap_rows:
        rseg_by_key_role[(str(r.get("mission","")), int(r.get("surface_class", 0)), str(r.get("sample_role","")))] = r

    resources_by_mission: Dict[str, List[dict]] = {}
    for r in resource_string_rows:
        resources_by_mission.setdefault(str(r.get("mission","")), []).append(r)

    adjacency_by_key: Dict[Tuple[str, int], List[dict]] = {}
    for r in adjacency_rows:
        adjacency_by_key.setdefault((str(r.get("mission","")), int(r.get("surface_class", 0))), []).append(r)

    total_faces_by_mission: Dict[str, int] = {}
    for s in surface_rows:
        mission = str(s.get("mission",""))
        total_faces_by_mission[mission] = total_faces_by_mission.get(mission, 0) + int(s.get("face_count", 0) or 0)

    rows: List[dict] = []
    for s in surface_rows:
        mission = str(s.get("mission",""))
        sc = int(s.get("surface_class", 0))
        face_count = int(s.get("face_count", 0) or 0)
        total_faces = total_faces_by_mission.get(mission, 0)
        face_pct = 100.0 * face_count / total_faces if total_faces else 0.0

        regs = regions_by_key.get((mission, sc), [])
        largest = max(regs, key=lambda r: int(r.get("face_count", 0))) if regs else {}
        largest_pct = float(largest.get("percent_of_mission_faces", 0.0) or 0.0) if largest else 0.0
        largest_bounds = ""
        if largest:
            largest_bounds = f"x={largest.get('world_x_min')}..{largest.get('world_x_max')} z={largest.get('world_z_min')}..{largest.get('world_z_max')}"

        center = rseg_by_key_role.get((mission, sc, "centerline"), {})
        left = rseg_by_key_role.get((mission, sc, "left_edge"), {})
        right = rseg_by_key_role.get((mission, sc, "right_edge"), {})
        center_pct = float(center.get("percent_of_role_samples", 0.0) or 0.0) if center else 0.0
        edge_pct = 0.0
        edge_count = 0
        for rr in (left, right):
            if rr:
                edge_pct += float(rr.get("percent_of_role_samples", 0.0) or 0.0)
                edge_count += 1
        if edge_count:
            edge_pct /= edge_count

        forced = str(s.get("runtime_forced_split", "")).lower() == "true"

        adj_rows = adjacency_by_key.get((mission, sc), [])
        dominant_adj = {}
        if adj_rows:
            dominant_adj = max(adj_rows, key=lambda r: int(r.get("shared_edge_count", 0) or 0))
        dominant_adj_surface = str(dominant_adj.get("adjacent_surface_class", "")) if dominant_adj else ""
        dominant_adj_pct = float(dominant_adj.get("percent_of_surface_boundary_edges", 0.0) or 0.0) if dominant_adj else 0.0

        inference, confidence, evidence_note = terrain_surface_role_from_evidence(
            sc, face_pct, center_pct, edge_pct, forced, dominant_adj_surface, dominant_adj_pct
        )

        # Mission-level resources are relevant to all surface classes, but not a direct binding.
        resources = resources_by_mission.get(mission, [])
        palette_refs = [r.get("normalized_name","") for r in resources if r.get("resource_role") == "palette_or_color_context_candidate"]
        terrain_tex_refs = [r.get("normalized_name","") for r in resources if r.get("resource_role") == "terrain_surface_texture_candidate"]
        env_tex_refs = [r.get("normalized_name","") for r in resources if r.get("resource_role") == "sky_or_environment_texture_candidate"]
        table_refs = [r.get("normalized_name","") for r in resources if r.get("resource_role") == "lighting_luma_translucency_table_candidate"]

        rows.append({
            "mission": mission,
            "surface_class": sc,
            "high_bits_hex": s.get("high_bits_hex",""),
            "binary_code": s.get("binary_code",""),
            "face_count": face_count,
            "face_percent": f"{face_pct:.6f}",
            "region_count": len(regs),
            "largest_region_faces": largest.get("face_count","") if largest else "",
            "largest_region_percent": f"{largest_pct:.6f}",
            "largest_region_world_bounds": largest_bounds,
            "rseg_centerline_percent": f"{center_pct:.6f}",
            "rseg_edge_average_percent": f"{edge_pct:.6f}",
            "dominant_adjacent_surface_class": dominant_adj_surface,
            "dominant_adjacent_percent": f"{dominant_adj_pct:.6f}",
            "runtime_forced_split": s.get("runtime_forced_split",""),
            "inferred_surface_role": inference,
            "confidence": confidence,
            "evidence_note": evidence_note,
            "palette_context_refs": ";".join(palette_refs),
            "terrain_texture_refs": ";".join(terrain_tex_refs),
            "environment_texture_refs": ";".join(env_tex_refs),
            "lighting_table_refs": ";".join(table_refs),
            "note": "Evidence join only: TER class + connected regions + RSEG overlap + surface adjacency + literal mission strings. Not final terrain texture binding.",
        })
    return rows

def build_terrain_rseg_overlap_rows(rt: RuntimeTerrain, mission_name: str, rseg_points: List[dict]) -> List[dict]:
    """Sample terrain surface classes under RSEG center/edge points.

    This does not prove visible material identity.  It correlates encoded TER surface
    classes with runtime road/corridor samples, which is one of the strongest available
    clues for whether a class is roadbed, shoulder, base ground, or special surface.
    """
    counters: Dict[Tuple[str, int], Dict[str, Any]] = {}

    def add(sample_role: str, x: float, z: float, width: float) -> None:
        try:
            sx = int(round(float(x) / SAMPLE_WORLD_SCALE))
            sz = int(round(float(z) / SAMPLE_WORLD_SCALE))
            sc = int(rt.surface_class(sx, sz)) & 0x7
            h = float(rt.height_world(sx, sz))
        except Exception:
            return
        key = (sample_role, sc)
        c = counters.setdefault(key, {
            "count": 0,
            "width_sum": 0.0,
            "height_min": 1e30,
            "height_max": -1e30,
            "height_sum": 0.0,
        })
        c["count"] += 1
        c["width_sum"] += float(width or 0.0)
        c["height_min"] = min(c["height_min"], h)
        c["height_max"] = max(c["height_max"], h)
        c["height_sum"] += h

    for p in rseg_points:
        try:
            lx = float(p.get("left_x", 0.0)); lz = float(p.get("left_z", 0.0))
            rx = float(p.get("right_x", 0.0)); rz = float(p.get("right_z", 0.0))
            cx = float(p.get("center_x", (lx + rx) * 0.5)); cz = float(p.get("center_z", (lz + rz) * 0.5))
            width = float(p.get("width", 0.0) or 0.0)
        except Exception:
            continue
        add("left_edge", lx, lz, width)
        add("right_edge", rx, rz, width)
        add("centerline", cx, cz, width)

    totals_by_role: Dict[str, int] = {}
    for (role, _sc), c in counters.items():
        totals_by_role[role] = totals_by_role.get(role, 0) + int(c["count"])

    rows: List[dict] = []
    for (role, sc), c in sorted(counters.items(), key=lambda kv: (kv[0][0], kv[0][1])):
        total = totals_by_role.get(role, 0)
        count = int(c["count"])
        rows.append({
            "mission": mission_name,
            "sample_role": role,
            "surface_class": sc,
            "high_bits_hex": f"0x{(sc << 13):04x}",
            "binary_code": format(sc, "03b"),
            "sample_count": count,
            "percent_of_role_samples": f"{(100.0 * count / total) if total else 0.0:.6f}",
            "avg_rseg_width": f"{(c['width_sum'] / count) if count else 0.0:.6f}",
            "height_min": f"{c['height_min'] if count else 0.0:.6f}",
            "height_max": f"{c['height_max'] if count else 0.0:.6f}",
            "height_avg": f"{(c['height_sum'] / count) if count else 0.0:.6f}",
            "runtime_forced_split": terrain_surface_runtime_forced_split(sc),
            "diagnostic_role": terrain_surface_diagnostic_role(sc),
            "candidate_inference": "rseg_correlated_surface_class" if count else "",
            "note": "RSEG point sampled onto TER surface class; attribution clue only, not final texture binding",
        })
    return rows

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
    out_dir = timestamped_out_dir(args.out_dir, "i76_level_reconstruction_export_v36")
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
        "version": 36,
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
    all_terrain_surface_region_rows: List[dict] = []
    all_terrain_material_attribution_rows: List[dict] = []
    all_terrain_sidecar_candidate_rows: List[dict] = []
    all_mission_resource_string_rows: List[dict] = []
    all_terrain_rseg_overlap_rows: List[dict] = []
    all_terrain_surface_adjacency_rows: List[dict] = []

    for msn in sorted(missions):
        try:
            mission = load_mission(msn)
            all_mission_resource_string_rows.extend(build_mission_resource_string_rows(mission, file_index, embedded_index))
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
                                terrain_material_style=args.terrain_material_style,
                                header="# I76 dense welded runtime-page-grid terrain baseline with diagnostic surface-class materials\n",
                                write_uvs=args.write_terrain_uvs,
                                uv_mode=args.terrain_uv_mode,
                                uv_repeat=args.terrain_uv_repeat,
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
                    if args.write_terrain_attribution:
                        region_rows = build_terrain_surface_region_rows(rt, msn.stem.lower(), args.boundary_sampling)
                        all_terrain_surface_region_rows.extend(region_rows)
                        all_terrain_surface_adjacency_rows.extend(build_terrain_surface_adjacency_rows(rt, msn.stem.lower(), args.boundary_sampling))
                        all_terrain_sidecar_candidate_rows.extend(build_mission_sidecar_candidate_rows(msn, file_index, embedded_index))
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
                    args.write_static_uvs,
                    args.static_uv_v_flip,
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
            if rt is not None and rseg_points:
                all_terrain_rseg_overlap_rows.extend(build_terrain_rseg_overlap_rows(rt, msn.stem.lower(), rseg_points))
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
    all_terrain_material_attribution_rows = build_terrain_material_attribution_rows(all_terrain_material_rows, all_terrain_surface_region_rows)
    write_tsv(
        out_dir / "tables" / "terrain_surface_regions.tsv",
        all_terrain_surface_region_rows,
        ["mission", "surface_class", "region_id", "face_count", "percent_of_mission_faces", "sample_x_min", "sample_x_max", "sample_z_min", "sample_z_max", "world_x_min", "world_x_max", "world_z_min", "world_z_max", "world_x_center", "world_z_center", "height_min", "height_max", "height_avg", "runtime_forced_split", "diagnostic_role", "candidate_role", "note"],
    )
    write_tsv(
        out_dir / "tables" / "terrain_material_attribution.tsv",
        all_terrain_material_attribution_rows,
        ["mission", "surface_class", "high_bits_hex", "binary_code", "face_count", "region_count", "largest_region_faces", "largest_region_percent_of_mission_faces", "largest_region_world_bounds", "runtime_forced_split", "diagnostic_role", "candidate_role", "candidate_texture", "candidate_palette_or_pcf", "confidence", "note"],
    )
    write_tsv(
        out_dir / "tables" / "terrain_sidecar_candidates.tsv",
        all_terrain_sidecar_candidate_rows,
        ["mission", "candidate_name", "candidate_ext", "resource_role", "found", "found_file", "found_embedded", "file_hit_count", "embedded_hit_count", "hit_count", "first_file_path", "first_embedded_path", "embedded_source", "all_file_paths", "all_embedded_paths", "first_path", "all_paths", "note"],
    )
    write_tsv(
        out_dir / "tables" / "mission_resource_strings.tsv",
        all_mission_resource_string_rows,
        ["mission", "path", "offset_hex", "token", "normalized_name", "ext", "resource_role", "found", "found_file", "found_embedded", "file_hit_count", "embedded_hit_count", "hit_count", "first_file_path", "first_embedded_path", "embedded_source", "all_file_paths", "all_embedded_paths", "first_path", "all_paths", "note"],
    )
    write_tsv(
        out_dir / "tables" / "terrain_rseg_surface_overlap.tsv",
        all_terrain_rseg_overlap_rows,
        ["mission", "sample_role", "surface_class", "high_bits_hex", "binary_code", "sample_count", "percent_of_role_samples", "avg_rseg_width", "height_min", "height_max", "height_avg", "runtime_forced_split", "diagnostic_role", "candidate_inference", "note"],
    )
    write_tsv(
        out_dir / "tables" / "terrain_surface_adjacency.tsv",
        all_terrain_surface_adjacency_rows,
        ["mission", "surface_class", "adjacent_surface_class", "shared_edge_count", "percent_of_surface_boundary_edges", "surface_runtime_forced_split", "adjacent_runtime_forced_split", "surface_diagnostic_role", "adjacent_diagnostic_role", "note"],
    )
    terrain_surface_inference_rows = build_terrain_surface_inference_rows(all_terrain_material_rows, all_terrain_surface_region_rows, all_terrain_rseg_overlap_rows, all_mission_resource_string_rows, all_terrain_surface_adjacency_rows)
    write_tsv(
        out_dir / "tables" / "terrain_surface_inference.tsv",
        terrain_surface_inference_rows,
        ["mission", "surface_class", "high_bits_hex", "binary_code", "face_count", "face_percent", "region_count", "largest_region_faces", "largest_region_percent", "largest_region_world_bounds", "rseg_centerline_percent", "rseg_edge_average_percent", "dominant_adjacent_surface_class", "dominant_adjacent_percent", "runtime_forced_split", "inferred_surface_role", "confidence", "evidence_note", "palette_context_refs", "terrain_texture_refs", "environment_texture_refs", "lighting_table_refs", "note"],
    )
    static_texture_export_rows: List[dict] = []
    static_palette_selection_rows: List[dict] = select_static_palette_rows(
        all_mission_resource_string_rows,
        args.static_palette_mode,
        args.static_palette_file,
        args.static_palette_scale,
        args.palette_file,
        args.palette_scale,
    )
    write_tsv(
        out_dir / "tables" / "static_palette_selection.tsv",
        static_palette_selection_rows,
        ["mission", "static_palette_mode", "palette_name", "palette_path", "palette_source", "palette_scale", "note"],
    )
    texture_export_warnings: List[str] = []
    texture_mtls_rewritten = 0
    if args.export_static_textures:
        static_texture_export_rows, static_texture_bindings, texture_export_warnings = extract_static_textures(
            out_dir, all_static_material_rows, embedded_index, geo_module, args.palette_file, args.palette_scale, args.vqm_layout, static_palette_selection_rows
        )
        texture_mtls_rewritten = rewrite_static_mtls_with_textures(out_dir, static_texture_bindings)
        manifest["warnings"].extend(texture_export_warnings)
    write_tsv(
        out_dir / "tables" / "static_texture_exports.tsv",
        static_texture_export_rows,
        ["mission", "material_key", "texture_name", "texture_probe_name", "asset_name", "asset_id", "asset_ext", "status", "output_relpath", "evidence", "palette_path", "palette_scale", "palette_source", "error"],
    )
    terrain_texture_candidate_rows: List[dict] = []
    terrain_texture_hypothesis_rows: List[dict] = []
    terrain_mtls_annotated = 0
    terrain_palette_selection_rows: List[dict] = select_terrain_palette_rows(
        all_mission_resource_string_rows,
        args.terrain_palette_mode,
        args.terrain_palette_file,
        args.terrain_palette_scale,
        args.palette_file,
        args.palette_scale,
    )
    write_tsv(
        out_dir / "tables" / "terrain_palette_selection.tsv",
        terrain_palette_selection_rows,
        ["mission", "terrain_palette_mode", "palette_name", "palette_path", "palette_source", "palette_scale", "note"],
    )
    if args.export_terrain_texture_candidates:
        terrain_texture_candidate_rows, terrain_texture_warnings = export_terrain_candidate_textures(
            out_dir, all_mission_resource_string_rows, embedded_index, geo_module, terrain_palette_selection_rows, args.vqm_layout
        )
        manifest["warnings"].extend(terrain_texture_warnings)

    terrain_palette_variant_rows: List[dict] = []
    if args.export_terrain_palette_variants:
        if not args.export_terrain_texture_candidates:
            manifest["warnings"].append("--export-terrain-palette-variants requires --export-terrain-texture-candidates; no variants written")
        else:
            terrain_palette_variant_rows, terrain_palette_variant_warnings = export_terrain_palette_variants(
                out_dir,
                terrain_texture_candidate_rows,
                all_mission_resource_string_rows,
                file_index,
                embedded_index,
                geo_module,
                terrain_palette_selection_rows,
                args.palette_file,
                args.palette_scale,
                args.terrain_palette_file,
                args.terrain_palette_scale,
                args.vqm_layout,
                args.terrain_palette_variant_sweep,
                args.terrain_palette_variant_glob,
                args.terrain_palette_variant_limit,
            )
            manifest["warnings"].extend(terrain_palette_variant_warnings)
    write_tsv(
        out_dir / "tables" / "terrain_palette_variants.tsv",
        terrain_palette_variant_rows,
        ["mission", "texture_name", "resource_role", "asset_name", "asset_id", "asset_ext", "texture_probe_name", "palette_variant_source", "palette_name", "palette_path", "palette_scale", "status", "output_relpath", "evidence", "error", "note"],
    )

    terrain_map_probe_rows = build_terrain_map_probe_rows(all_mission_resource_string_rows, file_index, embedded_index)
    write_tsv(
        out_dir / "tables" / "terrain_map_probe.tsv",
        terrain_map_probe_rows,
        ["mission", "offset_hex", "token", "normalized_name", "stem", "resource_role", "found_file", "found_embedded", "direct_asset_name", "direct_asset_id", "direct_source", "direct_ext", "direct_payload_size", "direct_sha256_12", "direct_first32_hex", "direct_first4_ascii", "direct_u16_0", "direct_u16_2", "direct_u32_0", "direct_u32_4", "direct_ascii_tokens", "direct_contains_resource_strings", "sibling_m16_found", "sibling_m16_source", "sibling_m16_asset_name", "sibling_m16_asset_id", "sibling_m16_payload_size", "sibling_m16_sha256_12", "sibling_m16_first4_ascii", "sibling_vqm_found", "sibling_vqm_source", "sibling_vqm_asset_name", "sibling_vqm_asset_id", "sibling_vqm_payload_size", "sibling_vqm_sha256_12", "sibling_vqm_first4_ascii", "sibling_tmt_found", "sibling_tmt_source", "sibling_tmt_asset_name", "sibling_tmt_asset_id", "sibling_tmt_payload_size", "sibling_tmt_sha256_12", "sibling_tmt_first4_ascii", "sibling_cbk_found", "sibling_cbk_source", "sibling_cbk_asset_name", "sibling_cbk_asset_id", "sibling_cbk_payload_size", "sibling_cbk_sha256_12", "sibling_cbk_first4_ascii", "sibling_map_found", "sibling_map_source", "sibling_map_asset_name", "sibling_map_asset_id", "sibling_map_payload_size", "sibling_map_sha256_12", "sibling_map_first4_ascii", "sibling_summary", "inferred_map_kind", "note"],
    )

    terrain_texture_hypothesis_rows = build_terrain_surface_texture_hypotheses(terrain_surface_inference_rows, terrain_texture_candidate_rows)
    if args.export_terrain_texture_candidates:
        terrain_mtls_annotated = rewrite_terrain_mtls_with_candidate_comments(out_dir, terrain_texture_candidate_rows, terrain_texture_hypothesis_rows)
    terrain_texture_binding_rows: List[dict] = []
    terrain_texture_mtls_bound = 0
    if args.bind_terrain_candidate_textures:
        if not args.export_terrain_texture_candidates:
            manifest["warnings"].append("--bind-terrain-candidate-textures requires --export-terrain-texture-candidates; no terrain texture bindings written")
        else:
            terrain_texture_mtls_bound, terrain_texture_binding_rows = bind_terrain_candidate_textures(
                out_dir, terrain_texture_candidate_rows, terrain_texture_hypothesis_rows, args.terrain_texture_binding_mode
            )
    write_tsv(
        out_dir / "tables" / "terrain_texture_candidates.tsv",
        terrain_texture_candidate_rows,
        ["mission", "token", "normalized_name", "resource_role", "candidate_priority", "asset_name", "asset_id", "asset_ext", "texture_probe_name", "palette_name", "palette_path", "palette_source", "palette_scale", "status", "output_relpath", "evidence", "error", "note"],
    )
    write_tsv(
        out_dir / "tables" / "terrain_surface_texture_hypotheses.tsv",
        terrain_texture_hypothesis_rows,
        ["mission", "surface_class", "inferred_surface_role", "surface_confidence", "runtime_forced_split", "rseg_centerline_percent", "rseg_edge_average_percent", "candidate_texture_names", "candidate_texture_outputs", "environment_texture_names", "binding_confidence", "note"],
    )
    write_tsv(
        out_dir / "tables" / "terrain_texture_bindings.tsv",
        terrain_texture_binding_rows if 'terrain_texture_binding_rows' in locals() else [],
        ["mission", "surface_class", "material_key", "binding_mode", "texture_name", "asset_name", "texture_probe_name", "map_kd", "mtl_path", "status", "confidence", "note"],
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
        "static_object_texcoords": sum(int((m.get("static_objects_obj") or {}).get("texcoords") or 0) for m in manifest["missions"] if isinstance(m.get("static_objects_obj"), dict)),
        "static_material_texture_hits": sum(1 for r in all_static_material_rows if str(r.get("texture_found", "")).lower() in {"true", "1", "yes"}),
        "static_texture_export_rows": len(static_texture_export_rows),
        "static_texture_export_success_rows": sum(1 for r in static_texture_export_rows if str(r.get("status", "")) == "exported"),
        "static_texture_mtls_rewritten": texture_mtls_rewritten,
        "terrain_material_surface_class_rows": len(all_terrain_material_rows),
        "terrain_material_runtime_forced_split_rows": sum(1 for r in all_terrain_material_rows if str(r.get("runtime_forced_split", "")).lower() in {"true", "1", "yes"}),
        "terrain_surface_region_rows": len(all_terrain_surface_region_rows),
        "terrain_material_attribution_rows": len(all_terrain_material_attribution_rows),
        "terrain_sidecar_candidate_rows": len(all_terrain_sidecar_candidate_rows),
        "mission_resource_string_rows": len(all_mission_resource_string_rows),
        "terrain_rseg_surface_overlap_rows": len(all_terrain_rseg_overlap_rows),
        "terrain_surface_adjacency_rows": len(all_terrain_surface_adjacency_rows),
        "terrain_surface_inference_rows": len(terrain_surface_inference_rows) if 'terrain_surface_inference_rows' in locals() else 0,
        "terrain_palette_selection_rows": len(terrain_palette_selection_rows) if 'terrain_palette_selection_rows' in locals() else 0,
        "terrain_texture_candidate_rows": len(terrain_texture_candidate_rows) if 'terrain_texture_candidate_rows' in locals() else 0,
        "terrain_palette_variant_rows": len(terrain_palette_variant_rows) if 'terrain_palette_variant_rows' in locals() else 0,
        "terrain_map_probe_rows": len(terrain_map_probe_rows) if 'terrain_map_probe_rows' in locals() else 0,
        "terrain_texture_binding_rows": len(terrain_texture_binding_rows) if 'terrain_texture_binding_rows' in locals() else 0,
        "terrain_texture_mtls_bound": terrain_texture_mtls_bound if 'terrain_texture_mtls_bound' in locals() else 0,
        "static_material_unique_textures": len([r for r in static_material_texture_summary_rows if r.get("texture_name")]),
        "static_material_solid_color_groups": len(static_material_solid_color_rows),
        "combined_scene_objs": sum(1 for m in manifest["missions"] if isinstance(m.get("combined_scene_obj"), dict) and m["combined_scene_obj"].get("components_written", 0) > 0),
        "unresolved_resource_rows": len(all_unresolved),
        "rseg_records": len(all_rseg_record_rows),
        "rseg_points": len(all_rseg_point_rows),
    }

    notes = [
        "i76_level_reconstruction_export_v36 notes",
        "",
        "This revision is based on the repo/local_history v4 BWD2 mission-parser workflow and adds v36 static material palette selection plus validated static UV V-flip default.",
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
        "Lighting, collision, and exact render-record semantics remain downstream work. Static MAP/M16/VQM textures are bound with emitted GEO UVs; v36 separates static palette selection from terrain palette selection and defaults static V flip to the visually validated path.",
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
    ap = argparse.ArgumentParser(description="Interstate '76 level reconstruction exporter with v42 class-specific object resource resolution, static SGEO/GEO assembly, bounds, combined scene validation, and material diagnostics and visible terrain surface-code diagnostics")
    ap.add_argument("input", help="Directory containing .MSN/.SPC/.LVL and .TER sidecars, or a single mission file")
    ap.add_argument("--resource-root", action="append", default=[], help="Additional resource root(s), e.g. extracted zfs and/or retail install root. Repeatable.")
    ap.add_argument("--resolver", type=Path, default=None, help="Optional historical resolver script, usually scripts/local_history/i76_vehicle_texture_slot_resolver_v5.py, for embedded ZFS/PIX/PAK asset names")
    ap.add_argument("--zfs", type=Path, default=None, help="Optional I76.ZFS path used with --resolver to index embedded GEO/TMT/MAP/M16/VQM/CBK assets")
    ap.add_argument("--zix", type=Path, default=None, help="Reserved for compatibility with older commands; current resolver hook uses --zfs")
    ap.add_argument("--geo-exporter", type=Path, default=None, help="Optional historical GEO exporter/parser script, usually scripts/local_history/i76_vehicle_geo_obj_export_v20.py. Defaults to sibling of --resolver when present.")
    ap.add_argument("--export-static-textures", action="store_true", help="Decode/export unique M16/VQM texture payloads used by static SGEO/GEO materials and bind them into static_objects.mtl")
    ap.add_argument("--export-terrain-texture-candidates", action="store_true", help="Decode/export mission-level terrain/environment texture candidates for inspection without binding them to TER surface classes")
    ap.add_argument("--export-terrain-palette-variants", action="store_true", help="Diagnostic: export terrain/environment candidate textures with mission ACT, global palette, explicit palette, resource ACT sweep, and no-palette variants side by side")
    ap.add_argument("--terrain-palette-variant-sweep", choices=["none", "all-act", "glob"], default="all-act", help="When exporting terrain palette variants, also sweep ACT files from the resource index. all-act is broad but useful while the terrain palette context is unknown.")
    ap.add_argument("--terrain-palette-variant-glob", action="append", default=[], help="When --terrain-palette-variant-sweep glob is used, include ACT palette filenames matching this glob. Repeatable, e.g. 't*.act'.")
    ap.add_argument("--terrain-palette-variant-limit", type=int, default=256, help="Maximum ACT palettes to include from the resource-index sweep.")
    ap.add_argument("--bind-terrain-candidate-textures", action="store_true", help="Experimental: add map_Kd bindings from exported mission-level terrain texture candidates to diagnostic terrain surface materials")
    ap.add_argument("--terrain-texture-binding-mode", choices=["evidence-single", "road-surfaces-only"], default="evidence-single", help="Experimental terrain candidate binding policy. evidence-single binds the best terrain candidate to every TER surface material; road-surfaces-only binds it only to inferred road/shoulder classes.")
    ap.add_argument("--palette-file", type=Path, default=None, help="Optional fallback/global 256*3 RGB palette/ACT file for static indexed texture PNG export")
    ap.add_argument("--palette-scale", choices=["auto", "raw", "x4"], default="auto", help="Palette scaling mode for --palette-file")
    ap.add_argument("--static-palette-mode", choices=["mission-act", "explicit", "global"], default="mission-act", help="Palette selection for static object texture PNGs. Default mission-act uses mission ACT references such as t01.ACT; global uses --palette-file; explicit uses --static-palette-file.")
    ap.add_argument("--static-palette-file", type=Path, default=None, help="Optional explicit ACT/RGB palette for static object texture PNG export")
    ap.add_argument("--static-palette-scale", choices=["auto", "raw", "x4"], default="auto", help="Palette scaling mode for --static-palette-file or mission ACT static palette")
    ap.add_argument("--terrain-palette-mode", choices=["mission-act", "explicit", "global"], default="mission-act", help="Palette selection for terrain/environment texture candidate PNGs. mission-act uses literal ACT references such as t09_16.ACT from the mission when present; explicit uses --terrain-palette-file; global uses --palette-file.")
    ap.add_argument("--terrain-palette-file", type=Path, default=None, help="Optional explicit ACT/RGB palette for terrain/environment texture candidate PNG export")
    ap.add_argument("--terrain-palette-scale", choices=["auto", "raw", "x4"], default="auto", help="Palette scaling mode for terrain candidate palette selection")
    ap.add_argument("--vqm-layout", default="yx", help="VQM/CBK 4x4 tile layout for texture export; yx is the current validated default")
    ap.add_argument("--write-terrain-materials", action="store_true", help="When writing dense terrain, emit diagnostic TER surface-class materials on the ground mesh")
    ap.add_argument("--write-terrain-uvs", action="store_true", default=True, help="Emit OBJ vt coordinates for dense terrain when writing terrain materials; default true so map_Kd candidate textures are visible")
    ap.add_argument("--no-write-terrain-uvs", dest="write_terrain_uvs", action="store_false")
    ap.add_argument("--terrain-uv-mode", choices=["whole-terrain", "world-repeat"], default="world-repeat", help="UV model for diagnostic terrain texture candidates. Default is world-repeat, visually validated for terrain MAP binding. whole-terrain maps one image across the dense terrain bounds; world-repeat repeats in world units.")
    ap.add_argument("--terrain-uv-repeat", type=float, default=1.0, help="Multiplier for diagnostic terrain UVs")
    ap.add_argument("--terrain-material-style", choices=["natural", "high-contrast"], default="natural", help="Diagnostic Kd palette for TER surface-class terrain materials; default natural for current validation; use high-contrast for debugging")
    ap.add_argument("--write-terrain-attribution", action="store_true", default=True, help="Emit connected terrain surface-region and sidecar attribution tables; default true")
    ap.add_argument("--no-write-terrain-attribution", dest="write_terrain_attribution", action="store_false")
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
    ap.add_argument("--write-static-uvs", action="store_true", default=True, help="Emit OBJ vt coordinates from static GEO face refs; default true so non-terrain MAP/M16/VQM textures are visible")
    ap.add_argument("--no-write-static-uvs", dest="write_static_uvs", action="store_false")
    ap.add_argument("--static-uv-v-flip", action="store_true", default=True, help="Flip static GEO V coordinate as 1-v when emitting OBJ vt records; default true after visual validation")
    ap.add_argument("--no-static-uv-v-flip", dest="static_uv_v_flip", action="store_false", help="Disable static GEO V flip for diagnostics")
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
