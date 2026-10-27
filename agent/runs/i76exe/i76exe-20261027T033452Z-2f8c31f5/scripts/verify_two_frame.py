#!/usr/bin/env python3
"""Validate original-retail x86 emulation evidence against separately held private inputs."""
from pathlib import Path
import csv,hashlib,struct,math,json,sys
W=Path('/mnt/data/i76_pose_v08')
RUN=(W/'run_id').read_text().strip()
R=W/'publication/agent/runs/i76exe'/RUN
EXE=Path('/mnt/data/i76_milestone_a/runtime/retail/i76.exe')
GZF=Path('/mnt/data/i76_milestone_a/runtime/archives/i76_mission_v97_verified_names.gzf')
ZFS=Path('/mnt/data/i76_milestone_b/private/I76.ZFS')
TR={k:W/'private'/f for k,f in [('bus_drive_a','bus_motion_a.tsv'),('bus_drive_b','bus_motion_b.tsv'),('gtsi_drive_a','gtsi_motion_a.tsv'),('bus_idle','bus_active.tsv')]}
N=0

def chk(v,description=''):
 global N;N+=1
 if not v:raise AssertionError(f'check {N}: {description}')

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
chk(digest(EXE)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','retail PE identity')
chk(digest(GZF)=='b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','v97 GZF identity')
chk(digest(ZFS)=='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d','retail ZFS identity')
chk(TR['bus_drive_a'].read_bytes()==TR['bus_drive_b'].read_bytes(),'identical independent bus replays')
raw=EXE.read_bytes();pe=struct.unpack_from('<I',raw,0x3c)[0];chk(raw[pe:pe+4]==b'PE\0\0','PE header');image=struct.unpack_from('<I',raw,pe+52)[0];ns=struct.unpack_from('<H',raw,pe+6)[0];sect=pe+24+struct.unpack_from('<H',raw,pe+20)[0];sections=[struct.unpack_from('<8sIIII',raw,sect+40*i) for i in range(ns)]
def at(addr,n):
 rv=addr-image
 for _,vs,rva,size,pos in sections:
  if rva<=rv and rv+n<=rva+size:return raw[pos+rv-rva:pos+rv-rva+n]
 raise AssertionError(hex(addr))
def csvrows(p):
 with p.open() as f:return list(csv.DictReader(f,delimiter='\t'))
for row in csvrows(R/'evidence/retail_opcode_anchors.tsv'):
 chk(at(int(row['va'],16),8).hex().upper()==row['hex8'],'retail original opcode '+row['va'])
for row in csvrows(R/'evidence/direct_call_edges.tsv'):
 src=int(row['site'],16);target=int(row['target'],16);bs=at(src,5)
 chk(bs[0]==0xe8,'direct call opcode');chk((src+5+struct.unpack('<i',bs[1:])[0])&0xffffffff==target,'direct call target');chk(bs.hex().upper()==row['opcode'],'call bytes')
P=json.loads((R/'evidence/replay_provenance.json').read_text())
chk(P['base_commit']=='5da264c093a9d694a7d5e36f4be62c3a26b5b0fb','pinned base')
for name,p in TR.items():chk(P['private_trace_sha256'][name]==digest(p),'private trace identity '+name)

def fields(s):return dict(x.split('=',1) for x in s.split(';') if '=' in x)

published=csvrows(R/'evidence/two_frame_scenarios.tsv');chk(len(published)==6,'6 derived scenario frames')
for scenario in ['bus_drive_a','gtsi_drive_a','bus_idle']:
 tr=csvrows(TR[scenario]);events=lambda event:[fields(r['detail']) for r in tr if r['kind']==event]
 phy=events('PHYSICS_NATIVE_CALLEE');begin=events('POSE_BEFORE_FRAME');end=events('POSE_CLASS_CALLBACK_END');cams=events('CAMERA_CALLBACK_END');mat=events('ROOT_TO_MATRIX_RESULT');vals=events('TWO_FRAME_NUMERICAL_RESULT');reg=events('NATIVE_WORLD_REGISTRATION')
 chk(len(phy)==6,'3 simulation functions x 2 frames '+scenario)
 chk(len(begin)==len(end)==len(cams)==len(mat)==2,'two complete frames '+scenario)
 chk(len(reg)==1,'native registration '+scenario)
 chk(reg[0]['owner']=='26000000' and reg[0]['entry']=='00542830','original active entry '+scenario)
 for i in range(2):
  r=next(x for x in published if x['scenario']==scenario and x['frame']==str(i))
  chk(r['matrix_bad_f32']==mat[i]['invalid']=='0','finite original camera helper '+scenario)
  chk(r['camera_steps']==cams[i]['n'],'camera step count '+scenario)
  chk(r['camera_bytes_changed']==cams[i]['cameraChangedBytes'],'camera changed byte count '+scenario)
  chk(cams[i]['eligible']=='true' and cams[i]['guardReached']=='true','selected camera reaches guard '+scenario)
  chk(int(cams[i]['cameraChangedBytes'])>0,'callback updated persistent camera '+scenario)
  chk(len(phy[i*3:i*3+3])==3 and all(x['return']!='' for x in phy[i*3:i*3+3]),'original 3 physics services entered')
  if scenario!='bus_idle':
   chk(len(vals)==2,'measured moving frames '+scenario)
   d=vals[i]
   for col,k in [('root_z','rootPositionXYZ'),('axis_norm_squared','axisNormSq'),('root_bad_f32','rootBadF32'),('root_z_changed','rootZChanged'),('camera_bad_d64','cameraBadD64'),('camera_six_doubles','cameraDoubles')]:
    expect=d[k].split(',')[-1] if k=='rootPositionXYZ' else d[k]
    chk(r[col]==expect,'source-to-derived '+scenario+col)
   chk(r['root_z_changed']=='true','vehicle translated on frame '+str(i))
   chk(r['root_bad_f32']==r['camera_bad_d64']=='0','finite original pose/camera')
   axis=float(r['axis_norm_squared']);chk(math.isfinite(axis) and axis>0,'nondegenerate axis')
   chk(abs(axis-1)>0.1,'explicitly nonunit axis caveat')
   nums=list(map(float,r['camera_six_doubles'].split(',')));chk(len(nums)==6 and all(map(math.isfinite,nums)),'six finite original camera doubles')
   if i==1:
    prev=next(x for x in published if x['scenario']==scenario and x['frame']=='0')
    chk(float(r['root_z'])>float(prev['root_z'])>0,'two successive world position advances')
    chk(r['camera_six_doubles']!=prev['camera_six_doubles'],'successive view update not constant')
  else:
   chk(len(vals)==0,'stationary control does not make moving claims')
print(f'PASSED {N}/{N} independent assertions')
