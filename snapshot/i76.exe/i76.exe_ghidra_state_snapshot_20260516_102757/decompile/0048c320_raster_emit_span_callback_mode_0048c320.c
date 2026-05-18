/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode_0048c320
 * Entry: 0048c320
 * Signature: undefined __cdecl raster_emit_span_callback_mode_0048c320(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Raster span callback target from
   draw table; exact mode still being separated by feature trace. */

void __cdecl raster_emit_span_callback_mode_0048c320(int *param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  ulonglong uVar10;
  uint uVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
  uint *puVar15;
  undefined1 *puVar16;
  int *piVar17;
  uint uVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  uint uVar23;
  float10 in_ST0;
  float10 fVar24;
  float10 fVar25;
  float10 fVar26;
  float10 fVar27;
  float10 fVar28;
  float10 fVar29;
  float10 fVar30;
  float10 fVar31;
  float10 fVar32;
  float10 fVar33;
  float local_28;
  undefined4 *local_24;
  int *local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar2 = *param_2;
  iVar3 = param_2[8];
  iVar4 = param_2[5];
  iVar5 = param_2[7];
  piVar6 = (int *)*param_1;
  if (piVar6 != DAT_006439c0) {
    iVar12 = *piVar6;
    piVar13 = piVar6 + 2;
    uVar19 = (piVar6[1] << 3) >> 3;
    piVar17 = (int *)(uVar19 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar6;
    if (piVar17 != (int *)0x0) {
      local_24 = &DAT_006439d8;
      local_20 = piVar17;
      do {
        *local_24 = piVar13;
        local_24 = local_24 + 1;
        piVar13 = (int *)((int)piVar13 + iVar12);
        local_20 = (int *)((int)local_20 - 1);
        param_2 = piVar17;
      } while (local_20 != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar19) {
      piVar17 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar19 - (int)param_2) + 3 >> 2);
      do {
        piVar17[-1] = (int)piVar13;
        *piVar17 = (int)piVar13 + iVar12;
        iVar14 = (int)piVar13 + iVar12 + iVar12;
        piVar17[1] = iVar14;
        iVar14 = iVar14 + iVar12;
        piVar17[2] = iVar14;
        piVar13 = (int *)(iVar14 + iVar12);
        piVar17 = piVar17 + 4;
        param_2 = (int *)((int)param_2 + -1);
      } while (param_2 != (int *)0x0);
    }
  }
  DAT_0059bc38 = *piVar6 - 1;
  DAT_0059bcb0 = ((piVar6[1] << 3) >> 3) - 1;
  piVar6 = (int *)param_1[0xc];
  *piVar6 = param_1[10];
  puVar15 = (uint *)(param_1[0xb] + 4);
  while (puVar15 != (uint *)(piVar6 + 1)) {
    uVar19 = *puVar15;
    puVar15 = puVar15 + 1;
    fVar7 = (float)(uVar19 >> 0x15);
    local_14 = (float)param_1[0x10];
    fVar9 = (float)(uVar19 & 0x3ff);
    local_1c = (float)param_1[0x12];
    local_18 = (float)param_1[0x14];
    local_c = local_14 * fVar7 + fVar9 * (float)param_1[0x11] + (float)param_1[3];
    local_8 = (float)param_1[0x16];
    puVar16 = (undefined1 *)
              ((uVar19 & 0x3ff) * iVar2 + (uVar19 >> 0x15) + iVar3 * iVar2 + iVar4 + iVar5);
    uVar19 = (uVar19 >> 10 & 0x7ff) - 1;
    uVar23 = uVar19 & 0xf;
    local_10 = local_1c * fVar7 + fVar9 * (float)param_1[0x13] + (float)param_1[4];
    fVar8 = local_18 * fVar7 + fVar9 * (float)param_1[0x15] + (float)param_1[5];
    local_28 = local_8 * fVar7 + fVar9 * (float)param_1[0x17] + (float)param_1[6];
    fVar7 = (float)uVar23;
    _DAT_0059bc50 = (double)(local_28 + (float)_DAT_004faf18);
    local_28 = fVar7 * local_8 + local_28;
    _DAT_0059bba0 = (double)(local_8 + (float)_DAT_004faf18);
    local_8 = local_8 * _DAT_004be774;
    uVar18 = DAT_0059bc50;
    if (((ulonglong)_DAT_0059bc50 & 0xffffe000) != 0) {
      uVar18 = ~DAT_0059bc50 >> 0x13;
      _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar18);
      local_28 = (float)uVar18;
    }
    uVar11 = DAT_0059bba0 * uVar19 + uVar18;
    if ((uVar11 & 0xffffe000) != 0) {
      iVar12 = (int)((~uVar11 >> 0x13) - uVar18) / (int)uVar19;
      _DAT_0059bba0 = (double)CONCAT44(DAT_0059bba0_4,iVar12);
      local_8 = (float)(iVar12 << 4);
    }
    fVar9 = _DAT_004be778 / fVar8;
    _DAT_0059bc90 = (double)(fVar9 * local_c + (float)_DAT_004faf18);
    _DAT_0059bc78 = (double)(fVar9 * local_10 + (float)_DAT_004faf18);
    local_c = fVar7 * local_14 + local_c;
    local_10 = fVar7 * local_1c + local_10;
    param_2 = (int *)(fVar7 * local_18 + fVar8);
    _DAT_0059bc00 =
         (double)(((_DAT_004be778 / (float)param_2) * local_c - (float)DAT_0059bc90) *
                  *(float *)(&DAT_004f9d38 + uVar23 * 4) + (float)_DAT_004faf18);
    _DAT_0059bc08 =
         (double)(((_DAT_004be778 / (float)param_2) * local_10 - (float)DAT_0059bc78) *
                  *(float *)(&DAT_004f9d38 + uVar23 * 4) + (float)_DAT_004faf18);
    if (0 < (int)uVar19 >> 4) {
      local_14 = local_14 * _DAT_004be774;
      local_1c = local_1c * _DAT_004be774;
      local_18 = local_18 * _DAT_004be774;
      local_c = local_c + local_14;
      local_10 = local_10 + local_1c;
      param_2 = (int *)((float)param_2 + local_18);
      in_ST0 = (float10)_DAT_004fa494 / (float10)(float)param_2;
    }
    DAT_0059bd38 = puVar16 + uVar23 + 1;
    iVar12 = DAT_0059bc90;
    iVar14 = DAT_0059bc78;
    if (puVar16 != DAT_0059bd38) {
      do {
        uVar18 = iVar14 >> 0x10;
        uVar23 = iVar12 >> 0x10;
        iVar14 = iVar14 + DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc00;
        uVar23 = (uint)*(byte *)((&DAT_006439d8)[uVar18 & DAT_0059bcb0] + (uVar23 & DAT_0059bc38));
        uVar18 = DAT_0059bc50;
        if (uVar23 != 0xff) {
          *puVar16 = (&DAT_0061b2a0)[(DAT_0059bc50 & 0x1f00) + uVar23];
        }
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar18 + DAT_0059bba0);
        puVar16 = puVar16 + 1;
      } while (puVar16 != DAT_0059bd38);
    }
    _DAT_0059bc90 = (double)CONCAT44(DAT_0059bc90_4,iVar12);
    _DAT_0059bc78 = (double)CONCAT44(DAT_0059bc78_4,iVar14);
    iVar20 = ((int)uVar19 >> 4) + -1;
    if (-1 < iVar20) {
      _DAT_0059bc90 = (double)CONCAT44(DAT_0059bc90_4,iVar12 - DAT_0059bc00);
      _DAT_0059bc78 = (double)CONCAT44(DAT_0059bc78_4,iVar14 - DAT_0059bc08);
      fVar24 = (float10)(iVar12 - DAT_0059bc00);
      fVar25 = (float10)local_10;
      fVar26 = (float10)_DAT_0059bc78 - (float10)_DAT_004faf18;
      fVar28 = in_ST0;
      fVar31 = (float10)(float)param_2;
      fVar32 = (float10)local_c;
      do {
        fVar7 = local_28 + (float)_DAT_004faf18;
        local_28 = local_28 + local_8;
        _DAT_0059bc50 = (double)fVar7;
        fVar27 = (fVar28 * fVar32 - fVar24) + (float10)_DAT_004fa490;
        fVar28 = (fVar28 * fVar25 - fVar26) + (float10)_DAT_004fa490;
        fVar29 = fVar25 + (float10)local_1c;
        _DAT_0059bc08 = (double)fVar28;
        _DAT_0059bc00 = (double)fVar27;
        fVar33 = (fVar28 - (float10)_DAT_004fa490) + fVar26;
        fVar28 = (fVar27 - (float10)_DAT_004fa490) + fVar24;
        fVar27 = fVar32;
        fVar30 = fVar29;
        fVar25 = fVar28;
        fVar24 = fVar33;
        if (iVar20 != 0) {
          fVar27 = fVar31 + (float10)local_18;
          fVar30 = fVar32 + (float10)local_14;
          fVar31 = (float10)_DAT_004fa494 / fVar27;
          fVar25 = fVar29;
          fVar24 = fVar28;
          fVar26 = fVar33;
        }
        iVar12 = DAT_0059bc08;
        iVar14 = DAT_0059bc78 + DAT_0059bc08 + DAT_0059bc08;
        iVar22 = DAT_0059bc90 + DAT_0059bc00 + DAT_0059bc00;
        uVar19 = DAT_0059bba0 + DAT_0059bc50;
        uVar10 = (ulonglong)_DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[DAT_0059bc78 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                         (DAT_0059bc90 + DAT_0059bc00 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar14 >> 0x10 & DAT_0059bcb0;
        DAT_0059bc50 = uVar19;
        if (cVar1 != -1) {
          *puVar16 = (&DAT_0061b2a0)[CONCAT31((int3)uVar10,cVar1) & 0x1fff];
        }
        iVar14 = iVar14 + iVar12;
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar21 = iVar14 + DAT_0059bc08;
        iVar12 = (&DAT_006439d8)[iVar14 >> 0x10 & DAT_0059bcb0];
        uVar18 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[1] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar12 + uVar18);
        uVar18 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[2] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        iVar21 = iVar21 + iVar12;
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar14 = iVar21 + DAT_0059bc08;
        iVar12 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar18 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[3] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar12 + uVar18);
        uVar18 = iVar14 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[4] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        iVar14 = iVar14 + iVar12;
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar21 = iVar14 + DAT_0059bc08;
        iVar12 = (&DAT_006439d8)[iVar14 >> 0x10 & DAT_0059bcb0];
        uVar18 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[5] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar12 + uVar18);
        uVar18 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[6] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        iVar21 = iVar21 + iVar12;
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar14 = iVar21 + DAT_0059bc08;
        iVar12 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar18 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[7] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar12 + uVar18);
        uVar18 = iVar14 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[8] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        iVar14 = iVar14 + iVar12;
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar21 = iVar14 + DAT_0059bc08;
        iVar12 = (&DAT_006439d8)[iVar14 >> 0x10 & DAT_0059bcb0];
        uVar18 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[9] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar12 + uVar18);
        uVar18 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[10] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        iVar21 = iVar21 + iVar12;
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar14 = iVar21 + DAT_0059bc08;
        iVar12 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar18 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[0xb] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar12 + uVar18);
        uVar18 = iVar14 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[0xc] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        iVar14 = iVar14 + iVar12;
        uVar23 = DAT_0059bba0 + DAT_0059bc50;
        uVar19 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar21 = iVar14 + DAT_0059bc08;
        iVar12 = (&DAT_006439d8)[iVar14 >> 0x10 & DAT_0059bcb0];
        uVar18 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar23;
        if (cVar1 != -1) {
          puVar16[0xd] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        uVar19 = DAT_0059bc50 >> 8;
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,DAT_0059bba0 + DAT_0059bc50);
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar12 + uVar18);
        uVar18 = iVar21 >> 0x10 & DAT_0059bcb0;
        if (cVar1 != -1) {
          puVar16[0xe] = (&DAT_0061b2a0)[CONCAT31((int3)uVar19,cVar1) & 0x1fff];
        }
        iVar12 = DAT_0059bba0 + DAT_0059bc50;
        cVar1 = *(char *)((&DAT_006439d8)[uVar18] + (iVar22 >> 0x10 & DAT_0059bc38));
        if (cVar1 != -1) {
          puVar16[0xf] = (&DAT_0061b2a0)
                         [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),cVar1) & 0x1fff];
        }
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,iVar12);
        puVar16 = puVar16 + 0x10;
        _DAT_0059bc90 = (double)CONCAT44(DAT_0059bc90_4,iVar22);
        _DAT_0059bc78 = (double)CONCAT44(DAT_0059bc78_4,iVar21);
        iVar20 = iVar20 + -1;
        fVar28 = fVar31;
        fVar31 = fVar27;
        fVar32 = fVar30;
        in_ST0 = fVar26;
      } while (-1 < iVar20);
    }
  }
  return;
}


