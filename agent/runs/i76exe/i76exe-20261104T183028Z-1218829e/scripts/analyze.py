#!/usr/bin/env python3
"""Standard-library structural detector. prepare requires private Ghidra capture + PE + GZF.
rank can reproduce every boundary using only compact published features.
"""
import argparse, collections, hashlib, itertools, json, pathlib, struct
WEIGHTS=[2,1,1,.5,-2,-1]
NAMES=['mutable_turnover','call_turnover','caller_turnover','literal_turnover','cross_density','adjacent_link']
def digest(p): return hashlib.sha256(pathlib.Path(p).read_bytes()).hexdigest()
def dump(p,x): pathlib.Path(p).write_text(json.dumps(x,indent=2,sort_keys=True)+'\n')
def prepare(capture,pe,gzf,out):
 d=json.loads(pathlib.Path(capture).read_text()); raw=pathlib.Path(pe).read_bytes()
 assert digest(pe)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
 assert digest(gzf)=='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'
 off=struct.unpack_from('<I',raw,0x3c)[0]; assert raw[off:off+4]==b'PE\0\0'
 count=struct.unpack_from('<H',raw,off+6)[0]; opt=struct.unpack_from('<H',raw,off+20)[0]; image=struct.unpack_from('<I',raw,off+24+28)[0]
 sections=[struct.unpack_from('<IIII',raw,off+24+opt+40*i+8) for i in range(count)]
 def bytes_at(va,n):
  rva=va-image
  for vs,base,rs,ptr in sections:
   if base<=rva and rva+n<=base+rs:return raw[ptr+rva-base:ptr+rva-base+n]
  raise ValueError(hex(va))
 checks=[]
 for f in d['functions']:
  for r in f['ranges']:
   lo,hi=int(r['start'],16),int(r['end'],16)
   h=hashlib.sha256(bytes_at(lo,hi-lo+1)).hexdigest();assert h==r['sha256']; checks.append(dict(entry=f['entry'],**r))
 assert d['modification_before']==d['modification_after']
 objs={o['address']:o for o in d['objects']}
 def category(o):
  if o['executable']:return 'code'
  if 'string' in o['type'].lower() or o['type'].lower() in ('char[]','unicode'):return 'literal'
  if not o['writable']:return 'literal'
  if any('WRITE' in r['type'] for r in o['users']):return 'mutable'
  return 'uncertain'
 os={k:dict(category=category(o),length=o['length'],type=o['type'],users=len({r['function'] for r in o['users'] if r.get('function')}),external_users=len({r['function'] for r in o['users'] if r.get('function') and not 0x46fa00<=int(r['function'],16)<=0x470d20}),writes=sum('WRITE' in r['type'] for r in o['users']),address_refs=sum('DATA'==r['type'] for r in o['users'])) for k,o in objs.items()}
 fs=[]
 for f in d['functions']:
  groups={k:sorted({r['object'] for r in f['refs'] if r['object'] in os and os[r['object']]['category']==k}) for k in ['mutable','literal','uncertain']}
  jumps=sorted({r['function'] for r in f['refs'] if 'JUMP' in r['type'] and r.get('function') and r['function']!=f['entry']})
  fs.append(dict(entry=f['entry'],context=f['context'],size=f['size'],ranges=f['ranges'],alignment=int(f['entry'],16)%16,gap_bytes=sum(int(g['end'],16)-int(g['start'],16)+1 for g in f['gap']),gap_kinds=dict(collections.Counter(g['kind'] for g in f['gap'])),calls=f['calls'],jumps=jumps,callers=sorted({r['function'] for r in f['incoming'] if r.get('function') and 'CALL' in r['type']}),address_taken=[r for r in f['incoming'] if 'CALL' not in r['type']],**groups))
 dump(out/'features.json',dict(functions=fs,objects=os))
 dump(out/'input_validation.json',dict(pe_sha256=digest(pe),gzf_sha256=digest(gzf),private_capture_sha256=digest(capture),ghidra=d['ghidra'],program=d['program'],defined_functions=d['defined_functions'],language=d['language'],image_base=d['image_base'],metadata_sha256=d['executable_sha256'],modification_before=d['modification_before'],modification_after=d['modification_after'],body_ranges_verified=len(checks),body_bytes_verified=sum(int(r['end'],16)-int(r['start'],16)+1 for r in checks),body_checks=checks))
def turnover(a,b,weights=None):
 u=a|b
 if not u:return 0
 w=weights or collections.defaultdict(lambda:1)
 return 1-sum(w[x] for x in a&b)/sum(w[x] for x in u)
def calculate(d,window=3,weights=WEIGHTS):
 fs=d['functions'];os=d['objects']; mw={k:1/max(1,o['users']) for k,o in os.items()}
 def linked(a,b):return bool(set(a['mutable'])&set(b['mutable']) or a['entry'] in b['calls']+b['jumps'] or b['entry'] in a['calls']+a['jumps'])
 rows=[]
 for i in range(1,len(fs)):
  if fs[i-1]['context'] or fs[i]['context']:continue
  left,right=fs[max(0,i-window):i],fs[i:i+window]
  union=lambda side,key:set().union(*(set(f[key]) for f in side))
  values=[turnover(union(left,k),union(right,k),mw if k=='mutable' else None) for k in ['mutable','calls','callers','literal']]
  crossing=[(a['entry'],b['entry']) for a in left for b in right if linked(a,b)]
  values += [len(crossing)/(len(left)*len(right)),int(linked(fs[i-1],fs[i]))]
  terms=[v*w for v,w in zip(values,weights)]
  rows.append(dict(left=fs[i-1]['entry'],right=fs[i]['entry'],score=round(sum(terms),8),features=dict(zip(NAMES,values)),terms=dict(zip(NAMES,terms)),cross_edges=crossing,window_left=[f['entry'] for f in left],window_right=[f['entry'] for f in right],gap_bytes=fs[i-1]['gap_bytes']))
 return sorted(rows,key=lambda r:(-r['score'],r['right']))
def rank(inp,out):
 d=json.loads(pathlib.Path(inp).read_text());base=calculate(d);variants=[('baseline',base)]
 for j in range(len(WEIGHTS)):
  for factor in [.8,1.2]:
   w=WEIGHTS.copy();w[j]*=factor;variants.append((NAMES[j]+'*'+str(factor),calculate(d,weights=w)))
 for n in [2,4]:variants.append(('window='+str(n),calculate(d,window=n)))
 for i,r in enumerate(base):
  ranks=[next(j+1 for j,x in enumerate(rows) if x['right']==r['right']) for name,rows in variants]
  r.update(rank=i+1,rank_min=min(ranks),rank_max=max(ranks),top5_count=sum(x<=5 for x in ranks),variant_count=len(ranks),stability='stable-top5' if max(ranks)<=5 else 'unstable-top5' if min(ranks)<=5 else 'outside-top5')
 result=dict(weights=dict(zip(NAMES,WEIGHTS)),window=3,boundaries=base,sensitivity={name:[r['right'] for r in rows] for name,rows in variants},alternative_partitions={str(t):[r['right'] for r in sorted(base,key=lambda x:x['right']) if r['score']>=t] for t in [1.5,2,2.5]})
 dump(out/'ranking.json',result)
 lines=['# Frozen blind boundary ranking','','Scores are ordinal heuristics, not source-file confidence. Feature definitions and counterevidence are in FEATURE_MODEL.md. All adjacent in-range cuts are listed. Context cuts are not ranked.','','| Rank | Before entry | Score | State turnover | Call turnover | Caller turnover | Literal turnover | Cross density | Adjacent link | Rank range | Top five / 15 |','|---|---|---|---|---|---|---|---|---|---|---|']
 for r in base:lines.append('| '+ ' | '.join(map(str,[r['rank'],r['right'],round(r['score'],3),*[round(r['features'][x],3) for x in NAMES],str(r['rank_min'])+'–'+str(r['rank_max']),r['top5_count']]))+' |')
 lines+=['','Positive terms quantify feature turnover; cross density and adjacent link are explicit counterevidence. ranking.json retains the exact cross-cut edges and all weighted terms. Zero turnover is also common-ownership evidence. No threshold is a claim of original linkage.','','Alternative cuts by score threshold:']
 for t,cuts in result['alternative_partitions'].items():lines+=['',f'- {t}: '+', '.join(cuts)]
 (out.parent/'BOUNDARY_RANKING.md').write_text('\n'.join(lines)+'\n')
if __name__=='__main__':
 p=argparse.ArgumentParser();sub=p.add_subparsers(dest='mode',required=True)
 q=sub.add_parser('prepare');q.add_argument('capture',type=pathlib.Path);q.add_argument('pe');q.add_argument('gzf');q.add_argument('out',type=pathlib.Path)
 q=sub.add_parser('rank');q.add_argument('input');q.add_argument('out',type=pathlib.Path)
 a=p.parse_args()
 if a.mode=='prepare':prepare(a.capture,a.pe,a.gzf,a.out)
 else:rank(a.input,a.out)
