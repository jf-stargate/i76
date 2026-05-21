/*
 * Program: i76.exe
 * Function: load_shell_vehicle_definition
 * Entry: 004b58a0
 * Signature: int __cdecl load_shell_vehicle_definition(int param_1, byte * param_2, int param_3)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=medium-high] Loads a frontend shell
   vehicle definition/config record from a VCF path into a shell vehicle descriptor slot. */

int __cdecl load_shell_vehicle_definition(int param_1,byte *param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  char *pcVar5;
  int iVar6;
  uint *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  ushort *puVar11;
  int *piVar12;
  byte *pbVar13;
  uint *puVar14;
  ushort *puVar15;
  char *pcVar16;
  undefined4 *puVar17;
  ushort *puVar18;
  uint *puVar19;
  char *pcVar20;
  char *pcVar21;
  bool bVar22;
  char *pcVar23;
  int local_ac4;
  char *local_ac0;
  int local_ab8;
  int local_ab4;
  char *local_aac;
  undefined4 local_aa8 [20];
  undefined1 local_a58 [80];
  undefined1 local_a08 [80];
  char local_9b8 [13];
  char local_9ab [26];
  ushort local_991;
  ushort uStack_98f;
  ushort uStack_98d;
  ushort local_98b;
  ushort uStack_975;
  ushort local_973;
  undefined1 auStack_971 [16];
  undefined1 local_961 [16];
  undefined1 local_951 [69];
  ushort local_90c;
  ushort uStack_90a;
  ushort local_8d4;
  ushort uStack_8d2;
  ushort local_89c;
  ushort uStack_89a;
  ushort local_864;
  ushort uStack_862;
  ushort local_82c;
  ushort uStack_82a;
  ushort local_7f4;
  ushort uStack_7f2;
  char local_7e8 [16];
  byte local_7d8 [48];
  char local_7a8 [64];
  char local_768 [294];
  ushort local_642 [763];
  int local_4c;
  int local_38 [4];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar17 = local_aa8;
  for (iVar8 = 0x2aa; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar17 = 0;
    puVar17 = puVar17 + 1;
  }
  iVar8 = parse_vcfc_vehicle_config_resource(param_2,local_aa8);
  if (iVar8 == 0) {
    report_error();
    return 0;
  }
  iVar8 = param_3 * 0x8c4;
  pcVar1 = (char *)(param_1 + iVar8);
  pcVar5 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,local_a08);
  uVar9 = 0xffffffff;
  do {
    pcVar23 = pcVar5;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar23 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar23;
  } while (cVar2 != '\0');
  uVar9 = ~uVar9;
  pcVar5 = pcVar23 + -uVar9;
  pcVar23 = pcVar1;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar23 = pcVar23 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar23 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar23 = pcVar23 + 1;
  }
  pcVar5 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,local_a58);
  uVar9 = 0xffffffff;
  do {
    pcVar23 = pcVar5;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar23 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar23;
  } while (cVar2 != '\0');
  uVar9 = ~uVar9;
  pcVar5 = pcVar23 + -uVar9;
  pcVar23 = pcVar1 + 0x14;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar23 = pcVar23 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar23 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar23 = pcVar23 + 1;
  }
  uVar9 = 0xffffffff;
  pcVar5 = local_9b8;
  do {
    pcVar23 = pcVar5;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar23 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar23;
  } while (cVar2 != '\0');
  uVar9 = ~uVar9;
  pcVar5 = pcVar23 + -uVar9;
  pcVar23 = pcVar1 + 0x820;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar23 = pcVar23 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar23 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar23 = pcVar23 + 1;
  }
  uVar9 = 0xffffffff;
  pcVar5 = local_9ab;
  do {
    pcVar23 = pcVar5;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar23 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar23;
  } while (cVar2 != '\0');
  uVar9 = ~uVar9;
  pcVar5 = pcVar23 + -uVar9;
  pcVar23 = pcVar1 + 0x82d;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar23 = pcVar23 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar23 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar23 = pcVar23 + 1;
  }
  *(undefined4 *)(pcVar1 + 0x28) = s_doarmel_005009a0._0_4_;
  *(undefined4 *)(pcVar1 + 0x2c) = s_doarmel_005009a0._4_4_;
  pcVar1[0x38] = '\x01';
  pcVar1[0x39] = '\0';
  pcVar1[0x3a] = '\0';
  pcVar1[0x3b] = '\0';
  pcVar1[0x40] = '\x02';
  pcVar1[0x41] = '\0';
  pcVar1[0x42] = '\0';
  pcVar1[0x43] = '\0';
  *(undefined4 *)(pcVar1 + 0x44) = s_ENGINE_00500998._0_4_;
  *(undefined2 *)(pcVar1 + 0x48) = s_ENGINE_00500998._4_2_;
  pcVar1[0x4a] = s_ENGINE_00500998[6];
  *(uint *)(pcVar1 + 0x54) = (uint)local_991;
  *(uint *)(pcVar1 + 0x58) = (uint)uStack_98f;
  pcVar1[0x5c] = '\0';
  pcVar1[0x5d] = '\0';
  pcVar1[0x5e] = '\0';
  pcVar1[0x5f] = '\0';
  pcVar5 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,auStack_971);
  uVar9 = 0xffffffff;
  do {
    pcVar23 = pcVar5;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar23 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar23;
  } while (cVar2 != '\0');
  uVar9 = ~uVar9;
  pcVar5 = pcVar23 + -uVar9;
  pcVar23 = pcVar1 + 0x400;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar23 = pcVar23 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar23 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar23 = pcVar23 + 1;
  }
  pcVar1[0x60] = '\x03';
  pcVar1[0x61] = '\0';
  pcVar1[0x62] = '\0';
  pcVar1[99] = '\0';
  *(undefined4 *)(pcVar1 + 100) = s_SUSP_00500990._0_4_;
  pcVar1[0x68] = s_SUSP_00500990[4];
  *(uint *)(pcVar1 + 0x74) = (uint)uStack_98d;
  *(uint *)(pcVar1 + 0x78) = (uint)local_98b;
  pcVar1[0x7c] = '\0';
  pcVar1[0x7d] = '\0';
  pcVar1[0x7e] = '\0';
  pcVar1[0x7f] = '\0';
  pcVar5 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,local_951);
  uVar9 = 0xffffffff;
  do {
    pcVar23 = pcVar5;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar23 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar23;
  } while (cVar2 != '\0');
  uVar9 = ~uVar9;
  pcVar5 = pcVar23 + -uVar9;
  pcVar23 = pcVar1 + 0x41e;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar23 = pcVar23 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar23 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar23 = pcVar23 + 1;
  }
  pcVar1[0x80] = '\x04';
  pcVar1[0x81] = '\0';
  pcVar1[0x82] = '\0';
  pcVar1[0x83] = '\0';
  *(undefined4 *)(pcVar1 + 0x84) = s_BRAKE_00500988._0_4_;
  *(undefined2 *)(pcVar1 + 0x88) = s_BRAKE_00500988._4_2_;
  *(uint *)(pcVar1 + 0x94) = (uint)uStack_975;
  *(uint *)(pcVar1 + 0x98) = (uint)local_973;
  pcVar1[0x9c] = '\0';
  pcVar1[0x9d] = '\0';
  pcVar1[0x9e] = '\0';
  pcVar1[0x9f] = '\0';
  pcVar5 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,local_961);
  uVar9 = 0xffffffff;
  do {
    pcVar23 = pcVar5;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar23 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar23;
  } while (cVar2 != '\0');
  uVar9 = ~uVar9;
  local_ac0 = pcVar1 + 0x45a;
  pcVar5 = pcVar23 + -uVar9;
  pcVar23 = pcVar1 + 0x43c;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar23 = pcVar23 + 4;
  }
  local_ac4 = 3;
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar23 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar23 = pcVar23 + 1;
  }
  puVar7 = (uint *)(pcVar1 + 0xb4);
  local_ab4 = 0;
  do {
    pcVar5 = &DAT_00504c28;
    pbVar13 = local_7d8 + (local_ab4 / 2) * 0x40;
    do {
      bVar3 = *pbVar13;
      bVar22 = bVar3 < (byte)*pcVar5;
      if (bVar3 != *pcVar5) {
LAB_004b5bdc:
        iVar6 = (1 - (uint)bVar22) - (uint)(bVar22 != 0);
        goto LAB_004b5be1;
      }
      if (bVar3 == 0) break;
      bVar3 = pbVar13[1];
      bVar22 = bVar3 < (byte)pcVar5[1];
      if (bVar3 != pcVar5[1]) goto LAB_004b5bdc;
      pbVar13 = pbVar13 + 2;
      pcVar5 = pcVar5 + 2;
    } while (bVar3 != 0);
    iVar6 = 0;
LAB_004b5be1:
    if (iVar6 != 0) {
      if (local_ab4 == 0) {
        strncpy(pcVar1 + 0x83a,local_7e8,8);
        uVar9 = 0xffffffff;
        pcVar1[0x842] = '\0';
        pcVar5 = &DAT_004ffec8;
        do {
          pcVar23 = pcVar5;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar23 = pcVar5 + 1;
          cVar2 = *pcVar5;
          pcVar5 = pcVar23;
        } while (cVar2 != '\0');
        uVar9 = ~uVar9;
        iVar6 = -1;
        pcVar5 = pcVar1 + 0x83a;
        do {
          pcVar20 = pcVar5;
          if (iVar6 == 0) break;
          iVar6 = iVar6 + -1;
          pcVar20 = pcVar5 + 1;
          cVar2 = *pcVar5;
          pcVar5 = pcVar20;
        } while (cVar2 != '\0');
        pcVar5 = pcVar23 + -uVar9;
        pcVar23 = pcVar20 + -1;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar23 = pcVar23 + 4;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pcVar23 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar23 = pcVar23 + 1;
        }
        puVar7[-4] = s_WHL_FR_00500980._0_4_;
        *(undefined2 *)(puVar7 + -3) = s_WHL_FR_00500980._4_2_;
        *(char *)((int)puVar7 + -10) = s_WHL_FR_00500980[6];
        *puVar7 = (uint)local_90c;
        puVar7[1] = (uint)uStack_90a;
      }
      else if (local_ab4 == 1) {
        puVar7[-4] = s_WHL_FL_00500978._0_4_;
        *(undefined2 *)(puVar7 + -3) = s_WHL_FL_00500978._4_2_;
        *(char *)((int)puVar7 + -10) = s_WHL_FL_00500978[6];
        *puVar7 = (uint)local_8d4;
        uVar9 = (uint)uStack_8d2;
LAB_004b5e6e:
        puVar7[1] = uVar9;
      }
      else if (local_ab4 == 2) {
        strncpy(pcVar1 + 0x847,local_7a8,8);
        uVar9 = 0xffffffff;
        pcVar1[0x84f] = '\0';
        pcVar5 = &DAT_004ffec8;
        do {
          pcVar23 = pcVar5;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar23 = pcVar5 + 1;
          cVar2 = *pcVar5;
          pcVar5 = pcVar23;
        } while (cVar2 != '\0');
        uVar9 = ~uVar9;
        iVar6 = -1;
        pcVar5 = pcVar1 + 0x847;
        do {
          pcVar20 = pcVar5;
          if (iVar6 == 0) break;
          iVar6 = iVar6 + -1;
          pcVar20 = pcVar5 + 1;
          cVar2 = *pcVar5;
          pcVar5 = pcVar20;
        } while (cVar2 != '\0');
        pcVar5 = pcVar23 + -uVar9;
        pcVar23 = pcVar20 + -1;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar23 = pcVar23 + 4;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pcVar23 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar23 = pcVar23 + 1;
        }
        puVar7[-4] = s_WHL_MR_00500970._0_4_;
        *(undefined2 *)(puVar7 + -3) = s_WHL_MR_00500970._4_2_;
        *(char *)((int)puVar7 + -10) = s_WHL_MR_00500970[6];
        *puVar7 = (uint)local_89c;
        puVar7[1] = (uint)uStack_89a;
      }
      else {
        if (local_ab4 == 3) {
          puVar7[-4] = s_WHL_ML_00500968._0_4_;
          *(undefined2 *)(puVar7 + -3) = s_WHL_ML_00500968._4_2_;
          *(char *)((int)puVar7 + -10) = s_WHL_ML_00500968[6];
          *puVar7 = (uint)local_864;
          uVar9 = (uint)uStack_862;
          goto LAB_004b5e6e;
        }
        if (local_ab4 == 4) {
          strncpy(pcVar1 + 0x854,local_768,8);
          uVar9 = 0xffffffff;
          pcVar1[0x85c] = '\0';
          pcVar5 = &DAT_004ffec8;
          do {
            pcVar23 = pcVar5;
            if (uVar9 == 0) break;
            uVar9 = uVar9 - 1;
            pcVar23 = pcVar5 + 1;
            cVar2 = *pcVar5;
            pcVar5 = pcVar23;
          } while (cVar2 != '\0');
          uVar9 = ~uVar9;
          iVar6 = -1;
          pcVar5 = pcVar1 + 0x854;
          do {
            pcVar20 = pcVar5;
            if (iVar6 == 0) break;
            iVar6 = iVar6 + -1;
            pcVar20 = pcVar5 + 1;
            cVar2 = *pcVar5;
            pcVar5 = pcVar20;
          } while (cVar2 != '\0');
          pcVar5 = pcVar23 + -uVar9;
          pcVar23 = pcVar20 + -1;
          for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar23 = pcVar23 + 4;
          }
          for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *pcVar23 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            pcVar23 = pcVar23 + 1;
          }
          puVar7[-4] = s_WHL_BR_00500960._0_4_;
          *(undefined2 *)(puVar7 + -3) = s_WHL_BR_00500960._4_2_;
          *(char *)((int)puVar7 + -10) = s_WHL_BR_00500960[6];
          *puVar7 = (uint)local_82c;
          puVar7[1] = (uint)uStack_82a;
        }
        else if (local_ab4 == 5) {
          puVar7[-4] = s_WHL_BL_00500958._0_4_;
          *(undefined2 *)(puVar7 + -3) = s_WHL_BL_00500958._4_2_;
          *(char *)((int)puVar7 + -10) = s_WHL_BL_00500958[6];
          *puVar7 = (uint)local_7f4;
          uVar9 = (uint)uStack_7f2;
          goto LAB_004b5e6e;
        }
      }
      puVar7[-5] = 5;
      pcVar5 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                     local_7d8 + (local_ab4 / 2) * 0x40);
      uVar9 = 0xffffffff;
      do {
        pcVar23 = pcVar5;
        if (uVar9 == 0) break;
        uVar9 = uVar9 - 1;
        pcVar23 = pcVar5 + 1;
        cVar2 = *pcVar5;
        pcVar5 = pcVar23;
      } while (cVar2 != '\0');
      uVar9 = ~uVar9;
      pcVar5 = pcVar23 + -uVar9;
      pcVar23 = local_ac0;
      for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *(undefined4 *)pcVar23 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar23 = pcVar23 + 4;
      }
      local_ac4 = local_ac4 + 1;
      for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
        *pcVar23 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar23 = pcVar23 + 1;
      }
      puVar7[2] = 0;
      puVar7 = puVar7 + 8;
      local_ac0 = local_ac0 + 0x1e;
    }
    local_ab4 = local_ab4 + 1;
    if (5 < local_ab4) {
      local_ab4 = 0;
      if (0 < local_4c) {
        puVar11 = local_642;
        local_ac0 = (char *)(param_1 + 0x784 + local_ac4 * 4 + param_3 * 0x8c4);
        local_aac = (char *)(param_1 + local_ac4 * 0x1e + 0x400 + iVar8);
        pcVar5 = pcVar1 + 0x86c;
        puVar7 = (uint *)(local_ac4 * 0x20 + param_1 + 0x54 + iVar8);
        do {
          iVar6 = *(int *)(puVar11 + -0x1b);
          if (iVar6 == 4) {
            puVar7[-5] = 8;
          }
          else if (iVar6 == 6) {
            if (*(int *)(puVar11 + -0x1d) == 3) {
              puVar7[-5] = 10;
            }
            else {
              if (*(int *)(puVar11 + -0x1d) != 4) {
                report_error();
                    /* WARNING: Subroutine does not return */
                exit(0);
              }
              puVar7[-5] = 9;
            }
          }
          else if (iVar6 == 3) {
            puVar7[-5] = 0xb;
          }
          else {
            puVar7[-5] = 7;
          }
          *puVar7 = (uint)puVar11[-1];
          puVar7[1] = (uint)*puVar11;
          *(undefined4 *)(pcVar5 + -4) = *(undefined4 *)(puVar11 + -0x1f);
          *(undefined4 *)pcVar5 = *(undefined4 *)(puVar11 + -0x1d);
          *(undefined4 *)(pcVar5 + 4) = *(undefined4 *)(puVar11 + -0x1b);
          uVar9 = 0xffffffff;
          puVar15 = puVar11 + -0x77;
          do {
            puVar18 = puVar15;
            if (uVar9 == 0) break;
            uVar9 = uVar9 - 1;
            puVar18 = (ushort *)((int)puVar15 + 1);
            uVar4 = *puVar15;
            puVar15 = puVar18;
          } while ((char)uVar4 != '\0');
          uVar9 = ~uVar9;
          puVar14 = (uint *)((int)puVar18 - uVar9);
          puVar19 = puVar7 + -4;
          for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *puVar19 = *puVar14;
            puVar14 = puVar14 + 1;
            puVar19 = puVar19 + 1;
          }
          for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *(char *)puVar19 = (char)*puVar14;
            puVar14 = (uint *)((int)puVar14 + 1);
            puVar19 = (uint *)((int)puVar19 + 1);
          }
          pcVar20 = &DAT_00504c28;
          *(undefined4 *)local_ac0 = *(undefined4 *)(puVar11 + -0x1f);
          pcVar23 = (char *)(puVar11 + -0x4f);
          puVar15 = (ushort *)pcVar23;
          do {
            bVar3 = (byte)*puVar15;
            bVar22 = bVar3 < (byte)*pcVar20;
            if (bVar3 != *pcVar20) {
LAB_004b6066:
              iVar6 = (1 - (uint)bVar22) - (uint)(bVar22 != 0);
              goto LAB_004b606b;
            }
            if (bVar3 == 0) break;
            bVar3 = *(byte *)((int)puVar15 + 1);
            bVar22 = bVar3 < (byte)pcVar20[1];
            if (bVar3 != pcVar20[1]) goto LAB_004b6066;
            puVar15 = puVar15 + 1;
            pcVar20 = pcVar20 + 2;
          } while (bVar3 != 0);
          iVar6 = 0;
LAB_004b606b:
          if (iVar6 == 0) {
            pcVar23 = s_EMPTY_0050090c;
          }
          pcVar23 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,pcVar23);
          uVar9 = 0xffffffff;
          do {
            pcVar20 = pcVar23;
            if (uVar9 == 0) break;
            uVar9 = uVar9 - 1;
            pcVar20 = pcVar23 + 1;
            cVar2 = *pcVar23;
            pcVar23 = pcVar20;
          } while (cVar2 != '\0');
          uVar9 = ~uVar9;
          pcVar23 = pcVar20 + -uVar9;
          pcVar20 = local_aac;
          for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar20 = *(undefined4 *)pcVar23;
            pcVar23 = pcVar23 + 4;
            pcVar20 = pcVar20 + 4;
          }
          local_aac = local_aac + 0x1e;
          for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *pcVar20 = *pcVar23;
            pcVar23 = pcVar23 + 1;
            pcVar20 = pcVar20 + 1;
          }
          puVar7[2] = 0;
          local_ac4 = local_ac4 + 1;
          local_ac0 = (char *)((int)local_ac0 + 4);
          local_ab4 = local_ab4 + 1;
          pcVar5 = pcVar5 + 0xc;
          puVar11 = puVar11 + 0x7e;
          puVar7 = puVar7 + 8;
        } while (local_ab4 < local_4c);
      }
      piVar12 = local_38;
      local_ab8 = 3;
      *(int *)(param_1 + 0x864) = local_4c;
      pcVar23 = (char *)(param_1 + local_ac4 * 0x1e + 0x400 + iVar8);
      pcVar5 = (char *)(local_ac4 * 0x20 + param_1 + 0x44 + iVar8);
      pcVar20 = pcVar5;
      local_ac0 = pcVar23;
      do {
        if (*piVar12 == 0) {
          pcVar20[-0xffffffff00000004] = '\0';
          pcVar20[-0xffffffff00000003] = '\0';
          pcVar20[-0xffffffff00000002] = '\0';
          pcVar20[-0xffffffff00000001] = '\0';
          *pcVar20 = DAT_00504c28;
          *pcVar23 = DAT_00504c28;
        }
        else {
          pcVar5[-0xffffffff00000004] = '\f';
          pcVar5[-0xffffffff00000003] = '\0';
          pcVar5[-0xffffffff00000002] = '\0';
          pcVar5[-0xffffffff00000001] = '\0';
          uVar9 = 0xffffffff;
          pcVar16 = *(char **)(s_Can_t_open__s_for_writing_005007bc + *piVar12 * 4 + 0x18);
          do {
            pcVar21 = pcVar16;
            if (uVar9 == 0) break;
            uVar9 = uVar9 - 1;
            pcVar21 = pcVar16 + 1;
            cVar2 = *pcVar16;
            pcVar16 = pcVar21;
          } while (cVar2 != '\0');
          uVar9 = ~uVar9;
          pcVar16 = pcVar21 + -uVar9;
          pcVar21 = pcVar5;
          for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar21 = *(undefined4 *)pcVar16;
            pcVar16 = pcVar16 + 4;
            pcVar21 = pcVar21 + 4;
          }
          for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *pcVar21 = *pcVar16;
            pcVar16 = pcVar16 + 1;
            pcVar21 = pcVar21 + 1;
          }
          pcVar5[0x18] = '\0';
          pcVar5[0x19] = '\0';
          pcVar5[0x1a] = '\0';
          pcVar5[0x1b] = '\0';
          uVar9 = 0xffffffff;
          pcVar16 = *(char **)(s_Can_t_open__s_for_writing_005007bc + *piVar12 * 4 + 0x18);
          do {
            pcVar21 = pcVar16;
            if (uVar9 == 0) break;
            uVar9 = uVar9 - 1;
            pcVar21 = pcVar16 + 1;
            cVar2 = *pcVar16;
            pcVar16 = pcVar21;
          } while (cVar2 != '\0');
          uVar9 = ~uVar9;
          pcVar16 = pcVar21 + -uVar9;
          pcVar21 = local_ac0;
          for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar21 = *(undefined4 *)pcVar16;
            pcVar16 = pcVar16 + 4;
            pcVar21 = pcVar21 + 4;
          }
          for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *pcVar21 = *pcVar16;
            pcVar16 = pcVar16 + 1;
            pcVar21 = pcVar21 + 1;
          }
          local_ac4 = local_ac4 + 1;
          local_ac0 = local_ac0 + 0x1e;
          pcVar5 = pcVar5 + 0x20;
        }
        piVar12 = piVar12 + 1;
        pcVar20 = pcVar20 + 0x20;
        pcVar23 = pcVar23 + 0x1e;
        local_ab8 = local_ab8 + -1;
        if (local_ab8 == 0) {
          *(int *)(pcVar1 + 0x3c) = local_ac4;
          *(int *)(pcVar1 + 0x7fc) = local_38[3];
          *(undefined4 *)(pcVar1 + 0x800) = local_24;
          *(undefined4 *)(pcVar1 + 0x804) = local_28;
          *(undefined4 *)(pcVar1 + 0x808) = local_20;
          *(undefined4 *)(pcVar1 + 0x80c) = local_1c;
          *(undefined4 *)(pcVar1 + 0x810) = local_14;
          *(undefined4 *)(pcVar1 + 0x814) = local_18;
          *(undefined4 *)(pcVar1 + 0x818) = local_10;
          *(undefined4 *)(pcVar1 + 0x81c) = local_c;
          *(undefined4 *)(pcVar1 + 0x8bc) = local_8;
          *(undefined4 *)(pcVar1 + 0x8c0) = local_4;
          return local_4c;
        }
      } while( true );
    }
  } while( true );
}


