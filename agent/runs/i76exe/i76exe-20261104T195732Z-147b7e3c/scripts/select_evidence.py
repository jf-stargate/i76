"""Select reviewed instruction windows; compare body bytes with HzdVerify first.
Inputs: private HzdAudit directory, authenticated PE, owned output directory.
"""
import argparse, hashlib, json, re, struct
from pathlib import Path
WINDOWS={
 '00401540':[(0x401540,0x4016df)],
 '00401510':[(0x401510,0x40153c)],
 '00471c10':[(0x471c10,0x471c61),(0x471c84,0x471c99),(0x471cc8,0x471d34),(0x471daa,0x471dc1),(0x471e1a,0x471e41)],
 '00471eb0':[(0x471e50,0x471e7c),(0x471ee5,0x471efc)],
 '00471840':[(0x471840,0x471974)],
 '00471f00':[(0x471f00,0x471f1f)],
 '004474b0':[(0x4474e2,0x4474f7),(0x4475da,0x447647),(0x44765b,0x447688),(0x44783a,0x4478a0)],
 '00447b20':[(0x447bf0,0x447c73)],
 '004016e0':[(0x4016e0,0x40173a),(0x4018a0,0x401963)],
 '00401970':[(0x401970,0x401994),(0x401ae0,0x401b01)],
 '00495060':[(0x495060,0x495090)],
 '004b8a10':[(0x4b8bcb,0x4b8bd7)],
 '0042d5d0':[(0x42d5d0,0x42d5d1)],
 '00403900':[(0x4045be,0x4045cd)],
}

def select(audit, pe, out):
 b=pe.read_bytes();assert hashlib.sha256(b).hexdigest()=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
 p=struct.unpack_from('<I',b,60)[0];t=p+24+struct.unpack_from('<H',b,p+20)[0]
 def raw(va):
  for i in range(struct.unpack_from('<H',b,p+6)[0]):
   _,rva,n,o=struct.unpack_from('<IIII',b,t+40*i+8)
   if rva<=va-0x400000<rva+n:return va-0x400000-rva+o
  raise ValueError('unmapped VA')
 lines=['function\taddress\toriginal_bytes\tinstruction']
 for target,windows in WINDOWS.items():
  text=(audit/(target+'.txt')).read_text();entry=re.search(r'FUNCTION .* ([0-9a-f]{8})',text)[1]
  ins=[(int(m[1],16),m[2]) for m in re.finditer(r'^([0-9a-f]{8}) (.+)$',text,re.M)]
  for i,(va,s) in enumerate(ins):
   if not any(lo<=va<hi for lo,hi in windows):continue
   length=ins[i+1][0]-va if i+1<len(ins) else 1
   assert 1<=length<=15
   data=b[raw(va):raw(va)+length]
   lines.append(f'{entry}\t{va:08x}\t{data.hex()}\t{s}')
 (out/'reviewed_instructions.tsv').write_text('\n'.join(lines)+'\n')
 (out/'review_selections.json').write_text(json.dumps(WINDOWS,indent=2)+'\n')
 constants=[]
 for va in [0x4bc280,0x4bc284,0x4bc288,0x4bc28c,0x4bc290]:
  data=b[raw(va):raw(va)+4];rva=struct.unpack('<I',data)[0]
  name=b[raw(rva+0x400000)+2:raw(rva+0x400000)+50].split(b'\0')[0].decode('ascii')
  constants.append({'va':f'{va:08x}','raw_iat_bytes':data.hex(),'import_name':name})
 constants.append({'va':'004c20d0','bytes':b[raw(0x4c20d0):raw(0x4c20d0)+6].hex(),'meaning':'strpbrk delimiter set plus NUL'})
 (out/'parser_constants.json').write_text(json.dumps(constants,indent=2)+'\n')
 print('selected instructions',len(lines)-1)

if __name__=='__main__':
 p=argparse.ArgumentParser()
 for k in ['audit','pe','output']:p.add_argument('--'+k,type=Path,required=True)
 a=p.parse_args();select(a.audit,a.pe,a.output)
