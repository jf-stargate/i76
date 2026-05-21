#!/usr/bin/env python3
"""
i76_vehicle_texture_slot_resolver_v5.py

Vehicle-aware texture/material resolver for Interstate '76.

Purpose:
  Resolve the largest remaining ambiguity in the ZFS asset graph:
  GEO section texture slots such as:
      V1 MD LF.MAP
      V1 BO DY.MAP
      V1 FT TP.MAP
  which are usually not literal missing files. They are vehicle material slots
  resolved through:
      VCF -> VDF + VTF
      VDF -> GEO part names
      VTF -> TMT/MAP texture slots
      TMT -> M16/VQM frame basenames
      VQM -> CBK

This script is report-only. It reads I76.ZFS/ZIX, decompresses in memory,
parses PIX/PAK embedded assets in memory, and emits compact TSV/JSON reports.

Outputs:
  summary.json
  vehicle_roots.tsv
  vehicle_geo_parts.tsv
  vehicle_texture_slot_resolution.tsv
  tmt_frame_resolution.tsv
  vqm_cbk_resolution.tsv
  unresolved_texture_slots.tsv
  unresolved_tmt_frames.tsv
  unresolved_vqm_cbk.tsv
  README.txt

Example:
  python3 i76_vehicle_texture_slot_resolver_v5.py \
      --zfs I76.ZFS \
      --zix I76.ZIX \
      --out i76_vehicle_texture_resolution_v5 \
      --overwrite
"""

from __future__ import annotations

import argparse
import ctypes
import ctypes.util
import csv
import hashlib
import json
import re
import shutil
import struct
import sys
import time
from collections import defaultdict
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Set, Tuple


ZFSF_HEADER_SIZE = 0x1C
ZFSF_RECORD_SIZE = 0x24
ZFSF_DTABLE_RECORDS = 100
ZFSF_DTABLE_SIZE = 4 + ZFSF_RECORD_SIZE * ZFSF_DTABLE_RECORDS

EXPLICIT_REF_RE = re.compile(
    rb"(?i)\b([A-Z0-9_+\-]{1,16})\.(VCF|VDF|VTF|WDF|GDF|GEO|TMT|MAP|M16|VQM|CBK|CDF|TAB|TBL|WAV|SMK)\b"
)
TOKEN_RE = re.compile(rb"[A-Za-z0-9_+\-]{3,16}")
GEO_SLOT_RE = re.compile(rb"(?i)([A-Z0-9][A-Z0-9 ]{1,14}\.MAP)")


@dataclass
class ZfsRecord:
    index: int
    record_id: int
    name: str
    extension: str
    file_offset: int
    stored_size: int
    logical_size: int
    flags_size: int
    compression: int
    compression_name: str
    unix_timestamp: int
    active: bool
    dtable_index: int
    dtable_slot: int


@dataclass
class Asset:
    asset_id: str
    name: str
    norm_name: str
    stem: str
    ext: str
    source: str                 # top_level | embedded
    record_index: int
    parent_record_index: int
    pix_name: str
    pak_name: str
    size: int
    sha256: str
    decoded_type: str


@dataclass
class VehicleRoot:
    vehicle: str
    vehicle_asset_id: str
    vcf_asset_id: str
    vdf_ref: str
    vdf_asset_id: str
    vtf_ref: str
    vtf_asset_id: str
    wdf_refs: str
    gdf_refs: str
    notes: str


@dataclass
class VehicleGeoPart:
    vehicle: str
    vdf: str
    vdf_asset_id: str
    geo_ref: str
    geo_asset_id: str
    geo_name: str
    source: str
    confidence: str
    evidence: str


@dataclass
class TextureSlotResolution:
    vehicle: str
    vcf: str
    vdf: str
    vtf: str
    geo: str
    geo_asset_id: str
    raw_slot: str
    normalized_slot: str
    resolved_kind: str
    resolved_name: str
    resolved_asset_id: str
    confidence: str
    evidence: str


@dataclass
class TmtFrameResolution:
    tmt: str
    tmt_asset_id: str
    frame_token: str
    resolved_m16: str
    resolved_m16_asset_id: str
    resolved_vqm: str
    resolved_vqm_asset_id: str
    confidence: str
    evidence: str


@dataclass
class VqmCbkResolution:
    vqm: str
    vqm_asset_id: str
    cbk_ref: str
    cbk_asset_id: str
    confidence: str
    evidence: str


class Lzo:
    def __init__(self) -> None:
        candidates: List[str] = []
        found = ctypes.util.find_library("lzo2")
        if found:
            candidates.append(found)
        candidates += ["liblzo2.so.2", "liblzo2.so", "lzo2.dll", "liblzo2.dylib"]
        self.lib = None
        last = None
        for c in candidates:
            try:
                self.lib = ctypes.CDLL(c)
                break
            except OSError as e:
                last = e
        if self.lib is None:
            raise RuntimeError(f"Could not load liblzo2; install liblzo2-2. Last error: {last!r}")
        for name in ["lzo1x_decompress_safe", "lzo1y_decompress_safe"]:
            fn = getattr(self.lib, name)
            fn.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_void_p, ctypes.POINTER(ctypes.c_size_t), ctypes.c_void_p]
            fn.restype = ctypes.c_int

    def decompress(self, payload: bytes, logical_size: int, compression: int) -> bytes:
        if compression == 0:
            return payload
        if compression == 0x02:
            fn = self.lib.lzo1x_decompress_safe
        elif compression == 0x04:
            fn = self.lib.lzo1y_decompress_safe
        else:
            raise ValueError(f"unsupported compression mode 0x{compression:02x}")
        src = ctypes.create_string_buffer(payload, len(payload))
        dst = ctypes.create_string_buffer(logical_size)
        out_len = ctypes.c_size_t(logical_size)
        rc = fn(src, len(payload), dst, ctypes.byref(out_len), None)
        if rc != 0:
            raise RuntimeError(f"liblzo failed rc={rc} mode=0x{compression:02x}")
        return dst.raw[: out_len.value]


def norm_name(name: str) -> str:
    return name.replace("\\", "/").split("/")[-1].strip().upper()


def stem_of(name: str) -> str:
    n = norm_name(name)
    return n.rsplit(".", 1)[0] if "." in n else n


def ext_of(name: str) -> str:
    n = norm_name(name)
    return n.rsplit(".", 1)[-1].lower() if "." in n else ""


def sha256_hex(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def compression_name(mode: int) -> str:
    return {0: "stored", 0x02: "lzo1x", 0x04: "lzo1y"}.get(mode, f"unknown_0x{mode:02x}")


def classify_payload(name: str, data: bytes) -> str:
    e = ext_of(name)
    if e == "pix":
        return "pix_text_index"
    if e == "pak":
        return "pak_binary_payload"
    if data[:4] == b"OEG." or e == "geo":
        return "geo_geometry"
    if e == "tmt":
        return "texture_material_table"
    if e == "map":
        return "texture_map"
    if e == "m16":
        return "m16_image_or_texture"
    if e == "vqm":
        return "vqm_image_or_texture"
    if e == "cbk":
        return "vqm_cbk_codebook"
    if data.startswith(b"BWD2"):
        return "bwd2_chunked_resource"
    return f"{e}_payload" if e else "binary_payload"


def safe_ascii(b: bytes) -> str:
    return b.decode("ascii", "replace").replace("\x00", "").strip()


def ensure_clean_dir(path: Path, overwrite: bool) -> None:
    if path.exists():
        if not overwrite:
            raise FileExistsError(f"output exists: {path}; use --overwrite")
        shutil.rmtree(path)
    path.mkdir(parents=True, exist_ok=True)


def write_tsv(path: Path, rows: Iterable[Dict[str, object]], fields: List[str]) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(fields) + "\n")
        for row in rows:
            vals = []
            for field in fields:
                val = str(row.get(field, ""))
                vals.append(val.replace("\t", " ").replace("\r", " ").replace("\n", " "))
            f.write("\t".join(vals) + "\n")


def write_json(path: Path, value: object) -> None:
    path.write_text(json.dumps(value, indent=2, sort_keys=True), encoding="utf-8")


def parse_zfs_records(zfs: Path) -> Tuple[Dict[str, int], List[ZfsRecord]]:
    with zfs.open("rb") as f:
        hdr = f.read(ZFSF_HEADER_SIZE)
        magic, version, name_size, per_dtable, record_count, xor_key, first_dtable = struct.unpack("<4sIIIIII", hdr)
        if magic != b"ZFSF":
            raise ValueError(f"bad ZFSF magic: {magic!r}")
        records: List[ZfsRecord] = []
        dtable = first_dtable
        dtable_idx = 0
        seen = set()
        while dtable and len(records) < record_count:
            if dtable in seen:
                raise ValueError(f"dtable loop at 0x{dtable:x}")
            seen.add(dtable)
            f.seek(dtable)
            data = f.read(ZFSF_DTABLE_SIZE)
            if len(data) != ZFSF_DTABLE_SIZE:
                raise IOError(f"short dtable at 0x{dtable:x}")
            next_dtable = struct.unpack_from("<I", data, 0)[0]
            for slot in range(ZFSF_DTABLE_RECORDS):
                if len(records) >= record_count:
                    break
                off = 4 + slot * ZFSF_RECORD_SIZE
                name = safe_ascii(data[off:off+0x10])
                file_offset, record_id, stored_size, unix_ts, flags_size = struct.unpack_from("<IIIII", data, off + 0x10)
                comp = flags_size & 0xff
                records.append(ZfsRecord(
                    len(records), record_id, name, ext_of(name), file_offset, stored_size,
                    flags_size >> 8, flags_size, comp, compression_name(comp), unix_ts,
                    (comp & 1) == 0, dtable_idx, slot
                ))
            dtable = next_dtable
            dtable_idx += 1
        header = {
            "version": version,
            "record_name_size": name_size,
            "records_per_dtable": per_dtable,
            "record_count": record_count,
            "xor_key": xor_key,
            "first_dtable_offset": first_dtable,
            "dtable_count_parsed": dtable_idx,
        }
        return header, records


def decompress_records(zfs: Path, records: List[ZfsRecord], wanted_exts: Optional[Set[str]]) -> Tuple[Dict[int, bytes], List[Dict[str, object]]]:
    lzo = Lzo()
    payloads: Dict[int, bytes] = {}
    errors: List[Dict[str, object]] = []
    wanted = [r for r in records if wanted_exts is None or r.extension in wanted_exts]
    with zfs.open("rb") as f:
        for i, r in enumerate(wanted):
            if i % 500 == 0:
                print(f"[zfs] {i}/{len(wanted)} {r.name}", file=sys.stderr)
            try:
                f.seek(r.file_offset)
                stored = f.read(r.stored_size)
                if len(stored) != r.stored_size:
                    raise IOError(f"short read got {len(stored)} expected {r.stored_size}")
                # Some tiny uncompressed PIX records in retail I76.ZFS have
                # logical_size == 0 even though stored_size is nonzero. Runtime
                # callers effectively consume the stored payload. Treat that as
                # valid for uncompressed records instead of reporting a false
                # decompression error.
                effective_logical = r.logical_size
                if r.compression == 0 and r.logical_size == 0 and r.stored_size > 0:
                    effective_logical = r.stored_size
                out = lzo.decompress(stored, effective_logical, r.compression)
                if len(out) != effective_logical:
                    raise IOError(f"size mismatch got {len(out)} expected {effective_logical}")
                payloads[r.index] = out
            except Exception as e:
                errors.append({"record_index": r.index, "name": r.name, "error": str(e)})
    return payloads, errors


def parse_pix_index(data: bytes) -> Tuple[List[Tuple[str, int, int]], str]:
    try:
        text = data.decode("ascii")
    except UnicodeDecodeError as e:
        return [], f"ascii decode failed: {e}"
    lines = [ln.strip() for ln in text.splitlines() if ln.strip()]
    if not lines:
        return [], "empty pix"
    try:
        declared = int(lines[0])
    except ValueError:
        return [], f"bad count: {lines[0]!r}"
    out = []
    for lineno, line in enumerate(lines[1:], 2):
        p = line.split()
        if len(p) != 3:
            return out, f"bad line {lineno}: {line!r}"
        try:
            out.append((p[0], int(p[1], 0), int(p[2], 0)))
        except ValueError:
            return out, f"bad numeric line {lineno}: {line!r}"
    if declared != len(out):
        return out, f"declared {declared} parsed {len(out)}"
    return out, ""


class AssetIndex:
    def __init__(self) -> None:
        self.assets: List[Asset] = []
        self.payloads: Dict[str, bytes] = {}
        self.by_norm: Dict[str, List[Asset]] = defaultdict(list)
        self.by_stem_ext: Dict[Tuple[str, str], List[Asset]] = defaultdict(list)

    def add(self, asset: Asset, payload: bytes) -> None:
        self.assets.append(asset)
        self.payloads[asset.asset_id] = payload
        self.by_norm[asset.norm_name].append(asset)
        self.by_stem_ext[(asset.stem, asset.ext)].append(asset)

    def resolve(self, ref: str, ext: Optional[str] = None, source: Optional[Asset] = None, prefer_embedded: bool = True) -> Optional[Asset]:
        refn = norm_name(ref)
        if "." in refn:
            cands = list(self.by_norm.get(refn, []))
            if ext:
                exact = [c for c in cands if c.ext == ext.lower()]
                if exact:
                    cands = exact
        else:
            if not ext:
                return None
            cands = list(self.by_stem_ext.get((refn, ext.lower()), []))
        if not cands:
            return None
        if source and source.source == "embedded":
            same = [c for c in cands if c.parent_record_index == source.parent_record_index]
            if same:
                cands = same
        if prefer_embedded:
            emb = [c for c in cands if c.source == "embedded"]
            if emb:
                cands = emb
        cands.sort(key=lambda a: (a.source != "top_level", a.name, a.asset_id))
        return cands[0]


def build_asset_index(records: List[ZfsRecord], payloads: Dict[int, bytes], max_pix: Optional[int]) -> Tuple[AssetIndex, List[Dict[str, object]]]:
    idx = AssetIndex()
    warnings: List[Dict[str, object]] = []

    # Top-level assets.
    for r in records:
        data = payloads.get(r.index)
        if data is None:
            continue
        asset = Asset(
            f"top:{r.index:06d}:{norm_name(r.name)}", r.name, norm_name(r.name), stem_of(r.name), r.extension,
            "top_level", r.index, -1, "", "", len(data), sha256_hex(data), classify_payload(r.name, data)
        )
        idx.add(asset, data)

    # Embedded PIX/PAK assets.
    by_lower = {r.name.lower(): r for r in records}
    pix_records = [r for r in records if r.extension == "pix" and r.index in payloads]
    if max_pix is not None:
        pix_records = pix_records[:max_pix]
    for i, pix in enumerate(pix_records):
        if i % 250 == 0:
            print(f"[pixpak] {i}/{len(pix_records)} {pix.name}", file=sys.stderr)
        entries, err = parse_pix_index(payloads[pix.index])
        if err:
            warnings.append({"pix": pix.name, "warning": err})
        stem = pix.name.rsplit(".", 1)[0]
        pak_name = stem + ".pak"
        pak = by_lower.get(pak_name.lower())
        if pak is None or pak.index not in payloads:
            warnings.append({"pix": pix.name, "warning": f"missing sibling pak {pak_name}"})
            continue
        pak_data = payloads[pak.index]
        for asset_i, (name, off, size) in enumerate(entries):
            if off < 0 or size < 0 or off + size > len(pak_data):
                warnings.append({"pix": pix.name, "asset": name, "warning": f"slice out of range off={off} size={size} pak_size={len(pak_data)}"})
                continue
            data = pak_data[off:off+size]
            asset = Asset(
                f"emb:{pak.index:06d}:{asset_i:04d}:{norm_name(name)}",
                name, norm_name(name), stem_of(name), ext_of(name), "embedded",
                -1, pak.index, pix.name, pak.name, len(data), sha256_hex(data), classify_payload(name, data)
            )
            idx.add(asset, data)
    return idx, warnings



def resolve_with_leading_byte_trim(idx: AssetIndex, ref: str, ext: str, source: Optional[Asset] = None, prefer_embedded: bool = True) -> Optional[Asset]:
    """Resolve a possibly contaminated fixed-width string.

    Some VTF names are adjacent to binary flag/float bytes, so ASCII regex can
    capture names like Y1cp1FTRT.TMT or OAcp11bdy1.map when the real assets are
    1cp1FTRT.TMT and cp11bdy1.map. Try exact resolution first, then strip up to
    four leading characters from the stem while preserving the extension.
    """
    a = idx.resolve(ref, ext, source=source, prefer_embedded=prefer_embedded)
    if a:
        return a
    rn = norm_name(ref)
    if "." not in rn:
        # Token-only case: try stripping leading characters directly.
        for n in range(1, min(5, len(rn) - 2)):
            a = idx.resolve(rn[n:], ext, source=source, prefer_embedded=prefer_embedded)
            if a:
                return a
        return None
    stem, dot_ext = rn.rsplit(".", 1)
    if dot_ext.lower() != ext.lower():
        return None
    for n in range(1, min(5, len(stem) - 2)):
        candidate = stem[n:] + "." + dot_ext
        a = idx.resolve(candidate, ext, source=source, prefer_embedded=prefer_embedded)
        if a:
            return a
    return None


def explicit_file_refs(data: bytes) -> List[str]:
    seen = set()
    out = []
    for m in EXPLICIT_REF_RE.finditer(data):
        ref = (m.group(1).decode("ascii", "replace") + "." + m.group(2).decode("ascii", "replace")).upper()
        if ref not in seen:
            seen.add(ref)
            out.append(ref)
    return out


def token_stems(data: bytes, max_tokens: int = 8000) -> List[str]:
    seen = set()
    out = []
    for m in TOKEN_RE.finditer(data):
        tok = m.group(0).decode("ascii", "replace").upper()
        if tok.isdigit() or tok in seen:
            continue
        seen.add(tok)
        out.append(tok)
        if len(out) >= max_tokens:
            break
    return out


def normalize_geo_slot(raw: str) -> str:
    s = raw.upper().replace(".MAP", "")
    s = re.sub(r"[^A-Z0-9]+", "", s)
    # Strip vehicle/material prefix like V1, V2, etc.
    s = re.sub(r"^V[0-9]+", "", s)
    # GEO section uses LF while VTF/TMT often uses LT for left side.
    if s.endswith("LF"):
        s = s[:-2] + "LT"
    s = s.replace("BO DY", "BODY")
    return s


def extract_geo_slots(data: bytes) -> List[str]:
    seen = set()
    out = []
    for m in GEO_SLOT_RE.finditer(data):
        raw = safe_ascii(m.group(1))
        # Filter obvious junk: require .MAP suffix and at least one space or V-prefix in most real slots.
        if not raw.upper().endswith(".MAP"):
            continue
        if len(raw) > 16:
            continue
        if raw.upper() not in seen:
            seen.add(raw.upper())
            out.append(raw)
    return out


def parse_vcf_refs(asset: Asset, data: bytes, idx: AssetIndex) -> Tuple[Optional[Asset], Optional[Asset], List[Asset], List[Asset]]:
    refs = explicit_file_refs(data)
    vdf = None
    vtf = None
    wdfs: List[Asset] = []
    gdfs: List[Asset] = []
    for ref in refs:
        e = ext_of(ref)
        a = idx.resolve(ref, e, source=asset, prefer_embedded=False)
        if not a:
            continue
        if e == "vdf" and vdf is None:
            vdf = a
        elif e == "vtf" and vtf is None:
            vtf = a
        elif e == "wdf":
            wdfs.append(a)
        elif e == "gdf":
            gdfs.append(a)
    return vdf, vtf, wdfs, gdfs


def find_vdf_geo_parts(vdf: Asset, data: bytes, idx: AssetIndex) -> List[Tuple[str, Asset, str, str]]:
    out: List[Tuple[str, Asset, str, str]] = []
    seen = set()

    # Explicit .GEO refs if present.
    for ref in explicit_file_refs(data):
        if ext_of(ref) == "geo":
            geo = idx.resolve(ref, "geo", source=vdf)
            if geo and geo.asset_id not in seen:
                seen.add(geo.asset_id)
                out.append((ref, geo, "high", "explicit .GEO reference string"))

    # VDF VGEO/SOBJ part names are often 8-byte stems without extension.
    for tok in token_stems(data):
        if tok in {"WORLD", "NULL", "EXIT", "BWD2", "REV", "VGEO", "SOBJ", "VLOC", "VSHL", "VDFC", "VCHK", "COLP", "WLOC", "HLOC"}:
            continue
        geo = idx.resolve(tok, "geo", source=vdf)
        if geo and geo.asset_id not in seen:
            seen.add(geo.asset_id)
            out.append((tok + ".GEO", geo, "medium", "VDF token matched known .GEO asset stem"))
    return out


def parse_vtf_slots(vtf: Asset, data: bytes, idx: AssetIndex) -> Tuple[List[Asset], List[Asset]]:
    tmts: List[Asset] = []
    maps: List[Asset] = []
    seen = set()
    for ref in explicit_file_refs(data):
        e = ext_of(ref)
        if e not in {"tmt", "map"}:
            continue
        a = resolve_with_leading_byte_trim(idx, ref, e, source=vtf)
        if a and a.asset_id not in seen:
            seen.add(a.asset_id)
            if e == "tmt":
                tmts.append(a)
            else:
                maps.append(a)

    # Also use tokens for fixed-width VTF names.
    for tok in token_stems(data):
        for e in ("tmt", "map"):
            a = resolve_with_leading_byte_trim(idx, tok, e, source=vtf)
            if a and a.asset_id not in seen:
                seen.add(a.asset_id)
                if e == "tmt":
                    tmts.append(a)
                else:
                    maps.append(a)
    return tmts, maps


def slot_to_tmt(slot_norm: str, tmt_assets: List[Asset]) -> Optional[Asset]:
    # Direct suffix match: MDLT -> 1CP1MDLT.TMT.
    exact_suffix = [a for a in tmt_assets if a.stem.endswith(slot_norm)]
    if exact_suffix:
        exact_suffix.sort(key=lambda a: a.name)
        return exact_suffix[0]

    # Common aliases.
    aliases = {
        "MDLF": "MDLT",
        "FTLF": "FTLT",
        "BKLF": "BKLT",
        "BODY": "BDY",
        "BOD": "BDY",
        "BOD Y": "BDY",
    }

    # Cockpit/top-panel vehicle component slots appear in GEO as:
    #   VC C1 TP.MAP -> normalized VCC1TP
    # while matching TMT assets use suffixes like:
    #   1MC1TPTP.TMT, 1CC1TPTP.TMT, ...
    # Treat this as component C# top-panel -> C#TPTP.
    cockpit = re.match(r"^VCC([0-9]+)TP$", slot_norm)
    if cockpit:
        alt2 = "C" + cockpit.group(1) + "TPTP"
        cands = [a for a in tmt_assets if a.stem.endswith(alt2) or alt2 in a.stem]
        if cands:
            cands.sort(key=lambda a: a.name)
            return cands[0]

    alt = aliases.get(slot_norm)
    if alt:
        cands = [a for a in tmt_assets if a.stem.endswith(alt) or alt in a.stem]
        if cands:
            cands.sort(key=lambda a: a.name)
            return cands[0]

    # Last resort: use the final 4 characters for face slots.
    if len(slot_norm) >= 4:
        tail = slot_norm[-4:]
        cands = [a for a in tmt_assets if a.stem.endswith(tail)]
        if cands:
            cands.sort(key=lambda a: a.name)
            return cands[0]
    return None



def clean_ref_stem_maybe_contaminated(ref: str) -> str:
    rn = norm_name(ref)
    stem = rn.rsplit(".", 1)[0] if "." in rn else rn
    # If the exact stem does not resolve, callers may trim leading junk.
    return stem


def parse_vtf_map_ref_stems(vtf: Asset, data: bytes, idx: AssetIndex) -> List[str]:
    """Return VTF MAP slot basenames, including refs that resolve to M16/VQM.

    VTF contains 13 MAP slot names. In practice these often name image basenames
    such as cp11bdy1.map, while the archive stores CP11BDY1.M16 / CP11BDY1.vqm.
    Some strings are contaminated by adjacent bytes, e.g. OAcp11bdy1.map.
    """
    stems: List[str] = []
    seen = set()
    refs = []
    for ref in explicit_file_refs(data):
        if ext_of(ref) == "map":
            refs.append(ref)
    for tok in token_stems(data):
        # Token regex also sees basename and MAP separately. Keep plausible map-ish names.
        if len(tok) >= 5 and any(tag in tok for tag in ("BDY", "FT", "MD", "BK", "TP", "LT", "RT")):
            refs.append(tok + ".MAP")
    for ref in refs:
        rn = norm_name(ref)
        stem = rn.rsplit(".", 1)[0] if "." in rn else rn
        candidates = [stem]
        for n in range(1, min(5, len(stem) - 2)):
            candidates.append(stem[n:])
        for cand in candidates:
            if cand in seen:
                continue
            # Keep only candidates that resolve as a texture image or are good-looking map slots.
            if idx.resolve(cand, "m16", source=vtf) or idx.resolve(cand, "vqm", source=vtf) or idx.resolve(cand, "map", source=vtf):
                seen.add(cand)
                stems.append(cand)
                break
    return stems


def resolve_texture_stem_to_asset(idx: AssetIndex, stem: str, source: Optional[Asset]) -> Optional[Asset]:
    for ex in ("tmt", "m16", "vqm", "map"):
        a = idx.resolve(stem, ex, source=source)
        if a:
            return a
    # Trim leading junk bytes if the string came from binary-adjacent text.
    for n in range(1, min(5, len(stem) - 2)):
        trimmed = stem[n:]
        for ex in ("tmt", "m16", "vqm", "map"):
            a = idx.resolve(trimmed, ex, source=source)
            if a:
                return a
    return None


def resolve_slot_as_direct_texture(raw_slot: str, slot_norm: str, idx: AssetIndex, source: Optional[Asset]) -> Optional[Asset]:
    """Resolve literal-looking GEO slots directly to TMT/M16/VQM/MAP.

    Handles slots like PP11BKX1.MAP, VW14MDU2.MAP, ZDASH101.MAP.
    """
    raw_stem = clean_ref_stem_maybe_contaminated(raw_slot)
    candidates = [raw_stem, slot_norm]
    if slot_norm.endswith("LF"):
        candidates.append(slot_norm[:-2] + "LT")
    if slot_norm == "BODY":
        candidates.extend(["BDY", "BODY"])
    seen = set()
    for c in candidates:
        if c in seen:
            continue
        seen.add(c)
        a = resolve_texture_stem_to_asset(idx, c, source)
        if a:
            return a
    return None


def resolve_body_slot_from_vtf_map_refs(map_ref_stems: List[str], idx: AssetIndex, source: Optional[Asset]) -> Optional[Asset]:
    body_refs = [s for s in map_ref_stems if "BDY" in s or "BODY" in s]
    for stem in sorted(body_refs, key=len):
        a = resolve_texture_stem_to_asset(idx, stem, source)
        if a:
            return a
    return None


def slot_to_map(slot_norm: str, map_assets: List[Asset]) -> Optional[Asset]:
    # Body maps usually appear as BDY in real asset names for BODY slots.
    keys = [slot_norm]
    if slot_norm in {"BODY", "BOD", "BOD Y"}:
        keys += ["BDY"]
    if slot_norm.endswith("BODY"):
        keys += ["BDY"]
    if slot_norm.endswith("LF"):
        keys.append(slot_norm[:-2] + "LT")
    for key in keys:
        cands = [a for a in map_assets if a.stem.endswith(key) or key in a.stem]
        if cands:
            cands.sort(key=lambda a: a.name)
            return cands[0]
    return None



def parse_tmt_frame_tokens(data: bytes) -> List[str]:
    """Parse TMT frame basenames.

    Observed layout:
      +0x14 uint32 dimension_count
      +0x18 uint32 dimension_values[dimension_count]
      +0x40 char frame_names[][8]

    The frame names are packed 8-byte basenames, e.g.
      cp11mdl1cp12mdl1cp13mdl1vw14mdl2
    so regex token extraction merges them incorrectly. This parser uses the
    dimension product when valid and falls back to 8-byte scanning from +0x40.
    """
    if len(data) < 0x40:
        return []

    count = 0
    try:
        dim_count = struct.unpack_from("<I", data, 0x14)[0]
        if 0 < dim_count <= 8 and len(data) >= 0x18 + 4 * dim_count:
            prod = 1
            for i in range(dim_count):
                v = struct.unpack_from("<I", data, 0x18 + 4 * i)[0]
                if v <= 0 or v > 1024:
                    prod = 0
                    break
                prod *= v
            if 0 < prod <= 4096:
                count = prod
    except struct.error:
        count = 0

    # Clamp by available bytes.
    max_by_size = max(0, (len(data) - 0x40) // 8)
    if count <= 0 or count > max_by_size:
        count = max_by_size

    out: List[str] = []
    seen = set()
    for i in range(count):
        raw = data[0x40 + i * 8 : 0x40 + (i + 1) * 8]
        name = raw.split(b"\x00", 1)[0].decode("ascii", "ignore").strip()
        if len(name) < 3:
            continue
        if not re.match(r"^[A-Za-z0-9_+\-]+$", name):
            continue
        up = name.upper()
        if up in {"NULL", "BWD2", "REV", "EXIT"}:
            continue
        if up not in seen:
            seen.add(up)
            out.append(up)
    return out


def resolve_tmt_frames(tmt_assets: List[Asset], idx: AssetIndex) -> Tuple[List[TmtFrameResolution], List[Dict[str, object]]]:
    rows: List[TmtFrameResolution] = []
    unresolved: List[Dict[str, object]] = []
    seen_frames = set()
    for tmt in tmt_assets:
        data = idx.payloads.get(tmt.asset_id, b"")
        if not data:
            continue
        # TMT frame names are packed 8-byte basenames at +0x40. Use the
        # real layout parser first, then fall back to token scan only if needed.
        frame_tokens = parse_tmt_frame_tokens(data)
        if not frame_tokens:
            frame_tokens = token_stems(data, max_tokens=2000)
        for tok in frame_tokens:
            if tok in {"BWD2", "REV", "EXIT", "NULL", "TMT"}:
                continue
            m16 = idx.resolve(tok, "m16", source=tmt)
            vqm = idx.resolve(tok, "vqm", source=tmt)
            if not m16 and not vqm:
                continue
            key = (tmt.asset_id, tok)
            if key in seen_frames:
                continue
            seen_frames.add(key)
            rows.append(TmtFrameResolution(
                tmt.name, tmt.asset_id, tok,
                m16.name if m16 else "", m16.asset_id if m16 else "",
                vqm.name if vqm else "", vqm.asset_id if vqm else "",
                "medium", "TMT token matched known M16/VQM stem"
            ))
            if not (m16 or vqm):
                unresolved.append({"tmt": tmt.name, "tmt_asset_id": tmt.asset_id, "frame_token": tok})
    return rows, unresolved


def resolve_vqm_cbks(vqm_assets: List[Asset], idx: AssetIndex) -> Tuple[List[VqmCbkResolution], List[Dict[str, object]]]:
    rows: List[VqmCbkResolution] = []
    unresolved: List[Dict[str, object]] = []
    for vqm in vqm_assets:
        data = idx.payloads.get(vqm.asset_id, b"")
        if len(data) < 0x14:
            continue
        cbk = safe_ascii(data[0x08:0x14]).upper()
        if not cbk:
            continue
        if "." not in cbk:
            cbk += ".CBK"
        asset = idx.resolve(cbk, "cbk", source=vqm)
        if asset:
            rows.append(VqmCbkResolution(vqm.name, vqm.asset_id, cbk, asset.asset_id, "high", "VQM +0x08 CBK header field"))
        else:
            unresolved.append({"vqm": vqm.name, "vqm_asset_id": vqm.asset_id, "cbk_ref": cbk})
    return rows, unresolved


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--zfs", required=True, type=Path)
    ap.add_argument("--zix", type=Path)
    ap.add_argument("--out", required=True, type=Path)
    ap.add_argument("--overwrite", action="store_true")
    ap.add_argument("--max-pix", type=int)
    args = ap.parse_args()

    t0 = time.time()
    ensure_clean_dir(args.out, args.overwrite)

    header, records = parse_zfs_records(args.zfs)

    # We need top-level definitions plus PIX/PAK containers. This is much lighter than
    # writing the whole corpus, but still enough to index embedded assets.
    wanted_exts = {"vcf", "vdf", "vtf", "wdf", "gdf", "pix", "pak", "tmt", "map", "m16", "vqm", "cbk"}
    payloads, errors = decompress_records(args.zfs, records, wanted_exts)
    idx, warnings = build_asset_index(records, payloads, args.max_pix)

    vehicles: List[VehicleRoot] = []
    geo_parts: List[VehicleGeoPart] = []
    slot_rows: List[TextureSlotResolution] = []
    unresolved_slots: List[Dict[str, object]] = []

    all_vehicle_tmt_assets: Dict[str, Asset] = {}
    all_vehicle_vqm_assets: Dict[str, Asset] = {}

    vcf_assets = sorted([a for a in idx.assets if a.ext == "vcf" and a.source == "top_level"], key=lambda a: a.name.lower())

    for vi, vcf in enumerate(vcf_assets):
        if vi % 50 == 0:
            print(f"[vehicle] {vi}/{len(vcf_assets)} {vcf.name}", file=sys.stderr)
        vcf_data = idx.payloads[vcf.asset_id]
        vdf, vtf, wdfs, gdfs = parse_vcf_refs(vcf, vcf_data, idx)
        vehicles.append(VehicleRoot(
            vcf.name, vcf.asset_id, vcf.asset_id,
            vdf.name if vdf else "", vdf.asset_id if vdf else "",
            vtf.name if vtf else "", vtf.asset_id if vtf else "",
            ";".join(w.name for w in wdfs), ";".join(g.name for g in gdfs),
            "" if (vdf and vtf) else "missing_vdf_or_vtf_reference"
        ))
        if not vdf or not vtf:
            continue

        vdf_data = idx.payloads.get(vdf.asset_id, b"")
        vtf_data = idx.payloads.get(vtf.asset_id, b"")

        vehicle_geos = find_vdf_geo_parts(vdf, vdf_data, idx)
        tmt_assets, map_assets = parse_vtf_slots(vtf, vtf_data, idx)
        map_ref_stems = parse_vtf_map_ref_stems(vtf, vtf_data, idx)

        for t in tmt_assets:
            all_vehicle_tmt_assets[t.asset_id] = t

        # Pre-resolve TMT frames for VQM accumulation later.
        tmt_frame_rows, _ = resolve_tmt_frames(tmt_assets, idx)
        for fr in tmt_frame_rows:
            if fr.resolved_vqm_asset_id:
                a = next((x for x in idx.assets if x.asset_id == fr.resolved_vqm_asset_id), None)
                if a:
                    all_vehicle_vqm_assets[a.asset_id] = a

        for geo_ref, geo, confidence, evidence in vehicle_geos:
            geo_parts.append(VehicleGeoPart(vcf.name, vdf.name, vdf.asset_id, geo_ref, geo.asset_id, geo.name, geo.source, confidence, evidence))
            data = idx.payloads.get(geo.asset_id, b"")
            slots = extract_geo_slots(data)
            for raw_slot in slots:
                norm = normalize_geo_slot(raw_slot)
                resolved = slot_to_tmt(norm, tmt_assets)
                kind = "tmt"
                evidence2 = "GEO slot normalized and matched VTF TMT suffix"
                conf2 = "high"

                if not resolved and norm == "BODY":
                    resolved = resolve_body_slot_from_vtf_map_refs(map_ref_stems, idx, geo)
                    kind = "vtf_map_image"
                    evidence2 = "GEO BODY slot resolved through VTF MAP/body image basename to M16/VQM/MAP asset"
                    conf2 = "high"

                if not resolved:
                    # Literal slots like PP11BKX1.MAP or VW14MDU2.MAP are often
                    # direct texture-image basenames stored as M16/VQM, not .MAP files.
                    resolved = resolve_slot_as_direct_texture(raw_slot, norm, idx, geo)
                    kind = "direct_texture"
                    evidence2 = "GEO slot literal stem resolved directly to TMT/M16/VQM/MAP asset"
                    conf2 = "medium"

                if not resolved:
                    resolved = slot_to_map(norm, map_assets)
                    kind = "map"
                    evidence2 = "GEO slot normalized and matched VTF MAP/body-map slot"
                    conf2 = "medium"

                if resolved:
                    slot_rows.append(TextureSlotResolution(
                        vcf.name, vcf.name, vdf.name, vtf.name, geo.name, geo.asset_id,
                        raw_slot, norm, kind, resolved.name, resolved.asset_id, conf2, evidence2
                    ))
                    if resolved.ext == "tmt":
                        all_vehicle_tmt_assets[resolved.asset_id] = resolved
                    if resolved.ext == "vqm":
                        all_vehicle_vqm_assets[resolved.asset_id] = resolved
                else:
                    reason = "no matching VTF TMT/MAP slot or direct texture asset"
                    # Classify expected non-texture placeholders for triage.
                    if re.match(r"^[0-9]+$", norm):
                        reason = "numeric_material_or_palette_placeholder"
                    elif re.match(r"^HL[0-9]+$", norm):
                        reason = "headlight_or_light_placeholder"
                    elif re.match(r"^VCC[0-9]+TP$", norm):
                        reason = "cockpit_top_panel_slot_without_matching_vehicle_tmt"
                    elif norm == "FTFT":
                        reason = "front_face_texture_slot_without_matching_vehicle_tmt"
                    elif len(norm) <= 3:
                        reason = "short_material_slot_placeholder"
                    slot_rows.append(TextureSlotResolution(
                        vcf.name, vcf.name, vdf.name, vtf.name, geo.name, geo.asset_id,
                        raw_slot, norm, "unresolved", "", "", "none", reason
                    ))
                    unresolved_slots.append({
                        "vehicle": vcf.name, "vdf": vdf.name, "vtf": vtf.name, "geo": geo.name,
                        "geo_asset_id": geo.asset_id, "raw_slot": raw_slot, "normalized_slot": norm,
                        "reason": reason
                    })

    tmt_rows, unresolved_tmt = resolve_tmt_frames(list(all_vehicle_tmt_assets.values()), idx)
    for fr in tmt_rows:
        if fr.resolved_vqm_asset_id:
            a = next((x for x in idx.assets if x.asset_id == fr.resolved_vqm_asset_id), None)
            if a:
                all_vehicle_vqm_assets[a.asset_id] = a

    vqm_rows, unresolved_vqm = resolve_vqm_cbks(list(all_vehicle_vqm_assets.values()), idx)

    write_tsv(args.out / "vehicle_roots.tsv", [asdict(v) for v in vehicles], list(asdict(vehicles[0]).keys()) if vehicles else [])
    write_tsv(args.out / "vehicle_geo_parts.tsv", [asdict(g) for g in geo_parts], list(asdict(geo_parts[0]).keys()) if geo_parts else [])
    write_tsv(args.out / "vehicle_texture_slot_resolution.tsv", [asdict(r) for r in slot_rows], list(asdict(slot_rows[0]).keys()) if slot_rows else [])
    write_tsv(args.out / "tmt_frame_resolution.tsv", [asdict(r) for r in tmt_rows], list(asdict(tmt_rows[0]).keys()) if tmt_rows else [])
    write_tsv(args.out / "vqm_cbk_resolution.tsv", [asdict(r) for r in vqm_rows], list(asdict(vqm_rows[0]).keys()) if vqm_rows else [])
    write_tsv(args.out / "unresolved_texture_slots.tsv", unresolved_slots, ["vehicle", "vdf", "vtf", "geo", "geo_asset_id", "raw_slot", "normalized_slot", "reason"])
    write_tsv(args.out / "unresolved_tmt_frames.tsv", unresolved_tmt, ["tmt", "tmt_asset_id", "frame_token"])
    write_tsv(args.out / "unresolved_vqm_cbk.tsv", unresolved_vqm, ["vqm", "vqm_asset_id", "cbk_ref"])
    write_tsv(args.out / "warnings.tsv", warnings, ["pix", "asset", "warning"])
    write_tsv(args.out / "errors.tsv", errors, ["record_index", "name", "error"])

    resolved_slots = [r for r in slot_rows if r.resolved_kind != "unresolved"]
    tmt_slot_count = sum(1 for r in slot_rows if r.resolved_kind == "tmt")
    map_slot_count = sum(1 for r in slot_rows if r.resolved_kind == "map")
    direct_texture_slot_count = sum(1 for r in slot_rows if r.resolved_kind == "direct_texture")
    vtf_map_image_slot_count = sum(1 for r in slot_rows if r.resolved_kind == "vtf_map_image")

    summary = {
        "zfs_header": header,
        "vehicles": len(vehicles),
        "vehicles_with_vdf_vtf": sum(1 for v in vehicles if v.vdf_asset_id and v.vtf_asset_id),
        "geo_part_rows": len(geo_parts),
        "texture_slot_rows": len(slot_rows),
        "texture_slots_resolved": len(resolved_slots),
        "texture_slots_unresolved": len(unresolved_slots),
        "texture_slots_resolved_tmt": tmt_slot_count,
        "texture_slots_resolved_map": map_slot_count,
        "texture_slots_resolved_direct_texture": direct_texture_slot_count,
        "texture_slots_resolved_vtf_map_image": vtf_map_image_slot_count,
        "unique_vehicle_tmt_assets": len(all_vehicle_tmt_assets),
        "tmt_frame_rows": len(tmt_rows),
        "unique_vehicle_vqm_assets": len(all_vehicle_vqm_assets),
        "vqm_cbk_rows": len(vqm_rows),
        "unresolved_tmt_frames": len(unresolved_tmt),
        "unresolved_vqm_cbk": len(unresolved_vqm),
        "zfs_decompression_errors": len(errors),
        "pix_pak_warnings": len(warnings),
        "elapsed_seconds": round(time.time() - t0, 3),
    }
    write_json(args.out / "summary.json", summary)

    (args.out / "README.txt").write_text("""I76 vehicle texture slot resolver v5

This report resolves GEO section texture-slot names through vehicle VTF material context.

Files:
  summary.json
  vehicle_roots.tsv
  vehicle_geo_parts.tsv
  vehicle_texture_slot_resolution.tsv
  tmt_frame_resolution.tsv
  vqm_cbk_resolution.tsv
  unresolved_texture_slots.tsv
  unresolved_tmt_frames.tsv
  unresolved_vqm_cbk.tsv
  warnings.tsv
  errors.tsv

Important:
  GEO slots like "V1 MD LF.MAP" are not generally literal files.
  They are normalized, LF is mapped to LT, and the resulting suffix is matched
  against TMT/MAP slots from the vehicle's VTF.
""", encoding="utf-8")

    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
