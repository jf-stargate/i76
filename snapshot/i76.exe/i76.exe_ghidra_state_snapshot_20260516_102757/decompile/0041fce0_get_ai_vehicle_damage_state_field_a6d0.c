/*
 * Program: i76.exe
 * Function: get_ai_vehicle_damage_state_field_a6d0
 * Entry: 0041fce0
 * Signature: undefined4 __cdecl get_ai_vehicle_damage_state_field_a6d0(int param_1)
 */


/* cgpt readability rename v13 set A: Returns AI/vehicle damage-event state field +0xa6d0. */

undefined4 __cdecl get_ai_vehicle_damage_state_field_a6d0(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar1 = get_vehicle_damage_event_state_block(iVar1);
  return *(undefined4 *)(iVar1 + 0xa6d0);
}


