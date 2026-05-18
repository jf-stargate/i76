/*
 * Program: i76.exe
 * Function: reset_ai_tactics_weight_scalars_to_one
 * Entry: 00415610
 * Signature: undefined __cdecl reset_ai_tactics_weight_scalars_to_one(int param_1)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Resets four AI tactic weight scalars at
   +0x9d58..+0x9d64 to 1.0. */

void __cdecl reset_ai_tactics_weight_scalars_to_one(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  *(undefined4 *)(iVar1 + 0x9d58) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x9d5c) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x9d60) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x9d64) = 0x3f800000;
  return;
}


