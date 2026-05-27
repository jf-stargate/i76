/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_00499cb0
 * Entry: 00499cb0
 * Signature: undefined __stdcall system_cutscene_memory_context_helper_00499cb0(void)
 */


/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_00499cb0. Shorten readability
   label for system/cutscene/virtual-memory context. */

void system_cutscene_memory_context_helper_00499cb0(void)

{
  if (DAT_005a7cc8 != (HANDLE)0x0) {
    HeapDestroy(DAT_005a7cc8);
  }
  DAT_005a7cc8 = (HANDLE)0x0;
  DAT_005a7cc0 = DAT_005a7cc4;
  return;
}


