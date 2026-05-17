/*
 * Program: i76.exe
 * Function: multiplayer_score_spawn_context_helper_00454ff0
 * Entry: 00454ff0
 * Signature: undefined __cdecl multiplayer_score_spawn_context_helper_00454ff0(short param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer score spawn context helper
   based on prior focused closure context. */

void __cdecl multiplayer_score_spawn_context_helper_00454ff0(short param_1)

{
  undefined4 uVar1;
  short sVar2;
  short *psVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined2 in_stack_00000006;
  undefined4 local_50 [20];
  
  sVar2 = DAT_00541028;
  iVar7 = 0;
  psVar3 = &DAT_00541070;
  do {
    if (*psVar3 == DAT_00541028) break;
    psVar3 = psVar3 + 0x24;
    iVar7 = iVar7 + 1;
  } while ((int)psVar3 < 0x5414f0);
  if (iVar7 == 0x10) {
    iVar7 = -1;
  }
  if (iVar7 != -1) {
    psVar3 = (short *)(iVar7 * 0x48 + 0x5410ac);
    *psVar3 = *psVar3 + 1;
    psVar3 = &DAT_00541070;
    do {
      if (*psVar3 == param_1) break;
      psVar3 = psVar3 + 0x24;
    } while ((int)psVar3 < 0x5414f0);
    iVar4 = ftol();
    uVar1 = DAT_00541024;
    (&DAT_005410b0)[iVar7 * 0x12] = (&DAT_005410b0)[iVar7 * 0x12] + iVar4;
    _param_1 = CONCAT22(in_stack_00000006,sVar2);
    puVar8 = local_50;
    for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
    }
    dpGetPlayerName(uVar1,_param_1,local_50,0x50);
    uVar5 = multiplayer_chat_ui_context_helper_00452df0();
    if (uVar5 != 0) {
      iVar4 = multiplayer_chat_ui_context_helper_00452e10();
      if (iVar4 == 0) {
        uVar6 = (&DAT_005410b0)[iVar7 * 0x12];
      }
      else {
        uVar6 = multiplayer_network_scoreboard_table_helper_00452930
                          ((uint)(&DAT_0054108c)[iVar7 * 0x12] >> 0x10 & 7,(short *)0x0,(short *)0x0
                          );
      }
      if (uVar5 <= uVar6) {
        multiplayer_chat_ui_context_helper_00453a90((&DAT_00541070)[iVar7 * 0x24]);
        DAT_005dd330 = 1;
      }
    }
  }
  return;
}


