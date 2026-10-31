#!/usr/bin/env python3
"""Authenticate Ghidra instruction extracts directly against immutable retail PE bytes."""
import argparse,csv,hashlib,importlib.util,json,sys
from pathlib import Path
sys.dont_write_bytecode=True
p=argparse.ArgumentParser();p.add_argument('--source-repo',type=Path,required=True);p.add_argument('--private',type=Path,required=True);p.add_argument('--exe',type=Path,required=True);p.add_argument('--out',type=Path,required=True);a=p.parse_args()
spec=importlib.util.spec_from_file_location('pe_reader',a.source_repo/'agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/scripts/verify_polygon.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
b=a.exe.read_bytes();assert hashlib.sha256(b).hexdigest()=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
rows=list(csv.DictReader((a.private/'opcodes.tsv').open(),delimiter='\t'))
for r in rows:assert m.pe_slice(b,int(r['va'],16),len(bytes.fromhex(r['hex']))).hex()==r['hex'],r
constants={f'{va:08X}':m.pe_slice(b,va,n).hex() for va,n in [(0x4be778,4),(0x4fa48c,4),(0x4f9d84,4),(0x4f9d88,8),(0x4faf18,8),(0x4bc154,4),(0x4bc150,4)]}
a.out.write_text(json.dumps({'exe_sha256':hashlib.sha256(b).hexdigest(),'instructions':rows,'constants':constants},indent=2)+'\n');print('retail opcodes independently matched:',len(rows))
