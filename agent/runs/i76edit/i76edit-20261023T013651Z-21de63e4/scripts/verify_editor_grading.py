#!/usr/bin/env python3
"""Original I76EDIT.EXE fingerprint checks; requires a private original executable."""
import sys, hashlib, json, struct
data=open(sys.argv[1],"rb").read()
assert hashlib.md5(data).hexdigest()=="4c7ed9e8a54fcadbf1895f34aa9918fe"
assert hashlib.sha256(data).hexdigest()=="69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df"
pe=struct.unpack_from("<I",data,0x3c)[0]
assert data[pe:pe+4]==b"PE\x00\x00"
count=struct.unpack_from("<H",data,pe+6)[0];opt=struct.unpack_from("<H",data,pe+20)[0]
image=struct.unpack_from("<I",data,pe+52)[0]
sections=[]
for i in range(count):
 p=pe+24+opt+i*40
 virt,addr,size,offset=struct.unpack_from("<IIII",data,p+8)
 sections.append((image+addr,max(virt,size),offset))
def va(where,n):
 for start,size,offset in sections:
  if start<=where and where+n<=start+size:
   return data[offset+where-start:offset+where-start+n]
 raise ValueError("address outside sections")
anchors={
 0x40a780:"e8fb8e0100",0x40a792:"e8e98e0100",0x40a7ac:"b905000000",
 0x40a86b:"e8fc69ffff",0x40a96c:"6681f90080",
 0x40a9bc:"83e85083f803",0x40a9c4:"ff248500ab4000",
 0x40a9d5:"c744242006000000",0x40a9df:"c744242007000000",
 0x40aa5c:"6689144d54c54300",0x40aa73:"e8fc69ffff",
 0x40ac33:"e87c64ffff",0x40ac4f:"89590c",
 0x40e4c1:"e81f2dffff",0x40e4d9:"e83130ffff",0x40e4fe:"e8e22cffff",
 0x41f4e7:"6a02",0x41f510:"66893c48"
}
checks={hex(p):va(p,len(bytes.fromhex(b)))==bytes.fromhex(b) for p,b in anchors.items()}
checks["class_jump_table"]=struct.unpack("<4I",va(0x40ab00,16))==(0x40a9d5,0x40a9d5,0x40a9df,0x40a9df)
print(json.dumps({"checks":checks,"passed":sum(checks.values()),"total":len(checks)},indent=2))
assert all(checks.values())
