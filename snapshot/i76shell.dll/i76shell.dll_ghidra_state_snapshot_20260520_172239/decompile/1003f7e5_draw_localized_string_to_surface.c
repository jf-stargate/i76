/*
 * Program: i76shell.dll
 * Function: draw_localized_string_to_surface
 * Entry: 1003f7e5
 * Signature: undefined __cdecl draw_localized_string_to_surface(int * param_1, int param_2, int param_3, int param_4, ushort * param_5, int param_6)
 */


/* i76shell locale/rich-text rename
   old_name: FUN_1003f7e5
   forced_name: get_or_update_character_stride
   basis: Reads DAT_1004efa0 and calls set_character_stride_or_locale_mode.
   
   i76shell localized glyph rename
   old_name: get_or_update_character_stride
   forced_name: draw_localized_string_to_surface
   basis: Localized string draw loop; advances source pointer by DAT_1004efa0 after each glyph. */

void __cdecl
draw_localized_string_to_surface
          (int *param_1,int param_2,int param_3,int param_4,ushort *param_5,int param_6)

{
  int iVar1;
  
  do {
    iVar1 = blit_localized_glyph_to_surface(param_1,param_2,param_3,param_4,(uint)*param_5,param_6);
    param_2 = param_2 + iVar1;
    param_5 = (ushort *)((int)param_5 + DAT_1004efa0);
  } while ((char)*param_5 != '\0');
  return;
}


