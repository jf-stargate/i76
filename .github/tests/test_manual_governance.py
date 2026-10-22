import json,unittest
from pathlib import Path
import yaml
ROOT=Path(__file__).resolve().parents[2]
class Governance(unittest.TestCase):
 def test_versions(self):
  p=yaml.safe_load((ROOT/"agent/protocol/access.yaml").read_text())
  v=json.loads((ROOT/"agent/protocol/SCHEMA_VERSIONS.json").read_text())
  self.assertEqual((ROOT/"agent/protocol/VERSION").read_text().strip(),"1.0.1")
  self.assertEqual(p["schema_version"],"1.0.1")
  self.assertEqual(v["publication_protocol_version"],"1.0.1")
  self.assertEqual(v["supported_research_schema_versions"],["1.0.0","1.1.0"])
 def test_manual_policy(self):
  p=yaml.safe_load((ROOT/"agent/protocol/access.yaml").read_text())["publication"]
  self.assertEqual(p["required_formal_approvals"],0)
  self.assertTrue(p["manual_maintainer_decision_required"])
  self.assertFalse(p["require_separate_reviewer_for_authoritative_changes"])
  self.assertTrue(p["all_changes_require_pr"])
  self.assertTrue(p["require_trusted_ci"])
  self.assertFalse(p["autonomous_run_merge"])
  self.assertFalse(p["direct_main_push"])
 def test_ruleset_template(self):
  r=json.loads((ROOT/".github/config/main-ruleset.json").read_text())
  self.assertEqual(r["enforcement"],"active")
  self.assertEqual(r["bypass_actors"],[])
  self.assertIn("refs/heads/main",r["conditions"]["ref_name"]["include"])
  rules={x["type"]:x for x in r["rules"]}
  self.assertIn("deletion",rules)
  self.assertIn("non_fast_forward",rules)
  p=rules["pull_request"]["parameters"]
  self.assertEqual(p["required_approving_review_count"],0)
  self.assertFalse(p["require_code_owner_review"])
  self.assertFalse(p["require_last_push_approval"])
  self.assertTrue(p["required_review_thread_resolution"])
  s=rules["required_status_checks"]["parameters"]
  self.assertTrue(s["strict_required_status_checks_policy"])
  self.assertEqual([c["context"] for c in s["required_status_checks"]],["integrity"])
if __name__=="__main__":unittest.main()
