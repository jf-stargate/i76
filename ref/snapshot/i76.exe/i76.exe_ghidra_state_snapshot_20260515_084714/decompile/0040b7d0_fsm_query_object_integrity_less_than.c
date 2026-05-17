/*
 * Program: i76.exe
 * Function: fsm_query_object_integrity_less_than
 * Entry: 0040b7d0
 * Signature: undefined4 __cdecl fsm_query_object_integrity_less_than(int param_1, undefined4 param_2, int * param_3)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: computes object integrity percentage
   and compares it against the supplied threshold. */

undefined4 __cdecl fsm_query_object_integrity_less_than(int param_1,undefined4 param_2,int *param_3)

{
  float10 fVar1;
  
  fVar1 = compute_world_object_damage_integrity_percent(param_1);
  if (fVar1 < (float10)*param_3) {
    return 1;
  }
  return 0;
}


