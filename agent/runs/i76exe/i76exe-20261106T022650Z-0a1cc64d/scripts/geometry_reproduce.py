#!/usr/bin/env python3
"""Fresh owned Ghidra project, immutable #140 original observer, explicit variants."""
import argparse,hashlib,json,os,subprocess,shutil
from pathlib import Path
p=argparse.ArgumentParser()
for k in ['headless','exe','gzf','zfs','msn','ter','work']:p.add_argument('--'+k,required=True,type=Path)
a=p.parse_args();r=Path(__file__).resolve().parents[1];repo=r.parents[3];prior=r.parent/'i76exe-20261106T011552Z-7f9377cc';w=a.work.resolve();w.mkdir(parents=True,exist_ok=False)
m=json.loads((prior/'manifest.json').read_text())
for key,name in [('exe','i76.exe'),('zfs','I76.ZFS'),('msn','miss8/M06.MSN'),('ter','miss8/M06.TER')]:assert hashlib.sha256(getattr(a,key).read_bytes()).hexdigest()==next(v['sha256'] for v in m['inputs'] if v['name']==name)
assert hashlib.sha256(a.gzf.read_bytes()).hexdigest()==m['baselines'][0]['baseline_sha256']
env=os.environ|{'XDG_CONFIG_HOME':str(w/'config'),'XDG_CACHE_HOME':str(w/'cache')}
def call(cmd,name):
 with (w/(name+'.log')).open('w') as f:subprocess.run(list(map(str,cmd)),stdout=f,stderr=subprocess.STDOUT,check=True,env=env)
extract=repo/'agent/runs/i76exe/i76exe-20261022T232710Z-96c58505'
call(['python3',extract/'scripts/extract_private_fixtures.py','--zfs',a.zfs.resolve(),'--out',w/'fixtures','--metadata',extract/'evidence/retail_resource_digests.json'],'extract')
call(['cc','-O2',prior/'scripts/x87_terrain_service.c','-o',w/'x87_terrain_service'],'cc')
(w/'project').mkdir();(w/'cases').mkdir();(w/'scripts').mkdir()
for name in ['I76_CameraBase.java','I76_TopologyProbe.java','I76_TopologyAudit.java']:shutil.copyfile(prior/'scripts'/name,w/'scripts'/name)
# Add pre-read allocation guards to the private observer copy only. Original
# instructions, accepted scripts and all published prior runs remain unchanged.
observer=w/'scripts/I76_TopologyProbe.java';text=observer.read_text()
needle='log("MATERIAL_PREDICATE_READ",pc,'
assert text.count(needle)==1
text=text.replace(needle,'if(!((ptr>=TER&&ptr+2<=TER+terrainBytes.length)||(ptr>=0x59c588L&&ptr+2<=0x5a4588L)))throw new Exception("blocked unowned adaptive read "+hx(ptr));'+needle)
observer.write_text(text)
shutil.copyfile(r/'scripts/BoundaryGeometryProbe.java',w/'scripts/BoundaryGeometryProbe.java');sp=str(w/'scripts')
call([a.headless,w/'project','boundary','-import',a.gzf.resolve(),'-noanalysis','-scriptPath',sp,'-postScript','I76_TopologyAudit.java',a.exe.resolve(),w/'audit.txt'],'audit')
assert (w/'audit.txt').read_text().startswith('CODE_EQUAL')
for variant in ['retail','clear','class2','class5','alias','default']:
 call([a.headless,w/'project','boundary','-process','i76exe_v100','-readOnly','-noanalysis','-scriptPath',sp,'-postScript','BoundaryGeometryProbe.java',w/'fixtures',w/'cases'/(variant+'.tsv'),'bus',a.msn.resolve(),a.ter.resolve(),w/'x87_terrain_service',variant],variant)
 trace=(w/'cases'/(variant+'.tsv')).read_text();assert 'COHERENT_COMPLETE' in trace and '\tBLOCKER\t' not in trace
 print(variant,'complete',flush=True)
