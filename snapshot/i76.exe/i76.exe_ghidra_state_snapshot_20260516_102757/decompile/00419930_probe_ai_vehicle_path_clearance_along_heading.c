/*
 * Program: i76.exe
 * Function: probe_ai_vehicle_path_clearance_along_heading
 * Entry: 00419930
 * Signature: undefined4 __cdecl probe_ai_vehicle_path_clearance_along_heading(float * param_1, float * param_2, undefined4 param_3, float param_4, float * param_5, float param_6, int param_7, float * param_8)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Samples transformed positions along a
   heading/trajectory and returns whether the projected path has clearance. */

undefined4 __cdecl
probe_ai_vehicle_path_clearance_along_heading
          (float *param_1,float *param_2,undefined4 param_3,float param_4,float *param_5,
          float param_6,int param_7,float *param_8)

{
  double dVar1;
  double dVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  uint uVar11;
  float10 extraout_ST0;
  float10 fVar12;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float10 extraout_ST0_03;
  float10 extraout_ST0_04;
  float local_70;
  float local_6c;
  float local_68;
  float local_5c;
  
  fVar3 = param_1[6];
  fVar4 = param_1[8];
  if (param_7 != 0) {
    apply_world_object_transform_to_bounds_or_geometry((double)*param_2,(double)param_2[2]);
    local_70 = 2.0;
    fVar12 = extraout_ST0;
    while( true ) {
      local_68 = (float)fVar12;
      fVar5 = fVar3 * param_6 * local_70 + *param_2;
      fVar6 = fVar4 * param_6 * local_70 + param_2[2];
      if ((_DAT_004bc914 < param_6) &&
         (uVar11 = terrain_map_context_helper_004926f0((double)fVar5,(double)fVar6), uVar11 != 0)) {
        *param_8 = 0.0;
        return 1;
      }
      apply_world_object_transform_to_bounds_or_geometry((double)fVar5,(double)fVar6);
      if ((extraout_ST0_00 - (float10)local_68 < (float10)_DAT_004bc8f0) ||
         ((float10)_DAT_004bca10 < extraout_ST0_00 - (float10)local_68)) break;
      local_70 = local_70 - _DAT_004bca14;
      fVar12 = extraout_ST0_00;
      if (_DAT_004bca18 < local_70) {
        return 0;
      }
    }
    if (local_70 <= _DAT_004bca1c) {
      *param_5 = local_70;
      return 1;
    }
    *param_5 = _DAT_004bca1c;
    return 1;
  }
  fVar10 = param_2[2] - param_1[2] * _DAT_004bca20;
  fVar6 = *param_2 - *param_1 * _DAT_004bca20;
  fVar5 = *param_2 - *param_1 * _DAT_004bca14;
  fVar9 = param_2[2] - param_1[2] * _DAT_004bca14;
  apply_world_object_transform_to_bounds_or_geometry((double)fVar6,(double)fVar10);
  local_6c = (float)extraout_ST0_01;
  apply_world_object_transform_to_bounds_or_geometry((double)fVar5,(double)fVar9);
  local_68 = param_4 * _DAT_004bca24;
  if (local_68 < _DAT_004bc9a4) {
    local_68 = 20.0;
  }
  local_70 = 2.5;
  fVar12 = extraout_ST0_02;
  if (local_68 < _DAT_004bca20) {
    return 0;
  }
  while( true ) {
    local_5c = (float)fVar12;
    fVar8 = fVar4 * param_6 * local_70;
    fVar7 = fVar3 * param_6 * local_70;
    dVar1 = (double)(fVar10 + fVar8);
    dVar2 = (double)(fVar6 + fVar7);
    uVar11 = terrain_map_context_helper_004926f0(dVar2,dVar1);
    if (uVar11 != 0) {
      if ((_DAT_004bc934 < param_4) && (param_4 < _DAT_004bc938)) {
        *param_8 = 3.4028235e+38;
        return 1;
      }
      *param_8 = local_70 / param_4;
      return 1;
    }
    apply_world_object_transform_to_bounds_or_geometry(dVar2,dVar1);
    if ((extraout_ST0_03 - (float10)local_6c < (float10)_DAT_004bc918) ||
       ((float10)_DAT_004bca24 < extraout_ST0_03 - (float10)local_6c)) break;
    local_6c = (float)extraout_ST0_03;
    apply_world_object_transform_to_bounds_or_geometry
              ((double)(fVar5 + fVar7),(double)(fVar9 + fVar8));
    if ((extraout_ST0_04 - (float10)local_5c < (float10)_DAT_004bc918) ||
       ((((float10)_DAT_004bca24 < extraout_ST0_04 - (float10)local_5c ||
         ((float10)local_6c - extraout_ST0_04 < (float10)_DAT_004bc8e0)) ||
        ((float10)_DAT_004bca24 < (float10)local_6c - extraout_ST0_04)))) break;
    local_70 = local_70 - _DAT_004bca14;
    fVar12 = extraout_ST0_04;
    if (local_68 < local_70) {
      return 0;
    }
  }
  if ((param_4 <= _DAT_004bc934) || (_DAT_004bc938 <= param_4)) {
    *param_8 = local_70 / param_4;
  }
  else {
    *param_8 = 3.4028235e+38;
  }
  if (local_70 <= _DAT_004bca1c) {
    *param_5 = local_70;
    return 1;
  }
  *param_5 = _DAT_004bca1c;
  return 1;
}


