/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409a90
 * Entry: 00401055
 * Signature: undefined4 __cdecl thunk_FUN_00409a90(int * param_1, uint param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00409a90(int *param_1,uint param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  int aiStack_c [3];
  
  piVar1 = (int *)param_1[2];
  iVar4 = i76edit_get_or_create_zone_cell_backing(param_2,param_3,1);
  if (iVar4 == -1) {
    return 0;
  }
  piVar5 = (int *)i76edit_world_xy_to_zone_local_triplet(aiStack_c,param_2,param_3);
  iVar4 = *piVar5;
  iVar2 = piVar5[1];
  iVar3 = piVar5[2];
  if (*piVar1 != iVar4) {
    thunk_FUN_0041c480(&DAT_00439be8 + *piVar1,param_1);
    uVar6 = i76edit_alloc_linked_list_node3((&DAT_00439be8)[iVar4],(undefined4 *)0x0,(int)piVar1);
    (&DAT_00439be8)[iVar4] = uVar6;
    *piVar1 = iVar4;
  }
  piVar1[1] = iVar2;
  piVar1[2] = iVar3;
  return 1;
}


