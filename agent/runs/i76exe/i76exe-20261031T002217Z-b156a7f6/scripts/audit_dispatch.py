#!/usr/bin/env python3
import importlib.util,json,hashlib,sys
sys.dont_write_bytecode=True
from pathlib import Path
import argparse
ap=argparse.ArgumentParser();ap.add_argument('--source-repo',type=Path,required=True);ap.add_argument('--private',type=Path,required=True);ap.add_argument('--exe',type=Path,required=True);ap.add_argument('--out',type=Path,required=True);args=ap.parse_args()
repo=args.source_repo;old=repo/'agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe'
spec=importlib.util.spec_from_file_location('v',old/'scripts/verify_integration.py');v=importlib.util.module_from_spec(spec);spec.loader.exec_module(v)
pe=args.exe.read_bytes();anchors=[]
for line in (args.private/'clip_audit.txt').read_text().splitlines():
 c=line.split('\t')
 if len(c)==3 and len(c[0])==8:
  try:pc=int(c[0],16);raw=bytes.fromhex(c[1])
  except ValueError:continue
  if 0x471fd0<=pc<0x472240 or 0x47bf00<=pc<0x47d300 or 0x487ea0<=pc<0x488100:
   assert v.pe_slice(pe,pc,len(raw))==raw
   anchors.append(dict(va=c[0].upper(),hex=raw.hex(),instruction=c[2]))
tables=[]
for ix in range(512):
 clip=v.unpack(v.pe_slice(pe,0x4f9538+4*ix,4),'I')[0];draw=v.unpack(v.pe_slice(pe,0x4f8d38+4*ix,4),'I')[0]
 tables.append(dict(index=ix,clip=f'{clip:08X}',draw=f'{draw:08X}'))
args.out.write_text(json.dumps(dict(exe_sha256=hashlib.sha256(pe).hexdigest(),constant_004be764=v.pe_slice(pe,0x4be764,4).hex(),tables=tables,anchors=anchors),indent=2)+'\n')
for pair in [('0047C8D0','0047CE40'),('0047BF00','0047D110'),('0047C2F0','00487EA0')]:
 print(pair,[hex(t['index']) for t in tables if (t['clip'],t['draw'])==pair])
print('verified instructions',len(anchors))
