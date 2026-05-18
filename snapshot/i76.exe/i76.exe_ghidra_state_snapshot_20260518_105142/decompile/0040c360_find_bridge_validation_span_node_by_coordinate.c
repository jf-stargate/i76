/*
 * Program: i76.exe
 * Function: find_bridge_validation_span_node_by_coordinate
 * Entry: 0040c360
 * Signature: uint __cdecl find_bridge_validation_span_node_by_coordinate(double * param_1, double param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v7 fsm predicate/bridge cluster: Searches a bridge/path validation span tree by
   coordinate, rejecting objects with world-object flag 0x200. */

uint __cdecl find_bridge_validation_span_node_by_coordinate(double *param_1,double param_2)

{
  while( true ) {
    if (param_1 == (double *)0x0) {
      return 0;
    }
    if (ABS(*param_1 - param_2) < _DAT_004bc670) break;
    if (param_2 <= *param_1) {
      param_1 = *(double **)(param_1 + 4);
    }
    else {
      param_1 = *(double **)((int)param_1 + 0x1c);
    }
  }
  return ~-(uint)((*(uint *)(*(int *)(param_1 + 3) + 0x10) & 0x200) != 0) & (uint)param_1;
}


