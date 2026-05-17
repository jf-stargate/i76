/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode_00488e40
 * Entry: 00488e40
 * Signature: undefined __cdecl raster_emit_span_callback_mode_00488e40(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Raster span callback target from
   draw table; exact mode still being separated by feature trace. */

void __cdecl raster_emit_span_callback_mode_00488e40(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  ulonglong uVar9;
  uint uVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  uint *puVar14;
  undefined1 *puVar15;
  int *piVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint uVar24;
  float10 in_ST0;
  float10 fVar25;
  float10 fVar26;
  float10 fVar27;
  float10 fVar28;
  float10 fVar29;
  float10 fVar30;
  float10 fVar31;
  float10 fVar32;
  float10 fVar33;
  float10 fVar34;
  float local_28;
  undefined4 *local_24;
  int *local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar1 = *param_2;
  iVar2 = param_2[8];
  iVar3 = param_2[7];
  iVar4 = param_2[5];
  piVar5 = (int *)*param_1;
  if (piVar5 != DAT_006439c0) {
    iVar11 = *piVar5;
    piVar12 = piVar5 + 2;
    uVar18 = (piVar5[1] << 3) >> 3;
    piVar16 = (int *)(uVar18 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar5;
    if (piVar16 != (int *)0x0) {
      local_24 = &DAT_006439d8;
      local_20 = piVar16;
      do {
        *local_24 = piVar12;
        local_24 = local_24 + 1;
        piVar12 = (int *)((int)piVar12 + iVar11);
        local_20 = (int *)((int)local_20 - 1);
        param_2 = piVar16;
      } while (local_20 != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar18) {
      piVar16 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar18 - (int)param_2) + 3 >> 2);
      do {
        piVar16[-1] = (int)piVar12;
        *piVar16 = (int)piVar12 + iVar11;
        iVar13 = (int)piVar12 + iVar11 + iVar11;
        piVar16[1] = iVar13;
        iVar13 = iVar13 + iVar11;
        piVar16[2] = iVar13;
        piVar12 = (int *)(iVar13 + iVar11);
        piVar16 = piVar16 + 4;
        param_2 = (int *)((int)param_2 + -1);
      } while (param_2 != (int *)0x0);
    }
  }
  DAT_0059bc38 = *piVar5 - 1;
  DAT_0059bcb0 = ((piVar5[1] << 3) >> 3) - 1;
  piVar5 = (int *)param_1[0xc];
  *piVar5 = param_1[10];
  puVar14 = (uint *)(param_1[0xb] + 4);
  while (puVar14 != (uint *)(piVar5 + 1)) {
    uVar18 = *puVar14;
    puVar14 = puVar14 + 1;
    fVar6 = (float)(uVar18 >> 0x15);
    local_14 = (float)param_1[0x10];
    fVar8 = (float)(uVar18 & 0x3ff);
    local_1c = (float)param_1[0x12];
    local_18 = (float)param_1[0x14];
    local_c = local_14 * fVar6 + fVar8 * (float)param_1[0x11] + (float)param_1[3];
    local_8 = (float)param_1[0x16];
    puVar15 = (undefined1 *)
              ((uVar18 & 0x3ff) * iVar1 + (uVar18 >> 0x15) + iVar2 * iVar1 + iVar3 + iVar4);
    uVar18 = (uVar18 >> 10 & 0x7ff) - 1;
    uVar24 = uVar18 & 0xf;
    local_10 = local_1c * fVar6 + fVar8 * (float)param_1[0x13] + (float)param_1[4];
    fVar7 = local_18 * fVar6 + fVar8 * (float)param_1[0x15] + (float)param_1[5];
    local_28 = local_8 * fVar6 + fVar8 * (float)param_1[0x17] + (float)param_1[6];
    fVar6 = (float)uVar24;
    _DAT_0059bc50 = (double)(local_28 + (float)_DAT_004faf18);
    local_28 = fVar6 * local_8 + local_28;
    _DAT_0059bba0 = (double)(local_8 + (float)_DAT_004faf18);
    local_8 = local_8 * _DAT_004be774;
    uVar17 = DAT_0059bc50;
    if (((ulonglong)_DAT_0059bc50 & 0xffffe000) != 0) {
      uVar17 = ~DAT_0059bc50 >> 0x13;
      _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar17);
      local_28 = (float)uVar17;
    }
    uVar10 = DAT_0059bba0 * uVar18 + uVar17;
    if ((uVar10 & 0xffffe000) != 0) {
      iVar11 = (int)((~uVar10 >> 0x13) - uVar17) / (int)uVar18;
      _DAT_0059bba0 = (double)CONCAT44(DAT_0059bba0_4,iVar11);
      local_8 = (float)(iVar11 << 4);
    }
    fVar8 = _DAT_004be778 / fVar7;
    _DAT_0059bc88 = (double)(fVar8 * local_c + (float)_DAT_004faf18);
    _DAT_0059bc70 = (double)(fVar8 * local_10 + (float)_DAT_004faf18);
    local_c = fVar6 * local_14 + local_c;
    local_10 = fVar6 * local_1c + local_10;
    param_2 = (int *)(fVar6 * local_18 + fVar7);
    _DAT_0059bc00 =
         (double)(((_DAT_004be778 / (float)param_2) * local_c - (float)DAT_0059bc88) *
                  *(float *)(&DAT_004f9d38 + uVar24 * 4) + (float)_DAT_004faf18);
    _DAT_0059bc08 =
         (double)(((_DAT_004be778 / (float)param_2) * local_10 - (float)DAT_0059bc70) *
                  *(float *)(&DAT_004f9d38 + uVar24 * 4) + (float)_DAT_004faf18);
    if (0 < (int)uVar18 >> 4) {
      local_14 = local_14 * _DAT_004be774;
      local_1c = local_1c * _DAT_004be774;
      local_18 = local_18 * _DAT_004be774;
      local_c = local_c + local_14;
      local_10 = local_10 + local_1c;
      param_2 = (int *)((float)param_2 + local_18);
      in_ST0 = (float10)_DAT_004fa494 / (float10)(float)param_2;
    }
    DAT_0059bd38 = puVar15 + uVar24 + 1;
    iVar11 = DAT_0059bc88;
    iVar13 = DAT_0059bc70;
    if (puVar15 != DAT_0059bd38) {
      do {
        uVar24 = iVar13 >> 0x10;
        uVar10 = iVar11 >> 0x10;
        iVar13 = iVar13 + DAT_0059bc08;
        iVar11 = iVar11 + DAT_0059bc00;
        uVar17 = DAT_0059bc50;
        iVar19 = DAT_0059bba0;
        *puVar15 = (&DAT_0061b2a0)
                   [(DAT_0059bc50 & 0x1f00) +
                    (uint)*(byte *)((&DAT_006439d8)[uVar24 & DAT_0059bcb0] + (uVar10 & DAT_0059bc38)
                                   )];
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar17 + iVar19);
        puVar15 = puVar15 + 1;
      } while (puVar15 != DAT_0059bd38);
    }
    _DAT_0059bc88 = (double)CONCAT44(DAT_0059bc88_4,iVar11);
    _DAT_0059bc70 = (double)CONCAT44(DAT_0059bc70_4,iVar13);
    iVar19 = ((int)uVar18 >> 4) + -1;
    if (-1 < iVar19) {
      _DAT_0059bc88 = (double)CONCAT44(DAT_0059bc88_4,iVar11 - DAT_0059bc00);
      _DAT_0059bc70 = (double)CONCAT44(DAT_0059bc70_4,iVar13 - DAT_0059bc08);
      fVar25 = (float10)(iVar11 - DAT_0059bc00);
      fVar26 = (float10)local_10;
      fVar27 = (float10)_DAT_0059bc70 - (float10)_DAT_004faf18;
      fVar29 = in_ST0;
      fVar32 = (float10)(float)param_2;
      fVar33 = (float10)local_c;
      do {
        fVar6 = local_28 + (float)_DAT_004faf18;
        local_28 = local_28 + local_8;
        _DAT_0059bc50 = (double)fVar6;
        fVar28 = (fVar29 * fVar33 - fVar25) + (float10)_DAT_004fa490;
        fVar29 = (fVar29 * fVar26 - fVar27) + (float10)_DAT_004fa490;
        fVar30 = fVar26 + (float10)local_1c;
        _DAT_0059bc08 = (double)fVar29;
        _DAT_0059bc00 = (double)fVar28;
        fVar34 = (fVar29 - (float10)_DAT_004fa490) + fVar27;
        fVar29 = (fVar28 - (float10)_DAT_004fa490) + fVar25;
        fVar28 = fVar33;
        fVar31 = fVar30;
        fVar26 = fVar29;
        fVar25 = fVar34;
        if (iVar19 != 0) {
          fVar28 = fVar32 + (float10)local_18;
          fVar31 = fVar33 + (float10)local_14;
          fVar32 = (float10)_DAT_004fa494 / fVar28;
          fVar26 = fVar30;
          fVar25 = fVar29;
          fVar27 = fVar34;
        }
        iVar11 = DAT_0059bc08;
        iVar13 = DAT_0059bc70 + DAT_0059bc08 + DAT_0059bc08;
        iVar21 = DAT_0059bc88 + DAT_0059bc00 + DAT_0059bc00;
        uVar9 = (ulonglong)_DAT_0059bc50 >> 8;
        uVar17 = iVar13 >> 0x10 & DAT_0059bcb0;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *puVar15 = (&DAT_0061b2a0)
                   [CONCAT31((int3)uVar9,
                             *(undefined1 *)
                              ((&DAT_006439d8)[DAT_0059bc70 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                              (DAT_0059bc88 + DAT_0059bc00 >> 0x10 & DAT_0059bc38))) & 0x1fff];
        iVar13 = iVar13 + iVar11;
        uVar18 = DAT_0059bc50 >> 8;
        iVar22 = iVar21 + DAT_0059bc00;
        iVar20 = iVar13 + DAT_0059bc08;
        iVar11 = (&DAT_006439d8)[iVar13 >> 0x10 & DAT_0059bcb0];
        uVar24 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[1] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar17] + (iVar21 >> 0x10 & DAT_0059bc38))) &
                      0x1fff];
        uVar18 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        uVar17 = iVar20 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[2] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,*(undefined1 *)(iVar11 + uVar24)) & 0x1fff];
        iVar20 = iVar20 + iVar13;
        uVar18 = DAT_0059bc50 >> 8;
        iVar23 = iVar22 + DAT_0059bc00;
        iVar21 = iVar20 + DAT_0059bc08;
        iVar11 = (&DAT_006439d8)[iVar20 >> 0x10 & DAT_0059bcb0];
        uVar24 = iVar23 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[3] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar17] + (iVar22 >> 0x10 & DAT_0059bc38))) &
                      0x1fff];
        uVar18 = DAT_0059bc50 >> 8;
        iVar23 = iVar23 + DAT_0059bc00;
        uVar17 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[4] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,*(undefined1 *)(iVar11 + uVar24)) & 0x1fff];
        iVar21 = iVar21 + iVar13;
        uVar18 = DAT_0059bc50 >> 8;
        iVar22 = iVar23 + DAT_0059bc00;
        iVar20 = iVar21 + DAT_0059bc08;
        iVar11 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar24 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[5] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar17] + (iVar23 >> 0x10 & DAT_0059bc38))) &
                      0x1fff];
        uVar18 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        uVar17 = iVar20 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[6] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,*(undefined1 *)(iVar11 + uVar24)) & 0x1fff];
        iVar20 = iVar20 + iVar13;
        uVar18 = DAT_0059bc50 >> 8;
        iVar23 = iVar22 + DAT_0059bc00;
        iVar21 = iVar20 + DAT_0059bc08;
        iVar11 = (&DAT_006439d8)[iVar20 >> 0x10 & DAT_0059bcb0];
        uVar24 = iVar23 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[7] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar17] + (iVar22 >> 0x10 & DAT_0059bc38))) &
                      0x1fff];
        uVar18 = DAT_0059bc50 >> 8;
        iVar23 = iVar23 + DAT_0059bc00;
        uVar17 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[8] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,*(undefined1 *)(iVar11 + uVar24)) & 0x1fff];
        iVar21 = iVar21 + iVar13;
        uVar18 = DAT_0059bc50 >> 8;
        iVar22 = iVar23 + DAT_0059bc00;
        iVar20 = iVar21 + DAT_0059bc08;
        iVar11 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar24 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[9] = (&DAT_0061b2a0)
                     [CONCAT31((int3)uVar18,
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar17] + (iVar23 >> 0x10 & DAT_0059bc38))) &
                      0x1fff];
        uVar18 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        uVar17 = iVar20 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[10] = (&DAT_0061b2a0)
                      [CONCAT31((int3)uVar18,*(undefined1 *)(iVar11 + uVar24)) & 0x1fff];
        iVar20 = iVar20 + iVar13;
        uVar18 = DAT_0059bc50 >> 8;
        iVar23 = iVar22 + DAT_0059bc00;
        iVar21 = iVar20 + DAT_0059bc08;
        iVar11 = (&DAT_006439d8)[iVar20 >> 0x10 & DAT_0059bcb0];
        uVar24 = iVar23 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[0xb] = (&DAT_0061b2a0)
                       [CONCAT31((int3)uVar18,
                                 *(undefined1 *)
                                  ((&DAT_006439d8)[uVar17] + (iVar22 >> 0x10 & DAT_0059bc38))) &
                        0x1fff];
        uVar18 = DAT_0059bc50 >> 8;
        iVar23 = iVar23 + DAT_0059bc00;
        uVar17 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[0xc] = (&DAT_0061b2a0)
                       [CONCAT31((int3)uVar18,*(undefined1 *)(iVar11 + uVar24)) & 0x1fff];
        iVar21 = iVar21 + iVar13;
        uVar18 = DAT_0059bc50 >> 8;
        iVar20 = iVar23 + DAT_0059bc00;
        iVar13 = iVar21 + DAT_0059bc08;
        iVar11 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar24 = iVar20 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[0xd] = (&DAT_0061b2a0)
                       [CONCAT31((int3)uVar18,
                                 *(undefined1 *)
                                  ((&DAT_006439d8)[uVar17] + (iVar23 >> 0x10 & DAT_0059bc38))) &
                        0x1fff];
        uVar18 = DAT_0059bc50 >> 8;
        iVar20 = iVar20 + DAT_0059bc00;
        uVar17 = iVar13 >> 0x10 & DAT_0059bcb0;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[0xe] = (&DAT_0061b2a0)
                       [CONCAT31((int3)uVar18,*(undefined1 *)(iVar11 + uVar24)) & 0x1fff];
        iVar11 = DAT_0059bba0 + DAT_0059bc50;
        puVar15[0xf] = (&DAT_0061b2a0)
                       [CONCAT31((int3)(DAT_0059bc50 >> 8),
                                 *(undefined1 *)
                                  ((&DAT_006439d8)[uVar17] + (iVar20 >> 0x10 & DAT_0059bc38))) &
                        0x1fff];
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,iVar11);
        puVar15 = puVar15 + 0x10;
        _DAT_0059bc88 = (double)CONCAT44(DAT_0059bc88_4,iVar20);
        _DAT_0059bc70 = (double)CONCAT44(DAT_0059bc70_4,iVar13);
        iVar19 = iVar19 + -1;
        fVar29 = fVar32;
        fVar32 = fVar28;
        fVar33 = fVar31;
        in_ST0 = fVar27;
      } while (-1 < iVar19);
    }
  }
  return;
}


