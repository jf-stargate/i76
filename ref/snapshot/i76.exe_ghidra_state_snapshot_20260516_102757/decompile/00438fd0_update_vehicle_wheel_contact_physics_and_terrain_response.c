/*
 * Program: i76.exe
 * Function: update_vehicle_wheel_contact_physics_and_terrain_response
 * Entry: 00438fd0
 * Signature: undefined __cdecl update_vehicle_wheel_contact_physics_and_terrain_response(float * param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Top-level vehicle physics
   integrator for velocity, transform, contact flags, wheel/tire child state, tire speed scalars,
   airborne/grounded state, and impact damage. */

void __cdecl update_vehicle_wheel_contact_physics_and_terrain_response(float *param_1,float param_2)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  uint uVar7;
  int iVar8;
  undefined2 extraout_var;
  float fVar9;
  uint uVar10;
  float fVar11;
  float fVar12;
  float10 fVar13;
  float fVar14;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
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
  float local_80;
  float local_7c;
  float local_78;
  uint local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40 [16];
  
                    /* I76 semantic baseline note:
                       Lower-level vehicle wheel/contact/terrain/impact integration. Terrain
                       material can affect underbody/speed damage. */
  iVar3 = get_vehicle_runtime_context((int)param_1);
  if (*(int *)(iVar3 + 0x38) == 0) {
    iVar4 = probe_vehicle_ground_contact_from_wheel_points
                      ((int)param_1,(undefined4 *)(iVar3 + 0x38),param_2);
    uVar10 = *(uint *)(iVar3 + 0x454);
    if (iVar4 == 0) {
      *(uint *)(iVar3 + 0x454) = uVar10 & 0xffffffef;
      goto LAB_00439b4d;
    }
    if ((uVar10 & 0x10) != 0) goto LAB_00439b4d;
    *(uint *)(iVar3 + 0x454) = uVar10 | 0x10;
  }
  local_cc = 0.0;
  local_d0 = 0.0;
  local_d4 = 0.0;
  local_b8 = *(float *)(iVar3 + 0xbc);
  fVar12 = 0.0;
  local_b4 = *(float *)(iVar3 + 0xc0);
  local_b0 = *(float *)(iVar3 + 0xc4);
  local_80 = *(float *)(iVar3 + 0x98);
  local_7c = *(float *)(iVar3 + 0x9c);
  local_a8 = 0.0;
  local_78 = *(float *)(iVar3 + 0xa0);
  local_a4 = 0.0;
  local_8c = *(float *)(iVar3 + 0x80);
  local_84 = *(float *)(iVar3 + 0x88);
  local_88 = 0.0;
  if ((_DAT_004bd14c <= local_8c * local_8c) || (_DAT_004bd14c <= local_84 * local_84)) {
    if (*(float *)(iVar3 + 0xac) <= _DAT_004bd150) {
      local_bc = 1.0;
    }
    else {
      fVar13 = dot_product_vec3(&local_b8,&local_80);
      fVar13 = fVar13 * (float10)*(float *)(iVar3 + 0xb0);
      local_bc = (float)((float10)_DAT_004bd134 - fVar13 * fVar13 * (float10)_DAT_004bd154);
    }
    if (local_bc <= _DAT_004bd134) {
      if (local_bc < _DAT_004bd158) {
        local_bc = 0.25;
      }
    }
    else {
      local_bc = 1.0;
    }
    local_90 = *(float *)(iVar3 + 0x3c);
    if (((local_90 == 0.0) ||
        (iVar4 = is_vehicle_or_weapon_source_world_object((int)local_90), iVar4 == 0)) ||
       (*(int *)((int)local_90 + 0x6c) == 7)) {
      fVar12 = local_80;
      fVar11 = local_7c;
      fVar9 = local_78;
      fVar13 = dot_product_vec3(&local_80,&local_b8);
      pfVar5 = (float *)vec3_madd_xyz(&local_d4,local_b8,local_b4,local_b0,
                                      (float)(fVar13 * (float10)_DAT_004bd164),fVar12,fVar11,fVar9);
      local_c8 = local_bc * *pfVar5;
      local_c4 = local_bc * pfVar5[1];
      local_c0 = local_bc * pfVar5[2];
      local_b8 = local_c8;
      local_b4 = local_c4;
      local_b0 = local_c0;
      fVar13 = dot_product_vec3(&local_b8,&local_b8);
      if (fVar13 <= (float10)_DAT_004bd15c) {
        if ((*(int *)(iVar3 + 0x3c) != 0) ||
           (((*(byte *)(iVar3 + 0x454) & 4) == 0 && (_DAT_004bd148 < param_1[10])))) {
          local_d4 = local_80 * _DAT_004bd160;
          local_d0 = local_7c * _DAT_004bd160;
          local_cc = local_78 * _DAT_004bd160;
          local_b8 = local_d4;
          local_b4 = local_d0;
          local_b0 = local_cc;
        }
      }
      else if (*(int *)(iVar3 + 0x3c) == 0) {
        play_positional_audio_for_object_or_active_player
                  (s_vtcoll_wav_004f1638,(int)param_1,(undefined4 *)0x0);
        apply_radial_damage_and_impulse_to_target
                  (param_1,0,(float *)(iVar3 + 0x8c),&local_80,(float *)(iVar3 + 0x80));
      }
      if (_DAT_004bd134 < local_b4) {
        local_b4 = local_b4 * _DAT_004bd168;
      }
      pfVar5 = (float *)mat3_transform_vec3(&local_d4,&local_80,param_1 + 6);
      local_9c = *pfVar5;
      local_98 = pfVar5[1];
      local_94 = pfVar5[2];
      pfVar5 = (float *)vec3_cross_product(&local_d4,&local_9c,&local_8c);
      local_c0 = *(float *)(iVar3 + 0xac) * _DAT_004bd16c;
      fVar12 = *pfVar5 * local_c0;
      local_c4 = pfVar5[1] * local_c0;
      local_c0 = pfVar5[2] * local_c0;
      local_c8 = fVar12;
      local_a8 = local_c4;
      local_a4 = local_c0;
    }
    else if (((uint)param_1[4] & 0x20) == 0) {
      local_90 = *(float *)(iVar3 + 0x40);
      local_bc = *(float *)(iVar3 + 0xa4);
      local_9c = *(float *)(iVar3 + 0x58);
      local_98 = *(float *)(iVar3 + 0x5c);
      local_94 = *(float *)(iVar3 + 0x60);
      pfVar5 = (float *)blend_two_vec3_weighted
                                  (&local_d4,local_bc,local_b8,local_b4,local_b0,local_90,
                                   *(float *)(iVar3 + 0x58),*(float *)(iVar3 + 0x5c),
                                   *(float *)(iVar3 + 0x60));
      local_c0 = _DAT_004bd134 / (local_90 + local_bc);
      fVar12 = *pfVar5 * local_c0;
      local_c4 = pfVar5[1] * local_c0;
      local_c0 = pfVar5[2] * local_c0;
      local_c8 = fVar12;
      pfVar5 = (float *)vec3_subtract_xyz(&local_d4,local_b8,local_b4,local_b0,fVar12,local_c4,
                                          local_c0);
      local_b8 = *pfVar5;
      local_b4 = pfVar5[1];
      local_b0 = pfVar5[2];
      fVar11 = local_80;
      fVar9 = local_7c;
      fVar14 = local_78;
      fVar13 = dot_product_vec3(&local_80,&local_b8);
      pfVar5 = (float *)blend_two_vec3_weighted
                                  (&local_d4,0.5,local_b8,local_b4,local_b0,(float)-fVar13,fVar11,
                                   fVar9,fVar14);
      local_b8 = *pfVar5;
      local_b4 = pfVar5[1];
      local_b0 = pfVar5[2];
      fVar13 = dot_product_vec3(&local_b8,&local_b8);
      if (fVar13 < (float10)_DAT_004bd15c) {
        local_d4 = local_80 * _DAT_004bd160;
        local_d0 = local_7c * _DAT_004bd160;
        local_cc = local_78 * _DAT_004bd160;
        local_b8 = local_d4;
        local_b4 = local_d0;
        local_b0 = local_cc;
      }
      pfVar5 = (float *)add_vec3_components(&local_d4,local_b8,local_b4,local_b0,fVar12,local_c4,
                                            local_c0);
      local_b8 = *pfVar5;
      local_b4 = pfVar5[1];
      local_b0 = pfVar5[2];
      pfVar5 = (float *)mat3_transform_vec3(&local_d4,(float *)(iVar3 + 0x8c),param_1 + 6);
      local_9c = *pfVar5;
      local_98 = pfVar5[1];
      local_94 = pfVar5[2];
      pfVar5 = (float *)vec3_cross_product(&local_d4,&local_9c,&local_8c);
      local_c8 = *pfVar5;
      local_c4 = pfVar5[1];
      local_c0 = pfVar5[2];
      fVar13 = dot_product_vec3(&local_8c,&local_8c);
      fVar13 = (float10)_DAT_004bd134 / fVar13;
      fVar12 = (float)((float10)local_c8 * fVar13);
      local_c4 = (float)((float10)local_c4 * fVar13);
      local_c0 = (float)((float10)local_c0 * fVar13);
      local_c8 = fVar12;
      local_a8 = local_c4;
      local_a4 = local_c0;
    }
    if ((*(uint *)(iVar3 + 0x454) & 0x200) == 0) {
      pfVar5 = (float *)vec3_madd_xyz(&local_d4,*(float *)(iVar3 + 200),*(float *)(iVar3 + 0xcc),
                                      *(float *)(iVar3 + 0xd0),*(float *)(iVar3 + 0xb4),fVar12,
                                      local_a8,local_a4);
      local_ac = *pfVar5;
      local_a8 = pfVar5[1];
      local_a4 = pfVar5[2];
      if (local_ac <= _DAT_004bd170) {
        if (local_ac < _DAT_004bd174) {
          local_ac = _DAT_004bd174 / local_ac;
          local_c8 = *pfVar5 * local_ac;
          local_c4 = pfVar5[1] * local_ac;
          local_a4 = pfVar5[2] * local_ac;
          local_c0 = local_a4;
          local_ac = local_c8;
          local_a8 = local_c4;
        }
      }
      else {
        local_ac = _DAT_004bd170 / local_ac;
        local_c8 = *pfVar5 * local_ac;
        local_c4 = pfVar5[1] * local_ac;
        local_a4 = pfVar5[2] * local_ac;
        local_c0 = local_a4;
        local_ac = local_c8;
        local_a8 = local_c4;
      }
      fVar12 = _DAT_004bd178;
      if ((_DAT_004bd178 < local_a8) ||
         (fVar11 = local_a8, fVar12 = _DAT_004bd17c, local_a8 < _DAT_004bd17c)) {
        local_d0 = fVar12 / local_a8;
        local_ac = local_ac * local_d0;
        local_cc = local_a4 * local_d0;
        local_d0 = local_a8 * local_d0;
        fVar11 = local_d0;
        local_d4 = local_ac;
        local_a4 = local_cc;
      }
      if (local_a4 <= _DAT_004bd180) {
        fVar9 = local_ac;
        fVar12 = local_a4;
        if (local_a4 < _DAT_004bd184) {
          fVar12 = _DAT_004bd184 / local_a4;
          fVar9 = local_ac * fVar12;
          fVar11 = fVar11 * fVar12;
          fVar12 = local_a4 * fVar12;
          local_d4 = fVar9;
          local_d0 = fVar11;
          local_cc = fVar12;
        }
      }
      else {
        fVar14 = _DAT_004bd180 / local_a4;
        fVar11 = fVar11 * fVar14;
        fVar9 = local_ac * fVar14;
        fVar12 = local_a4 * fVar14;
        local_d4 = local_ac * fVar14;
        local_d0 = fVar11;
        local_cc = local_a4 * fVar14;
      }
      *(float *)(iVar3 + 200) = fVar9;
      *(float *)(iVar3 + 0xcc) = fVar11;
      *(float *)(iVar3 + 0xd0) = fVar12;
    }
    *(float *)(iVar3 + 0xbc) = local_b8;
    *(float *)(iVar3 + 0xc0) = local_b4;
    *(float *)(iVar3 + 0xc4) = local_b0;
    fVar13 = vec3_length(local_b8,local_b4,local_b0);
    fVar9 = _DAT_004bd150;
    fVar12 = (float)fVar13;
    *(float *)(iVar3 + 0xac) = fVar12;
    fVar11 = _DAT_004bd188;
    if (fVar9 < fVar12) {
      fVar11 = _DAT_004bd134 / fVar12;
    }
    *(float *)(iVar3 + 0xb0) = fVar11;
    local_bc = fVar12;
    set_tire_child_speed_scalar(*(int *)(iVar3 + 0x3ac),fVar12);
    set_tire_child_speed_scalar(*(int *)(iVar3 + 0x3a8),fVar12);
    set_tire_child_speed_scalar(*(int *)(iVar3 + 0x3bc),fVar12);
    set_tire_child_speed_scalar(*(int *)(iVar3 + 0x3b8),fVar12);
    if (*(int *)(iVar3 + 0x3b4) != 0) {
      set_tire_child_speed_scalar(*(int *)(iVar3 + 0x3b4),fVar12);
    }
    if (*(int *)(iVar3 + 0x3b0) != 0) {
      set_tire_child_speed_scalar(*(int *)(iVar3 + 0x3b0),fVar12);
    }
    pfVar5 = param_1 + 6;
    pfVar6 = (float *)copy_transform_position_vec3(&local_d4,(int)pfVar5);
    local_70 = *pfVar6;
    local_6c = pfVar6[1];
    local_68 = pfVar6[2];
    pfVar6 = (float *)vec3_madd_xyz(&local_d4,*pfVar6,pfVar6[1],pfVar6[2],param_2,local_b8,local_b4,
                                    local_b0);
    local_70 = *pfVar6;
    local_6c = pfVar6[1];
    local_68 = pfVar6[2];
    if (((((uint)param_1[4] & 0x20) == 0) && ((*(byte *)(iVar3 + 0x454) & 4) != 0)) &&
       (_DAT_004bd18c < *(float *)(iVar3 + 0x474) - local_6c)) {
      trigger_vehicle_forced_damage_or_actor_cleanup((int)param_1);
    }
    store_vec3_as_double_triplet((int)pfVar5,&local_70);
    pfVar6 = (float *)effect_target_list_scan_context_helper_004389f0
                                (local_40,pfVar5,*(float *)(iVar3 + 200),*(float *)(iVar3 + 0xcc),
                                 *(float *)(iVar3 + 0xd0),param_2);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar5 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar5 = pfVar5 + 1;
    }
    initialize_vehicle_wheel_contact_state_block((undefined4 *)(iVar3 + 0x38));
    update_rear_tire_skid_fx_contact_state((int)param_1,*(uint *)(iVar3 + 0x454),1);
  }
LAB_00439b4d:
  effect_target_scan_target_query_helper_00436ff0((int)param_1);
  iVar3 = get_vehicle_runtime_context((int)param_1);
  if ((*(uint *)(iVar3 + 0x454) & 0x8020) != 0) {
    *(undefined4 *)(iVar3 + 0xe4) = 0xbf800000;
  }
  fVar11 = param_1[0x1c];
  fVar13 = get_vehicle_suspension_response_scalar((int)fVar11);
  fVar12 = (float)(fVar13 * (float10)_DAT_004bd184);
  local_64 = fVar12;
  world_object_geometry_context_helper_00458980(*(int *)((int)fVar11 + 0x3ac),fVar12);
  world_object_geometry_context_helper_00458980(*(int *)((int)fVar11 + 0x3a8),fVar12);
  local_58 = *(float *)(iVar3 + 0x3a8);
  local_54 = *(float *)(iVar3 + 0x3ac);
  local_60 = *(float *)(iVar3 + 0x3bc);
  local_64 = *(float *)(iVar3 + 0x3b0);
  local_5c = *(float *)(iVar3 + 0x3b8);
  fVar12 = *(float *)(iVar3 + 0x3b4);
  local_90 = fVar12;
  solve_vehicle_wheel_contact_suspension_solver
            (param_1,&local_74,(float *)(iVar3 + 0xbc),&local_a0,&local_4c,(float *)(iVar3 + 200),
             param_1 + 6,param_2);
  *(float *)(iVar3 + 0xd4) = local_4c;
  *(undefined4 *)(iVar3 + 0xd8) = local_48;
  *(undefined4 *)(iVar3 + 0xdc) = local_44;
  fVar14 = _DAT_004bd150;
  fVar11 = ABS(local_a0);
  *(float *)(iVar3 + 0xac) = fVar11;
  fVar9 = _DAT_004bd188;
  if (fVar14 < fVar11) {
    fVar9 = _DAT_004bd134 / fVar11;
  }
  *(float *)(iVar3 + 0xb0) = fVar9;
  if ((local_74 & 4) == 0) {
    local_bc = *(float *)(iVar3 + 0x454);
    if (((uint)local_bc & 4) != 0) {
      if (((((uint)local_bc & 0x8020) == 0) &&
          ((float)_DAT_004bd190 < *(float *)(iVar3 + 0x474) - (float)*(double *)(param_1 + 0x12)))
         && (((uint)param_1[4] & 0x20) == 0)) {
        *(uint *)(iVar3 + 0x454) = local_74;
        trigger_vehicle_forced_damage_or_actor_cleanup((int)param_1);
        return;
      }
      local_70 = 0.0;
      local_6c = -0.2;
      local_68 = 0.0;
      dispatch_vehicle_runtime_sound_event(4,(int)param_1,(undefined4 *)0x0);
      local_bc = *(float *)(iVar3 + 0x454);
      if (((uint)local_bc & 0x8020) == 0) {
        local_9c = -*(float *)(iVar3 + 0xbc);
        local_98 = -*(float *)(iVar3 + 0xc0);
        local_94 = -*(float *)(iVar3 + 0xc4);
        local_8c = local_9c;
        local_88 = local_98;
        local_84 = local_94;
        apply_radial_damage_and_impulse_to_target
                  (param_1,0,&local_9c,(float *)(iVar3 + 0x460),&local_70);
        local_bc = *(float *)(iVar3 + 0x454);
        if (((uint)local_bc & 0x8020) != 0) {
          return;
        }
      }
    }
    *(uint *)(iVar3 + 0x454) = local_74;
    set_tire_child_speed_scalar((int)local_54,local_a0);
    set_tire_child_speed_scalar((int)local_58,local_a0);
    set_tire_child_speed_scalar((int)local_60,local_a0);
    set_tire_child_speed_scalar((int)local_5c,local_a0);
    if (fVar12 != 0.0) {
      set_tire_child_speed_scalar((int)fVar12,local_a0);
    }
    if (local_64 != 0.0) {
      set_tire_child_speed_scalar((int)local_64,local_a0);
    }
    local_70 = (float)*(double *)(param_1 + 0x10);
    local_98 = (float)*(double *)(param_1 + 0x12);
    local_68 = (float)*(double *)(param_1 + 0x14);
    if (param_1[10] < _DAT_004bd148) {
      fVar12 = *(float *)(iVar3 + 0x34);
      local_70 = fVar12 * param_1[9] + local_70;
      local_98 = fVar12 * param_1[10] + local_98;
      local_68 = fVar12 * param_1[0xb] + local_68;
    }
    fVar11 = local_70;
    fVar12 = local_98;
    local_9c = local_70;
    local_94 = local_68;
    uVar2 = lookup_terrain_material_index_at_world_xz((double)local_70,(double)local_68);
    *(uint *)(iVar3 + 0x45c) = CONCAT22(extraout_var,uVar2);
    probe_effect_target_surface_height_at_position
              ((double)CONCAT44(fVar12,fVar11),local_68,&local_50,(undefined4 *)(iVar3 + 0x460));
    *(float *)(iVar3 + 0x46c) =
         *(float *)(iVar3 + 0x464) * *(float *)(iVar3 + 0x464) * *(float *)(iVar3 + 0x464) *
         _DAT_004bd19c;
    if ((*(byte *)(iVar3 + 0x454) & 4) == 0) {
      *(float *)(iVar3 + 0x474) = local_50;
    }
    update_tire_suspension_visual_compression_state
              ((int)param_1,&local_4c,(uint)local_bc & 0x202,0,param_2);
    uVar10 = local_74 & 2;
    iVar4 = get_vehicle_runtime_context((int)param_1);
    if ((uVar10 == 0) || (((uint)local_bc & 0x8020) != 0)) {
      uVar7 = *(uint *)(iVar4 + 0x454) & 0xfffffffd;
    }
    else {
      uVar7 = *(uint *)(iVar4 + 0x454) | 2;
    }
    *(uint *)(iVar4 + 0x454) = uVar7;
    update_tire_contact_skid_fx_state(*(int *)(iVar4 + 0x3bc),uVar10);
    update_tire_contact_skid_fx_state(*(int *)(iVar4 + 0x3b8),uVar10);
    if ((_DAT_004bd1a0 < local_a0) && (((uint)param_1[4] & 0x20) == 0)) {
      fVar13 = get_terrain_material_integer_scalar(*(int *)(iVar3 + 0x45c));
      apply_random_underbody_or_speed_damage((int)param_1,(float)(fVar13 * (float10)param_2));
    }
    bVar1 = _DAT_004bd148 <= *(float *)(iVar3 + 0xe8);
    iVar4 = *(int *)(*(int *)(iVar3 + 0x3c4) + 0x70);
    iVar8 = get_vehicle_drivetrain_mode_state((int)param_1);
  }
  else {
    if ((local_74 & 2) != 0) {
      iVar4 = get_vehicle_runtime_context((int)param_1);
      *(uint *)(iVar4 + 0x454) = *(uint *)(iVar4 + 0x454) & 0xfffffffd;
      update_tire_contact_skid_fx_state(*(int *)(iVar4 + 0x3bc),0);
      update_tire_contact_skid_fx_state(*(int *)(iVar4 + 0x3b8),0);
    }
    uVar10 = local_74 & 2;
    local_bc = *(float *)(iVar3 + 0x454);
    iVar4 = get_vehicle_runtime_context((int)param_1);
    if ((uVar10 == 0) || (((uint)local_bc & 0x8020) != 0)) {
      uVar7 = *(uint *)(iVar4 + 0x454) & 0xfffffffd;
    }
    else {
      uVar7 = *(uint *)(iVar4 + 0x454) | 2;
    }
    *(uint *)(iVar4 + 0x454) = uVar7;
    update_tire_contact_skid_fx_state(*(int *)(iVar4 + 0x3bc),uVar10);
    update_tire_contact_skid_fx_state(*(int *)(iVar4 + 0x3b8),uVar10);
    *(uint *)(iVar3 + 0x454) = local_74;
    update_tire_contact_height_and_compression_state(local_54,1,0.0,param_2,0.0);
    update_tire_contact_height_and_compression_state(local_58,1,0.0,param_2,0.0);
    update_tire_contact_height_and_compression_state(local_60,1,0.0,param_2,0.0);
    update_tire_contact_height_and_compression_state(local_5c,1,0.0,param_2,0.0);
    if (local_90 != 0.0) {
      update_tire_contact_height_and_compression_state(local_90,1,0.0,param_2,0.0);
    }
    if (local_64 != 0.0) {
      update_tire_contact_height_and_compression_state(local_64,1,0.0,param_2,0.0);
    }
    bVar1 = _DAT_004bd148 <= *(float *)(iVar3 + 0xe8);
    iVar4 = *(int *)(*(int *)(iVar3 + 0x3c4) + 0x70);
    iVar8 = get_vehicle_drivetrain_mode_state((int)param_1);
    local_74 = *(uint *)(iVar3 + 0x454);
    local_a0 = *(float *)(iVar3 + 0xac);
  }
  update_engine_gear_rpm_torque_state
            (iVar4,*(float *)(iVar3 + 0xe4),local_a0,local_74,(uint)!bVar1,iVar8);
  return;
}


