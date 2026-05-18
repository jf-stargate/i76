/*
 * Program: i76.exe
 * Function: load_zone_satellite_map
 * Entry: 004939d0
 * Signature: undefined4 __cdecl load_zone_satellite_map(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: strings addon/%s another.sat Zone loader error
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=i76_runtime_load_ter_sidecar_pages :: ZONE handler
   / .TER sidecar loader. Opens ADDON/%s or CD fallback, maps terrain payload, then fills runtime
   active-zone page pointer table with 0x8000-byte strides. */

undefined4 __cdecl load_zone_satellite_map(int param_1)

{
  char cVar1;
  int iVar2;
  BOOL BVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  char *pcVar12;
  bool bVar13;
  undefined4 local_1b0 [3];
  char local_1a4 [4];
  char local_1a0 [4];
  char local_19c [120];
  undefined1 local_124 [36];
  char local_100 [256];
  
  pcVar10 = (char *)(param_1 + 9);
  if ((pcVar10 == (char *)0x0) || (*pcVar10 == '\0')) goto LAB_00493b7d;
  sprintf(local_1a4,s_addon_percent_s,pcVar10);
  iVar2 = stat(local_1a4,local_124);
  if (iVar2 == -1) {
    iVar2 = mission16_system_log_tag((undefined4 *)local_1a4);
    uVar5 = 0xffffffff;
    pcVar9 = s___004f4bb4;
    do {
      pcVar12 = pcVar9;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar12 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar12;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    iVar6 = -1;
    pcVar9 = local_1a4;
    do {
      pcVar11 = pcVar9;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pcVar11 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar11;
    } while (cVar1 != '\0');
    pcVar9 = pcVar12 + -uVar5;
    pcVar12 = pcVar11 + -1;
    for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar12 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      pcVar12 = pcVar12 + 1;
    }
    uVar5 = 0xffffffff;
    do {
      pcVar9 = pcVar10;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar9 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar9;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    iVar6 = -1;
    pcVar10 = local_1a4;
    do {
      pcVar12 = pcVar10;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pcVar12 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar12;
    } while (cVar1 != '\0');
    pcVar10 = pcVar9 + -uVar5;
    pcVar9 = pcVar12 + -1;
    for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar9 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar9 = pcVar9 + 1;
    }
    if ((iVar2 != 0) && (cVar1 = get_active_cdrom_drive_letter(), cVar1 != '\0')) {
      stop_cd_audio_track_if_playing();
      sprintf(local_100,s__c___s_004faeb0,(int)cVar1,local_1a4);
      iVar2 = stat(local_100,local_124);
      if (iVar2 != -1) {
        SetFileAttributesA(s_another_sat,0x80);
        BVar3 = CopyFileA(local_100,s_another_sat,0);
        if (BVar3 != 0) {
          SetFileAttributesA(s_another_sat,0x80);
          local_1a4[0] = s_another_sat[0];
          local_1a4[1] = s_another_sat[1];
          local_1a4[2] = s_another_sat[2];
          local_1a4[3] = s_another_sat[3];
          local_1a0[0] = s_another_sat[4];
          local_1a0[1] = s_another_sat[5];
          local_1a0[2] = s_another_sat[6];
          local_1a0[3] = s_another_sat[7];
          local_19c[0] = s_another_sat[8];
          local_19c[1] = s_another_sat[9];
          local_19c[2] = s_another_sat[10];
          local_19c[3] = s_another_sat[0xb];
          goto LAB_00493b45;
        }
      }
LAB_00493b7d:
      bVar13 = false;
      goto LAB_00493b7f;
    }
  }
LAB_00493b45:
  puVar4 = (undefined4 *)
           graphics_error_ui_graphics_error_dialog_helper_00471400(local_1b0,local_1a4,(char *)0x0);
  _g_runtime_ter_file_mapping_or_handle_block = *puVar4;
  _DAT_005a606c = puVar4[1];
  DAT_005a6070 = puVar4[2];
  bVar13 = DAT_005a6070 != 0;
LAB_00493b7f:
  if (!bVar13) {
    report_chunk_parse_error();
    return 0;
  }
  if (0 < g_runtime_active_zone_count) {
    piVar8 = &g_runtime_active_zone_page_ptrs;
    iVar2 = DAT_005a6070;
    iVar6 = g_runtime_active_zone_count;
    do {
      *piVar8 = iVar2;
      iVar2 = iVar2 + 0x8000;
      piVar8 = piVar8 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  return 1;
}


