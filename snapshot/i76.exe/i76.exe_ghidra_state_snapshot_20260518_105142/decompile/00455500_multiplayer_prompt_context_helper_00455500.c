/*
 * Program: i76.exe
 * Function: multiplayer_prompt_context_helper_00455500
 * Entry: 00455500
 * Signature: undefined4 __stdcall multiplayer_prompt_context_helper_00455500(uint param_1)
 */


/* cgpt label refinement v18: was multiplayer_network_multiplayer_prompt_helper_00455500. Remove
   duplicated multiplayer wording from readability label. */

undefined4 multiplayer_prompt_context_helper_00455500(uint param_1)

{
  short *psVar1;
  int iVar2;
  short sVar3;
  
  sVar3 = (short)param_1;
  if (sVar3 == -0x5ff) {
    return 0;
  }
  multiplayer_chat_ui_context_helper_004541b0(param_1);
  iVar2 = 0;
  psVar1 = &DAT_00541070;
  do {
    if (*psVar1 == sVar3) break;
    psVar1 = psVar1 + 0x24;
    iVar2 = iVar2 + 1;
  } while ((int)psVar1 < 0x5414f0);
  if (iVar2 == 0x10) {
    iVar2 = -1;
  }
  if (iVar2 != -1) {
    param_1 = (&DAT_0054108c)[iVar2 * 0x12];
  }
  iVar2 = 0;
  psVar1 = &DAT_00541070;
  do {
    if (*psVar1 == sVar3) break;
    psVar1 = psVar1 + 0x24;
    iVar2 = iVar2 + 1;
  } while ((int)psVar1 < 0x5414f0);
  if (iVar2 == 0x10) {
    iVar2 = -1;
  }
  if (iVar2 != -1) {
    (&DAT_0054108c)[iVar2 * 0x12] = param_1 | 1;
  }
  return 1;
}


