/*
 * Program: i76shell.dll
 * Function: ShellWindowProc
 * Entry: 1001da10
 * Signature: LRESULT __thiscall ShellWindowProc(void * this, HWND param_1, uint param_2, WPARAM param_3, uint param_4)
 */


LRESULT __thiscall ShellWindowProc(void *this,HWND param_1,uint param_2,WPARAM param_3,uint param_4)

{
  int iVar1;
  HCURSOR hCursor;
  LRESULT LVar2;
  void *extraout_ECX;
  void *extraout_ECX_00;
  undefined4 *puVar3;
  undefined4 uVar4;
  tagPAINTSTRUCT local_40;
  
                    /* 0x1da10  2  ShellWindowProc */
  if (DAT_100d21c0 == 0) {
    return 0;
  }
  if (((((0xff < param_2) && (param_2 < 0x109)) &&
       (FUN_1001d1f0(param_2,param_3,param_4), this = extraout_ECX, DAT_10051c48 == 0)) &&
      ((DAT_100d21c4 == 0 &&
       (iVar1 = poll_keyboard_control_result(DAT_100cc50c), this = extraout_ECX_00, iVar1 == 3))))
     && (DAT_100d21a4 == 0)) {
    DAT_100d21ac = 1;
    DAT_100d2194 = 0;
  }
  if (DAT_100d21ac != 0) {
    if (DAT_100d21a0 != (code *)0x0) {
      (*DAT_100d21a0)(0);
    }
    switch(DAT_100d2194) {
    case 0:
      DAT_100d21ac = 0;
      handle_play_options_screen();
      DAT_10051c48 = 1;
      return 0;
    case 1:
      DAT_100d21ac = 0;
      handle_save_game_prompt();
      DAT_10051c48 = 1;
      return 0;
    case 2:
      DAT_100d21ac = 0;
      confirm_leave_game_dialog();
      DAT_10051c48 = 1;
      return 0;
    case 3:
      DAT_100d21ac = 0;
      handle_modem_setup_screen();
      DAT_10051c48 = 1;
      return 0;
    case 4:
      DAT_100d21ac = 0;
      handle_gameplay_options_screen();
      DAT_10051c48 = 1;
      return 0;
    case 5:
      DAT_100d21ac = 0;
      handle_video_options_screen();
      DAT_10051c48 = 1;
      return 0;
    case 6:
      DAT_100d21ac = 0;
      shell_screen_state_handler_b();
      DAT_10051c48 = 1;
      return 0;
    case 7:
      DAT_100d21ac = 0;
      handle_input_mapping_screen();
      DAT_10051c48 = 1;
      return 0;
    case 8:
      DAT_100d21ac = 0;
      shell_shared_ui_helper((int)DAT_100cc518);
      puVar3 = *(undefined4 **)((int)DAT_100cc518 + 0x44);
      for (iVar1 = 0x12c00; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      if (DAT_100d219c == (code *)0x0) {
        PostMessageA(DAT_100f702c,0xc002,0,0);
        return 0;
      }
      uVar4 = 0xc002;
      break;
    case 9:
      DAT_100d21ac = 0;
      init_shell_ui_state();
      DAT_10051c48 = 1;
      return 0;
    case 10:
      DAT_100d21ac = 0;
      shell_shared_ui_helper((int)DAT_100cc518);
      puVar3 = *(undefined4 **)((int)DAT_100cc518 + 0x44);
      for (iVar1 = 0x12c00; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      if (DAT_100d219c == (code *)0x0) {
        PostMessageA(DAT_100f702c,0xc00e,0,0);
        return 0;
      }
      uVar4 = 0xc00e;
      break;
    case 0xb:
      DAT_100d21ac = 0;
      FUN_10012fe0();
      DAT_10051c48 = 1;
      return 0;
    default:
      goto switchD_1001dab8_default;
    }
    (*DAT_100d219c)(DAT_100cc53c,&DAT_100d2198,&DAT_100d2178,uVar4);
    return 0;
  }
  if (param_2 < 0x10) {
    if (param_2 == 0xf) {
      BeginPaint(param_1,&local_40);
      if (DAT_100cc518 != (void *)0x0) {
        FUN_10037d00(DAT_100cc518,local_40.rcPaint.left,local_40.rcPaint.top,local_40.rcPaint.right,
                     local_40.rcPaint.bottom);
        flush_or_repaint_shell_surface_context((int)DAT_100cc518);
      }
      EndPaint(param_1,&local_40);
      return 0;
    }
    if (param_2 == 2) {
      PostQuitMessage(0);
      return 0;
    }
switchD_1001def9_caseD_c009:
    LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
    return LVar2;
  }
  if (param_2 < 0x1d) {
    if (param_2 != 0x1c) {
      if (param_2 == 0x10) {
        PostMessageA(param_1,2,0,0);
        return 0;
      }
      goto switchD_1001def9_caseD_c009;
    }
    DAT_10043224 = param_3;
    if (param_3 != 0) {
      ShowWindow(param_1,9);
      FUN_10021d40();
      FUN_10039a80();
      flush_or_repaint_shell_surface_context((int)DAT_100cc518);
      if ((DAT_10051c48 != 0) || (DAT_100d2184 == 0)) {
        hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
        SetCursor(hCursor);
        return 0;
      }
    }
  }
  else if (param_2 < 0xa1) {
    if (param_2 != 0xa0) {
      if (param_2 == 0x20) {
        return 1;
      }
      goto switchD_1001def9_caseD_c009;
    }
    if (DAT_100d21b8 != 0) {
      iVar1 = ShowCursor(1);
      while (iVar1 < 0) {
        iVar1 = ShowCursor(1);
      }
      DAT_100d21b8 = 0;
      return 0;
    }
  }
  else if (param_2 < 0xc003) {
    if (param_2 == 0xc002) {
      destroy_directplay_connection_handle();
      PostQuitMessage(0xc002);
      return 0;
    }
    if (param_2 != 0x30f) {
      if (param_2 != 0x311) goto switchD_1001def9_caseD_c009;
      if (param_1 == DAT_100f702c) {
        return 0;
      }
    }
    if (DAT_100cc518 != (void *)0x0) {
      apply_shell_surface_palette_to_backend((int)DAT_100cc518);
      if (DAT_100cc548 == '\0') {
        mark_shell_surface_dirty_rect(DAT_100cc518,0,0,0x280,0x1e0);
        flush_or_repaint_shell_surface_context((int)DAT_100cc518);
        return 1;
      }
      mark_shell_surface_dirty_rect(DAT_100cc518,0,0,0x140,200);
      shell_surface_repaint_or_flip_with_palette_update((int)DAT_100cc518);
      return 1;
    }
  }
  else {
    switch(param_2) {
    case 0xc008:
      DAT_100d2168 = param_2;
      DAT_10057a28 = 1;
      DAT_100d21ac = 1;
      DAT_100d21a8 = 0;
      DAT_100d2194 = 9;
      break;
    default:
      goto switchD_1001def9_caseD_c009;
    case 0xc00d:
      DAT_100d2168 = param_2;
      preload_final_mission_special_menu_record_0x40(DAT_100cc53c);
      return 0;
    case 0xc00e:
      DAT_100d2198 = 0;
      delete_user_repair_profile_file();
      DAT_100d2168 = param_2;
      FUN_10025980(DAT_100cc53c);
      return 0;
    case 0xc00f:
      DAT_100d2168 = param_2;
      shell_ui_object_event_handler(this,DAT_100cc53c);
      return 0;
    case 0xc010:
      if (DAT_100d217c < 2) {
        DAT_100d21a8 = 0;
        iVar1 = (**(code **)(DAT_10058198 + 0x44))(0);
        while (iVar1 == 0) {
          iVar1 = handle_modal_dialog_confirm_or_default();
          if (iVar1 == 0) {
            PostMessageA(param_1,0xc00e,0xc010,0);
            return 0;
          }
          iVar1 = (**(code **)(DAT_10058198 + 0x44))();
        }
      }
      PostQuitMessage(0xc001);
      return 0;
    case 0xc015:
      DAT_100d2168 = param_2;
      FUN_10023fc0(DAT_100cc53c);
      return 0;
    case 0xc017:
      DAT_100d2168 = param_2;
      FUN_10018ae0(DAT_100cc53c);
      return 0;
    case 0xc01c:
      DAT_100d2168 = param_2;
      PostMessageA(DAT_100f702c,0xc010,0xc01c,0);
      return 0;
    case 0xc01d:
      DAT_100d2168 = param_2;
      commit_selected_savegame_and_launch_session();
      return 0;
    case 0xc01e:
      DAT_100d2168 = param_2;
      dispatch_selected_mission_or_vehicle_config_transition();
      return 0;
    case 0xc01f:
      DAT_100d2168 = param_2;
      FUN_100258f0(DAT_100cc53c);
      return 0;
    case 0xc020:
      DAT_100d2168 = param_2;
      FUN_1001f3e0(DAT_100cc53c);
      return 0;
    case 0xc021:
      DAT_100d217c = 0;
      DAT_100d2168 = param_2;
      handle_mission_selection_screen(DAT_100cc53c);
      return 0;
    case 0xc022:
      DAT_100d2168 = param_2;
      launch_single_player_trip_seed_session();
      return 0;
    case 0xc024:
      DAT_100d2168 = param_2;
      DAT_100d217c = 1;
      handle_mission_selection_screen(DAT_100cc53c);
      return 0;
    case 0xc025:
      DAT_100d2168 = param_2;
      FUN_1003f830(DAT_100cc53c);
      return 0;
    case 0xc026:
      DAT_100d2168 = param_2;
      handle_mission_selection_screen(DAT_100cc53c);
      return 0;
    }
  }
switchD_1001dab8_default:
  return 0;
}


