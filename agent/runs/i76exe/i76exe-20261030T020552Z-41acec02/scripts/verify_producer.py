#!/usr/bin/env python3
"""Independent retail PE, fixture, numeric, event and bucket checks; no Ghidra imports."""
import argparse,hashlib,json,math,struct,sys,importlib.util
from pathlib import Path
p=argparse.ArgumentParser()
for n in ['run','private','exe','gzf','zfs','source-repo']:p.add_argument('--'+n,type=Path,required=True)
p.add_argument('--emit',action='store_true');a=p.parse_args();count=0
sys.dont_write_bytecode=True
def check(x,msg):
 global count
 count+=1
 if not x:raise AssertionError(msg)
def sha(b):return hashlib.sha256(b).hexdigest()
def f(v):return struct.unpack('<f',struct.pack('<I',int(v,16) if isinstance(v,str) else v))[0]
def d(words,i):return struct.unpack('<d',struct.pack('<II',int(words[i],16),int(words[i+1],16)))[0]
expected={'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'}
identities={}
for k,v in expected.items():
 b=getattr(a,k).read_bytes();check(sha(b)==v,'private '+k);identities[k]=dict(sha256=sha(b),md5=hashlib.md5(b).hexdigest(),bytes=len(b))
b=a.exe.read_bytes();h=struct.unpack_from('<I',b,60)[0];opt=h+24;base=struct.unpack_from('<I',b,opt+28)[0];sec=opt+struct.unpack_from('<H',b,h+20)[0]
def pe(va,n):
 for i in range(struct.unpack_from('<H',b,h+6)[0]):
  vs,r,sz,o=struct.unpack_from('<IIII',b,sec+40*i+8)
  if r<=va-base<r+max(vs,sz):return b[o+va-base-r:o+va-base-r+n]
 raise ValueError(hex(va))
anchors={0x457ff0:'558bec83e4f8',0x458007:'e8c4fe0100',0x458086:'8b01',0x458296:'e875a90100',0x45829b:'8bf0',0x4582a2:'0f8f94000000',0x458677:'c7400c06000000',0x458688:'89581c',0x458690:'897040',0x4586bf:'e84c770300',0x4901a2:'891e',0x4901af:'894804',0x4903e7:'894e08',0x490590:'a1c0436500',0x49059a:'c7401400000000',0x4905a6:'c70000000000',0x48f9ba:'e8818f0000',0x48fa77:'890e',0x48fe10:'83ec14d9442418',0x4facf8:'28000000',0x4bdfbc:'cdcc8c3f',0x4be5f0:'cdcc8c3f'}
for va,v in anchors.items():check(pe(va,len(bytes.fromhex(v))).hex()==v,'original opcode '+hex(va))
# Independently re-extract fixtures using the pinned accepted archive reader.
old=a.source_repo/'agent/runs/i76exe/i76exe-20261022T232710Z-96c58505'
spec=importlib.util.spec_from_file_location('retail_reader',old/'scripts/extract_private_fixtures.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
z=a.zfs.read_bytes();rd=m.Reader(z);records={r['name'].lower():r for r in m.read_records(z)}
meta=json.loads((old/'evidence/retail_resource_digests.json').read_text());fixtures={}
for path in sorted((a.private/'fixtures').iterdir()):
 raw=path.read_bytes();name=path.name
 if name in records:check(raw==rd.extract(records[name]),'archive source '+name)
 else:
  known=meta['geo'].get(name,meta['tmt'].get(name));check(known is not None and sha(raw)==known['sha256'],'packed GEO/TMT '+name)
 fixtures[name]=dict(bytes=len(raw),sha256=sha(raw))
check(len(fixtures)==64,'complete stock fixture subset')
def rows(case):
 out=[]
 for i,line in enumerate((a.private/(case+'.tsv')).read_text().splitlines()[1:],2):
  scenario,kind,pc,detail=line.split('\t',3);fields={}
  for kv in detail.split(';'):
   if '=' in kv:k,v=kv.split('=',1);fields[k]=v
  out.append(dict(line=i,kind=kind,pc=pc,detail=detail,fields=fields))
 return out
def sel(rs,k):return [r for r in rs if r['kind']==k]
def fields(rs,k):return sel(rs,k)[0]['fields']
def words(x):return x['words'].split(',')
summaries={};events=[]
safe={'CONTROLLED_POSE','NATIVE_ROOT_CTOR','NATIVE_SPAWN_STATUS','WORLD_REGISTERED','WORLD_AFTER','VIEW_RECORD','ARENA_GLOBALS','ARENA_SUMMARY','WORLD_VISIT','CULL_INPUT','CULL_RESULT','RECORD_PREPARE','KIND6_WRITE','ORIGINAL_WRITE_RETIRED','INSERT_ENTER','INSERT_RETURN','BUCKET','PRODUCER_COMPLETE','ORIGINAL_LIGHT_CONTEXT','ARENA_ALLOC'}
for case in ['visible','repeat','behind','empty']:
 rs=rows(case);log=(a.private/(case+'.log')).read_text();events.extend(dict(case=case,**r) for r in rs if r['kind'] in safe)
 check('ERROR' not in log,'headless clean '+case);check(len(sel(rs,'PRODUCER_COMPLETE'))==1,'original completed '+case)
 ret=[r for r in sel(rs,'RETURN') if r['pc']=='00457FF0'];check(len(ret)==1,'sentinel return '+case)
 warnings=[l.strip() for l in log.splitlines() if 'Uninitialized' in l]
 check(len(warnings)==(0 if case=='empty' else 1) and all('004461e0' in l and '00000000:1' in l for l in warnings),'only inherited optional geometry warning '+case)
 before,after=[r['fields'] for r in sel(rs,'ARENA_SUMMARY')];check(before['count']=='0' and before['heads']=='0','original zero buckets '+case)
 check(before['base']==after['base'],'same original arena '+case)
 check([int(x['fields']['size']) for x in sel(rs,'ARENA_ALLOC')][-5:]==[370000,128000,49152,49152,2880],'original arena requests '+case)
 v=words(fields(rs,'VIEW_RECORD'));vf=[f(x) for x in v];check(all(math.isfinite(x) for x in vf),'finite view words '+case)
 check(v[16:25]==['3F800000','00000000','00000000','00000000','3F800000','00000000','00000000','00000000','3F800000'],'original view identity basis '+case)
 ins=sel(rs,'INSERT_ENTER');rets=sel(rs,'INSERT_RETURN');numeric={}
 if case=='empty':
  check(not sel(rs,'WORLD_VISIT') and not ins and not sel(rs,'WORLD_REGISTERED'),'empty has no objects/insertions')
  check(after['count']=='0' and after['cursor']==before['cursor'],'empty original arena unchanged')
 else:
  root=fields(rs,'NATIVE_ROOT_CTOR');check(root['dir']=='00000000,00000000,3F800000','original constructor axis')
  wr=fields(rs,'WORLD_REGISTERED');ww=words(wr);check(wr['entry']=='00542830' and ww[0]=='26000000' and wr['class']=='1' and wr['count']=='1','native class1 world entry')
  check(words(fields(rs,'WORLD_AFTER'))==ww,'registry unchanged through producer')
  check(fields(rs,'WORLD_VISIT')['entry']==wr['entry'],'producer uses active world entry')
  check(fields(rs,'NATIVE_SPAWN_STATUS')['status']=='00020000','original unselected spawn policy')
  point=[f(x) for x in fields(rs,'CULL_INPUT')['point'].split(',')];radius=f(fields(rs,'CULL_INPUT')['radius']);zpos=float(fields(rs,'CONTROLLED_POSE')['z'])
  center=[f(x) for x in ww[1:4]];world=[center[0],center[1],center[2]+zpos]
  predicted=[sum(vf[16+axis+3*j]*world[j] for j in range(3))+d(v,26+axis*2) for axis in range(3)]
  check(all(math.isclose(x,y,abs_tol=1e-5) for x,y in zip(point,predicted)),'independent root/view transform '+case)
  check(math.isclose(radius,struct.unpack('<f',pe(0x4bdfbc,4))[0]*f(ww[4]),rel_tol=1e-6),'original expanded sphere radius '+case)
  distances=[vf[0xf8//4]*point[2]+vf[0xfc//4],vf[0xe8//4]*point[2]+vf[0xec//4]]+[sum(vf[(off//4)+j]*point[j] for j in range(3)) for off in [0xa0,0xb0,0xc0,0xd0]]
  rejected=any(x+radius<0 for x in distances[:2]) or any(x+radius*struct.unpack('<f',pe(0x4be5f0,4))[0]<0 for x in distances[2:])
  check(rejected==(case=='behind'),'independent frustum halfspaces '+case)
  check(fields(rs,'CULL_RESULT')['eax']==('00000001' if rejected else '00000000'),'original classifier agrees '+case)
  numeric=dict(world_center=world,view_point=point,radius=radius,plane_distances=distances,rejected=rejected)
  if case=='behind':
   check(not ins and not sel(rs,'KIND6_WRITE'),'culled no record creation')
   check(after['count']=='0' and after['cursor']==before['cursor'],'culled arena unchanged')
  else:
   check(len(ins)==len(rets)==2,'kind6 and separate kind10 insertions')
   w=words(ins[0]['fields']);rw=words(rets[0]['fields']);record=ins[0]['fields']['record'];bucket=rets[0]['fields']['bucket'];bucket_index=(int(bucket,16)-int(before['base'],16))//12
   check(ins[0]['fields']['return']=='004586C4' and w[3]=='00000006','original producer callsite and kind6')
   check(w[7]==ww[0] and w[16]==wr['entry'],'same source owner/entry')
   check(w[11]==ww[4] and w[14]=='00000000','original radius and pass selector')
   check([f(x) for x in w[8:11]]==point,'record holds classified point')
   depth=f(ins[0]['fields']['depth']);check(math.isclose(depth,point[2]-f(ww[4]),abs_tol=4e-6),'original depth minus radius')
   check(bucket_index==round(depth) and bucket_index==48,'independent bucket rounding from original zero near')
   check(rets[0]['fields']['bucketWords']==record+','+record+',00000001','native first insertion head tail count')
   check(int(rets[0]['fields']['cursor'],16)-int(record,16)==int.from_bytes(pe(0x4facf8,4),'little')+0x1c==0x44,'original kind6 size table cursor advance')
   for pc,addr,value in [('00458677',int(record,16)+12,'00000006'),('00458688',int(record,16)+28,ww[0]),('00458690',int(record,16)+64,wr['entry']),('004901A2',int(bucket,16),record),('004901AF',int(bucket,16)+4,record),('004903E7',int(bucket,16)+8,'00000001')]:
    check(any(r['pc']==pc and r['fields']['address']==f'{addr:08X}' and r['fields']['value']==value for r in sel(rs,'ORIGINAL_WRITE_RETIRED')),'retired original store '+pc+' '+case)
   check(after['count']=='2' and after['heads']=='1','one original bucket two kinds')
   check(words(ins[1]['fields'])[3]=='0000000A','distinct headlight kind')
   numeric.update(record=record,bucket=bucket,bucket_index=bucket_index,depth=depth)
 summaries[case]=dict(trace_sha256=sha((a.private/(case+'.tsv')).read_bytes()),producer_steps=int(ret[0]['fields']['steps']),insertions=len(ins),warnings=warnings,numeric=numeric)
check((a.private/'visible.tsv').read_bytes()==(a.private/'repeat.tsv').read_bytes(),'byte-identical fresh-process repeat')
# Guard against accidentally publishing a producer that substitutes services or writes nodes.
s=(a.run/'scripts/I76_VisibilityProducerProbe.java').read_text()
check('if(producing)throw new IllegalStateException("harness write during producer")' in s,'harness scalar write guard')
check('if(producing)throw new IllegalStateException("service reached during original producer")' in s,'producer service rejection')
outputs={'results.json':json.dumps(dict(identities=identities,fixtures=fixtures,anchors={f'{k:08X}':v for k,v in anchors.items()},cases=summaries),indent=2)+'\n','producer_events.json':json.dumps(events,indent=2)+'\n'}
for name,value in outputs.items():
 path=a.run/'evidence'/name
 if a.emit:path.write_text(value)
 else:check(path.read_text()==value,'exact public derived evidence '+name)
print(json.dumps(dict(status='passed',test_count=count,passed_count=count)))
