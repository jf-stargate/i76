/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00493da0
 * Entry: 00493da0
 * Signature: undefined __cdecl zone_satellite_map_context_helper_00493da0(float * param_1, float param_2)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00493da0. Remove
   duplicated zone_satellite_map wording. */

void __cdecl zone_satellite_map_context_helper_00493da0(float *param_1,float param_2)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  undefined8 uVar4;
  float local_40 [6];
  float local_28;
  float local_20;
  
  pfVar2 = (float *)&DAT_004faed8;
  pfVar3 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar3 = pfVar3 + 1;
  }
  uVar4 = mission_flow_map_context_helper_0049d400(param_2);
  local_40[0] = (float)((ulonglong)uVar4 >> 0x20);
  local_28 = (float)uVar4;
  local_40[2] = -(float)uVar4;
  local_20 = local_40[0];
  pfVar2 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


