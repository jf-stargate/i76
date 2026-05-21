/*
 * Program: i76shell.dll
 * Function: handle_mission_selection_screen
 * Entry: 10027f20
 * Signature: undefined __cdecl handle_mission_selection_screen(void * param_1)
 */


void __cdecl handle_mission_selection_screen(void *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  byte *pbVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  byte *pbVar14;
  LPVOID pvVar15;
  byte local_28 [8];
  byte local_20 [32];
  
  iVar3 = DAT_100f219c;
  DAT_10051e60 = 0x11;
  DAT_10051cd0 = 0x11;
  iVar7 = 1;
  DAT_100d21a8 = redraw_multiplayer_lobby_browser_screen;
  DAT_10051dc0 = 1;
  FUN_1002a3b0();
  *(undefined4 *)(DAT_100c5ad8 + 0x20) = 3;
  if ((((1 < DAT_100d217c) && (DAT_100d217c != 6)) && (DAT_100d217c != 2)) &&
     ((DAT_100d217c != 4 && (DAT_100d217c != 8)))) {
    initialize_directplay_connection_for_mode();
  }
  switch(DAT_100d217c) {
  case 0:
    if (DAT_1004b2f8 <= DAT_100d4474) {
      DAT_100d4474 = 0;
    }
    load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,(LPVOID)0x18);
    FUN_1002af00();
    iVar12 = 0x152;
    clear_text_rect(DAT_100cc518,0xb,0x27,0xce,0x1a4);
    clear_text_rect(DAT_100cc518,0x116,0x3a,0xaa,0x12);
    wsprintfA((LPSTR)local_28,s__2_2d_1004c198,DAT_100f1f50 + -1);
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0xad,0x120,*(int *)(DAT_100cc52c + 0x408),local_28,(undefined *)0x0);
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0xc,0x2d,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0);
    draw_shell_text_at_position(&DAT_100d4488 + DAT_100f1d60 * 0x8ec,0x120,0x3a);
    if (1 < DAT_100f1f50) {
      pbVar14 = (byte *)&DAT_100d4d74;
      do {
        draw_shell_text_at_position(pbVar14,0x14,iVar12);
        iVar12 = iVar12 + DAT_10051e60;
        iVar7 = iVar7 + 1;
        pbVar14 = pbVar14 + 0x8ec;
      } while (iVar7 < DAT_100f1f50);
    }
    draw_multiplayer_map_or_mission_list_page(0);
    goto switchD_10027f9c_default;
  case 1:
    update_victory_record_for_selected_map();
    *(undefined4 *)(DAT_100c5ad8 + 0x20) = 4;
    if (DAT_1004b2f4 <= DAT_100d4474) {
      DAT_100d4474 = 0;
    }
    load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,(LPVOID)0x19);
    iVar12 = 0x95;
    clear_text_rect(DAT_100cc518,0xb,0x71,0xce,0xa2);
    iVar7 = 0;
    if (0 < DAT_1004b2f4) {
      pcVar8 = s_Oil_Well_Well_1004b7e0;
      do {
        if (0x1004b8ed < (int)pcVar8) break;
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,0x28,iVar12,*(int *)(DAT_100cc52c + 0x408),(byte *)pcVar8,
                   (undefined *)0x0);
        pcVar8 = pcVar8 + 0x2d;
        iVar12 = iVar12 + DAT_10051e60;
        iVar7 = iVar7 + 1;
      } while (iVar7 < DAT_1004b2f4);
    }
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x28,0x6d,*(int *)(DAT_100cc52c + 0x408),
               (byte *)(s_Oil_Well_Well_1004b7e0 + DAT_100d4474 * 0x2d),(undefined *)0x0);
    draw_shell_text_at_position(&DAT_100f1d90,0x120,0x3a);
    if ((DAT_100d4478 == 0) ||
       (clear_text_rect(DAT_100cc518,9,0x123,0xce,200),
       *(int *)(DAT_100d4478 + 4 + DAT_100d4474 * 8) == -1)) goto switchD_10027f9c_default;
    uVar4 = 0xffffffff;
    pcVar8 = (char *)(&DAT_100581a0 + *(int *)(DAT_100d4478 + DAT_100d4474 * 8) * 0x231);
    do {
      pcVar9 = pcVar8;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pbVar14 = (byte *)(pcVar9 + -uVar4);
    pbVar10 = local_20;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pbVar10 = *(undefined4 *)pbVar14;
      pbVar14 = pbVar14 + 4;
      pbVar10 = pbVar10 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar10 = *pbVar14;
      pbVar14 = pbVar14 + 1;
      pbVar10 = pbVar10 + 1;
    }
    iVar7 = *(int *)(DAT_100cc52c + 0x408);
    pbVar14 = local_20;
    iVar13 = 0x134;
    iVar12 = 0x10;
    break;
  case 2:
    if (DAT_1004b2f8 <= DAT_100d4474) {
      DAT_100d4474 = 0;
    }
    DAT_100f1f50 = 2;
    load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,(LPVOID)0x14);
    draw_multiplayer_map_or_mission_list_page(0);
    iVar7 = *(int *)(DAT_100cc52c + 0x408);
    pbVar14 = &DAT_100f1d90;
    iVar13 = 0x3a;
    iVar12 = 0x120;
    break;
  case 3:
    if (DAT_1004b2f8 <= DAT_100d4474) {
      DAT_100d4474 = 0;
    }
    load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,(LPVOID)0x13);
    draw_multiplayer_map_or_mission_list_page(0);
    if (DAT_100f1f50 == 0) {
      DAT_100f1f50 = 4;
      draw_multiplayer_provider_status_panel();
      goto switchD_10027f9c_default;
    }
    goto LAB_10028383;
  case 4:
    if (DAT_1004b2f8 <= DAT_100d4474) {
      DAT_100d4474 = 0;
    }
    load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,(LPVOID)0x13);
    draw_multiplayer_map_or_mission_list_page(0);
    if (DAT_100f1f50 == 0) {
      DAT_100f1f50 = 4;
    }
LAB_10028383:
    draw_multiplayer_provider_status_panel();
    goto switchD_10027f9c_default;
  case 5:
    if (DAT_1004b2f8 <= DAT_100d4474) {
      DAT_100d4474 = 0;
    }
    DAT_100f1f50 = 2;
    load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,(LPVOID)0x16);
    draw_multiplayer_map_or_mission_list_page(0);
    iVar7 = *(int *)(DAT_100cc52c + 0x408);
    pbVar14 = &DAT_100f1d90;
    iVar13 = 0x3a;
    iVar12 = 0x120;
    break;
  case 6:
    pvVar15 = (LPVOID)0x15;
    goto LAB_10028393;
  case 7:
  case 8:
    load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,(LPVOID)0x12);
    measure_and_draw_string_from_glyph_sheet
              (DAT_100cc518,0x120,0x3a,*(int *)(DAT_100cc52c + 0x408),&DAT_100f1d90,(undefined *)0x0
              );
    pbVar14 = &DAT_100f1d90;
    iVar7 = *(int *)(DAT_100cc52c + 0x408);
    iVar13 = 0x2d;
    iVar12 = 0xc;
    break;
  case 9:
    pvVar15 = (LPVOID)0x17;
LAB_10028393:
    load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,pvVar15);
    pbVar14 = &DAT_100f1d90;
    iVar7 = *(int *)(DAT_100cc52c + 0x408);
    iVar13 = 0x3a;
    iVar12 = 0x120;
    break;
  default:
    goto switchD_10027f9c_default;
  }
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,iVar12,iVar13,iVar7,pbVar14,(undefined *)0x0);
switchD_10027f9c_default:
  redraw_multiplayer_lobby_browser_screen();
  iVar7 = -1;
  bVar2 = false;
  DAT_100f1dbc = 0;
  DAT_100f1db8 = (uint)(DAT_100d218c == 0);
  if (DAT_100f1db8 != 0) {
    piVar6 = &DAT_1004bb68;
    do {
      if (((!bVar2) || (iVar7 != -1)) && (iVar7 != *piVar6)) {
        bVar2 = false;
        iVar7 = *piVar6;
      }
      if ((!bVar2) && (piVar6[2] != 0)) {
        if (*piVar6 == -1) {
          puVar11 = &DAT_100f1dc0;
          for (iVar7 = 100; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar11 = 0;
            puVar11 = puVar11 + 1;
          }
          DAT_100f1dbc = -1;
          break;
        }
        (&DAT_100f1dc0)[DAT_100f1dbc * 2] = *piVar6;
        iVar12 = piVar6[1];
        (&DAT_100f1dc4)[DAT_100f1dbc * 2] = iVar12;
        DAT_100f1dbc = DAT_100f1dbc + 1;
        if (iVar12 == -1) {
          bVar2 = true;
        }
      }
      piVar6 = piVar6 + 0xb;
    } while (piVar6 < s_MacRill_III_1004bda4);
  }
  DAT_100d2184 = 0;
  SetCursor(DAT_100d216c);
  FUN_1001eca0(&LAB_10028610);
  if (iVar3 == 0) {
    if ((DAT_100d217c == 8) || (DAT_100d217c == 4)) {
      if ((DAT_100d21b0 == 0) && (DAT_100d21b4 == 0)) {
        read_internet_list_file();
      }
    }
    else if ((DAT_100d217c == 6) && (DAT_1004b2f0 == 1)) {
      DAT_1004b2f0 = 0;
      read_phone_list_file();
      return;
    }
  }
  return;
}


