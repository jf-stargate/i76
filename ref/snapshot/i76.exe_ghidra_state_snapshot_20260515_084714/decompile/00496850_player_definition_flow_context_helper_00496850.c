/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00496850
 * Entry: 00496850
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00496850(undefined4 param_1, int param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00496850. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00496850(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 4) {
    uVar1 = load_selected_loading_screen_bitmap((undefined *)*g_current_loading_screen_record);
    return uVar1;
  }
  return 0;
}


