"""Standard-library bounded TU evidence; full inventory input stays private."""
import re,json,sys,pathlib,collections
rows=[]
for line in pathlib.Path(sys.argv[1]).read_text().splitlines()[1:]:
 a,n,size,ranges,raw=line.split('\t'); refs=[]
 for chunk in raw.split('|'):
  m=re.fullmatch(r'([0-9a-f]{8}):([^:]+):([0-9a-f]{8}):(.*)',chunk)
  if m: refs.append(m.groups())
 ends=re.findall(r'([0-9a-f]{8})',ranges)
 rows.append(dict(entry=a,name=n,size=int(size),end=max(ends),refs=refs))
by={r['entry']:r for r in rows}
def calls(r):return {t for _,k,t,_ in r['refs'] if 'CALL' in k and t in by}
def data(r):return {t for _,k,t,_ in r['refs'] if k in ('READ','WRITE','READ_WRITE','DATA') and int(t,16)>=0x4c2000}
groups={'TU_TER_01':['004927b0','00493080','00493160','004931c0','00493550'], 'TU_TER_02':['00493910','00493960','004939d0','00493bd0'], 'TU_FSM_01':['00410490','004105a0','00410720','00412500','004125c0'], 'TU_FSM_02':['00412cc0','00412ce0','00414670','004149f0'], 'TU_RES_01':['0046fee0','0046ffc0','00470070','004702d0','00470340'], 'TU_RES_02':['00470660','00470ac0','00470b20'], 'TU_RES_04':['004703a0','004704a0','00470580'], 'TU_RES_03':['004b2e00','004b3000','004b3030']}
selected=[r for r in rows if any(lo<=int(r['entry'],16)<=hi for lo,hi in [(0x4927b0,0x493bd0),(0x410490,0x4149f0),(0x46fee0,0x470b20),(0x4b2e00,0x4b3030)])]
out=pathlib.Path(sys.argv[2]);out.mkdir(exist_ok=True)
with (out/'function_evidence.tsv').open('w') as w:
 w.write('entry\tname\tbody_bytes\tend\tgap_to_next\tdefined_call_targets\tdata_target_count\tcandidate\n')
 for r in selected:
  i=rows.index(r); gap=int(rows[i+1]['entry'],16)-int(r['end'],16)-1
  w.write('\t'.join([r['entry'],r['name'],str(r['size']),r['end'],str(gap),','.join(sorted(calls(r))),str(len(data(r))),','.join(g for g,aa in groups.items() if r['entry'] in aa) or 'unassigned'])+'\n')
with (out/'group_metrics.txt').open('w') as w:
 for g,aa in groups.items():
  ds=collections.Counter(t for a in aa for t in data(by[a])); internal=sum(len(calls(by[a])&set(aa)) for a in aa); outside=sorted({r['entry'] for r in rows if r['entry'] not in aa and calls(r)&set(aa)})
  w.write(f'{g}: members={len(aa)} internal_direct_edges={internal} outside_callers={len(outside)}\nshared_data='+str(sorted((t,c) for t,c in ds.items() if c>1))+'\noutside_callers='+','.join(outside)+'\n')
print('inventoried',len(rows),'bounded',len(selected))
