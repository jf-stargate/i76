/*
 * Program: i76.exe
 * Function: fsm_mark_vehicle_effect_object_if_flag6_mismatch
 * Entry: 0040c0e0
 * Signature: undefined __cdecl fsm_mark_vehicle_effect_object_if_flag6_mismatch(int param_1, uint * param_2)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action: compares script value against vehicle
   runtime field +0x454 bit 6 and marks current damage/effect object when mismatched. */

void __cdecl fsm_mark_vehicle_effect_object_if_flag6_mismatch(int param_1,uint *param_2)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((*(uint *)(iVar1 + 0x454) >> 6 & 1) != *param_2) {
    set_vehicle_current_damage_or_effect_object(param_1,1);
  }
  return;
}


