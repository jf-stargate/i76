/*
 * Program: i76.exe
 * Function: fsm_query_and_clear_vehicle_damage_event_flag
 * Entry: 0040b320
 * Signature: undefined4 __cdecl fsm_query_and_clear_vehicle_damage_event_flag(int param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: reads the vehicle damage-event state
   block, returns true when field +0x9c is 1, and clears it. */

undefined4 __cdecl fsm_query_and_clear_vehicle_damage_event_flag(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar1 = get_vehicle_damage_event_state_block(iVar1);
  if (*(int *)(iVar1 + 0x9c) == 1) {
    *(undefined4 *)(iVar1 + 0x9c) = 0;
    return 1;
  }
  return 0;
}


