/*
 * Program: i76shell.dll
 * Function: draw_vehicle_config_section_labels
 * Entry: 10005820
 * Signature: undefined __cdecl draw_vehicle_config_section_labels(int param_1)
 */


void __cdecl draw_vehicle_config_section_labels(int param_1)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 8) + -0x4b;
  iVar3 = *(int *)(param_1 + 0x10) + 1;
  iVar1 = 0;
  if (0 < DAT_10051f70) {
    pbVar2 = &DAT_10051f78;
    do {
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar4,iVar3 + 3,*(int *)(DAT_100cc520 + 0x408),pbVar2,(undefined *)0x0
                );
      FUN_100315d0(0xfe,iVar3);
      iVar3 = iVar3 + DAT_10051e60;
      iVar1 = iVar1 + 1;
      pbVar2 = pbVar2 + 0x10;
    } while (iVar1 < DAT_10051f70);
  }
  iVar1 = 0;
  if (0 < DAT_10051fac) {
    pbVar2 = &DAT_10051e70;
    do {
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar4,iVar3 + 3,*(int *)(DAT_100cc520 + 0x408),pbVar2,(undefined *)0x0
                );
      FUN_100315d0(0xfe,iVar3);
      iVar3 = iVar3 + DAT_10051e60;
      iVar1 = iVar1 + 1;
      pbVar2 = pbVar2 + 0x10;
    } while (iVar1 < DAT_10051fac);
  }
  iVar1 = 0;
  if (0 < DAT_10051f6c) {
    pbVar2 = &DAT_10051cb0;
    do {
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar4,iVar3 + 3,*(int *)(DAT_100cc520 + 0x408),pbVar2,(undefined *)0x0
                );
      FUN_100315d0(0xfe,iVar3);
      iVar3 = iVar3 + DAT_10051e60;
      iVar1 = iVar1 + 1;
      pbVar2 = pbVar2 + 0x10;
    } while (iVar1 < DAT_10051f6c);
  }
  iVar1 = 0;
  if (0 < DAT_10051e64) {
    pbVar2 = &DAT_10051e20;
    do {
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar4,iVar3 + 3,*(int *)(DAT_100cc520 + 0x408),pbVar2,(undefined *)0x0
                );
      FUN_100315d0(0xfe,iVar3);
      iVar3 = iVar3 + DAT_10051e60;
      iVar1 = iVar1 + 1;
      pbVar2 = pbVar2 + 0x10;
    } while (iVar1 < DAT_10051e64);
  }
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar4,0xff,*(int *)(DAT_100cc520 + 0x408),PTR_DAT_10043390,
             (undefined *)0x0);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x6c,0xfb,*(int *)(DAT_100cc52c + 0x408),PTR_s__45_CAL_10043394,
             (undefined *)0x0);
  if (DAT_10051dc0 != 0) {
    FUN_100315d0(0xfe,0x14c);
    clear_text_rect(DAT_100cc518,0x69,0x14b,0x82,0x11);
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x6c,0x14c,*(int *)(DAT_100cc52c + 0x408),(byte *)&DAT_10051cd8,
               (undefined *)0x0);
  }
  return;
}


