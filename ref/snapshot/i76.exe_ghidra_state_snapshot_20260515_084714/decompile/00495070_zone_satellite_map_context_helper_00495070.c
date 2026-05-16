/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00495070
 * Entry: 00495070
 * Signature: undefined4 __stdcall zone_satellite_map_context_helper_00495070(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00495070. Remove
   duplicated zone_satellite_map wording. */

undefined4 zone_satellite_map_context_helper_00495070(void)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  bVar1 = get_global_heap_handle();
  if (CONCAT31(extraout_var,bVar1) == 1) {
    if (DAT_00504be8 == 0) {
      release_all_video_memory_texture_cache_records();
    }
    else {
      (*DAT_00608bc0)(10,1);
    }
  }
  if (DAT_005a60b8 == 0) {
    DAT_005a60b8 = 1;
    show_in_game_pause_menu();
  }
  DAT_005a60c0._0_1_ = g_display_mode_variant_index;
  DAT_005a60bc = g_display_mode_variant_index;
  _DAT_004fc0b8 = &DAT_004fbf70;
  _DAT_004fc0bc = 5;
  _DAT_004fcec0 = &PTR_DAT_004fc440;
  if (((DAT_00504c10 == 0) && (((byte)DAT_00654b98 & 2) == 0)) && (DAT_005dd2f4 == 0)) {
    _DAT_004fc458 = &DAT_004fc220;
    _DAT_004fc45c = 5;
  }
  else {
    _DAT_004fc458 = &DAT_004fc350;
    _DAT_004fc45c = 4;
  }
  iVar2 = initialize_mission_loading_screen(&DAT_004fc0a0,initialize_player_definition_file);
  if (iVar2 != 0) {
    puVar3 = &DAT_00654b40;
    puVar4 = &DAT_00654ba0;
    for (iVar2 = 0x18; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    start_cd_audio_track_if_available(-1,1);
    update_audio_object_lists_and_release_finished();
    mission_flow_map_context_helper_0049cdd0(0x10);
    return 1;
  }
  return 0;
}


