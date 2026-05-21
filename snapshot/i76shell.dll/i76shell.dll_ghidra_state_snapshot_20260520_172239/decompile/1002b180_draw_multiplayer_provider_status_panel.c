/*
 * Program: i76shell.dll
 * Function: draw_multiplayer_provider_status_panel
 * Entry: 1002b180
 * Signature: undefined __stdcall draw_multiplayer_provider_status_panel(void)
 */


void draw_multiplayer_provider_status_panel(void)

{
  byte local_20 [32];
  
  clear_text_rect(DAT_100cc518,0x116,0x3a,0xaa,0x12);
  clear_text_rect(DAT_100cc518,9,0x12e,0xcf,0x7c);
  clear_text_rect(DAT_100cc518,0xb,0x130,0x9f,0x10);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x120,0x3a,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0);
  wsprintfA((LPSTR)local_20,s__2_2d_1004c1a0,DAT_100f1f50);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xac,0x152,*(int *)(DAT_100cc52c + 0x408),local_20,(undefined *)0x0);
  if ((DAT_100d4024 & 0x8000) != 0) {
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,DAT_1004ba84,DAT_1004ba8c,*(int *)(DAT_100cc52c + 0x408),&DAT_1004c1a8,
               (undefined *)0x0);
  }
  if ((DAT_100d4024 & 0x4000) != 0) {
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,DAT_1004ba98,DAT_1004baa0,*(int *)(DAT_100cc52c + 0x408),&DAT_1004c1ac,
               (undefined *)0x0);
  }
  if ((DAT_100d4024 & 0x2000) != 0) {
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,DAT_1004baac,DAT_1004bab4,*(int *)(DAT_100cc52c + 0x408),&DAT_1004c1b0,
               (undefined *)0x0);
  }
  wsprintfA((LPSTR)local_20,&DAT_1004c1b4,DAT_100d4028);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x7e,400,*(int *)(DAT_100cc52c + 0x408),local_20,(undefined *)0x0);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xb,0x131,*(int *)(DAT_100cc52c + 0x408),(byte *)&DAT_100d4050,
             (undefined *)0x0);
  return;
}


