/*
 * Program: i76.exe
 * Function: apply_network_vehicle_state_and_damage_update
 * Entry: 00464890
 * Signature: undefined __cdecl apply_network_vehicle_state_and_damage_update(uint param_1, undefined4 * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Applies a network vehicle state/damage packet, updates engine/tire state, death
   handling, and kill chat messages. */

void __cdecl apply_network_vehicle_state_and_damage_update(uint param_1,undefined4 *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  ushort uVar5;
  undefined4 *puVar6;
  uint *puVar7;
  undefined4 uVar8;
  char *_Format;
  undefined2 extraout_var;
  int iVar9;
  uint uVar10;
  byte *pbVar11;
  byte *pbVar12;
  int *piVar13;
  int iVar14;
  undefined4 *puVar15;
  uint uVar16;
  undefined8 in_stack_fffffed8;
  float in_stack_fffffee0;
  float in_stack_fffffee4;
  float in_stack_fffffee8;
  undefined2 in_stack_fffffeec;
  undefined2 in_stack_fffffeee;
  float in_stack_fffffef0;
  undefined2 in_stack_fffffef4;
  undefined2 in_stack_fffffef6;
  undefined2 in_stack_fffffef8;
  undefined2 uVar17;
  undefined2 in_stack_fffffefa;
  undefined2 uVar19;
  byte **ppbVar18;
  byte *local_f4;
  float local_f0;
  int local_ec;
  int *local_e8;
  int local_e4;
  int *local_e0;
  uint local_dc;
  int *local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  int local_c8;
  int local_c4;
  uchar local_c0 [24];
  uchar local_a8 [24];
  uchar local_90 [80];
  float local_40 [16];
  
  piVar13 = *(int **)(param_1 + 0x70);
  if ((*(byte *)(param_2 + 0x12) & 8) != 0) {
    uVar10 = piVar13[0x115];
    if (((uVar10 & 0x20) == 0) && ((uVar10 & 0x100000) != 0)) {
      return;
    }
    piVar13[0x115] = uVar10 & 0xffefffff;
  }
  puVar15 = (undefined4 *)&stack0xfffffed8;
  puVar6 = param_2;
  local_e0 = piVar13;
  for (iVar9 = 9; puVar6 = puVar6 + 1, iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar15 = *puVar6;
    puVar15 = puVar15 + 1;
  }
  puVar6 = (undefined4 *)
           runtime_library_string_or_memory_helper_004baee0
                     (local_40,in_stack_fffffed8,in_stack_fffffee0,in_stack_fffffee4,
                      in_stack_fffffee8,(float)CONCAT22(in_stack_fffffeee,in_stack_fffffeec),
                      in_stack_fffffef0,(float)CONCAT22(in_stack_fffffef6,in_stack_fffffef4),
                      (float)CONCAT22(in_stack_fffffefa,in_stack_fffffef8));
  puVar15 = (undefined4 *)(param_1 + 0x18);
  for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar15 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar15 = puVar15 + 1;
  }
  piVar13[0x2f] = param_2[10];
  piVar13[0x30] = param_2[0xb];
  piVar13[0x31] = param_2[0xc];
  piVar13[0x32] = param_2[0xd];
  piVar13[0x33] = param_2[0xe];
  piVar13[0x34] = param_2[0xf];
  fVar3 = _DAT_004be1fc;
  local_ec = piVar13[0xeb];
  local_d8 = piVar13 + 0xea;
  local_c8 = piVar13[0xef];
  local_c4 = *local_d8;
  local_e4 = piVar13[0xed];
  local_dc = piVar13[0xee];
  local_d4 = (float)param_2[10];
  local_e8 = (int *)piVar13[0xec];
  local_d0 = (float)param_2[0xb];
  local_cc = (float)param_2[0xc];
  fVar1 = SQRT(local_cc * local_cc + local_d0 * local_d0 + local_d4 * local_d4);
  piVar13[0x2b] = (int)fVar1;
  fVar2 = _DAT_004be200;
  if (fVar3 < fVar1) {
    fVar2 = _DAT_004be1a4 / fVar1;
  }
  uVar10 = piVar13[0x115];
  piVar13[0x2c] = (int)fVar2;
  piVar13[0x115] = 0;
  fVar1 = _DAT_004be1a4;
  if ((*(byte *)(param_2 + 0x12) & 4) != 0) {
    fVar1 = _DAT_004be1a0;
  }
  piVar13[0x3a] = (int)fVar1;
  piVar13[0x3c] = (uint)param_2[0x12] >> 1 & 1;
  local_f0 = (float)(uVar10 & 0x20);
  if (local_f0 == 0.0) {
    if ((*(byte *)(param_2 + 0x12) & 0x10) != 0) {
      piVar13[0x115] = 0x40;
    }
    if (((uVar10 ^ piVar13[0x115]) & 0x40) != 0) {
      piVar13[0x115] = piVar13[0x115] ^ 0x40;
      set_vehicle_current_damage_or_effect_object(param_1,1);
    }
  }
  if ((*(byte *)(param_2 + 0x12) & 1) != 0) {
    piVar13[0x115] = piVar13[0x115] | 2;
  }
  update_rear_tire_skid_fx_contact_state(param_1,uVar10,piVar13[0x115] & 2);
  if ((*(byte *)(param_2 + 0x12) & 0x20) != 0) {
    piVar13[0x115] = piVar13[0x115] | 1;
  }
  if ((param_2[0x12] & 0x800) != 0) {
    piVar13[0x115] = piVar13[0x115] | 0x200000;
    play_vehicle_engine_event_sound_attached(param_1);
  }
  if ((param_2[0x12] & 0x400) != 0) {
    piVar13[0x115] = piVar13[0x115] | 0x40000;
  }
  if ((param_2[0x12] & 0xc0000000) == 0xc0000000) {
    iVar9 = is_vehicle_or_actor_runtime_world_object(param_1);
    if (iVar9 != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x484) = 0x42c80000;
    }
  }
  else if ((param_2[0x12] & 0xc0000000) == 0x80000000) {
    iVar9 = is_vehicle_or_actor_runtime_world_object(param_1);
    if (iVar9 != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x484) = 0x42855555;
    }
  }
  else {
    iVar9 = is_vehicle_or_actor_runtime_world_object(param_1);
    if (iVar9 != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x484) = 0x42055555;
    }
  }
  uVar10 = piVar13[0x115] | uVar10 & 0x8000c120;
  piVar13[0x115] = uVar10;
  if (((*(byte *)(param_2 + 0x12) & 8) != 0) && (local_f0 == 0.0)) {
    piVar13[0x115] = uVar10 | 0x20;
    if ((*(byte *)(param_2 + 0x12) & 0x80) == 0) {
      apply_vehicle_catastrophic_damage_breakup(param_1,1);
    }
    else {
      piVar13[0x115] =
           CONCAT22((short)(uVar10 >> 0x10),CONCAT11((char)(uVar10 >> 8),(char)(uVar10 | 0x20))) |
           0x4000;
      iVar9 = *(int *)(param_1 + 0x70);
      *(undefined4 *)(iVar9 + 0x450) = 0x41200000;
      *(uint *)(iVar9 + 0x454) = *(uint *)(iVar9 + 0x454) | 0x80008000;
      play_cmike_voice_clip(param_1);
      iVar9 = world_object_has_optional_runtime_flag(param_1);
      if (iVar9 == 0) {
        load_gdf_resource_reference();
      }
      remove_loaded_vehicle_runtime_and_weapon_slots(param_1);
      mark_active_vehicle_damage_textures_dirty();
      dispatch_vehicle_runtime_sound_event(2,param_1,(undefined4 *)0x0);
      play_vehicle_engine_event_sound(param_1,1);
      get_world_object_class_id(param_1,0x200);
      iVar9 = get_active_player_or_camera_world_object_entry();
      if ((iVar9 != 0) &&
         (puVar7 = (uint *)get_active_player_or_camera_world_object_entry(), *puVar7 == param_1)) {
        clear_pending_input_action_code();
        uVar17 = 0xfefe;
        uVar19 = 0;
        uVar8 = get_active_player_or_camera_world_object_entry();
        dispatch_runtime_camera_mode_activation_by_id(uVar8,CONCAT22(uVar19,uVar17));
        weapon_hud_display_context_helper_004621b0();
        _DAT_0053679c = 8;
        iVar9 = is_damage_side_effects_suppressed();
        if (iVar9 != 0) {
          stamp_multiplayer_respawn_or_score_time();
        }
      }
    }
    sVar4 = get_local_multiplayer_player_id();
    if (*(short *)(param_2 + 0x16) == sVar4) {
      ppbVar18 = &local_f4;
      sVar4 = get_local_multiplayer_player_id();
      lookup_multiplayer_player_vehicle_config_id(sVar4,ppbVar18);
      lookup_multiplayer_player_vehicle_config_id((short)piVar13[0x120],&local_f0);
      if ((((uint)local_f0 ^ (uint)local_f4) & 0x70000) != 0) {
        multiplayer_score_spawn_context_helper_00454ff0((short)piVar13[0x120]);
      }
    }
    if ((param_2[0x12] & 0x200) == 0) {
      multiplayer_player_count_context_helper_00454620((short)piVar13[0x120],local_c0);
      if (*(short *)(param_2 + 0x16) == 0) {
        _Format = (char *)StrLookupFind();
        sprintf((char *)local_90,_Format);
      }
      else {
        multiplayer_player_count_context_helper_00454620(*(short *)(param_2 + 0x16),local_a8);
        StrLookupFormat();
      }
      draw_multiplayer_chat_message(0,local_90);
    }
  }
  if ((param_2[0x12] & 0x100) == 0) {
    if (*(int *)(param_1 + 0x6c) == 1) {
      *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x104) = 3;
    }
  }
  else if (*(int *)(param_1 + 0x6c) == 1) {
    *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x104) = 2;
  }
  if ((float)piVar13[0x3a] <= _g_float_zero) {
    local_f4 = (byte *)-(float)piVar13[0x2b];
  }
  else {
    local_f4 = (byte *)piVar13[0x2b];
  }
  pbVar12 = local_f4;
  update_engine_gear_rpm_torque_state
            (*(int *)(piVar13[0xf1] + 0x70),(float)piVar13[0x39],(float)local_f4,piVar13[0x115],
             (uint)((float)piVar13[0x3a] < _g_float_zero),*(int *)(*(int *)(param_1 + 0x70) + 0x104)
            );
  set_tire_child_speed_scalar(local_ec,pbVar12);
  set_tire_child_speed_scalar(local_c4,pbVar12);
  set_tire_child_speed_scalar(local_c8,pbVar12);
  set_tire_child_speed_scalar(local_dc,pbVar12);
  if (local_e4 != 0) {
    set_tire_child_speed_scalar(local_e4,pbVar12);
  }
  if (local_e8 != (int *)0x0) {
    set_tire_child_speed_scalar((int)local_e8,pbVar12);
  }
  piVar13[0x39] = param_2[0x10];
  piVar13[0x38] = param_2[0x11];
  update_vehicle_suspension_visual_tilt(param_1);
  uVar5 = *(ushort *)(param_2 + 0x15);
  if (uVar5 == 0) {
    radar_render_context_helper_00461270(param_1,0);
    uVar5 = 0;
  }
  else {
    if ((*(byte *)(param_2 + 0x12) & 0x40) == 0) {
      uVar10 = multiplayer_player_table_context_helper_004547c0(uVar5);
    }
    else {
      uVar10 = network_vehicle_message_context_helper_00456700(uVar5 - 1);
    }
    radar_render_context_helper_00461270(param_1,uVar10);
    uVar5 = 1;
  }
  set_default_selected_weapon_slot_for_vehicle(param_1,(uint)uVar5);
  if ((*(byte *)(piVar13 + 0x115) & 0x20) == 0) {
    uVar10 = 0;
    local_e4 = 0;
    local_f4 = (byte *)g_vehicle_damage_texture_name_table;
    piVar13 = local_e0 + 0x56;
    do {
      pbVar12 = local_f4;
      *piVar13 = 100;
      piVar13[4] = 100;
      piVar13[8] = 100;
      local_f0 = (float)((4 - ((uint)param_2[0x16] >> ((byte)local_e4 & 0x1f) & 3)) * 0x19);
      piVar13[0xd] = (int)local_f0;
      if (local_f4 < &DAT_004f8092) {
        if ((*piVar13 == 0) || (local_f4 == (byte *)s_V1_TP_TP_MAP_004f8010)) {
          local_e8 = (int *)((float)piVar13[8] * _DAT_004be1d4);
        }
        else {
          local_e8 = (int *)((float)piVar13[8] / (float)*piVar13);
        }
        local_dc = piVar13[4];
        if ((local_dc == 0) || (local_f4 == (byte *)s_V1_TP_TP_MAP_004f8010)) {
          fVar1 = (float)(int)local_f0 * _DAT_004be1d4;
        }
        else {
          fVar1 = (float)(int)local_f0 / (float)(int)local_dc;
        }
        if ((float)local_e8 <= fVar1) {
          fVar1 = (float)local_e8;
        }
        if (fVar1 <= _DAT_004be1e8) {
          if (fVar1 <= _DAT_004be1dc) {
            uVar16 = 2;
            if (fVar1 <= _DAT_004be1ec) {
              uVar16 = 3;
            }
          }
          else {
            uVar16 = 1;
          }
        }
        else {
          uVar16 = 0;
        }
        update_vehicle_damage_texture_state(local_e0,uVar10,uVar16);
        local_dc = local_e0[(&g_vehicle_damage_texture_slot_offsets)[uVar10] + 0x102];
        switch(uVar16) {
        case 0:
          local_ec = 0;
          break;
        case 1:
        case 2:
          local_ec = 1;
          break;
        case 3:
          local_ec = 2;
        }
        iVar9 = 0;
        pbVar11 = local_f4;
        if (0 < (int)(&g_vehicle_damage_texture_region_counts)[uVar10]) {
          do {
            set_texture_binding_frame_and_reload(local_dc,pbVar11,0,local_ec,1);
            iVar9 = iVar9 + 1;
            pbVar12 = local_f4;
            pbVar11 = pbVar11 + 0xd;
          } while (iVar9 < (int)(&g_vehicle_damage_texture_region_counts)[uVar10]);
        }
      }
      local_f4 = pbVar12 + 0x82;
      uVar10 = uVar10 + 1;
      local_e4 = local_e4 + 2;
      piVar13 = piVar13 + 1;
    } while ((int)local_f4 < 0x4f8092);
    local_e4 = 0;
    local_f4 = &DAT_004f8092;
    iVar9 = 0;
    piVar13 = local_d8;
    do {
      iVar14 = local_e4;
      local_e8 = piVar13;
      if (*piVar13 != 0) {
        set_damageable_part_state_pair
                  (*piVar13,(-(uint)(((byte)(1 << ((byte)local_e4 & 0x1f)) &
                                     *(byte *)((int)param_2 + 0x5d)) != 0) & 0xffffffb5) + 100,100);
        if (*piVar13 != 0) {
          extract_part_damage_state_pair(*piVar13,&local_d8,&local_f0);
          fVar1 = _g_float_zero;
          if (local_f0 != 0.0) {
            fVar1 = (float)(int)local_d8 / (float)(int)local_f0;
          }
          if (fVar1 <= _DAT_004be1e8) {
            if (fVar1 <= _DAT_004be1dc) {
              uVar10 = 2;
              if (fVar1 <= _DAT_004be1ec) {
                uVar10 = 3;
              }
            }
            else {
              uVar10 = 1;
            }
          }
          else {
            uVar10 = 0;
          }
          update_vehicle_damage_texture_state(local_e0,iVar14 + 5U,uVar10);
          if (iVar14 + 5U < 5) {
            uVar16 = local_e0[*(int *)((int)&DAT_004f7dd4 + iVar9) + 0x102];
            switch(uVar10) {
            case 0:
              local_ec = 0;
              break;
            case 1:
            case 2:
              local_ec = 1;
              break;
            case 3:
              local_ec = 2;
            }
            iVar14 = 0;
            pbVar12 = local_f4;
            if (0 < *(int *)((int)&DAT_004f7e04 + iVar9)) {
              do {
                set_texture_binding_frame_and_reload(uVar16,pbVar12,0,local_ec,1);
                iVar14 = iVar14 + 1;
                pbVar12 = pbVar12 + 0xd;
              } while (iVar14 < *(int *)((int)&DAT_004f7e04 + iVar9));
            }
          }
        }
      }
      iVar9 = iVar9 + 4;
      local_e4 = local_e4 + 1;
      piVar13 = local_e8 + 1;
      local_f4 = local_f4 + 0x82;
    } while (iVar9 < 0x18);
    local_d8 = (int *)(uint)*(byte *)(param_2 + 0x17);
    local_f0 = (float)(int)local_d8 * _DAT_004be204;
    local_e8 = piVar13;
    if (local_f0 < _DAT_004be1a4) {
      vehicle_damage_texture_dirty_context_helper_00466ca0(local_e0,local_f0);
    }
  }
  uVar5 = lookup_terrain_material_index_at_world_xz
                    (*(double *)(param_1 + 0x40),
                     (double)CONCAT26((short)((uint)*(undefined4 *)(param_1 + 0x54) >> 0x10),
                                      *(undefined6 *)(param_1 + 0x50)));
  piVar13 = local_e0;
  local_e0[0x117] = CONCAT22(extraout_var,uVar5);
  update_vehicle_skid_collision_damage_audio(param_1,local_e0[0x115],CONCAT22(extraout_var,uVar5));
  multiplayer_player_state_lookup_helper_00454ea0
            ((short)piVar13[0x120],param_2[0x13],*(undefined2 *)(param_2 + 0x14),
             *(undefined2 *)((int)param_2 + 0x52));
  return;
}


