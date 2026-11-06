#!/usr/bin/env python3
"""Asset-free trace/address/branch checks and exhaustive normal page residues."""
import copy,hashlib,json
from pathlib import Path
from scan_model import PCS,TER,DEFAULT,triggered
r=Path(__file__).resolve().parents[1]
def validate(rows):
 checks=0
 def ck(b,msg):
  nonlocal checks
  checks+=1
  if not b:raise AssertionError(msg)
 for case in rows:
  n=case['native'];reads=n['reads'];s=case['size'];x,z=case['origin']
  if not reads:ck(min(x,z)<0 or max(x,z)>10240,'empty scan origin guard');continue
  start=reads[0]['address']-2*(s-1);expected=[]
  page_base=start-2*((z&127)*128+(x&127))
  ck(page_base==DEFAULT or (page_base>=TER and (page_base-TER)%32768==0),'starting pointer matches local sample offset within backing page')
  for i in range(s-1,-1,-1):
   for pc,off in zip(PCS,[i,(s-1)*128+i,i*128,(s-1)+i*128]):expected.append((pc,start+2*off,i))
  ck(len(reads)<=4*s,'bounded number of scan attempts')
  for v,(pc,address,i) in zip(reads,expected):
   ck((v['pc'],v['address'],v['i'])==(pc,address,i),'original scan address, site, count and descending stride')
   if v['word'] is not None:
    if case['normal_alignment']:ck(0<=address-page_base and address+2<=page_base+32768,'normal aligned scan stays in same backing page')
  for v in reads[:-1]:ck(v['word'] is not None and not triggered(v['word']),'no read after terminating word')
  if n['outcome']=='split':
   ck(triggered(reads[-1]['word']),'split class')
   branch=[0x49160b,0x491623,0x49163b,0x491653][PCS.index(reads[-1]['pc'])]
   ck({'pc':branch,'next':0x49166c} in n['branches'],'original class JNZ enters shared split gate')
  elif n['outcome']=='leaf':ck(len(reads)==4*s and not triggered(reads[-1]['word']),'complete pass leaf')
  else:ck(reads[-1]['word'] is None and n['stopped_before_dereference'],'unsafe attempt stopped before dereference')
  if case['normal_alignment']:ck(n['outcome']==case['per_coordinate']['outcome'],'normal scan decision equals independently resolved class scan')
 return checks
def main():
 rows=[json.loads(s) for s in (r/'evidence/scan_cases.jsonl').read_text().splitlines()];checks=validate(rows);residues=0
 # Root origin multiple32, power-of-two bisection, hard split at side>=64,
 # size<=4 class bypass: all class-scanned leaves have side 8/16/32 and
 # phase divisible by side. 3072 translation preserves these phases.
 for size in (8,16,32):
  for x in range(0,128,size):
   for z in range(0,128,size):
    for i in range(size):
     for dx,dz in [(i,0),(i,size-1),(0,i),(size-1,i)]:
      assert 0<=x+dx<=127 and 0<=z+dz<=127;checks+=1;residues+=1
 rejected=[]
 for label in ['address','word','branch']:
  changed=copy.deepcopy(rows);target=next(c for c in changed if c['native']['outcome']=='split');v=target['native']
  if label=='address':v['reads'][0]['address']+=2
  if label=='word':v['reads'][-1]['word']=0xa000
  if label=='branch':v['branches']=[b for b in v['branches'] if b['next']!=0x49166c]
  try:validate(changed)
  except AssertionError:rejected.append(label)
  else:raise AssertionError('corruption not rejected: '+label)
 checks+=len(rejected)
 result={'status':'passed','checks':checks,'cases':len(rows),'exhaustive_residue_reads':residues,'corruption_controls_rejected':rejected,'normal_alignment_argument':'Root axes multiple32; power-of-two halves; class scan only for side8,16,32. Translation3072 divisible128. No local coordinate exceeds127.'}
 (r/'evidence/public_verification.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))
if __name__=='__main__':main()
