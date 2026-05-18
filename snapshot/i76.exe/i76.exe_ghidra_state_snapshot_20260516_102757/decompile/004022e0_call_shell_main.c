/*
 * Program: i76.exe
 * Function: call_shell_main
 * Entry: 004022e0
 * Signature: uint __cdecl call_shell_main(undefined4 param_1, undefined4 param_2, undefined4 param_3, uint * param_4)
 */


/* [cgpt i76.exe mission/resource rename v13; confidence=high] Loads i76shell.dll exports, builds
   ShellMain callback table, calls ShellMain, consumes shell launch results, then refreshes
   PIX/resource caches on non-cancel return. */

uint __cdecl call_shell_main(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint *param_4)

{
  char cVar1;
  undefined4 uVar2;
  FARPROC pFVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint *puVar8;
  char *pcVar9;
  uint *puVar10;
  char *pcVar11;
  code *local_6c;
  code *local_68;
  code *local_64;
  code *local_60;
  code *local_5c;
  code *local_58;
  code *local_54;
  code *local_50;
  code *local_4c;
  code *local_48;
  code *local_44;
  code *local_40;
  code *local_3c;
  code *local_38;
  code *local_34;
  code *local_30;
  code *local_2c;
  code *local_28;
  code *local_24;
  code *local_20;
  code *local_1c;
  code *local_18;
  code *local_14;
  code *local_10;
  code *local_c;
  code *local_8;
  code *local_4;
  
  release_pending_audio_objects_and_buffers();
  set_audio_runtime_global_flag(1);
  set_shell_return_launch_requested(0);
  local_6c = populate_shell_vehicle_part_records;
  local_68 = load_default_shell_vehicle_definitions;
  local_64 = register_resource_key_for_zix_path;
  local_60 = build_vehicle_descriptor_from_loaded_definition;
  local_5c = build_vehicle_descriptor_from_component_and_vcf_path;
  local_58 = load_shell_vehicle_definition;
  local_54 = copy_wdf_component_definition_to_shell_descriptor;
  local_50 = build_vehicle_descriptor_from_vcf_path;
  local_4c = read_vehicle_config_weapon_chunks;
  local_48 = read_vehicle_scene_state_chunks;
  local_44 = pump_audio_object_system;
  local_34 = shell_cb_38_cd_audio_or_redbook_helper;
  local_30 = shell_cb_3c_cd_audio_or_redbook_helper;
  local_2c = shell_cb_40_cd_audio_or_redbook_helper;
  local_40 = shell_cb_2c_audio_helper;
  local_3c = shell_cb_30_audio_helper;
  local_38 = shell_cb_34_audio_helper;
  local_28 = prompt_for_cd2_if_needed;
  local_24 = fill_recommended_performance_options;
  local_20 = shell_cb_4c_display_or_directdraw_helper;
  local_1c = start_cd_audio_track_if_available;
  local_18 = stop_cd_audio_track_if_playing;
  local_14 = load_bwd2_wdef_resource_text;
  local_10 = select_recommended_performance_option_value;
  local_c = measure_text_break_prefix_until_width;
  local_8 = set_expected_file_crc_validation_records;
  local_4 = compute_bwd2_file_crc32_and_validate_prefix;
  pFVar3 = GetProcAddress(DAT_005dd2f8,s_ShellMain_004c228c);
  if (pFVar3 == (FARPROC)0x0) {
    return 1;
  }
  DAT_00504bec = GetProcAddress(DAT_005dd2f8,s_ShellWindowProc_004c227c);
  uVar2 = g_game_flow_state;
  if (DAT_00504bec == (FARPROC)0x0) {
    return 1;
  }
  g_game_flow_state = 6;
  DAT_005dd360 = 0;
  iVar4 = (*DAT_005dd2cc)(&DAT_005dcec0,0);
  if (iVar4 == 0) {
    report_chunk_parse_error();
  }
  release_and_show_mouse_cursor();
  uVar5 = (*pFVar3)(DAT_005dd2f8,0,param_2,param_3,param_1,-(uint)(DAT_004f9f20 != 0) & 0x643920,
                    &DAT_004c2160,&DAT_005dcea4,&local_6c,param_4,uVar2,&DAT_005dce80,&DAT_004f9e08)
  ;
  uVar2 = param_1;
  if ((uVar5 & 0xff) == 0xff) goto LAB_004025a8;
  if (g_shell_return_state == 5) {
    set_damage_side_effects_suppressed(1);
    multiplayer_game_state_context_helper_00452db0(param_4);
    sprintf((char *)&g_selected_mission_resource_path,s__s_s_004c2250,(int)param_4 + 0x4e,&s_dot_vcf
           );
    strncpy(&g_shell_session_text_block,(char *)(param_4 + 0x1c),0x1e);
    g_shell_selected_map_or_session_scalar = param_4[0x1b];
    puVar8 = param_4 + 0x26;
    puVar10 = &g_shell_session_descriptor_block;
    for (iVar4 = 0x66; uVar2 = param_1, iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar10 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar10 = puVar10 + 1;
    }
    goto LAB_004025a8;
  }
  if (g_shell_return_state == 2) {
LAB_00402583:
    uVar6 = 0xffffffff;
    pcVar9 = &g_shell_return_path_buffer;
    do {
      pcVar11 = pcVar9;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar11 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar11;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar9 = pcVar11 + -uVar6;
    pcVar11 = (char *)&g_selected_mission_resource_path;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar11 = pcVar11 + 4;
    }
  }
  else {
    if (g_shell_return_state != 4) {
      uVar2 = param_1;
      if (g_shell_return_state != 3) goto LAB_004025a8;
      set_shell_return_launch_requested(1);
      goto LAB_00402583;
    }
    uVar6 = 0xffffffff;
    pcVar9 = &g_shell_return_path_buffer;
    do {
      pcVar11 = pcVar9;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar11 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar11;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar9 = pcVar11 + -uVar6;
    pcVar11 = (char *)&g_selected_mission_resource_path;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar11 = pcVar11 + 4;
    }
  }
  for (uVar6 = uVar6 & 3; uVar2 = param_1, uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar11 = pcVar11 + 1;
  }
LAB_004025a8:
  DAT_005dd360 = uVar2;
  iVar4 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005dd360);
  uVar6 = extraout_ECX;
  if (iVar4 == 0) {
    report_chunk_parse_error();
    uVar6 = extraout_ECX_00;
  }
  stop_and_demote_all_active_audio_objects(uVar6);
  release_pending_audio_objects_and_buffers();
  set_audio_runtime_global_flag(0);
  if ((uVar5 & 0xff) != 0xff) {
    free_pix_pak_resource_index();
    destroy_loaded_resource_cache_heap();
    initialize_loaded_resource_cache_heap();
    load_pix_pak_resource_index();
  }
  return uVar5;
}


