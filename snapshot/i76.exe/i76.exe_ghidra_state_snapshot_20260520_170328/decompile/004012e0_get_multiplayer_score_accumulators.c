/*
 * Program: i76.exe
 * Function: get_multiplayer_score_accumulators
 * Entry: 004012e0
 * Signature: undefined __cdecl get_multiplayer_score_accumulators(undefined4 * score_0_dst, undefined2 * score_1_dst)
 */


/* cgpt rename v3: Copies the two multiplayer score accumulator globals to optional caller-provided
   outputs. */

void __cdecl get_multiplayer_score_accumulators(undefined4 *score_0_dst,undefined2 *score_1_dst)

{
  if (score_0_dst != (undefined4 *)0x0) {
    *score_0_dst = g_mp_score_0;
  }
  if (score_1_dst != (undefined2 *)0x0) {
    *score_1_dst = g_mp_score_1;
  }
  return;
}


