/*
 * Program: i76.exe
 * Function: build_vehicle_descriptor_from_loaded_definition
 * Entry: 004b6850
 * Signature: undefined __cdecl build_vehicle_descriptor_from_loaded_definition(int param_1, char * param_2, int param_3, char * param_4, int param_5)
 */


/* WARNING: Type propagation algorithm not settling */
/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Builds shell vehicle descriptor from
   loaded definition, with explicit validation diagnostics for engine, suspension, brake, front/rear
   tires, wheels, and weapons. */

void __cdecl
build_vehicle_descriptor_from_loaded_definition
          (int param_1,char *param_2,int param_3,char *param_4,int param_5)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  char *pcVar12;
  undefined4 *puVar13;
  char *pcVar14;
  int local_150;
  char *local_144;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  char local_130 [16];
  char local_120 [13];
  char local_113 [13];
  undefined4 local_106;
  undefined4 local_102;
  undefined4 local_fe;
  char local_fa [13];
  char local_ed [4];
  char local_e9;
  char local_e0 [13];
  undefined4 local_d3;
  undefined4 local_cf;
  undefined4 local_cb;
  undefined4 local_c7;
  undefined4 local_c3;
  undefined4 local_bf;
  undefined4 local_bb;
  undefined4 local_b7;
  undefined4 local_b3;
  undefined4 local_ac [4];
  char local_9b [155];
  
  pcVar11 = local_130;
  for (iVar6 = 0x20; iVar6 != 0; iVar6 = iVar6 + -1) {
    pcVar11[0] = '\0';
    pcVar11[1] = '\0';
    pcVar11[2] = '\0';
    pcVar11[3] = '\0';
    pcVar11 = pcVar11 + 4;
  }
  *pcVar11 = '\0';
  puVar13 = local_ac;
  for (iVar6 = 0x2a; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  *(undefined2 *)puVar13 = 0;
  uVar7 = 0xffffffff;
  iVar6 = param_5 * 0x8c4;
  pcVar11 = (char *)(param_1 + 0x14 + iVar6);
  do {
    pcVar14 = pcVar11;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar11 + 1;
    cVar2 = *pcVar11;
    pcVar11 = pcVar14;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  pcVar11 = pcVar14 + -uVar7;
  pcVar14 = local_130;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar14 = pcVar14 + 1;
  }
  uVar7 = 0xffffffff;
  pcVar11 = (char *)(param_1 + 0x820 + iVar6);
  do {
    pcVar14 = pcVar11;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar11 + 1;
    cVar2 = *pcVar11;
    pcVar11 = pcVar14;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  pcVar11 = pcVar14 + -uVar7;
  pcVar14 = local_120;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar14 = pcVar14 + 1;
  }
  uVar7 = 0xffffffff;
  pcVar11 = (char *)(param_1 + 0x82d + iVar6);
  do {
    pcVar14 = pcVar11;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar11 + 1;
    cVar2 = *pcVar11;
    pcVar11 = pcVar14;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  pcVar11 = pcVar14 + -uVar7;
  pcVar14 = local_113;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar14 = pcVar14 + 4;
  }
  iVar3 = 0;
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar14 = pcVar14 + 1;
  }
  if (*(int *)(param_1 + 0x40 + iVar6) != 2) {
    iVar9 = param_1 + 0x40 + iVar6;
    do {
      if (*(int *)(param_1 + 0x3c + iVar6) <= iVar3) break;
      piVar1 = (int *)(iVar9 + 0x20);
      iVar9 = iVar9 + 0x20;
      iVar3 = iVar3 + 1;
    } while (*piVar1 != 2);
  }
  piVar1 = (int *)(param_1 + 0x3c + iVar6);
  if (iVar3 == *(int *)(param_1 + 0x3c + iVar6)) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  iVar9 = 0;
  if (0 < param_3) {
    pcVar11 = param_2;
    do {
      iVar4 = _stricmp((char *)(param_1 + iVar3 * 0x1e + 0x400 + iVar6),pcVar11);
      if (iVar4 == 0) break;
      iVar9 = iVar9 + 1;
      pcVar11 = pcVar11 + 0x54;
    } while (iVar9 < param_3);
  }
  if (iVar9 == param_3) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  local_106 = *(undefined4 *)(param_2 + iVar9 * 0x54 + 0x48);
  iVar3 = 0;
  if (*(int *)(param_1 + 0x40 + iVar6) != 3) {
    iVar9 = param_1 + 0x40 + iVar6;
    do {
      if (*piVar1 <= iVar3) break;
      piVar5 = (int *)(iVar9 + 0x20);
      iVar9 = iVar9 + 0x20;
      iVar3 = iVar3 + 1;
    } while (*piVar5 != 3);
  }
  if (iVar3 == *piVar1) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  iVar9 = 0;
  if (0 < param_3) {
    pcVar11 = param_2;
    do {
      iVar4 = _stricmp((char *)(param_1 + iVar3 * 0x1e + 0x400 + iVar6),pcVar11);
      if (iVar4 == 0) break;
      iVar9 = iVar9 + 1;
      pcVar11 = pcVar11 + 0x54;
    } while (iVar9 < param_3);
  }
  if (iVar9 == param_3) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  local_102 = *(undefined4 *)(param_2 + iVar9 * 0x54 + 0x48);
  iVar3 = 0;
  if (*(int *)(param_1 + 0x40 + iVar6) != 4) {
    iVar9 = param_1 + 0x40 + iVar6;
    do {
      if (*piVar1 <= iVar3) break;
      piVar5 = (int *)(iVar9 + 0x20);
      iVar9 = iVar9 + 0x20;
      iVar3 = iVar3 + 1;
    } while (*piVar5 != 4);
  }
  if (iVar3 == *piVar1) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  iVar9 = 0;
  if (0 < param_3) {
    pcVar11 = param_2;
    do {
      iVar4 = _stricmp((char *)(param_1 + iVar3 * 0x1e + 0x400 + iVar6),pcVar11);
      if (iVar4 == 0) break;
      iVar9 = iVar9 + 1;
      pcVar11 = pcVar11 + 0x54;
    } while (iVar9 < param_3);
  }
  if (iVar9 == param_3) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  local_fe = *(undefined4 *)(param_2 + iVar9 * 0x54 + 0x48);
  iVar3 = 0;
  if (*(int *)(param_1 + 0x40 + iVar6) != 5) {
    iVar9 = param_1 + 0x40 + iVar6;
    do {
      if (*piVar1 <= iVar3) break;
      piVar5 = (int *)(iVar9 + 0x20);
      iVar9 = iVar9 + 0x20;
      iVar3 = iVar3 + 1;
    } while (*piVar5 != 5);
  }
  if (iVar3 == *piVar1) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  iVar9 = 0;
  if (0 < param_3) {
    pcVar11 = param_2;
    do {
      iVar4 = _stricmp((char *)(param_1 + iVar3 * 0x1e + 0x400 + iVar6),pcVar11);
      if (iVar4 == 0) break;
      iVar9 = iVar9 + 1;
      pcVar11 = pcVar11 + 0x54;
    } while (iVar9 < param_3);
  }
  if (iVar9 == param_3) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  uVar7 = 0xffffffff;
  pcVar11 = param_2 + iVar9 * 0x54 + 0x3b;
  do {
    pcVar14 = pcVar11;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar11 + 1;
    cVar2 = *pcVar11;
    pcVar11 = pcVar14;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  pcVar11 = pcVar14 + -uVar7;
  pcVar14 = local_fa;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar14 = pcVar14 + 1;
  }
  iVar4 = iVar3 + 2;
  iVar9 = (iVar3 + 4) * 0x20 + param_1;
  iVar3 = iVar9 + iVar6;
  if (*(int *)(iVar9 + iVar6) != 5) {
    do {
      if (*piVar1 <= iVar4) break;
      piVar5 = (int *)(iVar3 + 0x20);
      iVar3 = iVar3 + 0x20;
      iVar4 = iVar4 + 1;
    } while (*piVar5 != 5);
  }
  if (iVar4 == *piVar1) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  iVar3 = 0;
  if (0 < param_3) {
    pcVar11 = param_2;
    do {
      iVar9 = _stricmp((char *)(param_1 + iVar4 * 0x1e + 0x400 + iVar6),pcVar11);
      if (iVar9 == 0) break;
      iVar3 = iVar3 + 1;
      pcVar11 = pcVar11 + 0x54;
    } while (iVar3 < param_3);
  }
  if (iVar3 == param_3) {
    report_error();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  iVar10 = iVar4 + 2;
  iVar4 = (iVar4 + 4) * 0x20 + param_1;
  iVar9 = iVar4 + iVar6;
  if (*(int *)(iVar4 + iVar6) != 5) {
    do {
      if (*piVar1 <= iVar10) break;
      piVar5 = (int *)(iVar9 + 0x20);
      iVar9 = iVar9 + 0x20;
      iVar10 = iVar10 + 1;
    } while (*piVar5 != 5);
  }
  if (iVar10 == *piVar1) {
    uVar7 = 0xffffffff;
    pcVar11 = param_2 + iVar3 * 0x54 + 0x3b;
    do {
      pcVar14 = pcVar11;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar11 + 1;
      cVar2 = *pcVar11;
      pcVar11 = pcVar14;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    pcVar11 = pcVar14 + -uVar7;
    pcVar14 = local_e0;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar14 = pcVar14 + 1;
    }
    local_e9 = s_NULL_005009ec[4];
    local_ed[0] = s_NULL_005009ec[0];
    local_ed[1] = s_NULL_005009ec[1];
    local_ed[2] = s_NULL_005009ec[2];
    local_ed[3] = s_NULL_005009ec[3];
  }
  else {
    iVar9 = 0;
    if (0 < param_3) {
      pcVar11 = param_2;
      do {
        iVar4 = _stricmp((char *)(param_1 + iVar10 * 0x1e + 0x400 + iVar6),pcVar11);
        if (iVar4 == 0) break;
        iVar9 = iVar9 + 1;
        pcVar11 = pcVar11 + 0x54;
      } while (iVar9 < param_3);
    }
    if (iVar9 == param_3) {
      report_error();
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    uVar7 = 0xffffffff;
    pcVar11 = param_2 + iVar3 * 0x54 + 0x3b;
    do {
      pcVar14 = pcVar11;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar11 + 1;
      cVar2 = *pcVar11;
      pcVar11 = pcVar14;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    pcVar11 = pcVar14 + -uVar7;
    pcVar14 = local_ed;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar14 = pcVar14 + 1;
    }
    uVar7 = 0xffffffff;
    pcVar11 = param_2 + iVar9 * 0x54 + 0x3b;
    do {
      pcVar14 = pcVar11;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar11 + 1;
      cVar2 = *pcVar11;
      pcVar11 = pcVar14;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    pcVar11 = pcVar14 + -uVar7;
    pcVar14 = local_e0;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar14 = pcVar14 + 1;
    }
  }
  local_cf = *(undefined4 *)(param_1 + 0x800 + iVar6);
  local_d3 = *(undefined4 *)(param_1 + 0x7fc + iVar6);
  local_c7 = *(undefined4 *)(param_1 + 0x808 + iVar6);
  local_cb = *(undefined4 *)(param_1 + 0x804 + iVar6);
  local_bf = *(undefined4 *)(param_1 + 0x810 + iVar6);
  local_c3 = *(undefined4 *)(param_1 + 0x80c + iVar6);
  local_b7 = *(undefined4 *)(param_1 + 0x818 + iVar6);
  local_bb = *(undefined4 *)(param_1 + 0x814 + iVar6);
  local_b3 = *(undefined4 *)(param_1 + 0x81c + iVar6);
  local_13c = 0;
  iVar3 = 0;
  local_138 = 0;
  local_134 = 0;
  local_150 = 0;
  for (piVar5 = (int *)(param_1 + 0x40 + iVar6); (*piVar5 < 7 || (0xb < *piVar5));
      piVar5 = piVar5 + 8) {
    iVar9 = *piVar1;
    if (iVar9 <= iVar3) goto LAB_004b6f42;
    iVar3 = iVar3 + 1;
  }
  iVar9 = *piVar1;
LAB_004b6f42:
  if (iVar3 != iVar9) {
    iVar9 = 0;
    if (0 < param_3) {
      pcVar11 = param_2;
      do {
        iVar4 = _stricmp((char *)(param_1 + iVar3 * 0x1e + 0x400 + iVar6),pcVar11);
        if (iVar4 == 0) break;
        iVar9 = iVar9 + 1;
        pcVar11 = pcVar11 + 0x54;
      } while (iVar9 < param_3);
    }
    if (iVar9 == param_3) {
      report_error();
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    local_150 = 1;
    uVar7 = 0xffffffff;
    pcVar11 = param_2 + iVar9 * 0x54 + 0x3b;
    do {
      pcVar14 = pcVar11;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar11 + 1;
      cVar2 = *pcVar11;
      pcVar11 = pcVar14;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    pcVar11 = pcVar14 + -uVar7;
    pcVar14 = (char *)(local_ac + 1);
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar14 = pcVar14 + 1;
    }
    iVar9 = iVar3 + 1;
    local_ac[0] = *(undefined4 *)(param_1 + 0x784 + (iVar3 + param_5 * 0x231) * 4);
    iVar3 = (iVar3 + 3) * 0x20 + param_1;
    piVar5 = (int *)(iVar3 + iVar6);
    if (6 < *(int *)(iVar3 + iVar6)) {
      local_144 = (char *)(param_1 + iVar9 * 0x1e + 0x400 + iVar6);
      pcVar11 = local_9b;
      do {
        if ((0xb < *piVar5) || (*piVar1 <= iVar9)) break;
        iVar6 = 0;
        pcVar14 = param_2;
        if (0 < param_3) {
          do {
            iVar3 = _stricmp(local_144,pcVar14);
            if (iVar3 == 0) break;
            iVar6 = iVar6 + 1;
            pcVar14 = pcVar14 + 0x54;
          } while (iVar6 < param_3);
        }
        if (iVar6 == param_3) {
          report_error();
                    /* WARNING: Subroutine does not return */
          exit(0);
        }
        uVar7 = 0xffffffff;
        pcVar14 = param_2 + iVar6 * 0x54 + 0x3b;
        do {
          pcVar12 = pcVar14;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar12 = pcVar14 + 1;
          cVar2 = *pcVar14;
          pcVar14 = pcVar12;
        } while (cVar2 != '\0');
        uVar7 = ~uVar7;
        pcVar12 = pcVar12 + -uVar7;
        pcVar14 = pcVar11;
        for (uVar8 = uVar7 >> 2; pcVar14 = pcVar14 + 4, uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
          pcVar12 = pcVar12 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar14 = *pcVar12;
          pcVar12 = pcVar12 + 1;
          pcVar14 = pcVar14 + 1;
        }
        local_144 = local_144 + 0x1e;
        *(undefined4 *)pcVar11 = *(undefined4 *)(param_1 + 0x784 + (iVar9 + param_5 * 0x231) * 4);
        local_150 = local_150 + 1;
        piVar5 = piVar5 + 8;
        iVar9 = iVar9 + 1;
        pcVar11 = pcVar11 + 0x11;
      } while (6 < *piVar5);
    }
  }
  read_vehicle_config_weapon_chunks(param_4,local_130,(int)local_ac,local_150,&local_13c);
  return;
}


