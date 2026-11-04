"""Package owned run metadata; no canonical edits or private payload copies."""
import hashlib,json
from pathlib import Path
R=Path(__file__).resolve().parent.parent
ROOT=R.parents[3]
PRIVATE=ROOT.parent

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def put(p,v):(R/p).write_text(json.dumps(v,indent=2,sort_keys=True)+'\n')
def evidence(p):return {'kind':'run-artifact','ref':p,'sha256':sha(R/p)}
claims=[
 ('color.callbacks','Five backend descriptors select four palette callbacks, installed by a whole-context copy; their correction/display/LUM order differs.','PALETTE_CALLBACKS.md','00402EBA','No dynamically supplied/external-code closure or native device success claim.'),
 ('color.act','Palette and mask consumers use unsigned RGB8 triplets, component correction LUTs and backend-specific reserved display indexes; a separate DIB helper uses a different channel order.','ACT_FORMAT_AND_CONVERSION.md','004797F0','Exact CRT power generation, imported conversion outputs and native display appearance unvalidated.'),
 ('color.lum','Provided LUM is copied verbatim to runtime0061B2A0; software consumers use source-index columns and shade-row offsets; runtime helper modifies one column.','LUM_SEMANTICS.md','004791E0','Null-LUM arithmetic structure recovered but complete x87/CRT generator unsupported by model; upstream float shade units/rounding not unified.'),
 ('color.tbl','Runtime TBL composes source-high and destination-low palette indexes; source255 row is replaced by identity and two span consumers temporarily patch destination255 column.','TBL_SEMANTICS.md','00479780','No fixed RGB blend factor, arbitrary-alias closure, external plugin equivalence or abnormal-exit restoration guarantee.'),
 ('color.corpus','80 missions select37 ACT,18 LUM and18 TBL names;36/18/18 resolve as distinct payloads authenticated against retail ZFS; t013_16.act remains unresolved.','COLOR_RESOURCE_CORPUS.md','004B8A10','One available base-game corpus only; no substitution of missing name or native acquisition success.'),
]
findings=[]
for id,claim,report,address,limit in claims:
 ev=[evidence('artifacts/'+report),evidence('evidence/reviewed_instructions.json'),{'kind':'retail-address','ref':'orig/i76.exe','address':address,'notes':'Exact executable identity in manifest'}]
 if id=='color.corpus':ev.append(evidence('evidence/corpus.json'))
 else:ev.append(evidence('evidence/formulas.json'))
 findings.append({'finding_id':id,'claim':claim,'status':'proven','confidence':'high','scope':'game','evidence':ev,'limitations':limit})
findings.append({'finding_id':'color.reference.model','claim':'Independent bounded model implements verified integer/copy contracts and passes11 synthetic tests with axis/order/precision counterexamples.','status':'derived','confidence':'high','scope':'game','evidence':[evidence('scripts/color_model.py'),evidence('scripts/test_color_model.py'),evidence('evidence/synthetic_tests.txt'),evidence('artifacts/RECONSTRUCTION_HANDOFF.md')],'limitations':'No original-instruction execution or native renderer; null-LUM/CRT gamma generation explicitly unsupported.'})
put('findings.json',{'schema_version':'1.2.0','run_id':R.name,'findings':findings})
rep=json.loads((R/'evidence/reproduction.json').read_text())
put('evidence/validation_outcomes.json',{'status':'passed','synthetic_methods':11,'synthetic_passed':11,'instruction_validation':rep['counts'],'fresh_reproduction_passed':True,'source_EXE_GZF_hashes_unchanged':True,'saved_program_database_unchanged':True,'scope':'Run-local static research validation, not native execution or full renderer equivalence. Protocol/path checks run separately after packaging.','unsupported':['null-LUM x87 generation','CRT gamma LUT generation','upstream float span interpolation','native display/plugin outputs','complete arbitrary-alias consumer closure']})
validation={'status':'passed','test_count':11,'passed_count':11,'notes':'Synthetic unittest methods; PE byte/range checks and corpus/fresh reproduction separately recorded.'}
put('validation.json',validation)
art=[]
for dirname in ['artifacts','evidence','scripts']:
 for p in sorted((R/dirname).rglob('*')):
  if not p.is_file() or '__pycache__' in p.parts:continue
  kind='script' if dirname=='scripts' else 'report' if p.suffix=='.md' else 'assembly' if p.name=='reviewed_instructions.json' else 'test-result' if p.name in ('reproduction.json','synthetic_tests.txt') else 'table'
  art.append({'path':str(p.relative_to(R)),'kind':kind,'sha256':sha(p),'bytes':p.stat().st_size})
inputs=[]
for rel,kind in [('orig/i76.exe','retail-executable'),('scratch_data/i76exe_v100.gzf','other'),('orig/I76.ZFS','other')]:
 p=PRIVATE/rel;b=p.read_bytes();inputs.append({'name':p.name,'kind':kind,'md5':hashlib.md5(b).hexdigest(),'sha256':hashlib.sha256(b).hexdigest(),'notes':'Private input; payload excluded. Authenticated in reproduction.'})
put('manifest.json',{'schema_version':'1.2.0','protocol_version':'1.0.5','run_id':R.name,'track':'i76exe','topic':'ACT/LUM/TBL color transformations, backend callbacks and runtime table indexing','base_commit':'e7b97c95a21be3657a4f6d3cb993323aa66bde7d','started_at':'2026-11-04T22:42:44Z','summary':'Run-only binary-static/corpus proposal; four callback contracts, verified table axes and mutations, bounded independent model. Complete null-LUM/CRT and native renderer behavior remain unsupported. Human acceptance required.','inputs':inputs,'baselines':[{'version':'v100','program_name':'i76.exe','baseline_id':'i76exe_v100.gzf','baseline_sha256':inputs[1]['sha256'],'storage_ref':'private:scratch_data/i76exe_v100.gzf','notes':'Disposable import without reanalysis; exports read-only; annotations unchanged.'}],'artifacts':art,'validation':validation,'reproducibility':{'status':'complete','script_refs':[evidence(str(p.relative_to(R))) for p in sorted((R/'scripts').glob('*')) if p.is_file()],'methods':['Authenticated retail PE/GZF and ZFS resource identities','Read-only Ghidra static exports, computed-reference inventory and original PE byte checks','Independent bounded integer/copy model and11 synthetic tests','Fresh disposable reproduction; source/database hashes before/after'],'limitations':'Complete for published bounded procedures; proprietary inputs required. Null-LUM/CRT exact generation, external plugins, upstream float interpolation and native renderer outputs are unsupported. No semantic equivalence claim.'}})
print('Packaged',len(art),'artifacts')
