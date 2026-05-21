/*
 * Program: i76.exe
 * Function: insert_bridge_validation_span_node_sorted
 * Entry: 0040c310
 * Signature: undefined4 __cdecl insert_bridge_validation_span_node_sorted(double * param_1, undefined4 * param_2)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: Recursively inserts a bridge/path validation span
   node into a binary tree sorted by span key. */

undefined4 __cdecl insert_bridge_validation_span_node_sorted(double *param_1,undefined4 *param_2)

{
  double *pdVar1;
  
  pdVar1 = (double *)*param_2;
  if (pdVar1 == (double *)0x0) {
    *param_2 = param_1;
    return 0;
  }
  if (*pdVar1 < *param_1) {
    insert_bridge_validation_span_node_sorted(param_1,(undefined4 *)((int)pdVar1 + 0x1c));
    return 0;
  }
  insert_bridge_validation_span_node_sorted(param_1,(undefined4 *)(pdVar1 + 4));
  return 0;
}


