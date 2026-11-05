"""Validate private Ghidra exports against authenticated PE, emit curated evidence.
No decompilation or full instruction bodies are emitted publicly.
"""
import argparse,hashlib,json,struct
from pathlib import Path
EXE='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'
def sha(b):return hashlib.sha256(b).hexdigest()
def pe_reader(blob):
 assert sha(blob)==EXE
 p=struct.unpack_from('<I',blob,60)[0];assert blob[p:p+4]==b'PE\0\0'
 base=struct.unpack_from('<I',blob,p+52)[0];n=struct.unpack_from('<H',blob,p+6)[0];s=p+24+struct.unpack_from('<H',blob,p+20)[0]
 sections=[struct.unpack_from('<8sIIII',blob,s+40*i) for i in range(n)]
 def read(va,length):
  for _,vsize,rva,size,off in sections:
   at=va-base-rva
   if 0<=at and at+length<=size:return blob[off+at:off+at+length]
  raise ValueError('VA outside raw sections')
 return read
# Hand-reviewed bounded selections, not all exported bodies.
WINDOWS=[('00402da4','00402da9'),('004032ee','004032f8'),('004035eb','00403604'),('00402ea6','00402eba'),('00476068','00476168'),('004761b0','00476222'),
 ('0042d0c0','0042d116'),('00431500','00431556'),('00433e0d','00433e65'),
 ('004b8a33','004b8b20'),('0048dc82','0048dcd1'),('0048dcdd','0048dcf1'),('0048dd4c','0048dd67'),
 ('00475a72','00475ac4'),('00475af1','00475b32'),('0042dbf3','0042dc62'),('004345c3','00434632'),
 ('004791f7','00479255'),('004792a9','0047931d'),('00479394','00479428'),('0047949f','0047953c'),
 ('004796a3','004796cf'),('004796e7','00479739'),('004797f0','0047985d'),('0047990c','0047996e'),
 ('00478b30','00478b7f'),('00478b80','00478c0f'),('00479780','004797ef'),
 ('0047a4b0','0047a4c7'),('0047af20','0047af40'),('00482b14','00482b29'),
 ('00483ce4','00483d04'),('004843d9','004843f4'),('00484654','00484674'),('00484e3e','00484e59'),
 ('0047cc31','0047cc66'),('0047d020','0047d072'),('004852ae','004852cb'),('00485404','00485416'),
 ('0042d958','0042da02'),('004344a7','00434564'),('00476e01','00476e23'),('0047ab8e','0047aba8'),('0047ac40','0047ac53')]
def review(exe,private,output):
 raw=exe.read_bytes();read=pe_reader(raw);allins={};bodies=[];mods=[]
 for path in sorted(p for p in private.glob('pass*.json') if '.refs.' not in p.name):
  obj=json.loads(path.read_text());assert obj['modification_before']==obj['modification_after']
  mods.append({'pass':path.name,'before':obj['modification_before'],'after':obj['modification_after']})
  for f in obj['functions']:
   ins=f.get('instructions',[])
   if not ins:continue
   total=0
   for i in ins:
    va=int(i['va'],16);b=bytes.fromhex(i['bytes']);assert read(va,len(b))==b,hex(va)
    if i['va'] in allins:assert allins[i['va']]['bytes']==i['bytes']
    allins[i['va']]={'va':i['va'],'bytes':i['bytes'],'asm':i['asm']};total+=len(b)
   for r in f.get('ranges',[]):assert sha(read(int(r['start'],16),r['length']))==r['sha256']
   bodies.append({'pass':path.name,'entry_or_window':f['entry'],'instructions':len(ins),'instruction_bytes':total,'ranges':f.get('ranges',[]),'retail_match':True})
 selected=[v for k,v in sorted(allins.items()) if any(a<=k<=b for a,b in WINDOWS)]
 output.mkdir(parents=True,exist_ok=True)
 for name,v in [('reviewed_instructions.json',selected),('instruction_validation.json',{'unique_instructions':len(allins),'bodies_or_windows':bodies,'modification_counts':mods,'all_retail_match':True,'selection_windows':WINDOWS})]:
  (output/name).write_text(json.dumps(v,indent=2,sort_keys=True)+'\n')
 tables=[]
 for va in [0x4fa498,0x4f9dc0,0x4ede98,0x4f0050,0x4f1520]:
  values=struct.unpack('<13I',read(va,52));tables.append({'va':f'{va:08x}','context_destination':'000003e8','words':[f'{v:08x}' for v in values],'callback_slot_va':f'{va+28:08x}','callback_target':f'{values[7]:08x}','raw_sha256':sha(read(va,52))})
 constants=[]
 for va in [0x4be698,0x4be6e4,0x4be6e8,0x4be6d0,0x4be6e0,0x4be6ec]:
  b=read(va,4);constants.append({'va':f'{va:08x}','bits':b.hex(),'float32':struct.unpack('<f',b)[0]})
 for va in [0x4be700,0x4be740,0x4be748,0x4faf18]:
  b=read(va,8);constants.append({'va':f'{va:08x}','bits':b.hex(),'float64':struct.unpack('<d',b)[0]})
 imports=[]
 pe=struct.unpack_from('<I',raw,60)[0];base=struct.unpack_from('<I',raw,pe+52)[0]
 directory=struct.unpack_from('<I',raw,pe+24+104)[0];at=base+directory
 def cstring(va):
  b=bytearray()
  for k in range(256):
   x=read(va+k,1)[0]
   if x==0:return b.decode('ascii')
   b.append(x)
  raise ValueError('unbounded import string')
 while True:
  oft,_,_,name,iat=struct.unpack('<5I',read(at,20))
  if not any((oft,name,iat)):break
  dll=cstring(base+name);k=0
  while True:
   v=struct.unpack('<I',read(base+(oft or iat)+k*4,4))[0]
   if v==0:break
   if not v&0x80000000:
    symbol=cstring(base+v+2)
    if symbol in ('_CIpow','_ftol'):imports.append({'dll':dll,'symbol':symbol,'iat_va':f'{base+iat+k*4:08x}'})
   k+=1
  at+=20
 assert {x['symbol'] for x in imports}=={'_CIpow','_ftol'}
 (output/'descriptors_constants.json').write_text(json.dumps({'descriptors':tables,'constants':constants,'imports':imports},indent=2,sort_keys=True)+'\n')
 return {'unique_instructions':len(allins),'reviewed_instructions':len(selected),'body_or_window_records':len(bodies),'all_retail_match':True}
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--private',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();print(review(a.exe,a.private,a.output))
