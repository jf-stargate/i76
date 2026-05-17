/*
 * Program: i76.exe
 * Function: apply_vehicle_destruction_effects_and_chunk_spawns
 * Entry: 0046b220
 * Signature: undefined __cdecl apply_vehicle_destruction_effects_and_chunk_spawns(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium-high] Vehicle destruction helper
   referencing CHUNK1/CHUNK2/K1/K2 and explosion/building/car effect resources. */

void __cdecl apply_vehicle_destruction_effects_and_chunk_spawns(int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  float *pfVar12;
  uint uVar13;
  char *pcVar14;
  int local_110;
  uint local_10c;
  uint local_108;
  float local_104;
  float local_100;
  float local_fc;
  char *local_f4;
  int local_f0;
  float local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  float local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80 [16];
  float local_40 [16];
  
  iVar6 = *(int *)(param_1 + 0x70);
  local_f0 = iVar6;
  get_world_object_class_id(param_1,0x200);
  iVar5 = is_transform_composed_world_object_class(param_1);
  if (iVar5 != 0) {
    *(undefined4 *)(iVar6 + 0x28) = 1;
  }
  create_chunk_manager_geometry_runtime(param_1);
  for (iVar6 = *(int *)(param_1 + 100); iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x60)) {
    apply_vehicle_destruction_effects_and_chunk_spawns(iVar6);
  }
  iVar6 = copy_world_object_position_vector(param_1);
  if (iVar6 != 0) {
    iVar6 = get_parent_if_current_is_last_child_link(param_1);
    pcVar14 = *(char **)(iVar6 + 0x70);
    local_f4 = pcVar14;
    iVar5 = is_transform_composed_world_object_class(iVar6);
    if (iVar5 != 0) {
      pcVar14[0x28] = '\x01';
      pcVar14[0x29] = '\0';
      pcVar14[0x2a] = '\0';
      pcVar14[0x2b] = '\0';
      create_chunk_manager_geometry_runtime(iVar6);
      iVar5 = copy_world_object_orientation_or_velocity_vector(iVar6,0x1000000);
      if (iVar5 != 0) {
        iVar1 = *(int *)(iVar6 + 0x70);
        local_10c = 0;
        local_108 = 0;
        if (iVar1 != 0) {
          pfVar7 = (float *)compose_world_object_runtime_transform(&local_ec,iVar5);
          fVar2 = *pfVar7;
          local_100 = pfVar7[1];
          local_fc = pfVar7[2];
          if (*(int *)(iVar6 + 0x6c) != 3) {
            iVar8 = _strnicmp((char *)(iVar1 + 0x10),s_null_004c3280,8);
            if (iVar8 == 0) {
              strncpy((char *)&local_10c,s_x1_bldx1_004f7d34,8);
              uVar10 = local_10c;
              uVar13 = local_108;
            }
            else {
              uVar10 = *(uint *)(iVar1 + 0x10);
              uVar13 = *(uint *)(iVar1 + 0x14);
            }
            spawn_cached_explosion_runtime_object(uVar10,uVar13,iVar5,fVar2,local_100,local_fc,0);
            iVar8 = _stricmp((char *)(iVar1 + 0x18),s_null_004c3280);
            if (iVar8 == 0) {
              dispatch_vehicle_runtime_sound_event(7,iVar5,(undefined4 *)0x0);
            }
            else {
              play_positional_audio_for_object_or_active_player
                        ((char *)(iVar1 + 0x18),iVar5,(undefined4 *)0x0);
            }
          }
          *(undefined4 *)(iVar1 + 0x28) = 2;
          pcVar14 = local_f4;
        }
      }
      if ((*(uint *)(iVar6 + 0x10) & 0x800) != 0) {
        release_world_object_light_runtime(iVar6);
      }
      iVar6 = is_damage_side_effects_suppressed();
      if (iVar6 != 0) {
        network_vehicle_message_context_helper_00456710(*(uint *)(pcVar14 + 8));
      }
    }
  }
  iVar6 = is_transform_composed_world_object_class(param_1);
  if (((iVar6 == 0) || (*(int *)(param_1 + 0x5c) == 0)) || ((*(byte *)(local_f0 + 0x28) & 1) == 0))
  goto LAB_0046b6cd;
  iVar6 = *(int *)(param_1 + 0x70);
  local_10c = 0;
  local_108 = 0;
  pfVar7 = (float *)compute_transform_relative_to_ancestor(local_40,param_1,0);
  local_e0 = *(float *)(param_1 + 0x94);
  local_dc = *(undefined4 *)(param_1 + 0x98);
  local_d0 = *(undefined4 *)(param_1 + 0x98);
  local_c4 = *(undefined4 *)(param_1 + 0x98);
  local_bc = *(undefined4 *)(param_1 + 0x94);
  local_b8 = *(undefined4 *)(param_1 + 0x98);
  local_d8 = *(undefined4 *)(param_1 + 0x9c);
  pfVar12 = local_80;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar12 = *pfVar7;
    pfVar7 = pfVar7 + 1;
    pfVar12 = pfVar12 + 1;
  }
  local_cc = *(undefined4 *)(param_1 + 0x9c);
  local_c0 = *(undefined4 *)(param_1 + 0xa8);
  local_b4 = *(undefined4 *)(param_1 + 0xa8);
  local_d4 = *(undefined4 *)(param_1 + 0xa0);
  local_c8 = local_d4;
  transform_vec3_array_by_matrix(&local_b0,&local_e0,4,local_80);
  local_104 = (local_b0 + local_a4 + local_98 + local_8c) * _DAT_004be31c;
  local_100 = (local_ac + local_a0 + local_94 + local_88) * _DAT_004be31c;
  local_fc = (local_a8 + local_9c + local_90 + local_84) * _DAT_004be31c;
  if ((*(uint *)(param_1 + 0x10) & 0x400000) == 0) {
    if ((*(uint *)(param_1 + 0x10) & 0x800000) != 0) {
      pcVar14 = s_x1_cars1_004f8168;
      goto LAB_0046b5a1;
    }
  }
  else {
    pcVar14 = s_x1_bldx1_004f7d34;
LAB_0046b5a1:
    strncpy((char *)&local_10c,pcVar14,8);
  }
  fVar4 = local_fc;
  fVar3 = local_100;
  fVar2 = local_104;
  if (((-1 < (int)local_108) && ((0 < (int)local_108 || (local_10c != 0)))) &&
     (*(int *)(param_1 + 0x6c) != 3)) {
    spawn_cached_explosion_runtime_object
              (local_10c,local_108,param_1,local_104,local_100,local_fc,0);
    iVar5 = is_transform_composed_world_object_class(param_1);
    if (iVar5 != 0) {
      local_f4 = (char *)(iVar6 + 0x18);
      iVar5 = _stricmp(local_f4,s_null_004c3280);
      if (iVar5 != 0) {
        play_positional_audio_for_object_or_active_player(local_f4,param_1,(undefined4 *)0x0);
        goto LAB_0046b625;
      }
    }
    dispatch_vehicle_runtime_sound_event(7,param_1,(undefined4 *)0x0);
  }
LAB_0046b625:
  create_chunk_manager_geometry_runtime(param_1);
  local_104 = 0.0;
  local_100 = 15.0;
  local_fc = 0.0;
  local_ec = 0.0;
  local_e8 = 0x41700000;
  local_e4 = 0;
  local_110 = 8;
  do {
    uVar9 = rand();
    uVar11 = (int)uVar9 >> 0x1f;
    uVar10 = DAT_004f7d24;
    uVar13 = DAT_004f7d28;
    if (((uVar9 ^ uVar11) - uVar11 & 1 ^ uVar11) != uVar11) {
      uVar10 = DAT_004f7d2c;
      uVar13 = DAT_004f7d30;
    }
    destroy_chunk_manager_objects(uVar10,uVar13,fVar2,fVar3,fVar4,&local_ec,15.0);
    local_110 = local_110 + -1;
  } while (local_110 != 0);
  iVar5 = is_transform_composed_world_object_class(param_1);
  if (iVar5 != 0) {
    *(undefined4 *)(iVar6 + 0x28) = 2;
  }
LAB_0046b6cd:
  release_or_detach_object_geometry_variant(param_1,1);
  iVar6 = is_damage_side_effects_suppressed();
  if ((iVar6 != 0) && (iVar6 = is_transform_composed_world_object_class(param_1), iVar6 != 0)) {
    network_vehicle_message_context_helper_00456710(*(uint *)(local_f0 + 8));
  }
  return;
}


