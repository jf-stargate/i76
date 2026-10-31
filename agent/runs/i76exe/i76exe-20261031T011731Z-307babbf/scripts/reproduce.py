#!/usr/bin/env python3
"""Fresh accepted baseline, native draw, native finalizer, controls and fresh imports."""
import argparse,hashlib,json,os,shutil,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser()
for k in ['source-repo','work','headless','exe','gzf','zfs']:p.add_argument('--'+k,type=Path,required=True)
a=p.parse_args()
for k,v in vars(a).items():setattr(a,k,v.resolve())
assert not a.work.exists()
scripts=Path(__file__).resolve().parent
expected={'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'}
for k,h in expected.items():assert hashlib.sha256(getattr(a,k).read_bytes()).hexdigest()==h,k
a.work.mkdir()
old=a.source_repo/'agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/scripts/reproduce.py'
args=[x for k,v in vars(a).items() for x in ['--'+k.replace('_','-'),str(a.work/'baseline') if k=='work' else str(v)]]
subprocess.run([sys.executable,str(old),*args],check=True)
os.environ['XDG_CONFIG_HOME']=str(a.work/'config');os.environ['XDG_CACHE_HOME']=str(a.work/'cache')
def run(cmd,name):
 with (a.work/(name+'.log')).open('w') as f:r=subprocess.run([str(x) for x in cmd],stdout=f,stderr=subprocess.STDOUT)
 assert r.returncode==0,name
 return (a.work/(name+'.log')).read_text()
# Remove the draw replacement first; then supply one measured dependency at a time.
for name,option,marker in [('raw',None,'\tORIGINAL_FAILURE\t000C0DD2'),('heap','heap','\tDRAW_BLOCKER\t00473788'),('workspace','workspace','\tORIGINAL_FAILURE\t000C0DC2')]:
 cmd=[a.headless,a.work/'baseline','research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',scripts,'-postScript','I76_DrawBoundaryProbe.java',a.work/'baseline/fixtures',a.work/(name+'.tsv'),'visible']
 if option:cmd.append(option)
 run(cmd,name)
 assert marker in (a.work/(name+'.tsv')).read_text() and '\tPRODUCER_COMPLETE\t' not in (a.work/(name+'.tsv')).read_text(),name
for case,mode in [('visible','visible'),('behind','behind'),('repeat','visible'),('flush','visible'),('flush_repeat','visible')]:
 project=a.work/'baseline'
 if case in ['repeat','flush_repeat']:
  project=a.work/('fresh-'+case);project.mkdir();shutil.copyfile(a.gzf,project/a.gzf.name)
  assert 'ERROR' not in run([a.headless,project,'research','-import',project/a.gzf.name,'-noanalysis'],case+'-import')
 log=run([a.headless,project,'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',scripts,'-postScript','I76_DrawBoundaryProbe.java',a.work/'baseline/fixtures',a.work/(case+'.tsv'),mode,'workspace-delete-flush' if case.startswith('flush') else 'workspace-delete'],case)
 assert 'ERROR' not in log and '\tPRODUCER_COMPLETE\t' in (a.work/(case+'.tsv')).read_text(),case
 print(case+' completed',flush=True)
for c,r in [('visible','repeat'),('flush','flush_repeat')]:assert (a.work/(c+'.tsv')).read_bytes()==(a.work/(r+'.tsv')).read_bytes()
run([a.headless,a.work/'baseline','research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',scripts,'-postScript','I76_DrawOpcodeAudit.java',a.work/'opcodes.tsv',a.work/'visible.tsv',a.work/'flush.tsv'],'opcodes')
subprocess.run([sys.executable,str(scripts/'audit_retail.py'),'--source-repo',str(a.source_repo),'--private',str(a.work),'--exe',str(a.exe),'--out',str(a.work/'retail_opcodes.json')],check=True)
assert (a.work/'retail_opcodes.json').read_bytes()==(scripts.parent/'evidence/retail_opcodes.json').read_bytes()
subprocess.run([sys.executable,str(scripts/'verify_draw.py'),'--source-repo',str(a.source_repo),'--private',str(a.work),'--exe',str(a.exe),'--corruptions'],check=True)
