/*
 * Program: i76.exe
 * Function: entity_instance_id_lookup_or_update
 * Entry: 00457420
 * Signature: undefined __cdecl entity_instance_id_lookup_or_update(int * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: ent */

void __cdecl entity_instance_id_lookup_or_update(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar2 = 0;
  piVar1 = &g_active_world_object_entries;
  do {
    if (param_1 == piVar1) goto LAB_00457444;
    piVar1 = piVar1 + 0x1e;
    iVar2 = iVar2 + 1;
  } while ((int)piVar1 < 0x54a030);
  iVar2 = 0;
LAB_00457444:
  iVar3 = 0;
  if (0 < g_world_object_tree_callback_count) {
    puVar4 = &g_world_object_tree_callbacks;
    do {
      (*(code *)*puVar4)(param_1);
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar3 < g_world_object_tree_callback_count);
  }
  iVar3 = world_object_has_optional_runtime_flag(*param_1);
  if (iVar3 != 0) {
    g_active_player_or_camera_world_object_entry = 0;
  }
  finalize_released_world_object_after_damage((LPVOID)*param_1,s_ent_004f5d04);
  if ((param_1[5] == 1) && ((LPVOID)param_1[6] != (LPVOID)0x0)) {
    xfree_global_heap((LPVOID)param_1[6]);
  }
  piVar1 = param_1;
  for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar1 = 0;
    piVar1 = piVar1 + 1;
  }
  param_1[5] = 0;
  if (iVar2 == g_active_world_object_entry_count + -1) {
    g_active_world_object_entry_count = g_active_world_object_entry_count + -1;
  }
  return;
}


