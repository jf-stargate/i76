/*
 * Program: i76.exe
 * Function: vehicle_class_damage_or_release_callback
 * Entry: 00463a80
 * Signature: undefined4 __cdecl vehicle_class_damage_or_release_callback(int param_1, int * param_2, float * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle class physics rename v29; confidence=high] Class-id 1 damage callback.
   Applies vehicle damage, updates texture state, handles death/kill messages, and removes the
   loaded vehicle runtime when destroyed. */

undefined4 __cdecl vehicle_class_damage_or_release_callback(int param_1,int *param_2,float *param_3)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  int *piVar6;
  char *_Format;
  int *piVar7;
  undefined4 uVar8;
  int iVar9;
  float fVar10;
  int iVar11;
  uint uVar12;
  float10 fVar13;
  float10 fVar14;
  int *local_b8;
  undefined8 local_a8;
  uint local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  undefined4 local_88;
  undefined4 local_84;
  uchar local_80 [24];
  uchar local_68 [24];
  uchar local_50 [80];
  
                    /* I76 semantic baseline: vehicle_class_damage_or_release_callback
                       Vehicle class damage/release callback candidate. */
  local_8c = 0.0;
  piVar7 = *(int **)(param_1 + 0x70);
  local_88 = 0x40a00000;
  local_84 = 0;
  if (((param_2 != (int *)0x0) && ((*(byte *)(param_1 + 0x10) & 0x20) != 0)) ||
     ((local_9c = (uint)piVar7[0x115] >> 5 & 1, param_2 != (int *)0x0 && (local_9c != 0)))) {
    return 0;
  }
  if (param_3 != (float *)0x0) {
    transform_vec3_array_by_matrix(&local_98,param_3,1,(float *)(param_1 + 0x18));
    destroy_chunk_manager_objects
              (s_CHUNK4_004f8160._0_4_,ram0x004f8164,local_98,local_94,local_90,&local_8c,2.5);
  }
  if (param_2 != (int *)0x0) {
    dVar1 = (double)(*param_3 * *param_3 + param_3[2] * param_3[2] + param_3[1] * param_3[1]);
    fVar13 = zone_satellite_map_context_helper_00495000
                       (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
    fVar10 = param_3[1];
    local_a8 = (double)fVar13;
    fVar2 = *param_3 * (float)fVar13;
    fVar3 = param_3[2] * (float)fVar13;
    if (fVar10 * (float)fVar13 <= _DAT_004be1c8) {
      dVar1 = (double)(fVar3 * fVar3 + fVar2 * fVar2);
      fVar14 = zone_satellite_map_context_helper_00495000
                         (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
      fVar4 = fVar2 * (float)fVar14;
      local_a8._4_4_ = (undefined4)((ulonglong)(double)fVar14 >> 0x20);
      local_a8 = (double)CONCAT44(local_a8._4_4_,fVar4);
      if (fVar4 <= _DAT_004be1cc) {
        if (_DAT_004be1d0 <= fVar4) {
          local_b8 = (int *)0x0;
          if (fVar3 * (float)fVar14 <= _DAT_004be1cc) {
            local_b8 = (int *)0x3;
          }
        }
        else {
          local_b8 = (int *)0x1;
        }
      }
      else {
        local_b8 = (int *)0x2;
      }
    }
    else {
      local_b8 = (int *)0x4;
    }
    if (fVar10 * (float)fVar13 <= _DAT_004be1c8) {
      dVar1 = (double)(fVar3 * fVar3 + fVar2 * fVar2);
      fVar13 = zone_satellite_map_context_helper_00495000
                         (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
      local_a8 = (double)fVar13;
      fVar3 = fVar3 * (float)fVar13;
      if (fVar3 <= _DAT_004be1cc) {
        if (_DAT_004be1d0 <= fVar3) {
          if (fVar3 <= _g_float_zero) {
            fVar10 = 5.60519e-45;
            if (fVar2 * (float)fVar13 <= _g_float_zero) {
              fVar10 = 2.8026e-45;
            }
          }
          else if (fVar2 * (float)fVar13 <= _g_float_zero) {
            fVar10 = 1.4013e-45;
          }
          else {
            fVar10 = 4.2039e-45;
          }
        }
        else {
          fVar10 = 7.00649e-45;
        }
      }
      else {
        fVar10 = 0.0;
      }
    }
    else {
      fVar10 = 8.40779e-45;
    }
    if ((piVar7[(int)local_b8 + 0x56] == 0) || (local_b8 == (int *)0x4)) {
      fVar2 = (float)piVar7[(int)local_b8 + 0x5e] * _DAT_004be1d4;
    }
    else {
      fVar2 = (float)piVar7[(int)local_b8 + 0x5e] / (float)piVar7[(int)local_b8 + 0x56];
    }
    if ((piVar7[(int)local_b8 + 0x5a] == 0) || (local_b8 == (int *)0x4)) {
      fVar3 = (float)piVar7[(int)local_b8 + 99] * _DAT_004be1d4;
    }
    else {
      fVar3 = (float)piVar7[(int)local_b8 + 99] / (float)piVar7[(int)local_b8 + 0x5a];
    }
    if (fVar3 < fVar2) {
      fVar2 = fVar3;
    }
    local_a8 = (double)CONCAT44(local_a8._4_4_,fVar2);
    if (((*(byte *)((int)param_2 + 6) & 1) != 0) &&
       (fVar13 = compute_world_object_damage_integrity_percent(param_1),
       (float10)_DAT_004be1d8 < fVar13)) {
      *(undefined2 *)(param_2 + 1) = 1;
      param_2[2] = 5;
    }
    if ((*(byte *)((int)param_2 + 6) & 0x10) == 0) {
      iVar11 = world_object_has_optional_runtime_flag(param_1);
      iVar11 = apply_vehicle_damage_record_to_accumulators((int)piVar7,local_b8,(int)param_2,iVar11)
      ;
    }
    else {
      iVar11 = 0;
      iVar9 = 0;
      piVar6 = param_2 + 2;
      do {
        if (((uint)*(ushort *)(param_2 + 1) & 1 << ((byte)iVar9 & 0x1f)) != 0) {
          iVar11 = iVar11 + *piVar6;
        }
        iVar9 = iVar9 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar9 < 4);
    }
    if (local_b8 == (int *)0x0) {
      if (piVar7[0x56] == 0) {
        fVar2 = (float)piVar7[0x5e] * _DAT_004be1d4;
      }
      else {
        fVar2 = (float)piVar7[0x5e] / (float)piVar7[0x56];
      }
      if (piVar7[0x5a] == 0) {
        fVar3 = (float)piVar7[99] * _DAT_004be1d4;
      }
      else {
        fVar3 = (float)piVar7[99] / (float)piVar7[0x5a];
      }
      if (fVar2 <= fVar3) {
        fVar3 = fVar2;
      }
      if ((fVar3 < _DAT_004be1dc) && ((float)_DAT_004be1e0 < (float)local_a8)) {
        palette_dib_surface_lock_context_helper_00477e80(param_1,0);
      }
    }
    while (iVar11 != 0) {
      fVar13 = compute_world_object_damage_integrity_percent(param_1);
      iVar11 = apply_vehicle_part_damage_and_special_equipment_effects
                         (piVar7,fVar10,(int)param_2,1,(float)fVar13);
    }
    if ((local_9c == 0) && (local_b8 < (int *)0x5)) {
      fVar13 = vehicle_damage_threshold_context_helper_00466c20((int)piVar7,(int)local_b8);
      if (fVar13 <= (float10)_DAT_004be1e8) {
        if (fVar13 <= (float10)_DAT_004be1dc) {
          uVar12 = 2;
          if (fVar13 <= (float10)_DAT_004be1ec) {
            uVar12 = 3;
          }
        }
        else {
          uVar12 = 1;
        }
      }
      else {
        uVar12 = 0;
      }
      update_vehicle_damage_texture_state(piVar7,(uint)local_b8,uVar12);
      set_vehicle_damage_texture_frame_group((int)piVar7,(uint)local_b8,uVar12);
    }
  }
  fVar13 = compute_world_object_damage_integrity_percent(param_1);
  fVar10 = (float)(fVar13 * (float10)_DAT_004be1d4);
  local_a8 = (double)CONCAT44(local_a8._4_4_,fVar10);
  if (fVar13 * (float10)_DAT_004be1d4 < (float10)_DAT_004be1a4) {
    vehicle_damage_texture_dirty_context_helper_00466ca0(piVar7,fVar10);
  }
  if ((*(byte *)(piVar7 + 0x115) & 0x20) == 0) {
    return 0;
  }
  iVar11 = is_damage_side_effects_suppressed();
  if ((iVar11 == 0) || (sVar5 = get_local_multiplayer_player_id(), (short)piVar7[0x120] != sVar5))
  goto LAB_004640c4;
  if (param_2 == (int *)0x0) {
    *(undefined2 *)((int)piVar7 + 0x482) = 0;
  }
  else {
    uVar12 = multiplayer_player_table_context_helper_004551f0(*param_2);
    *(short *)((int)piVar7 + 0x482) = (short)uVar12;
  }
  iVar11 = world_object_has_optional_runtime_flag(param_1);
  if (iVar11 != 0) {
    if (*(short *)((int)piVar7 + 0x482) == 0) {
      sVar5 = 0;
    }
    else {
      lookup_multiplayer_player_vehicle_config_id((short)piVar7[0x120],(undefined4 *)&local_a8);
      lookup_multiplayer_player_vehicle_config_id(*(short *)((int)piVar7 + 0x482),&local_9c);
      if (((local_9c ^ (uint)(float)local_a8) & 0x70000) == 0) goto LAB_00464035;
      sVar5 = *(short *)((int)piVar7 + 0x482);
    }
    multiplayer_player_table_context_helper_00455130(sVar5);
  }
LAB_00464035:
  multiplayer_player_count_context_helper_00454620((short)piVar7[0x120],local_80);
  if (*(short *)((int)piVar7 + 0x482) == 0) {
    _Format = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                    s______s_has_been_killed_004f812c);
    sprintf((char *)local_50,_Format);
  }
  else {
    multiplayer_player_count_context_helper_00454620(*(short *)((int)piVar7 + 0x482),local_68);
    StrLookupFormat(local_50,s______1_s_was_killed_by__2_s_004f8144,local_80);
  }
  draw_multiplayer_chat_message(0,local_50);
LAB_004640c4:
  if ((piVar7[0x115] & 0x4000U) == 0) {
    apply_vehicle_catastrophic_damage_breakup(param_1,1);
  }
  else {
    iVar11 = *(int *)(param_1 + 0x70);
    *(undefined4 *)(iVar11 + 0x450) = 0x41200000;
    *(uint *)(iVar11 + 0x454) = *(uint *)(iVar11 + 0x454) | 0x80008000;
    play_cmike_voice_clip(param_1);
    iVar11 = world_object_has_optional_runtime_flag(param_1);
    if (iVar11 == 0) {
      load_gdf_resource_reference();
    }
    remove_loaded_vehicle_runtime_and_weapon_slots(param_1);
    mark_active_vehicle_damage_textures_dirty();
    dispatch_vehicle_runtime_sound_event(2,param_1,(undefined4 *)0x0);
    play_vehicle_engine_event_sound(param_1,1);
    get_world_object_class_id(param_1,0x200);
    iVar11 = get_active_player_or_camera_world_object_entry();
    if ((iVar11 != 0) &&
       (piVar7 = (int *)get_active_player_or_camera_world_object_entry(), *piVar7 == param_1)) {
      clear_pending_input_action_code();
      iVar11 = 0xfefe;
      uVar8 = get_active_player_or_camera_world_object_entry();
      dispatch_runtime_camera_mode_activation_by_id(uVar8,iVar11);
      weapon_hud_display_context_helper_004621b0();
      _DAT_0053679c = 8;
      iVar11 = is_damage_side_effects_suppressed();
      if (iVar11 != 0) {
        stamp_multiplayer_respawn_or_score_time();
      }
    }
  }
  if (((param_2 != (int *)0x0) && (iVar11 = is_network_or_trip_runtime_mode(), iVar11 != 0)) &&
     (iVar11 = world_object_has_optional_runtime_flag(*param_2), iVar11 != 0)) {
    accumulate_multiplayer_score_distance_from_active_vehicle();
  }
  return 1;
}


