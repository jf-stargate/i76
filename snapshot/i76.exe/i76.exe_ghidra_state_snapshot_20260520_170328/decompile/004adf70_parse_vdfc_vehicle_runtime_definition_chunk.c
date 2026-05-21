/*
 * Program: i76.exe
 * Function: parse_vdfc_vehicle_runtime_definition_chunk
 * Entry: 004adf70
 * Signature: undefined4 __cdecl parse_vdfc_vehicle_runtime_definition_chunk(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] Alternate VDFC
   callback used by the runtime VDF descriptor table; copies vehicle definition fields into runtime
   descriptor storage. */

undefined4 __cdecl parse_vdfc_vehicle_runtime_definition_chunk(int param_1,int param_2)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  iVar3 = *(int *)(param_2 + 4);
  uVar4 = 0xffffffff;
  pcVar6 = (char *)(param_1 + 8);
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar7 + -uVar4;
  pcVar7 = (char *)(iVar3 + 0xa0);
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  *(undefined4 *)(iVar3 + 0xa5c) = *(undefined4 *)(param_1 + 0x44);
  uVar1 = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(iVar3 + 0xaa4) = uVar1;
  *(undefined4 *)(iVar3 + 0xaa0) = uVar1;
  return 1;
}


