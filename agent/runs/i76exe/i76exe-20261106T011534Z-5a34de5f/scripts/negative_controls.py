#!/usr/bin/env python3
"""Ensure the independent verifier rejects corrupted addresses and CPU results."""
import argparse,pathlib,tempfile,subprocess,sys,json
p=argparse.ArgumentParser()
for k in ['private','orig','gzf','run']:p.add_argument('--'+k,type=pathlib.Path,required=True)
a=p.parse_args()
for k in vars(a):setattr(a,k,getattr(a,k).resolve())
checks=[]
for mode in ['address','cpu']:
 with tempfile.TemporaryDirectory(prefix='negative-',dir=a.private) as tmp:
  t=pathlib.Path(tmp)
  for f in list(a.private.iterdir()):
   if f!=t and not f.name.startswith('negative-'):(t/f.name).symlink_to(f,target_is_directory=f.is_dir())
  if mode=='address':
   f=t/'M06.tsv';s=f.read_text();lines=s.splitlines()
   for i,l in enumerate(lines):
    if '\tREAD\t004931A4\t' in l:
     before,after=l.split(';address=',1);addr,rest=after.split(';',1);lines[i]=before+';address='+f'{int(addr,16)+2:08X}'+';'+rest;break
   else:raise AssertionError('no address row')
   f.unlink();f.write_text('\n'.join(lines)+'\n')
  else:
   f=t/'native_M06';f.unlink();f.mkdir();rows=json.loads((a.private/'native_M06/native.json').read_text())
   for row in rows:
    if row['kind']=='sample':row['value']^=1;break
   (f/'native.json').write_text(json.dumps(rows))
  cmd=[sys.executable,str(a.run/'scripts/verify_coordinates.py'),'--private',str(t),'--orig',str(a.orig),'--gzf',str(a.gzf),'--run',str(a.run)]
  result=subprocess.run(cmd,capture_output=True,text=True)
  assert result.returncode!=0 and 'AssertionError' in result.stderr,result.stderr
  checks.append({'control':mode,'rejected':True,'reason':result.stderr.strip().splitlines()[-1]})
(a.run/'evidence/negative_controls.json').write_text(json.dumps({'passed':len(checks),'failed':0,'checks':checks},indent=2)+'\n')
print(json.dumps(checks))
