/*
 * Program: i76.exe
 * Function: parse_gdf_equipment_definition_resource
 * Entry: 004af340
 * Signature: bool __cdecl parse_gdf_equipment_definition_resource(byte * param_1, byte * param_2)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Parses a GDF equipment component
   definition resource. */

bool __cdecl parse_gdf_equipment_definition_resource(byte *param_1,byte *param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  
  bVar1 = parse_bwd2_resource_with_descriptor_table(param_1,&GDF_descriptor_table,6,param_2);
  return CONCAT31(extraout_var,bVar1) != 0;
}


