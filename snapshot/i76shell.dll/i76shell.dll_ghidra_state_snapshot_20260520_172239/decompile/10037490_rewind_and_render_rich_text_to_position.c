/*
 * Program: i76shell.dll
 * Function: rewind_and_render_rich_text_to_position
 * Entry: 10037490
 * Signature: undefined __fastcall rewind_and_render_rich_text_to_position(undefined4 * param_1)
 */


/* i76shell localized glyph rename
   old_name: FUN_10037490
   forced_name: rewind_and_render_rich_text_to_position
   basis: Rich-text object positioning/render helper. */

void __fastcall rewind_and_render_rich_text_to_position(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = param_1[0x10];
  param_1[0x10] = 0xffffffff;
  if (-1 < iVar1) {
    do {
      process_rich_text_glyph_stream(param_1);
    } while ((int)param_1[0x10] < iVar1);
  }
  return;
}


