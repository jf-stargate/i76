/*
 * Program: i76shell.dll
 * Function: redraw_vehicle_part_dialog_list_entries
 * Entry: 1000a440
 * Signature: undefined __cdecl redraw_vehicle_part_dialog_list_entries(int param_1)
 */


void __cdecl redraw_vehicle_part_dialog_list_entries(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined4 *local_114;
  int local_110;
  int local_10c;
  int local_108;
  int local_104;
  byte local_100 [256];
  
  iVar2 = *(int *)(param_1 + 0x14);
  local_114 = &DAT_10053398;
  iVar1 = *DAT_100533b8 + *(int *)(param_1 + 4);
  iVar8 = DAT_100533b8[1] + *(int *)(param_1 + 0xc);
  iVar7 = (*(int *)(param_1 + 8) - *(int *)(param_1 + 4)) + 1;
  iVar4 = (*(int *)(param_1 + 0x10) - *(int *)(param_1 + 0xc)) + 1;
  iVar6 = iVar8 + 2;
  local_108 = iVar1 + -1 + iVar7;
  local_104 = iVar8 + -1 + iVar4;
  local_110 = iVar1;
  local_10c = iVar8;
  uVar5 = lock_shell_surface_for_draw((int)DAT_100cc518);
  if ((char)uVar5 == '\0') {
    blit_or_fill_rect_clipped
              ((int *)&local_114,0,0,(int *)((int)DAT_100cc518 + 0x6c),iVar1,iVar8,0xffffffff);
    blit_or_fill_rect_clipped
              ((int *)&local_114,0,0,(int *)((int)DAT_100cc518 + 0xa8),iVar1,iVar8,0xffffffff);
    unlock_shell_surface_after_draw((int)DAT_100cc518);
  }
  mark_shell_surface_dirty_rect(DAT_100cc518,iVar1,iVar8,iVar7,iVar4);
  iVar4 = 0;
  if (0 < *(int *)(iVar2 + 4)) {
    do {
      piVar3 = *(int **)(*(int *)(iVar2 + 8) + iVar4 * 4);
      draw_vehicle_part_damage_indicator(piVar3,iVar1 + 3,iVar6);
      iVar7 = piVar3[4];
      if (iVar7 == 1) {
        iVar7 = *piVar3;
        pcVar9 = s____s_10044298;
LAB_1000a572:
        wsprintfA((LPSTR)local_100,pcVar9,iVar7);
      }
      else {
        if (iVar7 == 2) {
          iVar7 = *piVar3;
          pcVar9 = s____s_100442a0;
          goto LAB_1000a572;
        }
        if (iVar7 == 3) {
          iVar7 = *piVar3;
          pcVar9 = s____s_100442a8;
          goto LAB_1000a572;
        }
      }
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,iVar1 + 3,iVar6,*(int *)(DAT_100cc52c + 0x408),local_100,
                 (undefined *)0x0);
      iVar6 = iVar6 + DAT_10051cd0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(iVar2 + 4));
  }
  return;
}


