/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041f4a0
 * Entry: 00401474
 * Signature: undefined __cdecl thunk_FUN_0041f4a0(uint param_1, uint param_2, undefined2 param_3, int param_4)
 */


void __cdecl thunk_FUN_0041f4a0(uint param_1,uint param_2,undefined2 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  int aiStack_c [3];
  
  iVar2 = i76edit_get_or_create_zone_cell_backing(param_1,param_2,(uint)(param_4 == 0));
  if (iVar2 != -1) {
    piVar3 = (int *)i76edit_world_xy_to_zone_local_triplet(aiStack_c,param_1,param_2);
    iVar2 = *piVar3;
    iVar5 = piVar3[1];
    iVar1 = piVar3[2];
    puVar4 = i76edit_get_terrain_plane_row_ptr(iVar2,2);
    iVar5 = iVar1 * 0x80 + iVar5;
    *(undefined2 *)((int)puVar4 + iVar5 * 2) = param_3;
    if (param_4 != 0) {
      puVar4 = i76edit_get_terrain_plane_row_ptr(iVar2,4);
      *(undefined2 *)(iVar5 * 2 + (int)puVar4) = param_3;
    }
  }
  return;
}


