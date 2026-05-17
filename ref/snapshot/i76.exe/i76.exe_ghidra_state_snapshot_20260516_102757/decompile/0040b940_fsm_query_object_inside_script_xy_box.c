/*
 * Program: i76.exe
 * Function: fsm_query_object_inside_script_xy_box
 * Entry: 0040b940
 * Signature: undefined4 __cdecl fsm_query_object_inside_script_xy_box(int param_1, int param_2, int * param_3)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: compares object X/Z position against
   script-provided X/Z coordinates using axis-aligned absolute thresholds. */

undefined4 __cdecl fsm_query_object_inside_script_xy_box(int param_1,int param_2,int *param_3)

{
  if ((ABS(**(float **)(param_1 + 0x54) - (float)*(double *)(param_2 + 0x40)) < (float)*param_3) &&
     (ABS((*(float **)(param_1 + 0x54))[2] - (float)*(double *)(param_2 + 0x50)) < (float)*param_3))
  {
    return 1;
  }
  return 0;
}


