/*
 * Program: i76.exe
 * Function: update_ordnance_collision_state
 * Entry: 004aa9f0
 * Signature: bool __cdecl update_ordnance_collision_state(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

bool __cdecl update_ordnance_collision_state(int param_1,float param_2)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  bool bVar7;
  int *piVar8;
  undefined3 extraout_var;
  uint uVar9;
  float *pfVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  float10 fVar15;
  float10 extraout_ST0;
  uint local_170;
  int local_15c;
  float local_158;
  float local_154;
  float local_150;
  float *local_14c;
  int local_148;
  int local_144;
  LPVOID local_140;
  int local_13c [3];
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c [3];
  float local_100;
  float local_fc;
  float local_f8;
  float local_e8;
  int local_e4;
  double local_c8;
  float local_bc [31];
  float local_40 [16];
  
  iVar13 = *(int *)(param_1 + 0x70);
  local_14c = (float *)(iVar13 + 0x14);
  local_148 = iVar13;
  piVar8 = (int *)build_vehicle_ordnance_runtime_context(local_bc,param_1);
  piVar14 = &local_144;
  for (iVar12 = 0x1f; iVar12 != 0; iVar12 = iVar12 + -1) {
    *piVar14 = *piVar8;
    piVar8 = piVar8 + 1;
    piVar14 = piVar14 + 1;
  }
  if (local_140 != (LPVOID)0x0) {
    bVar7 = radar_render_context_helper_00461680((int)local_140);
    if (CONCAT31(extraout_var,bVar7) == 1) {
      finalize_released_world_object_after_damage(local_140,s_ordnc_004fe6f0);
      local_140 = (LPVOID)0x0;
      *(undefined4 *)(iVar13 + 0x10) = 0;
    }
    if (local_140 != (LPVOID)0x0) {
      iVar12 = is_vehicle_or_actor_runtime_world_object((int)local_140);
      if ((iVar12 != 0) &&
         (uVar9 = vehicle_damage_component_runtime_context_helper_00466de0((int)local_140),
         uVar9 == 0)) {
        finalize_released_world_object_after_damage(local_140,s_ordnc_004fe6f0);
        local_140 = (LPVOID)0x0;
        *(undefined4 *)(iVar13 + 0x10) = 0;
      }
      if (local_140 != (LPVOID)0x0) {
        pfVar10 = (float *)get_world_object_position_vector((float *)&local_c8,(float)local_140);
        fVar2 = *pfVar10 - local_124;
        fVar4 = pfVar10[1] - local_120;
        fVar3 = pfVar10[2] - local_11c;
        dVar1 = (double)(fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2);
        fVar15 = zone_satellite_map_context_helper_00495000
                           (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
        fVar2 = fVar2 * (float)fVar15;
        fVar4 = fVar4 * (float)fVar15;
        fVar3 = fVar3 * (float)fVar15;
        if (fVar3 * local_110 + fVar4 * local_114 + fVar2 * local_118 < _DAT_004bec20) {
          fVar5 = fVar3 * local_114 - fVar4 * local_110;
          fVar6 = fVar2 * local_110 - fVar3 * local_118;
          fVar4 = fVar4 * local_118 - fVar2 * local_114;
          fVar2 = SQRT(fVar4 * fVar4 + fVar6 * fVar6 + fVar5 * fVar5);
          fVar3 = fVar2 * _DAT_004bec24;
          if ((*(float *)(iVar13 + 0x40) < _DAT_004bec28) && (_DAT_004bec2c < fVar3)) {
            fVar3 = _DAT_004bec2c;
          }
          if (((_DAT_004bec28 <= *(float *)(iVar13 + 0x40)) &&
              (*(float *)(iVar13 + 0x40) < _DAT_004bec30)) && (_DAT_004bec34 < fVar3)) {
            fVar3 = _DAT_004bec34;
          }
          if ((_DAT_004bec30 < *(float *)(iVar13 + 0x40)) && (_DAT_004bec38 < fVar3)) {
            fVar3 = _DAT_004bec38;
          }
          fVar2 = _DAT_004bec3c / fVar2;
          pfVar10 = (float *)zone_satellite_map_context_helper_00494460
                                       (local_bc,-fVar3,fVar5 * fVar2,fVar6 * fVar2,fVar4 * fVar2);
          pfVar11 = local_40;
          for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
            *pfVar11 = *pfVar10;
            pfVar10 = pfVar10 + 1;
            pfVar11 = pfVar11 + 1;
          }
          pfVar10 = compose_matrix_or_transform_a(local_bc,(float *)(param_1 + 0x18),local_40);
          pfVar11 = (float *)(param_1 + 0x18);
          for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
            *pfVar11 = *pfVar10;
            pfVar10 = pfVar10 + 1;
            pfVar11 = pfVar11 + 1;
          }
          local_118 = *(float *)(param_1 + 0x30);
          local_114 = *(float *)(param_1 + 0x34);
          local_110 = *(float *)(param_1 + 0x38);
          *(double *)(param_1 + 0x40) = (double)local_124;
          *(double *)(param_1 + 0x48) = (double)local_120;
          *(double *)(param_1 + 0x50) = (double)local_11c;
        }
        goto LAB_004aad17;
      }
    }
  }
  *(undefined4 *)(iVar13 + 0x10) = 0;
LAB_004aad17:
  if (((_DAT_004bec04 <= param_2) && (param_2 <= _DAT_004bec08)) &&
     ((float)_DAT_004bec10 <= ABS(local_e8 - local_f8))) {
    local_e8 = (local_e8 - local_f8) * param_2 + local_f8;
  }
  pfVar10 = (float *)(param_1 + 0x18);
  fVar3 = *(float *)(param_1 + 0x24) * local_fc;
  fVar2 = *(float *)(param_1 + 0x2c) * local_fc;
  local_fc = *(float *)(param_1 + 0x34) * local_e8 +
             *(float *)(param_1 + 0x1c) * local_100 + *(float *)(param_1 + 0x28) * local_fc;
  local_f8 = *(float *)(param_1 + 0x38) * local_e8 + *(float *)(param_1 + 0x20) * local_100 + fVar2;
  local_100 = *(float *)(param_1 + 0x30) * local_e8 + fVar3 + *(float *)(param_1 + 0x18) * local_100
  ;
  effect_target_list_scan_context_helper_004383a0(&local_124,&local_100,local_10c,param_2);
  fVar2 = *(float *)(param_1 + 0x20) * local_f8;
  fVar4 = *(float *)(param_1 + 0x2c) * local_f8;
  fVar3 = *(float *)(param_1 + 0x24) * local_100;
  local_c8 = (double)local_124;
  local_f8 = *(float *)(param_1 + 0x34) * local_fc +
             *(float *)(param_1 + 0x30) * local_100 + *(float *)(param_1 + 0x38) * local_f8;
  local_170 = SUB84((double)(_DAT_006442c4 * local_124 + (float)_DAT_004faf18),0);
  uVar9 = local_170;
  local_170 = SUB84((double)(_DAT_006442c4 * local_11c + (float)_DAT_004faf18),0);
  if (((0x2800 - local_170 | 0x2800 - uVar9 | local_170 | uVar9) & 0x80000000) == 0) {
    local_100 = *(float *)(param_1 + 0x1c) * local_fc + fVar2 + *pfVar10 * local_100;
    local_fc = fVar3 + fVar4 + *(float *)(param_1 + 0x28) * local_fc;
    apply_world_object_transform_to_bounds_or_geometry(local_c8,(double)local_11c);
    if ((float10)local_120 < extraout_ST0 - (float10)_DAT_004bec40) {
      local_120 = (float)(extraout_ST0 - (float10)_DAT_004bec40);
    }
    iVar13 = 0;
    for (; 0 < local_e4; local_e4 = local_e4 + -1) {
      iVar13 = local_144;
      if (_DAT_004bec18 < *(float *)(local_148 + 0x40)) {
        iVar13 = 0;
      }
      iVar13 = scan_effect_targets_for_collision_response_b
                         (param_1,iVar13,&local_124,local_13c,&local_15c);
    }
    if ((iVar13 == 0) &&
       (iVar13 = weapon_ordnance_query_context_helper_004a7800(param_1,&local_124), iVar13 != 0)) {
      local_13c[0] = 0;
      local_15c = -1;
    }
    iVar12 = local_148;
    local_158 = local_124 - local_130;
    local_154 = local_120 - local_12c;
    local_150 = local_11c - local_128;
    *(float *)(local_148 + 0x40) =
         SQRT(local_150 * local_150 + local_154 * local_154 + local_158 * local_158) +
         *(float *)(local_148 + 0x40);
    if (iVar13 == 0) {
      pfVar11 = (float *)zone_satellite_map_context_helper_00494880(&local_124,&local_158,local_bc);
      for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
        *pfVar10 = *pfVar11;
        pfVar11 = pfVar11 + 1;
        pfVar10 = pfVar10 + 1;
      }
      *local_14c = local_100;
      local_14c[1] = local_fc;
      local_14c[2] = local_f8;
    }
    else {
      if (local_140 != (LPVOID)0x0) {
        finalize_released_world_object_after_damage(local_140,s_ordnc_004fe6f0);
        local_140 = (LPVOID)0x0;
        *(undefined4 *)(iVar12 + 0x10) = 0;
      }
      if (SQRT(local_150 * local_150 + local_154 * local_154 + local_158 * local_158) <=
          _DAT_004bec1c) {
        *(double *)(param_1 + 0x40) = (double)local_124;
        *(double *)(param_1 + 0x48) = (double)local_120;
        *(double *)(param_1 + 0x50) = (double)local_11c;
      }
      else {
        pfVar11 = (float *)zone_satellite_map_context_helper_00494880
                                     (&local_124,&local_158,local_bc);
        for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
          *pfVar10 = *pfVar11;
          pfVar11 = pfVar11 + 1;
          pfVar10 = pfVar10 + 1;
        }
      }
      *local_14c = 0.0;
      local_14c[1] = 0.0;
      local_14c[2] = 0.0;
      spawn_mission_vehicle_effect_by_slot(param_1,&local_124,local_13c[0],local_15c);
    }
    vehicle_effect_audio_context_helper_00443150(param_1);
    return iVar13 == 0;
  }
  return false;
}


