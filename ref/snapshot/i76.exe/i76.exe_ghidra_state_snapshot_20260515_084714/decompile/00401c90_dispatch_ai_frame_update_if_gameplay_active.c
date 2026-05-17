/*
 * Program: i76.exe
 * Function: dispatch_ai_frame_update_if_gameplay_active
 * Entry: 00401c90
 * Signature: undefined __cdecl dispatch_ai_frame_update_if_gameplay_active(float * param_1)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] AI/frame-update gate. Runs
   only while g_game_flow_state == 5 and selects heap/runtime-dependent update path. */

void __cdecl dispatch_ai_frame_update_if_gameplay_active(float *param_1)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  
  iVar2 = get_game_flow_state();
  if (iVar2 == 5) {
    bVar1 = get_global_heap_handle();
    if (CONCAT31(extraout_var,bVar1) != 0) {
      render_game_frame_d3d_pipeline_debug_timed(param_1);
      return;
    }
    render_game_frame_software_pipeline_debug_timed(param_1);
  }
  return;
}


