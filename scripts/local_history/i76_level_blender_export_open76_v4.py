#!/usr/bin/env python3
"""
Interstate '76 Open76-aligned runtime terrain exporter for Blender, v4.

Validation basis:
  Open76's MsnMissionParser reads terrain only from the BWD2 mission stream:
    WDEF/WRLD gives filenames and metadata.
    TDEF/ZMAP gives active patch count and 80x80 patch-index map.
    TDEF/ZONE gives a terrain sidecar filename.
    The sidecar is read as active_patch_count * 128*128 uint16 packed samples.
    height = (sample & 0x0fff) / 4096.0 in Open76; Unity Terrain size.y = 409.5.
  LUM/TBL are mission metadata tables, not terrain heightfields.
  TAB is not treated as height.

This script therefore:
  - imports only .MSN/.LVL + matching .TER/TAB-like sidecar when a BWD2 ZONE chunk points to it
  - copies and reports retail .LUM/.TBL/.TAB/.HZD resources as supporting files only
  - refuses to generate terrain from standalone .LUM or .TAB unless explicitly requested for debugging

Output:
  <out-dir>/i76_level_blender_manifest.json
  <out-dir>/terrain_raw/<sidecar files>
  <out-dir>/terrain_obj/<optional OBJ preview from sidecar pages>
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


PAGE_W = 128
PAGE_H = 128
PAGE_SIZE = PAGE_W * PAGE_H * 2
DEFAULT_HORIZONTAL_SCALE = 5.0
# Open76 uses normalized height = low12/4096 and Unity TerrainData.size.y = 409.5.
# Export OBJ height therefore defaults to low12/4096*409.5.
DEFAULT_VERTICAL_SCALE = 409.5 / 4096.0


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


def fourcc(raw: bytes) -> str:
    return raw.decode("ascii", errors="replace")


def u32(data: bytes, off: int) -> int:
    if off + 4 > len(data):
        raise ValueError(f"u32 out of range at 0x{off:x}")
    return struct.unpack_from("<I", data, off)[0]


def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out: List[Chunk] = []
    off = start
    while off + 8 <= end:
        t = fourcc(data[off:off + 4])
        size = u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        out.append(Chunk(t, off, size, off + 8, size - 8, parent))
        off += size
    return out


def parse_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat(data, 0, len(data), "")

    def rec(c: Chunk) -> None:
        if c.tag in CONTAINERS and c.payload_size >= 8:
            kids = parse_flat(data, c.payload_offset, c.end, c.tag)
            if kids:
                c.children = kids
                for kid in kids:
                    rec(kid)

    for root in roots:
        rec(root)
    return roots


def walk(chunks: Iterable[Chunk]) -> Iterable[Chunk]:
    for c in chunks:
        yield c
        yield from walk(c.children)


def first_chunk(chunks: Iterable[Chunk], name: str) -> Optional[Chunk]:
    for c in walk(chunks):
        if c.tag == name:
            return c
    return None


@dataclasses.dataclass
class ZMap:
    active_patch_count: int
    cells: List[int]

    def origins_by_page(self) -> Dict[int, Tuple[int, int]]:
        origins: Dict[int, Tuple[int, int]] = {}
        for z in range(80):
            for x in range(80):
                v = self.cells[z * 80 + x]
                if v == 0xFF:
                    continue
                origins.setdefault(v, (x, z))
        return origins

    def to_dict(self) -> dict:
        used = sorted({v for v in self.cells if v != 0xFF})
        return {
            "active_patch_count": self.active_patch_count,
            "width": 80,
            "height": 80,
            "used_page_indices": used,
            "invalid_page_indices": sorted({v for v in used if v >= self.active_patch_count}),
            "page_origins": {str(k): [v[0], v[1]] for k, v in self.origins_by_page().items()},
        }


def decode_zmap(msn_data: bytes, chunks: List[Chunk]) -> Optional[ZMap]:
    c = first_chunk(chunks, "ZMAP")
    if c is None:
        return None
    if c.payload_size < 1 + 80 * 80:
        raise ValueError(f"ZMAP too small at 0x{c.offset:x}: payload_size=0x{c.payload_size:x}")
    return ZMap(
        active_patch_count=msn_data[c.payload_offset],
        cells=list(msn_data[c.payload_offset + 1:c.payload_offset + 1 + 80 * 80]),
    )


def decode_zone_sidecar_name(msn_data: bytes, chunks: List[Chunk]) -> str:
    c = first_chunk(chunks, "ZONE")
    if c is None:
        return ""
    # Open76 reads one byte, then ReadCString(13). Our i76.exe trace indicated filename at +9.
    # Support both layouts and prefer the printable one that exists.
    payload = msn_data[c.payload_offset:c.end]
    candidates: List[str] = []
    if len(payload) > 1:
        candidates.append(payload[1:].split(b"\0", 1)[0].decode("ascii", errors="ignore"))
    if len(payload) > 9:
        candidates.append(payload[9:].split(b"\0", 1)[0].decode("ascii", errors="ignore"))
    for s in candidates:
        s = s.strip()
        if s and "." in s:
            return s
    return candidates[0].strip() if candidates else ""


def decode_wrld_filenames(msn_data: bytes, chunks: List[Chunk]) -> Dict[str, str]:
    c = first_chunk(chunks, "WRLD")
    if c is None:
        return {}
    p = c.payload_offset
    # Open76 skips 30 bytes, then reads nine CString(13) fields.
    p += 30
    names = {}
    keys = [
        "palette", "luma_table", "xlucency_table", "objective", "sky_texture",
        "scrounge_texture", "surface_texture", "level_map", "hzd",
    ]
    for key in keys:
        if p >= c.end:
            break
        raw = msn_data[p:min(p + 13, c.end)]
        names[key] = raw.split(b"\0", 1)[0].decode("ascii", errors="ignore")
        p += 13
    return names


def sha1_file(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        while True:
            block = f.read(1024 * 1024)
            if not block:
                break
            h.update(block)
    return h.hexdigest()


def copy_resource(src: Path, out_dir: Path) -> Path:
    out_dir.mkdir(parents=True, exist_ok=True)
    dst = out_dir / src.name.lower()
    if src.resolve() != dst.resolve():
        shutil.copy2(src, dst)
    return dst


def find_files(root: Path) -> List[Path]:
    if root.is_file():
        return [root]
    return [p for p in root.rglob("*") if p.is_file()]


def find_sidecar(msn_path: Path, sidecar_name: str, all_by_lower_name: Dict[str, Path]) -> Optional[Path]:
    candidates = []
    if sidecar_name:
        candidates.extend([
            msn_path.parent / sidecar_name,
            msn_path.parent / sidecar_name.upper(),
            msn_path.parent / sidecar_name.lower(),
            all_by_lower_name.get(sidecar_name.lower()),
        ])
    for ext in (".ter", ".tab"):
        candidates.extend([
            msn_path.with_suffix(ext),
            msn_path.with_suffix(ext.upper()),
            all_by_lower_name.get(msn_path.stem.lower() + ext),
        ])
    for c in candidates:
        if c and c.exists():
            return c
    return None


def summarize_sidecar(path: Path, active_count: int) -> dict:
    size = path.stat().st_size
    warnings = []
    if size % PAGE_SIZE != 0:
        warnings.append(f"sidecar size 0x{size:x} is not multiple of 0x{PAGE_SIZE:x}")
    page_count = size // PAGE_SIZE
    if active_count and page_count < active_count:
        warnings.append(f"sidecar has {page_count} pages but ZMAP active count is {active_count}")

    pages = []
    with path.open("rb") as f:
        for page in range(page_count):
            raw = f.read(PAGE_SIZE)
            if len(raw) < PAGE_SIZE:
                break
            words = struct.unpack("<" + "H" * (PAGE_W * PAGE_H), raw)
            heights = [w & 0x0FFF for w in words]
            pages.append({
                "page_index": page,
                "min_low12": min(heights),
                "max_low12": max(heights),
                "surface_classes": sorted({(w >> 13) & 7 for w in words}),
                "surface_flag_count": sum(1 for w in words if w & 0x1000),
            })
    return {
        "byte_size": size,
        "page_count": page_count,
        "page_size": PAGE_SIZE,
        "pages": pages,
        "warnings": warnings,
    }


def write_obj(path: Path, sidecar_path: Path, zmap: ZMap, horizontal_scale: float, vertical_scale: float) -> None:
    origins = zmap.origins_by_page()
    data = sidecar_path.read_bytes()
    page_count = len(data) // PAGE_SIZE

    verts = []
    faces = []
    for page in range(page_count):
        words = struct.unpack_from("<" + "H" * (PAGE_W * PAGE_H), data, page * PAGE_SIZE)
        ox, oz = origins.get(page, (page, 0))
        base_x = ox * PAGE_W * horizontal_scale
        base_z = oz * PAGE_H * horizontal_scale
        vbase = len(verts) + 1

        # Open76 extends each patch to 129x129 by copying neighbor edges. We emit 128x128 here;
        # Blender seam stitching can be added later.
        for z in range(PAGE_H):
            for x in range(PAGE_W):
                h = words[z * PAGE_W + x] & 0x0FFF
                verts.append((base_x + x * horizontal_scale, h * vertical_scale, base_z + z * horizontal_scale))

        for z in range(PAGE_H - 1):
            for x in range(PAGE_W - 1):
                v0 = vbase + z * PAGE_W + x
                faces.append((v0, v0 + 1, v0 + PAGE_W + 1, v0 + PAGE_W))

    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        f.write("# Interstate '76 Open76-aligned terrain OBJ\n")
        f.write(f"# sidecar={sidecar_path.name} pages={page_count}\n")
        for x, y, z in verts:
            f.write(f"v {x:.6f} {y:.6f} {z:.6f}\n")
        for a, b, c, d in faces:
            f.write(f"f {a} {b} {c} {d}\n")


def resource_inventory(files: List[Path]) -> Dict[str, int]:
    inv: Dict[str, int] = {}
    for p in files:
        ext = p.suffix.lower()
        inv[ext] = inv.get(ext, 0) + 1
    return dict(sorted(inv.items()))


def export_package(input_path: Path, out_dir: Path, emit_obj: bool, horizontal_scale: float, vertical_scale: float, fail_empty: bool) -> dict:
    if not input_path.exists():
        raise FileNotFoundError(input_path)

    files = find_files(input_path)
    all_by_lower_name = {p.name.lower(): p for p in files}
    mission_files = [p for p in files if p.suffix.lower() in {".msn", ".lvl"}]

    out_dir.mkdir(parents=True, exist_ok=True)
    raw_dir = out_dir / "terrain_raw"
    obj_dir = out_dir / "terrain_obj"

    manifest = {
        "format": "i76_open76_aligned_blender_manifest",
        "version": 4,
        "source": str(input_path),
        "resource_inventory": resource_inventory(files),
        "coordinate_system": {
            "x": "I76 world X",
            "y": "height",
            "z": "I76 world Z",
            "horizontal_sample_scale_default": horizontal_scale,
            "vertical_scale_default": vertical_scale,
        },
        "terrain": [],
        "supporting_resources": [],
        "notes": [
            "Validated against Open76: terrain comes from BWD2 TDEF/ZMAP/ZONE sidecar pages, not LUM/TBL/TAB alone.",
            "LUM/TBL are WRLD metadata tables and are not used as height by this exporter.",
            "Retail ZFS without mission .MSN/.LVL sidecars is insufficient for game-faithful terrain mesh reconstruction by this path.",
        ],
    }

    for p in files:
        if p.suffix.lower() in {".lum", ".tbl", ".tab", ".hzd", ".rtm", ".npt"}:
            manifest["supporting_resources"].append({
                "name": p.name,
                "path": str(p),
                "ext": p.suffix.lower(),
                "size": p.stat().st_size,
            })

    for msn in mission_files:
        try:
            data = msn.read_bytes()
            chunks = parse_tree(data)
            zmap = decode_zmap(data, chunks)
            sidecar_name = decode_zone_sidecar_name(data, chunks)
            wrld = decode_wrld_filenames(data, chunks)
            if zmap is None:
                manifest.setdefault("warnings", []).append(f"{msn}: no ZMAP chunk found")
                continue
            sidecar = find_sidecar(msn, sidecar_name, all_by_lower_name)
            if sidecar is None:
                manifest.setdefault("warnings", []).append(f"{msn}: no terrain sidecar found for ZONE name {sidecar_name!r}")
                continue

            copied = copy_resource(sidecar, raw_dir)
            entry = {
                "mission": str(msn),
                "name": msn.stem,
                "sidecar_name_from_zone": sidecar_name,
                "sidecar_path": str(copied),
                "sidecar_sha1": sha1_file(copied),
                "wrld_filenames": wrld,
                "zmap": zmap.to_dict(),
                "sidecar": summarize_sidecar(copied, zmap.active_patch_count),
                "height_decode": "Open76: normalized=(word&0x0fff)/4096.0; OBJ height=(word&0x0fff)*vertical_scale",
                "import_enabled": True,
            }
            if emit_obj:
                obj_path = obj_dir / f"{msn.stem.lower()}.terrain.obj"
                write_obj(obj_path, copied, zmap, horizontal_scale, vertical_scale)
                entry["preview_obj"] = str(obj_path)
            manifest["terrain"].append(entry)
        except Exception as e:
            manifest.setdefault("warnings", []).append(f"{msn}: {type(e).__name__}: {e}")

    manifest_path = out_dir / "i76_level_blender_manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    print(json.dumps({
        "manifest": str(manifest_path),
        "mission_files": len(mission_files),
        "terrain_entries": len(manifest["terrain"]),
        "inventory": manifest["resource_inventory"],
    }, indent=2))

    if fail_empty and not manifest["terrain"]:
        raise SystemExit(
            "No Open76-style terrain entries found. Need .MSN/.LVL files with TDEF/ZMAP/ZONE and matching .TER/.TAB sidecar."
        )
    return manifest


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("input", type=Path, help="Directory containing .MSN/.LVL plus sidecar .TER/.TAB, or a mission file")
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--no-obj", action="store_true")
    ap.add_argument("--horizontal-scale", type=float, default=DEFAULT_HORIZONTAL_SCALE)
    ap.add_argument("--vertical-scale", type=float, default=DEFAULT_VERTICAL_SCALE)
    ap.add_argument("--fail-empty", action="store_true")
    args = ap.parse_args()

    export_package(args.input, args.out_dir, not args.no_obj, args.horizontal_scale, args.vertical_scale, args.fail_empty)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
