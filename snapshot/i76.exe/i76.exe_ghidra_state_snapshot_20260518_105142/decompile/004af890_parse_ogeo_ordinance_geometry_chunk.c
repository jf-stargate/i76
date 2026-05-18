/*
 * Program: i76.exe
 * Function: parse_ogeo_ordinance_geometry_chunk
 * Entry: 004af890
 * Signature: undefined4 __cdecl parse_ogeo_ordinance_geometry_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] OGEO callback for
   ordinance/projectile geometry records. */

undefined4 __cdecl parse_ogeo_ordinance_geometry_chunk(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1;
  param_1 = 0;
  fill_resource_lookup_key_stride100(iVar1 + 0xc,&param_1,1,*(int *)(iVar1 + 8));
  iVar1 = instantiate_part_record_array_with_geo_cache
                    (&param_1,(int *)0x0,1,1,*(int *)(iVar1 + 8),(undefined *)0x0);
  *(int *)(param_2 + 0x148) = iVar1;
  if (iVar1 == 0) {
    return 0;
  }
  set_world_object_class_and_register_runtime(iVar1,0x33);
  return 1;
}


