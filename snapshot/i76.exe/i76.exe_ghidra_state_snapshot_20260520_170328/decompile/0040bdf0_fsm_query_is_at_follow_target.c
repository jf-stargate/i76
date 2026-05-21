/*
 * Program: i76.exe
 * Function: fsm_query_is_at_follow_target
 * Entry: 0040bdf0
 * Signature: undefined4 __cdecl fsm_query_is_at_follow_target(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: isAtFollow non-vehicle */

undefined4 __cdecl fsm_query_is_at_follow_target(int param_1)

{
  int iVar1;
  
  iVar1 = is_vehicle_or_actor_runtime_world_object(param_1);
  if (iVar1 == 0) {
    report_error();
    return 0;
  }
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar1 = get_vehicle_damage_event_state_block(iVar1);
  if (*(int *)(iVar1 + 0xa988) != 0) {
    *(undefined4 *)(iVar1 + 0xa988) = 0;
    return 1;
  }
  return 0;
}


