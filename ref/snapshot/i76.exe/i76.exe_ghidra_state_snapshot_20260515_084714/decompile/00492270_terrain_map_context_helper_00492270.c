/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00492270
 * Entry: 00492270
 * Signature: int * __cdecl terrain_map_context_helper_00492270(int * param_1, short * param_2)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00492270. Remove
   duplicated terrain wording. */

int * __cdecl terrain_map_context_helper_00492270(int *param_1,short *param_2)

{
  int *piVar1;
  
  if (*(short **)(param_2 + 2) != (short *)0x0) {
    piVar1 = terrain_map_context_helper_00492270(param_1,*(short **)(param_2 + 2));
    piVar1 = terrain_map_context_helper_00492270(piVar1,*(short **)(param_2 + 4));
    return piVar1;
  }
  *param_1 = (int)*param_2;
  return param_1 + 1;
}


