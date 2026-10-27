#!/usr/bin/env python3
"""Validate research evidence against private original assets and private Ghidra traces.
Do not publish traces, executable, ZFS, or GZF. Script prints only derived summaries.
"""
import argparse, hashlib, pathlib, struct, json, csv
p=argparse.ArgumentParser()
p.add_argument('--retail',required=True,type=pathlib.Path)
p.add_argument('--ghidra',required=True,type=pathlib.Path)
p.add_argument('--zfs',required=True,type=pathlib.Path)
p.add_argument('--traces',required=True,type=pathlib.Path)
p.add_argument('--out',required=True,type=pathlib.Path)
a=p.parse_args();checked=0

def require(expr,message):
 global checked
 checked+=1
 if not expr:raise AssertionError(message)

def sha(path):
 h=hashlib.sha256()
 with path.open('rb') as f:
  for chunk in iter(lambda:f.read(1024*1024),b''):h.update(chunk)
 return h.hexdigest()
for path,expected in [(a.retail,'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'),(a.ghidra,'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'),(a.zfs,'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d')]:require(sha(path)==expected,'source identity '+path.name)
pe=a.retail.read_bytes();peoff=struct.unpack_from('<I',pe,0x3c)[0];n=struct.unpack_from('<H',pe,peoff+6)[0];opsize=struct.unpack_from('<H',pe,peoff+20)[0];secbase=peoff+24+opsize;imagebase=struct.unpack_from('<I',pe,peoff+24+28)[0]
sections=[]
for i in range(n):
 pos=secbase+i*40;name=pe[pos:pos+8].strip(b'\0').decode();size,virt,rawsize,raw=struct.unpack_from('<IIII',pe,pos+8);sections.append((virt,max(size,rawsize),raw,name))
def get(va,length):
 rva=va-imagebase
 for v,size,raw,name in sections:
  if v<=rva and rva+length<=v+size:
   b=pe[raw+rva-v:raw+rva-v+length]
   require(len(b)==length,'section read bytes')
   return b
 raise AssertionError('out of PE '+hex(va))
anchors=[]
for va in [0x00405970,0x00406ab0,0x00406b02,0x00406b0d,0x00406b13,0x00406b86,0x00406c22,0x00406c90,0x00406cfe,0x00406d22,0x00406d27,0x00406d37,0x00406d40,0x00406d45,0x00406d6f,0x00406d87,0x00406d8c,0x00406db1,0x00406db6,0x00406dc4,0x00406dd0,0x00406dec,0x00406df4,0x00437f90,0x00458cb0,0x00472400,0x00472990,0x00493e60,0x00494e20,0x0049d400,0x004ba090]:
 b=get(va,4)
 require(any(b),'zero PE bytes '+hex(va));anchors.append((f'{va:08X}',b.hex()))

def rows(name):
 path=a.traces/name;require(path.exists(),name+' missing')
 with path.open(encoding='utf-8',errors='replace',newline='') as f:return list(csv.DictReader(f,delimiter='\t'))
files={'bus_selected':'bus_1_cam.tsv','bus_repeat':'bus_1_cam_repeat.tsv','gtsi_selected':'gtsi_1_cam.tsv','bus_unselected':'bus_0_cam.tsv','bus_init':'bus_1_with_init.tsv','bus_boundary':'bus_1_boundaries.tsv'}
records={k:rows(name) for k,name in files.items()}
require(sha(a.traces/files['bus_selected'])==sha(a.traces/files['bus_repeat']),'selected bus replays differ')
expected={'bus_selected':('4457',True,'140'),'bus_repeat':('4457',True,'140'),'gtsi_selected':('4473',True,'140'),'bus_unselected':('40',False,'0'),'bus_init':('4433',True,'80'),'bus_boundary':('4433',True,'80')}
for key,(n,sel,change) in expected.items():
 rr=records[key]
 ends=[e for e in rr if e['kind']=='CAMERA_CALLBACK_END']
 require(len(ends)==1,key+' return count');v=ends[0]['detail']
 require('n='+n+';' in v,key+' step count');require('cameraChangedBytes='+change in v,key+' changed byte count')
 require('eligible='+str(sel).lower() in v,key+' eligible flag');require('guardReached=true' in v,key+' guard reach')
 require(len([e for e in rr if e['kind']=='CAMERA_RUNTIME_READ'])==1,key+' runtime read count')
 require(('camera164=7FF80000' in v)==sel,key+' NaN field unexpected')
 require(('CAMERA_POST_GUARD' in {x['kind'] for x in rr})==sel,key+' post guard branch')
 require(('00472990' in [x['pc'] for x in rr if x['kind']=='CAMERA_NATIVE_CALLEE_ENTER'])==sel,key+' matrix compositor reach')
 require(('CAMERA_EXECUTION_STOP' not in {x['kind'] for x in rr}),key+' emulator stop')
 require(('NATIVE_VCF_COMPLETE' in {x['kind'] for x in rr}),key+' native VCF')
 require((('nodes=45' in next(x['detail'] for x in rr if x['kind']=='NATIVE_VCF_COMPLETE')) if key!='gtsi_selected' and sel else True),'bus class-28 node count')
init=records['bus_init'];require(len([x for x in init if x['kind']=='CAMERA_PROJECTION_INIT_END'])==1,'native camera init success')
require(any(x['kind']=='CAMERA_INIT_MATH_BOUNDARY' for x in init),'camera initialization boundary not logged')
b=records['bus_boundary']; phases={x['pc']:x['detail'] for x in b if x['kind']=='CAMERA_TRANSFORM_OUTPUT'}
for addr in ['00406D27','00406D45','00406D6F','00406D8C','00406DB6']:require(addr in phases,'missing transform phase '+addr)
require('nonFiniteF32Words=0' in phases['00406D27'],'sin/cos output already nonfinite')
require('nonFiniteF32Words=9' in phases['00406D45'],'world-root transform boundary changed')
require('nonFiniteF32Words=12' in phases['00406D6F'],'world-root matrix propagation unexpected')
require('nonFiniteF32Words=13' in phases['00406DB6'],'final matrix propagation unexpected')
for name, expected_type in [('bus_selected','28'),('gtsi_selected','28')]:
 v=next(x['detail'] for x in records[name] if x['kind']=='FLAGGED_VCF_POST')
 require('class28=40;' in v,name+' attachment missing')
summary={'run_check_count':checked,'retail_sha256':sha(a.retail),'ghidra_sha256':sha(a.ghidra),'zfs_sha256':sha(a.zfs),'repeat_bus_trace_sha256':sha(a.traces/files['bus_selected']),'scenarios':{key:next(x['detail'] for x in rr if x['kind']=='CAMERA_CALLBACK_END') for key,rr in records.items()},'matrix_boundary':phases,'original_opcode_anchors':len(anchors),'caution':'Original x86 executed under Ghidra with intercepted math functions and uninitialized world transform; finite camera pose NOT established'}
a.out.write_text(json.dumps(summary,indent=2)+'\n')
print('VERIFIED',checked,'/',checked,'; repeat_sha256='+summary['repeat_bus_trace_sha256'])
