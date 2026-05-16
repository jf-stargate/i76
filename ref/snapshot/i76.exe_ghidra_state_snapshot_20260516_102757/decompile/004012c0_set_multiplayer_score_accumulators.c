/*
 * Program: i76.exe
 * Function: set_multiplayer_score_accumulators
 * Entry: 004012c0
 * Signature: undefined __cdecl set_multiplayer_score_accumulators(undefined4 param_1, undefined2 param_2)
 */


/* cgpt rename v3: Sets the two globals later read by scoreboard/report writers. */

void __cdecl set_multiplayer_score_accumulators(undefined4 param_1,undefined2 param_2)

{
  DAT_00501784 = param_1;
  DAT_00501788 = param_2;
  return;
}


