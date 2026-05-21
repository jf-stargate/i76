#!/usr/bin/env python3
"""
Interstate '76 geometry reconstruction corpus probe, v4.

Data-side companion for cgpt_i76exe_export_geometry_reconstruction_deeptrace_v23.java.
It does not claim final semantics. It extracts reconstruction-critical record shapes:
  * ODEF/OBJ 100-byte placement/entity records, including transform basis, position, tail dwords, class byte.
  * RDEF/RSEG kind/count plus 0x18-byte point records as six-float probes.
  * LDEF/OBJ variable-size static/world entity records as string/number probes.
  * TDEF/ZMAP/ZONE terrain sidecar references and active patch layout.
  * Optional route polyline OBJ for visual inspection of RSEG point columns.

Default output root for project work remains /media/neon-remote/prj/i76/scratch_data.
"""
from __future__ import annotations

import argparse
import dataclasses
import json
import math
import os
import struct
import subprocess
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

DEFAULT_ROOT = Path('/media/neon-remote/prj/i76/scratch_data')
CONTAINERS = {'BWD2','WDEF','TDEF','RDEF','ODEF','LDEF','ADEF'}
PAGE_W = 128
PATCH_SIZE_WORLD = 640.0
SAMPLE_SCALE = PATCH_SIZE_WORLD / PAGE_W

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

def f32(data: bytes, off: int) -> float:
    return struct.unpack_from('<f', data, off)[0]

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode('ascii', errors='replace')

def clean_tag(tag: str) -> str:
    return tag.replace('\x00','')

def cstr(buf: bytes) -> str:
    return buf.split(b'\0',1)[0].decode('ascii', errors='replace').strip()

def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        size = u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        out.append(Chunk(tag, off, size, off+8, size-8, parent))
        off += size
    return out

def parse_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat(data, 0, len(data), '')
    def rec(chunks: List[Chunk]) -> List[Chunk]:
        allc = []
        for c in chunks:
            allc.append(c)
            if clean_tag(c.tag) in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, clean_tag(c.tag))
                if kids:
                    allc.extend(rec(kids))
        return allc
    return rec(roots)

def mission_files(root: Path, filt: str) -> List[Path]:
    files = [p for p in root.rglob('*') if p.is_file() and p.suffix.lower() in {'.msn','.spc','.lvl'}]
    if filt:
        lf = filt.lower()
        files = [p for p in files if lf in p.name.lower() or lf in p.stem.lower()]
    return sorted(files)

def zmap_summary(data: bytes, chunks: List[Chunk]) -> dict:
    for c in chunks:
        if clean_tag(c.tag) == 'ZMAP' and c.payload_size >= 6401:
            active = data[c.payload_offset]
            cells = data[c.payload_offset+1:c.payload_offset+1+6400]
            used = []
            hist = Counter()
            for z in range(80):
                for x in range(80):
                    v = cells[z*80+x]
                    if v != 0xff:
                        used.append((x,z,v)); hist[v]+=1
            if used:
                xs=[u[0] for u in used]; zs=[u[1] for u in used]
                bounds=[min(xs),min(zs),max(xs),max(zs)]
            else:
                bounds=None
            return {'active_count':active,'used_count':len(used),'bounds':bounds,'page_histogram':dict(sorted(hist.items())),'used_cells':used}
    return {'active_count':0,'used_count':0,'bounds':None,'page_histogram':{},'used_cells':[]}

def zone_name(data: bytes, chunks: List[Chunk]) -> str:
    for c in chunks:
        if clean_tag(c.tag) == 'ZONE':
            p = data[c.payload_offset:c.end]
            for off in (1,0,8,9):
                if off < len(p):
                    s = cstr(p[off:])
                    if s and ('.' in s or s.lower().endswith('ter')):
                        return s
            return cstr(p)
    return ''

def finite(v: float) -> bool:
    return math.isfinite(v) and abs(v) < 1e20

def fmtf(v: float) -> str:
    if not finite(v): return ''
    return f'{v:.8g}'

def unpack_floats(data: bytes, off: int, count: int) -> List[float]:
    out=[]
    for i in range(count):
        if off + i*4 + 4 <= len(data): out.append(f32(data, off+i*4))
    return out

def analyze_odef_obj(payload: bytes) -> dict:
    name = cstr(payload[:8])
    basis = unpack_floats(payload, 8, 9)
    pos = unpack_floats(payload, 0x2c, 3)
    tail = [u32(payload, off) if off+4 <= len(payload) else 0 for off in range(0x38, min(len(payload),0x64),4)]
    cls = payload[0x5c] if len(payload) > 0x5c else None
    # Simple matrix diagnostics for detecting transform columns/rows.
    row_lens=[]
    dots=[]
    if len(basis)==9:
        rows=[basis[0:3],basis[3:6],basis[6:9]]
        for r in rows:
            row_lens.append(math.sqrt(sum(x*x for x in r)) if all(finite(x) for x in r) else float('nan'))
        dots=[sum(rows[0][i]*rows[1][i] for i in range(3)), sum(rows[0][i]*rows[2][i] for i in range(3)), sum(rows[1][i]*rows[2][i] for i in range(3))]
    return {'name':name,'basis':basis,'pos':pos,'tail':tail,'class':cls,'row_lens':row_lens,'row_dots':dots}

def write_header(path: Path, header: str):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(header+'\n', encoding='utf-8')

def append_line(path: Path, fields: Iterable[object]):
    with path.open('a', encoding='utf-8') as f:
        f.write('\t'.join(str(x).replace('\t',' ').replace('\n',' ').replace('\r',' ') for x in fields)+'\n')

def export_rseg_obj(route_obj: Path, route_rows: List[Tuple[str,str,int,int,int,List[float]]]):
    route_obj.parent.mkdir(parents=True, exist_ok=True)
    with route_obj.open('w', encoding='utf-8') as f:
        f.write('# RSEG route/segment probe OBJ. Uses point floats [0], [1], [2] as XYZ probe only.\n')
        vbase = 1
        by_seg = defaultdict(list)
        for corpus, mission, rseg_idx, kind, point_idx, vals in route_rows:
            if len(vals) >= 3 and all(finite(v) for v in vals[:3]):
                by_seg[(corpus, mission, rseg_idx)].append((vals[0], vals[1], vals[2]))
        for key, pts in by_seg.items():
            if len(pts) < 2: continue
            f.write(f'o {key[0]}_{key[1]}_rseg_{key[2]}\n')
            for x,y,z in pts:
                f.write(f'v {x:.6f} {z:.6f} {y:.6f}\n')
            idxs = list(range(vbase, vbase+len(pts)))
            f.write('l ' + ' '.join(str(i) for i in idxs) + '\n')
            vbase += len(pts)

def run(args) -> dict:
    out = args.out_dir or (DEFAULT_ROOT / 'i76_geometry_reconstruction_corpus_probe_v4')
    out.mkdir(parents=True, exist_ok=True)
    dbg = out / 'debug'
    dbg.mkdir(exist_ok=True)

    paths = {
        'mission_summary': out/'mission_geometry_summary.tsv',
        'odef': out/'odef_obj_records.tsv',
        'odef_classes': out/'odef_class_histogram.tsv',
        'rseg': out/'rdef_rseg_records.tsv',
        'rseg_points': dbg/'rdef_rseg_points_sample.tsv',
        'ldef': out/'ldef_obj_records.tsv',
        'tdef': out/'tdef_zmap_zone_summary.tsv',
    }
    write_header(paths['mission_summary'], 'corpus\tmission\tpath\tchunk_count\todef_obj_count\trseg_count\trseg_point_count\tldef_obj_count\tzmap_active\tzmap_used\tzmap_bounds\tzone')
    write_header(paths['odef'], 'corpus\tmission\tobj_index\tchunk_offset\tname\tclass_dec\tclass_hex\tpos_x\tpos_y\tpos_z\tbasis_0\tbasis_1\tbasis_2\tbasis_3\tbasis_4\tbasis_5\tbasis_6\tbasis_7\tbasis_8\trow_len_0\trow_len_1\trow_len_2\trow_dot_01\trow_dot_02\trow_dot_12\ttail_dwords_hex')
    write_header(paths['odef_classes'], 'corpus\tclass_dec\tclass_hex\tcount\tnames_sample')
    write_header(paths['rseg'], 'corpus\tmission\trseg_index\tchunk_offset\tkind\tcount\tpayload_size\texpected_size\tsize_match\tfirst6_float\tlast6_float')
    write_header(paths['rseg_points'], 'corpus\tmission\trseg_index\tkind\tpoint_index\tf0\tf1\tf2\tf3\tf4\tf5\traw_hex')
    write_header(paths['ldef'], 'corpus\tmission\tobj_index\tchunk_offset\tpayload_size\tname_guess\tfirst16_hex\tfirst12_float')
    write_header(paths['tdef'], 'corpus\tmission\tactive_count\tused_count\tbounds\tzone\tused_cells_json')

    class_hist = defaultdict(Counter)
    class_names = defaultdict(lambda: defaultdict(Counter))
    route_rows=[]
    manifest = {'format':'i76_geometry_reconstruction_corpus_probe','version':4,'corpora':{},'warnings':[]}

    corpora=[]
    if args.miss8: corpora.append(('miss8', args.miss8))
    if args.miss16: corpora.append(('miss16', args.miss16))
    if args.input: corpora.append(('input', args.input))

    for cname, root in corpora:
        files = mission_files(root, args.mission_filter)
        manifest['corpora'][cname]={'root':str(root),'missions_seen':len(files)}
        for mp in files:
            try:
                data = mp.read_bytes(); chunks = parse_tree(data)
                mission = mp.stem.lower()
                zsum = zmap_summary(data, chunks); zname = zone_name(data, chunks)
                odef_count=rseg_count=rseg_point_count=ldef_count=0
                for c in chunks:
                    tag=clean_tag(c.tag); parent=clean_tag(c.parent)
                    payload=data[c.payload_offset:c.end]
                    if parent=='ODEF' and tag=='OBJ' and len(payload)>=0x64:
                        odef_count += 1
                        rec=analyze_odef_obj(payload)
                        cls=rec['class']; class_hist[cname][cls]+=1; class_names[cname][cls][rec['name']]+=1
                        append_line(paths['odef'], [cname,mission,odef_count-1,f'0x{c.offset:08x}',rec['name'],cls if cls is not None else '',f'0x{cls:02x}' if cls is not None else '',*(fmtf(v) for v in rec['pos']),*(fmtf(v) for v in rec['basis']),*(fmtf(v) for v in rec['row_lens']),*(fmtf(v) for v in rec['row_dots']),' '.join(f'0x{x:08x}' for x in rec['tail'])])
                    elif parent=='RDEF' and tag=='RSEG' and len(payload)>=8:
                        rseg_count += 1
                        kind=u32(payload,0); cnt=u32(payload,4); exp=8+cnt*0x18
                        rseg_point_count += cnt
                        first=unpack_floats(payload,8,6) if len(payload)>=8+24 else []
                        last=unpack_floats(payload,8+(cnt-1)*24,6) if cnt and len(payload)>=8+cnt*24 else []
                        append_line(paths['rseg'], [cname,mission,rseg_count-1,f'0x{c.offset:08x}',kind,cnt,len(payload),exp,len(payload)==exp,','.join(fmtf(v) for v in first),','.join(fmtf(v) for v in last)])
                        sample_limit=min(cnt,args.max_rseg_points_per_segment)
                        for pi in range(sample_limit):
                            off=8+pi*24
                            raw=payload[off:off+24]
                            vals=unpack_floats(payload,off,6)
                            append_line(paths['rseg_points'], [cname,mission,rseg_count-1,kind,pi,*(fmtf(v) for v in vals),raw.hex(' ')])
                            route_rows.append((cname,mission,rseg_count-1,kind,pi,vals))
                    elif parent=='LDEF' and tag=='OBJ':
                        ldef_count += 1
                        ng=cstr(payload[:16])
                        floats=unpack_floats(payload,0,min(12,len(payload)//4))
                        append_line(paths['ldef'], [cname,mission,ldef_count-1,f'0x{c.offset:08x}',len(payload),ng,payload[:16].hex(' '),','.join(fmtf(v) for v in floats)])
                append_line(paths['mission_summary'], [cname,mission,str(mp),len(chunks),odef_count,rseg_count,rseg_point_count,ldef_count,zsum['active_count'],zsum['used_count'],json.dumps(zsum['bounds']),zname])
                append_line(paths['tdef'], [cname,mission,zsum['active_count'],zsum['used_count'],json.dumps(zsum['bounds']),zname,json.dumps([{'x':x,'z':z,'page':p} for x,z,p in zsum['used_cells']])])
            except Exception as e:
                manifest['warnings'].append(f'{cname}:{mp}: {type(e).__name__}: {e}')
    for cname,hist in class_hist.items():
        for cls,count in sorted(hist.items(), key=lambda kv: (-kv[1], kv[0] if kv[0] is not None else -1)):
            names=','.join(name for name,_ in class_names[cname][cls].most_common(12))
            append_line(paths['odef_classes'], [cname, cls if cls is not None else '', f'0x{cls:02x}' if cls is not None else '', count, names])
    if args.write_rseg_obj:
        export_rseg_obj(out/'rdef_rseg_points_probe.obj', route_rows)
    manifest['outputs']={k:str(v) for k,v in paths.items()}
    if args.write_rseg_obj: manifest['outputs']['rseg_obj']=str(out/'rdef_rseg_points_probe.obj')
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
    if args.make_tar:
        subprocess.run(['tar','-cf',out.name+'.tar',out.name],cwd=str(out.parent),check=False)
    return manifest

def main() -> int:
    ap=argparse.ArgumentParser()
    ap.add_argument('--miss8', type=Path)
    ap.add_argument('--miss16', type=Path)
    ap.add_argument('--input', type=Path)
    ap.add_argument('--out-dir', type=Path)
    ap.add_argument('--mission-filter', default='')
    ap.add_argument('--max-rseg-points-per-segment', type=int, default=32)
    ap.add_argument('--write-rseg-obj', action='store_true')
    ap.add_argument('--make-tar', action='store_true')
    args=ap.parse_args()
    if not (args.miss8 or args.miss16 or args.input):
        ap.error('provide --miss8, --miss16, or --input')
    manifest=run(args)
    print(json.dumps({'outputs':manifest.get('outputs',{}),'warnings':len(manifest.get('warnings',[]))},indent=2))
    return 0
if __name__=='__main__':
    raise SystemExit(main())
