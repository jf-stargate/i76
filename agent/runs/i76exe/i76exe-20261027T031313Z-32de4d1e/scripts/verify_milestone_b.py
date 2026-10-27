#!/usr/bin/env python3
"""Check native root/active-registry/camera differential against private retail fixtures.

Public run stores derived records and original-code script, not full private traces.
This independent verifier requires the user-provided retail PE/GZF/ZFS and locally generated original-instruction traces.
"""
import argparse,csv,hashlib,struct,math,json
from pathlib import Path

def digest(p,algorithm='sha256'):
 h=hashlib.new(algorithm)
 with Path(p).open('rb') as f:
  for chunk in iter(lambda:f.read(2**20),b''):h.update(chunk)
 return h.hexdigest()

def entries(p):
 with Path(p).open(newline='') as f:return list(csv.DictReader(f,delimiter='\t'))

def fields(s):
 out={}
 for v in s.split(';'):
  if '=' in v:k,val=v.split('=',1);out[k]=val
 return out

def from_events(e,kind):return [x for x in e if x.get('kind')==kind]

def main():
 ap=argparse.ArgumentParser()
 for x in ['exe','gzf','zfs','bus-native','bus-native-repeat','gtsi-native','bus-zero','bus-unselected','run-dir']:ap.add_argument('--'+x,required=True,type=Path)
 a=ap.parse_args();checks=0
 def check(msg,condition):
  nonlocal checks
  if not condition:raise AssertionError(f'FAILED {checks+1}: {msg}')
  checks+=1
 sha={'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'}
 for item,h in sha.items():check('input SHA '+item,digest(getattr(a,item))==h)
 check('input MD5',digest(a.exe,'md5')=='a640ea0097dbb62e0c77b7f2847c7161')
 check('independent same-input native replay',a.bus_native.read_bytes()==a.bus_native_repeat.read_bytes())
 raw=a.exe.read_bytes();pe=struct.unpack_from('<I',raw,0x3c)[0];check('PE signature',raw[pe:pe+4]==b'PE\0\0')
 img=struct.unpack_from('<I',raw,pe+24+28)[0];opt=pe+24;sc=struct.unpack_from('<H',raw,pe+6)[0];st=opt+struct.unpack_from('<H',raw,pe+20)[0]
 sect=[struct.unpack_from('<8sIIII',raw,st+i*40) for i in range(sc)]
 def pebytes(va,n):
  rva=va-img
  for _,unused,start,size,rawstart in sect:
   if start<=rva and rva+n<=start+size:return raw[rawstart+rva-start:rawstart+rva-start+n]
  raise ValueError('No section '+hex(va))
 anchors=entries(a.run_dir/'evidence/retail_opcode_anchors.tsv');check('anchor count',len(anchors)>=30)
 for x in anchors:
  expected=bytes.fromhex(x['hex']);check('PE opcode at '+x['va'],pebytes(int(x['va'],16),len(expected))==expected)
 casepaths={'bus_native_registered':a.bus_native,'gtsi_native_registered':a.gtsi_native,'bus_zero_registered':a.bus_zero,'bus_unselected_native_registered':a.bus_unselected}
 traces={k:entries(path) for k,path in casepaths.items()}
 for name,events in traces.items():
  check(name+' trace scenario identity',len({x['scenario'] for x in events})==1)
  check(name+' spawn original instructions',len(from_events(events,'NATIVE_SPAWN_STATUS'))==1)
  check(name+' constructor output/class',len(from_events(events,'NATIVE_VCF_COMPLETE'))==1)
  check(name+' original VLOC flag',len(from_events(events,'NATIVE_FLAG_PREDICATE'))>=1)
  check(name+' native camera projection',len(from_events(events,'CAMERA_PROJECTION_INIT_END'))==1)
  check(name+' original active-entry registration',len(from_events(events,'NATIVE_WORLD_REGISTRATION'))==1)
  check(name+' original camera read',len(from_events(events,'CAMERA_RUNTIME_READ'))==1)
  check(name+' camera terminal event',len(from_events(events,'CAMERA_CALLBACK_END'))==1)
  check(name+' camera six-double event',len(from_events(events,'CAMERA_DOUBLE_FIELDS'))==1)
  before=fields(from_events(events,'ROOT_BEFORE_VCF')[0]['detail']);after=fields(from_events(events,'ROOT_AFTER_VCF')[0]['detail']);reg=fields(from_events(events,'NATIVE_WORLD_REGISTRATION')[0]['detail']);act=fields(from_events(events,'ACTIVE_CAMERA_ENTRY')[0]['detail']);out=fields(from_events(events,'CAMERA_CALLBACK_END')[0]['detail']);dbl=fields(from_events(events,'CAMERA_DOUBLE_FIELDS')[0]['detail']);post=fields(from_events(events,'FLAGGED_VCF_POST')[0]['detail']);spawn=fields(from_events(events,'NATIVE_SPAWN_STATUS')[0]['detail'])
  for state in [before,after]:check(name+' consistent root direction',state['dir']=='00000000,00000000,00000000' if name=='bus_zero_registered' else state['dir']=='00000000,00000000,3F800000')
  check(name+' registry points at original entry',reg['entry']=='00542830' and reg['owner']=='26000000')
  check(name+' reference acquisition',reg['countBefore']=='0' and reg['countAfter']=='1' and reg['refBefore']=='3' and reg['refAfter']=='4')
  check(name+' true original active entry fed camera',act['entry']==reg['entry'] and act['owner']=='26000000' and act['nativeRegistry']=='true')
  check(name+' original camera returned epilogue',from_events(events,'CAMERA_CALLBACK_END')[0]['pc']=='00406DF4')
  check(name+' baseline viewport projection not omitted',len(from_events(events,'CAMERA_INIT_MATH_BOUNDARY'))>=4)
  check(name+' camera state hash',len(dbl['cameraStateSha256'])==64 and int(dbl['cameraStateSha256'],16)>0)
  check(name+' camera finite double count',int(dbl['invalid'])== (6 if name=='bus_zero_registered' else 0))
  check(name+' measured six doubles',len(dbl['values'].split(','))==6)
  check(name+' source VCF status determined by flag',('status=00010010' in from_events(events,'NATIVE_SPAWN_STATUS')[0]['detail'])== (name!='bus_unselected_native_registered'))
  if name=='bus_unselected_native_registered':
   check(name+' missing VLOC child',post['runtime398']=='00000000')
   check(name+' missing camera post guard',not from_events(events,'CAMERA_POST_GUARD'))
   check(name+' skips matrix builder',not from_events(events,'ROOT_TO_MATRIX_RESULT'))
   check(name+' untouched camera',int(out['cameraChangedBytes'])==0 and int(out['n'])==40)
  else:
   check(name+' VLOC attachment class 0x28',post['runtime398']=='27000800' and post['class28']=='40')
   check(name+' post guard',len(from_events(events,'CAMERA_POST_GUARD'))==1)
   check(name+' original world-matrix entry',len(from_events(events,'ROOT_TO_MATRIX_INPUT'))==1)
   check(name+' original matrix result',len(from_events(events,'ROOT_TO_MATRIX_RESULT'))==1)
   transform=fields(from_events(events,'ROOT_TO_MATRIX_RESULT')[0]['detail'])
   check(name+' transform finite count',int(transform['invalid'])==(9 if name=='bus_zero_registered' else 0))
   check(name+' original matrix entries',len(transform['matrix'].split(','))==16)
   check(name+' original view commit flag',out['cameraViewFlag']=='00010000')
   check(name+' camera changes',int(out['cameraChangedBytes'])>0)
   check(name+' original view matrix composition',len([x for x in from_events(events,'CAMERA_NATIVE_CALLEE_ENTER') if x['pc']=='00472990'])==1)
  if name!='bus_zero_registered':check(name+' original root ctor executed',len(from_events(events,'NATIVE_ROOT_CTOR'))==1)
  if name=='bus_zero_registered':check('zero root did not execute node ctor',not from_events(events,'NATIVE_ROOT_CTOR'))
 # independent finite camera and numerical consistency checks
 for name in ('bus_native_registered','gtsi_native_registered'):
  values=fields(from_events(traces[name],'CAMERA_DOUBLE_FIELDS')[0]['detail'])['values'].split(',')
  for idx,v in enumerate(values):check(name+f' camera scalar {idx} finite',math.isfinite(float(v)))
 zeros=fields(from_events(traces['bus_zero_registered'],'CAMERA_DOUBLE_FIELDS')[0]['detail'])['values'].split(',')
 for idx,v in enumerate(zeros):check(f'zero root NaN propagated {idx}',math.isnan(float(v)))
 # public derived summary should be consistent with private replay, not unverifiable manually authored numbers
 public={r['scenario']:r for r in entries(a.run_dir/'evidence/scenario_results.tsv')}
 check('public has exact four cases',set(public)==set(casepaths))
 for name,events in traces.items():
  final=fields(from_events(events,'CAMERA_DOUBLE_FIELDS')[0]['detail']);reg=fields(from_events(events,'NATIVE_WORLD_REGISTRATION')[0]['detail']);rec=public[name]
  for field,event_field in [('camera_double_nonfinite','invalid'),('camera_double_values','values'),('camera_state_sha256','cameraStateSha256')]:check(name+' derived field '+field,rec[field]==final[event_field])
  check(name+' derived active entry',rec['registration_entry']==reg['entry'])
 check('provenance repeat hashes identical',digest(a.bus_native)==digest(a.bus_native_repeat))
 report=json.loads((a.run_dir/'evidence/replay_provenance.json').read_text())
 check('provenance current binary',report['binary_sha256']==sha['exe'])
 check('provenance current GZF',report['ghidra_v97_gzf_sha256']==sha['gzf'])
 for name,path in [('bus_native_registered',a.bus_native),('bus_native_repeat',a.bus_native_repeat),('gtsi_native_registered',a.gtsi_native),('bus_zero_registered',a.bus_zero),('bus_unselected_native_registered',a.bus_unselected)]:check('private trace SHA '+name,report['private_replay_traces_sha256'][name]==digest(path))
 print(f'PASS {checks}/{checks} original PE and independent Milestone-B replay assertions')
 return checks

if __name__=='__main__':main()
