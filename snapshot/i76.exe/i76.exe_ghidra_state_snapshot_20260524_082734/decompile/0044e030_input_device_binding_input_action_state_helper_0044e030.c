/*
 * Program: i76.exe
 * Function: input_device_binding_input_action_state_helper_0044e030
 * Entry: 0044e030
 * Signature: undefined __cdecl input_device_binding_input_action_state_helper_0044e030(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: likely input_device_binding /
   input_action_state_helper based on address neighborhood and prior focused closure context. */

void __cdecl input_device_binding_input_action_state_helper_0044e030(int param_1)

{
  bool bVar1;
  bool bVar2;
  short sVar3;
  int *piVar4;
  int iVar5;
  undefined3 extraout_var;
  uint uVar6;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  iVar5 = is_damage_side_effects_suppressed();
  if ((iVar5 == 0) || (piVar4 != (int *)0x0)) {
    bVar2 = true;
    switch(param_1) {
    case 0:
    case 0x54:
      break;
    default:
      bVar2 = false;
      break;
    case 10:
      bVar1 = is_miss16_high_color_resource_mode();
      if (CONCAT31(extraout_var,bVar1) == 0) {
        format_screenshot_pcx_name(&DAT_005dcec0);
      }
      else {
        DAT_00504bf0 = 1;
      }
      break;
    case 0x22:
      if (((byte)g_runtime_display_input_mode & 0x10) == 0) {
        enter_mission_loading_flow_and_refresh_render_resources();
      }
      else {
        initialize_player_definition_file();
      }
      break;
    case 0x26:
      iVar5 = is_damage_side_effects_suppressed();
      if ((iVar5 != 0) && (uVar6 = entity_instance_table_context_helper_00457540(), uVar6 != 0)) {
        multiplayer_respawn_state_context_helper_00451570(1);
      }
      break;
    case 0x33:
      mission_flow_map_context_helper_0049d140();
      break;
    case 0x34:
      set_game_flow_state(2);
      break;
    case 0x5d:
      DAT_00654b8c._2_1_ = DAT_00654b8c._2_1_ ^ 1;
    }
    if (((!bVar2) && (uVar6 = entity_instance_table_context_helper_00457540(), uVar6 == 0)) &&
       (sVar3 = multiplayer_chat_ui_context_helper_00453ab0(), sVar3 == 0)) {
      switch(param_1) {
      case 0xb:
        force_feedback_device_state_helper_00445640();
        _DAT_0053eb38 = param_1;
        return;
      case 0xc:
        bVar2 = is_miss16_high_color_resource_mode();
        if (CONCAT31(extraout_var_00,bVar2) != 0) {
          DAT_0054ac68 = (uint)(DAT_0054ac68 == 0);
          _DAT_0053eb38 = param_1;
          return;
        }
        DAT_0054ac68 = 0;
        _DAT_0053eb38 = param_1;
        return;
      case 0xe:
        DAT_0053eb30 = 1;
        dispatch_runtime_camera_mode_activation_by_id(piVar4,param_1);
        _DAT_0053eb38 = param_1;
        return;
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
        if (param_1 == 0x12) {
          weapon_hud_display_context_helper_004621b0();
        }
        DAT_0053eb30 = 0;
        DAT_0053eb34 = param_1;
        dispatch_runtime_camera_mode_activation_by_id(piVar4,param_1);
        _DAT_0053eb38 = param_1;
        return;
      case 0x25:
        DAT_005367f9 = 1;
        _DAT_0053eb38 = param_1;
        return;
      case 0x27:
        iVar5 = is_damage_side_effects_suppressed();
        if (iVar5 != 0) {
          draw_multiplayer_chat_prompt(0);
          _DAT_0053eb38 = param_1;
          return;
        }
        break;
      case 0x28:
        iVar5 = is_damage_side_effects_suppressed();
        if (iVar5 != 0) {
          cockpit_gauge_context_helper_0045be00();
          _DAT_0053eb38 = param_1;
          return;
        }
        break;
      case 0x29:
        iVar5 = is_damage_side_effects_suppressed();
        if ((iVar5 != 0) &&
           (bVar2 = is_local_multiplayer_sync_player_current(), CONCAT31(extraout_var_01,bVar2) != 0
           )) {
          iVar5 = multiplayer_prompt_context_helper_00455800();
          if (iVar5 != 0) {
            multiplayer_vote_prompt_context_helper_004557a0();
            _DAT_0053eb38 = param_1;
            return;
          }
          iVar5 = multiplayer_chat_ui_context_helper_00452e00();
          if (iVar5 == 0) {
            directplay_message_dispatch_context_helper_00455c00();
            _DAT_0053eb38 = param_1;
            return;
          }
        }
        break;
      case 0x2a:
        iVar5 = is_damage_side_effects_suppressed();
        if ((iVar5 != 0) &&
           (bVar2 = is_local_multiplayer_sync_player_current(), CONCAT31(extraout_var_02,bVar2) != 0
           )) {
          iVar5 = multiplayer_prompt_context_helper_00455800();
          if (iVar5 != 0) {
            multiplayer_prompt_context_helper_004557e0();
            _DAT_0053eb38 = param_1;
            return;
          }
          iVar5 = multiplayer_chat_ui_context_helper_00452e00();
          if (iVar5 == 0) {
            network_vehicle_message_context_helper_00455cd0();
            _DAT_0053eb38 = param_1;
            return;
          }
        }
        break;
      case 0x2b:
        iVar5 = is_damage_side_effects_suppressed();
        if (((iVar5 != 0) &&
            (bVar2 = is_local_multiplayer_sync_player_current(),
            CONCAT31(extraout_var_03,bVar2) != 0)) &&
           ((iVar5 = multiplayer_chat_ui_context_helper_00452e00(), iVar5 == 0 &&
            (iVar5 = multiplayer_prompt_context_helper_00455800(), iVar5 == 0)))) {
          network_vehicle_message_context_helper_00455d80();
          _DAT_0053eb38 = param_1;
          return;
        }
        break;
      case 0x2c:
      case 0x2d:
      case 0x2e:
      case 0x2f:
      case 0x30:
      case 0x31:
      case 0x32:
        iVar5 = is_damage_side_effects_suppressed();
        if ((iVar5 != 0) &&
           (bVar2 = is_local_multiplayer_sync_player_current(), CONCAT31(extraout_var_04,bVar2) != 0
           )) {
          prompt_boot_player_from_game(param_1 - 0x2c);
          _DAT_0053eb38 = param_1;
          return;
        }
        break;
      case 0x5c:
        DAT_004f4ca4 = DAT_005dd360;
        do {
          DAT_005dd360 = (DAT_005dd360 + 1) % 9;
          if (DAT_005dd360 == 0) {
            DAT_005dd360 = 1;
          }
        } while ((&DAT_004f9e08)[DAT_005dd360 * 7] == 0);
        iVar5 = (*DAT_005dd2cc)(&DAT_005dcec0,DAT_005dd360);
        if (iVar5 == 0) {
          DAT_005dd360 = DAT_004f4ca4;
          fatal_out_of_memory_message((LPCSTR)0x0);
        }
        g_display_mode_variant_index = (undefined1)DAT_005dd360;
        save_player_definition();
        load_base_font_resource_variants();
        input_action_registration_context_helper_0044bb30();
        preload_cockpit_gauge_textures(*piVar4);
        initialize_runtime_camera_projection_matrix(1);
        initialize_or_refresh_player_weapon_hud_overlay((int *)0x0);
        load_specials_backing_texture(*piVar4);
        initialize_or_resize_runtime_text_overlay_buffers(1);
      }
    }
    _DAT_0053eb38 = param_1;
  }
  else if ((param_1 == 0x34) || (param_1 == 0x35)) {
    set_game_flow_state(2);
    return;
  }
  return;
}


