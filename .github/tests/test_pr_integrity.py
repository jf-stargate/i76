import importlib.util,json,hashlib,subprocess,tempfile,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location("i76_guard",ROOT/".github/scripts/pr_integrity.py")
guard=importlib.util.module_from_spec(spec);spec.loader.exec_module(guard)
RID="i76edit-20261021T221900Z-a7d2e2f4"
def git(path,*args):
    r=subprocess.run(["git","-C",str(path),*args],capture_output=True)
    if r.returncode:raise RuntimeError(r.stderr.decode())
    return r.stdout.decode().strip()
class Tests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.r=Path(self.tmp.name)
        git(self.r,"init","-q");git(self.r,"config","user.name","Test");git(self.r,"config","user.email","test@example.com")
        self.add("README.md","initial")
        self.base=git(self.r,"rev-parse","HEAD")
    def add(self,p,s):
        f=self.r/p;f.parent.mkdir(parents=True,exist_ok=True)
        f.write_bytes(s if isinstance(s,bytes) else s.encode())
        git(self.r,"add","-A");git(self.r,"commit","-q","-m","test");return git(self.r,"rev-parse","HEAD")
    def check(self,head,branch=None):return guard.inspect(self.r,self.base,head,ROOT,branch)
    def runfiles(self,artifact=False):
        name=f"agent/runs/i76edit/{RID}"
        m=json.loads((ROOT/"agent/protocol/examples/manifest.json").read_text())
        f=json.loads((ROOT/"agent/protocol/examples/findings.json").read_text())
        m["base_commit"]=self.base
        m["validation"]={"status":"passed","test_count":1,"passed_count":1}
        m["artifacts"]=[]
        if artifact:
            body=b"payload"
            m["artifacts"]=[{"path":"evidence/data.txt","kind":"other","sha256":hashlib.sha256(body).hexdigest(),"bytes":len(body)}]
        self.add(name+"/manifest.json",json.dumps(m))
        self.add(name+"/findings.json",json.dumps(f))
        head=self.add(name+"/validation.json",json.dumps(m["validation"]))
        if artifact:head=self.add(name+"/evidence/data.txt",b"payload")
        return head,name

    def shellfiles(self,mutation=None):
        rid="i76shell-20261028T200000Z-11223344"
        name=f"agent/runs/i76shell/{rid}"
        m=json.loads((ROOT/"agent/protocol/examples/v1.2.0/manifest.json").read_text())
        f=json.loads((ROOT/"agent/protocol/examples/v1.2.0/findings.json").read_text())
        m["base_commit"]=self.base
        if mutation:mutation(m,f)
        self.add(name+"/manifest.json",json.dumps(m))
        self.add(name+"/findings.json",json.dumps(f))
        h=self.add(name+"/validation.json",json.dumps(m["validation"]))
        return h,rid
    def test_v12_shell_run(self):
        h,rid=self.shellfiles()
        self.assertEqual(self.check(h,f"agent/i76shell/{rid}")["runs"][0]["run_id"],rid)
    def test_v12_shell_missing_binary_provenance(self):
        h,rid=self.shellfiles(lambda m,f:m.update(inputs=[]))
        with self.assertRaises(Exception):self.check(h,f"agent/i76shell/{rid}")
    def test_v12_shell_missing_baseline(self):
        h,rid=self.shellfiles(lambda m,f:m.update(baselines=[]))
        with self.assertRaises(Exception):self.check(h,f"agent/i76shell/{rid}")
    def test_v12_shell_cross_track_branch(self):
        h,rid=self.shellfiles()
        with self.assertRaises(guard.Rejected):self.check(h,f"agent/i76exe/{rid}")
    def test_v12_shell_wrong_manifest_track(self):
        h,rid=self.shellfiles(lambda m,f:m.update(track="i76exe"))
        with self.assertRaises(guard.Rejected):self.check(h,f"agent/i76shell/{rid}")
    def test_v12_shell_wrong_run_prefix(self):
        h,rid=self.shellfiles(lambda m,f:m.update(run_id="i76exe-20261028T200000Z-11223344"))
        with self.assertRaises(guard.Rejected):self.check(h,f"agent/i76shell/{rid}")
    def test_manual_proposal(self):
        h=self.add("manual/reference/abc.md","hi");self.assertEqual(self.check(h)["publication"],"review-required")
    def test_unlisted_path(self):
        h=self.add("random/x","a")
        with self.assertRaises(guard.Rejected):self.check(h)
    def test_binary(self):
        h=self.add("agent/tools/prog.EXE",b"MZ")
        with self.assertRaises(guard.Rejected):self.check(h)
    def test_secret(self):
        h=self.add("manual/roadmap/x.md","ghp_"+"z"*36)
        with self.assertRaises(guard.Rejected):self.check(h)
    def test_own_run(self):
        h,_=self.runfiles(True);self.assertEqual(self.check(h,"agent/i76edit/"+RID)["runs"][0]["artifacts"],1)
    def test_wrong_branch(self):
        h,_=self.runfiles()
        with self.assertRaises(guard.Rejected):self.check(h,"agent/i76exe/"+RID)
    def test_tampered_hash(self):
        h,p=self.runfiles(True);h=self.add(p+"/evidence/data.txt","tampered")
        with self.assertRaises(guard.Rejected):self.check(h,"agent/i76edit/"+RID)
    def test_existing_run(self):
        h,p=self.runfiles();self.base=h;h=self.add(p+"/manifest.json","{}")
        with self.assertRaises(guard.Rejected):self.check(h,"agent/i76edit/"+RID)
    def test_unlisted_run_file(self):
        h,p=self.runfiles();h=self.add(p+"/evidence/unknown.txt","x")
        with self.assertRaises(guard.Rejected):self.check(h,"agent/i76edit/"+RID)
    def test_mixed_run_and_manual(self):
        h,p=self.runfiles();h=self.add("manual/README.md","x")
        with self.assertRaises(guard.Rejected):self.check(h,"agent/i76edit/"+RID)
    def test_symlink(self):
        f=self.r/"manual/ref.md";f.parent.mkdir();f.symlink_to("../README.md")
        git(self.r,"add","-A");git(self.r,"commit","-q","-m","link")
        with self.assertRaises(guard.Rejected):self.check(git(self.r,"rev-parse","HEAD"))
    def test_deletion(self):
        (self.r/"README.md").unlink();git(self.r,"add","-A");git(self.r,"commit","-q","-m","delete")
        with self.assertRaises(guard.Rejected):self.check(git(self.r,"rev-parse","HEAD"))
    def test_unsafe_path(self):
        with self.assertRaises(guard.Rejected):guard.path_ok("../escape")
if __name__=="__main__":unittest.main()
