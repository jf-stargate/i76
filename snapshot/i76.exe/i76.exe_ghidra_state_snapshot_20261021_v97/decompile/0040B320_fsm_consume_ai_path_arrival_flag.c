/* Decompiled retail i76.exe, Ghidra v97; 0040b320 fsm_consume_ai_path_arrival_flag */

/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: reads the vehicle damage-event state
   block, returns true when field +0x9c is 1, and clears it.
   I76 v90: 00415020 writes AI+0x9c on final route waypoint; 00420A20 resets it; 0040B320 checks
   value 1 then clears to 0 */

undefined4 __cdecl fsm_consume_ai_path_arrival_flag(int param_1)

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


