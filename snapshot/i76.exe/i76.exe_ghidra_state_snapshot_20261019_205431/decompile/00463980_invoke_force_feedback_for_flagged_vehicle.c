/*
 * Program: i76.exe
 * Function: invoke_force_feedback_for_flagged_vehicle
 * Entry: 00463980
 * Signature: undefined __cdecl invoke_force_feedback_for_flagged_vehicle(int param_1)
 */


void __cdecl invoke_force_feedback_for_flagged_vehicle(int param_1)

{
  int iVar1;
  
  iVar1 = world_object_has_optional_runtime_flag(param_1);
  if (iVar1 != 0) {
    force_feedback_effect_table_helper_00445610();
    return;
  }
  return;
}


