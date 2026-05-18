/*
 * Program: i76.exe
 * Function: project_point_to_ai_path_segment_state
 * Entry: 004158c0
 * Signature: undefined __cdecl project_point_to_ai_path_segment_state(float param_1, undefined4 param_2, float param_3, int * param_4)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Projects a point into AI/path segment state through the
   path projection helper at 0048e700. */

void __cdecl
project_point_to_ai_path_segment_state(float param_1,undefined4 param_2,float param_3,int *param_4)

{
  project_point_to_path_segment_context_helper_0048e700(param_1,param_2,param_3,param_4 + 7,param_4)
  ;
  return;
}


