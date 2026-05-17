/*
 * Program: i76.exe
 * Function: select_ai_target_candidate_for_behavior_state
 * Entry: 0041d820
 * Signature: undefined4 __cdecl select_ai_target_candidate_for_behavior_state(float * param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Selects an AI candidate through the target/path
   selector and writes state progress outputs. */

undefined4 __cdecl select_ai_target_candidate_for_behavior_state(float *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_c;
  int local_8;
  
  local_8 = 0;
  local_8 = get_ai_vehicle_behavior_state_block((int)param_1);
  if (*(int *)(local_8 + 0x9d14) == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = get_vehicle_runtime_context((int)param_1);
    uVar1 = select_ai_vehicle_target_or_path_candidate
                      (param_1,*(undefined4 *)(iVar2 + 0xe0),*(undefined4 *)(iVar2 + 0xe4),
                       (uint *)(local_8 + 0x9d2c),&local_c,(float *)(local_8 + 0x9d34),0,1,
                       (float *)(local_8 + 0x9d28));
  }
  return uVar1;
}


