/*
 * Program: i76shell.dll
 * Function: draw_string_from_glyph_sheet_object
 * Entry: 100157a0
 * Signature: undefined __thiscall draw_string_from_glyph_sheet_object(void * this, int param_1, int param_2, byte * param_3, undefined * param_4)
 */


/* i76shell localized glyph rename
   old_name: FUN_100157a0
   forced_name: draw_string_from_glyph_sheet_object
   basis: Object wrapper for drawing a string from a glyph sheet. */

void __thiscall
draw_string_from_glyph_sheet_object
          (void *this,int param_1,int param_2,byte *param_3,undefined *param_4)

{
  measure_and_draw_string_from_glyph_sheet
            (*(void **)((int)this + 0x410),param_1,param_2,*(int *)this,param_3,param_4);
  return;
}


