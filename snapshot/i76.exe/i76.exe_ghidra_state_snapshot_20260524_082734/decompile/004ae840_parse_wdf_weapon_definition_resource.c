/*
 * Program: i76.exe
 * Function: parse_wdf_weapon_definition_resource
 * Entry: 004ae840
 * Signature: bool __cdecl parse_wdf_weapon_definition_resource(byte * param_1, byte * param_2)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Parses a WDF weapon component
   definition resource. */

bool __cdecl parse_wdf_weapon_definition_resource(byte *param_1,byte *param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  byte *pbVar3;
  
  pbVar3 = param_2;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pbVar3[0] = 0;
    pbVar3[1] = 0;
    pbVar3[2] = 0;
    pbVar3[3] = 0;
    pbVar3 = pbVar3 + 4;
  }
  bVar1 = parse_bwd2_resource_with_descriptor_table(param_1,&WDF_descriptor_table,3,param_2);
  return CONCAT31(extraout_var,bVar1) != 0;
}


