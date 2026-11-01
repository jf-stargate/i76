#!/usr/bin/env python3
"""Compare accepted listings and disposable Ghidra instructions with supplied retail PE.
Emits counts/hashes only; no proprietary instructions or source are republished.
"""
import argparse,csv,hashlib,json,struct
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--repo',type=Path,required=True);p.add_argument('--exe',type=Path,required=True);p.add_argument('--ghidra-output',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
b=a.exe.read_bytes();sha=hashlib.sha256(b).hexdigest();assert sha=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
pe=struct.unpack_from('<I',b,0x3c)[0];assert b[pe:pe+4]==b'PE\0\0';n=struct.unpack_from('<H',b,pe+6)[0];opt=struct.unpack_from('<H',b,pe+20)[0];base=struct.unpack_from('<I',b,pe+52)[0]
sections=[struct.unpack_from('<8sIIII',b,pe+24+opt+40*i) for i in range(n)]
def raw(va,count):
 rva=va-base
 for _,vs,rv,sz,off in sections:
  if rv<=rva and rva+count<=rv+sz:return b[off+rva-rv:off+rva-rv+count]
 raise ValueError(hex(va))
addresses=['00410490','00412500','00414670','004149f0','0040a320','00412ce0'];rows=[]
snap=a.repo/'snapshot/i76.exe/i76.exe_ghidra_state_snapshot_20261021_v97/disassembly'
for va in addresses:
 f=next(x for x in snap.iterdir() if x.name.lower().startswith(va+'_'));count=0
 for r in csv.DictReader(f.open(),delimiter='\t'):
  expected=bytes.fromhex(r['bytes']);assert raw(int(r['address'],16),len(expected))==expected,(f,r['address']);count+=1
 files=[a.ghidra_output/(phase+'-'+va.lstrip('0')+'-instructions.tsv') for phase in ['before','after']]
 assert files[0].read_bytes()==files[1].read_bytes()
 gcount=0
 for r in csv.DictReader(files[0].open(),delimiter='\t'):
  expected=bytes.fromhex(r['bytes']);assert raw(int(r['address'],16),len(expected))==expected;gcount+=1
 rows.append({'address':va,'accepted_listing_instructions':count,'ghidra_instructions':gcount,'ghidra_listing_sha256':hashlib.sha256(files[0].read_bytes()).hexdigest(),'snapshot_sha256':hashlib.sha256(f.read_bytes()).hexdigest(),'match':True})
# Reporter and jump tables are additional direct PE checks, independent of labels.
assert raw(0x42d5d0,1)==b'\xc3'
targets=struct.unpack('<14I',raw(0x4149b8,56));assert len(set(targets))==14
out={'method':'binary-static byte equality, not instruction execution','retail_sha256':sha,'retail_md5':hashlib.md5(b).hexdigest(),'functions':rows,'vm_jump_targets':[f'{x:08x}' for x in targets],'retail_reporter_is_ret':True,'instruction_bytes_unchanged_by_annotations':True}
a.output.write_text(json.dumps(out,indent=2)+'\n');print(json.dumps({'functions':len(rows),'accepted_instructions':sum(r['accepted_listing_instructions'] for r in rows),'ghidra_instructions':sum(r['ghidra_instructions'] for r in rows),'all_match':True}))
