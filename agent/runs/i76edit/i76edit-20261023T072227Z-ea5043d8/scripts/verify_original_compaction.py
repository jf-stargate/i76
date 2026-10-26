#!/usr/bin/env python3
"""Read-only original I76EDIT.EXE native zone-compaction opcode checks."""
import hashlib,struct,sys,json
from pathlib import Path
MD5='4c7ed9e8a54fcadbf1895f34aa9918fe'
SHA='69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df'
A={
0x411c11:'0fbebc10f09e4300',0x411c19:'3bfb',0x411c3b:'b820c89b00',
0x411c4a:'0504800000',0x411c57:'8d0489',0x411c61:'0fbeb410f09e4300',
0x411c7c:'83f950',0x411c81:'83fa50',0x411c90:'c600ff',
0x411c97:'83f8ff',0x411cbe:'b901000000',0x411cda:'889c38f09e4300',
0x411ce1:'e8c1f6feff',0x411d02:'66c702ffff',0x411d60:'f3a5',
0x411d8d:'f3a5',0x411dba:'f3a5',0x411ddd:'f3a5',0x411e07:'f3a5',
0x411e16:'c70201000000',0x411e54:'f3a5',0x411e8e:'e81bf3feff',
0x411e97:'e8b2f3feff',0x411ed1:'f3ab',0x411ef3:'e8ddf3feff',
0x411f19:'e8b7f3feff',0x411f35:'f3ab',0x411f55:'e87bf3feff',
0x411f5d:'c70700000000',0x411f92:'e83ef3feff',
0x411fc3:'e8dff3feff',0x411fd5:'c78620c89b0000000000',
0x412005:'b801000000',0x409e0f:'890c95e89b4300',
0x409e2c:'8b4808',0x409e2f:'8911',0x409dc6:'8b3cb5e89b4300'}
def verify(path):
 b=Path(path).read_bytes()
 assert hashlib.md5(b).hexdigest()==MD5
 assert hashlib.sha256(b).hexdigest()==SHA
 p=struct.unpack_from('<I',b,0x3c)[0]
 assert b[p:p+4]==bytes((80,69,0,0))
 n=struct.unpack_from('<H',b,p+6)[0]
 size=struct.unpack_from('<H',b,p+20)[0]
 image=struct.unpack_from('<I',b,p+52)[0]
 sections=[]
 for i in range(n):
  q=p+24+size+40*i
  virtual,rva,rawlen,offset=struct.unpack_from('<IIII',b,q+8)
  sections.append((image+rva,rawlen,offset))
 def at(a,n):
  for start,length,off in sections:
   if start<=a and a+n<=start+length:return b[off+a-start:off+a-start+n]
  raise ValueError(hex(a))
 checks={hex(a):at(a,len(bytes.fromhex(s)))==bytes.fromhex(s) for a,s in A.items()}
 return {'test_count':len(checks),'passed_count':sum(checks.values()),'checks':checks}
if __name__=='__main__':
 if len(sys.argv)!=2:raise SystemExit('Usage: verify_native.py PRIVATE_I76EDIT.EXE')
 x=verify(sys.argv[1]);print(json.dumps(x,indent=2))
 assert x['test_count']==x['passed_count']
