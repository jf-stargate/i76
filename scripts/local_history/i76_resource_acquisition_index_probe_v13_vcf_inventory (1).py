#!/usr/bin/env python3
"""
Interstate '76 resource acquisition audit, v13: recursive VCF inventory.

Purpose:
  Corrects the v12 naming issue where only direct asset-root children were reported
  as root-level VCFs.  This version inventories every .vcf recursively under the
  supplied asset roots, compares binary-truth ODEF label.vcf candidates against
  that inventory, and keeps Open76/SDF same-stem alternatives diagnostic-only.

Binary-backed policy:
  ODEF dispatch-valid records -> label.vcf
  ODEF spawn/regen -> special marker
  ODEF blank/class 0 -> special/invalid diagnostic
  LDEF records -> label.sdf
"""
from __future__ import annotations

import argparse, csv, json, os, struct, tarfile, time
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}

class Chunk:
    __slots__ = ("tag","offset","size","payload_offset","payload_size","parent")
    def __init__(self, tag, offset, size, payload_offset, payload_size, parent=""):
        self.tag=tag; self.offset=offset; self.size=size; self.payload_offset=payload_offset; self.payload_size=payload_size; self.parent=parent
    @property
    def end(self): return self.offset+self.size

def u32(data: bytes, off: int) -> int:
    return struct.unpack_from('<I', data, off)[0]

def f32(data: bytes, off: int) -> float:
    return struct.unpack_from('<f', data, off)[0]

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode('ascii', errors='replace')

def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out=[]; off=start
    while off+8 <= end:
        tag=fourcc(data, off); size=u32(data, off+4)
        if size < 8 or off+size > end: break
        out.append(Chunk(tag, off, size, off+8, size-8, parent))
        off += size
    return out

def parse_tree(data: bytes) -> List[Chunk]:
    roots=parse_flat(data,0,len(data),"")
    allc=[]
    def rec(chunks):
        for c in chunks:
            allc.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids=parse_flat(data,c.payload_offset,c.end,c.tag)
                if kids: rec(kids)
    rec(roots)
    return allc

def decode_label(raw: bytes) -> Tuple[str,int]:
    chars=[]; bits=0
    for i,b in enumerate(raw[:8]):
        if b & 0x80: bits |= (1<<i)
        c=b & 0x7f
        if c == 0: break
        chars.append(chr(c))
    return ''.join(chars).strip(), bits

def find_files(root: Path) -> List[Path]:
    if root.is_file(): return [root]
    return [p for p in root.rglob('*') if p.is_file()]

def collect_assets(roots: List[Path]):
    files=[]
    for r in roots:
        if r.exists(): files.extend(find_files(r))
    by_name: Dict[str,List[Path]]={}
    by_stem: Dict[str,List[Path]]={}
    ext_counts: Dict[str,int]={}
    for p in files:
        name=p.name.lower(); stem=p.stem.lower(); ext=p.suffix.lower()
        by_name.setdefault(name,[]).append(p)
        by_stem.setdefault(stem,[]).append(p)
        ext_counts[ext]=ext_counts.get(ext,0)+1
    return files, by_name, by_stem, ext_counts

def iter_missions(root: Path) -> List[Path]:
    return [p for p in find_files(root) if p.suffix.lower() in {'.msn','.lvl','.spc'}]

def write_tsv(path: Path, rows: List[dict], fields: List[str]):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('w', newline='', encoding='utf-8') as f:
        w=csv.DictWriter(f, fieldnames=fields, delimiter='\t', extrasaction='ignore')
        w.writeheader()
        for r in rows: w.writerow(r)

def scan_objects(miss_roots: List[Tuple[str,Path]], mission_filter: str) -> List[dict]:
    rows=[]
    for corpus, root in miss_roots:
        for msn in sorted(iter_missions(root)):
            if mission_filter and mission_filter.lower() not in msn.name.lower() and mission_filter.lower() not in msn.stem.lower():
                continue
            data=msn.read_bytes(); chunks=parse_tree(data)
            for c in chunks:
                if c.tag == 'OBJ\x00' and c.parent == 'ODEF' and c.payload_size >= 0x64:
                    off=c.payload_offset; raw=data[off:off+8]; label,bits=decode_label(raw)
                    cls=data[off+0x5c]
                    if not label or cls == 0:
                        policy='odef_blank_or_class0_special'; cand=''
                    elif label.lower() in {'spawn','regen'}:
                        policy='odef_spawn_regen_special'; cand=''
                    else:
                        policy='binary_odef_vcf'; cand=label.lower()+'.vcf'
                    rows.append({
                        'corpus':corpus,'mission':msn.name,'chunk_offset_hex':f'0x{c.offset:08x}','parent':'ODEF',
                        'label':label,'raw_name_hex':raw.hex(),'label_highbits':str(bits),'class_hex':f'0x{cls:02x}',
                        'policy':policy,'candidate_name':cand,
                        'pos_x':f'{f32(data,off+0x2c):.6f}','pos_y':f'{f32(data,off+0x30):.6f}','pos_z':f'{f32(data,off+0x34):.6f}'
                    })
                elif c.tag == 'OBJ\x00' and c.parent == 'LDEF' and c.payload_size >= 8:
                    raw=data[c.payload_offset:c.payload_offset+8]; label,bits=decode_label(raw)
                    cand=label.lower()+'.sdf' if label else ''
                    rows.append({'corpus':corpus,'mission':msn.name,'chunk_offset_hex':f'0x{c.offset:08x}','parent':'LDEF','label':label,'raw_name_hex':raw.hex(),'label_highbits':str(bits),'class_hex':'','policy':'binary_ldef_sdf','candidate_name':cand,'pos_x':'','pos_y':'','pos_z':''})
    return rows

def make_tar(out_dir: Path):
    tar_path=out_dir.with_suffix('.tar')
    with tarfile.open(tar_path,'w') as t:
        t.add(out_dir, arcname=out_dir.name)
    return tar_path

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--miss8', type=Path, required=True)
    ap.add_argument('--miss16', type=Path, required=True)
    ap.add_argument('--mission-filter', default='')
    ap.add_argument('--asset-root', type=Path, action='append', required=True)
    ap.add_argument('--out-dir', type=Path, required=True)
    ap.add_argument('--make-tar', action='store_true')
    args=ap.parse_args()
    out=args.out_dir; out.mkdir(parents=True, exist_ok=True)
    files, by_name, by_stem, ext_counts = collect_assets(args.asset_root)
    obj_rows=scan_objects([('miss8',args.miss8),('miss16',args.miss16)], args.mission_filter)

    inv=[]
    for p in sorted([p for p in files if p.suffix.lower()=='.vcf'], key=lambda x: x.name.lower()):
        inv.append({'name':p.name.lower(),'stem':p.stem.lower(),'path':str(p),'size':str(p.stat().st_size),'parent':str(p.parent)})

    exact=[]; unresolved=[]; alts=[]
    for r in obj_rows:
        cand=r.get('candidate_name','')
        if not cand:
            unresolved.append(dict(r, reason=r['policy']))
            continue
        matches=by_name.get(cand.lower(),[])
        if matches:
            for p in matches:
                exact.append(dict(r, matched_name=p.name.lower(), matched_path=str(p), matched_ext=p.suffix.lower(), matched_size=str(p.stat().st_size)))
        else:
            unresolved.append(dict(r, reason='candidate_not_found'))
            stem=Path(cand).stem.lower()
            for p in by_stem.get(stem,[]):
                if p.name.lower()!=cand.lower():
                    alts.append(dict(r, alternative_name=p.name.lower(), alternative_ext=p.suffix.lower(), alternative_path=str(p), alternative_size=str(p.stat().st_size), diagnostic_only='true'))

    fields_obj=['corpus','mission','chunk_offset_hex','parent','label','raw_name_hex','label_highbits','class_hex','policy','candidate_name','pos_x','pos_y','pos_z']
    write_tsv(out/'object_records_binarytruth.tsv', obj_rows, fields_obj)
    write_tsv(out/'recursive_vcf_inventory.tsv', inv, ['name','stem','path','size','parent'])
    write_tsv(out/'binary_resource_exact_matches.tsv', exact, fields_obj+['matched_name','matched_path','matched_ext','matched_size'])
    write_tsv(out/'binary_resource_unresolved.tsv', unresolved, fields_obj+['reason'])
    write_tsv(out/'same_stem_alternative_matches.tsv', alts, fields_obj+['alternative_name','alternative_ext','alternative_path','alternative_size','diagnostic_only'])
    ext_rows=[{'ext':k,'count':v} for k,v in sorted(ext_counts.items(), key=lambda kv:(-kv[1],kv[0]))]
    write_tsv(out/'asset_extension_inventory.tsv', ext_rows, ['ext','count'])
    manifest={'format':'i76_resource_acquisition_index_probe_v13_vcf_inventory','mission_filter':args.mission_filter,'asset_roots':[str(x) for x in args.asset_root],'indexed_files':len(files),'recursive_vcf_count':len(inv),'object_records':len(obj_rows),'binary_exact_matches':len(exact),'binary_unresolved':len(unresolved),'same_stem_alternatives':len(alts),'outputs':['object_records_binarytruth.tsv','recursive_vcf_inventory.tsv','binary_resource_exact_matches.tsv','binary_resource_unresolved.tsv','same_stem_alternative_matches.tsv','asset_extension_inventory.tsv']}
    if args.make_tar:
        manifest['tar_path']=str(make_tar(out))
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2), encoding='utf-8')
    print(json.dumps(manifest,indent=2))

if __name__=='__main__': main()
