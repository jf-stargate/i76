#!/usr/bin/env python3
"""
Interstate '76 ZFS level-resource extractor and first-pass terrain preview exporter.

Purpose:
  - Extract level-related runtime resources from I76.ZFS.
  - Decode LZO1X/LZO1Y records using system liblzo2.
  - Identify likely runtime terrain sidecars: *.TAB records are 0x20000 bytes
    after decompression, i.e. 4 pages * 0x8000 bytes.
  - Emit simple OBJ previews from TAB/TER-like packed terrain pages.

This intentionally targets the retail/archive corpus rather than the editor-only .I76 workspace format.
"""

from __future__ import annotations

import argparse
import ctypes
import ctypes.util
import dataclasses
import json
import re
import struct
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


LEVEL_EXTS_DEFAULT = {
    ".tab", ".hzd", ".npt", ".rtm", ".fsi", ".act", ".lum", ".tbl", ".pcx"
}


@dataclasses.dataclass
class ZfsRecord:
    name: str
    file_offset: int
    record_id: int
    stored_size: int
    timestamp: int
    flags: int
    logical_size: int

    def to_dict(self) -> dict:
        return dataclasses.asdict(self)


class LzoDecoder:
    def __init__(self) -> None:
        path = ctypes.util.find_library("lzo2")
        if not path:
            raise RuntimeError("liblzo2 was not found; install liblzo2-2 or equivalent")
        self.lib = ctypes.CDLL(path)
        for name in ("lzo1x_decompress_safe", "lzo1y_decompress_safe"):
            f = getattr(self.lib, name)
            f.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint), ctypes.c_void_p]
            f.restype = ctypes.c_int

    def decompress(self, mode: int, raw: bytes, out_len: int) -> bytes:
        out = (ctypes.c_ubyte * out_len)()
        out_size = ctypes.c_uint(out_len)
        inp = (ctypes.c_ubyte * len(raw)).from_buffer_copy(raw)
        if mode == 2:
            f = self.lib.lzo1x_decompress_safe
        elif mode == 4:
            f = self.lib.lzo1y_decompress_safe
        else:
            raise ValueError(f"unsupported compression mode/flags 0x{mode:02x}")
        rc = f(inp, len(raw), out, ctypes.byref(out_size), None)
        if rc != 0:
            raise RuntimeError(f"LZO decompress failed rc={rc} mode={mode} stored={len(raw)} logical={out_len} produced={out_size.value}")
        return bytes(out[:out_size.value])


class ZfsArchive:
    def __init__(self, path: Path) -> None:
        self.path = path
        self.data = path.read_bytes()
        self.records = self._parse_records()
        self._lzo: Optional[LzoDecoder] = None

    def _parse_records(self) -> List[ZfsRecord]:
        data = self.data
        if data[:4] != b"ZFSF":
            raise ValueError(f"{self.path} is not a ZFSF archive")
        version, name_size, records_per_table, record_count, xor_key, first_table = struct.unpack_from("<6I", data, 4)
        if version != 1 or name_size != 0x10:
            raise ValueError(f"unexpected ZFSF header version={version} name_size={name_size}")
        records: List[ZfsRecord] = []
        table_off = first_table
        while table_off and table_off < len(data) and len(records) < record_count:
            next_table = struct.unpack_from("<I", data, table_off)[0]
            p = table_off + 4
            for _ in range(records_per_table):
                if len(records) >= record_count:
                    break
                name_raw = data[p:p + name_size]
                name = name_raw.split(b"\0", 1)[0].decode("ascii", errors="ignore")
                file_offset, rid, stored, ts, flags_size = struct.unpack_from("<5I", data, p + name_size)
                records.append(ZfsRecord(
                    name=name,
                    file_offset=file_offset,
                    record_id=rid,
                    stored_size=stored,
                    timestamp=ts,
                    flags=flags_size & 0xFF,
                    logical_size=flags_size >> 8,
                ))
                p += name_size + 20
            table_off = next_table
        return records

    def read_record(self, rec: ZfsRecord) -> bytes:
        raw = self.data[rec.file_offset:rec.file_offset + rec.stored_size]
        if rec.flags & 0x01:
            raise ValueError(f"record {rec.name} is tombstoned/inactive")
        if rec.flags == 0:
            return raw
        if self._lzo is None:
            self._lzo = LzoDecoder()
        return self._lzo.decompress(rec.flags, raw, rec.logical_size)


def is_level_resource(name: str, include_exts: set[str]) -> bool:
    lower = name.lower()
    ext = "." + lower.rsplit(".", 1)[1] if "." in lower else ""
    if ext in include_exts:
        return True
    # Include common mission-scoped vehicle configs such as t07cp01.vcf only when explicitly requested elsewhere.
    return False


def parse_zix(path: Optional[Path]) -> Dict[str, int]:
    out: Dict[str, int] = {}
    if not path or not path.exists():
        return out
    for line in path.read_text(errors="ignore").splitlines():
        line = line.strip()
        m = re.match(r"^(\d+)\s+(.+)$", line)
        if m:
            out[m.group(2).lower()] = int(m.group(1))
    return out


def page_summaries(words: List[int]) -> dict:
    heights = [w & 0x0FFF for w in words]
    return {
        "min_height": min(heights),
        "max_height": max(heights),
        "surface_classes": sorted({(w >> 13) & 7 for w in words}),
        "surface_flag_count": sum(1 for w in words if w & 0x1000),
    }


def decode_tab_pages(data: bytes) -> List[List[int]]:
    if len(data) % 0x8000 != 0:
        raise ValueError(f"terrain payload length {len(data)} is not a multiple of 0x8000")
    pages = []
    for i in range(len(data) // 0x8000):
        raw = data[i * 0x8000:(i + 1) * 0x8000]
        pages.append(list(struct.unpack("<" + "H" * (128 * 128), raw)))
    return pages


def write_tab_obj(path: Path, pages: List[List[int]], horizontal_scale: float, vertical_scale: float) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        f.write("# Interstate '76 TAB/TER terrain preview\n")
        f.write(f"# pages={len(pages)} horizontal_scale={horizontal_scale} vertical_scale={vertical_scale}\n")
        vertex_base = 1
        faces: List[Tuple[int, int, int, int]] = []
        for page_index, words in enumerate(pages):
            # Retail TAB records are usually 4 pages. Arrange in a compact 2x2 tile for preview.
            tile_x = page_index % 2
            tile_z = page_index // 2
            base_x = tile_x * 128 * horizontal_scale
            base_z = tile_z * 128 * horizontal_scale
            for z in range(128):
                for x in range(128):
                    h = words[z * 128 + x] & 0x0FFF
                    f.write(f"v {base_x + x * horizontal_scale:.6f} {h * vertical_scale:.6f} {base_z + z * horizontal_scale:.6f}\n")
            for z in range(127):
                for x in range(127):
                    v0 = vertex_base + z * 128 + x
                    faces.append((v0, v0 + 1, v0 + 129, v0 + 128))
            vertex_base += 128 * 128
        for a, b, c, d in faces:
            f.write(f"f {a} {b} {c} {d}\n")


def extract(args: argparse.Namespace) -> dict:
    archive = ZfsArchive(args.zfs)
    zix_flags = parse_zix(args.zix)
    include_exts = {e if e.startswith(".") else "." + e for e in args.ext}
    out_dir: Path = args.out_dir
    res_dir = out_dir / "resources"
    obj_dir = out_dir / "terrain_obj"
    res_dir.mkdir(parents=True, exist_ok=True)
    if args.obj:
        obj_dir.mkdir(parents=True, exist_ok=True)

    summary = {
        "zfs": str(args.zfs),
        "record_count": len(archive.records),
        "extracted": [],
        "terrain_payloads": [],
        "extension_counts": {},
    }

    for rec in archive.records:
        ext = "." + rec.name.lower().rsplit(".", 1)[1] if "." in rec.name else ""
        summary["extension_counts"][ext] = summary["extension_counts"].get(ext, 0) + 1
        if not is_level_resource(rec.name, include_exts):
            continue
        try:
            payload = archive.read_record(rec)
        except Exception as e:
            summary["extracted"].append({"name": rec.name, "error": f"{type(e).__name__}: {e}"})
            continue
        out_path = res_dir / rec.name
        out_path.parent.mkdir(parents=True, exist_ok=True)
        out_path.write_bytes(payload)
        item = rec.to_dict()
        item.update({"decoded_size": len(payload), "out_path": str(out_path), "zix_flag": zix_flags.get(rec.name.lower())})
        summary["extracted"].append(item)

        if ext in {".tab", ".ter"} and len(payload) % 0x8000 == 0:
            pages = decode_tab_pages(payload)
            tinfo = {
                "name": rec.name,
                "decoded_size": len(payload),
                "page_count": len(pages),
                "pages": [dict(page_index=i, **page_summaries(p)) for i, p in enumerate(pages)],
            }
            if args.obj:
                obj_path = obj_dir / f"{Path(rec.name).stem}.terrain.obj"
                write_tab_obj(obj_path, pages, args.horizontal_scale, args.vertical_scale)
                tinfo["obj_path"] = str(obj_path)
            summary["terrain_payloads"].append(tinfo)

    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "zfs_level_extract_summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    return summary


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("zfs", type=Path)
    ap.add_argument("--zix", type=Path, default=None)
    ap.add_argument("--out-dir", type=Path, default=Path("i76_zfs_level_extract"))
    ap.add_argument("--ext", nargs="*", default=sorted(LEVEL_EXTS_DEFAULT), help="extensions to extract")
    ap.add_argument("--obj", action="store_true", help="emit OBJ previews for TAB/TER payloads")
    ap.add_argument("--horizontal-scale", type=float, default=5.0)
    ap.add_argument("--vertical-scale", type=float, default=1.0)
    args = ap.parse_args()
    summary = extract(args)
    print(json.dumps({
        "records": summary["record_count"],
        "extracted": len(summary["extracted"]),
        "terrain_payloads": len(summary["terrain_payloads"]),
        "summary": str(args.out_dir / "zfs_level_extract_summary.json"),
    }, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
