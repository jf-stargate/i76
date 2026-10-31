#!/usr/bin/env python3
"""Independent byte/source/geometry verifier. Does not import or execute the producer."""
import argparse,collections,csv,hashlib,json,math,pathlib,struct,subprocess,sys,tempfile
P=argparse.ArgumentParser();P.add_argument('--private',type=pathlib.Path,required=True);P.add_argument('--msn',type=pathlib.Path,required=True);P.add_argument('--ter',type=pathlib.Path,required=True);P.add_argument('--exe',type=pathlib.Path,required=True);P.add_argument('--gzf',type=pathlib.Path,required=True);P.add_argument('--zfs',type=pathlib.Path,required=True);P.add_argument('--fixtures',type=pathlib.Path,required=True);P.add_argument('--repeat',type=pathlib.Path);P.add_argument('--emit',type=pathlib.Path);P.add_argument('--cases',default='primary,contrast,below');P.add_argument('--corruptions',action='store_true');a=P.parse_args();N=0

def ck(ok,msg):
 global N
 N+=1
 if not ok:raise AssertionError(msg)
def sha(b):return hashlib.sha256(b).hexdigest()
def unpack(b,fmt,o=0):return struct.unpack_from('<'+fmt,b,o)
def f32(x):return unpack(struct.pack('<f',x),'f')[0]
def wb(s):return struct.pack('<'+'I'*len(s.split(',')),*[int(x,16) for x in s.split(',')])
def rows(p):
 with p.open() as f:return [{**r,'d':dict(s.split('=',1) for s in r['detail'].split(';') if '=' in s)} for r in csv.DictReader(f,delimiter='\t')]
def ulp(x):return unpack(struct.pack('<I',unpack(struct.pack('<f',abs(f32(x))),'I')[0]+1),'f')[0]-abs(f32(x)) if x else 2**-149
def rounded(v,w,n=1):return abs(v-f32(w))<=n*ulp(w)
def sumclose(got,terms):return abs(got-sum(terms))<=8*2**-52*sum(abs(t) for t in terms)+2**-1074
inputs={}
for kind,p,h in [('exe',a.exe,'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'),('msn',a.msn,'923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f'),('ter',a.ter,'fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea'),('gzf',a.gzf,'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'),('zfs',a.zfs,'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d')]:
 data=p.read_bytes();ck(sha(data)==h,'authenticated '+kind);inputs[kind]={'sha256':h,'bytes':len(data)}
msn=a.msn.read_bytes();ter=a.ter.read_bytes();pe=a.exe.read_bytes();zm=msn[msn.index(b'ZMAP')+9:][:6400]
ph=unpack(pe,'I',60)[0];sec=ph+24+unpack(pe,'H',ph+20)[0];sections=[unpack(pe,'III',sec+j*40+12) for j in range(unpack(pe,'H',ph+6)[0])]
def pebytes(va,n):
 for rv,size,off in sections:
  if rv<=va-0x400000 and va-0x400000+n<=rv+size:return pe[off+va-0x400000-rv:off+va-0x400000-rv+n]
 raise AssertionError('PE mapping')
run=pathlib.Path(__file__).resolve().parent.parent
fixture_meta=json.loads((run.parents[3]/'agent/runs/i76exe/i76exe-20261030T020546Z-e1909f11/evidence/provenance.json').read_text())['fixtures']
for item in fixture_meta:
 b=(a.fixtures/item['name']).read_bytes();ck(len(b)==item['bytes'] and sha(b)==item['sha256'],'authenticated stock vehicle fixture')
ck(len(fixture_meta)==64,'all 64 stock fixtures')
for r in csv.DictReader((run/'evidence/instruction_anchors.tsv').open(),delimiter='\t'):
 b=bytes.fromhex(r['hex']);ck(pebytes(int(r['va'],16),len(b))==b,'original PE anchor '+r['va'])
# This model is independent of trace outputs. Float32 stores are applied at
# explicit clipping/interpolation stages; source and projected geometry are distinct.
def clip(poly,axis,bound,lower):
 out=[]
 for k,q in enumerate(poly):
  p=poly[k-1];iq=q[axis]>=bound if lower else q[axis]<bound;ip=p[axis]>=bound if lower else p[axis]<bound
  if iq!=ip:
   t=f32((bound-p[axis])/(q[axis]-p[axis]));v=[f32(p[j]+t*(q[j]-p[j])) for j in range(len(q))];v[axis]=bound;out.append(v)
  if iq:out.append(q)
 return out
summary={};selected={};views={}
for case in a.cases.split(','):
 p=a.private/(case+'.tsv');rs=rows(p);by=collections.defaultdict(list)
 for r in rs:by[r['kind']].append(r)
 ck(not by['BLOCKER'],'no scientific blocker');ck(len(by['COHERENT_COMPLETE'])==1,'complete bounded execution');ck(len(by['CAMERA_RETURN'])==2,'two original callbacks')
 ck(by['NATIVE_WORLD_REGISTRATION'][0]['d']['owner']=='26000000','registered original root');ck(by['VLOC_ATTACHMENT_FIELDS'][0]['d']['class']=='00000028','original VLOC class')
 # Replay actual changed stores from the first pre-callback state. Initialization
 # copy events are separately authenticated as original REP MOVSD, not harness writes.
 samples=by['SAMPLE'];ck(len(samples)==4,'persistent before/after snapshots')
 for frame in range(2):
  pre=next(r for r in samples if r['d']['frame']==str(frame) and r['d']['phase']=='before');post=next(r for r in samples if r['d']['frame']==str(frame) and r['d']['phase']=='after');b=bytearray.fromhex(pre['d']['camera']);z=bytes.fromhex(post['d']['camera'])
  for r in rs[rs.index(pre)+1:rs.index(post)]:
   if r['kind']!='NATIVE_CHANGED_DWORD':continue
   d=r['d'];addr=int(d['address'],16)
   if d.get('frame')==str(frame) and 0x4c2730<=addr<0x4c2908:
    off=addr-0x4c2730;ck(b[off:off+4]==bytes.fromhex(d['before']),'original view write chronology');b[off:off+4]=bytes.fromhex(d['after'])
  ck(bytes(b)==z,'all callback bytes explained by original writes')
  if frame:ck(pre['d']['camera']==samples[1]['d']['camera'],'frame persistence')
  src=bytes.fromhex(next(r['d']['bytes'] for r in by['CAMERA_SOURCE'] if r['d']['frame']==str(frame)));rot=unpack(src,'9f');pos=unpack(src,'3d',40);inv=unpack(z,'9f',0x40);tr=unpack(z,'3d',0x68)
  ck(inv==tuple(rot[j*3+i] for i in range(3) for j in range(3)),'exact original transpose')
  ck(unpack(z,'3d',0x160)==pos,'exact source camera position')
  for k in range(3):ck(sumclose(tr[k],[-pos[j]*rot[k*3+j] for j in range(3)]),'inverse translation from same camera')
  for k in range(3):ck(sumclose(0.,[pos[j]*inv[j*3+k] for j in range(3)]+[tr[k]]),'camera origin maps to zero')
  points=[pos]
  for k in range(4):
   local=unpack(z,'3f',0x130+k*12);world=unpack(z,'3d',0x178+k*24);points.append(world)
   for c in range(3):ck(sumclose(world[c],[local[j]*rot[j*3+c] for j in range(3)]+[pos[c]]),'same-camera transformed frustum corner')
  center=unpack(z,'3d',0x80)
  for k in range(3):ck(sumclose(center[k],[(min(q[k] for q in points)+max(q[k] for q in points))*.5]),'frustum AABB center')
  radius=max(math.dist(q,center) for q in points);ck(abs(unpack(z,'d',0x98)[0]-radius)<=8*2**-52*max(sum(abs(q[k])+abs(center[k]) for k in range(3)) for q in points),'frustum bounding radius')
  det=rot[0]*(rot[4]*rot[8]-rot[5]*rot[7])-rot[1]*(rot[3]*rot[8]-rot[5]*rot[6])+rot[2]*(rot[3]*rot[7]-rot[4]*rot[6]);ck(det>0,'right handed basis')
  # No normalization or repair: report Gram defect, and require it is consistent
  # with the transpose-as-inverse approximation measured by original instructions.
  gram=max(abs(sum(rot[i*3+k]*rot[j*3+k] for k in range(3))-(i==j)) for i in range(3) for j in range(3));ck(gram<2**-13,'bounded observed original basis conditioning')
 # Plane residuals use float32 coefficient/coordinate magnitude, not a world-distance constant.
  local_far=[unpack(z,'3f',0x130+k*12) for k in range(4)];local_near=[unpack(z,'3f',0x100+k*12) for k in range(4)]
  onplanes=[[(0.,0.,0.),local_far[0],local_far[3]],[(0.,0.,0.),local_far[1],local_far[2]],[(0.,0.,0.),local_far[0],local_far[1]],[(0.,0.,0.),local_far[2],local_far[3]],local_far[:3],local_near[:3]]
  for k,pts in enumerate(onplanes):
   plane=unpack(z,'4f',0xa0+k*16);ck(all(math.isfinite(v) for v in plane) and sum(v*v for v in plane[:3])>0,'finite nondegenerate original frustum plane')
   for q in pts:
    terms=[q[j]*plane[j] for j in range(3)]+[plane[3]];ck(abs(sum(terms))<=8*2**-23*sum(abs(v) for v in terms)+2**-149,'frustum plane contains its original corner triple')
 view=(a.private/(case+'.tsv.view.bin')).read_bytes();ck(view==z==wb(by['NATIVE_VIEW'][0]['d']['record']),'same complete camera drives terrain');ck(by['NATIVE_VIEW'][0]['d']['pointer']=='004C2730','persistent original camera pointer');views[case]=view
 cx,cy,sx,sy=unpack(view,'4f');near=unpack(view,'f',0x108)[0];far=unpack(view,'f',0x138)[0];rect=unpack(view,'4f',0x1c)
 ck((cx,cy)==(320.,240.) and rect==(0.,0.,639.,479.),'original projection from declared viewport');ck(near==f32(.1) and far==150.,'native near and far offsets');ck(sx==f32(320/unpack(view,'f',0x2c)[0]) and sy==-sx,'original FOV scale');ck(unpack(view,'I',0x3c)[0]==0x5dcec0,'viewport identity')
 grid=unpack((a.private/(case+'.tsv.grid.bin')).read_bytes(),'16384I')
 for j,ptr in enumerate(grid):
  x,z0=j%128-24,j//128-24;page=zm[z0*80+x] if 0<=x<80 and 0<=z0<80 else 255;ck(ptr==(0x59c588 if page==255 else 0x40000000+page*32768),'original M06 page grid')
 out=by['OUTPUT'][0]['d'];ck(out['harnessOutputWrites']=='0','no supplied sealed output');pre=(a.private/(case+'.tsv.pre.bin')).read_bytes() if by['PRETRANSFORM_BOUNDARY'] else b'';post=(a.private/(case+'.tsv.post.bin')).read_bytes() if by['TRANSFORM_RETURN'] else b'';vs=list(struct.iter_unpack('<3f',pre));ts=list(struct.iter_unpack('<3f',post));ck(len(vs)==len(ts)==int(out['vertices']),'vertex counts')
 sources=[];tw={int(r['d']['address'],16):r for r in by['TRANSFORM_WRITE']};vw={int(r['d']['address'],16):r for r in by['ORIGINAL_VERTEX_WRITE']}
 if vs:
  composed=wb(by['COMPOSED_MATRIX'][0]['d']['data']);mat=unpack(composed,'9f');tr=unpack(composed,'3d',40);iv=unpack(view,'9f',0x40)
  ck(mat==tuple(f32(iv[j]*([5.,f32(.1),5.][j//3])) for j in range(9)),'original composed source-unit matrix');ck(tr==unpack(view,'3d',0x68),'same camera inverse translation')
  bound=by['TRANSFORM_RETURN'][0]['d'];ck(bound['near']=='C3960000','native renderer bin minimum')
  max_depth=max([1000.]+[f32(sum(v[c]*mat[c*3+2] for c in range(3))+tr[2]+1000.) for v in vs]);expected_far=f32(max_depth+300.-1000.);ck(unpack(wb(bound['far']),'f')[0]==expected_far,'native renderer bin maximum')
  ck(unpack(wb(bound['minHeight']),'f')[0]==f32(min(v[1] for v in vs)*f32(.1)),'native minimum source height')
 for j,(v,t) in enumerate(zip(vs,ts)):
  x,h,z0=v;ck(x.is_integer() and z0.is_integer(),'integral source lattice');x,z0=int(x),int(z0);ck(0<=x<10240 and 0<=z0<10240,'source coordinate range');page=zm[z0//128*80+x//128];ck(page!=255,'active M06 page');off=page*32768+2*((z0%128)*128+x%128);word=unpack(ter,'H',off)[0];ck(h==word&4095,'source height');sources.append(dict(index=j,page=page,row=z0%128,column=x%128,offset=off,word=word,material_class=word>>13))
  addr=0x42000000+j*12;ck(addr in vw and wb(vw[addr]['d']['xyz'])==pre[j*12:j*12+12],'original source vertex writer');ck(vw[addr]['pc'] in ['00490C2D','00490CB8','00490D45','00490DD0','0049199D'],'source writer PC')
  for k in range(3):
   expect=f32(sum(v[c]*mat[c*3+k] for c in range(3))+tr[k]);ck(t[k]==expect,'rounded original transform');event=tw[addr+k*4];ck(event['pc']==['004938A8','004938BC','004938AA'][k] and int(event['d']['value'],16)==unpack(post,'I',j*12+k*4)[0],'original transform store ownership')
 for kind in ['VISUAL_HEIGHT_READ','MATERIAL_PREDICATE_READ']:
  for r in by[kind]:
   off=int(r['d']['address'],16)-0x40000000;ck(0<=off<len(ter)-1 and unpack(ter,'H',off)[0]==int(r['d']['word'],16),'original source height/material read')
 arena=(a.private/(case+'.tsv.arena.bin')).read_bytes();leaves={int(r['d']['address'],16):unpack(wb(r['d']['data']),'7I') for r in by['LEAF']}
 def edge(ptr,reverse=False,seen=()):
  ck(ptr not in seen and 0<=ptr-0x44000000<=len(arena)-12,'edge ownership/acyclic');v0,v1,c0,c1=unpack(arena,'hhII',ptr-0x44000000);ck(0<=v0<len(vs) and 0<=v1<len(vs),'edge source indices')
  if c0:return edge(c1,True,seen+(ptr,))+edge(c0,True,seen+(ptr,)) if reverse else edge(c0,False,seen+(ptr,))+edge(c1,False,seen+(ptr,))
  ck(c1==0,'paired edge children');return [v1 if reverse else v0]
 loops={ptr:edge(r[5])+edge(r[4])+edge(r[6],True)+edge(r[3],True) for ptr,r in leaves.items()};ck(set(leaves)=={int(r['d']['address'],16) for r in by['ORIGINAL_LEAF_WRITE']},'all original leaf writers')
 for event in by['ORIGINAL_LEAF_WRITE']:ck(event['pc']=='00491892','original leaf final writer PC')
 inits=by['ORIGINAL_BUCKET_INITIALIZE'];ck(len(inits)==12288 and {int(r['d']['address'],16) for r in inits}==set(range(0x48200000,0x4820c000,4)) and all(r['d']['value']=='00000000' for r in inits),'original bucket initialization')
 ck([int(r['d']['bytes']) for r in by['SERVICE_DIAGNOSTIC_HEAP']]==[370000,128000,49152,49152,2880],'original allocation requests')
 accepted={};cursor=0x48000000;bucketstate={};bins=collections.Counter();current=None;copied=None;clipcount=0;rejected=0
 for r in rs:
  d=r['d'];kind=r['kind']
  if kind=='EMITTER_ENTER':
   idx=unpack(wb(d['indices']),'I'*len(d['indices'].split(',')));leaf=int(d['leaf'],16);ck(leaf in loops and all(j in loops[leaf] for j in idx),'original leaf owns emitted indices');copied=None;polygon_writes={}
  elif kind=='ALLOCATOR_RETURN':ck(int(d['record'],16)==cursor and int(d['active'],16)==cursor,'original allocator cursor/active identity')
  elif kind=='POLYGON_XYZ_WRITE':polygon_writes[int(d['address'],16)]=r
  elif kind=='CLIP_ENTER':
   clipcount+=1;raw=wb(d['data']);head=unpack(raw,'7I');ck(head[0]==len(idx) and head[1]==0xb4 and head[3]==0,'original polygon header');ck(int(d['record'],16)==cursor,'same clip record');args=unpack(wb(d['args']),'6I');ck(args[1:]==(0x4c2730,cursor+28,cursor+28,len(idx),0),'original same-camera clip arguments');projected_events=[];poly=[]
   for k,j in enumerate(reversed(idx)):
    ck(raw[28+k*24:40+k*24]==post[j*12:j*12+12],'source emitter vertex ownership');poly.append(list(ts[j]))
    for c in range(3):
     event=polygon_writes[cursor+28+k*24+c*4];ck(event['pc']==['0049233A','0049233F','00492345'][c] and int(event['d']['value'],16)==unpack(post,'I',j*12+c*4)[0],'original emitter retired XYZ store')
   poly=clip(clip(poly,2,near,True),2,far,False)
   zpoly=poly;poly=[[f32(v[0]/v[2]*sx+cx),f32(v[1]/v[2]*sy+cy),f32(1/v[2])] for v in poly]
   for axis,bound,lower in [(0,rect[0],True),(0,rect[2],False),(1,rect[1],True),(1,rect[3],False)]:poly=clip(poly,axis,bound,lower)
  elif kind=='ORIGINAL_PROJECTION_WRITE':projected_events.append(r)
  elif kind=='SERVICE_CLIP_MEMCPY':
   copied=wb(d['data']);ck(d['caller']=='0047BEDF' and int(d['destination'],16)==cursor+28 and int(d['bytes'])==len(copied),'bounded original compact-clip copy')
  elif kind=='CLIP_RETURN':
   count=int(d['count']);result=wb(d['data']);ck(len(projected_events)==len(zpoly)*4,'original z-clipped projection count')
   for k,v in enumerate(zpoly):
    events=projected_events[k*4:k*4+4];ck([e['pc'] for e in events]==['0047C29D','0047C2AB','0047C2AF','0047C2B6'],'original projection stores')
    got=[unpack(wb(e['d']['value']),'f')[0] for e in events];want=[v[0]/v[2]*sx+cx,v[1]/v[2]*sy+cy,1/v[2],0.]
    for g,w in zip(got,want):ck(rounded(g,w,1),'independent projected coordinates')
   ck(count==len(poly),'independent depth/screen clip count')
   if not count:rejected+=1;continue
   ck(copied==result[28:28+count*24],'original clipped buffer copy identity');actual=[unpack(copied,'3f',k*24) for k in range(count)]
   # Four screen planes plus near/far can store intermediate float32 values.
   # Error is compared per coordinate using propagation below, never world units.
   ck(any(all(all(rounded(actual[k][c],poly[(k+shift)%count][c],8) for c in range(3)) for k in range(count)) for shift in range(count)),'independent clipped coordinates')
   accepted[cursor]=(count,result,idx,leaf);selected.setdefault(case,{'record':f'{cursor:08X}','source':[sources[j] for j in idx],'clip_count':count})
  elif kind=='ORIGINAL_BUCKET_WRITE':
   addr=int(d['address'],16);ck(list(unpack(wb(d['before']),'3I'))==bucketstate.get(addr,[0,0,0]),'original bucket chronology');bucketstate[addr]=list(unpack(wb(d['after']),'3I'))
  elif kind=='BIN_ENTER':ck(int(d['record'],16)==cursor and cursor in accepted,'original accepted bin handoff')
  elif kind=='BIN_RETURN':
   ck(cursor in accepted,'bin accepted clipped record');count,data,idx,leaf=accepted[cursor];depth=unpack(data,'f',16)[0];bucket=round(depth+300);ck(int(d['bucket'],16)==0x48200000+bucket*12,'original spatial depth bin');bins[bucket]+=1;ck(unpack(wb(d['bucketData']),'3I')[1:]==(cursor,bins[bucket]),'bucket tail/count');cursor+=28+count*24;ck(int(d['cursor'],16)==cursor,'original allocation advancement')
 storage=(a.private/(case+'.tsv.polygons.bin')).read_bytes();buckets=(a.private/(case+'.tsv.buckets.bin')).read_bytes();ck(len(storage)==cursor-0x48000000,'complete allocation accounting');members=set()
 for bucket in range(4096):
  head,tail,count=unpack(buckets,'3I',bucket*12);ck([head,tail,count]==bucketstate.get(0x48200000+bucket*12,[0,0,0]),'final bucket table equals original stores')
  if not count:ck(head==tail==0,'empty bucket');continue
  ptr=head;chain=[]
  while ptr:
   ck(ptr in accepted and ptr not in members,'unique accepted record ownership');members.add(ptr);chain.append(ptr);n,data,idx,leaf=accepted[ptr];off=ptr-0x48000000;ck(unpack(storage,'I',off)[0]==n and storage[off+28:off+28+n*24]==data[28:28+n*24],'final source-owned clipped record');ptr=unpack(storage,'I',off+20)[0]
  ck(len(chain)==count and chain[-1]==tail,'final original bucket chain')
 ck(members==set(accepted),'every accepted polygon actually binned')
 if case=='below':ck(not vs and not accepted and by['BOUNDS_RESULT'][0]['d']['eax']=='0','negative original region rejection')
 else:ck(vs and accepted,'coherent camera reaches original terrain binning')
 summary[case]={'vertices':len(vs),'leaves':len(leaves),'clip_attempts':clipcount,'rejected':rejected,'accepted':len(accepted),'occupied_bins':len(bins),'polygon_bytes':len(storage),'trace_sha256':sha(p.read_bytes()),'view_sha256':sha(view),'view_origin':unpack(view,'3d',0x160),'projection':{'center':[cx,cy],'scale':[sx,sy],'near':near,'far':far,'rect':rect},'determinant':det,'gram_max_error':gram}
if 'primary' in views and 'contrast' in views:ck(views['primary']!=views['contrast'] and summary['primary']['trace_sha256']!=summary['contrast']['trace_sha256'],'distinct valid configurations')
if a.repeat:
 for suffix in ['', '.view.bin','.grid.bin','.pre.bin','.post.bin','.vertices.bin','.arena.bin','.polygons.bin','.buckets.bin']:ck((a.private/('primary.tsv'+suffix)).read_bytes()==pathlib.Path(str(a.repeat)+suffix).read_bytes(),'fresh project exact repeat '+suffix)
if a.corruptions:
 for mutation,needle in [('source','source height'),('matrix','same complete camera'),('record','source emitter vertex ownership')]:
  with tempfile.TemporaryDirectory() as name:
   tmp=pathlib.Path(name)
   for p in a.private.glob('primary.tsv*'):(tmp/p.name).symlink_to(p.resolve())
   suffix='.pre.bin' if mutation=='source' else '.view.bin' if mutation=='matrix' else '';p=tmp/('primary.tsv'+suffix);b=p.read_bytes();p.unlink()
   if mutation=='source':b=b[:4]+struct.pack('<f',999.)+b[8:]
   elif mutation=='matrix':b=b[:0x40]+struct.pack('<f',99.)+b[0x44:]
   else:
    lines=b.decode().splitlines()
    for j,line in enumerate(lines):
     if '\tCLIP_ENTER\t' in line:
      k=line.index(';data=')+6;v=line[k:].split(',');v[7]='4479C000';lines[j]=line[:k]+','.join(v);break
    b=('\n'.join(lines)+'\n').encode()
   p.write_bytes(b);cmd=[sys.executable,__file__,'--private',str(tmp),'--cases','primary']
   for flag in ['msn','ter','exe','gzf','zfs','fixtures']:cmd+=['--'+flag,str(getattr(a,flag))]
   proc=subprocess.run(cmd,capture_output=True,text=True);ck(proc.returncode!=0 and needle in proc.stderr,'deliberate verifier corruption rejected '+mutation)
result={'inputs':inputs,'cases':summary,'selected':selected,'scope':'Original-updated same-camera terrain clipping/binning; controlled root/viewport, OS/resource/numerical services. No retail frame, draw or pixels.'};validation={'status':'passed','test_count':N,'passed_count':N,'notes':'Executed standalone checks of original field ownership, M06 source, camera/frustum, rounded transforms, independent depth/screen clipping, final bucket chains, differential/negative/repeat and deliberate corruptions when requested.'}
if a.emit:
 a.emit.mkdir(parents=True,exist_ok=True)
 for name,value in [('results.json',result),('validation.json',validation)]: (a.emit/name).write_text(json.dumps(value,indent=2,sort_keys=True)+'\n')
print(json.dumps(validation,indent=2))
