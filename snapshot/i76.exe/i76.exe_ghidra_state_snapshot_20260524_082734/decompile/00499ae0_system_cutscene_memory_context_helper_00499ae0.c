/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_00499ae0
 * Entry: 00499ae0
 * Signature: undefined __cdecl system_cutscene_memory_context_helper_00499ae0(undefined4 * param_1)
 */


/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_00499ae0. Shorten readability
   label for system/cutscene/virtual-memory context. */

void __cdecl system_cutscene_memory_context_helper_00499ae0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_005a7ca0;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


