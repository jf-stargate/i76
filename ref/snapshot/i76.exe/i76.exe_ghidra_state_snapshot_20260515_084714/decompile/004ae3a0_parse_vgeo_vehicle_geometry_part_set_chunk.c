/*
 * Program: i76.exe
 * Function: parse_vgeo_vehicle_geometry_part_set_chunk
 * Entry: 004ae3a0
 * Signature: bool __cdecl parse_vgeo_vehicle_geometry_part_set_chunk(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] VGEO callback: copies indexed part
   records and instantiates named vehicle child geometry using .geo cache entries. */

bool __cdecl parse_vgeo_vehicle_geometry_part_set_chunk(int param_1,undefined4 *param_2)

{
  int iVar1;
  int *piVar2;
  int local_70 [28];
  
  piVar2 = local_70;
  for (iVar1 = 0x1c; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  fill_resource_lookup_key_stride100(param_1 + 0xc,local_70,0x1c,*(int *)(param_1 + 8));
  iVar1 = instantiate_part_record_array_with_geo_cache
                    (local_70,(int *)*param_2,7,4,*(int *)(param_1 + 8),
                     vehicle_component_config_context_helper_004ae2e0);
  return iVar1 != 0;
}


