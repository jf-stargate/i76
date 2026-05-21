/*
 * Program: i76shell.dll
 * Function: get_glyph_width
 * Entry: 1003e42c
 * Signature: undefined4 __cdecl get_glyph_width(int param_1, int param_2)
 */


/* i76shell text/glyph rename
   old_name: FUN_1003e42c
   suggested_name: get_glyph_width
   basis: Reads glyph offset table and returns the first dword of a glyph payload, confirmed as
   glyph width.
   
   i76shell forced text/glyph rename
   old_name: get_glyph_width
   forced_name: get_glyph_width
   basis: Reads glyph offset table and returns first dword of glyph payload. */

undefined4 __cdecl get_glyph_width(int param_1,int param_2)

{
  return *(undefined4 *)(*(int *)(param_2 * 4 + param_1 + 0x10) + param_1);
}


