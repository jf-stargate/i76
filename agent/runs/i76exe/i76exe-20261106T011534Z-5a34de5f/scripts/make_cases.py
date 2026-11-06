#!/usr/bin/env python3
"""Choose bounded locations from a private retail ZMAP, independent of emulator."""
import argparse,pathlib,itertools,json
p=argparse.ArgumentParser();p.add_argument('msn',type=pathlib.Path);p.add_argument('out',type=pathlib.Path);a=p.parse_args()
b=a.msn.read_bytes();o=b.index(b'ZMAP');zm=b[o+9:o+6409];cases={}
def add(label,kind,x,z):cases[(kind,x,z)]=(label,kind,x,z)
anchors={}
for z in range(79):
 for x in range(79):
  q=[zm[z*80+x],zm[z*80+x+1],zm[(z+1)*80+x],zm[(z+1)*80+x+1]]
  if q[0]!=255 and q[0]==q[1]:anchors.setdefault('repeated',(x,z))
  if all(v!=255 for v in q):
   if q[0]!=q[1]:anchors.setdefault('different_x',(x,z))
   if q[0]!=q[2]:anchors.setdefault('different_z',(x,z))
   if len(set(q))>=3:anchors.setdefault('diagonal',(x,z))
   if q[0]==q[1]:anchors.setdefault('repeated',(x,z))
  if q[0]==255:anchors.setdefault('unmapped',(x,z))
  if q[0]!=255:anchors.setdefault('interior',(x,z))
for label,(px,pz) in anchors.items():
 for lx,lz in [(17,29),(126,33),(127,33),(128,33),(129,33),(33,126),(33,127),(33,128),(33,129),*itertools.product([126,127,128,129],repeat=2)]:
  x,z=px*128+lx,pz*128+lz;add(label,'sample',x,z)
 for lx,lz in [(17,29),(127,33),(33,127),(127,127),(128,33),(33,128),(128,128)]:
  for dx,dz in [(0,0),(-.001,-.001),(.001,.001),(2.5,1.25),(4.999,4.999)]:add(label,'world',(px*128+lx)*5+dx,(pz*128+lz)*5+dz)
px,pz=anchors['interior'];ox,oz=px*128,pz*128
for dx,dz in [(-1,0),(0,-1),(-1,-1),(0,0),(1,0),(0,1)]:add('active_default','sample',ox+dx,oz+dz)
for dx,dz in [(-.001,0),(.001,0),(0,-.001),(0,.001),(-.001,-.001),(.001,.001),(-2.5,-2.5)]:add('active_default','world',ox*5+dx,oz*5+dz)
for x,z in [(0,0),(-1,0),(0,-1),(-1,-1),(-128,129),(-3072,0),(-3073,0),(10239,10239),(10240,10240),(13311,13311),(13312,13311),(13312,0),(0,13312)]:add('grid_extent','sample',x,z)
for x,z in [(-2.502,0),(-2.5013,0),(-2.5012,0),(-2.5001,0),(51202.498,0),(51202.501,0),(-2.50001,0),(-2.5,0),(-2.49999,0),(-.001,0),(0,-.001),(-.001,-.001),(0,0),(.001,.001),(2.5,0),(7.5,0),(51200,51200),(51202.49,0),(51202.5,0),(51202.51,0),(51205,0),(-5,0),(0,-5)]:add('admission','world',x,z)
a.out.write_text(''.join(f'{i:04d}_{v[0]}\t{v[1]}\t{v[2]:.17g}\t{v[3]:.17g}\n' for i,v in enumerate(cases.values())))
print(json.dumps({'cases':len(cases),'anchors':anchors}))
