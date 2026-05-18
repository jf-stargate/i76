/*
 * Program: i76.exe
 * Function: mark_ai_behavior_ready_after_delay
 * Entry: 0041e030
 * Signature: undefined __cdecl mark_ai_behavior_ready_after_delay(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Sets a behavior-ready flag after a 3-second delay
   from state +0x9d24. */

void __cdecl mark_ai_behavior_ready_after_delay(int param_1)

{
  float fVar1;
  int iVar2;
  float10 fVar3;
  
  iVar2 = get_ai_vehicle_behavior_state_block(param_1);
  fVar1 = *(float *)(iVar2 + 0x9d24) + _DAT_004bcb34;
  fVar3 = get_gameplay_runtime_seconds();
  if ((float10)fVar1 < fVar3) {
    *(undefined4 *)(iVar2 + 0x98) = 1;
  }
  return;
}


