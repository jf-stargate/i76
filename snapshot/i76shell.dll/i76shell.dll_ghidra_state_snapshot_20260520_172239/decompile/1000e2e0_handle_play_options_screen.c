/*
 * Program: i76shell.dll
 * Function: handle_play_options_screen
 * Entry: 1000e2e0
 * Signature: undefined __stdcall handle_play_options_screen(void)
 */


void handle_play_options_screen(void)

{
  char cVar1;
  size_t *psVar2;
  char *pcVar3;
  int iVar4;
  HCURSOR hCursor;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  int *piVar8;
  undefined4 local_18;
  long local_14;
  void *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_1004017b;
  local_c = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_c;
  if (DAT_10044ee8 != 0) {
    DAT_10044ee8 = 0;
    ExceptionList = &local_c;
    pcVar3 = (char *)resolve_localized_shell_string_cached(DAT_100f5360,s_Play_Options_10045004);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Play_Options_10044608;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Graphic_Detail_10045014);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Graphic_Detail_10044626;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Audio_Control_10045024);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Audio_Control_10044644;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Control_Configuration_10045034);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Control_Configuration_10044662;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Load_Bookmark_1004504c);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Load_Bookmark_10044680;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Save_Bookmark_1004505c);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Save_Bookmark_1004469e;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Exit_Interstate__76_1004506c);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Exit_Interstate__76_100446bc;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Done_10045080);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = (char *)&DAT_100446da;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Exit_Trip_10045088);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Exit_Trip_100446f8;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Credits_10045094);
    psVar2 = DAT_100f5360;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Credits_10044716;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar3 = (char *)resolve_localized_shell_string_cached(psVar2,s_Modem_Setup_1004509c);
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar7 + -uVar5;
    pcVar7 = s_Modem_Setup_10044734;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  DAT_10055d90 = 0;
  copy_shell_surface_palette_out(DAT_100cc518,(undefined4 *)&DAT_10055db0);
  *(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0x10;
  clear_text_rect(DAT_100cc518,0x177,0x7c,0x102,0x160);
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0x6);
  FUN_1001a6e0();
  FUN_100076c0();
  mpack_database_get_item(DAT_100cc53c,0x48,&local_18,&local_14);
  local_10 = operator_new(4);
  local_4 = 0;
  if (local_10 == (void *)0x0) {
    DAT_10055d98 = (undefined4 *)0x0;
  }
  else {
    DAT_10055d98 = (undefined4 *)FUN_10036610(local_10,local_18);
  }
  local_4 = 0xffffffff;
  FUN_100366d0();
  FUN_10036640(DAT_10055d98);
  iVar4 = 1;
  do {
    *(char *)(iVar4 + 0x10056af8) = (char)iVar4;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x100);
  DAT_10056af9 = 200;
  FUN_1001c0a0(DAT_100cc50c);
  if (DAT_100d2168 == 0xc00e) {
    piVar8 = (int *)&DAT_10044990;
  }
  else if (*(int *)(DAT_100c5ad8 + 0x20) == 2) {
    piVar8 = (int *)&DAT_10044780;
  }
  else {
    piVar8 = (int *)&DAT_10044b48;
  }
  FUN_10016600(piVar8);
  read_player_definition_file(0,(undefined4 *)0x0);
  FUN_1001ed30(handle_static_menu_descriptor_selection);
  DAT_100d2184 = 0;
  hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  SetCursor(hCursor);
  ExceptionList = local_c;
  return;
}


