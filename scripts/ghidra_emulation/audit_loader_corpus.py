#!/usr/bin/env python3
"""Read-only static BWD2/ADEF/FSM structural inspector. Does NOT emulate retail parser."""
import argparse, csv, hashlib, json, struct
from pathlib import Path
from collections import Counter
U32=lambda b,p: struct.unpack_from('<I',b,p)[0]

def chunks(b, start, end):
    result=[]; offset=start
    if not (0<=start<=end<=len(b)): raise ValueError('invalid enclosing bounds')
    while offset<end:
        if offset+8>end: raise ValueError('truncated eight-byte chunk header')
        tag=b[offset:offset+4]; size=U32(b,offset+4)
        if size<8: raise ValueError('chunk length less than header')
        if offset+size>end: raise ValueError('chunk length exceeds parent')
        result.append((tag,offset,size));offset+=size
    return result

def validate_blob(b):
    root=chunks(b,0,len(b));tags=[t[0] for t in root]
    if tags!=[b'BWD2',b'REV\0',b'WDEF',b'TDEF',b'RDEF',b'ODEF',b'LDEF',b'ADEF',b'EXIT']:
        raise ValueError('not the exact known-stock outer tag sequence')
    if root[0][2]!=8: raise ValueError('unexpected BWD2 marker length')
    if root[1][2]<12:raise ValueError('short revision record')
    if U32(b,root[1][1]+8)!=2:raise ValueError('different outer revision')
    expected_revisions={b'WDEF':(b'WREV',9),b'TDEF':(b'TREV',4),b'RDEF':(b'RREV',1),b'ODEF':(b'OREV',3),b'LDEF':(b'LREV',1),b'ADEF':(b'AREV',1)}
    section_revisions=[]
    for sect in root:
        if sect[0] not in expected_revisions:continue
        records=chunks(b,sect[1]+8,sect[1]+sect[2]);expected=expected_revisions[sect[0]]
        if not records or records[0][0]!=expected[0] or records[0][2]<12 or U32(b,records[0][1]+8)!=expected[1]:
            raise ValueError('section revision mismatch: '+repr(sect[0]))
        section_revisions.append(sect[0].decode('ascii')+':'+str(expected[1]))
    adef=next(r for r in root if r[0]==b'ADEF');nested=chunks(b,adef[1]+8,adef[1]+adef[2]);child_tags=[c[0] for c in nested]
    if child_tags!=[b'AREV',b'FSM\0',b'EXIT']:raise ValueError('not the stock nested tag sequence')
    if nested[0][2]<12 or U32(b,nested[0][1]+8)!=1:raise ValueError('different ADEF revision')
    fsm=nested[1]; data=b[fsm[1]+8:fsm[1]+fsm[2]];index=0
    counts={k:0 for k in ('commands','actors','media','positions','nodes','globals','tokens')}
    names=[]
    if not data: return dict(revision=2,arev=1,**counts,outer_tags=';'.join(t.decode('latin-1').rstrip('\x00') for t in tags),section_revisions=';'.join(section_revisions),fsm_size=fsm[2],tokens_sha256=hashlib.sha256(b'').hexdigest())
    def take(count):
        nonlocal index
        if count<0 or index+count>len(data): raise ValueError('FSM table exceeds declared payload')
        val=data[index:index+count];index+=count;return val
    def word(): return U32(take(4),0)
    counts['commands']=word(); raw=take(counts['commands']*40)
    for j in range(counts['commands']):names.append(raw[j*40:j*40+40].split(b'\0')[0].decode('latin-1'))
    counts['actors']=word();take(counts['actors']*48)
    counts['media']=word();take(counts['media']*40)
    counts['positions']=word()
    for _ in range(counts['positions']):take(40);take(word()*12)
    counts['nodes']=word();take(counts['nodes']*168)
    counts['globals']=word();take(counts['globals']*4)
    counts['tokens']=word();token=take(counts['tokens']*8)
    if index!=len(data):raise ValueError('trailing bytes in FSM payload')
    return dict(revision=2,arev=1,**counts,outer_tags=';'.join(t.decode('latin-1').rstrip('\x00') for t in tags),section_revisions=';'.join(section_revisions),fsm_size=fsm[2],tokens_sha256=hashlib.sha256(token).hexdigest(),command_lexicon_sha256=hashlib.sha256('\0'.join(names).encode('latin-1')).hexdigest())

def main():
    p=argparse.ArgumentParser();p.add_argument('--corpus',type=Path,required=True,help='Parent containing miss8 and miss16 dirs, or game root');p.add_argument('--output',type=Path,required=True)
    args=p.parse_args();args.output.mkdir(parents=True,exist_ok=True)
    rows=[];problems=[];counts=Counter();lexica=set();variant_map={}
    for variant in ('miss8','miss16'):
        files=sorted((args.corpus/variant).glob('*.MSN'))
        for f in files:
            try:
                b=f.read_bytes(); val=validate_blob(b);val.update(variant=variant,filename=f.name,file_size=len(b),file_sha256=hashlib.sha256(b).hexdigest());rows.append(val)
                counts[variant+'_files']+=1
                counts[variant+'_nonempty' if val['fsm_size']>8 else variant+'_empty']+=1
                counts[variant+'_tokens']+=val['tokens'];counts[variant+'_nodes']+=val['nodes']
                if val.get('command_lexicon_sha256'): lexica.add(val['command_lexicon_sha256'])
                variant_map[(variant,f.name)]=val
            except Exception as e:problems.append(dict(variant=variant,file=f.name,reason=str(e)))
    # Non-executing synthetic cases: only the stricter Python inspector is exercised.
    source=next((args.corpus/'miss8').glob('*.MSN')).read_bytes()
    tests=[]
    def probe(name,data,expect):
        try:validate_blob(bytes(data));actual='accepted_by_inspector'
        except Exception as e:actual='rejected_by_inspector: '+str(e)
        tests.append(dict(case=name,expectation=expect,observed=actual,retail_engine_executed=False))
    probe('unchanged_stock_file',source,'accepted_by_inspector')
    corrupted=bytearray(source);corrupted[0:4]=b'XXXX';probe('unknown_root_tag',corrupted,'rejected_by_inspector')
    probe('truncated_terminal_header',source[:-4],'rejected_by_inspector')
    corrupted=bytearray(source);corrupted[4:8]=struct.pack('<I',4);probe('short_bwd2_marker',corrupted,'rejected_by_inspector')
    corrupted=bytearray(source);corrupted[4:8]=struct.pack('<I',len(corrupted)+1024);probe('outer_chunk_overflow',corrupted,'rejected_by_inspector')
    corrupted=bytearray(source); root=chunks(corrupted,0,len(corrupted));rev=root[1][1];corrupted[rev+8:rev+12]=struct.pack('<I',3);probe('root_wrong_revision',corrupted,'rejected_by_inspector')
    def matched(a,b):return sum(variant_map[('miss8',n)][a]==variant_map[('miss16',n)][b] for n in set(n for v,n in variant_map if v=='miss8') & set(n for v,n in variant_map if v=='miss16'))
    summary=dict(files=len(rows),parsing_errors=problems,counts=dict(counts),lexicon_hash_count=len(lexica),paired_missions=len(set(n for v,n in variant_map if v=='miss8')&set(n for v,n in variant_map if v=='miss16')),paired_matching_tokens_sha256=matched('tokens_sha256','tokens_sha256'),synthetic_probe_scope='Independent Python structural inspector, NOT retail-engine behavior')
    fields=['variant','filename','file_size','revision','arev','fsm_size','commands','actors','media','positions','nodes','globals','tokens','outer_tags','section_revisions','command_lexicon_sha256','tokens_sha256','file_sha256']
    with (args.output/'CORPUS_LOADER_INVENTORY.tsv').open('w') as h:
        writer=csv.DictWriter(h,fieldnames=fields,delimiter='\t',extrasaction='ignore');writer.writeheader();writer.writerows(rows)
    (args.output/'CORPUS_STATIC_VALIDATION.json').write_text(json.dumps(summary,indent=2)+'\n')
    (args.output/'INSPECTOR_ONLY_MUTATION_PROBES.json').write_text(json.dumps(tests,indent=2)+'\n')
    assert summary['files']==80 and not problems and counts['miss8_nonempty']==25 and counts['miss16_nonempty']==25 and counts['miss8_empty']==15 and counts['miss16_empty']==15 and len(lexica)==1 and summary['paired_matching_tokens_sha256']==40
    print(json.dumps(summary,indent=2))
if __name__=='__main__': main()
