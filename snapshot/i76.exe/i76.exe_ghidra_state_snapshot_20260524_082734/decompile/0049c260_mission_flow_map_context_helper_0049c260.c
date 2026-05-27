/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049c260
 * Entry: 0049c260
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049c260(int * param_1)
 */


/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049c260.
   Remove duplicated mission-flow/map wording. */

void __cdecl mission_flow_map_context_helper_0049c260(int *param_1)

{
  LPVOID lpMem;
  
  lpMem = (LPVOID)param_1[2];
  release_bitmap_surface_context((int *)((int)lpMem + 0x10));
  HeapFree(DAT_005a7d9c,0,lpMem);
  unlink_and_free_linked_list_node_3field(&g_static_text_overlay_list,param_1);
  return;
}


