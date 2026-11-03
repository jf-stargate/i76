#!/usr/bin/env python3
"""Validate private captures. Outputs reviewed counts/digests, never raw C/inventories."""
import argparse,csv,hashlib,json,re,struct
from pathlib import Path
ap=argparse.ArgumentParser();ap.add_argument('--captures',type=Path,required=True);ap.add_argument('--pe',type=Path,required=True);ap.add_argument('--gzf',type=Path,required=True);ap.add_argument('--output',type=Path,required=True);a=ap.parse_args();p=a.captures
checks=[]
def check(name,yes,detail=None):
 checks.append({'name':name,'passed':bool(yes),'detail':detail});assert yes,(name,detail)
def sha(b):return hashlib.sha256(b).hexdigest()
def tab(phase,name):return list(csv.DictReader((p/phase/name).open(),delimiter='\t'))
def same(x,y):
 fs={f.name for f in (p/x).iterdir()};gs={f.name for f in (p/y).iterdir()}
 check(f'complete capture equality {x}/{y}',fs==gs and all((p/x/n).read_bytes()==(p/y/n).read_bytes() for n in fs),len(fs))
pe=a.pe.read_bytes();check('retail SHA256',sha(pe)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3');check('selected GZF identity',sha(a.gzf.read_bytes())=='ca211238170806eda27a2b4ecf6aee2192abb69df27fe56f106b455ac75bc710' and a.gzf.stat().st_size==6500304)
ph=struct.unpack_from('<I',pe,0x3c)[0];ns=struct.unpack_from('<H',pe,ph+6)[0];op=struct.unpack_from('<H',pe,ph+20)[0];sects=[struct.unpack_from('<IIII',pe,ph+24+op+i*40+8) for i in range(ns)]
def raw(va,n):
 rva=va-0x400000
 for vs,v,sz,off in sects:
  if v<=rva and rva+n<=v+sz:return pe[off+rva-v:off+rva-v+n]
 raise ValueError(hex(va))
before={r['address']:r for r in tab('before','functions.tsv')}
for phase in ['before','terrain','approved-v100','final-v101','final-v102','final-repeat','one-shot','one-shot-repeat']:
 rows=tab(phase,'functions.tsv');check('2102 original function ranges and retail bytes '+phase,len(rows)==2102 and all(sha(b''.join(raw(int(lo,16),int(hi,16)-int(lo,16)+1) for lo,hi in re.findall(r'\[([0-9a-f]+), ([0-9a-f]+)\]',r['body'])))==r['bytes_sha256'] and r['body']==before[r['address']]['body'] for r in rows))
for x,y in [('before','terrain-preview'),('terrain','terrain-repeat'),('before','final-rollback'),('before','final-preview'),('final-v101','v102-preview'),('final-v102','final-repeat'),('one-shot','one-shot-repeat'),('one-shot','final-v102')]:same(x,y)
end={r['address']:r for r in tab('final-v102','functions.tsv')}
changed=[va for va,r in before.items() if r['signature']!=end[va]['signature']]
check('exact reviewed signature set',set(changed)==set(['00490a00','004929b0','0048fac0','0047cb00','00491810','0045ebd0','00461970','00463120','00463800','00463950','0045f0f0','0045ef70','004572b0','0049c320','0049c360','00457420','00409850','00462040','00463a80','0046f2b0','0045f810','0046dfe0']),changed)
for va in ['004931c0','00493550','00410490','00412500','00414670','004149f0','00412ce0','0046ffc0','00470070','00470340','00470b20','004b2e00','004b3030']:
 check('protected ABI '+va,before[va]['signature']==end[va]['signature'])
for va in ['00457ff0','00474c60','00472c10','00409980']:check('deferred parameter unchanged '+va,before[va]['signature']==end[va]['signature'])
for name in ['external_functions.tsv','components.tsv']:
 old=(p/'before'/name).read_text().splitlines();new=set((p/'final-v102'/name).read_text().splitlines());check('all old '+name+' rows preserved',all(r in new for r in old))
oldtypes=(p/'before/types.tsv').read_text().splitlines();newtypes=set((p/'final-v102/types.tsv').read_text().splitlines());check('all preexisting datatype entries preserved',set(oldtypes)<=newtypes,len(oldtypes))
oldcomments=(p/'before/comments.tsv').read_text().splitlines();newcomments={r.split('\t',2)[0]+'\t'+r.split('\t',2)[1]:r.split('\t',2)[2] for r in (p/'final-v102/comments.tsv').read_text().splitlines()};check('all analyst comment text preserved',all(r.split('\t',2)[2] in newcomments.get('\t'.join(r.split('\t',2)[:2]),'') for r in oldcomments),len(oldcomments))
oldsyms={r for r in (p/'before/symbols.tsv').read_text().splitlines() if '\tUSER_DEFINED\t' in r};newsyms=set((p/'final-v102/symbols.tsv').read_text().splitlines());lost=sorted(oldsyms-newsyms);check('analyst symbols except reviewed resolver alias preserved',len(lost)==1 and lost[0].startswith('0045f0f0\trelease_world_object_tree_reference\t'),lost)
refs=lambda ph:set((p/ph/'references.tsv').read_text().splitlines())
table=lambda rs:{r for r in rs if 0x4f76e0<=int(r.split('\t')[0],16)<=0x4f7c5b}
oldrefs=table(refs('before'));newrefs=table(refs('final-v102'));check('exact table references retained',oldrefs<=newrefs,{'before':len(oldrefs),'after':len(newrefs)})
check('113 original nonzero callback values',sum(struct.unpack_from('<I',raw(0x4f76e0,0x57c),i)[0]!=0 for i in range(0,0x57c,4) if i%0x34)==113 and len(newrefs)==113)
olddata={r['address']:r for r in tab('before','data.tsv')};newdata={r['address']:r for r in tab('final-v102','data.tsv')};datadelta={v for v in olddata.keys()|newdata.keys() if olddata.get(v)!=newdata.get(v)}
allowed=lambda v:0x4f76e0<=int(v,16)<=0x4f7c5b or v in ['006442c0','004ed7ec','0054b204','0054b208','0054b20c','0054b210']
check('data changes confined to reviewed locations',all(allowed(v) for v in datadelta),len(datadelta))
check('descriptor 27 rows extent',newdata['004f76e0']['length']=='1404' and newdata['004f76e0']['type'].endswith('I76_ClassDescriptor_0x34[27]'))
# Counts apply only to fixed sample; digest changes do not imply improvements.
metrics={}
for x,y in [('before','terrain'),('terrain','approved-v100'),('approved-v100','final-v101'),('final-v101','final-v102'),('before','final-v102')]:
 names=sorted(f.name for f in (p/x).glob('*.c'));check('same 419 C sample '+y,len(names)==419 and set(names)=={f.name for f in (p/y).glob('*.c')})
 changedc=[n[:-2] for n in names if (p/x/n).read_bytes()!=(p/y/n).read_bytes()]
 metrics[x+'/'+y]={'sample':419,'changed':len(changedc),'unchanged':419-len(changedc),'changed_addresses':changedc,'arrow_fields_before':sum(len(re.findall(r'->\w+', (p/x/n).read_text())) for n in names),'arrow_fields_after':sum(len(re.findall(r'->\w+', (p/y/n).read_text())) for n in names)}
log=(p/'final-tests.log').read_text();cases=re.findall(r'NEGATIVE PASS (\w+)',log);check('ten negative cases passed',set(cases)==set(['type','prerequisite','bytes','boundary','identity','tablebytes','overlap','signature','label','rollback']),cases);check('clean final test log','ERROR' not in log)
check('default preview expected summary','mode=PREVIEW phase=ALL eligible=54 applied=0 already=0 preserved=0 conflicted=0 deferred=4 committed=false' in log)
check('one-shot successful apply','mode=APPLY phase=ALL eligible=54 applied=54 already=0 preserved=0 conflicted=0 deferred=4 committed=true' in log)
check('zero-edit repeat','mode=APPLY phase=ALL eligible=0 applied=0 already=54 preserved=0 conflicted=0 deferred=4 committed=true' in log)
indexes={}
for phase in ['before','terrain-preview','terrain','terrain-repeat','approved-v100','final-v101','v102-preview','final-v102','final-repeat','final-rollback','final-preview','one-shot','one-shot-repeat']:
 entries=[f'{f.name}\t{f.stat().st_size}\t{sha(f.read_bytes())}\n' for f in sorted((p/phase).iterdir())];indexes[phase]={'files':len(entries),'index_sha256':sha(''.join(entries).encode()),'tables':{f.name:{'sha256':sha(f.read_bytes()),'bytes':f.stat().st_size} for f in sorted((p/phase).glob('*.tsv'))}}
result={'status':'passed','test_count':len(checks),'passed_count':len(checks),'checks':checks,'metrics':metrics,'capture_indexes':indexes,'negative_cases':cases,'changed_signatures':changed,'table_references':{'before':len(oldrefs),'after':len(newrefs)},'gui_tested':False}
a.output.write_text(json.dumps(result,indent=2)+'\n');print(json.dumps({'checks':len(checks),'metrics':{k:{i:v for i,v in val.items() if i!='changed_addresses'} for k,val in metrics.items()}}))
