/*
 * Program: i76.exe
 * Function: create_textured_building_piece
 * Entry: 0046c8b0
 * Signature: undefined __cdecl create_textured_building_piece(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: strings x1_bldx1 and V1 FT/LF/MD texture slots */

void __cdecl create_textured_building_piece(int param_1)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined3 extraout_var;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  byte *pbVar11;
  uint uVar12;
  byte *local_2c;
  uint local_28;
  undefined4 local_24;
  uint local_20;
  uint local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c [3];
  
  iVar2 = param_1;
  local_20 = 0;
  local_1c = 0;
  piVar1 = *(int **)(param_1 + 0x70);
  has_world_object_class_damage_handler(*piVar1);
  iVar4 = get_active_player_or_camera_world_object_entry();
  if ((iVar4 != 0) &&
     (piVar5 = (int *)get_active_player_or_camera_world_object_entry(), *piVar5 == param_1)) {
    clear_pending_input_action_state();
    iVar4 = 0xfefe;
    uVar6 = get_active_player_or_camera_world_object_entry();
    dispatch_runtime_camera_mode_activation_by_id(uVar6,iVar4);
    weapon_hud_display_context_helper_004621b0();
    _DAT_0053679c = 8;
    iVar4 = is_damage_side_effects_suppressed();
    if (iVar4 != 0) {
      stamp_multiplayer_respawn_or_score_time();
    }
  }
  local_18 = (float)*(double *)(param_1 + 0x40);
  local_14 = (float)*(double *)(param_1 + 0x48);
  local_10 = (float)*(double *)(param_1 + 0x50);
  local_2c = (byte *)0x0;
  local_28 = 0;
  strncpy((char *)&local_2c,s_x1_bldx1_004f7d34,8);
  spawn_cached_explosion_runtime_object
            ((uint)local_2c,local_28,param_1,local_18,local_14,local_10,0);
  local_18 = (float)*(double *)(param_1 + 0x40);
  local_14 = (float)*(double *)(param_1 + 0x48);
  local_10 = (float)*(double *)(param_1 + 0x50);
  strncpy((char *)&local_20,s_x1_bldx1_004f7d34,8);
  spawn_cached_explosion_runtime_object
            (local_20,local_1c,param_1,local_18,local_14,local_10,param_1);
  local_2c = (byte *)s_V1_FT_FT_MAP_004f86b8;
  iVar4 = 0;
  do {
    if ((piVar1[*(int *)((int)&DAT_004f8688 + iVar4) + 0x102] != 0) &&
       (bVar3 = release_or_detach_object_geometry_variant
                          (piVar1[*(int *)((int)&DAT_004f8688 + iVar4) + 0x102],3),
       CONCAT31(extraout_var,bVar3) == 1)) {
      has_world_object_class_damage_handler(*piVar1);
    }
    uVar8 = piVar1[*(int *)((int)&DAT_004f8688 + iVar4) + 0x102];
    if ((uVar8 != 0) && (iVar10 = 0, pbVar11 = local_2c, 0 < *(int *)((int)&DAT_004f86a0 + iVar4)))
    {
      do {
        set_texture_binding_frame_and_reload(uVar8,pbVar11,0,3,1);
        iVar10 = iVar10 + 1;
        pbVar11 = pbVar11 + 0xd;
      } while (iVar10 < *(int *)((int)&DAT_004f86a0 + iVar4));
    }
    iVar4 = iVar4 + 4;
    local_2c = local_2c + 0x82;
  } while ((int)local_2c < 0x4f8942);
  get_world_object_class_id(param_1,0x201);
  for (iVar4 = *(int *)(param_1 + 100); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x60)) {
    create_chunk_manager_geometry_runtime(iVar4);
  }
  local_2c = (byte *)0x0;
  local_28 = 0;
  local_24 = 0;
  param_1 = 10;
  do {
    local_c[0] = 0.0;
    local_c[1] = 0.0;
    local_c[2] = (float)local_24;
    uVar7 = rand();
    uVar9 = (int)uVar7 >> 0x1f;
    uVar8 = DAT_004f7d24;
    uVar12 = DAT_004f7d28;
    if (((uVar7 ^ uVar9) - uVar9 & 1 ^ uVar9) != uVar9) {
      uVar8 = DAT_004f7d2c;
      uVar12 = DAT_004f7d30;
    }
    destroy_chunk_manager_objects(uVar8,uVar12,local_18,local_14,local_10,local_c,15.0);
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  remove_loaded_vehicle_runtime_and_weapon_slots(iVar2);
  mark_active_vehicle_damage_textures_dirty();
  dispatch_vehicle_runtime_sound_event(7,iVar2,(undefined4 *)0x0);
  iVar4 = world_object_has_optional_runtime_flag(iVar2);
  if ((iVar4 == 0) &&
     ((iVar4 = is_network_or_trip_runtime_mode(), iVar4 != 0 ||
      ((iVar4 = is_damage_side_effects_suppressed(), iVar4 != 0 &&
       (iVar4 = multiplayer_player_count_context_helper_00454620((short)piVar1[0x120],(uchar *)0x0),
       iVar4 == 0)))))) {
    vehicle_system_log_tag((int *)*piVar1);
    return;
  }
  unregister_effect_target_record((int *)*piVar1);
  stop_vehicle_engine_loop_sound(iVar2);
  return;
}


