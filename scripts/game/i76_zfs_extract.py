#!/usr/bin/env python3
"""
Interstate '76 / Activision ZFSF archive extractor.

Archive model recovered from i76.exe:
  Header:
    magic               'ZFSF'
    version             uint32, usually 1
    record_name_size    uint32, usually 0x10
    records_per_dtable  uint32, usually 100
    record_count        uint32
    xor_key             uint32, usually 0 in retail I76.ZFS
    first_dtable_offset uint32

  DTable chain:
    uint32 next_dtable_offset
    records_per_dtable * zfsf_record

  Record:
    char     name[16]
    uint32   file_offset      absolute payload offset in ZFS
    uint32   record_id
    uint32   stored_size      compressed/raw byte count
    uint32   unix_timestamp
    uint32   flags_size       low byte flags/mode, upper 24 bits logical size

  flags/mode:
    bit 0x01  tombstone/inactive
    0x02      LZO1X compressed payload
    0x04      LZO1Y compressed payload
    otherwise uncompressed

Dependencies:
  - Python 3.8+
  - liblzo2 shared library for compressed records:
      Debian/Ubuntu: sudo apt install liblzo2-2
    The script loads liblzo2 with ctypes; no Python lzo package required.

Typical usage:
  python3 i76_zfs_extract.py I76.ZFS --out-dir scratch_data/i76_zfs_extract
  python3 i76_zfs_extract.py I76.ZFS --out-dir scratch_data/i76_zfs_extract --ext .tab .hzd .npt .rtm .lum .tbl
  python3 i76_zfs_extract.py I76.ZFS --list-only --json-out scratch_data/i76_zfs_manifest.json

Notes:
  - I76.ZIX is accepted for bookkeeping, but retail extraction is driven by the ZFS dtable.
  - xor_key is reported. Retail I76.ZFS uses xor_key=0; nonzero XOR variants are not transformed
    unless --allow-nonzero-xor is supplied, and even then no XOR transform is currently guessed.
"""

from __future__ import annotations

import argparse
import ctypes
import ctypes.util
import dataclasses
import datetime as _dt
import json
import re
import struct
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple


ZFS_HEADER_STRUCT = struct.Struct("<4sIIIIII")
RECORD_STRUCT = struct.Struct("<16sIIIII")
DTABLE_NEXT_STRUCT = struct.Struct("<I")

FLAG_INACTIVE = 0x01
MODE_LZO1X = 0x02
MODE_LZO1Y = 0x04


@dataclasses.dataclass
class ZfsHeader:
    magic: str
    version: int
    record_name_size: int
    records_per_dtable: int
    record_count: int
    xor_key: int
    first_dtable_offset: int

    def to_dict(self) -> dict:
        return dataclasses.asdict(self)


@dataclasses.dataclass
class ZfsRecord:
    index: int
    table_index: int
    slot_index: int
    name: str
    file_offset: int
    record_id: int
    stored_size: int
    unix_timestamp: int
    flags_size: int
    mode: int
    logical_size: int
    inactive: bool

    @property
    def ext(self) -> str:
        return Path(self.name).suffix.lower()

    def to_dict(self) -> dict:
        out = dataclasses.asdict(self)
        out["ext"] = self.ext
        if self.unix_timestamp:
            try:
                out["timestamp_iso_utc"] = _dt.datetime.utcfromtimestamp(self.unix_timestamp).isoformat() + "Z"
            except Exception:
                out["timestamp_iso_utc"] = None
        else:
            out["timestamp_iso_utc"] = None
        return out


class LzoDecompressor:
    def __init__(self, required: bool = True):
        self.lib = self._load_lib()
        if self.lib is None:
            if required:
                raise RuntimeError("Could not load liblzo2. Install it with: sudo apt install liblzo2-2")
            return

        try:
            init = self.lib.__lzo_init_v2
            init.argtypes = [
                ctypes.c_uint, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int,
                ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int,
            ]
            init.restype = ctypes.c_int
            rc = init(
                0x2080,
                ctypes.sizeof(ctypes.c_short),
                ctypes.sizeof(ctypes.c_int),
                ctypes.sizeof(ctypes.c_long),
                ctypes.sizeof(ctypes.c_size_t),
                ctypes.sizeof(ctypes.c_void_p),
                ctypes.sizeof(ctypes.c_void_p),
                ctypes.sizeof(ctypes.c_void_p),
                ctypes.sizeof(ctypes.c_uint32),
                ctypes.sizeof(ctypes.c_size_t),
            )
            if rc != 0:
                raise RuntimeError(f"__lzo_init_v2 failed with rc={rc}")
        except AttributeError:
            pass

        self._setup_safe("lzo1x_decompress_safe")
        self._setup_safe("lzo1y_decompress_safe")

    def _load_lib(self):
        names = [ctypes.util.find_library("lzo2"), "liblzo2.so.2", "liblzo2.so"]
        for name in names:
            if not name:
                continue
            try:
                return ctypes.CDLL(name)
            except OSError:
                continue
        return None

    def _setup_safe(self, name: str) -> None:
        fn = getattr(self.lib, name)
        fn.argtypes = [
            ctypes.c_void_p,
            ctypes.c_size_t,
            ctypes.c_void_p,
            ctypes.POINTER(ctypes.c_size_t),
            ctypes.c_void_p,
        ]
        fn.restype = ctypes.c_int

    def decompress(self, mode: int, payload: bytes, logical_size: int) -> bytes:
        if mode == MODE_LZO1X:
            fn = self.lib.lzo1x_decompress_safe
        elif mode == MODE_LZO1Y:
            fn = self.lib.lzo1y_decompress_safe
        else:
            raise ValueError(f"unsupported LZO mode 0x{mode:02x}")

        src = ctypes.create_string_buffer(payload)
        dst = ctypes.create_string_buffer(logical_size)
        out_len = ctypes.c_size_t(logical_size)

        rc = fn(
            ctypes.byref(src),
            len(payload),
            ctypes.byref(dst),
            ctypes.byref(out_len),
            None,
        )
        if rc != 0:
            raise RuntimeError(f"LZO decompress failed rc={rc}, mode=0x{mode:02x}, stored={len(payload)}, logical={logical_size}")
        return dst.raw[:out_len.value]


def parse_header(data: bytes) -> ZfsHeader:
    if len(data) < ZFS_HEADER_STRUCT.size:
        raise ValueError("file too small for ZFSF header")
    magic, version, name_size, per_table, count, xor_key, first_dtable = ZFS_HEADER_STRUCT.unpack_from(data, 0)
    if magic != b"ZFSF":
        raise ValueError(f"bad magic {magic!r}; expected b'ZFSF'")
    if name_size != 0x10:
        raise ValueError(f"unexpected record name size 0x{name_size:x}; this extractor expects 0x10")
    if per_table <= 0 or per_table > 10000:
        raise ValueError(f"implausible records_per_dtable={per_table}")
    return ZfsHeader(
        magic=magic.decode("ascii"),
        version=version,
        record_name_size=name_size,
        records_per_dtable=per_table,
        record_count=count,
        xor_key=xor_key,
        first_dtable_offset=first_dtable,
    )


def clean_name(raw: bytes) -> str:
    s = raw.split(b"\0", 1)[0].decode("ascii", errors="replace").strip()
    if not s:
        return ""
    s = s.replace("\\", "/").split("/")[-1]
    s = re.sub(r"[^A-Za-z0-9._$#@!+\-]+", "_", s)
    return s


def parse_records(data: bytes, header: ZfsHeader) -> Tuple[List[ZfsRecord], List[dict]]:
    records: List[ZfsRecord] = []
    dtables: List[dict] = []
    off = header.first_dtable_offset
    table_index = 0
    seen_offsets = set()

    while off != 0 and len(records) < header.record_count:
        if off in seen_offsets:
            raise ValueError(f"dtable loop detected at 0x{off:x}")
        seen_offsets.add(off)

        if off + DTABLE_NEXT_STRUCT.size > len(data):
            raise ValueError(f"dtable {table_index} next pointer out of range at 0x{off:x}")

        next_off = DTABLE_NEXT_STRUCT.unpack_from(data, off)[0]
        dtables.append({"table_index": table_index, "offset": off, "next_offset": next_off})

        rec_base = off + DTABLE_NEXT_STRUCT.size
        for slot in range(header.records_per_dtable):
            if len(records) >= header.record_count:
                break
            roff = rec_base + slot * RECORD_STRUCT.size
            if roff + RECORD_STRUCT.size > len(data):
                raise ValueError(f"record out of range: table={table_index} slot={slot} offset=0x{roff:x}")

            raw_name, file_offset, record_id, stored_size, unix_ts, flags_size = RECORD_STRUCT.unpack_from(data, roff)
            mode = flags_size & 0xFF
            logical_size = (flags_size >> 8) & 0x00FFFFFF
            inactive = (mode & FLAG_INACTIVE) != 0
            name = clean_name(raw_name)

            records.append(ZfsRecord(
                index=len(records),
                table_index=table_index,
                slot_index=slot,
                name=name,
                file_offset=file_offset,
                record_id=record_id,
                stored_size=stored_size,
                unix_timestamp=unix_ts,
                flags_size=flags_size,
                mode=mode,
                logical_size=logical_size,
                inactive=inactive,
            ))

        off = next_off
        table_index += 1

    if len(records) != header.record_count:
        raise ValueError(f"expected {header.record_count} records, parsed {len(records)}")

    return records, dtables


def read_payload(zfs_data: bytes, rec: ZfsRecord) -> bytes:
    if rec.file_offset + rec.stored_size > len(zfs_data):
        raise ValueError(
            f"{rec.name} payload out of range: offset=0x{rec.file_offset:x} stored=0x{rec.stored_size:x} file=0x{len(zfs_data):x}"
        )
    return zfs_data[rec.file_offset:rec.file_offset + rec.stored_size]


def decode_payload(zfs_data: bytes, rec: ZfsRecord, lzo: Optional[LzoDecompressor]) -> Tuple[bytes, str]:
    payload = read_payload(zfs_data, rec)
    mode_no_inactive = rec.mode & ~FLAG_INACTIVE

    if rec.inactive:
        return payload, "inactive_raw"

    if mode_no_inactive == 0:
        return payload, "raw"

    if mode_no_inactive in (MODE_LZO1X, MODE_LZO1Y):
        if lzo is None:
            raise RuntimeError(f"{rec.name} is compressed but LZO is disabled/unavailable")
        if rec.logical_size <= 0:
            raise ValueError(f"{rec.name} has compressed mode but logical_size={rec.logical_size}")
        out = lzo.decompress(mode_no_inactive, payload, rec.logical_size)
        if len(out) != rec.logical_size:
            raise RuntimeError(f"{rec.name} decompressed size mismatch: got {len(out)}, expected {rec.logical_size}")
        return out, "lzo1x" if mode_no_inactive == MODE_LZO1X else "lzo1y"

    return payload, f"unknown_mode_0x{rec.mode:02x}_raw"


def extension_matches(rec: ZfsRecord, exts: Optional[set]) -> bool:
    if not exts:
        return True
    return rec.ext in exts


def unique_output_path(out_dir: Path, name: str, index: int, collision_mode: str) -> Path:
    if not name:
        name = f"record_{index:05d}.bin"
    candidate = out_dir / name.lower()
    if collision_mode == "overwrite" or not candidate.exists():
        return candidate
    stem = candidate.stem
    suffix = candidate.suffix
    return candidate.with_name(f"{stem}__rec{index:05d}{suffix}")


def summarize_records(records: Iterable[ZfsRecord]) -> dict:
    by_ext: Dict[str, int] = {}
    by_mode: Dict[str, int] = {}
    live = 0
    inactive = 0

    for r in records:
        by_ext[r.ext or "<none>"] = by_ext.get(r.ext or "<none>", 0) + 1
        mode = f"0x{r.mode:02x}"
        by_mode[mode] = by_mode.get(mode, 0) + 1
        if r.inactive:
            inactive += 1
        else:
            live += 1

    return {
        "live_records": live,
        "inactive_records": inactive,
        "by_extension": dict(sorted(by_ext.items())),
        "by_mode": dict(sorted(by_mode.items())),
    }


def write_manifest(path: Path, manifest: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(manifest, indent=2, sort_keys=True), encoding="utf-8")


def write_listing_tsv(path: Path, records: List[ZfsRecord]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("index\tname\text\tfile_offset\tstored_size\tlogical_size\tmode\tinactive\trecord_id\ttimestamp\n")
        for r in records:
            f.write(
                f"{r.index}\t{r.name}\t{r.ext}\t0x{r.file_offset:08x}\t{r.stored_size}\t"
                f"{r.logical_size}\t0x{r.mode:02x}\t{r.inactive}\t{r.record_id}\t{r.unix_timestamp}\n"
            )


def maybe_read_zix(zix_path: Optional[Path]) -> dict:
    if zix_path is None:
        return {"provided": False}
    if not zix_path.exists():
        return {"provided": True, "exists": False, "path": str(zix_path)}
    data = zix_path.read_bytes()
    return {
        "provided": True,
        "exists": True,
        "path": str(zix_path),
        "size": len(data),
        "first_64_hex": data[:64].hex(),
        "note": "ZIX is recorded for correlation only; extraction is driven by ZFSF dtables.",
    }


def main() -> int:
    ap = argparse.ArgumentParser(description="Extract Interstate '76 ZFSF archives")
    ap.add_argument("zfs", type=Path, help="Input I76.ZFS archive")
    ap.add_argument("--zix", type=Path, default=None, help="Optional I76.ZIX index companion, recorded in manifest")
    ap.add_argument("--out-dir", type=Path, default=Path("i76_zfs_extract"), help="Output directory")
    ap.add_argument("--ext", nargs="*", default=None, help="Optional extension filter, e.g. --ext .tab .hzd .npt .rtm .lum .tbl")
    ap.add_argument("--include-inactive", action="store_true", help="Extract tombstone/inactive records too")
    ap.add_argument("--list-only", action="store_true", help="Only write manifest/listing; do not extract payloads")
    ap.add_argument("--raw", action="store_true", help="Write stored compressed/raw bytes without decompression")
    ap.add_argument("--no-lzo", action="store_true", help="Do not load/use liblzo2")
    ap.add_argument("--collision-mode", choices=["suffix", "overwrite"], default="suffix")
    ap.add_argument("--json-out", type=Path, default=None, help="Explicit manifest JSON path")
    ap.add_argument("--allow-nonzero-xor", action="store_true", help="Allow archives with nonzero xor_key. No XOR transform is currently applied.")
    args = ap.parse_args()

    zfs_path: Path = args.zfs
    if not zfs_path.exists():
        raise FileNotFoundError(zfs_path)

    zfs_data = zfs_path.read_bytes()
    header = parse_header(zfs_data)

    if header.xor_key != 0 and not args.allow_nonzero_xor:
        raise RuntimeError(
            f"Archive xor_key is nonzero: 0x{header.xor_key:08x}. "
            "Retail I76.ZFS uses 0. Re-run with --allow-nonzero-xor to list/extract raw without XOR transform."
        )

    records, dtables = parse_records(zfs_data, header)

    exts = None
    if args.ext:
        exts = {e.lower() if e.startswith(".") else "." + e.lower() for e in args.ext}

    selected = [
        r for r in records
        if (args.include_inactive or not r.inactive) and extension_matches(r, exts)
    ]

    out_dir: Path = args.out_dir
    resources_dir = out_dir / "resources"
    raw_dir = out_dir / "raw_payloads"

    lzo = None
    if not args.raw and not args.no_lzo and any(((r.mode & ~FLAG_INACTIVE) in (MODE_LZO1X, MODE_LZO1Y)) for r in selected if not r.inactive):
        lzo = LzoDecompressor(required=True)

    extracted = []
    errors = []

    if not args.list_only:
        target_dir = raw_dir if args.raw else resources_dir
        target_dir.mkdir(parents=True, exist_ok=True)

        for r in selected:
            try:
                data, method = (read_payload(zfs_data, r), "stored_raw") if args.raw else decode_payload(zfs_data, r, lzo)
                out_path = unique_output_path(target_dir, r.name, r.index, args.collision_mode)
                out_path.parent.mkdir(parents=True, exist_ok=True)
                out_path.write_bytes(data)
                extracted.append({
                    "index": r.index,
                    "name": r.name,
                    "path": str(out_path),
                    "method": method,
                    "stored_size": r.stored_size,
                    "output_size": len(data),
                    "logical_size": r.logical_size,
                    "mode": f"0x{r.mode:02x}",
                })
            except Exception as e:
                errors.append({"index": r.index, "name": r.name, "error": f"{type(e).__name__}: {e}"})

    manifest = {
        "format": "i76_zfs_extract_manifest",
        "version": 1,
        "zfs_path": str(zfs_path),
        "zfs_size": len(zfs_data),
        "zix": maybe_read_zix(args.zix),
        "header": header.to_dict(),
        "dtables": dtables,
        "summary_all_records": summarize_records(records),
        "summary_selected_records": summarize_records(selected),
        "filters": {
            "extensions": sorted(exts) if exts else None,
            "include_inactive": args.include_inactive,
            "raw": args.raw,
            "list_only": args.list_only,
        },
        "records": [r.to_dict() for r in records],
        "selected_record_indices": [r.index for r in selected],
        "extracted": extracted,
        "errors": errors,
    }

    out_dir.mkdir(parents=True, exist_ok=True)
    manifest_path = args.json_out or (out_dir / "zfs_extract_manifest.json")
    listing_path = out_dir / "zfs_records.tsv"
    write_manifest(manifest_path, manifest)
    write_listing_tsv(listing_path, records)

    print(json.dumps({
        "records": len(records),
        "selected": len(selected),
        "extracted": len(extracted),
        "errors": len(errors),
        "manifest": str(manifest_path),
        "listing": str(listing_path),
    }, indent=2))

    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
