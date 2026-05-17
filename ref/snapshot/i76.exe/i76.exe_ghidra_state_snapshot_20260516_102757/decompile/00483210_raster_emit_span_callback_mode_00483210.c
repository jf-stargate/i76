/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode_00483210
 * Entry: 00483210
 * Signature: undefined __cdecl raster_emit_span_callback_mode_00483210(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Raster span callback target from
   draw table; exact mode still being separated by feature trace. */

void __cdecl raster_emit_span_callback_mode_00483210(int *param_1,int *param_2)

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
  byte *pbVar13;
  int iVar14;
  int *piVar15;
  uint uVar16;
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
  
  iVar1 = *param_2;
  iVar2 = param_2[8];
  iVar3 = param_2[7];
  iVar4 = param_2[5];
  piVar5 = (int *)*param_1;
  if (piVar5 != DAT_006439c0) {
    iVar14 = *piVar5;
    piVar10 = piVar5 + 2;
    uVar17 = (piVar5[1] << 3) >> 3;
    piVar15 = (int *)(uVar17 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar5;
    if (piVar15 != (int *)0x0) {
      local_18 = &DAT_006439d8;
      local_14 = piVar15;
      do {
        *local_18 = piVar10;
        local_18 = local_18 + 1;
        piVar10 = (int *)((int)piVar10 + iVar14);
        local_14 = (int *)((int)local_14 - 1);
        param_2 = piVar15;
      } while (local_14 != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar17) {
      piVar15 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar17 - (int)param_2) + 3 >> 2);
      do {
        piVar15[-1] = (int)piVar10;
        *piVar15 = (int)piVar10 + iVar14;
        iVar11 = (int)piVar10 + iVar14 + iVar14;
        piVar15[1] = iVar11;
        iVar11 = iVar11 + iVar14;
        piVar15[2] = iVar11;
        piVar10 = (int *)(iVar11 + iVar14);
        piVar15 = piVar15 + 4;
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
    uVar17 = *puVar12;
    puVar12 = puVar12 + 1;
    fVar7 = (float)(uVar17 >> 0x15);
    local_c = (float)param_1[0x10];
    fVar8 = (float)(uVar17 & 0x3ff);
    local_14 = (int *)param_1[0x12];
    local_10 = (float)param_1[0x14];
    fVar6 = local_c * fVar7 + fVar8 * (float)param_1[0x11] + (float)param_1[3];
    pbVar13 = (byte *)((uVar17 & 0x3ff) * iVar1 + (uVar17 >> 0x15) + iVar2 * iVar1 + iVar3 + iVar4);
    local_8 = (float)local_14 * fVar7 + fVar8 * (float)param_1[0x13] + (float)param_1[4];
    fVar7 = local_10 * fVar7 + fVar8 * (float)param_1[0x15] + (float)param_1[5];
    uVar17 = (uVar17 >> 10 & 0x7ff) - 1;
    uVar16 = uVar17 & 0xf;
    fVar9 = (float)uVar16;
    fVar8 = _DAT_004be778 / fVar7;
    iVar14 = (int)uVar17 >> 4;
    _DAT_0059bc18 = (double)(fVar8 * fVar6 + (float)_DAT_004faf18);
    _DAT_0059bbf0 = (double)(fVar8 * local_8 + (float)_DAT_004faf18);
    param_2 = (int *)(fVar9 * local_c + fVar6);
    local_8 = fVar9 * (float)local_14 + local_8;
    local_18 = (undefined4 *)(fVar9 * local_10 + fVar7);
    _DAT_0059bc00 =
         (double)(((_DAT_004be778 / (float)local_18) * (float)param_2 - (float)DAT_0059bc18) *
                  *(float *)(&DAT_004f9d38 + uVar16 * 4) + (float)_DAT_004faf18);
    _DAT_0059bc08 =
         (double)(((_DAT_004be778 / (float)local_18) * local_8 - (float)DAT_0059bbf0) *
                  *(float *)(&DAT_004f9d38 + uVar16 * 4) + (float)_DAT_004faf18);
    fVar22 = in_ST0;
    if (0 < iVar14) {
      local_c = local_c * _DAT_004be774;
      local_14 = (int *)((float)local_14 * _DAT_004be774);
      local_10 = local_10 * _DAT_004be774;
      param_2 = (int *)((float)param_2 + local_c);
      local_8 = local_8 + (float)local_14;
      local_18 = (undefined4 *)((float)local_18 + local_10);
      fVar22 = (float10)_DAT_004fa494 / (float10)(float)local_18;
      in_ST1 = in_ST0;
    }
    DAT_0059bd38 = pbVar13 + uVar16 + 1;
    iVar11 = DAT_0059bc18;
    iVar19 = DAT_0059bbf0;
    if (pbVar13 != DAT_0059bd38) {
      do {
        uVar17 = iVar19 >> 0x10;
        uVar16 = iVar11 >> 0x10;
        iVar19 = iVar19 + DAT_0059bc08;
        iVar11 = iVar11 + DAT_0059bc00;
        *pbVar13 = *(byte *)((int)&g_palette_blend_table_a +
                            (uint)*pbVar13 +
                            (uint)*(byte *)((&DAT_006439d8)[uVar17 & DAT_0059bcb0] +
                                           (uVar16 & DAT_0059bc38)) * 0x100);
        pbVar13 = pbVar13 + 1;
      } while (pbVar13 != DAT_0059bd38);
    }
    _DAT_0059bc18 = (double)CONCAT44(DAT_0059bc18_4,iVar11);
    _DAT_0059bbf0 = (double)CONCAT44(DAT_0059bbf0_4,iVar19);
    iVar14 = iVar14 + -1;
    in_ST0 = fVar22;
    if (-1 < iVar14) {
      _DAT_0059bc18 = (double)CONCAT44(DAT_0059bc18_4,iVar11 - DAT_0059bc00);
      _DAT_0059bbf0 = (double)CONCAT44(DAT_0059bbf0_4,iVar19 - DAT_0059bc08);
      fVar23 = (float10)(iVar11 - DAT_0059bc00);
      fVar24 = (float10)local_8;
      in_ST0 = (float10)_DAT_0059bbf0 - (float10)_DAT_004faf18;
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
        if (iVar14 != 0) {
          fVar25 = fVar28 + (float10)local_10;
          fVar27 = fVar29 + (float10)local_c;
          fVar28 = (float10)_DAT_004fa494 / fVar25;
          fVar24 = fVar26;
          fVar23 = fVar22;
          in_ST0 = fVar30;
        }
        iVar11 = DAT_0059bc08;
        iVar19 = DAT_0059bbf0 + DAT_0059bc08 + DAT_0059bc08;
        iVar20 = DAT_0059bc18 + DAT_0059bc00 + DAT_0059bc00;
        uVar17 = iVar19 >> 0x10 & DAT_0059bcb0;
        *pbVar13 = *(byte *)((int)&g_palette_blend_table_a +
                            (uint)CONCAT11(*(undefined1 *)
                                            ((&DAT_006439d8)
                                             [DAT_0059bbf0 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                                            (DAT_0059bc18 + DAT_0059bc00 >> 0x10 & DAT_0059bc38)),
                                           *pbVar13));
        iVar19 = iVar19 + iVar11;
        iVar21 = iVar20 + DAT_0059bc00;
        uVar16 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[1] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar17] +
                                              (iVar20 >> 0x10 & DAT_0059bc38)),pbVar13[1]));
        iVar19 = iVar19 + iVar11;
        iVar20 = iVar21 + DAT_0059bc00;
        uVar17 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[2] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar16] +
                                              (iVar21 >> 0x10 & DAT_0059bc38)),pbVar13[2]));
        iVar19 = iVar19 + iVar11;
        iVar21 = iVar20 + DAT_0059bc00;
        uVar16 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[3] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar17] +
                                              (iVar20 >> 0x10 & DAT_0059bc38)),pbVar13[3]));
        iVar19 = iVar19 + iVar11;
        iVar20 = iVar21 + DAT_0059bc00;
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[4] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar16] +
                                              (iVar21 >> 0x10 & DAT_0059bc38)),pbVar13[4]));
        iVar19 = iVar19 + iVar11;
        iVar21 = iVar20 + DAT_0059bc00;
        uVar17 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[5] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar18] +
                                              (iVar20 >> 0x10 & DAT_0059bc38)),pbVar13[5]));
        iVar19 = iVar19 + iVar11;
        iVar20 = iVar21 + DAT_0059bc00;
        uVar16 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[6] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar17] +
                                              (iVar21 >> 0x10 & DAT_0059bc38)),pbVar13[6]));
        iVar19 = iVar19 + iVar11;
        iVar21 = iVar20 + DAT_0059bc00;
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[7] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar16] +
                                              (iVar20 >> 0x10 & DAT_0059bc38)),pbVar13[7]));
        iVar19 = iVar19 + iVar11;
        iVar20 = iVar21 + DAT_0059bc00;
        uVar17 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[8] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar18] +
                                              (iVar21 >> 0x10 & DAT_0059bc38)),pbVar13[8]));
        iVar19 = iVar19 + iVar11;
        iVar21 = iVar20 + DAT_0059bc00;
        uVar16 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[9] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar17] +
                                              (iVar20 >> 0x10 & DAT_0059bc38)),pbVar13[9]));
        iVar19 = iVar19 + iVar11;
        iVar20 = iVar21 + DAT_0059bc00;
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[10] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar16] +
                                               (iVar21 >> 0x10 & DAT_0059bc38)),pbVar13[10]));
        iVar19 = iVar19 + iVar11;
        iVar21 = iVar20 + DAT_0059bc00;
        uVar17 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[0xb] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar18] +
                                                (iVar20 >> 0x10 & DAT_0059bc38)),pbVar13[0xb]));
        iVar19 = iVar19 + iVar11;
        iVar20 = iVar21 + DAT_0059bc00;
        uVar16 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[0xc] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar17] +
                                                (iVar21 >> 0x10 & DAT_0059bc38)),pbVar13[0xc]));
        iVar19 = iVar19 + iVar11;
        iVar21 = iVar20 + DAT_0059bc00;
        uVar18 = iVar19 >> 0x10 & DAT_0059bcb0;
        iVar11 = DAT_0059bc08;
        pbVar13[0xd] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar16] +
                                                (iVar20 >> 0x10 & DAT_0059bc38)),pbVar13[0xd]));
        iVar19 = iVar19 + iVar11;
        iVar20 = iVar21 + DAT_0059bc00;
        uVar17 = iVar20 >> 0x10 & DAT_0059bc38;
        iVar11 = (&DAT_006439d8)[iVar19 >> 0x10 & DAT_0059bcb0];
        pbVar13[0xe] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar18] +
                                                (iVar21 >> 0x10 & DAT_0059bc38)),pbVar13[0xe]));
        pbVar13[0xf] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)(iVar11 + uVar17),pbVar13[0xf]));
        _DAT_0059bc18 = (double)CONCAT44(DAT_0059bc18_4,iVar20);
        _DAT_0059bbf0 = (double)CONCAT44(DAT_0059bbf0_4,iVar19);
        iVar14 = iVar14 + -1;
        pbVar13 = pbVar13 + 0x10;
        fVar22 = fVar28;
        fVar28 = fVar25;
        fVar29 = fVar27;
      } while (-1 < iVar14);
    }
  }
  return;
}


