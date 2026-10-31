#!/usr/bin/env python3
"""Authenticate source containers and extract sparse PE/ABI provenance, no payload dumps."""
import argparse,hashlib,json,struct
from pathlib import Path
p=argparse.ArgumentParser()
for k in ['exe','gzf','zfs','out']:p.add_argument('--'+k,type=Path,required=True)
a=p.parse_args();b=a.exe.read_bytes();pe=struct.unpack_from('<I',b,60)[0];optional=pe+24;n=struct.unpack_from('<H',b,pe+6)[0];sect=optional+struct.unpack_from('<H',b,pe+20)[0];base=struct.unpack_from('<I',b,optional+28)[0]
def off(rva):
 for i in range(n):
  vs,r,sz,f=struct.unpack_from('<IIII',b,sect+40*i+8)
  if r<=rva<r+sz:return f+rva-r
 raise AssertionError('unbacked RVA')
def cstr(at):return b[at:b.index(b'\0',at)].decode('ascii')
rva=struct.unpack_from('<I',b,optional+104)[0];d=off(rva);imports=[]
while any(b[d:d+20]):
 lookup,stamp,forward,name,iat=struct.unpack_from('<IIIII',b,d);dll=cstr(off(name));i=0
 while True:
  value=struct.unpack_from('<I',b,off(lookup or iat)+4*i)[0]
  if not value:break
  if base+iat+4*i==0x4bc27c:imports.append({'dll':dll,'name':cstr(off(value)+2),'iat_va':'004BC27C'})
  i+=1
 d+=20
assert len(imports)==1 and imports[0]['name']=='_ftol'
constants={hex(va):struct.unpack_from('<f',b,off(va-base))[0] for va in [0x4be698,0x4be6e4,0x4be6e8,0x4be6d0,0x4be6e0,0x4be6ec]}
anchors={hex(va):b[off(va-base):off(va-base)+size].hex() for va,size in [(0x4791f7,6),(0x479247,5),(0x47924c,2),(0x4793a4,2),(0x4794af,2),(0x4794ed,2),(0x47950b,2),(0x47cc55,7),(0x47cc62,2),(0x4ba090,6),(0x446f44,5),(0x42dc36,5),(0x434606,5),(0x475ac4,5)]}
hashes={k:{'md5':hashlib.md5(getattr(a,k).read_bytes()).hexdigest(),'sha256':hashlib.sha256(getattr(a,k).read_bytes()).hexdigest()} for k in ['exe','gzf','zfs']}
assert hashes['exe']['sha256']=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
assert hashes['gzf']['sha256']=='b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'
assert hashes['zfs']['sha256']=='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'
a.out.write_text(json.dumps({'inputs':hashes,'import':imports,'float32_constants':constants,'sparse_retail_anchors':anchors},indent=2)+'\n')
