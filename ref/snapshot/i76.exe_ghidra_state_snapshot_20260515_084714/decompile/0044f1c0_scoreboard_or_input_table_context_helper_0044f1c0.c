/*
 * Program: i76.exe
 * Function: scoreboard_or_input_table_context_helper_0044f1c0
 * Entry: 0044f1c0
 * Signature: undefined __stdcall scoreboard_or_input_table_context_helper_0044f1c0(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: scoreboard or input table context
   helper based on prior focused closure context. */

void scoreboard_or_input_table_context_helper_0044f1c0(void)

{
  float fVar1;
  int iVar2;
  bool bVar3;
  float fVar4;
  short sVar5;
  uint *puVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  uint *puVar11;
  int *piVar12;
  float10 fVar13;
  float10 fVar14;
  undefined4 uVar15;
  int local_14;
  uint local_c [3];
  
  fVar13 = get_runtime_frame_delta_seconds();
  fVar1 = (float)fVar13;
  puVar6 = (uint *)get_active_player_or_camera_world_object_entry();
  iVar2 = *(int *)(*puVar6 + 0x70);
  iVar7 = is_damage_side_effects_suppressed();
  if ((iVar7 != 0) &&
     ((sVar5 = multiplayer_chat_ui_context_helper_00453ab0(), sVar5 != 0 ||
      (iVar7 = multiplayer_network_scoreboard_table_helper_00451950(), iVar7 != 0)))) {
    *(undefined4 *)(iVar2 + 0xe4) = 0xbf800000;
    *(undefined4 *)(iVar2 + 0xe0) = 0;
    return;
  }
  fVar14 = get_runtime_frame_delta_seconds();
  fVar4 = _DAT_004bd8b8;
  fVar13 = (float10)_DAT_004f5340;
  _DAT_004f5340 = (float)(fVar13 - fVar14);
  if (fVar13 - fVar14 <= (float10)_DAT_004bd8b8) {
    _DAT_004f5340 = 0.0;
  }
  if (DAT_005367d1 == '\0') {
    if (DAT_005367d0 != '\0') goto LAB_0044f2cd;
    if ((DAT_005367d9 != '\0') || (DAT_005367da != '\0')) goto LAB_0044f2c9;
    *(float *)(iVar2 + 0xe4) = (float)DAT_005367cc * _DAT_004bd8e4;
    *(float *)(iVar2 + 0xe0) = (float)_DAT_005367d4 * _DAT_004bd8e4;
    _DAT_0053eb5c = fVar4;
    _DAT_0053eb60 = fVar4;
    _DAT_0053eb64 = fVar4;
    _DAT_0053eb68 = fVar4;
  }
  else {
LAB_0044f2c9:
    if (DAT_005367d0 == '\0') {
      _DAT_0053eb5c = 0.0;
    }
    else {
LAB_0044f2cd:
      _DAT_0053eb5c = fVar1 + _DAT_0053eb5c;
      if (_DAT_004bd8e8 < _DAT_0053eb5c) {
        _DAT_0053eb5c = 3.0;
      }
      *(float *)(iVar2 + 0xe4) =
           *(float *)(iVar2 + 0xe4) -
           (_DAT_004bd8f0 - _DAT_0053eb5c * _DAT_004bd8ec) * _DAT_004bd8f4;
    }
    if (DAT_005367d1 == '\0') {
      _DAT_0053eb60 = 0.0;
    }
    else {
      _DAT_0053eb60 = fVar1 + _DAT_0053eb60;
      if (_DAT_004bd8e8 < _DAT_0053eb60) {
        _DAT_0053eb60 = 3.0;
      }
      *(float *)(iVar2 + 0xe4) =
           *(float *)(iVar2 + 0xe4) -
           (_DAT_004bd8f0 - _DAT_0053eb60 * _DAT_004bd8ec) * _DAT_004bd8f8;
    }
    if (DAT_005367d9 == '\0') {
      _DAT_0053eb64 = 0.0;
    }
    else {
      _DAT_0053eb64 = fVar1 + _DAT_0053eb64;
      if (_DAT_004bd8e8 < _DAT_0053eb64) {
        _DAT_0053eb64 = 3.0;
      }
      *(float *)(iVar2 + 0xe0) = SQRT(_DAT_0053eb64 * _DAT_004bd8ec) * _DAT_004bd8fc;
    }
    if (DAT_005367da == '\0') {
      _DAT_0053eb68 = 0.0;
    }
    else {
      _DAT_0053eb68 = fVar1 + _DAT_0053eb68;
      if (_DAT_004bd8e8 < _DAT_0053eb68) {
        _DAT_0053eb68 = 3.0;
      }
      *(float *)(iVar2 + 0xe0) = SQRT(_DAT_0053eb68 * _DAT_004bd8ec);
    }
    if ((DAT_005367d1 == '\0') && (DAT_005367d0 == '\0')) {
      *(undefined4 *)(iVar2 + 0xe4) = 0;
    }
    if ((DAT_005367da == '\0') && (DAT_005367d9 == '\0')) {
      *(undefined4 *)(iVar2 + 0xe0) = 0;
    }
  }
  if (_DAT_004bd900 < *(float *)(iVar2 + 0xe4)) {
    *(undefined4 *)(iVar2 + 0xe4) = 0x3f7ff972;
  }
  if (*(float *)(iVar2 + 0xe4) < _DAT_004bd904) {
    *(undefined4 *)(iVar2 + 0xe4) = 0xbf7ff972;
  }
  if (_DAT_004bd900 < *(float *)(iVar2 + 0xe0)) {
    *(undefined4 *)(iVar2 + 0xe0) = 0x3f7ff972;
  }
  if (*(float *)(iVar2 + 0xe0) < _DAT_004bd904) {
    *(undefined4 *)(iVar2 + 0xe0) = 0xbf7ff972;
  }
  *(int *)(iVar2 + 0xec) = (int)DAT_005367e6;
  *(int *)(iVar2 + 0x100) = (int)DAT_005367e7;
  *(int *)(iVar2 + 0xf0) = (int)DAT_005367e9;
  if (*(int *)(*puVar6 + 0x6c) == 1) {
    if (DAT_005367ea != '\0') {
      vehicle_specials_state_setter_helper_00467390(*puVar6);
    }
    if (DAT_005367eb != '\0') {
      vehicle_specials_indicator_value_helper_004673b0(*puVar6);
    }
    iVar7 = get_vehicle_drivetrain_mode_state(*puVar6);
    if (iVar7 == 1) {
      *(undefined4 *)(iVar2 + 0xe8) = 0xbf800000;
    }
    else {
      *(undefined4 *)(iVar2 + 0xe8) = 0x3f800000;
    }
    if (DAT_005367e8 != '\0') {
      bVar3 = -*(float *)(iVar2 + 0xe8) == _DAT_004bd8fc;
      *(float *)(iVar2 + 0xe8) = -*(float *)(iVar2 + 0xe8);
      if (bVar3) {
        uVar10 = *puVar6;
        uVar15 = 1;
      }
      else {
        uVar10 = *puVar6;
        uVar15 = 3;
      }
      vehicle_specials_state_getter_helper_00467370(uVar10,uVar15);
    }
  }
  if (DAT_005367f9 != '\0') {
    trigger_vehicle_forced_damage_or_actor_cleanup(*puVar6);
    DAT_005367f9 = '\0';
  }
  if (iVar2 != 0) {
    piVar12 = (int *)(iVar2 + 0x3ec);
    local_c[0] = (uint)(DAT_005367e3 != '\0');
    puVar11 = local_c;
    local_c[1] = (uint)(DAT_005367e4 != '\0');
    local_c[2] = (uint)(DAT_005367e5 != '\0');
    local_14 = 3;
    do {
      iVar7 = *piVar12;
      if ((*puVar11 != 0) && (iVar7 != 0)) {
        iVar8 = get_special_equipment_runtime_index(iVar7);
        if (iVar8 == 1) {
          piVar9 = (int *)get_active_player_or_camera_world_object_entry();
          if (piVar9 != (int *)0x0) {
            play_clock_or_jammer_audio(*piVar9,iVar7);
          }
        }
        else if (iVar8 == 2) {
          play_nitro_boost_audio();
        }
        else if (iVar8 == 4) {
          *(undefined4 *)(iVar2 + 0xf4) = 1;
        }
      }
      piVar12 = piVar12 + 1;
      puVar11 = puVar11 + 1;
      local_14 = local_14 + -1;
    } while (local_14 != 0);
  }
  if (DAT_005367ec != '\0') {
    initialize_mission_map_display();
  }
  if ((DAT_005367ed != '\0') && (iVar7 = is_damage_side_effects_suppressed(), iVar7 == 0)) {
    initialize_notepad_objective_display();
  }
  if (DAT_005367ee == '\0') {
    iVar7 = is_damage_side_effects_suppressed();
    if (iVar7 == 0) goto LAB_0044f6ae;
    uVar10 = *(uint *)(iVar2 + 0x454) & 0xffdfffff;
  }
  else {
    play_vehicle_engine_event_sound_unattached(*puVar6);
    iVar7 = is_damage_side_effects_suppressed();
    if (iVar7 == 0) goto LAB_0044f6ae;
    uVar10 = *(uint *)(iVar2 + 0x454) | 0x200000;
  }
  *(uint *)(iVar2 + 0x454) = uVar10;
LAB_0044f6ae:
  if (DAT_005367ef != '\0') {
    play_post_mission_audio_sequence_b(*puVar6);
  }
  if (DAT_005367f0 != '\0') {
    input_device_binding_input_action_state_helper_0044dff0(0);
    input_device_binding_input_action_state_helper_0044e000(0xd);
    dispatch_runtime_camera_mode_activation_by_id(puVar6,0xd);
  }
  if (DAT_005367f1 != '\0') {
    radar_render_context_helper_00460db0(*puVar6);
  }
  if (DAT_005367f2 != '\0') {
    radar_render_context_helper_00460de0(*puVar6);
  }
  if (DAT_005367f3 != '\0') {
    radar_render_context_helper_00460e10(*puVar6);
  }
  if (DAT_005367f4 != '\0') {
    uVar10 = select_fsm_target_or_closest_user_vehicle(*puVar6);
    radar_render_context_helper_00461270(*puVar6,uVar10);
  }
  if (DAT_005367f5 != '\0') {
    if (_DAT_004f5340 == _DAT_004bd8b8) {
      radar_render_context_helper_00461220(*puVar6);
    }
    radar_render_context_helper_00460f20((int *)*puVar6);
    _DAT_004f5340 = 5.0;
  }
  if (DAT_005367f6 != '\0') {
    if (_DAT_004f5340 == _DAT_004bd8b8) {
      radar_render_context_helper_00461220(*puVar6);
    }
    radar_render_context_helper_00461040((int *)*puVar6);
    _DAT_004f5340 = 5.0;
  }
  if (DAT_005367f7 != '\0') {
    radar_render_context_helper_00461150(*puVar6,1);
  }
  if (DAT_005367f8 != '\0') {
    radar_render_context_helper_00461220(*puVar6);
  }
  if (DAT_005367fa != '\0') {
    input_device_binding_input_action_state_helper_0044dfa0(puVar6);
  }
  player_score_table_context_helper_004522c0((int)DAT_005367fb);
  if (DAT_005367fb == '\0') {
    write_player_score_table((int)DAT_005367fc);
  }
  return;
}


