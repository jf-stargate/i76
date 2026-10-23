#!/usr/bin/env python3
"""Check original editor identity and 24 small native anchors; never ships PE."""
import sys,struct,json,hashlib
from pathlib import Path
MD5="4c7ed9e8a54fcadbf1895f34aa9918fe"
SHA="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
anchors={
0x409210:"8b442410",0x40923e:"2bc7",0x409242:"0faf442410",
0x40924b:"99",0x40924c:"33c2",0x409250:"8bd8",
0x409264:"3be8",0x40926a:"3bdd",0x40926c:"7c0a",
0x409294:"b801000000",0x4092bd:"b801000000",
0x4092e6:"b803000000",0x40930f:"b803000000",
0x40931c:"b802000000",0x4235af:"668b45fe",
0x4235b3:"80cc0c",0x4235bd:"df7df4",0x4235c0:"d96dfe",
0x4221ea:"e8b5130000",0x4221f5:"f7f9",
0x4221f7:"83fa04",0x422200:"d80538224300",
0x422402:"83f803",0x422416:"83f802"}
def run(path):
 b=Path(path).read_bytes()
 assert hashlib.md5(b).hexdigest()==MD5
 assert hashlib.sha256(b).hexdigest()==SHA
 pe=struct.unpack_from("<I",b,0x3c)[0];assert b[pe:pe+4]==b"PE\x00\x00"
 n=struct.unpack_from("<H",b,pe+6)[0];opt=struct.unpack_from("<H",b,pe+20)[0]
 base=struct.unpack_from("<I",b,pe+52)[0];sections=[]
 for i in range(n):
  p=pe+24+opt+i*40
  virt,rva,length,offset=struct.unpack_from("<IIII",b,p+8)
  sections.append((base+rva,length,offset))
 def read(addr,size):
  for first,length,off in sections:
   if first<=addr and addr+size<=first+length:return b[off+addr-first:off+addr-first+size]
  raise ValueError(hex(addr))
 checks={hex(a):read(a,len(bytes.fromhex(v))).hex()==v for a,v in anchors.items()}
 return {"passed":sum(checks.values()),"total":len(checks),"checks":checks}
if __name__=="__main__":
 if len(sys.argv)!=2:raise SystemExit("Usage: verify_original_anchors.py PRIVATE_I76EDIT.EXE")
 result=run(sys.argv[1]);print(json.dumps(result,indent=2))
 assert result["passed"]==result["total"]
