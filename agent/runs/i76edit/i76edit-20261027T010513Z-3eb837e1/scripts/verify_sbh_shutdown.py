#!/usr/bin/env python3
"""Private original I76EDIT.EXE initial SBH threshold and 26 opcode anchor verifier."""
import sys,struct,hashlib,json
from pathlib import Path
b=Path(sys.argv[1]).read_bytes()
assert hashlib.md5(b).hexdigest()=="4c7ed9e8a54fcadbf1895f34aa9918fe"
assert hashlib.sha256(b).hexdigest()=="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
p=struct.unpack_from("<I",b,0x3c)[0];assert b[p:p+4]==bytes((80,69,0,0))
n=struct.unpack_from("<H",b,p+6)[0];o=struct.unpack_from("<H",b,p+20)[0];base=struct.unpack_from("<I",b,p+52)[0]
sec=[]
for i in range(n):
 q=p+24+o+40*i;v,r,raw,off=struct.unpack_from("<IIII",b,q+8)
 sec.append((base+r,raw,off))
def read(a,k):
 for first,count,off in sec:
  if first<=a and a+k<=first+count:return b[off+a-first:off+a-first+k]
 raise ValueError(hex(a))
assert struct.unpack("<I",read(0x438674,4))[0]==480
anchors={
0x424181:"e87a0d0000",0x424f00:"6a00",0x424f09:"ff1534456401",0x424f1b:"e890000000",
0x424f2a:"ff15a8446401",0x424f90:"8b442404",0x424f9a:"3d80070000",0x424fa1:"a374864300",
0x424f40:"56",0x424f5f:"ffd7",0x424f71:"ff15a8446401",
0x425121:"6800800000",0x425133:"ff1524456401",0x425172:"c7056886430000000000",
0x4251b2:"803bf0",0x4251b7:"6800400000",0x4251ca:"ff1524456401",0x4251d4:"c603ff",
0x4251d7:"ff0d70864300",0x425233:"50",0x425234:"e8e7feffff",
0x4252ec:"ff0570864300",0x4252f2:"833d7086430020",0x4252fd:"e87efeffff",
0x424fb0:"833d6886430000",0x4254bb:"ff1514456401"}
out={hex(a):read(a,len(bytes.fromhex(s))).hex()==s for a,s in anchors.items()}
print(json.dumps({"initial_threshold_bytes":480,"total":len(out),"passed":sum(out.values()),"checks":out},indent=2))
assert all(out.values())
