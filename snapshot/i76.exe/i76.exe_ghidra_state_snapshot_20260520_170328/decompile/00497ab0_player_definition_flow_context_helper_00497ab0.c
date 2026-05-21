/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00497ab0
 * Entry: 00497ab0
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00497ab0(undefined4 param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00497ab0. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00497ab0(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_10 [4];
  
  if (param_2 == 4) {
    puVar1 = (undefined4 *)fill_recommended_performance_options(local_10);
    _DAT_00654b84 = puVar1[1];
    _DAT_00654b88 = puVar1[2];
    DAT_00654b8c = puVar1[3];
    g_display_mode_variant_index = (undefined1)*puVar1;
    DAT_005a60c0._0_1_ = g_display_mode_variant_index;
    _g_display_mode_variant_index = CONCAT31((int3)((uint)*puVar1 >> 8),DAT_005a60bc);
    uVar2 = load_selected_loading_screen_bitmap(g_current_loading_screen_record);
    return uVar2;
  }
  return 1;
}


