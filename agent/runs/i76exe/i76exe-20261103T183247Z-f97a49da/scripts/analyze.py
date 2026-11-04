#!/usr/bin/env python3
"""Derive bounded tables and factual validation from PRIVATE captures.
Hypotheses are a reviewed input, never an automatic clustering result.
"""
import argparse,collections,csv,hashlib,itertools,json,pathlib,struct
p=argparse.ArgumentParser();p.add_argument('--private',required=True);p.add_argument('--exe',required=True);p.add_argument('--gzf',required=True);p.add_argument('--evidence',required=True);a=p.parse_args()
w=pathlib.Path(a.private);out=pathlib.Path(a.evidence);out.mkdir(exist_ok=True)
sha=lambda b:hashlib.sha256(b).hexdigest()
fs=[json.loads(x) for x in (w/'capture1/inventory.jsonl').read_text().splitlines()];idx={f['entry']:f for f in fs}
detail={x['address']:x for x in map(json.loads,(w/'capture1/detail.jsonl').read_text().splitlines())}
h=json.loads((out/'hypotheses.json').read_text());groups={g['id']:set(g['members']) for g in h['groups']};assignment={e:g for g,es in groups.items() for e in es}
ranges=[(0x4927b0,0x493bd0),(0x410490,0x4149f0),(0x46fee0,0x470b20),(0x4b2e00,0x4b3030)]
bounded=[f for f in fs if any(lo<=int(f['entry'],16)<=hi for lo,hi in ranges)];bs={f['entry'] for f in bounded}
assert len(bs)==42 and len(assignment)==41 and set(assignment)<bs
states='004fad20 004fad24 006442c0 006442c4 006442d4 006442ec 006442f4 00644380 005a4620 005a4628 005a4768 005a6068 005244d0 005244d4 005244dc 005244e0 005244e4 0058d908 0058d90c 0058d91c 0058d920 0058d924 0058d928 00609560 00609564 00609580 00609584 0060958c 00609590 00609594 005dacc8 005daccc 005db990 006593e8 006564e0 00669ee4'.split()
uses=collections.defaultdict(set);writers=collections.defaultdict(set);access=collections.defaultdict(lambda:collections.defaultdict(set))
for f in fs:
 for r in f['refs']:
  if r['to'] in states and not r['flow']:
   uses[r['to']].add(f['entry']);access[r['to']][f['entry']].add('W' if r['write'] else 'R' if r['read'] else 'A')
   if r['write']:writers[r['to']].add(f['entry'])
def table(name,cols,rows):
 with (out/name).open('w',newline='') as f:
  t=csv.writer(f,delimiter='\t',lineterminator='\n');t.writerow(cols);t.writerows([["-" if x is None or x=="" else x for x in row] for row in rows])
def state_set(es):return {t for t,u in uses.items() if u&es}
def calls(es):return {(e,t) for e in es for t in idx[e]['calls']}
table('bounded_inventory.tsv',['entry','current_name','group','body_bytes','ranges','previous','next','gap_to_next','thunk_target','incoming_call_owners','incoming_noncall_count','indirect_pcs','selected_state_targets','string_reference_targets'],[
 [f['entry'],f['name'],assignment.get(f['entry'],'UNKNOWN'),f['size'],';'.join(r['start']+'-'+r['end'] for r in f['ranges']),f.get('previous'),f.get('next'),f.get('gap_to_next'),f.get('thunk_target',''),','.join(sorted({r.get('owner') or 'unowned@'+r['from'] for r in f['incoming'] if r['call']})),sum(not r['call'] for r in f['incoming']),','.join(i['address']+':'+i['type'] for i in f['indirect']),','.join(sorted(state_set({f['entry']}))),','.join(sorted({r['to'] for r in f['refs'] if r.get('string')}))] for f in bounded])
table('membership.tsv',['group','confidence','entry','current_name','original_filename'],[[g['id'],g['confidence'],e,idx[e]['name'],'UNVERIFIED'] for g in h['groups'] for e in g['members']]+[['UNKNOWN','UNKNOWN','00493150',idx['00493150']['name'],'UNVERIFIED']])
table('function_ranges.tsv',['entry','start','end','bytes','sha256'],[[f['entry'],r['start'],r['end'],r['bytes'],r['sha256']] for f in bounded for r in f['ranges']])
table('direct_calls.tsv',['caller','callsite','callee','caller_group','callee_group'],[[f['entry'],r['from'],r['to'],assignment[f['entry']],assignment.get(r['to'],'outside-or-unassigned')] for f in bounded if f['entry'] in assignment for r in f['refs'] if r['call'] and not r['type'].startswith('COMPUTED')])
table('state_ownership.tsv',['target','whole_program_users','whole_program_writers','users_and_access','bounded_groups','qualifier'],[[t,len(uses[t]),','.join(sorted(writers[t])), ';'.join(e+':'+''.join(sorted(access[t][e])) for e in sorted(uses[t])),','.join(sorted({assignment[e] for e in uses[t] if e in assignment})),'Exact referenced address; A includes indexed accesses that Ghidra labels DATA; not source-level linkage'] for t in states])
table('group_connectivity.tsv',['group','members','internal_direct_edges','outgoing_direct_edges','incoming_direct_edges','selected_state_targets','targets_shared_by_members','targets_exclusive_to_members'],[[g,len(es),sum(t in es for e,t in calls(es)),sum(t not in es for e,t in calls(es)),sum(t in es and f['entry'] not in es for f in fs for t in f['calls']),len(state_set(es)),sum(len(uses[t]&es)>=2 for t in state_set(es)),sum(uses[t]<=es for t in state_set(es))] for g,es in groups.items()])
table('cross_group.tsv',['group_a','group_b','a_to_b_direct_edges','b_to_a_direct_edges','shared_selected_state_targets'],[[ga,gb,sum(t in eb for e,t in calls(ea)),sum(t in ea for e,t in calls(eb)),','.join(sorted(state_set(ea)&state_set(eb)))] for (ga,ea),(gb,eb) in itertools.combinations(groups.items(),2) if any(t in eb for e,t in calls(ea)) or any(t in ea for e,t in calls(eb)) or state_set(ea)&state_set(eb)])
table('boundaries.tsv',['id','left','left_name','right','right_name','left_end','gap_bytes','confidence','decision'],[[x['id'],x['left'],idx[x['left']]['name'],x['right'],idx[x['right']]['name'],idx[x['left']]['ranges'][-1]['end'],idx[x['left']]['gap_to_next'],x['confidence'],x['decision']] for x in h['boundaries']])
# Raw pointer occurrences: these are potential references, distinct from Ghidra xrefs.
pe=json.loads((w/'pe.json').read_text());b=pathlib.Path(a.exe).read_bytes()
def raw(v,n):
 for s in pe['sections']:
  if 0x400000+s['rva']<=v and v+n<=0x400000+s['rva']+s['rawsize']:
   o=s['raw']+v-0x400000-s['rva'];return b[o:o+n]
 raise ValueError(hex(v))
ptrs=[]
for f in bounded:
 for s in pe['sections']:
  if s['name'] not in ['.data','.rdata']:continue
  segment=b[s['raw']:s['raw']+s['rawsize']];start=0
  while True:
   n=segment.find(struct.pack('<I',int(f['entry'],16)),start)
   if n<0:break
   ptrs.append(['%08x'%(0x400000+s['rva']+n),f['entry'],f['name'],'raw-little-endian-pointer; manually checked callback table']);start=n+1
table('pointer_evidence.tsv',['storage','target','name','interpretation'],ptrs)
# A deliberately small, manually selected instruction ledger.
checks=[
 ('P01','positive','00410490','reader base/cursor accesses bind imported-node reader to adjacent reader helpers'),
 ('P01','positive','00410738','reader base initialized by table importer'),
 ('P01','positive','0041092e','table importer calls execution-node reader'),
 ('P02','positive','00414949','interpreter calls host dispatcher'),
 ('P02','positive','004136ed','host dispatcher writes deadline read by scheduler'),
 ('P02','positive','004149fb','scheduler reads same deadline cell'),
 ('P02','positive','00414a58','scheduler calls interpreter'),
 ('P03','positive','004703e8','texture wrapper writes shared scratch name buffer'),
 ('P03','positive','004704e8','second texture wrapper writes same buffer'),
 ('P03','positive','004705c8','release wrapper writes same buffer'),
 ('P04','positive','0047089b','PIX initialization installs member-table pointer'),
 ('P04','positive','00470b25','PIX lookup reads installed member-table pointer'),
 ('P05','positive','00493942','loader passes descriptor table containing original callback pointers'),
 ('P05','positive','00493986','ZMAP callback writes zone count read by ZONE callback'),
 ('P05','positive','00493b9d','ZONE callback reads zone count'),
 ('P06','positive','004930fb','grid setup writes reciprocal consumed by material and normal samplers'),
 ('P06','positive','004927b3','material sampler reads reciprocal'),
 ('P06','positive','004931c3','normal sampler reads reciprocal'),
 ('B01','boundary','00493839','map helper reads render/mesh count 006442ec'),
 ('B01','boundary','00493927','adjacent loader instead clears page source storage 005a4628'),
 ('B06','boundary','00412aa0','AI callback selected through tactics table at 004c3e54'),
 ('B06','boundary','00412cc0','next function resets VM budget latch at 005244dc'),
 ('B09','boundary','0047036b','membership API delegates PIX route'),
 ('B09','boundary','00470385','membership API delegates registered-source route'),
 ('B09','boundary','004703e0','following texture wrapper selects distinct scratch buffer'),
 ('B10','boundary','00470644','last texture wrapper calls texture release service'),
 ('B10','boundary','00470677','following PIX initializer writes distinct retained-package array pointer'),
 ('N01','negative','00493150','five-byte jump targets loader cleanup outside sampler neighborhood'),
 ('N02','negative','00470b66','PIX lookup calls loaded cache; dependency alone cannot merge owners'),
 ('N03','negative','00412d09','large apparent function gap contains host switch table'),
 ('N04','negative','0047032f','historically named key canonicalizer calls cache eviction'),
 ('N05','negative','00470cae','shared comparator examines key words; it owns no distinctive mutable state'),
 ('N06','negative','004b3014','small bool wrapper calls registered payload reader, despite external incoming cache caller'),
 ('B02','rejected-boundary','0049294b','visibility-only math helper calls common math service; functional separation is insufficient'),
 ('B02','rejected-boundary','004930e1','following grid initializer also feeds map-level render state')]
table('instruction_evidence.tsv',['check_id','category','function','instruction_va','instruction','reference_relationships','interpretation'],[[id,cat,detail[pc]['function'],pc,detail[pc]['instruction'],';'.join(r['to']+':'+r['type'] for r in detail[pc]['refs'] if not r['to'].startswith('Stack')),note] for id,cat,pc,note in checks])
# Configuration and literal references are deliberately distinct from mutable-state counts.
table('table_references.tsv',['function','instruction_va','target','reference_type','instruction'],[[x['function'],x['address'],r['to'],r['type'],x['instruction']] for x in detail.values() if x['function'] in ['00412630','00412680','00412830'] for r in x['refs'] if r.get('block')=='.data' and not r.get('string') and '004c3e50'<=r['to']<='004d86e4'])
literal_targets={'004fae58','004fae90','004faeb8','004faeb0','004c2e5c','004c3394','004c33b4','004c33d0','004c33e8','004c3404','004f8afc','004f8b94','004fff18','004fffe8','004fae18'}
table('literal_evidence.tsv',['function','instruction_va','target','annotated_string','qualification'],[[f['entry'],r['from'],r['to'],r.get('string',''),'Annotated literal, not an original source filename; pooling/extent can affect text'] for f in bounded for r in f['refs'] if r['to'] in literal_targets and r.get('string')])

# Factual validations, explicitly separate from TU inference.
valid=[]
def check(name,ok,notes):valid.append(dict(check=name,passed=bool(ok),notes=notes))
check('retail_sha256',sha(b)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3',sha(b))
check('gzf_sha256',sha(pathlib.Path(a.gzf).read_bytes())=='f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0',sha(pathlib.Path(a.gzf).read_bytes()))
meta=json.loads((w/'capture1/metadata.json').read_text())
check('defined_and_external_counts',meta['defined_functions']==2102 and meta['external_functions']==235,str(meta))
check('bounded_coverage',len(bs)==42 and len(assignment)==41,'42 included, 41 provisionally assigned, one UNKNOWN forwarding thunk')
for f in bounded:
 check('entry_'+f['entry'],f['entry'] in detail and detail[f['entry']]['function']==f['entry'],'Ghidra defined entry and first decoded instruction; no proof of original source symbol')
 for r in f['ranges']:
  x=raw(int(r['start'],16),r['bytes']);check('body_'+r['start'],sha(x)==r['sha256'],r['end']+' '+r['sha256'])
for e in json.loads((w/'envelopes.json').read_text())['envelopes']:
 check('envelope_'+e['start'],sha(raw(int(e['start'],16),int(e['end'],16)-int(e['start'],16)+1))==e['sha256'],e['end']+' '+e['sha256'])
for n in ['inventory.jsonl','detail.jsonl','metadata.json']:
 check('repeat_'+n,(w/'capture1'/n).read_bytes()==(w/'capture2'/n).read_bytes(),sha((w/'capture1'/n).read_bytes()))
check('modification_counter',meta['modification_before']==meta['modification_after'],'3 -> 3; same for envelope audit')
before=json.loads((w/'db-before.json').read_text());project=w/'project';after={str(x.relative_to(project)):sha(x.read_bytes()) for x in sorted(project.rglob('*')) if x.is_file() and x.suffix!='.lock'}
program_files=[k for k in before if k.endswith('.gbf')]
check('program_database_pages_unchanged',program_files and all(before[k]==after.get(k) for k in program_files),';'.join(k+':'+before[k] for k in program_files))
housekeeping=[k for k in before.keys()|after.keys() if before.get(k)!=after.get(k)]
check('manual_instruction_checks',all(pc in detail for _,_,pc,_ in checks),'Reviewed ledger: 6 positive relationships, 4 separation pairs, 6 negative qualifications; checks establish instruction/reference facts only')
check('callback_pointer_values',[(x[0],x[1]) for x in ptrs]==[('004fae30','00493960'),('004fae40','004939d0'),('004fae50','00493bd0')],'Original PE pointer values; descriptor tags ZMAP, ZONE, EXIT manually checked; TREV descriptor calls external 004b4610')
res=dict(method='binary-static',defined_functions=2102,external_functions=235,bounded_functions=len(bs),assigned=len(assignment),unassigned=1,candidates=len(groups),tests=valid,test_count=len(valid),passed_count=sum(t['passed'] for t in valid),private_capture_digests={n:sha((w/'capture1'/n).read_bytes()) for n in ['inventory.jsonl','detail.jsonl','metadata.json']},project_housekeeping_changes=sorted(housekeeping),limitations='No source ground truth; passed factual checks do not validate TU boundaries. Program .gbf unchanged; project backup indexes/journal may be maintained even in read-only processing.')
(out/'validation_results.json').write_text(json.dumps(res,indent=2)+'\n')
# Publish compact PE metadata only, excluding the bulk list of game asset names.
summary={k:v for k,v in pe.items() if k!='source_like_strings'}
summary['source_like_ascii_count']=len(pe['source_like_strings']);summary['non_map_ascii_matches']=[x for x in pe['source_like_strings'] if not x['text'].lower().endswith('.map')];summary['private_provenance_capture_sha256']=sha((w/'pe.json').read_bytes())
(out/'pe_provenance.json').write_text(json.dumps(summary,indent=2)+'\n')
print(json.dumps({k:res[k] for k in ['bounded_functions','assigned','unassigned','candidates','test_count','passed_count']},indent=2))
assert res['test_count']==res['passed_count']
