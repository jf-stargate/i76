#!/usr/bin/env python3
"""Standalone source/matrix/projection/retired-store verifier, no Ghidra dependency."""
import argparse,csv,hashlib,importlib.util,json,math,struct,subprocess,sys,tempfile,copy
from pathlib import Path
sys.dont_write_bytecode=True
N=0
def ck(x,msg):
 global N
 N+=1
 if not x:raise AssertionError(msg)
def sha(b):return hashlib.sha256(b).hexdigest()
def f(r):return dict(x.split('=',1) for x in r['detail'].split(';') if '=' in x)
def un(b,fmt,off=0):return struct.unpack_from('<'+fmt,b,off)
def affine(v,b):
 r=un(b,'9f');t=un(b,'3d',40)
 return [sum(v[k]*r[k*3+j] for k in range(3))+t[j] for j in range(3)]
def close(a,b):return math.isclose(a,b,rel_tol=2e-6,abs_tol=2e-5)
def pe_slice(b,va,n):
 p=un(b,'I',60)[0];base=un(b,'I',p+52)[0];size=un(b,'H',p+20)[0]
 for i in range(un(b,'H',p+6)[0]):
  vs,r,sz,o=un(b,'4I',p+24+size+40*i+8)
  if r<=va-base<r+max(vs,sz):return b[o+va-base-r:o+va-base-r+n]
 raise AssertionError(hex(va))
EXTRA={'NATIVE_PREPARE_ENTER','NATIVE_PREPARE_RETURN','PREPARE_INSTRUCTION','PREPARE_DWORD','DISPATCH_CALL','FALLBACK_ORIGINAL_ENTER','FALLBACK_ORIGINAL_RETURN','ORIGINAL_FAILURE'}
def load_baseline(repo):
 old=repo/'agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe'
 spec=importlib.util.spec_from_file_location('accepted_verifier',old/'scripts/verify_integration.py');v=importlib.util.module_from_spec(spec);spec.loader.exec_module(v)
 return old,v
def collect(work,v):
 out={}
 for case in ['visible','behind','repeat']:
  rows=list(csv.DictReader((work/('native_'+case+'.tsv')).open(),delimiter='\t'))
  out[case]=[r for r in rows if not (r['kind'] in {'SERVICE_STRICMP','SERVICE_MEMCPY'} and 'producer=true' not in r['detail']) and (r['kind'] in v.SAFE|EXTRA or r['kind']=='RETURN' and r['pc'] in {'00493C50','004572B0','0048F9B0','00457FF0','0048FAC0'})]
 return out
def verify(data,dispatch):
 source=bytes.fromhex(data['source_vertex_excerpt']);ck(len(source)==192 and sha(source)=='31d85d852950cc079175612da560b3aa0054ac187d1cf8a3fd435e19fff55468','authenticated 16 retail vertex excerpt')
 rows=data['cases'];ck(rows['visible']==rows['repeat'],'fresh-project evidence byte repeat')
 tabs=dispatch['tables'];ck(tabs[0x101]['clip']=='0047C8D0' and tabs[1]['clip']=='0047BF00' and tabs[1]['draw']=='0047CE40','actual dispatch indices')
 ck(tabs[0x80]['clip']=='0047BF00' and tabs[0x80]['draw']=='0047D110' and tabs[0x15]['clip']=='0047C2F0' and tabs[0x15]['draw']=='00487EA0','distinct requested mode pairs')
 summary={}
 for case,rr in rows.items():
  def get(k):return [r for r in rr if r['kind']==k]
  ck(not get('ORIGINAL_FAILURE') and len(get('PRODUCER_COMPLETE'))==1,case+' completed original chronology')
  ck(len(get('CAMERA_RETURN'))==2 and len(get('HOST_WRITE_GUARD'))==1 and f(get('HOST_WRITE_GUARD')[0])['violations']=='0',case+' camera and host ownership guard')
  ck([r['pc'] for r in get('RETURN')][-3:]==['0048F9B0','00457FF0','0048FAC0'],case+' original arena producer consumer return')
  snaps={f(r)['phase']:f(r) for r in get('QUEUE_SNAPSHOT')};ck(snaps['produced']['camera']==snaps['consumed']['camera'],case+' sealed view')
  enters=get('NATIVE_PREPARE_ENTER');returns=get('NATIVE_PREPARE_RETURN')
  if case=='behind':
   ck(not enters and not get('POLYGON_WRAPPER') and not get('CONSUME_RECORD'), 'behind no polygon or consumer')
   ck(f(get('CULL_RESULT')[0])['eax']=='00000001','behind original rejection')
   summary[case]={'native_prepare_calls':0,'reason':'original visibility rejection'};continue
  ck(len(enters)==len(returns)==2,case+' two original prepare calls')
  produced=un(bytes.fromhex(snaps['produced']['bytes']),'17I');ck(produced[3]==6 and produced[7]==0x26100000 and produced[16]==0x5428a8,'original kind6 owner and registry')
  consumed=f(get('CONSUME_RECORD')[0]);ck(consumed['record']=='38015540' and consumed['view']=='004C2730','same producer record/view consumed')
  gs=f(get('GEO_SOURCE')[0]);ck(gs['owner'] in gs['rootChildren'].split(',') and gs['root']=='26100000' and gs['vertices_sha256']==sha(source),'GEO child and vertex identity')
  world=bytes.fromhex(gs['matrix']);camera=bytes.fromhex(snaps['produced']['camera']);view=camera[0x40:0x80]
  transformed=bytes.fromhex(f(get('GEO_BUILD_RETURN')[0])['transformedVertices'])
  for i in range(16):
   expected=affine(affine(un(source,'3f',i*12),world),view);actual=un(transformed,'3f',i*12)
   ck(all(close(a,b) for a,b in zip(expected,actual)),case+' independent source/world/view vertex '+str(i))
  outs=[f(r)['vertices'] for r in get('GEO_OUTPUT') if f(r)['count']=='4'];polys=[f(r) for r in get('POLYGON_WRAPPER') if f(r)['kind']=='6']
  ck(sorted(outs)==sorted(p['vertices'] for p in polys),'original GEO outputs reach wrapper unchanged')
  ck([f(r)['src'] for r in enters]==[p['vertices'] for p in polys],'wrapper source is original callback source')
  projected=[]
  for k,(en,re) in enumerate(zip(enters,returns)):
   a,b=f(en),f(re);src=bytes.fromhex(a['src']);dst=bytes.fromhex(b['dst']);before=bytes.fromhex(a['dst']);params=un(bytes.fromhex(a['viewBytes']),'4f')
   ck(a['viewBytes']==snaps['produced']['camera'] and a['view']=='004C2730','callback uses persistent view')
   ck(a['flags']=='00000101' and a['count']=='4' and a['kind']=='6' and en['pc']=='0047C8D0','callback exact flags and entry')
   ck(re['pc']==a['return']=='004720AF' and b['eax']=='00000004' and a['src']==b['src'],'original return count and unchanged source')
   for i in range(4):
    xyz=un(src,'3f',24*i);matches=[j for j in range(16) if src[24*i:24*i+12]==transformed[12*j:12*j+12]];ck(bool(matches),'callback XYZ belongs to actual original transformed GEO vertex')
    original=un(source,'3f',12*matches[0]);expected_xyz=affine(affine(original,world),view)
    ck(all(close(a,b) for a,b in zip(xyz,expected_xyz)),'independent source callback coordinates')
    x,y,z=xyz;c0,c1,sx,sy=params;q=un(bytes.fromhex(dispatch['constant_004be764']),'f')[0]/z
    expected=[x*q*sx+c0,q*sy*y+c1,q];actual=un(dst,'3f',24*i)
    ck(all(close(a,b) for a,b in zip(actual,expected)),'independently recomputed screen XY and reciprocal depth')
    # A second oracle uses original GEO coordinates and measured affine parameters end-to-end.
    x0,y0,z0=expected_xyz;ck(all(close(a,b) for a,b in zip(actual,[x0/z0*sx+c0,y0/z0*sy+c1,1/z0])),'source-to-screen independent result')
    ck(dst[24*i+20:24*i+24]==src[24*i+20:24*i+24],'last attribute copied exactly')
    ck(dst[24*i+12:24*i+20]==before[24*i+12:24*i+20],'unused attributes untouched, not initialized UV')
   # Replay the actual retired original stores, reject missing/forged effects.
   start=rr.index(en);end=rr.index(re);state=bytearray(before);base=int(a['dstPtr'],16)
   for r in rr[start:end]:
    if r['kind']=='PREPARE_DWORD':
     d=f(r);off=int(d['address'],16)-base;ck(r['pc'] in {'0047C910','0047C91C','0047C920','0047C926'},'retail writer PC')
     ck(state[off:off+4].hex()==d['before'],'retired prepare store before');state[off:off+4]=bytes.fromhex(d['after'])
   ck(state==dst,'original stores reconstruct full output memory')
   steps=[r['pc'] for r in rr[start:end] if r['kind']=='PREPARE_INSTRUCTION'];ck(steps.count('0047C910')==4 and steps.count('0047C920')==4 and steps[-1]=='0047C92F','actual original projection loop and RET')
   projected.append([list(un(dst,'3f',24*i)) for i in range(4)])
  calls=[(r['pc'],f(r)['index'],f(r)['target']) for r in get('DISPATCH_CALL')];ck(calls==[('004720A8','00000101','0047C8D0'),('00472145','00000001','0047BF00'),('004721AC','00000001','0047CE40')]*2+[('004720A8','00000080','0047BF00'),('004721AC','00000080','0047D110')],'exact wrapper initial, fallback and draw dispatch chronology')
  fe,fr=get('FALLBACK_ORIGINAL_ENTER'),get('FALLBACK_ORIGINAL_RETURN');ck(len(fe)==len(fr)==2,'unsubstituted baseline fallback observed')
  draws=get('SERVICE_DRAW');ck(len(draws)==3,'all draw bodies explicitly substituted')
  for i,(a,b) in enumerate(zip(fe,fr)):
   a,b=f(a),f(b);ck(a['src']==b['src'] and b['eax']=='00000004','original fallback preserves source and returns four')
   ck(b['dst']==f(draws[i])['vertices'],'subsequent substituted draw receives original fallback output')
   prep=bytes.fromhex(f(returns[i])['dst']);fallback=bytes.fromhex(b['dst'])
   ck(all(prep[j*24:j*24+12]==fallback[j*24:j*24+12] for j in range(4)),'fallback retains projected XYZ, no observed new intersection vertex')
   ck(a['viewport'].split(',')[:2]==['00000000','00000000'],'zero descriptor extent explains wrapper fallback')
  summary[case]={'native_prepare_calls':2,'projected_vertices':projected,'fallback_calls':2,'draw':'substituted','clipping_intersections':'not demonstrated'}
 return summary

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--run',type=Path,default=Path(__file__).resolve().parents[1]);ap.add_argument('--source-repo',type=Path,required=True)
 for k in ['private','exe','gzf','zfs']:ap.add_argument('--'+k,type=Path)
 ap.add_argument('--evidence',type=Path);ap.add_argument('--emit',action='store_true');ap.add_argument('--negative-controls',action='store_true');a=ap.parse_args();old,v=load_baseline(a.source_repo);ev=a.run/'evidence'
 data=json.loads((a.evidence or ev/'polygon_events.json').read_text()) if not a.emit else {'source_vertex_excerpt':(a.private/'fixtures/xb11bdym.geo').read_bytes()[36:228].hex(),'cases':collect(a.private,v)}
 dispatch=json.loads((ev/'retail_dispatch.json').read_text())
 if a.private:
  ck(data['cases']==collect(a.private,v),'exact regenerated trace allowlist')
  baseline=v.collect(a.private)
  for case in ['visible','behind','repeat']:
   accepted=[{k:r[k] for k in ['scenario','kind','pc','detail']} for r in baseline if r['case']==case]
   measured=data['cases'][case]
   def prefix(rows):
    end=next(i for i,r in enumerate(rows) if r['kind']=='QUEUE_SNAPSHOT' and f(r)['phase']=='produced')
    return rows[:end+1]
   ck(prefix(accepted)==prefix(measured),'exact accepted camera/visibility/queue chronology '+case)

  ck(data['source_vertex_excerpt']==(a.private/'fixtures/xb11bdym.geo').read_bytes()[36:228].hex(),'source GEO original bytes')
  for key,digest in {'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'}.items():ck(sha(getattr(a,key).read_bytes())==digest,'private '+key+' identity')
  pe=a.exe.read_bytes()
  for x in dispatch['anchors']:ck(pe_slice(pe,int(x['va'],16),len(bytes.fromhex(x['hex']))).hex()==x['hex'],'retail instruction '+x['va'])
  for x in dispatch['tables']:
   for base,key in [(0x4f9538,'clip'),(0x4f8d38,'draw')]:ck(un(pe_slice(pe,base+4*x['index'],4),'I')[0]==int(x[key],16),'retail dispatch cell')
  ck((a.private/'native_visible.tsv').read_bytes()==(a.private/'native_repeat.tsv').read_bytes(),'full private fresh-project byte repeat')
  for case in ['visible','behind','repeat']:
   log=(a.private/('native_'+case+'.log')).read_text();ck('ERROR' not in log and len([l for l in log.splitlines() if 'Uninitialized' in l])==1 and '004461e0' in log,'only inherited optional-name warning')
 summary=verify(data,dispatch)
 if a.emit:
  (ev/'polygon_events.json').write_text(json.dumps(data,indent=2)+'\n');(ev/'numerical_results.json').write_text(json.dumps(summary,indent=2)+'\n')
 else:ck(json.loads((ev/'numerical_results.json').read_text())==summary,'derived numerical artifact')
 if a.negative_controls:
  rejected=[]
  for label in ['projected_x','source_geo','return_count','retired_store']:
   bad=copy.deepcopy(data)
   if label=='source_geo':bad['source_vertex_excerpt']='00'+bad['source_vertex_excerpt'][2:]
   else:
    for case in ['visible','repeat']:
     kind={'projected_x':'NATIVE_PREPARE_RETURN','return_count':'NATIVE_PREPARE_RETURN','retired_store':'PREPARE_DWORD'}[label];r=next(x for x in bad['cases'][case] if x['kind']==kind);d=f(r)
     if label=='projected_x':r['detail']=r['detail'].replace('dst='+d['dst'],'dst=00000000'+d['dst'][8:])
     elif label=='return_count':r['detail']=r['detail'].replace('eax=00000004','eax=00000003')
     else:r['detail']=r['detail'].replace('after='+d['after'],'after=00000000')
   try:verify(bad,dispatch)
   except AssertionError as error:rejected.append({'mutation':label,'rejected':True,'reason':str(error)})
   else:raise AssertionError('corruption accepted '+label)
  if a.emit:
   (ev/'corrupted_sample.json').write_text(json.dumps(bad,indent=2)+'\n');(ev/'negative_controls.json').write_text(json.dumps(rejected,indent=2)+'\n')
  print(json.dumps({'negative_controls':rejected}))
 print(json.dumps({'status':'passed','assertions':N,'source_verification':bool(a.private),'cases':3}))
if __name__=='__main__':main()
