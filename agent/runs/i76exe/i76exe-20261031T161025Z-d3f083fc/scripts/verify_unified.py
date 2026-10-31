#!/usr/bin/env python3
"""Preliminary standalone typed ownership verifier; never imports producer/Ghidra."""
import argparse,csv,hashlib,json,pathlib,struct
p=argparse.ArgumentParser();p.add_argument('trace',type=pathlib.Path);p.add_argument('--fixtures',type=pathlib.Path);a=p.parse_args();n=0
def ck(x,msg):
 global n
 n+=1
 if not x:raise AssertionError(msg)
def words(b):return struct.unpack('<'+'I'*(len(b)//4),b)
def load(s):return pathlib.Path(str(a.trace)+s).read_bytes()
rows=list(csv.DictReader(a.trace.open(),delimiter='\t'))
for r in rows:r['d']=dict(v.split('=',1) for v in r['detail'].split(';') if '=' in v)
def events(k):return [r for r in rows if r['kind']==k]
ck(len(events('PRODUCER_COMPLETE'))==1,'complete trace');ck(len(events('EMULATOR_CREATED'))==1,'single retained emulator creation')
ck(len(events('CAMERA_RETURN'))==2,'two camera callbacks')
samples=events('SAMPLE');view=bytes.fromhex(samples[-1]['d']['camera']);ck(view==load('.view.bin'),'persistent camera')
for r in events('QUEUE_SNAPSHOT'):ck(bytes.fromhex(r['d']['camera'])==view,'unchanged camera through consumer')
summary={r['d']['phase']:r['d'] for r in events('ARENA_SUMMARY')}
base=int(summary['after']['recordBase'],16);data=load('.produced.records.bin');buckets=load('.produced.buckets.bin');members={}
for i in range(4096):
 head,tail,count=words(buckets[i*12:i*12+12]);cur=head;chain=[]
 while cur:
  ck(base<=cur<base+len(data),'record in original arena');ck(cur not in members,'unique acyclic ownership');off=cur-base;header=words(data[off:off+28]);vertices,tex,flags,kind,depth,nxt,prev=header
  ck(vertices<32 and kind<12,'typed consumer eligibility');ck((vertices>0 and off+28+24*vertices<=len(data)) or (vertices==0 and kind in (6,10)),'typed size')
  members[cur]={'header':header,'bucket':i,'count':vertices,'kind':kind,'owner':words(data[off+28:off+32])[0] if vertices==0 else None};chain.append(cur);cur=nxt;ck(len(chain)<=10000,'bounded chain')
 ck(len(chain)==count,'exact bucket count');ck((chain[-1] if chain else 0)==tail,'exact tail')
ck(len(members)==int(summary['after']['count']),'all arena memberships')
terrain={k for k,v in members.items() if v['count']};vehicle={k for k,v in members.items() if v['count']==0 and v['kind']==6}
accepted={int(r['d']['record'],16) for r in events('BIN_RETURN')};ck(terrain==accepted,'terrain insertion identity')
for r in events('CONSUME_RECORD'):
 addr=int(r['d']['record'],16);ck(addr in members,'original dispatch membership');ck(r['d']['view']=='004C2730','consumer camera identity');h=words(bytes.fromhex(''.join(int(x,16).to_bytes(4,'little').hex() for x in r['d']['words'].split(','))))
 ck(h[3]==members[addr]['kind'] and h[7]==members[addr]['owner'],'consumer typed owner');ck(tuple(h[:7])==members[addr]['header'],'original record header survives to dispatch')
seen=set()
for r in events('SUBMISSION_OWNER'):
 addr=int(r['d']['active'],16);ck(addr in members,'submission record identity');ck(r['d']['view']=='004C2730','submission camera');seen.add(addr)
ck(terrain<=seen,'all terrain reaches original submission')
ck(vehicle<={int(r['d']['record'],16) for r in events('CONSUME_RECORD')},'vehicle original dispatch')
ck(not any(load('.consumed.buckets.bin')),'original bucket clearing');ck(summary['consumed']['cursor']==summary['consumed']['recordBase'],'original cursor reset')
ck(int(summary['after']['cursor'],16)==base+len(data),'exact cursor allocation')

# Independent original-store reconstruction across both producers and the consumer.
state=bytearray(370000);initial=load('.before.observed.bin');state[:len(initial)]=initial
bank={base+i:state[i:i+4] for i in range(0,len(state),4)}
bucketbase=int(summary['after']['base'],16);initial_buckets=load('.before.buckets.bin')
bank.update({bucketbase+i:initial_buckets[i:i+4] for i in range(0,49152,4)})
started=False
for r in rows:
 if r['kind']=='QUEUE_SNAPSHOT' and r['d']['phase']=='before':started=True
 if not started:continue
 if r['kind']=='QUEUE_DWORD':
  addr=int(r['d']['address'],16)
  if addr in bank:
   ck(bytes(bank[addr]).hex()==r['d']['before'],'retired original queue-store chronology');bank[addr]=bytes.fromhex(r['d']['after'])
 if r['kind']=='QUEUE_SNAPSHOT' and r['d']['phase']=='produced':
  ck(b''.join(bytes(bank[base+i]) for i in range(0,len(data),4))==data,'original retired stores reconstruct complete produced arena')
if a.fixtures:
 geo=(a.fixtures/'xb11bdym.geo').read_bytes();native=geo[36:228]
 ck(hashlib.sha256(native).hexdigest()=='31d85d852950cc079175612da560b3aa0054ac187d1cf8a3fd435e19fff55468','retail GEO vertex identity')
 def affine(v,b):
  rot=struct.unpack_from('<9f',b);tr=struct.unpack_from('<3d',b,40)
  return [sum(v[k]*rot[k*3+j] for k in range(3))+tr[j] for j in range(3)]
 def near(x,y):
  import math
  return all(math.isclose(v,w,rel_tol=1e-6,abs_tol=1e-5) for v,w in zip(x,y))
 sources=events('GEO_SOURCE');returns=events('GEO_BUILD_RETURN')
 ck(len(sources)==len(returns)==len(vehicle),'one original target body GEO build per kind6')
 for source,ret in zip(sources,returns):
  ck(source['d']['owner']=='27006800' and source['d']['root']=='26100000','original target body ownership')
  ck(source['d']['vertices_sha256']==hashlib.sha256(native).hexdigest(),'original parsed GEO source hash')
  ck(source['d']['owner'] in source['d']['rootChildren'].split(','),'original hierarchy owns GEO')
  trans=bytes.fromhex(ret['d']['transformedVertices']);mat=bytes.fromhex(source['d']['matrix'])
  for i in range(16):ck(near(affine(affine(struct.unpack_from('<3f',native,i*12),mat),view[0x40:0x80]),struct.unpack_from('<3f',trans,i*12)),'independent retail GEO world/view transform')
  for out in events('GEO_OUTPUT'):
   if out['d']['count']=='0':continue
   verts=bytes.fromhex(out['d']['vertices'])
   for j in range(int(out['d']['count'])):ck(verts[j*24:j*24+12] in [trans[k*12:k*12+12] for k in range(16)],'GEO scratch vertex retains source identity')
# Consumer traverses exact bucket chains in descending depth order.
expected=[]
for i in reversed(range(4096)):
 cur=words(buckets[i*12:i*12+12])[0]
 while cur:
  expected.append(cur);cur=words(data[cur-base+20:cur-base+24])[0]
actual=[]
for r in rows:
 if r['kind']=='CONSUME_RECORD':actual.append(int(r['d']['record'],16))
 elif r['kind']=='SUBMISSION_OWNER':
  addr=int(r['d']['active'],16)
  if addr in terrain:
   ck(tuple(int(x,16) for x in r['d']['header'].split(','))==members[addr]['header'],'terrain header survives to submission');actual.append(addr)
ck(actual==expected,'exact original typed consumer order')
print(json.dumps({'status':'passed','checks':n,'terrain_records':len(terrain),'vehicle_records':len(vehicle),'other_records':len(members)-len(terrain)-len(vehicle)},indent=2))
