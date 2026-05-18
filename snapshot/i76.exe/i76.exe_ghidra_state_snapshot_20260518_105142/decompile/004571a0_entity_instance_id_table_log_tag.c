/*
 * Program: i76.exe
 * Function: entity_instance_id_table_log_tag
 * Entry: 004571a0
 * Signature: undefined __stdcall entity_instance_id_table_log_tag(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: ent */

void entity_instance_id_table_log_tag(void)

{
  LPVOID pvVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  
  vehicle_config_loader_context_helper_004ad600((undefined4 *)&DAT_0054a178);
  piVar3 = &DAT_00542844;
  do {
    pvVar1 = (LPVOID)piVar3[-5];
    if (pvVar1 != (LPVOID)0x0) {
      iVar2 = 0;
      if (0 < g_world_object_tree_callback_count) {
        puVar4 = &g_world_object_tree_callbacks;
        do {
          (*(code *)*puVar4)(piVar3 + -5);
          iVar2 = iVar2 + 1;
          puVar4 = puVar4 + 1;
        } while (iVar2 < g_world_object_tree_callback_count);
      }
      pvVar1 = release_world_object_tree_reference(pvVar1,s_ent_004f5d04);
      if (pvVar1 != (LPVOID)0x0) {
        if (*(int *)((int)pvVar1 + 0xc) < 2) {
          finalize_released_world_object_after_damage(pvVar1,s_ent_004f5d04);
        }
        else {
          finalize_released_world_object_after_damage(pvVar1,s_ent_004f5d04);
          unlink_and_release_world_object_node_refcounted(pvVar1,s_ent_004f5d04);
        }
      }
    }
    if ((*piVar3 == 1) && ((LPVOID)piVar3[1] != (LPVOID)0x0)) {
      xfree_global_heap((LPVOID)piVar3[1]);
    }
    piVar5 = piVar3 + -5;
    for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar5 = 0;
      piVar5 = piVar5 + 1;
    }
    *piVar3 = 0;
    piVar3 = piVar3 + 0x1e;
  } while ((int)piVar3 < 0x54a045);
  g_active_world_object_entry_count = 0;
  return;
}


