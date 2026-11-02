#!/usr/bin/env python3
"""Offline provenance/layout checks; optional private capture/PE validation."""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import struct

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
TARGETS = {'00493080','00493160','004927b0','004931c0','00493550',
           '00410490','00412500','00414670','004149f0','00412ce0',
           '0046ffc0','00470070','00470340','00470b20','004b2e00','004b3030',
           '00461970','00461b80','00461c80','00461d50'}
CONTROLS = {'00461970','00461b80','00461c80','00461d50'}

def rows(path):
    return list(csv.DictReader(path.open(),delimiter='\t'))

def sha(data):
    return hashlib.sha256(data).hexdigest()

def metrics(c):
    c = re.sub(r'/\*.*?\*/','',c,flags=re.S)
    return {
        'named_fields':len(re.findall(r'->(?:x|y|z|ip|token_base|frame|operand_cursor|host_cursor|workspace_words|host_words|condition|next)\b',c)),
        'anonymous_params':len(re.findall(r'\bparam_\d+\b',c)),
        'anonymous_globals':len(re.findall(r'\b_?DAT_[0-9a-fA-F]+\b',c)),
        'pointer_casts':len(re.findall(r'\([A-Za-z_][\w ]*\*+\)',c)),
        'all_casts':len(re.findall(r'\((?:u?int|u?short|u?long|float|double|char|undefined\d*|Vm\w+|TER_\w+)[\w *]*\)',c)),
        'grid_accesses':len(re.findall(r'g_runtime_terrain_page_pointer_grid\[',c)),
        'normal_result_uses':len(re.findall(r'=\s*(?:\([^;\n]*?\)\s*)?TER_SampleSurfaceNormalXZ\s*\(',c)),
    }

def check_captures(base,pe):
    original=pe.read_bytes()
    assert sha(original)=='bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
    ph=struct.unpack_from('<I',original,60)[0]
    assert original[ph:ph+4]==b'PE\0\0'
    assert struct.unpack_from('<H',original,ph+4)[0]==0x14c
    n=struct.unpack_from('<H',original,ph+6)[0]
    opt=struct.unpack_from('<H',original,ph+20)[0]
    assert struct.unpack_from('<I',original,ph+52)[0]==0x400000
    sections=[struct.unpack_from('<III',original,ph+24+opt+40*i+12) for i in range(n)]
    def pe_bytes(va,size):
        for rva,length,off in sections:
            if rva<=va-0x400000 and va-0x400000+size<=rva+length:
                start=off+va-0x400000-rva
                return original[start:start+size]
        raise AssertionError(f'Unmapped original range {va:x}')
    for name in ('functions.tsv','symbols.tsv','types.tsv','comments.tsv','instructions.tsv','decompilations.tsv'):
        assert (base/'before'/name).read_bytes()==(base/'preview'/name).read_bytes(),('preview changed',name)
        assert (base/'after'/name).read_bytes()==(base/'repeat'/name).read_bytes(),('repeat changed',name)
    before={r['address']:r for r in rows(base/'before/functions.tsv')}
    after={r['address']:r for r in rows(base/'after/functions.tsv')}
    assert len(before)==len(after)==2102 and before.keys()==after.keys()
    for address,r in before.items():
        assert (r['body'],r['bytes_sha256'])==(after[address]['body'],after[address]['bytes_sha256'])
        ranges=re.findall(r'\[([0-9a-f]+), ([0-9a-f]+)\]',r['body'])
        data=b''.join(pe_bytes(int(a,16),int(z,16)-int(a,16)+1) for a,z in ranges)
        assert data and sha(data)==r['bytes_sha256'],address
    for name in ('symbols.tsv','comments.tsv','types.tsv'):
        old=(base/'before'/name).read_text().splitlines()
        new=(base/'after'/name).read_text().splitlines()
        if name=='symbols.tsv':
            assert set(x for x in old if '\tUSER_DEFINED\t' in x)<=set(new)
        elif name=='types.tsv':
            assert set(old)<=set(new), 'Existing type changed'
        else:
            newmap={tuple(x.split('\t',2)[:2]):x.split('\t',2)[2] for x in new}
            for line in old:
                a,k,text=line.split('\t',2)
                assert newmap[(a,k)].startswith(text),('comment lost',a,k)
    out=[]
    for p in sorted((base/'before').glob('*.c')):
        a=p.stem;old=p.read_text();new=(base/'after'/p.name).read_text()
        if a in CONTROLS or a in {'00410490','00412500'}:
            assert old==new,('control/phase typing regression',a)
        r={'address':a,'changed':old!=new,'before_sha256':sha(p.read_bytes()),'after_sha256':sha((base/'after'/p.name).read_bytes())}
        for phase,c in [('before',old),('after',new)]:
            for k,v in metrics(c).items():r[phase+'_'+k]=v
        out.append(r)
    assert TARGETS<={r['address'] for r in out}
    normal=after['004931c0']['signature']
    assert '/TER_Normal3f *32|EAX:4' in normal and 'Stack[0x4]:4' in normal and 'Stack[0x8]:8' in normal and 'Stack[0x10]:8' in normal
    height=after['00493550']['signature']
    assert '|/float|ST0:10|' in height and height.count('Stack[')==2
    assert all(x not in after['00410490']['signature']+after['00412500']['signature'] for x in ('VmNode','VmToken'))
    return out

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--captures',type=Path)
    ap.add_argument('--pe',type=Path)
    ap.add_argument('--metrics-out',type=Path)
    a=ap.parse_args()
    inv=json.loads((HERE/'SEMANTIC_INVENTORY.json').read_text())
    for entity in inv['entities']:
        assert entity['disposition'] in {'APPLY','ALREADY','PRESERVE','CONFLICT','DEFER','MANUAL'}
        assert entity['evidence_tier'] in {'binary-static','inherited-migration','derived','unresolved'}
        for source in entity['sources']:
            path=ROOT/source['path']
            assert path.is_file(),path
            assert sha(path.read_bytes())==source['sha256'],path
    assert len({x['id'] for x in inv['entities']})==len(inv['entities'])
    assert TARGETS <= {x.get('address','').lower() for x in inv['entities']}
    assert len(rows(HERE/'SEMANTIC_DECISIONS.tsv'))==len(inv['entities'])
    assert TARGETS <= {r['address'] for r in rows(HERE/'code_guards.tsv')}
    print('PASS inventory dispositions, evidence classes, source paths/digests, unique IDs, target coverage')
    if a.captures:
        assert a.pe and a.metrics_out
        out=check_captures(a.captures,a.pe)
        with a.metrics_out.open('w') as f:
            w=csv.DictWriter(f,fieldnames=list(out[0]),delimiter='\t',lineterminator='\n');w.writeheader();w.writerows(out)
        print('PASS private PE mapping, all 2102 bodies, annotations/types, preview, repeat, ABI and regression controls')
        print('sample',len(out),'text changed',sum(r['changed'] for r in out))

if __name__=='__main__':
    main()
