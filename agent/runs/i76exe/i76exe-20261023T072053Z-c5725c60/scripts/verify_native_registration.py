#!/usr/bin/env python3
"""Reproducible private-input verification for the original-code I76 registration checkpoint.
Never publish input executable, GZF, ZFS, private native traces, or fixtures.
"""
import argparse,csv,hashlib,json,struct,tarfile
from pathlib import Path

PE_HASH='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF_HASH='b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce'
ZFS_HASH='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d'
TRACE_HASH='7b4a567be1ca1f64f73ccb8cc7e6b69aaf8f30101343271557174a054692a4bf'

def sha(raw):return hashlib.sha256(raw).hexdigest()
def readtab(p):return list(csv.DictReader(open(p,newline=''),delimiter='\t'))
def detail(row):return dict(p.split('=',1) for p in row['detail'].split(';') if '=' in p)

def pe_extract(b,va,n):
 off=struct.unpack_from('<I',b,0x3c)[0];assert b[off:off+4]==b'PE\0\0'
 sec=off+24+struct.unpack_from('<H',b,off+20)[0];num=struct.unpack_from('<H',b,off+6)[0]
 base=struct.unpack_from('<I',b,off+24+28)[0];rva=va-base
 for i in range(num):
  o=sec+i*40;vsize,vaddr,rsize,roff=struct.unpack_from('<IIII',b,o+8)
  if vaddr<=rva< vaddr+rsize and rva+n<=vaddr+rsize:return b[roff+rva-vaddr:roff+rva-vaddr+n]
 raise ValueError(f'VA {va:08x} not in image raw section')

def run(args):
 checks=[]
 def ck(ok,n):
  if not ok:raise AssertionError(n)
  checks.append(n)
 runroot=Path(args.run_root)
 pe=Path(args.retail_exe).read_bytes();ck(sha(pe)==PE_HASH,'retail PE SHA256')
 ck(sha(Path(args.private_gzf).read_bytes())==GZF_HASH,'private Ghidra v97 GZF SHA256')
 with tarfile.open(args.game_tar,'r') as t:
  z=t.extractfile('interstate 76/I76.ZFS');assert z is not None
  ck(sha(z.read())==ZFS_HASH,'retail I76.ZFS SHA256')
 ta=Path(args.trace_a).read_bytes();tb=Path(args.trace_b).read_bytes()
 ck(ta==tb,'original x86 double-replay byte-for-byte equality')
 ck(sha(ta)==TRACE_HASH,'original x86 replay SHA256')
 for x in readtab(runroot/'evidence/native_opcode_anchors.tsv'):
  va=int(x['retail_va'],16);expected=bytes.fromhex(x['first_four_bytes_hex']);ck(len(expected)==4 and pe_extract(pe,va,4)==expected,f'original instruction anchor {va:08X}')
 recs=list(csv.DictReader(ta.decode().splitlines(),delimiter='\t'))
 def select(v,k):return [r for r in recs if r['scenario']==v and r['kind']==k]
 cases=readtab(runroot/'evidence/registered_vehicle_scenarios.tsv')
 lifecycle=readtab(runroot/'evidence/registration_refcount_lifecycle.tsv')
 ck(len(cases)==4,'scenario table cardinality')
 ck(len(lifecycle)==2,'lifecycle table cardinality')
 for ve in ['gtsi_top_level_vcf','bus_top_level_vcf']:
  prefix=ve.split('_')[0]
  reg=detail(select(ve,'REGISTER_ROOT_RETURN')[0]);begin=detail(select(ve,'REGISTER_ROOT_BEGIN')[0]);unreg=detail(select(ve,'REGISTERED_UNREGISTER_DONE')[0]);again=detail(select(ve,'REGISTERED_REREGISTER_DONE')[0]);start=detail(select(ve,'REGISTERED_UNREGISTER_BEGIN')[0]);
  ck(begin['root']=='26000000' and begin['class']=='1',f'{ve}: authentic constructed vehicle root class')
  ck(begin['refBefore']=='3' and reg['rootRef']=='4',f'{ve}: native registration increments root reference')
  ck(reg['entry']=='00542830' and reg['entryOwner']=='26000000' and reg['activeCount']=='1',f'{ve}: original 0x78-stride entry identity')
  ck(int(reg['radius'],16)==0,f'{ve}: synthetic native radius documented zero')
  ck(start['ref']=='4' and unreg['ref']=='3' and unreg['count']=='0' and unreg['entryObject']=='00000000',f'{ve}: original unregister clears entry and decrements reference')
  ck(again['entry']=='00542830' and again['rootRef']=='4' and again['count']=='1',f'{ve}: original re-register slot reuse')
  begin_cases=[detail(r) for r in select(ve,'REGISTERED_PRODUCE_BEGIN')]
  end_cases=[detail(r) for r in select(ve,'REGISTERED_PRODUCE_END')]
  ck(len(begin_cases)==2 and len(end_cases)==2,f'{ve}: accept reject scenario count')
  accepted=next(r for r in end_cases if r['visible']=='true')
  rejected=next(r for r in end_cases if r['visible']=='false')
  ck((accepted['frustum'],accepted['alloc'],accepted['binCalls'],accepted['records'])==('2','2','2','2'),f'{ve}: native accepted frustum and queue')
  ck((rejected['frustum'],rejected['alloc'],rejected['binCalls'],rejected['records'])==('1','0','0','0'),f'{ve}: native rejected frustum and no allocation')
  buck=[detail(r) for r in select(ve,'REGISTERED_BUCKET')]
  ck(sorted((r['type'],r['bin'],r['count']) for r in buck)==[('10','90','1'),('6','100','1')],f'{ve}: two distinct native queue buckets')
  bline=[detail(r) for r in select(ve,'PRODUCER_NATIVE_BIN_ENTER')]
  ck(len(bline)==2 and sorted((r['type'],r['callerReturn']) for r in bline)==[('10','0048F4A8'),('6','004586C4')],f'{ve}: original type6 and type10 caller addresses')
  work=[detail(r) for r in select(ve,'REGISTERED_RECORD')]
  ck(len(work)>=2 and work[0]['kind']=='6' and work[0]['owner']=='26000000' and work[0]['mode']=='0',f'{ve}: type6 original root/secondary')
  ck(work[1]['kind']=='10' and work[1]['owner']=='27000C00',f'{ve}: type10 distinct child owner')
  ck(accepted['cursor']=='2E1800B8',f'{ve}: authentic cursor advanced across two records')
  ck(len(select(ve,'SCENE_NATIVE_DISPATCH'))==1 and len(select(ve,'SCENE_ORIGINAL_TREE_ENTRY'))==1,f'{ve}: native consumer and secondary dispatch')
  ck(select(ve,'SCENE_ORIGINAL_TREE_ENTRY')[0]['pc']=='0045D530',f'{ve}: secondary traversal exact address')
  ck(len(select(ve,'NATIVE_GEO_SECTION_BUILDER_ENTER'))==1,f'{ve}: actual child GEO builder')
  cc=detail(select(ve,'REGISTERED_CONSUMER_DONE')[0]);ck(cc['builder']=='1' and cc['submissions']=='0' and cc['materialCalls']=='0',f'{ve}: geometry scratch but no polygon for synthetic camera')
  ccases=[r for r in cases if r['vehicle']==ve]
  ck(len(ccases)==2 and next(r for r in ccases if r['accepted']=='1')['records']=='2' and next(r for r in ccases if r['accepted']=='0')['records']=='0',f'{ve}: derived scenario table parity')
  croot=next(r for r in lifecycle if r['vehicle']==ve)
  ck((croot['ref_before_register'],croot['ref_after_register'],croot['ref_after_unregister'],croot['ref_after_reregister'])==('3','4','3','4'),f'{ve}: derived lifecycle table parity')
 ck(sum(r['kind']=='SCENE_NATIVE_SUBMIT_ENTER' for r in recs)==0,'no original polygon submitters in this test')
 ck(sum(r['kind']=='REGISTERED_REREGISTER_DONE' for r in recs)==2,'both vehicles complete original registration lifecycle')
 provenance=json.loads((runroot/'evidence/replay_provenance.json').read_text())
 ck(provenance['private_trace_sha256']==TRACE_HASH and provenance['replay_count']==2,'private replay provenance identity')
 print(json.dumps({'status':'passed','test_count':len(checks),'passed_count':len(checks),'anchors':len(readtab(runroot/'evidence/native_opcode_anchors.tsv')),'native_vehicle_cases':4,'root_lifecycle_sequences':2,'trace_sha256':TRACE_HASH},indent=2))
 return len(checks)
if __name__=='__main__':
 ap=argparse.ArgumentParser();ap.add_argument('--retail-exe',required=True);ap.add_argument('--private-gzf',required=True);ap.add_argument('--game-tar',required=True);ap.add_argument('--trace-a',required=True);ap.add_argument('--trace-b',required=True);ap.add_argument('--run-root',required=True)
 run(ap.parse_args())
