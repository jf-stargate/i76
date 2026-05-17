/*
 * Program: i76.exe
 * Function: update_weapon_cooldowns_ammo_and_fire_effects
 * Entry: 004a6470
 * Signature: undefined __stdcall update_weapon_cooldowns_ammo_and_fire_effects(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Per-frame weapon
   cooldown/ammo/fire loop: transitions, counters, delays, fire effects, and HUD/audio feedback. */

void update_weapon_cooldowns_ammo_and_fire_effects(void)

{
  float fVar1;
  int iVar2;
  float fVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  int *piVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  float10 fVar15;
  float *pfVar16;
  float local_2fc;
  int local_2f8;
  undefined4 *local_2f0;
  float local_2e8;
  int local_2e4;
  float local_2e0;
  float local_2dc;
  undefined4 local_2d8;
  undefined4 local_2d4;
  float local_2d0;
  undefined4 local_2cc;
  undefined4 local_2c8;
  float local_2c4;
  undefined4 local_2c0;
  undefined4 local_2bc;
  float local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  float local_2ac;
  undefined4 local_2a8;
  undefined4 local_2a4;
  float local_2a0;
  undefined4 local_29c;
  undefined4 local_298;
  float local_294;
  undefined4 local_290;
  undefined4 local_28c;
  float local_288;
  undefined4 local_284;
  undefined4 local_280;
  float local_27c;
  undefined4 local_278;
  undefined4 local_274;
  float local_270;
  undefined4 local_26c;
  undefined4 local_268;
  float local_264;
  undefined4 local_260;
  undefined4 local_25c;
  float local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c [3];
  undefined4 local_240 [6];
  float local_228;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_200 [6];
  float local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1c0 [6];
  float local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_180 [6];
  float local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_140 [6];
  float local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_100 [6];
  float local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  float local_c0 [16];
  float local_80 [16];
  float local_40 [16];
  
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 != (int *)0x0) {
    iVar5 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar10 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar10 == *piVar4) goto LAB_004a64aa;
        iVar5 = iVar5 + 1;
        piVar10 = piVar10 + 0xb2;
      } while (iVar5 < g_loaded_vehicle_runtime_count);
    }
    iVar5 = -1;
LAB_004a64aa:
    if ((iVar5 != -1) && (iVar5 < g_loaded_vehicle_runtime_count)) {
      local_2f0 = &g_loaded_vehicle_runtime_table + iVar5 * 0xb2;
      goto LAB_004a64ce;
    }
  }
  local_2f0 = (undefined4 *)0x0;
LAB_004a64ce:
  local_2e4 = 0;
  if (0 < g_weapon_runtime_slot_count) {
    do {
      local_2e8 = 0.0;
      iVar13 = local_2e4 * 0x4c;
      iVar2 = (&DAT_005aab38)[local_2e4 * 0x13];
      iVar5 = iVar2 * 0xd8;
      fVar15 = get_runtime_frame_delta_seconds();
      local_2fc = (float)fVar15;
      iVar6 = 0;
      local_2f8 = 0;
      piVar4 = (int *)((&DAT_005aab20)[local_2e4 * 0x13] + 0xa8);
      do {
        if (local_2e4 == *piVar4) {
          if (5 < iVar6) {
            iVar6 = 5;
          }
          goto LAB_004a6544;
        }
        iVar6 = iVar6 + 1;
        piVar4 = piVar4 + 0x16;
      } while (iVar6 < 7);
      iVar6 = -1;
LAB_004a6544:
      if ((local_2fc <= *(float *)(&DAT_005aab2c + iVar13)) ||
         (local_2fc <= *(float *)(&DAT_005aab30 + iVar13))) {
        if ((*(int *)(&DAT_005aab44 + iVar13) == 0) && (*(int *)(&DAT_005aab48 + iVar13) == 1)) {
          *(undefined4 *)(&DAT_005aab48 + iVar13) = 0;
        }
        else if ((*(int *)(&DAT_005aab44 + iVar13) == 1) && (*(int *)(&DAT_005aab48 + iVar13) == 0))
        {
          if ((local_2f0 == (undefined4 *)(&DAT_005aab20)[local_2e4 * 0x13]) &&
             (play_sound_if_object_tree_is_audible
                        (s_WCLICK_WAV_004feecc,g_player_weapon_hud_world_object,(undefined4 *)0x0),
             iVar6 != -1)) {
            iVar5 = (&DAT_005d8930)[iVar2 * 0x36];
            if (iVar5 < 100) {
              uVar8 = *(undefined4 *)
                       (&DAT_004fec80 + ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar5) * 4);
            }
            else {
              uVar8 = *(undefined4 *)
                       (s_3num_tens_1_004feaf0 + ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar5) * 4);
            }
            *(undefined4 *)(&DAT_004f2364 + iVar6 * 0x1c) = uVar8;
            *(undefined4 *)(&DAT_004f235c + iVar6 * 0x1c) = 1;
          }
          *(undefined4 *)(&DAT_005aab48 + iVar13) = 1;
        }
        fVar3 = _DAT_004beab8;
        *(undefined4 *)(&DAT_005aab44 + iVar13) = 0;
        if (fVar3 < *(float *)(&DAT_005aab2c + iVar13)) {
          *(float *)(&DAT_005aab2c + iVar13) = *(float *)(&DAT_005aab2c + iVar13) - local_2fc;
        }
        if (_DAT_004beab8 < *(float *)(&DAT_005aab30 + iVar13)) {
          *(float *)(&DAT_005aab30 + iVar13) = *(float *)(&DAT_005aab30 + iVar13) - local_2fc;
        }
      }
      else {
        if (_DAT_004beab8 < local_2fc) {
          do {
            iVar12 = local_2f8;
            fVar3 = _DAT_004beac0;
            if ((local_2fc <= *(float *)(&DAT_005aab2c + iVar13)) ||
               (local_2fc <= *(float *)(&DAT_005aab30 + iVar13))) break;
            if (*(float *)(&DAT_005aab2c + iVar13) <= _DAT_004beab8) {
              if (_DAT_004beab8 < *(float *)(&DAT_005aab30 + iVar13)) {
                local_2fc = local_2fc - *(float *)(&DAT_005aab30 + iVar13);
                if (_DAT_004beab8 <= local_2fc) {
                  *(undefined4 *)(&DAT_005aab30 + iVar13) = 0;
                }
                else {
                  *(float *)(&DAT_005aab30 + iVar13) = -local_2fc;
                  local_2fc = 0.0;
                }
                goto LAB_004a6623;
              }
              if (*(int *)(&DAT_005aab34 + iVar13) < 1) {
                if (*(int *)(&DAT_005aab44 + iVar13) == 1) {
                  if ((*(int *)(&DAT_005aab28 + iVar13) != 0) ||
                     ((DAT_005da798 != 0 &&
                      (iVar7 = is_damage_side_effects_suppressed(), iVar7 == 0)))) {
                    iVar7 = *(int *)(&DAT_005d8950 + iVar5);
                    *(int *)(&DAT_005aab34 + iVar13) = iVar7;
                    iVar7 = iVar7 + -1;
                    *(undefined4 *)(&DAT_005aab48 + iVar13) = 1;
                    *(int *)(&DAT_005aab34 + iVar13) = iVar7;
                    if ((*(int *)(&DAT_005aab28 + iVar13) < iVar7) &&
                       ((DAT_005da798 == 0 ||
                        (iVar7 = is_damage_side_effects_suppressed(), iVar7 != 0)))) {
                      *(undefined4 *)(&DAT_005aab34 + iVar13) =
                           *(undefined4 *)(&DAT_005aab28 + iVar13);
                    }
                    *(float *)(&DAT_005aab30 + iVar13) =
                         _DAT_004beac0 / *(float *)(&DAT_005d8948 + iVar5);
                    iVar7 = *(int *)(&DAT_005d8958 + iVar5);
                    if ((((iVar7 == 0xc) || (iVar7 == 0x11)) || (iVar7 == 0xe)) &&
                       (get_world_object_damage_or_target_vectors
                                  (*(int *)(&DAT_005aab20)[local_2e4 * 0x13],local_24c,&local_2e0),
                       local_2e0 < _DAT_004beb40)) {
                      *(float *)(&DAT_005aab30 + iVar13) =
                           (_DAT_004beac0 - *(float *)(&DAT_005aab30 + iVar13)) * _DAT_004beae8 *
                           _DAT_004beb44 * local_2e0 - _DAT_004beae8;
                    }
                    if (*(int *)(&DAT_005aab34 + iVar13) == 0) {
                      if (*(float *)(&DAT_005d8944 + iVar5) < *(float *)(&DAT_005aab30 + iVar13)) {
                        if (*(float *)(&DAT_005d8944 + iVar5) != _DAT_004beab8) goto LAB_004a6979;
                        *(undefined4 *)(&DAT_005aab2c + iVar13) =
                             *(undefined4 *)(&DAT_005aab30 + iVar13);
                      }
                      else {
                        *(undefined4 *)(&DAT_005aab2c + iVar13) =
                             *(undefined4 *)(&DAT_005d8944 + iVar5);
                      }
                      *(undefined4 *)(&DAT_005aab30 + iVar13) = 0;
                    }
LAB_004a6979:
                    iVar7 = local_2f8 + 1;
                    if ((*(int *)(&DAT_005d8958 + iVar5) != 1) &&
                       (*(int *)(&DAT_005d8958 + iVar5) != 0x12)) {
                      if ((iVar6 != -1) &&
                         (local_2f0 == (undefined4 *)(&DAT_005aab20)[local_2e4 * 0x13])) {
                        iVar7 = (&DAT_005d8930)[iVar2 * 0x36];
                        if (iVar7 < 100) {
                          uVar8 = *(undefined4 *)
                                   (&DAT_004fec84 + ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar7) * 4)
                          ;
                        }
                        else {
                          uVar8 = *(undefined4 *)
                                   (s_3num_tens_1_004feaf0 +
                                   ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar7) * 4 + 4);
                        }
                        iVar7 = iVar6 * 0x1c;
                        *(undefined4 *)(&DAT_004f2364 + iVar7) = uVar8;
                        uVar8 = ftol();
                        *(undefined4 *)(&DAT_004f236c + iVar7) = uVar8;
                        piVar4 = (int *)(&DAT_005aab20)[local_2e4 * 0x13];
                        *(undefined4 *)(&DAT_004f2358 + iVar7) = 1;
                        puVar9 = (undefined4 *)(*piVar4 + 0x18);
                        puVar14 = local_180;
                        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                          *puVar14 = *puVar9;
                          puVar9 = puVar9 + 1;
                          puVar14 = puVar14 + 1;
                        }
                        local_2dc = local_168;
                        local_288 = local_168;
                        local_2d8 = local_164;
                        local_284 = local_164;
                        local_2d4 = local_160;
                        local_280 = local_160;
                        puVar9 = (undefined4 *)
                                 compute_transform_relative_to_ancestor
                                           (local_80,(&DAT_005aab0c)[local_2e4 * 0x13],0);
                        puVar14 = local_100;
                        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                          *puVar14 = *puVar9;
                          puVar9 = puVar9 + 1;
                          puVar14 = puVar14 + 1;
                        }
                        local_2d0 = local_e8;
                        local_270 = local_e8;
                        pfVar16 = &local_270;
                        local_2cc = local_e4;
                        local_26c = local_e4;
                        local_2c8 = local_e0;
                        local_268 = local_e0;
                        pfVar11 = &local_288;
                        goto LAB_004a6ad6;
                      }
                      goto LAB_004a6b0a;
                    }
                    goto LAB_004a6b27;
                  }
                  puVar9 = (undefined4 *)(&DAT_005aab20)[local_2e4 * 0x13];
                  *(undefined4 *)(&DAT_005aab44 + iVar13) = 0;
                  *(undefined4 *)(&DAT_005aab2c + iVar13) = 0x3f800000;
                  *(undefined4 *)(&DAT_005aab48 + iVar13) = 1;
                  if ((local_2f0 == puVar9) &&
                     (play_sound_if_object_tree_is_audible
                                (s_WCLICK_WAV_004feecc,g_player_weapon_hud_world_object,
                                 (undefined4 *)0x0), iVar6 != -1)) {
                    iVar12 = (&DAT_005d8930)[iVar2 * 0x36];
                    if (iVar12 < 100) {
                      *(undefined4 *)(&DAT_004f2364 + iVar6 * 0x1c) =
                           *(undefined4 *)
                            (&DAT_004fec80 + ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar12) * 4);
                      *(undefined4 *)(&DAT_004f235c + iVar6 * 0x1c) = 1;
                    }
                    else {
                      *(undefined4 *)(&DAT_004f2364 + iVar6 * 0x1c) =
                           *(undefined4 *)
                            (s_3num_tens_1_004feaf0 +
                            ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar12) * 4);
                      *(undefined4 *)(&DAT_004f235c + iVar6 * 0x1c) = 1;
                    }
                  }
                }
                goto LAB_004a6b40;
              }
              iVar7 = *(int *)(&DAT_005aab34 + iVar13) + -1;
              *(int *)(&DAT_005aab34 + iVar13) = iVar7;
              fVar1 = *(float *)(&DAT_005d8948 + iVar5);
              *(float *)(&DAT_005aab30 + iVar13) = fVar3 / fVar1;
              if ((iVar7 == 0) && (fVar3 / fVar1 < *(float *)(&DAT_005d8944 + iVar5))) {
                uVar8 = *(undefined4 *)(&DAT_005d8944 + iVar5);
                *(undefined4 *)(&DAT_005aab30 + iVar13) = 0;
                *(undefined4 *)(&DAT_005aab2c + iVar13) = uVar8;
              }
              iVar7 = local_2f8 + 1;
              if ((*(int *)(&DAT_005d8958 + iVar5) != 1) &&
                 (*(int *)(&DAT_005d8958 + iVar5) != 0x12)) {
                if ((iVar6 != -1) && (local_2f0 == (undefined4 *)(&DAT_005aab20)[local_2e4 * 0x13]))
                {
                  iVar7 = (&DAT_005d8930)[iVar2 * 0x36];
                  if (iVar7 < 100) {
                    uVar8 = *(undefined4 *)
                             (&DAT_004fec84 + ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar7) * 4);
                  }
                  else {
                    uVar8 = *(undefined4 *)
                             (s_3num_tens_1_004feaf0 +
                             ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar7) * 4 + 4);
                  }
                  iVar7 = iVar6 * 0x1c;
                  *(undefined4 *)(&DAT_004f2364 + iVar7) = uVar8;
                  uVar8 = ftol();
                  *(undefined4 *)(&DAT_004f236c + iVar7) = uVar8;
                  piVar4 = (int *)(&DAT_005aab20)[local_2e4 * 0x13];
                  *(undefined4 *)(&DAT_004f2358 + iVar7) = 1;
                  puVar9 = (undefined4 *)(*piVar4 + 0x18);
                  puVar14 = local_140;
                  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                    *puVar14 = *puVar9;
                    puVar9 = puVar9 + 1;
                    puVar14 = puVar14 + 1;
                  }
                  local_2ac = local_128;
                  local_258 = local_128;
                  local_2a8 = local_124;
                  local_254 = local_124;
                  local_2a4 = local_120;
                  local_250 = local_120;
                  puVar9 = (undefined4 *)
                           compute_transform_relative_to_ancestor
                                     (local_c0,(&DAT_005aab0c)[local_2e4 * 0x13],0);
                  puVar14 = local_240;
                  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                    *puVar14 = *puVar9;
                    puVar9 = puVar9 + 1;
                    puVar14 = puVar14 + 1;
                  }
                  local_2c4 = local_228;
                  local_294 = local_228;
                  pfVar16 = &local_294;
                  local_2c0 = local_224;
                  local_290 = local_224;
                  local_2bc = local_220;
                  local_28c = local_220;
                  pfVar11 = &local_258;
LAB_004a6ad6:
                  fVar15 = compute_yaw_degrees_between_xz_vectors(pfVar11,pfVar16);
                  if ((&DAT_005d8934)[(&DAT_005aab38)[local_2e4 * 0x13] * 0x36] == 1) {
                    fVar15 = (float10)_DAT_004beab8;
                  }
                  *(float *)(&DAT_004f2368 + iVar6 * 0x1c) = (float)fVar15;
                }
LAB_004a6b0a:
                local_2f8 = local_2f8 + 1;
                fire_weapon_runtime_slot_and_spawn_effects
                          ((int)(&g_weapon_runtime_slot_table + local_2e4 * 0x13),
                           (int)(&DAT_005d88d8 + iVar2 * 0x36),local_2f8,local_2fc);
                iVar7 = iVar12;
              }
LAB_004a6b27:
              local_2f8 = iVar7;
              if (local_2e8 < local_2fc) {
                local_2e8 = local_2fc;
              }
            }
            else {
              local_2fc = local_2fc - *(float *)(&DAT_005aab2c + iVar13);
              if (_DAT_004beab8 <= local_2fc) {
                *(undefined4 *)(&DAT_005aab2c + iVar13) = 0;
              }
              else {
                *(float *)(&DAT_005aab2c + iVar13) = -local_2fc;
                local_2fc = 0.0;
              }
LAB_004a6623:
              if (local_2fc < _DAT_004beb38) {
LAB_004a6b40:
                local_2fc = 0.0;
              }
            }
          } while (_DAT_004beab8 < local_2fc);
        }
        *(undefined4 *)(&DAT_005aab44 + iVar13) = 0;
        if (local_2fc < *(float *)(&DAT_005aab2c + iVar13)) {
          if (_DAT_004beab8 < local_2fc) {
            *(float *)(&DAT_005aab2c + iVar13) = *(float *)(&DAT_005aab2c + iVar13) - local_2fc;
          }
          *(undefined4 *)(&DAT_005aab30 + iVar13) = 0;
          *(undefined4 *)(&DAT_005aab34 + iVar13) = 0;
        }
        if (local_2fc < *(float *)(&DAT_005aab30 + iVar13)) {
          if (_DAT_004beab8 < local_2fc) {
            *(float *)(&DAT_005aab30 + iVar13) = *(float *)(&DAT_005aab30 + iVar13) - local_2fc;
          }
          *(undefined4 *)(&DAT_005aab2c + iVar13) = 0;
        }
        if (0 < local_2f8) {
          if ((iVar6 != -1) && (local_2f0 == (undefined4 *)(&DAT_005aab20)[local_2e4 * 0x13])) {
            iVar12 = (&DAT_005d8930)[iVar2 * 0x36];
            if (iVar12 < 100) {
              uVar8 = *(undefined4 *)
                       (&DAT_004fec84 + ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar12) * 4);
            }
            else {
              uVar8 = *(undefined4 *)
                       (s_3num_tens_1_004feaf0 +
                       ((&DAT_005d8934)[iVar2 * 0x36] * 7 + iVar12) * 4 + 4);
            }
            iVar6 = iVar6 * 0x1c;
            *(undefined4 *)(&DAT_004f2364 + iVar6) = uVar8;
            uVar8 = ftol();
            *(undefined4 *)(&DAT_004f236c + iVar6) = uVar8;
            piVar4 = (int *)(&DAT_005aab20)[local_2e4 * 0x13];
            *(undefined4 *)(&DAT_004f2358 + iVar6) = 1;
            puVar9 = (undefined4 *)(*piVar4 + 0x18);
            puVar14 = local_200;
            for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
              *puVar14 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar14 = puVar14 + 1;
            }
            local_2b8 = local_1e8;
            local_264 = local_1e8;
            local_2b4 = local_1e4;
            local_260 = local_1e4;
            local_2b0 = local_1e0;
            local_25c = local_1e0;
            puVar9 = (undefined4 *)
                     compute_transform_relative_to_ancestor
                               (local_40,(&DAT_005aab0c)[local_2e4 * 0x13],0);
            puVar14 = local_1c0;
            for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
              *puVar14 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar14 = puVar14 + 1;
            }
            local_2a0 = local_1a8;
            local_27c = local_1a8;
            local_29c = local_1a4;
            local_278 = local_1a4;
            local_298 = local_1a0;
            local_274 = local_1a0;
            fVar15 = compute_yaw_degrees_between_xz_vectors(&local_264,&local_27c);
            if ((&DAT_005d8934)[(&DAT_005aab38)[local_2e4 * 0x13] * 0x36] == 1) {
              fVar15 = (float10)_DAT_004beab8;
            }
            *(float *)(&DAT_004f2368 + iVar6) = (float)fVar15;
          }
          fire_weapon_runtime_slot_and_spawn_effects
                    ((int)(&g_weapon_runtime_slot_table + local_2e4 * 0x13),
                     (int)(&DAT_005d88d8 + iVar2 * 0x36),local_2f8,local_2e8 * _DAT_004beb48);
          if ((*(int *)(&DAT_005aab34 + iVar13) == 0) &&
             (*(float *)(&DAT_005aab30 + iVar13) < *(float *)(&DAT_005d8944 + iVar5))) {
            uVar8 = *(undefined4 *)(&DAT_005d8944 + iVar5);
            *(undefined4 *)(&DAT_005aab30 + iVar13) = 0;
            *(undefined4 *)(&DAT_005aab2c + iVar13) = uVar8;
          }
        }
      }
      local_2e4 = local_2e4 + 1;
    } while (local_2e4 < g_weapon_runtime_slot_count);
  }
  return;
}


