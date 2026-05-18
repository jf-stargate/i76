/*
 * Program: i76.exe
 * Function: winmain_top_level_game_fsm
 * Entry: 00402b30
 * Signature: WPARAM __stdcall winmain_top_level_game_fsm(HINSTANCE param_1, int param_2, char * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Top-level WinMain-hosted game-flow
   FSM. Contains shell launch/re-entry, mission setup, active gameplay loop, teardown, and
   post-mission state transitions. */

WPARAM winmain_top_level_game_fsm(HINSTANCE param_1,int param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
  undefined1 uVar3;
  byte bVar4;
  undefined2 uVar5;
  short sVar6;
  short sVar7;
  undefined4 uVar8;
  HWND hWnd;
  undefined3 extraout_var;
  int iVar9;
  undefined4 *puVar10;
  size_t *psVar11;
  undefined3 extraout_var_00;
  BOOL BVar12;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  int *piVar13;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  LPCSTR lpText;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined2 extraout_var_14;
  undefined2 extraout_var_15;
  HANDLE pvVar14;
  undefined3 extraout_var_11;
  undefined3 extraout_var_12;
  undefined3 extraout_var_13;
  uint uVar15;
  uint uVar16;
  uint extraout_ECX;
  undefined4 *puVar17;
  tagMSG *ptVar18;
  uint *puVar19;
  int *piVar20;
  char *pcVar21;
  float10 fVar22;
  time_t tVar23;
  undefined4 uVar24;
  void *pvVar25;
  char *pcVar26;
  int iVar27;
  size_t sVar28;
  DWORD DVar29;
  float fStack_9d8;
  uint local_9d4;
  int local_9d0;
  undefined4 uStack_9cc;
  undefined4 uStack_9c8;
  tagMSG tStack_9c4;
  float fStack_9a8;
  float fStack_9a4;
  float fStack_9a0;
  float fStack_99c;
  float fStack_998;
  float fStack_994;
  uint uStack_990;
  uint uStack_98c;
  float fStack_988;
  float fStack_984;
  float fStack_980;
  float fStack_97c;
  float fStack_978;
  float fStack_974;
  WNDCLASSA local_970;
  tagMSG tStack_948;
  tagMSG tStack_92c;
  tagMSG tStack_910;
  tagMSG tStack_8f4;
  tagMSG tStack_8d8;
  char acStack_8bc [16];
  tagMSG local_8ac;
  char acStack_878 [20];
  uchar auStack_864 [80];
  int aiStack_814 [13];
  uchar auStack_7e0 [80];
  uint auStack_790 [3];
  undefined4 uStack_784;
  char acStack_782 [32];
  char acStack_762 [47];
  char acStack_733 [467];
  int aiStack_560 [13];
  char local_52c [256];
  int local_42c [267];
  
                    /* I76 semantic baseline: winmain_top_level_game_fsm
                       Top-level game-flow FSM: shell transition, mission setup, active gameplay
                       loop, teardown. */
  local_9d4 = 0;
  local_9d0 = 0;
  uVar8 = StrLookupCreate(s_lang_txt_004c269c);
  *(undefined4 *)StrLookup_Global_Object_exref = uVar8;
  PTR_s_Grey_Hounds_004c2130 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Grey_Hounds_004c2214);
  PTR_s_Puce_Panthers_004c2134 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Puce_Panthers_004c2204);
  PTR_s_Crimson_Kings_004c2138 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Crimson_Kings_004c21f4);
  PTR_s_Yellow_Jackets_004c213c =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Yellow_Jackets_004c21e4);
  PTR_s_Aqua_Marines_004c2140 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Aqua_Marines_004c21d4);
  PTR_s_Mauve_Mayhem_004c2144 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Mauve_Mayhem_004c21c4);
  PTR_s_Mr__Brown_s_Clowns_004c2148 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Mr__Brown_s_Clowns_004c21b0);
  PTR_s_Men_In_Black_004c214c =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Men_In_Black_004c21a0);
  PTR_s_Red_Dawn_004c2150 =
       (undefined *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Red_Dawn_004c2194);
  PTR_s_Gang_Green_004c2154 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Gang_Green_004c2188);
  PTR_s_Purple_Reign_004c2158 =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Purple_Reign_004c2178);
  PTR_s_Black_Plague_004c215c =
       (undefined *)
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Black_Plague_004c2168);
  DAT_005dd330 = 0;
  hWnd = FindWindowA(s_Interstate__76_Gold_Edition_004c2680,(LPCSTR)0x0);
  if ((hWnd != (HWND)0x0) && (ShowWindow(hWnd,9), hWnd != (HWND)0x0)) {
    return 0;
  }
  bVar2 = init_registry_install_settings();
  if (CONCAT31(extraout_var,bVar2) != 0) {
    initialize_cd_audio_playback_state();
    enumerate_logical_drives();
    prompt_for_cd2_if_needed(1);
  }
  system_cutscene_memory_context_helper_00499b00(&local_8ac.hwnd);
  system_cutscene_memory_context_helper_00499c30();
  system_cutscene_memory_context_helper_00499c80();
  strncpy(local_52c,param_3,0xff);
  DAT_005049f0 = DAT_00504c28;
  g_selected_mission_resource_path = DAT_004c2674;
  _DAT_005dd374 = DAT_004c2678;
  DAT_005dd378 = DAT_004c267c;
  iVar9 = parse_command_line_options(param_3,&DAT_005049f0);
  if (iVar9 == 0) {
    report_chunk_parse_error();
  }
  if (DAT_005049f0 == '\0') {
    if (DAT_00504c10 != 0) {
      DAT_00504c10 = 0;
    }
  }
  else {
    local_9d0 = 1;
  }
  tVar23 = time((time_t *)0x0);
  srand((uint)tVar23);
  zone_satellite_map_context_helper_00493c50();
  matrix_transform_composition_context_helper_00479860();
  DAT_005dd2f8 = LoadLibraryA(s_I76SHELL_DLL_004c2630);
  if (DAT_005dd2f8 == (HMODULE)0x0) {
    return 1;
  }
  if (g_cmdline_hardware_raster_requested != 0) {
    parse_driver_selection_arg(s_RASTER_004c2628,&g_selected_raster_plugin_dll_name,1);
    load_raster_plugin_and_resolve_exports(&g_selected_raster_plugin_dll_name);
  }
  if (param_2 == 0) {
    local_970.style = 3;
    local_970.lpfnWndProc = (WNDPROC)&LAB_00404830;
    local_970.cbClsExtra = 0;
    local_970.cbWndExtra = 4;
    local_970.hInstance = param_1;
    local_970.hIcon = (HICON)0x0;
    local_970.hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
    local_970.hbrBackground = GetStockObject(4);
    local_970.lpszMenuName = (LPCSTR)0x0;
    local_970.lpszClassName = s_Interstate__76_Gold_Edition_004c2680;
    RegisterClassA(&local_970);
  }
  else {
    report_chunk_parse_error();
  }
  report_not_enough_graphic_buffer_memory();
  puVar10 = (undefined4 *)
            select_display_backend(local_42c,param_1,s_Interstate__76_Gold_Edition_004c2680);
  puVar17 = &DAT_005dcec0;
  for (iVar9 = 0x10b; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar17 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar17 = puVar17 + 1;
  }
  if (DAT_005dcfa4 != 0) {
    report_chunk_parse_error();
  }
  keyboard_joystick_input_binding_context_helper_0044ece0(1);
  load_or_create_player_definition();
  DAT_005dd360 = 0;
  iVar9 = (*DAT_005dd2cc)(&DAT_005dcec0,0);
  if (iVar9 == 0) {
    report_chunk_parse_error();
  }
  psVar11 = geometry_math_context_helper_00479c90(s_addon_loadgame_pcx_004c25f4);
  if (psVar11 != (size_t *)0x0) {
    iVar9 = projection_or_clip_context_helper_0047a100(s_addon_loadgame_pcx_004c25f4,&DAT_005dcfa8);
    if (iVar9 != 0) {
      puVar10 = (undefined4 *)
                construct_bitmap_surface_context
                          (aiStack_814,*psVar11,(int)(psVar11[1] << 3) >> 3,(int)(psVar11 + 2),0);
      ptVar18 = &local_8ac;
      for (iVar9 = 0xd; iVar9 != 0; iVar9 = iVar9 + -1) {
        ptVar18->hwnd = (HWND)*puVar10;
        puVar10 = puVar10 + 1;
        ptVar18 = (tagMSG *)&ptVar18->message;
      }
      (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_005dcfa8);
      mission_objective_notepad_context_helper_0045e190((int *)&local_8ac);
    }
    if (psVar11 != (size_t *)0x0) {
      xfree_global_heap(psVar11);
    }
  }
  initialize_force_feedback_runtime();
  g_runtime_terrain_vertex_xyz_buffer = virtual_alloc_reserved_commit_region(0x1a5e0,0x40000);
  if (g_runtime_terrain_vertex_xyz_buffer == (LPVOID)0x0) {
    report_chunk_parse_error();
  }
  g_runtime_terrain_vertex_projected_or_scaled_buffer =
       (int)g_runtime_terrain_vertex_xyz_buffer + 54000;
  DAT_005dd324 = virtual_alloc_reserved_commit_region(0x80000,0x80000);
  if (DAT_005dd324 == (LPVOID)0x0) {
    report_chunk_parse_error();
  }
  enumerate_cdrom_drives();
  detect_language_and_keyboard();
  install_or_register_game_font(0x5dcec0);
  initialize_audio_runtime_directsound_cd((int)DAT_005dcf7c);
  system_cutscene_memory_context_helper_0049a040();
  capture_and_hide_mouse_cursor();
  iVar9 = open_smacker_cutscene(DAT_005dcf7c,s_introf01_smk_004c25b0);
  if (iVar9 != 0) {
    bVar2 = is_active_smacker_cutscene();
    iVar9 = CONCAT31(extraout_var_00,bVar2);
    while (iVar9 != 0) {
      if (DAT_00504c1c != 0) {
        update_runtime_display_mode_and_input_fsm();
        if (g_runtime_display_input_mode == 0x20) {
          advance_smacker_cutscene_frame();
        }
        else {
          pump_audio_object_system(1);
        }
      }
      if ((g_received_wm_quit == 0) &&
         (BVar12 = PeekMessageA(&tStack_9c4,(HWND)0x0,0,0,1), BVar12 != 0)) {
        if ((tStack_9c4.hwnd == (HWND)0x0) || (tStack_9c4.message != 0x12)) {
          TranslateMessage(&tStack_9c4);
          DispatchMessageA(&tStack_9c4);
        }
        else {
          g_received_wm_quit = 1;
          g_process_exit_code_from_wm_quit = tStack_9c4.wParam;
        }
      }
      bVar2 = is_active_smacker_cutscene();
      iVar9 = CONCAT31(extraout_var_01,bVar2);
    }
  }
  iVar9 = open_smacker_cutscene(DAT_005dcf7c,s_credf01_smk_004c25a4);
  if (iVar9 != 0) {
    bVar2 = is_active_smacker_cutscene();
    iVar9 = CONCAT31(extraout_var_02,bVar2);
    while (iVar9 != 0) {
      if (DAT_00504c1c != 0) {
        update_runtime_display_mode_and_input_fsm();
        if (g_runtime_display_input_mode == 0x20) {
          advance_smacker_cutscene_frame();
        }
        else {
          pump_audio_object_system(1);
        }
      }
      if ((g_received_wm_quit == 0) &&
         (BVar12 = PeekMessageA(&tStack_9c4,(HWND)0x0,0,0,1), BVar12 != 0)) {
        if ((tStack_9c4.hwnd == (HWND)0x0) || (tStack_9c4.message != 0x12)) {
          TranslateMessage(&tStack_9c4);
          DispatchMessageA(&tStack_9c4);
        }
        else {
          g_received_wm_quit = 1;
          g_process_exit_code_from_wm_quit = tStack_9c4.wParam;
        }
      }
      bVar2 = is_active_smacker_cutscene();
      iVar9 = CONCAT31(extraout_var_03,bVar2);
    }
  }
  g_game_flow_state = 5;
  puVar19 = auStack_790;
  for (iVar9 = 0x8c; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar19 = 0;
    puVar19 = puVar19 + 1;
  }
  if (DAT_00504c10 != 0) goto LAB_00403201;
  if (DAT_00504c14 != 0) {
    auStack_790[0] = auStack_790[0] | 0x10;
  }
  if (DAT_00504c18 != 0) {
    auStack_790[0] = auStack_790[0] | 0x20;
  }
  parse_world_object_placement_record(s_engsnd_dat_004c2598);
LAB_004031f5:
  local_9d4 = call_shell_main(DAT_005dcf7c,local_52c,1,auStack_790);
LAB_00403201:
  reset_runtime_display_input_mode_state();
  load_or_create_player_definition();
LAB_0040320b:
  do {
    if ((char)local_9d4 == -1) {
      system_cutscene_memory_context_helper_00498a00(DAT_005dd324);
      system_cutscene_memory_context_helper_00498a00(g_runtime_terrain_vertex_xyz_buffer);
      dib_surface_context_getter_helper_004766d0(DAT_00504c0c);
      cleanup_registered_game_font(0x5dcec0);
      close_smacker_cutscene_and_restore_display();
      shutdown_audio_runtime_directsound_cd();
      reset_pix_pak_and_resource_cache();
      windowed_high_color_error_context_helper_00476190(0x5dcec0);
      localized_texture_resource_context_helper_00474c40();
      FreeLibrary(DAT_005dd2f8);
      force_feedback_runtime_helper_00445b10();
      system_cutscene_memory_context_helper_00499c50();
      keyboard_joystick_input_binding_context_helper_0044ece0(0);
      StrLookupDestroy(*(undefined4 *)StrLookup_Global_Object_exref);
      return g_process_exit_code_from_wm_quit;
    }
    if (DAT_00504c08 != 0) {
      open_interval_log();
    }
    _DAT_00504c20 = 0;
    _DAT_00504c24 = 0;
    set_audio_runtime_global_flag(0);
    set_audio_runtime_pause_when_zero_flag(1);
    system_cutscene_memory_context_helper_00499c90();
    initialize_runtime_clock_state();
    init_input_bindings();
    special_equipment_state_context_helper_00468040();
    allocate_entity_instance_id_handler();
    if (DAT_00504c0c != (undefined4 *)0x0) {
      dib_surface_context_getter_helper_004766d0(DAT_00504c0c);
    }
    if (g_display_mode_variant_index == '\x06') {
      pcVar26 = s_base6x74_fnt_004c2588;
      iVar9 = 1;
    }
    else if (g_display_mode_variant_index == '\a') {
      pcVar26 = s_base6x7_fnt_004c257c;
      iVar9 = 0;
    }
    else {
      pcVar26 = s_base6x76_fnt_004c256c;
      iVar9 = 2;
    }
    system_cutscene_memory_context_helper_004998f0(iVar9,pcVar26);
    DAT_00504c0c = dib_surface_palette_context_helper_004764c0();
    mission_flow_map_context_helper_0049c300();
    classifier_display_context_helper_00461800();
    keyboard_joystick_input_binding_context_helper_0044ed20();
    ui_bitmap_region_context_helper_0049b7e0();
    initialize_or_resize_runtime_text_overlay_buffers(0);
    iVar9 = is_damage_side_effects_suppressed();
    if (iVar9 != 0) {
      initialize_multiplayer_game_runtime_state(auStack_790[2],(short)uStack_784);
      local_9d0 = -0x40800000;
    }
    matrix_rotation_context_helper_00479780(&DAT_005dcec0,0xff);
    vec3_transform_context_helper_00479a10();
    psVar11 = geometry_math_context_helper_00479c90(s_addon_loadscr_pcx_004c2558);
    if (psVar11 != (size_t *)0x0) {
      iVar9 = projection_or_clip_context_helper_0047a100(s_addon_loadscr_pcx_004c2558,&DAT_005dcfa8)
      ;
      if (iVar9 != 0) {
        piVar13 = (int *)construct_bitmap_surface_context
                                   (aiStack_560,*psVar11,(int)(psVar11[1] << 3) >> 3,
                                    (int)(psVar11 + 2),0);
        piVar20 = aiStack_814;
        for (iVar9 = 0xd; iVar9 != 0; iVar9 = iVar9 + -1) {
          *piVar20 = *piVar13;
          piVar13 = piVar13 + 1;
          piVar20 = piVar20 + 1;
        }
        (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_005dcfa8);
        mission_objective_notepad_context_helper_0045e190(aiStack_814);
      }
      if (psVar11 != (size_t *)0x0) {
        xfree_global_heap(psVar11);
      }
    }
    vec3_transform_context_helper_00479a60(0x3c23d70a,0x20);
    initialize_dynamic_geometry_render_arenas();
    terrain_map_context_helper_004925e0();
    texture_resource_buffer_context_helper_00447f90();
    force_feedback_effect_dispatch_context_helper_004461a0();
    texture_resource_preload_helper_00447420();
    definition_record_parser_context_helper_00449610();
    texture_animation_table_context_helper_0044ae30();
    chunk_manager_update_context_helper_004a2d30();
    init_radar_mask_texture();
    load_target_reticle_textures();
    vehicle_specials_display_flag_helper_00467690();
    load_effect_xdf_resources();
    explosion_effect_context_helper_0049f1f0();
    initialize_fsm_vehicle_runtime_system();
    artillery_carrier_weapon_context_helper_00462990();
    initialize_effect_target_system();
    chunk_manager_log_tag();
    initialize_chunk_manager_objects();
    if (local_9d0 == 0) {
      uVar15 = 0xffffffff;
      pcVar26 = acStack_733;
      do {
        pcVar21 = pcVar26;
        if (uVar15 == 0) break;
        uVar15 = uVar15 - 1;
        pcVar21 = pcVar26 + 1;
        cVar1 = *pcVar26;
        pcVar26 = pcVar21;
      } while (cVar1 != '\0');
      uVar15 = ~uVar15;
      pcVar26 = pcVar21 + -uVar15;
      pcVar21 = &DAT_005049f0;
      for (uVar16 = uVar15 >> 2; uVar16 != 0; uVar16 = uVar16 - 1) {
        *(undefined4 *)pcVar21 = *(undefined4 *)pcVar26;
        pcVar26 = pcVar26 + 4;
        pcVar21 = pcVar21 + 4;
      }
      for (uVar15 = uVar15 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
        *pcVar21 = *pcVar26;
        pcVar26 = pcVar26 + 1;
        pcVar21 = pcVar21 + 1;
      }
      uVar15 = 0xffffffff;
      pcVar26 = (char *)((int)register0x00000010 + -0x782);
      do {
        pcVar21 = pcVar26;
        if (uVar15 == 0) break;
        uVar15 = uVar15 - 1;
        pcVar21 = pcVar26 + 1;
        cVar1 = *pcVar26;
        pcVar26 = pcVar21;
      } while (cVar1 != '\0');
      uVar15 = ~uVar15;
      pcVar26 = pcVar21 + -uVar15;
      pcVar21 = (char *)&DAT_00504bc8;
      for (uVar16 = uVar15 >> 2; uVar16 != 0; uVar16 = uVar16 - 1) {
        *(undefined4 *)pcVar21 = *(undefined4 *)pcVar26;
        pcVar26 = pcVar26 + 4;
        pcVar21 = pcVar21 + 4;
      }
      for (uVar15 = uVar15 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
        *pcVar21 = *pcVar26;
        pcVar26 = pcVar26 + 1;
        pcVar21 = pcVar21 + 1;
      }
      uVar15 = 0xffffffff;
      pcVar26 = acStack_762;
      do {
        pcVar21 = pcVar26;
        if (uVar15 == 0) break;
        uVar15 = uVar15 - 1;
        pcVar21 = pcVar26 + 1;
        cVar1 = *pcVar26;
        pcVar26 = pcVar21;
      } while (cVar1 != '\0');
      uVar15 = ~uVar15;
      pcVar26 = pcVar21 + -uVar15;
      pcVar21 = (char *)&DAT_005049d0;
      for (uVar16 = uVar15 >> 2; uVar16 != 0; uVar16 = uVar16 - 1) {
        *(undefined4 *)pcVar21 = *(undefined4 *)pcVar26;
        pcVar26 = pcVar26 + 4;
        pcVar21 = pcVar21 + 4;
      }
      for (uVar15 = uVar15 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
        *pcVar21 = *pcVar26;
        pcVar26 = pcVar26 + 1;
        pcVar21 = pcVar21 + 1;
      }
    }
    iVar9 = is_network_or_trip_runtime_mode();
    if (iVar9 != 0) {
      initialize_multiplayer_runtime_player_state();
    }
    iVar9 = _strnicmp(&DAT_005049f0,s_t01_004c2554,3);
    if ((iVar9 == 0) || (iVar9 = _strnicmp(&DAT_005049f0,s_t13_004c2550,3), iVar9 == 0)) {
LAB_004034cf:
      DAT_005dd2f4 = 1;
    }
    else {
      iVar9 = _strnicmp(&DAT_005049f0,s_t17_004c254c,3);
      DAT_005dd2f4 = 0;
      if (iVar9 == 0) goto LAB_004034cf;
    }
    select_runtime_display_mode_from_token((char *)0x0);
    parse_world_object_placement_record(s_engsnd_dat_004c2598);
    load_and_parse_selected_mission_resource(&DAT_005049f0);
    load_mission_objective_text_file();
    initialize_palette_shading_tables();
    dispatch_queued_world_object_class_callbacks();
    register_world_object_tree_callback(&LAB_004093e0);
    iVar9 = is_damage_side_effects_suppressed();
    if (iVar9 != 0) {
      publish_local_player_vehicle_config_to_directplay();
      do {
        update_runtime_clock_from_gettickcount();
        iVar9 = wait_for_multiplayer_mission_start_sync();
      } while (iVar9 == 0);
      fVar22 = get_network_or_session_runtime_seconds();
      _DAT_00504a28 = (float)fVar22;
    }
    force_feedback_user_entity_lookup_context_helper_00444e30(0x10);
    preload_contrail_textures(8);
    preload_flamer_textures(0x10);
    load_projectile_tracer_texture(100);
    mission_flow_map_context_helper_0049c5e0();
    preload_smoke_animation_textures();
    play_post_mission_audio_sequence_a();
    iVar9 = is_damage_side_effects_suppressed();
    if (iVar9 != 0) {
      mission_flow_map_context_helper_0049c480(2);
    }
    initialize_horizon_ring_vertex_table();
    init_sky_textures();
    load_road_textures(&DAT_005049f0);
    uVar3 = convert_rgb_floats_to_nearest_palette_index();
    DAT_005dd32c = CONCAT31(extraout_var_04,uVar3);
    _DAT_005dd328 = 0xff;
    do {
      uVar3 = convert_rgb_floats_to_nearest_palette_index();
      _DAT_005dd328 = CONCAT31(extraout_var_05,uVar3);
    } while (_DAT_005dd328 == 0xff);
    matrix_vector_projection_context_helper_00478b80(&DAT_005dcec0,0xe0,0xef,0xef);
    matrix_transform_bounds_context_helper_00478c20(0x5dcec0);
    terrain_map_context_helper_004909b0();
    iVar9 = is_network_or_trip_runtime_mode();
    if (iVar9 != 0) {
      uStack_9cc = 0;
      uStack_9c8 = 0;
      _splitpath((char *)&g_selected_mission_resource_path,(char *)0x0,(char *)0x0,acStack_878,
                 (char *)0x0);
      strncpy((char *)&uStack_9cc,acStack_878,8);
      iVar27 = 1;
      iVar9 = 0;
      uVar8 = uStack_9cc;
      uVar24 = uStack_9c8;
      uVar15 = get_spawn_location_or_report_missing();
      load_vehicle_entity(uVar15,iVar9,uVar8,uVar24,iVar27);
      load_opponent_vehicle_files();
    }
    input_device_binding_input_action_state_helper_0044df80();
    fsm_get_car_weapon_info_indexed();
    shutdown_fsm_vehicle_runtime_system();
    initialize_artillery_carrier_weapon_info();
    ui_bitmap_region_context_helper_0049aea0();
    capture_and_hide_mouse_cursor();
    entity_instance_table_context_helper_00457870();
    entity_instance_table_context_helper_004577f0();
    geometry_math_context_helper_00479c60(0x3c23d70a,0x20);
    bVar4 = convert_rgb_floats_to_nearest_palette_index();
    piVar13 = DAT_004c276c;
    if (DAT_004c276c != (int *)0x0) {
      (*DAT_005dd2bc)(&DAT_005dcec0);
      fill_bitmap_surface_context(piVar13,bVar4);
      (*DAT_005dd2c0)(&DAT_005dcec0);
      (*DAT_005dd2e0)(&DAT_005dcec0);
    }
    stop_cd_audio_track_if_playing();
    iVar9 = open_smacker_cutscene(DAT_005dcf7c,&DAT_005dd300);
    if (iVar9 != 0) {
      bVar2 = is_active_smacker_cutscene();
      iVar9 = CONCAT31(extraout_var_06,bVar2);
      while (iVar9 != 0) {
        if (DAT_00504c1c != 0) {
          update_runtime_display_mode_and_input_fsm();
          if (g_runtime_display_input_mode == 0x20) {
            advance_smacker_cutscene_frame();
          }
          else {
            pump_audio_object_system(1);
          }
        }
        if ((g_received_wm_quit == 0) &&
           (BVar12 = PeekMessageA(&tStack_8f4,(HWND)0x0,0,0,1), BVar12 != 0)) {
          if ((tStack_8f4.hwnd == (HWND)0x0) || (tStack_8f4.message != 0x12)) {
            TranslateMessage(&tStack_8f4);
            DispatchMessageA(&tStack_8f4);
          }
          else {
            g_received_wm_quit = 1;
            g_process_exit_code_from_wm_quit = tStack_8f4.wParam;
          }
        }
        bVar2 = is_active_smacker_cutscene();
        iVar9 = CONCAT31(extraout_var_07,bVar2);
      }
    }
    keyboard_joystick_input_binding_context_helper_0044eca0();
    start_cd_audio_track_if_available(-1,0);
    iVar9 = world_reader_record_table_context_helper_004b8960();
    if (iVar9 == 0) {
      lpText = (LPCSTR)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                     s_Sorry__there_is_not_enough_memor_004c24ac);
      release_and_show_mouse_cursor();
      update_or_clear_input_binding_state_after_poll();
      shutdown_audio_runtime_directsound_cd();
      if ((DAT_005dcfa0 != 0) &&
         (windowed_high_color_error_context_helper_00476190(0x5dcec0), DAT_005dcf7c != (HWND)0x0)) {
        DestroyWindow(DAT_005dcf7c);
      }
      MessageBoxA((HWND)0x0,lpText,s_Interstate__76_Gold_Edition_004c2680,0x10);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    iVar9 = is_damage_side_effects_suppressed();
    if (iVar9 == 0) {
      (*g_runtime_display_mode_change_callback)();
    }
    matrix_transform_composition_context_helper_00479970(0,0x100);
    bVar4 = convert_rgb_floats_to_nearest_palette_index();
    piVar13 = DAT_004c276c;
    if (DAT_004c276c != (int *)0x0) {
      (*DAT_005dd2bc)(&DAT_005dcec0);
      fill_bitmap_surface_context(piVar13,bVar4);
      (*DAT_005dd2c0)(&DAT_005dcec0);
      (*DAT_005dd2e0)(&DAT_005dcec0);
    }
    _DAT_00504c20 = 1;
    force_feedback_runtime_helper_00445b40();
    force_feedback_runtime_helper_00445b80();
    DAT_005dd360 = _g_display_mode_variant_index & 0xff;
    iVar9 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005dd360);
    if (iVar9 == 0) {
      report_chunk_parse_error();
    }
    bVar2 = is_miss16_high_color_resource_mode();
    if (CONCAT31(extraout_var_08,bVar2) != 0) {
      do {
        uVar3 = convert_rgb_floats_to_nearest_palette_index();
        _DAT_005dd328 = CONCAT31(extraout_var_09,uVar3);
      } while ((&DAT_00608460)[_DAT_005dd328] == 0);
    }
    initialize_runtime_camera_projection_matrix(1);
    if (g_cmdline_hardware_raster_requested == 0) {
      preload_asset_caches(&DAT_005049f0);
    }
    initialize_or_resize_runtime_text_overlay_buffers(1);
    while (g_game_flow_state == 5) {
      geometry_cache_reference_helper_004471e0();
      texture_cache_record_lookup_helper_00447d20();
      short_startup_spin_delay_stub();
      if (g_received_wm_quit != 0) {
        report_chunk_parse_error();
      }
      restore_or_acquire_directdraw_surface_if_needed();
      update_runtime_clock_from_gettickcount();
      update_runtime_input_state_and_pending_action();
      bVar2 = has_pending_smacker_cutscene_request();
      if (CONCAT31(extraout_var_10,bVar2) == 0) {
        if (((DAT_00504c1c == 0) || ((g_runtime_display_input_mode & 0x3e) != 0)) &&
           (iVar9 = is_damage_side_effects_suppressed(), iVar9 == 0)) {
          if (DAT_00504c1c != 0) {
            update_runtime_display_mode_and_input_fsm();
            if (g_runtime_display_input_mode == 0x20) {
              advance_smacker_cutscene_frame();
            }
            else {
              pump_audio_object_system(1);
            }
          }
          if ((g_received_wm_quit == 0) &&
             (BVar12 = PeekMessageA(&tStack_910,(HWND)0x0,0,0,1), BVar12 != 0)) {
            if ((tStack_910.hwnd == (HWND)0x0) || (tStack_910.message != 0x12)) {
              TranslateMessage(&tStack_910);
              DispatchMessageA(&tStack_910);
            }
            else {
              g_received_wm_quit = 1;
              g_process_exit_code_from_wm_quit = tStack_910.wParam;
            }
          }
        }
        else {
          restore_or_acquire_directdraw_surface_if_needed();
          begin_frame_timing_sample();
          uVar15 = g_runtime_display_input_mode;
          update_effect_target_collision_pairs();
          restore_or_acquire_directdraw_surface_if_needed();
          dispatch_pending_input_action_code();
          restore_or_acquire_directdraw_surface_if_needed();
          iVar9 = is_damage_side_effects_suppressed();
          if (iVar9 != 0) {
            process_directplay_runtime_messages();
            fVar22 = get_network_or_session_runtime_seconds();
            if ((float10)_DAT_004bc48c <= fVar22 - (float10)_DAT_00504a28) {
              update_multiplayer_scoreboard_overlay();
              fVar22 = get_network_or_session_runtime_seconds();
              _DAT_00504a28 = (float)fVar22;
            }
            sVar7 = multiplayer_chat_ui_context_helper_00453ab0();
            if ((sVar7 == 0) || (fStack_9d8 != _DAT_004bc47c)) {
              iVar9 = multiplayer_chat_ui_context_helper_00452e20();
              if ((iVar9 == 0) || (fStack_9d8 != _DAT_004bc47c)) {
                if ((fStack_9d8 != _DAT_004bc47c) &&
                   (fVar22 = get_network_or_session_runtime_seconds(),
                   (float10)_DAT_004bc490 <= fVar22 - (float10)fStack_9d8)) {
                  g_game_flow_state = 3;
                }
              }
              else {
                fVar22 = get_network_or_session_runtime_seconds();
                fStack_9d8 = (float)fVar22;
                multiplayer_chat_ui_context_helper_00453ef0(1);
                pcVar26 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                                s_____Host_has_disconnected_004c2388);
                sprintf((char *)auStack_7e0,pcVar26);
                clear_pending_input_action_code();
                iVar9 = get_active_player_or_camera_world_object_entry();
                if ((iVar9 == 0) &&
                   (uVar16 = get_spawn_location_or_report_missing(), uVar16 != 0xffffffff)) {
                  sVar28 = 0;
                  pvVar25 = (void *)0x0;
                  iVar9 = 0;
                  uVar5 = get_local_multiplayer_player_id();
                  pcVar26 = load_or_create_player_vehicle_entity
                                      (CONCAT22(extraout_var_15,uVar5),uVar16,iVar9,pvVar25,sVar28);
                  fStack_99c = (float)*(double *)(pcVar26 + 0x40);
                  fStack_998 = (float)*(double *)(pcVar26 + 0x48);
                  fStack_994 = (float)*(double *)(pcVar26 + 0x50);
                  fStack_97c = fStack_99c;
                  fStack_978 = fStack_998;
                  fStack_974 = fStack_994;
                  chunk_manager_lookup_or_remove_entry(&fStack_97c,20.0);
                }
                iVar9 = 0xfefe;
                uVar8 = get_active_player_or_camera_world_object_entry();
                dispatch_runtime_camera_mode_activation_by_id(uVar8,iVar9);
                weapon_hud_display_context_helper_004621b0();
                _DAT_0053679c = 8;
                draw_multiplayer_chat_message(0,auStack_7e0);
              }
            }
            else {
              fVar22 = get_network_or_session_runtime_seconds();
              fStack_9d8 = (float)fVar22;
              multiplayer_chat_ui_context_helper_00453ef0(1);
              iVar9 = get_active_player_or_camera_world_object_entry();
              if ((iVar9 == 0) &&
                 (uVar16 = get_spawn_location_or_report_missing(), uVar16 != 0xffffffff)) {
                sVar28 = 0;
                pvVar25 = (void *)0x0;
                iVar9 = 0;
                uVar5 = get_local_multiplayer_player_id();
                pcVar26 = load_or_create_player_vehicle_entity
                                    (CONCAT22(extraout_var_14,uVar5),uVar16,iVar9,pvVar25,sVar28);
                fStack_9a8 = (float)*(double *)(pcVar26 + 0x40);
                fStack_9a4 = (float)*(double *)(pcVar26 + 0x48);
                fStack_9a0 = (float)*(double *)(pcVar26 + 0x50);
                fStack_988 = fStack_9a8;
                fStack_984 = fStack_9a4;
                fStack_980 = fStack_9a0;
                chunk_manager_lookup_or_remove_entry(&fStack_988,20.0);
              }
              iVar9 = multiplayer_chat_ui_context_helper_00452e10();
              if (iVar9 == 0) {
                sVar6 = get_local_multiplayer_player_id();
                if (sVar7 == sVar6) {
                  pcVar26 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                                  s_____You_have_reached_the_maximum_004c244c);
                  sprintf((char *)auStack_864,pcVar26);
                  goto LAB_00403bc6;
                }
                multiplayer_player_count_context_helper_00454620(sVar7,(uchar *)&tStack_9c4);
                ptVar18 = &tStack_9c4;
                pcVar26 = s______s_has_reached_the_maximum_s_004c2414;
LAB_00403c0a:
                pcVar26 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,pcVar26
                                                ,ptVar18);
                sprintf((char *)auStack_864,pcVar26);
                piVar13 = (int *)get_active_player_or_camera_world_object_entry();
                trigger_vehicle_forced_damage_or_actor_cleanup(*piVar13);
              }
              else {
                puVar19 = &uStack_98c;
                sVar6 = get_local_multiplayer_player_id();
                lookup_multiplayer_player_vehicle_config_id(sVar6,puVar19);
                lookup_multiplayer_player_vehicle_config_id(sVar7,&uStack_990);
                uVar16 = uStack_990 >> 0x10 & 7;
                if (((uStack_990 ^ uStack_98c) & 0x70000) != 0) {
                  multiplayer_player_count_context_helper_00454620(sVar7,(uchar *)&tStack_9c4);
                  ptVar18 = (tagMSG *)(&PTR_s_Grey_Hounds_004c2130)[uVar16];
                  pcVar26 = s_____Team__s_has_reached_the_maxi_004c23a4;
                  goto LAB_00403c0a;
                }
                pcVar26 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                                s_____Team__s_has_reached_the_maxi_004c23e0,
                                                (&PTR_s_Grey_Hounds_004c2130)[uVar16]);
                sprintf((char *)auStack_864,pcVar26);
LAB_00403bc6:
                clear_pending_input_action_code();
                iVar9 = 0xfefe;
                uVar8 = get_active_player_or_camera_world_object_entry();
                dispatch_runtime_camera_mode_activation_by_id(uVar8,iVar9);
                weapon_hud_display_context_helper_004621b0();
                _DAT_0053679c = 8;
              }
              draw_multiplayer_chat_message(0,auStack_864);
            }
          }
                    /* I76 semantic baseline note:
                       Main active gameplay loop: world-object pre-update dispatch begins here
                       before explicit FSM/weapon/presentation stages. */
          dispatch_world_object_pre_update_callbacks();
          if (g_cmdline_hardware_raster_requested == 0) {
            iVar9 = is_network_or_trip_runtime_mode();
            if ((iVar9 != 0) || (iVar9 = is_damage_side_effects_suppressed(), iVar9 != 0)) {
              maybe_respawn_player_vehicle_at_valid_spawn();
            }
          }
          else {
            iVar9 = is_network_or_trip_runtime_mode();
            if (((iVar9 != 0) || (iVar9 = is_damage_side_effects_suppressed(), iVar9 != 0)) &&
               (iVar9 = maybe_respawn_player_vehicle_at_valid_spawn(), iVar9 != 0)) {
              (*DAT_00608bc0)(10,1);
            }
          }
                    /* I76 semantic baseline note:
                       Main active gameplay loop: world-object post-update dispatch follows shortly
                       after pre-update; this ends object update phase, not rendered frame. */
          dispatch_world_object_post_update_callbacks();
                    /* I76 semantic baseline note:
                       Main active gameplay loop: AI/FSM vehicle runtime frame update after object
                       callback passes. */
          update_fsm_vehicle_runtime_frame();
                    /* I76 semantic baseline note:
                       Main active gameplay loop: vehicle weapon fire-state update after AI/FSM. */
          update_vehicle_weapon_runtime_fire_state();
          update_mission_dynamic_runtime_object_lists();
          restore_or_acquire_directdraw_surface_if_needed();
          update_local_player_vehicle_weapons_and_hud();
          update_texture_animation_timer_list();
          iVar9 = is_damage_side_effects_suppressed();
          if ((iVar9 == 0) || (iVar9 = get_active_player_or_camera_world_object_entry(), iVar9 != 0)
             ) {
            (*g_runtime_display_mode_change_callback)();
            update_distance_culled_world_object_render_state();
            pump_audio_object_system(1);
            set_audio_runtime_global_flag(1);
            if ((g_runtime_display_input_mode & 0xc) == 0) {
              DVar29 = 0x100;
              pvVar14 = GetCurrentProcess();
              SetPriorityClass(pvVar14,DVar29);
              mark_frame_timing_interval(s_AI_004c2380);
              dispatch_ai_frame_update_if_gameplay_active((float *)&DAT_004c2730);
              DVar29 = 0x20;
              pvVar14 = GetCurrentProcess();
              SetPriorityClass(pvVar14,DVar29);
            }
            if (g_runtime_display_input_mode == 1) {
              (*DAT_005dd2bc)(&DAT_005dcec0);
              render_display_mode1_bitmap_overlay(0x4c2730);
              draw_scrolling_status_message_overlays();
              draw_static_text_overlay_entries();
              (*DAT_005dd2c0)(&DAT_005dcec0);
            }
          }
          if ((g_runtime_display_input_mode & 0x10) == 0) {
            if ((g_runtime_display_input_mode & 0xc) == 0) {
              (*DAT_005dd2e0)(&DAT_005dcec0);
            }
          }
          else {
            redraw_mission_loading_screen();
          }
          mark_frame_timing_interval(s_Blit_004c2378);
          special_equipment_state_context_helper_00468040();
          if ((uVar15 & 0x3e) == 0) {
            if ((g_received_wm_quit == 0) &&
               (BVar12 = PeekMessageA(&tStack_948,(HWND)0x0,0,0,1), BVar12 != 0)) {
              if ((tStack_948.hwnd == (HWND)0x0) || (tStack_948.message != 0x12)) {
                TranslateMessage(&tStack_948);
                ptVar18 = &tStack_948;
                goto LAB_00403fee;
              }
              g_received_wm_quit = 1;
              g_process_exit_code_from_wm_quit = tStack_948.wParam;
            }
          }
          else {
            if (DAT_00504c1c != 0) {
              update_runtime_display_mode_and_input_fsm();
              if (g_runtime_display_input_mode == 0x20) {
                advance_smacker_cutscene_frame();
              }
              else {
                pump_audio_object_system(1);
              }
            }
            if ((g_received_wm_quit == 0) &&
               (BVar12 = PeekMessageA(&tStack_92c,(HWND)0x0,0,0,1), BVar12 != 0)) {
              if ((tStack_92c.hwnd == (HWND)0x0) || (tStack_92c.message != 0x12)) {
                TranslateMessage(&tStack_92c);
                ptVar18 = &tStack_92c;
LAB_00403fee:
                DispatchMessageA(ptVar18);
              }
              else {
                g_received_wm_quit = 1;
                g_process_exit_code_from_wm_quit = tStack_92c.wParam;
              }
            }
          }
          finish_frame_timing_sample_and_log_stats();
          if ((DAT_00504bf0 != 0) &&
             (bVar2 = is_miss16_high_color_resource_mode(), CONCAT31(extraout_var_11,bVar2) != 0)) {
            DAT_00504bf0 = 0;
            write_directdraw_surface_to_bmp_file();
          }
        }
      }
      else {
        pcVar26 = (char *)consume_pending_smacker_cutscene_path();
        open_smacker_cutscene(DAT_005dcf7c,pcVar26);
      }
    }
    if ((FILE *)g_resource_debug_log_file != (FILE *)0x0) {
      if (g_resource_debug_log_file != DAT_005a7c90) {
        fclose((FILE *)g_resource_debug_log_file);
      }
      g_resource_debug_log_file = 0;
    }
    write_frame_timing_summary();
    write_frame_histogram_log();
    save_player_definition();
    stop_and_demote_all_active_audio_objects(extraout_ECX);
    release_all_audio_objects_and_buffers();
    release_pending_audio_objects_and_buffers();
    noop_world_object_callback_stub();
    initialize_classifier_display();
    iVar9 = is_network_or_trip_runtime_mode();
    if (iVar9 != 0) {
      write_multiplayer_score_results_file();
    }
    if ((g_game_flow_state == 1) && (DAT_00535f78 != 0)) {
      g_game_flow_state = 0xb;
    }
    iVar9 = g_game_flow_state;
    if (g_game_flow_state == 1) {
      iVar27 = _strnicmp(s_t04_004c2368,&DAT_005049f0,3);
      if (iVar27 != 0) {
        iVar27 = _strnicmp(s_t12_004c2364,&DAT_005049f0,3);
        DAT_005dd2f0 = (uint)(iVar27 == 0);
        gdf_resource_reference_context_helper_004b1a20(&DAT_005049f0);
        strncpy(acStack_8bc,s_vehscn_vsf_004c2358,0x10);
        write_trip_vehicle_scene_state_file(s_addon_004c2350,acStack_8bc);
        register_resource_key_for_zix_path(acStack_8bc,s_addon_004c2350);
      }
      geometry_math_context_helper_00479c60(0x3c23d70a,0x20);
      uVar8 = DAT_005dd32c;
      piVar13 = DAT_004c276c;
      if (DAT_004c276c != (int *)0x0) {
        (*DAT_005dd2bc)(&DAT_005dcec0);
        fill_bitmap_surface_context(piVar13,(byte)uVar8);
        (*DAT_005dd2c0)(&DAT_005dcec0);
        (*DAT_005dd2e0)(&DAT_005dcec0);
      }
      DAT_005dd360 = 0;
      iVar27 = (*DAT_005dd2cc)(&DAT_005dcec0,0);
      if (iVar27 == 0) {
        report_chunk_parse_error();
      }
      stop_cd_audio_track_if_playing();
      iVar27 = open_smacker_cutscene(DAT_005dcf7c,&DAT_005dd310);
      if (iVar27 != 0) {
        bVar2 = is_active_smacker_cutscene();
        iVar27 = CONCAT31(extraout_var_12,bVar2);
        while (iVar27 != 0) {
          if (DAT_00504c1c != 0) {
            update_runtime_display_mode_and_input_fsm();
            if (g_runtime_display_input_mode == 0x20) {
              advance_smacker_cutscene_frame();
            }
            else {
              pump_audio_object_system(1);
            }
          }
          if ((g_received_wm_quit == 0) &&
             (BVar12 = PeekMessageA(&tStack_8d8,(HWND)0x0,0,0,1), BVar12 != 0)) {
            if ((tStack_8d8.hwnd == (HWND)0x0) || (tStack_8d8.message != 0x12)) {
              TranslateMessage(&tStack_8d8);
              DispatchMessageA(&tStack_8d8);
            }
            else {
              g_received_wm_quit = 1;
              g_process_exit_code_from_wm_quit = tStack_8d8.wParam;
            }
          }
          bVar2 = is_active_smacker_cutscene();
          iVar27 = CONCAT31(extraout_var_13,bVar2);
        }
      }
    }
    else if ((g_game_flow_state == 0) || (g_game_flow_state == 0xb)) {
      iVar27 = run_post_mission_shell_transition_screen();
      if (iVar27 == 0) {
        g_game_flow_state = 2;
      }
      else {
        while (iVar9 = g_game_flow_state, g_game_flow_state = iVar9, iVar9 == 0) {
          update_runtime_input_state_and_pending_action();
          if (DAT_00504c1c != 0) {
            update_runtime_display_mode_and_input_fsm();
            if (g_runtime_display_input_mode == 0x20) {
              advance_smacker_cutscene_frame();
            }
            else {
              pump_audio_object_system(1);
            }
          }
          if ((g_received_wm_quit == 0) &&
             (BVar12 = PeekMessageA(&local_8ac,(HWND)0x0,0,0,1), BVar12 != 0)) {
            if ((local_8ac.hwnd == (HWND)0x0) || (local_8ac.message != 0x12)) {
              TranslateMessage(&local_8ac);
              DispatchMessageA(&local_8ac);
            }
            else {
              g_received_wm_quit = 1;
              g_process_exit_code_from_wm_quit = local_8ac.wParam;
            }
          }
        }
      }
      geometry_math_context_helper_00479c60(0x3c23d70a,0x20);
      uVar8 = DAT_005dd32c;
      piVar13 = DAT_004c276c;
      if (DAT_004c276c != (int *)0x0) {
        (*DAT_005dd2bc)(&DAT_005dcec0);
        fill_bitmap_surface_context(piVar13,(byte)uVar8);
        (*DAT_005dd2c0)(&DAT_005dcec0);
        (*DAT_005dd2e0)(&DAT_005dcec0);
      }
      DAT_005dd360 = 0;
      iVar27 = (*DAT_005dd2cc)(&DAT_005dcec0,0);
      if (iVar27 == 0) {
        report_chunk_parse_error();
      }
    }
    else {
      geometry_math_context_helper_00479c60(0x3c23d70a,0x20);
      uVar8 = DAT_005dd32c;
      piVar13 = DAT_004c276c;
      if (DAT_004c276c != (int *)0x0) {
        (*DAT_005dd2bc)(&DAT_005dcec0);
        fill_bitmap_surface_context(piVar13,(byte)uVar8);
        (*DAT_005dd2c0)(&DAT_005dcec0);
        (*DAT_005dd2e0)(&DAT_005dcec0);
      }
      DAT_005dd360 = 0;
      iVar27 = (*DAT_005dd2cc)(&DAT_005dcec0,0);
      if (iVar27 == 0) {
        report_chunk_parse_error();
      }
      iVar27 = is_damage_side_effects_suppressed();
      if ((iVar27 != 0) &&
         ((sVar7 = multiplayer_chat_ui_context_helper_00453ab0(), sVar7 == 0 || (DAT_005dd330 != 0))
         )) {
        DAT_005dd330 = 0;
        write_multiplayer_score_results_file();
      }
    }
    if (iVar9 == 7) {
      stop_cd_audio_track_if_playing();
      start_cd_audio_track_if_available(-1,0);
    }
    DAT_005dd360 = 0;
    iVar27 = (*DAT_005dd2cc)(&DAT_005dcec0,0);
    if (iVar27 == 0) {
      report_chunk_parse_error();
    }
    free_mission_salvage_resource_list();
    release_and_show_mouse_cursor();
    force_feedback_runtime_helper_00445b80();
    force_feedback_runtime_helper_00445b60();
    update_or_clear_input_binding_state_after_poll();
    terrain_map_context_helper_00490830();
    palette_dib_surface_blit_context_helper_00477be0();
    preload_smoke_or_dust_textures();
    load_smoke_animation_texture_pair();
    vehicle_effect_runtime_shutdown_helper_00443c50();
    release_projectile_tracer_runtime_records();
    force_feedback_user_entity_lookup_context_helper_00444e90();
    update_target_reticle_texture_state();
    release_sky_texture_resources();
    load_predefined_localized_m16_texture_set();
    world_transform_projection_context_helper_0048e6c0();
    terrain_map_log_tag();
    chunk_manager_update_log_tag();
    chunk_manager_entry_context_helper_004a1f90();
    update_classifier_display();
    iVar27 = is_network_or_trip_runtime_mode();
    if (iVar27 != 0) {
      cleanup_temp_network_vehicle_files();
      multiplayer_network_scoreboard_table_helper_00451960();
    }
    load_another_satellite_map();
    ordnance_system_log_tag();
    chunk_manager_update_context_helper_004a2d30();
    explosion_system_log_tag();
    initialize_muzzle_flash_effect_system();
    entity_instance_id_table_log_tag();
    shutdown_fsm_runtime_heap_and_tables();
    shutdown_effect_target_system();
    destroy_texture_animation_list();
    texture_cache_lru_helper_00447c80();
    initialize_explosion_effect_system();
    special_equipment_state_context_helper_00468040();
    destroy_geometry_binding_hash_heaps();
    geometry_buffer_preconstruct_helper_00446c70();
    shutdown_radar_mask_texture();
    destroy_texture_binding_cache_heaps();
    terrain_map_context_helper_004905e0();
    mission_objective_notepad_context_helper_0045eba0();
    texture_resource_cache_context_helper_00447fd0();
    iVar27 = is_damage_side_effects_suppressed();
    if (iVar27 != 0) {
      multiplayer_chat_ui_context_helper_00453860();
      set_damage_side_effects_suppressed(0);
    }
    mission_flow_map_context_helper_0049c3b0();
    mission_flow_map_context_helper_0049c2a0();
    ui_bitmap_region_context_helper_0049b770();
    notepad_objective_text_context_helper_0045e110();
    system_cutscene_memory_context_helper_00499cb0();
    system_cutscene_memory_context_helper_00499c80();
    if ((iVar9 == 7) && (iVar27 = _strnicmp(&DAT_005049f0,s_t17_004c254c,3), iVar27 == 0)) {
      iVar9 = 8;
      g_game_flow_state = 8;
    }
    if (DAT_00504c10 == 0) {
      if (iVar9 != 7) {
        if (iVar9 == 10) goto LAB_004046e2;
        goto LAB_004031f5;
      }
    }
    else {
LAB_004046e2:
      if (iVar9 != 7) {
        if ((DAT_00504c10 != 0) || (iVar9 == 10)) {
          local_9d4 = 0xff;
        }
        goto LAB_0040320b;
      }
    }
    if (g_shell_return_state == 2) {
LAB_0040472b:
      uVar15 = 0xffffffff;
      pcVar26 = &g_shell_return_path_buffer;
      do {
        pcVar21 = pcVar26;
        if (uVar15 == 0) break;
        uVar15 = uVar15 - 1;
        pcVar21 = pcVar26 + 1;
        cVar1 = *pcVar26;
        pcVar26 = pcVar21;
      } while (cVar1 != '\0');
      uVar15 = ~uVar15;
      pcVar26 = pcVar21 + -uVar15;
      pcVar21 = (char *)&g_selected_mission_resource_path;
      for (uVar16 = uVar15 >> 2; uVar16 != 0; uVar16 = uVar16 - 1) {
        *(undefined4 *)pcVar21 = *(undefined4 *)pcVar26;
        pcVar26 = pcVar26 + 4;
        pcVar21 = pcVar21 + 4;
      }
LAB_0040474b:
      for (uVar15 = uVar15 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
        *pcVar21 = *pcVar26;
        pcVar26 = pcVar26 + 1;
        pcVar21 = pcVar21 + 1;
      }
    }
    else {
      if (g_shell_return_state == 4) {
        uVar15 = 0xffffffff;
        pcVar26 = &g_shell_return_path_buffer;
        do {
          pcVar21 = pcVar26;
          if (uVar15 == 0) break;
          uVar15 = uVar15 - 1;
          pcVar21 = pcVar26 + 1;
          cVar1 = *pcVar26;
          pcVar26 = pcVar21;
        } while (cVar1 != '\0');
        uVar15 = ~uVar15;
        pcVar26 = pcVar21 + -uVar15;
        pcVar21 = (char *)&g_selected_mission_resource_path;
        for (uVar16 = uVar15 >> 2; uVar16 != 0; uVar16 = uVar16 - 1) {
          *(undefined4 *)pcVar21 = *(undefined4 *)pcVar26;
          pcVar26 = pcVar26 + 4;
          pcVar21 = pcVar21 + 4;
        }
        goto LAB_0040474b;
      }
      if (g_shell_return_state == 3) {
        set_shell_return_launch_requested(1);
        goto LAB_0040472b;
      }
    }
    g_game_flow_state = 5;
    DAT_005dd360 = _g_display_mode_variant_index & 0xff;
  } while( true );
}


