/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049beb0
 * Entry: 0049beb0
 * Signature: undefined4 * __stdcall ui_bitmap_region_context_helper_0049beb0(void)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049beb0. Remove
   duplicated UI/region wording. */

undefined4 * ui_bitmap_region_context_helper_0049beb0(void)

{
  undefined4 *puVar1;
  
  puVar1 = g_static_text_overlay_list;
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if ((*(uint *)(puVar1[2] + 0xb0) & 0x100) != 0) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


