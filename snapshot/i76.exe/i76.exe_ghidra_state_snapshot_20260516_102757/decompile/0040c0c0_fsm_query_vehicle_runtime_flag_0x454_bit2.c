/*
 * Program: i76.exe
 * Function: fsm_query_vehicle_runtime_flag_0x454_bit2
 * Entry: 0040c0c0
 * Signature: uint __cdecl fsm_query_vehicle_runtime_flag_0x454_bit2(int param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: returns vehicle runtime field +0x454
   bit 2. */

uint __cdecl fsm_query_vehicle_runtime_flag_0x454_bit2(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  return *(uint *)(iVar1 + 0x454) & 4;
}


