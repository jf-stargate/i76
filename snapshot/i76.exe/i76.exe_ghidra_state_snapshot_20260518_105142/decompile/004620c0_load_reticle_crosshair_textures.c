/*
 * Program: i76.exe
 * Function: load_reticle_crosshair_textures
 * Entry: 004620c0
 * Signature: undefined __cdecl load_reticle_crosshair_textures(int param_1)
 */


/* cgpt whole-binary semantic rename v1: references zretc_6.map/zretc_1.map */

void __cdecl load_reticle_crosshair_textures(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_0054b67c = 0;
  DAT_0054b680 = 0;
  DAT_0054b684 = 0;
  DAT_0054b680 = world_object_geometry_context_helper_004588b0(param_1,s_zretc_6_map_004f7c85);
  DAT_0054b684 = world_object_geometry_context_helper_004588b0(param_1,s_zretc_1_map_004f7c78);
  world_object_geometry_context_helper_00458860(DAT_0054b684,1);
  get_world_object_class_id(DAT_0054b680,1);
  puVar2 = &DAT_0054b648;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}


