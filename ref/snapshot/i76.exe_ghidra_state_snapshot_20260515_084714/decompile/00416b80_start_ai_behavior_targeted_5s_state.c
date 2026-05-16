/*
 * Program: i76.exe
 * Function: start_ai_behavior_targeted_5s_state
 * Entry: 00416b80
 * Signature: undefined __cdecl start_ai_behavior_targeted_5s_state(int param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Stores an AI behavior target object, sets speed/state
   35.0, and starts a 5-second behavior timer. */

void __cdecl start_ai_behavior_targeted_5s_state(int param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  float10 fVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  *(undefined4 *)(iVar1 + 0xa998) = param_2;
  fVar3 = get_runtime_time_seconds();
  fVar2 = (float10)_DAT_004bc880;
  *(undefined4 *)(iVar1 + 0x80) = 0x420c0000;
  *(float *)(iVar1 + 0xa82c) = (float)(fVar3 - fVar2);
  return;
}


