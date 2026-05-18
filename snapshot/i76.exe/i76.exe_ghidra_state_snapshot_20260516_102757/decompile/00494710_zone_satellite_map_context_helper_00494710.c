/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00494710
 * Entry: 00494710
 * Signature: undefined __fastcall zone_satellite_map_context_helper_00494710(float * param_1, float * param_2, float * param_3)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00494710. Remove
   duplicated zone_satellite_map wording. */

void __fastcall
zone_satellite_map_context_helper_00494710(float *param_1,float *param_2,float *param_3)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float *pfVar6;
  float10 fVar7;
  float local_40 [4];
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  fVar4 = param_2[2] * param_1[1] - param_2[1] * param_1[2];
  fVar2 = *param_2 * param_1[2] - *param_1 * param_2[2];
  local_40[3] = *param_1;
  local_18 = 0;
  fVar3 = *param_1 * param_2[1] - *param_2 * param_1[1];
  local_30 = param_1[1];
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_2c = param_1[2];
  local_8 = 0;
  local_4 = 0;
  dVar1 = (double)(fVar3 * fVar3 + fVar2 * fVar2 + fVar4 * fVar4);
  fVar7 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  local_40[2] = (float)fVar7;
  local_40[0] = fVar4 * local_40[2];
  local_40[1] = fVar2 * local_40[2];
  local_40[2] = fVar3 * local_40[2];
  local_28 = local_40[1] * param_1[2] - local_40[2] * param_1[1];
  local_24 = *param_1 * local_40[2] - local_40[0] * param_1[2];
  local_20 = local_40[0] * param_1[1] - *param_1 * local_40[1];
  pfVar6 = local_40;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *param_3 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    param_3 = param_3 + 1;
  }
  return;
}


