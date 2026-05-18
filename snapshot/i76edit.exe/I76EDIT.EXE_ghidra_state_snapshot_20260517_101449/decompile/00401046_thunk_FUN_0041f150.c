/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041f150
 * Entry: 00401046
 * Signature: uint __cdecl thunk_FUN_0041f150(uint param_1, uint param_2)
 */


uint __cdecl thunk_FUN_0041f150(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int aiStack_c [3];
  
  if ((-1 < (int)param_1) && (-1 < (int)param_2)) {
    iVar2 = i76edit_get_or_create_zone_cell_backing(param_1,param_2,0);
    if (iVar2 < 0) {
      return 0xffffffff;
    }
    piVar3 = (int *)i76edit_world_xy_to_zone_local_triplet(aiStack_c,param_1,param_2);
    iVar2 = piVar3[1];
    iVar1 = piVar3[2];
    puVar4 = i76edit_get_terrain_plane_row_ptr(*piVar3,2);
    return (uint)*(ushort *)((int)puVar4 + (iVar1 * 0x80 + iVar2) * 2);
  }
  return 0xffffffff;
}


