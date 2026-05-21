/*
 * Program: i76shell.dll
 * Function: get_shell_glyph_sheet_height
 * Entry: 1003e419
 * Signature: undefined4 __cdecl get_shell_glyph_sheet_height(int param_1)
 */


/* i76shell glyph/font rename
   old_name: FUN_1003e419
   suggested_name: parse_shell_glyph_bitmap_table_header
   basis: Candidate helper referenced by glyph-sheet object construction/use path; name cautious.
   
   i76shell text/glyph rename
   old_name: parse_shell_glyph_bitmap_table_header
   suggested_name: get_shell_glyph_sheet_height
   basis: Returns *(glyph_sheet + 8), the glyph sheet height.
   
   i76shell forced text/glyph rename
   old_name: parse_shell_glyph_bitmap_table_header
   forced_name: get_shell_glyph_sheet_height
   basis: Returns *(glyph_sheet + 8), confirmed glyph height. */

undefined4 __cdecl get_shell_glyph_sheet_height(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


