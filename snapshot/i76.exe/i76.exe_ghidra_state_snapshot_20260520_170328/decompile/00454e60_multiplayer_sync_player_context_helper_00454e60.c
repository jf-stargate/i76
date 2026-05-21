/*
 * Program: i76.exe
 * Function: multiplayer_sync_player_context_helper_00454e60
 * Entry: 00454e60
 * Signature: undefined4 __stdcall multiplayer_sync_player_context_helper_00454e60(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer sync player context helper
   based on prior focused closure context. */

undefined4 multiplayer_sync_player_context_helper_00454e60(void)

{
  short *psVar1;
  
  psVar1 = &DAT_00541070;
  while (((*psVar1 == 0 || (*psVar1 == DAT_00541028)) || (*(int *)(psVar1 + 0x16) != -0x40800000)))
  {
    psVar1 = psVar1 + 0x24;
    if (0x5414ef < (int)psVar1) {
      return 1;
    }
  }
  return 0;
}


