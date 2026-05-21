/*
 * Program: i76.exe
 * Function: load_and_parse_selected_mission_resource
 * Entry: 004b42b0
 * Signature: undefined4 __cdecl load_and_parse_selected_mission_resource(char * param_1)
 */


/* [cgpt i76.exe mission/resource rename v13; confidence=high] Parses selected .msn name/family,
   stores mission-number/family globals, resolves registered resource path, loads resource,
   validates BWD2, then parses WDEF mission descriptor table.
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=load_and_parse_selected_mission_resource :: Loads
   selected mission resource, validates BWD2, then parses WDEF mission descriptor table.
   
   I76 rename v43: load_and_parse_selected_mission_resource
   Mission/resource loader path that opens/parses selected BWD2 resource. */

undefined4 __cdecl load_and_parse_selected_mission_resource(char *param_1)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  char *pcVar9;
  byte *pbVar10;
  bool bVar11;
  char local_314 [4];
  byte local_310 [16];
  char local_300 [256];
  char local_200 [256];
  char local_100 [256];
  
  reset_mission_resource_parse_callbacks();
  strncpy((char *)local_310,param_1,0x10);
  _splitpath((char *)local_310,local_314,local_100,local_300,local_200);
  _strlwr((char *)local_310);
  iVar5 = -1;
  pcVar3 = local_300;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    cVar2 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar2 != '\0');
  g_selected_mission_family = 0;
  g_selected_mission_number = 0x27;
  if (iVar5 == -5) {
    iVar5 = _stricmp(local_200,&DAT_00500678);
    if (iVar5 == 0) {
      g_selected_mission_number = atol(local_300 + 1);
      if (0 < g_selected_mission_number) {
        if (local_300[0] != 'm') {
          if (local_300[0] == 't') {
            g_selected_mission_family = 2;
            goto LAB_004b43ac;
          }
          if (local_300[0] == 's') {
            g_selected_mission_family = 3;
            goto LAB_004b43ac;
          }
          if (local_300[0] == 'p') {
            g_selected_mission_family = 3;
            goto LAB_004b43ac;
          }
          if (local_300[0] != 'n') goto LAB_004b43ac;
        }
        g_selected_mission_family = 1;
      }
    }
  }
LAB_004b43ac:
  if (local_200[0] == '\0') {
    uVar6 = 0xffffffff;
    pcVar3 = &DAT_00500678;
    do {
      pcVar9 = pcVar3;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar3 + 1;
      cVar2 = *pcVar3;
      pcVar3 = pcVar9;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    iVar5 = -1;
    pbVar8 = local_310;
    do {
      pbVar10 = pbVar8;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pbVar10 = pbVar8 + 1;
      bVar1 = *pbVar8;
      pbVar8 = pbVar10;
    } while (bVar1 != 0);
    pbVar8 = (byte *)(pcVar9 + -uVar6);
    pbVar10 = pbVar10 + -1;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pbVar10 = *(undefined4 *)pbVar8;
      pbVar8 = pbVar8 + 4;
      pbVar10 = pbVar10 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar10 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      pbVar10 = pbVar10 + 1;
    }
  }
  pcVar3 = (char *)format_registered_resource_record_path((undefined4 *)local_310);
  if (pcVar3 == (char *)0x0) {
    report_error();
  }
  _splitpath(pcVar3,local_314,local_100,local_300,local_200);
  cVar2 = get_active_cdrom_drive_letter();
  iVar5 = toupper((int)cVar2);
  iVar4 = toupper((int)local_314[0]);
  if (iVar4 == iVar5) {
    stop_cd_audio_track_if_playing();
  }
  if (&stack0x00000000 == (undefined1 *)0x310) {
    bVar11 = false;
  }
  else {
    iVar5 = _strnicmp((char *)local_310,s_null_004c3280,4);
    if (iVar5 == 0) {
      bVar11 = true;
    }
    else {
      g_current_bwd2_parse_cursor = open_resource_file_into_memory((char *)local_310);
      if (g_current_bwd2_parse_cursor != (uint *)0x0) {
        iVar5 = get_loaded_resource_file_size((char *)local_310);
        g_current_bwd2_parse_end = (int *)(iVar5 + (int)g_current_bwd2_parse_cursor);
        g_current_bwd2_parse_cursor =
             (uint *)parse_tagged_chunk_descriptor_table
                               ((int *)g_current_bwd2_parse_cursor,&g_bwd2_descriptor_table,2,
                                (byte *)0x0,local_310,1,g_current_bwd2_parse_end);
        if (g_current_bwd2_parse_cursor != (uint *)0x0) {
          g_current_bwd2_parse_cursor =
               (uint *)parse_tagged_chunk_descriptor_table
                                 ((int *)g_current_bwd2_parse_cursor,
                                  &g_wdef_mission_descriptor_table,7,(byte *)0x0,local_310,1,
                                  g_current_bwd2_parse_end);
        }
        release_resource_file_reference((char *)local_310);
      }
      bVar11 = g_current_bwd2_parse_cursor != (uint *)0x0;
    }
  }
  if (!bVar11) {
    report_error();
  }
  return 1;
}


