/*
 * Program: i76.exe
 * Function: load_specials_backing_texture
 * Entry: 004679a0
 * Signature: undefined __cdecl load_specials_backing_texture(int param_1)
 */


/* cgpt whole-binary semantic rename v1: references zbks_.map/zbks_320.map */

void __cdecl load_specials_backing_texture(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  uint uVar5;
  int local_34 [13];
  
  release_bitmap_surface_context(&DAT_0054b9b8);
  puVar1 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar3 = &DAT_0054b9b8;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  if (param_1 != 0) {
    if (g_display_mode_variant_index < 6) {
      pcVar4 = s_zbks_320_map_004f8190;
    }
    else {
      pcVar4 = s_zbks__map_004f819d;
    }
    uVar5 = 1;
    DAT_004f863c = (uint)(g_display_mode_variant_index < 6);
    iVar2 = world_object_geometry_context_helper_004588b0(param_1,pcVar4);
    get_world_object_class_id(iVar2,uVar5);
    DAT_0054b9ec = world_object_geometry_context_helper_004588b0
                             (param_1,s_zbks_320_map_004f8190 + DAT_004f863c * 0xd);
    if (DAT_0054b9ec != 0) {
      world_object_geometry_context_helper_00458860(DAT_0054b9ec,1);
      if (*(int *)(param_1 + 0x70) != 0) {
        *(int *)(*(int *)(param_1 + 0x70) + 0x43c) = DAT_0054b9ec;
        initialize_specials_housing_display(param_1);
      }
    }
  }
  return;
}


