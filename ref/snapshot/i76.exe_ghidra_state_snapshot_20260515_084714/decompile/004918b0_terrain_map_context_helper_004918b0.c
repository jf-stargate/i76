/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004918b0
 * Entry: 004918b0
 * Signature: undefined __cdecl terrain_map_context_helper_004918b0(undefined2 param_1, undefined2 param_2)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004918b0. Remove
   duplicated terrain wording. */

void __cdecl terrain_map_context_helper_004918b0(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  puVar2 = DAT_00654380;
  puVar1 = DAT_00654380 + 1;
  DAT_00654380 = DAT_00654380 + 6;
  *puVar1 = param_2;
  *puVar2 = param_1;
  *(undefined4 *)(puVar2 + 2) = 0;
  *(undefined4 *)(puVar2 + 4) = 0;
  DAT_0059c568 = DAT_0059c568 + 1;
  return;
}


