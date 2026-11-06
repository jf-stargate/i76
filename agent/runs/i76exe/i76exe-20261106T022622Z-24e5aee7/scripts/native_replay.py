#!/usr/bin/env python3
"""Private supplied PE image; unchanged root/math/sampler instructions on i386.

Frame prefix 00490A8B..00490B22 executes unchanged. Continuation 00490B23
is replaced with ADD ESP,4;RET to stop before topology. OS/image backing is
substituted; this is not a Windows frame. Table is originally initialized.
"""
import argparse,pathlib,struct,subprocess,json,hashlib
p=argparse.ArgumentParser()
for n in ['exe','msn','ter','cases','out']:p.add_argument('--'+n,type=pathlib.Path,required=True)
a=p.parse_args();a.out.mkdir(exist_ok=True,parents=True);src=pathlib.Path(__file__).parent
b=a.exe.read_bytes()
assert hashlib.sha256(b).hexdigest()=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
h=struct.unpack_from('<I',b,60)[0];s=h+24+struct.unpack_from('<H',b,h+20)[0]
image=bytearray(0x300000)
for j in range(struct.unpack_from('<H',b,h+6)[0]):
    _,_,rva,size,off=struct.unpack_from('<8sIIII',b,s+j*40);image[rva:rva+size]=b[off:off+size]
assert image[0x90b23:0x90b26]==bytes.fromhex('83c404')
image[0x90b23:0x90b27]=bytes.fromhex('83c404c3')
image[0x2442c0:0x2442c8]=struct.pack('<ff',5.,struct.unpack('<f',bytes.fromhex('cdcc4c3e'))[0])
msn=a.msn.read_bytes();zm=msn.index(b'ZMAP');grid=[]
for j in range(16384):
    x,z=j%128-24,j//128-24
    page=msn[zm+9+z*80+x] if 0<=x<80 and 0<=z<80 else 255
    grid.append(0x59c588 if page==255 else 0x40000000+page*32768)
image[0x244380:0x254380]=struct.pack('<16384I',*grid)
image[0x19c588:0x1a4588]=bytes(32768)
subprocess.run(['as','--32',str(src/'native_root.S'),'-o',str(a.out/'shim.o')],check=True)
subprocess.run(['ld','-m','elf_i386',str(a.out/'shim.o'),'-o',str(a.out/'shim')],check=True)
ter=a.ter.read_bytes();result={}
for f in sorted(a.cases.glob('*.tsv.view.bin')):
    case=f.name.removesuffix('.tsv.view.bin');view=f.read_bytes()
    width=800 if case=='lodwide' else 640
    raw=subprocess.run([str(a.out/'shim')],input=bytes(image)+ter+bytes(0x800000-len(ter))+view+struct.pack('<III',width,480,int(case[-1]) if case.startswith('quality') else 0),capture_output=True,check=True).stdout
    assert len(raw)==168
    accepted,tx,tz,x,z,e,n=struct.unpack_from('<7I',raw)
    planes=[]
    for j in range(n if accepted else 0):
        off=48+j*24
        planes.append({'nx_bits':f'{struct.unpack_from("<I",raw,off)[0]:08X}','nz_bits':f'{struct.unpack_from("<I",raw,off+8)[0]:08X}','offset_le':raw[off+16:off+24].hex(),'ny_bits':f'{struct.unpack_from("<I",raw,off+4)[0]:08X}','padding_bits':f'{struct.unpack_from("<I",raw,off+12)[0]:08X}'})
    result[case]={'accepted':bool(accepted),'threshold_bits':[f'{tx:08X}',f'{tz:08X}'],'root':[x,z,e],'planes':planes,'raw_sha256':hashlib.sha256(raw).hexdigest()}
(a.out/'native.json').write_text(json.dumps(result,indent=2)+'\n')
print('Native root cases:',len(result))
