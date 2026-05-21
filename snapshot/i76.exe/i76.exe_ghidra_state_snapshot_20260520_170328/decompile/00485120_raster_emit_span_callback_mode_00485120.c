/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode_00485120
 * Entry: 00485120
 * Signature: undefined __cdecl raster_emit_span_callback_mode_00485120(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Raster span callback target from
   draw table; exact mode still being separated by feature trace. */

void __cdecl raster_emit_span_callback_mode_00485120(int *param_1,int *param_2)

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
  int *piVar10;
  int iVar11;
  uint *puVar12;
  undefined1 *puVar13;
  int *piVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  float10 in_ST0;
  float10 fVar22;
  float10 fVar23;
  float10 fVar24;
  float10 fVar25;
  float10 fVar26;
  float10 fVar27;
  float10 fVar28;
  float10 in_ST1;
  float10 fVar29;
  float10 fVar30;
  undefined4 *local_18;
  int *local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar1 = *param_2;
  iVar2 = param_2[8];
  iVar3 = param_2[7];
  iVar4 = param_2[5];
  piVar5 = (int *)*param_1;
  if (piVar5 != DAT_006439c0) {
    iVar15 = *piVar5;
    piVar10 = piVar5 + 2;
    uVar16 = (piVar5[1] << 3) >> 3;
    piVar14 = (int *)(uVar16 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar5;
    if (piVar14 != (int *)0x0) {
      local_18 = &DAT_006439d8;
      local_14 = piVar14;
      do {
        *local_18 = piVar10;
        local_18 = local_18 + 1;
        piVar10 = (int *)((int)piVar10 + iVar15);
        local_14 = (int *)((int)local_14 - 1);
        param_2 = piVar14;
      } while (local_14 != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar16) {
      piVar14 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar16 - (int)param_2) + 3 >> 2);
      do {
        piVar14[-1] = (int)piVar10;
        *piVar14 = (int)piVar10 + iVar15;
        iVar11 = (int)piVar10 + iVar15 + iVar15;
        piVar14[1] = iVar11;
        iVar11 = iVar11 + iVar15;
        piVar14[2] = iVar11;
        piVar10 = (int *)(iVar11 + iVar15);
        piVar14 = piVar14 + 4;
        param_2 = (int *)((int)param_2 + -1);
      } while (param_2 != (int *)0x0);
    }
  }
  DAT_0059bc38 = *piVar5 - 1;
  DAT_0059bcb0 = ((piVar5[1] << 3) >> 3) - 1;
  piVar5 = (int *)param_1[0xc];
  *piVar5 = param_1[10];
  puVar12 = (uint *)(param_1[0xb] + 4);
  while (puVar12 != (uint *)(piVar5 + 1)) {
    uVar16 = *puVar12;
    puVar12 = puVar12 + 1;
    fVar7 = (float)(uVar16 >> 0x15);
    local_c = (float)param_1[0x10];
    fVar8 = (float)(uVar16 & 0x3ff);
    local_14 = (int *)param_1[0x12];
    local_10 = (float)param_1[0x14];
    fVar6 = local_c * fVar7 + fVar8 * (float)param_1[0x11] + (float)param_1[3];
    puVar13 = (undefined1 *)
              ((uVar16 & 0x3ff) * iVar1 + (uVar16 >> 0x15) + iVar2 * iVar1 + iVar3 + iVar4);
    uVar16 = (uVar16 >> 10 & 0x7ff) - 1;
    uVar19 = uVar16 & 0xf;
    iVar15 = (int)uVar16 >> 4;
    local_8 = (float)local_14 * fVar7 + fVar8 * (float)param_1[0x13] + (float)param_1[4];
    fVar7 = local_10 * fVar7 + fVar8 * (float)param_1[0x15] + (float)param_1[5];
    fVar9 = (float)uVar19;
    _DAT_0059bc50 = (double)((float)param_1[6] + (float)_DAT_004faf18);
    fVar8 = _DAT_004be778 / fVar7;
    _DAT_0059bc50 = (double)((ulonglong)_DAT_0059bc50 & 0xffffffff00001f00);
    _DAT_0059bbc8 = (double)(fVar8 * fVar6 + (float)_DAT_004faf18);
    _DAT_0059bd30 = (double)(fVar8 * local_8 + (float)_DAT_004faf18);
    param_2 = (int *)(fVar9 * local_c + fVar6);
    local_8 = fVar9 * (float)local_14 + local_8;
    local_18 = (undefined4 *)(fVar9 * local_10 + fVar7);
    _DAT_0059bc00 =
         (double)(((_DAT_004be778 / (float)local_18) * (float)param_2 - (float)DAT_0059bbc8) *
                  *(float *)(&DAT_004f9d38 + uVar19 * 4) + (float)_DAT_004faf18);
    _DAT_0059bc08 =
         (double)(((_DAT_004be778 / (float)local_18) * local_8 - (float)DAT_0059bd30) *
                  *(float *)(&DAT_004f9d38 + uVar19 * 4) + (float)_DAT_004faf18);
    fVar22 = in_ST0;
    if (0 < iVar15) {
      local_c = local_c * _DAT_004be774;
      local_14 = (int *)((float)local_14 * _DAT_004be774);
      local_10 = local_10 * _DAT_004be774;
      param_2 = (int *)((float)param_2 + local_c);
      local_8 = local_8 + (float)local_14;
      local_18 = (undefined4 *)((float)local_18 + local_10);
      fVar22 = (float10)_DAT_004fa494 / (float10)(float)local_18;
      in_ST1 = in_ST0;
    }
    DAT_0059bd38 = puVar13 + uVar19 + 1;
    iVar11 = DAT_0059bbc8;
    iVar20 = DAT_0059bd30;
    if ((int)DAT_0059bd38 - (int)puVar13 != 0) {
      if (((int)DAT_0059bd38 - (int)puVar13 & 1U) == 0) goto LAB_00485427;
      iVar20 = DAT_0059bd30 + DAT_0059bc08;
      iVar11 = DAT_0059bbc8 + DAT_0059bc00;
      *puVar13 = (&DAT_0061b2a0)
                 [DAT_0059bc50 +
                  (uint)*(byte *)((&DAT_006439d8)[DAT_0059bd30 >> 0x10 & DAT_0059bcb0] +
                                 (DAT_0059bbc8 >> 0x10 & DAT_0059bc38))];
      for (puVar13 = puVar13 + 1; puVar13 != DAT_0059bd38; puVar13 = puVar13 + 2) {
LAB_00485427:
        iVar21 = iVar20 + DAT_0059bc08;
        iVar18 = iVar11 + DAT_0059bc00;
        uVar16 = iVar21 >> 0x10 & DAT_0059bcb0;
        *puVar13 = (&DAT_0061b2a0)
                   [DAT_0059bc50 +
                    (uint)*(byte *)((&DAT_006439d8)[iVar20 >> 0x10 & DAT_0059bcb0] +
                                   (iVar11 >> 0x10 & DAT_0059bc38))];
        iVar20 = iVar21 + DAT_0059bc08;
        iVar11 = iVar18 + DAT_0059bc00;
        puVar13[1] = (&DAT_0061b2a0)
                     [DAT_0059bc50 +
                      (uint)*(byte *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38))];
      }
    }
    _DAT_0059bbc8 = (double)CONCAT44(DAT_0059bbc8_4,iVar11);
    _DAT_0059bd30 = (double)CONCAT44(DAT_0059bd30_4,iVar20);
    iVar15 = iVar15 + -1;
    in_ST0 = fVar22;
    if (-1 < iVar15) {
      _DAT_0059bbc8 = (double)CONCAT44(DAT_0059bbc8_4,iVar11 - DAT_0059bc00);
      _DAT_0059bd30 = (double)CONCAT44(DAT_0059bd30_4,iVar20 - DAT_0059bc08);
      fVar23 = (float10)(iVar11 - DAT_0059bc00);
      fVar24 = (float10)local_8;
      in_ST0 = (float10)_DAT_0059bd30 - (float10)_DAT_004faf18;
      fVar28 = (float10)(float)local_18;
      fVar29 = (float10)(float)param_2;
      do {
        fVar25 = (fVar22 * fVar29 - fVar23) + (float10)_DAT_004fa490;
        fVar22 = (fVar22 * fVar24 - in_ST0) + (float10)_DAT_004fa490;
        fVar26 = fVar24 + (float10)(float)local_14;
        _DAT_0059bc08 = (double)fVar22;
        _DAT_0059bc00 = (double)fVar25;
        fVar30 = (fVar22 - (float10)_DAT_004fa490) + in_ST0;
        fVar22 = (fVar25 - (float10)_DAT_004fa490) + fVar23;
        fVar25 = fVar29;
        fVar27 = fVar26;
        fVar24 = fVar22;
        fVar23 = fVar30;
        in_ST0 = in_ST1;
        if (iVar15 != 0) {
          fVar25 = fVar28 + (float10)local_10;
          fVar27 = fVar29 + (float10)local_c;
          fVar28 = (float10)_DAT_004fa494 / fVar25;
          fVar24 = fVar26;
          fVar23 = fVar22;
          in_ST0 = fVar30;
        }
        iVar11 = DAT_0059bc08;
        iVar20 = DAT_0059bd30 + DAT_0059bc08 + DAT_0059bc08;
        iVar18 = DAT_0059bbc8 + DAT_0059bc00 + DAT_0059bc00;
        uVar16 = iVar20 >> 0x10 & DAT_0059bcb0;
        *puVar13 = (&DAT_0061b2a0)
                   [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                             *(undefined1 *)
                              ((&DAT_006439d8)[DAT_0059bd30 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                              (DAT_0059bbc8 + DAT_0059bc00 >> 0x10 & DAT_0059bc38)))];
        iVar20 = iVar20 + iVar11;
        iVar21 = iVar18 + DAT_0059bc00;
        uVar19 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[1] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38)))];
        iVar11 = DAT_0059bc08;
        iVar20 = iVar20 + DAT_0059bc08;
        iVar18 = iVar21 + DAT_0059bc00;
        uVar16 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[2] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar19] + (iVar21 >> 0x10 & DAT_0059bc38)))];
        iVar20 = iVar20 + iVar11;
        iVar21 = iVar18 + DAT_0059bc00;
        uVar19 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[3] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38)))];
        iVar11 = DAT_0059bc08;
        iVar20 = iVar20 + DAT_0059bc08;
        iVar18 = iVar21 + DAT_0059bc00;
        uVar17 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[4] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar19] + (iVar21 >> 0x10 & DAT_0059bc38)))];
        iVar20 = iVar20 + iVar11;
        iVar21 = iVar18 + DAT_0059bc00;
        uVar16 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[5] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar17] + (iVar18 >> 0x10 & DAT_0059bc38)))];
        iVar11 = DAT_0059bc08;
        iVar20 = iVar20 + DAT_0059bc08;
        iVar18 = iVar21 + DAT_0059bc00;
        uVar19 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[6] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar16] + (iVar21 >> 0x10 & DAT_0059bc38)))];
        iVar20 = iVar20 + iVar11;
        iVar21 = iVar18 + DAT_0059bc00;
        uVar17 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[7] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar19] + (iVar18 >> 0x10 & DAT_0059bc38)))];
        iVar11 = DAT_0059bc08;
        iVar20 = iVar20 + DAT_0059bc08;
        iVar18 = iVar21 + DAT_0059bc00;
        uVar16 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[8] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar17] + (iVar21 >> 0x10 & DAT_0059bc38)))];
        iVar20 = iVar20 + iVar11;
        iVar21 = iVar18 + DAT_0059bc00;
        uVar19 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[9] = (&DAT_0061b2a0)
                     [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                               *(undefined1 *)
                                ((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38)))];
        iVar11 = DAT_0059bc08;
        iVar20 = iVar20 + DAT_0059bc08;
        iVar18 = iVar21 + DAT_0059bc00;
        uVar17 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[10] = (&DAT_0061b2a0)
                      [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                                *(undefined1 *)
                                 ((&DAT_006439d8)[uVar19] + (iVar21 >> 0x10 & DAT_0059bc38)))];
        iVar20 = iVar20 + iVar11;
        iVar21 = iVar18 + DAT_0059bc00;
        uVar16 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[0xb] = (&DAT_0061b2a0)
                       [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                                 *(undefined1 *)
                                  ((&DAT_006439d8)[uVar17] + (iVar18 >> 0x10 & DAT_0059bc38)))];
        iVar11 = DAT_0059bc08;
        iVar20 = iVar20 + DAT_0059bc08;
        iVar18 = iVar21 + DAT_0059bc00;
        uVar19 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[0xc] = (&DAT_0061b2a0)
                       [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                                 *(undefined1 *)
                                  ((&DAT_006439d8)[uVar16] + (iVar21 >> 0x10 & DAT_0059bc38)))];
        iVar20 = iVar20 + iVar11;
        iVar11 = iVar18 + DAT_0059bc00;
        uVar17 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[0xd] = (&DAT_0061b2a0)
                       [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                                 *(undefined1 *)
                                  ((&DAT_006439d8)[uVar19] + (iVar18 >> 0x10 & DAT_0059bc38)))];
        iVar20 = iVar20 + DAT_0059bc08;
        iVar18 = iVar11 + DAT_0059bc00;
        uVar16 = iVar20 >> 0x10 & DAT_0059bcb0;
        puVar13[0xe] = (&DAT_0061b2a0)
                       [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                                 *(undefined1 *)
                                  ((&DAT_006439d8)[uVar17] + (iVar11 >> 0x10 & DAT_0059bc38)))];
        puVar13[0xf] = (&DAT_0061b2a0)
                       [CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),
                                 *(undefined1 *)
                                  ((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38)))];
        puVar13 = puVar13 + 0x10;
        _DAT_0059bbc8 = (double)CONCAT44(DAT_0059bbc8_4,iVar18);
        _DAT_0059bd30 = (double)CONCAT44(DAT_0059bd30_4,iVar20);
        iVar15 = iVar15 + -1;
        fVar22 = fVar28;
        fVar28 = fVar25;
        fVar29 = fVar27;
      } while (-1 < iVar15);
    }
  }
  return;
}


