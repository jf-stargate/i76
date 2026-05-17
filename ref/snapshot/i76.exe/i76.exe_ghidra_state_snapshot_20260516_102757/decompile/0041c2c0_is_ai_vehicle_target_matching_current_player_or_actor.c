/*
 * Program: i76.exe
 * Function: is_ai_vehicle_target_matching_current_player_or_actor
 * Entry: 0041c2c0
 * Signature: bool __cdecl is_ai_vehicle_target_matching_current_player_or_actor(int param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Checks AI behavior state target id against the
   current actor/player id returned by FUN_00415600. */

bool __cdecl is_ai_vehicle_target_matching_current_player_or_actor(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = get_ai_vehicle_behavior_state_block(param_1);
  iVar2 = get_vehicle_damage_source_event_state();
  return *(int *)(iVar1 + 0xa6d8) == iVar2;
}


