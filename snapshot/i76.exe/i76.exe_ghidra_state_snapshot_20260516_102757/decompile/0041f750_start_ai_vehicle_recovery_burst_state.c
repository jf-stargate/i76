/*
 * Program: i76.exe
 * Function: start_ai_vehicle_recovery_burst_state
 * Entry: 0041f750
 * Signature: undefined __cdecl start_ai_vehicle_recovery_burst_state(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Starts a short recovery/boost state, preserves
   steering sign, sets override flag, and marks recovery timer. */

void __cdecl start_ai_vehicle_recovery_burst_state(int param_1)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar2 = get_vehicle_damage_event_state_block(iVar1);
  if (_DAT_004bcae8 <= *(float *)(iVar1 + 0xe0)) {
    *(undefined4 *)(iVar1 + 0xe0) = 0x3f800000;
  }
  else {
    *(undefined4 *)(iVar1 + 0xe0) = 0xbf800000;
  }
  *(undefined4 *)(iVar1 + 0xf0) = 1;
  fVar3 = get_gameplay_runtime_seconds();
  *(float *)(iVar2 + 0x9d34) = (float)(fVar3 + (float10)_DAT_004bcad4);
  *(undefined4 *)(iVar2 + 0xa97c) = 1;
  return;
}


