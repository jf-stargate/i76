import unittest
from validate_protocol import policy,evaluate,safe_path
RUN="i76edit-20261021T221900Z-a7d2e2f4"
BR="agent/i76edit/"+RUN
class AccessTests(unittest.TestCase):
 def test_policy(self):self.assertEqual(policy()["schema_version"],"1.0.5")
 def test_own_run(self):self.assertTrue(evaluate(f"agent/runs/i76edit/{RUN}/manifest.json",RUN,BR))
 def test_shell_run(self):
  rid="i76shell-20261028T200000Z-11223344"
  self.assertTrue(evaluate(f"agent/runs/i76shell/{rid}/manifest.json",rid,f"agent/i76shell/{rid}"))
  self.assertFalse(evaluate(f"agent/runs/i76exe/{rid}/manifest.json",rid,f"agent/i76shell/{rid}"))
  self.assertFalse(evaluate(f"agent/runs/i76shell/{rid}/manifest.json",rid,f"agent/i76edit/{rid}"))
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
 def test_reconstruction_scope_and_activation(self):
  p=policy()
  r=p["reconstruction_merge"]
  self.assertEqual(r["authority"],"conditional-implementation-self-merge")
  self.assertEqual(r["eligible"]["changed_path_prefix"],"reconstruction/")
  self.assertTrue(r["eligible"]["exclusive_path_scope"])
  self.assertTrue(r["eligible"]["prohibit_test_weakening"])
  self.assertFalse(r["research_governance_baseline_or_documentation_self_merge"])
  self.assertEqual(r["activation"]["on_unknown"],"proposal-only")
  self.assertEqual(r["activation"]["accepted_prs"],[112,114,115])
  self.assertEqual(set(r["exact_head_required_success_checks"]),{
   "integrity","linux-gcc-ctest","linux-clang-ctest","windows-msvc-ctest",
   "linux-asan-ubsan-ctest","linux-coverage","linux-valgrind-memcheck"})
if __name__=="__main__":unittest.main()
