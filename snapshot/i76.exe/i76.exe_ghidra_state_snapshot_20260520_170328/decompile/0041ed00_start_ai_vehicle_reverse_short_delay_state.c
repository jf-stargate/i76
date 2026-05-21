/*
 * Program: i76.exe
 * Function: start_ai_vehicle_reverse_short_delay_state
 * Entry: 0041ed00
 * Signature: undefined __cdecl start_ai_vehicle_reverse_short_delay_state(int param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Starts reverse drive mode with randomized 5-8 second
   timer and speed limit 20. */

void __cdecl start_ai_vehicle_reverse_short_delay_state(int param_1,undefined4 param_2)

{
  float10 fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float10 fVar5;
  
  iVar2 = get_vehicle_runtime_context(param_1);
  fVar5 = get_gameplay_runtime_seconds();
  fVar1 = (float10)_DAT_004bcb28;
  uVar3 = rand();
  uVar4 = (int)uVar3 >> 0x1f;
  *(float *)(*(int *)(iVar2 + 0x108) + 0xa82c) =
       (float)(int)(((uVar3 ^ uVar4) - uVar4 & 3 ^ uVar4) - uVar4) + (float)(fVar5 + fVar1);
  *(undefined4 *)(*(int *)(iVar2 + 0x108) + 0xa998) = param_2;
  *(undefined4 *)(iVar2 + 0xf0) = 0;
  *(undefined4 *)(iVar2 + 0xe8) = 0xbf800000;
  vehicle_specials_state_getter_helper_00467370(param_1,1);
  *(undefined4 *)(*(int *)(iVar2 + 0x108) + 0x80) = 0x41a00000;
  return;
}


