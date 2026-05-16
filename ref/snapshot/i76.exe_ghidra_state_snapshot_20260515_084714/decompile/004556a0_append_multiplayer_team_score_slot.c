/*
 * Program: i76.exe
 * Function: append_multiplayer_team_score_slot
 * Entry: 004556a0
 * Signature: undefined __cdecl append_multiplayer_team_score_slot(undefined2 param_1)
 */


/* cgpt rename v4: Appends a team/player id into the bounded multiplayer team-score slot array. */

void __cdecl append_multiplayer_team_score_slot(undefined2 param_1)

{
  if (DAT_005414f8 != 0x10) {
    *(undefined2 *)(&DAT_00541500 + DAT_005414f8 * 2) = param_1;
    DAT_005414f8 = DAT_005414f8 + 1;
  }
  return;
}


