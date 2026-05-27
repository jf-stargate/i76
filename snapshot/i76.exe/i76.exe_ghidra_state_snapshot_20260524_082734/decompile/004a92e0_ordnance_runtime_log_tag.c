/*
 * Program: i76.exe
 * Function: ordnance_runtime_log_tag
 * Entry: 004a92e0
 * Signature: bool __cdecl ordnance_runtime_log_tag(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

bool __cdecl ordnance_runtime_log_tag(int param_1,float param_2)

{
  bool bVar1;
  int *piVar2;
  float *pfVar3;
  undefined3 extraout_var;
  undefined4 *puVar4;
  int iVar5;
  float *pfVar6;
  float fVar7;
  float fVar8;
  int *piVar9;
  float fVar10;
  undefined4 *puVar11;
  float10 fVar12;
  float fVar13;
  float fVar14;
  float local_20c;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float *local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  int local_1cc;
  float *local_1c8;
  int local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  int local_1b4;
  LPVOID local_1b0;
  int local_1ac;
  int local_1a8;
  int local_1a4;
  float local_194;
  float local_190;
  float local_18c;
  float local_17c [3];
  float local_170;
  float local_16c;
  float local_168;
  int local_154;
  float local_150;
  float local_14c;
  int local_138;
  float local_134;
  float local_130;
  float local_12c;
  int local_128;
  int local_124;
  float *local_120;
  float local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110 [15];
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
  float local_ac [3];
  float local_a0 [3];
  float local_94 [3];
  float local_88 [3];
  float local_7c [31];
  
  local_128 = *(int *)(param_1 + 0x70);
  local_120 = (float *)(local_128 + 0x14);
  pfVar6 = (float *)(local_128 + 0x2c);
  local_1c8 = pfVar6;
  piVar2 = (int *)build_vehicle_ordnance_runtime_context(local_7c,param_1);
  piVar9 = &local_1b4;
  for (iVar5 = 0x1f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar9 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar9 = piVar9 + 1;
  }
  local_1c4 = 0;
  if (_DAT_004bebd0 <= local_168 * local_168 + local_16c * local_16c + local_170 * local_170) {
    local_1e4 = (float *)(param_1 + 0x18);
    transform_vec3_array_by_matrix(local_7c,(float *)&DAT_004feee0,8,local_1e4);
    local_1cc = 0;
    local_1e8 = 0.0;
    do {
      fVar8 = local_1e8;
      pfVar6 = (float *)effect_target_list_scan_context_helper_00438810
                                  (local_a0,*(float *)((int)&DAT_004feee0 + (int)local_1e8),
                                   *(float *)((int)&DAT_004feee4 + (int)local_1e8),
                                   *(float *)((int)&DAT_004feee8 + (int)local_1e8),param_1);
      fVar7 = *pfVar6;
      fVar13 = pfVar6[1];
      fVar14 = pfVar6[2];
      local_200 = fVar7;
      local_1fc = fVar13;
      local_1f8 = fVar14;
      if (((_DAT_004bebd4 <= fVar7 * fVar7) || (_DAT_004bebd4 <= fVar13 * fVar13)) ||
         (_DAT_004bebd4 <= fVar14 * fVar14)) {
        fVar12 = vec3_length(*pfVar6,pfVar6[1],pfVar6[2]);
        local_1d4 = (float)fVar12;
        pfVar6 = (float *)vec3_madd_xyz(local_88,*(float *)((int)local_7c + (int)fVar8),
                                        *(float *)((int)local_7c + (int)fVar8 + 4),
                                        *(float *)((int)local_7c + (int)fVar8 + 8),param_2,fVar7,
                                        fVar13,fVar14);
        local_1d8 = _DAT_004bebd0 / local_1d4;
        local_20c = *pfVar6;
        fVar7 = *(float *)((int)local_7c + (int)fVar8);
        fVar10 = *(float *)((int)local_7c + (int)fVar8 + 4);
        local_208 = pfVar6[1];
        fVar8 = *(float *)((int)local_7c + (int)fVar8 + 8);
        local_204 = pfVar6[2];
        local_1e0 = local_200 * local_1d8;
        local_1dc = fVar13 * local_1d8;
        local_1d8 = fVar14 * local_1d8;
        local_1f4 = fVar7;
        local_1f0 = fVar10;
        local_1ec = fVar8;
        local_124 = ftol();
        iVar5 = 0;
        if (-1 < local_124) {
          do {
            bVar1 = ordnance_projectile_state_context_helper_004aa0f0
                              ((double)local_1f4,(double)local_1ec);
            if (CONCAT31(extraout_var,bVar1) == 0) {
              local_1f0 = -1e-10;
              fVar10 = -1e-10;
            }
            probe_effect_target_surface_height_at_position
                      ((double)CONCAT44(fVar10,fVar7),fVar8,&local_11c,(undefined4 *)0x0);
            if (local_1f0 < local_11c) {
              local_118 = 1;
              local_114 = 0;
              effect_target_list_scan_context_helper_004382e0(local_110);
              local_1d0 = (float)(iVar5 + 1);
              local_d4 = ((float)(int)local_1d0 * _DAT_004bebe0) / local_1d4;
              local_d0 = (float)(&DAT_004feee0)[local_1cc * 3];
              local_cc = (float)(&DAT_004feee4)[local_1cc * 3];
              local_c8 = (float)(&DAT_004feee8)[local_1cc * 3];
              local_bc = -local_1d4;
              local_c4 = local_bc * local_1e0;
              local_c0 = local_1dc * local_bc;
              pfVar6 = local_ac;
              local_bc = local_1d8 * local_bc;
              goto LAB_004a9a04;
            }
            pfVar6 = (float *)vec3_madd_xyz(local_94,fVar7,fVar10,fVar8,5.0,local_1e0,local_1dc,
                                            local_1d8);
            fVar7 = *pfVar6;
            iVar5 = iVar5 + 1;
            fVar10 = pfVar6[1];
            fVar8 = pfVar6[2];
            local_1f4 = fVar7;
            local_1f0 = fVar10;
            local_1ec = fVar8;
          } while (iVar5 <= local_124);
        }
        probe_effect_target_surface_height_at_position
                  ((double)CONCAT44(local_208,local_20c),local_204,&local_1d0,(undefined4 *)0x0);
        fVar8 = local_1e8;
        if (local_208 < local_1d0) {
          local_118 = 1;
          local_114 = 0;
          effect_target_list_scan_context_helper_004382e0(local_110);
          local_d4 = param_2;
          local_bc = -local_1d4;
          local_c4 = local_bc * local_1e0;
          local_d0 = (float)(&DAT_004feee0)[local_1cc * 3];
          local_cc = (float)(&DAT_004feee4)[local_1cc * 3];
          local_c8 = (float)(&DAT_004feee8)[local_1cc * 3];
          local_c0 = local_1dc * local_bc;
          pfVar6 = &local_20c;
          local_bc = local_1d8 * local_bc;
LAB_004a9a04:
          local_200 = local_c4;
          local_1fc = local_c0;
          local_1f8 = local_bc;
          pfVar6 = (float *)sample_runtime_terrain_packed_word
                                      (pfVar6,(double)local_1f4,SUB84((double)local_1ec,0),
                                       (int)((ulonglong)(double)local_1ec >> 0x20));
          pfVar3 = local_1e4;
          local_134 = *pfVar6;
          local_130 = pfVar6[1];
          local_12c = pfVar6[2];
          local_1f4 = *local_1e4 * local_170 + local_1e4[6] * local_168 + local_1e4[3] * local_16c;
          local_1f0 = local_1e4[7] * local_168 + local_1e4[4] * local_16c + local_1e4[1] * local_170
          ;
          local_1ec = local_1e4[8] * local_168 + local_1e4[5] * local_16c + local_1e4[2] * local_170
          ;
          fVar7 = (local_1f4 * local_134 + local_1ec * local_12c + local_1f0 * local_130) *
                  _DAT_004bebe4;
          local_1c0 = fVar7 * local_134 - local_1f4 * _DAT_004bebe8;
          local_1bc = fVar7 * local_130 - local_1f0 * _DAT_004bebe8;
          local_1b8 = fVar7 * local_12c - local_1ec * _DAT_004bebe8;
          fVar7 = *local_1e4 * local_c4 + local_1e4[2] * local_bc + local_1e4[1] * local_c0;
          pfVar6 = (float *)(_DAT_004bebec /
                            (local_c8 * local_c8 + local_cc * local_cc + local_d0 * local_d0));
          fVar13 = local_1e4[3] * local_c4 + local_1e4[5] * local_bc + local_1e4[4] * local_c0;
          fVar14 = local_1e4[8] * local_bc + local_1e4[7] * local_c0 + local_1e4[6] * local_c4;
          local_20c = fVar13 * local_c8 - fVar14 * local_cc;
          local_208 = fVar14 * local_d0 - fVar7 * local_c8;
          local_204 = fVar7 * local_cc - fVar13 * local_d0;
          local_200 = (float)pfVar6 * local_20c;
          local_1fc = local_208 * (float)pfVar6;
          local_1f8 = local_204 * (float)pfVar6;
          local_1e4 = pfVar6;
          local_170 = local_1f4;
          local_16c = local_1f0;
          local_168 = local_1ec;
          local_b8 = local_134;
          local_b4 = local_130;
          local_b0 = local_12c;
          pfVar6 = (float *)vec3_madd_xyz(local_ac,local_194,local_190,local_18c,param_2,local_1c0,
                                          local_1bc,local_1b8);
          local_194 = *pfVar6;
          local_190 = pfVar6[1];
          local_18c = pfVar6[2];
          if (local_1b8 * local_1b8 + local_1bc * local_1bc + local_1c0 * local_1c0 < _DAT_004bebd0)
          {
            play_positional_audio_for_object_or_active_player
                      (&DAT_006552f8 + local_1a4 * 0xd0,0,(undefined4 *)0x0);
            probe_effect_target_surface_height_at_position
                      ((double)CONCAT44(local_190,local_194),local_18c,&local_1d0,(undefined4 *)0x0)
            ;
            local_20c = 0.0;
            local_190 = local_1d0;
            local_208 = 0.0;
            local_204 = 0.0;
            local_170 = 0.0;
            local_16c = 0.0;
            local_168 = 0.0;
            local_1c4 = 1;
          }
          pfVar3 = (float *)mat3_transform_vec3(local_ac,&local_1c0,pfVar3);
          pfVar6 = local_1c8;
          local_170 = *pfVar3;
          local_16c = pfVar3[1];
          local_168 = pfVar3[2];
          pfVar3 = (float *)add_vec3_components(local_ac,*local_1c8,local_1c8[1],local_1c8[2],
                                                local_200,local_1fc,local_1f8);
          *pfVar6 = *pfVar3;
          pfVar6[1] = pfVar3[1];
          pfVar6[2] = pfVar3[2];
          pfVar6 = local_1c8;
          goto LAB_004a9ebb;
        }
      }
      pfVar6 = local_1e4;
      local_1e8 = (float)((int)fVar8 + 0xc);
      local_1cc = local_1cc + 1;
    } while ((int)local_1e8 < 0x60);
    local_20c = *local_1e4 * local_170 + local_1e4[3] * local_16c + local_1e4[6] * local_168;
    local_208 = local_1e4[1] * local_170 + local_1e4[4] * local_16c + local_1e4[7] * local_168;
    local_204 = local_1e4[8] * local_168 + local_1e4[2] * local_170 + local_1e4[5] * local_16c;
    local_170 = local_20c;
    local_16c = local_208;
    local_168 = local_204;
    effect_target_list_scan_context_helper_004383a0(&local_194,&local_170,local_17c,param_2);
    local_20c = *pfVar6 * local_170 + pfVar6[1] * local_16c + pfVar6[2] * local_168;
    local_208 = pfVar6[3] * local_170 + pfVar6[4] * local_16c + pfVar6[5] * local_168;
    local_204 = pfVar6[8] * local_168 + pfVar6[6] * local_170 + pfVar6[7] * local_16c;
    pfVar6 = local_1c8;
    local_170 = local_20c;
    local_16c = local_208;
    local_168 = local_204;
  }
  else {
    local_1c4 = 1;
    probe_effect_target_surface_height_at_position
              ((double)CONCAT44(local_190,local_194),local_18c,&local_1e8,(undefined4 *)0x0);
    local_190 = local_1e8;
    pfVar3 = (float *)sample_runtime_terrain_packed_word
                                (&local_20c,(double)local_194,SUB84((double)local_18c,0),
                                 (int)((ulonglong)(double)local_18c >> 0x20));
    local_134 = *pfVar3;
    local_130 = pfVar3[1];
    local_12c = pfVar3[2];
  }
LAB_004a9ebb:
  if (local_1c4 == 0) {
    local_208 = pfVar6[1];
    fVar7 = *pfVar6;
    fVar13 = pfVar6[2];
    pfVar6 = (float *)(param_1 + 0x18);
    store_vec3_as_double_triplet((int)pfVar6,&local_194);
    pfVar3 = (float *)effect_target_list_scan_context_helper_004389f0
                                (local_7c,pfVar6,fVar7,local_208,fVar13,param_2);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar6 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar6 = pfVar6 + 1;
    }
  }
  else {
    puVar4 = (undefined4 *)
             zone_satellite_map_context_helper_00494710
                       (&local_134,(float *)(param_1 + 0x30),local_7c);
    puVar11 = (undefined4 *)(param_1 + 0x18);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar11 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar11 = puVar11 + 1;
    }
    store_vec3_as_double_triplet(param_1 + 0x18,&local_194);
  }
  fVar8 = local_18c;
  fVar14 = local_190;
  fVar13 = local_194;
  *local_120 = local_170;
  local_120[1] = local_16c;
  local_120[2] = local_168;
  local_1e8 = 0.0;
  fVar7 = local_1e8;
  for (; local_1e8 = fVar7, local_194 = fVar13, local_18c = fVar8, 0 < local_154;
      local_154 = local_154 + -1) {
    local_190 = fVar14 - _DAT_004bebf4;
    iVar5 = local_1b4;
    if (_DAT_004bebf8 < local_14c - local_150) {
      iVar5 = 0;
    }
    iVar5 = scan_effect_targets_for_collision_response_b
                      (param_1,iVar5,&local_194,&local_1ac,&local_138);
    if (iVar5 != 0) {
      local_1e8 = 1.4013e-45;
    }
    fVar7 = local_1e8;
  }
  if (fVar7 != 0.0) {
    local_190 = fVar14;
    if (local_1b0 != (LPVOID)0x0) {
      finalize_released_world_object_after_damage(local_1b0,s_ordnc_004fe6f0);
      local_1b0 = (LPVOID)0x0;
      *(undefined4 *)(local_128 + 0x10) = 0;
    }
    spawn_mission_vehicle_effect_by_slot(param_1,&local_194,local_1ac,local_138);
    if ((local_1ac != 0) && (local_138 == 1)) {
      if (local_1a8 == 0xf) {
        fVar8 = 0.75;
        fVar14 = 2.0;
        fVar13 = 1.0;
      }
      else {
        if (local_1a8 != 0x10) goto LAB_004aa0de;
        fVar14 = 0.5;
        fVar8 = 0.5;
        fVar13 = 0.5;
      }
      apply_vehicle_local_impulse_response(local_1ac,&local_194,fVar13,fVar14,fVar8);
    }
  }
LAB_004aa0de:
  return fVar7 == 0.0;
}


