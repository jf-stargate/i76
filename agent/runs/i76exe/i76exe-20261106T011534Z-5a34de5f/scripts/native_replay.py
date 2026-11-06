#!/usr/bin/env python3
"""Build private mapped PE image and execute unmodified original samplers on i386 CPU."""
import pathlib,struct,subprocess,argparse,hashlib,json
p=argparse.ArgumentParser()
for k in ['exe','ter','trace','cases','out']:p.add_argument('--'+k,type=pathlib.Path,required=True)
p.add_argument('--variant',choices=['retail','alias','bit12'],default='retail')
a=p.parse_args();src=pathlib.Path(__file__).parent;out=a.out;out.mkdir(exist_ok=True,parents=True)
b=a.exe.read_bytes();assert hashlib.sha256(b).hexdigest()=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
ph=struct.unpack_from('<I',b,60)[0];sec=ph+24+struct.unpack_from('<H',b,ph+20)[0];image=bytearray(0x300000)
for i in range(struct.unpack_from('<H',b,ph+6)[0]):
 _,vs,rv,size,off=struct.unpack_from('<8sIIII',b,sec+i*40);image[rv:rv+size]=b[off:off+size]
# Explicit fixture installation from original parser's initialized grid.
grid=pathlib.Path(str(a.trace)+'.grid.bin').read_bytes();image[0x244380:0x254380]=grid
image[0x2442c0:0x2442c8]=struct.pack('<ff',5.,struct.unpack('<f',bytes.fromhex('cdcc4c3e'))[0])
default=pathlib.Path(str(a.trace)+'.default.bin').read_bytes();image[0x19c588:0x1a4588]=default
ter=a.ter.read_bytes()
if a.variant=='bit12':ter=bytes(v^16 if i%2 else v for i,v in enumerate(ter))
assert len(ter)<=0x800000
rows=[l.split('\t') for l in a.cases.read_text().splitlines() if l and not l.startswith('#')]
records=[]
for id,k,x,z in rows:
 x,z=float(x),float(z)
 if k=='sample':records.append(struct.pack('<IIIII',0,int(x)&0xffffffff,0,int(z)&0xffffffff,0)+bytes(4))
 else:records.append(struct.pack('<IddI',1,x,z,0))
subprocess.run(['as','--32',str(src/'native_sampler.S'),'-o',str(out/'shim.o')],check=True)
subprocess.run(['ld','-m','elf_i386',str(out/'shim.o'),'-o',str(out/'shim')],check=True)
raw=subprocess.run([str(out/'shim')],input=bytes(image)+ter+bytes(0x800000-len(ter))+struct.pack('<I',len(rows))+b''.join(records),capture_output=True,check=True).stdout
assert len(raw)==24*len(rows)
results=[]
for i,(id,k,x,z) in enumerate(rows):
 v=raw[24*i:24*i+24];d={'id':id,'kind':k}
 if k=='sample':d['value']=struct.unpack_from('<I',v)[0]
 else:d.update(st0=v[:10].hex(),surface_class=struct.unpack_from('<I',v,10)[0],cw=struct.unpack_from('<H',v,14)[0],row_bits=[f'{b:08X}' for b in struct.unpack_from('<II',v,16)])
 results.append(d)
(out/'native.json').write_text(json.dumps(results,indent=2)+'\n')
print(json.dumps({'cases':len(rows),'output_sha256':hashlib.sha256(raw).hexdigest()}))
