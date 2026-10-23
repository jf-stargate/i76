#!/usr/bin/env python3
"""Hash and instruction-anchor checks against the private original I76EDIT.EXE.

The file is required locally and never copied or uploaded. This is static
original-PE instruction validation, not runtime behavior verification.
"""
import sys, hashlib, struct, json
from pathlib import Path
MD5='4c7ed9e8a54fcadbf1895f34aa9918fe'
SHA='69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df'
RANGES=[('object_grade',0x40a6e0,1055),('road_neighbor',0x421be0,422),('smoothing',0x422870,941),('scheduler',0x40e3c0,774),('material_writer',0x41f4a0,151),('surface_reader',0x41f150,140),('list_node',0x41c430,58)]
ANCHORS={
0x40a6f3:'c7442418e89b4300',
0x40a72f:'8b421c',
0x40a775:'668b3c48',
0x40a780:'e8fb8e0100',
0x40a792:'e8e98e0100',
0x40a7ac:'b905000000',
0x40a80f:'e8f469ffff',
0x40a86b:'e8fc69ffff',
0x40a8c4:'2bcf',
0x40a8c6:'2bd6',
0x40a8c8:'41',
0x40a8c9:'42',
0x40a8dc:'bbffffffff',
0x40a8f8:'bd01000000',
0x40a905:'6a01',
0x40a927:'e8f068ffff',
0x40a95f:'668b0c5554c54300',
0x40a96c:'6681f90080',
0x40a973:'45',
0x40a985:'43',
0x40a99b:'8b542414',
0x40a99f:'668b420c',
0x40a9a8:'663d0100',
0x40a9c4:'ff248500ab4000',
0x40a9d5:'c744242006000000',
0x40a9df:'c744242007000000',
0x40a9e7:'bbffffffff',
0x40aa03:'bd01000000',
0x40aa5c:'6689144d54c54300',
0x40aa64:'85c0',
0x40aa73:'e8fc69ffff',
0x40aaa4:'33c0',
0x40aaa8:'668b044d54c54300',
0x40aab0:'83f8ff',
0x40aab5:'89420c',
0x40aac2:'85c9',
0x40aad2:'0502400000',
0x421c0d:'3d00800000',
0x421d40:'8b442410',
0x421d49:'83f806',
0x422bda:'b900200000',
0x422bdf:'f3a5',
}
def run(path):
    b=Path(path).read_bytes()
    assert hashlib.md5(b).hexdigest()==MD5
    assert hashlib.sha256(b).hexdigest()==SHA
    h=struct.unpack_from('<I',b,0x3c)[0]
    assert b[h:h+4]==b'PE\x00\x00'
    cnt,op=struct.unpack_from('<H',b,h+6)[0],struct.unpack_from('<H',b,h+20)[0]
    base=struct.unpack_from('<I',b,h+52)[0]
    sections=[]
    for i in range(cnt):
        p=h+24+op+40*i
        memsize,rva,rawsize,rawp=struct.unpack_from('<IIII',b,p+8)
        sections.append((base+rva,rawsize,rawp))
    def rd(va,n):
        for start,size,off in sections:
            if va>=start and va+n<=start+size:return b[off+va-start:off+va-start+n]
        raise ValueError(hex(va))
    checks={hex(addr):rd(addr,len(bytes.fromhex(sig))).hex()==sig for addr,sig in ANCHORS.items()}
    jumps=struct.unpack('<4I',rd(0x40ab00,16))
    checks['class_jump_table']=jumps==(0x40a9d5,0x40a9d5,0x40a9df,0x40a9df)
    ranges={name:hashlib.sha256(rd(start,length)).hexdigest() for name,start,length in RANGES}
    return {'input_md5':MD5,'input_sha256':SHA,'instruction_checks_passed':sum(checks.values()),'instruction_checks_total':len(checks),'checks':checks,'original_function_window_sha256':ranges,'limitations':'Static PE identity/opcode checks. The semantic fixture script is an independent analytical model, not original-code execution.'}
if __name__=='__main__':
    if len(sys.argv)!=2:raise SystemExit('Usage: verify_original_editor_functions.py /private/I76EDIT.EXE')
    r=run(sys.argv[1]);print(json.dumps(r,indent=2));raise SystemExit(0 if r['instruction_checks_passed']==r['instruction_checks_total'] else 1)
