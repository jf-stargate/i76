/*
 * Program: i76.exe
 * Function: find_cutscene_smk_file
 * Entry: 0049a4c0
 * Signature: undefined4 __cdecl find_cutscene_smk_file(char * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: strings cutscene and smk directories */

undefined4 __cdecl find_cutscene_smk_file(char *param_1,int param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  undefined1 local_24 [20];
  int local_10;
  
  bVar1 = true;
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    cVar2 = get_active_cdrom_drive_letter();
    if (cVar2 == '\0') {
      DAT_005a7cd8 = s_smk__004fe28c[0];
      DAT_005a7cd9 = s_smk__004fe28c[1];
      DAT_005a7cd8_1._1_1_ = s_smk__004fe28c[2];
      DAT_005a7cd8_1._2_1_ = s_smk__004fe28c[3];
      DAT_005a7cdc = s_smk__004fe28c[4];
    }
    else {
      DAT_005a7cd8 = s___cutscene__004fe294[0];
      DAT_005a7cd9 = s___cutscene__004fe294[1];
      DAT_005a7cd8_1._1_1_ = s___cutscene__004fe294[2];
      DAT_005a7cd8_1._2_1_ = s___cutscene__004fe294[3];
      DAT_005a7cdc = s___cutscene__004fe294[4];
      DAT_005a7cdd = s___cutscene__004fe294[5];
      DAT_005a7cdc_1._1_1_ = s___cutscene__004fe294[6];
      DAT_005a7cdc_1._2_1_ = s___cutscene__004fe294[7];
      DAT_005a7ce0 = s___cutscene__004fe294[8];
      DAT_005a7ce0_1._0_1_ = s___cutscene__004fe294[9];
      DAT_005a7ce0_1._1_1_ = s___cutscene__004fe294[10];
      DAT_005a7ce0_1._2_1_ = s___cutscene__004fe294[0xb];
      DAT_005a7ce4 = s___cutscene__004fe294[0xc];
      cVar2 = get_active_cdrom_drive_letter();
      DAT_005a7cd8 = cVar2;
    }
    uVar3 = 0xffffffff;
    pcVar6 = param_1;
    do {
      pcVar8 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar8 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar2 != '\0');
    uVar3 = ~uVar3;
    iVar4 = -1;
    pcVar6 = &DAT_005a7cd8;
    do {
      pcVar7 = pcVar6;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar2 != '\0');
    pcVar6 = pcVar8 + -uVar3;
    pcVar8 = pcVar7 + -1;
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    iVar4 = stat(&DAT_005a7cd8,local_24);
    if (iVar4 == -1) {
      bVar1 = false;
      cVar2 = get_active_cdrom_drive_letter();
      if ((cVar2 != '\0') && (param_2 != 0)) {
        DAT_005a7cd8 = s_smk__004fe28c[0];
        DAT_005a7cd9 = s_smk__004fe28c[1];
        DAT_005a7cd8_1._1_1_ = s_smk__004fe28c[2];
        DAT_005a7cd8_1._2_1_ = s_smk__004fe28c[3];
        uVar3 = 0xffffffff;
        DAT_005a7cdc = s_smk__004fe28c[4];
        do {
          pcVar6 = param_1;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pcVar6 = param_1 + 1;
          cVar2 = *param_1;
          param_1 = pcVar6;
        } while (cVar2 != '\0');
        uVar3 = ~uVar3;
        iVar4 = -1;
        pcVar8 = &DAT_005a7cd8;
        do {
          pcVar7 = pcVar8;
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          pcVar7 = pcVar8 + 1;
          cVar2 = *pcVar8;
          pcVar8 = pcVar7;
        } while (cVar2 != '\0');
        pcVar6 = pcVar6 + -uVar3;
        pcVar8 = pcVar7 + -1;
        for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar8 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar8 = pcVar8 + 1;
        }
        iVar4 = stat(&DAT_005a7cd8,local_24);
        if (iVar4 != -1) {
          bVar1 = true;
        }
      }
    }
    if ((bVar1) && ((param_2 == 0 || (param_2 == local_10)))) {
      return 1;
    }
  }
  return 0;
}


