/*
 * Program: i76.exe
 * Function: multiplayer_player_state_lookup_helper_00454ea0
 * Entry: 00454ea0
 * Signature: undefined __cdecl multiplayer_player_state_lookup_helper_00454ea0(short param_1, undefined4 param_2, undefined2 param_3, undefined2 param_4)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer player state lookup helper
   based on prior focused closure context. */

void __cdecl
multiplayer_player_state_lookup_helper_00454ea0
          (short param_1,undefined4 param_2,undefined2 param_3,undefined2 param_4)

{
  short *psVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = 0;
  psVar1 = &DAT_00541070;
  do {
    if (*psVar1 == param_1) break;
    psVar1 = psVar1 + 0x24;
    iVar5 = iVar5 + 1;
  } while ((int)psVar1 < 0x5414f0);
  if (iVar5 == 0x10) {
    iVar5 = -1;
  }
  if (iVar5 != -1) {
    (&DAT_005410b0)[iVar5 * 0x12] = param_2;
    *(undefined2 *)(iVar5 * 0x48 + 0x5410ac) = param_3;
    *(undefined2 *)(iVar5 * 0x48 + 0x5410ae) = param_4;
    uVar2 = multiplayer_chat_ui_context_helper_00452df0();
    if (uVar2 != 0) {
      iVar3 = multiplayer_chat_ui_context_helper_00452e10();
      if (iVar3 == 0) {
        uVar4 = (&DAT_005410b0)[iVar5 * 0x12];
      }
      else {
        uVar4 = multiplayer_network_scoreboard_table_helper_00452930
                          ((uint)(&DAT_0054108c)[iVar5 * 0x12] >> 0x10 & 7,(short *)0x0,(short *)0x0
                          );
      }
      if (uVar2 <= uVar4) {
        multiplayer_chat_ui_context_helper_00453a90((&DAT_00541070)[iVar5 * 0x24]);
        DAT_005dd330 = 1;
      }
    }
  }
  return;
}


