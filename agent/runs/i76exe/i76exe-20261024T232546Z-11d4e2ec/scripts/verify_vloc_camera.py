#!/usr/bin/env python3
"""Independent retail PE / VDF / original-x86 emulator trace validator. Private files required."""
import argparse,csv,hashlib,json,pathlib,struct,sys,collections
p=argparse.ArgumentParser();p.add_argument('--exe',type=pathlib.Path,required=True);p.add_argument('--gzf',type=pathlib.Path,required=True);p.add_argument('--zfs',type=pathlib.Path,required=True);p.add_argument('--fixtures',type=pathlib.Path,required=True);p.add_argument('--trace-a',type=pathlib.Path,required=True);p.add_argument('--trace-b',type=pathlib.Path,required=True);p.add_argument('--run-dir',type=pathlib.Path,required=True);args=p.parse_args()
checks=0;failures=[]
def check(ok,why):
 global checks
 checks+=1
 if not ok: failures.append(why)
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def rows(path):return list(csv.DictReader(path.open(),delimiter='\t'))
run=args.run_dir;data=json.loads((run/'evidence/experiment_summary.json').read_text());check(sha(args.exe)==data['retail_exe_sha256'],'retail exe sha256');check(hashlib.md5(args.exe.read_bytes()).hexdigest()==data['retail_exe_md5'],'retail exe md5');check(sha(args.gzf)==data['private_v97_gzf_sha256'],'private GZF hash');check(sha(args.zfs)==data['zfs_sha256'],'retail ZFS hash')
for name,h in data['vdf_sha256'].items():check(sha(args.fixtures/name)==h,f'VDF digest {name}')
check(args.trace_a.read_bytes()==args.trace_b.read_bytes(),'byte-identical traces');check(sha(args.trace_a)==data['private_trace_sha256'],'private replay digest')
exe=args.exe.read_bytes();pe=struct.unpack_from('<I',exe,0x3c)[0];n=struct.unpack_from('<H',exe,pe+6)[0];sections_off=pe+24+struct.unpack_from('<H',exe,pe+20)[0];sectors=[]
for i in range(n):
 o=sections_off+40*i;vsz,va,rawsz,rawptr=struct.unpack_from('<IIII',exe,o+8);sectors.append((va,rawsz,rawptr))
def code_at(addr,count):
 rva=addr-0x400000
 for va,sz,off in sectors:
  if va<=rva and rva+count<=va+sz:return exe[off+rva-va:off+rva-va+count]
 raise RuntimeError(f'Unmapped VA {addr:08X}')
anchors=rows(run/'evidence/native_opcode_anchors.tsv')
for x in anchors:check(code_at(int(x['va'],16),len(bytes.fromhex(x['bytes_hex'])))==bytes.fromhex(x['bytes_hex']),f"PE opcode {x['va']}")
# Important dispatch table: index 5 (0x28-0x23) routes to the flagged VLOC writer.
expected=[0x4ae072,0x4ae072,0x4ae227,0x4ae146,0x4ae227,0x4ae056,0x4ae227,0x4ae02e]
for i,v in enumerate(expected):check(struct.unpack('<I',code_at(0x4ae2b4+4*i,4))[0]==v,f'VLOC switch target index {i}')
inv=rows(run/'evidence/vdf_vloc_census.tsv')
for fn in ('valeprec.vdf','vxbus.vdf'):
 raw=(args.fixtures/fn).read_bytes();rec=[x for x in inv if x['retail_resource']==fn];check(len(rec)==5,f'VLOC record count {fn}');check([int(x['type_hex'],16) for x in rec]==[0x28,0x2a,0x23,0x24,0x26],f'VLOC order {fn}')
 for row in rec:
  off=int(row['VLOC_offset_hex'],16);sz=int(row['size_bytes']);kind=int(row['type_hex'],16)
  check(raw[off:off+4]==b'VLOC',f'{fn} VLOC signature @{off:x}');check(struct.unpack_from('<II',raw,off+4)==(sz,kind),f'{fn} VLOC length/type @{off:x}')
trace=rows(args.trace_a);check(len([x for x in trace if x['event']=='ASSERT_PASS'])==4,'four original-code scenarios succeeded')
for fn in ('valeprec.vdf','vxbus.vdf'):
 for flag,suffix in [(0,'unflagged'),(16,'flagged')]:
  scenario=fn+'_'+suffix;subset=[x for x in trace if x['scenario']==scenario];events=collections.defaultdict(list)
  for x in subset:events[x['event']].append(x['detail'])
  ev=lambda key: events[key][0] if len(events[key])==1 else ''
  check(len(events['RETAIL_VLOC'])==1,f'{scenario} VLOC entry')
  check(f'status={flag:08X}' in ev('RETAIL_VLOC'),f'{scenario} expected status')
  check(len(events['NATIVE_FLAG_TEST_ENTER'])==1,f'{scenario} actual native eligibility call')
  check('eax=00000001' in ev('VLOC_NATIVE_RETURN'),f'{scenario} successful VLOC callback')
  check(('runtime398=21005000' if flag else 'runtime398=00000000') in ev('VLOC_NATIVE_RETURN'),f'{scenario} runtime field')
  check(('nodeAllocBoundary=1' if flag else 'nodeAllocBoundary=0') in ev('VLOC_NATIVE_RETURN'),f'{scenario} allocation branch')
  check(('classBindBoundary=1' if flag else 'classBindBoundary=0') in ev('VLOC_NATIVE_RETURN'),f'{scenario} class bind branch')
  check(len(events['NATIVE_CAMERA_RUNTIME_READ'])==1,f'{scenario} retail camera read')
  check(len(events['NATIVE_CAMERA_POST_GUARD' if flag else 'NATIVE_CAMERA_NULL_EXIT'])==1,f'{scenario} camera guard decision')
  check(len(events['ASSERT_PASS'])==1,f'{scenario} scenario assertion')
  if flag:
   check('nine_source_dwords_copied_exactly=true' in ev('NATIVE_LOCAL_TRANSFORM'),f'{scenario} exact nine-word original transform copy')
   check('childClass=00000028' in ev('NATIVE_LOCAL_TRANSFORM'),f'{scenario} original VLOC object type')
print(json.dumps({'status':'passed' if not failures else 'failed','test_count':checks,'passed_count':checks-len(failures),'failures':failures},indent=2))
if failures:sys.exit(1)
