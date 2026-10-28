#!/usr/bin/env python3
"""Independent PE and replay evidence verification. Requires private licensed inputs."""
import argparse,csv,hashlib,json,math,struct
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--run',type=Path,required=True);p.add_argument('--exe',type=Path,required=True);p.add_argument('--gzf',type=Path,required=True);p.add_argument('--zfs',type=Path,required=True);p.add_argument('--private-traces',type=Path,required=True);a=p.parse_args();R=a.run;N=0

def check(v,s):
 global N;N+=1
 if not v:raise AssertionError(s)
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def rows(p):return list(csv.DictReader(p.open(),delimiter='\t'))
def fields(s):return dict(v.split('=',1) for v in s.split(';') if '=' in v)
def f32(x):return struct.unpack('<f',struct.pack('<f',x))[0]
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
def fl(x):return struct.unpack('<f',struct.pack('<I',int(x,16)))[0]
for path,expected in [(a.exe,'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'),(a.gzf,'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'),(a.zfs,'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d')]:check(sha(path)==expected,'private input identity')
b=a.exe.read_bytes();pe=struct.unpack_from('<I',b,60)[0];check(b[pe:pe+4]==b'PE\0\0','PE');image=struct.unpack_from('<I',b,pe+52)[0];n=struct.unpack_from('<H',b,pe+6)[0];sh=pe+24+struct.unpack_from('<H',b,pe+20)[0];ss=[struct.unpack_from('<8sIIII',b,sh+i*40) for i in range(n)]
def at(va,n):
 for _,vs,rv,size,pos in ss:
  if rv<=va-image and va-image+n<=rv+size:return b[pos+va-image-rv:pos+va-image-rv+n]
 raise AssertionError(hex(va))
for x in rows(R/'evidence/instruction_anchors.tsv'):
 bs=bytes.fromhex(x['hex']);va=int(x['va'],16);check(at(va,len(bs))==bs,'PE opcode '+x['va'])
 if bs[0]==0xe8:check(va+5+struct.unpack('<i',bs[1:5])[0]==int(x['instruction'].split('0x')[-1],16),'direct call edge')
for va,value in [(0x4f777c,1),(0x4f7784,0x463120),(0x4f7788,0x463800),(0x4f778c,0x463950)]:check(struct.unpack('<I',at(va,4))[0]==value,'original class-1 descriptor')
# Independent f32 arithmetic against original helper outputs, including exact endpoint subdivision.
t=rows(R/'evidence/subdivision.tsv');check(len(t)==16,'timer sweep rows')
for x in t:
 dt=fl(x['dt_bits']);count=min(int(dt*20)+1,20);check(int(x['count'])==count,'subdivision count');check(float(x['rate'])==20,'original interval reciprocal')
 expected=f32(dt*f32(1/count)) if x['clock_initialized']=='1' else 0.0
 check(int(x['step_bits'],16)==bits(expected),'duration bits');check(int(x['positive_returns'])==(count if expected>0 else 0),'positive durations');check(x['terminated']=='true','bounded consumption')
prov=json.loads((R/'evidence/provenance.json').read_text());events=rows(R/'evidence/replay_events.tsv')
for test,meta in prov['private_traces'].items():
 path=a.private_traces/f'final_{test}.tsv';check(sha(path)==meta['sha256'] and path.stat().st_size==meta['bytes'],'private trace identity '+test)
 raw=rows(path);filtered=[{'test':test,**{k:x[k] for k in ['kind','pc','detail']}} for x in raw if x['kind'] in {r['kind'] for r in events}]
 check(filtered==[r for r in events if r['test']==test],'source versus published events '+test)
check((a.private_traces/'final_math.tsv').read_bytes()==(a.private_traces/'final_math_repeat.tsv').read_bytes(),'identical repeat')
for test in ['legacy','math','math_repeat','gtsi_math','pop']:
 es=[r for r in events if r['test']==test];grams=[fields(r['detail']) for r in es if r['kind']=='POSE_GRAM'];vals=[fields(r['detail']) for r in es if r['kind']=='TWO_FRAME_NUMERICAL_RESULT'];cams=[r for r in es if r['kind']=='CAMERA_CALLBACK_END'];check(len(grams)==len(vals)==len(cams)==2,'two original completed simulation/camera-epilogue frames')
 for i,(g,v) in enumerate(zip(grams,vals)):
  bs=list(map(fl,g['basis'].split(',')));upper=[]
  for r in range(3):
   for c in range(r,3):upper.append(sum(bs[r*3+k]*bs[c*3+k] for k in range(3)))
  check(all(math.isclose(x,y,abs_tol=1e-10) for x,y in zip(upper,map(float,g['upper'].split(',')))),'independent Gram product')
  check(v['rootBadF32']==v['cameraBadD64']=='0','finite tested values')
  if 'math' in test:check(max(abs(x-y) for x,y in zip(upper,[1,0,0,1,0,1]))<1e-4,'near orthonormal basis')
  else:check(upper[5]<0.9,'reproduced uninitialized basis error')
 check(len([r for r in es if r['kind']=='PHYSICS_NATIVE_CALLEE' and r['pc']=='0043BDF0'])==2,'original integrator entry twice')
for frame in range(2):
 get=lambda test:next(fields(r['detail']) for r in events if r['test']==test and r['kind']=='POSE_GRAM' and fields(r['detail'])['frame']==str(frame))
 check(get('legacy')['basis']==get('pop')['basis'],'ftol pop alone does not fix basis')
contact=[r for r in events if r['test']=='contact'];calls=[r for r in contact if r['kind']=='PHYSICS_NATIVE_CALLEE' and r['pc']=='00438FD0'];check(len(calls)==1 and fl(fields(calls[0]['detail'])['dtRaw'])>0,'positive original wheel physics entry');check(any(r['kind']=='FIXEDSTEP_NATIVE' and r['pc']=='00440740' for r in contact),'original contact probe entered');check(any(r['kind']=='TERRAIN_PREREQUISITE_STOP' for r in contact),'explicit terrain prerequisite stop');check(not any(r['kind']=='TWO_FRAME_NUMERICAL_RESULT' for r in contact),'no completed contact-frame claim')
print(json.dumps({'status':'passed','test_count':N,'passed_count':N,'notes':'Original PE anchors, private identities, timer subdivision sweep, source-to-public trace comparisons, repeated math replay, basis Gram matrices, controlled ftol comparison, positive wheel-path entry and expected unloaded-terrain stop.'},indent=2))
