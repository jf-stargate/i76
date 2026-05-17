/*
 * Program: i76.exe
 * Function: parse_colp_vehicle_collision_bounds_chunk
 * Entry: 004ae570
 * Signature: undefined4 __cdecl parse_colp_vehicle_collision_bounds_chunk(int param_1, int * param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=high] COLP callback; parses
   inner/outer vehicle collision bounds. */

undefined4 __cdecl parse_colp_vehicle_collision_bounds_chunk(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  if (*(int *)(*param_2 + 0x6c) != 8) {
    piVar2 = (int *)(param_1 + 8);
    piVar3 = param_2 + 3;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar3 = piVar3 + 1;
    }
    param_2[2] = 1;
  }
  return 1;
}


