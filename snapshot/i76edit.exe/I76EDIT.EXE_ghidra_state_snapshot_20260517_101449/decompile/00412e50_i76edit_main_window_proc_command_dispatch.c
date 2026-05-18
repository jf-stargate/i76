/*
 * Program: I76EDIT.EXE
 * Function: i76edit_main_window_proc_command_dispatch
 * Entry: 00412e50
 * Signature: undefined __stdcall i76edit_main_window_proc_command_dispatch(HWND param_1, uint param_2, uint param_3, int param_4)
 */


/* [cgpt_i76edit_level_renames_v2:high] Main window procedure / command dispatcher. Evidence:
   DefWindowProcA/PostQuitMessage/GetOpenFileNameA/GetSaveFileNameA, open/save/export strings, and
   many thunked command handlers. */

void i76edit_main_window_proc_command_dispatch(HWND param_1,uint param_2,uint param_3,int param_4)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  BOOL BVar4;
  uint uVar5;
  int iVar6;
  code *pcVar7;
  char *pcVar8;
  int iVar9;
  undefined4 *puVar10;
  char *pcVar11;
  HWND pHVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  char *pcVar15;
  char local_460 [4];
  undefined1 local_45c [80];
  DWORD DStack_40c;
  DWORD local_408;
  char local_404 [4];
  char local_400 [256];
  char local_300 [256];
  char local_200 [256];
  char local_100 [256];
  
  if (param_2 < 0x4f) {
    if (param_2 == 0x4e) {
      if (*(int *)(param_4 + 8) == -0x20a) {
        i76edit_set_status_bar_text(s_Ready_004346ec);
        return;
      }
      if (*(int *)(param_4 + 8) == -0x208) {
        i76edit_show_edit_terrain_layer_dialog(param_4);
        return;
      }
      goto LAB_004137c5;
    }
    if (param_2 == 1) {
      Ordinal_17();
      thunk_FUN_00407140(param_1);
      thunk_FUN_00407190(param_1);
      thunk_FUN_004071c0(param_1);
      uVar2 = GetWindowLongA(DAT_01641fb4,-0x10);
      SetWindowLongA(DAT_01641fb4,-0x10,uVar2 | 0x2000000);
      return;
    }
    if (param_2 == 2) {
      PostQuitMessage(0);
      return;
    }
    if (param_2 == 5) {
      SendMessageA(DAT_016423ac,5,param_3,param_4);
      return;
    }
  }
  else {
    if (param_2 == 0x100) {
      return;
    }
    if (param_2 == 0x111) {
      if (param_3 < 0x8026) {
        if (param_3 == 0x8025) {
          iVar9 = 0;
          thunk_FUN_0041e730(0x8025,0x80);
          do {
            iVar6 = 0;
            do {
              iVar3 = i76edit_get_or_assign_zone_map_cell_id(iVar9,iVar6,0);
              if (iVar3 != -1) {
                _sprintf(local_400,s_Painting_Zone__d_00434598,iVar3 + 1);
                i76edit_set_status_bar_text(local_400);
                i76edit_export_height_txt_debug_view(iVar3);
              }
              iVar6 = iVar6 + 1;
            } while (iVar6 < 0x50);
            iVar9 = iVar9 + 1;
          } while (iVar9 < 0x50);
          i76edit_set_status_bar_text(s_Ready__00434590);
        }
        else {
          switch(param_3) {
          case 0x800f:
            thunk_FUN_0041e730(0x800f,1);
            break;
          case 0x8010:
            iVar9 = 0;
            thunk_FUN_0041e730(0x8010,2);
            do {
              iVar6 = 0;
              do {
                iVar3 = i76edit_get_or_assign_zone_map_cell_id(iVar9,iVar6,0);
                if (iVar3 != -1) {
                  _sprintf(local_400,s_Painting_Zone__d_00434598,iVar3 + 1);
                  i76edit_set_status_bar_text(local_400);
                  i76edit_export_height_txt_debug_view(iVar3);
                }
                iVar6 = iVar6 + 1;
              } while (iVar6 < 0x50);
              iVar9 = iVar9 + 1;
            } while (iVar9 < 0x50);
            i76edit_set_status_bar_text(s_Ready__00434590);
            break;
          case 0x8011:
            iVar9 = 0;
            thunk_FUN_0041e730(0x8011,4);
            do {
              iVar6 = 0;
              do {
                iVar3 = i76edit_get_or_assign_zone_map_cell_id(iVar9,iVar6,0);
                if (iVar3 != -1) {
                  _sprintf(local_400,s_Painting_Zone__d_00434598,iVar3 + 1);
                  i76edit_set_status_bar_text(local_400);
                  i76edit_export_height_txt_debug_view(iVar3);
                }
                iVar6 = iVar6 + 1;
              } while (iVar6 < 0x50);
              iVar9 = iVar9 + 1;
            } while (iVar9 < 0x50);
            i76edit_set_status_bar_text(s_Ready__00434590);
            break;
          case 0x8012:
            thunk_FUN_0041e730(0x8012,0x10);
            break;
          case 0x8013:
            thunk_FUN_0041e730(0x8013,0x20);
            break;
          case 0x8014:
            thunk_FUN_0041e730(0x8014,0x40);
          }
        }
      }
      else if (param_3 < 0x9c50) {
        if (param_3 == 0x9c4f) {
          DAT_00433a48 = DAT_00433a48 + 1;
          if (DAT_00433a48 != 7) {
            pcVar15 = local_45c + 0x4c;
            DAT_00433a44 = (&DAT_00433a50)[DAT_00433a48];
            GetClientRect(DAT_01641fb4,(LPRECT)pcVar15);
            SetScrollRange(DAT_01641fb4,1,0,(int)(local_408 * -100) / DAT_00433a44 + 0x2800,0);
            SetScrollRange(DAT_01641fb4,0,0,(int)(DStack_40c * -100) / DAT_00433a44 + 0x2800,0);
            uVar14 = 1;
            uVar13 = 0;
            pcVar7 = InvalidateRgn_exref;
            pHVar12 = DAT_01641fb4;
            goto LAB_004137aa;
          }
          DAT_00433a48 = 6;
        }
        else if (param_3 == 0x9c41) {
          PostQuitMessage(0);
          return;
        }
      }
      else if (param_3 < 0x9c71) {
        if (param_3 == 0x9c70) {
          thunk_FUN_0041e370(8);
        }
        else {
          switch(param_3) {
          case 0x9c57:
            thunk_FUN_0041e370(0);
            break;
          case 0x9c58:
            thunk_FUN_0041e370(1);
            break;
          case 0x9c59:
            thunk_FUN_0041e370(2);
            break;
          case 0x9c5a:
            thunk_FUN_0041e370(4);
            break;
          case 0x9c5b:
            thunk_FUN_0041e370(5);
            break;
          case 0x9c5c:
            thunk_FUN_0041e370(6);
            break;
          case 0x9c65:
            __splitpath(&DAT_004358f0,local_460,local_100,local_300,local_200);
            __makepath(&DAT_004358f0,&DAT_00434334,&DAT_00434334,local_300,&DAT_00436010);
            puVar10 = (undefined4 *)local_45c;
            for (iVar9 = 0x13; iVar9 != 0; iVar9 = iVar9 + -1) {
              *puVar10 = 0;
              puVar10 = puVar10 + 1;
            }
            local_45c._0_4_ = 0x4c;
            local_45c._12_4_ = s_Mission____LVL__004358c0;
            local_45c._24_4_ = 1;
            local_45c._28_4_ = &DAT_004358f0;
            local_45c._32_4_ = 0x100;
            local_45c._4_4_ = param_1;
            local_45c._52_4_ = 0x1800;
            local_45c._48_4_ = s_Export_Interstate__76_Mission_00435fec;
            local_45c._60_4_ = &DAT_00436010;
            BVar4 = GetSaveFileNameA((LPOPENFILENAMEA)local_45c);
            if (BVar4 != 0) {
              i76edit_export_runtime_mission_file(&DAT_004358f0,local_45c._24_4_);
              goto LAB_00413721;
            }
            break;
          case 0x9c66:
            DAT_00433a48 = DAT_00433a48 + -1;
            if (-1 < DAT_00433a48) {
              pcVar15 = local_45c + 0x4c;
              DAT_00433a44 = (&DAT_00433a50)[DAT_00433a48];
              GetClientRect(DAT_01641fb4,(LPRECT)pcVar15);
              SetScrollRange(DAT_01641fb4,1,0,(int)(local_408 * -100) / DAT_00433a44 + 0x2800,0);
              SetScrollRange(DAT_01641fb4,0,0,(int)(DStack_40c * -100) / DAT_00433a44 + 0x2800,0);
              uVar14 = 1;
              uVar13 = 0;
              pcVar7 = InvalidateRgn_exref;
              pHVar12 = DAT_01641fb4;
              goto LAB_004137aa;
            }
            DAT_00433a48 = 0;
            break;
          case 0x9c67:
            thunk_FUN_0041e730(0x9c67,8);
            break;
          case 0x9c68:
            thunk_FUN_0041e370(3);
            break;
          case 0x9c69:
            thunk_FUN_0041e370(7);
          }
        }
      }
      else {
        switch(param_3) {
        case 0xe101:
          __splitpath(&DAT_004358f0,local_460,local_100,local_300,local_200);
          __makepath(&DAT_004358f0,&DAT_00434334,&DAT_00434334,local_300,&DAT_0043605c);
          puVar10 = (undefined4 *)local_45c;
          for (iVar9 = 0x13; iVar9 != 0; iVar9 = iVar9 + -1) {
            *puVar10 = 0;
            puVar10 = puVar10 + 1;
          }
          local_45c._0_4_ = 0x4c;
          local_45c._12_4_ = s_Interstate__76_Mission____I76__00435880;
          local_45c._24_4_ = 1;
          local_45c._28_4_ = &DAT_004358f0;
          local_45c._32_4_ = 0x100;
          pcVar15 = local_45c;
          local_45c._4_4_ = param_1;
          local_45c._52_4_ = 0x1800;
          local_45c._48_4_ = s_Open_Interstate__76_Mission_00436038;
          local_45c._60_4_ = &DAT_0043605c;
          BVar4 = GetOpenFileNameA((LPOPENFILENAMEA)pcVar15);
          if (BVar4 != 0) {
            i76edit_load_mission_file(&DAT_004358f0);
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
            for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
              pcVar15[0] = '\0';
              pcVar15[1] = '\0';
              pcVar15[2] = '\0';
              pcVar15[3] = '\0';
              pcVar15 = pcVar15 + 4;
            }
            uVar2 = 0xffffffff;
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_00434034;
            do {
              pcVar8 = pcVar15;
              if (uVar2 == 0) break;
              uVar2 = uVar2 - 1;
              pcVar8 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar8;
            } while (cVar1 != '\0');
            uVar2 = ~uVar2;
            iVar9 = -1;
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
            do {
              pcVar11 = pcVar15;
              if (iVar9 == 0) break;
              iVar9 = iVar9 + -1;
              pcVar11 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar11;
            } while (cVar1 != '\0');
            pcVar15 = pcVar8 + -uVar2;
            pcVar8 = pcVar11 + -1;
            for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar8 = *(undefined4 *)pcVar15;
              pcVar15 = pcVar15 + 4;
              pcVar8 = pcVar8 + 4;
            }
            for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
              *pcVar8 = *pcVar15;
              pcVar15 = pcVar15 + 1;
              pcVar8 = pcVar8 + 1;
            }
            uVar2 = 0xffffffff;
            pcVar15 = &DAT_004358f0;
            do {
              pcVar8 = pcVar15;
              if (uVar2 == 0) break;
              uVar2 = uVar2 - 1;
              pcVar8 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar8;
            } while (cVar1 != '\0');
            uVar2 = ~uVar2;
            iVar9 = -1;
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
            do {
              pcVar11 = pcVar15;
              if (iVar9 == 0) break;
              iVar9 = iVar9 + -1;
              pcVar11 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar11;
            } while (cVar1 != '\0');
            pcVar8 = pcVar8 + -uVar2;
            pcVar11 = pcVar11 + -1;
            for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar11 = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              pcVar11 = pcVar11 + 4;
            }
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
            for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
              *pcVar11 = *pcVar8;
              pcVar8 = pcVar8 + 1;
              pcVar11 = pcVar11 + 1;
            }
            SendMessageA(DAT_01642370,0xc,0,0x4345b0);
          }
          iVar9 = 0;
          do {
            iVar6 = 0;
            do {
              iVar3 = i76edit_get_or_assign_zone_map_cell_id(iVar9,iVar6,0);
              if (iVar3 != -1) {
                _sprintf(local_404,s_Painting_Zone__d_00434598,iVar3 + 1);
                i76edit_set_status_bar_text(local_404);
                i76edit_export_height_txt_debug_view(iVar3);
              }
              iVar6 = iVar6 + 1;
            } while (iVar6 < 0x50);
            iVar9 = iVar9 + 1;
          } while (iVar9 < 0x50);
          i76edit_set_status_bar_text(s_Ready__00434590);
          uVar14 = 0;
          uVar13 = 0;
          pcVar7 = InvalidateRgn_exref;
          pHVar12 = DAT_01641fb4;
LAB_004137aa:
          (*pcVar7)(pHVar12,uVar13,uVar14,pcVar15);
          break;
        case 0xe103:
          __splitpath(&DAT_004358f0,local_460,local_100,local_300,local_200);
          __makepath(&DAT_004358f0,&DAT_00434334,&DAT_00434334,local_300,&DAT_0043605c);
          puVar10 = (undefined4 *)local_45c;
          for (iVar9 = 0x13; iVar9 != 0; iVar9 = iVar9 + -1) {
            *puVar10 = 0;
            puVar10 = puVar10 + 1;
          }
          local_45c._0_4_ = 0x4c;
          local_45c._12_4_ = s_Interstate__76_Mission____I76__00435880;
          local_45c._24_4_ = 1;
          local_45c._28_4_ = &DAT_004358f0;
          local_45c._32_4_ = 0x100;
          local_45c._4_4_ = param_1;
          local_45c._52_4_ = 0x1800;
          local_45c._48_4_ = s_Save_Interstate__76_Mission_00436014;
          local_45c._60_4_ = &DAT_0043605c;
          BVar4 = GetSaveFileNameA((LPOPENFILENAMEA)local_45c);
          if (BVar4 != 0) {
            i76edit_save_editor_mission_file(&DAT_004358f0);
LAB_00413721:
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
            for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
              pcVar15[0] = '\0';
              pcVar15[1] = '\0';
              pcVar15[2] = '\0';
              pcVar15[3] = '\0';
              pcVar15 = pcVar15 + 4;
            }
            uVar2 = 0xffffffff;
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_00434034;
            do {
              pcVar8 = pcVar15;
              if (uVar2 == 0) break;
              uVar2 = uVar2 - 1;
              pcVar8 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar8;
            } while (cVar1 != '\0');
            uVar2 = ~uVar2;
            iVar9 = -1;
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
            do {
              pcVar11 = pcVar15;
              if (iVar9 == 0) break;
              iVar9 = iVar9 + -1;
              pcVar11 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar11;
            } while (cVar1 != '\0');
            pcVar15 = pcVar8 + -uVar2;
            pcVar8 = pcVar11 + -1;
            for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar8 = *(undefined4 *)pcVar15;
              pcVar15 = pcVar15 + 4;
              pcVar8 = pcVar8 + 4;
            }
            for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
              *pcVar8 = *pcVar15;
              pcVar15 = pcVar15 + 1;
              pcVar8 = pcVar8 + 1;
            }
            uVar2 = 0xffffffff;
            pcVar15 = &DAT_004358f0;
            do {
              pcVar8 = pcVar15;
              if (uVar2 == 0) break;
              uVar2 = uVar2 - 1;
              pcVar8 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar8;
            } while (cVar1 != '\0');
            uVar2 = ~uVar2;
            iVar9 = -1;
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
            do {
              pcVar11 = pcVar15;
              if (iVar9 == 0) break;
              iVar9 = iVar9 + -1;
              pcVar11 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar11;
            } while (cVar1 != '\0');
            pcVar8 = pcVar8 + -uVar2;
            pcVar11 = pcVar11 + -1;
            for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar11 = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              pcVar11 = pcVar11 + 4;
            }
            pcVar15 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
            uVar14 = 0;
            for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
              *pcVar11 = *pcVar8;
              pcVar8 = pcVar8 + 1;
              pcVar11 = pcVar11 + 1;
            }
            uVar13 = 0xc;
            pcVar7 = SendMessageA_exref;
            pHVar12 = DAT_01642370;
            goto LAB_004137aa;
          }
        }
      }
    }
  }
LAB_004137c5:
  DefWindowProcA(param_1,param_2,param_3,param_4);
  return;
}


