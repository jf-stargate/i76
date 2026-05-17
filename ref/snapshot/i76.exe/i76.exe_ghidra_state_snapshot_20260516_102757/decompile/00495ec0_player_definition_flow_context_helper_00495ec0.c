/*
 * Program: i76.exe
 * Function: player_definition_flow_context_helper_00495ec0
 * Entry: 00495ec0
 * Signature: undefined4 __cdecl player_definition_flow_context_helper_00495ec0(uint * param_1, undefined4 param_2)
 */


/* cgpt label refinement v20: was
   player_definition_runtime_player_definition_or_flow_helper_00495ec0. Shorten readability label
   for player-definition / mission-flow loading screen context. */

undefined4 __cdecl player_definition_flow_context_helper_00495ec0(uint *param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  switch(param_2) {
  case 2:
  case 3:
    uVar1 = *param_1;
    uVar2 = param_1[4];
    do {
      uVar3 = param_1[6];
      if (uVar2 == 1) {
        uVar4 = 0;
      }
      else {
        uVar4 = uVar3;
        switch(param_2) {
        case 0:
        case 2:
          uVar4 = uVar3 + 1;
          if (((int)uVar2 <= (int)(uVar3 + 1)) &&
             (((uVar1 & 0x180) == 0 || (uVar4 = uVar3, (uVar1 & 0x2000) != 0)))) {
            uVar4 = uVar1 >> 0xc & 1;
          }
          break;
        case 1:
        case 3:
          uVar4 = uVar3 - 1;
          if (((int)(uVar3 - 1) < (int)(uVar1 >> 0xc & 1)) &&
             (((uVar1 & 0x180) == 0 || (uVar4 = uVar3, (uVar1 & 0x2000) != 0)))) {
            uVar4 = uVar2 - 1;
          }
        }
      }
      param_1[6] = uVar4;
    } while ((&DAT_004f9e08)[uVar4 * 7] == 0);
    return 1;
  case 6:
    param_1[6] = DAT_005a60c0 & 0xff;
    return 1;
  case 8:
    DAT_005a60c0 = CONCAT31(DAT_005a60c0._1_3_,(char)param_1[6]);
    DAT_00654be0 = (char)param_1[6];
    return 1;
  case 9:
    DAT_005a60c0 = CONCAT31(DAT_005a60c0._1_3_,DAT_00654be0);
  }
  return 1;
}


