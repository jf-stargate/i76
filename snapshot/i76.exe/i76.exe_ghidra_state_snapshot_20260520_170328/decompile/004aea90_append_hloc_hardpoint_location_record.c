/*
 * Program: i76.exe
 * Function: append_hloc_hardpoint_location_record
 * Entry: 004aea90
 * Signature: undefined4 __cdecl append_hloc_hardpoint_location_record(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] Runtime HLOC callback: appends a
   hardpoint record with name, position, and extra fields into a seven-entry 0xfc-byte hardpoint
   table. */

undefined4 __cdecl append_hloc_hardpoint_location_record(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  iVar2 = *(int *)(param_2 + 4);
  if (6 < *(int *)(iVar2 + 0xa60)) {
    return 0;
  }
  uVar3 = 0xffffffff;
  pcVar5 = (char *)(param_1 + 8);
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = (char *)(iVar2 + 0x378 + *(int *)(iVar2 + 0xa60) * 0xfc);
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  *(undefined4 *)(iVar2 + 0x428 + *(int *)(iVar2 + 0xa60) * 0xfc) = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(iVar2 + 0x42c + *(int *)(iVar2 + 0xa60) * 0xfc) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(iVar2 + 0x430 + *(int *)(iVar2 + 0xa60) * 0xfc) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(iVar2 + 0x464 + *(int *)(iVar2 + 0xa60) * 0xfc) = *(undefined4 *)(param_1 + 0x54);
  *(int *)(iVar2 + 0xa60) = *(int *)(iVar2 + 0xa60) + 1;
  return 1;
}


