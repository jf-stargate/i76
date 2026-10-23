#!/usr/bin/env python3
"""Original editor object lifetime and heap dispatch opcode anchors."""
import hashlib,json,struct,sys
from pathlib import Path
MD5="4c7ed9e8a54fcadbf1895f34aa9918fe"
SHA="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
A={
0x409877:"6a78",0x409881:"e85a9a0100",0x4098ea:"e8c879ffff",
0x41c437:"6a0c",0x41c4a9:"ff1538456401",
0x409a60:"8b442404",0x409a66:"8b7008",0x409a69:"8b0e",
0x409a6b:"8d048de89b4300",0x409a73:"e8887affff",
0x409a7c:"e81f950100",0x409a84:"5e",
0x409dd4:"8b3f",0x409dd6:"e8e372ffff",
0x409de2:"c704b5e89b430000000000",
0x41c480:"8b542408",0x41c48b:"8b4a04",
0x41c49f:"8908",0x422fa0:"83ec08",
0x422fa8:"85f6",0x422fb7:"e8a4220000",
0x422fc1:"7418",0x422fce:"e8ed220000",
0x422fe4:"ff1538456401",0x4010be:"e99d890000"}
def inspect(path):
 b=Path(path).read_bytes()
 assert hashlib.md5(b).hexdigest()==MD5
 assert hashlib.sha256(b).hexdigest()==SHA
 pe=struct.unpack_from("<I",b,0x3c)[0];assert b[pe:pe+4]==b"PE\x00\x00"
 n=struct.unpack_from("<H",b,pe+6)[0]
 op=struct.unpack_from("<H",b,pe+20)[0]
 base=struct.unpack_from("<I",b,pe+52)[0]
 sections=[]
 for i in range(n):
  q=pe+24+op+40*i
  virt,rva,sz,off=struct.unpack_from("<IIII",b,q+8)
  sections.append((base+rva,sz,off))
 def read(addr,size):
  for start,length,off in sections:
   if start<=addr and addr+size<=start+length:
    return b[off+addr-start:off+addr-start+size]
  raise ValueError(hex(addr))
 checks={hex(a):read(a,len(bytes.fromhex(sig))).hex()==sig for a,sig in A.items()}
 return {"test_count":len(checks),"passed_count":sum(checks.values()),"checks":checks,"original_code_executed":False}
if __name__=="__main__":
 if len(sys.argv)!=2:raise SystemExit("Usage: verify_public_anchors.py PRIVATE_I76EDIT.EXE")
 result=inspect(sys.argv[1]);print(json.dumps(result,indent=2))
 assert result["test_count"]==result["passed_count"]
