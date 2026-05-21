/*
 * Program: i76shell.dll
 * Function: blit_mw2_image_subresource_rle_clipped
 * Entry: 1003a8f4
 * Signature: undefined4 __cdecl blit_mw2_image_subresource_rle_clipped(int * param_1, int param_2, int param_3, int param_4, int param_5)
 */


undefined4 __cdecl
blit_mw2_image_subresource_rle_clipped(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  byte bVar14;
  byte bVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  uint *puVar20;
  byte *pbVar21;
  uint *puVar22;
  uint *puVar23;
  bool bVar24;
  bool bVar25;
  byte *local_30;
  byte *local_2c;
  uint *local_28;
  int local_24;
  
  piVar1 = (int *)*param_1;
  iVar9 = piVar1[1];
  iVar5 = iVar9 + 1;
  if ((iVar5 == 0 || iVar9 < -1) || (iVar10 = piVar1[2], iVar10 < 0)) {
    return 0xffffffff;
  }
  iVar2 = param_1[1];
  iVar6 = iVar2;
  if (iVar2 < 1) {
    iVar6 = 0;
  }
  iVar3 = param_1[2];
  iVar7 = iVar3;
  if (iVar3 < 1) {
    iVar7 = 0;
  }
  iVar8 = param_1[3];
  if (iVar9 <= param_1[3]) {
    iVar8 = iVar9;
  }
  iVar9 = param_1[4];
  if (iVar10 <= param_1[4]) {
    iVar9 = iVar10;
  }
  if ((iVar8 < iVar6) || (iVar9 < iVar7)) {
    return 0xfffffffe;
  }
  iVar2 = param_4 + iVar2;
  iVar3 = param_5 + iVar3;
  iVar19 = *(int *)(param_3 * 8 + 8 + param_2) + param_2;
  iVar10 = *(int *)(iVar19 + 8) + iVar2;
  local_24 = *(int *)(iVar19 + 0xc) + iVar3;
  iVar11 = *(int *)(iVar19 + 0x10) + iVar2;
  iVar12 = *(int *)(iVar19 + 0x14) + iVar3;
  puVar20 = (uint *)(iVar19 + 0x18);
  if ((iVar11 < iVar10) || (iVar12 < local_24)) {
    return 0xfffffffc;
  }
  bVar14 = (((iVar10 - iVar6 < 0) * '\x02' + (iVar8 - iVar10 < 0)) * '\x02' + (local_24 - iVar7 < 0)
           ) * '\x02' + (iVar9 - local_24 < 0);
  bVar15 = (((iVar11 - iVar6 < 0) * '\x02' + (iVar8 - iVar11 < 0)) * '\x02' + (iVar12 - iVar7 < 0))
           * '\x02' + (iVar9 - iVar12 < 0);
  if ((bVar15 & bVar14) != 0) {
    return 0xfffffffd;
  }
  if (bVar14 == 0 && bVar15 == 0) {
    blit_mw2_image_subresource_rle_unclipped(param_1,iVar19,iVar2 - param_1[1],iVar3 - param_1[2]);
    return 0;
  }
  local_28 = (uint *)(local_24 * iVar5 + *piVar1 + iVar10);
LAB_1003aaa0:
  if (local_24 < iVar7) {
    do {
      uVar17 = *puVar20;
      puVar20 = (uint *)((int)puVar20 + 1);
      bVar24 = (bool)((byte)uVar17 & 1);
      bVar4 = (byte)uVar17 >> 1;
      if (bVar24 || bVar4 == 0) {
        if (bVar4 != 0) {
          puVar20 = (uint *)((int)puVar20 + (bVar4 - 1));
        }
        else if (!bVar24) goto code_r0x1003aa9c;
      }
      puVar20 = (uint *)((int)puVar20 + 1);
    } while( true );
  }
  local_2c = (byte *)((int)local_28 + (iVar6 - iVar10));
  local_30 = (byte *)((int)local_28 + (iVar8 - iVar10));
LAB_1003ad3e:
  if (iVar12 < local_24) {
    return 0;
  }
  if (iVar9 < local_24) {
    return 0;
  }
  puVar23 = local_28;
  if ((bVar14 & 8) == 0) {
    if ((bVar15 & 4) == 0) {
      uVar17 = *puVar20;
      puVar20 = (uint *)((int)puVar20 + 1);
      bVar24 = (bool)((byte)uVar17 & 1);
      bVar4 = (byte)uVar17 >> 1;
      uVar17 = (uint)bVar4;
      if (!bVar24 && bVar4 != 0) goto LAB_1003ab16;
      if (bVar4 != 0) goto LAB_1003ab55;
joined_r0x1003aaf8:
      if (bVar24) {
        do {
          while( true ) {
            pbVar21 = (byte *)((int)puVar20 + 1);
            puVar23 = (uint *)((int)puVar23 + (uint)(byte)*puVar20);
            puVar20 = (uint *)((int)puVar20 + 2);
            bVar24 = (bool)(*pbVar21 & 1);
            bVar4 = *pbVar21 >> 1;
            uVar17 = (uint)bVar4;
            if (!bVar24 && bVar4 != 0) goto LAB_1003ab16;
            if (bVar4 == 0) break;
LAB_1003ab55:
            do {
              while( true ) {
                puVar22 = puVar20;
                if (4 < (int)uVar17) {
                  uVar13 = -(int)puVar23 & 3;
                  uVar16 = uVar17 - uVar13;
                  for (; uVar13 != 0; uVar13 = uVar13 - 1) {
                    *(byte *)puVar23 = (byte)*puVar20;
                    puVar20 = (uint *)((int)puVar20 + 1);
                    puVar23 = (uint *)((int)puVar23 + 1);
                  }
                  uVar17 = uVar16 & 3;
                  puVar22 = puVar20;
                  for (uVar16 = uVar16 >> 2; uVar16 != 0; uVar16 = uVar16 - 1) {
                    *puVar23 = *puVar22;
                    puVar22 = puVar22 + 1;
                    puVar23 = puVar23 + 1;
                  }
                }
                for (; uVar17 != 0; uVar17 = uVar17 - 1) {
                  *(byte *)puVar23 = (byte)*puVar22;
                  puVar22 = (uint *)((int)puVar22 + 1);
                  puVar23 = (uint *)((int)puVar23 + 1);
                }
                puVar20 = (uint *)((int)puVar22 + 1);
                bVar24 = (bool)((byte)*puVar22 & 1);
                bVar4 = (byte)*puVar22 >> 1;
                uVar17 = (uint)bVar4;
                if (!bVar24 && bVar4 != 0) break;
                if (bVar4 == 0) goto joined_r0x1003aaf8;
              }
LAB_1003ab16:
              do {
                bVar4 = (byte)*puVar20;
                uVar13 = (uint)bVar4;
                pbVar21 = (byte *)((int)puVar20 + 1);
                if (4 < (int)uVar17) {
                  uVar13 = -(int)puVar23 & 3;
                  uVar16 = uVar17 - uVar13;
                  for (; uVar13 != 0; uVar13 = uVar13 - 1) {
                    *(byte *)puVar23 = bVar4;
                    puVar23 = (uint *)((int)puVar23 + 1);
                  }
                  uVar13 = CONCAT31(CONCAT21(CONCAT11(bVar4,bVar4),bVar4),bVar4);
                  uVar17 = uVar16 & 3;
                  for (uVar16 = uVar16 >> 2; uVar16 != 0; uVar16 = uVar16 - 1) {
                    *puVar23 = uVar13;
                    puVar23 = puVar23 + 1;
                  }
                }
                for (; uVar17 != 0; uVar17 = uVar17 - 1) {
                  *(byte *)puVar23 = (byte)uVar13;
                  puVar23 = (uint *)((int)puVar23 + 1);
                }
                puVar20 = (uint *)((int)puVar20 + 2);
                bVar24 = (bool)(*pbVar21 & 1);
                bVar4 = *pbVar21 >> 1;
                uVar17 = (uint)bVar4;
              } while (!bVar24 && bVar4 != 0);
              if (!bVar24) goto LAB_1003ad2f;
            } while (bVar4 != 0);
          }
        } while (bVar24);
      }
    }
    else {
      uVar17 = *puVar20;
      puVar20 = (uint *)((int)puVar20 + 1);
      bVar24 = (bool)((byte)uVar17 & 1);
      bVar4 = (byte)uVar17 >> 1;
      if (!bVar24 && bVar4 != 0) goto LAB_1003ac41;
      if (bVar4 != 0) goto LAB_1003ac9a;
joined_r0x1003ac22:
      if (bVar24) {
        do {
          while( true ) {
            pbVar21 = (byte *)((int)puVar20 + 1);
            puVar23 = (uint *)((int)puVar23 + (uint)(byte)*puVar20);
            puVar20 = (uint *)((int)puVar20 + 2);
            bVar24 = (bool)(*pbVar21 & 1);
            bVar4 = *pbVar21 >> 1;
            if (!bVar24 && bVar4 != 0) goto LAB_1003ac41;
            if (bVar4 == 0) break;
LAB_1003ac9a:
            do {
              while( true ) {
                uVar17 = (uint)bVar4;
LAB_1003ac9d:
                if ((int)local_30 < (int)puVar23) goto LAB_1003ad20;
                pbVar21 = (byte *)((int)puVar23 + ((uVar17 - 1) - (int)local_30));
                uVar13 = ~((int)pbVar21 >> 0x1f) & (uint)pbVar21;
                uVar17 = uVar17 - uVar13;
                if (4 < (int)uVar17) {
                  uVar16 = -(int)puVar23 & 3;
                  uVar18 = uVar17 - uVar16;
                  for (; uVar16 != 0; uVar16 = uVar16 - 1) {
                    *(byte *)puVar23 = (byte)*puVar20;
                    puVar20 = (uint *)((int)puVar20 + 1);
                    puVar23 = (uint *)((int)puVar23 + 1);
                  }
                  uVar17 = uVar18 & 3;
                  for (uVar18 = uVar18 >> 2; uVar18 != 0; uVar18 = uVar18 - 1) {
                    *puVar23 = *puVar20;
                    puVar20 = puVar20 + 1;
                    puVar23 = puVar23 + 1;
                  }
                }
                for (; uVar17 != 0; uVar17 = uVar17 - 1) {
                  *(byte *)puVar23 = (byte)*puVar20;
                  puVar20 = (uint *)((int)puVar20 + 1);
                  puVar23 = (uint *)((int)puVar23 + 1);
                }
                puVar23 = (uint *)((int)puVar23 + uVar13);
                bVar4 = *(byte *)((int)puVar20 + uVar13);
                puVar20 = (uint *)((byte *)((int)puVar20 + uVar13) + 1);
                bVar24 = (bool)(bVar4 & 1);
                bVar4 = bVar4 >> 1;
                if (!bVar24 && bVar4 != 0) break;
                if (bVar4 == 0) goto joined_r0x1003ac22;
              }
LAB_1003ac41:
              do {
                uVar17 = (uint)bVar4;
LAB_1003ac44:
                if ((int)local_30 < (int)puVar23) goto LAB_1003ad0f;
                pbVar21 = (byte *)((int)puVar23 + ((uVar17 - 1) - (int)local_30));
                uVar16 = ~((int)pbVar21 >> 0x1f) & (uint)pbVar21;
                uVar17 = uVar17 - uVar16;
                bVar4 = (byte)*puVar20;
                uVar13 = (uint)bVar4;
                pbVar21 = (byte *)((int)puVar20 + 1);
                if (4 < (int)uVar17) {
                  uVar13 = -(int)puVar23 & 3;
                  uVar18 = uVar17 - uVar13;
                  for (; uVar13 != 0; uVar13 = uVar13 - 1) {
                    *(byte *)puVar23 = bVar4;
                    puVar23 = (uint *)((int)puVar23 + 1);
                  }
                  uVar13 = CONCAT31(CONCAT21(CONCAT11(bVar4,bVar4),bVar4),bVar4);
                  uVar17 = uVar18 & 3;
                  for (uVar18 = uVar18 >> 2; uVar18 != 0; uVar18 = uVar18 - 1) {
                    *puVar23 = uVar13;
                    puVar23 = puVar23 + 1;
                  }
                }
                for (; uVar17 != 0; uVar17 = uVar17 - 1) {
                  *(byte *)puVar23 = (byte)uVar13;
                  puVar23 = (uint *)((int)puVar23 + 1);
                }
                puVar23 = (uint *)((int)puVar23 + uVar16);
                puVar20 = (uint *)((int)puVar20 + 2);
                bVar24 = (bool)(*pbVar21 & 1);
                bVar4 = *pbVar21 >> 1;
              } while (!bVar24 && bVar4 != 0);
              if (!bVar24) goto LAB_1003ad2f;
            } while (bVar4 != 0);
          }
        } while (bVar24);
      }
    }
  }
  else {
    uVar17 = *puVar20;
    puVar20 = (uint *)((int)puVar20 + 1);
    bVar24 = (bool)((byte)uVar17 & 1);
    bVar4 = (byte)uVar17 >> 1;
    if (!bVar24 && bVar4 != 0) goto LAB_1003abab;
    if (bVar4 != 0) goto LAB_1003abdc;
joined_r0x1003ab94:
    if (bVar24) {
      do {
        while( true ) {
          pbVar21 = (byte *)((int)puVar20 + 1);
          puVar23 = (uint *)((int)puVar23 + (uint)(byte)*puVar20);
          puVar20 = (uint *)((int)puVar20 + 2);
          bVar24 = (bool)(*pbVar21 & 1);
          bVar4 = *pbVar21 >> 1;
          if (!bVar24 && bVar4 != 0) goto LAB_1003abab;
          if (bVar4 == 0) break;
LAB_1003abdc:
          do {
            while( true ) {
              uVar17 = (uint)bVar4;
              iVar10 = (int)local_2c - (int)puVar23;
              if (iVar10 < (int)uVar17) {
                if (-1 < iVar10) {
                  puVar23 = (uint *)((int)puVar23 + iVar10);
                  uVar17 = uVar17 - iVar10;
                  puVar20 = (uint *)((int)puVar20 + iVar10);
                }
                if ((bVar15 & 4) == 0) goto LAB_1003ab55;
                goto LAB_1003ac9d;
              }
              puVar23 = (uint *)((int)puVar23 + uVar17);
              bVar4 = *(byte *)((int)puVar20 + uVar17);
              puVar20 = (uint *)((byte *)((int)puVar20 + uVar17) + 1);
              bVar24 = (bool)(bVar4 & 1);
              bVar4 = bVar4 >> 1;
              if (!bVar24 && bVar4 != 0) break;
              if (bVar4 == 0) goto joined_r0x1003ab94;
            }
LAB_1003abab:
            do {
              uVar17 = (uint)bVar4;
              iVar10 = (int)local_2c - (int)puVar23;
              if (iVar10 < (int)uVar17) {
                if (-1 < iVar10) {
                  puVar23 = (uint *)((int)puVar23 + iVar10);
                  uVar17 = uVar17 - iVar10;
                }
                if ((bVar15 & 4) == 0) goto LAB_1003ab16;
                goto LAB_1003ac44;
              }
              puVar23 = (uint *)((int)puVar23 + uVar17);
              pbVar21 = (byte *)((int)puVar20 + 1);
              puVar20 = (uint *)((int)puVar20 + 2);
              bVar24 = (bool)(*pbVar21 & 1);
              bVar4 = *pbVar21 >> 1;
            } while (!bVar24 && bVar4 != 0);
            if (!bVar24) goto LAB_1003ad2f;
          } while (bVar4 != 0);
        }
      } while (bVar24);
    }
  }
  goto LAB_1003ad2f;
code_r0x1003aa9c:
  local_28 = (uint *)((int)local_28 + iVar5);
  local_24 = local_24 + 1;
  goto LAB_1003aaa0;
LAB_1003ad0f:
  do {
    pbVar21 = (byte *)((int)puVar20 + 1);
    puVar20 = (uint *)((int)puVar20 + 2);
    bVar24 = (bool)(*pbVar21 & 1);
    bVar4 = *pbVar21 >> 1;
  } while (!bVar24 && bVar4 != 0);
  if (bVar24) {
    if (bVar4 == 0) goto LAB_1003acf7;
    while( true ) {
      uVar17 = (uint)bVar4;
LAB_1003ad20:
      bVar4 = *(byte *)((int)puVar20 + uVar17);
      puVar20 = (uint *)((byte *)((int)puVar20 + uVar17) + 1);
      bVar24 = (bool)(bVar4 & 1);
      bVar4 = bVar4 >> 1;
      bVar25 = bVar4 != 0;
      if (!bVar24 && bVar25) break;
      while (!bVar25) {
        if (!bVar24) goto LAB_1003ad2f;
LAB_1003acf7:
        pbVar21 = (byte *)((int)puVar20 + 1);
        puVar20 = (uint *)((int)puVar20 + 2);
        bVar24 = (bool)(*pbVar21 & 1);
        bVar4 = *pbVar21 >> 1;
        bVar25 = bVar4 != 0;
        if (!bVar24 && bVar25) goto LAB_1003ad0f;
      }
    }
    goto LAB_1003ad0f;
  }
LAB_1003ad2f:
  local_28 = (uint *)((int)local_28 + iVar5);
  local_2c = local_2c + iVar5;
  local_30 = local_30 + iVar5;
  local_24 = local_24 + 1;
  goto LAB_1003ad3e;
}


