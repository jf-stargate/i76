/*
 * Program: i76.exe
 * Function: entity_instance_table_context_helper_00457540
 * Entry: 00457540
 * Signature: uint __stdcall entity_instance_table_context_helper_00457540(void)
 */


/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_00457540. Remove
   duplicated network/entity wording. */

uint entity_instance_table_context_helper_00457540(void)

{
  if (g_active_player_or_camera_world_object_entry != (int *)0x0) {
    return *(uint *)(*(int *)(*g_active_player_or_camera_world_object_entry + 0x70) + 0x454) & 0x20;
  }
  return 0;
}


