"""Independent bounded arithmetic model; no decoding or original execution."""
import struct
TER=0x40000000
DEFAULT=0x59c588
PCS=[0x4915f7,0x49160f,0x491627,0x49163f]
def triggered(word):return word>>13 in (2,3,4,6,7)
def resolve(zmap,x,z):
 X,Z=x+3072,z+3072
 slot=(Z&~127)+(X>>7)
 if not 0<=slot<16384:return None
 px,pz=slot%128-24,slot//128-24
 page=zmap[pz*80+px] if 0<=px<80 and 0<=pz<80 else 255
 return (DEFAULT if page==255 else TER+page*32768)+2*((Z&127)*128+(X&127))
def read(terrain,address):
 if TER<=address and address+2<=TER+len(terrain):return struct.unpack_from('<H',terrain,address-TER)[0]
 if DEFAULT<=address and address+2<=DEFAULT+32768:return 0
 return None
def predict(zmap,terrain,x,z,size,coordinate=False):
 if min(x,z)<0 or max(x,z)>10240:return {'outcome':'leaf','reads':[]}
 start=resolve(zmap,x,z)
 if start is None:return {'outcome':'leaf','reads':[]}
 reads=[]
 for i in range(size-1,-1,-1):
  for pc,(dx,dz) in zip(PCS,[(i,0),(i,size-1),(0,i),(size-1,i)]):
   address=resolve(zmap,x+dx,z+dz) if coordinate else start+2*(dz*128+dx)
   word=read(terrain,address) if address is not None else None
   reads.append({'pc':pc,'address':address,'word':word,'i':i})
   if word is None:return {'outcome':'unsafe','reads':reads}
   if triggered(word):return {'outcome':'split','reads':reads}
 return {'outcome':'leaf','reads':reads}
