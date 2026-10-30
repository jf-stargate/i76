#!/usr/bin/env python3
"""Standalone byte, ownership, chronology and numerical verifier; no emulator imports.
--run alone checks public evidence; add all private arguments for source verification.
--emit deliberately regenerates reviewed derived artifacts in a new unaccepted run.
"""
import argparse,csv,hashlib,importlib.util,json,math,struct,sys
from pathlib import Path
sys.dont_write_bytecode=True
N=0
def check(x,msg):
 global N
 N+=1
 if not x:raise AssertionError(msg)
def sha(b):return hashlib.sha256(b).hexdigest()
def fields(r):return dict(v.split('=',1) for v in r['detail'].split(';') if '=' in v)
def unpack(b,fmt,off=0):return struct.unpack_from('<'+fmt,b,off)
def matrix(b):return unpack(b,'9f'),unpack(b,'3d',40)
def affine(v,b):
 r,t=matrix(b);return [sum(v[k]*r[k*3+j] for k in range(3))+t[j] for j in range(3)]
def near(x,y,tol=1e-5):return len(x)==len(y) and all(math.isclose(a,b,abs_tol=tol,rel_tol=1e-6) for a,b in zip(x,y))
def pe_slice(b,va,n):
 at=unpack(b,'I',60)[0];cnt=unpack(b,'H',at+6)[0];size=unpack(b,'H',at+20)[0];base=unpack(b,'I',at+52)[0]
 for i in range(cnt):
  vs,r,sz,o=unpack(b,'4I',at+24+size+40*i+8)
  if r<=va-base<r+max(vs,sz):return b[o+va-base-r:o+va-base-r+n]
 raise ValueError(hex(va))
SAFE={'NATIVE_ROOT_CTOR','NATIVE_SPAWN_STATUS','WORLD_REGISTERED','TARGET_REGISTERED','WORLD_AFTER','CONTROLLED_POSE','CONTROLLED_TARGET_POSE','SAMPLE','CAMERA_ENTER','CAMERA_RETURN','CAMERA_SOURCE','NATIVE_CHANGED_DWORD','CALL_EVENT','ROOT_READ_ANCHOR','VIEW_RECORD','ARENA_GLOBALS','ARENA_SUMMARY','BUCKET','QUEUE_SEALED','QUEUE_DWORD','QUEUE_SNAPSHOT','HOST_WRITE_GUARD','WORLD_VISIT','CULL_INPUT','CULL_RESULT','KIND6_WRITE','RECORD_PREPARE','ORIGINAL_WRITE_RETIRED','INSERT_ENTER','INSERT_RETURN','CONSUME_RECORD','GEO_TRAVERSAL','GEO_BUILD','GEO_SOURCE','GEO_SECTION','GEO_OUTPUT','GEO_BUILD_RETURN','MATERIAL_LOOKUP','POLYGON_WRAPPER','SERVICE_CLIP','SERVICE_DRAW','SERVICE_TEXTURE','SERVICE_STRICMP','SERVICE_MEMCPY','PRODUCER_CRT_RETURN','PREBIND_CAMERA_LIGHT','SUPPLIED_RENDER_SCRATCH','PRODUCER_COMPLETE','ARENA_ALLOC'}
CASES=['visible','repeat','behind','empty','camera_only']
def collect(work):
 rows=[]
 for case in CASES:
  for line,r in enumerate(csv.DictReader((work/(case+'.tsv')).open(),delimiter='\t'),2):
   if r['kind'] in {'SERVICE_STRICMP','SERVICE_MEMCPY'} and 'producer=true' not in r['detail']:continue
   if r['kind'] in SAFE or r['kind']=='RETURN' and r['pc'] in {'00493C50','004572B0','0048F9B0','00457FF0','0048FAC0'}:rows.append(dict(case=case,line=line,**r))
 return rows

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--run',type=Path,required=True)
 for k in ['private','source-repo','exe','zfs','gzf']:ap.add_argument('--'+k,type=Path)
 ap.add_argument('--emit',action='store_true');a=ap.parse_args();ev=a.run/'evidence'
 if a.emit:
  check(a.private is not None,'emit requires private source');rows=collect(a.private);(ev/'events.json').write_text(json.dumps(rows,indent=2)+'\n')
 else:rows=json.loads((ev/'events.json').read_text())
 if a.private:check(rows==collect(a.private),'exact private-to-public allowlist')
 summaries={}
 for case in CASES:
  rr=[r for r in rows if r['case']==case]
  def get(k):return [r for r in rr if r['kind']==k]
  def one(k):
   ar=get(k);check(len(ar)==1,case+' one '+k);return fields(ar[0])
  def returns(pc):return [r for r in get('RETURN') if r['pc']==pc]
  check(len(returns('00493C50'))==1,case+' original math startup')
  check(len(returns('0048F9B0'))==len(returns('00457FF0'))==len(returns('0048FAC0'))==1,case+' original arena/producer/consumer return')
  check(len(get('PRODUCER_COMPLETE'))==1,case+' full completion marker')
  guard=one('HOST_WRITE_GUARD');check(guard['violations']=='0',case+' no host queue/view writes')
  before,produced,consumed=[fields(r) for r in get('ARENA_SUMMARY')]
  check([before['phase'],produced['phase'],consumed['phase']]==['before','after','consumed'],case+' lifecycle')
  check(before['base']==produced['base']==consumed['base'],case+' same original bucket table')
  check(before['cursor']==before['recordBase']==consumed['cursor'],case+' original cursor reset')
  check(before['count']==before['heads']==consumed['count']==consumed['heads']=='0',case+' empty start and drained end')
  check([int(fields(r)['size']) for r in get('ARENA_ALLOC')][-5:]==[370000,128000,49152,49152,2880],case+' original arena requests')
  original_view=bytes.fromhex(''.join(int(x,16).to_bytes(4,'little').hex() for x in one('VIEW_RECORD')['words'].split(',')))
  check(len(original_view)==472,case+' full persistent camera record')
  if case!='empty':
   check(len(get('CAMERA_RETURN'))==2 and all(r['pc']=='70000000' for r in get('CAMERA_RETURN')),case+' two completed camera callbacks')
   samples={(int(fields(r)['frame']),fields(r)['phase']):fields(r) for r in get('SAMPLE')}
   check(samples[1,'before']['camera']==samples[0,'after']['camera'] and samples[1,'before']['smooth']==samples[0,'after']['smooth'],case+' preserved camera and smoothing')
   for f in (0,1):
    bef=samples[f,'before'];aft=samples[f,'after'];state={0x4c2730+i:bytes.fromhex(bef['camera'])[i:i+4] for i in range(0,472,4)}
    sb=bytes.fromhex(bef['smooth']);state.update({0x4c2964+i:sb[i:i+4] for i in range(0,24,4)});state.update({0x52b93c+i:sb[24+i:28+i] for i in range(0,12,4)})
    for r in get('NATIVE_CHANGED_DWORD'):
     d=fields(r)
     if int(d['frame'])!=f:continue
     addr=int(d['address'],16);check(state[addr].hex()==d['before'],case+' native camera write chronology');state[addr]=bytes.fromhex(d['after'])
    check(b''.join(state[0x4c2730+i] for i in range(0,472,4)).hex()==aft['camera'],case+' original writes reconstruct entire camera')
    b=bytes.fromhex(aft['camera']);src=bytes.fromhex(fields(get('CAMERA_SOURCE')[f])['bytes']);rot,pos=matrix(src);inv,trans=matrix(b[0x40:0x80]);check(near(inv,[rot[j*3+i] for i in range(3) for j in range(3)],0),case+' inverse transpose')
    check(near(trans,[-sum(pos[k]*rot[j*3+k] for k in range(3)) for j in range(3)],1e-12),case+' inverse translation')
    check(near(unpack(b,'3d',0x160),pos,0),case+' exact source camera origin')
    check(all(math.isfinite(v) for v in unpack(b,'6d',0x160)),case+' finite original view')
   check(bytes.fromhex(samples[1,'after']['camera'])==original_view,case+' callback view used unchanged for producer')
   check(samples[0,'after']['camera']!=samples[1,'after']['camera'],case+' native smoothing evolves')
   camreg=one('WORLD_REGISTERED');check(camreg['entry']=='00542830' and camreg['root']=='26000000',case+' selected camera registry ownership')
  else:check(not get('CAMERA_RETURN') and not get('WORLD_VISIT'),case+' empty world no invented camera or objects')
  snaps={fields(r)['phase']:fields(r) for r in get('QUEUE_SNAPSHOT')}
  check(all(bytes.fromhex(v['camera'])==original_view for v in snaps.values()),case+' one unmodified camera through drain')
  base=int(before['recordBase'],16);state={base+i:b'\0'*4 for i in range(0,512,4)};bucket_state={}
  for r in rr:
   if r['kind']=='QUEUE_DWORD':
    d=fields(r);addr=int(d['address'],16);bank=state if base<=addr<base+512 else bucket_state
    if addr not in bank:bank[addr]=bytes.fromhex(d['before'])
    check(bank[addr].hex()==d['before'],case+' original queue store chronology '+r['pc']);bank[addr]=bytes.fromhex(d['after'])
   if r['kind']=='QUEUE_SNAPSHOT':
    check(b''.join(state[base+i] for i in range(0,184,4)).hex()==fields(r)['bytes'],case+' original stores reconstruct record bytes')
  attempts=get('INSERT_ENTER');insert=[r for r in get('INSERT_RETURN') if int(fields(r)['cursor'],16)>int(fields(r)['record'],16)];dispatch=get('CONSUME_RECORD');positive=case in ('visible','repeat')
  if case not in ('empty','camera_only'):
   check([fields(r)['status'] for r in get('NATIVE_SPAWN_STATUS')]==['00010010','00020000'],case+' original selected and unselected spawn policy');check(len(get('NATIVE_ROOT_CTOR'))==2,case+' two original constructed stock roots');target=one('TARGET_REGISTERED');check(target['entry']=='005428A8' and target['root']=='26100000' and target['count']=='2',case+' separate unselected target registry')
   pose=bytes.fromhex(one('CONTROLLED_TARGET_POSE')['root']);v=unpack(original_view,'9f',0x40)
   bound=target['words'].split(',');center=[struct.unpack('<f',int(x,16).to_bytes(4,'little'))[0] for x in bound[1:4]]
   pred=affine(affine(center,pose),original_view[0x40:0x80]);point=fields(get('CULL_INPUT')[0]);actual=[struct.unpack('<f',int(x,16).to_bytes(4,'little'))[0] for x in point['point'].split(',')]
   check(near(pred,actual),case+' independent registered-sphere world/view transform')
   check(one('CULL_RESULT')['eax']==('00000000' if positive else '00000001'),case+' target visible/culled original classification')
   rad=struct.unpack('<f',int(point['radius'],16).to_bytes(4,'little'))[0];vf=unpack(original_view,'118f')
   distances=[vf[62]*actual[2]+vf[63],vf[58]*actual[2]+vf[59]]+[sum(vf[off//4+j]*actual[j] for j in range(3)) for off in (0xa0,0xb0,0xc0,0xd0)]
   rejected=any(x+rad<0 for x in distances[:2]) or any(x+rad*1.100000023841858<0 for x in distances[2:]);check(rejected!=positive,case+' independent frustum halfspaces')
  if positive:
   check(len(attempts)==3,case+' selected kind10 attempt plus accepted pair');check(fields(attempts[0])['depth']=='C0A00000',case+' camera-owner kind10 negative depth -5');check(len(insert)==len(dispatch)==2,case+' exactly kind6 and kind10 produced/consumed')
   produced_bytes=bytes.fromhex(snaps['produced']['bytes']);w=unpack(produced_bytes,'17I');k10=unpack(produced_bytes,'29I',68)
   check(w[3]==6 and w[7]==0x26100000 and w[16]==0x5428a8 and w[14]==0,case+' native kind6 owner/entry/secondary selector')
   check(w[5]==base+68 and k10[3]==10 and k10[7]==0x27006600,case+' original linked kind10 and distinct owner')
   for r,expected in zip(dispatch,(base,base+68)):
    d=fields(r);check(int(d['record'],16)==expected and d['view']=='004C2730',case+' exact same record/view dispatch')
   ret=fields(insert[0]);bucket=int(ret['bucket'],16);ix=(bucket-int(before['base'],16))//12
   depth=struct.unpack('<f',w[4].to_bytes(4,'little'))[0];check(ix==round(depth),case+' independently derived depth bucket')
   check(fields(dispatch[0])['words'].split(',')[7]=='26100000',case+' unchanged kind6 dispatch owner')
   check(one('GEO_TRAVERSAL')['record']==f'{base+28:08X}',case+' dispatch passes original record substructure')
   src=one('GEO_SOURCE');check(src['root']=='26100000' and src['owner'] in src['rootChildren'].split(','),case+' native geometry child belongs to target root')
   check(src['vertices_sha256']=='31d85d852950cc079175612da560b3aa0054ac187d1cf8a3fd435e19fff55468',case+' native GEO vertices source identity')
   outs=[fields(r) for r in get('GEO_OUTPUT') if fields(r)['count']!='0'];check(len(outs)==2 and all(x['count']=='4' and x['owner']==src['owner'] for x in outs),case+' two genuine kind6 geometry quads')
   polys=[fields(r) for r in get('POLYGON_WRAPPER')];check([p['kind'] for p in polys]==['6','6','10'] and [p['count'] for p in polys]==['4','4','8'],case+' separate kind6 and kind10 wrapper paths')
   check(sorted(out['vertices'] for out in outs)==sorted(poly['vertices'] for poly in polys if poly['kind']=='6'),case+' original GEO output reaches wrapper unchanged in native tree order')
   check(len(get('SERVICE_CLIP'))==len(get('SERVICE_DRAW'))==3,case+' every wrapper reaches explicitly substituted clip/draw')
   cleared={r['pc'] for r in get('QUEUE_DWORD') if int(fields(r)['address'],16) in (bucket,bucket+4,bucket+8) and fields(r)['after']=='00000000'}
   check({'0048FCFE','0048FD07','0048FD10'}<=cleared,case+' original bucket count/tail/head clearing PCs')
   z=[r for r in get('QUEUE_DWORD') if int(fields(r)['address'],16)==base+68+60 and r['pc']=='0048FCCD'];check(len(z)==1 and fields(z[0])['after']=='00000000',case+' explicit original kind10 +3c clear')
   summaries[case]=dict(record=f'{base:08X}',owner='26100000',entry='005428A8',bucket=ix,kind10_record=f'{base+68:08X}',geometry=src['geometry'],geometry_owner=src['owner'],quad_count=2,kind10_polygon_count=1)
  else:
   check(not insert and not dispatch and not get('GEO_BUILD') and not get('POLYGON_WRAPPER'),case+' no generated or consumed geometry work')
   check(produced['count']=='0' and produced['cursor']==before['cursor'],case+' rejected/empty arena unchanged')
   summaries[case]=dict(records=0,rejected_kind10_attempts=len(attempts))
 # Compare complete independently produced evidence, including original writes and services.
 check([dict(r,case='visible') for r in rows if r['case']=='repeat']==[r for r in rows if r['case']=='visible'],'independent repeat public trace exactly identical')
 if a.private:
  check((a.private/'visible.tsv').read_bytes()==(a.private/'repeat.tsv').read_bytes(),'fresh-project full private trace byte identity')
  for case in CASES:
   log=(a.private/(case+'.log')).read_text();check('ERROR' not in log,case+' clean headless result')
   warnings=[l for l in log.splitlines() if 'Uninitialized' in l];check(len(warnings)==(0 if case=='empty' else 1) and all('004461e0' in l for l in warnings),case+' only inherited optional-name warning')
  for key,digest in {'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'}.items():check(sha(getattr(a,key).read_bytes())==digest,'private '+key+' identity')
  old=a.source_repo/'agent/runs/i76exe/i76exe-20261022T232710Z-96c58505';spec=importlib.util.spec_from_file_location('retail',old/'scripts/extract_private_fixtures.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
  z=a.zfs.read_bytes();reader=m.Reader(z);records={r['name'].lower():r for r in m.read_records(z)};meta=json.loads((old/'evidence/retail_resource_digests.json').read_text());fixtures=[]
  for p in sorted((a.private/'fixtures').iterdir()):
   b=p.read_bytes();known=meta['geo'].get(p.name,meta['tmt'].get(p.name))
   check(b==reader.extract(records[p.name]) if p.name in records else known is not None and sha(b)==known['sha256'],'independent source resource '+p.name);fixtures.append(dict(name=p.name,sha256=sha(b),bytes=len(b)))
  check(len(fixtures)==65,'complete 64 inherited fixtures plus native camera headlight variant')
  geo=(a.private/'fixtures/xb11bdym.geo').read_bytes();native=bytes.fromhex(''.join(f'{x:02x}' for x in geo[36:36+192]));check(sha(native)=='31d85d852950cc079175612da560b3aa0054ac187d1cf8a3fd435e19fff55468','original parsed vertices match GEO source +0x24')
  rr=[r for r in rows if r['case']=='visible'];src=fields(next(r for r in rr if r['kind']=='GEO_SOURCE'));cam=bytes.fromhex(fields(next(r for r in rr if r['kind']=='QUEUE_SNAPSHOT'))['camera']);trans=bytes.fromhex(fields(next(r for r in rr if r['kind']=='GEO_BUILD_RETURN'))['transformedVertices']);mat=bytes.fromhex(src['matrix'])
  for i in range(16):check(near(affine(affine(unpack(native,'3f',12*i),mat),cam[0x40:0x80]),unpack(trans,'3f',12*i)),f'independent source vertex {i} through native matrices')
  for r in rr:
   if r['kind']=='GEO_OUTPUT' and fields(r)['count']!='0':
    verts=bytes.fromhex(fields(r)['vertices'])
    for i in range(int(fields(r)['count'])):check(verts[i*24:i*24+12] in [trans[j*12:j*12+12] for j in range(16)],'quad position is actual transformed retail vertex')
  # Sparse opcode assertions come from read-only annotated instruction listing, checked against independent PE bytes.
  audit={}
  for line in (a.private/'source_audit.txt').read_text().splitlines():
   cols=line.split('\t')
   if len(cols)==3 and len(cols[0])==8:
    try:audit[int(cols[0],16)]=cols[1]
    except ValueError:pass
  needed={int(r['pc'],16) for r in rows if r['kind'] in {'QUEUE_DWORD','NATIVE_CHANGED_DWORD','CALL_EVENT','ROOT_READ_ANCHOR','KIND6_WRITE','CONSUME_RECORD','GEO_TRAVERSAL','GEO_BUILD','POLYGON_WRAPPER','GEO_BUILD_RETURN','CULL_RESULT','WORLD_VISIT'}}
  anchors=[];pe=a.exe.read_bytes()
  for va in sorted(needed):
   check(va in audit,'audited original PC '+hex(va));raw=bytes.fromhex(audit[va]);check(pe_slice(pe,va,len(raw))==raw,'retail PE instruction '+hex(va));anchors.append(dict(va=f'{va:08X}',hex=raw.hex()))
  # Also validate kind dispatch targets and record-size table from original PE data.
  check(unpack(pe_slice(pe,0x4facc0,4),'I')[0]==0x48f4c0,'original kind6 dispatch table');check(unpack(pe_slice(pe,0x4facd0,4),'I')[0]==0x490640,'original kind10 dispatch table')
  provenance=dict(inputs={k:dict(sha256=sha(getattr(a,k).read_bytes()),bytes=getattr(a,k).stat().st_size) for k in ('exe','gzf','zfs')},fixtures=fixtures,private_traces={c:dict(sha256=sha((a.private/(c+'.tsv')).read_bytes()),bytes=(a.private/(c+'.tsv')).stat().st_size) for c in CASES},probe_sha256=sha((a.run/'scripts/I76_IntegratedRenderProbe.java').read_bytes()),anchors=anchors)
  data=json.dumps(provenance,indent=2)+'\n'
  if a.emit:(ev/'provenance.json').write_text(data)
  check((ev/'provenance.json').read_text()==data,'exact regenerated provenance')
 else:
  prov=json.loads((ev/'provenance.json').read_text());check(sha((a.run/'scripts/I76_IntegratedRenderProbe.java').read_bytes())==prov['probe_sha256'],'measured probe hash')
 data=json.dumps(summaries,indent=2)+'\n'
 if a.emit:(ev/'summary.json').write_text(data)
 check((ev/'summary.json').read_text()==data,'independently derived summary')
 print(json.dumps(dict(status='passed',assertions=N,source_verification=bool(a.private),cases=5)))
if __name__=='__main__':main()
