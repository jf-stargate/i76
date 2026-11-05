"""Package run metadata after reproduction; no original payload is copied."""
import argparse
import hashlib
import json
from pathlib import Path
RUN_ID='i76exe-20261104T224258Z-8e34c41d'
BASE='e7b97c95a21be3657a4f6d3cb993323aa66bde7d'

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def write(path,doc):path.write_text(json.dumps(doc,sort_keys=True,indent=2)+'\n')
def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--workspace',type=Path,required=True);a=ap.parse_args()
 run=Path(__file__).resolve().parents[1]
 reproduction=json.loads((run/'evidence/reproduction.json').read_text())
 assert reproduction['status']=='passed' and reproduction['compared_published_aggregates']
 notes='50 synthetic unit/model tests, six historical differential fixtures, seven complete check groups: authenticated immutable inputs, original PE instructions/ranges, bounded directory traversal, all logical lookups/decodes, historical/extracted byte comparison, installed ZIX membership, fresh deterministic reproduction. No retail execution or maintained provider.'
 validation={'status':'passed','test_count':63,'passed_count':63,'notes':notes};write(run/'validation.json',validation)
 definitions=[
 ('ZFS-001','Retail ZFSF v1 uses fixed 28-byte header, 3604-byte chained tables and 36-byte records; table sentinel/tombstone filtering and signed packed sizes differ from historical parser assumptions.','proven',['artifacts/ZFSF_FORMAT.md','artifacts/fields.json','evidence/instructions.json'], 'Binary-static and one authenticated archive; producer semantics of identifier/time word and other writer variants unresolved.'),
 ('ZFS-002','Retail compression dispatch selects LZO1X for bit1 before LZO1Y for bit2, ignores supplied decoded capacity and actual decoded count, and XORs complete logical DWORDs after decoding.','proven',['artifacts/ZFSF_DECOMPRESSION.md','evidence/instructions.json','evidence/corpus.json'], 'No unsafe retail malformed-input execution; backend codec correctness is external; nonzero XOR is static/synthetic only.'),
 ('ZFS-003','All 6116 active base-game ZFS records enumerate and decode safely through statically selected modes, with exact historical and extracted byte/hash equality and no duplicate keys or storage overlaps.','proven',['artifacts/ZFSF_CORPUS.md','evidence/corpus.json','evidence/provenance.json','evidence/reproduction.json'], 'This authenticated base-game specimen only; historical and independent wrappers share system liblzo2, not independent codec implementations.'),
 ('RES-001','Registered source selection uses 256-bit membership and first-any/first-mode0/active-media ordering, then one selected loose/ZFS source without failed-read alternate-source retry.','proven',['artifacts/RESOURCE_SOURCE_SELECTION.md','evidence/instructions.json','evidence/zix.json','scripts/source_model.py'], 'Binary-static with analytical source-model tests; actual OS enumeration, source collisions and media callbacks not executed.'),
 ('RES-002','Runtime key registration calls loaded-cache invalidation at 004702D0, not key canonicalization; forced eviction can free a referenced cache record, while archive close independently frees only archive/index state.','proven',['artifacts/RESOURCE_LIFETIME.md','artifacts/RESOURCE_SOURCE_SELECTION.md','evidence/instructions.json'], 'Static pointer-lifetime implications; full native invalidation effects, concurrent state changes and shutdown sequencing unresolved.'),
 ('ZFS-004','The run-owned reader enforces a bounded immutable logical-byte boundary, explicit duplicate/alias policies and safe X/Y decoder capacity/return checks, with 50 synthetic tests and six historical differential fixtures passing.','derived',['artifacts/RECONSTRUCTION_HANDOFF.md','scripts/zfs_reader.py','scripts/test_zfs.py','scripts/test_source_model.py','evidence/synthetic_results.json','evidence/historical_differences.json'], 'Stricter independent profile, not complete retail input acceptance or runtime lifecycle compatibility; Linux LP64 backend only; no maintained reconstruction integration.')]
 findings=[]
 for ident,claim,status,refs,limitations in definitions:
  findings.append({'finding_id':ident,'claim':claim,'status':status,'confidence':'high','scope':'game','evidence':[{'kind':'run-artifact','ref':r,'sha256':sha(run/r)} for r in refs],'limitations':limitations})
 write(run/'findings.json',{'schema_version':'1.2.0','run_id':RUN_ID,'findings':findings})
 inputs=[]
 for rel,kind in [('orig/i76.exe','retail-executable'),('scratch_data/i76exe_v100.gzf','other'),('orig/I76.ZFS','other'),('orig/I76.ZIX','other')]:
  p=a.workspace/rel;b=p.read_bytes();inputs.append({'name':p.name,'kind':kind,'sha256':hashlib.sha256(b).hexdigest(),'md5':hashlib.md5(b).hexdigest(),'notes':'Private authenticated input; never copied into run.'})
 artifacts=[]
 for p in sorted(run.rglob('*')):
  if not p.is_file() or p.name in ('manifest.json','findings.json','validation.json'):continue
  assert '__pycache__' not in p.parts
  rel=p.relative_to(run).as_posix();kind='script' if rel.startswith('scripts/') else 'report' if p.suffix=='.md' else 'test-result' if any(s in p.name for s in ('synthetic','reproduction','historical_differences')) else 'table'
  artifacts.append({'path':rel,'bytes':p.stat().st_size,'sha256':sha(p),'kind':kind})
 scripts=[{'kind':'run-artifact','ref':x['path'],'sha256':x['sha256']} for x in artifacts if x['kind']=='script']
 manifest={'schema_version':'1.2.0','protocol_version':'1.0.5','run_id':RUN_ID,'track':'i76exe','base_commit':BASE,'started_at':'2026-11-04T22:42:58Z',
 'topic':'ZFSF archive, bounded LZO logical resources and registered source selection',
 'summary':'Independent retail-static ZFSF/source contract; all 6116 base-game records safely decoded and compared. Read-only research reader/model/tests; no maintained provider or canonical edits.',
 'inputs':inputs,'baselines':[{'baseline_id':'i76exe_v100.gzf','baseline_sha256':inputs[1]['sha256'],'program_name':'i76.exe','version':'12.1.4','storage_ref':'private:scratch_data/i76exe_v100.gzf','notes':'Supplied v100 GZF; disposable readOnly/noanalysis import, modification number unchanged. Ghidra 12.1.4; no baseline promotion.'}],
 'artifacts':artifacts,'validation':validation,
 'reproducibility':{'status':'complete','script_refs':scripts,'methods':['Pinned-main governance and live GitHub enforcement bootstrap','Fresh read-only Ghidra 12.1.4 import with exact PE-byte/range comparison','Complete independently bounded directory and logical-name survey; historical and extracted comparisons','50 synthetic tests, six historical differential fixtures and deterministic fresh reproduction'],
 'limitations':'Original assets, inventories, GZF, opcode bytes and bulk audits private. System liblzo2 2.10 correctness is external; original mode selection proved statically. No retail path execution, non-ASCII or Nitro Pack claim, complete lifecycle compatibility or maintained provider.'}}
 write(run/'manifest.json',manifest)
if __name__=='__main__':main()
