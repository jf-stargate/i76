#!/usr/bin/env python3
"""Seven illustrative branch/scheduling cases, NOT actual original editor execution."""
from dataclasses import dataclass
S=0x8000
@dataclass(frozen=True)
class O:
 name:str
 kind:int
 ext:tuple
 origin_height:int
def footprint(o):
 x0,z0,x1,z1=o.ext
 x=x0 or 1;z=z0 or 1
 return [(a,b) for a in range(x-1,x+x1-x0+1) for b in range(z+1,z+z1-z0+3)]
def grade(objects,height=None,material=None):
 h=dict(height or {});m=dict(material or {});trace=[]
 for o in objects:
  points=footprint(o)
  found=[h[p] for p in points if p in h and h[p]!=S]
  value=found[0] if found else (o.origin_height or 1)
  surface=6 if o.kind in (80,81) else 7 if o.kind in (82,83) else None
  for p in points:
   h[p]=value
   if surface is not None:m[p]=surface
  trace.append((o.name,value,surface))
 return h,m,trace
def test():
 a=O('A',80,(10,10,12,12),100);b=O('B',82,(12,11,14,13),300);c=O('C',83,(14,12,16,14),600)
 assert len(footprint(a))==16 and footprint(a)[0]==(9,11)
 h,m,t=grade([a,b]);assert t[-1][1]==100 and all(m[x]==7 for x in set(footprint(a))&set(footprint(b)))
 h,m,t=grade([b,a]);assert t[-1][1]==300 and all(m[x]==6 for x in set(footprint(a))&set(footprint(b)))
 assert not(set(footprint(a))&set(footprint(c)))
 h,m,t=grade([a,b,c]);assert t[-1][1]==100
 assert grade([a],{(9,11):700})[2][0][1]==700
 assert grade([O('zero',81,(5,5,7,7),0)])[2][0][1]==1
 assert grade([O('heightonly',2,(5,5,7,7),100)],material={(4,6):3})[1][(4,6)]==3
 initial={0:0,1:0,2:90,3:0}
 def mean(v,i):
  xs=[v[j] for j in (i-1,i,i+1) if j in v]
  return sum(xs)//len(xs)
 sync={i:mean(initial,i) for i in initial};stage=dict(initial)
 for ids in ((0,1),(2,3)):
  batch={i:mean(stage,i) for i in ids};stage.update(batch)
 assert stage!=sync
 return {'test_count':7,'passed_count':7,'original_code_executed':False,'illustrative_global':sync,'illustrative_zone_order':stage}
if __name__=='__main__':
 import json
 print(json.dumps(test(),indent=2))
