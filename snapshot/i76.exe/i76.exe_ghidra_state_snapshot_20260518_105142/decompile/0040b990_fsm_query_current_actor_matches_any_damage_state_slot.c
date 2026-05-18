/*
 * Program: i76.exe
 * Function: fsm_query_current_actor_matches_any_damage_state_slot
 * Entry: 0040b990
 * Signature: undefined4 __cdecl fsm_query_current_actor_matches_any_damage_state_slot(int param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: checks state slot +0xa6dc against
   current actor/player id, then clears slots +0xa6d4/+0xa6d8/+0xa6dc on success. */

undefined4 __cdecl fsm_query_current_actor_matches_any_damage_state_slot(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  iVar2 = get_vehicle_damage_source_event_state();
  if (*(int *)(iVar1 + 0xa6dc) != iVar2 + -1) {
    iVar2 = get_vehicle_damage_source_event_state();
    if (*(int *)(iVar1 + 0xa6dc) != iVar2) {
      return 0;
    }
  }
  *(undefined4 *)(iVar1 + 0xa6d8) = 0xfffffff6;
  *(undefined4 *)(iVar1 + 0xa6d4) = 0xfffffff6;
  *(undefined4 *)(iVar1 + 0xa6dc) = 0xfffffff6;
  return 1;
}


