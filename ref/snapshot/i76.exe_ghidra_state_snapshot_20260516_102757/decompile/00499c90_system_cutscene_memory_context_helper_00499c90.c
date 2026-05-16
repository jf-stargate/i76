/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_00499c90
 * Entry: 00499c90
 * Signature: undefined __stdcall system_cutscene_memory_context_helper_00499c90(void)
 */


/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_00499c90. Shorten readability
   label for system/cutscene/virtual-memory context. */

void system_cutscene_memory_context_helper_00499c90(void)

{
  if (DAT_005a7cc8 == (HANDLE)0x0) {
    DAT_005a7cc8 = HeapCreate(0,0,0);
  }
  DAT_005a7cc0 = DAT_005a7cc8;
  return;
}


