/*
 * Program: i76.exe
 * Function: multiplayer_player_table_context_helper_004547c0
 * Entry: 004547c0
 * Signature: undefined4 __cdecl multiplayer_player_table_context_helper_004547c0(short param_1)
 */


/* cgpt label refinement v18: was multiplayer_network_multiplayer_player_table_helper_004547c0.
   Remove duplicated multiplayer wording from readability label. */

undefined4 __cdecl multiplayer_player_table_context_helper_004547c0(short param_1)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = 0;
  psVar1 = &DAT_00541070;
  do {
    if (*psVar1 == param_1) break;
    psVar1 = psVar1 + 0x24;
    iVar2 = iVar2 + 1;
  } while ((int)psVar1 < 0x5414f0);
  if (iVar2 == 0x10) {
    iVar2 = -1;
  }
  if (iVar2 == -1) {
    return 0;
  }
  return (&DAT_00541098)[iVar2 * 0x12];
}


