/*
 * Program: i76.exe
 * Function: destroy_geometry_binding_hash_heaps
 * Entry: 00446870
 * Signature: undefined __stdcall destroy_geometry_binding_hash_heaps(void)
 */


/* cgpt rename v2: Releases all geometry binding hash records, child binding lists, and destroys the
   geometry-binding heaps. */

void destroy_geometry_binding_hash_heaps(void)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  LPVOID lpMem;
  undefined4 *puVar3;
  
  puVar3 = &g_geometry_binding_hash;
  do {
    lpMem = (LPVOID)*puVar3;
    while (lpMem != (LPVOID)0x0) {
      release_geometry_cache_reference(*(int *)((int)lpMem + 4));
      pvVar2 = *(LPVOID *)((int)lpMem + 0x34);
      while (pvVar2 != (LPVOID)0x0) {
        pvVar1 = *(LPVOID *)((int)pvVar2 + 0x70);
        HeapFree(DAT_0052dba0,0,pvVar2);
        pvVar2 = pvVar1;
      }
      pvVar2 = *(LPVOID *)((int)lpMem + 0x38);
      HeapFree(DAT_0052db9c,0,lpMem);
      lpMem = pvVar2;
    }
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  } while ((int)puVar3 < 0x52db9c);
  HeapDestroy(DAT_0052db9c);
  HeapDestroy(DAT_0052dba0);
  return;
}


