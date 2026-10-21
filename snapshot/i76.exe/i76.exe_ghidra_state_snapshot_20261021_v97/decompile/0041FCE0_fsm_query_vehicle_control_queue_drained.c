/* Decompiled retail i76.exe, Ghidra v97; 0041fce0 fsm_query_vehicle_control_queue_drained */

/* cgpt readability rename v13 set A: Returns AI/vehicle damage-event state field +0xa6d0.
   I76 v91: AI+A6D0 initialized 1; enqueue at 0041F9C0 clears to 0; last dequeue at 0041F8E0 sets to
   1 */

undefined4 __cdecl fsm_query_vehicle_control_queue_drained(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar1 = get_vehicle_damage_event_state_block(iVar1);
  return *(undefined4 *)(iVar1 + 0xa6d0);
}


