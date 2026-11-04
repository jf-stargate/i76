"""Read-only reproduction. All new outputs must be outside the public checkout."""
import argparse
import hashlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from inspect_corpus import inspect
import test_pix_reader

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--workspace",type=Path,required=True)
    ap.add_argument("--private-output",type=Path,required=True)
    group=ap.add_mutually_exclusive_group(required=True)
    group.add_argument("--headless",type=Path)
    group.add_argument("--audit",type=Path,help="Reuse private Ghidra extraction instead of importing again")
    args=ap.parse_args()
    script=Path(__file__).resolve().parent;repo=script.parents[4]
    out=args.private_output.resolve()
    if out.is_relative_to(repo):raise ValueError("outputs must be outside public checkout")
    out.mkdir(parents=True,exist_ok=True)
    exe=args.workspace/"orig/i76.exe";gzf=args.workspace/"scratch_data/i76exe_v100.gzf"
    archive=args.workspace/"orig/I76.ZFS"
    historical=repo/"scripts/local_history/i76_zfs_inmemory_asset_graph_reports_v1.py"
    vehicle=historical.with_name("i76_vehicle_texture_slot_resolver_v5.py")
    before={p.name:sha(p) for p in (exe,gzf,archive,historical,vehicle)}
    suite=unittest.defaultTestLoader.loadTestsFromModule(test_pix_reader)
    result=unittest.TextTestRunner(stream=io.StringIO(),verbosity=2).run(suite)
    assert result.wasSuccessful()
    tests={"tests":result.testsRun,"passed":result.testsRun,"failures":0,"errors":0}
    (out/"synthetic_results.json").write_text(json.dumps(tests,sort_keys=True,indent=2)+"\n")
    corpus=inspect(args.workspace/"zfs/resources",archive,historical,out/"private_details.json")
    (out/"corpus.json").write_text(json.dumps(corpus,sort_keys=True,indent=2)+"\n")
    audit=args.audit
    if args.headless:
        project=Path(tempfile.mkdtemp(prefix="ghidra-",dir=out))
        audit=out/"audit.json"
        subprocess.run([str(args.headless),str(project),"pix", "-import",str(gzf),"-readOnly","-noanalysis",
                        "-scriptPath",str(script),"-postScript","AuditPix.java",str(audit),"-log",str(out/"ghidra.log")],check=True,stdout=subprocess.DEVNULL)
    with (out/"instructions.json").open("w") as stream:
        subprocess.run([sys.executable,"-B",str(script/"verify_instructions.py"),"--exe",str(exe),"--gzf",str(gzf),"--audit",str(audit)],check=True,stdout=stream)
    with (out/"examples.json").open("w") as stream:
        subprocess.run([sys.executable,"-B",str(script/"validate_examples.py"),"--root",str(args.workspace/"zfs/resources"),"--archive",str(archive),"--historical",str(historical),"--corpus",str(out/"corpus.json")],check=True,stdout=stream)
    after={p.name:sha(p) for p in (exe,gzf,archive,historical,vehicle)}
    assert before==after
    expected=script.parent/"artifacts"
    for name in ("corpus.json","examples.json"):
        assert json.loads((out/name).read_text())==json.loads((expected/name).read_text()),name
    actual=json.loads((out/"instructions.json").read_text())
    original=json.loads((expected/"instructions.json").read_text())
    for key in ("functions","reviewed_instructions","verified_instructions","exe_sha256","gzf_sha256"):
        assert actual[key]==original[key],key
    report={"status":"passed","synthetic_tests":tests,"input_sha256_before":before,"input_sha256_after":after,
            "corpus_exact_reproduction":True,"examples_exact_reproduction":True,"instruction_bytes_reproduction":True,
            "fresh_readonly_ghidra_import":bool(args.headless),"retail_execution":False}
    (out/"reproduction.json").write_text(json.dumps(report,sort_keys=True,indent=2)+"\n")
    print(json.dumps(report,sort_keys=True,indent=2))
if __name__=="__main__":main()
