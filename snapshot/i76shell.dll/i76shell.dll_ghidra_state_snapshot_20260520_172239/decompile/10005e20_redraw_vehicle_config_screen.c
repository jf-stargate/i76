/*
 * Program: i76shell.dll
 * Function: redraw_vehicle_config_screen
 * Entry: 10005e20
 * Signature: undefined __stdcall redraw_vehicle_config_screen(void)
 */


void redraw_vehicle_config_screen(void)

{
  undefined **ppuVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  
  DAT_10051cd0 = *(int *)(DAT_100cc52c + 0x40c) + 2;
  DAT_10051e60 = DAT_10051cd0;
  if (DAT_10051dc0 != 0) {
    FUN_1002bc10();
  }
  iVar3 = 0;
  iVar4 = DAT_100433e0 + -0x4b;
  iVar2 = DAT_100433e8 + 1;
  if (0 < DAT_100433dc) {
    ppuVar1 = &PTR_s_Engine_10043360;
    do {
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar4,iVar2 + 3,*(int *)(DAT_100cc520 + 0x408),*ppuVar1,
                 (undefined *)0x0);
      FUN_100315d0(0xfe,iVar2);
      iVar2 = iVar2 + DAT_10051e60;
      iVar3 = iVar3 + 1;
      ppuVar1 = ppuVar1 + 1;
    } while (iVar3 < DAT_100433dc);
  }
  draw_vehicle_config_section_labels(0x100433f8);
  iVar3 = 0;
  iVar4 = DAT_10043440 + -0x4b;
  iVar2 = DAT_10043448 + 1;
  if (0 < DAT_1004343c) {
    ppuVar1 = &PTR_s_Special_1_10043398;
    do {
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar4,iVar2 + 3,*(int *)(DAT_100cc520 + 0x408),*ppuVar1,
                 (undefined *)0x0);
      FUN_100315d0(0xfe,iVar2);
      iVar2 = iVar2 + DAT_10051e60;
      iVar3 = iVar3 + 1;
      ppuVar1 = ppuVar1 + 1;
    } while (iVar3 < DAT_1004343c);
  }
  *(undefined4 *)(PTR_DAT_100432c0 + 0x1e) = 2;
  draw_vehicle_part_list_column(DAT_1005209c,0x100433d8);
  *(undefined4 *)(PTR_DAT_100432c0 + 0x1e) = 7;
  draw_vehicle_part_list_column(DAT_100520a4,0x100433f8);
  *(undefined4 *)(PTR_DAT_100432c0 + 0x1e) = 0xc;
  draw_vehicle_part_list_column(DAT_100520ac,0x10043438);
  *(undefined4 *)(PTR_DAT_100432c0 + 0x1e) = 8;
  draw_vehicle_part_list_column_indented(DAT_100520a8,0x10043418);
  if (DAT_100520a0 != 0) {
    draw_vehicle_part_inventory_scroll_list(DAT_100520a0,0x10043458);
  }
  FUN_10025600(0x10043478);
  if (DAT_10051dc0 == 0) {
    pbVar5 = (byte *)(&DAT_100581a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x231);
    iVar4 = *(int *)(DAT_100cc52c + 0x408);
    iVar2 = 10;
  }
  else {
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x69,2,*(int *)(DAT_100cc52c + 0x408),
               (byte *)(&DAT_100581a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x231),(undefined *)0x0);
    pbVar5 = &DAT_100581b4 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
    iVar4 = *(int *)(DAT_100cc52c + 0x408);
    iVar2 = 0x11;
  }
  measure_and_draw_string_from_glyph_sheet(DAT_100cc518,0x52,iVar2,iVar4,pbVar5,(undefined *)0x0);
  FUN_10005cb0();
  return;
}


