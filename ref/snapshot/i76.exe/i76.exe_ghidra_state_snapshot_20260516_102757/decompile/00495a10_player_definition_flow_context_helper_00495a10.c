/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00495a10
 * Entry: 00495a10
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00495a10(undefined4 param_1, int param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00495a10. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00495a10(undefined4 param_1,int param_2)

{
  if (param_2 == 4) {
    load_selected_loading_screen_bitmap((undefined *)&PTR_DAT_004fcb38);
  }
  return 1;
}


