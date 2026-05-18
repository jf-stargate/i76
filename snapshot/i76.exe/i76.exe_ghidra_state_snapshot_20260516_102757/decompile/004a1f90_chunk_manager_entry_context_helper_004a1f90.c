/*
 * Program: i76.exe
 * Function: chunk_manager_entry_context_helper_004a1f90
 * Entry: 004a1f90
 * Signature: undefined __stdcall chunk_manager_entry_context_helper_004a1f90(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: chunk manager entry context helper
   based on adjacent named subsystem context. */

void chunk_manager_entry_context_helper_004a1f90(void)

{
  LPVOID pvVar1;
  LPVOID lpMem;
  undefined4 *puVar2;
  
  noop_world_object_callback_stub();
  puVar2 = &DAT_005a8118;
  do {
    lpMem = (LPVOID)*puVar2;
    while (lpMem != (LPVOID)0x0) {
      pvVar1 = *(LPVOID *)((int)lpMem + 0x46c);
      HeapFree(DAT_005aaac0,0,lpMem);
      lpMem = pvVar1;
    }
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  } while ((int)puVar2 < 0x5a82dc);
  HeapDestroy(DAT_005aaac0);
  _DAT_005aaacc = 0;
  DAT_005aaac8 = 0;
  _DAT_005a82e0 = 1;
  return;
}


