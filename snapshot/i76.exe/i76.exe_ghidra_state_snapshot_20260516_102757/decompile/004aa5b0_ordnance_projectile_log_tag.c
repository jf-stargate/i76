/*
 * Program: i76.exe
 * Function: ordnance_projectile_log_tag
 * Entry: 004aa5b0
 * Signature: bool __cdecl ordnance_projectile_log_tag(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

bool __cdecl ordnance_projectile_log_tag(int param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int *piVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int *piVar8;
  float *pfVar9;
  float10 fVar10;
  int local_110;
  float local_10c;
  float local_108;
  float local_104;
  float *local_100;
  int local_fc;
  int local_f8;
  LPVOID local_f4;
  int local_f0 [3];
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
  float local_7c [31];
  
  local_fc = *(int *)(param_1 + 0x70);
  local_100 = (float *)(local_fc + 0x14);
  fVar10 = get_runtime_frame_delta_seconds();
  piVar4 = (int *)build_vehicle_ordnance_runtime_context(local_7c,param_1);
  fVar1 = (float)fVar10 * _DAT_004bec00;
  piVar8 = &local_f8;
  for (iVar7 = 0x1f; iVar7 != 0; iVar7 = iVar7 + -1) {
    *piVar8 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar8 = piVar8 + 1;
  }
  if (((_DAT_004bec04 <= fVar1) && (fVar1 <= _DAT_004bec08)) &&
     ((float)_DAT_004bec10 <= ABS(local_9c - local_ac))) {
    local_9c = (local_9c - local_ac) * fVar1 + local_ac;
  }
  pfVar9 = (float *)(param_1 + 0x18);
  fVar2 = *(float *)(param_1 + 0x24) * local_b0;
  fVar1 = *(float *)(param_1 + 0x2c) * local_b0;
  local_b0 = *(float *)(param_1 + 0x34) * local_9c +
             *(float *)(param_1 + 0x28) * local_b0 + *(float *)(param_1 + 0x1c) * local_b4;
  local_ac = *(float *)(param_1 + 0x38) * local_9c + fVar1 + *(float *)(param_1 + 0x20) * local_b4;
  local_b4 = *(float *)(param_1 + 0x30) * local_9c + *(float *)(param_1 + 0x18) * local_b4 + fVar2;
  effect_target_list_scan_context_helper_004383a0(&local_d8,&local_b4,local_c0,param_2);
  fVar1 = *(float *)(param_1 + 0x1c) * local_b0;
  fVar2 = *(float *)(param_1 + 0x20) * local_ac;
  fVar3 = *(float *)(param_1 + 0x34) * local_b0;
  local_b0 = *(float *)(param_1 + 0x2c) * local_ac +
             *(float *)(param_1 + 0x28) * local_b0 + *(float *)(param_1 + 0x24) * local_b4;
  local_ac = *(float *)(param_1 + 0x38) * local_ac + fVar3 + *(float *)(param_1 + 0x30) * local_b4;
  iVar7 = 0;
  local_b4 = *pfVar9 * local_b4 + fVar2 + fVar1;
  for (; 0 < local_98; local_98 = local_98 + -1) {
    if (*(float *)(local_fc + 0x40) <= _DAT_004bec18) {
      iVar5 = scan_effect_targets_for_collision_response_b
                        (param_1,local_f8,&local_d8,local_f0,&local_110);
    }
    else {
      iVar5 = scan_effect_targets_for_collision_response_b(param_1,0,&local_d8,local_f0,&local_110);
    }
    if (iVar5 != 0) {
      iVar7 = 1;
    }
  }
  if ((iVar7 == 0) &&
     (iVar7 = weapon_ordnance_query_context_helper_004a7800(param_1,&local_d8), iVar7 != 0)) {
    local_f0[0] = 0;
    local_110 = -1;
  }
  iVar5 = local_fc;
  local_10c = local_d8 - local_e4;
  local_108 = local_d4 - local_e0;
  local_104 = local_d0 - local_dc;
  *(float *)(local_fc + 0x40) =
       SQRT(local_104 * local_104 + local_108 * local_108 + local_10c * local_10c) +
       *(float *)(local_fc + 0x40);
  if (iVar7 == 0) {
    pfVar6 = (float *)zone_satellite_map_context_helper_00494880(&local_d8,&local_10c,local_7c);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar9 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar9 = pfVar9 + 1;
    }
    *local_100 = local_b4;
    local_100[1] = local_b0;
    local_100[2] = local_ac;
  }
  else {
    if (local_f4 != (LPVOID)0x0) {
      finalize_released_world_object_after_damage(local_f4,s_ordnc_004fe6f0);
      local_f4 = (LPVOID)0x0;
      *(undefined4 *)(iVar5 + 0x10) = 0;
    }
    if (SQRT(local_104 * local_104 + local_108 * local_108 + local_10c * local_10c) <= _DAT_004bec1c
       ) {
      *(double *)(param_1 + 0x40) = (double)local_d8;
      *(double *)(param_1 + 0x48) = (double)local_d4;
      *(double *)(param_1 + 0x50) = (double)local_d0;
    }
    else {
      pfVar6 = (float *)zone_satellite_map_context_helper_00494880(&local_d8,&local_10c,local_7c);
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *pfVar9 = *pfVar6;
        pfVar6 = pfVar6 + 1;
        pfVar9 = pfVar9 + 1;
      }
    }
    *local_100 = 0.0;
    local_100[1] = 0.0;
    local_100[2] = 0.0;
    spawn_mission_vehicle_effect_by_slot(param_1,&local_d8,local_f0[0],local_110);
  }
  vehicle_effect_audio_context_helper_00443150(param_1);
  return iVar7 == 0;
}


