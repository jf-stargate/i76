/*
 * Program: i76.exe
 * Function: effect_target_scan_query_context_helper_00436790
 * Entry: 00436790
 * Signature: int __stdcall effect_target_scan_query_context_helper_00436790(void)
 */


/* cgpt label refinement v18: was effect_target_scan_target_query_helper_00436790. Remove duplicated
   target wording from readability-pass label. */

int effect_target_scan_query_context_helper_00436790(void)

{
  int iVar1;
  
  iVar1 = 0;
  if (g_effect_target_scan_current_node != (int *)0x0) {
    g_effect_target_scan_current_node = (int *)*g_effect_target_scan_current_node;
    if (g_effect_target_scan_current_node == (int *)0x0) {
      if (g_effect_target_scan_current_list_head == &g_effect_target_primary_list) {
        g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
        g_effect_target_scan_current_node = g_effect_target_secondary_list;
      }
      if (g_effect_target_scan_current_node == (int *)0x0) {
        return 0;
      }
    }
    iVar1 = g_effect_target_scan_current_node[2];
  }
  return iVar1;
}


