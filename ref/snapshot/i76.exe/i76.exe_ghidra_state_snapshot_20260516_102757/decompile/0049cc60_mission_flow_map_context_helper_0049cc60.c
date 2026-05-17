/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049cc60
 * Entry: 0049cc60
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049cc60(int param_1, float param_2)
 */


/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049cc60.
   Remove duplicated mission-flow/map wording. */

void __cdecl mission_flow_map_context_helper_0049cc60(int param_1,float param_2)

{
  int iVar1;
  
  iVar1 = ftol();
  *(int *)(param_1 + 8) = iVar1 + 1;
  if (0x14 < iVar1 + 1) {
    *(undefined4 *)(param_1 + 8) = 0x14;
  }
  *(float *)(param_1 + 4) = (float)(&DAT_005a7e1c)[*(int *)(param_1 + 8)] * param_2;
  return;
}


