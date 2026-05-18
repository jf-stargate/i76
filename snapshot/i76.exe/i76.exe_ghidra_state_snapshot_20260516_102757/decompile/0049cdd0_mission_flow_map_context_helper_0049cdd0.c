/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049cdd0
 * Entry: 0049cdd0
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049cdd0(int param_1)
 */


/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049cdd0.
   Remove duplicated mission-flow/map wording. */

void __cdecl mission_flow_map_context_helper_0049cdd0(int param_1)

{
  bool bVar1;
  
  bVar1 = g_runtime_display_input_mode != param_1;
  g_runtime_display_input_mode = 1;
  if (bVar1) {
    g_runtime_display_input_mode = param_1;
  }
  return;
}


