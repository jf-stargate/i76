#!/usr/bin/env python3
"""Independent research verifier. Private retail inputs and full traces stay local."""
import argparse,csv,hashlib,json,struct
from pathlib import Path

def digest(p,algorithm='sha256'):
 h=hashlib.new(algorithm)
 with p.open('rb') as f:
  for chunk in iter(lambda:f.read(1<<20),b''):h.update(chunk)
 return h.hexdigest()

def data(p):
 with p.open(newline='') as f:return list(csv.DictReader(f,delimiter='\t'))

def pe_map(b,va):
 pe=struct.unpack_from('<I',b,0x3c)[0];assert b[pe:pe+4]==b'PE\0\0'
 cnt=struct.unpack_from('<H',b,pe+6)[0];oh=struct.unpack_from('<H',b,pe+20)[0];image=struct.unpack_from('<I',b,pe+24+28)[0];rva=va-image
 for i in range(cnt):
  off=pe+24+oh+40*i;size,rstart,rsize,pstart=struct.unpack_from('<IIII',b,off+8)
  if rstart<=rva<rstart+max(size,rsize):return pstart+rva-rstart
 raise ValueError(hex(va))

def validate(run,pe,zfs,gzf,first,second):
 meta=json.loads((run/'evidence/experiment_provenance.json').read_text()); checks=[]
 def ck(v,msg):
  if not v:raise AssertionError(msg)
  checks.append(msg)
 ck(digest(pe,'md5')==meta['retail_exe_md5']=='a640ea0097dbb62e0c77b7f2847c7161','retail PE MD5')
 ck(digest(pe)==meta['retail_exe_sha256']=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','PE SHA')
 ck(digest(zfs)==meta['retail_zfs_sha256']=='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d','source ZFS SHA')
 ck(digest(gzf)==meta['ghidra_v97_sha256']=='b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','annotated program SHA')
 ck(digest(first)==digest(second)==meta['private_trace_sha256']==meta['private_second_trace_sha256'],'exact repeated original-code traces')
 ck(digest(run/'scripts/I76_RenderSceneTraversalProbe.java')==meta['source_sha256'],'replay source SHA')
 wire=pe.read_bytes(); anchors=data(run/'evidence/retail_x86_anchors.tsv')
 ck(len(anchors)==21,'21 PE anchor rows')
 for row in anchors:
  addr=int(row['va'],16);value=bytes.fromhex(row['original_pe_bytes']);off=pe_map(wire,addr)
  ck(wire[off:off+len(value)]==value,hex(addr)+' original retail instruction bytes')
 runs=data(run/'evidence/native_traversal_summary.tsv')
 ck(len(runs)==8,'8 finished native scene/bucket phases')
 expected={('gtsi','pass','4','1'):(8136,1,3,40),('gtsi','pass','0','1'):(1320,1,1,1),('gtsi','pass','0','0'):(1656,1,0,0),('gtsi','bucket','0','bucket'):(0,1,0,1),('bus','pass','4','1'):(15240,1,0,90),('bus','pass','0','1'):(456,1,1,1),('bus','pass','0','0'):(1224,1,0,0),('bus','bucket','0','bucket'):(0,1,0,1)}
 ck(set((r['vehicle'],r['test'],r['variant'],r['mode']) for r in runs)==set(expected),'all expected scene cases')
 for r in runs:
  key=(r['vehicle'],r['test'],r['variant'],r['mode']);exp=expected[key]
  ck(tuple(int(r[k]) for k in ('scratch_bytes','builders','lookups','submits'))==exp,'native state and dispatch '+str(key))
  ck(all(int(r[k])==int(r['submits']) for k in ('clips','draws','actual_submits','actual_clips','actual_draws')),'every original submit intercepted exactly once '+str(key))
  ck(int(r['builders_observed'])==1,'native builder entered '+str(key))
  if r['test']=='bucket':ck(r['queue_left']=='0','original queue count reset '+str(key))
  else:ck(r['root']=='2D000000','native depth root points to scratch '+str(key))
 mats=data(run/'evidence/native_scene_materials.tsv')
 ck(len(mats)==7,'7 native material binder invocations')
 ck(sum(x['material']=='V1 MD UN.MAP' for x in mats)==4,'two per vehicle exterior and bucket material bindings')
 ck(sum(x['material']=='V1 BO DY.MAP' for x in mats)==3,'three GTSi cockpit materials')
 ck(all(x['owner']=='27000E00' for x in mats),'owner points to original body object')
 traced=data(first);events=[x['kind'] for x in traced]
 ck(events.count('NATIVE_BUCKET_FLUSH_BEGIN')==2 and events.count('NATIVE_BUCKET_FLUSH_END')==2,'original bucket drain logged')
 ck(events.count('SCENE_NATIVE_SUBMIT_ENTER')==134,'134 original polygon wrappers after native traversal and bucket drain')
 ck(events.count('SCENE_ORIGINAL_TREE_ENTRY')==8,'all eight traversal entries original')
 ck(events.count('SCENE_NATIVE_DISPATCH')==8,'all eight scene dispatcher entries original')
 ck(events.count('STUB_RASTER_CLIP_PREPARE')>=134,'stub clip callbacks clearly recorded')
 ck(events.count('STUB_RASTER_DRAW_SUBMIT')>=134,'stub draw callbacks clearly recorded')
 return {'test_count':len(checks),'passed_count':len(checks),'status':'passed','original_test_cases':8,'original_polygon_submissions':134,'remarks':'Raster handlers and pixel decoders remain stubbed. Camera, work queues and bucket indices artificially prepared. Native scene builder/traversal/queue consumption/submit wrapper executed.'}

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('run',type=Path);p.add_argument('--pe',required=True,type=Path);p.add_argument('--zfs',required=True,type=Path);p.add_argument('--gzf',required=True,type=Path);p.add_argument('--trace',required=True,type=Path);p.add_argument('--repeat',required=True,type=Path);a=p.parse_args()
 print(json.dumps(validate(a.run,a.pe,a.zfs,a.gzf,a.trace,a.repeat),indent=2))
