import unittest
from validate_protocol import policy,evaluate,safe_path
RUN="i76edit-20261021T221900Z-a7d2e2f4"
BR="agent/i76edit/"+RUN
class AccessTests(unittest.TestCase):
 def test_policy(self):self.assertEqual(policy()["schema_version"],"1.0.0")
 def test_own_run(self):self.assertTrue(evaluate(f"agent/runs/i76edit/{RUN}/manifest.json",RUN,BR))
 def test_other_run(self):self.assertFalse(evaluate("agent/runs/i76edit/i76edit-20261021T221901Z-bbbbbbbb/manifest.json",RUN,BR))
 def test_merged_run(self):self.assertFalse(evaluate(f"agent/runs/i76edit/{RUN}/manifest.json",RUN,BR,existing=True))
 def test_wrong_branch(self):self.assertFalse(evaluate("manual/README.md",RUN,"main"))
 def test_unlisted(self):self.assertFalse(evaluate("unknown/file",RUN,BR))
 def test_manual_proposal(self):self.assertTrue(evaluate("manual/README.md",RUN,BR))
 def test_bad_paths(self):
  for p in ("../etc/passwd","/etc/passwd","agent//foo"):
   with self.assertRaises(ValueError):safe_path(p)
 def test_no_direct_publication(self):self.assertFalse(policy()["publication"]["direct_main_push"])
 def test_no_self_merge(self):self.assertFalse(policy()["publication"]["autonomous_run_merge"])
if __name__=="__main__":unittest.main()
