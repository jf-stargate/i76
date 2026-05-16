/*
 * Program: i76.exe
 * Function: entity_instance_table_context_helper_004577f0
 * Entry: 004577f0
 * Signature: undefined __stdcall entity_instance_table_context_helper_004577f0(void)
 */


/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_004577f0. Remove
   duplicated network/entity wording. */

void entity_instance_table_context_helper_004577f0(void)

{
  uint *puVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  piVar2 = g_active_player_or_camera_world_object_entry;
  iVar7 = 0;
  if (0 < g_active_world_object_entry_count) {
    piVar6 = &g_active_world_object_entries;
    do {
      iVar5 = *piVar6;
      if ((((iVar5 != 0) && (iVar3 = is_vehicle_or_actor_runtime_world_object(iVar5), iVar3 == 1))
          && (iVar5 != *piVar2)) && (*(int *)(iVar5 + 0x70) != 0)) {
        piVar4 = (int *)(*(int *)(iVar5 + 0x70) + 0x420);
        iVar5 = 8;
        do {
          if (*piVar4 != 0) {
            puVar1 = (uint *)(*piVar4 + 0x10);
            *puVar1 = *puVar1 | 1;
          }
          piVar4 = piVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      iVar7 = iVar7 + 1;
      piVar6 = piVar6 + 0x1e;
    } while (iVar7 < g_active_world_object_entry_count);
  }
  return;
}


