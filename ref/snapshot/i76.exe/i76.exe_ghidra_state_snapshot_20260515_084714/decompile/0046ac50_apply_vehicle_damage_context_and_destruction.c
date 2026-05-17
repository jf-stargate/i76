/*
 * Program: i76.exe
 * Function: apply_vehicle_damage_context_and_destruction
 * Entry: 0046ac50
 * Signature: undefined4 __cdecl apply_vehicle_damage_context_and_destruction(undefined4 * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Vehicle class damage
   callback; updates damage state and destruction side effects. */

undefined4 __cdecl apply_vehicle_damage_context_and_destruction(undefined4 *param_1,int param_2)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  float *pfVar12;
  float fVar13;
  float fVar14;
  uint local_128;
  uint local_124;
  int local_120;
  float local_11c;
  float local_118;
  float local_114;
  undefined4 local_110;
  float local_10c;
  float local_108;
  int local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
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
  
  piVar1 = (int *)param_1[0x1c];
  local_fc = *param_1;
  local_f8 = param_1[1];
  local_f4 = 0;
  _strlwr((char *)&local_fc);
  pcVar4 = strstr((char *)&local_fc,s_flag_004f8680);
  if (((pcVar4 != (char *)0x0) || (iVar9 = 0, param_2 == 0)) || ((param_1[4] & 0x200) != 0)) {
    return 0;
  }
  if ((param_1[0x1b] == 0xc) && ((*(ushort *)(param_2 + 4) & 4) != 0)) {
    *(undefined4 *)(param_2 + 0x10) = 0;
    *(ushort *)(param_2 + 4) = *(ushort *)(param_2 + 4) & 0xfffb;
  }
  piVar11 = (int *)(param_2 + 8);
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar9 & 0x1f)) != 0) {
      if (((*(ushort *)(param_2 + 4) & 8) != 0) && (param_1[0x1b] == 2)) {
        *(uint *)(param_2 + 0x14) = *(uint *)(param_2 + 0x14) >> 2;
      }
      if (*piVar1 < *piVar11) {
        puVar5 = get_active_world_object_entry_object((int)param_1);
        has_world_object_class_damage_handler((int)puVar5);
        *piVar1 = 0;
        iVar9 = param_1[0x1c];
        get_world_object_class_id((int)param_1,0x200);
        iVar6 = is_transform_composed_world_object_class((int)param_1);
        if (iVar6 != 0) {
          *(undefined4 *)(iVar9 + 0x28) = 1;
        }
        create_chunk_manager_geometry_runtime((int)param_1);
        for (iVar6 = param_1[0x19]; iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x60)) {
          apply_vehicle_destruction_effects_and_chunk_spawns(iVar6);
        }
        iVar6 = copy_world_object_position_vector((int)param_1);
        if (iVar6 != 0) {
          iVar6 = get_parent_if_current_is_last_child_link((int)param_1);
          uVar10 = *(uint *)(iVar6 + 0x70);
          local_128 = uVar10;
          local_100 = iVar6;
          iVar7 = is_transform_composed_world_object_class(iVar6);
          if (iVar7 != 0) {
            *(undefined4 *)(uVar10 + 0x28) = 1;
            create_chunk_manager_geometry_runtime(iVar6);
            iVar7 = copy_world_object_orientation_or_velocity_vector(iVar6,0x1000000);
            if (iVar7 != 0) {
              local_120 = *(int *)(iVar6 + 0x70);
              local_11c = 0.0;
              local_118 = 0.0;
              if (local_120 != 0) {
                pfVar8 = (float *)compose_world_object_runtime_transform(&local_ec,iVar7);
                iVar3 = local_120;
                fVar2 = *pfVar8;
                local_10c = pfVar8[1];
                local_108 = pfVar8[2];
                if (*(int *)(iVar6 + 0x6c) != 3) {
                  pfVar8 = (float *)(local_120 + 0x10);
                  iVar6 = _strnicmp((char *)pfVar8,s_null_004c3280,8);
                  if (iVar6 == 0) {
                    strncpy((char *)&local_11c,s_x1_bldx1_004f7d34,8);
                    fVar13 = local_11c;
                    fVar14 = local_118;
                  }
                  else {
                    fVar13 = *pfVar8;
                    fVar14 = *(float *)(iVar3 + 0x14);
                  }
                  spawn_cached_explosion_runtime_object
                            ((uint)fVar13,(uint)fVar14,iVar7,fVar2,local_10c,local_108,0);
                  pcVar4 = (char *)(local_120 + 0x18);
                  iVar6 = _stricmp(pcVar4,s_null_004c3280);
                  if (iVar6 == 0) {
                    dispatch_vehicle_runtime_sound_event(7,iVar7,(undefined4 *)0x0);
                    iVar6 = local_100;
                  }
                  else {
                    play_positional_audio_for_object_or_active_player
                              (pcVar4,iVar7,(undefined4 *)0x0);
                    iVar6 = local_100;
                  }
                }
                *(undefined4 *)(local_120 + 0x28) = 2;
                uVar10 = local_128;
              }
            }
            if ((*(uint *)(iVar6 + 0x10) & 0x800) != 0) {
              release_world_object_light_runtime(iVar6);
            }
            iVar6 = is_damage_side_effects_suppressed();
            if (iVar6 != 0) {
              network_vehicle_message_context_helper_00456710(*(uint *)(uVar10 + 8));
            }
          }
        }
        iVar6 = is_transform_composed_world_object_class((int)param_1);
        if (((iVar6 == 0) || (param_1[0x17] == 0)) || ((*(byte *)(iVar9 + 0x28) & 1) == 0))
        goto LAB_0046b1a2;
        iVar6 = param_1[0x1c];
        local_128 = 0;
        local_124 = 0;
        pfVar8 = (float *)compute_transform_relative_to_ancestor(local_40,(int)param_1,0);
        local_e0 = (float)param_1[0x25];
        local_dc = param_1[0x26];
        local_d0 = param_1[0x26];
        local_c4 = param_1[0x26];
        local_bc = param_1[0x25];
        local_b8 = param_1[0x26];
        local_d8 = param_1[0x27];
        pfVar12 = local_80;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar12 = *pfVar8;
          pfVar8 = pfVar8 + 1;
          pfVar12 = pfVar12 + 1;
        }
        local_cc = param_1[0x27];
        local_c0 = param_1[0x2a];
        local_b4 = param_1[0x2a];
        local_d4 = param_1[0x28];
        local_c8 = local_d4;
        transform_vec3_array_by_matrix(&local_b0,&local_e0,4,local_80);
        local_11c = (local_b0 + local_a4 + local_98 + local_8c) * _DAT_004be31c;
        local_118 = (local_ac + local_a0 + local_94 + local_88) * _DAT_004be31c;
        local_114 = (local_a8 + local_9c + local_90 + local_84) * _DAT_004be31c;
        if ((param_1[4] & 0x400000) == 0) {
          if ((param_1[4] & 0x800000) != 0) {
            pcVar4 = s_x1_cars1_004f8168;
            goto LAB_0046b0cb;
          }
        }
        else {
          pcVar4 = s_x1_bldx1_004f7d34;
LAB_0046b0cb:
          strncpy((char *)&local_128,pcVar4,8);
        }
        if (((-1 < (int)local_124) && ((0 < (int)local_124 || (local_128 != 0)))) &&
           (param_1[0x1b] != 3)) {
          spawn_cached_explosion_runtime_object
                    (local_128,local_124,param_1,local_11c,local_118,local_114,0);
          iVar7 = is_transform_composed_world_object_class((int)param_1);
          if (iVar7 != 0) {
            pcVar4 = (char *)(iVar6 + 0x18);
            iVar7 = _stricmp(pcVar4,s_null_004c3280);
            if (iVar7 != 0) {
              play_positional_audio_for_object_or_active_player
                        (pcVar4,(int)param_1,(undefined4 *)0x0);
              goto LAB_0046b143;
            }
          }
          dispatch_vehicle_runtime_sound_event(7,(int)param_1,(undefined4 *)0x0);
        }
LAB_0046b143:
        create_chunk_manager_geometry_runtime((int)param_1);
        local_110 = 0;
        local_10c = 15.0;
        local_ec = 0.0;
        local_e8 = 0x41700000;
        local_108 = 0.0;
        local_e4 = 0;
        spawn_vehicle_damage_chunk_pair(&local_11c,&local_ec);
        iVar7 = is_transform_composed_world_object_class((int)param_1);
        if (iVar7 != 0) {
          *(undefined4 *)(iVar6 + 0x28) = 2;
        }
LAB_0046b1a2:
        release_or_detach_object_geometry_variant((int)param_1,1);
        iVar6 = is_damage_side_effects_suppressed();
        if ((iVar6 != 0) &&
           (iVar6 = is_transform_composed_world_object_class((int)param_1), iVar6 != 0)) {
          network_vehicle_message_context_helper_00456710(*(uint *)(iVar9 + 8));
        }
        spawn_chC_runtime_effect((int)param_1);
        return 1;
      }
      *piVar1 = *piVar1 - *piVar11;
    }
    iVar9 = iVar9 + 1;
    piVar11 = piVar11 + 1;
    if (3 < iVar9) {
      return 0;
    }
  } while( true );
}


