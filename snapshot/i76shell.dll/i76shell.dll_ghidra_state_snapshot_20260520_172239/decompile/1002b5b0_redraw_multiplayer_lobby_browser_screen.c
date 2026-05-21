/*
 * Program: i76shell.dll
 * Function: redraw_multiplayer_lobby_browser_screen
 * Entry: 1002b5b0
 * Signature: undefined __stdcall redraw_multiplayer_lobby_browser_screen(void)
 */


void redraw_multiplayer_lobby_browser_screen(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  int iVar8;
  bool bVar9;
  int local_8 [2];
  
  clear_text_rect(DAT_100cc518,0x1c7,0x37,0xa6,0x6c);
  clear_text_rect(DAT_100cc518,0xe6,0xa9,0x18c,0x10e);
  clear_text_rect(DAT_100cc518,0xb,0x2c,0xa0,0xe);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xc,0x2d,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0);
  FUN_10031570(*(int *)(DAT_100f21a8 + DAT_100f1d5c * 0x1c));
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x14a,399,*(int *)(DAT_100cc52c + 0x408),
             (byte *)(&DAT_100581a0 + DAT_100f1d5c * 0x231),(undefined *)0x0);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x124,0x1a5,*(int *)(DAT_100cc52c + 0x408),
             &DAT_100581b4 + DAT_100f1d5c * 0x8c4,(undefined *)0x0);
  DAT_100d4044 = find_current_vehicle_part_by_type_and_name(2,DAT_100d1dac);
  DAT_100d404c = find_current_vehicle_part_by_type_and_name(3,DAT_100d1dc0);
  DAT_100d4048 = find_current_vehicle_part_by_type_and_name(4,DAT_100d1dbc);
  clear_pointer_list(DAT_100d403c);
  populate_equipped_vehicle_part_selection_list(&LAB_10034350,(int)DAT_100d403c,DAT_100d1db8);
  clear_pointer_list(DAT_100d4038);
  populate_matching_vehicle_part_selection_list
            (is_special_equipment_part_type,DAT_100d4038,DAT_100d1db4);
  clear_pointer_list(DAT_100d4040);
  populate_matching_vehicle_part_selection_list(&LAB_10034360,DAT_100d4040,DAT_100d1db0);
  FUN_100343a0(*(int *)(DAT_100c5ad8 + 0x38));
  piVar2 = DAT_100d4038;
  iVar4 = 0x3a;
  local_8[0] = 0;
  if (0 < DAT_100d4038[1]) {
    do {
      puVar1 = *(undefined4 **)(piVar2[2] + local_8[0] * 4);
      if (puVar1 != (undefined4 *)0x0) {
        pbVar5 = (byte *)*puVar1;
        iVar3 = 5;
        bVar9 = true;
        pbVar6 = pbVar5 + 0x2e;
        pbVar7 = &DAT_1004c1d0;
        do {
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          bVar9 = *pbVar6 == *pbVar7;
          pbVar6 = pbVar6 + 1;
          pbVar7 = pbVar7 + 1;
        } while (bVar9);
        if (!bVar9) {
          measure_and_draw_string_from_glyph_sheet
                    (DAT_100cc518,0x1d6,iVar4,*(int *)(DAT_100cc52c + 0x408),pbVar5,(undefined *)0x0
                    );
          iVar4 = iVar4 + DAT_10051e60;
        }
      }
      local_8[0] = local_8[0] + 1;
    } while (local_8[0] < piVar2[1]);
  }
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x1d6,0xb1,*(int *)(DAT_100cc52c + 0x408),*DAT_100d4044,(undefined *)0x0);
  iVar4 = DAT_10051e60 + 0xb1;
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x1d6,iVar4,*(int *)(DAT_100cc52c + 0x408),*DAT_100d404c,(undefined *)0x0)
  ;
  iVar4 = iVar4 + DAT_10051e60;
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x1d6,iVar4,*(int *)(DAT_100cc52c + 0x408),*DAT_100d4048,(undefined *)0x0)
  ;
  piVar2 = DAT_100d403c;
  iVar4 = iVar4 + DAT_10051e60;
  iVar3 = 0;
  if (0 < DAT_100d403c[1]) {
    do {
      if (3 < iVar3) break;
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,0x1d6,iVar4,*(int *)(DAT_100cc52c + 0x408),
                 (byte *)**(undefined4 **)(piVar2[2] + iVar3 * 4),(undefined *)0x0);
      iVar4 = iVar4 + DAT_10051e60;
      iVar3 = iVar3 + 1;
    } while (iVar3 < piVar2[1]);
  }
  iVar4 = DAT_100f21b0;
  switch(DAT_100d217c) {
  case 0:
    iVar3 = 0x152;
    clear_text_rect(DAT_100cc518,0xb,0x27,0xce,0x1a4);
    clear_text_rect(DAT_100cc518,0x116,0x3a,0xaa,0x12);
    wsprintfA((LPSTR)local_8,s__2_2d_1004c198,DAT_100f1f50 + -1);
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0xad,0x120,*(int *)(DAT_100cc52c + 0x408),(byte *)local_8,
               (undefined *)0x0);
    draw_shell_text_at_position(&DAT_100f1d90,0xc,0x2d);
    draw_shell_text_at_position(&DAT_100d4488 + DAT_100f1d60 * 0x8ec,0x120,0x3a);
    iVar8 = 1;
    if (1 < DAT_100f1f50) {
      pbVar5 = (byte *)&DAT_100d4d74;
      do {
        draw_shell_text_at_position(pbVar5,0x14,iVar3);
        iVar3 = iVar3 + DAT_10051e60;
        iVar8 = iVar8 + 1;
        pbVar5 = pbVar5 + 0x8ec;
      } while (iVar8 < DAT_100f1f50);
    }
    draw_multiplayer_map_or_mission_list_page(iVar4);
    return;
  case 1:
    break;
  case 2:
    draw_multiplayer_map_or_mission_list_page(DAT_100f21b0);
    return;
  case 3:
    draw_multiplayer_map_or_mission_list_page(DAT_100f21b0);
    draw_multiplayer_provider_status_panel();
    return;
  case 4:
    draw_multiplayer_map_or_mission_list_page(DAT_100f21b0);
    draw_multiplayer_provider_status_panel();
    return;
  case 5:
    draw_multiplayer_map_or_mission_list_page(DAT_100f21b0);
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x120,0x3a,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0
              );
    return;
  case 6:
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x120,0x3a,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0
              );
    return;
  case 7:
  case 8:
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x120,0x3a,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0
              );
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0xc,0x2d,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0);
    return;
  case 9:
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x120,0x3a,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0
              );
    return;
  default:
    return;
  }
  iVar3 = 0x95;
  clear_text_rect(DAT_100cc518,0xb,0x71,0xce,0xa2);
  if (iVar4 < DAT_1004b2f4) {
    iVar8 = iVar4 + 6;
    pbVar5 = (byte *)(s_Oil_Well_Well_1004b7e0 + iVar4 * 0x2d);
    do {
      if (iVar8 <= iVar4) break;
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,0x28,iVar3,*(int *)(DAT_100cc52c + 0x408),pbVar5,(undefined *)0x0);
      pbVar5 = pbVar5 + 0x2d;
      iVar3 = iVar3 + DAT_10051e60;
      iVar4 = iVar4 + 1;
    } while (iVar4 < DAT_1004b2f4);
  }
  draw_shell_text_at_position((byte *)(s_Oil_Well_Well_1004b7e0 + DAT_100d4474 * 0x2d),0x28,0x6d);
  draw_shell_text_at_position(&DAT_100f1d90,0x120,0x3a);
  return;
}


