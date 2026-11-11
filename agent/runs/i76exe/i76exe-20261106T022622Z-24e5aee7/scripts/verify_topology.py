#!/usr/bin/env python3
"""Independent graph construction and flatten oracle. No producer code imported.
Decision replay validates topology independently, not the numerical LOD predicate.
Private source files are read for authentication and midpoint height checks only.
"""
import argparse,collections,csv,hashlib,json,struct
from pathlib import Path
BASE=0x44000000
checks=0
def ck(v,msg):
 global checks
 checks+=1
 if not v: raise AssertionError(msg)
def sha(b):return hashlib.sha256(b).hexdigest()
def words(s):return [int(x,16) for x in s.split(',')]
def rows(p):
 return [{**r,'d':dict(t.split('=',1) for t in r['detail'].split(';') if '=' in t)} for r in csv.DictReader(p.open(),delimiter='\t')]
def floats(b):return list(struct.iter_unpack('<3f',b))
def fbits(v):return struct.unpack('<I',struct.pack('<f',v))[0]
def dump(p,v):p.write_text(json.dumps(v,indent=2,sort_keys=True)+'\n')
def f32(v):return struct.unpack('<f',struct.pack('<f',v))[0]
def original_predicate(m,es,thresholds,cam,planes,special):
 # Independently authored formula transcription. Graph replay does not depend on this result.
 a,b,c,d=es;v=m.v;A=v[m.edges[c][0]];O=v[m.edges[d][1]];D=v[m.edges[d][0]];B=v[m.edges[c][1]]
 size=int(O[0]-A[0]+.5);radius=size*.5
 if radius<32:
  for nx,_,nz,_,offset in planes:
   dist=nx*(A[0]+radius)+nz*(A[2]+radius)+offset
   if dist+radius*1.42<0 and dist-radius*1.42<0:return 'cull','bounds_plane'
 half=size>>1
 if half>=32:return 'split','hard_floor'
 if half==0:return 'leaf','minimum'
 dx=f32(A[0]+half-cam[0]);dz=f32(A[2]+half-cam[2]);dist=f32(dx*dx+dz*dz)
 if size*size*thresholds[0]<dist:return 'leaf','distance_limit'
 if size*size>dist+dist:return 'split','near_distance'
 tol=f32(struct.unpack('<f',struct.pack('<I',fbits(dist)&0xff800000))[0]*thresholds[1]);cx=int(A[0]+.5)+half;cz=int(A[2]+.5)+half;mid=f32((A[1]+O[1])*.5)
 probes=[(cx,cz,mid)]
 if half!=1:
  q=size>>2
  probes.extend([(cx-q,cz+q,(D[1]+mid)*.5),(cx+q,cz+q,(mid+O[1])*.5),(cx-q,cz-q,(mid+A[1])*.5),(cx+q,cz-q,(B[1]+mid)*.5)])
 for i,(x,z,h) in enumerate(probes):
  if abs((h-(m.sample(x,z)&4095))*size)>tol:return 'split','height_'+str(i)
 if size<=4:return 'leaf','small_surface_guard'
 if special(cx-half,cz-half,size):return 'split','surface_class'
 return 'leaf','height_and_surface_pass'

class Model:
 def __init__(self,vertices,sample):self.v=list(vertices);self.sample=sample;self.edges={};self.leaves=[];self.cursor=BASE;self.reused=0
 def edge(self,a,b):
  p=self.cursor;self.cursor+=12;self.edges[p]=[a,b,0,0];return p
 def split(self,p):
  e=self.edges[p]
  if e[2]:self.reused+=1;return
  a,b=(self.v[i] for i in e[:2]);x=(int(a[0])+int(b[0]))>>1;z=(int(a[2])+int(b[2]))>>1;i=len(self.v);self.v.append((float(x),float(self.sample(x,z)&4095),float(z)));e[2]=self.edge(e[0],i);e[3]=self.edge(i,e[1])
 def leaf(self,es):
  x,_,z=self.v[self.edges[es[0]][0]];right=self.v[self.edges[es[1]][1]][0];p=self.cursor;self.cursor+=28;self.leaves.append([p,[int(x),int(z),int(right-x),0,*es]])
 def quad(self,es,decisions):
  if callable(decisions):d={'outcome':decisions(self,es)}
  else:
   q,d=next(decisions);ck(words(q['edges'])==list(es),'recursive edge argument identity')
  if d['outcome']=='cull':return
  if d['outcome']=='leaf':self.leaf(es);return
  a,b,c,d=es
  for e in es:self.split(e)
  mid=lambda p:self.edges[self.edges[p][2]][1]
  cross=self.edge(mid(c),mid(d));self.split(cross)
  left=self.edge(mid(a),mid(cross));right=self.edge(mid(cross),mid(b));A,B,C,D=(self.edges[e] for e in es);E=self.edges[cross]
  for child in [(A[2],E[2],C[2],left),(E[2],B[2],C[3],right),(E[3],B[3],right,D[3]),(A[3],E[3],left,D[2])]:self.quad(child,decisions)
 def flat(self,p,reverse=False):
  a,b,c,d=self.edges[p]
  if not c:return [b if reverse else a]
  return self.flat(d,True)+self.flat(c,True) if reverse else self.flat(c)+self.flat(d)
 def loop(self,es):return self.flat(es[2])+self.flat(es[1])+self.flat(es[3],True)+self.flat(es[0],True)
 def binary(self):
  b=bytearray(self.cursor-BASE)
  for p,(a,z,c,d) in self.edges.items():struct.pack_into('<hhII',b,p-BASE,a,z,c,d)
  for i,(p,rec) in enumerate(self.leaves):
   x,z,size,_,*es=rec;struct.pack_into('<hhiIIIII',b,p-BASE,x,z,size,self.leaves[i+1][0] if i+1<len(self.leaves) else 0,*es)
  return bytes(b)
def main():
 p=argparse.ArgumentParser();p.add_argument('--cases',type=Path,required=True);p.add_argument('--msn',type=Path,required=True);p.add_argument('--ter',type=Path,required=True);p.add_argument('--emit',type=Path,required=True);a=p.parse_args();a.emit.mkdir(parents=True,exist_ok=True)
 msn=a.msn.read_bytes();ter=a.ter.read_bytes();ck(sha(msn)=='923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f','MSN identity');ck(sha(ter)=='fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea','TER identity');off=msn.index(b'ZMAP');zm=msn[off+9:off+9+6400]
 def sample(x,z):
  ck(0<=x<10240 and 0<=z<10240,'bounded mapped sample');page=zm[(z//128)*80+x//128];ck(page!=255,'active mapped sample');return struct.unpack_from('<H',ter,page*32768+2*((z&127)*128+(x&127)))[0]
 def special(x,z,size):
  if min(x,z)<0 or max(x,z)>10240:return False
  page=zm[(z//128)*80+x//128]
  if page==255:raise ValueError('special default page unresolved')
  start=page*32768+2*((z&127)*128+(x&127))
  for i in range(size-1,-1,-1):
   for off in [i,(size-1)*128+i,i*128,(size-1)+i*128]:
    w=struct.unpack_from('<H',ter,start+2*off)[0]
    if w>=0x4000 and w&0xe000!=0xa000:return True
  return False
 summaries={};graphs={};polys=[];decrows=[]
 for trace in sorted(a.cases.glob('*.tsv')):
  case=trace.stem;
  if case=='alternate':continue
  rs=rows(trace);by=collections.defaultdict(list)
  for r in rs:by[r['kind']].append(r)
  ck(not by['BLOCKER'] and len(by['COHERENT_COMPLETE'])==1,'complete original execution');out=by['OUTPUT'][0]['d'];ck(out['harnessOutputWrites']=='0','sealed output');counts={k:int(out[k]) for k in ['vertices','edges','leaves']}
  if not by['QUAD']:
   ck(counts==dict(vertices=0,edges=0,leaves=0),'invalid no graph');summaries[case]=counts|{'rejected':True};continue
  src=Path(str(trace)+'.pre.bin').read_bytes();v=floats(src);post=floats(Path(str(trace)+'.post.bin').read_bytes());ck(len(v)==counts['vertices'],'source count');
  for x,h,z in v:ck(h==sample(int(x),int(z))&4095,'authenticated source height')
  bounds=words(out['bounds']);ox,oz,ex=bounds[:3];side=1<<ex;seeds=[(float(x),float(sample(x,z)&4095),float(z)) for x,z in [(ox,oz),(ox+side,oz),(ox+side,oz+side),(ox,oz+side)]];ck(seeds==v[:4],'root seeds from original bounds and authenticated samples')
  m=Model(seeds,sample);root=[m.edge(3,2),m.edge(0,1),m.edge(1,2),m.edge(0,3)]
  last={};original_branches={}
  for row in rs:
   d=row['d']
   if row['kind']=='LOD_BRANCH':last[d['frame']]={'pc':row['pc'],'next':d['next']}
   if row['kind']=='DECISION':original_branches[d['id']]=last.get(d['frame'],{})
  qs={r['d']['id']:r['d'] for r in by['QUAD']};ds={r['d']['id']:r['d'] for r in by['DECISION']};ck(len(qs)==len(ds),'one terminal decision per quad');stream=iter((qs[k],ds[k]) for k in qs);m.quad((root[3],root[2],root[1],root[0]),stream);ck(next(stream,None) is None,'all decisions consumed');ck(m.v==v,'exact complete source vertex order');ck(m.binary()==Path(str(trace)+'.source-arena.bin').read_bytes(),'bitwise complete edge/leaf arena')
  ck(len(m.edges)==counts['edges'] and len(m.leaves)==counts['leaves'],'graph counts')
  lod=by['LOD_INPUTS'][0]['d'];thresholds=struct.unpack('<2f',struct.pack('<2I',*words(lod['thresholds'])));cam=struct.unpack('<3f',struct.pack('<3I',*words(lod['cameraXZ'])));pb=struct.pack('<'+'I'*len(words(lod['planes'])),*words(lod['planes']));planes=list(struct.iter_unpack('<4fd',pb));predicate_mismatches=[];reasons=collections.Counter()
  predicted=Model(seeds,sample);pr=[predicted.edge(3,2),predicted.edge(0,1),predicted.edge(1,2),predicted.edge(0,3)]
  predicted.quad((pr[3],pr[2],pr[1],pr[0]),lambda model,edges:original_predicate(model,edges,thresholds,cam,planes,special)[0])
  ck(predicted.binary()==m.binary() and predicted.v==m.v,'independent numerical predicate generates exact complete source graph')
  for k,q in qs.items():
   es=words(q['edges']);x,_,z=m.v[m.edges[es[2]][0]];size=m.v[m.edges[es[3]][1]][0]-x
   pred,reason=original_predicate(m,es,thresholds,cam,planes,special);reasons[reason]+=1
   if pred!=ds[k]['outcome']:predicate_mismatches.append({'quad':k,'expected':ds[k]['outcome'],'model':pred,'reason':reason})
   decrows.append([case,k,int(x),int(z),int(size),ds[k]['outcome'],ds[k]['frame'],original_branches[k].get('pc'),original_branches[k].get('next'),reason,pred])
  flattened={int(r['d']['leaf'],16):words(r['d']['indices']) for r in by['FLATTENED']};ck(len(flattened)==len(m.leaves),'every leaf flattened')
  incidence=collections.defaultdict(list);longloops=0
  for p,rec in m.leaves:
   loop=m.loop(rec[4:]);ck(loop==flattened[p],'exact original flattened loop');longloops+=len(loop)>4
   area=sum(m.v[loop[i]][0]*m.v[loop[(i+1)%len(loop)]][2]-m.v[loop[(i+1)%len(loop)]][0]*m.v[loop[i]][2] for i in range(len(loop)));ck(area>0,'consistent positive XZ signed area (normal -Y for XYZ cross)')
   for i,j in zip(loop,loop[1:]+loop[:1]):incidence[tuple(sorted((i,j)))].append((p,i,j,rec[2]))
  shared=[v for v in incidence.values() if len(v)==2];unequal=[v for v in shared if v[0][3]!=v[1][3]]
  for pair in shared:ck(pair[0][1:3]==pair[1][1:3][::-1],'shared terminal segment exact reversed indices')
  for val in incidence.values():ck(len(val)<=2,'manifold segment ownership')
  segments=[(p,i,j) for val in incidence.values() for p,i,j,_ in val];overlaps=0
  for ai,(pa,ia,ja) in enumerate(segments):
   A,B=m.v[ia],m.v[ja]
   for pb,ib,jb in segments[ai+1:]:
    if pa==pb:continue
    C,D=m.v[ib],m.v[jb]
    axis=2 if A[0]==B[0]==C[0]==D[0] else 0 if A[2]==B[2]==C[2]==D[2] else None
    if axis is not None and min(max(A[axis],B[axis]),max(C[axis],D[axis]))>max(min(A[axis],B[axis]),min(C[axis],D[axis])):
     ck((ia,ja)==(jb,ib),'all geometric boundary overlaps exactly match reversed indices; no partial T junction');overlaps+=1
  ck(overlaps==len(shared),'all common boundaries accounted')
  # Verify every split invocation independently, including no-op reuse and exact midpoint identity.
  pending=None;new=0;reuse=0
  for r in rs:
   d=r['d'];kind=r['kind']
   if kind=='SPLIT_ENTER':ck(pending is None,'nonrecursive split');pending=d
   if kind=='SPLIT_RETURN':
    ck(pending is not None and d['edge']==pending['edge'],'paired split');e=words(pending['data']);after=words(d['data']);nv=int(d['vertices'])-int(pending['vertices']);ck(nv==(0 if e[1] else 1),'one midpoint or no-op');ck(e==after if e[1] else after[1]!=0 and after[2]!=0,'split pointer behavior');reuse+=bool(e[1]);new+=not bool(e[1]);pending=None
  leafrecs={p:rec for p,rec in m.leaves}
  def anchor(leaf):
   es=leafrecs[leaf][4:]
   for e in es:
    E=m.edges[e]
    if E[2] and not m.edges[E[2]][2] and not m.edges[E[3]][2]:return m.edges[E[2]][1]
   a,b,c,d=[m.edges[e] for e in es]
   if not a[2]:
    if not c[2]:return c[0]
    if not d[2]:return d[0]
   elif not b[2]:
    if not c[2]:return c[1]
    if not d[2]:return d[1]
   raise AssertionError('uncovered walker center creation')
  aux=Path(str(trace)+'.source-aux.bin').read_bytes()
  current=None
  for r in rs:
   d=r['d'];kind=r['kind']
   if kind=='EMITTER_ENTER':
    current={'case':case,'ordinal':len([x for x in polys if x['case']==case]),'leaf':int(d['leaf'],16),'indices':words(d['indices']),'emitter_pc':r['pc'],'clip_count':None,'bin_attempted':False,'bin_accepted':False};loop=flattened[current['leaf']];ix=current['indices'];ck(all(i<len(post) for i in ix),'emitter source vertex identity');current['source_attributes']=[{'index':i,'lattice_x':int(v[i][0]),'lattice_z':int(v[i][2]),'packed_word':sample(int(v[i][0]),int(v[i][2])),'source_xyz_bits':[fbits(x) for x in v[i]],'view_xyz_bits':[fbits(x) for x in post[i]],'source_aux_bits':list(struct.unpack_from('<3I',aux,i*12))} for i in ix];current['shade_argument_bits']=words(d['args'])[3];current['work_source_indices']=ix[::-1];current['boundary_loop']=loop;current['triangle_fallback']=len(ix)==3;ck(ix==loop if len(ix)!=3 else all(i in loop for i in ix),'emitter loop or boundary fan membership')
    if len(ix)==3:
     center=anchor(current['leaf']);fan=[[center,j,k] for j,k in zip(loop,loop[1:]+loop[:1]) if j!=center and k!=center];ck(ix in fan,'exact fan anchor and ordered adjacent boundary pair')
    polys.append(current)
   elif kind=='CLIP_ENTER' and current:
    w=words(d['data']);ck(w[0]==len(current['indices']),'preclip candidate count')
    for j,i in enumerate(current['work_source_indices']):
     ck(w[7+6*j:10+6*j]==[fbits(x) for x in post[i]],'original emitter reverses exact view XYZ into work records');ck(w[12+6*j]==current['shade_argument_bits'],'ordinary shade argument copy')
   elif kind=='CLIP_RETURN' and current:current['clip_count']=int(d['count'])
   elif kind=='BIN_ENTER' and current:current['bin_attempted']=True;current['cursor_before']=int(d['cursor'],16)
   elif kind=='BIN_RETURN' and current:current['bin_accepted']=int(d['cursor'],16)>current['cursor_before']
  cp=[x for x in polys if x['case']==case]
  summaries[case]=counts|{'complete_polygon_oracle_sha256':sha(b''.join((json.dumps(x,sort_keys=True)+'\n').encode() for x in cp)),'quad_decisions':len(qs),'outcomes':dict(collections.Counter(d['outcome'] for d in ds.values())),'midpoint_creations':new,'split_reuse_calls':reuse,'long_boundary_loops':longloops,'shared_terminal_segments':len(shared),'unequal_size_shared_segments':len(unequal),'emitter_attempts':len(cp),'triangle_attempts':sum(x['triangle_fallback'] for x in cp),'clip_accepted':sum((x['clip_count'] or 0)>0 for x in cp),'bin_attempts':sum(x['bin_attempted'] for x in cp),'bin_accepted':sum(x['bin_accepted'] for x in cp),'arena_sha256':sha(m.binary()),'source_sha256':sha(src),'model_graph_bitwise_equal':True,'model_decisions':'both original-outcome replay and independent formula construction match','independent_predicate_graph_bitwise_equal':True,'predicate_mismatches':predicate_mismatches,'predicate_reasons':dict(reasons),'max_boundary_vertices':max(map(len,flattened.values())),'unique_lattice_vertices':len({(x,z) for x,h,z in m.v}),'seam_z9600_vertices':sum(z==9600 for x,h,z in m.v)}
  # Full selected graph is bounded to two stock fixtures; remaining cases retain hashes and summaries.
  if case in ['primary','contrast']:
   graphs[case]={'edges':m.edges,'leaves':m.leaves,'vertices':m.v,'flattened':flattened,'unequal_examples':unequal[:4]}
 dump(a.emit/'geometry_comparisons.json',{'scenarios':summaries,'checks':checks,'limitations':['root and visible planes supplied from original bounds; predicate and graph independently generated from those inputs','no hardware-wide x87 claim','ordinary full emission; alternate header only inherited/static'],'status':'passed'})
 dump(a.emit/'edge_graph.json',graphs)
 with (a.emit/'polygons.jsonl').open('w') as f:
  for row in polys:f.write(json.dumps(row,sort_keys=True)+'\n')
 with (a.emit/'subdivision_decisions.tsv').open('w') as f:
  f.write('case\tquad_id\tx\tz\tsize\toutcome\tframe\tbranch_pc\tbranch_next\tmodel_reason\tmodel_outcome\n');f.writelines('\t'.join(map(str,row))+'\n' for row in decrows)
 print(json.dumps({'checks':checks,'scenarios':summaries},indent=2))
if __name__=='__main__':main()
