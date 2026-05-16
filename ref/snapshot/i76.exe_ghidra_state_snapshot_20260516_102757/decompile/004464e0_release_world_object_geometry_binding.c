/*
 * Program: i76.exe
 * Function: release_world_object_geometry_binding
 * Entry: 004464e0
 * Signature: undefined4 __cdecl release_world_object_geometry_binding(int param_1)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Releases geometry binding
   attached to a world object. */

undefined4 __cdecl release_world_object_geometry_binding(int param_1)

{
  LPVOID pvVar1;
  LPVOID lpMem;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int *lpMem_00;
  
  if (param_1 != 0) {
    uVar3 = (param_1 * 0x6cd + 0xaabU) % 0x7ed;
    piVar2 = (int *)(&g_geometry_binding_hash)[uVar3];
    if (piVar2 != (int *)0x0) {
      if (*piVar2 == param_1) {
        (&g_geometry_binding_hash)[uVar3] = piVar2[0xe];
        lpMem_00 = piVar2;
      }
      else {
        piVar4 = (int *)piVar2[0xe];
        if ((int *)piVar2[0xe] == (int *)0x0) {
          return 1;
        }
        do {
          if (*piVar4 == param_1) {
            piVar2[0xe] = piVar4[0xe];
            lpMem_00 = piVar4;
            break;
          }
          lpMem_00 = (int *)piVar4[0xe];
          piVar2 = piVar4;
          piVar4 = lpMem_00;
        } while (lpMem_00 != (int *)0x0);
      }
      if (lpMem_00 != (int *)0x0) {
        release_geometry_cache_reference(lpMem_00[1]);
        lpMem_00[1] = 0;
        *(undefined4 *)(*lpMem_00 + 0x5c) = 0;
        lpMem = (LPVOID)lpMem_00[0xd];
        while (lpMem != (LPVOID)0x0) {
          pvVar1 = *(LPVOID *)((int)lpMem + 0x70);
          HeapFree(DAT_0052dba0,0,lpMem);
          lpMem = pvVar1;
        }
        lpMem_00[0xd] = 0;
        HeapFree(DAT_0052db9c,0,lpMem_00);
      }
    }
  }
  return 1;
}


