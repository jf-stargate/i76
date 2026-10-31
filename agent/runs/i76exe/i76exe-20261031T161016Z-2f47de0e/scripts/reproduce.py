#!/usr/bin/env python3
"""Full accepted PR77 reproduction, then bounded native palette-column experiments."""
import argparse,hashlib,json,os,shutil,struct,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser()
for key in ['source-repo','work','headless','exe','gzf','zfs']:p.add_argument('--'+key,type=Path,required=True)
a=p.parse_args()
for key,v in vars(a).items():setattr(a,key,v.resolve())
assert not a.work.exists(),'use new private work directory'
H={'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'}
for key,h in H.items():assert hashlib.sha256(getattr(a,key).read_bytes()).hexdigest()==h,key
a.work.mkdir(parents=True)
run=a.source_repo/'agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e'
accepted=a.source_repo/'agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808'
with (a.work/'baseline77.log').open('w') as f:
 subprocess.run([sys.executable,str(accepted/'scripts/reproduce.py'),'--source-repo',str(a.source_repo),'--work',str(a.work/'baseline77'),'--headless',str(a.headless),'--exe',str(a.exe),'--gzf',str(a.gzf),'--zfs',str(a.zfs)],stdout=f,stderr=subprocess.STDOUT,check=True)
print('unchanged PR77 baseline passed',flush=True)
fixtures=a.work/'fixtures';shutil.copytree(a.work/'baseline77/baseline/baseline/fixtures',fixtures)
z=a.zfs.read_bytes();cursor=struct.unpack_from('<I',z,24)[0];found=[]
while cursor:
 for i in range(100):
  raw,off,ident,stored,mtime,flags=struct.unpack_from('<16sIIIII',z,cursor+4+36*i)
  if raw.partition(b'\0')[0].lower()==b'm02.act':
   assert flags&255==0 and stored==768
   found.append(z[off:off+stored])
 cursor=struct.unpack_from('<I',z,cursor)[0]
assert len(found)==1 and hashlib.sha256(found[0]).hexdigest()=='d1f57fdef1029e2f2b41d25c2db52f641ada6d55b89342970c50bc49bd9bccb8'
(fixtures/'m02.act').write_bytes(found[0])
env=os.environ.copy();env['XDG_CONFIG_HOME']=str(a.work/'config');env['XDG_CACHE_HOME']=str(a.work/'cache')
project=a.work/'baseline77/baseline/baseline'
def invoke(name,project,kind):
 with (a.work/(name+'.log')).open('w') as f:
  subprocess.run([str(a.headless),str(project),'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',str(run/'scripts'),'-postScript','I76_PaletteProbe.java',str(fixtures),str(a.work/(name+'.tsv')),'visible','workspace-delete-flush',kind],env=env,stdout=f,stderr=subprocess.STDOUT,check=True)
 trace=(a.work/(name+'.tsv')).read_text();log=(a.work/(name+'.log')).read_text()
 if kind=='offset':assert '\tPALETTE_INPUT_BLOCKER\t00479202\tsource=000000E8' in trace and 'TABLE_ORIGINAL_STORE' not in trace and 'SCRIPT ERROR' in log
 elif kind=='palette_raw':assert '\tORIGINAL_FAILURE\t000C0BFC' in trace and 'TABLE_ORIGINAL_STORE' not in trace and 'SCRIPT ERROR' in log
 else:assert '\tTABLE_COLUMN_COMPLETE\t0047951E' in trace and 'SCRIPT ERROR' not in log and '\tFRAMEBUFFER_FINAL\t' in trace
 print(name+' completed',flush=True)
invoke('raw',project,'palette_raw');invoke('positive',project,'diagnostic');invoke('missing',project,'offset')
fresh=a.work/'fresh';fresh.mkdir();shutil.copyfile(a.gzf,fresh/a.gzf.name)
with (a.work/'fresh_import.log').open('w') as f:subprocess.run([str(a.headless),str(fresh),'research','-import',str(fresh/a.gzf.name),'-noanalysis'],env=env,stdout=f,stderr=subprocess.STDOUT,check=True)
assert 'ERROR' not in (a.work/'fresh_import.log').read_text()
invoke('repeat',fresh,'diagnostic')
for suffix in ['.tsv','.tsv.frame','.tsv.guards']:assert (a.work/('positive'+suffix)).read_bytes()==(a.work/('repeat'+suffix)).read_bytes(),suffix
with (a.work/'opcodes.log').open('w') as f:subprocess.run([str(a.headless),str(fresh),'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',str(run/'scripts'),'-postScript','I76_PaletteOpcodeAudit.java',str(a.work/'opcodes.tsv'),str(a.work/'positive.tsv')],env=env,stdout=f,stderr=subprocess.STDOUT,check=True)
assert 'SCRIPT ERROR' not in (a.work/'opcodes.log').read_text()
cmd=[sys.executable,str(run/'scripts/verify_palette.py'),'--trace',str(a.work/'positive.tsv'),'--palette',str(fixtures/'m02.act'),'--exe',str(a.exe),'--audit',str(a.work/'opcodes.tsv'),'--baseline',str(a.work/'baseline77/diagnostic.tsv')]
result=subprocess.check_output(cmd,text=True);(a.work/'verification.json').write_text(result);print(result,flush=True)
