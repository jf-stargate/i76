/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_004944d0
 * Entry: 004944d0
 * Signature: undefined __cdecl zone_satellite_map_context_helper_004944d0(float * param_1, float * param_2, float * param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_004944d0. Remove
   duplicated zone_satellite_map wording. */

void __cdecl
zone_satellite_map_context_helper_004944d0
          (float *param_1,float *param_2,float *param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_c;
  
  fVar1 = *param_2 * *param_3 +
          param_2[1] * param_3[1] + param_2[2] * param_3[2] + param_2[3] * param_3[3];
  if (fVar1 - _DAT_004be8d8 <= _DAT_004be8f4) {
    fVar1 = param_2[1];
    fVar2 = *param_2;
    local_1c = param_2[3];
    fVar3 = param_2[2];
    uVar5 = mission_flow_map_context_helper_0049d400((_DAT_004be8e8 - param_4) * _DAT_004be8f8);
    uVar6 = mission_flow_map_context_helper_0049d400(param_4 * _DAT_004be8f8);
    local_14 = (float)uVar5;
    local_18 = local_c * fVar3 + local_14 * param_2[3];
    local_c = (float)uVar6;
    local_24 = *param_2 * local_14 + local_c * -fVar1;
    local_20 = local_c * fVar2 + local_14 * param_2[1];
    local_14 = local_14 * param_2[2];
    local_1c = local_c * local_1c;
  }
  else {
    if (_DAT_004be8e8 - fVar1 <= _DAT_004be8f4) {
      local_14 = _DAT_004be8e8 - param_4;
    }
    else {
      fVar4 = (float10)fpatan((float10)SQRT(_DAT_004be8e8 - fVar1 * fVar1),(float10)fVar1);
      fVar1 = (float)fVar4;
      uVar5 = mission_flow_map_context_helper_0049d400(fVar1);
      fVar2 = _DAT_004be8e8 / (float)uVar5;
      uVar6 = mission_flow_map_context_helper_0049d400((_DAT_004be8e8 - param_4) * fVar1);
      mission_flow_map_context_helper_0049d400(fVar1 * param_4);
      local_14 = (float)uVar6;
      local_14 = local_14 * fVar2;
      param_4 = (float)uVar5 * fVar2;
    }
    local_18 = param_4 * param_3[3] + local_14 * param_2[3];
    local_24 = *param_2 * local_14 + *param_3 * param_4;
    local_20 = param_4 * param_3[1] + local_14 * param_2[1];
    local_14 = local_14 * param_2[2];
    local_1c = param_4 * param_3[2];
  }
  local_1c = local_1c + local_14;
  fVar1 = local_18 * local_18 + local_1c * local_1c + local_20 * local_20 + local_24 * local_24;
  if (_DAT_004be8f4 < _DAT_004be8e8 - fVar1) {
    fVar1 = (float)_DAT_004be900 / SQRT(fVar1);
    local_24 = fVar1 * local_24;
    local_20 = fVar1 * local_20;
    local_1c = fVar1 * local_1c;
    local_18 = fVar1 * local_18;
  }
  *param_1 = local_24;
  param_1[1] = local_20;
  param_1[2] = local_1c;
  param_1[3] = local_18;
  return;
}


