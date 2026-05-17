/*
 * Program: i76.exe
 * Function: apply_vehicle_catastrophic_damage_breakup
 * Entry: 00466180
 * Signature: uint * __cdecl apply_vehicle_catastrophic_damage_breakup(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium-high] Large catastrophic
   damage/destruction path. Spawns car/chunk explosions, releases lights/geometry, updates damage
   textures, detaches chunks, and removes loaded vehicle/runtime state. */

uint * __cdecl apply_vehicle_catastrophic_damage_breakup(int param_1,int param_2)

{
  double dVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  uint *puVar7;
  float *pfVar8;
  LPVOID pvVar9;
  undefined4 *puVar10;
  uint uVar11;
  code *pcVar12;
  byte *pbVar13;
  byte *pbVar14;
  float fVar15;
  uint uVar16;
  int *piVar17;
  float *pfVar18;
  undefined4 *puVar19;
  float10 fVar20;
  float local_dc;
  float local_d8;
  float local_d4;
  byte *local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  int *local_b0;
  uint local_ac;
  uint local_a8;
  float local_a4 [3];
  float local_98 [10];
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined2 local_54;
  int local_4c;
  float local_40 [16];
  
  fVar15 = (float)*(double *)(param_1 + 0x40);
  piVar17 = *(int **)(param_1 + 0x70);
  local_ac = 0;
  fVar2 = (float)*(double *)(param_1 + 0x48);
  local_a8 = 0;
  local_d4 = (float)*(double *)(param_1 + 0x50);
  local_dc = fVar15;
  local_d8 = fVar2;
  local_cc = fVar15;
  local_c8 = fVar2;
  local_c4 = local_d4;
  local_b0 = piVar17;
  has_world_object_class_damage_handler(*piVar17);
  pcVar12 = rand_exref;
  if (param_2 != 0) {
    piVar17[0x114] = 0x41200000;
    piVar17[0x115] = piVar17[0x115] | 0x80008000;
    play_cmike_voice_clip(param_1);
    unregister_world_object_smoke_emitter(*(LPVOID *)*piVar17);
    piVar17[0x115] = piVar17[0x115] & 0xffffffbf;
    set_vehicle_current_damage_or_effect_object(param_1,0);
    if ((*(uint *)(param_1 + 0x10) & 0x800) != 0) {
      release_world_object_light_runtime(param_1);
    }
    if (piVar17[0xe9] != 0) {
      puVar7 = (uint *)(piVar17[0xe9] + 0x10);
      *puVar7 = *puVar7 | 1;
    }
    strncpy((char *)&local_ac,s_x1_carx1_004f817c,8);
    spawn_cached_explosion_runtime_object(local_ac,local_a8,param_1,fVar15,fVar2,local_d4,param_1);
    pcVar12 = rand_exref;
    local_d0 = (byte *)rand();
    local_c0 = (float)(int)local_d0 * _DAT_004be218 - _DAT_004be1a0;
    local_c0 = local_c0 + local_c0;
    iVar4 = rand();
    local_d0 = (byte *)((float)iVar4 * _DAT_004be218 - _DAT_004be1a0);
    apply_vehicle_random_bounce_impulse(param_1,local_c0,(float)local_d0);
    uVar16 = 0;
    local_d0 = (byte *)g_vehicle_damage_texture_name_table;
    do {
      pbVar13 = local_d0;
      update_vehicle_damage_texture_state(piVar17,uVar16,4);
      pbVar14 = pbVar13;
      if (pbVar13 < &DAT_004f8092) {
        uVar11 = piVar17[(&g_vehicle_damage_texture_slot_offsets)[uVar16] + 0x102];
        iVar4 = 0;
        pcVar12 = rand_exref;
        piVar17 = local_b0;
        if (0 < (int)(&g_vehicle_damage_texture_region_counts)[uVar16]) {
          do {
            set_texture_binding_frame_and_reload(uVar11,pbVar13,0,3,1);
            iVar4 = iVar4 + 1;
            pbVar13 = pbVar13 + 0xd;
            pcVar12 = rand_exref;
            pbVar14 = local_d0;
            piVar17 = local_b0;
          } while (iVar4 < (int)(&g_vehicle_damage_texture_region_counts)[uVar16]);
        }
      }
      local_d0 = pbVar14 + 0x82;
      uVar16 = uVar16 + 1;
    } while (local_d0 < &DAT_004f839e);
    get_world_object_class_id(param_1,0x200);
    dispatch_vehicle_runtime_sound_event(2,param_1,(undefined4 *)0x0);
    dispatch_vehicle_runtime_sound_event(7,param_1,(undefined4 *)0x0);
    iVar4 = get_active_player_or_camera_world_object_entry();
    if ((iVar4 == 0) ||
       (piVar5 = (int *)get_active_player_or_camera_world_object_entry(), *piVar5 != param_1)) {
      iVar4 = is_damage_side_effects_suppressed();
      if (iVar4 == 0) {
        piVar5 = piVar17 + 0xea;
        local_d0 = (byte *)0x14;
        do {
          if (*piVar5 != 0) {
            puVar10 = &local_58;
            for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar10 = 0;
              puVar10 = puVar10 + 1;
            }
            local_54 = 2;
            iVar4 = *piVar5;
            if (iVar4 == 0) {
switchD_00466425_caseD_19:
              iVar4 = 0;
            }
            else {
              switch(*(undefined4 *)(iVar4 + 0x6c)) {
              case 0x14:
                iVar4 = **(int **)(iVar4 + 0x70);
                break;
              case 0x15:
              case 0x17:
                iVar4 = **(int **)(iVar4 + 0x70);
                break;
              case 0x16:
                iVar4 = *(int *)(*(int *)(iVar4 + 0x70) + 4);
                break;
              case 0x18:
                iVar4 = *(int *)(*(int *)(iVar4 + 0x70) + 8);
                break;
              default:
                goto switchD_00466425_caseD_19;
              case 0x1e:
                iVar4 = *(int *)(*(int *)(iVar4 + 0x70) + 4);
                break;
              case 0x32:
                iVar4 = weapon_fire_request_context_helper_004a4c50(iVar4);
              }
            }
            uVar16 = (*pcVar12)();
            uVar11 = (int)uVar16 >> 0x1f;
            local_4c = (int)(((((uVar16 ^ uVar11) - uVar11 & 0x7f ^ uVar11) - uVar11) + 0x81) *
                            iVar4) >> 8;
            dispatch_damage_context_to_world_object_class_handler(*piVar5,&local_58,0);
            piVar17 = local_b0;
          }
          piVar5 = piVar5 + 1;
          local_d0 = local_d0 + -1;
        } while (local_d0 != (byte *)0x0);
      }
    }
    else {
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
    iVar4 = world_object_has_optional_runtime_flag(param_1);
    if (iVar4 == 0) {
      load_gdf_resource_reference();
    }
    remove_loaded_vehicle_runtime_and_weapon_slots(param_1);
    mark_active_vehicle_damage_textures_dirty();
    fVar15 = local_dc;
  }
  uVar16 = (*pcVar12)();
  puVar7 = (uint *)(uVar16 & 0xf);
  switch(puVar7) {
  case (uint *)0x0:
    iVar4 = (*pcVar12)();
    uVar16 = iVar4 % 5;
    do {
      if ((piVar17[uVar16 + 0xea] != 0) && ((*(byte *)(piVar17[uVar16 + 0xea] + 0x10) & 1) == 0)) {
        pvVar9 = *(LPVOID *)(piVar17[uVar16 + 0xea] + 100);
        pfVar8 = (float *)reticle_texture_context_helper_00458e30(&local_bc,(int)pvVar9,param_1);
        local_dc = *pfVar8;
        local_d8 = pfVar8[1];
        local_d4 = pfVar8[2];
        pfVar8 = (float *)compute_transform_relative_to_ancestor(local_40,param_1,0);
        pfVar18 = local_98;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pfVar18 = *pfVar8;
          pfVar8 = pfVar8 + 1;
          pfVar18 = pfVar18 + 1;
        }
        dVar1 = (double)(local_d4 * local_d4 + local_dc * local_dc);
        local_70 = 0;
        local_6c = 0;
        local_68 = 0;
        local_64 = 0;
        local_60 = 0;
        local_5c = 0;
        local_d8 = 0.0;
        fVar20 = zone_satellite_map_context_helper_00495000
                           (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
        local_bc = (float)((float10)local_dc * fVar20);
        local_b8 = (float)((float10)local_d8 * fVar20);
        local_b4 = (float)((float10)local_d4 * fVar20);
        local_dc = local_bc * _DAT_004be21c;
        local_c8 = local_b8 * _DAT_004be21c;
        local_d4 = local_b4 * _DAT_004be21c;
        local_d8 = 2.0;
        local_cc = local_dc;
        local_c4 = local_d4;
        transform_vec3_array_by_matrix(local_a4,&local_dc,1,local_98);
        update_chunk_manager_runtime(pvVar9,local_a4,0,0);
        puVar7 = (uint *)(*(uint *)(local_b0[uVar16 + 0xea] + 0x10) | 1);
        *(uint **)(local_b0[uVar16 + 0xea] + 0x10) = puVar7;
        return puVar7;
      }
      puVar7 = (uint *)((uVar16 + 1) / 5);
      uVar16 = (uVar16 + 1) % 5;
    } while (uVar16 != iVar4 % 5);
    break;
  case (uint *)0x1:
    iVar4 = (*pcVar12)();
    uVar16 = iVar4 % 6;
    do {
      if ((piVar17[uVar16 + 0xf4] != 0) && ((*(byte *)(piVar17[uVar16 + 0xf4] + 0x10) & 1) == 0)) {
        local_d0 = (byte *)piVar17[uVar16 + 0xf4];
        pfVar8 = (float *)reticle_texture_context_helper_00458e30(&local_bc,(int)local_d0,param_1);
        local_dc = *pfVar8;
        local_d8 = pfVar8[1];
        local_d4 = pfVar8[2];
        pfVar8 = (float *)compute_transform_relative_to_ancestor(local_40,param_1,0);
        pfVar18 = local_98;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pfVar18 = *pfVar8;
          pfVar8 = pfVar8 + 1;
          pfVar18 = pfVar18 + 1;
        }
        dVar1 = (double)(local_d4 * local_d4 + local_d8 * local_d8 + local_dc * local_dc);
        fVar20 = zone_satellite_map_context_helper_00495000
                           (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
        local_bc = (float)((float10)local_dc * fVar20);
        local_b8 = (float)((float10)local_d8 * fVar20);
        local_b4 = (float)((float10)local_d4 * fVar20);
        local_dc = local_bc * _DAT_004be220;
        local_70 = 0;
        local_d8 = local_b8 * _DAT_004be220;
        local_6c = 0;
        local_68 = 0;
        local_d4 = local_b4 * _DAT_004be220;
        local_64 = 0;
        local_60 = 0;
        local_5c = 0;
        local_cc = local_dc;
        local_c8 = local_d8;
        local_c4 = local_d4;
        transform_vec3_array_by_matrix(local_a4,&local_dc,1,local_98);
        pvVar9 = allocate_world_object_node(0);
        puVar10 = (undefined4 *)compute_transform_relative_to_ancestor(local_40,(int)local_d0,0);
        puVar19 = (undefined4 *)((int)pvVar9 + 0x18);
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar19 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar19 = puVar19 + 1;
        }
        *(undefined4 *)((int)pvVar9 + 0x10) = 0;
        *(undefined4 *)((int)pvVar9 + 0x5c) = 0;
        iVar4 = *(int *)((int)local_d0 + 100);
        while (iVar3 = iVar4, iVar3 != 0) {
          iVar4 = *(int *)(iVar3 + 0x60);
          if (*(int *)(iVar3 + 0x6c) == 0x3f) {
            radar_context_setup_helper_0045f310(iVar3);
            attach_world_object_as_first_child(iVar3,(int)pvVar9);
          }
        }
        update_chunk_manager_runtime(pvVar9,local_a4,0,0);
        puVar7 = (uint *)(*(uint *)(local_b0[uVar16 + 0xf4] + 0x10) | 1);
        *(uint **)(local_b0[uVar16 + 0xf4] + 0x10) = puVar7;
        return puVar7;
      }
      puVar7 = (uint *)((uVar16 + 1) / 6);
      uVar16 = (uVar16 + 1) % 6;
    } while (uVar16 != iVar4 % 6);
    break;
  case (uint *)0x2:
  case (uint *)0x3:
    iVar4 = *(int *)(param_1 + 100);
    if (iVar4 != 0) {
      do {
        puVar7 = (uint *)(*pcVar12)();
        if (((uint)puVar7 & 1) != 0) {
          puVar7 = (uint *)spawn_random_chunk_child_object(iVar4);
        }
        iVar4 = *(int *)(iVar4 + 0x60);
      } while (iVar4 != 0);
      return puVar7;
    }
    break;
  case (uint *)0x4:
  case (uint *)0x5:
    local_bc = 0.0;
    local_b8 = 15.0;
    local_b4 = 0.0;
    local_cc = 0.0;
    local_c8 = 15.0;
    local_c4 = 0.0;
    uVar16 = (*pcVar12)();
    uVar11 = (int)uVar16 >> 0x1f;
    if (((uVar16 ^ uVar11) - uVar11 & 1 ^ uVar11) == uVar11) {
      puVar7 = destroy_chunk_manager_objects
                         (DAT_004f7d24,DAT_004f7d28,fVar15,local_d8,local_d4,&local_cc,15.0);
      return puVar7;
    }
    puVar7 = destroy_chunk_manager_objects
                       (DAT_004f7d2c,DAT_004f7d30,fVar15,local_d8,local_d4,&local_cc,15.0);
    return puVar7;
  case (uint *)0x6:
  case (uint *)0x7:
    puVar10 = get_active_world_object_entry_object(param_1);
    iVar4 = (*pcVar12)();
    local_c0 = (float)(iVar4 + -0x7fff >> 1);
    local_cc = local_dc - (float)(int)local_c0 * (float)puVar10[4] * _DAT_004be224;
    iVar4 = (*pcVar12)();
    local_c0 = (float)(iVar4 + -0x7fff >> 1);
    local_c8 = local_c8 - (float)(int)local_c0 * (float)puVar10[4] * _DAT_004be228;
    iVar4 = (*pcVar12)();
    local_c0 = (float)(iVar4 + -0x7fff >> 1);
    local_c4 = local_c4 - (float)(int)local_c0 * (float)puVar10[4] * _DAT_004be224;
    strncpy((char *)&local_ac,s_x1_cars1_004f8168,8);
    puVar7 = spawn_cached_explosion_runtime_object
                       (local_ac,local_a8,param_1,local_cc,local_c8,local_c4,param_1);
  }
  return puVar7;
}


