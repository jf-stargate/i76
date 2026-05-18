/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_004979a0
 * Entry: 004979a0
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_004979a0(undefined4 param_1, int param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_004979a0. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_004979a0(undefined4 param_1,int param_2)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  
  ppuVar1 = g_current_loading_screen_record;
  if (param_2 != 4) {
    return 1;
  }
  pbVar3 = g_current_loading_screen_record[6];
  iVar4 = 0;
  if (0 < (int)g_current_loading_screen_record[7]) {
    do {
      if ((*(code **)(pbVar3 + 8) != (code *)0x0) && ((*pbVar3 & 2) == 0)) {
        (**(code **)(pbVar3 + 8))(pbVar3,8);
      }
      iVar4 = iVar4 + 1;
      pbVar3 = pbVar3 + 0x3c;
    } while (iVar4 < (int)ppuVar1[7]);
  }
  g_loading_screen_previous_state = 1;
  if (((ppuVar1 != &PTR_DAT_004fcb38) && (ppuVar1 == &PTR_DAT_004fc6f8)) &&
     (((byte)DAT_00654b98 & 0x1c) != 0)) {
    uVar2 = load_selected_loading_screen_bitmap(&DAT_004fd018);
    return uVar2;
  }
  uVar2 = load_selected_loading_screen_bitmap(*g_current_loading_screen_record);
  return uVar2;
}


