/*
 * Program: i76.exe
 * Function: raster_emit_textured_lit_spans_variant_d
 * Entry: 00481e80
 * Signature: undefined __cdecl raster_emit_textured_lit_spans_variant_d(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe geo raster span family renames v38; confidence=medium] Affine textured+lit span
   callback variant D. */

void __cdecl raster_emit_textured_lit_spans_variant_d(int *param_1,int *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int *piVar11;
  int iVar12;
  uint *puVar13;
  byte *pbVar14;
  int iVar15;
  int *piVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
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
  
  iVar2 = *param_2;
  iVar3 = param_2[8];
  iVar4 = param_2[5];
  iVar5 = param_2[7];
  piVar6 = (int *)*param_1;
  if (piVar6 != DAT_006439c0) {
    iVar15 = *piVar6;
    piVar11 = piVar6 + 2;
    uVar18 = (piVar6[1] << 3) >> 3;
    piVar16 = (int *)(uVar18 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar6;
    if (piVar16 != (int *)0x0) {
      local_18 = &DAT_006439d8;
      local_14 = piVar16;
      do {
        *local_18 = piVar11;
        local_18 = local_18 + 1;
        piVar11 = (int *)((int)piVar11 + iVar15);
        local_14 = (int *)((int)local_14 - 1);
        param_2 = piVar16;
      } while (local_14 != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar18) {
      piVar16 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar18 - (int)param_2) + 3 >> 2);
      do {
        piVar16[-1] = (int)piVar11;
        *piVar16 = (int)piVar11 + iVar15;
        iVar12 = (int)piVar11 + iVar15 + iVar15;
        piVar16[1] = iVar12;
        iVar12 = iVar12 + iVar15;
        piVar16[2] = iVar12;
        piVar11 = (int *)(iVar12 + iVar15);
        piVar16 = piVar16 + 4;
        param_2 = (int *)((int)param_2 + -1);
      } while (param_2 != (int *)0x0);
    }
  }
  DAT_0059bc38 = *piVar6 - 1;
  DAT_0059bcb0 = ((piVar6[1] << 3) >> 3) - 1;
  piVar6 = (int *)param_1[0xc];
  *piVar6 = param_1[10];
  puVar13 = (uint *)(param_1[0xb] + 4);
  while (puVar13 != (uint *)(piVar6 + 1)) {
    uVar18 = *puVar13;
    puVar13 = puVar13 + 1;
    fVar8 = (float)(uVar18 >> 0x15);
    local_c = (float)param_1[0x10];
    fVar9 = (float)(uVar18 & 0x3ff);
    local_14 = (int *)param_1[0x12];
    local_10 = (float)param_1[0x14];
    fVar7 = local_c * fVar8 + fVar9 * (float)param_1[0x11] + (float)param_1[3];
    pbVar14 = (byte *)((uVar18 & 0x3ff) * iVar2 + (uVar18 >> 0x15) + iVar3 * iVar2 + iVar4 + iVar5);
    local_8 = (float)local_14 * fVar8 + fVar9 * (float)param_1[0x13] + (float)param_1[4];
    fVar8 = local_10 * fVar8 + fVar9 * (float)param_1[0x15] + (float)param_1[5];
    uVar18 = (uVar18 >> 10 & 0x7ff) - 1;
    uVar17 = uVar18 & 0xf;
    fVar10 = (float)uVar17;
    fVar9 = _DAT_004be778 / fVar8;
    iVar15 = (int)uVar18 >> 4;
    _DAT_0059bd20 = (double)(fVar9 * fVar7 + (float)_DAT_004faf18);
    _DAT_0059bc48 = (double)(fVar9 * local_8 + (float)_DAT_004faf18);
    param_2 = (int *)(fVar10 * local_c + fVar7);
    local_8 = fVar10 * (float)local_14 + local_8;
    local_18 = (undefined4 *)(fVar10 * local_10 + fVar8);
    _DAT_0059bc00 =
         (double)(((_DAT_004be778 / (float)local_18) * (float)param_2 - (float)DAT_0059bd20) *
                  *(float *)(&DAT_004f9d38 + uVar17 * 4) + (float)_DAT_004faf18);
    _DAT_0059bc08 =
         (double)(((_DAT_004be778 / (float)local_18) * local_8 - (float)DAT_0059bc48) *
                  *(float *)(&DAT_004f9d38 + uVar17 * 4) + (float)_DAT_004faf18);
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
    DAT_0059bd38 = pbVar14 + uVar17 + 1;
    iVar12 = DAT_0059bd20;
    iVar19 = DAT_0059bc48;
    if (pbVar14 != DAT_0059bd38) {
      do {
        uVar18 = iVar19 >> 0x10;
        uVar17 = iVar12 >> 0x10;
        iVar19 = iVar19 + DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc00;
        *pbVar14 = *(byte *)((int)&g_palette_blend_table_c +
                            (uint)*pbVar14 +
                            (uint)*(byte *)((&DAT_006439d8)[uVar18 & DAT_0059bcb0] +
                                           (uVar17 & DAT_0059bc38)) * 0x100);
        pbVar14 = pbVar14 + 1;
      } while (pbVar14 != DAT_0059bd38);
    }
    _DAT_0059bd20 = (double)CONCAT44(DAT_0059bd20_4,iVar12);
    _DAT_0059bc48 = (double)CONCAT44(DAT_0059bc48_4,iVar19);
    iVar15 = iVar15 + -1;
    in_ST0 = fVar22;
    if (-1 < iVar15) {
      _DAT_0059bd20 = (double)CONCAT44(DAT_0059bd20_4,iVar12 - DAT_0059bc00);
      _DAT_0059bc48 = (double)CONCAT44(DAT_0059bc48_4,iVar19 - DAT_0059bc08);
      fVar23 = (float10)(iVar12 - DAT_0059bc00);
      fVar24 = (float10)local_8;
      in_ST0 = (float10)_DAT_0059bc48 - (float10)_DAT_004faf18;
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
        iVar12 = DAT_0059bc08;
        iVar19 = DAT_0059bc48 + DAT_0059bc08 + DAT_0059bc08;
        iVar20 = DAT_0059bd20 + DAT_0059bc00 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[DAT_0059bc48 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                         (DAT_0059bd20 + DAT_0059bc00 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          *pbVar14 = bVar1;
        }
        iVar19 = iVar19 + iVar12;
        iVar12 = iVar20 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar20 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[1] = bVar1;
        }
        iVar20 = DAT_0059bc08;
        iVar19 = iVar19 + DAT_0059bc08;
        iVar21 = iVar12 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar12 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[2] = bVar1;
        }
        iVar19 = iVar19 + iVar20;
        iVar12 = iVar21 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar21 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[3] = bVar1;
        }
        iVar20 = DAT_0059bc08;
        iVar19 = iVar19 + DAT_0059bc08;
        iVar21 = iVar12 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar12 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[4] = bVar1;
        }
        iVar19 = iVar19 + iVar20;
        iVar12 = iVar21 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar21 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[5] = bVar1;
        }
        iVar20 = DAT_0059bc08;
        iVar19 = iVar19 + DAT_0059bc08;
        iVar21 = iVar12 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar12 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[6] = bVar1;
        }
        iVar19 = iVar19 + iVar20;
        iVar12 = iVar21 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar21 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[7] = bVar1;
        }
        iVar20 = DAT_0059bc08;
        iVar19 = iVar19 + DAT_0059bc08;
        iVar21 = iVar12 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar12 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[8] = bVar1;
        }
        iVar19 = iVar19 + iVar20;
        iVar12 = iVar21 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar21 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[9] = bVar1;
        }
        iVar20 = DAT_0059bc08;
        iVar19 = iVar19 + DAT_0059bc08;
        iVar21 = iVar12 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar12 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[10] = bVar1;
        }
        iVar19 = iVar19 + iVar20;
        iVar12 = iVar21 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar21 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[0xb] = bVar1;
        }
        iVar20 = DAT_0059bc08;
        iVar19 = iVar19 + DAT_0059bc08;
        iVar21 = iVar12 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar12 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[0xc] = bVar1;
        }
        iVar19 = iVar19 + iVar20;
        iVar12 = iVar21 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar21 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          pbVar14[0xd] = bVar1;
        }
        iVar19 = iVar19 + DAT_0059bc08;
        iVar20 = iVar12 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + (iVar12 >> 0x10 & DAT_0059bc38));
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        uVar17 = iVar20 >> 0x10 & DAT_0059bc38;
        if (bVar1 != 0xff) {
          pbVar14[0xe] = bVar1;
        }
        bVar1 = *(byte *)((&DAT_006439d8)[uVar18] + uVar17);
        if (bVar1 != 0xff) {
          pbVar14[0xf] = bVar1;
        }
        pbVar14 = pbVar14 + 0x10;
        _DAT_0059bd20 = (double)CONCAT44(DAT_0059bd20_4,iVar20);
        _DAT_0059bc48 = (double)CONCAT44(DAT_0059bc48_4,iVar19);
        iVar15 = iVar15 + -1;
        fVar22 = fVar28;
        fVar28 = fVar25;
        fVar29 = fVar27;
      } while (-1 < iVar15);
    }
  }
  return;
}


