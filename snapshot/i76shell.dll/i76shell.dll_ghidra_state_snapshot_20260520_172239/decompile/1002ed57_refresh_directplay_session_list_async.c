/*
 * Program: i76shell.dll
 * Function: refresh_directplay_session_list_async
 * Entry: 1002ed57
 * Signature: undefined4 __stdcall refresh_directplay_session_list_async(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 refresh_directplay_session_list_async(void)

{
  char cVar1;
  DWORD DVar2;
  char *pcVar3;
  LPCSTR lpCaption;
  LPCSTR lpText;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  char *pcVar8;
  undefined4 *puVar9;
  bool bVar10;
  UINT uType;
  int local_d4;
  
  validate_joined_multiplayer_session_and_fill_launch_config();
  if (DAT_100f354c != 1) goto LAB_1002f004;
  DVar2 = GetTickCount();
  if ((1000 < DVar2 - _DAT_100f4910) && (DAT_100f2320 == 0)) {
    _DAT_100f3564 = 0;
    local_d4 = 0;
    do {
      if (DAT_100f224c <= local_d4) {
        DAT_100f21cc = 0;
        uType = 0;
        lpCaption = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Notice_1004c404);
        lpText = (LPCSTR)resolve_localized_shell_string_cached
                                   (DAT_100f5360,s_This_game_has_closed__1004c40c);
        MessageBoxA(DAT_100f702c,lpText,lpCaption,uType);
        return 2;
      }
      iVar4 = 2;
      bVar10 = true;
      pcVar3 = &DAT_100f227f;
      pcVar8 = &DAT_100f2357 + local_d4 * 0x90;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar10 = *pcVar3 == *pcVar8;
        pcVar3 = pcVar3 + 1;
        pcVar8 = pcVar8 + 1;
      } while (bVar10);
      if (bVar10) {
        if (*(int *)(&DAT_100f23ac + local_d4 * 0x90) != 0) {
          pcVar3 = (char *)resolve_localized_shell_string_cached(DAT_100f5360,s_Yes_1004c3e8);
          uVar5 = 0xffffffff;
          goto code_r0x1002ee30;
        }
        pcVar3 = (char *)resolve_localized_shell_string_cached(DAT_100f5360,s_No_1004c3ec);
        uVar5 = 0xffffffff;
        goto code_r0x1002ee6a;
      }
      local_d4 = local_d4 + 1;
    } while( true );
  }
  goto LAB_1002efec;
  while( true ) {
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar8;
    if (cVar1 == '\0') break;
code_r0x1002ee6a:
    pcVar8 = pcVar3;
    if (uVar5 == 0) break;
  }
  uVar5 = ~uVar5;
  pcVar3 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_100f22e8;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar8 = pcVar8 + 1;
  }
  goto LAB_1002ee82;
  while( true ) {
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar8;
    if (cVar1 == '\0') break;
code_r0x1002ee30:
    pcVar8 = pcVar3;
    if (uVar5 == 0) break;
  }
  uVar5 = ~uVar5;
  pcVar3 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_100f22e8;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar8 = pcVar8 + 1;
  }
LAB_1002ee82:
  if (*(int *)(&DAT_100f23b0 + local_d4 * 0x90) == 0) {
    pcVar3 = (char *)resolve_localized_shell_string_cached(DAT_100f5360,s_Open_1004c3fc);
    uVar5 = 0xffffffff;
    do {
      pcVar8 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar8;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar8 + -uVar5;
    pcVar8 = (char *)&DAT_100f22c3;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  else {
    pcVar3 = (char *)resolve_localized_shell_string_cached(DAT_100f5360,s_Invite_Only_1004c3f0);
    uVar5 = 0xffffffff;
    do {
      pcVar8 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar8;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar8 + -uVar5;
    pcVar8 = (char *)&DAT_100f22c3;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  DAT_100f22e4 = *(undefined4 *)(&DAT_100f23b4 + local_d4 * 0x90);
  _DAT_100f21e0 = DAT_100f4ee8;
  puVar7 = &DAT_100f2270;
  puVar9 = &DAT_100f21e4;
  for (iVar4 = 0x14; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar9 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar9 = puVar9 + 1;
  }
  *(undefined2 *)puVar9 = *(undefined2 *)puVar7;
  *(undefined1 *)((int)puVar9 + 2) = *(undefined1 *)((int)puVar7 + 2);
  _DAT_100f2244 = DAT_100f21d0;
  _DAT_100f2238 = &DAT_100f3568;
  _DAT_100f223c = &DAT_100f4bf8;
  _DAT_100f2240 = &DAT_100f3564;
  _DAT_100f2248 = &DAT_100f22fc;
  DAT_100f2320 = 1;
  release_directplay_interface((undefined4 *)&DAT_100f21e0);
  _DAT_100f4910 = GetTickCount();
LAB_1002efec:
  if (DAT_100f2320 == 2) {
    DAT_100f2320 = 0;
    rebuild_directplay_session_pointer_list();
  }
LAB_1002f004:
  redraw_multiplayer_connection_status_dialog();
  return 0;
}


