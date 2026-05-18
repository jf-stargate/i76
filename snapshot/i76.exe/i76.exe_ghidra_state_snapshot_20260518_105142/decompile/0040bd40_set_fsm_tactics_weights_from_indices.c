/*
 * Program: i76.exe
 * Function: set_fsm_tactics_weights_from_indices
 * Entry: 0040bd40
 * Signature: undefined __cdecl set_fsm_tactics_weights_from_indices(int param_1, int param_2, int param_3, int param_4, int param_5)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: Stores four tactic/behavior weight values into
   AI/FSM state fields +0xa81c..+0xa828 using table indices. */

void __cdecl
set_fsm_tactics_weights_from_indices(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  *(undefined4 *)(param_1 + 0xa820) = *(undefined4 *)(&DAT_005fcb80 + param_2 * 4);
  *(undefined4 *)(param_1 + 0xa81c) = *(undefined4 *)(&DAT_005fcba0 + param_3 * 4);
  *(undefined4 *)(param_1 + 0xa824) = *(undefined4 *)(&DAT_005fcbe0 + param_4 * 4);
  *(undefined4 *)(param_1 + 0xa828) = *(undefined4 *)(&DAT_005fcbc0 + param_5 * 4);
  return;
}


