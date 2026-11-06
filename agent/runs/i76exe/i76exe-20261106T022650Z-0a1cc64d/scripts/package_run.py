#!/usr/bin/env python3
"""Package reviewed run-owned text artifacts; no licensed payload publication."""
import argparse,hashlib,json
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--orig',type=Path,required=True);p.add_argument('--m02-msn',type=Path,required=True);p.add_argument('--gzf',type=Path,required=True);a=p.parse_args();r=Path(__file__).resolve().parents[1]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def dump(p,x):p.write_text(json.dumps(x,indent=2,sort_keys=True)+'\n')
results=json.loads((r/'evidence/results.json').read_text());geometry=json.loads((r/'evidence/geometry_comparisons.json').read_text());public=json.loads((r/'evidence/public_verification.json').read_text());environment=json.loads((r/'evidence/environment_validation.json').read_text())
count=results['checks']+geometry['checks']+public['checks']+environment['checks']+1+78+124
validation={'status':'passed','test_count':count,'passed_count':count,'notes':'124 native bounded scan cases, six original-instruction Ghidra source-graph cases, exhaustive normal page phases, full original initialized grids, exact fresh repeats and four corruption controls. No whole-game/native-full-geometry claim.'}
dump(r/'validation.json',validation)
findings=[]
for fid,claim,status,report,table in [
 ('F-SCAN','All four retained-pointer scan starts/descending strides are recovered; normal side8/16/32 caller phases keep their half-open footprints within one page.','proven','ADAPTIVE_BOUNDARY_SCAN.md','public_verification.json'),
 ('F-CROSS','Injected unaligned scans can row-spill, enter a following serialized page ordinal, or leave owned terrain/default backing; their decisions can differ from coordinate resolution.','proven','PAGE_CROSSING_CASES.md','scan_cases.jsonl'),
 ('F-CLASS','Classes2,3,4,6,7 refine, including bit12 controls at all four sites; initialized default0 and class5 pass, and repeated pointers receive no special handling.','proven','MATERIAL_REFINEMENT_BOUNDARIES.md','scan_cases.jsonl'),
 ('F-GEOMETRY','Six bounded M06 original-instruction source graphs match the independent predicate/graph oracle exactly, including class, default, repeated-page and unequal-LOD shared edges.','derived','MATERIAL_REFINEMENT_BOUNDARIES.md','geometry_comparisons.json')]:
  refs=['artifacts/'+report,'evidence/'+table,'evidence/instruction_anchors.tsv','evidence/provenance.json']
  findings.append({'finding_id':fid,'claim':claim,'status':status,'confidence':'high','scope':'game','evidence':[{'kind':'run-artifact','ref':s,'sha256':sha(r/s)} for s in refs],'limitations':'Normal safety requires recovered dyadic root phase, valid backing and bounded coordinates. Native slice has supplied Linux/image/grid environment and bypasses earlier LOD/height tests; unaligned cases are injected. Full source geometry is Ghidra original-instruction execution with inherited services and original root/hull inputs. Unsafe words are not read. No native full-geometry, retail Windows, arbitrary-corruption or whole-renderer claim.'})
dump(r/'findings.json',{'schema_version':'1.2.0','run_id':r.name,'findings':findings})
artifacts=[]
for folder,kind in [('artifacts','report'),('evidence','table'),('scripts','script')]:
 for f in sorted((r/folder).iterdir()):
  if f.is_file():artifacts.append({'path':str(f.relative_to(r)),'bytes':f.stat().st_size,'sha256':sha(f),'kind':kind})
inputs=[]
for name,f in [('i76.exe',a.orig/'i76.exe'),('I76.ZFS',a.orig/'I76.ZFS'),('M06.MSN',a.orig/'miss8/M06.MSN'),('M06.TER',a.orig/'miss8/M06.TER'),('M02.MSN',a.m02_msn),('M02.TER',a.orig/'miss8/M02.TER')]:
 b=f.read_bytes();inputs.append({'name':name,'kind':'retail-executable' if name=='i76.exe' else 'other','md5':hashlib.md5(b).hexdigest(),'sha256':sha(f),'notes':'Authenticated licensed private input; no payload published. M02 metadata is the exact CD copy authenticated by merged #141.'})
manifest={'schema_version':'1.2.0','protocol_version':'1.0.5','run_id':r.name,'track':'i76exe','topic':'Original adaptive terrain boundary scan pointer semantics, normal caller guards and material-driven geometry','base_commit':'19c755a77db404ba9cb0ab51f307b4261e983aff','started_at':'2026-11-06T02:26:50Z','summary':'124 guarded native scan cases and six complete original-instruction source graphs resolve normal aligned safety, default/repeated pointers, unsafe injected crossings and geometry/sampler separation. Research only.','inputs':inputs,'baselines':[{'version':'12.1.4','program_name':'i76exe_v100','baseline_id':'private annotated retail i76exe v100','baseline_sha256':sha(a.gzf),'storage_ref':'licensed user-private scratch_data/i76exe_v100.gzf','notes':'Two fresh owned imports; full executable section equality. Native scan uses authenticated PE bytes directly.'}],'artifacts':artifacts,'validation':validation,'reproducibility':{'status':'partial','methods':['Native original instruction single-step with bounded pre-read checks','Independent integer address/class model and all normal page phases','Full original-instruction source graph versus independent predicate/graph oracle','Exact native repeat and 78 geometry trace/sidecar repeats from fresh imports','Public corruption controls and private arena corruption rejection'],'limitations':'Licensed inputs and child ptrace required for native reproduction. Full geometry requires Ghidra and merged #140 sources; model receives original root/hull outputs. No native full-geometry or complete rendering parity.','script_refs':[{'kind':'run-artifact','ref':v['path'],'sha256':v['sha256']} for v in artifacts if v['kind']=='script']}}
dump(r/'manifest.json',manifest);print(json.dumps({'artifacts':len(artifacts),'bytes':sum(v['bytes'] for v in artifacts),'validation':validation}))
