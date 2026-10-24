#!/usr/bin/env python3
"""Read-only independent verifier of private I76 camera-follow replay.
No copyrighted bytes or input files are written to the Git repository.
"""
import argparse,csv,hashlib,json,struct
from pathlib import Path
p=argparse.ArgumentParser()
p.add_argument('--run',required=True,type=Path)
p.add_argument('--exe',required=True,type=Path)
p.add_argument('--zfs',required=True,type=Path)
p.add_argument('--gzf',required=True,type=Path)
p.add_argument('--trace1',required=True,type=Path)
p.add_argument('--trace2',required=True,type=Path)
a=p.parse_args()
run=a.run
summary=json.loads((run/'evidence/experiment_summary.json').read_text())
checks=[]
def ok(label,condition):
 checks.append((label,bool(condition)))
 if not condition: print('FAIL',label)
sha=lambda b:hashlib.sha256(b).hexdigest()
raw=a.exe.read_bytes()
ok('PE md5',hashlib.md5(raw).hexdigest()==summary['retail_md5'])
ok('PE sha256',sha(raw)==summary['retail_sha256'])
ok('ZFS sha256',sha(a.zfs.read_bytes())==summary['zfs_sha256'])
ok('annotated GZF sha256',sha(a.gzf.read_bytes())==summary['private_ghidra_gzf_sha256'])
r1=a.trace1.read_bytes();r2=a.trace2.read_bytes()
ok('trace1 sha256',sha(r1)==summary['private_trace_sha256'])
ok('trace2 sha256',sha(r2)==summary['private_trace_sha256'])
ok('repeat byte equality',r1==r2)
ok('trace count',summary['replays']==2)
# Map original PE 0x400000 image-based VAs into raw PE .text bytes without relying on imports.
elfanew=struct.unpack_from('<I',raw,0x3c)[0]
section_count=struct.unpack_from('<H',raw,elfanew+6)[0]
optional_length=struct.unpack_from('<H',raw,elfanew+20)[0]
sec_start=elfanew+24+optional_length
sections=[]
for i in range(section_count):
 part=raw[sec_start+i*40:sec_start+(i+1)*40]
 vsize,rva,sz,roff=struct.unpack_from('<IIII',part,8)
 sections.append((rva,sz,roff))
def pe_at(va,n):
 rva=va-0x400000
 for start,sz,off in sections:
  if start<=rva<start+sz:
   return raw[off+rva-start:off+rva-start+n]
 raise ValueError('unmapped virtual address '+hex(va))
anchors=list(csv.DictReader((run/'evidence/original_opcode_anchors.tsv').open(),delimiter='\t'))
ok('21 opcode rows',len(anchors)==21)
for row in anchors:
 va=int(row['address'],16);expect=bytes.fromhex(row['retail_bytes_hex'])
 ok('original PE byte anchor '+row['address'],pe_at(va,len(expect))==expect)
lines=list(csv.DictReader(a.trace1.open(),delimiter='\t'))
# All scenario checks below use output of executed original instructions and distinguish stubs.
scenarios={'gtsi_top_level_vcf':46,'bus_top_level_vcf':44}
for label,node_count in scenarios.items():
 ev=[x for x in lines if x['scenario']==label]
 find=lambda kind:[x for x in ev if x['kind']==kind]
 obj=[x for x in summary['scenarios'] if x['scenario']==label]
 ok(label+' exactly one summary',len(obj)==1)
 if len(obj)!=1:continue
 obj=obj[0]
 ok(label+' original VCF construction',len(find('NATIVE_VCF_COMPLETE'))==1)
 ok(label+' original registration',len(find('REGISTER_ROOT_RETURN'))==1)
 ok(label+' active entry identity',obj['registered_active']=='00542830')
 ok(label+' root pointer',obj['world_object']=='26000000')
 ok(label+' original runtime pointer',obj['vehicle_runtime']=='36000000')
 ok(label+' camera target null',obj['extra_runtime_ptr_398']=='00000000')
 ok(label+' original default callback return',obj['default_callback_returned'] and len(find('CAMERA_DEFAULT_CALLBACK_RETURN'))==1)
 ok(label+' native class-1 guard 00458A90',any(x['pc']=='00458A90' for x in find('CAMERA_DEFAULT_DEPENDENCY_ENTER')))
 ok(label+' native runtime accessor 00467440',any(x['pc']=='00467440' for x in find('CAMERA_DEFAULT_DEPENDENCY_ENTER')))
 ok(label+' follow callback completed',obj['follow_callback_returned'] and len(find('CAMERA_REGISTERED_FOLLOW_RETURN'))==1)
 ok(label+' native view composition 00472990',obj['original_view_composition_calls']==1)
 ok(label+' one identified FPATAN substitution',obj['quaternion_interpolation_substitutions']==1)
 ok(label+' original sin/cos interface calls',obj['sin_cos_substitutions']==3)
 ok(label+' original projection FTOL boundaries',obj['float_to_int_substitutions']==4)
 ok(label+' view transform present',obj['view_y_bits']=='6D99997C' and obj['view_z_bits']=='A7420358')
 ok(label+' unmodified world object refcount',any('ref=4' in x['detail'] for x in find('CAMERA_REGISTERED_FOLLOW_BEGIN')))
 ok(label+' matching original callback record target',all(x['pc']=='00405B90' for x in find('CAMERA_REGISTERED_FOLLOW_RETURN')))
 ok(label+' original view target global',any('context=004C2730' in x['detail'] for x in find('CAMERA_ORIGINAL_VIEW_COMPOSITION')))
 ok(label+' camera world identity retained',any('worldObject=26000000' in x['detail'] for x in find('CAMERA_REGISTERED_FOLLOW_RETURN')))
 ok(label+' vehicle node count',any('nodes='+str(node_count) in x['detail'] for x in find('NATIVE_VCF_COMPLETE')))
 ok(label+' registered active object still present after',len(find('REGISTERED_REREGISTER_DONE'))==1)
print(f'{sum(b for _,b in checks)}/{len(checks)} checks passed')
if not all(b for _,b in checks):raise SystemExit(1)
