/*
 * Program: i76.exe
 * Function: evaluate_ai_pair_condition_side_effect
 * Entry: 0041e640
 * Signature: undefined __cdecl evaluate_ai_pair_condition_side_effect(int param_1, int param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Thin wrapper around the paired-object condition
   evaluator FUN_0040ac00. */

void __cdecl evaluate_ai_pair_condition_side_effect(int param_1,int param_2)

{
  fsm_query_target_not_over_subscribed(param_1,param_2);
  return;
}


