"""Reproduce research in a NEW private work directory. No public mutation.
Private installation root, exact EXE/GZF, Ghidra12.1.4, liblzo2 required.
"""
import argparse,json,os,re,subprocess,sys
from pathlib import Path
sys.dont_write_bytecode=True
from review import review,sha,EXE,GZF
from survey import survey

def snapshot(project):
 return {str(p.relative_to(project)):sha(p.read_bytes()) for p in sorted(project.rglob('*')) if p.is_file() and (p.suffix in ('.gbf','.prp') or p.name=='~index.dat')}
def main():
 p=argparse.ArgumentParser()
 for k in ['root','repo','exe','gzf','work','headless']:p.add_argument('--'+k,type=Path,required=True)
 a=p.parse_args();assert sha(a.exe.read_bytes())==EXE and sha(a.gzf.read_bytes())==GZF
 a.work=a.work.resolve();a.work.mkdir(exist_ok=False);out=a.work/'metadata';out.mkdir();project=a.work/'project';project.mkdir()
 scripts=Path(__file__).resolve().parent;requests=json.loads((scripts.parent/'evidence/export_requests.json').read_text())
 results=subprocess.run([sys.executable,'-m','unittest','discover','-s',str(scripts),'-p','test_color_model.py','-v'],text=True,capture_output=True,env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1'))
 (out/'synthetic_tests.txt').write_text(results.stdout+results.stderr);assert results.returncode==0
 v=survey(a.root,a.repo);(out/'corpus.json').write_text(json.dumps(v,indent=2,sort_keys=True)+'\n');print('Corpus and synthetic tests passed',flush=True)
 domain=a.gzf.stem
 def gh(args,log):
  r=subprocess.run([str(a.headless),str(project),'color','-noanalysis','-scriptPath',str(scripts)]+args,text=True,capture_output=True)
  s=r.stdout+r.stderr;(a.work/log).write_text(s)
  assert r.returncode==0 and not re.search(r'SCRIPT ERROR|ERROR.*\.java|Exception:',s),log
 # Import once without analysis, then all exports read-only.
 gh(['-import',str(a.gzf)],'import.log');before=snapshot(project/'color.rep')
 for name,entries in sorted(requests.items()):
  gh(['-process',domain,'-readOnly','-postScript','ColorAudit.java',str(a.work/name),*entries],name+'.log')
  print('Authenticated export '+name,flush=True)
 gh(['-process',domain,'-readOnly','-postScript','ColorScan.java',str(a.work/'scan.json')],'scan.log')
 after=snapshot(project/'color.rep');assert before==after
 counts=review(a.exe,a.work,out)
 assert sha(a.exe.read_bytes())==EXE and sha(a.gzf.read_bytes())==GZF
 (out/'reproduction.json').write_text(json.dumps({'status':'passed','counts':counts,'original_hashes_unchanged':True,'saved_program_files_unchanged':before==after,'program_before':before,'program_after':after,'limitations':'Binary-static and synthetic; no original instructions executed, no device calls, null-LUM/CRT gamma generation unsupported'},indent=2,sort_keys=True)+'\n')
 print('Reproduction passed: '+str(out),flush=True)
if __name__=='__main__':main()
