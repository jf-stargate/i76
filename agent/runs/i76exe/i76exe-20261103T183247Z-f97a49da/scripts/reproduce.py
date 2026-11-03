#!/usr/bin/env python3
"""Extract into a NEW PRIVATE directory; never point this at the maintainer's project."""
import argparse,hashlib,json,os,pathlib,subprocess
p=argparse.ArgumentParser();p.add_argument('--headless',required=True);p.add_argument('--gzf',required=True);p.add_argument('--exe',required=True);p.add_argument('--work',required=True);a=p.parse_args()
def digest(p):return hashlib.sha256(pathlib.Path(p).read_bytes()).hexdigest()
assert digest(a.gzf)=='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'
assert digest(a.exe)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
w=pathlib.Path(a.work).absolute();w.mkdir(exist_ok=False);(w/'project').mkdir();(w/'home').mkdir()
scripts=pathlib.Path(__file__).resolve().parent
env=os.environ.copy();env['JAVA_TOOL_OPTIONS']='-Duser.home='+str(w/'home')
common=[a.headless,str(w/'project'),'pilot2']
def run(args,name):
 with open(w/(name+'.log'),'w') as f:subprocess.run(common+args,stdout=f,stderr=subprocess.STDOUT,env=env,check=True)
run(['-import',str(pathlib.Path(a.gzf).resolve()),'-noanalysis'],'import')
def snapshot():return {str(x.relative_to(w/'project')):digest(x) for x in sorted((w/'project').rglob('*')) if x.is_file() and x.suffix!='.lock'}
before=snapshot();(w/'db-before.json').write_text(json.dumps(before,indent=2)+'\n')
for c in ['capture1','capture2']:
 run(['-process','i76exe_v100','-readOnly','-noanalysis','-scriptPath',str(scripts),'-postScript','TUInventory.java',str(w/c)],c)
run(['-process','i76exe_v100','-readOnly','-noanalysis','-scriptPath',str(scripts),'-postScript','TUValidate.java',str(w/'envelopes.json')],'envelopes')
after=snapshot();same=[k for k in before if k.endswith('.gbf') and before[k]==after.get(k)]
r=dict(repeat_equal={n:digest(w/'capture1'/n)==digest(w/'capture2'/n) for n in ['inventory.jsonl','detail.jsonl','metadata.json']},unchanged_program_database_files=same,changed_project_housekeeping=[k for k in before.keys()|after.keys() if before.get(k)!=after.get(k)],input_gzf_after=digest(a.gzf),input_exe_after=digest(a.exe))
assert same and all(r['repeat_equal'].values())
(w/'reproduction.json').write_text(json.dumps(r,indent=2)+'\n');print(json.dumps(r,indent=2))
