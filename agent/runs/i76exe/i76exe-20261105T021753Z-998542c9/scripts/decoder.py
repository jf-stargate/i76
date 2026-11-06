"""Bounded independent VQM/CBK decoder. Strict checks are host policy."""
import struct
MAX_PIXELS=4*1024*1024
class InvalidTexture(ValueError): pass

def decode(vqm,cbk):
    if len(vqm)<24 or len(cbk)<4: raise InvalidTexture('short header')
    w,hf=struct.unpack_from('<II',vqm);h=hf&0x1fffffff
    if not w or not h or w*h>MAX_PIXELS: raise InvalidTexture('dimensions')
    if hf&0xe0000000: raise InvalidTexture('flagged input requires separate allocation contract')
    if b'\0' not in vqm[8:24]: raise InvalidTexture('unterminated dependency')
    n=struct.unpack_from('<I',cbk)[0]
    if n>32768 or len(cbk)!=4+16*n: raise InvalidTexture('codebook extent')
    bw,bh=(w+3)//4,(h+3)//4
    if len(vqm)!=24+2*bw*bh: raise InvalidTexture('token extent')
    out=bytearray(8+w*h);struct.pack_into('<II',out,0,w,hf)
    for by in range(bh):
        for bx in range(bw):
            t=struct.unpack_from('<H',vqm,24+2*(by*bw+bx))[0]
            if not t&0x8000 and t>=n: raise InvalidTexture('codebook index')
            for y in range(min(4,h-by*4)):
                for x in range(min(4,w-bx*4)):
                    out[8+(by*4+y)*w+bx*4+x]=t&255 if t&0x8000 else cbk[4+t*16+y*4+x]
    return bytes(out)
