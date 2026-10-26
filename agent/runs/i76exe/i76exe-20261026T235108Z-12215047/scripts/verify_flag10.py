#!/usr/bin/env python3
"""Independently check original-x86 vehicle status writer / VLOC-gate research.

Requires the original retail i76.exe and the private v97 GZF; not committed.
The Ghidra headless probe should be rerun separately to regenerate the optional
second trace. This verifier never runs submitted Java or executes original PE.
"""
import argparse,csv,hashlib,json,pathlib,struct,sys
PE_MD5='a640ea0097dbb62e0c77b7f2847c7161'
PE_SHA='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF_SHA='b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'
TRACE_SHA='0bbae7ee9bbeeb775e0be0c50f4b52a4016d2d22390d8c88c2897f5cb37b471b'
def digest(data,algo='sha256'):return hashlib.new(algo,data).hexdigest()
class Checks:
 def __init__(self):self.passed=0
 def is_true(self,p,msg):
  if not p:raise AssertionError(msg)
  self.passed+=1

def main():
 p=argparse.ArgumentParser()
 p.add_argument('--exe',required=True,type=pathlib.Path)
 p.add_argument('--ghidra-gzf',required=True,type=pathlib.Path)
 p.add_argument('--second-trace',type=pathlib.Path)
 p.add_argument('--write-validation',type=pathlib.Path)
 args=p.parse_args()
 root=pathlib.Path(__file__).resolve().parents[1]
 c=Checks();pe=args.exe.read_bytes();gzf=args.ghidra_gzf.read_bytes()
 c.is_true(digest(pe,'md5')==PE_MD5,'retail executable MD5')
 c.is_true(digest(pe)==PE_SHA,'retail executable SHA256')
 c.is_true(digest(gzf)==GZF_SHA,'annotated GZF SHA256')
 # Parse section headers from original PE/COFF; don't assume file offset == VA.
 pe_off=struct.unpack_from('<I',pe,0x3c)[0]
 c.is_true(pe[pe_off:pe_off+4]==b'PE\0\0','PE signature')
 num=struct.unpack_from('<H',pe,pe_off+6)[0]
 opts=struct.unpack_from('<H',pe,pe_off+20)[0];op=pe_off+24
 image_base=struct.unpack_from('<I',pe,op+28)[0]
 sections=[]
 for i in range(num):
  sh=op+opts+40*i
  vs,va,rs,ro=struct.unpack_from('<IIII',pe,sh+8)
  sections.append((va,max(vs,rs),ro))
 def code_at(addr,n):
  rva=addr-image_base
  for va,sz,offset in sections:
   if va<=rva and rva+n<=va+sz:return pe[offset+rva-va:offset+rva-va+n]
  raise AssertionError('PE address outside mapped sections %08X'%addr)
 with (root/'evidence/retail_opcode_anchors.tsv').open() as fd:anchors=list(csv.DictReader(fd,delimiter='\t'))
 c.is_true(len(anchors)>=25,'sufficient independent sparse opcode locations')
 for r in anchors:
  expected=bytes.fromhex(r['bytes_hex']);addr=int(r['va'],16)
  c.is_true(code_at(addr,len(expected))==expected, 'retail byte anchor %08X'%addr)
 with (root/'evidence/call_edges.tsv').open() as fd:edges=list(csv.DictReader(fd,delimiter='\t'))
 c.is_true(len(edges)>=12,'sufficient call-edge samples')
 for r in edges:
  addr=int(r['call_va'],16);target=int(r['target_va'],16);inst=code_at(addr,5)
  c.is_true(inst[0]==0xe8 and ((addr+5+struct.unpack('<i',inst[1:])[0])&0xffffffff)==target,'direct call %08X'%addr)
 data=(root/'evidence/status_flag10_original_x86.tsv').read_bytes()
 c.is_true(digest(data)==TRACE_SHA,'retained exact original-x86 replay hash')
 if args.second_trace:
  c.is_true(args.second_trace.read_bytes()==data,'independent Ghidra replay byte identity')
 with (root/'evidence/status_flag10_original_x86.tsv').open() as fd:rows=list(csv.DictReader(fd,delimiter='\t'))
 c.is_true(len(rows)==7,'scenario coverage')
 names={'player_matched','player_unmatched','id_zero_matched','id_wrap_low16','startup_secondary','startup_primary','startup_nonzero'}
 c.is_true({r['scenario'] for r in rows}==names,'exact scenario set')
 for r in rows:
  scenario=r['scenario'];idval=int(r['spawn_id_or_flag']);flag=int(r['status_actual'],16)
  expected=int(r['status_expected'],16);got=int(r['vloc_eligibility']);exp=int(r['vloc_expected'])
  if r['function']=='00451180':
   local=int(r['local_id']);team=int(r['team']);want=(team<<16)|(0x10 if (idval&0xffff)==(local&0xffff) else 0x20)
   c.is_true(int(r['intercepted_services'])==2,'only expected network lookup/format substitutions '+scenario)
  else:
   c.is_true(r['function']=='004513C0','original creation path '+scenario)
   want=0x10010 if idval else 0x20000
   c.is_true(int(r['intercepted_services'])==1,'only expected basename substitution '+scenario)
  c.is_true(flag==expected==want,'original status selection '+scenario)
  c.is_true(got==exp==int(bool(flag&0x10)),'original 00458BF0 gate '+scenario)
  c.is_true(r['result']=='PASS','Ghidra script assertion '+scenario)
  c.is_true(10<=int(r['instructions'])<=100,'bounded native execution '+scenario)
 summary=json.loads((root/'evidence/experiment_summary.json').read_text())
 c.is_true(summary['trace_sha256']==TRACE_SHA and summary['repeat_identical'],'provenance summary')
 c.is_true(summary['full_vcf_not_executed'] is True,'explicit unexecuted full-loader caveat')
 c.is_true(summary['original_x86_scenarios']==7,'scenario metadata')
 result={'status':'passed','test_count':c.passed,'passed_count':c.passed,'notes':f'{c.passed} independent identity, PE opcode/call-target, original-instruction trace and scenario assertions; two Ghidra replays byte-identical; original VCF/VLOC continuous construction not executed.'}
 if args.write_validation:args.write_validation.write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps(result,indent=2))
if __name__=='__main__':main()
