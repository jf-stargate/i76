/*
 * Program: i76shell.dll
 * Function: draw_glyph_from_glyph_sheet_object
 * Entry: 100157d0
 * Signature: undefined __thiscall draw_glyph_from_glyph_sheet_object(void * this, int param_1, int param_2, int param_3, undefined * param_4)
 */


/* i76shell locale/rich-text rename
   old_name: FUN_100157d0
   forced_name: draw_glyph_from_glyph_sheet_object
   basis: Wrapper that draws one glyph from shell glyph-sheet object through
   draw_single_glyph_to_shell_surfaces. */

void __thiscall
draw_glyph_from_glyph_sheet_object
          (void *this,int param_1,int param_2,int param_3,undefined *param_4)

{
  draw_single_glyph_to_shell_surfaces
            (*(void **)((int)this + 0x410),param_1,param_2,*(int *)this,param_3,param_4);
  return;
}


