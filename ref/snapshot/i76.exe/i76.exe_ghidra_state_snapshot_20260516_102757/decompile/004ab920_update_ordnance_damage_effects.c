/*
 * Program: i76.exe
 * Function: update_ordnance_damage_effects
 * Entry: 004ab920
 * Signature: bool __cdecl update_ordnance_damage_effects(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

bool __cdecl update_ordnance_damage_effects(int param_1,float param_2)

{
  float fVar1;
  int *piVar2;
  float *pfVar3;
  int iVar4;
  LPVOID pvVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  float *pfVar9;
  float10 fVar10;
  float local_13c;
  int local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float *local_10c;
  float *local_108;
  int local_104;
  LPVOID local_100;
  int local_fc [3];
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_a8;
  int local_a4;
  float local_84;
  float local_80;
  float local_7c [31];
  
  local_10c = (float *)(*(int *)(param_1 + 0x70) + 0x40);
  fVar10 = get_runtime_frame_delta_seconds();
  iVar7 = *(int *)(param_1 + 0x70);
  fVar1 = (float)fVar10;
  local_108 = (float *)(iVar7 + 0x14);
  piVar2 = (int *)build_vehicle_ordnance_runtime_context(local_7c,param_1);
  piVar8 = &local_104;
  for (iVar6 = 0x1f; iVar6 != 0; iVar6 = iVar6 + -1) {
    *piVar8 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar8 = piVar8 + 1;
  }
  if ((fVar1 < _DAT_004bec04) || (_DAT_004bec08 < fVar1)) {
    local_13c = local_a8;
  }
  else if ((float)_DAT_004bec10 <= ABS(local_a8 - local_b8)) {
    local_13c = (local_a8 - local_b8) * fVar1 + local_b8;
  }
  else {
    local_13c = local_a8;
  }
  pfVar9 = (float *)(param_1 + 0x18);
  local_124 = *(float *)(param_1 + 0x30) * local_13c +
              *(float *)(param_1 + 0x18) * local_c0 + *(float *)(param_1 + 0x24) * local_bc;
  local_120 = *(float *)(param_1 + 0x34) * local_13c +
              *(float *)(param_1 + 0x1c) * local_c0 + *(float *)(param_1 + 0x28) * local_bc;
  local_e4 = local_124 * param_2 + local_f0;
  local_e0 = local_120 * param_2 + local_ec;
  local_11c = *(float *)(param_1 + 0x38) * local_13c +
              *(float *)(param_1 + 0x20) * local_c0 + *(float *)(param_1 + 0x2c) * local_bc;
  local_dc = local_11c * param_2 + local_e8;
  iVar6 = 0;
  local_c0 = local_124 * *pfVar9 +
             *(float *)(param_1 + 0x1c) * local_120 + *(float *)(param_1 + 0x20) * local_11c;
  local_bc = *(float *)(param_1 + 0x2c) * local_11c +
             *(float *)(param_1 + 0x28) * local_120 + *(float *)(param_1 + 0x24) * local_124;
  local_b8 = *(float *)(param_1 + 0x38) * local_11c +
             *(float *)(param_1 + 0x34) * local_120 + *(float *)(param_1 + 0x30) * local_124;
  local_84 = local_120;
  local_80 = local_11c;
  for (; 0 < local_a4; local_a4 = local_a4 + -1) {
    iVar6 = local_104;
    if (_DAT_004bec18 < *local_10c) {
      iVar6 = 0;
    }
    iVar6 = scan_effect_targets_for_collision_response_b
                      (param_1,iVar6,&local_e4,local_fc,&local_128);
  }
  if ((iVar6 == 0) &&
     (iVar6 = weapon_ordnance_query_context_helper_004a7800(param_1,&local_e4), iVar6 != 0)) {
    local_fc[0] = 0;
    local_128 = -1;
  }
  local_118 = local_e4 - local_f0;
  local_114 = local_e0 - local_ec;
  local_110 = local_dc - local_e8;
  *local_10c = SQRT(local_110 * local_110 + local_114 * local_114 + local_118 * local_118) +
               *local_10c;
  if (iVar6 == 0) {
    *(double *)(param_1 + 0x40) = (double)local_e4;
    *(double *)(param_1 + 0x48) = (double)local_e0;
    *(double *)(param_1 + 0x50) = (double)local_dc;
    *local_108 = local_c0;
    local_108[1] = local_bc;
    local_108[2] = local_b8;
    iVar4 = test_effect_target_forward_alignment(param_1,(int)local_100);
    if (iVar4 == 0) {
      if (local_100 != (LPVOID)0x0) {
        finalize_released_world_object_after_damage(local_100,s_ordnc_004fe6f0);
        *(undefined4 *)(iVar7 + 0x10) = 0;
      }
      pvVar5 = (LPVOID)raycast_weapon_fire_from_muzzle_transform(param_1,local_104);
      increment_refcount_recursive_for_object_tree((int)pvVar5,s_ordnc_004fe6f0);
      pvVar5 = release_world_object_tree_reference(pvVar5,s_ordnc_004fe6f0);
      *(LPVOID *)(iVar7 + 0x10) = pvVar5;
      if (pvVar5 == (LPVOID)0x0) {
        if (_DAT_004bec1c <
            SQRT(local_110 * local_110 + local_114 * local_114 + local_118 * local_118)) {
          pfVar3 = (float *)zone_satellite_map_context_helper_00494880
                                      (&local_e4,&local_118,local_7c);
          for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
            *pfVar9 = *pfVar3;
            pfVar3 = pfVar3 + 1;
            pfVar9 = pfVar9 + 1;
          }
        }
      }
      else {
        weapon_ordnance_query_context_helper_004a7bb0(param_1,(float)pvVar5);
      }
    }
    else {
      weapon_ordnance_query_context_helper_004a7bb0(param_1,(float)local_100);
    }
  }
  else {
    if (local_100 != (LPVOID)0x0) {
      finalize_released_world_object_after_damage(local_100,s_ordnc_004fe6f0);
      *(undefined4 *)(iVar7 + 0x10) = 0;
    }
    if (SQRT(local_11c * local_11c + local_120 * local_120 + local_124 * local_124) <= _DAT_004bec1c
       ) {
      *(double *)(param_1 + 0x40) = (double)local_e4;
      *(double *)(param_1 + 0x48) = (double)local_e0;
      *(double *)(param_1 + 0x50) = (double)local_dc;
    }
    else {
      pfVar3 = (float *)zone_satellite_map_context_helper_00494880(&local_e4,&local_124,local_7c);
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        *pfVar9 = *pfVar3;
        pfVar3 = pfVar3 + 1;
        pfVar9 = pfVar9 + 1;
      }
    }
    *local_108 = 0.0;
    local_108[1] = 0.0;
    local_108[2] = 0.0;
    spawn_mission_vehicle_effect_by_slot(param_1,&local_e4,local_fc[0],local_128);
  }
  vehicle_effect_audio_context_helper_00443150(param_1);
  return iVar6 == 0;
}


