/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00494880
 * Entry: 00494880
 * Signature: undefined __fastcall zone_satellite_map_context_helper_00494880(float * param_1, float * param_2, float * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00494880. Remove
   duplicated zone_satellite_map wording. */

void __fastcall
zone_satellite_map_context_helper_00494880(float *param_1,float *param_2,float *param_3)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float *pfVar6;
  float10 fVar7;
  float local_64;
  float fStack_60;
  float local_5c;
  float local_40 [4];
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  double local_18;
  double local_10;
  double local_8;
  
  fVar2 = *param_2;
  fVar3 = param_2[1];
  fVar4 = param_2[2];
  local_18 = (double)*param_1;
  local_10 = (double)param_1[1];
  local_8 = (double)param_1[2];
  dVar1 = (double)(fVar4 * fVar4 + fVar3 * fVar3 + fVar2 * fVar2);
  fVar7 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  local_24 = (float)fVar7;
  local_28 = fVar2 * local_24;
  local_20 = fVar4 * local_24;
  local_24 = fVar3 * local_24;
  if ((float)_DAT_004be908 <= local_20 * local_20 + local_28 * local_28) {
    local_64 = local_20 - _DAT_004be8ec;
    local_5c = _DAT_004be8ec - local_28;
    dVar1 = (double)(local_5c * local_5c + local_64 * local_64 + 0.0);
    fVar7 = zone_satellite_map_context_helper_00495000
                      (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
    fVar2 = (float)fVar7;
    local_64 = local_64 * fVar2;
    fStack_60 = fVar2 * 0.0;
    local_5c = local_5c * fVar2;
  }
  else {
    local_64 = 1.0;
    fStack_60 = 0.0;
    local_5c = 0.0;
  }
  local_40[1] = fStack_60;
  local_40[0] = local_64;
  local_40[2] = local_5c;
  local_30 = local_20 * local_64 - local_28 * local_5c;
  local_40[3] = local_24 * local_5c - local_20 * fStack_60;
  local_2c = local_28 * fStack_60 - local_24 * local_64;
  pfVar6 = local_40;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *param_3 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    param_3 = param_3 + 1;
  }
  return;
}


