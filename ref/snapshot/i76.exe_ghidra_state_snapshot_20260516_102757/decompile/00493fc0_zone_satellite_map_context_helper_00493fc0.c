/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00493fc0
 * Entry: 00493fc0
 * Signature: undefined4 __cdecl zone_satellite_map_context_helper_00493fc0(float * param_1, float * param_2, float * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00493fc0. Remove
   duplicated zone_satellite_map wording. */

undefined4 __cdecl
zone_satellite_map_context_helper_00493fc0(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  float local_80 [4];
  float local_70;
  float local_60;
  float local_40 [16];
  
  local_80[0] = *param_2;
  local_70 = param_2[1];
  fVar1 = *param_3;
  local_60 = param_2[2];
  fVar2 = param_3[1];
  fVar3 = param_3[2];
  fVar4 = fVar3 * local_60 + fVar2 * local_70 + fVar1 * local_80[0];
  if (fVar4 < (float)_DAT_004be8c8) {
    return 0;
  }
  fVar4 = (float)_DAT_004be8d0 / fVar4;
  pfVar5 = (float *)&DAT_004faed8;
  pfVar7 = local_80;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar7 = pfVar7 + 1;
  }
  local_80[0] = local_80[0] * fVar4;
  local_70 = local_70 * fVar4;
  local_60 = local_60 * fVar4;
  *param_1 = fVar1;
  param_1[1] = fVar2;
  param_1[2] = fVar3;
  param_1[3] = fVar1;
  param_1[4] = fVar2;
  param_1[5] = fVar3;
  param_1[6] = fVar1;
  param_1[7] = fVar2;
  param_1[8] = fVar3;
  *(double *)(param_1 + 10) = (double)fVar1;
  *(double *)(param_1 + 0xc) = (double)fVar2;
  *(double *)(param_1 + 0xe) = (double)fVar3;
  pfVar5 = compose_matrix_or_transform_a(local_40,local_80,param_1);
  pfVar7 = param_1;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar7 = pfVar7 + 1;
  }
  fVar4 = param_2[3] * fVar4;
  *(double *)(param_1 + 10) = (double)(fVar4 * (float)*(double *)(param_1 + 10));
  fVar1 = *param_1 - _DAT_004be8d8;
  fVar2 = param_1[4] - _DAT_004be8d8;
  fVar3 = param_1[8] - _DAT_004be8d8;
  *(double *)(param_1 + 0xc) = (double)(fVar4 * (float)*(double *)(param_1 + 0xc));
  *(double *)(param_1 + 0xe) = (double)(fVar4 * (float)*(double *)(param_1 + 0xe));
  *param_1 = fVar1;
  param_1[4] = fVar2;
  param_1[8] = fVar3;
  return 1;
}


