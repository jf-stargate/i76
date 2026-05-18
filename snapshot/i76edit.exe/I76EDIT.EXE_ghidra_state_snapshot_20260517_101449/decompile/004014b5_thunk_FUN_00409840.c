/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409840
 * Entry: 004014b5
 * Signature: undefined __cdecl thunk_FUN_00409840(uint param_1, uint param_2)
 */


void __cdecl thunk_FUN_00409840(uint param_1,uint param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int iVar7;
  int aiStack_c [3];
  
  iVar3 = i76edit_get_or_create_zone_cell_backing(param_1,param_2,1);
  puVar4 = (undefined4 *)i76edit_world_xy_to_zone_local_triplet(aiStack_c,param_1,param_2);
  uVar6 = *puVar4;
  uVar1 = puVar4[1];
  uVar2 = puVar4[2];
  puVar5 = _malloc(0x78);
  *puVar5 = uVar6;
  puVar5[1] = uVar1;
  puVar5[2] = uVar2;
  puVar5[6] = 0;
  puVar4 = (undefined4 *)((int)puVar5 + 0x29);
  for (iVar7 = 10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar5[8] = 0;
  puVar5[9] = 0;
  *(undefined1 *)(puVar5 + 10) = 0;
  puVar5[0x19] = 0;
  puVar5[0x1a] = 0;
  *(undefined1 *)(puVar5 + 0x1b) = 0;
  *(undefined4 *)((int)puVar5 + 0x6d) = 0;
  *(undefined4 *)((int)puVar5 + 0x71) = 0;
  *(undefined1 *)((int)puVar5 + 0x75) = 0;
  puVar5[0x18] = 0;
  puVar5[7] = 1;
  puVar5[3] = 0;
  uVar6 = i76edit_alloc_linked_list_node3((&DAT_00439be8)[iVar3],(undefined4 *)0x0,(int)puVar5);
  (&DAT_00439be8)[iVar3] = uVar6;
  return;
}


