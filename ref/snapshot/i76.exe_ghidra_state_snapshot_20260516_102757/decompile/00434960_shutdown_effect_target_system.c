/*
 * Program: i76.exe
 * Function: shutdown_effect_target_system
 * Entry: 00434960
 * Signature: undefined __stdcall shutdown_effect_target_system(void)
 */


/* cgpt rename v4: Clears primary and secondary effect-target lists, resets scan iterators, clears
   collision links, and shuts down target heap state. */

void shutdown_effect_target_system(void)

{
  while (g_effect_target_primary_list != (int *)0x0) {
    unlink_and_free_linked_list_node_3field
              ((int *)&g_effect_target_primary_list,g_effect_target_primary_list);
  }
  g_effect_target_primary_list = (int *)0x0;
  while (g_effect_target_secondary_list != (int *)0x0) {
    unlink_and_free_linked_list_node_3field
              ((int *)&g_effect_target_secondary_list,g_effect_target_secondary_list);
  }
  g_effect_target_scan_current_list_head = 0;
  g_effect_target_scan_current_node = 0;
  clear_effect_target_collision_link_lists();
  shutdown_effect_target_collision_heap();
  return;
}


