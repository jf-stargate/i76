/*
 * Program: i76.exe
 * Function: projection_or_clip_context_helper_0047a860
 * Entry: 0047a860
 * Signature: undefined __cdecl projection_or_clip_context_helper_0047a860(undefined4 * param_1)
 */


/* cgpt readability rename set D v16: Readability pass set D: projection or clip context helper
   based on adjacent named subsystem context. */

void __cdecl projection_or_clip_context_helper_0047a860(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  ushort uVar8;
  uint uVar9;
  int *piVar10;
  uint uVar11;
  uint *puVar12;
  undefined1 *puVar13;
  bool bVar14;
  uint local_202c [2048];
  int local_2c [2];
  uint *local_24;
  int local_20;
  uint local_1c;
  uint local_18;
  undefined1 *local_14;
  int iVar15;
  
  zfsf_error_context_helper_004ba0a0();
  iVar6 = param_1[0xb];
  iVar5 = param_1[5];
  local_2c[0] = (iVar6 >> 0x10) * iVar5;
  local_2c[1] = local_2c[0] + iVar5;
  iVar15 = 0;
  if (0 < (int)param_1[9]) {
    iVar15 = iVar6 * param_1[9];
  }
  local_1c = iVar6 * 0x10000;
  local_18 = 0;
  if (0 < (int)param_1[8]) {
    local_18 = param_1[10] * param_1[8];
  }
  iVar6 = param_1[2];
  local_20 = ((iVar15 >> 0x10) + param_1[7]) * iVar5 + param_1[1] + param_1[6];
  local_24 = (uint *)*param_1;
  iVar5 = param_1[3];
  local_14 = (undefined1 *)iVar6;
  iVar3 = param_1[4];
  uVar9 = param_1[10];
  uVar11 = uVar9 * 0x10000;
  uVar4 = local_18 << 0x10;
  local_18 = local_18 >> 0x10;
  iVar7 = -iVar6;
  do {
    bVar14 = CARRY4(uVar4,uVar11);
    uVar4 = uVar4 + uVar11;
    local_18 = local_18 + (uVar9 >> 0x10) + (uint)bVar14;
    local_202c[iVar6 + iVar7] = local_18;
    bVar14 = iVar7 < -1;
    iVar7 = iVar7 + 1;
  } while (bVar14);
  if (iVar6 < 9) {
    puVar13 = (undefined1 *)((int)local_24 + iVar6);
    local_14 = (undefined1 *)-iVar6;
    uVar9 = iVar15 << 0x10;
    iVar15 = (int)local_14;
    do {
      do {
        puVar13[iVar15] =
             *(undefined1 *)
              ((int)&g_palette_blend_table_c +
              CONCAT31(CONCAT21((short)(local_202c[iVar6 + iVar15] >> 0x10),
                                *(undefined1 *)(local_20 + local_202c[iVar6 + iVar15])),
                       puVar13[iVar15]));
        iVar7 = iVar15 + 1;
        bVar14 = iVar15 < -1;
        iVar15 = iVar7;
      } while (bVar14);
      puVar13 = puVar13 + iVar3;
      bVar14 = CARRY4(uVar9,local_1c);
      uVar9 = uVar9 + local_1c;
      local_20 = local_20 + local_2c[iVar7 * 2 + (uint)bVar14];
      iVar5 = iVar5 + -1;
      iVar15 = (int)local_14;
    } while (iVar5 != 0);
  }
  else {
    iVar15 = iVar15 << 0x10;
    local_14 = &stack0xfffffffc;
    do {
      *(int *)(local_14 + -4) = iVar15;
      piVar10 = (int *)(local_14 + -0x2028);
      uVar9 = -(int)local_24 & 3;
      *(int *)(local_14 + -0xc) = iVar5;
      iVar6 = *(int *)(local_14 + -0x10) - uVar9;
      for (; uVar9 != 0; uVar9 = uVar9 - 1) {
        iVar5 = *piVar10;
        piVar10 = piVar10 + 1;
        *(undefined1 *)local_24 =
             *(undefined1 *)
              ((int)&g_palette_blend_table_c +
              CONCAT31(CONCAT21((short)((uint)iVar5 >> 0x10),*(undefined1 *)(local_20 + iVar5)),
                       (char)*local_24));
        local_24 = (uint *)((int)local_24 + 1);
      }
      do {
        iVar6 = iVar6 + -4;
        piVar1 = piVar10 + 2;
        uVar8 = CONCAT11(*(undefined1 *)
                          ((int)&g_palette_blend_table_c +
                          CONCAT31(CONCAT21((short)((uint)piVar10[1] >> 0x10),
                                            *(undefined1 *)(local_20 + piVar10[1])),
                                   *(undefined1 *)((int)local_24 + 1))),
                         *(undefined1 *)
                          ((int)&g_palette_blend_table_c +
                          CONCAT31(CONCAT21((short)((uint)*piVar10 >> 0x10),
                                            *(undefined1 *)(local_20 + *piVar10)),(char)*local_24)))
        ;
        piVar2 = piVar10 + 3;
        puVar12 = local_24 + 1;
        piVar10 = piVar10 + 4;
        *local_24 = (uint)uVar8 |
                    CONCAT22(uVar8,CONCAT11(*(undefined1 *)
                                             ((int)&g_palette_blend_table_c +
                                             CONCAT31(CONCAT21((short)((uint)*piVar2 >> 0x10),
                                                               *(undefined1 *)(local_20 + *piVar2)),
                                                      *(undefined1 *)((int)local_24 + 3))),
                                            *(undefined1 *)
                                             ((int)&g_palette_blend_table_c +
                                             CONCAT31(CONCAT21((short)((uint)*piVar1 >> 0x10),
                                                               *(undefined1 *)(local_20 + *piVar1)),
                                                      *(undefined1 *)((int)local_24 + 2))))) << 0x10
        ;
        local_24 = puVar12;
      } while (3 < iVar6);
      for (; iVar6 != 0; iVar6 = iVar6 + -1) {
        iVar5 = *piVar10;
        piVar10 = piVar10 + 1;
        *(undefined1 *)puVar12 =
             *(undefined1 *)
              ((int)&g_palette_blend_table_c +
              CONCAT31(CONCAT21((short)((uint)iVar5 >> 0x10),*(undefined1 *)(local_20 + iVar5)),
                       (char)*puVar12));
        puVar12 = (uint *)((int)puVar12 + 1);
      }
      local_24 = (uint *)((int)puVar12 + *(int *)(local_14 + -8));
      iVar15 = *(uint *)(local_14 + -4) + *(uint *)(local_14 + -0x18);
      local_20 = local_20 +
                 *(int *)(local_14 +
                         (uint)CARRY4(*(uint *)(local_14 + -4),*(uint *)(local_14 + -0x18)) * 4 +
                         -0x28);
      iVar5 = *(int *)(local_14 + -0xc) + -1;
    } while (iVar5 != 0);
  }
  return;
}


