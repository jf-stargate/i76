/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00495970
 * Entry: 00495970
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00495970(undefined4 param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00495970. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00495970(undefined4 param_1,int param_2)

{
  if (param_2 == 4) {
    if (((DAT_00504c10 == 0) && (((byte)DAT_00654b98 & 2) == 0)) && (DAT_005dd2f4 == 0)) {
      _DAT_004fc458 = &DAT_004fc220;
      _DAT_004fc45c = 5;
      load_selected_loading_screen_bitmap((undefined *)&PTR_DAT_004fc440);
      return 1;
    }
    _DAT_004fc458 = &DAT_004fc350;
    _DAT_004fc45c = 4;
    load_selected_loading_screen_bitmap((undefined *)&PTR_DAT_004fc440);
  }
  return 1;
}


