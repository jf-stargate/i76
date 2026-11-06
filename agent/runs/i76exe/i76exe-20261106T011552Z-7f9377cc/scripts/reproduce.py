#!/usr/bin/env python3
"""Licensed local inputs required. Creates a new private project; never ships payloads."""
import argparse,hashlib,json,os,subprocess
from pathlib import Path
p=argparse.ArgumentParser()
for k in ['headless','exe','gzf','zfs','msn','ter','work','repo']:p.add_argument('--'+k,required=True)
p.add_argument('--cases',nargs='+',default=['primary','contrast','below','x2952.6','x2953.5','x2957.5','z47996.4','z47996.6','z47999.9','z48000.1']);a=p.parse_args();run=Path(__file__).resolve().parents[1];work=Path(a.work).resolve();repo=Path(a.repo).resolve();assert not work.exists();work.mkdir(parents=True)
manifest=json.loads((run/'manifest.json').read_text())
for key,name in [('exe','i76.exe'),('zfs','I76.ZFS'),('msn','miss8/M06.MSN'),('ter','miss8/M06.TER')]:
 expected=next(x for x in manifest['inputs'] if x['name']==name);b=Path(getattr(a,key)).read_bytes();assert hashlib.sha256(b).hexdigest()==expected['sha256'] and hashlib.md5(b).hexdigest()==expected['md5']
assert hashlib.sha256(Path(a.gzf).read_bytes()).hexdigest()==manifest['baselines'][0]['baseline_sha256']
env=os.environ|{'XDG_CONFIG_HOME':str(work/'config'),'XDG_CACHE_HOME':str(work/'cache')}
def call(cmd,name):
 with (work/(name+'.log')).open('w') as f:subprocess.run(list(map(str,cmd)),stdout=f,stderr=subprocess.STDOUT,env=env,check=True)
extract=repo/'agent/runs/i76exe/i76exe-20261022T232710Z-96c58505';call(['python3',extract/'scripts/extract_private_fixtures.py','--zfs',a.zfs,'--out',work/'fixtures','--metadata',extract/'evidence/retail_resource_digests.json'],'extract');call(['cc','-O2',run/'scripts/x87_terrain_service.c','-o',work/'x87_terrain_service'],'cc');(work/'project').mkdir();(work/'cases').mkdir()
call([a.headless,work/'project','topology','-import',a.gzf,'-noanalysis','-scriptPath',run/'scripts','-postScript','I76_TopologyAudit.java',a.exe,work/'audit.txt'],'audit');assert (work/'audit.txt').read_text().startswith('CODE_EQUAL')
for case in a.cases:
 call([a.headless,work/'project','topology','-process','i76exe_v100','-readOnly','-noanalysis','-scriptPath',run/'scripts','-postScript','I76_TopologyProbe.java',work/'fixtures',work/'cases'/f'{case}.tsv','bus',a.msn,a.ter,work/'x87_terrain_service',case],case)
 print(case,'executed',flush=True)
call(['python3',run/'scripts/verify_topology.py','--cases',work/'cases','--msn',a.msn,'--ter',a.ter,'--emit',work/'derived'],'verify')
expected=json.loads((run/'evidence/geometry_comparisons.json').read_text())['scenarios'];actual=json.loads((work/'derived/geometry_comparisons.json').read_text())['scenarios']
for case in a.cases:assert actual[case]==expected[case],case
print('All requested scenario summaries match publication.',flush=True)
