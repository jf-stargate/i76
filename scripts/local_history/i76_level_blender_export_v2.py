#!/usr/bin/env python3
"""
Interstate '76 level package exporter for Blender, v2.

Fixes over v1:
  - Fails loudly when the input path does not exist.
  - Writes discovery diagnostics to the manifest.
  - Supports any-case file extensions by scanning all files and comparing suffix.lower().
  - Supports common extractor layouts:
      <extract>/resources/*.tab
      <extract>/resources/**/*.tab
      <extract>/terrain_raw/*.tab
      <extract>/**/*.tab
  - Prints terrain/LVL discovery counts before writing the manifest.
  - Optional --fail-empty exits non-zero if no terrain was discovered.

Output:
  <out-dir>/i76_level_blender_manifest.json
  <out-dir>/terrain_raw/<copied terrain files>
  <out-dir>/terrain_obj/<optional preview OBJ files>
"""

from __future__ import annotations

import argparse
import dataclasses
import hashlib
import json
import math
import shutil
import struct
import sys
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


PAGE_SIZE = 0x8000
PAGE_W = 128
PAGE_H = 128
GRID_SAMPLE_METERS = 5.0


def read_u32(data: bytes, off: int) -> int:
    if off + 4 > len(data):
        raise ValueError(f"u32 out of range at 0x{off:x}")
    return struct.unpack_from("<I", data, off)[0]


def fourcc(raw: bytes) -> str:
    return raw.decode("ascii", errors="replace")


@dataclasses.dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ""
    children: List["Chunk"] = dataclasses.field(default_factory=list)

    @property
    def end(self) -> int:
        return self.offset + self.size


CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}


def parse_flat_chunks(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out: List[Chunk] = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data[off:off + 4])
        size = read_u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        out.append(Chunk(tag, off, size, off + 8, size - 8, parent))
        off += size
    return out


def parse_chunk_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat_chunks(data, 0, len(data), "")

    def rec(c: Chunk) -> None:
        if c.tag in CONTAINERS and c.payload_size >= 8:
            kids = parse_flat_chunks(data, c.payload_offset, c.end, c.tag)
            if kids:
                c.children = kids
                for kid in kids:
                    rec(kid)

    for root in roots:
        rec(root)
    return roots


def walk_chunks(chunks: Iterable[Chunk]) -> Iterable[Chunk]:
    for c in chunks:
        yield c
        yield from walk_chunks(c.children)


def first_chunk(chunks: Iterable[Chunk], wanted: str) -> Optional[Chunk]:
    for c in walk_chunks(chunks):
        if c.tag == wanted:
            return c
    return None


@dataclasses.dataclass
class ZMap:
    active_zone_count: int
    cells: List[int]

    def origins_by_page(self) -> Dict[int, Tuple[int, int]]:
        origins: Dict[int, Tuple[int, int]] = {}
        for y in range(80):
            for x in range(80):
                v = self.cells[y * 80 + x]
                if v == 0xFF:
                    continue
                origins.setdefault(v, (x, y))
        return origins

    def to_manifest(self) -> dict:
        used = sorted({v for v in self.cells if v != 0xFF})
        return {
            "active_zone_count": self.active_zone_count,
            "width": 80,
            "height": 80,
            "used_page_indices": used,
            "invalid_page_indices": sorted({v for v in used if v >= self.active_zone_count}),
            "page_origins": {str(k): [v[0], v[1]] for k, v in self.origins_by_page().items()},
        }


def decode_zmap(lvl_data: bytes, chunks: List[Chunk]) -> Optional[ZMap]:
    c = first_chunk(chunks, "ZMAP")
    if c is None:
        return None
    if c.payload_size < 1 + 80 * 80:
        raise ValueError(f"ZMAP too small at 0x{c.offset:x}: payload_size=0x{c.payload_size:x}")
    return ZMap(
        active_zone_count=lvl_data[c.payload_offset],
        cells=list(lvl_data[c.payload_offset + 1:c.payload_offset + 1 + 80 * 80]),
    )


def decode_zone_filename(lvl_data: bytes, chunks: List[Chunk]) -> str:
    c = first_chunk(chunks, "ZONE")
    if c is None:
        return ""
    payload = lvl_data[c.payload_offset:c.end]
    if len(payload) <= 9:
        return ""
    return payload[9:].split(b"\0", 1)[0].decode("ascii", errors="ignore")


def sha1_file(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        while True:
            b = f.read(1024 * 1024)
            if not b:
                break
            h.update(b)
    return h.hexdigest()


def terrain_page_count(path: Path) -> int:
    size = path.stat().st_size
    if size % PAGE_SIZE != 0:
        raise ValueError(f"{path} size 0x{size:x} is not a multiple of 0x{PAGE_SIZE:x}")
    return size // PAGE_SIZE


def page_grid_for_count(count: int) -> Tuple[int, int]:
    if count <= 0:
        return (0, 0)
    cols = math.ceil(math.sqrt(count))
    rows = math.ceil(count / cols)
    return cols, rows


def default_page_origins(page_count: int) -> Dict[int, Tuple[int, int]]:
    cols, _rows = page_grid_for_count(page_count)
    return {i: (i % cols, i // cols) for i in range(page_count)}


def page_summary(raw_path: Path, page_index: int) -> dict:
    with raw_path.open("rb") as f:
        f.seek(page_index * PAGE_SIZE)
        raw = f.read(PAGE_SIZE)
    if len(raw) != PAGE_SIZE:
        raise ValueError(f"{raw_path} page {page_index} short read")

    words = struct.unpack("<" + "H" * (PAGE_W * PAGE_H), raw)
    heights = [w & 0x0FFF for w in words]
    return {
        "page_index": page_index,
        "min_height": min(heights),
        "max_height": max(heights),
        "surfaces": sorted({(w >> 13) & 7 for w in words}),
        "surface_flag_count": sum(1 for w in words if w & 0x1000),
    }


def write_preview_obj(raw_path: Path, terrain_entry: dict, obj_path: Path,
                      horizontal_scale: float, vertical_scale: float) -> None:
    page_count = terrain_entry["page_count"]
    origins = {int(k): tuple(v) for k, v in terrain_entry["page_origins"].items()}
    data = raw_path.read_bytes()

    vertices: List[Tuple[float, float, float]] = []
    faces: List[Tuple[int, int, int, int]] = []

    for page_index in range(page_count):
        words = struct.unpack_from("<" + "H" * (PAGE_W * PAGE_H), data, page_index * PAGE_SIZE)
        ox, oz = origins.get(page_index, (page_index, 0))
        base_x = ox * PAGE_W * horizontal_scale
        base_z = oz * PAGE_H * horizontal_scale
        base_vertex = len(vertices) + 1

        for z in range(PAGE_H):
            for x in range(PAGE_W):
                h = words[z * PAGE_W + x] & 0x0FFF
                vertices.append((base_x + x * horizontal_scale, h * vertical_scale, base_z + z * horizontal_scale))

        for z in range(PAGE_H - 1):
            for x in range(PAGE_W - 1):
                v0 = base_vertex + z * PAGE_W + x
                faces.append((v0, v0 + 1, v0 + PAGE_W + 1, v0 + PAGE_W))

    obj_path.parent.mkdir(parents=True, exist_ok=True)
    with obj_path.open("w", encoding="utf-8") as f:
        f.write("# Interstate '76 terrain preview OBJ\n")
        f.write(f"# source={raw_path.name} pages={page_count}\n")
        for vx, vy, vz in vertices:
            f.write(f"v {vx:.6f} {vy:.6f} {vz:.6f}\n")
        for a, b, c, d in faces:
            f.write(f"f {a} {b} {c} {d}\n")


def discover_files(input_path: Path) -> Tuple[List[Path], List[Path], dict]:
    """
    Return (lvl_like_files, terrain_files, diagnostics).
    Scans with suffix.lower() so case variants do not matter.
    """
    diagnostics = {
        "input_exists": input_path.exists(),
        "input_is_file": input_path.is_file(),
        "input_is_dir": input_path.is_dir(),
        "scanned_roots": [],
        "all_file_count": 0,
        "lvl_like_count": 0,
        "terrain_like_count": 0,
        "sample_files": [],
    }

    if not input_path.exists():
        raise FileNotFoundError(f"input path does not exist: {input_path}")

    lvl_exts = {".lvl", ".msn"}
    terrain_exts = {".tab", ".ter"}

    if input_path.is_file():
        suffix = input_path.suffix.lower()
        if suffix in lvl_exts:
            diagnostics["all_file_count"] = 1
            diagnostics["lvl_like_count"] = 1
            diagnostics["sample_files"] = [str(input_path)]
            return [input_path], [], diagnostics
        if suffix in terrain_exts:
            diagnostics["all_file_count"] = 1
            diagnostics["terrain_like_count"] = 1
            diagnostics["sample_files"] = [str(input_path)]
            return [], [input_path], diagnostics
        raise ValueError(f"unsupported input file extension: {input_path}")

    # If the user points at an extraction root, prioritize common resource subfolders too,
    # but ultimately scan the whole tree once.
    roots = [input_path]
    for sub in ("resources", "terrain_raw", "terrain", "out", "extract"):
        candidate = input_path / sub
        if candidate.exists() and candidate.is_dir():
            roots.append(candidate)

    seen = set()
    all_files: List[Path] = []
    for root in roots:
        diagnostics["scanned_roots"].append(str(root))
        for p in root.rglob("*"):
            if p.is_file():
                rp = p.resolve()
                if rp not in seen:
                    seen.add(rp)
                    all_files.append(p)

    lvl_files = sorted([p for p in all_files if p.suffix.lower() in lvl_exts])
    terrain_files = sorted([p for p in all_files if p.suffix.lower() in terrain_exts])

    diagnostics["all_file_count"] = len(all_files)
    diagnostics["lvl_like_count"] = len(lvl_files)
    diagnostics["terrain_like_count"] = len(terrain_files)
    diagnostics["sample_files"] = [str(p) for p in all_files[:40]]

    return lvl_files, terrain_files, diagnostics


def copy_resource(src: Path, out_dir: Path) -> Path:
    out_dir.mkdir(parents=True, exist_ok=True)
    dst = out_dir / src.name.lower()
    if src.resolve() != dst.resolve():
        shutil.copy2(src, dst)
    return dst


def make_terrain_entry_from_raw(src: Path, copied: Path, source_kind: str,
                                page_origins: Optional[Dict[int, Tuple[int, int]]] = None,
                                zmap: Optional[ZMap] = None,
                                lvl_path: Optional[Path] = None) -> dict:
    count = terrain_page_count(copied)
    origins = page_origins if page_origins is not None else default_page_origins(count)
    entry = {
        "name": src.stem,
        "source_kind": source_kind,
        "source_path": str(src),
        "raw_path": str(copied),
        "sha1": sha1_file(copied),
        "page_count": count,
        "page_width": PAGE_W,
        "page_height": PAGE_H,
        "page_size_bytes": PAGE_SIZE,
        "sample_format": "uint16_le_packed_height_surface",
        "height_mask": "0x0fff",
        "surface_flag_mask": "0x1000",
        "surface_class_mask": "0xe000",
        "horizontal_sample_scale": GRID_SAMPLE_METERS,
        "page_origins": {str(k): [v[0], v[1]] for k, v in origins.items()},
        "pages": [page_summary(copied, i) for i in range(count)],
    }
    if zmap is not None:
        entry["zmap"] = zmap.to_manifest()
    if lvl_path is not None:
        entry["lvl_path"] = str(lvl_path)
    return entry


def find_sidecar_for_lvl(lvl: Path, zone_name: str) -> Optional[Path]:
    candidates: List[Path] = []
    if zone_name:
        candidates.extend([
            lvl.parent / zone_name,
            lvl.parent / zone_name.upper(),
            lvl.parent / zone_name.lower(),
        ])
    candidates.extend([lvl.with_suffix(".TER"), lvl.with_suffix(".ter"), lvl.with_suffix(".TAB"), lvl.with_suffix(".tab")])
    for c in candidates:
        if c.exists() and c.is_file():
            return c
    return None


def export_package(input_path: Path, out_dir: Path, emit_obj: bool,
                   horizontal_scale: float, vertical_scale: float,
                   fail_empty: bool) -> dict:
    lvl_files, terrain_files, diagnostics = discover_files(input_path)

    print(f"Input: {input_path}")
    print(f"Discovered {diagnostics['all_file_count']} files")
    print(f"Discovered {len(lvl_files)} LVL/MSN files")
    print(f"Discovered {len(terrain_files)} TAB/TER terrain files")

    out_dir.mkdir(parents=True, exist_ok=True)
    terrain_raw_dir = out_dir / "terrain_raw"
    terrain_obj_dir = out_dir / "terrain_obj"

    manifest = {
        "format": "i76_blender_level_manifest",
        "version": 2,
        "source": str(input_path),
        "discovery": diagnostics,
        "coordinate_system": {
            "x": "i76 world/editor X",
            "y": "height",
            "z": "i76 world/editor Z",
            "horizontal_sample_scale_default": horizontal_scale,
            "vertical_scale_default": vertical_scale,
        },
        "terrain": [],
        "roads": [],
        "objects": [],
        "notes": [
            "Retail TAB placement is provisional unless a matching LVL/ZMAP is present.",
            "LVL/TER placement uses runtime ZMAP page indices directly.",
            "Road and object import placeholders are reserved for the next decoder pass.",
        ],
    }

    consumed_terrain_paths = set()

    for lvl in lvl_files:
        try:
            lvl_data = lvl.read_bytes()
            chunks = parse_chunk_tree(lvl_data)
            zmap = decode_zmap(lvl_data, chunks)
            zone_name = decode_zone_filename(lvl_data, chunks)
            sidecar = find_sidecar_for_lvl(lvl, zone_name)
            if sidecar is None:
                continue

            copied = copy_resource(sidecar, terrain_raw_dir)
            consumed_terrain_paths.add(sidecar.resolve())
            origins = zmap.origins_by_page() if zmap is not None else None
            entry = make_terrain_entry_from_raw(sidecar, copied, "lvl_sidecar", origins, zmap=zmap, lvl_path=lvl)
            if emit_obj:
                obj_path = terrain_obj_dir / f"{lvl.stem.lower()}.terrain.obj"
                write_preview_obj(copied, entry, obj_path, horizontal_scale, vertical_scale)
                entry["preview_obj"] = str(obj_path)
            manifest["terrain"].append(entry)
        except Exception as e:
            manifest.setdefault("warnings", []).append(f"LVL sidecar handling failed for {lvl}: {type(e).__name__}: {e}")

    for terrain in terrain_files:
        if terrain.resolve() in consumed_terrain_paths:
            continue
        try:
            copied = copy_resource(terrain, terrain_raw_dir)
            entry = make_terrain_entry_from_raw(terrain, copied, "standalone_tab_or_ter")
            if emit_obj:
                obj_path = terrain_obj_dir / f"{terrain.stem.lower()}.terrain.obj"
                write_preview_obj(copied, entry, obj_path, horizontal_scale, vertical_scale)
                entry["preview_obj"] = str(obj_path)
            manifest["terrain"].append(entry)
        except Exception as e:
            manifest.setdefault("warnings", []).append(f"Terrain handling failed for {terrain}: {type(e).__name__}: {e}")

    manifest_path = out_dir / "i76_level_blender_manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    if not manifest["terrain"]:
        msg = (
            "No terrain entries were exported. Check the input path and confirm it contains "
            "*.TAB/*.TER files, or point at the extractor's resources directory."
        )
        print("WARNING:", msg, file=sys.stderr)
        print(f"Manifest written with discovery diagnostics: {manifest_path}", file=sys.stderr)
        if fail_empty:
            raise SystemExit(2)

    return manifest


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("input", type=Path, help="Directory or single .LVL/.MSN/.TAB/.TER")
    ap.add_argument("--out-dir", type=Path, required=True, help="Output Blender package directory")
    ap.add_argument("--no-obj", action="store_true", help="Do not emit preview OBJ files")
    ap.add_argument("--horizontal-scale", type=float, default=GRID_SAMPLE_METERS)
    ap.add_argument("--vertical-scale", type=float, default=1.0)
    ap.add_argument("--fail-empty", action="store_true", help="Exit non-zero if no terrain entries are exported")
    args = ap.parse_args()

    manifest = export_package(
        args.input,
        args.out_dir,
        emit_obj=not args.no_obj,
        horizontal_scale=args.horizontal_scale,
        vertical_scale=args.vertical_scale,
        fail_empty=args.fail_empty,
    )
    print(json.dumps({
        "manifest": str(args.out_dir / "i76_level_blender_manifest.json"),
        "terrain_entries": len(manifest["terrain"]),
        "out_dir": str(args.out_dir),
    }, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
