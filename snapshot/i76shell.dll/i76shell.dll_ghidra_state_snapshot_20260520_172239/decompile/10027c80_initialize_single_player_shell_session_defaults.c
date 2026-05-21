/*
 * Program: i76shell.dll
 * Function: initialize_single_player_shell_session_defaults
 * Entry: 10027c80
 * Signature: undefined __stdcall initialize_single_player_shell_session_defaults(void)
 */


void initialize_single_player_shell_session_defaults(void)

{
  char cVar1;
  LPVOID pvVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  undefined4 *puVar8;
  char *pcVar9;
  undefined1 local_118 [20];
  char local_104 [260];
  
  DAT_1004b2f4 = 7;
  puVar8 = &DAT_100d4038;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  DAT_100d2174 = 0;
  DAT_100f219c = 0;
  DAT_100f21a0 = 0;
  DAT_100f21a4 = 0;
  DAT_100f2198 = 0;
  DAT_100f21a8 = 0;
  DAT_100f21ac = 0;
  DAT_1004b2f8 = 0xf;
  DAT_100f1db0 = 0;
  DAT_100d3fd8 = 0;
  DAT_100d4478 = 0;
  iVar4 = read_user_mel_file((char *)&DAT_100d3fe0,&DAT_100f1d90,&DAT_100d4474,&DAT_100d402c,
                             &DAT_100f1f50,(char *)&DAT_100d4050);
  if (iVar4 == 0) {
    uVar5 = 0xffffffff;
    pcVar7 = s_Unnamed_1004c0b0;
    do {
      pcVar9 = pcVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    DAT_100d4474 = 0;
    DAT_100d402c = 1;
    pcVar7 = pcVar9 + -uVar5;
    pcVar9 = (char *)&DAT_100d3fe0;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar5 = uVar5 & 3; iVar4 = DAT_100c5ad8, uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    uVar5 = 0xffffffff;
    pcVar7 = s_Unnamed_1004c0b8;
    do {
      pcVar9 = pcVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar7 = pcVar9 + -uVar5;
    pcVar9 = &DAT_100f1d90;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    *(undefined4 *)(iVar4 + 0x38) = 0;
    uVar5 = 0xffffffff;
    pcVar7 = s_The_Crater_1004b510 + DAT_100d4474 * 0x2d;
    do {
      pcVar9 = pcVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar7 = pcVar9 + -uVar5;
    pcVar9 = (char *)&DAT_100d4050;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  DAT_100f1d68 = 0;
  DAT_100d4484 = DAT_100d402c;
  DAT_100d4480 = *(undefined4 *)(DAT_100c5ad8 + 0x38);
  DAT_100f1f50 = 0;
  DAT_100f1d60 = 0;
  DAT_100d4030 = *(undefined4 *)(DAT_100c5ad8 + 0x38);
  uVar5 = 0xffffffff;
  pcVar7 = s_Unknown_1004c0c0;
  do {
    pcVar9 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar9 + -uVar5;
  pcVar9 = (char *)&DAT_100d4000;
  DAT_100f1d5c = DAT_100d4030;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  FUN_10036000(&DAT_100d4000);
  FUN_10035fd0((char *)&DAT_100d4000);
  DAT_100d4024 = 0;
  DAT_100d4028 = 20000;
  DAT_100d4470 = 1;
  DAT_100f21b0 = 0;
  DAT_100f2194 = (int *)0x0;
  iVar4 = findfirst(s_addon___lvl_1004c0a4,local_118);
  if (iVar4 != -1) {
    DAT_100f2194 = create_pointer_list_with_capacity(0x100);
    do {
      pvVar2 = HeapAlloc(DAT_10051c50,1,0x2d);
      uVar5 = 0xffffffff;
      pcVar7 = local_104;
      do {
        pcVar9 = pcVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar7 = pcVar9 + -uVar5;
      pcVar9 = (char *)((int)pvVar2 + 0x20);
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      (**(code **)(DAT_10058198 + 0x58))(local_104,pvVar2,0x20);
      insert_pointer_list_item_sorted_or_append((int)DAT_100f2194,(int)pvVar2,(undefined *)0x0);
      iVar3 = findnext(iVar4,local_118);
    } while (iVar3 == 0);
    _findclose(iVar4);
    DAT_1004b2f8 = DAT_1004b2f8 + DAT_100f2194[1];
  }
  clear_preloaded_shell_ui_image_record_globals();
  reset_vehicle_config_ui_globals();
  return;
}


