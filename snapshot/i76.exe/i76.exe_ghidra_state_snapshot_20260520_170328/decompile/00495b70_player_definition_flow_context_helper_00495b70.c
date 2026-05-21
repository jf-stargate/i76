/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00495b70
 * Entry: 00495b70
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00495b70(int param_1, int param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00495b70. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00495b70(int param_1,int param_2)

{
  if (param_2 == 6) {
    *(uint *)(param_1 + 0x18) = DAT_00654b98 & 1;
  }
  else {
    if (param_2 == 8) {
      if (*(int *)(param_1 + 0x18) != 0) {
        DAT_00654b98 = DAT_00654b98 | 1;
        set_active_vehicle_runtime_flag_0x10000(1);
        return 1;
      }
      DAT_00654b98 = DAT_00654b98 & 0xfffffffe;
      set_active_vehicle_runtime_flag_0x10000(0);
      return 1;
    }
    if (param_2 == 9) {
      DAT_00654b98 = DAT_00654bf8;
      return 1;
    }
  }
  return 1;
}


