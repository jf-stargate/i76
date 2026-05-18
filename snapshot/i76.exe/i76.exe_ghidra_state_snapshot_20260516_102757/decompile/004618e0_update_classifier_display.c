/*
 * Program: i76.exe
 * Function: update_classifier_display
 * Entry: 004618e0
 * Signature: undefined __stdcall update_classifier_display(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: clasfn */

void update_classifier_display(void)

{
  LPVOID pvVar1;
  
  while (DAT_0054b208 != (int *)0x0) {
    unlink_and_free_linked_list_node_3field((int *)&DAT_0054b208,DAT_0054b208);
    DAT_0054b20c = DAT_0054b20c + -1;
  }
  DAT_0054b208 = (int *)0x0;
  while (g_queued_world_object_class_callback_list != (int *)0x0) {
    pvVar1 = release_world_object_tree_reference
                       ((LPVOID)g_queued_world_object_class_callback_list[2],s_clasfn_004f7c5c);
    if (pvVar1 != (LPVOID)0x0) {
      finalize_released_world_object_after_damage(pvVar1,s_clasfn_004f7c5c);
    }
    unlink_and_free_linked_list_node_3field
              ((int *)&g_queued_world_object_class_callback_list,
               g_queued_world_object_class_callback_list);
    DAT_0054b210 = DAT_0054b210 + -1;
  }
  return;
}


