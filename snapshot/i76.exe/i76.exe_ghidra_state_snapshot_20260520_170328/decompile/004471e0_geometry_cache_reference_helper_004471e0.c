/*
 * Program: i76.exe
 * Function: geometry_cache_reference_helper_004471e0
 * Entry: 004471e0
 * Signature: undefined __stdcall geometry_cache_reference_helper_004471e0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: geometry cache reference helper based
   on prior focused closure context. */

void geometry_cache_reference_helper_004471e0(void)

{
  int iVar1;
  SIZE_T SVar2;
  uint uVar3;
  int *piVar4;
  
  piVar4 = &g_geometry_cache_by_handle;
  do {
    for (iVar1 = *piVar4; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x10)) {
      SVar2 = HeapSize(g_geometry_heap_handle,0,*(LPCVOID *)(iVar1 + 0xc));
      if (0 < (int)SVar2) {
        uVar3 = SVar2 + 0xfff >> 0xc;
        do {
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
      }
    }
    piVar4 = piVar4 + 1;
    iVar1 = g_geo_constructor_allocation_list_head;
  } while ((int)piVar4 < 0x52fb5c);
  for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x18)) {
    SVar2 = HeapSize(g_geometry_heap_handle,0,*(LPCVOID *)(iVar1 + 0xc));
    if (0 < (int)SVar2) {
      uVar3 = SVar2 + 0xfff >> 0xc;
      do {
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
  }
  return;
}


