#!/usr/bin/env python3
"""v0.4.0 cumulative static checkpoint verifier. No original game execution."""
import csv, json, subprocess, sys
from pathlib import Path
root=Path(__file__).resolve().parent
p=subprocess.run([sys.executable,str(root/'verify_checkpoint.py')],capture_output=True,text=True)
if p.returncode:print(p.stdout,p.stderr);sys.exit(1)
old=json.loads((root/'VALIDATION_RESULTS.json').read_text())
def t(s):return (root/s).read_text()
def rows(s):return list(csv.DictReader((root/s).open(),delimiter='\t'))
ref=rows('evidence/v100_descriptor_references.tsv')
initial=rows('evidence/v100_descriptor_initial_values.tsv')
call=t('evidence/v100_parser_call_sites.txt')
new=t('DESCRIPTOR_STATE_AND_REPEATED_LOAD_CONTRACT.md')
base=t('evidence/v99_loader_full_instructions.tsv')
reset=t('evidence/v100_targeted_decompilation.txt')
model=json.loads(t('evidence/REQUIRED_SEEN_MODEL_RESULTS.json'))
cmd=t('evidence/v100_headless.stdout')
checks={
  'v100_script_success': 'V100_DESCRIPTOR_READONLY_OK' in cmd,
  'v100_no_script_error': 'ERROR' not in cmd.split('REPORT: Execute script:')[-1],
  'root_ref_generic': any(x['target']=='00500328' and x['ref_source']=='004b4234' for x in ref),
  'root_ref_mission': any(x['target']=='00500328' and x['ref_source']=='004b44c2' for x in ref),
  'root_ref_alt_generic': any(x['target']=='00500328' and x['ref_source']=='004b4ae4' for x in ref),
  'world_ref_mission': any(x['target']=='00500348' and x['ref_source']=='004b44eb' for x in ref),
  'adef_ref_nested': any(x['target']=='00500D20' and x['ref_source']=='004b89c4' for x in ref),
  'five_pointer_references': len(ref)==5,
  'twelve_descriptor_rows': len(initial)==12,
  'initial_all_unseen': all(int(x['initial_flags'],16)&0x80==0 for x in initial),
  'root_bwd2_required': next(x for x in initial if x['address']=='00500328')['initial_flags']=='00000044',
  'only_root_bwd2_mandatory': [x['address'] for x in initial if x['required']=='1']==['00500328'],
  'root_parsers_3_call_sites': all(x in call for x in ['004b423f','004b44c8','004b4aef']),
  'parser_seen_read': '004b3db0\t004b3f2c\tMOV EAX,dword ptr [EDI + 0xc]' in base,
  'parser_seen_update': '004b3db0\t004b3f2f\tOR AL,0x80' in base,
  'parser_seen_write': '004b3db0\t004b3f31\tMOV dword ptr [EDI + 0xc],EAX' in base,
  'parser_mandatory_test': '004b3db0\t004b4163\tTEST CL,0x40' in base,
  'parser_previous_seen_test': '004b3db0\t004b4168\tTEST CL,0x80' in base,
  'inherited_reset_no_table_clear': 'register_world_object_tree_callback(clear_mission_parse_object_callback_state)' in reset,
  'model_cold_no_match_fails': model['results'][0]['required_check_passes'] is False,
  'model_warm_no_match_passes': model['results'][2]['required_check_passes'] is True,
  'model_no_retail_execution': all(x['retail_engine_executed'] is False for x in model['results']),
  'model_not_full_parser': all(x['full_parser_emulated'] is False for x in model['results']),
  'proper_scope_language': all(w in new for w in ['not a whole-process nonexistence proof','not claims of a successful modified-resource load','not dynamically observed']),
  'reconciliation_updated': 'L-10d' in t('RECONCILIATION_AND_OPEN_ISSUES.md'),
  'test_plan_present': 'S-08' in t('DESCRIPTOR_STATE_TEST_PLAN.md'),
  'version_reflected': 'I76-MISSION-0.4.0' in t('MISSION_EXECUTION_CONTRACT.md'),
  'abi_preserved_96': len(rows('ABI_DISPATCH_CONTRACT_96.tsv'))==96,
}
combined=dict(old['checks']);combined.update(checks)
failed=[x for x,v in combined.items() if not v]
results={'version':'0.4.0','passed':sum(combined.values()),'failed':len(failed),'checks':combined,
         'all_check_names_unique':len(combined)==len(old['checks'])+len(checks),
         'retail_malformed_files_executed':False,'original_binary_mutated':False,
         'new_ghidra_names_applied':False,'static_branch_model_only':True}
(root/'VALIDATION_RESULTS.json').write_text(json.dumps(results,indent=2)+'\n')
print('v0.4.0 validation',results['passed'],'/',len(combined),'passed, failures',failed)
sys.exit(bool(failed))
