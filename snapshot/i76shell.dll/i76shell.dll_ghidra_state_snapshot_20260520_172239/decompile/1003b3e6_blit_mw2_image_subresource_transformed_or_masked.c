/*
 * Program: i76shell.dll
 * Function: blit_mw2_image_subresource_transformed_or_masked
 * Entry: 1003b3e6
 * Signature: int * __cdecl blit_mw2_image_subresource_transformed_or_masked(int * param_1, int param_2, int param_3, int param_4, int param_5, int param_6, uint param_7, int param_8, int param_9, uint param_10)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

int * __cdecl
blit_mw2_image_subresource_transformed_or_masked
          (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,uint param_7,
          int param_8,int param_9,uint param_10)

{
  char cVar1;
  int iVar2;
  ulonglong uVar3;
  longlong lVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  short sVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  int *piVar21;
  uint uVar22;
  int *piVar23;
  char *pcVar24;
  int *piVar25;
  char *pcVar26;
  uint local_d4;
  uint local_d0;
  uint local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_9c;
  int *local_98;
  int *local_94;
  int *local_90;
  int local_8c;
  int local_88;
  int local_84;
  int *local_80;
  int *local_7c;
  int *local_70;
  int local_60;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  if (((param_8 == 0x10000) && (param_9 == 0x10000)) && (param_7 == 0)) {
    if ((param_10 & 1) == 0) {
      piVar25 = (int *)blit_mw2_image_subresource_rle_clipped
                                 (param_1,param_2,param_3,param_4,param_5);
      return piVar25;
    }
    local_94 = (int *)blit_mw2_image_subresource_rle_transparent_remap
                                (param_1,param_2,param_3,param_4,param_5);
  }
  else {
    uVar5 = get_mw2_image_subresource_dimensions(param_2,param_3);
    iVar6 = (uVar5 >> 0x10) - 1;
    iVar14 = (uVar5 & 0xffff) - 1;
    local_2c = &local_18;
    local_18 = param_6;
    local_28 = 0;
    DAT_1004ef48 = 0;
    DAT_1004ef84 = 0;
    local_24 = 0;
    DAT_1004ef4c = 0;
    DAT_1004ef60 = 0;
    DAT_1004ef5c = iVar6;
    DAT_1004ef70 = iVar6;
    DAT_1004ef74 = iVar14;
    DAT_1004ef88 = iVar14;
    local_20 = iVar6;
    local_1c = iVar14;
    local_14 = iVar6;
    local_10 = iVar14;
    iVar7 = get_mw2_image_subresource_origin(param_2,param_3);
    local_40 = -(int)(short)iVar7;
    local_44 = -(iVar7 >> 0x10);
    if ((param_10 & 2) == 0) {
      FUN_1003c785((int *)&local_2c,0xff);
      if ((param_10 & 1) == 0) {
        blit_mw2_image_subresource_rle_clipped((int *)&local_2c,param_2,param_3,local_44,local_40);
      }
      else {
        blit_mw2_image_subresource_rle_transparent_remap
                  ((int *)&local_2c,param_2,param_3,local_44,local_40);
      }
    }
    piVar25 = (int *)*param_1;
    iVar7 = piVar25[1];
    iVar8 = iVar7 + 1;
    if ((iVar8 == 0 || iVar7 < -1) || (iVar12 = piVar25[2], iVar12 < 0)) {
      return (int *)0xffffffff;
    }
    iVar2 = param_1[1];
    iVar9 = iVar2;
    if (iVar2 < 1) {
      iVar9 = 0;
    }
    piVar21 = (int *)param_1[2];
    piVar10 = piVar21;
    if ((int)piVar21 < 1) {
      piVar10 = (int *)0x0;
    }
    iVar11 = param_1[3];
    if (iVar7 <= param_1[3]) {
      iVar11 = iVar7;
    }
    iVar7 = param_1[4];
    if (iVar12 <= param_1[4]) {
      iVar7 = iVar12;
    }
    if ((iVar11 < iVar9) || (iVar7 < (int)piVar10)) {
      return (int *)0xfffffffe;
    }
    local_60 = *piVar25;
    iVar12 = param_4 - local_44;
    iVar13 = param_5 - local_40;
    local_34 = 0;
    local_30 = 0;
    transform_image_point_fixed(&local_34,&local_3c,&local_44,param_7,param_8,param_9);
    DAT_1004ef3c = local_3c + iVar12;
    DAT_1004ef40 = local_38 + iVar13;
    local_30 = 0;
    local_34 = iVar6;
    transform_image_point_fixed(&local_34,&local_3c,&local_44,param_7,param_8,param_9);
    DAT_1004ef3c = DAT_1004ef3c + iVar2;
    DAT_1004ef50 = local_3c + iVar12 + iVar2;
    DAT_1004ef40 = DAT_1004ef40 + (int)piVar21;
    DAT_1004ef54 = local_38 + iVar13 + (int)piVar21;
    local_34 = iVar6;
    local_30 = iVar14;
    transform_image_point_fixed(&local_34,&local_3c,&local_44,param_7,param_8,param_9);
    DAT_1004ef64 = local_3c + iVar12;
    DAT_1004ef68 = local_38 + iVar13;
    local_34 = 0;
    local_30 = iVar14;
    transform_image_point_fixed(&local_34,&local_3c,&local_44,param_7,param_8,param_9);
    DAT_1004ef64 = DAT_1004ef64 + iVar2;
    DAT_1004ef78 = local_3c + iVar12 + iVar2;
    DAT_1004ef68 = DAT_1004ef68 + (int)piVar21;
    DAT_1004ef7c = local_38 + iVar13 + (int)piVar21;
    local_14 = local_14 + 1;
    piVar21 = &DAT_1004ef3c;
    local_90 = (int *)0x7fff;
    piVar25 = (int *)0xffff8000;
    uVar5 = 0xf;
    do {
      local_94 = (int *)piVar21[1];
      if ((int)local_94 <= (int)local_90) {
        local_90 = local_94;
        local_70 = piVar21;
      }
      if ((int)piVar25 <= (int)local_94) {
        piVar25 = local_94;
      }
      uVar5 = uVar5 & (((((uint)(*piVar21 - iVar9) >> 0x1f) << 1 | (uint)(iVar11 - *piVar21) >> 0x1f
                        ) << 1 | (uint)(piVar21[1] - (int)piVar10) >> 0x1f) << 1 |
                      (uint)(iVar7 - piVar21[1]) >> 0x1f);
      piVar21 = piVar21 + 5;
    } while (piVar21 != (int *)&DAT_1004ef8c);
    if (uVar5 == 0) {
      local_7c = local_70;
      local_80 = local_70;
      local_94 = local_70;
      piVar21 = local_7c;
      if (piVar25 != local_90) {
        do {
          local_7c = piVar21;
          piVar21 = local_7c + -5;
          if ((int)piVar21 < 0x1004ef3c) {
            piVar21 = &DAT_1004ef78;
          }
        } while (((local_7c[1] < (int)piVar10) && (piVar21[1] <= (int)piVar10)) ||
                (local_84 = piVar21[1] - local_7c[1], local_84 == 0));
        local_ac = (int)((longlong)
                         ((ulonglong)(uint)((*piVar21 - *local_7c) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_84 * 0x10000));
        local_b4 = (int)((longlong)
                         ((ulonglong)(uint)((piVar21[3] - local_7c[3]) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_84 * 0x10000));
        local_bc = (int)((longlong)
                         ((ulonglong)(uint)((piVar21[4] - local_7c[4]) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_84 * 0x10000));
        local_94 = (int *)(*local_7c * 0x10000 + 0x8000);
        local_9c = local_7c[3] * 0x10000 + 0x8000;
        local_a4 = local_7c[4] * 0x10000 + 0x8000;
        piVar23 = local_80;
        do {
          local_80 = piVar23;
          piVar23 = local_80 + 5;
          if (0x1004ef8b < (int)piVar23) {
            piVar23 = &DAT_1004ef3c;
          }
        } while (((local_80[1] < (int)piVar10) && (piVar23[1] <= (int)piVar10)) ||
                (local_88 = piVar23[1] - local_80[1], local_88 == 0));
        local_b0 = (int)((longlong)
                         ((ulonglong)(uint)((*piVar23 - *local_80) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_88 * 0x10000));
        local_b8 = (int)((longlong)
                         ((ulonglong)(uint)((piVar23[3] - local_80[3]) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_88 * 0x10000));
        local_c0 = (int)((longlong)
                         ((ulonglong)(uint)((piVar23[4] - local_80[4]) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_88 * 0x10000));
        local_98 = (int *)(*local_80 * 0x10000 + 0x8000);
        local_a0 = local_80[3] * 0x10000 + 0x8000;
        local_a8 = local_80[4] * 0x10000 + 0x8000;
        local_8c = iVar7 - (int)local_90;
        if ((int)piVar25 - iVar7 == 0 || (int)piVar25 < iVar7) {
          local_8c = local_8c + ((int)piVar25 - iVar7);
        }
        if ((int)piVar10 - (int)local_90 != 0 && (int)local_90 <= (int)piVar10) {
          local_8c = local_8c - ((int)piVar10 - (int)local_90);
          local_84 = local_84 - ((int)piVar10 - local_7c[1]);
          iVar6 = ((int)piVar10 - local_7c[1]) * 0x10000;
          local_94 = (int *)((int)local_94 +
                            ((uint)((longlong)local_ac * (longlong)iVar6) >> 0x10 |
                            (int)((ulonglong)((longlong)local_ac * (longlong)iVar6) >> 0x20) << 0x10
                            ));
          local_9c = local_9c +
                     ((uint)((longlong)local_b4 * (longlong)iVar6) >> 0x10 |
                     (int)((ulonglong)((longlong)local_b4 * (longlong)iVar6) >> 0x20) << 0x10);
          local_a4 = local_a4 +
                     ((uint)((longlong)local_bc * (longlong)iVar6) >> 0x10 |
                     (int)((ulonglong)((longlong)local_bc * (longlong)iVar6) >> 0x20) << 0x10);
          local_88 = local_88 - ((int)piVar10 - local_80[1]);
          iVar6 = ((int)piVar10 - local_80[1]) * 0x10000;
          local_98 = (int *)((int)local_98 +
                            ((uint)((longlong)local_b0 * (longlong)iVar6) >> 0x10 |
                            (int)((ulonglong)((longlong)local_b0 * (longlong)iVar6) >> 0x20) << 0x10
                            ));
          local_a0 = local_a0 +
                     ((uint)((longlong)local_b8 * (longlong)iVar6) >> 0x10 |
                     (int)((ulonglong)((longlong)local_b8 * (longlong)iVar6) >> 0x20) << 0x10);
          local_a8 = local_a8 +
                     ((uint)((longlong)local_c0 * (longlong)iVar6) >> 0x10 |
                     (int)((ulonglong)((longlong)local_c0 * (longlong)iVar6) >> 0x20) << 0x10);
          local_90 = piVar10;
        }
        local_60 = (int)local_90 * iVar8 + local_60;
        local_80 = piVar23;
        local_7c = piVar21;
LAB_1003ba59:
        piVar25 = local_94;
        local_d4 = local_9c;
        uVar17 = local_a0;
        piVar21 = local_98;
        uVar5 = local_a4;
        uVar22 = local_a8;
        if ((int)local_98 <= (int)local_94) {
          piVar25 = local_98;
          local_d4 = local_a0;
          uVar17 = local_9c;
          piVar21 = local_94;
          uVar5 = local_a8;
          uVar22 = local_a4;
        }
        local_c4 = (int)piVar25 >> 0x10;
        if ((local_c4 <= iVar11) && (local_c8 = (int)piVar21 >> 0x10, iVar9 <= local_c8)) {
          iVar6 = local_c8 - local_c4;
          if (iVar6 != 0) {
            uVar3 = CONCAT44((int)(uVar17 - local_d4) >> 0x10,(uVar17 - local_d4) * 0x10000) /
                    (longlong)(iVar6 * 0x10000);
            local_cc = (uint)uVar3;
            uVar17 = local_cc >> 0x10;
            iVar7 = 1;
            if ((uVar17 & 0x8000) != 0) {
              iVar7 = -1;
              uVar17 = ((uVar17 | 0xffff0000) + 1) - (uint)((uVar3 & 0xffff) == 0);
            }
            uVar3 = CONCAT44((int)(uVar22 - uVar5) >> 0x10,(uVar22 - uVar5) * 0x10000) /
                    (longlong)(iVar6 * 0x10000);
            local_d0 = (uint)uVar3;
            sVar16 = (short)(uVar3 >> 0x10);
            _DAT_1004ef98 = local_14;
            if ((local_d0 >> 0x10 & 0x8000) != 0) {
              _DAT_1004ef98 = -local_14;
              sVar16 = (sVar16 + 1) - (ushort)((uVar3 & 0xffff) == 0);
            }
            _DAT_1004ef94 = (int)(short)((short)local_14 * sVar16);
            _DAT_1004ef8c = uVar17 + _DAT_1004ef94;
            _DAT_1004ef90 = _DAT_1004ef8c + _DAT_1004ef98;
            _DAT_1004ef94 = iVar7 + uVar17 + _DAT_1004ef94;
            _DAT_1004ef98 = _DAT_1004ef94 + _DAT_1004ef98;
            iVar6 = iVar9 - local_c4;
            if (iVar6 != 0 && local_c4 <= iVar9) {
              local_c4 = local_c4 + iVar6;
              lVar4 = (longlong)(int)local_cc * (longlong)(iVar6 * 0x10000);
              local_d4 = local_d4 + ((uint)lVar4 >> 0x10 | (int)((ulonglong)lVar4 >> 0x20) << 0x10);
              lVar4 = (longlong)(int)local_d0 * (longlong)(iVar6 * 0x10000);
              uVar5 = uVar5 + ((uint)lVar4 >> 0x10 | (int)((ulonglong)lVar4 >> 0x20) << 0x10);
            }
            if (local_c8 - iVar11 != 0 && iVar11 <= local_c8) {
              local_c8 = local_c8 - (local_c8 - iVar11);
            }
          }
          pcVar24 = (char *)((local_d4 >> 0x10) + (uVar5 >> 0x10) * local_14 + local_18);
          pcVar26 = (char *)(local_60 + local_c4);
          local_c8 = local_c8 - local_c4;
          uVar17 = local_cc;
          if ((int)local_cc < 0) {
            uVar17 = -local_cc;
            local_d4 = ~local_d4;
          }
          uVar17 = uVar17 * 0x10000;
          local_d4 = local_d4 << 0x10;
          uVar22 = local_d0;
          if ((int)local_d0 < 0) {
            uVar22 = -local_d0;
            uVar5 = ~uVar5;
          }
          uVar22 = uVar22 * 0x10000;
          uVar5 = uVar5 << 0x10;
          do {
            if (local_c8 < 5) {
              if (*pcVar24 != -1) {
                *pcVar26 = *pcVar24;
              }
              pcVar24 = pcVar24 + *(int *)(&DAT_1004ef8c +
                                          ((uint)CARRY4(local_d4,uVar17) * 2 +
                                          (uint)CARRY4(uVar5,uVar22)) * 4);
              if (-1 < local_c8 + -1) {
                if (*pcVar24 != -1) {
                  pcVar26[1] = *pcVar24;
                }
                uVar18 = local_d4 + uVar17 + uVar17;
                uVar15 = uVar5 + uVar22 + uVar22;
                pcVar24 = pcVar24 + *(int *)(&DAT_1004ef8c +
                                            ((uint)CARRY4(local_d4 + uVar17,uVar17) * 2 +
                                            (uint)CARRY4(uVar5 + uVar22,uVar22)) * 4);
                if (-1 < local_c8 + -2) {
                  if (*pcVar24 != -1) {
                    pcVar26[2] = *pcVar24;
                  }
                  iVar6 = *(int *)(&DAT_1004ef8c +
                                  ((uint)CARRY4(uVar18,uVar17) * 2 + (uint)CARRY4(uVar15,uVar22)) *
                                  4);
                  if (-1 < local_c8 + -3) {
                    cVar1 = pcVar24[iVar6];
                    if (cVar1 != -1) {
                      pcVar26[3] = cVar1;
                    }
                    if ((-1 < local_c8 + -4) &&
                       (cVar1 = (pcVar24 + iVar6)
                                [*(int *)(&DAT_1004ef8c +
                                         ((uint)CARRY4(uVar18 + uVar17,uVar17) * 2 +
                                         (uint)CARRY4(uVar15 + uVar22,uVar22)) * 4)], cVar1 != -1))
                    {
                      pcVar26[4] = cVar1;
                    }
                  }
                }
              }
              break;
            }
            if (*pcVar24 != -1) {
              *pcVar26 = *pcVar24;
            }
            pcVar24 = pcVar24 + *(int *)(&DAT_1004ef8c +
                                        ((uint)CARRY4(local_d4,uVar17) * 2 +
                                        (uint)CARRY4(uVar5,uVar22)) * 4);
            if (*pcVar24 != -1) {
              pcVar26[1] = *pcVar24;
            }
            uVar18 = local_d4 + uVar17 + uVar17;
            uVar15 = uVar5 + uVar22 + uVar22;
            pcVar24 = pcVar24 + *(int *)(&DAT_1004ef8c +
                                        ((uint)CARRY4(local_d4 + uVar17,uVar17) * 2 +
                                        (uint)CARRY4(uVar5 + uVar22,uVar22)) * 4);
            if (*pcVar24 != -1) {
              pcVar26[2] = *pcVar24;
            }
            uVar19 = uVar18 + uVar17;
            uVar5 = uVar15 + uVar22;
            pcVar24 = pcVar24 + *(int *)(&DAT_1004ef8c +
                                        ((uint)CARRY4(uVar18,uVar17) * 2 +
                                        (uint)CARRY4(uVar15,uVar22)) * 4);
            if (*pcVar24 != -1) {
              pcVar26[3] = *pcVar24;
            }
            uVar18 = uVar19 + uVar17;
            uVar15 = uVar5 + uVar22;
            pcVar24 = pcVar24 + *(int *)(&DAT_1004ef8c +
                                        ((uint)CARRY4(uVar19,uVar17) * 2 +
                                        (uint)CARRY4(uVar5,uVar22)) * 4);
            if (*pcVar24 != -1) {
              pcVar26[4] = *pcVar24;
            }
            uVar20 = uVar18 + uVar17;
            uVar19 = uVar15 + uVar22;
            iVar6 = *(int *)(&DAT_1004ef8c +
                            ((uint)CARRY4(uVar18,uVar17) * 2 + (uint)CARRY4(uVar15,uVar22)) * 4);
            cVar1 = pcVar24[iVar6];
            if (cVar1 != -1) {
              pcVar26[5] = cVar1;
            }
            local_d4 = uVar20 + uVar17;
            uVar5 = uVar19 + uVar22;
            pcVar24 = pcVar24 + iVar6 +
                      *(int *)(&DAT_1004ef8c +
                              ((uint)CARRY4(uVar20,uVar17) * 2 + (uint)CARRY4(uVar19,uVar22)) * 4);
            pcVar26 = pcVar26 + 6;
            local_c8 = local_c8 + -6;
          } while (-1 < local_c8);
        }
        local_60 = local_60 + iVar8;
        local_8c = local_8c + -1;
        if (-1 < local_8c) {
          if (local_8c == 0) {
            local_94 = (int *)((int)local_94 + local_ac);
            local_9c = local_9c + local_b4;
            local_a4 = local_a4 + local_bc;
            local_98 = (int *)((int)local_98 + local_b0);
            local_a0 = local_a0 + local_b8;
            local_a8 = local_a8 + local_c0;
          }
          else {
            local_84 = local_84 + -1;
            if (local_84 == 0) {
              piVar25 = local_7c + -5;
              if ((int)piVar25 < 0x1004ef3c) {
                piVar25 = &DAT_1004ef78;
              }
              local_84 = (piVar25[1] - local_7c[1]) + (uint)(piVar25[1] - local_7c[1] == 0);
              local_ac = (int)((longlong)
                               ((ulonglong)(uint)((*piVar25 - *local_7c) * 0x10000 >> 0x10) << 0x20)
                              / (longlong)(local_84 * 0x10000));
              local_b4 = (int)((longlong)
                               ((ulonglong)(uint)((piVar25[3] - local_7c[3]) * 0x10000 >> 0x10) <<
                               0x20) / (longlong)(local_84 * 0x10000));
              local_bc = (int)((longlong)
                               ((ulonglong)(uint)((piVar25[4] - local_7c[4]) * 0x10000 >> 0x10) <<
                               0x20) / (longlong)(local_84 * 0x10000));
              local_94 = (int *)(*local_7c * 0x10000 + 0x8000);
              local_9c = local_7c[3] * 0x10000 + 0x8000;
              local_a4 = local_7c[4] * 0x10000 + 0x8000;
              local_7c = piVar25;
            }
            else {
              local_94 = (int *)((int)local_94 + local_ac);
              local_9c = local_9c + local_b4;
              local_a4 = local_a4 + local_bc;
            }
            local_88 = local_88 + -1;
            if (local_88 == 0) {
              piVar25 = local_80 + 5;
              if (0x1004ef8b < (int)piVar25) {
                piVar25 = &DAT_1004ef3c;
              }
              local_88 = (piVar25[1] - local_80[1]) + (uint)(piVar25[1] - local_80[1] == 0);
              local_b0 = (int)((longlong)
                               ((ulonglong)(uint)((*piVar25 - *local_80) * 0x10000 >> 0x10) << 0x20)
                              / (longlong)(local_88 * 0x10000));
              local_b8 = (int)((longlong)
                               ((ulonglong)(uint)((piVar25[3] - local_80[3]) * 0x10000 >> 0x10) <<
                               0x20) / (longlong)(local_88 * 0x10000));
              local_c0 = (int)((longlong)
                               ((ulonglong)(uint)((piVar25[4] - local_80[4]) * 0x10000 >> 0x10) <<
                               0x20) / (longlong)(local_88 * 0x10000));
              local_a0 = local_80[3] * 0x10000 + 0x8000;
              local_a8 = local_80[4] * 0x10000 + 0x8000;
              local_98 = (int *)(*local_80 * 0x10000 + 0x8000);
              local_80 = piVar25;
            }
            else {
              local_98 = (int *)((int)local_98 + local_b0);
              local_a0 = local_a0 + local_b8;
              local_a8 = local_a8 + local_c0;
            }
          }
          goto LAB_1003ba59;
        }
      }
    }
  }
  return local_94;
}


