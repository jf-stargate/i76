#!/usr/bin/env python3
"""Interstate '76 resource-acquisition/index probe, v8.

Binary-truth policy used by this probe:
  * ODEF dispatch-valid records predict <label>.vcf.
  * ODEF spawn/regen are special markers.
  * ODEF blank/class-0 records are diagnostic special/invalid rows.
  * LDEF string/object records predict <label>.sdf.
  * Open76 ODEF <label>.sdf is comparison-only.

This probe is intentionally corpus-friendly. Leave --mission-filter unset for the full
miss8/miss16 corpus, or set it for a focused mission such as m06.
"""
from __future__ import annotations

import argparse
import dataclasses
import hashlib
import json
import os
import struct
import tarfile
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
MISSION_EXTS = {".msn", ".spc", ".lvl"}
SCAN_EXTS = {".pak", ".pix", ".zfs", ".zix", ".mw2", ".idx", ".dat", ".bin", ".res"}

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
    return data[off:off+4].decode('ascii', errors='replace')

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
    all_chunks: List[Chunk] = []
    def rec(chs: List[Chunk]):
        for c in chs:
            all_chunks.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    rec(kids)
    rec(roots)
    return all_chunks

def strip_label(raw: bytes) -> Tuple[str, int]:
    chars = []
    high_bits = 0
    for i, b in enumerate(raw[:8]):
        if b & 0x80:
            high_bits |= (1 << i)
        c = b & 0x7f
        if c == 0:
            break
        if 32 <= c <= 126:
            chars.append(chr(c))
    return ''.join(chars).strip(), high_bits

def parse_odef_records(msn: Path, corpus: str) -> List[dict]:
    data = msn.read_bytes()
    chunks = parse_tree(data)
    rows: List[dict] = []
    for c in chunks:
        if c.parent != 'ODEF' or c.tag != 'OBJ\x00' or c.payload_size < 0x64:
            continue
        p = c.payload_offset
        label, high = strip_label(data[p:p+8])
        floats = struct.unpack_from('<12f', data, p+8) if p+8+48 <= c.end else (0.0,)*12
        cls = data[p+0x5c] if p+0x5c < c.end else 0
        rows.append({
            'corpus': corpus,
            'mission': msn.name,
            'mission_stem': msn.stem.lower(),
            'chunk_offset_hex': f'0x{c.offset:08x}',
            'label': label,
            'label_highbits': high,
            'class_hex': f'0x{cls:02x}',
            'class_dec': cls,
            'pos_x': floats[9] if len(floats) > 9 else '',
            'pos_y': floats[10] if len(floats) > 10 else '',
            'pos_z': floats[11] if len(floats) > 11 else '',
        })
    return rows

def parse_ldef_records(msn: Path, corpus: str) -> List[dict]:
    data = msn.read_bytes()
    chunks = parse_tree(data)
    rows: List[dict] = []
    for c in chunks:
        if c.parent != 'LDEF' or c.tag != 'OBJ\x00' or c.payload_size < 8:
            continue
        label, high = strip_label(data[c.payload_offset:c.payload_offset+8])
        rows.append({
            'corpus': corpus,
            'mission': msn.name,
            'mission_stem': msn.stem.lower(),
            'chunk_offset_hex': f'0x{c.offset:08x}',
            'label': label,
            'label_highbits': high,
            'payload_size': c.payload_size,
        })
    return rows

def iter_missions(root: Path, mission_filter: str) -> Iterable[Path]:
    if root.is_file() and root.suffix.lower() in MISSION_EXTS:
        candidates = [root]
    else:
        candidates = [p for p in root.rglob('*') if p.is_file() and p.suffix.lower() in MISSION_EXTS]
    mf = mission_filter.lower().strip()
    for p in sorted(candidates):
        if mf and mf not in p.stem.lower() and mf not in p.name.lower():
            continue
        yield p

def index_assets(roots: List[Path]) -> dict:
    files: List[Path] = []
    missing: List[str] = []
    for r in roots:
        if not r.exists():
            missing.append(str(r)); continue
        if r.is_file():
            files.append(r)
        else:
            files.extend([p for p in r.rglob('*') if p.is_file()])
    by_name: Dict[str, List[Path]] = {}
    by_stem: Dict[str, List[Path]] = {}
    by_ext: Dict[str, int] = {}
    for p in files:
        by_name.setdefault(p.name.lower(), []).append(p)
        by_stem.setdefault(p.stem.lower(), []).append(p)
        by_ext[p.suffix.lower()] = by_ext.get(p.suffix.lower(), 0) + 1
    return {'files': files, 'missing': missing, 'by_name': by_name, 'by_stem': by_stem, 'by_ext': by_ext}

def write_tsv(path: Path, rows: List[dict], fields: List[str]) -> None:
    with path.open('w', encoding='utf-8', newline='') as f:
        f.write('\t'.join(fields) + '\n')
        for r in rows:
            f.write('\t'.join(str(r.get(k, '')).replace('\t','\\t').replace('\n','\\n').replace('\r','\\r') for k in fields) + '\n')

def classify_odef(row: dict) -> Tuple[str, Optional[str]]:
    label = row['label']
    cls = int(row['class_dec'])
    if not label or cls == 0:
        return 'odef_invalid_or_special_blank_class0', None
    if label.lower() == 'spawn':
        return 'odef_spawn_marker', None
    if label.lower() == 'regen':
        return 'odef_regen_marker', None
    return 'binary_odef_vcf', f'{label}.vcf'

def match_name(index: dict, name: str) -> List[Path]:
    return index['by_name'].get(name.lower(), [])

def checksum_short(p: Path) -> str:
    h = hashlib.sha1()
    try:
        with p.open('rb') as f:
            h.update(f.read(65536))
        return h.hexdigest()[:16]
    except Exception:
        return ''

def scan_containers(index: dict, names: List[str], max_mb: int) -> List[dict]:
    pats = []
    for n in sorted(set(x for x in names if x)):
        pats.append((n, n.lower().encode('ascii', errors='ignore')))
        stem = Path(n).stem
        pats.append((stem, stem.lower().encode('ascii', errors='ignore')))
    pats = [(lab, pat) for lab, pat in pats if pat]
    out: List[dict] = []
    max_bytes = max_mb * 1024 * 1024
    for p in index['files']:
        if p.suffix.lower() not in SCAN_EXTS and p.stat().st_size > max_bytes:
            continue
        if p.stat().st_size > max_bytes:
            continue
        try:
            data = p.read_bytes().lower()
        except Exception:
            continue
        for label, pat in pats:
            pos = data.find(pat)
            if pos >= 0:
                out.append({'candidate': label, 'container': str(p), 'offset': pos, 'offset_hex': f'0x{pos:x}', 'container_size': len(data)})
    return out

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument('--miss8', type=Path, required=True)
    ap.add_argument('--miss16', type=Path, required=True)
    ap.add_argument('--asset-root', type=Path, action='append', required=True)
    ap.add_argument('--out-dir', type=Path, required=True)
    ap.add_argument('--mission-filter', default='')
    ap.add_argument('--scan-containers', action='store_true')
    ap.add_argument('--max-container-mb', type=int, default=64)
    ap.add_argument('--make-tar', action='store_true')
    args = ap.parse_args()

    args.out_dir.mkdir(parents=True, exist_ok=True)
    idx = index_assets(args.asset_root)

    odef_rows: List[dict] = []
    ldef_rows: List[dict] = []
    for corpus, root in [('miss8', args.miss8), ('miss16', args.miss16)]:
        for msn in iter_missions(root, args.mission_filter):
            odef_rows.extend(parse_odef_records(msn, corpus))
            ldef_rows.extend(parse_ldef_records(msn, corpus))

    binary_candidates: List[dict] = []
    binary_matches: List[dict] = []
    binary_unresolved: List[dict] = []
    basename_alts: List[dict] = []

    for r in odef_rows:
        policy, cand = classify_odef(r)
        base = dict(r); base['policy'] = policy; base['candidate_name'] = cand or ''
        binary_candidates.append(base)
        if not cand:
            binary_unresolved.append(base)
            continue
        ms = match_name(idx, cand)
        if ms:
            for p in ms:
                m = dict(base); m['matched_path'] = str(p); m['matched_ext'] = p.suffix.lower(); m['size'] = p.stat().st_size; m['sha1_64k'] = checksum_short(p)
                binary_matches.append(m)
        else:
            binary_unresolved.append(base)
            for p in idx['by_stem'].get(Path(cand).stem.lower(), []):
                a = dict(base); a['alternative_path'] = str(p); a['alternative_ext'] = p.suffix.lower(); a['alternative_size'] = p.stat().st_size
                basename_alts.append(a)

    for r in ldef_rows:
        label = r['label']
        cand = f'{label}.sdf' if label else ''
        base = dict(r); base['policy'] = 'binary_ldef_sdf'; base['candidate_name'] = cand
        binary_candidates.append(base)
        if not cand:
            binary_unresolved.append(base); continue
        ms = match_name(idx, cand)
        if ms:
            for p in ms:
                m = dict(base); m['matched_path'] = str(p); m['matched_ext'] = p.suffix.lower(); m['size'] = p.stat().st_size; m['sha1_64k'] = checksum_short(p)
                binary_matches.append(m)
        else:
            binary_unresolved.append(base)
            for p in idx['by_stem'].get(Path(cand).stem.lower(), []):
                a = dict(base); a['alternative_path'] = str(p); a['alternative_ext'] = p.suffix.lower(); a['alternative_size'] = p.stat().st_size
                basename_alts.append(a)

    # Open76 comparison only for ODEF .sdf.
    open76_rows: List[dict] = []
    for r in odef_rows:
        label = r['label']
        cls = int(r['class_dec'])
        if not label or cls == 0 or label.lower() in {'spawn','regen'}:
            continue
        cand = f'{label}.sdf'
        ms = match_name(idx, cand)
        row = dict(r); row['comparison_policy'] = 'open76_odef_sdf_comparison_only'; row['candidate_name'] = cand; row['found_count'] = len(ms); row['matched_paths'] = ';'.join(str(p) for p in ms)
        open76_rows.append(row)

    container_hits: List[dict] = []
    if args.scan_containers:
        names = [r['candidate_name'] for r in binary_candidates if r.get('candidate_name')]
        container_hits = scan_containers(idx, names, args.max_container_mb)

    common_fields = ['corpus','mission','chunk_offset_hex','label','label_highbits','class_hex','policy','candidate_name']
    write_tsv(args.out_dir/'binary_candidate_names.tsv', binary_candidates, common_fields + ['pos_x','pos_y','pos_z'])
    write_tsv(args.out_dir/'binary_resource_matches.tsv', binary_matches, common_fields + ['matched_path','matched_ext','size','sha1_64k'])
    write_tsv(args.out_dir/'binary_resource_unresolved.tsv', binary_unresolved, common_fields + ['pos_x','pos_y','pos_z'])
    write_tsv(args.out_dir/'basename_alternative_matches.tsv', basename_alts, common_fields + ['alternative_path','alternative_ext','alternative_size'])
    write_tsv(args.out_dir/'open76_comparison_odef_sdf.tsv', open76_rows, ['corpus','mission','chunk_offset_hex','label','class_hex','comparison_policy','candidate_name','found_count','matched_paths'])
    write_tsv(args.out_dir/'container_name_hits.tsv', container_hits, ['candidate','container','offset','offset_hex','container_size'])
    ext_rows = [{'extension': k, 'count': v} for k, v in sorted(idx['by_ext'].items())]
    write_tsv(args.out_dir/'asset_extension_inventory.tsv', ext_rows, ['extension','count'])

    summary = {
        'format': 'i76_resource_acquisition_index_probe',
        'version': 8,
        'mission_filter': args.mission_filter,
        'asset_roots': [str(p) for p in args.asset_root],
        'missing_asset_roots': idx['missing'],
        'indexed_files': len(idx['files']),
        'odef_records': len(odef_rows),
        'ldef_records': len(ldef_rows),
        'binary_candidates': len(binary_candidates),
        'binary_matches': len(binary_matches),
        'binary_unresolved': len(binary_unresolved),
        'basename_alternatives': len(basename_alts),
        'open76_comparison_rows': len(open76_rows),
        'container_hits': len(container_hits),
        'policy': 'ODEF label.vcf; LDEF label.sdf; spawn/regen special; Open76 ODEF label.sdf comparison-only',
    }
    (args.out_dir/'manifest.json').write_text(json.dumps(summary, indent=2), encoding='utf-8')
    if args.make_tar:
        tar_path = args.out_dir.with_suffix('.tar')
        with tarfile.open(tar_path, 'w') as tf:
            tf.add(args.out_dir, arcname=args.out_dir.name)
        summary['tar_path'] = str(tar_path)
        (args.out_dir/'manifest.json').write_text(json.dumps(summary, indent=2), encoding='utf-8')
    print(json.dumps(summary, indent=2))
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
