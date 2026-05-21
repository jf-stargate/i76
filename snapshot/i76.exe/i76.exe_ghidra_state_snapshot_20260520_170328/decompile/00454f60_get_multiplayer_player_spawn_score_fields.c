/*
 * Program: i76.exe
 * Function: get_multiplayer_player_spawn_score_fields
 * Entry: 00454f60
 * Signature: undefined __cdecl get_multiplayer_player_spawn_score_fields(short param_1, undefined4 * param_2, undefined2 * param_3, undefined2 * param_4)
 */


/* cgpt rename v4: Looks up a multiplayer player slot and returns associated score/spawn fields
   through optional output pointers. */

void __cdecl
get_multiplayer_player_spawn_score_fields
          (short param_1,undefined4 *param_2,undefined2 *param_3,undefined2 *param_4)

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
    *param_4 = 0;
    *param_3 = 0;
    *param_2 = 0;
    return;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = (&DAT_005410b0)[iVar2 * 0x12];
  }
  if (param_3 != (undefined2 *)0x0) {
    *param_3 = *(undefined2 *)(iVar2 * 0x48 + 0x5410ac);
  }
  if (param_4 != (undefined2 *)0x0) {
    *param_4 = *(undefined2 *)(iVar2 * 0x48 + 0x5410ae);
  }
  return;
}


