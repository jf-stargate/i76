"""Independent integer addressing and rational IEEE/x87 arithmetic; no original calls."""
from fractions import Fraction as F
import struct,math

def f32(x):return struct.unpack('<f',struct.pack('<f',x))[0]
R=F(f32(.2));H=F(f32(.1));BIAS=F(6755399441055744)
def pow2(n):return F(2**n) if n>=0 else F(1,2**-n)
def rounded(v,p=64,rc='nearest'):
 v=F(v)
 if not v:return F(0)
 av=abs(v);e=av.numerator.bit_length()-av.denominator.bit_length()
 if av<pow2(e):e-=1
 unit=pow2(e-p+1);u=v/unit;n=u.numerator//u.denominator
 if rc=='nearest':
  rem=u-n
  if rem>F(1,2) or (rem==F(1,2) and n&1):n+=1
 return n*unit

def signed32(n):return ((n+2**31)%2**32)-2**31

def location(x,z):
 X=signed32(x+3072);Z=signed32(z+3072)
 slot=signed32((Z&0xffffff80)+(X>>7));sample=(Z&127)*128+(X&127)
 return slot,sample

def bias(v):
 biased=rounded(rounded(rounded(F(v)*R)+BIAS),53)
 return struct.unpack('<i',struct.pack('<d',float(biased))[:4])[0]

def admitted(x,z):return ((x|z|signed32(10240-x)|signed32(10240-z))&0x80000000)==0

def ext_fraction(h):
 bits=int.from_bytes(bytes.fromhex(h),'little');m=bits&((1<<64)-1);e=(bits>>64)&32767
 return (-1 if bits>>79 else 1)*m*pow2(e-16383-63) if m else F(0)

class Terrain:
 def __init__(self,msn,ter,default,variant='retail'):
  i=msn.index(b'ZMAP');self.zm=bytearray(msn[i+9:i+6409]);self.ter=bytearray(ter);self.default=default
  if variant=='alias':
   for z in range(80):
    found=False
    for x in range(79):
     at=z*80+x
     if self.zm[at]!=255 and self.zm[at+1]!=255 and self.zm[at]!=self.zm[at+1]:
      self.zm[at+1]=self.zm[at];found=True;break
    if found:break
  if variant=='bit12':
   for i in range(1,len(self.ter),2):self.ter[i]^=16
 def sample(self,x,z):
  slot,sample=location(x,z);px,pz=slot%128,slot//128
  if not 0<=slot<16384:
   return {'global':[x,z],'grid_slot':slot,'local_sample':sample,'outcome':'invalid_flattened_index' if slot>=16384 else 'unsafe_negative_index','height12':0}
  page=self.zm[(pz-24)*80+px-24] if 24<=px<104 and 24<=pz<104 else 255
  off=(page*32768 if page!=255 else 0)+2*sample
  word=struct.unpack_from('<H',self.ter if page!=255 else self.default,off)[0]
  address=(0x40000000+page*32768 if page!=255 else 0x59c588)+2*sample
  return {'global':[x,z],'runtime_grid':[px,pz],'grid_slot':slot,'serialized_cell':[px-24,pz-24] if 24<=px<104 and 24<=pz<104 else None,'page':page if page!=255 else 'default','local_sample':sample,'local':[sample%128,sample//128],'ter_byte_offset':off if page!=255 else None,'address':f'{address:08X}','raw_word':f'{word:04X}','height12':word&4095,'class':word>>13,'bit12':bool(word&4096),'world_position':[5*x,float((word&4095)*H),5*z]}
 def height(self,x,z):
  bx,bz=bias(x),bias(z)
  if not admitted(bx,bz):return {'admission':[bx,bz],'admitted':False,'corners':[],'expected':F(0),'class':5}
  sx=rounded(rounded(F(x)*R,64,'down'),53,'down');sz=rounded(rounded(F(z)*R,64,'down'),53,'down')
  ix,iz=math.floor(sx),math.floor(sz);fx=sx-ix;fz=sz-iz
  cs=[self.sample(ix,iz),self.sample(ix+1,iz),self.sample(ix,iz+1),self.sample(ix+1,iz+1)]
  a,b,c,d=[v['height12'] for v in cs]
  top=rounded(rounded(rounded((b-a)*fx,64,'down')+a,64,'down'),24,'down')
  bottom=rounded(rounded(rounded((d-c)*fx,64,'down')+c,64,'down'),24,'down')
  result=rounded(rounded(rounded(rounded(bottom-top)*fz)+top)*H)
  mat=self.sample(bx,bz)
  return {'admission':[bx,bz],'admitted':True,'scaled':[float(sx),float(sz)],'floor':[ix,iz],'fractions':[float(fx),float(fz)],'corners':cs,'rows':[float(top),float(bottom)],'expected':result,'class':mat.get('class',0),'class_sample':mat}
