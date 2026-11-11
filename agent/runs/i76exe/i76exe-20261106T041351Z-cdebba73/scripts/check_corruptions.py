#!/usr/bin/env python3
"""Mutate observed decisions; independent verifier must reject each mutation."""
import argparse,json,subprocess,sys,tempfile
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--cases',type=Path,required=True);p.add_argument('--exe',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args();results={}
for kind,field in [('EMITTER_ENTER','indices'),('ANCHOR','index'),('TURN_TEST','score'),('BIN_RETURN','cursor'),('SHADE_TEST','first')]:
 case='shade' if kind=='SHADE_TEST' else 'primary';source=a.cases/(case+'.tsv');lines=source.read_text().splitlines();done=False
 for k,line in enumerate(lines):
  cells=line.split('\t')
  if len(cells)!=4 or cells[1]!=kind:continue
  fields=cells[3].split(';')
  for j,f in enumerate(fields):
   if f.startswith(field+'='):
    v=f.split('=',1)[1];fields[j]=field+'='+('FFFFFFFF' if field in ['cursor','indices'] else str(int(v)+1) if field in ['score','index'] else f'{int(v,16)^0x100:08X}');done=True;break
  if done:cells[3]=';'.join(fields);lines[k]='\t'.join(cells);break
 assert done
 with tempfile.TemporaryDirectory(prefix='i76-walker-negative-') as td:
  w=Path(td);(w/source.name).write_text('\n'.join(lines)+'\n')
  for s in a.cases.glob(source.name+'.*'):(w/s.name).symlink_to(s.resolve())
  q=subprocess.run([sys.executable,str(Path(__file__).with_name('verify.py')),'--cases',str(w),'--exe',str(a.exe),'--out',str(w/'out')],text=True,capture_output=True)
  assert q.returncode and 'AssertionError' in q.stderr,(kind,q.stdout,q.stderr)
  results[kind]={'rejected':True,'failure':q.stderr.splitlines()[-1]}
a.out.write_text(json.dumps(results,indent=2)+'\n');print(results)
