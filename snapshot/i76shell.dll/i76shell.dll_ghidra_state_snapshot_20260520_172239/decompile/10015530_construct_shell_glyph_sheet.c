/*
 * Program: i76shell.dll
 * Function: construct_shell_glyph_sheet
 * Entry: 10015530
 * Signature: int * __thiscall construct_shell_glyph_sheet(void * this, int param_1, int param_2)
 */


/* i76shell glyph/font rename
   old_name: FUN_10015530
   suggested_name: construct_shell_glyph_bitmap_table
   basis: ShellMain feeds DATABASE.MW2 records 65-71 into this constructor/parser; records are
   confirmed glyph sheets.
   
   i76shell text/glyph rename
   old_name: construct_shell_glyph_bitmap_table
   suggested_name: construct_shell_glyph_sheet
   basis: Constructs a thin wrapper around raw DATABASE.MW2 glyph-sheet records 65-71.
   
   i76shell forced text/glyph rename
   old_name: construct_shell_glyph_bitmap_table
   forced_name: construct_shell_glyph_sheet
   basis: Constructs shell glyph-sheet wrapper from DATABASE.MW2 records 65-71. */

int * __thiscall construct_shell_glyph_sheet(void *this,int param_1,int param_2)

{
  undefined4 uVar1;
  
  *(int *)((int)this + 0x410) = param_2;
  *(int *)this = param_1;
  *(int *)((int)this + 0x408) = param_1;
  uVar1 = get_shell_glyph_sheet_height(param_1);
  *(undefined4 *)((int)this + 0x40c) = uVar1;
  return this;
}


