/*
 * Program: i76.exe
 * Function: fsm_query_object_near_script_xy_position
 * Entry: 0040b8e0
 * Signature: undefined4 __cdecl fsm_query_object_near_script_xy_position(int param_1, int param_2, int * param_3)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: compares object X/Z position against
   script-provided X/Z coordinates using radius^2. */

undefined4 __cdecl fsm_query_object_near_script_xy_position(int param_1,int param_2,int *param_3)

{
  float fVar1;
  float fVar2;
  
  fVar2 = **(float **)(param_1 + 0x54) - (float)*(double *)(param_2 + 0x40);
  fVar1 = (*(float **)(param_1 + 0x54))[2] - (float)*(double *)(param_2 + 0x50);
  if (fVar1 * fVar1 + fVar2 * fVar2 < (float)(*param_3 * *param_3)) {
    return 1;
  }
  return 0;
}


