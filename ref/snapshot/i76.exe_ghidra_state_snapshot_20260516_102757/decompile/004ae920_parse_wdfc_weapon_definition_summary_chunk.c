/*
 * Program: i76.exe
 * Function: parse_wdfc_weapon_definition_summary_chunk
 * Entry: 004ae920
 * Signature: undefined4 __cdecl parse_wdfc_weapon_definition_summary_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=medium-high] Alternative WDFC callback used
   by summary/validation descriptor table for WDF weapon definitions. */

undefined4 __cdecl parse_wdfc_weapon_definition_summary_chunk(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  strncpy((char *)(param_2 + 0x18),(char *)(param_1 + 8),0x10);
  uVar2 = 0xffffffff;
  *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0x30);
  pcVar4 = (char *)(param_1 + 0x3c);
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
  pcVar5 = (char *)(param_2 + 0x2c);
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  *(float *)(param_2 + 0x3c) = *(float *)(param_1 + 0x34) + *(float *)(param_1 + 0x34);
  return 1;
}


