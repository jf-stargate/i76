/*
 * Program: i76.exe
 * Function: multiplayer_chat_ui_context_helper_004541b0
 * Entry: 004541b0
 * Signature: undefined4 __cdecl multiplayer_chat_ui_context_helper_004541b0(undefined4 param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was multiplayer_network_multiplayer_chat_ui_helper_004541b0. Remove
   duplicated multiplayer wording from readability label. */

undefined4 __cdecl multiplayer_chat_ui_context_helper_004541b0(undefined4 param_1)

{
  undefined4 uVar1;
  short *psVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  uchar *puVar7;
  float10 fVar8;
  uchar local_68;
  char local_67;
  
  uVar1 = param_1;
  psVar2 = &DAT_00541070;
  iVar4 = 0;
  do {
    sVar6 = (short)param_1;
    if (*psVar2 == sVar6) break;
    psVar2 = psVar2 + 0x24;
    iVar4 = iVar4 + 1;
  } while ((int)psVar2 < 0x5414f0);
  if (iVar4 == 0x10) {
    iVar4 = -1;
  }
  if (iVar4 != -1) {
    return 1;
  }
  iVar4 = 0;
  psVar2 = &DAT_00541070;
  do {
    if (*psVar2 == 0) break;
    psVar2 = psVar2 + 0x24;
    iVar4 = iVar4 + 1;
  } while ((int)psVar2 < 0x5414f0);
  if (iVar4 == 0x10) {
    return 0;
  }
  puVar7 = &local_68;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar7[0] = '\0';
    puVar7[1] = '\0';
    puVar7[2] = '\0';
    puVar7[3] = '\0';
    puVar7 = puVar7 + 4;
  }
  iVar5 = dpGetPlayerName(DAT_00541024,param_1,&local_68,0x68);
  if (iVar5 != 0) {
    return 0;
  }
  iVar5 = iVar4 * 0x48;
  (&DAT_00541070)[iVar4 * 0x24] = sVar6;
  _mbsnbcpy(&DAT_00541072 + iVar5,&local_68,0x18);
  *(undefined4 *)(iVar5 + 0x541090) = 0;
  *(undefined4 *)(iVar5 + 0x541094) = 0;
  (&DAT_00541098)[iVar4 * 0x12] = 0;
  (&DAT_005410a0)[iVar4 * 0x12] = 0xbf800000;
  fVar8 = get_multiplayer_or_runtime_seconds();
  (&DAT_0054109c)[iVar4 * 0x12] = (float)(fVar8 - (float10)_DAT_004bdf68);
  *(undefined4 *)(iVar5 + 0x5410a4) = 0;
  (&DAT_005410a8)[iVar4 * 0x12] = 0;
  *(undefined2 *)(iVar5 + 0x5410ac) = 0;
  *(undefined2 *)(iVar5 + 0x5410ae) = 0;
  (&DAT_005410b0)[iVar4 * 0x12] = 0;
  (&DAT_0054108c)[iVar4 * 0x12] = 0;
  *(undefined4 *)(iVar5 + 0x5410b4) = 0x3f800000;
  iVar5 = multiplayer_chat_ui_context_helper_00452e10();
  if (iVar5 == 0) {
    uVar3 = (&DAT_0054108c)[iVar4 * 0x12] | (uint)(sVar6 != DAT_00541028) << 0x10;
  }
  else {
    param_1 = 0x68;
    iVar5 = dpGetPlayerData(DAT_00541024,uVar1,1,&local_68,&param_1,0);
    if (iVar5 == 2) goto LAB_0045432d;
    uVar3 = (&DAT_0054108c)[iVar4 * 0x12] | (local_67 + 0xffff) * 0x10000 | 2U;
  }
  (&DAT_0054108c)[iVar4 * 0x12] = uVar3;
LAB_0045432d:
  DAT_00541068 = DAT_00541068 + 1;
  return 1;
}


