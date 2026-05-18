/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00491810
 * Entry: 00491810
 * Signature: short * __cdecl terrain_map_context_helper_00491810(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00491810. Remove
   duplicated terrain wording. */

short * __cdecl
terrain_map_context_helper_00491810
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short *psVar1;
  short sVar2;
  int iVar3;
  
  psVar1 = DAT_00654380;
  DAT_00654380 = DAT_00654380 + 0xe;
  sVar2 = ftol();
  *psVar1 = sVar2;
  sVar2 = ftol();
  psVar1[1] = sVar2;
  iVar3 = ftol();
  *(int *)(psVar1 + 2) = iVar3 - *psVar1;
  *(undefined4 *)(psVar1 + 6) = param_1;
  *(undefined4 *)(psVar1 + 8) = param_2;
  *(undefined4 *)(psVar1 + 10) = param_3;
  *(undefined4 *)(psVar1 + 0xc) = param_4;
  psVar1[4] = 0;
  psVar1[5] = 0;
  DAT_0059c56c = DAT_0059c56c + 1;
  return psVar1;
}


