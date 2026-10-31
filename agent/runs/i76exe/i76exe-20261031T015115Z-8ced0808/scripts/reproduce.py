#!/usr/bin/env python3
"""Reproduce accepted PR75, then bounded original surface/raster experiments."""
import argparse, hashlib, os, shutil, subprocess, sys
from pathlib import Path

RUN_ID='i76exe-20261031T015115Z-8ced0808'
BASE_ID='i76exe-20261031T011731Z-307babbf'
HASHES={'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'}
p=argparse.ArgumentParser()
for k in ('source-repo','work','headless','exe','gzf','zfs'):
    p.add_argument('--'+k,type=Path,required=True)
a=p.parse_args()
for k,v in vars(a).items():
    setattr(a,k,v.resolve())
assert not a.work.exists(), 'private work must be new'
for k,h in HASHES.items():
    assert hashlib.sha256(getattr(a,k).read_bytes()).hexdigest()==h,k
a.work.mkdir(parents=True)
run=a.source_repo/'agent/runs/i76exe'/RUN_ID
accepted=a.source_repo/'agent/runs/i76exe'/BASE_ID
baseline=a.work/'baseline'
subprocess.run([sys.executable,str(accepted/'scripts/reproduce.py'),'--source-repo',str(a.source_repo),'--work',str(baseline),'--headless',str(a.headless),'--exe',str(a.exe),'--gzf',str(a.gzf),'--zfs',str(a.zfs)],check=True)
env=os.environ.copy()
env['XDG_CONFIG_HOME']=str(a.work/'config')
env['XDG_CACHE_HOME']=str(a.work/'cache')
def invoke(name,project,mode,kind):
    cmd=[str(a.headless),str(project),'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',str(run/'scripts'),'-postScript','I76_RasterProbe.java',str(baseline/'baseline/fixtures'),str(a.work/(name+'.tsv')),mode,'workspace-delete-flush',kind]
    with (a.work/(name+'.log')).open('w') as log:
        status=subprocess.run(cmd,stdout=log,stderr=subprocess.STDOUT,env=env)
    trace=(a.work/(name+'.tsv')).read_text()
    output=(a.work/(name+'.log')).read_text()
    assert status.returncode==0,name+' Ghidra launcher failed'
    expected={'init_raw':'\tORIGINAL_FAILURE\t000C0FE2','palette_raw':'\tORIGINAL_FAILURE\t000C0BFC','absent':'\tSURFACE_BLOCKER\t0047CC25'}
    if name in expected:
        assert expected[name] in trace and 'SCRIPT ERROR' in output and '\tRASTER_BYTE_WRITE\t' not in trace,name+' expected failure changed'
    else:
        assert 'SCRIPT ERROR' not in output and '\tPRODUCER_COMPLETE\t' in trace,name+' incomplete'
    print(name+' '+('expected blocker' if name in expected else 'completed'),flush=True)
for name,mode,kind in [('init_raw','visible','init_raw'),('palette_raw','visible','palette_raw'),('diagnostic','visible','diagnostic'),('offset','visible','offset'),('behind','behind','diagnostic'),('absent','visible','absent')]:
    invoke(name,baseline/'baseline',mode,kind)
fresh=a.work/'fresh'
fresh.mkdir()
shutil.copyfile(a.gzf,fresh/a.gzf.name)
with (a.work/'fresh_import.log').open('w') as log:
    status=subprocess.run([str(a.headless),str(fresh),'research','-import',str(fresh/a.gzf.name),'-noanalysis'],stdout=log,stderr=subprocess.STDOUT,env=env)
assert status.returncode==0 and 'ERROR' not in (a.work/'fresh_import.log').read_text(),'fresh GZF import'
invoke('fresh_repeat',fresh,'visible','diagnostic')
assert (a.work/'diagnostic.tsv').read_bytes()==(a.work/'fresh_repeat.tsv').read_bytes(),'full original trace fresh equality'
assert (a.work/'diagnostic.tsv.frame').read_bytes()==(a.work/'fresh_repeat.tsv.frame').read_bytes(),'framebuffer fresh equality'
assert (a.work/'diagnostic.tsv.guards').read_bytes()==(a.work/'fresh_repeat.tsv.guards').read_bytes(),'surface guards fresh equality'
with (a.work/'raster_opcodes.log').open('w') as log:
    status=subprocess.run([str(a.headless),str(baseline/'baseline'),'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',str(run/'scripts'),'-postScript','I76_RasterOpcodeAudit.java',str(a.work/'raster_opcodes.tsv'),str(a.work/'diagnostic.tsv')],stdout=log,stderr=subprocess.STDOUT,env=env)
assert status.returncode==0 and 'SCRIPT ERROR' not in (a.work/'raster_opcodes.log').read_text(),'opcode audit'
subprocess.run([sys.executable,str(run/'scripts/verify_raster.py'),'--private',str(a.work),'--exe',str(a.exe),'--gzf',str(a.gzf),'--zfs',str(a.zfs),'--corruptions'],check=True)
