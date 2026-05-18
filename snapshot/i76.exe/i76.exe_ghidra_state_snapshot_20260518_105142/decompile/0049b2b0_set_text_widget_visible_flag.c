/*
 * Program: i76.exe
 * Function: set_text_widget_visible_flag
 * Entry: 0049b2b0
 * Signature: undefined __cdecl set_text_widget_visible_flag(int param_1, int param_2)
 */


/* cgpt rename v4: Sets or clears bit 0x02 in a text/widget flags field. */

void __cdecl set_text_widget_visible_flag(int param_1,int param_2)

{
  *(uint *)(*(int *)(param_1 + 8) + 0x94) =
       -(uint)(param_2 != 0) & 2 | *(uint *)(*(int *)(param_1 + 8) + 0x94) & 0xfffffffd;
  return;
}


