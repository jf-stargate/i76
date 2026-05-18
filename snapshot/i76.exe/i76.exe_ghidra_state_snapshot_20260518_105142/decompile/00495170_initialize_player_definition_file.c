/*
 * Program: i76.exe
 * Function: initialize_player_definition_file
 * Entry: 00495170
 * Signature: undefined __stdcall initialize_player_definition_file(void)
 */


/* cgpt whole-binary semantic rename v1: references I76PLYR.DEF and graphics init strings */

void initialize_player_definition_file(void)

{
  int *piVar1;
  int iVar2;
  FILE *_File;
  
  piVar1 = (int *)get_active_player_or_camera_world_object_entry();
  destroy_mission_loading_screen();
  if (g_display_mode_variant_index != (char)DAT_005a60c0) {
    g_display_mode_variant_index = (char)DAT_005a60c0;
    DAT_005dd360 = DAT_005a60c0 & 0xff;
    iVar2 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005dd360);
    if (iVar2 == 0) {
      report_chunk_parse_error();
    }
    input_action_registration_context_helper_0044bb30();
    preload_cockpit_gauge_textures(*piVar1);
    initialize_runtime_camera_projection_matrix(0);
    initialize_or_refresh_player_weapon_hud_overlay((int *)0x0);
    load_specials_backing_texture(*piVar1);
  }
  _File = fopen(s_I76PLYR_DEF_004fd7dc,s_wb_004edf28);
  if (_File != (FILE *)0x0) {
    fwrite(&g_player_display_options_block,1,0x60,_File);
    fclose(_File);
  }
  if (((byte)DAT_00654b98 & 0x1c) != 0) {
    DAT_00535f78 = 1;
  }
  if ((byte)DAT_00654b90 < 2) {
    stop_cd_audio_track_if_playing();
  }
  if (DAT_00654b90._2_1_ < 2) {
    release_audio_world_object_attachment_records(0);
  }
  trim_audio_object_list_to_priority_limit((uint)DAT_00654b90._3_1_);
  set_audio_runtime_category_enable_mask(0xffffffff,0xffffffff,0xffffffff);
  DAT_005a60c0 = DAT_005a60c0 & 0xffffff00;
  DAT_005a60bc = 0;
  iVar2 = get_game_flow_state();
  if (iVar2 == 5) {
    start_pending_audio_objects();
    start_cd_audio_track_if_available(-1,0);
  }
  mission_flow_map_context_helper_0049cdd0(1);
  return;
}


