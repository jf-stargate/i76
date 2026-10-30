#!/usr/bin/env python3
"""Independent typed source/graph/instruction checks. No emulator or mesh producer.
Requires licensed inputs and private outputs; emits only bounded derived evidence.
"""
import argparse, collections, csv, hashlib, json, math, pathlib, struct, subprocess
P=argparse.ArgumentParser();P.add_argument('--run',type=pathlib.Path,required=True);P.add_argument('--private',type=pathlib.Path,required=True);P.add_argument('--repeat',type=pathlib.Path,required=True)
for x in ('exe','gzf','zfs','msn','ter','service'):P.add_argument('--'+x,type=pathlib.Path,required=True)
P.add_argument('--emit',type=pathlib.Path);a=P.parse_args();N=0

def check(ok,why):
 global N
 N+=1
 if not ok:raise AssertionError(why)
def sha(b):return hashlib.sha256(b).hexdigest()
def dump(p,x):p.write_text(json.dumps(x,indent=2,sort_keys=True)+'\n')
def detail(s):return dict(t.split('=',1) for t in s.split(';') if '=' in t)
def rows(p):
 with p.open() as f:return [{**r,'d':detail(r['detail'])} for r in csv.DictReader(f,delimiter='\t')]
def ext(n):
 v=int(n,16);e=(v>>64)&32767;m=v&((1<<64)-1)
 return (-1 if v>>79 else 1)*math.ldexp(float(m),e-16383-63) if m else 0.
expected={'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d','msn':'923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f','ter':'fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea'}
for k,h in expected.items():check(sha(getattr(a,k).read_bytes())==h,'private identity '+k)
pe=a.exe.read_bytes();ph=struct.unpack_from('<I',pe,60)[0];sec=ph+24+struct.unpack_from('<H',pe,ph+20)[0];sections=[]
for j in range(struct.unpack_from('<H',pe,ph+6)[0]):
 p=sec+40*j;_,vs,rv,size,off=struct.unpack_from('<8sIIII',pe,p);sections.append((rv,size,off))
def at(va,n):
 for rv,size,off in sections:
  if rv<=va-0x400000 and va-0x400000+n<=rv+size:return pe[off+va-0x400000-rv:off+va-0x400000-rv+n]
 raise AssertionError(hex(va))
anchors=list(csv.DictReader((a.run/'evidence/instruction_anchors.tsv').open(),delimiter='\t'))
for r in anchors:
 va=int(r['va'],16);bs=bytes.fromhex(r['hex']);check(at(va,len(bs))==bs,'retail opcode '+r['va'])
 if bs[0]==0xe8:check(va+5+struct.unpack('<i',bs[1:])[0]==int(r['instruction'].split('0x')[-1],16),'direct call target')
audit=(a.private/'retail_audit.txt').read_text();code_line=next(l for l in audit.splitlines() if l.startswith('CODE_EQUAL\t'));_,rva,size,h=code_line.split('\t');check(sha(at(0x400000+int(rva,16),int(size)))==h,'Ghidra executable section equality vs PE')
msn=a.msn.read_bytes();ter=a.ter.read_bytes();zoff=msn.index(b'ZMAP');zm=msn[zoff+9:zoff+6409];wrld=msn.index(b'WRLD')
def source(x,z):
 check(float(x).is_integer() and float(z).is_integer(),'integral lattice vertex');x,z=int(x),int(z)
 check(0<=x<10240 and 0<=z<10240,'inside source mission grid');page=zm[z//128*80+x//128];check(page!=255,'active authentic page')
 off=page*32768+2*(z%128*128+x%128);w=struct.unpack_from('<H',ter,off)[0]
 return {'page':page,'row':z%128,'column':x%128,'ter_offset':f'{off:08X}','word':f'{w:04X}','height_low12':w&4095,'material_class':w>>13,'bit12':bool(w&4096),'sample_position':[x*5,(w&4095)*struct.unpack('<f',bytes.fromhex('cdcccc3d'))[0],z*5]}
summary={};selected={};hardware=[];all_services=collections.Counter();read_classes=collections.Counter()
for case in ('primary','contrast','below','raw','poison'):
 base=a.private/(case+'.tsv');rs=rows(base);by=collections.defaultdict(list)
 for r in rs:by[r['kind']].append(r)
 check(not by['BLOCKER'] if case!='raw' else len(by['BLOCKER'])==1 and by['BLOCKER'][0]['pc']=='00492EAF' and 'fpatan' in by['BLOCKER'][0]['detail'].lower(),'no unexplained blocker '+case)
 check(len(by['OUTPUT'])==1,'one bounded result');out=by['OUTPUT'][0]['d'];nv,nl,ne=(int(out[x]) for x in ('vertices','leaves','edges'));arena=base.with_name(base.name+'.arena.bin').read_bytes();vb=base.with_name(base.name+'.vertices.bin').read_bytes();vs=list(struct.iter_unpack('<fff',vb));check(len(vs)==nv,'vertex ownership length');check(len(arena)==ne*12+nl*28,'arena allocation accounting');check(int(out['harnessOutputWrites'])==0,'harness output guard')
 grid=struct.unpack('<16384I',base.with_name(base.name+'.grid.bin').read_bytes())
 for j,p in enumerate(grid):
  x,z=j%128-24,j//128-24;page=zm[z*80+x] if 0<=x<80 and 0<=z<80 else 255;check(p==(0x59c588 if page==255 else 0x40000000+page*32768),'original full page grid')
 props=bytes.fromhex(''.join(struct.pack('<I',int(w,16)).hex() for w in by['WRLD_MATERIALS'][0]['d']['properties'].split(',')))
 check(props==msn[wrld+0x9f:wrld+0x9f+160],'WRLD physical properties; no visual material inference')
 sources=[];pages=collections.Counter();materials=collections.Counter()
 for x,hgt,z in vs:
  src=source(x,z);check(hgt==src['height_low12'],'original generated height equals TER low12');sources.append(src);pages[src['page']]+=1;materials[src['material_class']]+=1
 writes={}
 for r in by['ORIGINAL_VERTEX_WRITE']:
  check(r['pc'] in ('00490C2D','00490CB8','00490D45','00490DD0','0049199D'),'original FSTP writer PC');addr=int(r['d']['address'],16);j=(addr-0x42000000)//12;check(addr==0x42000000+j*12 and 0<=j<nv,'owned original vertex write');data=struct.pack('<3I',*(int(x,16) for x in r['d']['xyz'].split(',')));check(data==vb[j*12:j*12+12],'original vertex event vs final bytes');writes[j]=r['pc']
 check(len(writes)==nv,'every vertex has an original writer')
 for kind in ('VISUAL_HEIGHT_READ','MATERIAL_PREDICATE_READ'):
  for r in by[kind]:
   addr=int(r['d']['address'],16);check(0x40000000<=addr<0x40000000+len(ter),'authentic '+kind+' read');w=struct.unpack_from('<H',ter,addr-0x40000000)[0];check(w==int(r['d']['word'],16),'source word vs original read')
   if kind=='MATERIAL_PREDICATE_READ':read_classes[w>>13]+=1
 leaf_writes={int(r['d']['address'],16):r for r in by['ORIGINAL_LEAF_WRITE']};enters={int(r['d']['cursor'],16):r for r in by['LEAF_ENTER']};leaves=[]
 def data(addr,n):
  check(0x44000000<=addr and addr+n<=0x44000000+len(arena),'arena pointer ownership');return arena[addr-0x44000000:addr-0x44000000+n]
 def edge(addr,reverse=False,path=()):
  check(addr not in path,'acyclic shared-edge graph');v0,v1,c0,c1=struct.unpack('<hhII',data(addr,12));check(0<=v0<nv and 0<=v1<nv,'edge endpoints owned')
  if c0:check(c1!=0,'paired edge children');return edge(c1,True,path+(addr,))+edge(c0,True,path+(addr,)) if reverse else edge(c0,False,path+(addr,))+edge(c1,False,path+(addr,))
  check(c1==0,'leaf edge children');return [v1 if reverse else v0]
 ptr=int(out['head'],16);seen=set()
 while ptr:
  check(ptr not in seen,'acyclic original primitive list');seen.add(ptr);rec=struct.unpack('<7I',data(ptr,28));check(ptr in leaf_writes and ptr in enters,'each leaf original allocator and writer');w=leaf_writes[ptr];check(w['pc']=='00491892','original leaf final-store PC');wd=[int(x,16) for x in w['d']['data'].split(',')];check(list(rec[:2])+list(rec[3:])==wd[:2]+wd[3:],'leaf final bytes vs original store event');check(rec[3:]==tuple(int(x,16) for x in enters[ptr]['d']['edges'].split(',')),'allocator caller edge ownership')
  loop=edge(rec[5])+edge(rec[4])+edge(rec[6],True)+edge(rec[3],True);check(len(loop)>=4 and len(set(loop))==len(loop),'flattened leaf loop unique vertices')
  points=[vs[j] for j in loop];area=sum(points[j][0]*points[(j+1)%len(points)][2]-points[(j+1)%len(points)][0]*points[j][2] for j in range(len(points)));check(area!=0,'nonzero lattice polygon signed area')
  leaves.append({'address':f'{ptr:08X}','vertex_indices':loop,'grid_vertices':[list(vs[j]) for j in loop],'source':[sources[j] for j in loop],'signed_xz_area_twice':area,'original_vertex_writer_pcs':[writes[j] for j in loop]});ptr=rec[2]
 check(len(leaves)==nl==len(leaf_writes)==len(enters),'all primitive records original-authored')
 if case in ('primary','contrast','poison'):
  check(len(by['PRETRANSFORM_BOUNDARY'])==1 and by['PRETRANSFORM_BOUNDARY'][0]['d']['caller']=='00490EF2','original producer -> transform call');check(by['BOUNDS_RESULT'][0]['d']['eax']=='1','native bounds accepted');check(nl>0,'positive native primitive output')
 else:check(nv==nl==ne==0,'negative control empty')
 if case=='below':check(by['BOUNDS_RESULT'][0]['d']['eax']=='0' and len(by['SERVICE_EMPTY_FILL'])==1,'original rejected-region branch')
 if case=='raw':check(len(by['RAW_UNSUPPORTED_BOUNDARY'])==1 and by['RAW_UNSUPPORTED_BOUNDARY'][0]['pc']=='00492EAF','exact unsupported original instruction control')
 for r in by['SERVICE_FTOL']:
  value=ext(r['d']['st0']);check(math.isfinite(value) and math.trunc(value)==int(r['d']['result']),'independent finite ftol truncation')
 for r in by['HARDWARE_INSTRUCTION']:hardware.append(r)
 for r in rs:
  if r['kind'].startswith('SERVICE_'):all_services[(r['kind'],r['pc'])]+=1
 summary[case]={'vertices':nv,'leaves':nl,'edges':ne,'page_vertex_counts':dict(pages),'material_vertex_counts':dict(materials),'bounds_result':by['BOUNDS_RESULT'][0]['d'] if by['BOUNDS_RESULT'] else None,'trace_sha256':sha(base.read_bytes()),'vertex_sha256':sha(vb),'arena_sha256':sha(arena),'original_height_reads':len(by['VISUAL_HEIGHT_READ']),'material_predicate_reads':len(by['MATERIAL_PREDICATE_READ']),'harness_output_writes':int(out['harnessOutputWrites'])}
 if leaves:selected[case]=next((l for l in leaves if any(s['material_class']==3 for s in l['source'])),leaves[0])
# Byte-identical fresh project repeat and poison-output overwrite control.
for suffix in ('','.grid.bin','.vertices.bin','.arena.bin'):
 check((a.private/('primary.tsv'+suffix)).read_bytes()==(a.repeat/('primary.tsv'+suffix)).read_bytes(),'fresh-project byte-identical '+suffix)
for key in ('vertex_sha256','arena_sha256'):check(summary['primary'][key]==summary['poison'][key],'poison storage overwritten by originals')
check(summary['primary']['vertex_sha256']!=summary['contrast']['vertex_sha256'],'view contrast changes native output');check(summary['primary']['leaves']!=summary['contrast']['leaves'],'view contrast changes leaf count')
# Independent numerical oracle: replay exact ext80 requests, compare finite atan result
# against Python atan2, FISTP against declared RC. Host service itself is separately rerun.
requests=[]
for r in hardware:
 d=r['d'];op=int(d['op']);requests.append(bytes([op])+int(d['st0'],16).to_bytes(10,'little')+int(d['st1'],16).to_bytes(10,'little')+int(d['cw'],16).to_bytes(2,'little'))
proc=subprocess.run([str(a.service.resolve())],input=b''.join(requests),stdout=subprocess.PIPE,check=True);offset=0;max_atan_error=0
for r in hardware:
 d=r['d'];op=int(d['op']);n=10 if op else 8;v=int.from_bytes(proc.stdout[offset:offset+n],'little');offset+=n;check(v==int(d['result'],16),'independent host instruction repeat')
 if op:
  err=abs(ext(d['result'])-math.atan2(ext(d['st1']),ext(d['st0'])));max_atan_error=max(max_atan_error,err);check(err<=5e-16,'FPATAN independent double oracle')
 else:
  cw=int(d['cw'],16);rc=(cw>>10)&3;value=ext(d['st0']);expected=round(value) if rc==0 else math.floor(value) if rc==1 else math.ceil(value) if rc==2 else math.trunc(value);signed=v if v<1<<63 else v-(1<<64);check(signed==expected,'FISTP independent RC oracle')
check(offset==len(proc.stdout),'no unexpected hardware response')
result={'scenarios':summary,'selected_primitives':selected,'material_predicate_class_counts':dict(read_classes),'hardware_requests':len(hardware),'max_fpatan_double_oracle_error':max_atan_error,'fresh_repeat':'byte-identical trace, grid, vertex and arena bytes','code_equality':{'rva':rva,'bytes':int(size),'sha256':h},'services':[{'kind':k,'pc':pc,'count':n} for (k,pc),n in sorted(all_services.items())],'scope':'Original pre-transform adaptive leaves. No flattened/rendered polygon, texture/UV, framebuffer or M-RND-03 claim.'}
validation={'status':'passed','test_count':N,'passed_count':N,'notes':'Private identities, retail opcode/section equality, all source heights and native writers, original leaf ownership and independent edge flattening, full page grids, material-predicate reads, independent numerical instruction checks, reject/contrast/poison/raw controls and fresh-project repeat. Counts measure checks only.'}
if a.emit:
 a.emit.mkdir(parents=True,exist_ok=True);dump(a.emit/'results.json',result);dump(a.emit/'verification.json',validation)
else:
 assert json.loads((a.run/'evidence/results.json').read_text())==json.loads(json.dumps(result)), 'published bounded result regenerates exactly'
print(json.dumps(validation,indent=2))
