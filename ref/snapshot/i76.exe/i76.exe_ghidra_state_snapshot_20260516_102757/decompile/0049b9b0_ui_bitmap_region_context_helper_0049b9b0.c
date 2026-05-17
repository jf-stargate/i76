/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049b9b0
 * Entry: 0049b9b0
 * Signature: undefined __cdecl ui_bitmap_region_context_helper_0049b9b0(int param_1, int param_2)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049b9b0. Remove
   duplicated UI/region wording. */

void __cdecl ui_bitmap_region_context_helper_0049b9b0(int param_1,int param_2)

{
  *(uint *)(*(int *)(param_1 + 8) + 0xb0) =
       (uint)(param_2 != 0) | *(uint *)(*(int *)(param_1 + 8) + 0xb0) & 0xfffffffe;
  return;
}


