/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00493e00
 * Entry: 00493e00
 * Signature: undefined __cdecl zone_satellite_map_context_helper_00493e00(undefined4 * param_1, float param_2)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00493e00. Remove
   duplicated zone_satellite_map wording. */

void __cdecl zone_satellite_map_context_helper_00493e00(undefined4 *param_1,float param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  undefined4 local_40 [4];
  undefined4 local_30;
  float local_2c;
  float local_24;
  undefined4 local_20;
  
  puVar2 = &DAT_004faed8;
  puVar3 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  uVar4 = mission_flow_map_context_helper_0049d400(param_2);
  local_30 = (undefined4)((ulonglong)uVar4 >> 0x20);
  local_2c = (float)uVar4;
  local_24 = -(float)uVar4;
  local_20 = local_30;
  puVar2 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


