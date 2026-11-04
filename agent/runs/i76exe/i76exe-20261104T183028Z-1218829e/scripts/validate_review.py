#!/usr/bin/env python3
"""Original PE validation of layout/callback/control observations; no bytes emitted."""
import hashlib,json,pathlib,struct,sys
from analyze import dump
pe,capture,control,out=map(pathlib.Path,sys.argv[1:]);raw=pe.read_bytes();x=json.loads(capture.read_text());c=json.loads(control.read_text())
p=struct.unpack_from('<I',raw,0x3c)[0];count=struct.unpack_from('<H',raw,p+6)[0];opt=struct.unpack_from('<H',raw,p+20)[0];image=struct.unpack_from('<I',raw,p+52)[0]
ss=[struct.unpack_from('<IIII',raw,p+24+opt+40*i+8) for i in range(count)]
def read(va,n):
 for vs,base,sz,ptr in ss:
  if base<=va-image and va-image+n<=base+sz:return raw[ptr+va-image-base:ptr+va-image-base+n]
 raise ValueError(hex(va))
gaps=[]
for f in x['functions'][1:-2]:
 for g in f['gap']:
  lo,hi=int(g['start'],16),int(g['end'],16);b=read(lo,hi-lo+1)
  assert b==bytes.fromhex(g['hex']) and set(b)=={0x90}
 gaps.append(dict(after=f['entry'],bytes=sum(len(bytes.fromhex(g['hex'])) for g in f['gap'])))
sites=[0x470aa0,0x470b30,0x470bd0,0x470c4f,0x470c7f]
for va in sites:assert read(va,1)==b'\x68' and struct.unpack('<I',read(va+1,4))[0]==0x470ca0
for row in c['rows']:
 if row['text'].startswith('addr '):assert struct.unpack('<I',read(int(row['start'],16),4))[0]==int(row['text'].split()[1],16)
for ins in c['computed_instructions']:
 for ref in ins['references']:
  if ref['type']=='DATA' and ref['to'].startswith('00412c'):assert struct.unpack('<I',read(int(ins['address'],16)+3,4))[0]==int(ref['to'],16)
assert read(0x412cbc,4)==b'\x90'*4
assert c['modification_before']==c['modification_after']
dump(out,dict(internal_gap_count=len(gaps),internal_gaps=gaps,internal_gap_occupancy='all NOP alignment, no switch table',callback_push_sites=[f'{v:08x}' for v in sites],control_gap=dict(start='00412c30',end='00412cbf',bytes=144,sha256=hashlib.sha256(read(0x412c30,144)).hexdigest(),jump_table_entries=sum(row['text'].startswith('addr ') for row in c['rows']),trailing_nops=4,computed_jumps=[ins['address'] for ins in c['computed_instructions'] if ins['text'].startswith('JMP')]),control_session_modifications=[c['modification_before'],c['modification_after']],private_control_capture_sha256=hashlib.sha256(control.read_bytes()).hexdigest(),status='passed'))
