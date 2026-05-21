/*
 * Program: i76.exe
 * Function: mount_weapon_on_hardpoint
 * Entry: 004a2ff0
 * Signature: undefined __cdecl mount_weapon_on_hardpoint(char * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence max weapon definitions / nonexistent
   hardpoint */

void __cdecl mount_weapon_on_hardpoint(char *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  
                    /* I76 semantic baseline: mount_weapon_on_hardpoint
                       Mounts a weapon on a vehicle hardpoint. */
  iVar4 = DAT_005d88d4;
  iVar5 = 0;
  piVar3 = &DAT_005d8930;
  do {
    if ((piVar3[1] == *(int *)(param_1 + 0x50)) && (*piVar3 == *(int *)(param_1 + 0x54)))
    goto LAB_004a3022;
    piVar3 = piVar3 + 0x36;
    iVar5 = iVar5 + 1;
  } while ((int)piVar3 < 0x5da790);
  iVar5 = -1;
LAB_004a3022:
  if (iVar5 == -1) {
    if (DAT_005d88d4 < 0x24) {
      uVar6 = 0xffffffff;
      iVar5 = DAT_005d88d4 * 0xd8;
      pcVar8 = param_1;
      do {
        pcVar9 = pcVar8;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar9 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar8 = pcVar9 + -uVar6;
      pcVar9 = (char *)(&DAT_005d88d8 + DAT_005d88d4 * 0x36);
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar9 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar9 = pcVar9 + 1;
      }
      (&DAT_005d8927)[iVar5] = 0;
      (&DAT_005d8930)[iVar4 * 0x36] = *(undefined4 *)(param_1 + 0x54);
      (&DAT_005d8934)[iVar4 * 0x36] = *(undefined4 *)(param_1 + 0x50);
      *(undefined4 *)(&DAT_005d8938 + iVar5) = *(undefined4 *)(param_1 + 0x58);
      *(undefined4 *)(&DAT_005d893c + iVar5) = *(undefined4 *)(param_1 + 0x5c);
      *(undefined4 *)(&DAT_005d8940 + iVar5) = *(undefined4 *)(param_1 + 0x60);
      iVar2 = (&DAT_005d8934)[iVar4 * 0x36];
      *(undefined4 *)(&DAT_005d8944 + iVar5) = *(undefined4 *)(param_1 + 100);
      if ((iVar2 == 4) && ((&DAT_005d8930)[iVar4 * 0x36] == 4)) {
        *(undefined4 *)(&DAT_005d8944 + iVar5) = 0x3c23d70a;
      }
      *(undefined4 *)(&DAT_005d8948 + iVar5) = *(undefined4 *)(param_1 + 0x68);
      *(undefined4 *)(&DAT_005d8954 + iVar5) = *(undefined4 *)(param_1 + 0x6c);
      *(undefined4 *)(&DAT_005d8950 + iVar5) = *(undefined4 *)(param_1 + 0x70);
      *(undefined4 *)(&DAT_005d894c + iVar5) = *(undefined4 *)(param_1 + 0x74);
      *(undefined4 *)(&DAT_005d8958 + iVar5) = *(undefined4 *)(param_1 + 0x78);
      *(undefined4 *)(&DAT_005d895c + iVar5) = *(undefined4 *)(param_1 + 0x7c);
      *(undefined4 *)(&DAT_005d8960 + iVar5) = *(undefined4 *)(param_1 + 0x80);
      *(undefined4 *)(&DAT_005d8964 + iVar5) = *(undefined4 *)(param_1 + 0x84);
      uVar6 = 0xffffffff;
      pcVar8 = param_1 + 0x88;
      do {
        pcVar9 = pcVar8;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar9 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar8 = pcVar9 + -uVar6;
      pcVar9 = &DAT_005d8968 + iVar5;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar9 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar9 = pcVar9 + 1;
      }
      strncpy(&DAT_005d8980 + iVar5,param_1 + 0xb8,0x10);
      strncpy(&DAT_005d8995 + iVar5,param_1 + 0xcd,0x10);
      *(undefined4 *)(&DAT_005d8978 + iVar5) = *(undefined4 *)(param_1 + 0x98);
      *(undefined4 *)(&DAT_005d897c + iVar5) = *(undefined4 *)(param_1 + 0x9c);
    }
    else {
      report_error();
    }
    iVar5 = DAT_005d88d4;
    DAT_005d88d4 = DAT_005d88d4 + 1;
  }
  iVar4 = register_weapon_instance((int)param_1,iVar5);
  iVar5 = 0;
  piVar3 = DAT_005da754;
  do {
    piVar3 = piVar3 + 0x16;
    if (*piVar3 == *(int *)(param_1 + 0xa0)) goto LAB_004a31a0;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 7);
  iVar5 = -1;
LAB_004a31a0:
  if (iVar5 == -1) {
    report_error();
    return;
  }
  DAT_005da754[iVar5 * 0x16 + 0x2a] = iVar4;
  return;
}


