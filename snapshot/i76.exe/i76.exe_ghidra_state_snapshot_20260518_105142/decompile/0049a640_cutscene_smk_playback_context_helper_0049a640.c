/*
 * Program: i76.exe
 * Function: cutscene_smk_playback_context_helper_0049a640
 * Entry: 0049a640
 * Signature: uint __stdcall cutscene_smk_playback_context_helper_0049a640(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: cutscene smk playback context helper
   based on adjacent named subsystem context. */

uint cutscene_smk_playback_context_helper_0049a640(void)

{
  uint uVar1;
  
  if (DAT_004f9f20 != 0) {
    _DAT_005a7d7c = 1;
    return DAT_004f9f20;
  }
  if (DAT_005a7d74 != 0) {
    uVar1 = _SmackBufferSetPalette_4(DAT_005a7d74);
    return uVar1 & 0xffff;
  }
  return 0;
}


