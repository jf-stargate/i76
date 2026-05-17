/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041f3a0
 * Entry: 00401244
 * Signature: undefined __cdecl thunk_FUN_0041f3a0(uint param_1, uint param_2, undefined2 param_3, int param_4)
 */


void __cdecl thunk_FUN_0041f3a0(uint param_1,uint param_2,undefined2 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *apuStack_c [3];
  
  iVar3 = i76edit_get_or_create_zone_cell_backing(param_1,param_2,(uint)(param_4 != 0));
  if (iVar3 != -1) {
    piVar4 = (int *)i76edit_world_xy_to_zone_local_triplet((int *)apuStack_c,param_1,param_2);
    iVar1 = *piVar4;
    iVar3 = piVar4[1];
    iVar2 = piVar4[2];
    apuStack_c[0] = i76edit_get_terrain_plane_row_ptr(iVar1,param_4);
    iVar3 = (iVar2 * 0x80 + iVar3) * 2;
    *(undefined2 *)(iVar3 + (int)apuStack_c[0]) = param_3;
    if (param_4 == 0) {
      if (DAT_004376f4 == 10) {
        uVar5 = i76edit_get_or_create_zone_surface_sample(param_1,param_2,5);
        *(short *)(iVar3 + (int)apuStack_c[0]) = (short)uVar5;
      }
      puVar6 = i76edit_get_terrain_plane_row_ptr(iVar1,3);
      *(undefined2 *)(iVar3 + (int)puVar6) = param_3;
    }
  }
  return;
}


