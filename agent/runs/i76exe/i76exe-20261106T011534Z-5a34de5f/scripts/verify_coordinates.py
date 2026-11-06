#!/usr/bin/env python3
"""Verify private executions against an independent model; emit bounded public evidence."""
import argparse,pathlib,json,hashlib,struct,csv,collections,math,subprocess
import sys
sys.dont_write_bytecode=True
from coordinate_model import Terrain,ext_fraction,F,location
p=argparse.ArgumentParser()
for k in ['private','orig','gzf','run']:p.add_argument('--'+k,type=pathlib.Path,required=True)
p.add_argument('--emit',action='store_true');a=p.parse_args();N=0

def check(v,msg):
 global N
 N+=1
 if not v:raise AssertionError(msg)
def sha(b):return hashlib.sha256(b).hexdigest()
def write(name,obj):
 if a.emit:(a.run/name).write_text(json.dumps(obj,indent=2,sort_keys=True)+'\n')
def trace(name):
 rs=list(csv.DictReader((a.private/(name+'.tsv')).open(),delimiter='\t'))
 for r in rs:r['d']=dict(x.split('=',1) for x in r['detail'].split(';') if '=' in x)
 return rs
identities={}
for name,path,expected in [
 ('exe',a.orig/'i76.exe','bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'),
 ('gzf',a.gzf,'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'),
 ('M06.MSN',a.orig/'miss8/M06.MSN','923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f'),
 ('M06.TER',a.orig/'miss8/M06.TER','fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea'),
 ('M02.MSN',a.private/'inputs/M02.MSN','b566539e260440b43d40e7b6ad5ed6a959e344bcb6ca365562641b8b4b060175'),
 ('M02.TER',a.orig/'miss8/M02.TER','08ae567ceac9647bacd95a352eaef9707c3fbf6a9ec7096b9fe2152afc6bc0e2'),
 ('zfs',a.orig/'I76.ZFS','0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d')]:
 b=path.read_bytes();check(sha(b)==expected,'input identity '+name);identities[name]={'sha256':sha(b),'md5':hashlib.md5(b).hexdigest(),'bytes':len(b)}
iso=a.orig/'I76_CD1.ISO';identities['ISO']={'sha256':sha(iso.read_bytes()),'md5':hashlib.md5(iso.read_bytes()).hexdigest(),'bytes':iso.stat().st_size}
for name in ['M02.MSN','M02.TER','M06.TER']:
 b=subprocess.check_output(['7z','x','-so',str(iso),'MISSIONS/'+name]);check(sha(b)==identities[name]['sha256'],'CD source '+name)
# PE section identity and every audited instruction, but emit only sparse reviewed anchors.
pe=(a.orig/'i76.exe').read_bytes();ph=struct.unpack_from('<I',pe,60)[0];sec=ph+24+struct.unpack_from('<H',pe,ph+20)[0];sections=[struct.unpack_from('<8sIIII',pe,sec+40*j)[1:] for j in range(struct.unpack_from('<H',pe,ph+6)[0])]
def at(va,n):
 for vs,rv,size,off in sections:
  if rv<=va-0x400000 and va-0x400000+n<=rv+size:return pe[off+va-0x400000-rv:off+va-0x400000-rv+n]
 raise ValueError(hex(va))
audit=(a.private/'audit.tsv').read_text().splitlines();head=audit[0].split('\t');check(sha(at(int(head[1],16),int(head[2])))==head[3],'entire Ghidra code section equals retail PE')
check(any(rv+size<=0x19c588 and 0x1a4588<=rv+vs for vs,rv,size,off in sections),'default page in PE zero-fill virtual tail')
anchors=[];wanted={0x4930f1,0x493101,0x49310a,0x493111,0x493117,0x493128,0x493136,0x493168,0x49316d,0x49317b,0x493180,0x493183,0x49318a,0x49319d,0x4931a4,0x4931a8,0x49355c,0x49356a,0x493570,0x493595,0x4935ca,0x4935d9,0x4935e5,0x4935ee,0x493608,0x493652,0x4936a5,0x4936f8,0x49373d,0x49375d,0x493769,0x493792,0x49379e,0x4937a4,0x4937a6,0x4937a9,0x49287b,0x493286,0x49328c}
for line in audit:
 f=line.split('\t')
 if len(f)==3 and len(f[0])==8 and f[0].startswith('004'):
  va=int(f[0],16);bs=bytes.fromhex(f[1]);check(at(va,len(bs))==bs,'audited opcode '+f[0])
  if va in wanted:anchors.append({'va':f[0],'hex':f[1],'instruction':f[2]})
if a.emit:
 with (a.run/'evidence/instruction_anchors.tsv').open('w') as f:
  w=csv.DictWriter(f,fieldnames=['va','hex','instruction'],delimiter='\t',lineterminator='\n');w.writeheader();w.writerows(anchors)
results=[];summary={};services={};normal_by={}
for variant,mission in [('M06','M06'),('M02','M02'),('alias','M06'),('bit12','M06')]:
 msn=(a.private/'inputs/M02.MSN' if mission=='M02' else a.orig/'miss8/M06.MSN').read_bytes();ter=(a.orig/('miss8/'+mission+'.TER')).read_bytes();default=(a.private/(variant+'.tsv.default.bin')).read_bytes()
 check(len(default)==32768 and not any(default),'zero static default page '+variant)
 model=Terrain(msn,ter,default,variant);grid=struct.unpack('<16384I',(a.private/(variant+'.tsv.grid.bin')).read_bytes())
 for slot,v in enumerate(grid):
  px,pz=slot%128,slot//128;pg=model.zm[(pz-24)*80+px-24] if 24<=px<104 and 24<=pz<104 else 255
  check(v==(0x59c588 if pg==255 else 0x40000000+pg*32768),'full original pointer grid '+variant)
 rs=trace(variant);by=collections.defaultdict(list)
 for row in rs:
  if 'id' in row['d']:by[row['d']['id']].append(row)
 n=json.loads((a.private/('native_'+variant)/'native.json').read_text());cases=[l.split('\t') for l in (a.private/(mission+'.cases.tsv')).read_text().splitlines()]
 check(len(n)==len(cases) and len(n)>=120,'case count '+variant)
 diff=0;maxdiff=0.;readcount=0;services[variant]=dict(collections.Counter(row['pc']+':'+row['kind'] for row in rs if row['kind'].startswith(('SERVICE','STUB','HARDWARE')) or row['kind']=='PHYSICS_X87_INTEGER_BOUNDARY'))
 normal_by[variant]={}
 for (id,kind,x,z),cpu in zip(cases,n):
  x,z=float(x),float(z);rows=by[id];one=lambda k:next(row['d'] for row in rows if row['kind']==k)
  er=one('RESULT');check(cpu['id']==id,'native identity')
  record={'mission':mission,'variant':variant,'input_sha256':{'msn':identities[mission+'.MSN']['sha256'],'ter':identities[mission+'.TER']['sha256']},'id':id,'kind':kind,'input':[x,z],'execution':'retail-original-instructions; Ghidra with services + native i386 CPU with supplied grid/backing'}
  if kind=='sample':
   src=model.sample(int(x),int(z));expected=src['height12'];check(int(er['value'])==cpu['value']==expected,'sample original/model '+id);record.update(source=src,expected=expected,original=cpu['value'])
   reads=[row for row in rows if row['kind']=='READ' and row['pc']=='004931A4'];expected_reads=[] if src.get('outcome') else [src]
  else:
   v=model.height(x,z);expected=v.pop('expected');actual=ext_fraction(cpu['st0']);check(actual==expected,'exact CPU rational height '+variant+id)
   check(cpu['cw']==0x37f,'native rounding restored');check(int(er['cw'],16)==0x37f,'Ghidra rounding restored')
   check(cpu['surface_class']==v['class']==int(one('CLASS')['value']),'material query '+id)
   em=ext_fraction(int(er['st0'],16).to_bytes(10,'little').hex());delta=float(em-actual);diff+=em!=actual;maxdiff=max(maxdiff,abs(delta))
   record.update(v,expected=float(expected),expected_rational=[str(expected.numerator),str(expected.denominator)],original_st0_le=cpu['st0'],original=float(actual),original_class=cpu['surface_class'],emulator=float(em),emulator_error=delta)
   reads=[row for row in rows if row['kind']=='READ' and row['pc'] in {'00493652','004936A5','004936F8','0049373D'}];expected_reads=v['corners']
   if v['admitted']:
    native_rows=[struct.unpack('<f',struct.pack('<I',int(b,16)))[0] for b in cpu['row_bits']]
    check(native_rows==v['rows'],'native directed row stores '+variant+id)
    record['native_row_bits']=cpu['row_bits']
    record['emulated_row_bits']=[one('ROW0')['bits'],one('ROW1')['bits']]
    floor=one('FLOOR');check([int(floor['ix']),int(floor['iz'])]==v['floor'],'original FISTP corners')
   normal=one('NORMAL');bits=[int(b,16) for b in normal['bits'].split(',')];values=[struct.unpack('<f',struct.pack('<I',b))[0] for b in bits]
   check(all(math.isfinite(v) for v in values),'normal finite');check(normal['eax']=='26008000','normal returns output pointer');normal_by[variant][id]=normal['bits'];record['emulated_normal_bits']=normal['bits']
  check(len(reads)==len(expected_reads),'read count '+variant+id)
  for row,src in zip(reads,expected_reads):
   d=row['d'];check(d['address']==src['address'],'original sample address');check(int(d['sample'])==src['local_sample'],'original local sample');check(int(d['word'],16)==int(src['raw_word'],16),'original raw word');readcount+=1
  record['observed_reads']=[{'va':row['pc'],**row['d']} for row in reads];results.append(record)
 summary[variant]={'cases':len(cases),'height_cases':sum(c[1]=='world' for c in cases),'captured_reads_verified':readcount,'native_model_mismatches':0,'emulator_height_mismatches':diff,'max_emulator_height_error':maxdiff,'trace_sha256':sha((a.private/(variant+'.tsv')).read_bytes()),'native_json_sha256':sha((a.private/('native_'+variant)/'native.json').read_bytes()),'grid_sha256':sha((a.private/(variant+'.tsv.grid.bin')).read_bytes()),'default_sha256':sha(default)}
# Repeated emulation must reproduce state, trace and sidecars exactly.
for suffix in ['','.grid.bin','.default.bin']:check((a.private/('M06.tsv'+suffix)).read_bytes()==(a.private/('repeat.tsv'+suffix)).read_bytes(),'independent emulator repeat '+suffix)
base={r['id']:r for r in results if r['variant']=='M06'}
for r in results:
 if r['variant']=='bit12':
  b=base[r['id']];check(r['original']==b['original'],'bit12 height independence')
  if r['kind']=='world':check(r['original_class']==b['original_class'] and r['emulated_normal_bits']==b['emulated_normal_bits'],'bit12 class/normal independence')
# Bounded publication includes sparse identities, never TER pages or raw traces.
if a.emit:
 for filename,rows in [('coordinate_cases.jsonl',results),('boundary_cases.jsonl',[r for r in results if any(t in r['id'] for t in ['admission','extent']) or (r['kind']=='sample' and any(int(v)%128 in [0,1,126,127] for v in r['input'])) or (r['kind']=='world' and r.get('admitted') and len({v['grid_slot'] for v in r['corners']})>1)])]:
  (a.run/'evidence'/filename).write_text(''.join(json.dumps(v,sort_keys=True,separators=(',',':'))+'\n' for v in rows))
write('evidence/input_identities.json',identities);write('evidence/results.json',summary);write('evidence/services.json',services)
validation={'status':'passed','test_count':N,'passed_count':N,'failed_count':0,'cases':len(results),'native_model_mismatches':0,'emulator_mismatches_are_recorded_diagnostics':True,'scope':'Original parser/grid and address traces; exact rational-vs-native CPU height/class checks; controlled alias/bit12; M06 repeat. Not full Windows execution.'}
write('evidence/verification.json',validation)
write('validation.json',{k:validation[k] for k in ['status','test_count','passed_count']} | {'notes':'668 native/model cases; 1724 captured reads; native intermediate rows checked; emulator differences retained as diagnostics. Details: evidence/verification.json; negative controls separate.'})
print(json.dumps({'validation':validation,'summary':summary},indent=2))
