/*
 * Program: i76.exe
 * Function: fsm_toggle_ai_behavior_state_flag_9d14
 * Entry: 0040bc10
 * Signature: undefined __cdecl fsm_toggle_ai_behavior_state_flag_9d14(int param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action: toggles AI/FSM behavior-state field
   +0x9d14 in the vehicle damage-event state block. */

void __cdecl fsm_toggle_ai_behavior_state_flag_9d14(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar1 = get_vehicle_damage_event_state_block(iVar1);
  *(uint *)(iVar1 + 0x9d14) = (uint)(*(int *)(iVar1 + 0x9d14) == 0);
  return;
}


