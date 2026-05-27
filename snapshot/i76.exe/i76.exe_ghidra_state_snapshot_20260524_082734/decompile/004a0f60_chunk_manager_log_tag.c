/*
 * Program: i76.exe
 * Function: chunk_manager_log_tag
 * Entry: 004a0f60
 * Signature: undefined __stdcall chunk_manager_log_tag(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence chnkmgr */

void chunk_manager_log_tag(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  world_instance_id_table_context_helper_004ad260();
  DAT_005aaac0 = HeapCreate(0,0,0);
  puVar4 = &DAT_005a8118;
  for (iVar3 = 0x71; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  DAT_005aaac4 = allocate_world_object_node(0);
  *(undefined4 *)((int)DAT_005aaac4 + 0x70) = 0;
  *(undefined4 *)((int)DAT_005aaac4 + 0x10) = 0x100;
  register_active_world_object_entry((int)DAT_005aaac4,0,(int *)0x0);
  DAT_005aaac8 = 0;
  _DAT_005aaacc = 0;
  DAT_005a82dc = &DAT_005a82e8;
  iVar3 = 0x95;
  puVar1 = &DAT_005a82e8;
  do {
    puVar2 = puVar1;
    iVar3 = iVar3 + -1;
    *(undefined **)(puVar2 + 0x40) = puVar2 + 0x44;
    puVar1 = puVar2 + 0x44;
  } while (iVar3 != 0);
  *(undefined4 *)(puVar2 + 0x84) = 0;
  _DAT_005a82e0 = 0;
  return;
}


