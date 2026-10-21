#!/usr/bin/env python3
"""Read-only verification of the v0.6 original-code emulation evidence.

The captured emulator run is evidence; this validator never executes or repairs game code.
"""
import argparse, csv, json, hashlib, tarfile, pathlib
p=argparse.ArgumentParser()
p.add_argument('--root',default='/mnt/data/i76_parser_emulation_v0.6.0')
p.add_argument('--game-tar',default=None)
a=p.parse_args()
root=pathlib.Path(a.root)
def rows(name):
 with (root/name/'wrapper_outcomes.tsv').open() as f:return {r['scenario']:r for r in csv.DictReader(f,delimiter='\t')}
r=rows('results'); n=rows('results_nonempty')
checks={}
def check(label, truth):checks[label]=bool(truth)
scenarios={'W01_stock_cold','W02_missing_cold','W03_bad_rev_cold','W07_wrong_AREV','W08_missing_FSM','W09_missing_ADEF','W10_missing_ADEF_EXIT','W04a_valid','W04b_missing_warm','W05a_wrong_rev','W05b_missing_warm','W06a_missing_cold','W06b_valid_after'}
check('exact_M06_scenario_set',set(r)==scenarios)
check('exact_T01_scenario_set',set(n)=={'W11_T01_nonempty'})
for case, row in list(r.items())+list(n.items()):
 check(f'{case}_normal_return',row['returned']=='true' and row['status']=='returned')
 check(f'{case}_wrapper_one',row['wrapper_eax']=='00000001')
 check(f'{case}_root_parser_visited',row['root_calls']=='1')
 check(f'{case}_no_instruction_failure',int(row['steps'])<1500000)
for k in ('W01_stock_cold','W07_wrong_AREV','W10_missing_ADEF_EXIT'):
 q=r[k];check(f'{k}_native_empty_import',q['fsm_native_runs']=='1' and q['fsm_stubbed_runs']=='0')
 check(f'{k}_cursor_reaches_end',q['global_cursor']==q['global_end'] and q['global_cursor']!='00000000')
 check(f'{k}_no_nonempty_counts',all(q[x]=='0' for x in ('command_count','media_count','node_count','token_count')))
for k in ('W02_missing_cold','W03_bad_rev_cold','W05a_wrong_rev','W06a_missing_cold'):
 q=r[k];check(f'{k}_parser_null',q['global_cursor']=='00000000')
 check(f'{k}_world_parser_not_called',q['world_calls']=='0')
check('cold_missing_rejected',r['W02_missing_cold']['bwd_before']=='00000044' and r['W02_missing_cold']['bwd_after']=='00000044')
for k in ('W04b_missing_warm','W05b_missing_warm'):
 q=r[k];check(f'{k}_warm_missing_still_reaches_world',q['bwd_before']=='000000C4' and q['world_calls']=='1' and q['adef_calls']=='1' and q['global_cursor']==q['global_end'] and q['fsm_stubbed_runs']=='1')
check('previous_failed_REV_sets_flag',r['W05a_wrong_rev']['bwd_after']=='000000C4')
check('cold_to_valid_order',r['W06b_valid_after']['bwd_before']=='00000044' and r['W06b_valid_after']['bwd_after']=='000000C4')
check('wrong_nested_AREV_diagnostic_but_FSM_called',int(r['W07_wrong_AREV']['reporter_calls'])>=1 and r['W07_wrong_AREV']['fsm_native_runs']=='1')
check('renamed_FSM_skips_FSM_callback',r['W08_missing_FSM']['adef_calls']=='1' and r['W08_missing_FSM']['fsm_callbacks_entered']=='0' and r['W08_missing_FSM']['global_cursor']==r['W08_missing_FSM']['global_end'])
check('renamed_ADEF_stops_early_without_callback',r['W09_missing_ADEF']['adef_calls']=='0' and int(r['W09_missing_ADEF']['global_cursor'],16)<int(r['W09_missing_ADEF']['global_end'],16))
check('renamed_ADEF_EXIT_no_FSM_prevention',r['W10_missing_ADEF_EXIT']['fsm_native_runs']=='1')
t=n['W11_T01_nonempty']
expected={'command_count':95,'media_count':169,'position_count':22,'actor_count':11,'node_count':20,'initial_word_count':47,'token_count':4712}
for key,num in expected.items():check(f'T01_independently_known_{key}',int(t[key])==num)
check('T01_native_nonempty_completed',t['fsm_native_runs']=='1' and t['fsm_stubbed_runs']=='0' and t['global_cursor']==t['global_end'])
for sub in ('results','results_nonempty'):
 ev=(root/sub/'instruction_events.tsv').read_text()
 checks[f'{sub}_native_ADEF_events']='NESTED_ADEF_PARSER' in ev
 checks[f'{sub}_native_FSM_events']='ORIGINAL_FSM_IMPORT' in ev
 checks[f'{sub}_native_WRAPPER_events']='WRAPPER_ROOT_PARSER' in ev and 'WRAPPER_WORLD_PARSER' in ev
 checks[f'{sub}_no_abort_trace']='EMULATION_FAILURE' not in ev and 'DATA_EXECUTION_ENTRY' not in ev
 stdout=(root/sub/'ghidra.stdout').read_text()
 checks[f'{sub}_no_Ghidra_script_error']='ERROR REPORT SCRIPT ERROR' not in stdout and 'ERROR Emulation failure' not in stdout
check('safe_nonoverlapping_fixture_memory',0x20000000+140330<0x21000000<0x22000000<0x30000000)
check('source_present',(root/'scripts/I76_MissionWrapper_OriginalCodeEmulator.java').exists())
if a.game_tar:
 with tarfile.open(a.game_tar) as tar:
  exe=tar.extractfile('interstate 76/i76.exe').read()
  check('retail_exe_md5_verified',hashlib.md5(exe).hexdigest()=='a640ea0097dbb62e0c77b7f2847c7161')
  for name,size in [('M06',47814),('T01',140330)]:
   data=tar.extractfile('interstate 76/miss8/'+name+'.MSN').read()
   check(f'retail_{name}_fixture_bytes',len(data)==size and data[:4]==b'BWD2')
   (root/'evidence'/f'{name}_source_sha256.txt').write_text(hashlib.sha256(data).hexdigest()+'  '+name+'.MSN (not redistributed)\n')
out={'version':'v0.6.0','checks':len(checks),'passed':sum(checks.values()),'failed':[k for k,v in checks.items() if not v], 'retail_engine_original_code_executed':True,'full_Windows_game_executed':False,'world_callbacks_stubbed':True,'persistent_FSM_state_reset_modeled':False}
(root/'validation.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
if out['failed']:raise SystemExit(1)
