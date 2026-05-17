/*
 * Program: i76.exe
 * Function: load_engine_brake_suspension_component_definition
 * Entry: 004b1010
 * Signature: undefined4 __cdecl load_engine_brake_suspension_component_definition(undefined4 param_1, int param_2, byte * param_3)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=high] Loads engine/brake/suspension
   component definitions and reports missing component diagnostics. */

undefined4 __cdecl
load_engine_brake_suspension_component_definition(undefined4 param_1,int param_2,byte *param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  byte *pbVar3;
  
  pbVar3 = param_3;
  for (iVar2 = 0x2c; iVar2 != 0; iVar2 = iVar2 + -1) {
    pbVar3[0] = 0;
    pbVar3[1] = 0;
    pbVar3[2] = 0;
    pbVar3[3] = 0;
    pbVar3 = pbVar3 + 4;
  }
  if (param_2 == 0) {
    param_3[0x3c] = 0;
    param_3[0x3d] = 0;
    param_3[0x3e] = 0;
    param_3[0x3f] = 0;
    *(undefined4 *)(param_3 + 4) = param_1;
    param_3[0x74] = 0;
    param_3[0x75] = 0;
    param_3[0x76] = 0;
    param_3[0x77] = 0;
  }
  else if (param_2 == 1) {
    param_3[4] = 0;
    param_3[5] = 0;
    param_3[6] = 0;
    param_3[7] = 0;
    *(undefined4 *)(param_3 + 0x3c) = param_1;
    param_3[0x74] = 0;
    param_3[0x75] = 0;
    param_3[0x76] = 0;
    param_3[0x77] = 0;
  }
  else if (param_2 == 2) {
    param_3[4] = 0;
    param_3[5] = 0;
    param_3[6] = 0;
    param_3[7] = 0;
    param_3[0x3c] = 0;
    param_3[0x3d] = 0;
    param_3[0x3e] = 0;
    param_3[0x3f] = 0;
    *(undefined4 *)(param_3 + 0x74) = param_1;
  }
  bVar1 = parse_bwd2_resource_with_descriptor_table
                    ((byte *)s_compnent_cdf_004ffcd0,&DAT_004ff450,0xd,param_3);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    return 0;
  }
  if (*(int *)(param_3 + 8) == 0) {
    report_chunk_parse_error();
  }
  if (*(int *)(param_3 + 0x40) == 0) {
    report_chunk_parse_error();
  }
  if (*(int *)(param_3 + 0x78) == 0) {
    report_chunk_parse_error();
  }
  return 1;
}


