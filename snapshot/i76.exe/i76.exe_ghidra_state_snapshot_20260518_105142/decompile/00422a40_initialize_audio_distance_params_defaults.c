/*
 * Program: i76.exe
 * Function: initialize_audio_distance_params_defaults
 * Entry: 00422a40
 * Signature: undefined __cdecl initialize_audio_distance_params_defaults(undefined4 * param_1)
 */


/* cgpt readability rename v13 set A: Initializes the shorter audio distance/attenuation parameter
   block. */

void __cdecl initialize_audio_distance_params_defaults(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[5] = 0x462c4400;
  param_1[6] = 0x42c80000;
  param_1[7] = 0;
  return;
}


