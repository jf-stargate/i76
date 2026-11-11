"""Independent research model. Inputs are geometry, camera and numerical constants.
No recorded emitter indices, choices, plane results or acceptance are inputs.
"""
import struct,math
def f32(x):return struct.unpack('<f',struct.pack('<f',x))[0]
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
def lowdouble(x):return struct.unpack('<II',struct.pack('<d',x))[0]
class Numerics:
 def __init__(self,pe):
  h=struct.unpack_from('<I',pe,60)[0];n=struct.unpack_from('<H',pe,h+6)[0];s=h+24+struct.unpack_from('<H',pe,h+20)[0];self.sections=[];self.pe=pe
  for j in range(n):
   p=s+j*40;size,rva,raw,off=struct.unpack_from('<4I',pe,p+8);self.sections.append((rva,max(size,raw),off,raw))
 def read(self,va,n):
  for r,size,off,raw in self.sections:
   if r<=va-0x400000<r+size:
    d=va-0x400000-r;return (self.pe[off+d:off+min(d+n,raw)]+bytes(n))[:n] if d<raw else bytes(n)
  raise ValueError(hex(va))
 def value(self,va,fmt):return struct.unpack('<'+fmt,self.read(va,struct.calcsize('<'+fmt)))[0]
 def seed(self,i):
  if i==128:return 255
  x=struct.unpack('<d',struct.pack('<II',0,((i|0x1ff00)<<13)&0xffffffff))[0]
  high=struct.unpack('<II',struct.pack('<d',self.value(0x4be8c0,'d')/math.sqrt(x)))[1]
  return ((high+0x400)>>12)&255
 def invsqrt(self,x):
  hi=struct.unpack('<II',struct.pack('<d',x))[1];seed=self.seed((hi>>13)&255)
  u=((((0xbfc-(hi>>20))&0xffffffff)>>1)<<20 | seed<<12)&0xffffffff
  y=struct.unpack('<d',struct.pack('<II',0,u))[0]
  return (self.value(0x4faf20,'d')-y*y*x)*(y*self.value(0x4faf28,'d'))*self.value(0x4faf30,'d')
 def plane(self,a,b,c):
  u=[b[i]-a[i] for i in range(3)];v=[c[i]-a[i] for i in range(3)]
  # Binary64 cross intermediates approximate original x87 temporaries;
  # the verifier checks the resulting normals/distances under stated bounds.
  cross=[v[2]*u[1]-v[1]*u[2],v[0]*u[2]-v[2]*u[0],v[1]*u[0]-v[0]*u[1]]
  rounded=list(map(f32,cross));length=sum(x*y for x,y in zip(cross,rounded));q=self.invsqrt(length)
  full=[x*q for x in rounded];normal=list(map(f32,full))
  # X was spilled before distance; Y/Z retain extended products in original.
  d=f32(-(a[0]*normal[0]+a[1]*full[1]+a[2]*full[2]))
  return normal+[d]
def flatten(edges,p,reverse=False):
 a,b,c,d=edges[p]
 if not c:return [b if reverse else a]
 return flatten(edges,d,True)+flatten(edges,c,True) if reverse else flatten(edges,c)+flatten(edges,d)
def anchor(edges,es):
 for p in es:
  a,b,c,d=edges[p]
  if c and not edges[c][2] and not edges[d][2]:return edges[c][1],'terminal_split_midpoint'
 a,b,c,d=[edges[p] for p in es]
 if not a[2]:
  if not c[2]:return c[0],'corner_c_start'
  if not d[2]:return d[0],'corner_d_start'
 elif not b[2]:
  if not c[2]:return c[1],'corner_c_end'
  if not d[2]:return d[1],'corner_d_end'
 return None,'additional_center'
def clip(poly,axis,bound,lower):
 out=[]
 for k,q in enumerate(poly):
  p=poly[k-1];iq=q[axis]>=bound if lower else q[axis]<bound;ip=p[axis]>=bound if lower else p[axis]<bound
  if iq!=ip:
   t=f32((bound-p[axis])/(q[axis]-p[axis]));v=[f32(p[j]+t*(q[j]-p[j])) for j in range(len(q))];v[axis]=bound;out.append(v)
  if iq:out.append(q)
 return out
def emission(indices,vertices,view):
 cx,cy,sx,sy=struct.unpack_from('<4f',view);near=struct.unpack_from('<f',view,0x108)[0];far=struct.unpack_from('<f',view,0x138)[0];rect=struct.unpack_from('<4f',view,0x1c)
 p=[list(vertices[i]) for i in reversed(indices)];depth=max(v[2] for v in p)
 p=clip(clip(p,2,near,True),2,far,False)
 if not p:return dict(accepted=False,return_value=0,clip_count=0,rejection='depth_clip',depth=depth)
 p=[[f32(v[0]/v[2]*sx+cx),f32(v[1]/v[2]*sy+cy),f32(1/v[2])] for v in p]
 for axis,bound,lower in [(0,rect[0],True),(0,rect[2],False),(1,rect[1],True),(1,rect[3],False)]:p=clip(p,axis,bound,lower)
 count=len(p)
 # Selected fixtures use initialized -300..4095 bins, so positive clip is accepted.
 accepted=bool(count) and depth>=-300 and round(depth+300)<=4096 and count<=32
 return dict(accepted=accepted,return_value=int(bool(count)),clip_count=count,rejection=None if accepted else 'screen_clip' if not count else 'bin_depth',depth=depth)
def walk(edges,leaves,vertices,view,light,ambient,attenuation,scale,numeric,high=0):
 vertices=list(vertices);result=[]
 def shade(plane,z):
  dot=-(plane[0]*light[0]+plane[1]*light[1]+plane[2]*light[2])
  return min(1.,dot*max(numeric.value(0x4be82c,'f'),min(1.,z*attenuation[1]+attenuation[0]))+ambient) if dot>=0 else ambient
 def band(s):return lowdouble((numeric.value(0x4be860,'d')-s)*scale+numeric.value(0x4faf18,'d'))&0x1f00
 for leaf,es in leaves:
  parts=[flatten(edges,es[2]),flatten(edges,es[1]),flatten(edges,es[3],True),flatten(edges,es[0],True)];loop=sum(parts,[]);center,selection=anchor(edges,es)
  if center is None:
   raise NotImplementedError('additional-center branch lacks an authenticated geometry fixture')
  closed=loop+[loop[0]];last=f32(vertices[loop[-1]][1]*f32(1/vertices[loop[-1]][2]));score=0;direction=0
  for i in closed:
   y=vertices[i][1]*f32(1/vertices[i][2]);rising=y>last;score+=-direction if rising else direction;direction=1 if rising else -1;last=f32(y)
  record=dict(leaf=leaf,boundary=loop,anchor=center,anchor_reason=selection,turn_score=score,turn_target=4-len(loop),whole_planes=[],shade_bands=[],attempts=[],filtered_triangles=[])
  def attempt(ix,kind,s):
   e=emission(ix,vertices,view);a=dict(indices=ix,kind=kind,shade=f32(s),**e);record['attempts'].append(a);return e['return_value']
  fallback='projected_y_turns'
  if score==4-len(loop):
   corners=[p[0] for p in parts];planes=[numeric.plane(vertices[corners[0]],vertices[corners[1]],vertices[corners[2]]),numeric.plane(vertices[corners[0]],vertices[corners[2]],vertices[corners[3]])];record['whole_planes']=planes
   fallback='corner_plane_facing'
   if all(p[3]<0 for p in planes):
    shades=[shade(p,vertices[loop[0]][2]) for p in planes];shades[0]=f32(shades[0]);bands=[band(s) for s in shades];record['shade_bands']=bands;fallback='shade_band_mismatch'
    if bands[0]==bands[1]:
     if attempt(loop,'whole',shades[0]):fallback=None
     else:fallback='whole_emitter_zero'
  record['fallback_reason']=fallback
  if fallback:
   # Compute all planes before any mutation of the in-place index array.
   fan=[([center,j,k],numeric.plane(vertices[center],vertices[j],vertices[k])) for j,k in zip(closed,closed[1:]) if j!=center and k!=center]
   for ix,p in fan:
    if p[3]<0:attempt(ix,'triangle',0. if high else shade(p,vertices[loop[0]][2]))
    else:record['filtered_triangles'].append(dict(indices=ix,plane=p,reason='plane_distance_nonnegative'))
  result.append(record)
 return result
