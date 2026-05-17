/*
 * Program: i76.exe
 * Function: load_smoke_animation_texture_pair
 * Entry: 00441260
 * Signature: undefined __stdcall load_smoke_animation_texture_pair(void)
 */


/* cgpt whole-binary semantic rename v1: references xwp1_101.map/xwp1_102.map */

void load_smoke_animation_texture_pair(void)

{
  int iVar1;
  
  iVar1 = DAT_0052ba24;
  if (DAT_0052ba34 != 0) {
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x1c)) {
      if (*(LPVOID *)(iVar1 + 8) != (LPVOID)0x0) {
        finalize_released_world_object_after_damage(*(LPVOID *)(iVar1 + 8),&DAT_004f1b84);
      }
    }
  }
  xfree_global_heap(DAT_0052ba2c);
  xfree_global_heap(DAT_0052b954);
  DAT_0052ba20 = 0;
  DAT_0052ba28 = 0;
  DAT_0052ba30 = 0;
  DAT_0052b950 = 0;
  DAT_0052b958 = 0;
  DAT_0052ba24 = 0;
  iVar1 = 0;
  do {
    if (*(int *)((int)&DAT_0052b960 + iVar1) != 0) {
      release_vqm_texture_cache_reference_by_name
                (*(char **)((int)&PTR_s_xwp1_101_map_004f1668 + iVar1));
    }
    *(undefined4 *)((int)&DAT_0052b960 + iVar1) = 0;
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0xc0);
  DAT_0052ba34 = 0;
  return;
}


