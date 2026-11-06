#!/usr/bin/env python3
"""Asset-free check of the published bounded original topology fixtures."""
import hashlib,json,struct
from pathlib import Path
r=Path(__file__).resolve().parents[1];graphs=json.loads((r/'evidence/edge_graph.json').read_text());N=0
def ck(v):
 global N
 N+=1
 assert v
for name,g in graphs.items():
 edges={int(p):e for p,e in g['edges'].items()};vertices=g['vertices'];loops={int(p):v for p,v in g['flattened'].items()}
 def flat(p,rev=False):
  a,b,c,d=edges[p]
  if not c:return [b if rev else a]
  return flat(d,True)+flat(c,True) if rev else flat(c)+flat(d)
 for p,rec in g['leaves']:
  a,b,c,d=rec[4:];ck(flat(c)+flat(b)+flat(d,True)+flat(a,True)==loops[p])
 for a,b,c,d in edges.values():
  ck(bool(c)==bool(d))
  if c:
   A,B=edges[c],edges[d];ck(A[0]==a and B[1]==b and A[1]==B[0]);v=vertices[A[1]];ck(v[0]==(vertices[a][0]+vertices[b][0])/2 and v[2]==(vertices[a][2]+vertices[b][2])/2)
 for line in (r/'evidence/polygons.jsonl').read_text().splitlines():
  p=json.loads(line)
  if p['case']!=name:continue
  ck(p['boundary_loop']==loops[p['leaf']]);ck(p['work_source_indices']==p['indices'][::-1])
  for attr in p['source_attributes']:
   v=vertices[attr['index']];ck([struct.unpack('<I',struct.pack('<f',x))[0] for x in v]==attr['source_xyz_bits']);ck(v[1]==attr['packed_word']&4095)
if (r/'manifest.json').exists():
 m=json.loads((r/'manifest.json').read_text())
 for item in m['artifacts']:
  data=(r/item['path']).read_bytes();ck(len(data)==item['bytes'] and hashlib.sha256(data).hexdigest()==item['sha256'])
print(json.dumps({'status':'passed','checks':N,'scope':'public graph/midpoint/flatten/source/emitter reversal and manifest hashes'}))
