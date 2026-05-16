/*
 * Program: i76.exe
 * Function: system_cutscene_memory_context_helper_0049a040
 * Entry: 0049a040
 * Signature: undefined4 __stdcall system_cutscene_memory_context_helper_0049a040(void)
 */


/* cgpt label refinement v20: was
   system_virtual_memory_cutscene_virtual_memory_or_cutscene_helper_0049a040. Shorten readability
   label for system/cutscene/virtual-memory context. */

undefined4 system_cutscene_memory_context_helper_0049a040(void)

{
  if (DAT_00524564 != (undefined4 *)0x0) {
    _SmackSoundUseDirectSound_4(*DAT_00524564);
    return 1;
  }
  _SmackSoundUseDirectSound_4(0);
  return 1;
}


