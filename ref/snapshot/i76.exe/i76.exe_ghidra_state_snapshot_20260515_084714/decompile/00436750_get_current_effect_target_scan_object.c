/*
 * Program: i76.exe
 * Function: get_current_effect_target_scan_object
 * Entry: 00436750
 * Signature: undefined4 __stdcall get_current_effect_target_scan_object(void)
 */


/* cgpt readability rename v13 set A: Returns the world object associated with the current
   effect-target scan node, or null when no scan is active. */

undefined4 get_current_effect_target_scan_object(void)

{
  if (g_effect_target_primary_list == 0) {
    g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
    g_effect_target_scan_current_node = g_effect_target_secondary_list;
  }
  else {
    g_effect_target_scan_current_list_head = &g_effect_target_primary_list;
    g_effect_target_scan_current_node = g_effect_target_primary_list;
  }
  if (g_effect_target_scan_current_node == 0) {
    return 0;
  }
  return *(undefined4 *)(g_effect_target_scan_current_node + 8);
}


