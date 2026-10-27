#!/usr/bin/env python3
"""Read-only original I76EDIT.EXE PE identity and CRT-SBH native opcode guards."""
import hashlib,struct,sys,json
from pathlib import Path
b=Path(sys.argv[1]).read_bytes()
assert hashlib.md5(b).hexdigest()=="4c7ed9e8a54fcadbf1895f34aa9918fe"
assert hashlib.sha256(b).hexdigest()=="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
a={
0x424fb0:"833d6886430000",0x424fd6:"ffd7",0x424fe9:"6800000100",
0x425077:"899e10080000",0x4250aa:"b900400000",0x4250cf:"895304",
0x425310:"53",0x42531e:"83bf1008000000",0x425364:"e827020000",
0x425410:"e89bfbffff",0x425426:"885a08",0x425590:"8b442404",
0x4255b0:"8817",0x4255d9:"c3",0x425260:"b9587e4300",
0x425269:"8b8110080000",0x42528d:"8b442408",0x4252c0:"8b4c2408",
0x4252d9:"005110",0x4252df:"c68110040000f1",
0x423350:"568b742408",0x42335b:"3b3574864300",
0x422fb7:"e8a4220000",0x422fce:"e8ed220000",
0x409881:"e85a9a0100",0x4098ea:"e8c879ffff",0x409a7c:"e81f950100"}
pe=struct.unpack_from("<I",b,0x3c)[0];assert b[pe:pe+4]==bytes((80,69,0,0))
n=struct.unpack_from("<H",b,pe+6)[0];op=struct.unpack_from("<H",b,pe+20)[0];base=struct.unpack_from("<I",b,pe+52)[0]
sections=[]
for i in range(n):
 q=pe+24+op+40*i;va,rva,raw,off=struct.unpack_from("<IIII",b,q+8)
 sections.append((base+rva,raw,off))
def read(addr,count):
 for start,n,off in sections:
  if start<=addr and addr+count<=start+n:return b[off+addr-start:off+addr-start+count]
 raise ValueError(hex(addr))
checks={hex(addr):read(addr,len(bytes.fromhex(sig))).hex()==sig for addr,sig in a.items()}
print(json.dumps({"passed":sum(checks.values()),"total":len(checks),"checks":checks},indent=2))
assert all(checks.values())
