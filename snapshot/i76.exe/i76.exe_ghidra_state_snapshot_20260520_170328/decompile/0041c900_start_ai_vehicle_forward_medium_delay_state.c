/*
 * Program: i76.exe
 * Function: start_ai_vehicle_forward_medium_delay_state
 * Entry: 0041c900
 * Signature: undefined __cdecl start_ai_vehicle_forward_medium_delay_state(int param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Sets a randomized 10-19 second forward AI state and
   enters drive mode 3. */

void __cdecl start_ai_vehicle_forward_medium_delay_state(int param_1,undefined4 param_2)

{
  float10 fVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  
  iVar2 = get_vehicle_runtime_context(param_1);
  fVar4 = get_gameplay_runtime_seconds();
  fVar1 = (float10)_DAT_004bcad0;
  iVar3 = rand();
  *(float *)(*(int *)(iVar2 + 0x108) + 0xa82c) = (float)(iVar3 % 10) + (float)(fVar4 + fVar1);
  *(undefined4 *)(*(int *)(iVar2 + 0x108) + 0xa998) = param_2;
  *(undefined4 *)(iVar2 + 0xf0) = 0;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  *(undefined4 *)(iVar2 + 0xe8) = 0x3f800000;
  *(undefined4 *)(*(int *)(iVar2 + 0x108) + 0x80) = 0x420c0000;
  return;
}


