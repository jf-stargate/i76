/*
 * Program: i76.exe
 * Function: update_player_weapon_targeting_lock_and_reticle_state
 * Entry: 004a3760
 * Signature: undefined __stdcall update_player_weapon_targeting_lock_and_reticle_state(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player weapon HUD rename v25; confidence=medium_high] Pre-pass under local player
   weapon/HUD update. Computes target/lock/lead state, target transforms, reticle or aim feedback,
   and sound hooks for selected/active weapons. */

void update_player_weapon_targeting_lock_and_reticle_state(void)

{
  float fVar1;
  double dVar2;
  uint *puVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  float *pfVar9;
  float fVar10;
  LPVOID pvVar11;
  int *piVar12;
  int iVar13;
  float *pfVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  char *pcVar18;
  float local_2cc;
  float local_2c8;
  float local_2c0;
  float local_2bc;
  float local_2b8;
  float local_2b4;
  int local_2b0;
  uint *local_2ac;
  float local_2a8;
  float local_2a4;
  float local_2a0;
  float local_29c;
  float local_298;
  float local_294;
  undefined8 local_290;
  int local_288;
  float local_284;
  float local_280 [4];
  float fStack_270;
  float fStack_26c;
  float local_268;
  float fStack_264;
  float local_260;
  double local_258;
  double local_250;
  double local_248;
  float local_240;
  uint local_23c;
  undefined4 uStack_238;
  int local_234;
  undefined4 local_230;
  float local_22c;
  float local_228;
  float local_224;
  float local_220;
  float local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  undefined4 local_208;
  float local_204 [3];
  undefined4 local_1f8 [3];
  float local_1ec [3];
  float local_1e0 [3];
  float local_1d4 [3];
  float local_1c8 [10];
  double local_1a0;
  double local_198;
  double local_190;
  float local_188 [16];
  float local_148 [16];
  float local_108 [16];
  float afStack_c8 [16];
  float local_88 [16];
  float local_48 [17];
  
  fVar15 = get_runtime_frame_delta_seconds();
  local_240 = (float)fVar15;
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 != (int *)0x0) {
    iVar5 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar12 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar12 == *piVar4) goto LAB_004a37aa;
        iVar5 = iVar5 + 1;
        piVar12 = piVar12 + 0xb2;
      } while (iVar5 < g_loaded_vehicle_runtime_count);
    }
    iVar5 = -1;
LAB_004a37aa:
    if ((iVar5 != -1) && (iVar5 < g_loaded_vehicle_runtime_count)) {
      local_2ac = &g_loaded_vehicle_runtime_table + iVar5 * 0xb2;
      goto LAB_004a37c8;
    }
  }
  local_2ac = (uint *)0x0;
LAB_004a37c8:
  if ((local_2ac != (uint *)0x0) && (local_288 = 0, 0 < g_weapon_runtime_slot_count)) {
    piVar4 = &DAT_005aab10;
    do {
      puVar3 = local_2ac;
      iVar5 = piVar4[10];
      piVar12 = (int *)piVar4[4];
      iVar13 = *piVar4;
      if (piVar12[piVar4[5] * 0x16 + 0x19] == 3) {
        uVar6 = get_primary_vehicle_weapon_target_object(*piVar12);
        piVar4[0xb] = 0;
        piVar4[0xc] = 0;
        iVar7 = is_damage_side_effects_suppressed();
        fVar10 = _DAT_004beac0;
        if (iVar7 == 0) {
          local_23c = piVar4[1];
          local_234 = *(int *)(&DAT_005d893c + iVar5 * 0xd8);
          uStack_238 = 0;
          local_230 = 0;
          fVar10 = (float)local_23c / (float)local_234;
        }
        iVar7 = 0;
        local_290 = (double)CONCAT44(local_290._4_4_,1);
        if (((&DAT_005d8934)[iVar5 * 0x36] == 3) && ((&DAT_005d8930)[iVar5 * 0x36] == 3)) {
          local_290 = (double)((ulonglong)local_290._4_4_ << 0x20);
        }
        fVar1 = *(float *)(&DAT_005d894c + iVar5 * 0xd8);
        local_2b4 = fVar10 * _DAT_004beac4 - _DAT_004beac8;
        local_2b0 = *(int *)piVar4[4];
        do {
          iVar5 = *(int *)(iVar13 + 100);
          if (iVar5 == 0) break;
          if (*(int *)(iVar5 + 0x6c) == 0x3f) {
            iVar7 = iVar7 + 1;
          }
          iVar13 = iVar5;
        } while (iVar7 < 3);
        if (((iVar7 < 3) || (iVar13 == 0)) || (local_2b0 == 0)) {
          fVar10 = 0.0;
        }
        else {
          if (uVar6 == 0) {
            local_2c0 = -*(float *)(*(int *)(iVar13 + 0x68) + 0x30);
            local_2bc = -*(float *)(iVar13 + 0x34);
            local_2b8 = *(float *)(*(int *)(iVar13 + 0x68) + 0x38);
          }
          else {
            pfVar9 = (float *)compute_transform_relative_to_ancestor(local_188,iVar13,0);
            pfVar14 = local_280;
            for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar14 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              pfVar14 = pfVar14 + 1;
            }
            pfVar9 = (float *)copy_object_local_translation_vec3(local_1f8,(int)local_280);
            local_2a8 = fVar1 * *pfVar9;
            local_2a4 = fVar1 * pfVar9[1];
            local_2a0 = fVar1 * pfVar9[2];
            local_29c = local_2a8;
            local_298 = local_2a4;
            local_294 = local_2a0;
            iVar5 = get_vehicle_runtime_context(local_2b0);
            pfVar9 = (float *)add_vec3_components(local_1e0,local_29c,local_298,local_294,
                                                  *(float *)(iVar5 + 0xbc),*(float *)(iVar5 + 0xc0),
                                                  *(float *)(iVar5 + 0xc4));
            local_29c = *pfVar9;
            local_298 = pfVar9[1];
            local_294 = pfVar9[2];
            pfVar9 = (float *)copy_transform_position_vec3(local_1d4,(int)(uVar6 + 0x18));
            local_220 = *pfVar9;
            local_21c = pfVar9[1];
            local_218 = pfVar9[2];
            pfVar9 = (float *)copy_transform_position_vec3(local_1ec,(int)local_280);
            local_22c = *pfVar9;
            local_228 = pfVar9[1];
            local_224 = pfVar9[2];
            get_world_object_damage_or_target_vectors(uVar6,local_204,&local_208);
            fVar15 = compute_line_closest_approach_parameter
                               (&local_220,local_204,&local_22c,&local_29c);
            local_2cc = (float)fVar15;
            if ((float10)_DAT_004beab8 <= fVar15) {
              if ((float)_DAT_004bead0 < local_2cc) {
                local_2cc = 5.0;
              }
            }
            else {
              local_2cc = 0.0;
            }
            predict_world_object_position_at_time(uVar6,local_2cc,&local_214);
            pfVar9 = (float *)(uVar6 + 0x18);
            pfVar14 = local_1c8;
            for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar14 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              pfVar14 = pfVar14 + 1;
            }
            local_1a0 = (double)local_214;
            local_198 = (double)local_210;
            local_190 = (double)local_20c;
            pfVar9 = (float *)compose_matrix_or_transform_b(local_280,local_108);
            pfVar14 = local_280;
            for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar14 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              pfVar14 = pfVar14 + 1;
            }
            pfVar9 = compose_matrix_or_transform_a(local_88,local_1c8,local_280);
            pfVar14 = local_280;
            for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar14 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              pfVar14 = pfVar14 + 1;
            }
            puVar8 = get_active_world_object_entry_object(uVar6);
            if (puVar8 == (undefined4 *)0x0) {
              local_2c0 = (float)local_258;
              local_2bc = (float)local_250;
              local_2b8 = (float)local_248;
            }
            else {
              transform_vec3_array_by_matrix(&local_2c0,(float *)(puVar8 + 1),1,local_280);
            }
            fVar15 = dot_product_vec3(&local_2c0,&local_2c0);
            fVar15 = zone_satellite_map_context_helper_00495000
                               (SUB84((double)fVar15,0),(uint)((ulonglong)(double)fVar15 >> 0x20));
            local_2c0 = (float)((float10)local_2c0 * fVar15);
            local_2bc = (float)((float10)local_2bc * fVar15);
            local_2b8 = (float)((float10)local_2b8 * fVar15);
          }
          if (*(int *)(local_2b0 + 0x6c) == 9) {
            fVar15 = get_runtime_frame_delta_seconds();
            fVar15 = fVar15 * (float10)local_2b4 * (float10)_DAT_004beadc;
          }
          else {
            fVar15 = get_runtime_frame_delta_seconds();
            fVar15 = fVar15 * (float10)local_2b4 * (float10)_DAT_004beae0;
          }
          local_2cc = local_2b8 * local_2b8 + local_2c0 * local_2c0;
          if (_DAT_004beae4 < local_2cc) {
            fVar17 = (float10)fpatan((float10)local_2c0,(float10)local_2b8);
            local_2cc = (float)fVar17;
          }
          local_2b4 = 0.0;
          if (local_2cc == _DAT_004beab8) {
            fVar17 = (float10)_DAT_004beab8;
          }
          else if (local_2cc <= _DAT_004beab8) {
            fVar17 = (float10)_DAT_004beae8;
          }
          else {
            fVar17 = (float10)_DAT_004beac0;
          }
          fVar17 = fVar17 * (float10)(float)fVar15;
          if (((float10)local_2cc - fVar17) * (float10)local_2cc < (float10)_DAT_004beab8) {
            fVar17 = (float10)local_2cc;
          }
          fVar16 = (float10)fsin(fVar17);
          iVar5 = *(int *)(iVar13 + 0x68);
          pfVar9 = (float *)&DAT_004faed8;
          pfVar14 = local_280;
          for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
            *pfVar14 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar14 = pfVar14 + 1;
          }
          fVar17 = (float10)fcos(fVar17);
          local_280[0] = (float)fVar17;
          local_280[2] = (float)-fVar16;
          local_268 = (float)fVar16;
          local_260 = local_280[0];
          pfVar9 = compose_matrix_or_transform_a(local_148,local_280,(float *)(iVar5 + 0x18));
          pfVar14 = (float *)(iVar5 + 0x18);
          for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
            *pfVar14 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar14 = pfVar14 + 1;
          }
          local_284 = *(float *)(iVar5 + 0x18);
          dVar2 = (double)(*(float *)(iVar5 + 0x20) * *(float *)(iVar5 + 0x20) +
                          local_284 * local_284);
          fVar17 = zone_satellite_map_context_helper_00495000
                             (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
          if ((float10)_DAT_004beaf0 < fVar17) {
            *(float *)(iVar5 + 0x18) = (float)(fVar17 * (float10)*(float *)(iVar5 + 0x18));
            *(float *)(iVar5 + 0x20) = (float)(fVar17 * (float10)*(float *)(iVar5 + 0x20));
            *(float *)(iVar5 + 0x30) = (float)(fVar17 * (float10)*(float *)(iVar5 + 0x30));
            *(float *)(iVar5 + 0x38) = (float)(fVar17 * (float10)*(float *)(iVar5 + 0x38));
          }
          if (((int)local_290 != 1) ||
             (local_290 = (double)ABS(local_2cc), (float)_DAT_004beaf8 <= ABS(local_2cc))) {
            if (ABS(local_2cc) < (float)_DAT_004beb08) {
              local_2b4 = 1.4013e-45;
            }
          }
          else {
            fVar17 = (float10)_CIasin();
            fVar10 = (float)fVar17;
            local_2c8 = _DAT_004beab8;
            if ((fVar17 != (float10)_DAT_004beab8) &&
               (local_2c8 = _DAT_004beae8, _DAT_004beab8 < fVar10)) {
              local_2c8 = _DAT_004beac0;
            }
            local_2c8 = (float)fVar15 * local_2c8;
            if ((fVar10 - local_2c8) * fVar10 < _DAT_004beab8) {
              local_2c8 = fVar10;
            }
            fVar15 = (float10)fsin((float10)local_2c8);
            iVar5 = *(int *)(iVar5 + 100);
            pfVar9 = (float *)&DAT_004faed8;
            pfVar14 = local_280;
            for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
              *pfVar14 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              pfVar14 = pfVar14 + 1;
            }
            fVar17 = (float10)fcos((float10)local_2c8);
            local_260 = (float)fVar17;
            fStack_270 = (float)fVar17;
            fStack_26c = (float)-fVar15;
            fStack_264 = (float)fVar15;
            pfVar9 = compose_matrix_or_transform_a(afStack_c8,local_280,(float *)(iVar5 + 0x18));
            pfVar14 = local_280;
            for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
              *pfVar14 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              pfVar14 = pfVar14 + 1;
            }
            if (ABS(fStack_26c) < (float)_DAT_004beb00) {
              dVar2 = (double)(local_260 * local_260 + fStack_264 * fStack_264);
              fVar15 = zone_satellite_map_context_helper_00495000
                                 (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
              if ((float10)_DAT_004beaf0 < fVar15) {
                fStack_270 = (float)((float10)fStack_270 * fVar15);
                fStack_26c = (float)((float10)fStack_26c * fVar15);
                fStack_264 = (float)((float10)fStack_264 * fVar15);
                local_260 = (float)((float10)local_260 * fVar15);
              }
              pfVar9 = local_280;
              pfVar14 = (float *)(iVar5 + 0x18);
              for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
                *pfVar14 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar14 = pfVar14 + 1;
              }
            }
            if ((ABS(fVar10) < (float)_DAT_004beb08) && (local_290 < _DAT_004beb08)) {
              local_2b4 = 1.4013e-45;
            }
          }
          pfVar9 = (float *)compute_transform_relative_to_ancestor(local_48,iVar5,0);
          pfVar14 = local_280;
          for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pfVar14 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar14 = pfVar14 + 1;
          }
          set_vehicle_weapon_target_transform(local_2b0,local_280);
          fVar10 = local_2b4;
        }
        if (fVar10 == 1.4013e-45) {
          piVar4[0xb] = 1;
          piVar4[0xc] = 1;
        }
      }
      else {
        piVar4[0xb] = 1;
        piVar4[0xc] = 1;
        if (((&DAT_005d8934)[iVar5 * 0x36] == 4) && ((&DAT_005d8930)[iVar5 * 0x36] == 4)) {
          if (piVar4[0xf] == 4) {
            pvVar11 = (LPVOID)get_primary_vehicle_weapon_target_object(*piVar12);
          }
          else {
            pvVar11 = release_vehicle_radar_or_weapon_target_object(*piVar12,piVar4[0xf]);
          }
          if (pvVar11 != (LPVOID)0x0) {
            piVar4[0x10] = (int)(local_240 + (float)piVar4[0x10]);
            if (((pvVar11 == (LPVOID)*puVar3) &&
                (iVar13 = weapon_selection_contains_slot((int *)piVar4[4],piVar4[5]), iVar13 != 0))
               && (_DAT_004beabc <= (float)piVar4[0x10])) {
              play_named_sound_attached_to_object_or_player
                        (s_msllock3_wav_004fee50,g_player_weapon_hud_world_object,(undefined4 *)0x0)
              ;
            }
            if (((puVar3 == (uint *)piVar4[4]) &&
                (iVar13 = weapon_selection_contains_slot((int *)piVar4[4],piVar4[5]), iVar13 != 0))
               && (piVar4[6] != 0)) {
              if ((float)piVar4[0x10] < _DAT_004beabc) {
                pcVar18 = s_msllock1_wav_004fee30;
              }
              else {
                pcVar18 = s_msllock2_wav_004fee40;
              }
              play_named_sound_attached_to_object_or_player
                        (pcVar18,g_player_weapon_hud_world_object,(undefined4 *)0x0);
            }
            iVar13 = weapon_selection_contains_slot((int *)piVar4[4],piVar4[5]);
            if (iVar13 != 0) goto LAB_004a40cc;
          }
          piVar4[0x10] = 0;
        }
LAB_004a40cc:
        iVar13 = (&DAT_005d8934)[iVar5 * 0x36];
        if (((iVar13 == 1) || (iVar13 == 2)) ||
           ((iVar13 == 4 &&
            (((&DAT_005d8930)[iVar5 * 0x36] == 0 || ((&DAT_005d8930)[iVar5 * 0x36] == 5)))))) {
          pvVar11 = release_vehicle_radar_or_weapon_target_object(*(int *)piVar4[4],piVar4[0xf]);
          update_vehicle_weapon_mount_pitch_toward_target(piVar4[-1],(float)pvVar11);
        }
      }
      local_288 = local_288 + 1;
      piVar4 = piVar4 + 0x13;
    } while (local_288 < g_weapon_runtime_slot_count);
  }
  return;
}


