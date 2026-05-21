/*
 * Program: i76.exe
 * Function: play_adwind_audio_clip
 * Entry: 0044ed50
 * Signature: undefined __stdcall play_adwind_audio_clip(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: references @ADWIND.WAV */

void play_adwind_audio_clip(void)

{
  int iVar1;
  char cVar2;
  char cVar3;
  int *piVar4;
  uint uVar5;
  float *pfVar6;
  float10 fVar7;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  int local_18;
  int local_14;
  int local_10;
  float local_c;
  float local_8;
  
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 == (int *)0x0) {
    return;
  }
  if (g_runtime_display_mode_state != 0) {
    world_object_texture_binding_lookup_helper_0046e240(*piVar4,1);
    world_object_texture_binding_lookup_helper_0046e240(*piVar4,2);
  }
  if ((g_runtime_display_mode_state == 0) || (g_runtime_display_mode_state == 2)) {
    DAT_0053eb54 = find_audio_object_by_name_and_world_object
                             (s__ADWIND_WAV_004f5343 + 1,*DAT_004c2908);
  }
  else if (*DAT_004c2908 != 0) {
    play_named_sound_attached_to_object_or_player
              (s__ADWIND_WAV_004f5343 + 1,*DAT_004c2908,(undefined4 *)0x0);
  }
  if (DAT_0053eb54 != (int *)0x0) {
    release_audio_object_if_present(DAT_0053eb54);
    DAT_0053eb54 = (int *)0x0;
  }
  cVar3 = DAT_0053678b;
  cVar2 = DAT_0053678a;
  if (g_runtime_display_mode_state == 0) {
    if (DAT_0053eb58 != 0) {
      DAT_00536770 = 0;
      _DAT_00536780 = 0;
      _DAT_00536778 = 0xfffffff3;
      _DAT_004c296c = 0;
      _DAT_004c2964 = 0xbe685696;
      _DAT_004c2974 = 0;
      DAT_004c2970 = 0;
      DAT_004c2968 = 0xbe685696;
      DAT_004c2978 = 0;
    }
    keyboard_joystick_input_binding_context_helper_0044f830();
    DAT_0053eb58 = g_runtime_display_mode_state;
    return;
  }
  if (g_runtime_display_mode_state != 2) {
    DAT_0053eb58 = g_runtime_display_mode_state;
    return;
  }
  if (DAT_0053eb58 != 2) {
    DAT_00536770 = 0;
    _DAT_00536780 = 0;
    _DAT_00536778 = 0;
    DAT_0053eb50 = 0;
    _DAT_004c296c = 0;
    _DAT_004c2964 = 0;
    _DAT_004c2974 = 0;
    DAT_004c2970 = 0;
    DAT_004c2968 = 0;
    DAT_004c2978 = 0;
  }
  local_14 = (int)DAT_00536787;
  local_18 = (int)DAT_00536788;
  local_10 = (int)DAT_00536789;
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 == (int *)0x0) {
    DAT_0053eb58 = g_runtime_display_mode_state;
    return;
  }
  uVar5 = get_primary_vehicle_weapon_target_object(*piVar4);
  if ((cVar3 != '\0') && (uVar5 != 0)) {
    iVar1 = *piVar4;
    local_3c = *(float *)(iVar1 + 0x30);
    local_38 = *(float *)(iVar1 + 0x34);
    local_34 = *(float *)(iVar1 + 0x38);
    local_24 = local_3c;
    local_20 = local_38;
    local_1c = local_34;
    pfVar6 = (float *)entity_instance_table_context_helper_004576a0(&local_4c,uVar5);
    local_48 = *pfVar6 - (float)*(double *)(iVar1 + 0x40);
    local_44 = pfVar6[1] - (float)*(double *)(iVar1 + 0x48);
    local_40 = pfVar6[2] - (float)*(double *)(iVar1 + 0x50);
    fVar7 = (float10)fpatan((float10)local_24,(float10)local_34);
    local_8 = (float)fVar7;
    fVar7 = (float10)fpatan((float10)local_48,(float10)local_40);
    local_c = local_8 - (float)fVar7;
    if (local_c <= _DAT_004bd8bc) {
      if (local_c < _DAT_004bd8c4) {
        local_c = local_c - _DAT_004bd8c8;
      }
    }
    else {
      local_c = local_c - _DAT_004bd8c0;
    }
    local_c = -local_c;
    local_30 = local_48;
    local_2c = local_44;
    local_28 = local_40;
    if ((local_c < _DAT_004bd8cc) && (_DAT_004bd8d0 < local_c)) {
      DAT_00536770 = ftol();
    }
    fVar7 = (float10)fpatan((float10)SQRT(local_1c * local_1c +
                                          local_20 * local_20 + local_24 * local_24),
                            (float10)local_38);
    local_c = (float)fVar7;
    fVar7 = (float10)fpatan((float10)SQRT(local_28 * local_28 +
                                          local_2c * local_2c + local_30 * local_30),
                            (float10)local_44);
    local_8 = (float)fVar7;
    fVar7 = keyboard_joystick_input_binding_context_helper_0044f180(local_8,local_c);
    local_c = (float)fVar7;
    if ((fVar7 < (float10)_DAT_004bd8d8) && (_DAT_004bd8dc < local_c)) {
      _DAT_00536778 = ftol();
    }
    goto LAB_0044f0c6;
  }
  DAT_00536770 = DAT_0053eb50;
  if (local_14 != 0) {
    if (cVar2 == '\0') {
      if (-0x58 < DAT_0053eb50) {
        DAT_00536770 = DAT_0053eb50 + -0x1d;
        DAT_0053eb50 = DAT_00536770;
      }
      goto LAB_0044f0c6;
    }
    if ((local_14 != 0) && ((cVar2 != '\0' || (local_10 != 0)))) {
      DAT_00536770 = -0x2d;
      DAT_0053eb50 = DAT_00536770;
      goto LAB_0044f0c6;
    }
  }
  if (local_18 != 0) {
    if (cVar2 == '\0') {
      if (DAT_0053eb50 < 0x5d) {
        DAT_00536770 = DAT_0053eb50 + 0x1f;
        DAT_0053eb50 = DAT_00536770;
      }
      goto LAB_0044f0c6;
    }
    if ((local_18 != 0) && ((cVar2 != '\0' || (local_10 != 0)))) {
      DAT_00536770 = 0x2d;
      DAT_0053eb50 = DAT_00536770;
      goto LAB_0044f0c6;
    }
  }
  DAT_00536770 = 0;
  DAT_0053eb50 = DAT_00536770;
LAB_0044f0c6:
  if (local_14 != 0) {
    DAT_00536787 = '\0';
  }
  if (local_18 != 0) {
    DAT_00536788 = '\0';
  }
  if (local_10 != 0) {
    DAT_00536789 = '\0';
  }
  if (cVar2 == '\0') {
    DAT_0053eb58 = g_runtime_display_mode_state;
    return;
  }
  DAT_0053678a = 0;
  DAT_0053eb58 = g_runtime_display_mode_state;
  return;
}


