/*
 * Program: i76shell.dll
 * Function: draw_ascii_string_from_glyph_sheet
 * Entry: 1003e5d7
 * Signature: undefined __cdecl draw_ascii_string_from_glyph_sheet(int * param_1, int param_2, int param_3, int param_4, byte * param_5, int param_6)
 */


/* i76shell text/glyph rename
   old_name: FUN_1003e5d7
   suggested_name: draw_string_from_glyph_sheet
   basis: Loops over byte string, blits each glyph, and advances x by glyph width.
   
   i76shell forced text/glyph rename
   old_name: draw_string_from_glyph_sheet
   forced_name: draw_ascii_string_from_glyph_sheet
   basis: Byte-indexed string draw loop using glyph-sheet character indices.
   
   i76shell locale/rich-text rename
   old_name: draw_ascii_string_from_glyph_sheet
   forced_name: draw_ascii_string_from_glyph_sheet
   basis: Simple byte-indexed draw loop. */

void __cdecl
draw_ascii_string_from_glyph_sheet
          (int *param_1,int param_2,int param_3,int param_4,byte *param_5,int param_6)

{
  int iVar1;
  
  do {
    iVar1 = blit_glyph_to_surface(param_1,param_2,param_3,param_4,(uint)*param_5,param_6);
    param_2 = param_2 + iVar1;
    param_5 = param_5 + 1;
  } while (*param_5 != 0);
  return;
}


