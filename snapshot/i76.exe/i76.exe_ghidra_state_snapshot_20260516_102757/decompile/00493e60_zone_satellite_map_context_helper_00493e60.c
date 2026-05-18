/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00493e60
 * Entry: 00493e60
 * Signature: undefined __cdecl zone_satellite_map_context_helper_00493e60(float * param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00493e60. Remove
   duplicated zone_satellite_map wording. */

void __cdecl
zone_satellite_map_context_helper_00493e60
          (float *param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  float local_c8;
  float local_c0 [6];
  float local_a8;
  float local_a0;
  double local_98;
  double local_90;
  double local_88;
  float local_80 [4];
  float local_70;
  float local_6c;
  float local_64;
  undefined4 local_60;
  float local_40 [16];
  
  pfVar2 = (float *)&DAT_004faed8;
  pfVar4 = local_c0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  uVar5 = mission_flow_map_context_helper_0049d400(param_3);
  local_c0[0] = (float)((ulonglong)uVar5 >> 0x20);
  fVar1 = (float)uVar5;
  pfVar2 = (float *)&DAT_004faed8;
  pfVar4 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  local_c0[2] = -fVar1;
  local_a8 = fVar1;
  local_a0 = local_c0[0];
  uVar5 = mission_flow_map_context_helper_0049d400(param_2);
  local_70 = (float)((ulonglong)uVar5 >> 0x20);
  local_64 = -fVar1;
  local_6c = fVar1;
  local_60 = local_70;
  pfVar2 = compose_matrix_or_transform_a(local_40,local_80,local_c0);
  pfVar4 = local_c0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  pfVar2 = (float *)&DAT_004faed8;
  pfVar4 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  uVar6 = mission_flow_map_context_helper_0049d400(param_4);
  local_80[0] = (float)((ulonglong)uVar6 >> 0x20);
  local_c8 = (float)uVar5;
  local_80[3] = local_c8;
  local_c8 = (float)uVar6;
  local_80[1] = local_c8;
  local_80[3] = -local_80[3];
  local_70 = local_80[0];
  pfVar2 = compose_matrix_or_transform_a(local_40,local_80,local_c0);
  pfVar4 = local_c0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar4 = pfVar4 + 1;
  }
  local_98 = (double)param_5;
  local_90 = (double)param_6;
  local_88 = (double)param_7;
  pfVar2 = local_c0;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


