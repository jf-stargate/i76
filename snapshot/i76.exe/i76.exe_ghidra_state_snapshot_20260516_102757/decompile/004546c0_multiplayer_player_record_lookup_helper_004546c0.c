/*
 * Program: i76.exe
 * Function: multiplayer_player_record_lookup_helper_004546c0
 * Entry: 004546c0
 * Signature: undefined4 __cdecl multiplayer_player_record_lookup_helper_004546c0(short param_1, undefined4 param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer player record lookup
   helper based on prior focused closure context. */

undefined4 __cdecl
multiplayer_player_record_lookup_helper_004546c0(short param_1,undefined4 param_2)

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
  (&DAT_0054108c)[iVar2 * 0x12] = param_2;
  return 1;
}


