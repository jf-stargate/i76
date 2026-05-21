/*
 * Program: i76.exe
 * Function: release_geometry_cache_reference
 * Entry: 00446bd0
 * Signature: undefined __cdecl release_geometry_cache_reference(int param_1)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=high] Releases/decrements a cached
   runtime geometry reference. */

void __cdecl release_geometry_cache_reference(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == 0) {
    return;
  }
  iVar2 = (&g_geometry_cache_by_handle)[(param_1 * 0x6cd + 0xaabU) % 0x7ed];
  if (iVar2 != 0) {
    do {
      if (*(int *)(iVar2 + 0xc) == param_1) break;
      iVar2 = *(int *)(iVar2 + 0x10);
    } while (iVar2 != 0);
    if (iVar2 != 0) {
      iVar1 = *(int *)(iVar2 + 8) + -1;
      *(int *)(iVar2 + 8) = iVar1;
      if (iVar1 != 0) {
        return;
      }
      if (g_geometry_purge_list_tail != 0) {
        *(int *)(g_geometry_purge_list_tail + 0x18) = iVar2;
        *(int *)(iVar2 + 0x1c) = g_geometry_purge_list_tail;
        g_geometry_purge_list_tail = iVar2;
        *(undefined4 *)(iVar2 + 0x18) = 0;
        return;
      }
      g_geo_constructor_allocation_list_head = iVar2;
      g_geometry_purge_list_tail = iVar2;
      *(undefined4 *)(iVar2 + 0x1c) = 0;
      *(undefined4 *)(iVar2 + 0x18) = 0;
      return;
    }
  }
  report_error();
  return;
}


