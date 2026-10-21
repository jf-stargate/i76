/* Decompiled retail i76.exe, Ghidra v97; 00457100 initialize_world_object_registry_and_instance_keys */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: cannot allocate EntityInstIDHandler */

void initialize_world_object_registry_and_instance_keys(void)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  
  iVar6 = 0;
  piVar5 = &DAT_00542428;
  puVar3 = &g_active_world_object_entries;
  do {
    puVar4 = puVar3 + 0x1e;
    puVar7 = puVar3;
    for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    iVar6 = iVar6 + 1;
    puVar3[5] = 0;
    *piVar5 = iVar6;
    piVar5 = piVar5 + 1;
    puVar3 = puVar4;
  } while ((int)puVar4 < 0x54a031);
  _DAT_00542828 = 0;
  initialize_world_object_and_aux_heaps();
  puVar3 = &g_world_object_tree_callbacks;
  for (iVar6 = 0x33; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar3 = &g_world_object_entry_callbacks;
  for (iVar6 = 0x33; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  g_active_world_object_entry_count = 0;
  DAT_0054a260 = 0;
  g_active_player_or_camera_world_object_entry = 0;
  g_world_object_entry_callback_count = 0;
  g_world_object_tree_callback_count = 0;
  bVar1 = initialize_world_object_instance_key_registry
                    ((undefined4 *)&g_world_object_instance_key_registry);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    report_error();
  }
  return;
}


