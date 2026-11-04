"""Reproduce into a NEW private directory; never mutate accepted run artifacts.
Requires the private installation/archive, exact EXE/GZF, Python3, liblzo2,
Ghidra12.1.4 and writable Java configuration when --headless is requested.
"""
import argparse, hashlib, json, os, re, subprocess, sys
sys.dont_write_bytecode = True
from pathlib import Path
from select_evidence import select, WINDOWS
from survey import survey
EXE='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def program_snapshot(p):
 return {str(f.relative_to(p)):digest(f) for f in sorted(p.rglob('*')) if f.is_file() and (f.suffix in ['.gbf','.prp'] or f.name=='~index.dat')}
def main():
 p=argparse.ArgumentParser()
 for k in ['root','repo','exe','gzf','work']:p.add_argument('--'+k,type=Path,required=True)
 p.add_argument('--headless',type=Path)
 a=p.parse_args();assert digest(a.exe)==EXE;assert digest(a.gzf)==GZF
 a.work=a.work.resolve();a.work.mkdir(exist_ok=False)
 scripts=Path(__file__).resolve().parent;out=a.work/'metadata';out.mkdir()
 tests=subprocess.run([sys.executable,'-m','unittest','discover','-s',str(scripts),'-p','test_hzd.py','-v'],capture_output=True,text=True,env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1'))
 (out/'synthetic_tests.txt').write_text(tests.stdout+tests.stderr);assert tests.returncode==0
 data=survey(a.root,a.repo,a.work/'private-corpus');deps=data.pop('anonymized_dependencies')
 for name,value in [('corpus.json',data),('dependency_inventory.json',deps)]:
  (out/name).write_text(json.dumps(value,sort_keys=True,indent=2)+'\n')
 if a.headless:
  project=a.work/'project';project.mkdir()
  base=[str(a.headless),str(project),'research','-noanalysis','-scriptPath',str(scripts)]
  def gh(args,log):
   result=subprocess.run(base+args,capture_output=True,text=True)
   s=result.stdout+result.stderr;(a.work/log).write_text(s)
   assert result.returncode==0 and not re.search(r'SCRIPT ERROR|ERROR.*\.java',s),log
   return s
  audit=a.work/'audit'
  s=gh(['-import',str(a.gzf),'-postScript','HzdAudit.java',str(audit),*WINDOWS],'import.log')
  assert 'READ_ONLY_HZD_EXPORT_OK' in s
  domain=a.gzf.stem
  before=program_snapshot(project/'research.rep')
  s=gh(['-process',domain,'-readOnly','-postScript','HzdRefs.java',str(out/'state_refs.txt'),
        '-postScript','HzdVerify.java',str(a.exe),str(out/'instruction_byte_validation.tsv'),*WINDOWS], 'read-only.log')
  assert 'HZD_RETAIL_BYTES_MATCH' in s
  after=program_snapshot(project/'research.rep');assert before==after
  (out/'database_integrity.json').write_text(json.dumps({'program_and_current_indexes_unchanged':True,'before':before,'after':after,'scope':'Ghidra backup/journal housekeeping excluded; no saved program changes'},indent=2)+'\n')
  select(audit,a.exe,out)
 assert digest(a.exe)==EXE and digest(a.gzf)==GZF
 print('Reproduction passed; private exports and derived metadata:',a.work)
if __name__=='__main__': main()
