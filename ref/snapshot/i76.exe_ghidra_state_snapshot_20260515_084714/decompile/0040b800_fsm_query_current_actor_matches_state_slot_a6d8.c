/*
 * Program: i76.exe
 * Function: fsm_query_current_actor_matches_state_slot_a6d8
 * Entry: 0040b800
 * Signature: undefined4 __cdecl fsm_query_current_actor_matches_state_slot_a6d8(int param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: checks AI/FSM state slot +0xa6d8
   against the current actor/player id, then clears the slot to sentinel -10 on success. */

undefined4 __cdecl fsm_query_current_actor_matches_state_slot_a6d8(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  iVar2 = get_vehicle_damage_source_event_state();
  if (*(int *)(iVar1 + 0xa6d8) != iVar2 + -1) {
    iVar2 = get_vehicle_damage_source_event_state();
    if (*(int *)(iVar1 + 0xa6d8) != iVar2) {
      return 0;
    }
  }
  *(undefined4 *)(iVar1 + 0xa6d8) = 0xfffffff6;
  return 1;
}


