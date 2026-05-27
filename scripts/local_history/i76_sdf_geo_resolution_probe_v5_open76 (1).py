#!/usr/bin/env python3
"""
Interstate '76 SDF/GEO resolution probe v5 (Open76 sanity-check aligned).

This probe intentionally separates two concepts:

1. Open76-style exact resolution:
   - ODEF class 1 -> <label>.vcf, except spawn/regen special markers.
   - Non-special ODEF classes -> <label>.sdf.
   - LDEF string objects -> <label>.sdf.
   - SDF SGEO parts -> <part.Name>.geo.
   No aliasing is applied to this path.

2. Heuristic alias resolution:
   Useful for diagnosing retail mission labels that are 8-byte/truncated/normalized
   differently from actual resource filenames, but not treated as proven runtime logic.

The SDF SGEO parser follows the Open76 SdfObjectParser layout:
   SGEO payload:
     uint32 numParts
     repeated SdfPart records, 0x78 bytes each:
       char name[8]
       float right[3]
       float up[3]
       float forward[3]
       float position[3]
       char parentName[8]
       uint8 skip[56]
     optional wreck/destroyed part records may follow and are reported separately.
"""
from __future__ import annotations

import argparse
import dataclasses
import json
import math
import os
import re
import struct
import subprocess
import tarfile
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

PAGE_W = 128
PAGE_H = 128
PATCH_WORLD = 640.0
SDF_PART_SIZE = 0x78
DEFAULT_ROOT = Path('/media/neon-remote/prj/i76/scratch_data')

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}


def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode('ascii', errors='replace')


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from('<I', data, off)[0]


def f32(data: bytes, off: int) -> float:
    return struct.unpack_from('<f', data, off)[0]


def clean_cstr(raw: bytes) -> str:
    raw = raw.split(b'\0', 1)[0]
    return ''.join(chr(b & 0x7f) for b in raw if (b & 0x7f) != 0).strip()


@dataclasses.dataclass
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


def parse_flat(data: bytes, start: int, end: int, parent: str = '') -> List[Chunk]:
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
    roots = parse_flat(data, 0, len(data), '')
    all_chunks: List[Chunk] = []

    def rec(chunks: List[Chunk]) -> None:
        for c in chunks:
            all_chunks.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                rec(parse_flat(data, c.payload_offset, c.end, c.tag))

    rec(roots)
    return all_chunks


def first_chunk(chunks: Iterable[Chunk], tag: str, parent: Optional[str] = None) -> Optional[Chunk]:
    for c in chunks:
        if c.tag == tag and (parent is None or c.parent == parent):
            return c
    return None


def iter_chunks(chunks: Iterable[Chunk], tag: str, parent: Optional[str] = None) -> Iterable[Chunk]:
    for c in chunks:
        if c.tag == tag and (parent is None or c.parent == parent):
            yield c


def find_files(root: Path) -> List[Path]:
    if not root.exists():
        return []
    if root.is_file():
        return [root]
    return [p for p in root.rglob('*') if p.is_file()]


def build_asset_index(roots: List[Path]) -> Dict[str, List[Path]]:
    idx: Dict[str, List[Path]] = {}
    for root in roots:
        for p in find_files(root):
            idx.setdefault(p.name.lower(), []).append(p)
    return idx


def lookup(asset_index: Dict[str, List[Path]], key: str) -> Optional[Path]:
    rows = asset_index.get(key.lower())
    return rows[0] if rows else None


def alias_bases(name: str) -> List[str]:
    base = name.lower().strip()
    out: List[str] = []
    def add(x: str):
        if x and x not in out:
            out.append(x)
    add(base)
    if not base:
        return out
    add(base + '1')
    if base.endswith('_'):
        add(base + '1')
    # Examples seen in M06: igd271 -> igd27_1, ixd271 -> ixd27_1.
    m = re.match(r'^([a-z]+\d+)(\d)$', base)
    if m:
        add(m.group(1) + '_' + m.group(2))
    # Examples: igd27_ / ild27_ -> igd27_1 / ild27_1.
    m = re.match(r'^(.*\d)_$', base)
    if m:
        add(m.group(1) + '_1')
    return out


def resolve_alias(asset_index: Dict[str, List[Path]], name: str, exts: Iterable[str]) -> Tuple[str, Optional[Path]]:
    for base in alias_bases(name):
        for ext in exts:
            key = base + ext
            p = lookup(asset_index, key)
            if p is not None:
                return key, p
    return '', None


def decode_odef_records(path: Path, mission_set: str) -> Tuple[List[dict], List[dict]]:
    data = path.read_bytes()
    chunks = parse_tree(data)
    recs: List[dict] = []
    unresolved_non_obj: List[dict] = []
    for i, c in enumerate(iter_chunks(chunks, 'OBJ\0', 'ODEF')):
        p = data[c.payload_offset:c.end]
        if len(p) < 0x64:
            continue
        raw_name = p[:8]
        labelhigh = 0
        label_chars = []
        for b in raw_name:
            if b > 0x7f:
                labelhigh = (labelhigh << 1) | 1
            else:
                labelhigh = (labelhigh << 1) & 0xfe
            b &= 0x7f
            if b:
                label_chars.append(chr(b))
        label = ''.join(label_chars).strip()
        right = struct.unpack_from('<fff', p, 0x08)
        up = struct.unpack_from('<fff', p, 0x14)
        fwd = struct.unpack_from('<fff', p, 0x20)
        pos = struct.unpack_from('<fff', p, 0x2c)
        class_u32 = u32(p, 0x5c)
        flags = struct.unpack_from('<H', p, 0x60)[0]
        team = struct.unpack_from('<H', p, 0x62)[0]
        recs.append({
            'mission_set': mission_set,
            'mission': path.name,
            'record_index': i,
            'label': label,
            'label_id_highbits': labelhigh,
            'class_dec': class_u32,
            'class_hex': f'0x{class_u32:02x}',
            'flags': flags,
            'team_id': team,
            'is_player': str(flags == 16).lower(),
            'right_x': right[0], 'right_y': right[1], 'right_z': right[2],
            'up_x': up[0], 'up_y': up[1], 'up_z': up[2],
            'forward_x': fwd[0], 'forward_y': fwd[1], 'forward_z': fwd[2],
            'pos_x': pos[0], 'pos_y': pos[1], 'pos_z': pos[2],
            'raw_payload_hex_prefix': p[:32].hex(' '),
        })
    return recs, unresolved_non_obj


def decode_ldef_records(path: Path, mission_set: str) -> List[dict]:
    data = path.read_bytes()
    chunks = parse_tree(data)
    rows: List[dict] = []
    for i, c in enumerate(iter_chunks(chunks, 'OBJ\0', 'LDEF')):
        p = data[c.payload_offset:c.end]
        if len(p) < 0x64:
            continue
        label = clean_cstr(p[:8])
        class_dec = u32(p, 0x5c) if len(p) >= 0x60 else 0
        nstrings = u32(p, 0x64) if len(p) >= 0x68 else 0
        rows.append({
            'mission_set': mission_set,
            'mission': path.name,
            'record_index': i,
            'label': label,
            'class_dec': class_dec,
            'class_hex': f'0x{class_dec:02x}',
            'num_string_positions_probe': nstrings,
            'payload_size': len(p),
        })
    return rows


def parse_sdf_open76(sdf_path: Path, asset_index: Dict[str, List[Path]]) -> Tuple[List[dict], List[dict], List[dict]]:
    data = sdf_path.read_bytes()
    chunks = parse_tree(data)
    parts: List[dict] = []
    extras: List[dict] = []
    geo_matches: List[dict] = []
    sdfc = first_chunk(chunks, 'SDFC')
    object_name = ''
    if sdfc:
        payload = data[sdfc.payload_offset:sdfc.end]
        object_name = clean_cstr(payload[:16])
    sgeo = first_chunk(chunks, 'SGEO')
    if not sgeo or sgeo.payload_size < 4:
        return parts, extras, geo_matches
    payload = data[sgeo.payload_offset:sgeo.end]
    num_parts = u32(payload, 0)
    off = 4

    def read_part(kind: str, idx: int, off: int) -> Optional[dict]:
        if off + SDF_PART_SIZE > len(payload):
            return None
        name = clean_cstr(payload[off:off+8])
        right = struct.unpack_from('<fff', payload, off + 8)
        up = struct.unpack_from('<fff', payload, off + 20)
        fwd = struct.unpack_from('<fff', payload, off + 32)
        pos = struct.unpack_from('<fff', payload, off + 44)
        parent = clean_cstr(payload[off+56:off+64])
        row = {
            'sdf_name': sdf_path.name,
            'sdf_path': str(sdf_path),
            'sdf_object_name': object_name,
            'record_kind': kind,
            'part_index': idx,
            'part_name': name,
            'parent_name': parent,
            'right_x': right[0], 'right_y': right[1], 'right_z': right[2],
            'up_x': up[0], 'up_y': up[1], 'up_z': up[2],
            'forward_x': fwd[0], 'forward_y': fwd[1], 'forward_z': fwd[2],
            'pos_x': pos[0], 'pos_y': pos[1], 'pos_z': pos[2],
            'record_offset_in_sgeo_payload': off,
        }
        return row

    for i in range(num_parts):
        row = read_part('declared_part', i, off)
        if row is None:
            break
        parts.append(row)
        off += SDF_PART_SIZE
    extra_i = 0
    while off + SDF_PART_SIZE <= len(payload):
        row = read_part('extra_or_wreck_part', extra_i, off)
        if row is None:
            break
        # Keep all records, but mark NULL/empty explicitly.
        extras.append(row)
        off += SDF_PART_SIZE
        extra_i += 1
    for row in parts + extras:
        name = row['part_name']
        if not name or name.lower() == 'null':
            continue
        key = name.lower() + '.geo'
        p = lookup(asset_index, key)
        geo_matches.append({
            **{k: row[k] for k in ['sdf_name','sdf_path','record_kind','part_index','part_name','parent_name']},
            'geo_key': key,
            'geo_found': str(p is not None).lower(),
            'geo_path': str(p) if p else '',
        })
    return parts, extras, geo_matches


def write_tsv(path: Path, rows: List[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        path.write_text('', encoding='utf-8')
        return
    keys: List[str] = []
    seen = set()
    for r in rows:
        for k in r.keys():
            if k not in seen:
                seen.add(k); keys.append(k)
    with path.open('w', encoding='utf-8', newline='') as f:
        import csv
        w = csv.DictWriter(f, fieldnames=keys, delimiter='\t', extrasaction='ignore')
        w.writeheader()
        w.writerows(rows)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument('--miss8', type=Path)
    ap.add_argument('--miss16', type=Path)
    ap.add_argument('--mission-filter', default='')
    ap.add_argument('--asset-root', type=Path, action='append', default=[])
    ap.add_argument('--out-dir', type=Path, required=True)
    ap.add_argument('--make-tar', action='store_true')
    args = ap.parse_args()

    out = args.out_dir
    out.mkdir(parents=True, exist_ok=True)
    asset_index = build_asset_index(args.asset_root)

    mission_paths: List[Tuple[str, Path]] = []
    for label, root in [('miss8', args.miss8), ('miss16', args.miss16)]:
        if root and root.exists():
            for p in sorted(root.rglob('*')):
                if p.is_file() and p.suffix.lower() in {'.msn', '.spc', '.lvl'}:
                    if args.mission_filter and args.mission_filter.lower() not in p.stem.lower() and args.mission_filter.lower() not in p.name.lower():
                        continue
                    mission_paths.append((label, p))

    odef_rows: List[dict] = []
    ldef_rows: List[dict] = []
    open76_exact: List[dict] = []
    open76_unresolved: List[dict] = []
    alias_rows: List[dict] = []
    sdf_paths_to_parse: Dict[str, Path] = {}

    for mission_set, path in mission_paths:
        orecs, _ = decode_odef_records(path, mission_set)
        odef_rows.extend(orecs)
        for r in orecs:
            label = r['label']
            cls = int(r['class_dec'])
            if not label or cls == 0:
                open76_unresolved.append({**r, 'open76_role': 'invalid_or_blank', 'expected_key': '', 'reason': 'blank label or class 0'})
                continue
            if cls == 1:
                if label.lower() in {'spawn','regen'}:
                    open76_exact.append({**r, 'open76_role': label.lower(), 'expected_key': '', 'matched_path': '', 'matched_ext': 'special_marker'})
                    continue
                key = label.lower() + '.vcf'
                p = lookup(asset_index, key)
                if p:
                    open76_exact.append({**r, 'open76_role': 'car_vcf', 'expected_key': key, 'matched_path': str(p), 'matched_ext': '.vcf'})
                else:
                    open76_unresolved.append({**r, 'open76_role': 'car_vcf', 'expected_key': key, 'reason': 'open76 exact key missing'})
                    akey, apath = resolve_alias(asset_index, label, ['.vcf','.vdf','.sdf'])
                    if apath:
                        alias_rows.append({**r, 'open76_expected_key': key, 'alias_key': akey, 'alias_path': str(apath)})
            elif cls == 9:
                open76_exact.append({**r, 'open76_role': 'special_ignored_by_open76', 'expected_key': '', 'matched_path': '', 'matched_ext': 'special'})
            else:
                key = label.lower() + '.sdf'
                p = lookup(asset_index, key)
                if p:
                    open76_exact.append({**r, 'open76_role': 'sdf_static_or_struct', 'expected_key': key, 'matched_path': str(p), 'matched_ext': '.sdf'})
                    sdf_paths_to_parse[str(p)] = p
                else:
                    open76_unresolved.append({**r, 'open76_role': 'sdf_static_or_struct', 'expected_key': key, 'reason': 'open76 exact key missing'})
                    akey, apath = resolve_alias(asset_index, label, ['.sdf','.vcf','.vdf'])
                    if apath:
                        alias_rows.append({**r, 'open76_expected_key': key, 'alias_key': akey, 'alias_path': str(apath)})
                        if apath.name.lower().endswith('.sdf'):
                            sdf_paths_to_parse[str(apath)] = apath
        lrecs = decode_ldef_records(path, mission_set)
        ldef_rows.extend(lrecs)
        for r in lrecs:
            label = r['label']
            key = label.lower() + '.sdf'
            p = lookup(asset_index, key)
            if p:
                open76_exact.append({**r, 'open76_role': 'ldef_string_sdf', 'expected_key': key, 'matched_path': str(p), 'matched_ext': '.sdf'})
                sdf_paths_to_parse[str(p)] = p
            else:
                open76_unresolved.append({**r, 'open76_role': 'ldef_string_sdf', 'expected_key': key, 'reason': 'open76 exact key missing'})

    sdf_parts: List[dict] = []
    sdf_extras: List[dict] = []
    geo_matches: List[dict] = []
    for p in sorted(sdf_paths_to_parse.values(), key=lambda x: x.name.lower()):
        parts, extras, geos = parse_sdf_open76(p, asset_index)
        sdf_parts.extend(parts)
        sdf_extras.extend(extras)
        geo_matches.extend(geos)

    write_tsv(out / 'odef_records.tsv', odef_rows)
    write_tsv(out / 'ldef_records.tsv', ldef_rows)
    write_tsv(out / 'open76_exact_resource_matches.tsv', open76_exact)
    write_tsv(out / 'open76_exact_unresolved.tsv', open76_unresolved)
    write_tsv(out / 'heuristic_alias_matches.tsv', alias_rows)
    write_tsv(out / 'sdf_open76_sgeo_parts.tsv', sdf_parts)
    write_tsv(out / 'sdf_open76_sgeo_extra_or_wreck_records.tsv', sdf_extras)
    write_tsv(out / 'sdf_open76_geo_matches.tsv', geo_matches)

    manifest = {
        'format': 'i76_sdf_geo_resolution_probe_open76_sanity',
        'version': 5,
        'asset_roots': [str(p) for p in args.asset_root],
        'asset_index_file_count': sum(len(v) for v in asset_index.values()),
        'mission_count': len(mission_paths),
        'odef_records': len(odef_rows),
        'ldef_records': len(ldef_rows),
        'open76_exact_rows': len(open76_exact),
        'open76_unresolved_rows': len(open76_unresolved),
        'heuristic_alias_rows': len(alias_rows),
        'unique_sdf_files_parsed': len(sdf_paths_to_parse),
        'sdf_declared_part_rows': len(sdf_parts),
        'sdf_extra_or_wreck_rows': len(sdf_extras),
        'sdf_geo_match_rows': len(geo_matches),
        'sdf_geo_found_rows': sum(1 for r in geo_matches if r.get('geo_found') == 'true'),
        'notes': [
            'Open76 exact path uses label + extension only; heuristic aliases are reported separately.',
            'SDF SGEO parser follows Open76 SdfObjectParser: uint32 count, 0x78-byte SdfPart records.',
            'SdfPart.Name + .geo is the Open76 part geometry lookup key.'
        ],
    }
    (out / 'manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')
    print(json.dumps(manifest, indent=2))

    if args.make_tar:
        tar_path = out.with_suffix('.tar')
        with tarfile.open(tar_path, 'w') as tf:
            tf.add(out, arcname=out.name)
        print(f'wrote {tar_path}')
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
