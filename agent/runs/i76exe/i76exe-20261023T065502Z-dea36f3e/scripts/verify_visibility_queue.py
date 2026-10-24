#!/usr/bin/env python3
"""Validate private inputs, identical original-code traces and derived public producer table."""
import argparse, csv, hashlib, json, struct
from pathlib import Path

def sha(p,alg='sha256'):
 h=hashlib.new(alg)
 with p.open('rb') as f:
  for chunk in iter(lambda:f.read(1<<20),b''):h.update(chunk)
 return h.hexdigest()
def tsv(p):
 with p.open(newline='') as f:return list(csv.DictReader(f,delimiter='\t'))
def pe_map(b,va):
 pe=struct.unpack_from('<I',b,0x3c)[0];assert b[pe:pe+4]==b'PE\0\0'
 cnt=struct.unpack_from('<H',b,pe+6)[0];oh=struct.unpack_from('<H',b,pe+20)[0];image=struct.unpack_from('<I',b,pe+24+28)[0];rva=va-image
 for i in range(cnt):
  off=pe+24+oh+40*i;size,rstart,rsize,pstart=struct.unpack_from('<IIII',b,off+8)
  if rstart<=rva<rstart+max(size,rsize):return pstart+rva-rstart
 raise ValueError(hex(va))
def fields(s):return dict(p.split('=',1) for p in s.split(';') if '=' in p)
def verify(run,pe,zfs,gzf,a,b):
 prov=json.loads((run/'evidence/experiment_provenance.json').read_text()); checks=[]
 def ck(value,reason):
  if not value:raise AssertionError(reason)
  checks.append(reason)
 ck(sha(pe,'md5')==prov['retail_exe_md5']=='a640ea0097dbb62e0c77b7f2847c7161','retail exe MD5')
 ck(sha(pe)==prov['retail_exe_sha256']=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3','retail exe SHA')
 ck(sha(zfs)==prov['retail_zfs_sha256']=='0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d','retail ZFS SHA')
 ck(sha(gzf)==prov['ghidra_v97_sha256']=='b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce','private GZF SHA')
 ck(sha(a)==sha(b)==prov['native_first_private_trace_sha256']==prov['native_second_private_trace_sha256'],'replay traces identical')
 ck(sha(run/'scripts/I76_VisibilityQueueNativeProbe.java')==prov['native_probe_source_sha256'],'script identity')
 pe_bytes=pe.read_bytes();anchors=tsv(run/'evidence/native_opcode_anchors.tsv')
 ck(len(anchors)==18,'18 original executable instruction anchors')
 for row in anchors:
  v=int(row['retail_va'],16);expected=bytes.fromhex(row['original_pe_5bytes']);off=pe_map(pe_bytes,v)
  ck(pe_bytes[off:off+len(expected)]==expected,'PE opcode at '+hex(v))
 table=tsv(run/'evidence/producer_scenarios.tsv')
 ck(len(table)==4,'four producer scenarios')
 expected={(veh,acc) for veh in ('gtsi','bus') for acc in ('true','false')}
 ck({(r['vehicle'],r['accepted']) for r in table}==expected,'scenario keys')
 for row in table:
  yes=row['accepted']=='true'
  for key,want in {'classifier_eax':'FFFFFFFF' if yes else '00000001','allocations':'1' if yes else '0','bin_calls':'1' if yes else '0','bucket':'1' if yes else 'none','records':'1' if yes else '0','stride_bytes':'68' if yes else '0','consumer_secondary':'1' if yes else '0','consumer_primary':'0','consumer_submit':'0','drained':'0'}.items():
   ck(row[key]==want,f"{row['vehicle']} {yes}: {key}")
 trace=tsv(a)
 by={v:[x for x in trace if x['scenario']==v+'_top_level_vcf'] for v in ('gtsi','bus')}
 for veh,events in by.items():
  kinds=[x['kind'] for x in events]
  for kind,n in [('PRODUCER_NATIVE_VISIBILITY_ENTER',2),('PRODUCER_NATIVE_VISIBILITY_RESULT',2),('PRODUCER_NATIVE_RECORD_ALLOC_ENTER',1),('PRODUCER_NATIVE_BIN_ENTER',1),('PRODUCER_BUCKET',1),('ORIGINAL_PRODUCER_RECORD',1),('NATIVE_PRODUCER_CONSUMER_END',1)]:ck(kinds.count(kind)==n,veh+': '+kind)
  results=[fields(x['detail'])['eax'] for x in events if x['kind']=='PRODUCER_NATIVE_VISIBILITY_RESULT']
  ck(results==['FFFFFFFF','00000001'],veh+': classifier return statuses')
  records=[fields(x['detail']) for x in events if x['kind']=='ORIGINAL_PRODUCER_RECORD']
  ck(len(records)==1 and records[0]['type']=='6' and records[0]['activeEntry']=='00542830' and records[0]['owner']=='27000E00' and records[0]['dispatchMode']=='0',veh+': original work record pointers')
  dispatch=[fields(x['detail']) for x in events if x['kind']=='NATIVE_PRODUCER_CONSUMER_END']
  ck(len(dispatch)==1 and dispatch[0]['secondaryPasses']=='1' and dispatch[0]['primaryPasses']=='0' and dispatch[0]['submissions']=='0',veh+': real secondary traversal no submissions')
 return {'status':'passed','test_count':len(checks),'passed_count':len(checks),'original_code_producer_scenarios':4,'native_visibility_executions':4,'real_original_bucket_inserts':2,'real_original_bucket_dispatches':2,'original_pixel_submissions_this_phase':0}
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('run',type=Path)
 for name in ('pe','zfs','gzf','trace','repeat'):p.add_argument('--'+name,required=True,type=Path)
 a=p.parse_args();print(json.dumps(verify(a.run,a.pe,a.zfs,a.gzf,a.trace,a.repeat),indent=2))
