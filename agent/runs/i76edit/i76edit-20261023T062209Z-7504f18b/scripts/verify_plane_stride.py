#!/usr/bin/env python3
"""Verify native original I76EDIT.EXE terrain zone stride instruction anchors."""
import hashlib,json,struct,sys
from pathlib import Path
b=Path(sys.argv[1]).read_bytes()
assert hashlib.md5(b).hexdigest()=='4c7ed9e8a54fcadbf1895f34aa9918fe'
assert hashlib.sha256(b).hexdigest()=='69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df'
pe=struct.unpack_from('<I',b,0x3c)[0];assert b[pe:pe+4]==b'PE\x00\x00'
n=struct.unpack_from('<H',b,pe+6)[0];opt=struct.unpack_from('<H',b,pe+20)[0];base=struct.unpack_from('<I',b,pe+52)[0]
sections=[]
for j in range(n):
 p=pe+24+opt+j*40
 v,r,s,o=struct.unpack_from('<IIII',b,p+8)
 sections.append((base+r,s,o))
def read(addr,length):
 for start,size,off in sections:
  if start<=addr and addr+length<=start+size:return b[off+addr-start:off+addr-start+length]
 raise ValueError(hex(addr))
anchors={0x41212f:'c1e00d',0x412132:'03c1',0x412134:'8d048554c54300',0x412147:'c1e00d',0x41214a:'03c1',0x41214c:'8d0485a4caeb00',0x41232a:'0fbe8401f09e4300',0x41233d:'83e07f',0x41234f:'83e07f'}
checks={hex(a):read(a,len(bytes.fromhex(code))).hex()==code for a,code in anchors.items()}
report={'status':'passed' if all(checks.values()) else 'failed','test_count':len(checks),'passed_count':sum(checks.values()),'native_stride_bytes':(8192+1)*4,'checks':checks}
print(json.dumps(report,indent=2));assert all(checks.values())
