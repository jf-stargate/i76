/*
 * Program: i76.exe
 * Function: get_ai_vehicle_behavior_state_block
 * Entry: 0041c2f0
 * Signature: undefined4 __cdecl get_ai_vehicle_behavior_state_block(int param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Returns the per-vehicle AI behavior/state block
   pointer from the vehicle runtime context. */

undefined4 __cdecl get_ai_vehicle_behavior_state_block(int param_1)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x108);
}


