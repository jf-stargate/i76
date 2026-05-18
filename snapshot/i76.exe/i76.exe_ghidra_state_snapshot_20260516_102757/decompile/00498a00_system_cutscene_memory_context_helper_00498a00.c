/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_00498a00
 * Entry: 00498a00
 * Signature: undefined __cdecl system_cutscene_memory_context_helper_00498a00(LPVOID param_1)
 */


/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_00498a00. Shorten readability
   label for system/cutscene/virtual-memory context. */

void __cdecl system_cutscene_memory_context_helper_00498a00(LPVOID param_1)

{
  int *piVar1;
  LPVOID pvVar2;
  LPVOID pvVar3;
  
  pvVar2 = (LPVOID)0x0;
  pvVar3 = DAT_005a6170;
  if (DAT_005a6170 != (LPVOID)0x0) {
    while (*(LPVOID *)((int)pvVar3 + 8) != param_1) {
      piVar1 = (int *)((int)pvVar3 + 0xc);
      pvVar2 = pvVar3;
      pvVar3 = (LPVOID)*piVar1;
      if ((LPVOID)*piVar1 == (LPVOID)0x0) {
        return;
      }
    }
    if (pvVar2 == (LPVOID)0x0) {
      DAT_005a6170 = *(LPVOID *)((int)pvVar3 + 0xc);
    }
    else {
      *(undefined4 *)((int)pvVar2 + 0xc) = *(undefined4 *)((int)pvVar3 + 0xc);
    }
    VirtualFree(param_1,0,0x8000);
    xfree_global_heap(pvVar3);
  }
  return;
}


