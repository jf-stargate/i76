#!/usr/bin/env python3
"""Analytical model of ONE native grading loop, not original-code execution.

The rectangles supplied are the already rotated/bounded integer extrema. See
original I76EDIT.EXE 0040A8CA..0040AA8B for the scan and stamping semantics.
"""
import json
from dataclasses import dataclass
SENTINEL = 0x8000
@dataclass(frozen=True)
class Object:
    name: str
    kind: int
    bounds: tuple[int,int,int,int]
    anchor_height: int

def footprint(o):
    min_x,min_y,max_x,max_y=o.bounds
    assert min_x<=max_x and min_y<=max_y
    min_x = min_x if min_x != 0 else 1
    min_y = min_y if min_y != 0 else 1
    for x in range(min_x-1, min_x+(max_x-o.bounds[0])+1):
        for y in range(min_y+1, min_y+(max_y-o.bounds[1])+3):
            yield x,y

def grade(objects, work_height=None, material=None):
    work_height=dict(work_height or {})
    material=dict(material or {})
    trace=[]
    for o in objects:
        assert o.kind in (2,3,0x50,0x51,0x52,0x53)
        points=list(footprint(o))
        hits=[(x,y,work_height.get((x,y),SENTINEL)) for x,y in points if work_height.get((x,y),SENTINEL)!=SENTINEL]
        if hits:
            sx,sy,selected=hits[0]
            origin=f'first valid plane1 sample at ({sx},{sy})'
        else:
            selected=o.anchor_height if o.anchor_height!=0 else 1
            origin='anchor plane0 fallback (0 promotes to 1)'
        index=6 if o.kind in (0x50,0x51) else 7 if o.kind in (0x52,0x53) else None
        for p in points:
            work_height[p]=selected
            if index is not None:material[p]=index
        trace.append(dict(object=o.name,type=o.kind,seed=selected,source=origin,footprint_cells=len(points),material=index))
    return work_height,material,trace

def check():
    A=Object('A',0x50,(10,10,12,12),100)
    B=Object('B',0x52,(12,11,14,13),300)
    assert set(footprint(A)) & set(footprint(B))
    for first,second in ((A,B),(B,A)):
        h,m,t=grade([first,second]);shared=sorted(set(footprint(A))&set(footprint(B)))
        assert t[1]['seed']==first.anchor_height,t
        assert all(h[p]==first.anchor_height for p in shared)
        assert all(m[p]==(7 if second.kind==0x52 else 6) for p in shared)
    C=Object('C',0x53,(14,12,16,14),600)
    assert set(footprint(A)).isdisjoint(set(footprint(C)))
    assert set(footprint(B))&set(footprint(C))
    h,m,t=grade([A,B,C]);assert t[-1]['seed']==100
    h,m,t=grade([A],{(9,11):700});assert t[0]['seed']==700
    h,m,t=grade([Object('zero',0x51,(5,5,7,7),0)]);assert t[0]['seed']==1
    h,m,t=grade([Object('unset',0x51,(5,5,7,7),SENTINEL)]);assert t[0]['seed']==SENTINEL and all(v==6 for v in m.values())
    h,m,t=grade([Object('no-surface',2,(5,5,7,7),100)],material={(4,6):3});assert m[(4,6)]==3 and t[0]['material']==None
    initial={0:0,1:0,2:90,3:0}; zone0=[0,1];zone1=[2,3]
    def mean_cell(values,i):return sum(values[j] for j in (i-1,i,i+1) if j in values)//len([j for j in (i-1,i,i+1) if j in values])
    global_pass={i:mean_cell(initial,i) for i in initial}
    stage=dict(initial)
    for zone in [zone0,zone1]:
        changes={i:mean_cell(stage,i) for i in zone}
        stage.update(changes)
    assert stage != global_pass
    return {'analytic_not_original_code_execution':True,'scenarios_passed':7,
      'A_then_B':grade([A,B])[2],'B_then_A':grade([B,A])[2],
      'propagation_A_B_C':grade([A,B,C])[2],
      'preseed_first_valid':grade([A],{(9,11):700})[2],
      'cross_zone_schedule_illustrative_not_native_numeric':{'global_simultaneous':global_pass,'zone_sequential':stage}}
if __name__=='__main__':print(json.dumps(check(),indent=2))
