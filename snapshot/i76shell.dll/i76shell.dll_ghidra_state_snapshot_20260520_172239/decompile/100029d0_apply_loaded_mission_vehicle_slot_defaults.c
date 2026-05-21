/*
 * Program: i76shell.dll
 * Function: apply_loaded_mission_vehicle_slot_defaults
 * Entry: 100029d0
 * Signature: undefined __stdcall apply_loaded_mission_vehicle_slot_defaults(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void apply_loaded_mission_vehicle_slot_defaults(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  int *piVar8;
  
  _DAT_1004f71c = DAT_100c5c3c;
  _DAT_1004f718 = DAT_100c5c38;
  _DAT_1004f700 = DAT_100c5c48;
  _DAT_1004f724 = DAT_100c5c44;
  _DAT_1004f70c = DAT_100c5c54;
  _DAT_1004f720 = DAT_100c5c40;
  _DAT_1004f708 = DAT_100c5c50;
  iVar2 = 0;
  _DAT_1004f704 = DAT_100c5c4c;
  if (DAT_1004f860 != 2) {
    puVar6 = &DAT_1004f860;
    do {
      if (DAT_100cc4f8 <= iVar2) break;
      piVar7 = puVar6 + 8;
      puVar6 = puVar6 + 8;
      iVar2 = iVar2 + 1;
    } while (*piVar7 != 2);
  }
  *(undefined4 *)((&DAT_1004f87c)[iVar2 * 8] + 0xc) = DAT_100c5b20;
  iVar2 = 0;
  if (DAT_1004f860 != 4) {
    puVar6 = &DAT_1004f860;
    do {
      if (DAT_100cc4f8 <= iVar2) break;
      piVar7 = puVar6 + 8;
      puVar6 = puVar6 + 8;
      iVar2 = iVar2 + 1;
    } while (*piVar7 != 4);
  }
  iVar3 = 0;
  *(undefined4 *)((&DAT_1004f87c)[iVar2 * 8] + 0xc) = DAT_100c5b24;
  if (DAT_1004f860 != 3) {
    puVar6 = &DAT_1004f860;
    do {
      if (DAT_100cc4f8 <= iVar3) break;
      piVar7 = puVar6 + 8;
      puVar6 = puVar6 + 8;
      iVar3 = iVar3 + 1;
    } while (*piVar7 != 3);
  }
  *(undefined4 *)((&DAT_1004f87c)[iVar3 * 8] + 0xc) = DAT_100c5b28;
  iVar2 = 0;
  if (DAT_1004f860 != 5) {
    puVar6 = &DAT_1004f860;
    do {
      if (DAT_100cc4f8 <= iVar2) break;
      piVar7 = puVar6 + 8;
      puVar6 = puVar6 + 8;
      iVar2 = iVar2 + 1;
    } while (*piVar7 != 5);
  }
  iVar3 = iVar2 + 1;
  *(undefined4 *)((&DAT_1004f87c)[iVar2 * 8] + 0xc) = DAT_100c5b2c;
  iVar2 = (&DAT_1004f860)[iVar3 * 8];
  puVar6 = &DAT_1004f860 + iVar3 * 8;
  for (; (iVar2 != 5 && (iVar3 < DAT_100cc4f8)); iVar3 = iVar3 + 1) {
    iVar2 = puVar6[8];
    puVar6 = puVar6 + 8;
  }
  iVar4 = iVar3 + 1;
  *(undefined4 *)((&DAT_1004f87c)[iVar3 * 8] + 0xc) = DAT_100c5b30;
  iVar2 = (&DAT_1004f860)[iVar4 * 8];
  puVar6 = &DAT_1004f860 + iVar4 * 8;
  for (; (iVar2 != 5 && (iVar4 < DAT_100cc4f8)); iVar4 = iVar4 + 1) {
    iVar2 = puVar6[8];
    puVar6 = puVar6 + 8;
  }
  iVar3 = iVar4 + 1;
  puVar6 = &DAT_1004f860 + iVar3 * 8;
  iVar2 = (&DAT_1004f860)[iVar3 * 8];
  for (; (iVar2 != 5 && (iVar3 < DAT_100cc4f8)); iVar3 = iVar3 + 1) {
    iVar2 = puVar6[8];
    puVar6 = puVar6 + 8;
  }
  iVar5 = iVar3 + 1;
  puVar6 = &DAT_1004f860 + iVar5 * 8;
  iVar2 = (&DAT_1004f860)[iVar5 * 8];
  while (iVar2 != 5) {
    if (DAT_100cc4f8 <= iVar5) goto LAB_10002c58;
    piVar7 = puVar6 + 8;
    puVar6 = puVar6 + 8;
    iVar5 = iVar5 + 1;
    iVar2 = *piVar7;
  }
  if (iVar5 < DAT_100cc4f8) {
    *(undefined4 *)((&DAT_1004f87c)[iVar4 * 8] + 0xc) = DAT_100c5b34;
    *(undefined4 *)((&DAT_1004f87c)[iVar3 * 8] + 0xc) = DAT_100c5b38;
    iVar3 = iVar5 + 1;
    *(undefined4 *)((&DAT_1004f87c)[iVar5 * 8] + 0xc) = DAT_100c5b3c;
    iVar2 = (&DAT_1004f860)[iVar3 * 8];
    puVar6 = &DAT_1004f860 + iVar3 * 8;
    for (; (iVar2 != 5 && (iVar3 < DAT_100cc4f8)); iVar3 = iVar3 + 1) {
      iVar2 = puVar6[8];
      puVar6 = puVar6 + 8;
    }
    *(undefined4 *)((&DAT_1004f87c)[iVar3 * 8] + 0xc) = DAT_100c5b40;
  }
  else {
LAB_10002c58:
    *(undefined4 *)((&DAT_1004f87c)[iVar4 * 8] + 0xc) = DAT_100c5b3c;
    *(undefined4 *)((&DAT_1004f87c)[iVar3 * 8] + 0xc) = DAT_100c5b40;
  }
  iVar2 = 0;
  if (0 < DAT_100cc4f8) {
    piVar7 = &DAT_1004f860;
    do {
      if ((5 < *piVar7) && (*piVar7 < 0xc)) break;
      iVar2 = iVar2 + 1;
      piVar7 = piVar7 + 8;
    } while (iVar2 < DAT_100cc4f8);
  }
  if (iVar2 < DAT_100cc4f8) {
    iVar3 = 0;
    bVar1 = false;
    piVar7 = &DAT_100c5b44;
    do {
      if (DAT_100cc4f8 <= iVar3) break;
      if (*(int *)(&DAT_10058924 + (iVar2 + DAT_100cc4fc * 0x231) * 4) == *piVar7) {
        bVar1 = true;
      }
      else {
        iVar3 = iVar3 + 1;
        piVar7 = piVar7 + 1;
      }
    } while (!bVar1);
    iVar4 = iVar2 + 1;
    *(undefined4 *)((&DAT_1004f87c)[iVar2 * 8] + 0xc) = (&DAT_100c5bbc)[iVar3];
    if (iVar4 < DAT_100cc4f8) {
      piVar7 = &DAT_1004f860 + iVar4 * 8;
      iVar2 = DAT_100cc4fc;
      do {
        if (*piVar7 < 7) {
          return;
        }
        if (0xb < *piVar7) {
          return;
        }
        iVar3 = 0;
        bVar1 = false;
        piVar8 = &DAT_100c5b44;
        do {
          if (DAT_100cc4f8 <= iVar3) break;
          if (*(int *)(&DAT_10058924 + (iVar4 + iVar2 * 0x231) * 4) == *piVar8) {
            bVar1 = true;
          }
          else {
            iVar3 = iVar3 + 1;
            piVar8 = piVar8 + 1;
          }
        } while (!bVar1);
        if (bVar1) {
          *(undefined4 *)(piVar7[7] + 0xc) = (&DAT_100c5bbc)[iVar3];
          iVar2 = DAT_100cc4fc;
        }
        iVar4 = iVar4 + 1;
        piVar7 = piVar7 + 8;
      } while (iVar4 < DAT_100cc4f8);
    }
  }
  return;
}


