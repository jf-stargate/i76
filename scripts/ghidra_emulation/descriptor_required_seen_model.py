#!/usr/bin/env python3
"""Standalone unit probe for a two-bit *fragment*, NOT an emulator of i76.exe.

This deliberately only reproduces the descriptor match's OR 0x80 and the
required-finalization condition (flags & 0x40) && !(flags & 0x80).
NEVER interpret a passing probe as evidence a mission is accepted by the game.
"""
import csv, json
from pathlib import Path
ROOT=Path(__file__).resolve().parent
rows=list(csv.DictReader((ROOT/'evidence/v100_descriptor_initial_values.tsv').open(),delimiter='\t'))
assert len(rows)==12
initial={r['address']:int(r['initial_flags'],16) for r in rows}
assert all(not (v&0x80) for v in initial.values())

def seen_update(flags: int)->int: return flags|0x80

def required_check(flags: int)->bool:
    return not(bool(flags&0x40) and not bool(flags&0x80))

def table_required_ok(table: list[int])->bool:
    return all(required_check(f) for f in table)

root=[initial[f'{0x500328+i*16:08X}'] for i in range(2)]
world=[initial[f'{0x500348+i*16:08X}'] for i in range(7)]
adef=[initial[f'{0x500D20+i*16:08X}'] for i in range(3)]
assert root==[0x44,0x2020]
assert root[0]&0x40
assert not table_required_ok(root)
assert table_required_ok(world) and table_required_ok(adef)
results=[]

def emit(name,flags,has_bwd2,expected_check):
    current=seen_update(flags) if has_bwd2 else flags
    outcome=required_check(current)
    assert outcome==expected_check,(name,outcome,expected_check)
    results.append({'case':name,'flags_in':f'0x{flags:04X}','bwd2_matched_in_current_run':has_bwd2,
                    'flags_after_match':f'0x{current:04X}','required_check_passes':outcome,
                    'retail_engine_executed':False,'full_parser_emulated':False})

emit('fresh_no_match',root[0],False,False)
emit('fresh_match',root[0],True,True)
emit('warm_no_match',seen_update(root[0]),False,True)
emit('warm_repeat_match',seen_update(root[0]),True,True)
results.append({'case':'cross_resource_root_shared','same_static_address':'00500328',
                'loaders':['004B41E0','004B42B0','004B4A80'],
                'retail_engine_executed':False,'full_parser_emulated':False})
(ROOT/'evidence/REQUIRED_SEEN_MODEL_RESULTS.json').write_text(json.dumps({'results':results,
    'scope':'isolated branch logic only; no full retail parser or malformed missions executed'},indent=2)+'\n')
print('required/seen logic model:',len(results),'checks passed (NOT a retail-engine test)')
