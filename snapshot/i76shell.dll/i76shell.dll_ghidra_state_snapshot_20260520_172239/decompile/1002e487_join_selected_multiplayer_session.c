/*
 * Program: i76shell.dll
 * Function: join_selected_multiplayer_session
 * Entry: 1002e487
 * Signature: undefined4 __cdecl join_selected_multiplayer_session(int param_1, int param_2, int param_3, int param_4)
 */


undefined4 __cdecl
join_selected_multiplayer_session(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  LPCSTR pCVar3;
  LPCSTR pCVar4;
  undefined4 uVar5;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  byte *pbVar10;
  byte *pbVar11;
  char *pcVar12;
  char *pcVar13;
  UINT UVar14;
  int iVar15;
  size_t _Count;
  int local_130 [2];
  undefined2 uStack_128;
  undefined1 uStack_126;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  char acStack_10c [24];
  byte local_f4 [80];
  char acStack_a4 [80];
  undefined4 local_54;
  
  if (param_2 == 0) {
    assert(s_param_1004c3b0,s_D__TVF_I76Upgrade_Shell_Source_F_1004c380,0x15f);
  }
  switch(param_1) {
  case 2:
  case 5:
    directplay_session_enum_callback((char *)(param_4 + param_3 * 0x2d));
  case 3:
  case 4:
    iVar15 = start_hosted_multiplayer_game_session_and_fill_launch_config
                       (param_2,(char *)(param_4 + param_3 * 0x2d));
    if (iVar15 != 0) {
      if (DAT_100f3548 != (HANDLE)0x0) {
        WaitForSingleObject(DAT_100f3548,0xffffffff);
        CloseHandle(DAT_100f3548);
        DAT_100f3548 = (HANDLE)0x0;
      }
      DAT_100f21cc = 3;
      return 1;
    }
    break;
  case 6:
  case 7:
  case 8:
  case 9:
    if (*(int *)(param_2 + 0x78) == *(int *)(param_2 + 0x7c)) {
      UVar14 = 0;
      pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Game_full__1004c3b8);
      pCVar4 = (LPCSTR)resolve_localized_shell_string_cached
                                 (DAT_100f5360,s_The_game_is_full__1004c3c4);
      MessageBoxA(DAT_100f702c,pCVar4,pCVar3,UVar14);
      return 0;
    }
    if ((param_1 == 6) || (param_1 == 9)) {
      iVar15 = 2;
    }
    else {
      iVar15 = 1;
    }
    restore_previous_shell_dialog_state(iVar15);
    DAT_100f4ee4 = 1;
    DAT_100f21d8 = GetTickCount();
    puVar8 = (undefined4 *)(param_2 + 0x20);
    puVar9 = &local_54;
    for (iVar15 = 0x14; iVar15 != 0; iVar15 = iVar15 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar9 = puVar9 + 1;
    }
    local_130[0] = 0;
    *(undefined2 *)puVar9 = *(undefined2 *)puVar8;
    *(undefined1 *)((int)puVar9 + 2) = *(undefined1 *)((int)puVar8 + 2);
    DAT_100f2324 = 0;
    if ((DAT_100d21b4 == 0) && (DAT_100d21b0 == 0)) {
      iVar15 = dpOpen(DAT_100f4ee8,&local_54,&LAB_1002f338,local_130);
      if (iVar15 != 0) {
        UVar14 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Notice_1004c948);
        pcVar13 = s_Cannot_get_info_on_this_game_1004c950;
LAB_1002e667:
        pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,pcVar13);
        MessageBoxA(DAT_100f702c,pCVar4,pCVar3,UVar14);
        FUN_1000c2a0();
        DAT_100f4ee4 = 0;
        return 0;
      }
      do {
        validate_joined_multiplayer_session_and_fill_launch_config();
      } while (local_130[0] == 0);
      if (local_130[0] == 2) {
        UVar14 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Notice_1004c920);
        pcVar13 = s_Cannot_open_connection_to_game_1004c928;
        goto LAB_1002e667;
      }
    }
    if (DAT_100d218c == 0) {
      do {
        validate_joined_multiplayer_session_and_fill_launch_config();
      } while (DAT_100f2324 == 0);
      format_launch_config_resource_path_at_0x4e((LPSTR)local_f4);
      iVar15 = -1;
      pbVar10 = local_f4;
      do {
        pbVar11 = pbVar10;
        if (iVar15 == 0) break;
        iVar15 = iVar15 + -1;
        pbVar11 = pbVar10 + 1;
        bVar1 = *pbVar10;
        pbVar10 = pbVar11;
      } while (bVar1 != 0);
      *(undefined4 *)(pbVar11 + -1) = DAT_1004c970;
      pbVar11[3] = DAT_1004c974;
      iVar15 = (**(code **)(DAT_10058198 + 0x68))(local_f4,DAT_100f4778,&DAT_100f3550);
      if (iVar15 == 0) {
        FUN_1000c2a0();
        DAT_100f4ee4 = 0;
        FUN_1000b980();
        dpClose(DAT_100f4ee8);
        FUN_1000c2a0();
        DAT_100f4ee4 = 0;
        return 0;
      }
    }
    _Count = 0x18;
    pcVar13 = directplay_player_enum_callback();
    strncpy(acStack_10c,pcVar13,_Count);
    pcVar13 = (char *)copy_directplay_guid_or_descriptor_blob();
    uVar6 = 0xffffffff;
    do {
      pcVar12 = pcVar13;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar12 = pcVar13 + 1;
      cVar2 = *pcVar13;
      pcVar13 = pcVar12;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar13 = pcVar12 + -uVar6;
    pcVar12 = acStack_a4;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar12 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      pcVar12 = pcVar12 + 1;
    }
    pbVar10 = local_f4;
    uVar6 = 0;
    iVar15 = 0;
    uVar5 = free_directplay_session_descriptor();
    FUN_10015af0(acStack_a4,(char)uVar5,iVar15,uVar6,pbVar10);
    DAT_100f3560 = 0;
    iVar15 = dpCreatePlayer(DAT_100f4ee8,&LAB_1002f358,&DAT_100f3560,acStack_10c);
    if (iVar15 == 0) {
      do {
        validate_joined_multiplayer_session_and_fill_launch_config();
      } while (DAT_100f3560 == 0);
      UVar14 = 0;
      if (DAT_100f3560 == -0x5ff) {
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c978);
        pCVar4 = (LPCSTR)resolve_localized_shell_string_cached
                                   (DAT_100f5360,s_Could_not_create_player_1004c980);
        MessageBoxA(DAT_100f702c,pCVar4,pCVar3,UVar14);
        dpClose(DAT_100f4ee8);
        FUN_1000c2a0();
        DAT_100f4ee4 = 0;
        return 0;
      }
      dpSetPlayerData(DAT_100f4ee8,CONCAT22(extraout_var,DAT_100f3560),1,local_f4,0x50);
      dpSetPlayerData(DAT_100f4ee8,CONCAT22(extraout_var_00,DAT_100f3560),4,&DAT_100f3554,4,0);
      local_130[1] = 0;
      uStack_124 = 0;
      uStack_128 = 0x4552;
      uStack_126 = 0;
      uStack_120 = 0;
      uStack_11c = 0;
      iVar15 = dpSend(DAT_100f4ee8,CONCAT22(0x1005,DAT_100f3560),0,0,&uStack_128,0x10);
      if ((iVar15 != 0) && (iVar15 != 3)) {
        assert(s__DP_OK____retval______dp_RES_FUL_1004ca08,
               s_D__TVF_I76Upgrade_Shell_Source_F_1004c9d8,0x704);
      }
      DAT_100f21d8 = GetTickCount();
      DAT_100f21cc = 2;
      return 1;
    }
    UVar14 = 0;
    if (iVar15 == 3) {
      pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Game_full__1004c998);
      pcVar13 = s_The_game_is_full__1004c9a4;
    }
    else {
      pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c9b8);
      pcVar13 = s_Could_not_create_player_1004c9c0;
    }
    pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,pcVar13);
    MessageBoxA(DAT_100f702c,pCVar4,pCVar3,UVar14);
    dpClose(DAT_100f4ee8);
    FUN_1000c2a0();
    DAT_100f4ee4 = 0;
    break;
  default:
    return 1;
  }
  return 0;
}


