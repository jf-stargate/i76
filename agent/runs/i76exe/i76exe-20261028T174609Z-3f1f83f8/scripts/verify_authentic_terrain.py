#!/usr/bin/env python3
"""Independently verify original-PE anchors, retail terrain and replay numerics."""
import argparse,csv,hashlib,json,math,struct,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--run',type=Path,required=True);p.add_argument('--private',type=Path,required=True);p.add_argument('--exe',type=Path,required=True);p.add_argument('--gzf',type=Path,required=True);p.add_argument('--zfs',type=Path,required=True);p.add_argument('--msn',type=Path,required=True);p.add_argument('--ter',type=Path,required=True);p.add_argument('--x87-service',type=Path,required=True);a=p.parse_args();N=0

def check(v,why):
 global N;N+=1
 if not v:raise AssertionError(f'{N}: {why}')
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def rows(p):return list(csv.DictReader(p.open(),delimiter='\t'))
def fields(r):return dict(x.split('=',1) for x in r['detail'].split(';') if '=' in x)
def f32(x):return struct.unpack('<f',struct.pack('<f',x))[0]
def fhex(h):return struct.unpack('<f',struct.pack('<I',int(h,16)))[0]
def ext80(h):
 x=int(h,16);ex=(x>>64)&32767;v=0 if x==0 else math.ldexp(float(x&((1<<64)-1)),ex-16383-63);return -v if x>>79 else v
for path,d in [(a.exe,'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'),(a.gzf,'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'),(a.zfs,'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'),(a.msn,'923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f'),(a.ter,'fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea')]:check(sha(path)==d,'private source identity')
b=a.exe.read_bytes();pe=struct.unpack_from('<I',b,60)[0];n=struct.unpack_from('<H',b,pe+6)[0];sh=pe+24+struct.unpack_from('<H',b,pe+20)[0];ss=[struct.unpack_from('<8sIIII',b,sh+i*40) for i in range(n)]
def at(va,count):
 for _,vs,rv,size,pos in ss:
  if rv<=va-0x400000 and va-0x400000+count<=rv+size:return b[pos+va-0x400000-rv:pos+va-0x400000-rv+count]
 raise AssertionError(hex(va))
for x in rows(a.run/'evidence/instruction_anchors.tsv'):
 va=int(x['va'],16);bs=bytes.fromhex(x['hex']);check(at(va,len(bs))==bs,'retail instruction '+x['va'])
 if bs[0]==0xe8:check(va+5+struct.unpack('<i',bs[1:5])[0]==int(x['instruction'].split('0x')[-1],16),'original direct CALL')
msn=a.msn.read_bytes();ter=a.ter.read_bytes();zoff=msn.index(b'ZMAP');zm=msn[zoff+9:zoff+6409];wrld=msn.index(b'WRLD');scale=f32(.2);height_scale=f32(.1)
def word(ix,iz):
 check(0<=ix<10240 and 0<=iz<10240,'sample inside mission grid')
 zone=zm[(iz//128)*80+ix//128];check(zone!=255,'sample uses authentic active page')
 off=zone*0x8000+2*((iz%128)*128+ix%128);return struct.unpack_from('<H',ter,off)[0]
def height(x,z):
 sx=x*scale;sz=z*scale;ix=math.floor(sx);iz=math.floor(sz);fx=sx-ix;fz=sz-iz
 h00=word(ix,iz)&4095;h10=word(ix+1,iz)&4095;h01=word(ix,iz+1)&4095;h11=word(ix+1,iz+1)&4095
 top=f32(h00+(h10-h00)*fx);bottom=f32(h01+(h11-h01)*fx)
 return (top+(bottom-top)*fz)*height_scale
def material(x,z):return word(round(x*scale),round(z*scale))>>13
expected=bytearray(struct.pack('<I',0x0059c588)*16384)
for z in range(80):
 for x in range(80):
  zone=zm[z*80+x]
  if zone!=255:struct.pack_into('<I',expected,4*((z+24)*128+x+24),0x40000000+zone*32768)
prov=json.loads((a.run/'evidence/provenance.json').read_text());summary=json.loads((a.run/'evidence/results.json').read_text());published=rows(a.run/'evidence/selected_events.tsv');all_traces={};errors=[];requests=[];request_expected=[]
for name,meta in prov['traces'].items():
 path=a.private/f'publish_{name}.tsv';check(sha(path)==meta['sha256'] and path.stat().st_size==meta['bytes'],'source trace '+name);r=rows(path);all_traces[name]=r
 check((a.private/f'publish_{name}.tsv.grid.bin').read_bytes()==expected,'all 16384 original-initialized page pointers')
 ev=lambda k:[x for x in r if x['kind']==k]
 if name!='bus_repeat':
  keep={'TERRAIN_INITIALIZED','TERRAIN_PAGE_CHECK','TERRAIN_PAGE','WRLD_MATERIALS','TERRAIN_SAMPLE','FILTER_INIT_RETURN','RETAIL_SPAWN_POSE','CONTACT_GEOMETRY','NATIVE_reporter_RET','ENGINE_VARIANTS_INITIALIZED','ENGINE_VARIANT_ROW','COMPONENT_RECORDS','TWO_FRAME_NUMERICAL_RESULT','POSE_GRAM'}
  want=[{'test':name,**{k:x[k] for k in ['kind','pc','detail']}} for x in r if x['kind'] in keep or x['kind']=='TIRE_CONTACT_RETURN' and fields(x)['mode']=='0'];check(want==[x for x in published if x['test']==name],'published events versus private source')
 check(not ev('NATIVE_reporter_RET'),'no original error reporter');check(fields(ev('ENGINE_VARIANTS_INITIALIZED')[0])['count']=='12','original engine registry initialized');
 check(len(ev('TERRAIN_INITIALIZED'))==1 and fields(ev('TERRAIN_INITIALIZED')[0])['scale']=='3E4CCCCD','original scale initialization')
 props=fields(ev('WRLD_MATERIALS')[0])['properties'].split(',');raw=b''.join(struct.pack('<I',int(v,16)) for v in props)
 check(raw==msn[wrld+0x9f:wrld+0x9f+160],'all original WRLD property bytes');check(raw[2*20:3*20]==raw[6*20:7*20] and raw[3*20:4*20]==raw[7*20:8*20],'road property aliases 2/6 and 3/7')
 variant=[fields(x) for x in ev('ENGINE_VARIANT_ROW')];engine_lines=[line.split() for line in (a.private/'fixtures/engsnd.dat').read_text().splitlines() if line.strip() and not line.lstrip().startswith('#')]
 check([(int(x['id']),int(x['component']),int(x['flags'])) for x in variant]==[tuple(map(int,line[:3])) for line in engine_lines],'original registry versus authentic engsnd data')
 vc=(a.private/'fixtures'/('noal01.vcf' if name in ['gtsi','slow'] else 'nobus1.vcf')).read_bytes();vpos=vc.index(b'VCFC');engine_id=struct.unpack_from('<I',vc,vpos+0x32)[0];engine_index=next(int(x['component']) for x in variant if int(x['id'])==engine_id)
 cdf=(a.private/'fixtures/compnent.cdf').read_bytes();chunks={b'ENGN':[],b'BRAK':[],b'SUSP':[]};off=0
 while off+8<=len(cdf):
  tag,size=struct.unpack_from('<4sI',cdf,off)
  if tag in chunks:chunks[tag].append(cdf[off:off+size])
  check(size>=8,'CDF record size');off+=size
 comp=fields(ev('COMPONENT_RECORDS')[0]);eng=list(int(x,16) for x in comp['engine'].split(','));chunk=chunks[b'ENGN'][engine_index];hp,drive=struct.unpack_from('<II',chunk,8);check(eng[0]==eng[1]==hp and eng[5]==drive,'original selected engine CDF values')
 for key,tag,vo in [('brake',b'BRAK',0x3a),('suspension',b'SUSP',0x36)]:
  index=struct.unpack_from('<I',vc,vpos+vo)[0];record=chunks[tag][index];hp,scalar=struct.unpack_from('<II',record,8);words=[int(x,16) for x in comp[key].split(',')]
  if key=='brake':check(words[1]==words[2]==hp and words[3]==scalar,'original selected brake CDF values')
  else:check(words[0]==words[1]==hp and words[2]==index and words[5]==words[6]==scalar,'original selected suspension CDF values')
 for x in ev('TERRAIN_NATIVE_READ'):
  d=fields(x);off=int(d['offset'],16);check(int(d['address'],16)==0x40000000+off and 0<=off<=len(ter)-2,'original terrain read bounds');check(int(d['word'],16)==struct.unpack_from('<H',ter,off)[0],'original terrain read value')
 local_errors=[]
 for x in ev('TERRAIN_SAMPLE')+ev('HEIGHT_RETURN'):
  d=fields(x);xx=float(d['x']);zz=float(d['z']);want=height(xx,zz);err=abs(float(d['height'])-want);local_errors.append(err)
  if name!='raw':check(err<2e-5,'independent bilinear height '+str((xx,zz,err)))
  if 'material' in d:check(int(d['material'])==material(xx,zz),'original packed material')
 if name!='raw':errors.extend(local_errors)
 check(math.isclose(max(local_errors),summary[name]['max_height_error'],abs_tol=1e-12),'published numeric error summary')
 frames=ev('TWO_FRAME_NUMERICAL_RESULT');solvers=ev('SOLVER_RETURN');returns=[x for x in ev('RETURN') if x['pc']=='00463800']
 check(len(frames)==summary[name]['frames']==len(returns),'complete original callback count');check(len(solvers)==summary[name]['solver_returns'],'completed original solver count')
 if name=='slow':check(len(solvers)==3*len(frames),'three original substeps per slow frame')
 for x in frames:
  d=fields(x);check(d['basisBadF32']==d['positionBadD64']==d['cameraBadD64']=='0','typed finite state');check(abs(float(d['axisNormSq'])-1)<1e-4,'near unit direction')
 for x in ev('POSE_GRAM'):
  d=fields(x);basis=list(map(fhex,d['basis'].split(',')));gram=[sum(basis[i*3+k]*basis[j*3+k] for k in range(3)) for i in range(3) for j in range(i,3)];check(max(abs(v-w) for v,w in zip(gram,[1,0,0,1,0,1]))<1e-4,'full near-orthonormal basis')
 tire=ev('TIRE_CONTACT_RETURN');contact=[fields(x) for x in tire if fields(x)['mode']=='0']
 if name!='raw':check(len(contact)>0 and any(abs(float(x['compression']))>.001 for x in contact),'positive finite tire compression in contact mode')
 for x in tire:
  d=fields(x);v=float(d['compression']);check(math.isfinite(float(d['height'])) and float(d['rangeMin'])-1e-6<=v<=float(d['rangeMax'])+1e-6,'original tire limits')
 # Validate the real filter initialization, not an omitted-function stub.
 enters=ev('FILTER_INIT_ENTER');outs=ev('FILTER_INIT_RETURN');check(len(enters)==len(outs)>=4,'full original filter initializers')
 pi_const=struct.unpack('<f',at(0x4bea14,4))[0];mult=struct.unpack('<f',at(0x4bea18,4))[0]
 for en,out in zip(enters,outs):
  par=fields(en);d=fields(out);aa=float(par['a']);bb=max(float(par['b']),4);want=math.cos(pi_const/bb)*aa*mult
  check(math.isclose(float(d['a']),want,rel_tol=3e-8),'filter cosine coefficient');check(math.isclose(float(d['b']),aa*aa,rel_tol=1e-7),'filter squared coefficient');check(float(d['gain'])>0 and d['previous0']==d['previous1']=='0.0','filter gain/history initialization')
 for x in ev('HARDWARE_FISTP'):
  d=fields(x);cw=int(d['cw'],16);requests.append(int(d['st0'],16).to_bytes(10,'little')+struct.pack('<H',cw));request_expected.append(('int',int(d['result'])));check(cw&0xc00==0x400,'original sampler requests round down');check(int(d['result'])==math.floor(ext80(d['st0'])),'floor semantics')
 for x in ev('HARDWARE_FCOS'):
  d=fields(x);requests.append(int(d['input'],16).to_bytes(10,'little')+struct.pack('<H',int(d['cw'],16)|0x8000));request_expected.append(('cos',int(d['result'],16)));check(abs(ext80(d['result'])-math.cos(ext80(d['input'])))<1e-15,'hardware cosine sanity')
check((a.private/'publish_bus.tsv').read_bytes()==(a.private/'publish_bus_repeat.tsv').read_bytes(),'byte-identical independent bus replay')
result=subprocess.run([str(a.x87_service.resolve())],input=b''.join(requests),capture_output=True,check=True).stdout;off=0
for kind,want in request_expected:
 count=8 if kind=='int' else 10;got=int.from_bytes(result[off:off+count],'little',signed=kind=='int');off+=count;check(got==want,'independent host x87 replay')
check(off==len(result),'host service response length');check(summary['raw']['max_height_error']>.1,'uncorrected Ghidra diagnostic differs')
print(json.dumps({'status':'passed','test_count':N,'passed_count':N,'notes':f'Original retail input/PE identity, original grid/material initialization, every logged TER read, independent bilinear/material model (maximum corrected error {max(errors):.3g}), original callback/solver completion, typed pose/camera checks, contact compression limits and independent hardware FISTP/FCOS replay.'},indent=2))
