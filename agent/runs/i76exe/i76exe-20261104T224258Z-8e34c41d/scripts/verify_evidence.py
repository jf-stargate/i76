"""Validate every private audited byte against PE; publish hashes/reviewed assembly.

Exact opcode bytes, decompilation, callback data ranges stay private.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
EXE_SHA='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF_SHA='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0'
ADDRESSES='004b95f0,004b9740,004b9800,004b9ad0,004b9af0,004b9b40,004b9ba0,004b9bd0,004b9db0,004b9fc0,004b2ac0,004b2b30,004b2e00,004b3000,004b3030,004b3310,004b34f0,004b3550,00470070,0042d5d0,004ba980,004baa00,004babd8,004b1df0,004b23e0,004b28c0,004b2d50,00471250,004b32f0,00470ca0,004702d0,004b95c0,004b2a70,004b2220,0046fbe0,00404d80,004b20f0'
WINDOWS=[('X EOF status',0x4bad70,0x4bad8e),('ZIX unquoted lowercase',0x4b21c4,0x4b21d8),('forced cache free',0x46fc9e,0x46fcba),('header constants',0x4b9877,0x4b9892),('signed table allocation',0x4b98f0,0x4b991d),
 ('table width',0x4b9973,0x4b9980),('empty/inactive/copy',0x4b99b0,0x4b99dc),('table termination',0x4b99de,0x4b99e6),
 ('actual table count',0x4b9a38,0x4b9a44),('directory sorting',0x4b9a7c,0x4b9a88),
 ('signed logical size',0x4b9b7d,0x4b9b8e),('lookup unchecked/compression',0x4b9c0c,0x4b9c28),
 ('payload seek/read',0x4b9c6a,0x4b9c93),('decoded allocation length',0x4b9cde,0x4b9cf0),
 ('dispatch args/temp free',0x4b9d2b,0x4b9d56),('declared length returned',0x4b9d62,0x4b9d78),
 ('postdecode XOR',0x4b9d78,0x4b9d9b),('LZO initialization version',0x4b9fd4,0x4b9fef),
 ('X dispatch',0x4ba014,0x4ba03c),('Y dispatch',0x4ba040,0x4ba064),('dispatch success',0x4ba07d,0x4ba087),
 ('Y distinctive match arithmetic',0x4baa94,0x4baaa9),('X distinctive match arithmetic',0x4bac6c,0x4bac82),
 ('Y first match distance',0x4baa6b,0x4baa7a),('X first match distance',0x4bac43,0x4bac52),
 ('Y EOF status',0x4bab98,0x4babb6),('Y EOF errors',0x4babc9,0x4babd5),
 ('registration invalidates cached key',0x4b2b30,0x4b2b3c),
 ('source scan initialization',0x4b2e72,0x4b2e84),('source bitmap word',0x4b2e92,0x4b2ea3),
 ('source first/mode/media',0x4b2ec0,0x4b2ef0),('source stride',0x4b2ef4,0x4b2f01),
 ('source earlier override',0x4b2f03,0x4b2f1f),('source active fallback',0x4b2f3a,0x4b2f41),
 ('close handles',0x4b2f77,0x4b2f9a),('switch callback',0x4b2f9c,0x4b2fcb),
 ('cache invalidation',0x47032a,0x470334),('forced refcount zero',0x46fbe0,0x46fc00),
 ('one RET reporter',0x42d5d0,0x42d5d0),('source dispatch substring',0x4b30e0,0x4b312d),
 ('source registration masks',0x4b2c30,0x4b2c6f),('directory name comparator',0x4b9ad0,0x4b9aed)]

def sha(data):return hashlib.sha256(data).hexdigest()
def pe_reader(raw):
 pe=struct.unpack_from('<I',raw,0x3c)[0]
 if raw[pe:pe+4]!=b'PE\0\0':raise ValueError('not PE')
 count=struct.unpack_from('<H',raw,pe+6)[0];opt=struct.unpack_from('<H',raw,pe+20)[0]
 image=struct.unpack_from('<I',raw,pe+52)[0];sections=[]
 for i in range(count):
  size,rva,stored,offset=struct.unpack_from('<4I',raw,pe+24+opt+40*i+8)
  sections.append((image+rva,stored,offset))
 def read(va,size):
  for start,stored,offset in sections:
   if start<=va and size<=stored-(va-start):
    out=raw[offset+va-start:offset+va-start+size]
    if len(out)==size:return out
  raise ValueError('range not backed by PE')
 return read

def verify(exe,gzf,audit,ranges):
 raw=exe.read_bytes();assert sha(raw)==EXE_SHA and sha(gzf.read_bytes())==GZF_SHA
 read=pe_reader(raw);doc=json.loads(audit.read_text());extra=json.loads(ranges.read_text())
 assert doc['modification_before']==doc['modification_after']
 assert doc['executable_sha256']==EXE_SHA and doc['ghidra']=='12.1.4'
 functions=[];selected=[];total=0
 for f in doc['functions']:
  for span in f['ranges']:assert sha(read(int(span['start'],16),span['length']))==span['sha256']
  functions.append({k:f[k] for k in ('entry','name','ranges')})
  for ins in f['instructions']:
   code=bytes.fromhex(ins['bytes']);va=int(ins['va'],16);assert read(va,len(code))==code;total+=1
   tags=[name for name,lo,hi in WINDOWS if lo<=va<=hi]
   if tags:selected.append({'va':ins['va'],'asm':ins['asm'],'length':len(code),'sha256':sha(code),'review':tags})
 for r in extra['ranges']:
  for ins in r['instructions']:
   code=bytes.fromhex(ins['bytes']);assert read(int(ins['va'],16),len(code))==code;total+=1
  functions.append({'entry':r['start'],'end_inclusive':r['end'],'name':'callback instruction range; no inferred Ghidra function extent',
                    'sha256':sha(read(int(r['start'],16),int(r['end'],16)-int(r['start'],16)+1))})
 for d in extra['data']:assert read(int(d['va'],16),len(bytes.fromhex(d['hex'])))==bytes.fromhex(d['hex'])
 assert {f['entry'] for f in doc['functions']}==set(ADDRESSES.split(','))
 return {'exe_sha256':EXE_SHA,'gzf_sha256':GZF_SHA,'ghidra':doc['ghidra'],'program':doc['program'],
         'modification_before':doc['modification_before'],'modification_after':doc['modification_after'],
         'verified_instructions':total,'functions':functions,'reviewed_instructions':selected,
         'publication':'opcode bytes and bulk export private; public per-instruction hashes and reviewed assembly only'}
if __name__=='__main__':
 ap=argparse.ArgumentParser(description=__doc__)
 for n in ('exe','gzf','audit','ranges','output'):ap.add_argument('--'+n,type=Path,required=True)
 a=ap.parse_args();a.output.write_text(json.dumps(verify(a.exe,a.gzf,a.audit,a.ranges),sort_keys=True,indent=2)+'\n')
