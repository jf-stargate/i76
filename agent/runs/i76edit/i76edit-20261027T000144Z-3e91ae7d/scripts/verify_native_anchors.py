#!/usr/bin/env python3
"""Check original editor identity and 32 native allocation/destructor opcode anchors."""
import sys, hashlib, struct, json
from pathlib import Path
MD5="4c7ed9e8a54fcadbf1895f34aa9918fe"
SHA="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
A={
0x4232e0:"a178864300",0x4232eb:"e810000000",0x423300:"56578b74240c",
0x423306:"83fee0",0x42330b:"33c0",0x423310:"85f6",0x423314:"be01000000",
0x423328:"e823000000",0x423334:"85ff",0x423339:"e8f22e0000",
0x423350:"568b742408",0x423355:"83c60f",0x423358:"83e6f0",
0x42335b:"3b3574864300",0x423369:"e8a21f0000",0x42337e:"ff15ac446401",
0x426230:"8b0d58c14300",0x42623f:"ffd1",0x426248:"b801000000",
0x409877:"6a78",0x409881:"e85a9a0100",0x40989a:"8903",
0x4098ea:"e8c879ffff",0x41c437:"6a0c",0x41c43c:"ff15ac446401",
0x41c442:"85c0",0x41c444:"7421",0x409dd4:"8b3f",
0x409dd6:"e8e372ffff",0x409a7c:"e81f950100",
0x422fb7:"e8a4220000",0x422fe4:"ff1538456401"
}
def verify(path):
 b=Path(path).read_bytes()
 assert hashlib.md5(b).hexdigest()==MD5
 assert hashlib.sha256(b).hexdigest()==SHA
 p=struct.unpack_from("<I",b,0x3c)[0];assert b[p:p+4]==bytes((80,69,0,0))
 n=struct.unpack_from("<H",b,p+6)[0];oh=struct.unpack_from("<H",b,p+20)[0]
 image=struct.unpack_from("<I",b,p+52)[0];sec=[]
 for i in range(n):
  q=p+24+oh+i*40
  virtual,rva,rawlen,off=struct.unpack_from("<IIII",b,q+8)
  sec.append((image+rva,rawlen,off))
 def at(addr,length):
  for start,sz,off in sec:
   if start<=addr and addr+length<=start+sz:return b[off+addr-start:off+addr-start+length]
  raise ValueError(hex(addr))
 out={hex(a):at(a,len(bytes.fromhex(s))).hex()==s for a,s in A.items()}
 print(json.dumps({"passed_count":sum(out.values()),"test_count":len(out),"checks":out},indent=2))
 assert all(out.values())
if __name__=="__main__":
 if len(sys.argv)!=2:raise SystemExit("Usage: verify_native_anchors.py PRIVATE_I76EDIT.EXE")
 verify(sys.argv[1])
