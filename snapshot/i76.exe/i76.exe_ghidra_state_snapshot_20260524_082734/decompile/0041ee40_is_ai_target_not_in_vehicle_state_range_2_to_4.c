/*
 * Program: i76.exe
 * Function: is_ai_target_not_in_vehicle_state_range_2_to_4
 * Entry: 0041ee40
 * Signature: undefined4 __cdecl is_ai_target_not_in_vehicle_state_range_2_to_4(undefined4 param_1, int param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Returns true unless target is a vehicle whose runtime
   state field +0x45c lies in range 2..4. */

undefined4 __cdecl is_ai_target_not_in_vehicle_state_range_2_to_4(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = is_vehicle_or_actor_runtime_world_object(param_2);
  if (iVar1 == 0) {
    uVar2 = 1;
  }
  else {
    iVar1 = get_vehicle_runtime_context(param_2);
    if ((*(int *)(iVar1 + 0x45c) < 2) || (4 < *(int *)(iVar1 + 0x45c))) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}


