#!/usr/bin/env python3
"""Asset-free predictive regression against original-observed decisions."""
import collections,copy,hashlib,json,struct
from pathlib import Path
from walker import Numerics,walk
r=Path(__file__).resolve().parents[1]
class Constants(Numerics):
 def __init__(self,constants):self.constants=constants
 def value(self,va,fmt):return self.constants[str(va)]
def predict(f):
 view=bytearray(472)
 for off,values in f['projection'].items():struct.pack_into('<'+'f'*len(values),view,int(off),*values)
 return walk({int(k):v for k,v in f['edges'].items()},f['leaves'],f['vertices'],view,f['light'],f['ambient'],f['attenuation'],f['scale'],Constants(f['constants']),f['high'])
def compare(pred,expected):
 assert len(pred)==len(expected)
 for p,e in zip(pred,expected):
  for field in ['leaf','boundary','anchor','anchor_reason','turn_score','turn_target','shade_bands','fallback_reason','whole_planes','filtered_triangles']:assert p[field]==e[field],field
  assert len(p['attempts'])==len(e['attempts'])
  for a,b in zip(p['attempts'],e['attempts']):
   for field in ['indices','kind','shade','accepted','clip_count','rejection','return_value','depth']:assert a[field]==b[field],field
   original=b['original'];assert a['indices']==original['indices'] and a['accepted']==original['accepted'] and a['clip_count']==original['clip_count'] and a['return_value']==original['return_value'] and a['rejection']==original['rejection']
   assert abs(a['shade']-original['shade'])<=2e-6
expected=collections.defaultdict(list)
for line in (r/'evidence/decisions.jsonl').read_text().splitlines():
 x=json.loads(line);expected[x['case']].append(x)
checks=0
for path in sorted((r/'evidence').glob('*.fixture.json')):
 case=path.name.split('.')[0];f=json.loads(path.read_text());p=predict(f);compare(p,expected[case]);checks+=len(p)+sum(len(x['attempts']) for x in p)
 # Ensure comparator rejects plausible corruption of scientific claims.
 for field,value in [('anchor',-1),('turn_score',999),('fallback_reason','invented')]:
  altered=copy.deepcopy(expected[case]);altered[0][field]=value
  try:compare(p,altered)
  except AssertionError:checks+=1
  else:raise AssertionError('corruption accepted '+field)
 for field,value in [('indices',[-1,-2,-3]),('accepted',None),('rejection','invented')]:
  altered=copy.deepcopy(expected[case]);first=next(x for x in altered if x['attempts']);first['attempts'][0][field]=value
  try:compare(p,altered)
  except AssertionError:checks+=1
  else:raise AssertionError('corruption accepted '+field)
 print(case,'predictive fixture passed')
m=json.loads((r/'manifest.json').read_text())
for entry in m['artifacts']:
 b=(r/entry['path']).read_bytes();assert hashlib.sha256(b).hexdigest()==entry['sha256'] and len(b)==entry['bytes'];checks+=1
print(checks,'asset-free predictive/negative/hash checks passed')
