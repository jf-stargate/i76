/*
 * Program: i76shell.dll
 * Function: draw_vehicle_part_list_column_indented
 * Entry: 10005ad0
 * Signature: undefined __cdecl draw_vehicle_part_list_column_indented(int param_1, int param_2)
 */


void __cdecl draw_vehicle_part_list_column_indented(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  DAT_10051e6c = 0;
  iVar1 = *(int *)(param_2 + 0x10);
  iVar3 = iVar1 + 2;
  clear_text_rect(DAT_100cc518,*(int *)(param_2 + 8),iVar1,
                  (*(int *)(param_2 + 0xc) - *(int *)(param_2 + 8)) + -0xe,
                  (*(int *)(param_2 + 0x14) - iVar1) + 1);
  if (0 < *(int *)(param_1 + 4)) {
    do {
      piVar2 = *(int **)(*(int *)(param_1 + 8) + iVar4 * 4);
      if (piVar2 != (int *)0x0) {
        draw_vehicle_part_damage_indicator
                  (piVar2,*(int *)(param_2 + 8) + 1,*(int *)(param_2 + 0x10) + 2);
        draw_vehicle_config_component_ui_overlays(piVar2);
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,*(int *)(param_2 + 8) + 1,iVar3,*(int *)(DAT_100cc52c + 0x408),
                   (byte *)*piVar2,(undefined *)0x0);
        iVar3 = iVar3 + DAT_10051e60;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(param_1 + 4));
  }
  return;
}


