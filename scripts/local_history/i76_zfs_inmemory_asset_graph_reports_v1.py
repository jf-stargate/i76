#!/usr/bin/env python3
"""
i76_zfs_inmemory_asset_graph_reports_v1.py

Report-only Interstate '76 ZFS/ZIX asset graph builder.

Parses I76.ZFS + I76.ZIX, decompresses records in memory, parses PIX/PAK
embedded payloads in memory, and writes compact TSV/JSON reports only.
It does not write the full extracted payload corpus.

Example:
  python3 i76_zfs_inmemory_asset_graph_reports_v1.py \
      --zfs I76.ZFS --zix I76.ZIX \
      --out i76_zfs_graph_reports_v1 --overwrite
"""
from __future__ import annotations

import argparse, ctypes, ctypes.util, csv, hashlib, json, re, shutil, struct, sys, time
from collections import defaultdict, deque
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Set, Tuple

ZFSF_HEADER_SIZE = 0x1C
ZFSF_RECORD_SIZE = 0x24
ZFSF_DTABLE_RECORDS = 100
ZFSF_DTABLE_SIZE = 4 + ZFSF_RECORD_SIZE * ZFSF_DTABLE_RECORDS
GRAPH_EXTS = {"vcf","vdf","vtf","wdf","gdf","geo","tmt","map","m16","vqm","cbk"}
INSPECT_EXTS = GRAPH_EXTS | {"sdf","act","npt","hzd","xdf","gpw","tab","tbl"}
EXPLICIT_REF_RE = re.compile(rb"(?i)\b([A-Z0-9_+\-]{1,16})\.(VCF|VDF|VTF|WDF|GDF|GEO|TMT|MAP|M16|VQM|CBK|WAV|SDF|ACT|NPT|HZD|XDF|GPW|PAK|PIX|SMK|LST|TXT|CDF|TAB|TBL)\b")
TOKEN_RE = re.compile(rb"[A-Za-z0-9_+\-]{3,16}")

@dataclass
class ZfsRecord:
    index:int; record_id:int; name:str; extension:str; file_offset:int; stored_size:int; logical_size:int; flags_size:int; compression:int; compression_name:str; unix_timestamp:int; active:bool; dtable_index:int; dtable_slot:int
@dataclass
class ZixEntry:
    index:int; prefix:str; name:str
@dataclass
class ManifestRecord:
    index:int; record_id:int; name:str; extension:str; zix_name:str; zix_prefix:str; zix_name_matches:bool; file_offset:int; stored_size:int; logical_size:int; actual_size:int; flags_size:str; compression:str; unix_timestamp:int; active:bool; sha256:str; decoded_type:str; error:str
@dataclass
class EmbeddedAsset:
    asset_id:str; pix_record_index:int; pak_record_index:int; pix_name:str; pak_name:str; asset_index:int; asset_name:str; asset_ext:str; offset:int; size:int; sha256:str; decoded_type:str; error:str
@dataclass
class AssetNode:
    asset_id:str; name:str; norm_name:str; stem:str; ext:str; source:str; record_index:int; parent_record_index:int; pix_name:str; pak_name:str; size:int; sha256:str; decoded_type:str
@dataclass
class AssetEdge:
    source_id:str; source_name:str; source_ext:str; target_id:str; target_name:str; target_ext:str; ref_text:str; ref_ext:str; edge_type:str; confidence:str; evidence:str
@dataclass
class UnresolvedRef:
    source_id:str; source_name:str; source_ext:str; ref_text:str; ref_ext:str; edge_type:str; confidence:str; evidence:str

class Lzo:
    def __init__(self):
        candidates=[]
        found=ctypes.util.find_library("lzo2")
        if found: candidates.append(found)
        candidates += ["liblzo2.so.2","liblzo2.so","lzo2.dll","liblzo2.dylib"]
        self.lib=None; last=None
        for c in candidates:
            try:
                self.lib=ctypes.CDLL(c); break
            except OSError as e:
                last=e
        if self.lib is None:
            raise RuntimeError(f"Could not load liblzo2. Install liblzo2-2. Last error: {last!r}")
        for name in ["lzo1x_decompress_safe","lzo1y_decompress_safe"]:
            fn=getattr(self.lib,name)
            fn.argtypes=[ctypes.c_void_p,ctypes.c_size_t,ctypes.c_void_p,ctypes.POINTER(ctypes.c_size_t),ctypes.c_void_p]
            fn.restype=ctypes.c_int
    def decompress(self, payload:bytes, logical_size:int, compression:int)->bytes:
        if compression==0: return payload
        if compression==0x02: fn=self.lib.lzo1x_decompress_safe
        elif compression==0x04: fn=self.lib.lzo1y_decompress_safe
        else: raise ValueError(f"unsupported compression mode 0x{compression:02x}")
        src=ctypes.create_string_buffer(payload,len(payload)); dst=ctypes.create_string_buffer(logical_size); out_len=ctypes.c_size_t(logical_size)
        rc=fn(src,len(payload),dst,ctypes.byref(out_len),None)
        if rc!=0: raise RuntimeError(f"liblzo failed rc={rc} mode=0x{compression:02x} stored={len(payload)} logical={logical_size}")
        return dst.raw[:out_len.value]

def norm_name(name:str)->str: return name.replace('\\','/').split('/')[-1].strip().upper()
def stem_of(name:str)->str:
    n=norm_name(name); return n.rsplit('.',1)[0] if '.' in n else n
def ext_of(name:str)->str:
    n=norm_name(name); return n.rsplit('.',1)[-1].lower() if '.' in n else ''
def safe_name(name:str)->str: return re.sub(r"[^A-Za-z0-9._+\-]+","_",name.replace('\\','/').split('/')[-1]) or "unnamed"
def sha256_hex(data:bytes)->str: return hashlib.sha256(data).hexdigest()
def compression_name(mode:int)->str: return {0:"stored",0x02:"lzo1x",0x04:"lzo1y"}.get(mode,f"unknown_0x{mode:02x}")
def is_text_like(data:bytes)->bool:
    if not data: return False
    s=data[:min(len(data),4096)]; good=sum(1 for b in s if b in (9,10,13) or 32<=b<=126)
    return good/len(s)>=0.88
def looks_like_pix(data:bytes)->bool:
    try: text=data.decode('ascii')
    except UnicodeDecodeError: return False
    lines=[ln.strip() for ln in text.splitlines() if ln.strip()]
    return bool(lines and re.match(r"^\d+$",lines[0]) and any(re.match(r"^[^\s]+\s+\d+\s+\d+$",ln) for ln in lines[1:min(len(lines),10)]))
def classify_payload(name:str,data:bytes)->str:
    e=ext_of(name)
    if e=='pix': return 'pix_text_index' if looks_like_pix(data) else 'pix_unknown'
    if e=='pak': return 'pak_binary_payload'
    if data.startswith(b'RIFF') and data[8:12]==b'WAVE': return 'audio_wav_riff'
    if data[:4]==b'OEG.' or e=='geo': return 'geo_geometry'
    if data.startswith(b'BWD2'): return 'bwd2_chunked_resource'
    if e=='vqm': return 'vqm_image_or_texture'
    if e=='cbk': return 'vqm_cbk_codebook'
    if e=='m16': return 'm16_image_or_texture'
    if e=='map': return 'texture_map'
    if e=='tmt': return 'texture_material_table'
    if e in {'vcf','vdf','vtf','wdf','gdf','sdf','act','npt','hzd','xdf','gpw','fsi','rtm','tab','tbl','cdf'}: return f'{e}_definition_or_table'
    if e=='wav': return 'audio_wav_unknown_header'
    if is_text_like(data): return 'text_like'
    return 'binary_unknown'

def ensure_clean_dir(path:Path, overwrite:bool):
    if path.exists():
        if not overwrite: raise FileExistsError(f"output exists: {path}. Use --overwrite")
        shutil.rmtree(path)
    path.mkdir(parents=True,exist_ok=True)
def write_tsv(path:Path, rows:Iterable[Dict[str,object]], fields:List[str]):
    with path.open('w',encoding='utf-8',newline='') as f:
        f.write('\t'.join(fields)+'\n')
        for row in rows:
            f.write('\t'.join(str(row.get(k,'')).replace('\t',' ').replace('\r',' ').replace('\n',' ') for k in fields)+'\n')
def write_json(path:Path,obj:object): path.write_text(json.dumps(obj,indent=2,sort_keys=True),encoding='utf-8')

def parse_zfs_records(zfs:Path)->Tuple[Dict[str,int],List[ZfsRecord]]:
    with zfs.open('rb') as f:
        hdr=f.read(ZFSF_HEADER_SIZE)
        magic,version,name_size,per_dtable,record_count,xor_key,first_dtable=struct.unpack('<4sIIIIII',hdr)
        if magic!=b'ZFSF': raise ValueError(f'bad magic {magic!r}')
        header={"version":version,"record_name_size":name_size,"records_per_dtable":per_dtable,"record_count":record_count,"xor_key":xor_key,"first_dtable_offset":first_dtable}
        records=[]; dtable_offset=first_dtable; dtable_idx=0; seen=set()
        while dtable_offset and len(records)<record_count:
            if dtable_offset in seen: raise ValueError(f'dtable loop at {dtable_offset:x}')
            seen.add(dtable_offset); f.seek(dtable_offset); data=f.read(ZFSF_DTABLE_SIZE)
            if len(data)!=ZFSF_DTABLE_SIZE: raise IOError(f'short dtable at 0x{dtable_offset:x}')
            next_dtable=struct.unpack_from('<I',data,0)[0]
            for slot in range(ZFSF_DTABLE_RECORDS):
                if len(records)>=record_count: break
                off=4+slot*ZFSF_RECORD_SIZE
                name=data[off:off+0x10].split(b'\0',1)[0].decode('ascii','replace')
                file_offset,record_id,stored_size,unix_ts,flags_size=struct.unpack_from('<IIIII',data,off+0x10)
                comp=flags_size&0xff
                records.append(ZfsRecord(len(records),record_id,name,ext_of(name),file_offset,stored_size,flags_size>>8,flags_size,comp,compression_name(comp),unix_ts,(comp&1)==0,dtable_idx,slot))
            dtable_offset=next_dtable; dtable_idx+=1
        header['dtable_count_parsed']=dtable_idx
        return header,records

def parse_zix(zix:Optional[Path])->List[ZixEntry]:
    if not zix: return []
    out=[]
    for raw in zix.read_text(errors='replace').splitlines():
        line=raw.strip(); m=re.match(r'^(\d+)\s+(.+)$',line)
        if not m: continue
        prefix,name=m.group(1),m.group(2).strip()
        if prefix=='0' or name.startswith('\\') or ' ' in name: continue
        out.append(ZixEntry(len(out),prefix,name))
    return out

def decompress_records(zfs:Path, records:List[ZfsRecord], zix_entries:List[ZixEntry], max_records:Optional[int]):
    lzo=Lzo(); zix_by_idx={e.index:e for e in zix_entries}; payloads={}; manifest=[]; errors=[]
    work=records if max_records is None else records[:max_records]
    with zfs.open('rb') as f:
        for i,rec in enumerate(work):
            if i%250==0: print(f"[zfs] {i}/{len(work)} {rec.name}",file=sys.stderr)
            zix=zix_by_idx.get(rec.index); err=''; blob=b''; h=''; dtype=''; actual=0
            try:
                f.seek(rec.file_offset); stored=f.read(rec.stored_size)
                if len(stored)!=rec.stored_size: raise IOError(f'short read got {len(stored)} expected {rec.stored_size}')
                blob=lzo.decompress(stored,rec.logical_size,rec.compression); actual=len(blob); h=sha256_hex(blob); dtype=classify_payload(rec.name,blob)
                if actual!=rec.logical_size: err=f'decoded size mismatch actual={actual} logical={rec.logical_size}'
                payloads[rec.index]=blob
            except Exception as e:
                err=str(e); errors.append({'index':rec.index,'name':rec.name,'error':err})
            manifest.append(ManifestRecord(rec.index,rec.record_id,rec.name,rec.extension,zix.name if zix else '',zix.prefix if zix else '',bool(zix and zix.name.lower()==rec.name.lower()),rec.file_offset,rec.stored_size,rec.logical_size,actual,f'0x{rec.flags_size:08x}',rec.compression_name,rec.unix_timestamp,rec.active,h,dtype,err))
    return payloads,manifest,errors

def parse_pix_index(data:bytes):
    try: text=data.decode('ascii')
    except UnicodeDecodeError as e: return 0,[],f'ascii decode failed: {e}'
    lines=[ln.strip() for ln in text.splitlines() if ln.strip()]
    if not lines: return 0,[],'empty pix'
    try: declared=int(lines[0])
    except ValueError: return 0,[],f'bad count line {lines[0]!r}'
    rows=[]
    for lineno,ln in enumerate(lines[1:],2):
        p=ln.split()
        if len(p)!=3: return declared,rows,f'bad line {lineno}: {ln!r}'
        try: rows.append((p[0],int(p[1],0),int(p[2],0)))
        except ValueError: return declared,rows,f'bad numeric line {lineno}: {ln!r}'
    return declared,rows,'' if declared==len(rows) else f'declared {declared} parsed {len(rows)}'

def materialize_embedded(records:List[ZfsRecord], payloads:Dict[int,bytes], max_pix:Optional[int]):
    by_lower={r.name.lower():r for r in records}; pix_records=[r for r in records if r.extension=='pix' and r.index in payloads]
    if max_pix is not None: pix_records=pix_records[:max_pix]
    embedded=[]; emb_payloads={}
    for i,pix in enumerate(pix_records):
        if i%250==0: print(f"[pixpak] {i}/{len(pix_records)} {pix.name}",file=sys.stderr)
        declared,rows,pix_err=parse_pix_index(payloads[pix.index]); stem=pix.name.rsplit('.',1)[0]; pak_name=stem+'.pak'; pak=by_lower.get(pak_name.lower())
        if pak is None or pak.index not in payloads:
            embedded.append(EmbeddedAsset(f'emb_missing:{pix.index:06d}',pix.index,-1,pix.name,pak_name,-1,'','',0,0,'','',f'missing sibling pak; pix_error={pix_err}')); continue
        pak_data=payloads[pak.index]
        if pix_err: embedded.append(EmbeddedAsset(f'emb_warn:{pix.index:06d}',pix.index,pak.index,pix.name,pak.name,-1,'','',0,0,'','',f'pix warning: {pix_err}'))
        for asset_idx,(name,off,size) in enumerate(rows):
            err=''; blob=b''; h=''; dtype=''
            if off<0 or size<0 or off+size>len(pak_data): err=f'slice out of range pak_size={len(pak_data)} off={off} size={size}'
            else:
                blob=pak_data[off:off+size]; h=sha256_hex(blob); dtype=classify_payload(name,blob)
            aid=f'emb:{pak.index:06d}:{asset_idx:04d}:{norm_name(name)}'
            embedded.append(EmbeddedAsset(aid,pix.index,pak.index,pix.name,pak.name,asset_idx,name,ext_of(name),off,size,h,dtype,err))
            if not err: emb_payloads[aid]=blob
    return embedded,emb_payloads

class AssetIndex:
    def __init__(self,nodes:List[AssetNode]):
        self.nodes=nodes; self.by_id={n.asset_id:n for n in nodes}; self.by_norm=defaultdict(list); self.by_stem_ext=defaultdict(list); self.stems_by_ext=defaultdict(set)
        for n in nodes:
            self.by_norm[n.norm_name].append(n); self.by_stem_ext[(n.stem,n.ext)].append(n); self.stems_by_ext[n.ext].add(n.stem)
    def resolve(self,ref_text:str,preferred_ext:Optional[str],source:Optional[AssetNode]):
        refn=norm_name(ref_text)
        if '.' in refn:
            cands=list(self.by_norm.get(refn,[]))
            if preferred_ext: cands=[c for c in cands if c.ext==preferred_ext] or cands
        else:
            if not preferred_ext: return None
            cands=list(self.by_stem_ext.get((refn,preferred_ext),[]))
        if not cands: return None
        if source and source.source=='embedded':
            same=[c for c in cands if c.parent_record_index==source.parent_record_index]
            if same: cands=same
        if preferred_ext in {'geo','tmt','map','m16','vqm','cbk'}:
            emb=[c for c in cands if c.source=='embedded']
            if emb: cands=emb
        cands.sort(key=lambda n:(n.source!='top_level',n.name,n.asset_id)); return cands[0]

def build_nodes(manifest:List[ManifestRecord], embedded:List[EmbeddedAsset])->List[AssetNode]:
    nodes=[]
    for m in manifest:
        nodes.append(AssetNode(f'top:{m.index:06d}:{norm_name(m.name)}',m.name,norm_name(m.name),stem_of(m.name),m.extension,'top_level',m.index,-1,'','',m.actual_size,m.sha256,m.decoded_type))
    for e in embedded:
        if e.error or e.asset_index<0: continue
        nodes.append(AssetNode(e.asset_id,e.asset_name,norm_name(e.asset_name),stem_of(e.asset_name),e.asset_ext,'embedded',-1,e.pak_record_index,e.pix_name,e.pak_name,e.size,e.sha256,e.decoded_type))
    return nodes

def candidate_exts_for_source(ext:str)->List[str]:
    d={'vcf':['vdf','vtf','wdf','gdf'],'vdf':['geo','vdf','sdf','gdf'],'vtf':['tmt','map','m16','vqm','vdf'],'tmt':['m16','vqm','map','tmt'],'map':['m16','vqm','tmt','cbk'],'vqm':['cbk'],'wdf':['geo','m16','vqm','wav'],'gdf':['geo','m16','vqm']}
    if ext in {'sdf','act','npt','hzd','xdf','gpw','tab','tbl'}: return ['geo','m16','vqm','wav','sdf','act','npt','hzd','xdf','gpw']
    return d.get(ext,[])
def explicit_refs(data:bytes):
    out=[]; seen=set()
    for m in EXPLICIT_REF_RE.finditer(data):
        ref=(m.group(1).decode('ascii','replace')+'.'+m.group(2).decode('ascii','replace')).upper(); ex=ref.rsplit('.',1)[1].lower()
        if ref not in seen: seen.add(ref); out.append((ref,ex))
    return out
def token_refs(data:bytes,max_tokens:int):
    out=[]; seen=set()
    for m in TOKEN_RE.finditer(data):
        tok=m.group(0).decode('ascii','replace').upper()
        if tok.isdigit() or tok in seen: continue
        seen.add(tok); out.append(tok)
        if len(out)>=max_tokens: break
    return out
def vqm_cbk_refs(data:bytes):
    if len(data)<0x14: return []
    cbk=data[0x08:0x14].split(b'\0',1)[0].decode('ascii','replace').strip().upper()
    if not cbk: return []
    if '.' not in cbk: cbk+='.CBK'
    return [(cbk,'cbk')]
def payload_for_node(node:AssetNode,top_payloads,emb_payloads): return top_payloads.get(node.record_index) if node.source=='top_level' else emb_payloads.get(node.asset_id)

def build_edges(nodes,idx,top_payloads,emb_payloads,max_bytes,max_tokens):
    edges=[]; unresolved=[]; seen_edges=set(); inspect=[n for n in nodes if n.ext in INSPECT_EXTS]
    for i,n in enumerate(inspect):
        if i%1000==0: print(f"[graph] {i}/{len(inspect)} {n.name}",file=sys.stderr)
        data=payload_for_node(n,top_payloads,emb_payloads)
        if data is None: continue
        if len(data)>max_bytes: data=data[:max_bytes]
        refs=explicit_refs(data)+(vqm_cbk_refs(data) if n.ext=='vqm' else [])
        for ref,rext in refs:
            target=idx.resolve(ref,rext,n); etype='vqm_cbk_header' if n.ext=='vqm' and rext=='cbk' else 'explicit_filename'
            if target:
                key=(n.asset_id,target.asset_id,ref,etype)
                if key in seen_edges: continue
                seen_edges.add(key); edges.append(AssetEdge(n.asset_id,n.name,n.ext,target.asset_id,target.name,target.ext,ref,rext,etype,'high','explicit filename or VQM CBK header'))
            else:
                unresolved.append(UnresolvedRef(n.asset_id,n.name,n.ext,ref,rext,etype,'high','explicit filename or VQM CBK header'))
        cexts=candidate_exts_for_source(n.ext)
        if cexts:
            for tok in token_refs(data,max_tokens):
                if '.' in tok: continue
                for ex in cexts:
                    if tok not in idx.stems_by_ext.get(ex,set()): continue
                    target=idx.resolve(tok,ex,n)
                    if not target or target.asset_id==n.asset_id: continue
                    ref=f'{tok}.{ex.upper()}'; etype=f'{n.ext}_implicit_{ex}_ref'; key=(n.asset_id,target.asset_id,ref,etype)
                    if key not in seen_edges:
                        seen_edges.add(key); edges.append(AssetEdge(n.asset_id,n.name,n.ext,target.asset_id,target.name,target.ext,ref,ex,etype,'medium',f"token {tok!r} matched known .{ex} asset stem"))
    return edges,unresolved

def vehicle_graphs(nodes,edges,out,depth):
    vg=out/'vehicle_asset_graphs'; vg.mkdir(parents=True,exist_ok=True); by_src=defaultdict(list); by_id={n.asset_id:n for n in nodes}
    for e in edges: by_src[e.source_id].append(e)
    rows=[]
    for root in sorted([n for n in nodes if n.ext=='vcf'],key=lambda n:n.norm_name):
        seen={root.asset_id}; q=deque([(root.asset_id,0)]); ge=[]
        while q:
            nid,d=q.popleft()
            if d>=depth: continue
            for e in by_src.get(nid,[]):
                ge.append(e)
                if e.target_id not in seen: seen.add(e.target_id); q.append((e.target_id,d+1))
        gn=[by_id[nid] for nid in sorted(seen) if nid in by_id]; fname=safe_name(root.name)+'.json'
        write_json(vg/fname,{'root':asdict(root),'node_count':len(gn),'edge_count':len(ge),'nodes':[asdict(n) for n in gn],'edges':[asdict(e) for e in ge]})
        rows.append({'vehicle':root.name,'asset_id':root.asset_id,'node_count':len(gn),'edge_count':len(ge),'graph_relpath':f'vehicle_asset_graphs/{fname}'})
    write_tsv(vg/'index.tsv',rows,['vehicle','asset_id','node_count','edge_count','graph_relpath']); return rows

def main():
    ap=argparse.ArgumentParser(); ap.add_argument('--zfs',required=True,type=Path); ap.add_argument('--zix',type=Path); ap.add_argument('--out',required=True,type=Path); ap.add_argument('--overwrite',action='store_true'); ap.add_argument('--max-records',type=int); ap.add_argument('--max-pix',type=int); ap.add_argument('--max-bytes',type=int,default=1000000); ap.add_argument('--max-tokens',type=int,default=4000); ap.add_argument('--vehicle-depth',type=int,default=8)
    args=ap.parse_args(); t0=time.time(); ensure_clean_dir(args.out,args.overwrite)
    header,records=parse_zfs_records(args.zfs); zix_entries=parse_zix(args.zix); top_payloads,manifest,errors=decompress_records(args.zfs,records,zix_entries,args.max_records); embedded,emb_payloads=materialize_embedded(records,top_payloads,args.max_pix); nodes=build_nodes(manifest,embedded); idx=AssetIndex(nodes); edges,unresolved=build_edges(nodes,idx,top_payloads,emb_payloads,args.max_bytes,args.max_tokens); vehicle_rows=vehicle_graphs(nodes,edges,args.out,args.vehicle_depth)
    write_tsv(args.out/'zfs_records.tsv',[asdict(r) for r in records],list(asdict(records[0]).keys()))
    write_tsv(args.out/'zix_listing.tsv',[asdict(z) for z in zix_entries],['index','prefix','name'])
    write_tsv(args.out/'manifest.tsv',[asdict(m) for m in manifest],list(asdict(manifest[0]).keys()) if manifest else [])
    write_tsv(args.out/'embedded_asset_manifest.tsv',[asdict(e) for e in embedded],list(asdict(embedded[0]).keys()) if embedded else ['asset_id','pix_record_index','pak_record_index','pix_name','pak_name','asset_index','asset_name','asset_ext','offset','size','sha256','decoded_type','error'])
    write_tsv(args.out/'asset_nodes.tsv',[asdict(n) for n in nodes],list(asdict(nodes[0]).keys()) if nodes else [])
    write_tsv(args.out/'asset_edges.tsv',[asdict(e) for e in edges],list(asdict(edges[0]).keys()) if edges else ['source_id','source_name','source_ext','target_id','target_name','target_ext','ref_text','ref_ext','edge_type','confidence','evidence'])
    write_tsv(args.out/'unresolved_references.tsv',[asdict(u) for u in unresolved],list(asdict(unresolved[0]).keys()) if unresolved else ['source_id','source_name','source_ext','ref_text','ref_ext','edge_type','confidence','evidence'])
    write_tsv(args.out/'errors.tsv',errors,['index','name','error'])
    def count(rows,attr):
        d=defaultdict(int)
        for r in rows: d[getattr(r,attr) or '_none']+=1
        return dict(sorted(d.items(),key=lambda kv:(-kv[1],kv[0])))
    edge_type_counts=defaultdict(int); target_ext_counts=defaultdict(int)
    for e in edges: edge_type_counts[e.edge_type]+=1; target_ext_counts[e.target_ext or '_none']+=1
    summary={'zfs_path':str(args.zfs),'zix_path':str(args.zix) if args.zix else '', 'out':str(args.out),'header':header,'records_total':len(records),'records_processed':len(manifest),'zix_entries':len(zix_entries),'embedded_assets':len([e for e in embedded if not e.error and e.asset_index>=0]),'embedded_error_or_warning_rows':len([e for e in embedded if e.error]),'asset_nodes':len(nodes),'asset_edges':len(edges),'unresolved_references':len(unresolved),'vehicle_graph_count':len(vehicle_rows),'top_level_extension_counts':count(manifest,'extension'),'top_level_decoded_type_counts':count(manifest,'decoded_type'),'embedded_extension_counts':count([e for e in embedded if not e.error and e.asset_index>=0],'asset_ext'),'edge_type_counts':dict(sorted(edge_type_counts.items(),key=lambda kv:(-kv[1],kv[0]))),'target_extension_counts':dict(sorted(target_ext_counts.items(),key=lambda kv:(-kv[1],kv[0]))),'errors':len(errors),'elapsed_seconds':round(time.time()-t0,3)}
    write_json(args.out/'summary.json',summary); (args.out/'README.txt').write_text('I76 ZFS in-memory asset graph reports v1\n\nFiles: summary.json, zfs_records.tsv, zix_listing.tsv, manifest.tsv, embedded_asset_manifest.tsv, asset_nodes.tsv, asset_edges.tsv, unresolved_references.tsv, vehicle_asset_graphs/index.tsv, vehicle_asset_graphs/*.json, errors.tsv\n\nConfidence: high = explicit filename string or VQM CBK header; medium = token matched known asset stem with expected extension.\n',encoding='utf-8')
    print(json.dumps(summary,indent=2,sort_keys=True)); return 0
if __name__=='__main__': raise SystemExit(main())
