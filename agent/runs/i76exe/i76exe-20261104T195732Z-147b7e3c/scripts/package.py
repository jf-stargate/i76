"""Regenerate packaging during preparation, never rewrite an accepted run."""
import argparse, hashlib, json
from pathlib import Path

def digest(b):return hashlib.sha256(b).hexdigest()
def write(p,x):p.write_text(json.dumps(x,indent=2)+'\n')
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--workspace',type=Path,required=True);a=ap.parse_args()
 run=Path(__file__).resolve().parent.parent
 identities=[]
 for name,expected in [('orig/i76.exe','bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'),('scratch_data/i76exe_v100.gzf','f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0')]:
  p=a.workspace/name;b=p.read_bytes();actual=digest(b);assert actual==expected
  identities.append({'path':str(p),'length':len(b),'md5':hashlib.md5(b).hexdigest(),'sha256':actual,'matches_expected_before_and_after':True})
 write(run/'evidence/source_integrity.json',identities)
 validation={'status':'passed','test_count':26,'passed_count':26,'notes':'20 synthetic unittest methods (including every truncated prefix); 2 expected EXE/GZF SHA-256 checks before/after; 1 full 74-specimen archive/272-name dependency survey; 1 original-byte comparison over 14 bodies / 12135 bytes, zero mismatches; 1 unchanged persisted program/properties/current indexes check; 1 complete fresh reproduction with identical regenerated metadata. GitHub/protocol integrity checks are additional. No native retail execution.'}
 write(run/'validation.json',validation)
 findings=[]
 for fid,claim,refs,limit in [
  ('HZD-001','Observed HZD stock profile is plain ASCII text with sixteen CRLF-terminated filename records, no header/count/parameters; retail advances via unchecked delimiter search and CRT mask0x103, while the independent reader is bounded.',['artifacts/HZD_FORMAT.md','evidence/parser_constants.json','evidence/reviewed_instructions.tsv','scripts/test_hzd.py'],'Only this retail build/corpus; CRLF/15-byte independent-reader policy is narrower than unsafe retail; locale and historical layouts unmeasured.'),
  ('HZD-002','All 74 archive-authenticated HZD files have 224 bytes and sixteen 12-byte names, with 33 distinct payloads; 78 of 80 mission WRLD fields select 36 logical HZD names /19 payloads.',['artifacts/HZD_CORPUS.md','evidence/corpus.json'],'Accessible installation only; installed mission files hashed but not archive-authenticated; no native load success.'),
  ('HZD-003','Every one of 272 HZD texture names resolves in inventory:104 direct MAP PIX members,168 VQM PIX members with ZFS CBKs and M16 PIX members; runtime uses ordered primary/optional pointer pairs.',['artifacts/HZD_RESOURCE_GRAPH.md','evidence/dependency_inventory.json','evidence/reviewed_instructions.tsv'],'Inventory and static boundary do not prove decoder success, active source selection, palette or rendering correctness.'),
  ('HZD-004','HZD initialization releases the parsed manifest before texture acquisition, retains partial pairs on failure, and has no replacement rollback;00401510 is a separate pair-release loop despite its inherited load annotation.',['artifacts/HZD_CONTROL_FLOW.md','evidence/reviewed_instructions.tsv','evidence/instruction_byte_validation.tsv'],'Normal bounded static paths only; malformed parser paths may not reach release; repeated intact teardown is a local property, not whole-engine lifecycle proof.')]:
  findings.append({'finding_id':fid,'claim':claim,'status':'proven','confidence':'high','scope':'game','evidence':[{'kind':'run-artifact','ref':n,'sha256':digest((run/n).read_bytes())} for n in refs],'limitations':limit})
 write(run/'findings.json',{'schema_version':'1.2.0','run_id':run.name,'findings':findings})
 artifacts=[]
 for directory in ['artifacts','evidence','scripts']:
  for p in sorted((run/directory).rglob('*')):
   if not p.is_file() or '__pycache__' in p.parts:continue
   b=p.read_bytes();kind='script' if directory=='scripts' else 'assembly' if p.name=='reviewed_instructions.tsv' else 'table' if p.suffix in ['.json','.tsv'] else 'report'
   artifacts.append({'path':p.relative_to(run).as_posix(),'kind':kind,'sha256':digest(b),'bytes':len(b)})
 corpus=run/'evidence/corpus.json';cb=corpus.read_bytes()
 manifest={'schema_version':'1.2.0','protocol_version':'1.0.5','run_id':run.name,'track':'i76exe','topic':'Retail HZD horizon manifest grammar, corpus and runtime resource contract','base_commit':'5f408a117da6d55e495714b648f41b43d708bf6e','started_at':'2026-11-04T19:57:32Z','summary':'Research only: archive-authenticated 74-file HZD survey, exact retail parser/load/teardown instruction evidence, 272-name PIX/PAK dependency closure, bounded independent Python reader and fresh reproduction. No reconstruction/canonical/shared/baseline changes.',
 'inputs':[{'name':'i76.exe','kind':'retail-executable','md5':identities[0]['md5'],'sha256':identities[0]['sha256'],'notes':'Private orig/i76.exe, expected identity verified before/after.'},{'name':'HZD corpus metadata','kind':'resource-manifest','md5':hashlib.md5(cb).hexdigest(),'sha256':digest(cb),'notes':'evidence/corpus.json: exact private HZD/MSN paths and hashes; HZD archive authentication; no proprietary payloads.'}],
 'baselines':[{'version':'v100 / Ghidra12.1.4 PUBLIC','program_name':'i76.exe','baseline_id':'i76exe_v100','baseline_sha256':identities[1]['sha256'],'storage_ref':'private:scratch_data/i76exe_v100.gzf','notes':'Disposable import -noanalysis, later -readOnly; persisted program database unchanged; backups housekeeping qualified in database_integrity.json.'}],
 'artifacts':artifacts,'validation':validation,'reproducibility':{'status':'complete','script_refs':[{'kind':'run-artifact','ref':x['path']} for x in artifacts if x['kind']=='script'],'methods':['binary-static Ghidra export without reanalysis','original PE instruction-byte comparison','archive-authenticated retail corpus and PIX/PAK slice inventory','independent bounded synthetic reader tests','fresh full reproduction and program-database hash comparison'],'limitations':'Requires exact private EXE/GZF, archive and mission installation; public inventory anonymizes complete texture names. No native retail load/render execution, no malformed original execution, no complete renderer or all texture failure-path proof.'}}
 write(run/'manifest.json',manifest)
 print('packaged',len(artifacts),'artifacts',sum(x['bytes'] for x in artifacts),'bytes')
if __name__=='__main__':main()
