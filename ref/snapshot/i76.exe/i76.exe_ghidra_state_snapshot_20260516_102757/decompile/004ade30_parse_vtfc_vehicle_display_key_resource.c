/*
 * Program: i76.exe
 * Function: parse_vtfc_vehicle_display_key_resource
 * Entry: 004ade30
 * Signature: undefined __cdecl parse_vtfc_vehicle_display_key_resource(byte * param_1, byte * param_2)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Wrapper around
   parse_bwd2_resource_with_descriptor_table using the VTFC descriptor table at 004ff1f0 to recover
   vehicle display/texture key data. */

void __cdecl parse_vtfc_vehicle_display_key_resource(byte *param_1,byte *param_2)

{
  parse_bwd2_resource_with_descriptor_table(param_1,&VTFC_descriptor_table,2,param_2);
  return;
}


