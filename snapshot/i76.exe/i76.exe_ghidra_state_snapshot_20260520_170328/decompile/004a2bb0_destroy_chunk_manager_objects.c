/*
 * Program: i76.exe
 * Function: destroy_chunk_manager_objects
 * Entry: 004a2bb0
 * Signature: LPVOID __cdecl destroy_chunk_manager_objects(uint param_1, uint param_2, float param_3, float param_4, float param_5, float * param_6, float param_7)
 */


/* cgpt whole-binary semantic rename v1: string evidence chnkmgr */

LPVOID __cdecl
destroy_chunk_manager_objects
          (uint param_1,uint param_2,float param_3,float param_4,float param_5,float *param_6,
          float param_7)

{
  uint uVar1;
  uint uVar2;
  LPVOID pvVar3;
  int iVar4;
  uint *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  uint local_8;
  uint local_4;
  
  pvVar3 = allocate_world_object_node(0);
  puVar6 = &DAT_004faed8;
  puVar8 = (undefined4 *)((int)pvVar3 + 0x18);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  *(double *)((int)pvVar3 + 0x40) = (double)param_3;
  *(double *)((int)pvVar3 + 0x48) = (double)param_4;
  *(double *)((int)pvVar3 + 0x50) = (double)param_5;
  *(undefined4 *)((int)pvVar3 + 0x10) = 0;
  *(undefined4 *)((int)pvVar3 + 0x5c) = 0;
  local_8 = param_1;
  local_4 = param_2;
  uVar7 = 0;
  do {
    iVar4 = toupper((int)*(char *)((int)&local_8 + uVar7));
    *(char *)((int)&local_8 + uVar7) = (char)iVar4;
    uVar2 = local_4;
    uVar1 = local_8;
    uVar7 = uVar7 + 1;
  } while (uVar7 < 8);
  uVar9 = __allshr(0x20,local_4);
  for (puVar5 = (uint *)(&DAT_005aaad0)
                        [((((uint)uVar9 ^ uVar1) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0xd];
      puVar5 != (uint *)0x0; puVar5 = (uint *)puVar5[4]) {
    if ((*puVar5 == uVar1) && (puVar5[1] == uVar2)) goto LAB_004a2c81;
  }
  puVar5 = (uint *)0x0;
LAB_004a2c81:
  if (puVar5 == (uint *)0x0) {
    unlink_and_release_world_object_node_refcounted(pvVar3,s_chnkmgr_004fe71c);
    return (LPVOID)0x0;
  }
  cache_add_indexed_entry(puVar5[2],(int)pvVar3);
  release_chunk_manager_runtime(pvVar3,param_6,param_7);
  return pvVar3;
}


