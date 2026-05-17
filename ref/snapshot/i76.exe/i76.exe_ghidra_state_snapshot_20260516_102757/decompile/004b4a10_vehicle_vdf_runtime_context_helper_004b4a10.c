/*
 * Program: i76.exe
 * Function: vehicle_vdf_runtime_context_helper_004b4a10
 * Entry: 004b4a10
 * Signature: undefined4 __cdecl vehicle_vdf_runtime_context_helper_004b4a10(int param_1, char * param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle vdf runtime context helper
   based on adjacent named subsystem context. */

undefined4 __cdecl vehicle_vdf_runtime_context_helper_004b4a10(int param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar2 = 0xffffffff;
  pcVar4 = (char *)(param_1 + 0x143);
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)param_2 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    param_2 = param_2 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_2 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    param_2 = param_2 + 1;
  }
  return 1;
}


