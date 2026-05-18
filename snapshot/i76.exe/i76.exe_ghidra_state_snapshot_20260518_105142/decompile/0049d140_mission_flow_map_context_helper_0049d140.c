/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049d140
 * Entry: 0049d140
 * Signature: undefined __stdcall mission_flow_map_context_helper_0049d140(void)
 */


/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049d140.
   Remove duplicated mission-flow/map wording. */

void mission_flow_map_context_helper_0049d140(void)

{
  int iVar1;
  
  iVar1 = is_damage_side_effects_suppressed();
  if (iVar1 == 0) {
    if (g_runtime_display_input_mode == 2) {
      iVar1 = ui_bitmap_region_context_helper_0049ae50();
      if ((iVar1 == 0) && (g_requested_runtime_display_input_mode == 1)) {
        resume_cd_audio_after_cutscene_or_mode_change();
        force_feedback_runtime_helper_00445b40();
      }
      if (g_runtime_display_input_mode == g_requested_runtime_display_input_mode) {
        g_runtime_display_input_mode = 1;
        return;
      }
      g_runtime_display_input_mode = g_requested_runtime_display_input_mode;
      return;
    }
    iVar1 = ui_bitmap_region_context_helper_0049ae20();
    if ((iVar1 == 0) && (g_requested_runtime_display_input_mode == 1)) {
      pause_cd_audio_for_cutscene_or_mode_change();
      force_feedback_runtime_helper_00445b60();
    }
    g_requested_runtime_display_input_mode = g_runtime_display_input_mode;
    g_runtime_display_input_mode = (g_runtime_display_input_mode != 2) + 1;
  }
  return;
}


