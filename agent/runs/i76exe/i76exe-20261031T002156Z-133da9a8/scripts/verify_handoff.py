#!/usr/bin/env python3
"""Standalone source-byte and original-event verifier; never invokes Ghidra or its producer."""
import argparse,collections,csv,hashlib,json,math,pathlib,struct,subprocess,sys,tempfile,shutil
P=argparse.ArgumentParser();P.add_argument('--private',type=pathlib.Path,required=True);P.add_argument('--msn',type=pathlib.Path,required=True);P.add_argument('--ter',type=pathlib.Path,required=True);P.add_argument('--exe',type=pathlib.Path,required=True);P.add_argument('--emit',type=pathlib.Path);P.add_argument('--cases',default='primary,contrast,below,baseline,diagnostic,projected,alternate');P.add_argument('--repeat',type=pathlib.Path);P.add_argument('--negative-controls',action='store_true');a=P.parse_args();N=0

def check(v,msg):
 global N
 N+=1
 if not v:raise AssertionError(msg)
def sha(b):return hashlib.sha256(b).hexdigest()
def f32(x):return struct.unpack('<f',struct.pack('<f',x))[0]
def words(s):return [int(x,16) for x in s.split(',')]
def wb(s):return struct.pack('<'+'I'*len(words(s)),*words(s))
def rows(p):
 with p.open() as f:return [{**r,'d':dict(t.split('=',1) for t in r['detail'].split(';') if '=' in t)} for r in csv.DictReader(f,delimiter='\t')]
msn=a.msn.read_bytes();ter=a.ter.read_bytes();pe=a.exe.read_bytes()
for data,h in [(msn,'923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f'),(ter,'fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea'),(pe,'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3')]:check(sha(data)==h,'authenticated input')
ph=struct.unpack_from('<I',pe,60)[0];sec=ph+24+struct.unpack_from('<H',pe,ph+20)[0];sections=[struct.unpack_from('<III',pe,sec+j*40+12) for j in range(struct.unpack_from('<H',pe,ph+6)[0])]
def at(va,n):
 for rv,size,off in sections:
  if rv<=va-0x400000 and va-0x400000+n<=rv+size:return pe[off+va-0x400000-rv:off+va-0x400000-rv+n]
 raise AssertionError('unmapped retail anchor')
run=pathlib.Path(__file__).resolve().parent.parent
for r in csv.DictReader((run/'evidence/instruction_anchors.tsv').open(),delimiter='\t'):
 b=bytes.fromhex(r['hex']);check(at(int(r['va'],16),len(b))==b,'authenticated original instruction '+r['va'])
audit=a.private/'retail_audit.txt'
if audit.exists():
 lines=[l for l in audit.read_text().splitlines() if l.startswith('CODE_EQUAL\t')];check(len(lines)==1,'one complete executable section equality');_,rv,size,h=lines[0].split('\t');check(sha(at(0x400000+int(rv,16),int(size)))==h,'fresh imported original executable bytes')
zm=msn[msn.index(b'ZMAP')+9:][:6400];sy=f32(.1);summary={};selected={}
for case in a.cases.split(','):
 path=a.private/(case+'.tsv');rs=rows(path);by=collections.defaultdict(list)
 for r in rs:by[r['kind']].append(r)
 check(not by['BLOCKER'],'no unexplained blocker '+case);
 grid=struct.unpack('<16384I',(a.private/(case+'.tsv.grid.bin')).read_bytes())
 for j,ptr in enumerate(grid):
  x,z=j%128-24,j//128-24;page=zm[z*80+x] if 0<=x<80 and 0<=z<80 else 255;check(ptr==(0x59c588 if page==255 else 0x40000000+page*32768),'original initialized grid source pointer')
 for kind in ['VISUAL_HEIGHT_READ','MATERIAL_PREDICATE_READ']:
  for r in by[kind]:
   atword=int(r['d']['address'],16)-0x40000000;check(0<=atword<len(ter)-1,'source read ownership');check(struct.unpack_from('<H',ter,atword)[0]==int(r['d']['word'],16),'original source word read')
 out=by['OUTPUT'][0]['d'];check(out['harnessOutputWrites']=='0','no harness source geometry writes')
 vb=(a.private/(case+'.tsv.pre.bin')).read_bytes() if by['PRETRANSFORM_BOUNDARY'] else b'';post=(a.private/(case+'.tsv.post.bin')).read_bytes() if by['TRANSFORM_RETURN'] else b''
 vs=list(struct.iter_unpack('<fff',vb));ts=list(struct.iter_unpack('<fff',post));check(len(vs)==len(ts),'transform counts');sources=[]
 view=wb(by['CONTROLLED_VIEW'][0]['d']['record']);basis=struct.unpack_from('<9f',view,0x40);tr=struct.unpack_from('<3d',view,0x68)
 check(basis==(1.,0.,0.,0.,1.,0.,0.,0.,1.),'declared proper affine identity basis');check(tr==(-3152.5 if case=='contrast' else -2952.5,-200.,-47800.),'declared affine translation')
 writers={int(r['d']['address'],16):r for r in by['ORIGINAL_VERTEX_WRITE']};tw={int(r['d']['address'],16):r for r in by['TRANSFORM_WRITE']};maxerr=0
 for j,(v,t) in enumerate(zip(vs,ts)):
  x,h,z=v;check(x.is_integer() and z.is_integer(),'integral source lattice');x,z=int(x),int(z);check(0<=x<10240 and 0<=z<10240,'source grid range');page=zm[z//128*80+x//128];check(page!=255,'active source page');off=page*32768+2*((z%128)*128+x%128);w=struct.unpack_from('<H',ter,off)[0];check(h==w&4095,'authenticated source height')
  sources.append(dict(index=j,page=page,row=z%128,column=x%128,offset=off,word=w,height=w&4095,material_class=w>>13))
  addr=0x42000000+j*12;check(addr in writers,'original source writer for every vertex');check(writers[addr]['pc'] in ['00490C2D','00490CB8','00490D45','00490DD0','0049199D'],'original source instruction writer');check(wb(writers[addr]['d']['xyz'])==vb[j*12:j*12+12],'source original-write bytes')
  expected=[x*5+tr[0],(w&4095)*sy+tr[1],z*5+tr[2]]
  for k in range(3):
   # Fixture products and translations are exact dyadic values in binary64;
   # x87 products/additions introduce no intermediate rounding here. One final
   # float32 rounding is the entire error budget: require exact rounded bits.
   check(t[k]==f32(expected[k]),'exact one-round float32 transform');maxerr=max(maxerr,abs(t[k]-expected[k]));at=addr+k*4;check(at in tw,'original transform write ownership');check(int(tw[at]['d']['value'],16)==struct.unpack_from('<I',post,j*12+k*4)[0],'original retired transform value');check(tw[at]['pc']==['004938A8','004938BC','004938AA'][k],'original transform store instruction')
 check(len(tw)==len(vs)*3,'exact transform write count')
 if vs:
  composed=wb(by['COMPOSED_MATRIX'][0]['d']['data']);check(struct.unpack_from('<9f',composed)==(5.,0.,0.,0.,sy,0.,0.,0.,5.),'original composed scale basis');check(struct.unpack_from('<3d',composed,40)==tr,'original composed translation')
  check(by['PRETRANSFORM_BOUNDARY'][0]['d']['caller']=='00490EF2','original call ownership');bound=by['TRANSFORM_RETURN'][0]['d'];check(bound['near']=='C3960000','original near bound -300');far=f32(max(1000.,max(t[2]+1000 for t in ts))+300-1000);check(int(bound['far'],16)==struct.unpack('<I',struct.pack('<f',far))[0],'original far bound');check(int(bound['minHeight'],16)==struct.unpack('<I',struct.pack('<f',min(v[1] for v in vs)*sy))[0],'original minimum source height bound')
 arena=(a.private/(case+'.tsv.arena.bin')).read_bytes();leaves={int(r['d']['address'],16):words(r['d']['data']) for r in by['LEAF']}
 def edge(at,rev=False,seen=()):
  check(at not in seen,'acyclic edges');off=at-0x44000000;check(0<=off<=len(arena)-12,'edge memory ownership');v0,v1,c0,c1=struct.unpack_from('<hhII',arena,off);check(0<=v0<len(vs) and 0<=v1<len(vs),'source-owned edge endpoints')
  if c0:return edge(c1,True,seen+(at,))+edge(c0,True,seen+(at,)) if rev else edge(c0,False,seen+(at,))+edge(c1,False,seen+(at,))
  check(c1==0,'paired child state');return [v1 if rev else v0]
 leaf_writes={int(r['d']['address'],16):words(r['d']['data']) for r in by['ORIGINAL_LEAF_WRITE']};leaf_enters={int(r['d']['cursor'],16):words(r['d']['edges']) for r in by['LEAF_ENTER']}
 check(set(leaves)==set(leaf_writes)==set(leaf_enters),'all original leaf allocator/writer ownership')
 for atleaf,rec in leaves.items():
  check(rec[:2]+rec[3:]==leaf_writes[atleaf][:2]+leaf_writes[atleaf][3:],'original leaf retired fields retained');check(rec[3:]==leaf_enters[atleaf],'source edges survive leaf allocator boundary')
 loops={at:edge(rec[5])+edge(rec[4])+edge(rec[6],True)+edge(rec[3],True) for at,rec in leaves.items()}
 if case in ['diagnostic','projected','alternate']:
  inits=by['ORIGINAL_BUCKET_INITIALIZE'];check(len(inits)==12288,'all original bucket initialization stores executed');check({int(r['d']['address'],16) for r in inits}==set(range(0x48200000,0x4820c000,4)),'original initializer owns entire bucket table');check(all(r['d']['value']=='00000000' for r in inits),'original initialization clears bucket dwords')
 current=None;record=None;entered=[];clips=0;bins=0;rejects=0;pw={};candidate=None;next_record=0x48000000;copied=None;projected={};bucket_counts=collections.Counter();accepted={};cursor_writes=[];bucket_state={};projected_input=None
 for r in rs:
  d=r['d'];kind=r['kind']
  if kind=='EMITTER_ENTER':
   idx=words(d['indices']);leaf=int(d['leaf'],16);check(leaf in loops,'emitter original leaf ownership');check(all(j in loops[leaf] for j in idx),'emitted vertices resolve to source leaf');check(len(idx)>=3,'valid candidate count');current=idx;candidate=d;entered.append(idx);pw={};projected={};copied=None;projected_input=None
  elif kind=='ALLOCATOR_RETURN':
   record=int(d['record'],16);check(record==(0 if case=='baseline' else next_record),'allocator result in declared context')
  elif kind=='ORIGINAL_BUCKET_WRITE':
   atbucket=int(d['address'],16);check(words(d['before'])==bucket_state.get(atbucket,[0,0,0]),'original bucket mutation chronology');bucket_state[atbucket]=words(d['after']);check(0x48fe10<=int(r['pc'],16)<=0x490465,'bucket change in original bin body')
  elif kind=='ORIGINAL_BIN_CURSOR_WRITE':cursor_writes.append(r)
  elif kind=='ORIGINAL_PROJECTION_WRITE':projected[int(d['address'],16)]=r
  elif kind=='POLYGON_XYZ_WRITE':pw[int(d['address'],16)]=r
  elif kind=='CLIP_ENTER':
   clips+=1;data=wb(d['data']);rec=struct.unpack_from('<7I',data);check(rec[0]==len(current) and rec[1]==0xb4 and rec[3]==0,'original record count/B4/type0');check(int(d['record'],16)==record,'same allocated record');args=words(d['args']);check(args[1:]==[0x45000000,record+28,record+28,len(current),0],'original clip arguments')
   for k,j in enumerate(reversed(current)):
    check(data[28+k*24:40+k*24]==post[j*12:j*12+12],'original emitter reverses source indices and copies XYZ')
    for c in range(3):
     at=record+28+k*24+c*4;check(at in pw,'original polygon field writer');check(int(pw[at]['d']['value'],16)==struct.unpack_from('<I',post,j*12+c*4)[0],'retired polygon coordinate write')
   if clips==1:selected[case]={'leaf':candidate['leaf'],'source_indices':current,'record':f'{record:08X}','record_bytes':len(data),'source':[sources[j] for j in current],'clip_input_words':d['data']}
  elif kind=='SERVICE_CLIP_MEMCPY':
   check(case=='projected','explicit memcpy context');copied=wb(d['data']);check(d['caller']=='0047BEDF','original compact clip memcpy callsite');check(int(d['destination'],16)==record+28 and int(d['bytes'])==len(copied),'same owned output buffer')
  elif kind=='CLIP_RETURN':
   count=int(d['count']);rejects+=count==0
   if case!='projected':check(count==0,'original default depth interval rejects all candidates')
   else:
    check(count>0,'original clip accepts candidate in controlled projection');data=wb(d['data']);check(data[28:28+count*24]==copied,'CRT copies original clip stack result exactly');check(len(projected)==len(current)*4,'every original projection field store observed')
    proj_rows=list(projected.values());projected_expected=[]
    for k,j in enumerate(reversed(current)):
     x,y,z=ts[j];ev=proj_rows[k*4:k*4+4];check([e['pc'] for e in ev]==['0047C29D','0047C2AB','0047C2AF','0047C2B6'],'original projection XYZ/light store sequence');got=[struct.unpack('<f',struct.pack('<I',int(e['d']['value'],16)))[0] for e in ev];want=[x/z*320+320,y/z*(-320)+240,1/z,0.]
     for value,expected in zip(got,want):
      rounded=f32(expected);ulp=abs(struct.unpack('<f',struct.pack('<I',struct.unpack('<I',struct.pack('<f',abs(rounded)))[0]+1))[0]-abs(rounded)) if rounded else 2**-149
      check(abs(value-rounded)<=ulp,'projection one float32 ULP: x87 reciprocal/product/add then final store')
     projected_expected.append(got[:3])
    # Independent screen clipping; binary64 is ample for the float32 coordinates.
    poly=projected_expected
    for axis,bound,lower in [(0,0.,True),(0,640.,False),(1,0.,True),(1,480.,False)]:
     output=[]
     for k,q in enumerate(poly):
      prev=poly[k-1];inq=q[axis]>=bound if lower else q[axis]<bound;inp=prev[axis]>=bound if lower else prev[axis]<bound
      if inq!=inp:
       t=(bound-prev[axis])/(q[axis]-prev[axis]);v=[f32(prev[c]+t*(q[c]-prev[c])) for c in range(3)];v[axis]=bound;output.append(v)
      if inq:output.append(q)
     poly=output
    check(len(poly)==count,'independent screen clip vertex count')
    actual=[struct.unpack_from('<3f',copied,k*24) for k in range(count)]
    # Cyclic polygon order is preserved by clipping; permit a cyclic start shift.
    def close(v,w):
     for x,y in zip(v,w):
      y=f32(y);bits=struct.unpack('<I',struct.pack('<f',abs(y)))[0];ulp=struct.unpack('<f',struct.pack('<I',bits+1))[0]-abs(y) if y else 2**-149
      if abs(x-y)>4*ulp:return False
     return True
    check(any(all(close(actual[k],poly[(k+shift)%count]) for k in range(count)) for shift in range(count)),'independent screen clip positions: four ULP budget for stored interpolation stages')
    check(all(0<=v[0]<=640 and 0<=v[1]<=480 and v[2]>0 for v in actual),'accepted output lies in screen/depth domain');accepted[record]=(count,data,candidate['leaf'],list(current))
  elif kind=='BIN_ENTER':
   bins+=1;check(case=='projected','bin only with full diagnostic projection');check(int(d['record'],16)==record and int(d['cursor'],16)==record,'same candidate handed to original bin')
  elif kind=='BIN_RETURN':
   check(record in accepted,'accepted original clipped polygon');count,data,leaf,idx=accepted[record];next_record=record+28+count*24;check(int(d['cursor'],16)==next_record,'original variable record stride');check(cursor_writes and int(cursor_writes[-1]['d']['before'],16)==record and int(cursor_writes[-1]['d']['after'],16)==next_record,'original instruction advances cursor');depth=struct.unpack_from('<f',data,16)[0];bucket=round(depth+300);check(int(d['bucket'],16)==0x48200000+bucket*12,'original bucket index from pre-projection depth');bucket_counts[bucket]+=1;head,tail,n=words(d['bucketData']);check(tail==record and n==bucket_counts[bucket],'original bucket tail/count after insertion')
 check(bins==0 if case!='projected' else bins==clips>0,'bin acceptance boundary')
 if case=='projected':
  storage=(a.private/(case+'.tsv.polygons.bin')).read_bytes();buckets=(a.private/(case+'.tsv.buckets.bin')).read_bytes();check(len(storage)==next_record-0x48000000,'final polygon allocation accounting');members=set()
  for b in range(4096):
   head,tail,n=struct.unpack_from('<3I',buckets,b*12);check([head,tail,n]==bucket_state.get(0x48200000+b*12,[0,0,0]),'original retired bucket writes equal final table')
   if not n:check(head==tail==0,'empty bucket ownership');continue
   ptr=head;chain=[]
   while ptr:
    check(ptr in accepted and ptr not in members,'accepted original record belongs to one bin');members.add(ptr);chain.append(ptr);off=ptr-0x48000000;cnt=struct.unpack_from('<I',storage,off)[0];count,data,leaf,idx=accepted[ptr];check(cnt==count,'final accepted count');check(storage[off+28:off+28+cnt*24]==data[28:28+cnt*24],'same clipped vertices retained in original bin');ptr=struct.unpack_from('<I',storage,off+20)[0]
   check(len(chain)==n and chain[-1]==tail,'final bucket chain length/tail')
  check(members==set(accepted),'every accepted candidate is actually binned')
 if case=='baseline':check(len(entered)==1 and by['ALLOCATOR_RETURN'][0]['d']['record']=='00000000' and not by['CLIP_ENTER'],'unmodified null allocator baseline');check([r['d']['address'] for r in by['ALLOCATOR_WRITE']]==['00000014','00000000'],'original null allocator stores captured')
 if case=='alternate':
  check(len(entered)==1 and len(by['DESCRIPTOR_SELECT'])==1 and len(by['DESCRIPTOR_RETURN'])==1 and len(by['ALTERNATE_HEADER_STOP'])==1,'original alternate leaf/descriptor/emitter header reached');desc=by['DESCRIPTOR_SELECT'][0]['d'];pair=words(desc['pair']);args=words(desc['args']);check(0x5a4588<=args[1]<=0x5a4588+6*8 and (args[1]-0x5a4588)%8==0,'original descriptor-pair table ownership');check(pair==[0,0] and by['DESCRIPTOR_RETURN'][0]['d']['value']=='00000000','uninitialized texture pair gives original null descriptor');header=words(by['ALTERNATE_HEADER_STOP'][0]['d']['header']);check(header[1]==header[3]==0,'original alternate record descriptor/type fields');check(not clips,'alternate stops before copying/clip with absent texture state')
 if case=='diagnostic':check(len(by['SERVICE_DIAGNOSTIC_HEAP'])==5 and clips==len(entered)>0 and rejects==clips,'separate native arena initializer diagnostic');check(any(r['pc']=='00490A00' for r in by['RETURN']),'original producer and walker return')
 if case=='below':check(not vs and not entered and by['BOUNDS_RESULT'][0]['d']['eax']=='0','rejected region contains no source primitives')
 if case=='contrast':check(len(vs)!=summary['primary']['source_vertices'],'valid changed view changes source primitives');check(sha(post)!=summary['primary']['post_sha256'],'valid changed view changes transform output')
 summary[case]={'source_vertices':len(vs),'leaves':len(leaves),'transform_writes':len(tw),'max_float32_rounding_error':maxerr,'emitter_entries':len(entered),'clip_calls':clips,'clip_rejections':rejects,'bin_calls':bins,'accepted_record_bytes':next_record-0x48000000 if case=='projected' else 0,'occupied_bins':len(bucket_counts),'pre_sha256':sha(vb),'post_sha256':sha(post),'trace_sha256':sha(path.read_bytes()),'arena_sha256':sha(arena)}
if a.repeat:
 for case in ['projected']:
  for suffix in ['', '.grid.bin','.pre.bin','.post.bin','.vertices.bin','.arena.bin','.polygons.bin','.buckets.bin']:check((a.private/(case+'.tsv'+suffix)).read_bytes()==(a.repeat/(case+'.tsv'+suffix)).read_bytes(),'fresh-project byte equality '+case+suffix)
if a.negative_controls:
 for mutation,needle in [('source','authenticated source height'),('transform','exact one-round float32 transform'),('record','original emitter reverses source indices')]:
  with tempfile.TemporaryDirectory() as name:
   tmp=pathlib.Path(name)
   for p in a.private.glob('diagnostic.tsv*'):(tmp/p.name).symlink_to(p.resolve())
   suffix='.pre.bin' if mutation=='source' else '.post.bin' if mutation=='transform' else ''
   target=tmp/('diagnostic.tsv'+suffix);payload=target.read_bytes();target.unlink()
   if mutation=='source':payload=payload[:4]+struct.pack('<f',999.)+payload[8:]
   elif mutation=='transform':payload=struct.pack('<f',999.)+payload[4:]
   else:
    lines=payload.decode().splitlines()
    for j,line in enumerate(lines):
     if '\tCLIP_ENTER\t' in line:
      start=line.index(';data=')+6;fields=line[start:].split(',');fields[7]='4479C000';lines[j]=line[:start]+','.join(fields);break
    payload=('\n'.join(lines)+'\n').encode()
   target.write_bytes(payload);proc=subprocess.run([sys.executable,__file__,'--private',str(tmp),'--msn',str(a.msn),'--ter',str(a.ter),'--exe',str(a.exe),'--cases','diagnostic'],capture_output=True,text=True);check(proc.returncode!=0 and needle in proc.stderr,'verifier rejects deliberate '+mutation+' corruption')
result={'cases':summary,'selected_candidates':selected,'scope':'Original source transformation, original-authored candidates, arena-only clip rejection and controlled projected clip/bin acceptance. No retail allocator lifecycle, textures or framebuffer.'}
validation={'status':'passed','test_count':N,'passed_count':N,'notes':'Actually executed standalone assertions; source provenance, exact rounded transforms, original writes, leaf and candidate ownership, null baseline and separate allocator diagnostic, controls and fresh repeat where requested.'}
if a.emit:
 a.emit.mkdir(parents=True,exist_ok=True);(a.emit/'results.json').write_text(json.dumps(result,indent=2,sort_keys=True)+'\n');(a.emit/'validation.json').write_text(json.dumps(validation,indent=2,sort_keys=True)+'\n')
print(json.dumps(validation,indent=2))
