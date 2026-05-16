/*
 * Program: i76.exe
 * Function: select_ai_target_candidate_excluding_current
 * Entry: 0041d770
 * Signature: undefined4 __cdecl select_ai_target_candidate_excluding_current(float * param_1, int param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Selects an AI candidate through the target/path
   selector but rejects a supplied current target. */

undefined4 __cdecl select_ai_target_candidate_excluding_current(float *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = get_ai_vehicle_behavior_state_block((int)param_1);
  if (*(int *)(iVar1 + 0x9d14) == 0) {
    uVar2 = 0;
  }
  else {
    iVar3 = get_vehicle_runtime_context((int)param_1);
    uVar2 = select_ai_vehicle_target_or_path_candidate
                      (param_1,*(undefined4 *)(iVar3 + 0xe0),*(undefined4 *)(iVar3 + 0xe4),
                       (uint *)(iVar1 + 0x9d2c),(undefined4 *)(iVar1 + 0x9d30),
                       (float *)(iVar1 + 0x9d34),0,1,(float *)(iVar1 + 0x9d28));
    if (*(int *)(iVar1 + 0x9d2c) == param_2) {
      uVar2 = 0;
    }
  }
  return uVar2;
}


