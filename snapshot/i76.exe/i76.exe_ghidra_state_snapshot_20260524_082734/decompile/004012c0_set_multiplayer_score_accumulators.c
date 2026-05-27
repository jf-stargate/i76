/*
 * Program: i76.exe
 * Function: set_multiplayer_score_accumulators
 * Entry: 004012c0
 * Signature: undefined __cdecl set_multiplayer_score_accumulators(undefined4 param_1, undefined2 param_2)
 */


/* cgpt rename v3: Sets the two globals later read by scoreboard/report writers. */

void __cdecl set_multiplayer_score_accumulators(undefined4 param_1,undefined2 param_2)

{
  g_mp_score_0 = param_1;
  g_mp_score_1 = param_2;
  return;
}


