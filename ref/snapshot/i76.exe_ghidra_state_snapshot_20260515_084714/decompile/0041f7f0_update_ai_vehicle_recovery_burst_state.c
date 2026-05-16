/*
 * Program: i76.exe
 * Function: update_ai_vehicle_recovery_burst_state
 * Entry: 0041f7f0
 * Signature: undefined __cdecl update_ai_vehicle_recovery_burst_state(float param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Clears recovery flag if needed and increases throttle
   toward maximum safe drive. */

void __cdecl update_ai_vehicle_recovery_burst_state(float param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = get_vehicle_runtime_context((int)param_1);
  iVar2 = get_vehicle_damage_event_state_block(iVar1);
  if (*(int *)(iVar2 + 0xa97c) == 0) {
    *(undefined4 *)(iVar1 + 0xf0) = 0;
  }
  else {
    *(undefined4 *)(iVar2 + 0xa97c) = 0;
  }
  increase_vehicle_throttle_toward_max_safe_drive(param_1);
  return;
}


