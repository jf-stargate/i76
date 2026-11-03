#!/usr/bin/env python3
"""Read-only PE provenance inspection; no third-party Python modules."""
import argparse, hashlib, json, pathlib, re, struct, subprocess
p=argparse.ArgumentParser();p.add_argument('exe');p.add_argument('output');p.add_argument('--repo');p.add_argument('--base');a=p.parse_args()
b=pathlib.Path(a.exe).read_bytes()
u16=lambda o:struct.unpack_from('<H',b,o)[0]
u32=lambda o:struct.unpack_from('<I',b,o)[0]
pe=u32(0x3c);co=pe+4;op=co+20;nsec=u16(co+2);optsize=u16(co+16)
assert b[pe:pe+4]==b'PE\0\0' and u16(op)==0x10b
sections=[]
for i in range(nsec):
 o=op+optsize+i*40;sections.append(dict(name=b[o:o+8].split(b'\0')[0].decode(),vsize=u32(o+8),rva=u32(o+12),rawsize=u32(o+16),raw=u32(o+20),flags=hex(u32(o+36))))
def off(rva):
 for s in sections:
  if s['rva']<=rva<s['rva']+s['rawsize']:return s['raw']+rva-s['rva']
 raise ValueError(hex(rva))
dirs=[dict(index=i,rva=u32(op+96+8*i),size=u32(op+100+8*i)) for i in range(u32(op+92))]
debug=[]
if dirs[6]['size']:
 for o in range(off(dirs[6]['rva']),off(dirs[6]['rva'])+dirs[6]['size'],28):
  typ=u32(o+12);sz=u32(o+16);ptr=u32(o+24);debug.append(dict(type=typ,size=sz,file_offset=ptr,signature=b[ptr:ptr+4].hex(),pdb_strings=[x.decode('ascii','replace') for x in re.findall(rb'[ -~]{4,}',b[ptr:ptr+sz])]))
strings=[]
for m in re.finditer(rb'[ -~]{4,}',b):
 t=m.group().decode()
 if re.search(r'(?i)(?:\.(?:c|cpp|cxx|h|obj|o|lib|pdb|dbg|map))(?:$|[\s:])',t) or re.search(r'(?i)(microsoft|borland|watcom|visual c|linker|codeview)',t):strings.append(dict(offset=hex(m.start()),text=t))
files=[];symptr=u32(co+8);nsyms=u32(co+12);i=0
while symptr and i<nsyms:
 o=symptr+i*18;aux=b[o+17]
 if b[o+16]==103:files.append(b[o+18:o+18+18*aux].split(b'\0')[0].decode('ascii','replace'))
 i+=1+aux
r=dict(sha256=hashlib.sha256(b).hexdigest(),md5=hashlib.md5(b).hexdigest(),file_size=len(b),pe_offset=pe,machine=hex(u16(co)),timestamp=u32(co+4),coff_symbol_pointer=symptr,coff_symbol_count=nsyms,coff_file_records=files,characteristics=hex(u16(co+18)),image_base=hex(u32(op+28)),entry_rva=hex(u32(op+16)),linker_version=[b[op+2],b[op+3]],debug_directory=dirs[6],debug_entries=debug,rich_signature_offsets=[m.start() for m in re.finditer(b'Rich',b[:pe])],codeview_signature_offsets={s.decode():[m.start() for m in re.finditer(s,b)] for s in [b'RSDS',b'NB10',b'NB09',b'NB11']},sections=sections,source_like_strings=strings)
r['utf16_source_like_strings']=[]
for m in re.finditer(rb'(?:[ -~]\x00){4,}',b):
 t=m.group().decode('utf-16le')
 if re.search(r'(?i)\.(?:c|cpp|cxx|h|obj|lib|pdb|dbg|map)(?:$|[\s:])',t):r['utf16_source_like_strings'].append(dict(offset=hex(m.start()),text=t))
if r['rich_signature_offsets']:
 rich=r['rich_signature_offsets'][0];key=u32(rich+4);start=None
 for pos in range(rich-4,0x3f,-4):
  if u32(pos)^key==0x536e6144:start=pos;break
 r['rich_decoded_records']=[] if start is None else [dict(compid=hex(u32(pos)^key),count=u32(pos+4)^key) for pos in range(start+16,rich,8)]
 r['rich_xor_key']=hex(key)
if a.repo:
 # Search accepted ancestry by filenames only; no PR branches or research-run contents.
 names=subprocess.check_output(['git','-C',a.repo,'log',a.base,'--format=','--name-only','--','*.obj','*.o','*.lib','*.a','*.pdb','*.dbg','*.map','*.sym','*.cod','*.lst','*.ilk','*.mak','*.dsw','*.dsp','*.vcproj','*.sln'],text=True)
 r['accepted_history_artifact_paths']=sorted(set(x for x in names.splitlines() if x and not x.startswith('agent/runs/')))
pathlib.Path(a.output).write_text(json.dumps(r,indent=2)+'\n')
print(json.dumps({k:v for k,v in r.items() if k not in ["source_like_strings"]},indent=2))
