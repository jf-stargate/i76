#!/usr/bin/env python3
"""Fresh private Ghidra import + original PE verification + deterministic public ranking.
Usage: reproduce.py --headless PATH --gzf PATH --pe PATH --private-dir NEW_DIRECTORY
Public-only: reproduce.py --ranking-only --private-dir NEW_DIRECTORY
Never writes to this run, the input GZF, PE, or any existing Ghidra project.
"""
import argparse,hashlib,json,pathlib,subprocess,sys
p=argparse.ArgumentParser();p.add_argument('--headless');p.add_argument('--gzf');p.add_argument('--pe');p.add_argument('--private-dir',type=pathlib.Path,required=True);p.add_argument('--ranking-only',action='store_true');a=p.parse_args()
r=pathlib.Path(__file__).resolve().parents[1];s=r/'scripts';w=a.private_dir.resolve();w.mkdir(parents=True,exist_ok=False);o=w/'artifacts';o.mkdir();freeze=json.loads((r/'artifacts/BLIND_FREEZE.json').read_text())
for name,h in freeze['files'].items():
 path=r/name
 if name in ['FEATURE_MODEL.md','BOUNDARY_RANKING.md']:path=r/'artifacts'/name
 assert hashlib.sha256(path.read_bytes()).hexdigest()==h,name
if not a.ranking_only:
 assert a.headless and a.gzf and a.pe
 (w/'project').mkdir()
 def gh(args):
  with (w/'headless.log').open('ab') as log:subprocess.run([a.headless,str(w/'project'),'blind',*args,'-noanalysis','-scriptPath',str(s)],stdout=log,stderr=subprocess.STDOUT,check=True)
 gh(['-import',str(pathlib.Path(a.gzf).resolve()),'-postScript','ExtractStructure.java',str(w/'extraction.json')])
 subprocess.run([sys.executable,str(s/'analyze.py'),'prepare',str(w/'extraction.json'),a.pe,a.gzf,str(o)],check=True)
 gh(['-process','i76exe_v100','-readOnly','-postScript','ExtractStructure.java',str(w/'replay.json')])
 x,y=[json.loads((w/n).read_text()) for n in ['extraction.json','replay.json']]
 for z in [x,y]:
  assert z.pop('modification_before')==z.pop('modification_after')
 assert x==y
 assert (o/'features.json').read_bytes()==(r/'artifacts/features.json').read_bytes()
 source=o/'features.json'
else:source=r/'artifacts/features.json'
subprocess.run([sys.executable,str(s/'analyze.py'),'rank',str(source),str(o)],check=True)
for f in ['ranking.json']:
 assert (o/f).read_bytes()==(r/'artifacts'/f).read_bytes(),f
assert (w/'BOUNDARY_RANKING.md').read_bytes()==(r/'artifacts/BOUNDARY_RANKING.md').read_bytes()
print('PASS: frozen digests and deterministic ranking'+(' plus fresh Ghidra/PE validation' if not a.ranking_only else ' (public inputs only)'))
