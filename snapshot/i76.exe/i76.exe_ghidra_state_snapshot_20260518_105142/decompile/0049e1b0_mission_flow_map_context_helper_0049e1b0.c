/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049e1b0
 * Entry: 0049e1b0
 * Signature: float10 __cdecl mission_flow_map_context_helper_0049e1b0(double * param_1, float param_2)
 */


/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049e1b0.
   Remove duplicated mission-flow/map wording. */

float10 __cdecl mission_flow_map_context_helper_0049e1b0(double *param_1,float param_2)

{
  double dVar1;
  float10 fVar2;
  
  dVar1 = param_1[4];
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_1 + 3);
  *(undefined4 *)((int)param_1 + 0x24) = *(undefined4 *)((int)param_1 + 0x1c);
  fVar2 = ((float10)param_2 * (float10)param_1[2] - (float10)*param_1 * (float10)param_1[3]) -
          (float10)param_1[1] * (float10)dVar1;
  param_1[3] = (double)fVar2;
  return fVar2;
}


