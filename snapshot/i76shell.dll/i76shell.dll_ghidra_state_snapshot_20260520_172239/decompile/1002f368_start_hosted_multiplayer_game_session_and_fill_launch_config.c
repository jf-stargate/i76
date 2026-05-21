/*
 * Program: i76shell.dll
 * Function: start_hosted_multiplayer_game_session_and_fill_launch_config
 * Entry: 1002f368
 * Signature: undefined4 __cdecl start_hosted_multiplayer_game_session_and_fill_launch_config(int param_1, char * param_2)
 */


undefined4 __cdecl
start_hosted_multiplayer_game_session_and_fill_launch_config(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  LPCSTR pCVar3;
  LPCSTR pCVar4;
  undefined4 uVar5;
  undefined2 extraout_var;
  HANDLE hObject;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined4 *puVar10;
  byte *pbVar11;
  uint *puVar12;
  undefined4 *puVar13;
  byte *pbVar14;
  uint *puVar15;
  bool bVar16;
  size_t sVar17;
  UINT UVar18;
  uint uStack_238;
  undefined1 auStack_232 [2];
  char acStack_230 [24];
  CHAR aCStack_218 [16];
  undefined4 uStack_208;
  char acStack_1fb [4];
  undefined2 uStack_1f7;
  undefined2 uStack_1f3;
  char acStack_1f1 [31];
  undefined1 uStack_1d2;
  uint uStack_1b9;
  byte abStack_1b4 [80];
  undefined4 uStack_164;
  char acStack_111 [30];
  char acStack_f3 [31];
  undefined4 uStack_d4;
  uint uStack_d0;
  char acStack_cc [32];
  uint uStack_ac;
  uint uStack_a8;
  uint uStack_a4;
  char acStack_a0 [80];
  char acStack_50 [80];
  
  format_directplay_session_descriptor(&DAT_100f4778);
  (**(code **)(DAT_10058198 + 100))(DAT_100f477c,&DAT_100f4780);
  format_launch_config_resource_path_at_0x4e(aCStack_218);
  iVar7 = -1;
  pcVar2 = aCStack_218;
  do {
    pcVar6 = pcVar2;
    if (iVar7 == 0) break;
    iVar7 = iVar7 + -1;
    pcVar6 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar6;
  } while (cVar1 != '\0');
  *(undefined4 *)(pcVar6 + -1) = DAT_1004c460;
  pcVar6[3] = DAT_1004c464;
  iVar7 = (**(code **)(DAT_10058198 + 0x68))(aCStack_218,DAT_100f4778,&DAT_100f3550);
  if (iVar7 == 0) {
    FUN_1000b980();
  }
  else {
    sVar17 = 0x20;
    puVar10 = &uStack_208;
    for (iVar7 = 0x14; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    *(undefined2 *)puVar10 = 0;
    *(undefined1 *)((int)puVar10 + 2) = 0;
    uStack_208._0_1_ = 0x53;
    acStack_1fb[0] = s_0_1004cedc[0];
    acStack_1fb[1] = s_0_1004cedc[1];
    uStack_1f3 = 1;
    pcVar2 = (char *)directplay_provider_enum_callback();
    strncpy(acStack_1f1,pcVar2,sVar17);
    uStack_1d2 = 0;
    uVar8 = *(uint *)(param_1 + 0x44);
    uStack_1f7 = *(undefined2 *)(param_1 + 0x40);
    uStack_1b9 = 0;
    if ((uVar8 & 0x4000) != 0) {
      uStack_1b9 = 0x40000000;
    }
    if ((uVar8 & 0x2000) != 0) {
      uStack_1b9 = uStack_1b9 | *(uint *)(param_1 + 0x48) & 0x3fffffff;
    }
    if ((uVar8 & 0x8000) != 0) {
      uStack_1b9 = uStack_1b9 | 0x80000000;
    }
    if (((DAT_100d21b4 == 0) && (DAT_100d21b0 == 0)) &&
       (iVar7 = dpOpen(DAT_100f4ee8,&uStack_208,0,0), iVar7 != 0)) {
      switch(iVar7) {
      case 1:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c468);
        pcVar2 = s_Could_not_start_game_1004c470;
        break;
      case 2:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c488);
        pcVar2 = s_Could_not_start_game_1004c490;
        break;
      case 3:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c4a8);
        pcVar2 = s_Could_not_start_game_1004c4b0;
        break;
      case 4:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c4c8);
        pcVar2 = s_Could_not_start_game_1004c4d0;
        break;
      case 5:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c4e8);
        pcVar2 = s_Could_not_start_game_1004c4f0;
        break;
      case 6:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c508);
        pcVar2 = s_Could_not_start_game_1004c510;
        break;
      case 7:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c528);
        pcVar2 = s_Could_not_start_game_1004c530;
        break;
      case 8:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c548);
        pcVar2 = s_Could_not_start_game_1004c550;
        break;
      case 9:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c568);
        pcVar2 = s_Modem_busy_1004c570;
        break;
      case 10:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c57c);
        pcVar2 = s_No_answer_from_modem_1004c584;
        break;
      case 0xb:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c59c);
        pcVar2 = s_No_dialtone_from_modem_1004c5a4;
        break;
      case 0xc:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c5bc);
        pcVar2 = s_No_response_from_modem_1004c5c4;
        break;
      case 0xd:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c5dc);
        pcVar2 = s_Network_not_present_1004c5e4;
        break;
      case 0xe:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c5f8);
        pcVar2 = s_Bad_service_provider_version_1004c600;
        break;
      case 0xf:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c620);
        pcVar2 = s_Network_not_responding_1004c628;
        break;
      case 0x10:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c640);
        pcVar2 = s_Game_Server_not_responding_1004c648;
        break;
      default:
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c664);
        pcVar2 = s_Could_not_start_game_1004c66c;
      }
      pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,pcVar2);
      MessageBoxA(DAT_100f702c,pCVar4,pCVar3,UVar18);
      return 0;
    }
    sVar17 = 0x18;
    pcVar2 = directplay_player_enum_callback();
    strncpy(acStack_230,pcVar2,sVar17);
    pcVar2 = (char *)copy_directplay_guid_or_descriptor_blob();
    uVar8 = 0xffffffff;
    do {
      pcVar6 = pcVar2;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      pcVar6 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar6;
    } while (cVar1 != '\0');
    uVar8 = ~uVar8;
    pcVar2 = pcVar6 + -uVar8;
    pcVar6 = acStack_a0;
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar6 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar6 = pcVar6 + 1;
    }
    pbVar11 = abStack_1b4;
    uVar8 = 0;
    iVar7 = 1;
    uVar5 = free_directplay_session_descriptor();
    FUN_10015af0(acStack_a0,(char)uVar5,iVar7,uVar8,pbVar11);
    DAT_100f3560 = 0;
    iVar7 = dpCreatePlayer(DAT_100f4ee8,&LAB_1002f358,&DAT_100f3560,acStack_230);
    if (iVar7 == 0) {
      UVar18 = 0;
      if (DAT_100f3560 == 0) {
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c6a4);
        pCVar4 = (LPCSTR)resolve_localized_shell_string_cached
                                   (DAT_100f5360,s_Could_not_create_player_id_1004c6ac);
        MessageBoxA(DAT_100f702c,pCVar4,pCVar3,UVar18);
        dpClose(DAT_100f4ee8);
        return 0;
      }
      dpSetPlayerData(DAT_100f4ee8,DAT_100f3560,1,abStack_1b4,0x50);
      dpSetPlayerData(DAT_100f4ee8,CONCAT22(extraout_var,DAT_100f3560),2,param_2,0x20,0);
      dpSetPlayerData(DAT_100f4ee8,CONCAT22(extraout_var_01,DAT_100f3560),3,&DAT_100f4778,0x198,0);
      dpSetPlayerData(DAT_100f4ee8,CONCAT22(extraout_var_00,DAT_100f3560),4,&DAT_100f3554,4,0);
      puVar10 = &uStack_208;
      puVar13 = &uStack_164;
      for (iVar7 = 0x14; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar13 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar13 = puVar13 + 1;
      }
      *(undefined2 *)puVar13 = *(undefined2 *)puVar10;
      *(undefined1 *)((int)puVar13 + 2) = *(undefined1 *)((int)puVar10 + 2);
      pcVar2 = (char *)directplay_provider_enum_callback();
      uVar8 = 0xffffffff;
      do {
        pcVar6 = pcVar2;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar6 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar6;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      pcVar2 = pcVar6 + -uVar8;
      pcVar6 = acStack_111;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar6 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar6 = pcVar6 + 1;
      }
      uVar8 = 0xffffffff;
      pcVar2 = param_2;
      do {
        pcVar6 = pcVar2;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar6 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar6;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      pcVar2 = pcVar6 + -uVar8;
      pcVar6 = acStack_f3;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar6 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar6 = pcVar6 + 1;
      }
      uStack_d4 = 0;
      uStack_d0 = *(uint *)(param_1 + 0x40);
      uVar8 = 0xffffffff;
      pcVar2 = acStack_230;
      do {
        pcVar6 = pcVar2;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar6 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar6;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      pcVar2 = pcVar6 + -uVar8;
      pcVar6 = acStack_cc;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar6 = pcVar6 + 4;
      }
      uVar9 = *(uint *)(param_1 + 0x44);
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar6 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar6 = pcVar6 + 1;
      }
      uStack_ac = uVar9 >> 0xe & 1;
      if ((uVar9 & 0x2000) == 0) {
        uStack_a8 = 0xffffffff;
      }
      else {
        uStack_a8 = *(uint *)(param_1 + 0x48);
      }
      uStack_a4 = uVar9 >> 0xf & 1;
      FUN_100159d0((int)&uStack_164,abStack_1b4);
      uVar8 = 0xffffffff;
      pcVar2 = &DAT_1004c6c8;
      do {
        pcVar6 = pcVar2;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar6 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar6;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      pcVar2 = pcVar6 + -uVar8;
      pcVar6 = acStack_230;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar6 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar6 = pcVar6 + 1;
      }
      iVar7 = dpCreateGroup(DAT_100f4ee8,auStack_232,acStack_230);
      if (iVar7 != 0) {
        UVar18 = 0;
        pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c6cc);
        pCVar4 = (LPCSTR)resolve_localized_shell_string_cached
                                   (DAT_100f5360,s_Could_not_start_game_1004c6d4);
        MessageBoxA(DAT_100f702c,pCVar4,pCVar3,UVar18);
        dpClose(DAT_100f4ee8);
        return 0;
      }
      pcVar2 = param_2 + 0x20;
      _splitpath(pcVar2,(char *)0x0,(char *)0x0,(char *)0x0,(char *)abStack_1b4);
      iVar7 = 5;
      bVar16 = true;
      pbVar11 = abStack_1b4;
      pbVar14 = &DAT_1004c6ec;
      do {
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        bVar16 = *pbVar11 == *pbVar14;
        pbVar11 = pbVar11 + 1;
        pbVar14 = pbVar14 + 1;
      } while (bVar16);
      if (bVar16) {
        sprintf((char *)abStack_1b4,s_addon__s_1004c6f4,pcVar2);
        hObject = CreateFileA((LPCSTR)abStack_1b4,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0,
                              (HANDLE)0x0);
        if (hObject == (HANDLE)0xffffffff) {
          pcVar6 = (char *)resolve_localized_shell_string_cached
                                     (DAT_100f5360,s_Mission_file__s_not_found__1004c700);
          sprintf(acStack_50,pcVar6,pcVar2);
          UVar18 = 0;
          pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c71c);
          MessageBoxA(DAT_100f702c,acStack_50,pCVar3,UVar18);
          return 0;
        }
        FUN_10022bc0();
        CloseHandle(hObject);
      }
      else {
        uStack_238 = 0;
      }
      puVar12 = DAT_100f231c;
      for (iVar7 = 0x8c; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar12 = 0;
        puVar12 = puVar12 + 1;
      }
      DAT_100f231c[2] = DAT_100f4ee8;
      DAT_100f231c[1] = DAT_100d217c;
      *(short *)(DAT_100f231c + 3) = DAT_100f3560;
      *DAT_100f231c = 1;
      *DAT_100f231c = *DAT_100f231c | -(uint)(DAT_100d218c != 0) & 0x20;
      *DAT_100f231c = *DAT_100f231c | (-(uint)(uStack_ac != 0) & 0xfffffffc) + 4;
      *DAT_100f231c = *DAT_100f231c | -(uint)(uStack_a4 != 0) & 8;
      format_launch_config_resource_path_at_0x4e((LPSTR)((int)DAT_100f231c + 0x4e));
      uVar8 = 0xffffffff;
      do {
        pcVar6 = pcVar2;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar6 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar6;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      pcVar2 = pcVar6 + -uVar8;
      pcVar6 = (char *)((int)DAT_100f231c + 0x5d);
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar6 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar6 = pcVar6 + 1;
      }
      uVar8 = 0xffffffff;
      do {
        pcVar2 = param_2;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar2 = param_2 + 1;
        cVar1 = *param_2;
        param_2 = pcVar2;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      puVar12 = (uint *)(pcVar2 + -uVar8);
      puVar15 = DAT_100f231c + 0x1c;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *puVar15 = *puVar12;
        puVar12 = puVar12 + 1;
        puVar15 = puVar15 + 1;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(char *)puVar15 = (char)*puVar12;
        puVar12 = (uint *)((int)puVar12 + 1);
        puVar15 = (uint *)((int)puVar15 + 1);
      }
      DAT_100f231c[0x1b] = uStack_238;
      DAT_100f231c[0x24] = uStack_d0;
      DAT_100f231c[0x25] = uStack_a8;
      puVar12 = &DAT_100f4778;
      puVar15 = DAT_100f231c + 0x26;
      for (iVar7 = 0x66; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar15 = *puVar12;
        puVar12 = puVar12 + 1;
        puVar15 = puVar15 + 1;
      }
      return 1;
    }
    UVar18 = 0;
    pCVar3 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c684);
    pCVar4 = (LPCSTR)resolve_localized_shell_string_cached
                               (DAT_100f5360,s_Could_not_create_player_1004c68c);
    MessageBoxA(DAT_100f702c,pCVar4,pCVar3,UVar18);
  }
  dpClose(DAT_100f4ee8);
  return 0;
}


