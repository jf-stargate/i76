"""Authenticate mission-selected ACT/LUM/TBL against ZFS and inventory. Metadata only."""
import argparse, collections, hashlib, importlib.util,json,sys
from pathlib import Path
from color_model import tbl_init,lum_init,update_lum_column
sys.dont_write_bytecode=True
def sha(b):return hashlib.sha256(b).hexdigest()
def load(n,p):
 s=importlib.util.spec_from_file_location(n,p);m=importlib.util.module_from_spec(s);sys.modules[n]=m;s.loader.exec_module(m);return m
def survey(root,repo):
 z=load('zfs',repo/'scripts/game/i76_zfs_extract.py');w=load('wrld',repo/'agent/runs/i76exe/i76exe-20261104T183156Z-085a5e76/scripts/wrld.py')
 archive=root/'orig/I76.ZFS';blob=archive.read_bytes();h=z.parse_header(blob);records,_=z.parse_records(blob,h);assert h.xor_key==0
 live={r.name.lower():r for r in records if not r.inactive};dec=z.LzoDecompressor();cache={}
 def payload(n):
  if n not in cache:
   r=live[n];b=blob[r.file_offset:r.file_offset+r.stored_size];assert len(b)==r.stored_size
   b=dec.decompress(r.mode,b,r.logical_size) if r.mode&6 else b
   assert len(b)==(r.logical_size if r.mode&6 else r.stored_size);cache[n]=b
  return cache[n]
 inventory=collections.defaultdict(list)
 for n in live:inventory[n].append(('zfs',n,0,None))
 for n in live:
  if n.endswith('.pix'):
   lines=payload(n).decode('ascii').splitlines();rows=[s.split() for s in lines[1:] if s.strip()];assert len(rows)==int(lines[0])
   for key,off,size in rows:inventory[key.lower()].append(('pix',n[:-4]+'.pak',int(off,0),int(size,0)))
 for d in ['orig','orig/miss8','orig/miss16','orig/ADDON']:
  for p in (root/d).iterdir():
   if p.is_file():inventory[p.name.lower()].append(('loose',str(p.relative_to(root)),0,None))
 missions=[];use=collections.defaultdict(list)
 for mode in ['miss8','miss16']:
  for p in sorted((root/'orig'/mode).glob('*.MSN')):
   b=p.read_bytes();a=w.inspect(b);assert len(a)==1;names=a[0][3].names
   r={'path':mode+'/'+p.name,'sha256':sha(b),'length':len(b)}
   for k in ['palette','luminance','blend_table']:
    r[k]=names[k];use[names[k].lower()].append(r['path'])
   missions.append(r)
 resources=[]
 for n in sorted(use):
  hits=[];bs=[]
  for kind,src,off,size in inventory[n]:
   b=(root/src).read_bytes() if kind=='loose' else payload(src)
   if kind=='pix':assert off+size<=len(b);b=b[off:off+size]
   hit={'kind':kind,'source':src,'offset':off,'length':len(b),'sha256':sha(b)}
   if kind in ('zfs','pix'):
    rec=live[src];hit.update(zfs_record_index=rec.index,zfs_file_offset=rec.file_offset,zfs_stored_size=rec.stored_size,zfs_mode=rec.mode)
   hits.append(hit);bs.append(b)
  if not bs:
   resources.append({'name':n,'missions':use[n],'status':'unresolved','sources':[]});continue
  assert len(set(map(sha,bs)))==1,(n,'ambiguous')
  b=bs[0];extracted=root/'zfs/resources'/n;assert extracted.read_bytes()==b
  r={'name':n,'length':len(b),'sha256':sha(b),'missions':use[n],'sources':hits,'extracted_matches':True,'minimum':min(b),'maximum':max(b),'zero_count':b.count(0),'distinct_bytes':len(set(b))}
  if len(b)==65536:
   r.update(identity_rows=[i for i in range(256) if b[i*256:(i+1)*256]==bytes(range(256))],constant_rows=[i for i in range(256) if len(set(b[i*256:(i+1)*256]))==1],transpose_differences=sum(b[i*256+j]!=b[j*256+i] for i in range(256) for j in range(256)),unique_rows=len(set(b[i*256:(i+1)*256] for i in range(256))))
  if n.endswith('.lum'):
   r['model_supplied_lum_sha256']=sha(lum_init(b))
   r['model_after_column239_sha256']=sha(update_lum_column(b,224,239,239))
   r['rows32_143_equal31']=all(b[i*256:(i+1)*256]==b[31*256:32*256] for i in range(32,144))
   r['rows144_255_equal0']=all(b[i*256:(i+1)*256]==b[:256] for i in range(144,256))
   r['column255_identity_first32']=all(b[i*256+255]==i for i in range(32))
  if n.endswith('.tbl'):
   r['model_runtime_tbl_sha256']=sha(tbl_init(b))
   r['row255_identity_change_count']=sum(b[65280+i]!=i for i in range(256))
   r['column255_vs_source_differences']=sum(b[i*256+255]!=i for i in range(256))
  resources.append(r)
 pairs=[];by={r['path']:r for r in missions};rb={r['name']:r for r in resources}
 for r in missions:
  if not r['path'].startswith('miss8/'):continue
  q=by[r['path'].replace('miss8/','miss16/')];pair={'mission':r['path'].split('/')[1]}
  for k in ['palette','luminance','blend_table']:pair[k]={'miss8':r[k],'miss16':q[k],'same_name':r[k].lower()==q[k].lower(),'same_payload':(rb[r[k].lower()].get('sha256')==rb[q[k].lower()].get('sha256')) if 'sha256' in rb[r[k].lower()] and 'sha256' in rb[q[k].lower()] else None}
  pairs.append(pair)
 summary={}
 for ext in ['act','lum','tbl']:
  rows=[r for r in resources if r['name'].endswith('.'+ext)]
  summary[ext]={'names':len(rows),'resolved':sum('sha256' in r for r in rows),'payloads':len(set(r['sha256'] for r in rows if 'sha256' in r)),'lengths':dict(collections.Counter(r['length'] for r in rows if 'length' in r))}
 return {'accepted_readers':[{'path':str(p.relative_to(repo)),'sha256':sha(p.read_bytes())} for p in [repo/'scripts/game/i76_zfs_extract.py',repo/'agent/runs/i76exe/i76exe-20261104T183156Z-085a5e76/scripts/wrld.py']], 'archive':{'path':'orig/I76.ZFS','length':len(blob),'sha256':sha(blob)},'summary':summary,'missions':missions,'resources':resources,'pairs':pairs}
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--root',type=Path,required=True);p.add_argument('--repo',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();v=survey(a.root,a.repo);a.output.write_text(json.dumps(v,indent=2,sort_keys=True)+'\n');print(json.dumps(v['summary']))
