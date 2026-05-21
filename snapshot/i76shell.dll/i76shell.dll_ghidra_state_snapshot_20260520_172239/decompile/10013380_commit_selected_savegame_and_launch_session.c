/*
 * Program: i76shell.dll
 * Function: commit_selected_savegame_and_launch_session
 * Entry: 10013380
 * Signature: undefined __stdcall commit_selected_savegame_and_launch_session(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void commit_selected_savegame_and_launch_session(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  CHAR local_40 [64];
  
  DAT_100d217c = 0xffffffff;
  *(undefined4 *)(DAT_100c5ad8 + 0x38) = 0;
  DAT_100c5b18 = 0;
  delete_user_repair_profile_file();
  destroy_repair_profile_pointer_list();
  reset_shell_session_resource_globals();
  wsprintfA(local_40,s__s_cmp_10046ef4,&DAT_10057a0c);
  read_spc_or_cmp_mission_vehicle_config(local_40);
  DAT_100c5af8 = DAT_100579e8;
  *DAT_100d2180 = DAT_100579e8;
  *DAT_100d2164 = DAT_10057a1c;
  *(undefined4 *)(DAT_100c5ad8 + 0x20) = 2;
  DAT_100d2174 = 1;
  write_player_definition_file(&DAT_100c5ae0);
  if ((*DAT_100d2180 == 0x10) && (DAT_10057a1c == 1)) {
    write_player_definition_file(&DAT_100c5ae0);
    PostMessageA(DAT_100f702c,0xc00d,0xc01e,0);
    return;
  }
  if ((DAT_10057a20 & 2) == 0) {
    if (*DAT_100d2180 == 0xc) {
      _DAT_100cc858 = _DAT_100cc858 & 0xfffffffd;
      write_player_definition_file(&DAT_100c5ae0);
      PostMessageA(DAT_100f702c,0xc015,0xc01e,0);
      return;
    }
    _DAT_100cc858 = _DAT_100cc858 & 0xfffffffd;
    write_player_definition_file(&DAT_100c5ae0);
    PostMessageA(DAT_100f702c,0xc017,0xc01d,0);
    return;
  }
  DAT_10047710 = (*(code *)*DAT_10058198)(&DAT_100c6288);
  build_vehicle_part_category_lists();
  export_current_vehicle_config_with_parts(s_addon_vehscn_vcf_10046efc,0);
  export_vehicle_scene_with_selected_parts(s_addon_vehscn_vsf_10046f10,0,0,0,0);
  uVar2 = 0xffffffff;
  pcVar4 = &DAT_10046f24;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  pcVar5 = (char *)(DAT_100c5ad8 + 0x29);
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  destroy_vehicle_part_category_lists();
  _DAT_100cc858 = _DAT_100cc858 | 2;
  write_player_definition_file(&DAT_100c5ae0);
  PostMessageA(DAT_100f702c,0xc015,0xc01e,0);
  return;
}


