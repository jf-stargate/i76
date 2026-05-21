/*
 * Program: i76shell.dll
 * Function: draw_vehicle_part_inventory_scroll_list
 * Entry: 10005b80
 * Signature: undefined __cdecl draw_vehicle_part_inventory_scroll_list(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl draw_vehicle_part_inventory_scroll_list(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = *(int *)(param_2 + 0x10);
  iVar1 = *(int *)(param_2 + 8);
  iVar6 = DAT_10051e60 + 2 + iVar5;
  clear_text_rect(DAT_100cc518,iVar1,iVar5,(*(int *)(param_2 + 0xc) - iVar1) + 1,
                  (*(int *)(param_2 + 0x14) - iVar5) + 1);
  param_2 = 0;
  iVar5 = DAT_10051e68;
  if (DAT_10051e68 < *(int *)(param_1 + 4)) {
    do {
      if (DAT_10051e68 + 10 <= iVar5) break;
      piVar2 = *(int **)(*(int *)(param_1 + 8) + iVar5 * 4);
      dVar3 = (double)*(int *)(*piVar2 + 0x4c) * _DAT_100412a0;
      if (dVar3 <= (double)piVar2[3]) {
        iVar4 = 2;
        if (dVar3 + dVar3 <= (double)piVar2[3]) {
          iVar4 = 1;
        }
      }
      else {
        iVar4 = 3;
      }
      param_2 = param_2 + *(int *)(&DAT_10043558 + *(int *)(*piVar2 + 0x1e) * 4) * iVar4;
      if (piVar2 != (int *)0x0) {
        draw_vehicle_part_damage_indicator(piVar2,iVar1 + 1,iVar6);
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,iVar1 + 1,iVar6,*(int *)(DAT_100cc52c + 0x408),(byte *)*piVar2,
                   (undefined *)0x0);
        iVar6 = iVar6 + DAT_10051e60;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(param_1 + 4));
  }
  if (0x20 < param_2) {
    param_2 = 0x20;
  }
  FUN_10031540(param_2 >> 1);
  return;
}


