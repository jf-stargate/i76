/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049d400
 * Entry: 0049d400
 * Signature: undefined8 __cdecl mission_flow_map_context_helper_0049d400(float param_1)
 */


/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049d400.
   Remove duplicated mission-flow/map wording. */

undefined8 __cdecl mission_flow_map_context_helper_0049d400(float param_1)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)param_1);
  fVar2 = (float10)fsin((float10)param_1);
  return CONCAT44((float)fVar1,(float)fVar2);
}


