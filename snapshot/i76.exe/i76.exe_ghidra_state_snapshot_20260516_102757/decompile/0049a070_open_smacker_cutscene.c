/*
 * Program: i76.exe
 * Function: open_smacker_cutscene
 * Entry: 0049a070
 * Signature: undefined4 __cdecl open_smacker_cutscene(undefined4 param_1, char * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_0049a070
   suggested_name: open_smacker_cutscene
   basis: Opens .smk cutscene, resolves cutscene path, calls SmackOpen and SmackBufferOpen. */

undefined4 __cdecl open_smacker_cutscene(undefined4 param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined2 uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  tagMSG local_ac;
  int local_90 [15];
  int local_54;
  int local_50;
  
  if ((g_active_smacker_cutscene_handle != 0) || (DAT_005a7d74 != (undefined1 *)0x0)) {
    return 0;
  }
  force_feedback_runtime_helper_00445b60();
  iVar2 = PeekMessageA(&local_ac,(HWND)0x0,0x200,0x209,1);
  while (iVar2 != 0) {
    iVar2 = PeekMessageA(&local_ac,(HWND)0x0,0x200,0x209,1);
  }
  iVar2 = PeekMessageA(&local_ac,(HWND)0x0,0x100,0x108,1);
  while (iVar2 != 0) {
    iVar2 = PeekMessageA(&local_ac,(HWND)0x0,0x100,0x108,1);
  }
  iVar2 = set_directsound_primary_buffer_rate(DAT_00524564,0x5622);
  if (iVar2 == 0) {
    return 0;
  }
  cVar1 = get_active_cdrom_drive_letter();
  if (cVar1 == '\0') {
    DAT_005a7cd8 = s_smk__004fe28c[0];
    DAT_005a7cd9 = s_smk__004fe28c[1];
    DAT_005a7cd8_1._1_1_ = s_smk__004fe28c[2];
    DAT_005a7cd8_1._2_1_ = s_smk__004fe28c[3];
    DAT_005a7cdc = s_smk__004fe28c[4];
  }
  else {
    DAT_005a7cd8 = s___cutscene__004fe294[0];
    DAT_005a7cd9 = s___cutscene__004fe294[1];
    DAT_005a7cd8_1._1_1_ = s___cutscene__004fe294[2];
    DAT_005a7cd8_1._2_1_ = s___cutscene__004fe294[3];
    DAT_005a7cdc = s___cutscene__004fe294[4];
    DAT_005a7cdd = s___cutscene__004fe294[5];
    DAT_005a7cdc_1._1_1_ = s___cutscene__004fe294[6];
    DAT_005a7cdc_1._2_1_ = s___cutscene__004fe294[7];
    DAT_005a7ce0 = s___cutscene__004fe294[8];
    DAT_005a7ce0_1._0_1_ = s___cutscene__004fe294[9];
    DAT_005a7ce0_1._1_1_ = s___cutscene__004fe294[10];
    DAT_005a7ce0_1._2_1_ = s___cutscene__004fe294[0xb];
    DAT_005a7ce4 = s___cutscene__004fe294[0xc];
    cVar1 = get_active_cdrom_drive_letter();
    DAT_005a7cd8 = cVar1;
  }
  uVar3 = 0xffffffff;
  pcVar6 = param_2;
  do {
    pcVar8 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar2 = -1;
  pcVar6 = &DAT_005a7cd8;
  do {
    pcVar7 = pcVar6;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  pcVar6 = pcVar8 + -uVar3;
  pcVar8 = pcVar7 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  iVar2 = ui_bitmap_region_context_helper_0049ab50(&DAT_005a7cd8,local_90);
  if (iVar2 == 0) {
LAB_0049a1dd:
    uVar3 = 0;
  }
  else if (local_50 == 0) {
    if (local_54 == 0) goto LAB_0049a1dd;
    uVar3 = 0x2000;
  }
  else {
    uVar3 = 0x4000;
  }
  g_active_smacker_cutscene_handle = _SmackOpen_12(&DAT_005a7cd8,uVar3 | 0x60,0xfa000);
  uVar5 = extraout_var;
  if (g_active_smacker_cutscene_handle == 0) {
    cVar1 = get_active_cdrom_drive_letter();
    uVar5 = extraout_var_00;
    if (cVar1 != '\0') {
      DAT_005a7cd8 = s_smk__004fe28c[0];
      DAT_005a7cd9 = s_smk__004fe28c[1];
      DAT_005a7cd8_1._1_1_ = s_smk__004fe28c[2];
      DAT_005a7cd8_1._2_1_ = s_smk__004fe28c[3];
      uVar3 = 0xffffffff;
      DAT_005a7cdc = s_smk__004fe28c[4];
      do {
        pcVar6 = param_2;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar6 = param_2 + 1;
        cVar1 = *param_2;
        param_2 = pcVar6;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      iVar2 = -1;
      pcVar8 = &DAT_005a7cd8;
      do {
        pcVar7 = pcVar8;
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        pcVar7 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar7;
      } while (cVar1 != '\0');
      pcVar6 = pcVar6 + -uVar3;
      pcVar8 = pcVar7 + -1;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar8 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar8 = pcVar8 + 1;
      }
      iVar2 = ui_bitmap_region_context_helper_0049ab50(&DAT_005a7cd8,local_90);
      if (iVar2 == 0) {
LAB_0049a286:
        uVar3 = 0;
      }
      else if (local_50 == 0) {
        if (local_54 == 0) goto LAB_0049a286;
        uVar3 = 0x2000;
      }
      else {
        uVar3 = 0x4000;
      }
      g_active_smacker_cutscene_handle = _SmackOpen_12(&DAT_005a7cd8,uVar3 | 0x60,0xfa000);
      uVar5 = extraout_var_01;
    }
    if (g_active_smacker_cutscene_handle != 0) goto LAB_0049a30b;
    if (DAT_005a7d74 == (undefined1 *)0x0) goto LAB_0049a373;
    _SmackBufferClose_4(DAT_005a7d74);
    DAT_005a7d74 = (undefined1 *)0x0;
    if (g_active_smacker_cutscene_handle == 0) goto LAB_0049a384;
    _SmackClose_4(g_active_smacker_cutscene_handle);
    g_active_smacker_cutscene_handle = 0;
    mission_flow_map_context_helper_0049cdd0(1);
    if (DAT_00504be8 != 0) {
      prepare_smacker_cutscene_display_surface(&DAT_005dcec0,DAT_005dd32c);
      goto LAB_0049a3bc;
    }
  }
  else {
LAB_0049a30b:
    DAT_005a7d6c = DAT_005dd360;
    if (DAT_005dd360 != 0) {
      DAT_005dd360 = 0;
      iVar2 = (*DAT_005dd2cc)(&DAT_005dcec0,0);
      uVar5 = extraout_var_02;
      if (iVar2 == 0) {
        report_chunk_parse_error();
        uVar5 = extraout_var_03;
      }
    }
    DAT_005a7d74 = (undefined1 *)
                   _SmackBufferOpen_24(param_1,0,
                                       CONCAT22(uVar5,*(undefined2 *)
                                                       (g_active_smacker_cutscene_handle + 4)),
                                       *(undefined2 *)(g_active_smacker_cutscene_handle + 8),0,0);
    if (DAT_005a7d74 != (undefined1 *)0x0) {
      mission_flow_map_context_helper_0049cdd0(0x20);
      pause_cd_audio_for_cutscene_or_mode_change();
      if (DAT_00504be8 == 0) {
        (*DAT_005dd2e4)(&DAT_005dcec0,DAT_005dd32c);
      }
      else {
        prepare_smacker_cutscene_display_surface(&DAT_005dcec0,DAT_005dd32c);
      }
      (*DAT_005dd2e0)(&DAT_005dcec0);
      _SmackToBuffer_28(g_active_smacker_cutscene_handle,0,0,*(undefined4 *)(DAT_005a7d74 + 0x18),
                        *(undefined4 *)(DAT_005a7d74 + 0x14),*(undefined4 *)(DAT_005a7d74 + 0x448),
                        *DAT_005a7d74);
      return 1;
    }
    DAT_005a7d74 = (undefined1 *)0x0;
LAB_0049a373:
    if (g_active_smacker_cutscene_handle != 0) {
      _SmackClose_4(g_active_smacker_cutscene_handle);
      g_active_smacker_cutscene_handle = 0;
    }
LAB_0049a384:
    mission_flow_map_context_helper_0049cdd0(1);
    if (DAT_00504be8 != 0) {
      prepare_smacker_cutscene_display_surface(&DAT_005dcec0,DAT_005dd32c);
      goto LAB_0049a3bc;
    }
  }
  (*DAT_005dd2e4)(&DAT_005dcec0,DAT_005dd32c);
LAB_0049a3bc:
  (*DAT_005dd2e0)(&DAT_005dcec0);
  DAT_005dd360 = DAT_005a7d6c;
  iVar2 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005a7d6c);
  if (iVar2 == 0) {
    report_chunk_parse_error();
  }
  (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_005dcfa8);
  set_directsound_primary_buffer_rate(DAT_00524564,0x2b11);
  return 0;
}


