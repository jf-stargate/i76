#!/usr/bin/env python3
"""Read-only audit of native I76 ODEF chunk multiplicity and registry branch anchors.

Counts serialized ODEF OBJ records, *not* instantiated or registered objects.
No mission bytes are written to the output, only aggregate structural metadata.
"""
import argparse
import csv
import hashlib
import json
import re
import struct
import subprocess
import tarfile
from collections import Counter
from pathlib import Path

MD5 = 'a640ea0097dbb62e0c77b7f2847c7161'
EXPECTED_TAGS = [b'BWD2', b'REV\x00', b'WDEF', b'TDEF', b'RDEF', b'ODEF', b'LDEF', b'ADEF', b'EXIT']

def chunks(buf, start, end, origin):
    cursor = start
    while cursor < end:
        if end-cursor < 8:
            raise ValueError(f'{origin}: truncated header at {cursor:#x}')
        tag = buf[cursor:cursor+4]
        size = struct.unpack_from('<I',buf,cursor+4)[0]
        if size < 8 or size > end-cursor:
            raise ValueError(f'{origin}: invalid {tag!r} size {size} at {cursor:#x}, remaining {end-cursor}')
        yield (tag,cursor,size)
        cursor += size
    if cursor != end: raise AssertionError('unfinished chunk walk')

def audit_bytes(name, b):
    top=list(chunks(b,0,len(b),name))
    tags=[t for t,_,_ in top]
    if tags!=EXPECTED_TAGS:raise ValueError(f'{name}: unusual outer tags {tags!r}')
    _, off, size = top[5]
    nested=list(chunks(b,off+8,off+size,name+'/ODEF'))
    n_tags=[t for t,_,_ in nested]
    if n_tags[0]!=b'OREV' or n_tags[-1]!=b'EXIT':
        raise ValueError(f'{name}: ODEF has unexpected bounds')
    obj=[(p,s) for t,p,s in nested if t==b'OBJ\x00']
    unusual=[(t.decode('ascii','backslashreplace'),s) for t,p,s in nested if t not in [b'OBJ\x00',b'OREV',b'EXIT']]
    if unusual:raise ValueError(f'{name}: unexpected ODEF tags {unusual!r}')
    obj_sizes=Counter(s for _,s in obj)
    if set(obj_sizes)!={108} or size != 28 + 108*len(obj):
        raise ValueError(f'{name}: ODEF length does not match OREV + fixed OBJ + EXIT layout')
    return {'file':name.split('interstate 76/',1)[1], 'bytes':len(b), 'odef_bytes':size,
            'odef_obj_records':len(obj), 'odef_obj_size_modes':';'.join(f'{s}:{n}' for s,n in sorted(obj_sizes.items())),
            'sha256':hashlib.sha256(b).hexdigest()}

def native_anchor_audit(exe):
    if hashlib.md5(exe.read_bytes()).hexdigest()!=MD5:raise ValueError('retail executable MD5 differs')
    dis=subprocess.check_output(['objdump','-D','-Mintel','-b','pei-i386','-m','i386',
        '--start-address=0x4ad410','--stop-address=0x4ad640',str(exe)],text=True)
    anchors={
        'reserve_bytes_0x8000': (r'4ad421:\s+68 00 80 00 00\s+push\s+0x8000'),
        'capacity_2048': (r'4ad43b:\s+c7 46 0c 00 08 00 00\s+mov\s+DWORD PTR \[esi\+0xc\],0x800'),
        'count_zero': (r'4ad442:\s+c7 46 08 00 00 00 00\s+mov\s+DWORD PTR \[esi\+0x8\],0x0'),
        'full_branch': (r'4ad461:\s+3b c1\s+cmp\s+eax,ecx'),
        'capacity_fastpath': (r'4ad463:\s+7c 42\s+jl\s+0x4ad4a7'),
        'heap_realloc_call': (r'4ad481:\s+ff 15 e4 c0 4b 00\s+call'),
        'realloc_nonnull_return': (r'4ad489:\s+74 0a\s+je\s+0x4ad495'),
        'null_path_table_pointer_clear': (r'4ad498:\s+c7 46 04 00 00 00 00\s+mov'),
        'append_count_increment': (r'4ad597:\s+40\s+inc\s+eax'),
        'reverse_lookup_start': (r'4ad5bc:\s+49\s+dec\s+ecx'),
    }
    result={n:bool(re.search(p,dis)) for n,p in anchors.items()}
    dis2=subprocess.check_output(['objdump','-D','-Mintel','-b','pei-i386','-m','i386',
        '--start-address=0x412400','--stop-address=0x412630',str(exe)],text=True)
    dis3=subprocess.check_output(['objdump','-D','-Mintel','-b','pei-i386','-m','i386',
        '--start-address=0x457610','--stop-address=0x457648',str(exe)],text=True)
    more={
       'actor_paired_key_0': (dis2,r'412420:\s+8b 4f 50\s+mov\s+ecx,DWORD PTR \[edi\+0x50\]'),
       'actor_paired_key_1': (dis2,r'41241d:\s+8b 47 54\s+mov\s+eax,DWORD PTR \[edi\+0x54\]'),
       'actor_lookup_wrapper_call': (dis2,r'412425:\s+e8 06 52 04 00\s+call\s+0x457630'),
       'actor_binding_write': (dis2,r'41242d:\s+89 47 58\s+mov\s+DWORD PTR \[edi\+0x58\],eax'),
       'actor_refonly_nonnul': (dis2,r'412432:\s+75 0d\s+jne\s+0x412441'),
       'actor_ref_acquire': (dis2,r'412447:\s+e8 b4 c8 04 00\s+call\s+0x45ed00'),
       'finalizer_actor_step': (dis2,r'4125eb:\s+e8 10 fe ff ff\s+call\s+0x412400'),
       'world_key_register_wrapper': (dis3,r'457624:\s+e8 27 5e 05 00\s+call\s+0x4ad450'),
       'actor_world_key_lookup_wrapper': (dis3,r'45763f:\s+e8 6c 5f 05 00\s+call\s+0x4ad5b0'),
    }
    result.update({name:bool(re.search(pattern,source)) for name,(source,pattern) in more.items()})
    if not all(result.values()):raise ValueError('native assembly anchor mismatch '+str(result))
    return result

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--game-tar',required=True,type=Path);ap.add_argument('--exe',required=True,type=Path);ap.add_argument('--out',required=True,type=Path)
    args=ap.parse_args();args.out.mkdir(parents=True,exist_ok=True)
    rows=[]
    with tarfile.open(args.game_tar,'r') as tf:
        names=sorted(m.name for m in tf.getmembers() if re.fullmatch(r'interstate 76/miss(?:8|16)/[^/]+\.MSN',m.name,re.IGNORECASE))
        if len(names)!=80:raise ValueError(f'expected 80 stock mission entries, got {len(names)}')
        for name in names:rows.append(audit_bytes(name,tf.extractfile(name).read()))
    anchors=native_anchor_audit(args.exe)
    with (args.out/'odef_counts.tsv').open('w',newline='') as f:
        w=csv.DictWriter(f,fieldnames=rows[0].keys(),delimiter='\t');w.writeheader();w.writerows(rows)
    counts=sorted([x['odef_obj_records'] for x in rows])
    variants = {}
    for x in rows:
        part, mission = x['file'].split('/',1)
        variants.setdefault(mission,{})[part] = x
    paired_count_matches = all(set(pair)=={'miss8','miss16'} and pair['miss8']['odef_obj_records']==pair['miss16']['odef_obj_records'] and pair['miss8']['odef_obj_size_modes']==pair['miss16']['odef_obj_size_modes'] for pair in variants.values())
    if not paired_count_matches or len(variants)!=40:raise ValueError('miss8/miss16 ODEF record-count mismatch')
    by_variant={variant:{'missions':sum(x['file'].startswith(variant+'/') for x in rows),
       'serialized_obj_records':sum(x['odef_obj_records'] for x in rows if x['file'].startswith(variant+'/')),
       'max_obj_records':max(x['odef_obj_records'] for x in rows if x['file'].startswith(variant+'/'))}
       for variant in ('miss8','miss16')}
    summary={'classification':'serialized ODEF chunk audit; NOT live registry occupancy',
       'program_md5':MD5,'missions':len(rows),'total_serialized_obj_records':sum(counts),
       'max_obj_records':max(counts), 'min_obj_records':min(counts),
       'max_missions':[x['file'] for x in rows if x['odef_obj_records']==max(counts)],
       'unique_obj_chunk_sizes':sorted({int(s.split(':')[0]) for x in rows for s in x['odef_obj_size_modes'].split(';')}),
       'miss8_miss16_count_matches':paired_count_matches,
       'odef_fixed_length_identity_verified':len(rows),
       'variant':by_variant,'under_2048_all_individual_missions':all(x<2048 for x in counts),
       'native_instruction_anchors':anchors,
       'limits':['Does not count non-ODEF/preloaded/dynamic object registration',
                 'Does not prove every serialized OBJ reaches insertion',
                 'Does not establish one OBJ generates one registry append',
                 'Does not model warm mission reuse or 2048 cumulative appends']}
    (args.out/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(json.dumps(summary,indent=2))
if __name__=='__main__':main()
