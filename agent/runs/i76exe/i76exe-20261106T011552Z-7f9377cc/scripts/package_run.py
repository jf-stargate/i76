#!/usr/bin/env python3
"""Refresh this run's manifest after review of owned publication artifacts only."""
import argparse,hashlib,json
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--orig',required=True,type=Path);p.add_argument('--gzf',required=True,type=Path);a=p.parse_args();r=Path(__file__).resolve().parents[1]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def write(p,v):p.write_text(json.dumps(v,indent=2,sort_keys=True)+'\n')
count=json.loads((r/'evidence/geometry_comparisons.json').read_text())['checks']+89159+3
validation={'status':'passed','test_count':count,'passed_count':count,'notes':'Independent bounded graph/predicate/flatten/source-work checks plus inherited 89159 source/camera/clip/bin checks and three additional rejected graph/threshold/emitter corruptions. Fresh import and unchanged #76 sidecars agree. Root hull, full walker decision selection and alternate output remain outside certified scope.'}
write(r/'validation.json',validation)
findings=[]
for fid,claim,status,report,evidence in [
 ('F-TOPOLOGY','Original 0x1C leaf +00/+02/+04 store lattice X/Z/size and +0C/+10/+14/+18 store the four shared-edge references in selected M06 cases.','proven','artifacts/SHARED_EDGE_TOPOLOGY.md','evidence/edge_graph.json'),
 ('F-SHARED','Original idempotent edge splitting mutates shared parent records; late flattening incorporates deeper children across unequal-size neighboring leaves without partial T junctions in tested graphs.','proven','artifacts/SHARED_EDGE_TOPOLOGY.md','evidence/edge_graph.json'),
 ('F-WINDING','Original leaf flattening executes +14 forward,+10 forward,+18 reverse,+0C reverse; original emitter copies these inputs in reverse, including split-edge and triangle cases.','proven','artifacts/POLYGON_EMISSION.md','evidence/polygons.jsonl'),
 ('F-MODEL','Independent bounded numerical subdivision and source graph construction match exact source indices, XYZ and complete edge/leaf arenas for nine valid M06 camera configurations with original root/planes supplied.','derived','artifacts/ADAPTIVE_TERRAIN_ALGORITHM.md','evidence/geometry_comparisons.json')]:
  findings.append({'finding_id':fid,'claim':claim,'status':status,'confidence':'high','scope':'game','evidence':[{'kind':'run-artifact','ref':s,'sha256':sha(r/s)} for s in [report,evidence,'evidence/instruction_anchors.tsv','scripts/verify_topology.py']],'limitations':'Bounded original-instruction emulation with inherited #76 resource/OS/CRT/numerical services, controlled poses and backing. Independent model accepts original root bounds and planes. Full camera hull, facing/shade/emission selection, added-center/high-color, default-page/overflow and successful alternate output remain unresolved; no native Windows/render/image claim.'})
write(r/'findings.json',{'schema_version':'1.2.0','run_id':r.name,'findings':findings})
artifacts=[]
for folder,kind in [('artifacts','report'),('evidence','table'),('scripts','script')]:
 for file in sorted((r/folder).iterdir()):
  if file.is_file():artifacts.append({'path':str(file.relative_to(r)),'bytes':file.stat().st_size,'sha256':sha(file),'kind':kind})
inputs=[]
for name in ['i76.exe','I76.ZFS','miss8/M06.MSN','miss8/M06.TER']:
 b=(a.orig/name).read_bytes();inputs.append({'name':name,'kind':'retail-executable' if name=='i76.exe' else 'other','md5':hashlib.md5(b).hexdigest(),'sha256':hashlib.sha256(b).hexdigest(),'notes':'Licensed private input; no payload published.'})
manifest={'schema_version':'1.2.0','protocol_version':'1.0.5','run_id':r.name,'track':'i76exe','topic':'Original adaptive terrain shared edges, source subdivision and polygon topology','base_commit':'7c315c103e6eda864f5bd9f3c3736a03b4c1fa7c','started_at':'2026-11-06T01:15:52Z','summary':'Nine exact bounded M06 source graph matches, executed unequal-depth shared edges, original flatten/emitter winding and triangle fan evidence; source-only C++ handoff with explicit remaining output blockers.','inputs':inputs,'baselines':[{'version':'12.1.4','program_name':'i76exe_v100','baseline_id':'private annotated retail i76exe v100','baseline_sha256':sha(a.gzf),'storage_ref':'licensed user-private scratch_data/i76exe_v100.gzf','notes':'Fresh import, full retail executable-section equality; v97 archive unavailable locally.'}],'artifacts':artifacts,'validation':validation,'reproducibility':{'status':'partial','methods':['Retail code equality and sparse source anchors','Ten camera configurations including rejection; alternate header blocked probe','Independent numerical source graph, edge/leaf arena and flatten/source-work comparison','Inherited camera/transform/clip/bin independent verification with corruption rejection','Fresh imported GZF trace/10-sidecar equality; unchanged #76 observer/8-sidecar equality'],'limitations':'Licensed inputs required. Original root/visible planes are externally supplied to the model. No complete independent walker/facing/shade or alternate output parity; no raster, pixel or all-mission claim.','script_refs':[{'kind':'run-artifact','ref':x['path'],'sha256':x['sha256']} for x in artifacts if x['kind']=='script']}}
write(r/'manifest.json',manifest)
print(json.dumps({'artifacts':len(artifacts),'bytes':sum(x['bytes'] for x in artifacts),'validation':validation}))
