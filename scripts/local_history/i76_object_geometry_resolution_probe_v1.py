#!/usr/bin/env python3
"""
Interstate '76 object geometry resolution probe v1.

This script starts from the current level reconstruction baseline:
  - dense terrain is the placement baseline,
  - RSEG is a road/corridor overlay,
  - ODEF axes are placement transforms.

It does not decode actual GEO meshes yet.  Instead it resolves ODEF/LDEF object names
against a set of candidate asset roots so that the next implementation pass can bind
placed records to real resources.

Typical roots to pass:
  --asset-root /path/to/extracted/I76.ZFS
  --asset-root /path/to/extracted/PAK/resources
  --asset-root /media/neon-remote/prj/i76/game/interstate\ 76

Outputs:
  object_resource_candidates.tsv
  unresolved_object_resources.tsv
  odef_class_summary.tsv
  ldef_name_summary.tsv
  manifest.json
"""
from __future__ import annotations

import argparse
import dataclasses
import json
import struct
import tarfile
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
OBJ_TAG = "OBJ\x00"

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

def u32(data: bytes, off: int) -> int:
    return struct.unpack_from('<I', data, off)[0]

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode('latin1', errors='replace')

def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out: List[Chunk] = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        size = u32(data, off+4)
        if size < 8 or off + size > end:
            break
        out.append(Chunk(tag, off, size, off+8, size-8, parent))
        off += size
    return out

def parse_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat(data, 0, len(data), '')
    def rec(chs: List[Chunk]) -> List[Chunk]:
        allc: List[Chunk] = []
        for c in chs:
            allc.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    allc.extend(rec(kids))
        return allc
    return rec(roots)

def cstr_fixed(bs: bytes) -> str:
    return bs.split(b'\0', 1)[0].decode('ascii', errors='ignore').strip()

def find_files(root: Path) -> List[Path]:
    if root.is_file():
        return [root]
    return [p for p in root.rglob('*') if p.is_file()]

def build_asset_index(roots: List[Path]) -> Dict[str, List[Path]]:
    idx: Dict[str, List[Path]] = defaultdict(list)
    for root in roots:
        if not root.exists():
            continue
        for p in find_files(root):
            idx[p.name.lower()].append(p)
            idx[p.stem.lower()].append(p)
    return idx

PREFERRED_EXTS = [
    '.vcf', '.vdf', '.vtf', '.wdf', '.sdf', '.sobj', '.geo', '.tmt', '.map', '.m16', '.vqm', '.cbk', '.pcf'
]

def candidates_for_name(name: str, idx: Dict[str, List[Path]]) -> List[Tuple[str, Path]]:
    if not name:
        return []
    n = name.lower().strip()
    out: List[Tuple[str, Path]] = []
    seen = set()
    probes = [n]
    for ext in PREFERRED_EXTS:
        probes.append(n + ext)
    # 8-byte names are often basenames.  Some resources may be upper-case.
    for q in probes:
        for p in idx.get(q, []):
            key = str(p)
            if key in seen:
                continue
            seen.add(key)
            out.append((q, p))
    return out

@dataclasses.dataclass
class OdefRecord:
    mission_set: str
    mission: str
    index: int
    name: str
    class_byte: int
    pos_x: float
    pos_y: float
    pos_z: float
    payload_hex: str

def parse_odef_records(data: bytes, chunks: List[Chunk], mission_set: str, mission: str) -> List[OdefRecord]:
    out: List[OdefRecord] = []
    i = 0
    for c in chunks:
        if c.parent == 'ODEF' and c.tag == OBJ_TAG and c.payload_size >= 0x64:
            p = data[c.payload_offset:c.end]
            name = cstr_fixed(p[0:8])
            pos_x, pos_y, pos_z = struct.unpack_from('<fff', p, 0x2c)
            class_byte = p[0x5c]
            out.append(OdefRecord(mission_set, mission, i, name, class_byte, pos_x, pos_y, pos_z, p[:0x64].hex()))
            i += 1
    return out

@dataclasses.dataclass
class LdefRecord:
    mission_set: str
    mission: str
    index: int
    name: str
    payload_size: int
    payload_hex_prefix: str

def parse_ldef_records(data: bytes, chunks: List[Chunk], mission_set: str, mission: str) -> List[LdefRecord]:
    out: List[LdefRecord] = []
    i = 0
    for c in chunks:
        if c.parent == 'LDEF' and c.tag == OBJ_TAG:
            p = data[c.payload_offset:c.end]
            name = cstr_fixed(p[:16])
            out.append(LdefRecord(mission_set, mission, i, name, c.payload_size, p[:96].hex()))
            i += 1
    return out

def write_tsv(path: Path, header: List[str], rows: Iterable[List[object]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('w', encoding='utf-8', newline='') as f:
        f.write('\t'.join(header) + '\n')
        for row in rows:
            f.write('\t'.join(str(x) for x in row) + '\n')

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument('--miss8', type=Path)
    ap.add_argument('--miss16', type=Path, required=True)
    ap.add_argument('--asset-root', type=Path, action='append', default=[])
    ap.add_argument('--out-dir', type=Path, required=True)
    ap.add_argument('--mission-filter', default='')
    ap.add_argument('--make-tar', action='store_true')
    args = ap.parse_args()

    args.out_dir.mkdir(parents=True, exist_ok=True)
    roots = list(args.asset_root)
    # Always index mission dirs too; sometimes resources sit beside missions.
    roots.append(args.miss16)
    if args.miss8:
        roots.append(args.miss8)
    asset_idx = build_asset_index(roots)

    mission_dirs = []
    if args.miss8:
        mission_dirs.append(('miss8', args.miss8))
    mission_dirs.append(('miss16', args.miss16))

    odefs: List[OdefRecord] = []
    ldefs: List[LdefRecord] = []
    warnings: List[str] = []
    for set_name, root in mission_dirs:
        for p in sorted(find_files(root)):
            if p.suffix.lower() not in {'.msn', '.lvl', '.spc'}:
                continue
            if args.mission_filter and args.mission_filter.lower() not in p.name.lower() and args.mission_filter.lower() not in p.stem.lower():
                continue
            try:
                data = p.read_bytes()
                chunks = parse_tree(data)
                odefs.extend(parse_odef_records(data, chunks, set_name, p.name, ))
                ldefs.extend(parse_ldef_records(data, chunks, set_name, p.name))
            except Exception as e:
                warnings.append(f'{p}: {type(e).__name__}: {e}')

    candidate_rows = []
    unresolved_rows = []
    for r in odefs:
        cands = candidates_for_name(r.name, asset_idx)
        if cands:
            for query, path in cands[:32]:
                candidate_rows.append([r.mission_set, r.mission, r.index, r.name, f'0x{r.class_byte:02x}', query, path.suffix.lower(), path])
        else:
            if r.name:
                unresolved_rows.append([r.mission_set, r.mission, r.index, r.name, f'0x{r.class_byte:02x}', f'{r.pos_x:.6f}', f'{r.pos_y:.6f}', f'{r.pos_z:.6f}'])
    for r in ldefs:
        cands = candidates_for_name(r.name, asset_idx)
        if cands:
            for query, path in cands[:32]:
                candidate_rows.append([r.mission_set, r.mission, f'LDEF:{r.index}', r.name, 'ldef', query, path.suffix.lower(), path])
        else:
            if r.name:
                unresolved_rows.append([r.mission_set, r.mission, f'LDEF:{r.index}', r.name, 'ldef', '', '', ''])

    class_counter = Counter((r.mission_set, r.class_byte) for r in odefs)
    name_counter = Counter(r.name for r in odefs if r.name)
    ldef_counter = Counter(r.name for r in ldefs if r.name)

    write_tsv(args.out_dir / 'object_resource_candidates.tsv',
              ['mission_set','mission','record_index','name','class_or_section','query','matched_ext','path'], candidate_rows)
    write_tsv(args.out_dir / 'unresolved_object_resources.tsv',
              ['mission_set','mission','record_index','name','class_or_section','pos_x','pos_y','pos_z'], unresolved_rows)
    write_tsv(args.out_dir / 'odef_class_summary.tsv',
              ['mission_set','class_byte_hex','count'],
              [[ms, f'0x{cb:02x}', cnt] for (ms, cb), cnt in sorted(class_counter.items())])
    write_tsv(args.out_dir / 'odef_name_summary.tsv',
              ['name','count'], [[n,c] for n,c in name_counter.most_common()])
    write_tsv(args.out_dir / 'ldef_name_summary.tsv',
              ['name','count'], [[n,c] for n,c in ldef_counter.most_common()])

    manifest = {
        'format': 'i76_object_geometry_resolution_probe',
        'version': 1,
        'miss8': str(args.miss8) if args.miss8 else '',
        'miss16': str(args.miss16),
        'asset_roots': [str(p) for p in roots],
        'mission_filter': args.mission_filter,
        'odef_records': len(odefs),
        'ldef_records': len(ldefs),
        'candidate_rows': len(candidate_rows),
        'unresolved_rows': len(unresolved_rows),
        'warnings': warnings,
    }
    (args.out_dir / 'manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')

    if args.make_tar:
        tar_path = args.out_dir.with_suffix('.tar')
        with tarfile.open(tar_path, 'w') as tf:
            tf.add(args.out_dir, arcname=args.out_dir.name)
        manifest['tar_path'] = str(tar_path)
        (args.out_dir / 'manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')

    print(json.dumps({'out_dir': str(args.out_dir), 'odef_records': len(odefs), 'ldef_records': len(ldefs), 'candidate_rows': len(candidate_rows), 'unresolved_rows': len(unresolved_rows), 'warnings': len(warnings)}, indent=2))
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
