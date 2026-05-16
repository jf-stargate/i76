/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode_00484630
 * Entry: 00484630
 * Signature: undefined __cdecl raster_emit_span_callback_mode_00484630(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Raster span callback target from
   draw table; exact mode still being separated by feature trace. */

void __cdecl raster_emit_span_callback_mode_00484630(int *param_1,int *param_2)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined1 *puVar8;
  int *piVar9;
  int iVar10;
  byte *pbVar11;
  int iVar12;
  int *piVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  float10 in_ST0;
  float10 fVar20;
  float10 fVar21;
  float10 fVar22;
  float10 fVar23;
  float10 fVar24;
  float10 fVar25;
  float10 fVar26;
  float10 in_ST1;
  float10 fVar27;
  float10 fVar28;
  undefined1 auStack_130 [256];
  int local_30;
  uint *local_2c;
  int local_28;
  uint *local_24;
  int local_20;
  float local_1c;
  int *local_18;
  float local_14;
  undefined4 *local_10;
  int *local_c;
  int *local_8;
  
  local_30 = *param_2;
  iVar19 = param_2[8] * *param_2 + param_2[7] + param_2[5];
  iVar12 = 0;
  local_28 = iVar19;
  puVar8 = &DAT_0060b09f;
  do {
    uVar2 = *puVar8;
    *puVar8 = (char)iVar12;
    auStack_130[iVar12] = uVar2;
    puVar8 = puVar8 + 0x100;
    iVar12 = iVar12 + 1;
  } while ((int)puVar8 < 0x61b09f);
  local_8 = (int *)*param_1;
  if (local_8 != DAT_006439c0) {
    iVar12 = *local_8;
    piVar9 = local_8 + 2;
    uVar15 = (local_8[1] << 3) >> 3;
    local_18 = (int *)(uVar15 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = local_8;
    if (local_18 != (int *)0x0) {
      local_10 = &DAT_006439d8;
      local_c = local_18;
      do {
        *local_10 = piVar9;
        local_10 = local_10 + 1;
        piVar9 = (int *)((int)piVar9 + iVar12);
        local_c = (int *)((int)local_c - 1);
        param_2 = local_18;
      } while (local_c != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar15) {
      piVar13 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar15 - (int)param_2) + 3 >> 2);
      do {
        piVar13[-1] = (int)piVar9;
        *piVar13 = (int)piVar9 + iVar12;
        iVar10 = (int)piVar9 + iVar12 + iVar12;
        piVar13[1] = iVar10;
        iVar10 = iVar10 + iVar12;
        piVar13[2] = iVar10;
        piVar9 = (int *)(iVar10 + iVar12);
        piVar13 = piVar13 + 4;
        param_2 = (int *)((int)param_2 + -1);
      } while (param_2 != (int *)0x0);
    }
  }
  DAT_0059bc38 = *local_8 - 1;
  DAT_0059bcb0 = ((local_8[1] << 3) >> 3) - 1;
  piVar9 = (int *)param_1[0xc];
  *piVar9 = param_1[10];
  local_2c = (uint *)(piVar9 + 1);
  local_24 = (uint *)(param_1[0xb] + 4);
  while (local_24 != local_2c) {
    uVar15 = *local_24;
    local_24 = local_24 + 1;
    fVar5 = (float)(uVar15 >> 0x15);
    fVar3 = (float)param_1[0x10];
    local_1c = fVar3;
    fVar6 = (float)(uVar15 & 0x3ff);
    local_c = (int *)param_1[0x12];
    local_8 = (int *)param_1[0x14];
    fVar4 = fVar3 * fVar5 + fVar6 * (float)param_1[0x11] + (float)param_1[3];
    pbVar11 = (byte *)((uVar15 & 0x3ff) * local_30 + (uVar15 >> 0x15) + iVar19);
    local_14 = (float)local_c * fVar5 + fVar6 * (float)param_1[0x13] + (float)param_1[4];
    fVar5 = (float)local_8 * fVar5 + fVar6 * (float)param_1[0x15] + (float)param_1[5];
    uVar15 = (uVar15 >> 10 & 0x7ff) - 1;
    uVar14 = uVar15 & 0xf;
    fVar7 = (float)uVar14;
    fVar6 = _DAT_004be778 / fVar5;
    local_20 = (int)uVar15 >> 4;
    _DAT_0059bca0 = (double)(fVar6 * fVar4 + (float)_DAT_004faf18);
    _DAT_0059bc60 = (double)(fVar6 * local_14 + (float)_DAT_004faf18);
    param_2 = (int *)(fVar7 * fVar3 + fVar4);
    local_14 = fVar7 * (float)local_c + local_14;
    local_10 = (undefined4 *)(fVar7 * (float)local_8 + fVar5);
    _DAT_0059bc00 =
         (double)(((_DAT_004be778 / (float)local_10) * (float)param_2 - (float)DAT_0059bca0) *
                  *(float *)(&DAT_004f9d38 + uVar14 * 4) + (float)_DAT_004faf18);
    _DAT_0059bc08 =
         (double)(((_DAT_004be778 / (float)local_10) * local_14 - (float)DAT_0059bc60) *
                  *(float *)(&DAT_004f9d38 + uVar14 * 4) + (float)_DAT_004faf18);
    fVar20 = in_ST0;
    if (0 < local_20) {
      local_1c = fVar3 * _DAT_004be774;
      local_c = (int *)((float)local_c * _DAT_004be774);
      local_8 = (int *)((float)local_8 * _DAT_004be774);
      param_2 = (int *)((float)param_2 + fVar3 * _DAT_004be774);
      local_14 = local_14 + (float)local_c;
      local_10 = (undefined4 *)((float)local_10 + (float)local_8);
      fVar20 = (float10)_DAT_004fa494 / (float10)(float)local_10;
      in_ST1 = in_ST0;
    }
    DAT_0059bd38 = pbVar11 + uVar14 + 1;
    iVar12 = DAT_0059bca0;
    iVar10 = DAT_0059bc60;
    if (pbVar11 != DAT_0059bd38) {
      do {
        uVar15 = iVar10 >> 0x10;
        uVar14 = iVar12 >> 0x10;
        iVar10 = iVar10 + DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc00;
        *pbVar11 = *(byte *)((int)&g_palette_blend_table_a +
                            (uint)*pbVar11 +
                            (uint)*(byte *)((&DAT_006439d8)[uVar15 & DAT_0059bcb0] +
                                           (uVar14 & DAT_0059bc38)) * 0x100);
        pbVar11 = pbVar11 + 1;
      } while (pbVar11 != DAT_0059bd38);
    }
    _DAT_0059bca0 = (double)CONCAT44(DAT_0059bca0_4,iVar12);
    _DAT_0059bc60 = (double)CONCAT44(DAT_0059bc60_4,iVar10);
    local_20 = local_20 + -1;
    iVar19 = local_28;
    in_ST0 = fVar20;
    if (-1 < local_20) {
      _DAT_0059bca0 = (double)CONCAT44(DAT_0059bca0_4,iVar12 - DAT_0059bc00);
      _DAT_0059bc60 = (double)CONCAT44(DAT_0059bc60_4,iVar10 - DAT_0059bc08);
      fVar21 = (float10)(iVar12 - DAT_0059bc00);
      fVar22 = (float10)local_14;
      in_ST0 = (float10)_DAT_0059bc60 - (float10)_DAT_004faf18;
      fVar26 = (float10)(float)local_10;
      fVar27 = (float10)(float)param_2;
      do {
        fVar23 = (fVar20 * fVar27 - fVar21) + (float10)_DAT_004fa490;
        fVar20 = (fVar20 * fVar22 - in_ST0) + (float10)_DAT_004fa490;
        fVar24 = fVar22 + (float10)(float)local_c;
        _DAT_0059bc08 = (double)fVar20;
        _DAT_0059bc00 = (double)fVar23;
        fVar28 = (fVar20 - (float10)_DAT_004fa490) + in_ST0;
        fVar20 = (fVar23 - (float10)_DAT_004fa490) + fVar21;
        fVar23 = fVar27;
        fVar25 = fVar24;
        fVar22 = fVar20;
        fVar21 = fVar28;
        in_ST0 = in_ST1;
        if (local_20 != 0) {
          fVar23 = fVar26 + (float10)(float)local_8;
          fVar25 = fVar27 + (float10)local_1c;
          fVar26 = (float10)_DAT_004fa494 / fVar23;
          fVar22 = fVar24;
          fVar21 = fVar20;
          in_ST0 = fVar28;
        }
        iVar12 = DAT_0059bc08;
        iVar10 = DAT_0059bc60 + DAT_0059bc08 + DAT_0059bc08;
        iVar17 = DAT_0059bca0 + DAT_0059bc00 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        *pbVar11 = *(byte *)((int)&g_palette_blend_table_a +
                            (uint)CONCAT11(*(undefined1 *)
                                            ((&DAT_006439d8)
                                             [DAT_0059bc60 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                                            (DAT_0059bca0 + DAT_0059bc00 >> 0x10 & DAT_0059bc38)),
                                           *pbVar11));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar14 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[1] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar15] +
                                              (iVar17 >> 0x10 & DAT_0059bc38)),pbVar11[1]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[2] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar14] +
                                              (iVar18 >> 0x10 & DAT_0059bc38)),pbVar11[2]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar14 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[3] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar15] +
                                              (iVar17 >> 0x10 & DAT_0059bc38)),pbVar11[3]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar16 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[4] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar14] +
                                              (iVar18 >> 0x10 & DAT_0059bc38)),pbVar11[4]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[5] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar16] +
                                              (iVar17 >> 0x10 & DAT_0059bc38)),pbVar11[5]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar14 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[6] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar15] +
                                              (iVar18 >> 0x10 & DAT_0059bc38)),pbVar11[6]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar16 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[7] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar14] +
                                              (iVar17 >> 0x10 & DAT_0059bc38)),pbVar11[7]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[8] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar16] +
                                              (iVar18 >> 0x10 & DAT_0059bc38)),pbVar11[8]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar14 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[9] = *(byte *)((int)&g_palette_blend_table_a +
                              (uint)CONCAT11(*(undefined1 *)
                                              ((&DAT_006439d8)[uVar15] +
                                              (iVar17 >> 0x10 & DAT_0059bc38)),pbVar11[9]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar16 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[10] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar14] +
                                               (iVar18 >> 0x10 & DAT_0059bc38)),pbVar11[10]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[0xb] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar16] +
                                                (iVar17 >> 0x10 & DAT_0059bc38)),pbVar11[0xb]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar14 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[0xc] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar15] +
                                                (iVar18 >> 0x10 & DAT_0059bc38)),pbVar11[0xc]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar16 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        pbVar11[0xd] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar14] +
                                                (iVar17 >> 0x10 & DAT_0059bc38)),pbVar11[0xd]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar15 = iVar17 >> 0x10 & DAT_0059bc38;
        iVar12 = (&DAT_006439d8)[iVar10 >> 0x10 & DAT_0059bcb0];
        pbVar11[0xe] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar16] +
                                                (iVar18 >> 0x10 & DAT_0059bc38)),pbVar11[0xe]));
        pbVar11[0xf] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)(iVar12 + uVar15),pbVar11[0xf]));
        _DAT_0059bca0 = (double)CONCAT44(DAT_0059bca0_4,iVar17);
        _DAT_0059bc60 = (double)CONCAT44(DAT_0059bc60_4,iVar10);
        local_20 = local_20 + -1;
        pbVar11 = pbVar11 + 0x10;
        fVar20 = fVar26;
        fVar26 = fVar23;
        fVar27 = fVar25;
      } while (-1 < local_20);
    }
  }
  iVar19 = 0;
  puVar8 = &DAT_0060b09f;
  do {
    puVar1 = auStack_130 + iVar19;
    iVar19 = iVar19 + 1;
    *puVar8 = *puVar1;
    puVar8 = puVar8 + 0x100;
  } while ((int)puVar8 < 0x61b09f);
  return;
}


