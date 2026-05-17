/*
 * Program: i76.exe
 * Function: multiplayer_player_count_context_helper_00454620
 * Entry: 00454620
 * Signature: undefined4 __cdecl multiplayer_player_count_context_helper_00454620(short param_1, uchar * param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer player count context
   helper based on prior focused closure context. */

undefined4 __cdecl multiplayer_player_count_context_helper_00454620(short param_1,uchar *param_2)

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
  if (param_2 != (uchar *)0x0) {
    _mbsnbcpy(param_2,&DAT_00541072 + iVar2 * 0x48,0x18);
  }
  return 1;
}


