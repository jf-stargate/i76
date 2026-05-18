/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049b720
 * Entry: 0049b720
 * Signature: undefined __cdecl ui_bitmap_region_context_helper_0049b720(int * param_1)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049b720. Remove
   duplicated UI/region wording. */

void __cdecl ui_bitmap_region_context_helper_0049b720(int *param_1)

{
  LPVOID lpMem;
  
  lpMem = (LPVOID)param_1[2];
  release_bitmap_surface_context((int *)((int)lpMem + 0x10));
  HeapFree(g_runtime_text_overlay_heap,0,*(LPVOID *)((int)lpMem + 0x5c));
  HeapFree(g_runtime_text_overlay_heap,0,lpMem);
  unlink_and_free_linked_list_node_3field(&g_scrolling_status_overlay_list,param_1);
  return;
}


