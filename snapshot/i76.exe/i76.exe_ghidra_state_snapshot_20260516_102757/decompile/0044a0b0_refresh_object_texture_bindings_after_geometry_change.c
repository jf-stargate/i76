/*
 * Program: i76.exe
 * Function: refresh_object_texture_bindings_after_geometry_change
 * Entry: 0044a0b0
 * Signature: undefined4 __cdecl refresh_object_texture_bindings_after_geometry_change(int param_1)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Refreshes per-object
   texture bindings after geometry changes; bridges geometry section texture slots to active texture
   resources. */

undefined4 __cdecl refresh_object_texture_bindings_after_geometry_change(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(&g_texture_bindings_by_object_hash)[(param_1 * 0x6cd + 0xaabU) % 0x71];
  if (piVar2 != (int *)0x0) {
    do {
      if (*piVar2 == param_1) break;
      piVar2 = (int *)piVar2[2];
    } while (piVar2 != (int *)0x0);
    if (piVar2 != (int *)0x0) {
      for (iVar1 = piVar2[1]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
        if ((*(byte *)(iVar1 + 0x3c) & 3) == 0) {
          release_vqm_texture_cache_reference_by_name((char *)(iVar1 + 4));
          *(undefined4 *)(iVar1 + 0x34) = 0;
          *(uint *)(iVar1 + 0x3c) = *(uint *)(iVar1 + 0x3c) | 2;
        }
        release_m16_resource_handle((int *)(iVar1 + 0x38),(char *)(iVar1 + 4));
      }
      return 1;
    }
  }
  return 0;
}


