/*
 * Program: i76.exe
 * Function: get_multiplayer_score_accumulators
 * Entry: 004012e0
 * Signature: undefined __cdecl get_multiplayer_score_accumulators(undefined4 * param_1, undefined2 * param_2)
 */


/* cgpt rename v3: Copies the two multiplayer score accumulator globals to optional caller-provided
   outputs. */

void __cdecl get_multiplayer_score_accumulators(undefined4 *param_1,undefined2 *param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = DAT_00501784;
  }
  if (param_2 != (undefined2 *)0x0) {
    *param_2 = DAT_00501788;
  }
  return;
}


