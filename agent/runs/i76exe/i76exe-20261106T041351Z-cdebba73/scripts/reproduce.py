#!/usr/bin/env python3
"""New private project, authenticated licensed inputs, original observer and oracle."""
import argparse,hashlib,json,os,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser()
for key in ['headless','exe','gzf','zfs','msn','ter','repo','work']:p.add_argument('--'+key,type=Path,required=True)
p.add_argument('--cases',nargs='+');a=p.parse_args();r=Path(__file__).resolve().parents[1];m=json.loads((r/'manifest.json').read_text());w=a.work.resolve();assert not w.exists();w.mkdir(parents=True)
for key,name in [('exe','i76.exe'),('zfs','I76.ZFS'),('msn','miss8/M06.MSN'),('ter','miss8/M06.TER')]:
 b=getattr(a,key).read_bytes();e=next(x for x in m['inputs'] if x['name']==name);assert hashlib.sha256(b).hexdigest()==e['sha256'] and hashlib.md5(b).hexdigest()==e['md5']
assert hashlib.sha256(a.gzf.read_bytes()).hexdigest()==m['baselines'][0]['baseline_sha256']
env=os.environ|{'XDG_CONFIG_HOME':str(w/'config'),'XDG_CACHE_HOME':str(w/'cache')}
def run(cmd,name):
 with (w/(name+'.log')).open('w') as f:subprocess.run(list(map(str,cmd)),stdout=f,stderr=subprocess.STDOUT,env=env,check=True)
extract=a.repo/'agent/runs/i76exe/i76exe-20261022T232710Z-96c58505'
run([sys.executable,extract/'scripts/extract_private_fixtures.py','--zfs',a.zfs,'--out',w/'fixtures','--metadata',extract/'evidence/retail_resource_digests.json'],'extract')
run(['cc','-O2',r/'scripts/x87_terrain_service.c','-o',w/'x87_terrain_service'],'cc');(w/'project').mkdir();(w/'cases').mkdir()
run([a.headless,w/'project','emission','-import',a.gzf,'-noanalysis','-scriptPath',r/'scripts','-postScript','I76_TopologyAudit.java',a.exe,w/'audit.txt'],'audit');assert (w/'audit.txt').read_text().startswith('CODE_EQUAL')
expected=json.loads((r/'evidence/verification.json').read_text())['scenarios'];cases=a.cases or sorted(expected)
run([sys.executable,r/'scripts/observe.py','--headless',a.headless,'--work',w,'--msn',a.msn,'--ter',a.ter,'--cases',*cases],'observe')
run([sys.executable,r/'scripts/verify.py','--cases',w/'cases','--exe',a.exe,'--out',w/'derived'],'verify')
actual=json.loads((w/'derived/verification.json').read_text())['scenarios']
for case in cases:assert actual[case]==expected[case],case
print('Original trace and independent scenario predictions match publication:',','.join(cases))
