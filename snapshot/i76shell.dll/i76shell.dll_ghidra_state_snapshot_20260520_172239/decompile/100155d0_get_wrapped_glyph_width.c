/*
 * Program: i76shell.dll
 * Function: get_wrapped_glyph_width
 * Entry: 100155d0
 * Signature: undefined __thiscall get_wrapped_glyph_width(void * this, int param_1)
 */


/* i76shell forced text/glyph rename
   old_name: FUN_100155d0
   forced_name: get_wrapped_glyph_width
   basis: Wrapper method around get_glyph_width for glyph-sheet object. */

void __thiscall get_wrapped_glyph_width(void *this,int param_1)

{
  get_glyph_width(*(int *)this,param_1);
  return;
}


