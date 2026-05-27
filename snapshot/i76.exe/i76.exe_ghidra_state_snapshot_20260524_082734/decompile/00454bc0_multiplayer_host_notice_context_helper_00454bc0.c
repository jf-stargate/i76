/*
 * Program: i76.exe
 * Function: multiplayer_host_notice_context_helper_00454bc0
 * Entry: 00454bc0
 * Signature: float10 __cdecl multiplayer_host_notice_context_helper_00454bc0(short param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: multiplayer host notice context helper
   based on prior focused closure context. */

float10 __cdecl multiplayer_host_notice_context_helper_00454bc0(short param_1)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = 0;
  psVar1 = &DAT_00541070;
  do {
    if (*psVar1 == param_1) break;
    psVar1 = psVar1 + 0x24;
    iVar2 = iVar2 + 1;
  } while ((int)psVar1 < 0x5414f0);
  if (iVar2 == 0x10) {
    iVar2 = -1;
  }
  if (iVar2 == -1) {
    return (float10)_DAT_004bdf6c;
  }
  if ((&DAT_005410a0)[iVar2 * 0x12] == -0x40800000) {
    return (float10)_DAT_004bdf64;
  }
  return (float10)(float)(&DAT_005410a0)[iVar2 * 0x12];
}


