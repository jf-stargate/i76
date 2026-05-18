/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049b770
 * Entry: 0049b770
 * Signature: undefined __stdcall ui_bitmap_region_context_helper_0049b770(void)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049b770. Remove
   duplicated UI/region wording. */

void ui_bitmap_region_context_helper_0049b770(void)

{
  LPVOID lpMem;
  int *piVar1;
  
  piVar1 = g_scrolling_status_overlay_list;
  while (piVar1 != (int *)0x0) {
    g_scrolling_status_overlay_list = (int *)*piVar1;
    lpMem = (LPVOID)piVar1[2];
    release_bitmap_surface_context((int *)((int)lpMem + 0x10));
    HeapFree(g_runtime_text_overlay_heap,0,*(LPVOID *)((int)lpMem + 0x5c));
    HeapFree(g_runtime_text_overlay_heap,0,lpMem);
    unlink_and_free_linked_list_node_3field((int *)&g_scrolling_status_overlay_list,piVar1);
    piVar1 = g_scrolling_status_overlay_list;
  }
  g_scrolling_status_overlay_list = piVar1;
  HeapDestroy(g_runtime_text_overlay_heap);
  return;
}


