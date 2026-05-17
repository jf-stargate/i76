/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_004998f0
 * Entry: 004998f0
 * Signature: undefined * * __cdecl system_cutscene_memory_context_helper_004998f0(int param_1, undefined * param_2)
 */


/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_004998f0. Shorten readability
   label for system/cutscene/virtual-memory context. */

undefined ** __cdecl system_cutscene_memory_context_helper_004998f0(int param_1,undefined *param_2)

{
  if ((PTR_DAT_004fe194 != (undefined *)0x0) && (param_1 < 4)) {
    return (undefined **)(*(int *)(PTR_DAT_004fe194 + 0xc) + param_1 * 8);
  }
  PTR_DAT_004fdec8 = param_2;
  return &PTR_DAT_004fdec8;
}


