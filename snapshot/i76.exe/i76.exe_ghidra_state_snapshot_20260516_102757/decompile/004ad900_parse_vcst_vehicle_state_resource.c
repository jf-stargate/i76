/*
 * Program: i76.exe
 * Function: parse_vcst_vehicle_state_resource
 * Entry: 004ad900
 * Signature: undefined __cdecl parse_vcst_vehicle_state_resource(byte * param_1, int param_2)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=high] Wrapper around
   parse_bwd2_resource_with_descriptor_table using the VCST descriptor table at 004ff180 and
   clearing output +0xbc before parse. */

void __cdecl parse_vcst_vehicle_state_resource(byte *param_1,int param_2)

{
  byte *pbVar1;
  int iVar2;
  byte local_54 [4];
  int local_50;
  
  pbVar1 = local_54;
  for (iVar2 = 0x15; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pbVar1 = 0;
    pbVar1 = (byte *)((int)pbVar1 + 4);
  }
  local_50 = param_2;
  *(undefined4 *)(param_2 + 0xbc) = 0;
  parse_bwd2_resource_with_descriptor_table(param_1,&VCST_descriptor_table,5,local_54);
  return;
}


