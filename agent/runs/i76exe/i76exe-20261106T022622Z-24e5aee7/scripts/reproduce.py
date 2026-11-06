#!/usr/bin/env python3
"""Authenticate licensed inputs, fresh-import baseline, run all owned observers."""
import argparse,hashlib,json,subprocess,os
from pathlib import Path
p=argparse.ArgumentParser()
for n in ['headless','exe','gzf','zfs','msn','ter','work','repo']:p.add_argument('--'+n,type=Path,required=True)
a=p.parse_args();r=Path(__file__).resolve().parents[1];w=a.work.resolve();assert not w.exists()
manifest=json.loads((r/'manifest.json').read_text())
for key,name in [('exe','i76.exe'),('zfs','I76.ZFS'),('msn','miss8/M06.MSN'),('ter','miss8/M06.TER')]:
    b=getattr(a,key).read_bytes();exp=next(v for v in manifest['inputs'] if v['name']==name)
    assert hashlib.sha256(b).hexdigest()==exp['sha256'] and hashlib.md5(b).hexdigest()==exp['md5']
assert hashlib.sha256(a.gzf.read_bytes()).hexdigest()==manifest['baselines'][0]['baseline_sha256']
w.mkdir(parents=True);(w/'project').mkdir();(w/'cases').mkdir()
env=os.environ|{'XDG_CONFIG_HOME':str(w/'config'),'XDG_CACHE_HOME':str(w/'cache')}
def call(cmd,name):
    with (w/(name+'.log')).open('w') as f:subprocess.run(list(map(str,cmd)),stdout=f,stderr=subprocess.STDOUT,env=env,check=True)
extract=a.repo/'agent/runs/i76exe/i76exe-20261022T232710Z-96c58505'
call(['python3',extract/'scripts/extract_private_fixtures.py','--zfs',a.zfs,'--out',w/'fixtures','--metadata',extract/'evidence/retail_resource_digests.json'],'extract')
call(['cc','-O2',r/'scripts/x87_terrain_service.c','-o',w/'x87_terrain_service'],'cc')
call([a.headless,w/'project','camera','-import',a.gzf,'-noanalysis','-scriptPath',r/'scripts','-postScript','I76_TopologyAudit.java',a.exe,w/'audit.txt'],'audit')
assert (w/'audit.txt').read_text().startswith('CODE_EQUAL')
call(['python3',r/'scripts/replay.py','--headless',a.headless,'--work',w,'--fixtures',w/'fixtures','--msn',a.msn,'--ter',a.ter],'emulate')
call(['python3',r/'scripts/native_replay.py','--exe',a.exe,'--msn',a.msn,'--ter',a.ter,'--cases',w/'cases','--out',w/'native'],'native')
call(['python3',r/'scripts/compare.py','--extract','--cases',w/'cases','--msn',a.msn,'--ter',a.ter,'--native',w/'native/native.json','--emit-dir',w/'derived'],'compare')
actual=json.loads((w/'derived/comparison.json').read_text());expected=json.loads((r/'evidence/comparison.json').read_text());assert actual==expected
call(['python3',r/'scripts/check_downstream.py','--cases',w/'cases','--msn',a.msn,'--ter',a.ter,'--fixtures',w/'derived/camera_fixtures.json','--emit',w/'derived/downstream.json'],'downstream')
print('Fresh replay matches all published camera comparisons.',flush=True)
