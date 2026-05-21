/*
 * Program: i76shell.dll
 * Function: draw_shell_text_at_position
 * Entry: 1002e2c0
 * Signature: undefined __cdecl draw_shell_text_at_position(byte * param_1, int param_2, int param_3)
 */


void __cdecl draw_shell_text_at_position(byte *param_1,int param_2,int param_3)

{
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,param_2,param_3,*(int *)(DAT_100cc52c + 0x408),param_1,(undefined *)0x0);
  return;
}


