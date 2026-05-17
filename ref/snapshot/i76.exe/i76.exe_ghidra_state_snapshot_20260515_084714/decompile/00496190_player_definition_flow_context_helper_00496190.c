/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00496190
 * Entry: 00496190
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00496190(int param_1, undefined4 param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00496190. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00496190(int param_1,undefined4 param_2)

{
  switch(param_2) {
  case 6:
    *(uint *)(param_1 + 0x18) = (uint)DAT_00654b8c._1_1_;
    return 1;
  case 7:
    DAT_00654b8c._1_1_ = *(undefined1 *)(param_1 + 0x18);
    return 1;
  case 8:
    DAT_00654bed = DAT_00654b8c._1_1_;
    initialize_runtime_camera_projection_matrix(0);
    force_feedback_effect_instance_helper_004456e0();
    return 1;
  case 9:
    DAT_00654b8c._1_1_ = DAT_00654bed;
  }
  return 1;
}


