#!/usr/bin/env python3
"""Static original I76EDIT.EXE fixed-anchor audit; not original-code execution."""
import sys,hashlib,struct,json
from pathlib import Path
MD5='4c7ed9e8a54fcadbf1895f34aa9918fe'
SHA='69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df'
A={
0x40a6f3:'c7442418e89b4300',0x40a72f:'8b421c',0x40a775:'668b3c48',
0x40a780:'e8fb8e0100',0x40a792:'e8e98e0100',0x40a7ac:'b905000000',
0x40a80f:'e8f469ffff',0x40a86b:'e8fc69ffff',0x40a8c4:'2bcf',
0x40a8c6:'2bd6',0x40a8c8:'41',0x40a8c9:'42',0x40a8dc:'bbffffffff',
0x40a8f8:'bd01000000',0x40a905:'6a01',0x40a927:'e8f068ffff',
0x40a95f:'668b0c5554c54300',0x40a96c:'6681f90080',
0x40a973:'45',0x40a985:'43',0x40a99b:'8b542414',
0x40a99f:'668b420c',0x40a9a8:'663d0100',
0x40a9c4:'ff248500ab4000',0x40a9d5:'c744242006000000',
0x40a9df:'c744242007000000',0x40a9e7:'bbffffffff',
0x40aa03:'bd01000000',0x40aa5c:'6689144d54c54300',
0x40aa64:'85c0',0x40aa73:'e8fc69ffff',0x40aaa4:'33c0',
0x40aaa8:'668b044d54c54300',0x40aab0:'83f8ff',
0x40aab5:'89420c',0x40aac2:'85c9',0x40aad2:'0502400000',
0x421c0d:'3d00800000',0x421d40:'8b442410',
0x421d49:'83f806',0x422bda:'b900200000',0x422bdf:'f3a5'}
def check(path):
 b=Path(path).read_bytes()
 assert hashlib.md5(b).hexdigest()==MD5 and hashlib.sha256(b).hexdigest()==SHA
 p=struct.unpack_from('<I',b,0x3c)[0]
 assert b[p:p+4]==bytes([80,69,0,0])
 n=struct.unpack_from('<H',b,p+6)[0];o=struct.unpack_from('<H',b,p+20)[0]
 base=struct.unpack_from('<I',b,p+52)[0];sects=[]
 for i in range(n):
  q=p+24+o+40*i
  v,r,sz,offset=struct.unpack_from('<IIII',b,q+8)
  sects.append((base+r,sz,offset))
 def read(va,size):
  for start,length,offset in sects:
   if start<=va and va+size<=start+length:
    return b[offset+va-start:offset+va-start+size]
  raise ValueError(hex(va))
 results={hex(addr):read(addr,len(bytes.fromhex(s))).hex()==s for addr,s in A.items()}
 results['class_table']=struct.unpack('<4I',read(0x40ab00,16))==(0x40a9d5,0x40a9d5,0x40a9df,0x40a9df)
 return dict(test_count=len(results),passed_count=sum(results.values()),checks=results,original_code_executed=False)
if __name__=='__main__':
 if len(sys.argv)!=2:raise SystemExit('Usage: verify_native.py PRIVATE_I76EDIT.EXE')
 x=check(sys.argv[1]);print(json.dumps(x,indent=2))
 assert x['test_count']==x['passed_count']
