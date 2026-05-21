/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00495b40
 * Entry: 00495b40
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00495b40(undefined4 param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00495b40. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00495b40(undefined4 param_1,int param_2)

{
  if (param_2 == 4) {
    _DAT_004fcdd8 = &LAB_00496830;
    load_selected_loading_screen_bitmap(&DAT_004fcec0);
  }
  return 1;
}


