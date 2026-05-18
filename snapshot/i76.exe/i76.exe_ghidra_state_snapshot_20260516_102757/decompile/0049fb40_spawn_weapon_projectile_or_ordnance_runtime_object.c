/*
 * Program: i76.exe
 * Function: spawn_weapon_projectile_or_ordnance_runtime_object
 * Entry: 0049fb40
 * Signature: int * __cdecl spawn_weapon_projectile_or_ordnance_runtime_object(int * param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe weapon/projectile v27; confidence=high] Creates projectile/ordnance world objects
   from weapon fire parameters, binds textures/lights, applies spread, and handles ordnc child
   effects. */

int * __cdecl spawn_weapon_projectile_or_ordnance_runtime_object(int *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int *piVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  LPVOID pvVar8;
  undefined4 *puVar9;
  int *piVar10;
  float *pfVar11;
  uint uVar12;
  int iVar13;
  float *pfVar14;
  float *pfVar15;
  float10 fVar16;
  int local_d4;
  uint local_d0;
  float local_c0 [16];
  float local_80 [16];
  float local_40 [16];
  
  if (param_1[9] == 0) {
    return (int *)0x0;
  }
  iVar6 = find_selected_mission_runtime_index(*param_1);
  switch(*param_1) {
  case 9:
    if (0 < param_1[9]) {
      do {
        initialize_flamer_effect_state
                  (param_1[8],0,param_1[5],(&DAT_00655308)[iVar6 * 0x34],
                   (&DAT_0065530c)[iVar6 * 0x34]);
        iVar7 = param_1[9];
        param_1[9] = iVar7 + -1;
      } while (0 < iVar7 + -1);
      return (int *)0x0;
    }
    break;
  case 10:
    if (0 < param_1[9]) {
      do {
        initialize_flamer_effect_state
                  (param_1[8],1,param_1[5],(&DAT_00655308)[iVar6 * 0x34],
                   (&DAT_0065530c)[iVar6 * 0x34]);
        iVar7 = param_1[9];
        param_1[9] = iVar7 + -1;
      } while (0 < iVar7 + -1);
      return (int *)0x0;
    }
    break;
  case 0xb:
    if (0 < param_1[9]) {
      do {
        initialize_flamer_effect_state
                  (param_1[8],2,param_1[5],(&DAT_00655308)[iVar6 * 0x34],
                   (&DAT_0065530c)[iVar6 * 0x34]);
        iVar7 = param_1[9];
        param_1[9] = iVar7 + -1;
      } while (0 < iVar7 + -1);
    }
    break;
  default:
    param_1[4] = (&DAT_006552b4)[iVar6 * 0x34];
    if ((&DAT_006552a0)[iVar6 * 0x34] == 0) {
      iVar7 = find_selected_mission_runtime_index((&g_mission_runtime_vehicle_table)[iVar6 * 0x34]);
      local_d4 = 0;
      if (0 < (int)(&DAT_0065529c)[iVar6 * 0x34]) {
        do {
          pvVar8 = allocate_world_object_node(0);
          *(undefined4 *)((int)pvVar8 + 100) = 0;
          *(undefined4 *)((int)pvVar8 + 0x60) = 0;
          *(undefined4 *)((int)pvVar8 + 0x68) = 0;
          *(undefined4 *)((int)pvVar8 + 0x90) = 0x3e800000;
          *(undefined4 *)((int)pvVar8 + 0x6c) =
               *(undefined4 *)((&DAT_00655284)[iVar6 * 0x34] + 0x6c);
          ordnance_object_release_context_helper_004a05f0(iVar7,2,(int)pvVar8);
          if ((&DAT_006552bc)[iVar6 * 0x34] == 1) {
            cache_add_indexed_entry((&DAT_00655284)[iVar6 * 0x34],(int)pvVar8);
          }
          puVar9 = HeapAlloc((HANDLE)(&DAT_00655298)[iVar6 * 0x34],0,0x4c);
          *(undefined4 **)((int)pvVar8 + 0x70) = puVar9;
          for (iVar13 = 0x13; iVar13 != 0; iVar13 = iVar13 + -1) {
            *puVar9 = 0;
            puVar9 = puVar9 + 1;
          }
          **(undefined4 **)((int)pvVar8 + 0x70) = (&g_mission_runtime_vehicle_table)[iVar6 * 0x34];
          if (((&DAT_006552c4)[iVar6 * 0x34] == 1) &&
             (*(char *)(&DAT_006552c8 + iVar6 * 0x34) != '\0')) {
            bind_texture_resource_to_object_slot
                      ((uint)pvVar8,(byte *)(&DAT_006552c8 + iVar6 * 0x34),
                       (byte *)(&DAT_006552c8 + iVar6 * 0x34));
          }
          local_d4 = local_d4 + 1;
        } while (local_d4 < (int)(&DAT_0065529c)[iVar6 * 0x34]);
      }
    }
    if ((int)(&DAT_006552ac)[iVar6 * 0x34] < (int)(&DAT_006552a4)[iVar6 * 0x34]) {
      iVar7 = *(int *)((&DAT_0065528c)[iVar6 * 0x34] + 100);
      for (iVar13 = *(int *)(*(int *)((&DAT_0065528c)[iVar6 * 0x34] + 100) + 0x60); iVar13 != 0;
          iVar13 = *(int *)(iVar13 + 0x60)) {
        iVar7 = iVar13;
      }
      iVar7 = ordnance_projectile_update_context_helper_004a06f0(iVar6,0,iVar7);
      ordnance_object_release_context_helper_004a05f0(iVar6,1,iVar7);
    }
    local_d0 = (uint)((&DAT_006552bc)[iVar6 * 0x34] == 0);
    if (((&g_mission_runtime_vehicle_table)[iVar6 * 0x34] == 1) ||
       ((&g_mission_runtime_vehicle_table)[iVar6 * 0x34] == 6)) {
      (&DAT_006552bc)[iVar6 * 0x34] = 0;
      local_d0 = 1;
    }
    piVar10 = (int *)ordnance_projectile_update_context_helper_004a06f0
                               (iVar6,2,(&DAT_00655294)[iVar6 * 0x34]);
    ordnance_object_release_context_helper_004a05f0(iVar6,local_d0,(int)piVar10);
    piVar10[4] = 0;
    pfVar15 = (float *)(piVar10 + 6);
    pfVar11 = (float *)compute_transform_relative_to_ancestor(local_80,param_1[8],0);
    pfVar14 = pfVar15;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar14 = *pfVar11;
      pfVar11 = pfVar11 + 1;
      pfVar14 = pfVar14 + 1;
    }
    fVar16 = get_runtime_frame_delta_seconds();
    iVar7 = rand();
    fVar2 = ((float)param_1[0xb] + (float)param_1[0xb]) * (float)iVar7 * _DAT_004bea38 -
            (float)param_1[0xb];
    iVar7 = rand();
    fVar3 = ((float)param_1[0xb] + (float)param_1[0xb]) * (float)iVar7 * _DAT_004bea38 -
            (float)param_1[0xb];
    iVar7 = rand();
    fVar5 = (float)iVar7 * _DAT_004bea38 * _DAT_004bea40;
    switch(*param_1) {
    case 1:
    case 4:
    case 5:
    case 6:
    case 7:
    case 0xf:
    case 0x10:
    case 0x12:
    case 0x13:
    case 0x15:
    case 0x16:
      if ((_DAT_004bea34 < fVar2) && (_DAT_004bea34 < fVar3)) {
        fVar1 = (float)param_1[0xb];
        pfVar11 = (float *)zone_satellite_map_context_helper_00493da0
                                     (local_c0,fVar2 * _DAT_004bea44);
        pfVar14 = local_40;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar14 = *pfVar11;
          pfVar11 = pfVar11 + 1;
          pfVar14 = pfVar14 + 1;
        }
        pfVar11 = (float *)zone_satellite_map_context_helper_00493e00
                                     (local_c0,(fVar3 - fVar1) * _DAT_004bea44);
        pfVar14 = local_80;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar14 = *pfVar11;
          pfVar11 = pfVar11 + 1;
          pfVar14 = pfVar14 + 1;
        }
        pfVar11 = compose_matrix_or_transform_a(local_c0,local_40,pfVar15);
        fVar2 = _DAT_004bea34;
        pfVar14 = pfVar15;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar14 = *pfVar11;
          pfVar11 = pfVar11 + 1;
          pfVar14 = pfVar14 + 1;
        }
        if (fVar2 < fVar3 - fVar1) {
          pfVar11 = compose_matrix_or_transform_a(local_c0,local_80,pfVar15);
          for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
            *pfVar15 = *pfVar11;
            pfVar11 = pfVar11 + 1;
            pfVar15 = pfVar15 + 1;
          }
        }
        ordnance_collision_context_helper_004a0cc0((int)piVar10,fVar5);
        goto LAB_004a00da;
      }
      break;
    case 2:
    case 8:
    case 0x14:
      ordnance_collision_context_helper_004a0dd0((int)piVar10,fVar2,fVar3 - (float)param_1[0xb]);
      iVar7 = rand();
      ordnance_collision_context_helper_004a0cc0
                ((int)piVar10,(float)iVar7 * _DAT_004bea38 * _DAT_004bea50 - _DAT_004bea54);
      break;
    case 3:
      ordnance_collision_context_helper_004a0cc0((int)piVar10,fVar5);
      iVar7 = rand();
      ordnance_collision_context_helper_004a0cc0
                ((int)piVar10,(float)iVar7 * _DAT_004bea38 * _DAT_004bea48 - _DAT_004bea58);
      if ((float)param_1[10] != 0.0) {
        weapon_ordnance_query_context_helper_004a7bb0((int)piVar10,(float)param_1[10]);
      }
      break;
    case 0xc:
    case 0xe:
    case 0x11:
      iVar7 = rand();
      fVar2 = (float)param_1[0xb];
      fVar5 = (float)iVar7 * _DAT_004bea38;
      fVar3 = (float)param_1[0xb];
      ordnance_collision_context_helper_004a0cc0
                ((int)piVar10,(float)param_1[2] * (float)fVar16 * _DAT_004bea48);
      ordnance_collision_context_helper_004a0dd0((int)piVar10,(fVar2 + fVar2) * fVar5 - fVar3,0.0);
      iVar7 = rand();
      ordnance_collision_context_helper_004a0cc0
                ((int)piVar10,
                 ((float)param_1[3] * (float)fVar16 - _DAT_004bea4c) * (float)iVar7 * _DAT_004bea38)
      ;
      ordnance_damage_effect_context_helper_004a0eb0((float)piVar10);
    }
LAB_004a00da:
    update_ordnance_system((int)piVar10,param_1);
    if ((&DAT_006552c0)[iVar6 * 0x34] != 0) {
      create_lobj_light_runtime_entry((int)piVar10,0,25.0,0.0,(float *)0x0,(undefined4 *)0x0);
    }
    switch(*param_1) {
    case 1:
    case 6:
    case 0x12:
      enqueue_projectile_tracer_runtime_record
                ((int)piVar10,(&DAT_006552e0)[iVar6 * 0x34],param_1[6]);
      break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 0x14:
    case 0x16:
      play_clockon_audio((int)piVar10,(&DAT_006552e0)[iVar6 * 0x34]);
      iVar6 = world_object_has_optional_runtime_flag(param_1[1]);
      if (iVar6 != 0) {
        set_ordnance_global_runtime_flag(piVar10);
      }
      break;
    case 0xc:
    case 0xe:
      if (*(char *)(&DAT_006552c8 + iVar6 * 0x34) == '\0') {
        return piVar10;
      }
      install_texture_animation_linear_timer
                ((uint)piVar10,(byte *)(&DAT_006552c8 + iVar6 * 0x34),0.16666667,0.0,1.12104e-44,0.0
                );
      return piVar10;
    case 0x11:
      if (*(char *)(&DAT_006552c8 + iVar6 * 0x34) == '\0') {
        return piVar10;
      }
      install_texture_animation_pingpong_timer
                ((uint)piVar10,(byte *)(&DAT_006552c8 + iVar6 * 0x34),0.16666667,1.4013e-45,
                 1.12104e-44,1);
      return piVar10;
    case 0x15:
      piVar10[4] = piVar10[4] | 0x40;
      if (*(byte *)(&DAT_006552c8 + iVar6 * 0x34) != 0) {
        install_texture_animation_pingpong_timer
                  ((uint)piVar10,(byte *)(&DAT_006552c8 + iVar6 * 0x34),0.16666667,0.0,8.40779e-45,1
                  );
      }
      iVar6 = world_object_has_optional_runtime_flag(param_1[1]);
      if (iVar6 == 0) {
        return piVar10;
      }
      set_ordnance_global_runtime_flag(piVar10);
      return piVar10;
    }
    if (((param_2 != _DAT_004bea34) && (piVar10 != (int *)0x0)) &&
       ((local_d0 == 0 || (local_d0 == 1)))) {
      piVar4 = (int *)piVar10[0x1c];
      iVar6 = find_selected_mission_runtime_index(*piVar4);
      *(float *)(piVar10[0x1c] + 4) = *(float *)(piVar10[0x1c] + 4) - param_2;
      iVar7 = ordnance_projectile_update_context_helper_004a07d0((int)piVar10);
      if (iVar7 == 0) {
        uVar12 = ordnance_projectile_update_context_helper_004a0800(piVar10,param_2);
      }
      else {
        iVar7 = world_object_has_optional_runtime_flag(piVar4[3]);
        uVar12 = 0;
        if (iVar7 != 0) {
          ordnance_runtime_flag_get_context_helper_004a7130((int)piVar10);
        }
      }
      if (uVar12 == 0) {
        if ((((&g_mission_runtime_vehicle_table)[iVar6 * 0x34] == 0x11) ||
            ((&g_mission_runtime_vehicle_table)[iVar6 * 0x34] == 0x15)) &&
           (*(char *)(&DAT_006552c8 + iVar6 * 0x34) != '\0')) {
          release_texture_animation_record((int)piVar10,(char *)(&DAT_006552c8 + iVar6 * 0x34));
        }
        if ((&g_mission_runtime_vehicle_table)[iVar6 * 0x34] == 0x16) {
          unregister_world_object_smoke_emitter(piVar10);
        }
        finalize_released_world_object_after_damage((LPVOID)piVar4[3],s_ordnc_004fe6f0);
        finalize_released_world_object_after_damage((LPVOID)piVar4[4],s_ordnc_004fe6f0);
        if ((&DAT_006552c0)[iVar6 * 0x34] == 1) {
          release_world_object_light_runtime((int)piVar10);
        }
        ordnance_projectile_update_context_helper_004a06f0(iVar6,local_d0,(int)piVar10);
        ordnance_object_release_context_helper_004a05f0(iVar6,2,(int)piVar10);
      }
    }
    return piVar10;
  case 0xd:
    break;
  }
  return (int *)0x0;
}


