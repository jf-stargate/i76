/*
 * Program: i76.exe
 * Function: ordnance_damage_log_tag
 * Entry: 004abe60
 * Signature: bool __cdecl ordnance_damage_log_tag(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

bool __cdecl ordnance_damage_log_tag(int param_1,float param_2)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  int *piVar9;
  float *pfVar10;
  float10 fVar11;
  float local_11c;
  float local_118;
  float local_114;
  undefined8 local_110;
  float local_108;
  float local_104;
  float *local_100;
  int local_fc;
  int local_f8;
  LPVOID local_f4;
  int local_f0;
  int local_ec;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_c0 [3];
  float local_b4;
  float local_b0;
  float local_ac;
  float local_9c;
  int local_98;
  float local_94;
  float local_90;
  float local_7c [31];
  
  local_110 = CONCAT44(local_110._4_4_,*(int *)(param_1 + 0x70));
  local_100 = (float *)(*(int *)(param_1 + 0x70) + 0x14);
  fVar11 = get_runtime_frame_delta_seconds();
  local_104 = (float)fVar11;
  piVar5 = (int *)build_vehicle_ordnance_runtime_context(local_7c,param_1);
  piVar9 = &local_f8;
  for (iVar8 = 0x1f; iVar8 != 0; iVar8 = iVar8 + -1) {
    *piVar9 = *piVar5;
    piVar5 = piVar5 + 1;
    piVar9 = piVar9 + 1;
  }
  if (((_DAT_004bec48 <= local_104) && (local_104 <= _DAT_004bec4c)) &&
     ((float)_DAT_004bec50 <= ABS(local_9c - local_ac))) {
    local_9c = (local_9c - local_ac) * local_104 + local_ac;
  }
  pfVar10 = (float *)(param_1 + 0x18);
  fVar3 = *(float *)(param_1 + 0x24) * local_b0;
  fVar2 = *(float *)(param_1 + 0x2c) * local_b0;
  local_b0 = *(float *)(param_1 + 0x34) * local_9c +
             *(float *)(param_1 + 0x1c) * local_b4 + *(float *)(param_1 + 0x28) * local_b0;
  local_ac = *(float *)(param_1 + 0x38) * local_9c + *(float *)(param_1 + 0x20) * local_b4 + fVar2;
  local_b4 = *(float *)(param_1 + 0x30) * local_9c + local_b4 * *pfVar10 + fVar3;
  effect_target_list_scan_context_helper_004383a0(&local_d8,&local_b4,local_c0,param_2);
  fVar2 = *(float *)(param_1 + 0x20) * local_ac;
  fVar3 = *(float *)(param_1 + 0x1c) * local_b0;
  fVar4 = *(float *)(param_1 + 0x34) * local_b0;
  local_b0 = *(float *)(param_1 + 0x24) * local_b4 +
             *(float *)(param_1 + 0x28) * local_b0 + *(float *)(param_1 + 0x2c) * local_ac;
  local_ac = *(float *)(param_1 + 0x30) * local_b4 + fVar4 + *(float *)(param_1 + 0x38) * local_ac;
  iVar8 = 0;
  local_f0 = 0;
  local_b4 = local_b4 * *pfVar10 + fVar3 + fVar2;
  for (; 0 < local_98; local_98 = local_98 + -1) {
    iVar6 = local_f8;
    if (_DAT_004bec58 < local_90 - local_94) {
      iVar6 = 0;
    }
    iVar6 = scan_effect_targets_for_collision_response_b
                      (param_1,iVar6,&local_d8,&local_f0,&local_fc);
    if (iVar6 != 0) {
      iVar8 = 1;
    }
  }
  if ((iVar8 == 0) &&
     (iVar8 = weapon_ordnance_query_context_helper_004a7800(param_1,&local_d8), iVar8 != 0)) {
    local_fc = -1;
    local_f0 = 0;
  }
  local_11c = local_d8 - local_e4;
  local_118 = local_d4 - local_e0;
  local_114 = local_d0 - local_dc;
  iVar6 = (int)local_110;
  *(float *)((int)local_110 + 0x40) =
       SQRT(local_114 * local_114 + local_118 * local_118 + local_11c * local_11c) +
       *(float *)((int)local_110 + 0x40);
  if (iVar8 == 0) {
    *(double *)(param_1 + 0x40) = (double)local_d8;
    *(double *)(param_1 + 0x48) = (double)local_d4;
    *(double *)(param_1 + 0x50) = (double)local_d0;
    *local_100 = local_b4;
    local_100[1] = local_b0;
    local_100[2] = local_ac;
  }
  else {
    if (local_f4 != (LPVOID)0x0) {
      finalize_released_world_object_after_damage(local_f4,s_ordnc_004fe6f0);
      local_f4 = (LPVOID)0x0;
      *(undefined4 *)(iVar6 + 0x10) = 0;
    }
    if (SQRT(local_114 * local_114 + local_118 * local_118 + local_11c * local_11c) <= _DAT_004bec5c
       ) {
      *(double *)(param_1 + 0x40) = (double)local_d8;
      *(double *)(param_1 + 0x48) = (double)local_d4;
      *(double *)(param_1 + 0x50) = (double)local_d0;
    }
    else {
      pfVar7 = (float *)zone_satellite_map_context_helper_00494880(&local_d8,&local_11c,local_7c);
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pfVar10 = *pfVar7;
        pfVar7 = pfVar7 + 1;
        pfVar10 = pfVar10 + 1;
      }
    }
    *local_100 = 0.0;
    local_100[1] = 0.0;
    local_100[2] = 0.0;
    dVar1 = (double)(local_114 * local_114 + local_118 * local_118 + local_11c * local_11c);
    fVar11 = zone_satellite_map_context_helper_00495000
                       (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
    fVar2 = (float)fVar11;
    local_108 = local_114 * fVar2;
    local_110 = CONCAT44(local_118 * fVar2,local_11c * fVar2);
    fVar3 = -(local_118 * fVar2);
    fVar2 = -(local_11c * fVar2);
    local_d8 = fVar2 + fVar2 + local_d8;
    local_d4 = fVar3 + fVar3 + local_d4;
    local_d0 = -local_108 + -local_108 + local_d0;
    spawn_mission_vehicle_effect_by_slot(param_1,&local_d8,local_f0,local_fc);
  }
  if (local_ec == 1) {
LAB_004ac395:
    iVar6 = 2;
  }
  else {
    if (local_ec != 6) {
      if (local_ec != 0x12) goto LAB_004ac3a0;
      goto LAB_004ac395;
    }
    iVar6 = 1;
  }
  update_projectile_tracer_runtime_record_for_object(param_1,iVar6);
LAB_004ac3a0:
  return iVar8 == 0;
}


