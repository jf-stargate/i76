/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00497a30
 * Entry: 00497a30
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00497a30(undefined4 param_1, int param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00497a30. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00497a30(undefined4 param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  
  if ((3 < param_2) && ((param_2 < 6 || (param_2 == 9)))) {
    pbVar3 = (byte *)g_current_loading_screen_record[6];
    piVar1 = g_current_loading_screen_record + 7;
    iVar4 = 0;
    if (0 < (int)g_current_loading_screen_record[7]) {
      do {
        if ((*(code **)(pbVar3 + 8) != (code *)0x0) && ((*pbVar3 & 2) == 0)) {
          (**(code **)(pbVar3 + 8))(pbVar3,9);
        }
        iVar4 = iVar4 + 1;
        pbVar3 = pbVar3 + 0x3c;
      } while (iVar4 < *piVar1);
    }
    g_loading_screen_previous_state = 0;
    uVar2 = load_selected_loading_screen_bitmap((undefined *)*g_current_loading_screen_record);
    return uVar2;
  }
  return 1;
}


