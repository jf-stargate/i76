/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00494460
 * Entry: 00494460
 * Signature: undefined __cdecl zone_satellite_map_context_helper_00494460(undefined4 * param_1, float param_2, float param_3, float param_4, float param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00494460. Remove
   duplicated zone_satellite_map wording. */

void __cdecl
zone_satellite_map_context_helper_00494460
          (undefined4 *param_1,float param_2,float param_3,float param_4,float param_5)

{
  undefined4 *puVar1;
  int iVar2;
  undefined8 uVar3;
  float local_58;
  float local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  float local_40 [16];
  
  uVar3 = mission_flow_map_context_helper_0049d400(param_2 * _DAT_004be8f0);
  local_44 = (undefined4)((ulonglong)uVar3 >> 0x20);
  local_50 = local_58 * param_3;
  local_58 = (float)uVar3;
  local_4c = local_58 * param_4;
  local_48 = local_58 * param_5;
  puVar1 = (undefined4 *)zone_satellite_map_context_helper_00494170(&local_50,local_40);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar1;
    puVar1 = puVar1 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


