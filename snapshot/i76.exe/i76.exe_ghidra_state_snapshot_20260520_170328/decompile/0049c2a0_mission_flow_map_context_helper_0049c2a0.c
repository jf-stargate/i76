/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049c2a0
 * Entry: 0049c2a0
 * Signature: undefined __stdcall mission_flow_map_context_helper_0049c2a0(void)
 */


/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049c2a0.
   Remove duplicated mission-flow/map wording. */

void mission_flow_map_context_helper_0049c2a0(void)

{
  LPVOID lpMem;
  int *piVar1;
  
  piVar1 = g_static_text_overlay_list;
  while (g_static_text_overlay_list = piVar1, piVar1 != (int *)0x0) {
    lpMem = (LPVOID)piVar1[2];
    release_bitmap_surface_context((int *)((int)lpMem + 0x10));
    HeapFree(DAT_005a7d9c,0,lpMem);
    unlink_and_free_linked_list_node_3field((int *)&g_static_text_overlay_list,piVar1);
    piVar1 = g_static_text_overlay_list;
  }
  HeapDestroy(DAT_005a7d9c);
  return;
}


