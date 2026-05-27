/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00495bf0
 * Entry: 00495bf0
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00495bf0(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00495bf0. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00495bf0(int param_1,int param_2)

{
  if (param_2 == 6) {
    *(uint *)(param_1 + 0x18) = DAT_00654b98 >> 1 & 1;
  }
  else {
    if (param_2 == 8) {
      if (*(int *)(param_1 + 0x18) != 0) {
        _DAT_004fc458 = &DAT_004fc350;
        DAT_00654b98 = DAT_00654b98 | 2;
        _DAT_004fc45c = 4;
        return 1;
      }
      _DAT_004fc458 = &DAT_004fc220;
      DAT_00654b98 = DAT_00654b98 & 0xfffffffd;
      _DAT_004fc45c = 5;
      return 1;
    }
    if (param_2 == 9) {
      DAT_00654b98 = DAT_00654bf8;
      return 1;
    }
  }
  return 1;
}


