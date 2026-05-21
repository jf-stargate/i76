/*
 * Program: i76shell.dll
 * Function: prepare_or_clear_text_draw_context
 * Entry: 100398b0
 * Signature: undefined __thiscall prepare_or_clear_text_draw_context(void * this, undefined4 param_1, int param_2)
 */


/* i76shell localized glyph rename
   old_name: FUN_100398b0
   forced_name: prepare_or_clear_text_draw_context
   basis: Prepares or clears shell text draw context before text rendering. */

void __thiscall prepare_or_clear_text_draw_context(void *this,undefined4 param_1,int param_2)

{
  if (param_2 != 0) {
    FUN_100372b0(*(void **)((int)this + 0x18),param_1);
    return;
  }
  FUN_100372b0(*(void **)((int)this + 0x1c),param_1);
  return;
}


