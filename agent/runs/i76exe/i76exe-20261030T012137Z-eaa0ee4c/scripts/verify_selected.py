#!/usr/bin/env python3
"""Independent PE/import, event, lifecycle-negative and native x87 validation.
Private payloads/traces are read only. --emit regenerates only reviewed derived evidence.
"""
import argparse,hashlib,json,math,struct
from pathlib import Path
p=argparse.ArgumentParser()
for name in ['run','private','exe','gzf','zfs','msn','ter','strlkup']:p.add_argument('--'+name,type=Path,required=True)
p.add_argument('--emit',action='store_true');a=p.parse_args();count=0

def check(ok,label):
 global count
 count+=1
 if not ok:raise AssertionError(label)
def sha(b):return hashlib.sha256(b).hexdigest()
class PE:
 def __init__(self,path):
  self.b=path.read_bytes();self.pe=self.u32(0x3c);self.opt=self.pe+24;self.base=self.u32(self.opt+28);self.sections=[]
  for i in range(self.u16(self.pe+6)):
   q=self.opt+self.u16(self.pe+20)+40*i;self.sections.append((self.u32(q+12),self.u32(q+8),self.u32(q+20)))
 def u16(self,o):return struct.unpack_from('<H',self.b,o)[0]
 def u32(self,o):return struct.unpack_from('<I',self.b,o)[0]
 def off(self,va):
  for r,n,f in self.sections:
   if r<=va-self.base<r+n:return f+va-self.base-r
  raise ValueError(hex(va))
 def data(self,va,n):return self.b[self.off(va):self.off(va)+n]
 def word(self,va):return self.u32(self.off(va))
 def string(self,va):
  q=self.off(va);return self.b[q:self.b.index(0,q)].decode('ascii')
 def imports(self):
  out={};r=self.u32(self.opt+104)
  while True:
   q=self.off(self.base+r);orig,_,_,name,first=struct.unpack_from('<5I',self.b,q)
   if not name:return out
   dll=self.string(self.base+name);i=0
   while (v:=self.word(self.base+(orig or first)+4*i)):
    out[self.base+first+4*i]=(dll,'ordinal '+str(v&65535) if v&0x80000000 else self.string(self.base+v+2));i+=1
   r+=20
 def exports(self):
  q=self.off(self.base+self.u32(self.opt+96));n=self.u32(q+24);fs=self.u32(q+28);ns=self.u32(q+32);ords=self.u32(q+36);out={}
  for i in range(n):
   name=self.string(self.base+self.word(self.base+ns+4*i));ordinal=self.u16(self.off(self.base+ords)+2*i);out[name]=self.base+self.word(self.base+fs+4*ordinal)
  return out
pe=PE(a.exe);dll=PE(a.strlkup)
expected={'exe':'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','gzf':'b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','zfs':'0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d','msn':'923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f','ter':'fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea'}
identities={}
for key in [*expected,'strlkup']:
 b=getattr(a,key).read_bytes();identities[key]={'sha256':sha(b),'md5':hashlib.md5(b).hexdigest(),'bytes':len(b)}
 if key in expected:check(sha(b)==expected[key],'accepted '+key)
anchors={0x402b3c:'689c264c00',0x402b49:'e8de6b0000',0x402b4e:'8b0da8c24b00',0x402b57:'8901',0x40972c:'ff25b0c24b00',0x461b94:'8b7d08',0x461bff:'ffd0',0x461c01:'83c404',0x4f7784:'20314600',0x4f778c:'50394600',0x4f7a5c:'b0f24600',0x4f7a64:'20f44600',0x4f79f4:'10f84500',0x4f79fc:'f0fa4500',0x49d409:'d9fb',0x49d40b:'d95dfc',0x49d40e:'d95df8',0x463963:'e83866ffff',0x46396c:'e82f22feff',0x46ea2f:'a1a8c24b00',0x46ea39:'8b08',0x409726:'ff25b4c24b00'}
for va,value in anchors.items():check(pe.data(va,len(bytes.fromhex(value))).hex()==value,'PE opcode '+hex(va))
imp=pe.imports();exp=dll.exports()
check(imp[0x4bc2a8]==('Strlkup.dll','StrLookup_Global_Object'),'actual imported data symbol')
check(imp[0x4bc2b4]==('Strlkup.dll','StrLookupFind'),'actual imported function')
check(imp[0x4bc2b0]==('Strlkup.dll','StrLookupCreate'),'actual constructor import')
check(exp['StrLookup_Global_Object']==0x1000c030 and dll.word(exp['StrLookup_Global_Object'])==0,'DLL initial exported cell zero')
check(exp['StrLookupCreate']==0x10001000 and exp['StrLookupFind']==0x10001aa0,'DLL original exports')
check(pe.string(0x4f8a30)=='.45 Handgun','exact lookup key')
check(pe.string(0x4c269c)=='lang.txt','original startup localization source')
def rows(name):
 out=[]
 for i,line in enumerate((a.private/(name+'.tsv')).read_text().splitlines()[1:],2):
  scenario,kind,pc,detail=line.split('\t',3);fields={}
  for x in detail.split(';'):
   if '=' in x:
    k,v=x.split('=',1);fields[k]=v
    if k=='fields' and v.startswith('animation='):fields['animation']=v.split('=',1)[1]
  out.append(dict(line=i,kind=kind,pc=pc,detail=detail,fields=fields))
 return out
def select(rs,kind):return [r for r in rs if r['kind']==kind]
summaries={};safe=[]
cases=['pending_bus','pending_repeat','pending_unselected','peripheral','noinit','postcontrol','x87','rawx87']
safe_kinds={'PENDING_BEFORE','PENDING_AFTER','PENDING_VISIT','INIT_DISPATCH','INIT_RETURN','INITIALIZER_ENTER','BOUNDED_STOP','LOCALIZATION_PREREQUISITE','PERIPHERAL_BEFORE','PERIPHERAL_INITIALIZED','PERIPHERAL_POST_RETURN','CLASS1_INIT_RETURN','CLASS1_POST_RETURN','HARDWARE_FSINCOS','HARDWARE_FSTP32','X87_RESULT','POST_GATE','OPTIONAL_BIND_FAILED'}
for case in cases:
 rs=rows(case);log=(a.private/(case+'.log')).read_text();warnings=[l.strip() for l in log.splitlines() if 'Uninitialized memory read' in l]
 check(not select(rs,'SERVICE_PERIPHERAL_POST'),'no peripheral body substitutes '+case)
 check(not select(rs,'CONTROLLED_DRIVE_INPUT'),'no manufactured controls '+case)
 for r in rs:
  if r['kind'] in safe_kinds:safe.append(dict(case=case,**r))
 if case.startswith('pending'):
  dispatch=select(rs,'INIT_DISPATCH');returns=select(rs,'INIT_RETURN')
  check([r['fields']['target'] for r in dispatch]==['0046D820']*4+['0046F2B0','0045F810','0046DFE0'],'original pending order '+case)
  check(len(returns)==6,'six completed initializers '+case)
  check(not [r for r in select(rs,'INITIALIZER_ENTER') if r['pc']=='00463120'],'class1 not reached '+case)
  for d in dispatch:
   f=d['fields'];check(pe.word(int(f['slot'],16))==int(f['target'],16),'original init slot')
   prior=[r for r in select(rs,'PENDING_VISIT') if r['line']<d['line']][-1]
   inserts=select(rs,'ORIGINAL_LIST_RETURN');pn=prior['fields'];pending=[r for r in inserts if r['fields']['node']==pn['pendingNode']][0];cn=[r for r in inserts if r['fields']['node']==pn['classNode']][0]
   check(pending['fields']['owner']==pn['classNode'] and cn['fields']['owner']==f['owner'],'pending -> class node -> owner')
  stop=select(rs,'LOCALIZATION_PREREQUISITE');check(len(stop)==1 and stop[0]['fields']['unresolvedTarget']=='000C09F8' and stop[0]['fields']['functionTarget']=='000C09E8','dynamic missing imports')
  check(select(rs,'BOUNDED_STOP')[0]['pc']=='000C09E8','exact expected stop')
  check(any('0046ea39' in l and '000c09f8:4' in l for l in warnings),'missing imported data read')
 elif case in ('peripheral','noinit'):
  before=select(rs,'PERIPHERAL_BEFORE');after=select(rs,'PERIPHERAL_INITIALIZED');post=select(rs,'PERIPHERAL_POST_RETURN')
  check(len(before)==len(after)==len(post)==2,'both peripheral controls')
  if case=='peripheral':
   check(after[0]['fields']['animation']!='00000000','class31 original animation allocated')
   check(after[0]['fields']['animationWords']=='00000024,00000009,00000009,00000009','class31 original initialized values')
   check(after[1]['fields']['root']=='26000000' and after[1]['fields']['self']==after[1]['fields']['owner'],'class34 root/self linkage')
   check(len(warnings)==1 and '004461e0' in warnings[0],'positive peripherals no additional invalid reads')
  else:
   check(any('0046f43d' in l and '0000000c:4' in l for l in warnings),'class31 missing-state negative')
   check(any('0045f978' in l and '00000070:4' in l for l in warnings),'class34 missing-owner negative')
 elif case=='postcontrol':
  check(len(select(rs,'CLASS1_INIT_RETURN'))==len(select(rs,'CLASS1_POST_RETURN'))==1,'complete original direct init/post control')
  check(select(rs,'CLASS1_INIT_RETURN')[0]['fields']['flags']=='00080040','native init flag transition')
  check(select(rs,'CLASS1_INIT_RETURN')[0]['fields']['counts']=='00000006,00000005,00000004,00000005,00000004,00000005,00000004','native command-list counts')
  check(select(rs,'POST_GATE')[0]['fields']['eax']=='1','selected post gate true')
  check(len(select(rs,'HARDWARE_FSINCOS'))>0,'post reaches original FSINCOS')
  check(len(warnings)==1 and '004461e0' in warnings[0],'post control no new invalid reads')
 elif case=='x87':
  ev=select(rs,'X87_RESULT');oracle=[l.split() for l in (a.private/'x87_oracle.tsv').read_text().splitlines()]
  check(len(ev)==len(oracle)==28,'seven operands x four rounding modes')
  for r,(raw,cw,s,c) in zip(ev,oracle):
   f=r['fields'];check((f['input'],int(f['cw'],16),f['sin'],f['cos'])==(raw,int(cw,16),s,c),'hardware helper versus independent native full helper')
  check(len(select(rs,'HARDWARE_FSTP32'))==56,'both original store boundaries serviced')
 elif case=='rawx87':check('Unimplemented CALLOTHER pcodeop (fcos), PC=0049d409' in log and not select(rs,'X87_RESULT'),'raw FSINCOS negative')
 summaries[case]={'trace_sha256':sha((a.private/(case+'.tsv')).read_bytes()),'memory_warnings':warnings,'init_dispatches':len(select(rs,'INIT_DISPATCH')),'init_returns':len(select(rs,'INIT_RETURN'))}
check((a.private/'pending_bus.tsv').read_bytes()==(a.private/'pending_repeat.tsv').read_bytes(),'independent pending byte repeat')
outputs={'results.json':json.dumps(dict(identities=identities,cases=summaries,imports={f'{k:08X}':v for k,v in imp.items() if k in (0x4bc2a8,0x4bc2b0,0x4bc2b4)},dll_exports={k:f'{v:08X}' for k,v in exp.items()},anchors={f'{k:08X}':v for k,v in anchors.items()}),indent=2)+'\n','selected_events.json':json.dumps(safe,indent=2)+'\n','x87_oracle.tsv':(a.private/'x87_oracle.tsv').read_text()}
for name,value in outputs.items():
 target=a.run/'evidence'/name
 if a.emit:target.write_text(value)
 else:check(target.read_text()==value,'published derived '+name)
print(json.dumps(dict(status='passed',test_count=count,passed_count=count,notes='Bounded prerequisites and controls; CAP-CONTROL-01 remains open.')))
