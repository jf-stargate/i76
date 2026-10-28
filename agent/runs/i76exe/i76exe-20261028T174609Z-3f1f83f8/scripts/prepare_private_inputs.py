#!/usr/bin/env python3
"""Reuse the accepted extractor, then add hash-verified M06 WRLD support inputs.
All extracted bytes must remain in private scratch, outside the public checkout.
"""
import argparse,hashlib,importlib.util,json,subprocess,sys
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--source-repo',type=Path,required=True);p.add_argument('--zfs',type=Path,required=True);p.add_argument('--msn',type=Path,required=True);p.add_argument('--ter',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
assert sha(a.zfs)=='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'
assert sha(a.msn)=='923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f'
assert sha(a.ter)=='fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea'
old=a.source_repo/'agent/runs/i76exe/i76exe-20261022T232710Z-96c58505'
extractor=old/'scripts/extract_private_fixtures.py'
subprocess.run([sys.executable,str(extractor),'--zfs',str(a.zfs),'--out',str(a.out),'--metadata',str(old/'evidence/retail_resource_digests.json')],check=True)
spec=importlib.util.spec_from_file_location('accepted_extractor',extractor);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
z=a.zfs.read_bytes();reader=m.Reader(z);records={r['name'].lower():r for r in m.read_records(z)}
for name in ['t01.act','t01.lum','t01.tbl','engsnd.dat']:
 r=records[name]
 if r['mode']==0:
  # Retail raw ACT record uses zero in the compressed-logical-size field.
  raw=z[r['off']:r['off']+r['stored']];assert r['logical'] in (0,len(raw))
 else:raw=reader.extract(r)
 (a.out/name).write_bytes(raw)
print(json.dumps({p.name:{'bytes':p.stat().st_size,'sha256':sha(p)} for p in sorted(a.out.iterdir()) if p.is_file()},indent=2))
