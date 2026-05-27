/*
 * Program: i76.exe
 * Function: parse_vcfc_vehicle_config_resource
 * Entry: 004ad8c0
 * Signature: undefined __cdecl parse_vcfc_vehicle_config_resource(byte * param_1, undefined4 param_2)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Wrapper around
   parse_bwd2_resource_with_descriptor_table using the VCFC descriptor table at 004fefb0. */

void __cdecl parse_vcfc_vehicle_config_resource(byte *param_1,undefined4 param_2)

{
  byte *pbVar1;
  int iVar2;
  byte local_54 [4];
  undefined4 local_50;
  
  pbVar1 = local_54;
  for (iVar2 = 0x15; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pbVar1 = 0;
    pbVar1 = (byte *)((int)pbVar1 + 4);
  }
  local_50 = param_2;
  parse_bwd2_resource_with_descriptor_table(param_1,&VCFC_descriptor_table,4,local_54);
  return;
}


