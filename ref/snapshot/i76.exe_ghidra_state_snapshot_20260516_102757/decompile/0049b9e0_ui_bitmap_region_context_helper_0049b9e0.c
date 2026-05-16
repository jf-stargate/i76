/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049b9e0
 * Entry: 0049b9e0
 * Signature: undefined __cdecl ui_bitmap_region_context_helper_0049b9e0(int param_1, int param_2)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049b9e0. Remove
   duplicated UI/region wording. */

void __cdecl ui_bitmap_region_context_helper_0049b9e0(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  puVar2 = g_static_text_overlay_list;
  if (param_2 != 0) {
    for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
      *(uint *)(puVar2[2] + 0xb0) = *(uint *)(puVar2[2] + 0xb0) & 0xfffffeff;
    }
  }
  *(uint *)(iVar1 + 0xb0) = -(uint)(param_2 != 0) & 0x100 | *(uint *)(iVar1 + 0xb0) & 0xfffffeff;
  return;
}


