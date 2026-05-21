/*
 * Program: i76.exe
 * Function: multiplayer_player_table_context_helper_00455130
 * Entry: 00455130
 * Signature: undefined __cdecl multiplayer_player_table_context_helper_00455130(short param_1)
 */


/* cgpt label refinement v18: was multiplayer_network_multiplayer_player_table_helper_00455130.
   Remove duplicated multiplayer wording from readability label. */

void __cdecl multiplayer_player_table_context_helper_00455130(short param_1)

{
  short sVar1;
  short *psVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined2 in_stack_00000006;
  undefined4 local_50 [20];
  
  sVar1 = DAT_00541028;
  iVar3 = 0;
  psVar2 = &DAT_00541070;
  do {
    if (*psVar2 == DAT_00541028) break;
    psVar2 = psVar2 + 0x24;
    iVar3 = iVar3 + 1;
  } while ((int)psVar2 < 0x5414f0);
  if (iVar3 == 0x10) {
    iVar3 = -1;
  }
  if (iVar3 != -1) {
    psVar2 = (short *)(iVar3 * 0x48 + 0x5410ae);
    *psVar2 = *psVar2 + 1;
    uVar4 = (&DAT_005410b0)[iVar3 * 0x12];
    if (param_1 == 0) {
      uVar4 = uVar4 - 500;
    }
    else {
      psVar2 = &DAT_00541070;
      do {
        if (*psVar2 == param_1) break;
        psVar2 = psVar2 + 0x24;
      } while ((int)psVar2 < 0x5414f0);
    }
    _param_1 = CONCAT22(in_stack_00000006,sVar1);
    (&DAT_005410b0)[iVar3 * 0x12] = ((int)uVar4 < 0) - 1 & uVar4;
    puVar5 = local_50;
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    dpGetPlayerName(DAT_00541024,_param_1,local_50,0x50);
  }
  return;
}


