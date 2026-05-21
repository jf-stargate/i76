/*
 * Program: i76shell.dll
 * Function: build_special_equipment_name_list
 * Entry: 100332c0
 * Signature: undefined __cdecl build_special_equipment_name_list(int param_1)
 */


void __cdecl build_special_equipment_name_list(int param_1)

{
  char cVar1;
  size_t *psVar2;
  int *piVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  char *pcVar11;
  undefined *puVar12;
  
  iVar8 = 0;
  puVar9 = &DAT_100f500c;
  do {
    puVar10 = puVar9 + -0x13;
    for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    iVar8 = iVar8 + 1;
    *(undefined4 *)((int)puVar9 + -0x2e) = 0xc;
    *puVar9 = 10;
    wsprintfA((LPSTR)((int)puVar9 + -0x1e),s_spc_2_2d_1004cd58,iVar8);
    puVar12 = (undefined *)0x0;
    piVar3 = FUN_1002c2b0((int)(puVar9 + -0x13));
    insert_pointer_list_item_sorted_or_append(param_1,(int)piVar3,puVar12);
    puVar9 = puVar9 + 0x15;
  } while ((int)puVar9 < 0x100f5300);
  pcVar4 = (char *)resolve_localized_shell_string_cached(DAT_100f5360,s_Radar_Jammer_1004cd64);
  psVar2 = DAT_100f5360;
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f4fc0;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  pcVar4 = (char *)resolve_localized_shell_string_cached(psVar2,s_NitrousOxide_1004cd74);
  psVar2 = DAT_100f5360;
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f5014;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  pcVar4 = (char *)resolve_localized_shell_string_cached(psVar2,s_Blower_1004cd84);
  psVar2 = DAT_100f5360;
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f5068;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  pcVar4 = (char *)resolve_localized_shell_string_cached(psVar2,s_X_Aust_Brake_1004cd8c);
  psVar2 = DAT_100f5360;
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f50bc;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  pcVar4 = (char *)resolve_localized_shell_string_cached(psVar2,s_Structo_Bmpr_1004cd9c);
  psVar2 = DAT_100f5360;
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f5110;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  pcVar4 = (char *)resolve_localized_shell_string_cached(psVar2,s_Curb_Feelers_1004cdac);
  psVar2 = DAT_100f5360;
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f5164;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  pcVar4 = (char *)resolve_localized_shell_string_cached(psVar2,s_Mud_Flaps_1004cdbc);
  psVar2 = DAT_100f5360;
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f51b8;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  pcVar4 = (char *)resolve_localized_shell_string_cached(psVar2,s_Heated_Seats_1004cdc8);
  psVar2 = DAT_100f5360;
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f520c;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  pcVar4 = (char *)resolve_localized_shell_string_cached(psVar2,s_Cup_Holders_1004cdd8);
  uVar6 = 0xffffffff;
  do {
    pcVar11 = pcVar4;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar11 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar4 = pcVar11 + -uVar6;
  pcVar11 = (char *)&DAT_100f5260;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar11 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar11 = pcVar11 + 1;
  }
  return;
}


