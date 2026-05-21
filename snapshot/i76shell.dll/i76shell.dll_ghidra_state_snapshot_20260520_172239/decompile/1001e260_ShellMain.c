/*
 * Program: i76shell.dll
 * Function: ShellMain
 * Entry: 1001e260
 * Signature: undefined4 __stdcall ShellMain(undefined4 param_1, undefined4 param_2, char * param_3, undefined4 param_4, HWND param_5, undefined4 param_6, int * param_7, undefined4 param_8, int param_9, uint * param_10, int param_11, int param_12, undefined4 param_13)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
ShellMain(undefined4 param_1,undefined4 param_2,char *param_3,undefined4 param_4,HWND param_5,
         undefined4 param_6,int *param_7,undefined4 param_8,int param_9,uint *param_10,int param_11,
         int param_12,undefined4 param_13)

{
  char *pcVar1;
  int iVar2;
  void *pvVar3;
  LPCSTR lpCaption;
  LPCSTR lpText;
  undefined4 *puVar4;
  BOOL BVar5;
  undefined4 uVar6;
  time_t tVar7;
  UINT UVar8;
  WPARAM wParam;
  int local_40;
  long lStack_3c;
  tagRECT local_38;
  tagMSG tStack_28;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
                    /* 0x1e260  1  ShellMain */
  local_4 = 0xffffffff;
  puStack_8 = &LAB_100402b3;
  local_c = ExceptionList;
  local_40 = 0;
  ExceptionList = &local_c;
  iVar2 = ShowCursor(1);
  if (iVar2 < 2) {
    if (iVar2 < 0) {
      iVar2 = ShowCursor(1);
      while (iVar2 != 0) {
        iVar2 = ShowCursor(1);
      }
    }
  }
  else {
    ShowCursor(0);
  }
  DAT_100f6368 = param_6;
  DAT_100f6364 = param_13;
  DAT_100d2180 = param_7;
  DAT_100d2164 = &param_11;
  DAT_100d21b8 = 0;
  DAT_10058198 = param_9;
  DAT_100c5ad8 = param_12;
  DAT_100d2170 = param_10;
  DAT_100d218c = *param_10 >> 5 & 1;
  puVar4 = &DAT_100581a0;
  for (iVar2 = 0x1b648; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = (undefined4 *)&DAT_100c6288;
  for (iVar2 = 0x189c; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = &DAT_100c5b20;
  for (iVar2 = 0x4e; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  tVar7 = time((time_t *)0x0);
  srand((uint)tVar7);
  DAT_10051c50 = HeapCreate(1,1000000,0);
  if (DAT_10051c50 == (HANDLE)0x0) {
    MessageBoxA((HWND)0x0,&DAT_10049bc0,s_Interstate__76_Gold_Edition_10043208,0x30);
    ExceptionList = local_c;
    return 0xff;
  }
  DAT_100f7020 = param_1;
  DAT_100f702c = param_5;
  DAT_100d2184 = 0;
  DAT_100d21b0 = 0;
  DAT_100d21b4 = 0;
  read_player_definition_file(0,(undefined4 *)0x0);
  _DAT_100d2190 = 1;
  DAT_10047774 = FUN_10024b80();
  _DAT_100d2190 = 0;
  if (*param_3 == '\0') {
    DAT_10047774 = 0;
  }
  FUN_10037380();
  pvVar3 = operator_new(0x8c);
  local_4 = 0;
  if (pvVar3 == (void *)0x0) {
    DAT_100cc53c = (char *)0x0;
  }
  else {
    DAT_100cc53c = open_mpack_database(pvVar3,s_DATABASE_MW2_10049bd4);
  }
  local_4 = 0xffffffff;
  GetClientRect(DAT_100f702c,&local_38);
  DAT_100f701c = 0x280;
  DAT_100f7018 = 0x1e0;
  pvVar3 = operator_new(0x3d8);
  local_4 = 1;
  if (pvVar3 == (void *)0x0) {
    DAT_100cc518 = (void *)0x0;
  }
  else {
    DAT_100cc518 = (void *)construct_shell_surface_context((int)pvVar3);
  }
  local_4 = 0xffffffff;
  _DAT_100f7030 = 0;
  DAT_100d216c = LoadCursorFromFileA(s_pencil_cur_10049be4);
  if (DAT_100d216c == (HCURSOR)0x0) {
    LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  }
  DAT_100d2188 = LoadCursorFromFileA(s_nopencil_cur_10049bf0);
  if (DAT_100d2188 == (HCURSOR)0x0) {
    LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f88);
  }
  (**(code **)(DAT_10058198 + 0x54))();
  (**(code **)(DAT_10058198 + 0x50))(0xd,1);
  reset_shell_session_resource_globals();
  bind_shell_launch_config_block_and_close_previous_directplay((byte *)param_10);
  if ((DAT_100d21b0 == 0) && (DAT_100d21b4 == 0)) {
    if ((param_11 == 5) ||
       (iVar2 = _stricmp((char *)((int)param_10 + 0x5d),s_a01_msn_10049c00), iVar2 == 0)) {
      wParam = 0;
      UVar8 = 0xc00e;
    }
    else {
      read_player_definition_file(param_8,&DAT_100c5ae0);
      iVar2 = *(int *)(DAT_100c5ad8 + 0x20);
      if (iVar2 == 2) {
        if (param_11 == 2) {
          DAT_100c5af8 = DAT_100c5af8 + -1;
          _DAT_100c5b00 = 0;
          write_player_definition_file(&DAT_100c5ae0);
          FUN_100169e0((void *)((int)&DAT_100c5ae0 + 2),param_8);
          wParam = 0xc00e;
          UVar8 = 0xc00e;
        }
        else if (param_11 == 8) {
          DAT_100c5af8 = DAT_100c5af8 + -1;
          write_player_definition_file(&DAT_100c5ae0);
          wParam = 0xc01e;
          UVar8 = 0xc01e;
        }
        else {
          if (param_11 != 1) goto LAB_1001e74f;
          if (*DAT_100d2180 == 0x11) {
            wParam = 0xc01e;
            UVar8 = 0xc008;
            DAT_100d2168 = 0xc01e;
          }
          else if ((*DAT_100d2180 == 4) && ((DAT_100cc858 & 2) == 0)) {
            delete_user_repair_profile_file();
            destroy_repair_profile_pointer_list();
            reset_shell_session_resource_globals();
            iVar2 = read_spc_or_cmp_mission_vehicle_config(s_trip4_spc_10049c08);
            UVar8 = 0;
            if (iVar2 == 0) {
              lpCaption = (LPCSTR)resolve_localized_shell_string_cached
                                            (DAT_100f5360,s_Error_10049c14);
              lpText = (LPCSTR)resolve_localized_shell_string_cached
                                         (DAT_100f5360,s_You_must_play_trip_3_before_trip_10049c1c);
              MessageBoxA(DAT_100f702c,lpText,lpCaption,UVar8);
              PostQuitMessage(0);
              goto LAB_1001e74f;
            }
            wParam = 0xc01e;
            UVar8 = 0xc017;
          }
          else {
            _DAT_100c5b00 = 1;
            write_player_definition_file(&DAT_100c5ae0);
            DAT_100c5af8 = *DAT_100d2180;
            reset_shell_session_resource_globals();
            wParam = 0xc01e;
            UVar8 = 0xc01e;
          }
        }
      }
      else if (iVar2 == 4) {
        initialize_single_player_shell_session_defaults();
        wParam = 0;
        UVar8 = 0xc024;
      }
      else if (iVar2 == 3) {
        initialize_single_player_shell_session_defaults();
        wParam = 0;
        UVar8 = 0xc025;
        DAT_100d217c = 0;
      }
      else {
        if (iVar2 != 5) goto LAB_1001e74f;
        initialize_single_player_shell_session_defaults();
        DAT_100d217c = param_10[1];
        wParam = 0;
        UVar8 = 0xc025;
      }
    }
  }
  else {
    DAT_100d217c = (-(uint)(DAT_100d21b0 != 0) & 0xfffffffc) + 8;
    initialize_single_player_shell_session_defaults();
    initialize_directplay_connection_for_mode();
    wParam = 0;
    UVar8 = 0xc026;
  }
  PostMessageA(DAT_100f702c,UVar8,wParam,0);
LAB_1001e74f:
  mpack_database_get_item(DAT_100cc53c,0x44,&local_40,&lStack_3c);
  pvVar3 = operator_new(0x414);
  local_4 = 2;
  if (pvVar3 == (void *)0x0) {
    DAT_100cc524 = (int *)0x0;
  }
  else {
    DAT_100cc524 = construct_shell_glyph_sheet(pvVar3,local_40,(int)DAT_100cc518);
  }
  local_4 = 0xffffffff;
  mpack_database_get_item(DAT_100cc53c,0x42,&local_40,&lStack_3c);
  pvVar3 = operator_new(0x414);
  local_4 = 3;
  if (pvVar3 == (void *)0x0) {
    DAT_100cc528 = (int *)0x0;
  }
  else {
    DAT_100cc528 = construct_shell_glyph_sheet(pvVar3,local_40,(int)DAT_100cc518);
  }
  local_4 = 0xffffffff;
  mpack_database_get_item(DAT_100cc53c,0x45,&local_40,&lStack_3c);
  pvVar3 = operator_new(0x414);
  local_4 = 4;
  if (pvVar3 == (void *)0x0) {
    DAT_100cc52c = (int *)0x0;
  }
  else {
    DAT_100cc52c = construct_shell_glyph_sheet(pvVar3,local_40,(int)DAT_100cc518);
  }
  local_4 = 0xffffffff;
  mpack_database_get_item(DAT_100cc53c,0x46,&local_40,&lStack_3c);
  pvVar3 = operator_new(0x414);
  local_4 = 5;
  if (pvVar3 == (void *)0x0) {
    DAT_100cc530 = (int *)0x0;
  }
  else {
    DAT_100cc530 = construct_shell_glyph_sheet(pvVar3,local_40,(int)DAT_100cc518);
  }
  local_4 = 0xffffffff;
  mpack_database_get_item(DAT_100cc53c,0x47,&local_40,&lStack_3c);
  pvVar3 = operator_new(0x414);
  local_4 = 6;
  if (pvVar3 == (void *)0x0) {
    DAT_100cc51c = (int *)0x0;
  }
  else {
    DAT_100cc51c = construct_shell_glyph_sheet(pvVar3,local_40,(int)DAT_100cc518);
  }
  local_4 = 0xffffffff;
  DAT_100cc520 = DAT_100cc51c;
  _DAT_100cc534 = DAT_100cc51c;
  _DAT_100cc538 = DAT_100cc51c;
  preload_shell_image_record_0x24();
  pvVar3 = operator_new(0x44);
  local_4 = 7;
  if (pvVar3 == (void *)0x0) {
    DAT_100cc514 = (void *)0x0;
  }
  else {
    DAT_100cc514 = (void *)FUN_1001fa40(pvVar3,DAT_100cc518,DAT_100cc51c,0);
  }
  local_4 = 0xffffffff;
  puVar4 = operator_new(0x110);
  local_4 = 8;
  if (puVar4 == (undefined4 *)0x0) {
    DAT_100cc50c = (undefined4 *)0x0;
  }
  else {
    DAT_100cc50c = FUN_1001c040(puVar4);
  }
  local_4 = 0xffffffff;
  ClipCursor((RECT *)0x0);
  DAT_100d2174 = 0;
  SendMessageA(DAT_100f702c,0x434,0,0);
  DAT_100d21c0 = 1;
  do {
    (**(code **)(DAT_10058198 + 0x28))(0);
    BVar5 = PeekMessageA(&tStack_28,(HWND)0x0,0,0,1);
    if (BVar5 != 0) {
      if (tStack_28.message == 0x12) {
        SendMessageA(DAT_100f702c,0x432,0,0);
        SetMenu(DAT_100f702c,(HMENU)0x0);
        if (DAT_100d21a0 != (code *)0x0) {
          (*DAT_100d21a0)(0);
        }
        if (DAT_100d219c != (code *)0x0) {
          (*DAT_100d219c)(DAT_100cc53c,&DAT_100d2198,&DAT_100d2178,0xc002);
        }
        if (tStack_28.wParam == 0xc001) {
          if ((*(int *)(DAT_100c5ad8 + 0x20) == 2) || (DAT_100d2174 != 0)) {
            if (param_11 == 1) {
              *DAT_100d2180 = *DAT_100d2180 + 1;
              DAT_100c5af8 = DAT_100c5af8 + 1;
              if (DAT_100c5afc < DAT_100c5af8) {
                DAT_100c5afc = DAT_100c5af8;
              }
              _DAT_100c5b00 = 2;
              write_player_definition_file(&DAT_100c5ae0);
            }
            wsprintfA((LPSTR)((int)param_10 + 0x5d),s_t_2_2d_msn_10049c40,*DAT_100d2180);
          }
          if ((*(int *)(DAT_100c5ad8 + 0x20) == 0) || (*(int *)(DAT_100c5ad8 + 0x20) == 1)) {
            *(undefined4 *)(DAT_100c5ad8 + 0x20) = 2;
          }
          uVar6 = 3;
        }
        else {
          uVar6 = 0xff;
          destroy_directplay_connection_handle();
        }
        shell_shared_ui_helper((int)DAT_100cc518);
        pcVar1 = DAT_100cc53c;
        if (DAT_100cc53c != (char *)0x0) {
          FUN_10008180((int)DAT_100cc53c);
          operator_delete(pcVar1);
        }
        pvVar3 = DAT_100cc514;
        if (DAT_100cc514 != (void *)0x0) {
          FUN_1001fae0();
          operator_delete(pvVar3);
        }
        puVar4 = DAT_100cc50c;
        if (DAT_100cc50c != (undefined4 *)0x0) {
          FUN_1001c090();
          operator_delete(puVar4);
        }
        pvVar3 = DAT_100cc518;
        if (DAT_100cc518 != (void *)0x0) {
          FUN_10037ca0((int)DAT_100cc518);
          operator_delete(pvVar3);
        }
        FUN_10001340();
        destroy_repair_profile_pointer_list();
        FUN_10031870();
        HeapDestroy(DAT_10051c50);
        DAT_10051c50 = (HANDLE)0x0;
        ExceptionList = local_c;
        return uVar6;
      }
      TranslateMessage(&tStack_28);
      DispatchMessageA(&tStack_28);
    }
    if (DAT_10043224 != 0) {
      update_debug_mouse_coordinate_overlay((int)DAT_100cc514);
      if (DAT_100d21a4 == (code *)0x0) {
        if (DAT_100d21a0 == (code *)0x0) {
          if (DAT_100d219c != (code *)0x0) {
            (*DAT_100d219c)(DAT_100cc53c,&DAT_100d2198,&DAT_100d2178,DAT_10049bbc);
            DAT_10049bbc = 0xc004;
          }
        }
        else {
          (*DAT_100d21a0)(1);
        }
      }
      else {
        (*DAT_100d21a4)();
      }
      if (DAT_100d21ac == 0) {
        flush_or_repaint_shell_surface_context((int)DAT_100cc518);
      }
    }
    validate_joined_multiplayer_session_and_fill_launch_config();
  } while( true );
}


