#!/usr/bin/env python3
"""Accepted baseline prerequisite followed by exact one-substitution removal."""
import argparse,os,shutil,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser()
for k in ['source-repo','work','headless','exe','gzf','zfs']:p.add_argument('--'+k,type=Path,required=True)
a=p.parse_args()
for k,v in vars(a).items():setattr(a,k,v.resolve())
assert not a.work.exists()
scripts=Path(__file__).resolve().parent
old=a.source_repo/'agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe'
args=[item for k,v in vars(a).items() for item in ['--'+k.replace('_','-'),str(v)]]
subprocess.run([sys.executable,str(old/'scripts/reproduce.py'),*args],check=True)
verify=[sys.executable,str(old/'scripts/verify_integration.py'),'--run',str(old),'--source-repo',str(a.source_repo),'--private',str(a.work),'--exe',str(a.exe),'--gzf',str(a.gzf),'--zfs',str(a.zfs)]
with (a.work/'baseline_verification.json').open('w') as f:subprocess.run(verify,stdout=f,check=True)
os.environ['XDG_CONFIG_HOME']=str(a.work/'config');os.environ['XDG_CACHE_HOME']=str(a.work/'cache')
def run(cmd,name):
 with (a.work/(name+'.log')).open('w') as f:r=subprocess.run([str(x) for x in cmd],stdout=f,stderr=subprocess.STDOUT)
 assert r.returncode==0 and 'ERROR' not in (a.work/(name+'.log')).read_text(),name
for name,mode in [('native_visible','visible'),('native_behind','behind'),('native_repeat','visible')]:
 project=a.work
 if name=='native_repeat':
  project=a.work/'native_repeat_project';project.mkdir();shutil.copyfile(a.gzf,project/a.gzf.name)
  run([a.headless,project,'research','-import',project/a.gzf.name,'-noanalysis'],'native_repeat_import')
 run([a.headless,project,'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',scripts,'-postScript','I76_PolygonBoundaryProbe.java',a.work/'fixtures',a.work/(name+'.tsv'),mode],name)
 assert '\tPRODUCER_COMPLETE\t' in (a.work/(name+'.tsv')).read_text(),name
 print(name+' completed',flush=True)
run([a.headless,a.work,'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',scripts,'-postScript','I76_CameraSourceAudit.java',a.work/'clip_audit.txt','00471fd0','0047c8d0','0047ce40','0047bf00','0047d110','0047c2f0','00487ea0'],'clip_audit')
print('Fresh baseline and polygon execution complete. Run verify_polygon.py.',flush=True)
subprocess.run([sys.executable,str(scripts/'audit_dispatch.py'),'--source-repo',str(a.source_repo),'--private',str(a.work),'--exe',str(a.exe),'--out',str(a.work/'retail_dispatch.json')],check=True)
assert (a.work/'retail_dispatch.json').read_bytes()==(scripts.parent/'evidence/retail_dispatch.json').read_bytes()
subprocess.run([sys.executable,str(scripts/'verify_polygon.py'),'--source-repo',str(a.source_repo),'--private',str(a.work),'--exe',str(a.exe),'--gzf',str(a.gzf),'--zfs',str(a.zfs),'--negative-controls'],check=True)
