/*
 * Program: i76shell.dll
 * Function: handle_save_game_scene_selection
 * Entry: 100147a0
 * Signature: undefined __stdcall handle_save_game_scene_selection(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void handle_save_game_scene_selection(void)

{
  byte bVar1;
  int *piVar2;
  LPCSTR pCVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  bool bVar10;
  int local_18;
  int *local_14;
  byte local_10 [16];
  
  DAT_10051c48 = 0;
  clear_text_rect(DAT_100cc518,0xb9,0x80,0x104,0x14);
  if (*DAT_100d2164 == 1) {
    iVar5 = *DAT_100d2180 + 1;
    pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Scene__d__100476b0);
  }
  else {
    iVar5 = *DAT_100d2180;
    pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Scene__d__100476bc);
  }
  wsprintfA((LPSTR)local_10,pCVar3,iVar5);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xba,0x84,*(int *)((int)DAT_100cc530 + 0x408),local_10,(undefined *)0x0);
  DAT_10057f3c = 0;
  piVar6 = (int *)&DAT_10057f38;
  pbVar8 = &DAT_10057f3c;
  _DAT_10057f38 = *DAT_100d2180;
  DAT_10057f80 = -1;
  do {
    iVar5 = FUN_1001c7b0(DAT_100cc530,0x113,0x84,(char *)pbVar8,0,0x20,0xbe);
    if (iVar5 != -1) break;
    iVar4 = hit_test_ui_object_list_by_point(DAT_10057f88,DAT_100d1f50,DAT_100d1f54);
    if (iVar4 == 1) {
      iVar4 = DAT_10057f7c + -1;
      if (DAT_10057f7c + -1 < 0) {
        DAT_10057f7c = 0;
      }
      else {
LAB_1001499f:
        DAT_10057f7c = iVar4;
        draw_save_game_scene_list();
      }
    }
    else if (iVar4 == 2) {
      iVar4 = DAT_10057f7c + 1;
      if (DAT_10057f7c + 1 <= DAT_10057f8c[1] - DAT_10057f30) goto LAB_1001499f;
    }
    else if (iVar4 == 3) {
      iVar4 = (DAT_100d1f54 + -0xb8) / DAT_10057ee8 + DAT_10057f7c;
      if (iVar4 < DAT_10057f8c[1]) {
        DAT_10057f74 = 1;
        piVar6 = *(int **)(DAT_10057f8c[2] + iVar4 * 4);
        *piVar6 = *DAT_100d2180;
        sscanf((char *)(piVar6 + 10),s__d_100476c8,&DAT_10057f80);
        DAT_10057f84 = DAT_10057f80;
        pbVar8 = (byte *)(piVar6 + 1);
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,0x113,0x84,*(int *)((int)DAT_100cc530 + 0x408),pbVar8,
                   (undefined *)0x0);
      }
    }
    else {
      iVar5 = 0;
    }
  } while (iVar5 == -1);
  piVar6[0xd] = *DAT_100d2164;
  piVar6[0xe] = _DAT_100cc858 & 2;
  iVar4 = find_pointer_list_item_index(DAT_10057f8c,(int)piVar6);
  if (iVar4 == -1) {
    iVar9 = 0;
    iVar4 = -1;
    if (0 < DAT_10057f8c[1]) {
      do {
        sscanf((char *)(*(int *)(DAT_10057f8c[2] + iVar9 * 4) + 0x28),s__d_100476ac,&local_18);
        if (iVar4 < local_18) {
          iVar4 = local_18;
        }
        iVar9 = iVar9 + 1;
      } while (iVar9 < DAT_10057f8c[1]);
    }
    DAT_10057f80 = iVar4 + 1;
    wsprintfA((LPSTR)(piVar6 + 9),s_save_3_3d_100476cc,DAT_10057f80);
    insert_pointer_list_item_sorted_or_append((int)DAT_10057f8c,(int)piVar6,(undefined *)0x0);
  }
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x113,0x84,*(int *)((int)DAT_100cc530 + 0x408),(byte *)(piVar6 + 1),
             (undefined *)0x0);
  if (iVar5 == 1) {
    if (DAT_10057f74 == 0) {
      iVar5 = 0;
      piVar6 = (int *)DAT_10057f8c[2];
      local_14 = (int *)piVar6[DAT_10057f8c[1] + -1];
      local_18 = DAT_10057f8c[1] + -1;
      if (0 < local_18) {
        do {
          piVar2 = (int *)*piVar6;
          if (*piVar2 == *local_14) {
            pbVar7 = (byte *)(local_14 + 1);
            pbVar8 = (byte *)(piVar2 + 1);
            do {
              bVar1 = *pbVar8;
              bVar10 = bVar1 < *pbVar7;
              if (bVar1 != *pbVar7) {
LAB_10014ae3:
                iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
                goto LAB_10014ae8;
              }
              if (bVar1 == 0) break;
              bVar1 = pbVar8[1];
              bVar10 = bVar1 < pbVar7[1];
              if (bVar1 != pbVar7[1]) goto LAB_10014ae3;
              pbVar8 = pbVar8 + 2;
              pbVar7 = pbVar7 + 2;
            } while (bVar1 != 0);
            iVar4 = 0;
LAB_10014ae8:
            if (iVar4 == 0) {
              sscanf((char *)(piVar2 + 10),s__d_10047700,&DAT_10057f84);
              goto LAB_10014b1a;
            }
          }
          iVar5 = iVar5 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar5 < local_18);
      }
    }
    else {
      DAT_10057f74 = 0;
LAB_10014b1a:
      remove_pointer_list_item((int)DAT_10057f8c,0x10057f38);
      iVar5 = show_modal_two_button_choice_dialog(&LAB_10014c90);
      if (iVar5 == 0) {
        load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0xb);
        if (DAT_10047678 != 0) {
          DAT_10047678 = 0;
          PTR_s_Save_100475f8 =
               (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Save_100476f0);
          PTR_s_Cancel_100475fc =
               (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Cancel_100476f8);
        }
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,0x148,0x1a4,*(int *)((int)DAT_100cc530 + 0x408),PTR_s_Save_100475f8,
                   (undefined *)0x0);
        _DAT_10047654 = 0x148;
        iVar5 = measure_string_width_from_glyph_sheet(DAT_100cc530,PTR_s_Save_100475f8);
        _DAT_10047658 = iVar5 + 0x148;
        iVar5 = iVar5 + 0x161;
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,iVar5,0x1a4,*(int *)((int)DAT_100cc530 + 0x408),
                   PTR_s_Cancel_100475fc,(undefined *)0x0);
        _DAT_10047668 = iVar5;
        _DAT_1004766c = measure_string_width_from_glyph_sheet(DAT_100cc530,PTR_s_Cancel_100475fc);
        _DAT_1004766c = iVar5 + _DAT_1004766c;
        draw_save_game_scene_list();
        DAT_10057ef0 = 0;
        handle_save_game_scene_selection();
        return;
      }
      DAT_10057f80 = DAT_10057f84;
    }
    DAT_10057f78 = 1;
    FUN_10007310();
    enumerate_savegame_directory((int)DAT_10057f8c,DAT_10057f80);
  }
  DAT_10051c48 = 1;
  return;
}


