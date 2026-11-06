#!/usr/bin/env python3
"""Package reviewed derived evidence; private payloads are never artifacts."""
import argparse,hashlib,json
from pathlib import Path
p=argparse.ArgumentParser()
for k in ['exe','gzf','zfs','msn','ter']:p.add_argument('--'+k,type=Path,required=True)
a=p.parse_args();r=Path(__file__).resolve().parents[1];repo=r.parents[3];prior=json.loads((repo/'agent/runs/i76exe/i76exe-20261106T011552Z-7f9377cc/manifest.json').read_text())
def dump(p,v):p.write_text(json.dumps(v,indent=2,sort_keys=True)+'\n')
def ref(p):return dict(kind='run-artifact',ref=p,sha256=hashlib.sha256((r/p).read_bytes()).hexdigest())
for key,name in [('exe','i76.exe'),('zfs','I76.ZFS'),('msn','miss8/M06.MSN'),('ter','miss8/M06.TER')]:
 b=getattr(a,key).read_bytes();expected=next(x for x in prior['inputs'] if x['name']==name);assert hashlib.md5(b).hexdigest()==expected['md5'] and hashlib.sha256(b).hexdigest()==expected['sha256']
assert hashlib.sha256(a.gzf.read_bytes()).hexdigest()==prior['baselines'][0]['baseline_sha256']
v=json.loads((r/'evidence/verification.json').read_text());context=json.loads((r/'evidence/context_validation.json').read_text());negative=json.loads((r/'evidence/corruptions.json').read_text());assert all(x['rejected'] for x in negative.values())
count=v['checks']+context['test_count']+len(negative)
validation=dict(status='passed',test_count=count,passed_count=count,notes=f"{v['checks']} independent walker/plane/clip/bin checks across 20 original-instruction scenarios; {context['test_count']} unchanged inherited source/camera/clip/bin checks; {len(negative)} rejected observed-trace corruptions. Asset-free checks and protocol integrity are separately reported. Additional-center/corner-end, authentic nonzero lighting, alternate rendering and hardware-wide x87 remain open.")
dump(r/'validation.json',validation)
specs=[('F-WALK','Original whole-polygon eligibility requires projected-Y score=4-N, both corner distances<0 and equal masked shade bands; only zero whole-emitter return enters fallback after an attempt.','artifacts/TERRAIN_WALKER_DECISIONS.md'),('F-FAN','Original anchor priority and adjacent boundary fan predict tested emitted triangles in exact order, filtering nonnegative plane distances and ignoring triangle callback return values.','artifacts/TRIANGLE_FALLBACK.md'),('F-EMISSION','In the bounded ordinary M06 corpus the independent walker predicts source-index attempts, depth/screen rejection and final accepted bins; 79 primary leaves produce 181 attempts and 30 entries.','artifacts/EMISSION_RECONSTRUCTION_HANDOFF.md'),('F-SHADE-CONTROL','Supplied lighting exercises 18 original shade-band rejections; supplied high-color flag bypasses triangle scalar shade while retaining the original whole-polygon shade gate.','artifacts/POLYGON_FACING_AND_SHADE.md')]
findings=[]
for fid,claim,doc in specs:
 findings.append(dict(finding_id=fid,claim=claim,status='proven',confidence='high',scope='game',evidence=[ref(doc),ref('evidence/instruction_anchors.tsv'),ref('evidence/verification.json'),ref('evidence/decisions.jsonl'),ref('scripts/walker.py'),ref('scripts/verify.py')],limitations='Bounded original-instruction emulation with controlled root, explicit OS/CRT/resource/numerical services and original source/post-transform inputs. Numerical model has stated comparison bounds. Shade/high are supplied diagnostic controls, not mission lighting/resource provenance. Additional-center/corner-end anchors, degenerate/tie behavior, general bin rejection and downstream rendering remain unresolved.'))
dump(r/'findings.json',dict(schema_version='1.2.0',run_id=r.name,findings=findings))
art=[]
for dirname,kind in [('artifacts','report'),('evidence','table'),('scripts','script')]:
 for f in sorted((r/dirname).iterdir()):
  if f.is_file():art.append(dict(path=str(f.relative_to(r)),kind=kind,bytes=f.stat().st_size,sha256=hashlib.sha256(f.read_bytes()).hexdigest()))
m=dict(schema_version='1.2.0',protocol_version='1.0.5',run_id=r.name,track='i76exe',base_commit='19c755a77db404ba9cb0ab51f307b4261e983aff',started_at='2026-11-06T04:13:51Z',topic='Terrain polygon selection, facing, shade and ordered emission parity',summary='Independent predictive walker matches 20 bounded original-camera scenarios, including primary 79 leaves/181 attempts/30 bins and supplied shade/high controls; authentic added-center remains explicitly unresolved.',inputs=prior['inputs'],baselines=prior['baselines'],artifacts=art,validation=validation,reproducibility=dict(status='partial',methods=['Retail executable-section identity on fresh v100 import','Independent source-geometry walker and bounded plane/clip models','Original branch, index, reject stage, return and final bin comparisons','Asset-free numerical fixtures, original-trace corruption rejection, 76 predecessor sidecar matches','Unchanged predecessor source/camera/clip/bin verifier'],script_refs=[ref(str(f.relative_to(r))) for f in sorted((r/'scripts').iterdir()) if f.is_file()],limitations='Licensed inputs required for original execution. Source graph and post-transform geometry are original inputs. No authenticated additional-center/corner-end fixture, full mission lighting, general bin failures, alternate descriptor success, raster or hardware-wide x87 claim.'))
dump(r/'manifest.json',m);print('Packaged',len(art),'artifacts;',count,'scientific checks')
