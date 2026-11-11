#!/usr/bin/env python3
"""Independent #140 graph/predicate oracle, with bounded scan/default semantics."""
import argparse,collections,hashlib,importlib.util,json,struct,sys
from pathlib import Path
from scan_model import predict,resolve,read
sys.dont_write_bytecode=True
r=Path(__file__).resolve().parents[1];prior=r.parent/'i76exe-20261106T011552Z-7f9377cc'
spec=importlib.util.spec_from_file_location('topology',prior/'scripts/verify_topology.py');t=importlib.util.module_from_spec(spec);spec.loader.exec_module(t)
def dump(p,x):p.write_text(json.dumps(x,indent=2,sort_keys=True)+'\n')
def sha(b):return hashlib.sha256(b).hexdigest()
def main():
 p=argparse.ArgumentParser();p.add_argument('--cases',type=Path,required=True);p.add_argument('--emit',type=Path,required=True);p.add_argument('--corrupt-arena',action='store_true');a=p.parse_args();checks=0;summaries={};details=[]
 def ck(b,msg):
  nonlocal checks
  checks+=1
  if not b:raise AssertionError(msg)
 for f in sorted(a.cases.glob('*.tsv')):
  case=f.stem;rs=t.rows(f);by=collections.defaultdict(list)
  for row in rs:by[row['kind']].append(row)
  ck(not by['BLOCKER'] and len(by['COHERENT_COMPLETE'])==1,'complete original geometry execution')
  msn=Path(str(f)+'.input.msn').read_bytes();ter=Path(str(f)+'.input.ter').read_bytes();at=msn.index(b'ZMAP');zm=msn[at+9:at+6409]
  def sample(x,z):
   address=resolve(zm,x,z);w=read(ter,address) if address is not None else None;ck(w is not None,'bounded ordinary vertex read');return w
  predicted_material=[];building=True
  def special(x,z,size):
   raw=predict(zm,ter,x,z,size);coordinate=predict(zm,ter,x,z,size,True)
   ck(raw==coordinate,'normal aligned scans exactly equal per-coordinate addresses/words/order')
   ck(raw['outcome']!='unsafe','safe original scan')
   if building:predicted_material.extend(raw['reads'])
   return raw['outcome']=='split'
  out=by['OUTPUT'][0]['d'];bounds=t.words(out['bounds']);x,z,ex=bounds[:3];side=1<<ex
  seeds=[(float(X),float(sample(X,Z)&4095),float(Z)) for X,Z in [(x,z),(x+side,z),(x+side,z+side),(x,z+side)]]
  lod=by['LOD_INPUTS'][0]['d'];thresholds=struct.unpack('<2f',struct.pack('<2I',*t.words(lod['thresholds'])));cam=struct.unpack('<3f',struct.pack('<3I',*t.words(lod['cameraXZ'])));pb=t.words(lod['planes']);planes=list(struct.iter_unpack('<4fd',struct.pack('<'+'I'*len(pb),*pb)))
  model=t.Model(seeds,sample);root=[model.edge(3,2),model.edge(0,1),model.edge(1,2),model.edge(0,3)]
  model.quad((root[3],root[2],root[1],root[0]),lambda m,es:t.original_predicate(m,es,thresholds,cam,planes,special)[0])
  building=False
  original_vertices=Path(str(f)+'.pre.bin').read_bytes();original_arena=Path(str(f)+'.source-arena.bin').read_bytes()
  if a.corrupt_arena:original_arena=bytes([original_arena[0]^1])+original_arena[1:]
  ck(model.v==t.floats(original_vertices),'exact original XYZ/index sequence');ck(model.binary()==original_arena,'exact original complete interleaved edge/leaf arena')
  ds={row['d']['id']:row['d'] for row in by['DECISION']};reasons=collections.Counter();decisions=[];last={};terminal={}
  for row in rs:
   if row['kind']=='LOD_BRANCH':last[row['d']['frame']]={'pc':row['pc'],'next':row['d']['next']}
   if row['kind']=='DECISION':terminal[row['d']['id']]=last.get(row['d']['frame'],{})
  for row in by['QUAD']:
   q=row['d'];outcome,reason=t.original_predicate(model,t.words(q['edges']),thresholds,cam,planes,special)
   ck(outcome==ds[q['id']]['outcome'],'exact original branch decision');reasons[reason]+=1
   es=t.words(q['edges']);A=model.v[model.edges[es[2]][0]];O=model.v[model.edges[es[3]][1]]
   decisions.append({'quad':int(q['id']),'origin':[int(A[0]),int(A[2])],'size':int(O[0]-A[0]),'original':ds[q['id']]['outcome'],'predicted':outcome,'reason':reason,'original_last_branch':terminal[q['id']]})
  flattened={int(row['d']['leaf'],16):t.words(row['d']['indices']) for row in by['FLATTENED']};incidence=collections.defaultdict(list);leaves=[]
  for leaf,rec in model.leaves:
   loop=model.loop(rec[4:]);ck(flattened[leaf]==loop,'exact original polygon boundary loop');leaves.append(rec[:3]+[loop])
   for i,j in zip(loop,loop[1:]+loop[:1]):incidence[tuple(sorted((i,j)))].append([i,j,rec[2]])
  shared=[v for v in incidence.values() if len(v)==2];unequal=[v for v in shared if v[0][2]!=v[1][2]]
  for pair in shared:ck(pair[0][:2]==pair[1][:2][::-1],'shared edges exact opposite indices')
  # Coordinate overlap test detects partial T junctions, including unequal LOD boundaries.
  segments=[(i,j) for i,j in incidence]
  for k,(ia,ib) in enumerate(segments):
   A,B=model.v[ia],model.v[ib]
   for ic,id in segments[k+1:]:
    C,D=model.v[ic],model.v[id];axis=2 if A[0]==B[0]==C[0]==D[0] else 0 if A[2]==B[2]==C[2]==D[2] else None
    if axis is not None:ck(min(max(A[axis],B[axis]),max(C[axis],D[axis]))<=max(min(A[axis],B[axis]),min(C[axis],D[axis])),'no partial shared-boundary overlap')
  material=[]
  for row in by['MATERIAL_PREDICATE_READ']:
   d=row['d'];address=int(d['address'],16);word=int(d['word'],16);ck(read(ter,address)==word,'exact original scan packed word');material.append({'pc':row['pc'],'address':d['address'],'word':d['word']})
  ck([(int(v['pc'],16),int(v['address'],16),int(v['word'],16)) for v in material]==[(v['pc'],v['address'],v['word']) for v in predicted_material],'complete original material read sequence equals independent model')
  summaries[case]={'vertices':len(model.v),'edges':len(model.edges),'leaves':len(model.leaves),'source_sha256':sha(original_vertices),'arena_sha256':sha(original_arena),'exact_graph_equal':True,'every_decision_equal':True,'every_flattened_loop_equal':True,'per_coordinate_scans_equal':True,'shared_segments':len(shared),'unequal_lod_segments':len(unequal),'material_reads':len(material),'reasons':dict(reasons),'msn_sha256':sha(msn),'ter_sha256':sha(ter),'emitter_attempts':len(by['EMITTER_ENTER']),'scan_max_size':32,'root':bounds[:3]}
  details.append({'case':case,'decisions':decisions,'leaf_regions_and_loops':leaves,'selected_material_reads':material[:32]})
 ck(summaries['retail']['source_sha256']==json.loads((prior/'evidence/geometry_comparisons.json').read_text())['scenarios']['primary']['source_sha256'],'unchanged original retail fixture matches accepted #140')
 ck(summaries['clear']['arena_sha256']==summaries['class5']['arena_sha256'],'class5 does not refine')
 ck(summaries['clear']['arena_sha256']!=summaries['class2']['arena_sha256'],'class2 changes original topology')
 a.emit.mkdir(parents=True,exist_ok=True);dump(a.emit/'geometry_comparisons.json',{'status':'passed','checks':checks,'scenarios':summaries,'scope':'Original-instruction Ghidra geometry with #140 services; independent graph/predicate. Original root hull inputs supplied, no raster parity claim.'});dump(a.emit/'geometry_details.json',details)
 print(json.dumps({'checks':checks,'scenarios':summaries},indent=2))
if __name__=='__main__':main()
