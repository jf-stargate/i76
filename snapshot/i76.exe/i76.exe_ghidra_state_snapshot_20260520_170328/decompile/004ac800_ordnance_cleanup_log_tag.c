/*
 * Program: i76.exe
 * Function: ordnance_cleanup_log_tag
 * Entry: 004ac800
 * Signature: undefined4 __cdecl ordnance_cleanup_log_tag(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

undefined4 __cdecl ordnance_cleanup_log_tag(int param_1,float param_2)

{
  float fVar1;
  int *piVar2;
  int iVar3;
  float *pfVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  undefined4 *puVar9;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  int local_150;
  uint local_14c;
  int local_148;
  LPVOID local_144;
  int local_140 [3];
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_110 [3];
  float local_104;
  float local_100;
  float local_fc;
  float local_ec;
  int local_e8;
  float local_e4;
  float local_e0;
  int local_cc;
  float *local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  undefined4 local_b8 [6];
  float local_a0;
  float local_9c;
  float local_98;
  float local_7c [31];
  
  iVar3 = *(int *)(param_1 + 0x70);
  local_c8 = (float *)(iVar3 + 0x14);
  local_150 = iVar3;
  get_runtime_frame_delta_seconds();
  piVar2 = (int *)build_vehicle_ordnance_runtime_context(local_7c,param_1);
  local_16c = 0.0;
  local_168 = 0.0;
  local_164 = 0.0;
  piVar8 = &local_148;
  for (iVar6 = 0x1f; iVar6 != 0; iVar6 = iVar6 + -1) {
    *piVar8 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar8 = piVar8 + 1;
  }
  local_15c = 0.0;
  local_158 = 0.0;
  local_154 = 0.0;
  local_160 = 0.0;
  uVar7 = (uint)(*(int *)(iVar3 + 0x48) == 0);
  local_14c = uVar7;
  if (uVar7 != 0) {
    if (((_DAT_004bec48 <= param_2) && (param_2 <= _DAT_004bec4c)) &&
       ((float)_DAT_004bec50 <= ABS(local_ec - local_fc))) {
      local_ec = (local_ec - local_fc) * param_2 + local_fc;
    }
    local_16c = *(float *)(param_1 + 0x30) * local_ec +
                *(float *)(param_1 + 0x24) * local_100 + *(float *)(param_1 + 0x18) * local_104;
    local_168 = *(float *)(param_1 + 0x34) * local_ec +
                *(float *)(param_1 + 0x1c) * local_104 + *(float *)(param_1 + 0x28) * local_100;
    local_164 = *(float *)(param_1 + 0x38) * local_ec +
                *(float *)(param_1 + 0x20) * local_104 + *(float *)(param_1 + 0x2c) * local_100;
    local_104 = local_16c;
    local_100 = local_168;
    local_fc = local_164;
    effect_target_list_scan_context_helper_004383a0(&local_128,&local_104,local_110,param_2);
    local_16c = *(float *)(param_1 + 0x1c) * local_100 +
                *(float *)(param_1 + 0x20) * local_fc + *(float *)(param_1 + 0x18) * local_104;
    local_168 = *(float *)(param_1 + 0x24) * local_104 +
                *(float *)(param_1 + 0x2c) * local_fc + *(float *)(param_1 + 0x28) * local_100;
    local_164 = *(float *)(param_1 + 0x34) * local_100 +
                *(float *)(param_1 + 0x30) * local_104 + *(float *)(param_1 + 0x38) * local_fc;
    local_104 = local_16c;
    local_100 = local_168;
    local_fc = local_164;
  }
  fVar1 = local_124;
  local_140[0] = 0;
  for (; local_124 = fVar1, 0 < local_e8; local_e8 = local_e8 + -1) {
    if (*(int *)(local_150 + 0x48) != 0) {
      local_124 = fVar1 - _DAT_004bec64;
    }
    iVar3 = local_148;
    if (_DAT_004bec58 < local_e0 - local_e4) {
      iVar3 = 0;
    }
    iVar3 = scan_effect_targets_for_vehicle_collision_response
                      (param_1,iVar3,&local_128,local_140,&local_cc);
    if (iVar3 != 0) {
      spawn_mission_vehicle_effect_by_slot(param_1,&local_128,local_140[0],local_cc);
      local_160 = 1.4013e-45;
    }
    iVar3 = local_150;
    uVar7 = local_14c;
  }
  if (uVar7 != 0) {
    iVar6 = weapon_ordnance_query_context_helper_004a7800(param_1,&local_128);
    if ((iVar6 != 0) || (local_160 != 0.0)) {
      local_14c = 0;
      *(undefined4 *)(iVar3 + 0x48) = 1;
      if (local_144 != (LPVOID)0x0) {
        finalize_released_world_object_after_damage(local_144,s_ordnc_004fe6f0);
        local_144 = (LPVOID)0x0;
        *(undefined4 *)(iVar3 + 0x10) = 0;
      }
      *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 1;
      probe_effect_target_surface_height_at_position
                ((double)CONCAT44(local_124,local_128),local_120,&local_160,(undefined4 *)0x0);
      local_124 = local_160;
      pfVar4 = (float *)sample_runtime_terrain_packed_word
                                  (&local_16c,(double)local_128,SUB84((double)local_120,0),
                                   (int)((ulonglong)(double)local_120 >> 0x20));
      local_c4 = *pfVar4;
      local_c0 = pfVar4[1];
      local_bc = pfVar4[2];
      puVar5 = (undefined4 *)
               zone_satellite_map_context_helper_00494710
                         (&local_c4,(float *)(param_1 + 0x30),local_7c);
      puVar9 = (undefined4 *)(param_1 + 0x18);
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar9 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar9 = puVar9 + 1;
      }
      *(double *)(param_1 + 0x40) = (double)local_128;
      *(double *)(param_1 + 0x48) = (double)local_124;
      *(double *)(param_1 + 0x50) = (double)local_120;
      puVar5 = (undefined4 *)ordnance_update_context_helper_004a0480(local_7c,param_1);
      puVar9 = local_b8;
      for (iVar3 = 0xf; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar9 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar9 = puVar9 + 1;
      }
      local_a0 = local_a0 * _DAT_004bec64;
      local_9c = local_9c * _DAT_004bec64;
      local_16c = 0.0;
      local_98 = local_98 * _DAT_004bec64;
      local_168 = 0.0;
      local_164 = 0.0;
      register_world_object_smoke_emitter(param_1,local_b8,0,0,0);
      set_world_object_smoke_emitter_mode(param_1,3);
      iVar3 = local_150;
      uVar7 = local_14c;
    }
    if (uVar7 != 0) {
      local_16c = local_128 - local_134;
      local_168 = local_124 - local_130;
      local_164 = local_120 - local_12c;
      *(float *)(iVar3 + 0x40) =
           SQRT(local_164 * local_164 + local_168 * local_168 + local_16c * local_16c) +
           *(float *)(iVar3 + 0x40);
      local_15c = local_16c;
      local_158 = local_168;
      local_154 = local_164;
      if (SQRT(local_164 * local_164 + local_168 * local_168 + local_16c * local_16c) <=
          _DAT_004bec5c) {
        *(double *)(param_1 + 0x40) = (double)local_128;
        *(double *)(param_1 + 0x48) = (double)local_124;
        *(double *)(param_1 + 0x50) = (double)local_120;
      }
      else {
        puVar5 = (undefined4 *)
                 zone_satellite_map_context_helper_00494880(&local_128,&local_15c,local_7c);
        puVar9 = (undefined4 *)(param_1 + 0x18);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar9 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar9 = puVar9 + 1;
        }
      }
      vehicle_effect_audio_context_helper_00443150(param_1);
      *local_c8 = local_104;
      local_c8[1] = local_100;
      local_c8[2] = local_fc;
    }
  }
  return 1;
}


