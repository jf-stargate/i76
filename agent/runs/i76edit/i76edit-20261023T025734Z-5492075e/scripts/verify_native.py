#!/usr/bin/env python3
"""Verify 47 original I76EDIT.EXE opcode anchors; no original-code execution."""
import hashlib,json,struct,sys
from pathlib import Path
MD5="4c7ed9e8a54fcadbf1895f34aa9918fe"
SHA="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
A={
0x4210fc:"ff248524144200",0x421103:"c705fc79430003000000",
0x42110f:"c705fc79430004000000",0x42111b:"c705fc79430002000000",
0x421188:"a32cc14300",0x4211bf:"a130c14300",0x4211c4:"8d444003",
0x4223f2:"a12cc14300",0x422402:"83f803",0x422416:"83f802",
0x422436:"a12cc14300",0x422450:"3d00800000",0x422524:"a12cc14300",
0x422529:"83f802",0x422532:"83f804",0x42253b:"83f803",
0x422540:"83f805",0x422549:"a130c14300",0x4225c0:"6a01",
0x4225cc:"3d00800000",0x4225d3:"a12cc14300",0x4225d8:"83f802",
0x4225f7:"e848ecfdff",0x4225ff:"a12cc14300",0x422606:"83f804",
0x42260b:"a1fc794300",0x422613:"6a00",0x422617:"e858eefdff",
0x421bf5:"e84cf4fdff",0x421c05:"e8b6f7fdff",0x421c0d:"3d00800000",
0x421cf0:"85ed",0x421cf8:"a12cc14300",0x421cfd:"83f803",
0x421d07:"f7fd",0x421d0c:"e833f5fdff",0x421d1a:"e855f7fdff",
0x421d30:"e83ff7fdff",0x421d44:"83f8ff",0x421d49:"83f806",
0x421d55:"83f803",0x421d5e:"e811f7fdff",0x421d6e:"a1fc794300",
0x421d76:"e8f9f6fdff",0x409294:"b801000000",
0x4092e6:"b803000000",0x40931c:"b802000000"}
def check(path):
 b=Path(path).read_bytes()
 assert hashlib.md5(b).hexdigest()==MD5 and hashlib.sha256(b).hexdigest()==SHA
 p=struct.unpack_from("<I",b,0x3c)[0];assert b[p:p+4]==b"PE\x00\x00"
 n=struct.unpack_from("<H",b,p+6)[0];o=struct.unpack_from("<H",b,p+20)[0]
 base=struct.unpack_from("<I",b,p+52)[0];sects=[]
 for i in range(n):
  q=p+24+o+40*i
  virt,addr,size,off=struct.unpack_from("<IIII",b,q+8)
  sects.append((base+addr,size,off))
 def at(va,size):
  for first,n,off in sects:
   if first<=va and va+size<=first+n:return b[off+va-first:off+va-first+size]
  raise ValueError(hex(va))
 matches={hex(a):at(a,len(bytes.fromhex(x))).hex()==x for a,x in A.items()}
 return {"input_sha256":SHA,"checks":matches,"test_count":len(matches),
         "passed_count":sum(matches.values()),"original_code_executed":False}
if __name__=="__main__":
 if len(sys.argv)!=2:raise SystemExit("Usage: verify_native.py PRIVATE_I76EDIT.EXE")
 r=check(sys.argv[1]);print(json.dumps(r,indent=2))
 raise SystemExit(0 if r["test_count"]==r["passed_count"] else 1)
