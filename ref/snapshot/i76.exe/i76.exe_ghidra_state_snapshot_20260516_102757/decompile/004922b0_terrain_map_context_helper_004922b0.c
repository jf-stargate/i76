/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004922b0
 * Entry: 004922b0
 * Signature: int * __cdecl terrain_map_context_helper_004922b0(int * param_1, int param_2)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004922b0. Remove
   duplicated terrain wording. */

int * __cdecl terrain_map_context_helper_004922b0(int *param_1,int param_2)

{
  int *piVar1;
  
  if (*(int *)(param_2 + 4) != 0) {
    piVar1 = terrain_map_context_helper_004922b0(param_1,*(int *)(param_2 + 8));
    piVar1 = terrain_map_context_helper_004922b0(piVar1,*(int *)(param_2 + 4));
    return piVar1;
  }
  *param_1 = (int)*(short *)(param_2 + 2);
  return param_1 + 1;
}


