#!/usr/bin/env python3
"""
Interstate '76 object geometry resolution probe v3.

Adds alias/fuzzy resolution on top of exact asset lookup. This is intended for
mission ODEF/LDEF names that are 8-byte/truncated/underscore-normalized variants
of resource filenames, e.g. bchotel -> bchotel1.sdf, igd271 -> igd27_1.sdf,
igd27_ -> igd27_1.sdf.
"""
from __future__ import annotations
import argparse, dataclasses, json, re, struct, tarfile
from pathlib import Path
from typing import Dict, List, Tuple, Optional, Iterable

CONTAINERS={"BWD2","WDEF","TDEF","RDEF","ODEF","LDEF","ADEF"}
PREFERRED_EXTS=[".sdf",".vcf",".vdf",".geo",".sobj",".sgeo"]

@dataclasses.dataclass
class Chunk:
    tag:str; offset:int; size:int; payload_offset:int; payload_size:int; parent:str=""
    @property
    def end(self): return self.offset+self.size

def fourcc(b,o): return b[o:o+4].decode('ascii','replace')
def u32(b,o): return struct.unpack_from('<I',b,o)[0]
def f32(b,o): return struct.unpack_from('<f',b,o)[0]

def parse_flat(data,start,end,parent):
    out=[]; off=start
    while off+8<=end:
        tag=fourcc(data,off); size=u32(data,off+4)
        if size<8 or off+size>end: break
        out.append(Chunk(tag,off,size,off+8,size-8,parent)); off+=size
    return out

def parse_tree(data):
    roots=parse_flat(data,0,len(data),"")
    out=[]
    def rec(chs):
        for c in chs:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size>=8:
                kids=parse_flat(data,c.payload_offset,c.end,c.tag)
                if kids: rec(kids)
    rec(roots); return out

def clean_name(raw:bytes)->str:
    return raw.split(b'\0',1)[0].decode('ascii','ignore').strip().lower()

def is_special(name:str, cls:int)->bool:
    return (not name) or name in {'spawn','regen','spaw','rege'} or cls==0

def norm_key(s:str)->str:
    return re.sub(r'[^a-z0-9]','',s.lower())

def alias_keys(name:str)->List[str]:
    n=name.lower().strip()
    keys=[]
    def add(x):
        x=norm_key(x)
        if x and x not in keys: keys.append(x)
    add(n)
    # exact plus underscore-free variants
    add(n.replace('_',''))
    # Common 8-char truncation variants: base without final digit may match base1.
    if not re.search(r'\d$', n):
        for d in range(1,10): add(n+str(d))
    # igd271 -> igd27_1 style: split trailing digit after a numeric stem.
    m=re.match(r'^(.*\d)(\d)$', n)
    if m:
        add(m.group(1)+'_'+m.group(2))
    # igd27_ -> igd27_1
    if n.endswith('_'):
        for d in range(1,10): add(n+str(d))
    # 8-byte truncation: candidate may be first 8 chars of a longer stem.
    if len(n)>=7:
        add(n[:8])
    return keys

def index_assets(roots:List[Path]):
    exact:Dict[str,List[Path]]={}
    norm:Dict[str,List[Path]]={}
    files=[]
    for r in roots:
        if not r.exists(): continue
        for p in r.rglob('*'):
            if not p.is_file(): continue
            files.append(p)
            exact.setdefault(p.name.lower(),[]).append(p)
            stem=p.stem.lower(); ext=p.suffix.lower()
            norm.setdefault(norm_key(stem)+ext,[]).append(p)
            norm.setdefault(norm_key(stem),[]).append(p)
    return exact,norm,files

def candidate_names(name:str, section:str, cls:int)->List[str]:
    if is_special(name,cls): return []
    # Binary evidence: most ODEF M06 static/building resources are .sdf; LDEF is .sdf.
    exts=PREFERRED_EXTS
    out=[]
    for ext in exts:
        out.append(name.lower()+ext)
    return out

def parse_objects(msn:Path):
    data=msn.read_bytes(); chunks=parse_tree(data); out=[]
    for c in chunks:
        if c.parent=='ODEF' and c.tag.startswith('OBJ') and c.payload_size>=0x64:
            p=c.payload_offset; name=clean_name(data[p:p+8]); cls=u32(data,p+0x5c)&0xff
            out.append({'section':'ODEF','record_index':len([x for x in out if x['section']=='ODEF']),'name':name,'class_hex':f'0x{cls:02x}','class_int':cls,
                        'pos_x':f32(data,p+0x2c),'pos_y':f32(data,p+0x30),'pos_z':f32(data,p+0x34),'payload_size':c.payload_size})
        elif c.parent=='LDEF' and c.tag.startswith('OBJ') and c.payload_size>=8:
            p=c.payload_offset; name=clean_name(data[p:p+16]) or clean_name(data[p:p+8])
            out.append({'section':'LDEF','record_index':len([x for x in out if x['section']=='LDEF']),'name':name,'class_hex':'LDEF','class_int':-1,
                        'pos_x':'','pos_y':'','pos_z':'','payload_size':c.payload_size})
    return out

def find_files(root:Path):
    return [p for p in root.rglob('*') if p.is_file()] if root.is_dir() else [root]

def write_tsv(path:Path, rows:List[dict], cols:List[str]):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('w',encoding='utf-8') as f:
        f.write('\t'.join(cols)+'\n')
        for r in rows:
            f.write('\t'.join(str(r.get(c,'')) for c in cols)+'\n')

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--miss8',type=Path,required=True); ap.add_argument('--miss16',type=Path,required=True)
    ap.add_argument('--asset-root',type=Path,action='append',default=[])
    ap.add_argument('--mission-filter',default='')
    ap.add_argument('--out-dir',type=Path,required=True); ap.add_argument('--make-tar',action='store_true')
    args=ap.parse_args(); args.out_dir.mkdir(parents=True, exist_ok=True)
    exact,norm,files=index_assets(args.asset_root)
    records=[]; exact_matches=[]; alias_matches=[]; unresolved=[]; attempts=[]
    for label,root in [('miss8',args.miss8),('miss16',args.miss16)]:
        missions=[p for p in find_files(root) if p.suffix.lower() in {'.msn','.spc','.lvl'}]
        if args.mission_filter:
            missions=[p for p in missions if args.mission_filter.lower() in p.name.lower() or args.mission_filter.lower() in p.stem.lower()]
        for msn in sorted(missions):
            for rec in parse_objects(msn):
                rec2={'mission_set':label,'mission':msn.name,**rec}; records.append(rec2)
                name=str(rec['name']) if rec['name'] else ''
                cls=int(rec['class_int'])
                cands=candidate_names(name,rec['section'],cls)
                if not cands:
                    unresolved.append({**rec2,'reason':'special/blank/class0; no asset candidate'}); continue
                matched=False
                for cand in cands:
                    m=exact.get(cand,[])
                    attempts.append({**rec2,'candidate_name':cand,'method':'exact','match_count':len(m)})
                    for p in m:
                        exact_matches.append({**rec2,'candidate_name':cand,'matched_ext':p.suffix.lower(),'path':str(p),'method':'exact'})
                        matched=True
                if not matched:
                    # alias by normalized stem + suffix preference
                    for key in alias_keys(name):
                        for ext in PREFERRED_EXTS:
                            k=key+ext
                            m=norm.get(k,[])
                            attempts.append({**rec2,'candidate_name':k,'method':'alias_norm','match_count':len(m)})
                            for p in m:
                                alias_matches.append({**rec2,'candidate_name':p.name.lower(),'matched_ext':p.suffix.lower(),'path':str(p),'method':'alias_norm','alias_key':k})
                                matched=True
                            if matched: break
                        if matched: break
                if not matched:
                    unresolved.append({**rec2,'reason':'no exact or alias match in indexed asset roots'})
    write_tsv(args.out_dir/'object_records.tsv', records, ['mission_set','mission','section','record_index','name','class_hex','pos_x','pos_y','pos_z','payload_size'])
    write_tsv(args.out_dir/'object_resource_exact_matches.tsv', exact_matches, ['mission_set','mission','section','record_index','name','class_hex','candidate_name','matched_ext','path','method'])
    write_tsv(args.out_dir/'object_resource_alias_matches.tsv', alias_matches, ['mission_set','mission','section','record_index','name','class_hex','candidate_name','matched_ext','path','method','alias_key'])
    allm=exact_matches+alias_matches
    write_tsv(args.out_dir/'object_resource_all_matches.tsv', allm, ['mission_set','mission','section','record_index','name','class_hex','candidate_name','matched_ext','path','method','alias_key'])
    write_tsv(args.out_dir/'object_resource_candidate_attempts.tsv', attempts, ['mission_set','mission','section','record_index','name','class_hex','candidate_name','method','match_count'])
    write_tsv(args.out_dir/'unresolved_object_resources.tsv', unresolved, ['mission_set','mission','section','record_index','name','class_hex','pos_x','pos_y','pos_z','reason'])
    manifest={'format':'i76_object_geometry_resolution_probe','version':3,'asset_roots':[str(p) for p in args.asset_root],
              'asset_index_file_count':len(files),'object_records':len(records),'exact_matches':len(exact_matches),'alias_matches':len(alias_matches),'unresolved_rows':len(unresolved)}
    (args.out_dir/'manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
    if args.make_tar:
        tar_path=args.out_dir.with_suffix('.tar')
        with tarfile.open(tar_path,'w') as t: t.add(args.out_dir,arcname=args.out_dir.name)
        manifest['tar_path']=str(tar_path); (args.out_dir/'manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
    print(json.dumps(manifest,indent=2))
if __name__=='__main__': main()
