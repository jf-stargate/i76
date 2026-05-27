/*
 * Program: i76.exe
 * Function: load_sobj_scene_object_geometry_id
 * Entry: 004b8470
 * Signature: undefined4 __cdecl load_sobj_scene_object_geometry_id(int param_1, int * param_2)
 */


/* [i76 level/static/material baseline v48]
   name: load_sobj_child_geo_resource
   confidence: high
   module: sdf_static_object
   SDF child SOBJ/SGEO loader that formats/loads partName.geo. Exporter v12-v47 confirms SDF SGEO
   declared parts resolve to embedded GEO assets.
   note: Rename skipped because existing name appears user-defined. */

undefined4 __cdecl load_sobj_scene_object_geometry_id(int param_1,int *param_2)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = (uint *)format_8char_resource_basename_with_suffix
                             (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
                              s__geo_004fe724);
  uVar2 = load_geometry_resource_into_cache(puVar1);
  *(uint *)(*param_2 + 0x5c) = uVar2;
  return 1;
}


