/*
 * Program: i76.exe
 * Function: multiplayer_player_table_context_helper_004548a0
 * Entry: 004548a0
 * Signature: undefined4 __cdecl multiplayer_player_table_context_helper_004548a0(short param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was multiplayer_network_multiplayer_player_table_helper_004548a0.
   Remove duplicated multiplayer wording from readability label. */

undefined4 __cdecl multiplayer_player_table_context_helper_004548a0(short param_1,float param_2)

{
  float fVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  psVar2 = &DAT_00541070;
  do {
    if (*psVar2 == param_1) break;
    psVar2 = psVar2 + 0x24;
    iVar3 = iVar3 + 1;
  } while ((int)psVar2 < 0x5414f0);
  if (iVar3 == 0x10) {
    iVar3 = -1;
  }
  if (iVar3 == -1) {
    return 0;
  }
  iVar4 = 0;
  psVar2 = &DAT_00541070;
  do {
    if (*psVar2 == (&DAT_00541070)[iVar3 * 0x24]) break;
    psVar2 = psVar2 + 0x24;
    iVar4 = iVar4 + 1;
  } while ((int)psVar2 < 0x5414f0);
  if (iVar4 == 0x10) {
    iVar4 = -1;
  }
  fVar1 = _DAT_004bdf6c;
  if ((iVar4 != -1) && (fVar1 = _DAT_004bdf64, (&DAT_005410a0)[iVar4 * 0x12] != -0x40800000)) {
    fVar1 = (float)(&DAT_005410a0)[iVar4 * 0x12];
  }
  fVar1 = fVar1 + param_2;
  if (*(float *)(iVar3 * 0x48 + 0x5410a4) <= fVar1) {
    *(float *)(iVar3 * 0x48 + 0x5410a4) = fVar1;
    (&DAT_005410a8)[iVar3 * 0x12] = fVar1;
    return 1;
  }
  return 0;
}


