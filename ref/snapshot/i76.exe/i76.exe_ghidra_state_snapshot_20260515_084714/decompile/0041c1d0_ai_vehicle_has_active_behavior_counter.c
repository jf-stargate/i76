/*
 * Program: i76.exe
 * Function: ai_vehicle_has_active_behavior_counter
 * Entry: 0041c1d0
 * Signature: bool __cdecl ai_vehicle_has_active_behavior_counter(int param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Returns whether vehicle runtime field +0x148 is
   positive. */

bool __cdecl ai_vehicle_has_active_behavior_counter(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  return 0 < *(int *)(iVar1 + 0x148);
}


