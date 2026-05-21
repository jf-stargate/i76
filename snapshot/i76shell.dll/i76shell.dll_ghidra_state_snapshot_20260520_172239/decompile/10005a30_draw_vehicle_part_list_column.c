/*
 * Program: i76shell.dll
 * Function: draw_vehicle_part_list_column
 * Entry: 10005a30
 * Signature: undefined __cdecl draw_vehicle_part_list_column(int * param_1, int param_2)
 */


void __cdecl draw_vehicle_part_list_column(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  DAT_10051e6c = 0;
  iVar2 = *(int *)(param_2 + 8) + 1;
  iVar4 = *(int *)(param_2 + 0x10) + 2;
  clear_text_rect(DAT_100cc518,*(int *)(param_2 + 8),*(int *)(param_2 + 0x10),
                  (*(int *)(param_2 + 0xc) - *(int *)(param_2 + 8)) + -0xe,
                  (*(int *)(param_2 + 0x14) - *(int *)(param_2 + 0x10)) + 1);
  if (0 < *param_1) {
    do {
      piVar1 = *(int **)(param_1[2] + iVar3 * 4);
      if (piVar1 != (int *)0x0) {
        draw_vehicle_part_damage_indicator(piVar1,iVar2,iVar4);
        draw_vehicle_config_component_ui_overlays(piVar1);
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,iVar2,iVar4,*(int *)(DAT_100cc52c + 0x408),(byte *)*piVar1,
                   (undefined *)0x0);
      }
      iVar4 = iVar4 + DAT_10051e60;
      iVar3 = iVar3 + 1;
    } while (iVar3 < *param_1);
  }
  return;
}


