/*
 * Program: i76.exe
 * Function: start_ai_behavior_targeted_long_delay_state
 * Entry: 00416e50
 * Signature: int __cdecl start_ai_behavior_targeted_long_delay_state(int param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Stores a target object, sets speed/state 35.0, and
   starts a randomized long 25-39 second behavior timer. */

int __cdecl start_ai_behavior_targeted_long_delay_state(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  *(undefined4 *)(iVar1 + 0xa998) = param_2;
  fVar3 = get_gameplay_runtime_seconds();
  iVar2 = rand();
  *(undefined4 *)(iVar1 + 0x80) = 0x420c0000;
  *(float *)(iVar1 + 0xa82c) = ((float)(iVar2 % 0xf) + (float)fVar3) - _DAT_004bc8ac;
  return iVar2 / 0xf;
}


