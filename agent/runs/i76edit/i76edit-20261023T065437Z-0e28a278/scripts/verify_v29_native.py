#!/usr/bin/env python3
"""Original I76EDIT.EXE zone allocation native opcode anchors, read-only."""
import hashlib,struct,sys,json
from pathlib import Path
MD5="4c7ed9e8a54fcadbf1895f34aa9918fe"
SHA="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
A={
0x411b36:"83f94f",0x411b3f:"83f84f",0x411b4a:"0fbe9c08f09e4300",
0x411b59:"83fbff",0x411b62:"85c0",0x411b66:"e8350a0000",
0x411b6c:"8806",0x411b70:"e8d9f6feff",0x411b7d:"b8ffffffff",
0x4125a0:"33c0",0x4125ad:"81c104800000",
0x4125b4:"81f960c9c300",0x4125bc:"b8ffffffff",
0x4125c9:"c7048d20c89b0001000000",
0x4118bb:"6840012800",0x4118c0:"6800800080",
0x411904:"6840012800",0x411909:"6800800080",
0x411931:"8dbbf09e4300",0x411937:"b8ffffffff",
0x41193c:"b914000000",0x411941:"f3ab",
0x411ba0:"8b44240c",0x411bc1:"e85af7feff"}
def verify(path):
 b=Path(path).read_bytes()
 assert hashlib.md5(b).hexdigest()==MD5
 assert hashlib.sha256(b).hexdigest()==SHA
 p=struct.unpack_from("<I",b,0x3c)[0];assert b[p:p+4]==b"PE\0\0"
 n=struct.unpack_from("<H",b,p+6)[0]
 oh=struct.unpack_from("<H",b,p+20)[0]
 base=struct.unpack_from("<I",b,p+52)[0];secs=[]
 for i in range(n):
  q=p+24+oh+40*i
  v,r,s,off=struct.unpack_from("<IIII",b,q+8)
  secs.append((base+r,s,off))
 def at(addr,size):
  for start,n,off in secs:
   if start<=addr and addr+size<=start+n:
    return b[off+addr-start:off+addr-start+size]
  raise ValueError(hex(addr))
 checks={hex(a):at(a,len(bytes.fromhex(value))).hex()==value for a,value in A.items()}
 return {"status":"passed" if all(checks.values()) else "failed","checks":checks,"passed_count":sum(checks.values()),"test_count":len(checks),"original_code_executed":False}
if __name__=="__main__":
 if len(sys.argv)!=2:raise SystemExit("Usage: verify_v29_native.py PRIVATE_I76EDIT.EXE")
 result=verify(sys.argv[1]);print(json.dumps(result,indent=2))
 assert result["test_count"]==result["passed_count"]
