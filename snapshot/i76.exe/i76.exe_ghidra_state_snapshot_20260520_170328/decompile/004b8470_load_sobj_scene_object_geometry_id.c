/*
 * Program: i76.exe
 * Function: load_sobj_scene_object_geometry_id
 * Entry: 004b8470
 * Signature: undefined4 __cdecl load_sobj_scene_object_geometry_id(int param_1, int * param_2)
 */


/* [cgpt i76.exe GEO mesh/render renames v29; confidence=high] Loads SOBJ geometry basename as a
   .geo resource and stores/returns the runtime geometry handle for a scene/vehicle object.
   
   I76 rename v43: load_sobj_scene_object_geometry_id
   SOBJ handler; formats part.geo and calls GEO loader path. */

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


