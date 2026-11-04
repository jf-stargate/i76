"""Fresh read-only Ghidra import, full safe corpus comparison and synthetic tests.

All outputs, bulk audit and complete inventories must stay outside the checkout.
"""
import argparse
import hashlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from survey import survey
from check_zix import check
from check_historical import check as historical_check
from verify_evidence import verify, ADDRESSES
import test_zfs
import test_source_model

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def write(path,doc):path.write_text(json.dumps(doc,sort_keys=True,indent=2)+'\n')
def main():
 ap=argparse.ArgumentParser(description=__doc__)
 ap.add_argument('--workspace',type=Path,required=True);ap.add_argument('--private-output',type=Path,required=True)
 ap.add_argument('--headless',type=Path,required=True)
 ap.add_argument('--compare',action='store_true',help='require exact published aggregate reproduction')
 args=ap.parse_args();script=Path(__file__).resolve().parent;repo=script.parents[4]
 out=args.private_output.resolve();workspace=args.workspace.resolve()
 if out.is_relative_to(repo):raise ValueError('private output must be outside public checkout')
 out.mkdir(parents=True,exist_ok=True)
 exe=workspace/'orig/i76.exe';gzf=workspace/'scratch_data/i76exe_v100.gzf';archive=workspace/'orig/I76.ZFS';zix=workspace/'orig/I76.ZIX'
 historical=repo/'scripts/game/i76_zfs_extract.py'
 paths=(exe,gzf,archive,zix,historical,workspace/'zfs/zfs_extract_manifest.json')
 before={str(p.relative_to(workspace)) if p.is_relative_to(workspace) else str(p):sha(p) for p in paths}
 expected={'i76.exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3',
           'i76exe_v100.gzf':'f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0',
           'I76.ZFS':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d',
           'I76.ZIX':'1002a75cb2d9e597eeef40e49412cb8b578cbbcafa84af3e0839af86f770dd6b'}
 for p in (exe,gzf,archive,zix):assert sha(p)==expected[p.name]
 suite=unittest.TestSuite(unittest.defaultTestLoader.loadTestsFromModule(m) for m in (test_zfs,test_source_model))
 log=io.StringIO();res=unittest.TextTestRunner(stream=log,verbosity=2).run(suite)
 (out/'synthetic_tests.txt').write_text(log.getvalue());assert res.wasSuccessful()
 tests={'tests':res.testsRun,'passed':res.testsRun,'failures':len(res.failures),'errors':len(res.errors)}
 write(out/'synthetic_results.json',tests)
 corpus=survey(archive,workspace/'zfs/resources',historical,out/'inventory.json')
 assert not corpus['errors'] and not corpus['disagreements'];write(out/'corpus.json',corpus)
 zix_result=check(zix,archive);write(out/'zix.json',zix_result)
 write(out/'historical_differences.json',historical_check(historical))
 project=Path(tempfile.mkdtemp(prefix='ghidra-',dir=out))
 cmd=[str(args.headless),str(project),'zfs','-import',str(gzf),'-readOnly','-noanalysis','-scriptPath',str(script),
      '-postScript','AuditZfs.java',str(out/'audit.json'),ADDRESSES,
      '-postScript','ZfsRanges.java',str(out/'ranges.json'),'00470d30:00470ecd','004fff40,004fff58,004fff7c,004fffe0,004faeb0',
      '-log',str(out/'ghidra.log')]
 with (out/'headless.log').open('w') as stream:subprocess.run(cmd,stdout=stream,stderr=subprocess.STDOUT,check=True)
 assert (out/'audit.json').exists() and (out/'ranges.json').exists()
 evidence=verify(exe,gzf,out/'audit.json',out/'ranges.json');write(out/'instructions.json',evidence)
 after={str(p.relative_to(workspace)) if p.is_relative_to(workspace) else str(p):sha(p) for p in paths};assert before==after
 if args.compare:
  for name in ('corpus.json','zix.json','instructions.json','synthetic_results.json','historical_differences.json'):
   assert json.loads((out/name).read_text())==json.loads((script.parent/'evidence'/name).read_text()),name
 report={'status':'passed','fresh_readonly_import':True,'reanalysis':False,'input_sha256_before':before,'input_sha256_after':after,
         'synthetic':tests,'decoded':corpus['decoded'],'matched_extracted':sum(x.get('extracted_equal',0) for x in corpus['by_extension'].values()),
         'verified_instructions':evidence['verified_instructions'],'compared_published_aggregates':args.compare,
         'retail_execution':False,'external_lzo_dependency':True}
 write(out/'reproduction.json',report);print(json.dumps(report,indent=2,sort_keys=True))
if __name__=='__main__':main()
