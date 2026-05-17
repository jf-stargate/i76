/*
 * Program: i76.exe
 * Function: initialize_audio_params_full_defaults
 * Entry: 004229f0
 * Signature: undefined __cdecl initialize_audio_params_full_defaults(undefined4 * param_1)
 */


/* cgpt readability rename v13 set A: Initializes the full audio parameter block with distance
   defaults, sentinel fields, and channel/category defaults. */

void __cdecl initialize_audio_params_full_defaults(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x1f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_1;
  for (iVar1 = 0xb; puVar2 = puVar2 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
  }
  param_1[8] = 0;
  param_1[6] = 0x462c4400;
  param_1[7] = 0x42c80000;
  param_1[0xc] = 0x30534147;
  param_1[0xd] = 0xffffffff;
  param_1[0xe] = 0xffffffff;
  param_1[0xf] = 0xffffffff;
  param_1[0x10] = 0xffffffff;
  param_1[0x11] = 0xffffffff;
  param_1[0x12] = 0xffffffff;
  *(undefined1 *)(param_1 + 0x1d) = 0xff;
  return;
}


