/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00495e40
 * Entry: 00495e40
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00495e40(int param_1, undefined4 param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00495e40. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00495e40(int param_1,undefined4 param_2)

{
  switch(param_2) {
  case 6:
    *(uint *)(param_1 + 0x18) = DAT_00654b9c & 0xff;
    return 1;
  case 7:
    DAT_00654b9c = CONCAT31(DAT_00654b9c._1_3_,*(undefined1 *)(param_1 + 0x18));
    return 1;
  case 8:
    DAT_00654bfc = (undefined1)DAT_00654b9c;
    return 1;
  case 9:
    DAT_00654b9c = CONCAT31(DAT_00654b9c._1_3_,DAT_00654bfc);
  }
  return 1;
}


