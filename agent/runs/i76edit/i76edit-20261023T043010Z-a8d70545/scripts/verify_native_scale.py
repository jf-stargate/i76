#!/usr/bin/env python3
"""Read-only original I76EDIT.EXE native scale and rounding anchors."""
import hashlib,struct,sys,json
from pathlib import Path
b=Path(sys.argv[1]).read_bytes()
assert hashlib.md5(b).hexdigest()=='4c7ed9e8a54fcadbf1895f34aa9918fe'
assert hashlib.sha256(b).hexdigest()=='69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df'
p=struct.unpack_from('<I',b,0x3c)[0];assert b[p:p+4]==b'PE\0\0'
n=struct.unpack_from('<H',b,p+6)[0];oh=struct.unpack_from('<H',b,p+20)[0];base=struct.unpack_from('<I',b,p+52)[0]
sections=[]
for i in range(n):
 q=p+24+oh+i*40;v,r,s,o=struct.unpack_from('<IIII',b,q+8);sections.append((base+r,s,o))
def read(addr,size):
 for start,length,offset in sections:
  if start<=addr and addr+size<=start+length:return b[offset+addr-start:offset+addr-start+size]
 raise ValueError(hex(addr))
anchors={0x4030c9:'d80d30204300',0x4030d2:'d80d30204300',0x421e62:'d80d40224300',0x4221d2:'d80d50224300',0x4235b3:'80cc0c',0x4235bd:'df7df4',0x4221f5:'f7f9',0x4221f7:'83fa04',0x422200:'d80538224300'}
constants={0x432030:5.,0x432240:.5,0x432244:10.,0x432248:-2.,0x43224c:2.,0x432250:5.}
checks={hex(a):read(a,len(bytes.fromhex(v))).hex()==v for a,v in anchors.items()}
checks.update({hex(a):struct.unpack('<f',read(a,4))[0]==v for a,v in constants.items()})
print(json.dumps({'checks':checks,'passed':sum(checks.values()),'total':len(checks)},indent=2))
assert all(checks.values())
