#!/usr/bin/env python3
"""Fresh private import, retail extraction and four sequential original-code probes."""
import argparse,hashlib,json,shutil,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser()
for n in ['source-repo','work','headless','exe','gzf','zfs']:p.add_argument('--'+n,type=Path,required=True)
a=p.parse_args()
for k,v in vars(a).items():setattr(a,k,v.resolve())
scripts=Path(__file__).resolve().parent
expected={'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'}
for k,v in expected.items():assert hashlib.sha256(getattr(a,k).read_bytes()).hexdigest()==v,k
assert not a.work.is_relative_to(a.source_repo),'private work must be outside checkout'
a.work.mkdir(parents=True,exist_ok=False)
def run(cmd,name):
 with (a.work/(name+'.log')).open('w') as f:r=subprocess.run([str(x) for x in cmd],stdout=f,stderr=subprocess.STDOUT)
 log=(a.work/(name+'.log')).read_text()
 assert r.returncode==0 and 'ERROR' not in log,name+' failed; inspect private log'
old=a.source_repo/'agent/runs/i76exe/i76exe-20261022T232710Z-96c58505'
run([sys.executable,old/'scripts/extract_private_fixtures.py','--zfs',a.zfs,'--out',a.work/'fixtures','--metadata',old/'evidence/retail_resource_digests.json'],'extract')
shutil.copyfile(a.gzf,a.work/a.gzf.name)
run([a.headless,a.work,'research','-import',a.work/a.gzf.name,'-noanalysis'],'import')
assert 'Import succeeded' in (a.work/'import.log').read_text()
for name,mode in [('visible','visible'),('repeat','visible'),('behind','behind'),('empty','empty')]:
 run([a.headless,a.work,'research','-process','i76_mission_v97_verified_names','-readOnly','-noanalysis','-scriptPath',scripts,'-postScript','I76_VisibilityProducerProbe.java',a.work/'fixtures',a.work/(name+'.tsv'),mode],name)
 assert '\tPRODUCER_COMPLETE\t' in (a.work/(name+'.tsv')).read_text(),name
 print(name+': original producer returned',flush=True)
print('Fresh replay complete; run verify_producer.py.',flush=True)
