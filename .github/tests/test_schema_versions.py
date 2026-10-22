import json,unittest
from pathlib import Path
from jsonschema import Draft202012Validator,ValidationError
P=Path(__file__).resolve().parents[2]/"agent/protocol"
def load(ver,typ):
 d=P/"schemas"
 if ver=="1.1.0":d=d/"v1.1.0"
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
if __name__=="__main__":unittest.main()
