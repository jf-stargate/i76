/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode_00486860
 * Entry: 00486860
 * Signature: undefined __cdecl raster_emit_span_callback_mode_00486860(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Raster span callback target from
   draw table; exact mode still being separated by feature trace. */

void __cdecl raster_emit_span_callback_mode_00486860(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  ulonglong uVar11;
  int *piVar12;
  int iVar13;
  uint *puVar14;
  uint uVar15;
  int iVar16;
  int *piVar17;
  uint uVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int local_20;
  undefined4 *local_1c;
  int *local_18;
  float local_14;
  float local_c;
  
  iVar1 = *param_2;
  iVar2 = param_2[8];
  iVar3 = param_2[7];
  iVar4 = param_2[5];
  piVar5 = (int *)*param_1;
  if (piVar5 != DAT_006439c0) {
    iVar16 = *piVar5;
    piVar12 = piVar5 + 2;
    uVar19 = (piVar5[1] << 3) >> 3;
    piVar17 = (int *)(uVar19 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar5;
    if (piVar17 != (int *)0x0) {
      local_1c = &DAT_006439d8;
      local_18 = piVar17;
      do {
        *local_1c = piVar12;
        local_1c = local_1c + 1;
        piVar12 = (int *)((int)piVar12 + iVar16);
        local_18 = (int *)((int)local_18 - 1);
        param_2 = piVar17;
      } while (local_18 != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar19) {
      piVar17 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar19 - (int)param_2) + 3 >> 2);
      do {
        piVar17[-1] = (int)piVar12;
        *piVar17 = (int)piVar12 + iVar16;
        iVar13 = (int)piVar12 + iVar16 + iVar16;
        piVar17[1] = iVar13;
        iVar13 = iVar13 + iVar16;
        piVar17[2] = iVar13;
        piVar12 = (int *)(iVar13 + iVar16);
        piVar17 = piVar17 + 4;
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
    uVar19 = *puVar14;
    puVar14 = puVar14 + 1;
    fVar9 = (float)(uVar19 >> 0x15);
    fVar6 = (float)param_1[0x10];
    fVar10 = (float)(uVar19 & 0x3ff);
    fVar7 = (float)param_1[0x12];
    fVar8 = (float)param_1[0x16];
    local_c = fVar6 * fVar9 + fVar10 * (float)param_1[0x11] + (float)param_1[3];
    local_18 = (int *)((uVar19 & 0x3ff) * iVar1 + (uVar19 >> 0x15) + iVar2 * iVar1 + iVar3 + iVar4);
    local_14 = fVar7 * fVar9 + fVar10 * (float)param_1[0x13] + (float)param_1[4];
    fVar10 = fVar8 * fVar9 + fVar10 * (float)param_1[0x17] + (float)param_1[6];
    uVar19 = (uVar19 >> 10 & 0x7ff) - 1;
    fVar9 = (float)(uVar19 & 0xf);
    local_20 = (int)uVar19 >> 4;
    _DAT_0059bc50 = (double)(fVar10 + (float)_DAT_004faf18);
    local_1c = (undefined4 *)(fVar9 * fVar8 + fVar10);
    _DAT_0059bba0 = (double)(fVar8 + (float)_DAT_004faf18);
    param_2 = (int *)(fVar8 * _DAT_004be774);
    uVar18 = DAT_0059bc50;
    if (((ulonglong)_DAT_0059bc50 & 0xffffe000) != 0) {
      uVar18 = ~DAT_0059bc50 >> 0x13;
      _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar18);
      local_1c = (undefined4 *)(float)uVar18;
    }
    uVar15 = DAT_0059bba0 * uVar19 + uVar18;
    if ((uVar15 & 0xffffe000) != 0) {
      iVar16 = (int)((~uVar15 >> 0x13) - uVar18) / (int)uVar19;
      _DAT_0059bba0 = (double)CONCAT44(DAT_0059bba0_4,iVar16);
      param_2 = (int *)(float)(iVar16 << 4);
    }
    DAT_0059bd38 = (undefined1 *)((int)local_18 + (uVar19 & 0xf) + 1);
    _DAT_0059bc00 = (double)(fVar6 + (float)_DAT_004faf18);
    _DAT_0059bc08 = (double)(fVar7 + (float)_DAT_004faf18);
    _DAT_0059bc20 = (double)(local_c + (float)_DAT_004faf18);
    _DAT_0059bbb0 = (double)(local_14 + (float)_DAT_004faf18);
    local_c = fVar9 * fVar6 + local_c;
    local_14 = fVar9 * fVar7 + local_14;
    fVar6 = fVar6 * _DAT_004be774;
    fVar7 = fVar7 * _DAT_004be774;
    iVar16 = DAT_0059bc20;
    iVar13 = DAT_0059bbb0;
    if (local_18 != (int *)DAT_0059bd38) {
      do {
        uVar18 = iVar13 >> 0x10;
        uVar15 = iVar16 >> 0x10;
        iVar13 = iVar13 + DAT_0059bc08;
        iVar16 = iVar16 + DAT_0059bc00;
        uVar19 = DAT_0059bc50;
        iVar20 = DAT_0059bba0;
        *(undefined1 *)local_18 =
             (&DAT_0061b2a0)
             [(DAT_0059bc50 & 0x1f00) +
              (uint)*(byte *)((&DAT_006439d8)[uVar18 & DAT_0059bcb0] + (uVar15 & DAT_0059bc38))];
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar19 + iVar20);
        local_18 = (int *)((int)local_18 + 1);
      } while (local_18 != (int *)DAT_0059bd38);
    }
    _DAT_0059bc20 = (double)CONCAT44(DAT_0059bc20_4,iVar16);
    _DAT_0059bbb0 = (double)CONCAT44(DAT_0059bbb0_4,iVar13);
    if (-1 < local_20 + -1) {
      do {
        _DAT_0059bc50 = (double)((float)local_1c + (float)_DAT_004faf18);
        local_1c = (undefined4 *)((float)local_1c + (float)param_2);
        _DAT_0059bc20 = (double)(local_c + (float)_DAT_004faf18);
        _DAT_0059bbb0 = (double)(local_14 + (float)_DAT_004faf18);
        local_c = local_c + fVar6;
        local_14 = local_14 + fVar7;
        iVar16 = DAT_0059bc08;
        iVar13 = DAT_0059bbb0 + DAT_0059bc08 + DAT_0059bc08;
        iVar21 = DAT_0059bc20 + DAT_0059bc00 + DAT_0059bc00;
        uVar11 = (ulonglong)_DAT_0059bc50 >> 8;
        uVar18 = iVar13 >> 0x10 & DAT_0059bcb0;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)local_18 =
             (&DAT_0061b2a0)
             [CONCAT31((int3)uVar11,
                       *(undefined1 *)
                        ((&DAT_006439d8)[DAT_0059bbb0 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                        (DAT_0059bc20 + DAT_0059bc00 >> 0x10 & DAT_0059bc38))) & 0x1fff];
        iVar13 = iVar13 + iVar16;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar21 + DAT_0059bc00;
        iVar20 = iVar13 + DAT_0059bc08;
        iVar16 = (&DAT_006439d8)[iVar13 >> 0x10 & DAT_0059bcb0];
        uVar15 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 1) =
             (&DAT_0061b2a0)
             [CONCAT31((int3)uVar19,
                       *(undefined1 *)((&DAT_006439d8)[uVar18] + (iVar21 >> 0x10 & DAT_0059bc38))) &
              0x1fff];
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        uVar18 = iVar20 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 2) =
             (&DAT_0061b2a0)[CONCAT31((int3)uVar19,*(undefined1 *)(iVar16 + uVar15)) & 0x1fff];
        iVar20 = iVar20 + iVar13;
        uVar19 = DAT_0059bc50 >> 8;
        iVar23 = iVar22 + DAT_0059bc00;
        iVar21 = iVar20 + DAT_0059bc08;
        iVar16 = (&DAT_006439d8)[iVar20 >> 0x10 & DAT_0059bcb0];
        uVar15 = iVar23 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 3) =
             (&DAT_0061b2a0)
             [CONCAT31((int3)uVar19,
                       *(undefined1 *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38))) &
              0x1fff];
        uVar19 = DAT_0059bc50 >> 8;
        iVar23 = iVar23 + DAT_0059bc00;
        uVar18 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 4) =
             (&DAT_0061b2a0)[CONCAT31((int3)uVar19,*(undefined1 *)(iVar16 + uVar15)) & 0x1fff];
        iVar21 = iVar21 + iVar13;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar23 + DAT_0059bc00;
        iVar20 = iVar21 + DAT_0059bc08;
        iVar16 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar15 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 5) =
             (&DAT_0061b2a0)
             [CONCAT31((int3)uVar19,
                       *(undefined1 *)((&DAT_006439d8)[uVar18] + (iVar23 >> 0x10 & DAT_0059bc38))) &
              0x1fff];
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        uVar18 = iVar20 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 6) =
             (&DAT_0061b2a0)[CONCAT31((int3)uVar19,*(undefined1 *)(iVar16 + uVar15)) & 0x1fff];
        iVar20 = iVar20 + iVar13;
        uVar19 = DAT_0059bc50 >> 8;
        iVar23 = iVar22 + DAT_0059bc00;
        iVar21 = iVar20 + DAT_0059bc08;
        iVar16 = (&DAT_006439d8)[iVar20 >> 0x10 & DAT_0059bcb0];
        uVar15 = iVar23 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 7) =
             (&DAT_0061b2a0)
             [CONCAT31((int3)uVar19,
                       *(undefined1 *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38))) &
              0x1fff];
        uVar19 = DAT_0059bc50 >> 8;
        iVar23 = iVar23 + DAT_0059bc00;
        uVar18 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 8) =
             (&DAT_0061b2a0)[CONCAT31((int3)uVar19,*(undefined1 *)(iVar16 + uVar15)) & 0x1fff];
        iVar21 = iVar21 + iVar13;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar23 + DAT_0059bc00;
        iVar20 = iVar21 + DAT_0059bc08;
        iVar16 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar15 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 9) =
             (&DAT_0061b2a0)
             [CONCAT31((int3)uVar19,
                       *(undefined1 *)((&DAT_006439d8)[uVar18] + (iVar23 >> 0x10 & DAT_0059bc38))) &
              0x1fff];
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        uVar18 = iVar20 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 10) =
             (&DAT_0061b2a0)[CONCAT31((int3)uVar19,*(undefined1 *)(iVar16 + uVar15)) & 0x1fff];
        iVar20 = iVar20 + iVar13;
        uVar19 = DAT_0059bc50 >> 8;
        iVar23 = iVar22 + DAT_0059bc00;
        iVar21 = iVar20 + DAT_0059bc08;
        iVar16 = (&DAT_006439d8)[iVar20 >> 0x10 & DAT_0059bcb0];
        uVar15 = iVar23 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 0xb) =
             (&DAT_0061b2a0)
             [CONCAT31((int3)uVar19,
                       *(undefined1 *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38))) &
              0x1fff];
        uVar19 = DAT_0059bc50 >> 8;
        iVar23 = iVar23 + DAT_0059bc00;
        uVar18 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar13 = DAT_0059bc08;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 0xc) =
             (&DAT_0061b2a0)[CONCAT31((int3)uVar19,*(undefined1 *)(iVar16 + uVar15)) & 0x1fff];
        iVar21 = iVar21 + iVar13;
        uVar19 = DAT_0059bc50 >> 8;
        iVar20 = iVar23 + DAT_0059bc00;
        iVar13 = iVar21 + DAT_0059bc08;
        iVar16 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar15 = iVar20 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 0xd) =
             (&DAT_0061b2a0)
             [CONCAT31((int3)uVar19,
                       *(undefined1 *)((&DAT_006439d8)[uVar18] + (iVar23 >> 0x10 & DAT_0059bc38))) &
              0x1fff];
        uVar19 = DAT_0059bc50 >> 8;
        iVar20 = iVar20 + DAT_0059bc00;
        uVar18 = iVar13 >> 0x10 & DAT_0059bcb0;
        DAT_0059bc50 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 0xe) =
             (&DAT_0061b2a0)[CONCAT31((int3)uVar19,*(undefined1 *)(iVar16 + uVar15)) & 0x1fff];
        iVar16 = DAT_0059bba0 + DAT_0059bc50;
        *(undefined1 *)((int)local_18 + 0xf) =
             (&DAT_0061b2a0)
             [CONCAT31((int3)(DAT_0059bc50 >> 8),
                       *(undefined1 *)((&DAT_006439d8)[uVar18] + (iVar20 >> 0x10 & DAT_0059bc38))) &
              0x1fff];
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,iVar16);
        local_18 = (int *)((int)local_18 + 0x10);
        _DAT_0059bc20 = (double)CONCAT44(DAT_0059bc20_4,iVar20);
        _DAT_0059bbb0 = (double)CONCAT44(DAT_0059bbb0_4,iVar13);
        local_20 = local_20 + -1;
      } while (local_20 != 0);
    }
  }
  return;
}


