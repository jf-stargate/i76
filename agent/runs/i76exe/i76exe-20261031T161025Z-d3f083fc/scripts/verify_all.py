#!/usr/bin/env python3
"""Standalone reproduction coordinator. Executes Python verifiers only, never producer/Ghidra."""
import argparse,csv,hashlib,json,pathlib,struct,subprocess,sys,tempfile
p=argparse.ArgumentParser();p.add_argument('--work',type=pathlib.Path,required=True);p.add_argument('--emit',type=pathlib.Path,required=True)
for k in ['exe','gzf','zfs','msn','ter']:p.add_argument('--'+k,type=pathlib.Path,required=True)
a=p.parse_args();run=pathlib.Path(__file__).resolve().parent.parent;checks=0

def ck(v,msg):
 global checks
 checks+=1
 if not v:raise AssertionError(msg)
def invoke(cmd):
 r=subprocess.run([sys.executable,*map(str,cmd)],capture_output=True,text=True);ck(r.returncode==0,r.stderr);return json.loads(r.stdout)
args=[]
for k in ['exe','gzf','zfs','msn','ter']:args+=['--'+k,str(getattr(a,k))]
terrain=invoke([run/'scripts/verify_terrain.py','--private',a.work,'--fixtures',a.work/'vehicle-baseline/fixtures',*args])
results={};traces={};anchors={}
for mode in ['visible','camera_only','behind','contrast','below']:
 f=a.work/('control-'+mode+'.tsv');rows=list(csv.DictReader(f.open(),delimiter='\t'))
 result=invoke([run/'scripts/verify_unified.py',f,'--fixtures',a.work/'vehicle-baseline/fixtures']);results[mode]=result
 ck(result['vehicle_records']==(0 if mode in ['camera_only','behind'] else 1),'vehicle control outcome')
 ck(result['terrain_records']==(0 if mode=='below' else 13 if mode=='contrast' else 30),'terrain control outcome')
 ck(not any(r['kind']=='BLOCKER' for r in rows),'no probe blocker');scratch=[r for r in rows if r['kind']=='ORIGINAL_SCRATCH_COMPLETE'];ck(len(scratch)==1 and scratch[0]['detail']=='positions=42000000;aux=4200D2F0;records=44000000','original scratch alias and ownership')
 traces[mode]={'sha256':hashlib.sha256(f.read_bytes()).hexdigest(),'bytes':f.stat().st_size}
 ck(sum(r['kind']=='RETURN' and r['pc']=='0048F9B0' for r in rows)==1,'one original arena initialization')
 order=[r['pc'] for r in rows if r['kind']=='RETURN' and r['pc'] in ['00490A00','00457FF0','0048FAC0']];ck(order==['00490A00','00457FF0','0048FAC0'],'original producer-consumer chronology')
 for r in rows:
  if r['kind'] in ['QUEUE_DWORD','ORIGINAL_WRITE_RETIRED','CONSUME_RECORD','SUBMISSION_OWNER','GEO_SOURCE','POLYGON_WRAPPER']:anchors[r['pc']]=None
# Fresh import exact equality, including untouched scratch and complete arena/bucket snapshots.
repeat={}
f=a.work/'control-visible.tsv'
for src in sorted(a.work.glob(f.name+'*')):
 suffix=src.name[len(f.name):];dst=a.work/('fresh-visible.tsv'+suffix);ck(src.read_bytes()==dst.read_bytes(),'fresh-project equality '+suffix);repeat[suffix or 'trace']=hashlib.sha256(src.read_bytes()).hexdigest()
# Independent retail opcode checks. Audit text supplies claimed instruction lengths/bytes only.
aud={}
for line in (a.work/'ownership-audit.txt').read_text().splitlines():
 c=line.split('\t')
 if len(c)==3 and len(c[0])==8:
  try:aud[c[0].upper()]=bytes.fromhex(c[1])
  except ValueError:pass
pe=a.exe.read_bytes();h=struct.unpack_from('<I',pe,60)[0];sec=h+24+struct.unpack_from('<H',pe,h+20)[0];sections=[struct.unpack_from('<III',pe,sec+j*40+12) for j in range(struct.unpack_from('<H',pe,h+6)[0])]
def raw(va,n):
 for rv,size,off in sections:
  if rv<=va-0x400000 and va-0x400000+n<=rv+size:return pe[off+va-0x400000-rv:off+va-0x400000-rv+n]
 raise AssertionError('PE mapping')
# Accepted sparse anchors cover camera callback regions with incomplete Ghidra function boundaries.
repo=run.parents[3]
for name in ['i76exe-20261030T025421Z-351de3fe']:
 for item in json.loads((repo/'agent/runs/i76exe'/name/'evidence/provenance.json').read_text())['anchors']:aud.setdefault(item['va'].upper(),bytes.fromhex(item['hex']))
for pc in anchors:
 ck(pc in aud,'source audit PC '+pc);ck(raw(int(pc,16),len(aud[pc]))==aud[pc],'retail opcode '+pc);anchors[pc]=aud[pc].hex()
ck(struct.unpack('<I',raw(0x4facc0,4))[0]==0x48f4c0,'retail kind6 dispatch');ck(struct.unpack('<I',raw(0x4facd0,4))[0]==0x490640,'retail kind10 dispatch')
# Deliberate semantic ownership corruption must fail independently, not just fail a digest.
with tempfile.TemporaryDirectory() as t:
 target=pathlib.Path(t)/'corrupt.tsv'
 for src in a.work.glob('control-visible.tsv*'):
  if src==f:continue
  pathlib.Path(str(target)+src.name[len(f.name):]).symlink_to(src.resolve())
 s=f.read_text();start=s.index('\tCONSUME_RECORD\t0048F4C0');i=s.index('26100000',start);target.write_text(s[:i]+'26100100'+s[i+8:])
 proc=subprocess.run([sys.executable,str(run/'scripts/verify_unified.py'),str(target)],capture_output=True,text=True);ck(proc.returncode!=0 and 'consumer typed owner' in proc.stderr,'corruption rejected at original consumer ownership')
validation={'status':'passed','test_count':checks+terrain['test_count']+sum(v['checks'] for v in results.values()),'passed_count':checks+terrain['test_count']+sum(v['checks'] for v in results.values()),'notes':'Standalone source/camera/terrain clip, typed arena/store chronology, GEO transforms, exact consumer order, five controls, exact fresh-GZF repeat and consumed-owner corruption. Bounded original-instruction state with declared services; no pixels.'}
a.emit.mkdir(parents=True,exist_ok=True)
for name,value in [('validation.json',validation),('results.json',dict(cases=results,traces=traces,fresh_repeat=repeat,terrain_validation=terrain,corruption='consumed-owner rejected')),('opcodes.json',anchors)]: (a.emit/name).write_text(json.dumps(value,indent=2,sort_keys=True)+'\n')
print(json.dumps(validation,indent=2))
