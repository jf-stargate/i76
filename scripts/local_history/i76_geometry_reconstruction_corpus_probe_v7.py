#!/usr/bin/env python3
"""
Interstate '76 geometry reconstruction corpus probe, v7.

Focused follow-up to v6:
  * Preserve raw ODEF/OBJ payloads for class-0 / dispatch-invalid records.
  * Emit class-dispatch corpus counts by mission and corpus.
  * Emit RSEG lane interpretation stats by kind and mission.
  * Emit OBJ probes for centerline, paired-edge rails, and crossbars.

This is a data-side probe only; it does not claim final runtime semantics.
"""
from __future__ import annotations

import argparse, csv, dataclasses, json, math, struct, tarfile
from pathlib import Path
from typing import Dict, List, Optional, Tuple

PAGE_W = 128
PAGE_H = 128

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}

@dataclasses.dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ""
    @property
    def end(self) -> int: return self.offset + self.size

def u32(data: bytes, off: int) -> int:
    return struct.unpack_from('<I', data, off)[0]

def f32(data: bytes, off: int) -> float:
    return struct.unpack_from('<f', data, off)[0]

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode('ascii', errors='replace')

def clean_name(raw: bytes) -> str:
    # Keep only printable prefix; preserve raw hex separately for corrupted names.
    s = raw.split(b'\0', 1)[0]
    out = ''.join(chr(c) if 32 <= c < 127 else '�' for c in s)
    return out.strip()

def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out=[]; off=start
    while off+8 <= end:
        tag=fourcc(data, off); size=u32(data, off+4)
        if size < 8 or off+size > end: break
        out.append(Chunk(tag, off, size, off+8, size-8, parent))
        off += size
    return out

def parse_tree(data: bytes) -> List[Chunk]:
    roots=parse_flat(data, 0, len(data), '')
    all=[]
    def rec(chunks):
        for c in chunks:
            all.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                rec(parse_flat(data, c.payload_offset, c.end, c.tag))
    rec(roots)
    return all

def chunks_of(chunks: List[Chunk], tag: str, parent: Optional[str]=None) -> List[Chunk]:
    return [c for c in chunks if c.tag == tag and (parent is None or c.parent == parent)]

def find_files(root: Path) -> List[Path]:
    return [root] if root.is_file() else [p for p in root.rglob('*') if p.is_file()]

def decode_zmap(data: bytes, chunks: List[Chunk]) -> Tuple[int, int, Optional[List[int]]]:
    zs=chunks_of(chunks,'ZMAP','TDEF')
    if not zs: return 0,0,None
    c=zs[0]
    if c.payload_size < 1+80*80: return 0,0,None
    active=data[c.payload_offset]
    cells=list(data[c.payload_offset+1:c.payload_offset+1+80*80])
    used=sum(1 for x in cells if x != 0xff)
    return active, used, cells

ODEF_CASE = {}
for cls in range(1,0x54):
    if cls == 1: case='special_spawn_regen_child_path'
    elif cls in (2,3,4,7,10,11,12,0x50,0x52,0x53): case='vehicle_or_resource_path'
    elif cls in (8,9): case='special_child_transform_path'
    elif cls in (5,6): case='case7_fallback_valid_class'
    elif cls == 0x51 or (0x0d <= cls <= 0x4f): case='case7_defaultish_valid_class'
    else: case='unknown_valid_class'
    ODEF_CASE[cls]=case

def iter_missions(root: Path, filt: str) -> List[Path]:
    files=find_files(root)
    out=[p for p in files if p.suffix.lower() in {'.msn','.spc','.lvl'}]
    if filt:
        ff=filt.lower(); out=[p for p in out if ff in p.name.lower() or ff in p.stem.lower()]
    return sorted(out)

def write_obj_lines(path: Path, vertices: List[Tuple[float,float,float]], lines: List[Tuple[int,int]], name: str):
    with path.open('w', encoding='utf-8') as f:
        f.write(f"# {name}\n")
        f.write(f"o {name}\n")
        for x,y,z in vertices:
            f.write(f"v {x:.6f} {y:.6f} {z:.6f}\n")
        for a,b in lines:
            f.write(f"l {a} {b}\n")

def main() -> int:
    ap=argparse.ArgumentParser()
    ap.add_argument('--miss8', type=Path, required=True)
    ap.add_argument('--miss16', type=Path, required=True)
    ap.add_argument('--out-dir', type=Path, required=True)
    ap.add_argument('--mission-filter', default='')
    ap.add_argument('--write-rseg-obj', action='store_true')
    ap.add_argument('--make-tar', action='store_true')
    args=ap.parse_args()
    out=args.out_dir; out.mkdir(parents=True, exist_ok=True)

    mission_rows=[]; odef_rows=[]; class0_rows=[]; class_hist: Dict[Tuple[str,int],int]={}
    rseg_rows=[]; rseg_point_rows=[]; rseg_kind_stats: Dict[Tuple[str,int], List[float]]={}
    center_vertices=[]; left_vertices=[]; right_vertices=[]; pair_vertices=[]; center_lines=[]; left_lines=[]; right_lines=[]; pair_lines=[]

    for corpus, root in [('miss8', args.miss8), ('miss16', args.miss16)]:
        for msn in iter_missions(root, args.mission_filter):
            data=msn.read_bytes(); chunks=parse_tree(data); mission=msn.stem.lower()
            active, used, cells=decode_zmap(data,chunks)
            odefs=chunks_of(chunks,'OBJ\0','ODEF')
            rsegs=chunks_of(chunks,'RSEG','RDEF')
            mission_rows.append([corpus, mission, str(msn), len(chunks), len(odefs), len(rsegs), active, used])
            for oi,c in enumerate(odefs):
                payload=data[c.payload_offset:c.end]
                if len(payload) < 0x64: continue
                raw_name=payload[:8]
                name=clean_name(raw_name)
                vals=[f32(payload,0x08+i*4) for i in range(9)]
                pos=(f32(payload,0x2c), f32(payload,0x30), f32(payload,0x34))
                tail=[u32(payload,0x38+i*4) for i in range(11)]
                cls=tail[9] & 0xffffffff
                dispatch=ODEF_CASE.get(cls, 'invalid_or_out_of_range')
                class_hist[(corpus, cls)] = class_hist.get((corpus,cls),0)+1
                odef_rows.append([corpus,mission,oi,c.offset,raw_name.hex(),name,cls,f"0x{cls:02x}",dispatch,pos[0],pos[1],pos[2],json.dumps([vals[0:3],vals[3:6],vals[6:9]]), ' '.join(f"0x{x:08x}" for x in tail)])
                if cls == 0 or cls >= 0x54:
                    class0_rows.append([corpus,mission,oi,c.offset,raw_name.hex(),name,cls,pos[0],pos[1],pos[2],payload.hex()])
            for ri,c in enumerate(rsegs):
                p=data[c.payload_offset:c.end]
                if len(p) < 8: continue
                kind=u32(p,0); count=u32(p,4); expected=8+count*0x18
                rseg_rows.append([corpus,mission,ri,c.offset,kind,count,c.payload_size,expected,c.payload_size==expected])
                prev_center_idx=None; prev_left_idx=None; prev_right_idx=None
                for pi in range(count):
                    off=8+pi*0x18
                    if off+0x18>len(p): break
                    fs=[f32(p,off+i*4) for i in range(6)]
                    lx,lz,f2,rx,h,rz=fs
                    cx=(lx+rx)/2.0; cz=(lz+rz)/2.0
                    width=math.hypot(rx-lx, rz-lz)
                    rseg_point_rows.append([corpus,mission,ri,kind,pi,lx,lz,f2,rx,h,rz,cx,cz,width])
                    rseg_kind_stats.setdefault((corpus,kind),[]).append(width)
                    if args.write_rseg_obj:
                        center_vertices.append((cx,h,cz)); ci=len(center_vertices)
                        left_vertices.append((lx,h,lz)); li=len(left_vertices)
                        right_vertices.append((rx,h,rz)); rti=len(right_vertices)
                        pair_vertices.extend([(lx,h,lz),(rx,h,rz)]); pai=len(pair_vertices)-1; pbi=len(pair_vertices)
                        pair_lines.append((pai,pbi))
                        if prev_center_idx and mission==mission: center_lines.append((prev_center_idx,ci))
                        if prev_left_idx: left_lines.append((prev_left_idx,li))
                        if prev_right_idx: right_lines.append((prev_right_idx,rti))
                        prev_center_idx=ci; prev_left_idx=li; prev_right_idx=rti

    def wtsv(name, header, rows):
        with (out/name).open('w', newline='', encoding='utf-8') as f:
            wr=csv.writer(f, delimiter='\t'); wr.writerow(header); wr.writerows(rows)

    wtsv('mission_geometry_summary_v7.tsv', ['corpus','mission','path','chunk_count','odef_obj_count','rseg_count','zmap_active','zmap_used'], mission_rows)
    wtsv('odef_obj_semantic_records_v7.tsv', ['corpus','mission','obj_index','chunk_offset_dec','name_raw_hex','name_guess','class_dec','class_hex','dispatch_case','pos_x','pos_y','pos_z','basis_rows_json','tail_dwords_hex'], odef_rows)
    wtsv('odef_dispatch_invalid_records_raw_v7.tsv', ['corpus','mission','obj_index','chunk_offset_dec','name_raw_hex','name_guess','class_dec','pos_x','pos_y','pos_z','payload_hex'], class0_rows)
    hist_rows=[[c,cls,f"0x{cls:02x}",n,ODEF_CASE.get(cls,'invalid_or_out_of_range')] for (c,cls),n in sorted(class_hist.items())]
    wtsv('odef_class_histogram_v7.tsv', ['corpus','class_dec','class_hex','count','dispatch_case'], hist_rows)
    wtsv('rdef_rseg_records_v7.tsv', ['corpus','mission','rseg_index','chunk_offset_dec','kind','count','payload_size','expected_size','size_match'], rseg_rows)
    wtsv('rdef_rseg_points_interpreted_v7.tsv', ['corpus','mission','rseg_index','kind','point_index','left_x','left_z','f2_raw','right_x','height_or_y','right_z','center_x','center_z','width'], rseg_point_rows)
    stat_rows=[]
    for (corpus,kind), widths in sorted(rseg_kind_stats.items()):
        stat_rows.append([corpus,kind,len(widths),min(widths),sum(widths)/len(widths),max(widths)])
    wtsv('rdef_rseg_width_by_kind_v7.tsv', ['corpus','kind','point_count','width_min','width_avg','width_max'], stat_rows)

    if args.write_rseg_obj:
        write_obj_lines(out/'rseg_centerline_v7.obj', center_vertices, center_lines, 'rseg_centerline_v7')
        write_obj_lines(out/'rseg_left_edge_v7.obj', left_vertices, left_lines, 'rseg_left_edge_v7')
        write_obj_lines(out/'rseg_right_edge_v7.obj', right_vertices, right_lines, 'rseg_right_edge_v7')
        write_obj_lines(out/'rseg_crossbars_v7.obj', pair_vertices, pair_lines, 'rseg_crossbars_v7')

    manifest={
        'format':'i76_geometry_reconstruction_corpus_probe',
        'version':7,
        'corpora':{'miss8':str(args.miss8),'miss16':str(args.miss16)},
        'mission_filter':args.mission_filter,
        'outputs':['mission_geometry_summary_v7.tsv','odef_obj_semantic_records_v7.tsv','odef_dispatch_invalid_records_raw_v7.tsv','odef_class_histogram_v7.tsv','rdef_rseg_records_v7.tsv','rdef_rseg_points_interpreted_v7.tsv','rdef_rseg_width_by_kind_v7.tsv']
    }
    (out/'manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')
    if args.make_tar:
        tar_path=out.with_suffix('.tar')
        with tarfile.open(tar_path,'w') as tf:
            tf.add(out, arcname=out.name)
    print(json.dumps({'out_dir':str(out),'missions':len(mission_rows),'odef_records':len(odef_rows),'invalid_dispatch_records':len(class0_rows),'rseg_records':len(rseg_rows),'rseg_points':len(rseg_point_rows)}, indent=2))
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
