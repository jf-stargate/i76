#!/usr/bin/env python3
"""Verify original editor opcode anchors using a private I76EDIT.EXE (never modifies input)."""
import hashlib, json, struct, sys
from pathlib import Path
MD5="4c7ed9e8a54fcadbf1895f34aa9918fe"
SHA256="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
ANCHORS={
0x409877:"6a78",0x4098bc:"8d4364",0x4098c8:"8d436d",
0x409f3d:"6a78",0x409f54:"6a70",0x40a03d:"6a68",
0x409cbf:"8d466d",0x409cd5:"8d5664",0x409ccf:"c6467500",0x409ce7:"c6466c00",
0x40f8cf:"8d466d",0x40f8e5:"8d5664",
0x4166b1:"68f5030000",0x4166cb:"68f4030000",0x416744:"e8f6aafeff",0x416836:"e859aafeff",
0x41c437:"6a0c",0x41c452:"8908",0x41c454:"895004",0x41c459:"897008",0x41c45e:"894104",
0x4229ed:"663d0080",0x4229f7:"6683f901",0x422a01:"6683f905",
0x422b46:"668901",0x422bda:"b900200000",0x422bdf:"f3a5",
0x40e52c:"e89e2effff",0x40e56a:"e8602effff",0x40e5a8:"e8222effff",0x40e5e6:"e8e42dffff",
0x40e605:"e83f2cffff",
}
def inspect(path):
 data=Path(path).read_bytes()
 assert hashlib.md5(data).hexdigest()==MD5,"Wrong original PE MD5"
 assert hashlib.sha256(data).hexdigest()==SHA256,"Wrong original PE SHA256"
 pe=struct.unpack_from("<I",data,0x3c)[0]
 assert data[pe:pe+4]==b"PE\x00\x00"
 count=struct.unpack_from("<H",data,pe+6)[0]
 opt=struct.unpack_from("<H",data,pe+20)[0]
 base=struct.unpack_from("<I",data,pe+24+28)[0]
 sec=[]
 for i in range(count):
  p=pe+24+opt+40*i
  vs,va,rawsize,rawptr=struct.unpack_from("<IIII",data,p+8)
  sec.append((base+va,rawsize,rawptr))
 def va_bytes(addr,n):
  for base,size,off in sec:
   if base<=addr and addr+n<=base+size:
    return data[off+addr-base:off+addr-base+n]
  raise AssertionError("unmapped original VA "+hex(addr))
 checks={hex(addr):va_bytes(addr,len(bytes.fromhex(sig)))==bytes.fromhex(sig) for addr,sig in ANCHORS.items()}
 return {"type":"native_PE_opcode_audit","md5":MD5,"sha256":SHA256,
         "passed":sum(checks.values()),"test_count":len(checks),"checks":checks,
         "limitations":"Opcode identities only; not a runtime experiment"}
if __name__=="__main__":
 if len(sys.argv)!=2:raise SystemExit("Usage: verify_v22_native.py PATH_TO_PRIVATE_ORIGINAL_I76EDIT.EXE")
 result=inspect(sys.argv[1]);print(json.dumps(result,indent=2))
 raise SystemExit(0 if result["passed"]==result["test_count"] else 1)
