#!/usr/bin/env python3
"""
Interstate '76 runtime level/config corpus probe, v1.

This is a data-side companion to the Ghidra level/config trace pass. It does not
claim semantic decode for RDEF/ODEF/LDEF/ADEF; it inventories chunk sizes,
resource strings, hashes, miss8/miss16 substitutions, PCF strings, and simple
record-shape evidence so the next binary trace can target concrete unknowns.
"""
from __future__ import annotations

import argparse
import dataclasses
import hashlib
import json
import re
import shutil
import struct
import subprocess
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

DEFAULT_ROOT = Path('/media/neon-remote/prj/i76/scratch_data')
CONTAINERS = {'BWD2', 'WDEF', 'TDEF', 'RDEF', 'ODEF', 'LDEF', 'ADEF'}
TOP_SECTIONS = {'WDEF', 'TDEF', 'RDEF', 'ODEF', 'LDEF', 'ADEF'}
PRINTABLE_RE = re.compile(rb'[\x20-\x7e]{3,}')

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


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from('<I', data, off)[0]


def fourcc(data: bytes, off: int) -> str:
    return data[off:off + 4].decode('ascii', errors='replace')


def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
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
    def rec(chunks: List[Chunk]) -> List[Chunk]:
        out: List[Chunk] = []
        for c in chunks:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids:
                    out.extend(rec(kids))
        return out
    return rec(roots)


def first_chunk(chunks: List[Chunk], tag: str, parent: Optional[str] = None) -> Optional[Chunk]:
    for c in chunks:
        if c.tag == tag and (parent is None or c.parent == parent):
            return c
    return None


def sha1(data: bytes) -> str:
    return hashlib.sha1(data).hexdigest()


def esc(s: object) -> str:
    if s is None:
        return ''
    return str(s).replace('\\', '\\\\').replace('\t', '\\t').replace('\r', '\\r').replace('\n', '\\n')


def write_tsv(path: Path, header: Iterable[str], rows: Iterable[Iterable[object]]) -> None:
    with path.open('w', encoding='utf-8', newline='') as f:
        f.write('\t'.join(header) + '\n')
        for row in rows:
            f.write('\t'.join(esc(x) for x in row) + '\n')


def printable_strings(payload: bytes) -> List[Tuple[int, str]]:
    out = []
    for m in PRINTABLE_RE.finditer(payload):
        s = m.group(0).decode('ascii', errors='ignore').strip()
        if s:
            out.append((m.start(), s))
    return out


def fixed_ascii_fields(payload: bytes, width: int = 13) -> List[Tuple[int, str]]:
    out = []
    for off in range(0, len(payload), width):
        b = payload[off:off + width]
        if not b:
            continue
        s = b.split(b'\0', 1)[0].decode('ascii', errors='ignore').strip()
        if len(s) >= 2 and any(c.isalpha() for c in s):
            out.append((off, s))
    return out


def zone_sidecar_name(data: bytes, chunks: List[Chunk]) -> str:
    c = first_chunk(chunks, 'ZONE', 'TDEF') or first_chunk(chunks, 'ZONE')
    if not c:
        return ''
    payload = data[c.payload_offset:c.end]
    candidates = []
    for off in (0, 1, 4, 8, 9):
        if off < len(payload):
            candidates.append(payload[off:].split(b'\0', 1)[0].decode('ascii', errors='ignore').strip())
    for s in candidates:
        if s and '.' in s:
            return s
    for s in candidates:
        if s:
            return s
    return ''


def zmap_summary(data: bytes, chunks: List[Chunk]) -> dict:
    c = first_chunk(chunks, 'ZMAP', 'TDEF') or first_chunk(chunks, 'ZMAP')
    if not c or c.payload_size < 1 + 80 * 80:
        return {}
    payload = data[c.payload_offset:c.end]
    active = payload[0]
    cells = payload[1:1 + 80 * 80]
    used = []
    hist = Counter()
    for z in range(80):
        for x in range(80):
            v = cells[z * 80 + x]
            if v != 0xff:
                used.append((x, z, v))
                hist[v] += 1
    if used:
        xs = [u[0] for u in used]
        zs = [u[1] for u in used]
        bounds = [min(xs), min(zs), max(xs), max(zs)]
    else:
        bounds = None
    return {
        'active_count': active,
        'used_cell_count': len(used),
        'bounds': bounds,
        'unique_pages': sorted(hist.keys()),
        'page_histogram': dict(sorted(hist.items())),
    }


def mission_files(root: Path) -> List[Path]:
    return sorted([p for p in root.rglob('*') if p.is_file() and p.suffix.lower() in {'.msn', '.spc', '.lvl'}])


def pcf_files(root: Path) -> List[Path]:
    return sorted([p for p in root.rglob('*') if p.is_file() and p.suffix.lower() == '.pcf'])


def top_section_payloads(data: bytes, chunks: List[Chunk]) -> Dict[str, bytes]:
    out = {}
    for c in chunks:
        if c.parent == '' and c.tag in TOP_SECTIONS:
            out[c.tag] = data[c.payload_offset:c.end]
    return out


def short_words(payload: bytes, count: int = 16) -> str:
    vals = []
    for i in range(min(count, len(payload) // 2)):
        vals.append(f'{struct.unpack_from("<H", payload, i * 2)[0]:04x}')
    return ' '.join(vals)


def dwords(payload: bytes, count: int = 8) -> str:
    vals = []
    for i in range(min(count, len(payload) // 4)):
        vals.append(f'{struct.unpack_from("<I", payload, i * 4)[0]:08x}')
    return ' '.join(vals)


def floats(payload: bytes, count: int = 8) -> str:
    vals = []
    for i in range(min(count, len(payload) // 4)):
        try:
            v = struct.unpack_from('<f', payload, i * 4)[0]
            if abs(v) < 1.0e9:
                vals.append(f'{v:.6g}')
            else:
                vals.append('nanish')
        except Exception:
            vals.append('err')
    return ' '.join(vals)


def analyze_one(path: Path) -> dict:
    data = path.read_bytes()
    chunks = parse_tree(data)
    sections = top_section_payloads(data, chunks)
    return {
        'path': path,
        'stem': path.stem.lower(),
        'data': data,
        'chunks': chunks,
        'sections': sections,
        'zmap': zmap_summary(data, chunks),
        'zone': zone_sidecar_name(data, chunks),
    }


def make_tar(out_dir: Path) -> Optional[Path]:
    tar_path = out_dir.with_suffix('.tar')
    try:
        subprocess.run(['tar', '-cf', tar_path.name, out_dir.name], cwd=str(out_dir.parent), check=True)
        return tar_path
    except Exception:
        return None


def run(args: argparse.Namespace) -> dict:
    miss8 = args.miss8
    miss16 = args.miss16
    inputs = []
    if args.input:
        inputs.append(args.input)
    if miss8:
        inputs.append(miss8)
    if miss16:
        inputs.append(miss16)
    if not inputs:
        raise SystemExit('provide --input, --miss8, or --miss16')

    out_dir = args.out_dir
    out_dir.mkdir(parents=True, exist_ok=True)
    debug_dir = out_dir / 'debug'
    debug_dir.mkdir(exist_ok=True)

    corpus = []
    for label, root in [('input', args.input), ('miss8', miss8), ('miss16', miss16)]:
        if not root:
            continue
        for p in mission_files(root):
            if args.mission_filter and args.mission_filter.lower() not in p.name.lower() and args.mission_filter.lower() not in p.stem.lower():
                continue
            rec = analyze_one(p)
            rec['label'] = label
            corpus.append(rec)

    chunk_rows = []
    section_rows = []
    string_rows = []
    wrld_fixed_rows = []
    zmap_rows = []
    rseg_rows = []
    obj_rows = []
    ldef_rows = []
    adef_rows = []

    for rec in corpus:
        label = rec['label']
        path = rec['path']
        data = rec['data']
        chunks = rec['chunks']
        stem = rec['stem']
        for c in chunks:
            payload = data[c.payload_offset:c.end]
            chunk_rows.append([label, path.name, stem, c.parent, c.tag, f'0x{c.offset:08x}', c.size, c.payload_size, sha1(payload)])
        for tag, payload in rec['sections'].items():
            section_rows.append([label, path.name, stem, tag, len(payload), sha1(payload), short_words(payload), dwords(payload)])
        for c in chunks:
            if c.tag in {'WRLD', 'ZONE', 'OBJ\x00', 'RSEG', 'FSM\x00'} or c.parent in {'WDEF', 'TDEF', 'ODEF', 'RDEF', 'LDEF', 'ADEF'}:
                payload = data[c.payload_offset:c.end]
                for off, s in printable_strings(payload):
                    string_rows.append([label, path.name, stem, c.parent, c.tag, f'0x{c.payload_offset + off:08x}', off, s])
        wrld = first_chunk(chunks, 'WRLD', 'WDEF') or first_chunk(chunks, 'WRLD')
        if wrld:
            payload = data[wrld.payload_offset:wrld.end]
            for off, s in fixed_ascii_fields(payload, 13):
                wrld_fixed_rows.append([label, path.name, stem, f'0x{wrld.payload_offset + off:08x}', off, 13, s])
            for off, s in printable_strings(payload):
                wrld_fixed_rows.append([label, path.name, stem, f'0x{wrld.payload_offset + off:08x}', off, 'string', s])
        zs = rec['zmap']
        if zs:
            zmap_rows.append([label, path.name, stem, zs.get('active_count'), zs.get('used_cell_count'), json.dumps(zs.get('bounds')), json.dumps(zs.get('unique_pages')), json.dumps(zs.get('page_histogram')), rec['zone']])
        for c in chunks:
            payload = data[c.payload_offset:c.end]
            if c.tag == 'RSEG':
                rseg_rows.append([label, path.name, stem, f'0x{c.offset:08x}', c.size, c.payload_size, short_words(payload, 24), dwords(payload, 12), floats(payload, 12)])
            if c.tag == 'OBJ\x00':
                obj_rows.append([label, path.name, stem, f'0x{c.offset:08x}', c.size, c.payload_size, short_words(payload, 32), dwords(payload, 16), floats(payload, 16)])
            if c.parent == 'LDEF':
                ldef_rows.append([label, path.name, stem, c.tag, f'0x{c.offset:08x}', c.size, c.payload_size, short_words(payload, 32), dwords(payload, 16), floats(payload, 16)])
            if c.parent == 'ADEF':
                adef_rows.append([label, path.name, stem, c.tag, f'0x{c.offset:08x}', c.size, c.payload_size, short_words(payload, 32), dwords(payload, 16), floats(payload, 16)])

    write_tsv(out_dir / 'chunks.tsv', ['corpus','mission','stem','parent','tag','offset','size','payload_size','payload_sha1'], chunk_rows)
    write_tsv(out_dir / 'top_section_fingerprints.tsv', ['corpus','mission','stem','section','payload_size','payload_sha1','first_u16','first_u32'], section_rows)
    write_tsv(out_dir / 'resource_strings.tsv', ['corpus','mission','stem','parent','tag','abs_offset','payload_offset','string'], string_rows)
    write_tsv(out_dir / 'wdef_wrld_resource_candidates.tsv', ['corpus','mission','stem','abs_offset','payload_offset','field_width','value'], wrld_fixed_rows)
    write_tsv(out_dir / 'zmap_zone_summary.tsv', ['corpus','mission','stem','active_count','used_cell_count','bounds','unique_pages','page_histogram','zone_sidecar_name'], zmap_rows)
    write_tsv(debug_dir / 'rdef_rseg_probe.tsv', ['corpus','mission','stem','offset','chunk_size','payload_size','first_u16','first_u32','first_f32'], rseg_rows)
    write_tsv(debug_dir / 'odef_obj_probe.tsv', ['corpus','mission','stem','offset','chunk_size','payload_size','first_u16','first_u32','first_f32'], obj_rows)
    write_tsv(debug_dir / 'ldef_probe.tsv', ['corpus','mission','stem','tag','offset','chunk_size','payload_size','first_u16','first_u32','first_f32'], ldef_rows)
    write_tsv(debug_dir / 'adef_probe.tsv', ['corpus','mission','stem','tag','offset','chunk_size','payload_size','first_u16','first_u32','first_f32'], adef_rows)

    # miss8/miss16 pair comparison by stem and section.
    by_label_stem = defaultdict(dict)
    for rec in corpus:
        by_label_stem[rec['stem']][rec['label']] = rec
    cmp_rows = []
    for stem, d in sorted(by_label_stem.items()):
        if 'miss8' not in d or 'miss16' not in d:
            continue
        a = d['miss8']
        b = d['miss16']
        cmp_rows.append([stem, 'whole_file', len(a['data']), len(b['data']), sha1(a['data']), sha1(b['data']), sha1(a['data']) == sha1(b['data'])])
        for sec in sorted(TOP_SECTIONS):
            pa = a['sections'].get(sec, b'')
            pb = b['sections'].get(sec, b'')
            cmp_rows.append([stem, sec, len(pa), len(pb), sha1(pa) if pa else '', sha1(pb) if pb else '', pa == pb])
    write_tsv(out_dir / 'miss8_miss16_section_compare.tsv', ['stem','scope','miss8_size','miss16_size','miss8_sha1','miss16_sha1','same'], cmp_rows)

    # PCF strings from miss16 or input directories.
    pcf_rows = []
    for label, root in [('input', args.input), ('miss16', miss16), ('miss8', miss8)]:
        if not root:
            continue
        for p in pcf_files(root):
            if args.mission_filter and args.mission_filter.lower() not in p.name.lower() and args.mission_filter.lower() not in p.stem.lower():
                continue
            data = p.read_bytes()
            for off, s in printable_strings(data):
                pcf_rows.append([label, p.name, f'0x{off:08x}', off, s])
    write_tsv(out_dir / 'pcf_printable_strings.tsv', ['corpus','pcf','offset_hex','offset','string'], pcf_rows)

    tag_hist = Counter((row[0], row[3], row[4]) for row in chunk_rows)
    tag_rows = [[corpus_label, parent, tag, count] for (corpus_label, parent, tag), count in sorted(tag_hist.items())]
    write_tsv(out_dir / 'chunk_tag_histogram.tsv', ['corpus','parent','tag','count'], tag_rows)

    manifest = {
        'format': 'i76_level_config_corpus_probe',
        'version': 1,
        'inputs': [str(p) for p in inputs if p],
        'out_dir': str(out_dir),
        'mission_filter': args.mission_filter,
        'mission_count': len(corpus),
        'outputs': [
            'chunks.tsv',
            'top_section_fingerprints.tsv',
            'resource_strings.tsv',
            'wdef_wrld_resource_candidates.tsv',
            'zmap_zone_summary.tsv',
            'miss8_miss16_section_compare.tsv',
            'pcf_printable_strings.tsv',
            'chunk_tag_histogram.tsv',
            'debug/rdef_rseg_probe.tsv',
            'debug/odef_obj_probe.tsv',
            'debug/ldef_probe.tsv',
            'debug/adef_probe.tsv',
        ],
        'notes': [
            'RDEF/ODEF/LDEF/ADEF rows are record-shape probes, not semantic decodes.',
            'Use this output to choose exact functions/fields for the next Ghidra trace pass.',
        ],
    }
    (out_dir / 'manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')
    tar_path = make_tar(out_dir) if args.make_tar else None
    print(json.dumps({'manifest': str(out_dir / 'manifest.json'), 'mission_count': len(corpus), 'tar': str(tar_path) if tar_path else None}, indent=2))
    return manifest


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument('--input', type=Path, default=None, help='Single mission corpus directory, e.g. miss16')
    ap.add_argument('--miss8', type=Path, default=None, help='miss8 directory for pair comparison')
    ap.add_argument('--miss16', type=Path, default=None, help='miss16 directory for pair comparison and PCF scan')
    ap.add_argument('--out-dir', type=Path, required=True)
    ap.add_argument('--mission-filter', default='', help='Optional substring filter, e.g. m06')
    ap.add_argument('--make-tar', action='store_true')
    args = ap.parse_args()
    run(args)
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
