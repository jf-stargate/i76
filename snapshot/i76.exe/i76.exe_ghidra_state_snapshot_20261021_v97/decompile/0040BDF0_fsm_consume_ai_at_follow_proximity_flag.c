/* Decompiled retail i76.exe, Ghidra v97; 0040bdf0 fsm_consume_ai_at_follow_proximity_flag */

/* cgpt whole-binary semantic rename v1: string evidence: isAtFollow non-vehicle
   I76 v91: AI+A988 is written by 0041EF40 proximity update; here nonzero is consumed by clearing to
   0 */

undefined4 __cdecl fsm_consume_ai_at_follow_proximity_flag(int param_1)

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


