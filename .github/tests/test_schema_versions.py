import json,unittest
from pathlib import Path
from jsonschema import Draft202012Validator,ValidationError
P=Path(__file__).resolve().parents[2]/"agent/protocol"
def load(ver,typ):
 d=P/"schemas"
 if ver!="1.0.0":d=d/("v"+ver)
 return json.loads((d/(typ+".schema.json")).read_text())
def sample(track="shared"):
 return dict(schema_version="1.1.0",protocol_version="1.0.0",run_id=track+"-20261022T191025Z-894e13c1",track=track,topic="synthetic test only",base_commit="a"*40,started_at="2026-10-22T19:10:25Z",inputs=[],baselines=[],artifacts=[],validation={"status":"not-run","test_count":0,"passed_count":0},reproducibility={"status":"unavailable","script_refs":[],"methods":[],"limitations":"No real binaries"})
class VersionTests(unittest.TestCase):
 def test_v10_historical(self):
  for typ,example in (("run","manifest"),("finding","findings")):
   Draft202012Validator(load("1.0.0",typ)).validate(json.loads((P/"examples"/(example+".json")).read_text()))
 def test_v11_infrastructure(self):Draft202012Validator(load("1.1.0","run")).validate(sample())
 def test_v11_editor_requires_provenance(self):
  with self.assertRaises(ValidationError):Draft202012Validator(load("1.1.0","run")).validate(sample("i76edit"))
 def test_v11_game_requires_provenance(self):
  with self.assertRaises(ValidationError):Draft202012Validator(load("1.1.0","run")).validate(sample("i76exe"))
 def test_v11_proven_requires_evidence(self):
  f={"schema_version":"1.1.0","run_id":"shared-20261022T191025Z-894e13c1","findings":[{"finding_id":"x.y","claim":"Proven sample claim","status":"proven","confidence":"high","scope":"shared","evidence":[],"limitations":"synthetic"}]}
  with self.assertRaises(ValidationError):Draft202012Validator(load("1.1.0","finding")).validate(f)
 def test_v11_unresolved_without_evidence(self):
  f={"schema_version":"1.1.0","run_id":"shared-20261022T191025Z-894e13c1","findings":[{"finding_id":"x.y","claim":"Unresolved sample claim","status":"unresolved","confidence":"unknown","scope":"shared","evidence":[],"limitations":"synthetic"}]}
  Draft202012Validator(load("1.1.0","finding")).validate(f)

 def sample12(self,track="i76shell"):
  d=sample(track);d["schema_version"]="1.2.0";d["protocol_version"]="1.0.4";return d
 def shell12(self):
  d=self.sample12();d["inputs"]=[{"name":"i76shell.dll","kind":"shell-dll","md5":"a"*32,"sha256":"b"*64}]
  d["baselines"]=[{"version":"test","program_name":"i76shell.dll","baseline_id":"SYNTHETIC","baseline_sha256":"c"*64}]
  return d
 def test_v12_synthetic_shell_with_provenance(self):
  Draft202012Validator(load("1.2.0","run")).validate(self.shell12())
 def test_v12_shell_requires_binary(self):
  d=self.shell12();d["inputs"]=[]
  with self.assertRaises(ValidationError):Draft202012Validator(load("1.2.0","run")).validate(d)
 def test_v12_shell_requires_explicit_shell_kind(self):
  d=self.shell12();d["inputs"][0]["kind"]="other"
  with self.assertRaises(ValidationError):Draft202012Validator(load("1.2.0","run")).validate(d)
 def test_v12_shell_requires_ghidra_baseline(self):
  d=self.shell12();d["baselines"]=[]
  with self.assertRaises(ValidationError):Draft202012Validator(load("1.2.0","run")).validate(d)
 def test_v12_rejects_bogus_track(self):
  d=self.sample12("bogus")
  with self.assertRaises(ValidationError):Draft202012Validator(load("1.2.0","run")).validate(d)
 def test_v12_legacy_tracks_still_valid(self):
  for track in ("shared","i76exe","i76edit"):
   d=self.sample12(track)
   if track!="shared":
    d["inputs"]=[{"name":"synthetic.exe","kind":"retail-executable" if track=="i76exe" else "editor-executable","md5":"a"*32,"sha256":"b"*64}]
    d["baselines"]=[{"version":"test","program_name":"synthetic","baseline_id":"SYNTHETIC","baseline_sha256":"c"*64}]
   Draft202012Validator(load("1.2.0","run")).validate(d)
 def test_v12_shell_findings_scope(self):
  f={"schema_version":"1.2.0","run_id":"i76shell-20261028T200000Z-11223344","findings":[{"finding_id":"shell.test","claim":"Synthetic unresolved claim","status":"unresolved","confidence":"unknown","scope":"shell","evidence":[],"limitations":"Synthetic"}]}
  Draft202012Validator(load("1.2.0","finding")).validate(f)
 def test_old_schemas_reject_shell(self):
  for v in ("1.0.0","1.1.0"):
   with self.assertRaises(ValidationError):Draft202012Validator(load(v,"run")).validate(self.shell12())
 def test_v11_still_accepts_existing_tracks(self):
  Draft202012Validator(load("1.1.0","run")).validate(sample("shared"))

if __name__=="__main__":unittest.main()
