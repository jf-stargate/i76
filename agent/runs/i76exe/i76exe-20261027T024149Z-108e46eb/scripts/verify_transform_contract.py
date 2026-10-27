#!/usr/bin/env python3
"""Independent evidence verifier for original i76.exe 00437F90 milestone-A run.

Requires user's private original executable/GZF, and local Ghidra-generated trace TSVs.
Never publishes or modifies those private source files.
"""
import argparse,csv,hashlib,struct,re,pathlib,sys
SHA_EXE='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
MD5_EXE='a640ea0097dbb62e0c77b7f2847c7161'
SHA_GZF='b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'
SHA_NODE='efad34a038353be667b34b450bcf0019b9e77cb07e044239d84c562bca294fb6'
SHA_ISOLATED='aa24c56b4a751399f98b6a48105d9ac777cd024ce4be566047acd4169f5a5a12'

def digest(p,alg='sha256'):
 h=hashlib.new(alg)
 with open(p,'rb') as f:
  for data in iter(lambda:f.read(1024*1024),b''):h.update(data)
 return h.hexdigest()

def pairs(p):
 data={}
 with open(p,newline='') as f:
  for r in list(csv.DictReader(f,delimiter='\t')):
   data.setdefault(r['scenario'],{}).setdefault(r['event'],[]).append(r['detail'])
 return data

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--exe',required=True,type=pathlib.Path);ap.add_argument('--gzf',required=True,type=pathlib.Path);ap.add_argument('--node1',required=True,type=pathlib.Path);ap.add_argument('--node2',required=True,type=pathlib.Path);ap.add_argument('--isolated1',required=True,type=pathlib.Path);ap.add_argument('--isolated2',required=True,type=pathlib.Path);ap.add_argument('--run-dir',required=True,type=pathlib.Path);a=ap.parse_args();checks=0
 def check(msg,yes):
  nonlocal checks
  if not yes:raise AssertionError(msg)
  checks+=1
 check('Retail PE SHA256',digest(a.exe)==SHA_EXE);check('Retail PE MD5',digest(a.exe,'md5')==MD5_EXE);check('v97 GZF SHA256',digest(a.gzf)==SHA_GZF)
 check('repeat native node traces exact',a.node1.read_bytes()==a.node2.read_bytes())
 check('repeat native isolated traces exact',a.isolated1.read_bytes()==a.isolated2.read_bytes())
 check('node trace SHA',digest(a.node1)==SHA_NODE);check('isolated trace SHA',digest(a.isolated1)==SHA_ISOLATED)
 raw=a.exe.read_bytes();pe=struct.unpack_from('<I',raw,0x3c)[0];check('PE signature',raw[pe:pe+4]==b'PE\0\0');sectc=struct.unpack_from('<H',raw,pe+6)[0];opt=pe+24;img=struct.unpack_from('<I',raw,opt+28)[0];sizeopt=struct.unpack_from('<H',raw,pe+20)[0];secs=[]
 for i in range(sectc):
  loc=opt+sizeopt+i*40;name,vs,va,sz,ptr=struct.unpack_from('<8sIIII',raw,loc);secs.append((va,sz,ptr))
 def va_bytes(va,n):
  address=va-img
  for off,length,rawstart in secs:
   if off<=address and address+n<=off+length:return raw[rawstart+address-off:rawstart+address-off+n]
  raise ValueError(hex(va))
 anchors=list(csv.DictReader((a.run_dir/'evidence/retail_opcode_anchors.tsv').open(),delimiter='\t'))
 check('at least 35 sparse retail anchors',len(anchors)>=35)
 for row in anchors:
  expected=bytes.fromhex(row['hex']);check('retail opcode '+row['va'],va_bytes(int(row['va'],16),len(expected))==expected)
 node=pairs(a.node1);isol=pairs(a.isolated1)
 check('three node scenarios',set(node)=={'original_node_identity','original_node_direction_erased','manual_zero_root'})
 check('five isolated scenarios',set(isol)=={'nonvehicle','vehicle_zero_direction','vehicle_direction_z','vehicle_direction_x','vehicle_direction_z_zero_runtime'})
 for case in ('original_node_identity','original_node_direction_erased'):
  ev=node[case];check(case+' invoked original ctor',len(ev.get('ORIGINAL_NODE_CTOR',[]))==1);check(case+' uses actual node HeapAlloc boundary',len(ev.get('STUB_WINDOWS_HEAPALLOC',[]))==1);check(case+' ctor alloc 176', 'size=176' in ev['STUB_WINDOWS_HEAPALLOC'][0]);check(case+' correct ctor matrix', 'matrix=3F800000,00000000,00000000,00000000,3F800000,00000000,00000000,00000000,3F800000,' in ev['ORIGINAL_NODE_CTOR'][0]);check(case+' ctor forward nonzero','dir=00000000,00000000,3F800000' in ev['ORIGINAL_NODE_CTOR'][0])
 for case,nonfinite,direction,steps in [('original_node_identity',0,'00000000,00000000,3F800000',612),('original_node_direction_erased',9,'00000000,00000000,00000000',600),('manual_zero_root',9,'00000000,00000000,00000000',600)]:
  ev=node[case];check(case+' one output',len(ev['NATIVE_437F90_RESULT'])==1);out=ev['NATIVE_437F90_RESULT'][0];check(case+' native return pointer','return EAX=23002000' in out);check(case+' nonfinite count',f'bad={nonfinite};' in out);check(case+' root direction',f'direction={direction};' in out);check(case+' steps',f'steps={steps};' in out)
 check('class non1 no helper', 'proj=0;cross=0;basis=0;normalize=0' in isol['nonvehicle']['RESULT'][0]);check('class non1 constant copy','nonfinite=0;matrix=3f800000,00000000,00000000,00000000,3f800000' in isol['nonvehicle']['RESULT'][0]);
 for case,nonfinite in [('vehicle_zero_direction',9),('vehicle_direction_z',0),('vehicle_direction_x',0),('vehicle_direction_z_zero_runtime',0)]:
  ev=isol[case];check(case+' success','status=RETURN' in ev['RESULT'][0]);check(case+' nonfinite',f'nonfinite={nonfinite};' in ev['RESULT'][0]);check(case+' projection visited',len(ev.get('ORIGINAL_PROJECTION_ENTER',[]))==1);check(case+' cross visited',len(ev.get('ORIGINAL_CROSS_ENTER',[]))==1);check(case+' basis visited',len(ev.get('ORIGINAL_BASIS_ENTER',[]))==1);check(case+' reciprocal sqrt visited twice',len(ev.get('ORIGINAL_INV_LENGTH_ENTER',[]))==2)
 for row in csv.DictReader((a.run_dir/'evidence/field_access_contract.tsv').open(),delimiter='\t'):
  check('field evidence '+row['start'],bool(row['original_x86_evidence']))
 for row in csv.DictReader((a.run_dir/'evidence/caller_helper_edges.tsv').open(),delimiter='\t'):
  src=int(row['source_va'],16);target=int(row['target_va'],16);data=va_bytes(src,5)
  # Direct calls (E8 rel32) at supported addresses; reject guessed Ghidra flow.
  check('edge opcode '+row['source_va'],data[0]==0xe8)
  dest=(src+5+struct.unpack_from('<i',data,1)[0])&0xffffffff
  check('edge target '+row['source_va'],dest==target)
 print(f'PASS {checks}/{checks} independent assertions')
 return checks
if __name__=='__main__':main()
