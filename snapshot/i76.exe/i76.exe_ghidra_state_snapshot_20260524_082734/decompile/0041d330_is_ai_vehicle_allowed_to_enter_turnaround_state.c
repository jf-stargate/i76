/*
 * Program: i76.exe
 * Function: is_ai_vehicle_allowed_to_enter_turnaround_state
 * Entry: 0041d330
 * Signature: undefined4 __cdecl is_ai_vehicle_allowed_to_enter_turnaround_state(int param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Predicate for entering a turnaround/reverse behavior
   based on vehicle type, backward motion, and damage/target response state. */

undefined4 __cdecl is_ai_vehicle_allowed_to_enter_turnaround_state(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0x6c) == 9) {
    local_8 = 0;
  }
  else {
    bVar1 = is_ai_vehicle_moving_backward_relative_to_forward(param_1);
    if (CONCAT31(extraout_var,bVar1) == 0) {
      iVar2 = get_vehicle_runtime_context(param_1);
      iVar2 = update_ai_vehicle_damage_response_state(param_1,iVar2);
      if (iVar2 == 0) {
        return 0;
      }
    }
    local_8 = 1;
  }
  return local_8;
}


