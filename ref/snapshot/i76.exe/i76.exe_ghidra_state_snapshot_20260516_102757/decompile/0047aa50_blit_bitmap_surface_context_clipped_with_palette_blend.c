/*
 * Program: i76.exe
 * Function: blit_bitmap_surface_context_clipped_with_palette_blend
 * Entry: 0047aa50
 * Signature: undefined __cdecl blit_bitmap_surface_context_clipped_with_palette_blend(int * param_1, int * param_2, int param_3, uint * param_4, uint * param_5)
 */


/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] Clipped 8bpp surface blitter that
   blends/copies through palette composition lookup tables. */

void __cdecl
blit_bitmap_surface_context_clipped_with_palette_blend
          (int *param_1,int *param_2,int param_3,uint *param_4,uint *param_5)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  byte *pbVar4;
  int iVar5;
  bool bVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  undefined2 *puVar10;
  uint uVar11;
  int iVar12;
  uint *puVar13;
  int iVar14;
  undefined2 *puVar15;
  ushort uVar16;
  uint uVar17;
  int iVar18;
  uint *puVar19;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  uint *local_c;
  uint *local_8;
  
  if ((param_1[0xb] != 0) && (param_2[0xb] != 0)) {
    local_20 = param_3 + param_1[7];
    local_1c = (int)param_4 + param_1[8];
    local_18 = (param_2[9] + local_20) - param_2[7];
    local_14 = (param_2[10] + local_1c) - param_2[8];
    iVar7 = clip_rect_to_rect_bounds(&local_20,param_1 + 7);
    if (-1 < iVar7) {
      iVar9 = ((local_20 - param_3) - param_1[7]) + param_2[7];
      iVar18 = ((local_1c - (int)param_4) - param_1[8]) + param_2[8];
      iVar12 = (local_18 - local_20) + 1;
      puVar13 = (uint *)((local_14 - local_1c) + 1);
      iVar7 = param_2[2] + param_1[2] * 2;
      if (iVar7 == 0) {
        iVar7 = *param_1;
        puVar8 = (uint *)(local_1c * iVar7 + param_1[5] + local_20);
        iVar5 = *param_2;
        local_8 = (uint *)(iVar18 * iVar5 + iVar9 + param_2[5]);
        param_4 = puVar8;
        switch(param_5) {
        case (uint *)0x1:
          local_c = puVar13;
          param_5 = puVar8;
          if (iVar12 < 8) {
            do {
              iVar9 = -iVar12;
              do {
                *(undefined1 *)((int)param_5 + iVar9 + iVar12) =
                     *(undefined1 *)
                      ((int)&g_palette_blend_table_c +
                      (uint)CONCAT11(*(undefined1 *)((int)local_8 + iVar9 + iVar12),
                                     *(undefined1 *)((int)param_5 + iVar9 + iVar12)));
                bVar6 = iVar9 < -1;
                iVar9 = iVar9 + 1;
              } while (bVar6);
              param_5 = (uint *)((int)param_5 + iVar7);
              local_8 = (uint *)((int)local_8 + iVar5);
              puVar13 = (uint *)((int)puVar13 + -1);
            } while (puVar13 != (uint *)0x0);
            return;
          }
          do {
            uVar11 = -(int)param_5 & 3;
            iVar9 = iVar12 - uVar11;
            puVar13 = param_5;
            puVar8 = local_8;
            for (; uVar11 != 0; uVar11 = uVar11 - 1) {
              uVar17 = *puVar8;
              puVar8 = (uint *)((int)puVar8 + 1);
              *(undefined1 *)puVar13 =
                   *(undefined1 *)
                    ((int)&g_palette_blend_table_c + (uint)CONCAT11((char)uVar17,(char)*puVar13));
              puVar13 = (uint *)((int)puVar13 + 1);
            }
            do {
              iVar9 = iVar9 + -4;
              puVar1 = (undefined1 *)((int)puVar8 + 2);
              uVar16 = CONCAT11(*(undefined1 *)
                                 ((int)&g_palette_blend_table_c +
                                 (uint)CONCAT11(*(undefined1 *)((int)puVar8 + 1),
                                                *(undefined1 *)((int)puVar13 + 1))),
                                *(undefined1 *)
                                 ((int)&g_palette_blend_table_c +
                                 (uint)CONCAT11((char)*puVar8,(char)*puVar13)));
              puVar2 = (undefined1 *)((int)puVar8 + 3);
              puVar8 = puVar8 + 1;
              *puVar13 = (uint)uVar16 |
                         CONCAT22(uVar16,CONCAT11(*(undefined1 *)
                                                   ((int)&g_palette_blend_table_c +
                                                   (uint)CONCAT11(*puVar2,*(undefined1 *)
                                                                           ((int)puVar13 + 3))),
                                                  *(undefined1 *)
                                                   ((int)&g_palette_blend_table_c +
                                                   (uint)CONCAT11(*puVar1,*(undefined1 *)
                                                                           ((int)puVar13 + 2))))) <<
                         0x10;
              puVar13 = puVar13 + 1;
            } while (3 < iVar9);
            for (; iVar9 != 0; iVar9 = iVar9 + -1) {
              uVar11 = *puVar8;
              puVar8 = (uint *)((int)puVar8 + 1);
              *(undefined1 *)puVar13 =
                   *(undefined1 *)
                    ((int)&g_palette_blend_table_c + (uint)CONCAT11((char)uVar11,(char)*puVar13));
              puVar13 = (uint *)((int)puVar13 + 1);
            }
            local_8 = (uint *)((int)local_8 + iVar5);
            param_5 = (uint *)((int)param_5 + iVar7);
            local_c = (uint *)((int)local_c + -1);
          } while (local_c != (uint *)0x0);
          return;
        case (uint *)0x2:
          local_c = puVar13;
          param_5 = puVar8;
          if (iVar12 < 8) {
            do {
              iVar9 = -iVar12;
              do {
                *(undefined1 *)((int)param_5 + iVar9 + iVar12) =
                     *(undefined1 *)
                      ((int)&g_palette_blend_table_a +
                      (uint)CONCAT11(*(undefined1 *)((int)local_8 + iVar9 + iVar12),
                                     *(undefined1 *)((int)param_5 + iVar9 + iVar12)));
                bVar6 = iVar9 < -1;
                iVar9 = iVar9 + 1;
              } while (bVar6);
              param_5 = (uint *)((int)param_5 + iVar7);
              local_8 = (uint *)((int)local_8 + iVar5);
              puVar13 = (uint *)((int)puVar13 + -1);
            } while (puVar13 != (uint *)0x0);
            return;
          }
          do {
            uVar11 = -(int)param_5 & 3;
            iVar9 = iVar12 - uVar11;
            puVar13 = param_5;
            puVar8 = local_8;
            for (; uVar11 != 0; uVar11 = uVar11 - 1) {
              uVar17 = *puVar8;
              puVar8 = (uint *)((int)puVar8 + 1);
              *(undefined1 *)puVar13 =
                   *(undefined1 *)
                    ((int)&g_palette_blend_table_a + (uint)CONCAT11((char)uVar17,(char)*puVar13));
              puVar13 = (uint *)((int)puVar13 + 1);
            }
            do {
              iVar9 = iVar9 + -4;
              puVar1 = (undefined1 *)((int)puVar8 + 2);
              uVar16 = CONCAT11(*(undefined1 *)
                                 ((int)&g_palette_blend_table_a +
                                 (uint)CONCAT11(*(undefined1 *)((int)puVar8 + 1),
                                                *(undefined1 *)((int)puVar13 + 1))),
                                *(undefined1 *)
                                 ((int)&g_palette_blend_table_a +
                                 (uint)CONCAT11((char)*puVar8,(char)*puVar13)));
              puVar2 = (undefined1 *)((int)puVar8 + 3);
              puVar8 = puVar8 + 1;
              *puVar13 = (uint)uVar16 |
                         CONCAT22(uVar16,CONCAT11(*(undefined1 *)
                                                   ((int)&g_palette_blend_table_a +
                                                   (uint)CONCAT11(*puVar2,*(undefined1 *)
                                                                           ((int)puVar13 + 3))),
                                                  *(undefined1 *)
                                                   ((int)&g_palette_blend_table_a +
                                                   (uint)CONCAT11(*puVar1,*(undefined1 *)
                                                                           ((int)puVar13 + 2))))) <<
                         0x10;
              puVar13 = puVar13 + 1;
            } while (3 < iVar9);
            for (; iVar9 != 0; iVar9 = iVar9 + -1) {
              uVar11 = *puVar8;
              puVar8 = (uint *)((int)puVar8 + 1);
              *(undefined1 *)puVar13 =
                   *(undefined1 *)
                    ((int)&g_palette_blend_table_a + (uint)CONCAT11((char)uVar11,(char)*puVar13));
              puVar13 = (uint *)((int)puVar13 + 1);
            }
            local_8 = (uint *)((int)local_8 + iVar5);
            param_5 = (uint *)((int)param_5 + iVar7);
            local_c = (uint *)((int)local_c + -1);
          } while (local_c != (uint *)0x0);
          return;
        default:
          iVar9 = iVar12;
          param_5 = local_8;
          if (7 < iVar12) {
            do {
              uVar11 = -(int)param_4 & 3;
              uVar17 = iVar12 - uVar11;
              puVar8 = param_5;
              puVar19 = param_4;
              for (; uVar11 != 0; uVar11 = uVar11 - 1) {
                *(char *)puVar19 = (char)*puVar8;
                puVar8 = (uint *)((int)puVar8 + 1);
                puVar19 = (uint *)((int)puVar19 + 1);
              }
              uVar11 = uVar17 & 3;
              for (uVar17 = uVar17 >> 2; uVar17 != 0; uVar17 = uVar17 - 1) {
                *puVar19 = *puVar8;
                puVar8 = puVar8 + 1;
                puVar19 = puVar19 + 1;
              }
              for (; uVar11 != 0; uVar11 = uVar11 - 1) {
                *(char *)puVar19 = (char)*puVar8;
                puVar8 = (uint *)((int)puVar8 + 1);
                puVar19 = (uint *)((int)puVar19 + 1);
              }
              param_4 = (uint *)((int)param_4 + iVar7);
              param_5 = (uint *)((int)param_5 + iVar5);
              puVar13 = (uint *)((int)puVar13 + -1);
            } while (puVar13 != (uint *)0x0);
            return;
          }
          do {
            for (; iVar9 != 0; iVar9 = iVar9 + -1) {
              *(char *)puVar8 = (char)*local_8;
              local_8 = (uint *)((int)local_8 + 1);
              puVar8 = (uint *)((int)puVar8 + 1);
            }
            puVar8 = (uint *)((int)param_4 + iVar7);
            local_8 = (uint *)((int)param_5 + iVar5);
            puVar13 = (uint *)((int)puVar13 + -1);
            iVar9 = iVar12;
            param_5 = local_8;
            param_4 = puVar8;
          } while (puVar13 != (uint *)0x0);
          break;
        case (uint *)0x4:
          local_c = puVar13;
          param_5 = puVar8;
          if (iVar12 < 8) {
            do {
              iVar9 = -iVar12;
              do {
                *(undefined1 *)((int)param_5 + iVar9 + iVar12) =
                     *(undefined1 *)
                      ((int)&g_palette_blend_table_c +
                      (uint)CONCAT11(*(undefined1 *)((int)local_8 + iVar9 + iVar12),
                                     *(undefined1 *)((int)param_5 + iVar9 + iVar12)));
                bVar6 = iVar9 < -1;
                iVar9 = iVar9 + 1;
              } while (bVar6);
              param_5 = (uint *)((int)param_5 + iVar7);
              local_8 = (uint *)((int)local_8 + iVar5);
              puVar13 = (uint *)((int)puVar13 + -1);
            } while (puVar13 != (uint *)0x0);
            return;
          }
          do {
            uVar11 = -(int)param_5 & 3;
            iVar9 = iVar12 - uVar11;
            puVar13 = param_5;
            puVar8 = local_8;
            for (; uVar11 != 0; uVar11 = uVar11 - 1) {
              uVar17 = *puVar8;
              puVar8 = (uint *)((int)puVar8 + 1);
              *(undefined1 *)puVar13 =
                   (&g_palette_blend_table_b)[CONCAT11((char)uVar17,(char)*puVar13)];
              puVar13 = (uint *)((int)puVar13 + 1);
            }
            do {
              iVar9 = iVar9 + -4;
              uVar11 = *puVar8;
              puVar1 = (undefined1 *)((int)puVar8 + 1);
              puVar2 = (undefined1 *)((int)puVar8 + 2);
              puVar3 = (undefined1 *)((int)puVar8 + 3);
              puVar8 = puVar8 + 1;
              *puVar13 = (uint)CONCAT11((&g_palette_blend_table_b)
                                        [CONCAT11(*puVar1,*(undefined1 *)((int)puVar13 + 1))],
                                        (&g_palette_blend_table_b)
                                        [CONCAT11((char)uVar11,(char)*puVar13)]) |
                         CONCAT22(CONCAT11((&g_palette_blend_table_b)
                                           [CONCAT11(*puVar1,*(undefined1 *)((int)puVar13 + 1))],
                                           (&g_palette_blend_table_b)
                                           [CONCAT11((char)uVar11,(char)*puVar13)]),
                                  CONCAT11((&g_palette_blend_table_b)
                                           [CONCAT11(*puVar3,*(undefined1 *)((int)puVar13 + 3))],
                                           (&g_palette_blend_table_b)
                                           [CONCAT11(*puVar2,*(undefined1 *)((int)puVar13 + 2))]))
                         << 0x10;
              puVar13 = puVar13 + 1;
            } while (3 < iVar9);
            for (; iVar9 != 0; iVar9 = iVar9 + -1) {
              uVar11 = *puVar8;
              puVar8 = (uint *)((int)puVar8 + 1);
              *(undefined1 *)puVar13 =
                   (&g_palette_blend_table_b)[CONCAT11((char)uVar11,(char)*puVar13)];
              puVar13 = (uint *)((int)puVar13 + 1);
            }
            local_8 = (uint *)((int)local_8 + iVar5);
            param_5 = (uint *)((int)param_5 + iVar7);
            local_c = (uint *)((int)local_c + -1);
          } while (local_c != (uint *)0x0);
          return;
        case (uint *)0x5:
          local_c = (uint *)-iVar5;
          local_8 = puVar13;
          param_5 = (uint *)(((((param_2[1] << 3) >> 3) - iVar18) + -1) * iVar5 + iVar9 + param_2[5]
                            );
          if (iVar12 < 8) {
            do {
              iVar9 = -iVar12;
              do {
                *(undefined1 *)((int)param_4 + iVar9 + iVar12) =
                     *(undefined1 *)
                      ((int)&g_palette_blend_table_c +
                      (uint)CONCAT11(*(undefined1 *)((int)param_5 + iVar9 + iVar12),
                                     *(undefined1 *)((int)param_4 + iVar9 + iVar12)));
                bVar6 = iVar9 < -1;
                iVar9 = iVar9 + 1;
              } while (bVar6);
              param_4 = (uint *)((int)param_4 + iVar7);
              param_5 = (uint *)((int)param_5 + (int)local_c);
              local_8 = (uint *)((int)local_8 + -1);
            } while (local_8 != (uint *)0x0);
            return;
          }
          do {
            uVar11 = -(int)param_4 & 3;
            iVar9 = iVar12 - uVar11;
            puVar13 = param_4;
            puVar8 = param_5;
            for (; uVar11 != 0; uVar11 = uVar11 - 1) {
              uVar17 = *puVar8;
              puVar8 = (uint *)((int)puVar8 + 1);
              *(undefined1 *)puVar13 =
                   *(undefined1 *)
                    ((int)&g_palette_blend_table_c + (uint)CONCAT11((char)uVar17,(char)*puVar13));
              puVar13 = (uint *)((int)puVar13 + 1);
            }
            do {
              iVar9 = iVar9 + -4;
              puVar1 = (undefined1 *)((int)puVar8 + 2);
              uVar16 = CONCAT11(*(undefined1 *)
                                 ((int)&g_palette_blend_table_c +
                                 (uint)CONCAT11(*(undefined1 *)((int)puVar8 + 1),
                                                *(undefined1 *)((int)puVar13 + 1))),
                                *(undefined1 *)
                                 ((int)&g_palette_blend_table_c +
                                 (uint)CONCAT11((char)*puVar8,(char)*puVar13)));
              puVar2 = (undefined1 *)((int)puVar8 + 3);
              puVar8 = puVar8 + 1;
              *puVar13 = (uint)uVar16 |
                         CONCAT22(uVar16,CONCAT11(*(undefined1 *)
                                                   ((int)&g_palette_blend_table_c +
                                                   (uint)CONCAT11(*puVar2,*(undefined1 *)
                                                                           ((int)puVar13 + 3))),
                                                  *(undefined1 *)
                                                   ((int)&g_palette_blend_table_c +
                                                   (uint)CONCAT11(*puVar1,*(undefined1 *)
                                                                           ((int)puVar13 + 2))))) <<
                         0x10;
              puVar13 = puVar13 + 1;
            } while (3 < iVar9);
            for (; iVar9 != 0; iVar9 = iVar9 + -1) {
              uVar11 = *puVar8;
              puVar8 = (uint *)((int)puVar8 + 1);
              *(undefined1 *)puVar13 =
                   *(undefined1 *)
                    ((int)&g_palette_blend_table_c + (uint)CONCAT11((char)uVar11,(char)*puVar13));
              puVar13 = (uint *)((int)puVar13 + 1);
            }
            param_4 = (uint *)((int)param_4 + iVar7);
            param_5 = (uint *)((int)param_5 + (int)local_c);
            local_8 = (uint *)((int)local_8 + -1);
          } while (local_8 != (uint *)0x0);
          return;
        }
      }
      else if (iVar7 == 2) {
        iVar7 = *param_1;
        iVar5 = *param_2;
        puVar15 = (undefined2 *)(param_1[5] + (local_1c * iVar7 + local_20) * 2);
        iVar14 = iVar18 * iVar5 + iVar9 + param_2[5];
        if (param_5 == (uint *)0x0) {
          param_5 = puVar13;
          if (0 < (int)puVar13) {
            do {
              iVar9 = 0;
              puVar10 = puVar15;
              if (0 < iVar12) {
                do {
                  pbVar4 = (byte *)(iVar14 + iVar9);
                  iVar9 = iVar9 + 1;
                  *puVar10 = (&DAT_00608460)[*pbVar4];
                  puVar10 = puVar10 + 1;
                } while (iVar9 < iVar12);
              }
              puVar15 = puVar15 + iVar7;
              iVar14 = iVar14 + iVar5;
              param_5 = (uint *)((int)param_5 + -1);
            } while (param_5 != (uint *)0x0);
            return;
          }
        }
        else if (param_5 == (uint *)0x1) {
          param_5 = puVar13;
          if (0 < (int)puVar13) {
            do {
              iVar9 = 0;
              puVar10 = puVar15;
              if (0 < iVar12) {
                do {
                  if (*(byte *)(iVar14 + iVar9) != 0xff) {
                    *puVar10 = (&DAT_00608460)[*(byte *)(iVar14 + iVar9)];
                  }
                  iVar9 = iVar9 + 1;
                  puVar10 = puVar10 + 1;
                } while (iVar9 < iVar12);
              }
              iVar14 = iVar14 + iVar5;
              puVar15 = puVar15 + iVar7;
              param_5 = (uint *)((int)param_5 + -1);
            } while (param_5 != (uint *)0x0);
            return;
          }
        }
        else if (param_5 == (uint *)0x5) {
          iVar9 = ((((param_2[1] << 3) >> 3) - iVar18) + -1) * iVar5 + iVar9 + param_2[5];
          param_4 = puVar13;
          if (0 < (int)puVar13) {
            do {
              iVar18 = 0;
              puVar10 = puVar15;
              if (0 < iVar12) {
                do {
                  if (*(byte *)(iVar9 + iVar18) != 0xff) {
                    *puVar10 = (&DAT_00608460)[*(byte *)(iVar9 + iVar18)];
                  }
                  iVar18 = iVar18 + 1;
                  puVar10 = puVar10 + 1;
                } while (iVar18 < iVar12);
              }
              iVar9 = iVar9 - iVar5;
              param_4 = (uint *)((int)param_4 + -1);
              puVar15 = puVar15 + iVar7;
            } while (param_4 != (uint *)0x0);
            return;
          }
        }
      }
    }
  }
  return;
}


