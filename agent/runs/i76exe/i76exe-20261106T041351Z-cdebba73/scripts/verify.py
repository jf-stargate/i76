#!/usr/bin/env python3
"""Predict first from source graph/post-transform geometry; compare trace second."""
import argparse,collections,csv,hashlib,json,struct
from pathlib import Path
from walker import Numerics,walk,bits,f32,flatten
def words(s):return [int(x,16) for x in s.split(',')]
def fs(s):return list(struct.unpack('<'+'f'*len(words(s)),struct.pack('<'+'I'*len(words(s)),*words(s))))
def rows(p):return [{**r,'d':dict(t.split('=',1) for t in r['detail'].split(';') if '=' in t)} for r in csv.DictReader(p.open(),delimiter='\t')]
N=0
def ck(v,msg):
 global N
 N+=1
 if not v:raise AssertionError(msg)
def main():
 p=argparse.ArgumentParser();p.add_argument('--cases',type=Path,required=True);p.add_argument('--exe',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args();a.out.mkdir(parents=True,exist_ok=True)
 pe=a.exe.read_bytes();ck(hashlib.sha256(pe).hexdigest()=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','PE identity');numeric=Numerics(pe);summary={};allrecords=[];max_normal=0.;max_distance=0.;max_shade=0.
 for anchor in csv.DictReader((Path(__file__).resolve().parents[1]/'evidence/instruction_anchors.tsv').open(),delimiter='\t'):
  raw=bytes.fromhex(anchor['hex']);ck(numeric.read(int(anchor['va'],16),len(raw))==raw,'retail instruction anchor '+anchor['va'])
 for t in sorted(a.cases.glob('*.tsv')):
  rs=rows(t);by=collections.defaultdict(list)
  for r in rs:by[r['kind']].append(r)
  ck(len(by['COHERENT_COMPLETE'])==1 and not by['BLOCKER'],t.stem+' completion')
  if not by['WALK_CONSTANTS']:
   ck(not by['EMITTER_ENTER'],'rejected camera no attempts');summary[t.stem]={'leaves':0,'attempts':0,'accepted':0};continue
  side=lambda suffix:Path(str(t)+suffix).read_bytes()
  source=side('.source-arena.bin');vertices=list(struct.iter_unpack('<3f',side('.post.bin')));view=side('.view.bin');head=int(by['WALK_ENTER'][0]['d']['head'],16)
  leaves=[];edges={};base=0x44000000
  def edge(q):
   if q in edges:return
   rec=struct.unpack_from('<hhII',source,q-base);edges[q]=rec
   if rec[2]:edge(rec[2]);edge(rec[3])
  while head:
   rec=struct.unpack_from('<hhiIIIII',source,head-base);es=rec[4:];leaves.append((head,es))
   for q in es:edge(q)
   head=rec[3]
  c=by['WALK_CONSTANTS'][0]['d'];world=fs(c['light']);light=[f32(sum(struct.unpack_from('<f',view,0x40+12*k+4*j)[0]*world[k] for k in range(3))) for j in range(3)]
  ck([bits(x) for x in light]==words(by['VIEW_LIGHT'][0]['d']['data']),'derived light from original view matrix')
  # Predict without loading or examining original emitter/branch decisions.
  predicted=walk(edges,leaves,vertices,view,light,fs(c['ambient'])[0],world[3:5],fs(c['scale'])[0],numeric,int(c['high']))
  if t.stem in ['primary','contrast','shade','high']:
   constants={str(va):numeric.value(va,fmt) for va,fmt in [(0x4be8c0,'d'),(0x4faf20,'d'),(0x4faf28,'d'),(0x4faf30,'d'),(0x4be860,'d'),(0x4faf18,'d'),(0x4be82c,'f')]}
   projection={str(off):list(struct.unpack_from('<'+fmt,view,off)) for off,fmt in [(0,'4f'),(0x1c,'4f'),(0x108,'f'),(0x138,'f')]}
   fixture=dict(edges=edges,leaves=leaves,vertices=vertices,projection=projection,light=light,ambient=fs(c['ambient'])[0],attenuation=world[3:5],scale=fs(c['scale'])[0],constants=constants,high=int(c['high']))
   (a.out/(t.stem+'.fixture.json')).write_text(json.dumps(fixture,sort_keys=True)+'\n')
  original=[];cur=None;cursor=0x48000000;plane_input=None;originalplanes=[];plane_indices=[]
  for r in rs:
   d=r['d'];kind=r['kind']
   if kind=='PLANE_ENTER':plane_input=[fs(','.join(d['points'].split(',')[k:k+3])) for k in [0,3,6]];plane_indices.append([(ptr-0x42000000)//12 for ptr in words(d['args'])[1:]])
   elif kind=='PLANE_RETURN':
    want=numeric.plane(*plane_input);got=fs(d['data']);max_normal=max(max_normal,max(abs(x-y) for x,y in zip(want[:3],got[:3])));max_distance=max(max_distance,abs(want[3]-got[3]));ck(all(abs(x-y)<=2e-6 for x,y in zip(want[:3],got[:3])) and abs(want[3]-got[3])<=max(2e-6,2e-6*sum(abs(x*y) for x,y in zip(plane_input[0],got[:3]))),'bounded plane numerical parity');ck((want[3]<0)==(got[3]<0),'plane facing sign');originalplanes.append(got)
   elif kind=='EMITTER_ENTER':
    cur=dict(leaf=int(d['leaf'],16),indices=words(d['indices']),shade=fs(d['args'])[3],clip_count=None,accepted=False);original.append(cur)
   elif kind=='ORIGINAL_PROJECTION_WRITE':cur['projected']=True
   elif kind=='CLIP_RETURN':cur['clip_count']=int(d['count']);cur['rejection']=None if int(d['count']) else 'screen_clip' if cur.get('projected') else 'depth_clip'
   elif kind=='ALLOCATOR_RETURN':ck(int(d['record'],16)==cursor,'predicted scratch cursor');cur['record']=cursor
   elif kind=='BIN_ENTER':cur['cursor_before']=int(d['cursor'],16);ck(cur['cursor_before']==cursor,'bin cursor before')
   elif kind=='BIN_RETURN':cur['accepted']=int(d['cursor'],16)>cur['cursor_before'];ck(int(d['cursor'],16)==cursor+28+24*cur['clip_count'],'bin retirement size');cursor=int(d['cursor'],16)
   elif kind=='EMITTER_RETURN':cur['return_value']=int(d['eax'])
  flat=[(r['leaf'],x) for r in predicted for x in r['attempts']];ck(len(flat)==len(original),t.stem+f' attempts {len(flat)} vs {len(original)}')
  for ordinal,((leaf,want),got) in enumerate(zip(flat,original)):
   label=f'{t.stem} attempt {ordinal}'
   ck(leaf==got['leaf'] and want['indices']==got['indices'],label+' order/source indices')
   ck(want['clip_count']==got['clip_count'],label+f' clip count {want["clip_count"]} != {got["clip_count"]}')
   ck(want['rejection']==got['rejection'],label+' rejection stage');ck(want['accepted']==got['accepted'],label+' bin acceptance');ck(want['return_value']==got['return_value'],label+' emitter return')
   err=abs(want['shade']-got['shade']);max_shade=max(max_shade,err);ck(err<=2e-6,label+' shade');want['original']=got;want['ordinal']=ordinal
  anchors={int(r['d']['leaf'],16):int(r['d']['index']) for r in by['ANCHOR']};turns={int(r['d']['leaf'],16):r['d'] for r in by['TURN_TEST']};fallbacks={int(r['d']['leaf'],16) for r in by['FALLBACK']};bands={int(r['d']['leaf'],16):r['d'] for r in by['SHADE_TEST']}
  expected_plane_indices=[]
  for record in predicted:
   loop=record['boundary'];es=dict(leaves)[record['leaf']]
   corners=[flatten(edges,es[2])[0],flatten(edges,es[1])[0],flatten(edges,es[3],True)[0],flatten(edges,es[0],True)[0]]
   if record['whole_planes']:expected_plane_indices.extend([[corners[0],corners[1],corners[2]],[corners[0],corners[2],corners[3]]])
   if record['fallback_reason']:expected_plane_indices.extend([[record['anchor'],j,k] for j,k in zip(loop,loop[1:]+loop[:1]) if j!=record['anchor'] and k!=record['anchor']])
   leaf=record['leaf'];ck(anchors[leaf]==record['anchor'],'anchor prediction');d=turns[leaf];ck(int(d['score'])&0xffffffff==record['turn_score']&0xffffffff,'projected Y score');ck(int(d['target'])&0xffffffff==record['turn_target']&0xffffffff,'turn target');ck((leaf in fallbacks)==bool(record['fallback_reason']),'fallback decision')
   if record['shade_bands']:
    d=bands[leaf];ck(record['shade_bands']==[int(d['second'],16)&0x1f00,int(d['first'],16)&0x1f00],'shade band pair')
   record['original_gates']=dict(anchor=anchors[leaf],score=int(turns[leaf]['score']),target=int(turns[leaf]['target']),fallback=leaf in fallbacks,shade_low_words=bands.get(leaf));record['case']=t.stem;allrecords.append(record)
  ck(plane_indices==expected_plane_indices,'every corner/fan plane input triple and ordering, including filtered triangles')
  # Final accepted bin membership, distinct from merely positive clip result.
  storage=side('.polygons.bin');buckets=side('.buckets.bin');members=[]
  for head,tail,count in struct.iter_unpack('<3I',buckets):
   chain=[]
   while head:
    ck(head not in members,'unique bin record');members.append(head);chain.append(head);head=struct.unpack_from('<I',storage,head-0x48000000+20)[0]
   ck(len(chain)==count and (chain[-1] if chain else 0)==tail,'bin chain count/tail')
  ck(set(members)=={x['record'] for x in original if x['accepted']},'source attempt record identity in final bins');ck(len(storage)==cursor-0x48000000,'final arena size');ck(len(members)==sum(x['accepted'] for _,x in flat),'accepted predictions equal final bin members')
  counts=dict(collections.Counter(r['fallback_reason'] or 'whole_success' for r in predicted));summary[t.stem]=dict(leaves=len(leaves),attempts=len(flat),whole=sum(x['kind']=='whole' for _,x in flat),triangles=sum(x['kind']=='triangle' for _,x in flat),accepted=len(members),fallbacks=counts,anchor_reasons=dict(collections.Counter(r['anchor_reason'] for r in predicted)),filtered_triangles=sum(len(r['filtered_triangles']) for r in predicted),trace_sha256=hashlib.sha256(t.read_bytes()).hexdigest())
  print(t.stem,summary[t.stem],flush=True)
 with (a.out/'decisions.jsonl').open('w') as f:
  for r in allrecords:f.write(json.dumps(r,sort_keys=True)+'\n')
 result=dict(status='passed',checks=N,scenarios=summary,max_absolute_normal_error=max_normal,max_absolute_distance_error=max_distance,max_absolute_shade_error=max_shade)
 (a.out/'verification.json').write_text(json.dumps(result,indent=2,sort_keys=True)+'\n');print(result)
if __name__=='__main__':main()
