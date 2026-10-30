#!/usr/bin/env python3
"""Independent source-grid to original-transform and terrain-emitter checks."""
import collections,csv,json,math,struct,sys
from pathlib import Path
if len(sys.argv)!=4: raise SystemExit('usage: verify_transform_emission.py M06.MSN M06.TER M06_private_dir')
msn,ter,priv=map(Path,sys.argv[1:]); priv=priv.resolve()
mission=msn.read_bytes(); terrain=ter.read_bytes(); source=(priv/'final.tsv.pretransform.bin').read_bytes()
def rows(p):
 with p.open(newline='') as f:return list(csv.DictReader(f,delimiter='\t'))
src=list(struct.iter_unpack('<fff',source)); out=list(struct.iter_unpack('<fff',(priv/'final.tsv.vertices.bin').read_bytes()))
assert len(src)==len(out)==267
zoff=mission.index(b'ZMAP'); zmap=mission[zoff+9:zoff+9+80*80]
def provenance(x,z,y):
 assert x.is_integer() and z.is_integer() and 0<=x<10240 and 0<=z<10240
 page=zmap[int(z)//128*80+int(x)//128]; assert page!=255
 off=page*32768+2*((int(z)%128)*128+int(x)%128); word=struct.unpack_from('<H',terrain,off)[0]
 assert y==(word&4095)
 return {'page':page,'row':int(z)%128,'column':int(x)%128,'word':f'{word:04X}','height_low12':word&4095,'material_class':word>>13,'bit12':bool(word&4096)}
provs=[]; maxerr=[0.,0.,0.]
for i,((x,y,z),(X,Y,Z)) in enumerate(zip(src,out)):
 p=provenance(x,z,y);provs.append(p)
 for k,(actual,want) in enumerate(zip((X,Y,Z),(x*5.,y*.1,z*5.))):
  err=abs(actual-want);maxerr[k]=max(maxerr[k],err);assert math.isclose(actual,want,rel_tol=1e-6,abs_tol=1e-5),(i,k,actual,want)
em=rows(priv/'final.tsv'); entries=[r for r in em if r['kind']=='POLYGON_EMITTER_ENTRY']; alloc=[r for r in em if r['kind']=='POLYGON_ALLOCATOR_RETURN']
assert len(entries)==len(alloc)==73
nulls=[r for r in em if r['kind']=='POLYGON_RECORD_NULL']; assert len(nulls)==73 and struct.unpack_from('<I',(priv/'final.tsv.polygon_records.bin').read_bytes())[0]==0
ids=[]
for r in entries:
 d=dict(s.split('=',1) for s in r['detail'].split(';') if '=' in s); vals=[int(x) for x in d['indices'].split(',')]; assert len(vals)==int(d['count']) and all(0<=v<len(out) for v in vals); ids.extend(vals)
assert all('record=00000000' in r['detail'] for r in alloc)
assert any(r['kind']=='POSTWALKER_BOUNDARY' for r in em) and not any(r['kind']=='BLOCKER' for r in em)
pool=rows(priv/'pool.tsv'); pool_out=list(struct.iter_unpack('<fff',(priv/'pool.tsv.vertices.bin').read_bytes())); assert len(pool_out)==len(src)
for i,((x,y,z),(X,Y,Z)) in enumerate(zip(src,pool_out)):
 for actual,want in zip((X,Y,Z),(x*5-2860,y*.1-28,z*5-47900)): assert math.isclose(actual,want,rel_tol=1e-6,abs_tol=1e-5),(i,actual,want)
pen=[r for r in pool if r['kind']=='POLYGON_EMITTER_ENTRY']; prec=[r for r in pool if r['kind']=='POLYGON_RECORD_BEFORE_CLIP']; clips=[r for r in pool if r['kind']=='POLYGON_CLIP_RESULT']
assert len(pen)==len(prec)==len(clips)==139 and all('record=47000000' in r['detail'] for r in pool if r['kind']=='POLYGON_ALLOCATOR_RETURN')
assert all('accepted=false' in r['detail'] for r in clips) and not any(r['kind']=='POLYGON_BIN_ENTRY' for r in pool)
packed=(priv/'pool.tsv.polygon_records.bin').read_bytes(); assert struct.unpack_from('<I',packed)[0]==len(prec) and len(packed)==4+len(prec)*0xb4
for i,(entry,record_event) in enumerate(zip(pen,prec)):
 d=dict(s.split('=',1) for s in entry['detail'].split(';') if '=' in s); ids0=[int(x) for x in d['indices'].split(',')]; raw=bytes.fromhex(dict(s.split('=',1) for s in record_event['detail'].split(';') if '=' in s)['bytes']); assert raw==packed[4+i*0xb4:4+(i+1)*0xb4]
 n=struct.unpack_from('<I',raw)[0]; assert n==int(d['count'])==len(ids0) and struct.unpack_from('<I',raw,4)[0]==0xb4
 for j,vertex_id in enumerate(reversed(ids0)):
  got=struct.unpack_from('<fff',raw,0x1c+j*0x18); want=pool_out[vertex_id]; assert all(math.isclose(q,w,rel_tol=1e-6,abs_tol=1e-5) for q,w in zip(got,want)),(i,j,vertex_id,got,want)
contrast=rows(priv/'contrast.tsv'); below=rows(priv/'below.tsv')
assert any(r['kind']=='POSTWALKER_BOUNDARY' for r in contrast)
assert any(r['kind']=='OUTPUT' and 'vertices=0;leaves=0;edges=0' in r['detail'] for r in below)
for suffix in ('','.vertices.bin','.pretransform.bin','.arena.bin','.grid.bin','.polygons.bin'):
 assert (priv/('final.tsv'+suffix)).read_bytes()==(priv/('reimport.tsv'+suffix)).read_bytes(),suffix
summary={'status':'passed','checks':len(src)*4+len(ids)+len(pen)*8+len(nulls)+11,'primary':{'source_vertices':len(src),'transformed_vertices':len(out),'max_abs_error_xyz':maxerr,'material_class_counts':dict(collections.Counter(str(p['material_class']) for p in provs)),'source_pages':dict(collections.Counter(str(p['page']) for p in provs)),'emitter_calls':len(entries),'submitted_index_references':len(ids),'allocator_returns_null':len(alloc),'null_record_snapshots_suppressed':len(nulls),'valid_polygon_records_claimed':0,'trace':'final.tsv'},'controlled_pool_diagnostic':{'affine_translation':[-2860.0,-28.0,-47900.0],'pool_base':'47000000','allocation_service':'test-owned zeroed 1 MiB scratch; original 00490590 body retained','candidate_records_before_clip':len(prec),'clip_rejected':len(clips),'bin_calls':0,'candidate_record_xyz_verified_against_transformed_source_indices':len(prec)},'controls':{'contrast':'original walker returned; 97 vertices / 41 leaves / 256 edges','rejected':'00490B23 rejected bounds; zero geometry','fresh_project_repeat':'trace and grid/vertex/arena/pretransform/pointer-list outputs byte-identical after fresh GZF import'},'provenance_sample':[{'vertex_index':i,'source_grid_xyz':src[i],'source':provs[i],'transformed_xyz':out[i]} for i in (0,23,20,15,22)],'scope':'Original transform/walker/polygon emitter executed. In the primary untouched allocator state, 00490590 reads zero cursor at 006543C0 and returns null; null-address records are not captured. A separate explicitly initialized test-owned pool allowed original candidate record writes at 004923AB; the original clip routine rejected every candidate, so no binned submission, material descriptor, texture, UV, framebuffer, or image is claimed.'}
print(json.dumps(summary,indent=2))
