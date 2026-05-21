#!/usr/bin/env python3
"""
i76_palette_census_v1.py

Palette census/extractor for Interstate '76 resources.

What it does:
  * Parses I76.ZFS/ZFSF records.
  * Decompresses records using system liblzo2 via ctypes.
  * Extracts top-level ACT-like 768-byte RGB palettes.
  * Extracts trailing PCX 768-byte palettes when present.
  * Extracts the known runtime game palette from i76.exe VA 0x004fa170.
  * Writes .act files, swatch PNG/PPM previews, and TSV/JSON reports.

This is deliberately a census tool, not a final palette-assignment oracle.
Use the report to decide which palette should drive M16/VQM previews/materials.
"""
from __future__ import annotations

import argparse
import ctypes
import ctypes.util
import hashlib
import json
import math
import os
import struct
import sys
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


@dataclass
class ZfsRecord:
    name: str
    file_offset: int
    record_id: int
    stored_size: int
    unix_timestamp: int
    flags: int
    logical_size: int


@dataclass
class PaletteRow:
    source_kind: str
    source_name: str
    record_id: int
    ext: str
    offset: int
    size: int
    rgb_max: int
    rgb_min: int
    unique_colors: int
    sha1: str
    out_act: str
    out_swatch: str
    notes: str


def cstring(b: bytes) -> str:
    return b.split(b"\0", 1)[0].decode("ascii", "replace").strip()


def safe_name(s: str) -> str:
    import re
    return re.sub(r"[^A-Za-z0-9._+-]+", "_", s) or "unnamed"


def parse_zfs_records(path: Path) -> Tuple[dict, List[ZfsRecord]]:
    with path.open("rb") as f:
        hdr = f.read(0x1c)
        if len(hdr) != 0x1c:
            raise ValueError("short ZFS header")
        magic, version, name_size, per_dtable, record_count, xor_key, first_dtable = struct.unpack("<4sIIIIII", hdr)
        if magic != b"ZFSF":
            raise ValueError(f"not ZFSF: {magic!r}")
        header = {
            "magic": magic.decode("ascii"),
            "version": version,
            "record_name_size": name_size,
            "records_per_dtable": per_dtable,
            "record_count": record_count,
            "xor_key": xor_key,
            "first_dtable_offset": first_dtable,
        }
        records: List[ZfsRecord] = []
        off = first_dtable
        for _di in range(record_count // per_dtable + 2):
            if not off:
                break
            f.seek(off)
            block = f.read(4 + per_dtable * 0x24)
            if len(block) < 4:
                break
            next_off = struct.unpack_from("<I", block, 0)[0]
            for i in range(per_dtable):
                ro = 4 + i * 0x24
                if ro + 0x24 > len(block):
                    break
                name = cstring(block[ro:ro+16])
                file_offset, record_id, stored_size, unix_timestamp, flags_size = struct.unpack_from("<IIIII", block, ro + 16)
                flags = flags_size & 0xff
                logical_size = flags_size >> 8
                if name and not (flags & 1):
                    records.append(ZfsRecord(name, file_offset, record_id, stored_size, unix_timestamp, flags, logical_size))
            off = next_off
        return header, records[:record_count]


class Lzo:
    def __init__(self) -> None:
        libname = ctypes.util.find_library("lzo2")
        if not libname:
            raise RuntimeError("liblzo2 not found")
        self.lib = ctypes.CDLL(libname)
        self.lib.lzo1x_decompress_safe.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_void_p, ctypes.POINTER(ctypes.c_size_t), ctypes.c_void_p]
        self.lib.lzo1x_decompress_safe.restype = ctypes.c_int
        self.lib.lzo1y_decompress_safe.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_void_p, ctypes.POINTER(ctypes.c_size_t), ctypes.c_void_p]
        self.lib.lzo1y_decompress_safe.restype = ctypes.c_int

    def decompress(self, data: bytes, out_len: int, mode: int) -> bytes:
        if mode == 0:
            return data
        out = ctypes.create_string_buffer(out_len)
        out_size = ctypes.c_size_t(out_len)
        src = ctypes.create_string_buffer(data)
        if mode == 2:
            rc = self.lib.lzo1x_decompress_safe(src, len(data), out, ctypes.byref(out_size), None)
        elif mode == 4:
            rc = self.lib.lzo1y_decompress_safe(src, len(data), out, ctypes.byref(out_size), None)
        else:
            raise ValueError(f"unsupported compression mode {mode}")
        if rc != 0:
            raise RuntimeError(f"lzo mode {mode} failed rc={rc}")
        return out.raw[:out_size.value]


def read_record_payload(zfs_path: Path, rec: ZfsRecord, lzo: Lzo) -> bytes:
    with zfs_path.open("rb") as f:
        f.seek(rec.file_offset)
        stored = f.read(rec.stored_size)
    return lzo.decompress(stored, rec.logical_size, rec.flags)


def palette_stats(pal: bytes) -> Tuple[int, int, int, str]:
    vals = list(pal)
    triples = [tuple(pal[i:i+3]) for i in range(0, min(len(pal), 768), 3)]
    return max(vals), min(vals), len(set(triples)), hashlib.sha1(pal).hexdigest()


def write_swatch(pal: bytes, path_no_ext: Path, scale: int = 16) -> str:
    w = 16 * scale
    h = 16 * scale
    pixels = bytearray(w * h * 3)
    for idx in range(256):
        r, g, b = pal[idx*3:idx*3+3]
        x0 = (idx % 16) * scale
        y0 = (idx // 16) * scale
        for y in range(y0, y0 + scale):
            for x in range(x0, x0 + scale):
                off = (y * w + x) * 3
                pixels[off:off+3] = bytes((r, g, b))
    try:
        from PIL import Image  # type: ignore
        img = Image.frombytes("RGB", (w, h), bytes(pixels))
        out = path_no_ext.with_suffix(".png")
        img.save(out)
        return out.name
    except Exception:
        out = path_no_ext.with_suffix(".ppm")
        with out.open("wb") as f:
            f.write(f"P6\n{w} {h}\n255\n".encode("ascii"))
            f.write(pixels)
        return out.name


def maybe_scale_palette(pal: bytes, mode: str) -> Tuple[bytes, str]:
    if mode == "raw":
        return pal, "raw"
    if mode == "x4":
        return bytes(min(255, v * 4) for v in pal), "x4"
    # auto: I76 runtime palette is often low-range 0..63. Scale for external PNG previews.
    mx = max(pal) if pal else 0
    if mx <= 63:
        return bytes(min(255, v * 4) for v in pal), "auto_x4_from_0_63"
    return pal, "auto_raw_0_255"


def write_palette(out_dir: Path, source_kind: str, source_name: str, record_id: int, ext: str, offset: int, pal_raw: bytes, scale_mode: str, notes: str) -> PaletteRow:
    pal, scale_note = maybe_scale_palette(pal_raw, scale_mode)
    mx, mn, uniq, sha1 = palette_stats(pal)
    base = safe_name(f"{source_kind}_{record_id}_{source_name}_{offset}_{scale_note}")
    act_path = out_dir / "palettes" / (base + ".act")
    act_path.parent.mkdir(parents=True, exist_ok=True)
    act_path.write_bytes(pal)
    swatch_name = write_swatch(pal, act_path.with_suffix(""))
    return PaletteRow(
        source_kind=source_kind,
        source_name=source_name,
        record_id=record_id,
        ext=ext,
        offset=offset,
        size=len(pal),
        rgb_max=mx,
        rgb_min=mn,
        unique_colors=uniq,
        sha1=sha1,
        out_act=str(act_path.relative_to(out_dir)),
        out_swatch=str((act_path.parent / swatch_name).relative_to(out_dir)),
        notes=(notes + ";" if notes else "") + scale_note,
    )


def extract_binary_palette(exe_path: Path, va: int = 0x004fa170) -> bytes:
    data = exe_path.read_bytes()
    pe_off = struct.unpack_from("<I", data, 0x3c)[0]
    if data[pe_off:pe_off+4] != b"PE\0\0":
        raise ValueError("not a PE file")
    coff = pe_off + 4
    _machine, nsec, _ts, _ptrsym, _nsym, opt_size, _chars = struct.unpack_from("<HHIIIHH", data, coff)
    opt = coff + 20
    image_base = struct.unpack_from("<I", data, opt + 28)[0]
    rva = va - image_base
    sec = opt + opt_size
    for i in range(nsec):
        s = data[sec+i*40:sec+(i+1)*40]
        name = cstring(s[:8])
        virt_size, virt_addr, raw_size, raw_ptr = struct.unpack_from("<IIII", s, 8)
        if virt_addr <= rva < virt_addr + max(virt_size, raw_size):
            off = raw_ptr + (rva - virt_addr)
            return data[off:off+768]
    raise ValueError(f"VA {va:#x} not mapped")


def looks_like_pcx(data: bytes) -> bool:
    return len(data) > 800 and data[0] == 0x0a and data[-769] == 0x0c


def write_tsv(path: Path, rows: List[PaletteRow]) -> None:
    fields = list(asdict(rows[0]).keys()) if rows else ["source_kind"]
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(fields) + "\n")
        for r in rows:
            d = asdict(r)
            f.write("\t".join(str(d.get(k, "")).replace("\t", " ").replace("\n", " ") for k in fields) + "\n")


def main(argv=None) -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--zfs", required=True, type=Path)
    ap.add_argument("--exe", type=Path, default=None)
    ap.add_argument("--out", required=True, type=Path)
    ap.add_argument("--scale", choices=["auto", "raw", "x4"], default="auto", help="How to write extracted palettes for preview/material PNG usage")
    ap.add_argument("--scan-all-768", action="store_true", help="Also treat any 768-byte top-level payload as palette candidate")
    args = ap.parse_args(argv)

    args.out.mkdir(parents=True, exist_ok=True)
    header, records = parse_zfs_records(args.zfs)
    lzo = Lzo()
    rows: List[PaletteRow] = []
    errors: List[dict] = []

    if args.exe:
        try:
            pal = extract_binary_palette(args.exe)
            rows.append(write_palette(args.out, "exe_va_004fa170", args.exe.name, -1, "exe", 0, pal, args.scale, "known runtime game palette"))
        except Exception as e:
            errors.append({"source": str(args.exe), "error": str(e)})

    for rec in records:
        ext = rec.name.rsplit(".", 1)[-1].lower() if "." in rec.name else ""
        should = ext in {"act", "pcx"} or (args.scan_all_768 and rec.logical_size == 768)
        if not should:
            continue
        try:
            data = read_record_payload(args.zfs, rec, lzo)
        except Exception as e:
            errors.append({"source": rec.name, "record_id": rec.record_id, "error": str(e)})
            continue
        if ext == "act" and len(data) >= 768:
            rows.append(write_palette(args.out, "zfs_act", rec.name, rec.record_id, ext, 0, data[:768], args.scale, f"logical_size={len(data)}"))
        elif ext == "pcx" and looks_like_pcx(data):
            rows.append(write_palette(args.out, "zfs_pcx_trailing", rec.name, rec.record_id, ext, len(data)-768, data[-768:], args.scale, f"logical_size={len(data)}"))
        elif args.scan_all_768 and len(data) == 768:
            rows.append(write_palette(args.out, "zfs_768_payload", rec.name, rec.record_id, ext, 0, data, args.scale, "exact 768-byte payload"))

    # Deduplicate report helper.
    sha_counts: Dict[str, int] = {}
    for r in rows:
        sha_counts[r.sha1] = sha_counts.get(r.sha1, 0) + 1
    unique = sorted(sha_counts.items(), key=lambda kv: (-kv[1], kv[0]))

    write_tsv(args.out / "palette_candidates.tsv", rows)
    (args.out / "palette_candidates.json").write_text(json.dumps([asdict(r) for r in rows], indent=2, sort_keys=True), encoding="utf-8")
    (args.out / "palette_unique_sha1.tsv").write_text("sha1\tcount\n" + "".join(f"{s}\t{c}\n" for s, c in unique), encoding="utf-8")
    (args.out / "summary.json").write_text(json.dumps({
        "zfs_header": header,
        "records": len(records),
        "palette_rows": len(rows),
        "unique_palette_sha1": len(unique),
        "errors": errors[:50],
        "error_count": len(errors),
        "notes": "ACT and PCX trailing palettes plus known i76.exe runtime palette. Values may be x4-scaled for external RGB previews depending on --scale.",
    }, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps({"out": str(args.out), "palette_rows": len(rows), "unique_palette_sha1": len(unique), "error_count": len(errors)}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
