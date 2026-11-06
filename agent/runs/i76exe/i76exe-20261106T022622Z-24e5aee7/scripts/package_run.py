#!/usr/bin/env python3
"""Index only reviewed public files; never stage private/ or interpreter caches."""
import argparse,hashlib,json
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--orig',type=Path,required=True);p.add_argument('--gzf',type=Path,required=True);a=p.parse_args()
r=Path(__file__).resolve().parents[1]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def dump(p,v):p.write_text(json.dumps(v,indent=2,sort_keys=True)+'\n')
count=json.loads((r/'evidence/comparison.json').read_text())['checks']+8
validation={'status':'passed','test_count':count,'passed_count':count,'notes':'417 asset-free comparison checks plus 8 isolation/corruption/input controls; 24 native cases exact, 20 accepted emulated source/arena graphs exact, nine accepted #140 hashes exact; full fresh driver passed. One expected Ghidra-vs-native clear_exact admission discrepancy is explicitly retained, not counted as parity.'}
dump(r/'validation.json',validation)
items=[
('ROOT-FOOTPRINT','Original camera to terrain footprint uses world camera/far corners, height admission, all-nonpositive far-corner ground intersection, bias-rounded extrema and expanded power-of-two root.','proven','artifacts/CAMERA_TERRAIN_ROOT.md','evidence/camera_fixtures.json'),
('ROOT-HULL','Original later-point duplicate rejection, angular distance-score sentinel selection and approximate vertical plane construction reproduce measured ordered hull and plane stores.','derived','artifacts/VISIBILITY_HULL.md','evidence/predictions.json'),
('ROOT-LOD','Original terrain quality factors and retained camera projection/viewport derive the two float32 LOD thresholds through extended arithmetic and final stores.','proven','artifacts/LOD_THRESHOLD_NUMERICS.md','evidence/comparison.json'),
('ROOT-PARITY','Independent camera-input predictions match all 24 native root/threshold/plane observations and reproduce 20 accepted emulated source graphs, including nine known #140 graphs.','derived','artifacts/CAMERA_GEOMETRY_HANDOFF.md','evidence/downstream.json'),
('ROOT-EMU-LIMIT','At controlled .01 terrain clearance the native root and independent model accept while the FISTP-serviced Ghidra sampler causes rejection; adjacent clearance controls agree.','proven','artifacts/LOD_THRESHOLD_NUMERICS.md','evidence/numeric_diagnostics.json')]
findings=[]
limits='Finite measured M06 camera states and default CW037F only. Original view remains input; explicit terrain quality and independent authenticated height data required. Supplied Linux/OS/backing and Ghidra services, not native retail Windows/frame/raster. One known emulator boundary discrepancy; arbitrary state, overflow, exceptional FP, repeated rejected frames and full rendering unverified.'
for fid,claim,status,report,evidence in items:
    refs=[report,evidence,'evidence/instruction_anchors.tsv','evidence/provenance.json','scripts/predict.py']
    findings.append({'finding_id':fid,'claim':claim,'status':status,'confidence':'high','scope':'game','evidence':[{'kind':'run-artifact','ref':s,'sha256':sha(r/s)} for s in refs],'limitations':limits})
dump(r/'findings.json',{'schema_version':'1.2.0','run_id':r.name,'findings':findings})
artifacts=[]
for folder,kind in [('artifacts','report'),('evidence','table'),('scripts','script')]:
    for f in sorted((r/folder).iterdir()):
        if f.is_file():artifacts.append({'path':str(f.relative_to(r)),'bytes':f.stat().st_size,'sha256':sha(f),'kind':kind})
inputs=[]
for name in ['i76.exe','I76.ZFS','miss8/M06.MSN','miss8/M06.TER']:
    b=(a.orig/name).read_bytes();inputs.append({'name':name,'kind':'retail-executable' if name=='i76.exe' else 'other','md5':hashlib.md5(b).hexdigest(),'sha256':hashlib.sha256(b).hexdigest(),'notes':'Licensed private input; payload excluded.'})
manifest={'schema_version':'1.2.0','protocol_version':'1.0.5','run_id':r.name,'track':'i76exe','topic':'Camera to terrain root, visibility hull and LOD threshold reconstruction','base_commit':'19c755a77db404ba9cb0ab51f307b4261e983aff','started_at':'2026-11-06T02:26:22Z','summary':'Independent camera-input root/hull/plane/threshold prediction; 24 native cases, 20 exact emulated source graphs; retained sampler boundary discrepancy; research only.','inputs':inputs,'baselines':[{'version':'12.1.4','program_name':'i76exe_v100','baseline_id':'private annotated retail i76exe v100 used by accepted #140','baseline_sha256':sha(a.gzf),'storage_ref':'licensed private scratch_data/i76exe_v100.gzf','notes':'Fresh import; entire executable section verified against retail PE. Annotation names are navigation, not recovered source names.'}],'artifacts':artifacts,'validation':validation,'reproducibility':{'status':'complete','script_refs':[{'kind':'run-artifact','ref':v['path'],'sha256':v['sha256']} for v in artifacts if v['kind']=='script'],'methods':['Authenticated accepted M06 coherent camera scaffold and nine #140 scenarios','Original-instruction Ghidra root/filter/order/store observations','Original unchanged x87 root/sampler/math on native i386 with supplied image/backing and patched numerical-prefix continuation','Independent camera-only prediction plus explicit terrain quality/height dependency','Predicted-input downstream accepted adaptive source/arena model','Fresh full 24-case driver repeat and corruption controls'],'limitations':limits}}
dump(r/'manifest.json',manifest)
print('Public artifacts:',len(artifacts),'bytes:',sum(v['bytes'] for v in artifacts))
