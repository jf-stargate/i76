/*
 * Program: i76.exe
 * Function: unregister_effect_target_record
 * Entry: 00434870
 * Signature: undefined __cdecl unregister_effect_target_record(int * param_1)
 */


/* cgpt rename v3: Removes an effect-target record from the primary/secondary target lists, fixes
   iterator state, and releases any child target registrations. */

void __cdecl unregister_effect_target_record(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  if (param_1[5] != 0) {
    iVar1 = is_vehicle_or_weapon_source_world_object(*param_1);
    piVar2 = &g_effect_target_primary_list;
    if (iVar1 == 0) {
      piVar2 = (int *)&g_effect_target_secondary_list;
    }
    piVar3 = (int *)*piVar2;
    if (piVar3 != (int *)0x0) {
      while ((int *)piVar3[2] != param_1) {
        piVar3 = (int *)*piVar3;
        if (piVar3 == (int *)0x0) {
          release_effect_target_collision_links(param_1);
          return;
        }
      }
      if ((((piVar3 == g_effect_target_scan_current_node) &&
           (g_effect_target_scan_current_node != (int *)0x0)) &&
          (g_effect_target_scan_current_node = (int *)*g_effect_target_scan_current_node,
          g_effect_target_scan_current_node == (int *)0x0)) &&
         (g_effect_target_scan_current_list_head == &g_effect_target_primary_list)) {
        g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
        g_effect_target_scan_current_node = g_effect_target_secondary_list;
      }
      if (param_1[5] == 3) {
        for (iVar1 = *param_1; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
          if ((*(uint *)(iVar1 + 0x10) & 0xf000) == 0x3000) {
            release_effect_target_collision_payload(iVar1);
          }
          if (*(int *)(iVar1 + 100) != 0) {
            find_nearest_effect_target_in_scan_list_helper_00436980(*(int *)(iVar1 + 100));
          }
        }
      }
      DAT_0052b938 = 0;
      unlink_and_free_linked_list_node_3field(piVar2,piVar3);
    }
  }
  release_effect_target_collision_links(param_1);
  return;
}


