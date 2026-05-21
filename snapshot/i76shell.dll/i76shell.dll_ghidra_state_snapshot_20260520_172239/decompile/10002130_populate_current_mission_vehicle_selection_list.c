/*
 * Program: i76shell.dll
 * Function: populate_current_mission_vehicle_selection_list
 * Entry: 10002130
 * Signature: undefined __stdcall populate_current_mission_vehicle_selection_list(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void populate_current_mission_vehicle_selection_list(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined4 *puVar10;
  char *pcVar11;
  bool bVar12;
  int local_8;
  undefined4 *local_4;
  
  iVar7 = DAT_100cc4fc;
  iVar8 = DAT_100cc4fc * 0x8c4;
  iVar2 = *(int *)(&DAT_100581dc + iVar8);
  puVar3 = (undefined4 *)(&DAT_100581e0 + iVar8);
  puVar10 = &DAT_1004f860;
  DAT_100cc4f8 = iVar2;
  for (uVar4 = (uint)(iVar2 << 5) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar10 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar10 = puVar10 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined1 *)puVar10 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar10 = (undefined4 *)((int)puVar10 + 1);
  }
  _DAT_1004f718 = *(undefined4 *)(&DAT_1005899c + iVar8);
  _DAT_1004f71c = *(undefined4 *)(&DAT_100589a0 + iVar8);
  _DAT_1004f720 = *(undefined4 *)(&DAT_100589a4 + iVar8);
  _DAT_1004f724 = *(undefined4 *)(&DAT_100589a8 + iVar8);
  _DAT_1004f700 = *(undefined4 *)(&DAT_100589ac + iVar8);
  _DAT_1004f704 = *(undefined4 *)(&DAT_100589b0 + iVar8);
  _DAT_1004f708 = *(undefined4 *)(&DAT_100589b4 + iVar8);
  _DAT_1004fc20 = *(undefined4 *)(&DAT_100589bc + iVar8);
  _DAT_1004f70c = *(undefined4 *)(&DAT_100589b8 + iVar8);
  uVar4 = 0xffffffff;
  pcVar9 = &DAT_100581b4 + iVar8;
  do {
    pcVar11 = pcVar9;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar11;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar9 = pcVar11 + -uVar4;
  pcVar11 = (char *)&DAT_1004f730;
  for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar11 = pcVar11 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar9 = (char *)(&DAT_100581a0 + iVar7 * 0x231);
  do {
    pcVar11 = pcVar9;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar11 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar11;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar8 = 0;
  local_8 = 0;
  pcVar9 = pcVar11 + -uVar4;
  pcVar11 = (char *)&DAT_1004f748;
  for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar11 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar11 = pcVar11 + 1;
  }
  if (0 < iVar2) {
    local_4 = &DAT_1004f860;
    do {
      iVar5 = 0;
      iVar2 = strncmp(&DAT_100585a0 + iVar7 * 0x8c4 + iVar8,&DAT_100c6288,0xf);
      if (iVar2 != 0) {
        pcVar9 = &DAT_100c6288;
        do {
          if (DAT_10047710 <= iVar5) break;
          pcVar9 = pcVar9 + 0x54;
          iVar5 = iVar5 + 1;
          iVar2 = strncmp(&DAT_100585a0 + DAT_100cc4fc * 0x8c4 + iVar8,pcVar9,0xf);
        } while (iVar2 != 0);
      }
      puVar3 = HeapAlloc(DAT_10051c50,1,0x20);
      *puVar3 = 0;
      if (DAT_100cc500 == (undefined4 *)0x0) {
        DAT_100cc500 = puVar3;
        puVar3[1] = puVar3;
        puVar3[2] = puVar3;
      }
      else {
        puVar3[1] = DAT_100cc500;
        *(undefined4 **)(DAT_100cc500[2] + 4) = puVar3;
        puVar3[2] = DAT_100cc500[2];
        DAT_100cc500[2] = puVar3;
      }
      puVar3[3] = 0;
      puVar3[5] = 0;
      puVar3[6] = 0;
      puVar3[7] = 0;
      puVar3[4] = 1;
      *puVar3 = &DAT_100c6288 + iVar5 * 0x54;
      puVar3[5] = *local_4;
      bVar12 = DAT_100cc500 == (undefined4 *)0x0;
      local_4[7] = puVar3;
      if (bVar12) {
        DAT_100cc500 = puVar3;
      }
      local_8 = local_8 + 1;
      iVar8 = iVar8 + 0x1e;
      local_4 = local_4 + 8;
      iVar7 = DAT_100cc4fc;
    } while (local_8 < DAT_100cc4f8);
  }
  return;
}


