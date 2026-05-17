/*
 * Program: i76.exe
 * Function: update_target_reticle_texture_state
 * Entry: 00459760
 * Signature: undefined __stdcall update_target_reticle_texture_state(void)
 */


/* cgpt whole-binary semantic rename v1: references ztarg201/202 maps */

void update_target_reticle_texture_state(void)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  
  if (DAT_00609504 != 0) {
    release_world_object_texture_bindings(DAT_00609504);
    DAT_00609504 = 0;
  }
  if (DAT_00609500 != 0) {
    release_world_object_texture_bindings(DAT_00609500);
    DAT_00609500 = 0;
  }
  if (DAT_00609508 != 0) {
    release_world_object_texture_bindings(DAT_00609508);
    DAT_00609508 = 0;
  }
  release_bitmap_surface_context(&DAT_0054ab98);
  release_bitmap_surface_context(&DAT_0054a3d0);
  release_bitmap_surface_context(&DAT_0054ac30);
  release_bitmap_surface_context(&DAT_0054a340);
  release_bitmap_surface_context(&DAT_0054a2f0);
  DAT_0054ac64 = 0;
  release_bitmap_surface_context(&DAT_0054a378);
  xfree_global_heap(DAT_0054a3c0);
  pcVar3 = s_ztarg201_map_004f6528;
  piVar2 = &DAT_0054a458;
  do {
    iVar1 = 4;
    do {
      release_vqm_texture_cache_reference_by_name(pcVar3);
      release_bitmap_surface_context(piVar2);
      pcVar3 = pcVar3 + 0xd;
      piVar2 = piVar2 + 0xd;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  } while ((int)piVar2 < 0x54aad8);
  return;
}


