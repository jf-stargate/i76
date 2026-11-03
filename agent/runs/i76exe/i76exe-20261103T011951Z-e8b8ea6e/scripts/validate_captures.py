#!/usr/bin/env python3
"""Validate private Ghidra captures. Output contains only reviewed digests/counts."""
import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path
import re
import struct

SHA = 'bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3'
GZF = 'ca211238170806eda27a2b4ecf6aee2192abb69df27fe56f106b455ac75bc710'
EXPECTED_CHANGED = {'00421400', '004217e0', '00422540', '00425130', '00425e60', '00425ef0', '00490a00', '00490fb0', '00493080', '004937c0'}

def digest(b):
    return hashlib.sha256(b).hexdigest()

def rows(p):
    return list(csv.DictReader(p.open(), delimiter='\t'))

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--captures', type=Path, required=True)
    p.add_argument('--pe', type=Path, required=True)
    p.add_argument('--gzf', type=Path, required=True)
    p.add_argument('--output', type=Path)
    a = p.parse_args()
    r = a.captures
    checks = {}
    def check(name, condition):
        checks[name] = bool(condition)
        if not condition:
            raise AssertionError(name)
    pe = a.pe.read_bytes()
    check('retail_sha256', digest(pe) == SHA)
    check('retail_md5', hashlib.md5(pe).hexdigest() == 'a640ea0097dbb62e0c77b7f2847c7161')
    gzf = a.gzf.read_bytes()
    check('exact_v99_gzf', len(gzf) == 6500304 and digest(gzf) == GZF)
    identity = dict(line.split('\t') for line in (r/'before/identity.tsv').read_text().splitlines())
    check('program_identity', all(identity[k] == v for k, v in {'program':'i76.exe','sha256':SHA,'language':'x86:LE:32:default','image_base':'00400000','functions':'2337','defined_functions':'2102','external_functions':'235','ghidra':'12.1.4'}.items()))
    ph = struct.unpack_from('<I', pe, 60)[0]
    n, opt = struct.unpack_from('<H', pe, ph+6)[0], struct.unpack_from('<H', pe, ph+20)[0]
    sections = [struct.unpack_from('<IIII', pe, ph+24+opt+j*40+8) for j in range(n)]
    def original(va, size):
        rv = va - 0x400000
        for _, start, length, off in sections:
            if start <= rv and rv+size <= start+length:
                return pe[off+rv-start:off+rv-start+size]
        raise AssertionError('unmapped original function range')
    funcs = rows(r/'before/functions.tsv')
    for f in funcs:
        ranges = re.findall(r'\[([0-9a-f]{8}), ([0-9a-f]{8})\]', f['body'])
        assert ranges, f['address']
        raw = b''.join(original(int(x,16), int(y,16)-int(x,16)+1) for x,y in ranges)
        assert digest(raw) == f['bytes_sha256'], f['address']
    check('all_2102_defined_bodies_match_original_pe', len(funcs) == 2102)
    for before, after, name in [('before','preview','preview'), ('before','negative-final','negative_rollback'), ('preflight-extra','negative-final-extra','negative_extra_rollback'), ('after','repeat','idempotency'), ('after-extra','repeat-extra','idempotency_extra')]:
        files = list((r/before).iterdir())
        check(name, all(x.read_bytes() == (r/after/x.name).read_bytes() for x in files))
    for name in ['identity.tsv','functions.tsv','types.tsv','comments.tsv','instructions.tsv']:
        check('unchanged_'+name, (r/'before'/name).read_bytes() == (r/'after'/name).read_bytes())
    check('all_terrain_instruction_captures_unchanged', (r/'preflight-extra/terrain_instructions.tsv').read_bytes() == (r/'after-extra/terrain_instructions.tsv').read_bytes())
    syms_before = {l for l in (r/'before/symbols.tsv').read_text().splitlines() if '\tUSER_DEFINED\t' in l}
    syms_after = {l for l in (r/'after/symbols.tsv').read_text().splitlines() if '\tUSER_DEFINED\t' in l}
    check('analyst_symbols_preserved', syms_before == syms_after)
    db = {x['address']:x for x in rows(r/'preflight-extra/data.tsv')}
    da = {x['address']:x for x in rows(r/'after-extra/data.tsv')}
    data_changed = {k for k in db.keys() | da.keys() if db.get(k) != da.get(k)}
    check('only_two_data_definitions_changed', data_changed == {'006442c0','004ed7ec'})
    check('float_and_literal', da['006442c0']['type'] == '/float' and da['004ed7ec']['type'] == '/TerminatedCString' and da['004ed7ec']['value'] == 'aud')
    before_c = {x.stem:x for d in ['before','preflight-extra'] for x in (r/d).glob('*.c')}
    after_c = {x.stem:x for d in ['after','after-extra'] for x in (r/d).glob('*.c')}
    changed = {k for k in before_c if before_c[k].read_bytes() != after_c[k].read_bytes()}
    check('exact_reviewed_c_changes', changed == EXPECTED_CHANGED)
    check('no_derived_terrain_alias_in_c', all('PTR_g_runtime_terrain_page_pointer_grid_3192__1_004ed7ec' not in x.read_text() for x in after_c.values()))
    functions = {f['address']:f for f in funcs}
    normal = functions['004931c0']['signature']
    check('normal_abi', all(v in normal for v in ['|true|','|EAX:4|','out_normal:/Interstate76/SemanticConsolidation/TER_Normal3f *32:Stack[0x4]:4','world_x:/double:Stack[0x8]:8','world_z:/double:Stack[0x10]:8']))
    check('height_abi', all(v in functions['00493550']['signature'] for v in ['/float|ST0:10','world_x:/double:Stack[0x4]:8','world_z:/double:Stack[0xc]:8']))
    log = (r/'negative-final.log').read_text()
    check('all_seven_negative_tests', all('SAFETY PASS '+m in log for m in ['type','label','boundary','guard','identity','rollback','arguments']) and 'ERROR' not in log)
    log = (r/'apply-final.log').read_text()
    check('preview_apply_repeat_reports', all(v in log for v in ['SUMMARY PREVIEW eligible=2; no edits','SUMMARY APPLY changed=2 committed=true','SUMMARY APPLY changed=0 committed=true']) and 'ERROR' not in log)
    shapes = rows(r/'type-comparison.tsv')
    check('12_structures_semantically_equivalent', len(shapes) == 12 and all(x['same_layout_names_types'] == 'true' for x in shapes))
    capture_digests = {}
    for d in ['before','preflight-extra','preview','negative-final','negative-final-extra','after','after-extra','repeat','repeat-extra']:
        files = sorted(x for x in (r/d).iterdir() if x.is_file())
        index = ''.join(x.name+'\t'+str(x.stat().st_size)+'\t'+digest(x.read_bytes())+'\n' for x in files).encode()
        capture_digests[d] = {'files':len(files), 'index_sha256':digest(index), 'tables':{x.name:{'sha256':digest(x.read_bytes()),'bytes':x.stat().st_size} for x in files if x.suffix == '.tsv'}}
    result = {'status':'passed','test_count':len(checks),'passed_count':sum(checks.values()),'checks':checks,'defined_pe_verified':len(funcs),'c_sample':len(before_c),'c_changed':len(changed),'c_unchanged':len(before_c)-len(changed),'changed_addresses':sorted(changed),'captures':capture_digests}
    if a.output:
        a.output.write_text(json.dumps(result, indent=2)+'\n')
    else:
        print(json.dumps(result, indent=2))

if __name__ == '__main__':
    main()
