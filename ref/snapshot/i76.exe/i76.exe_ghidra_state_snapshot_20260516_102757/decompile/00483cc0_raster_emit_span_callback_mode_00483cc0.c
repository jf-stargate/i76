/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode_00483cc0
 * Entry: 00483cc0
 * Signature: undefined __cdecl raster_emit_span_callback_mode_00483cc0(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Raster span callback target from
   draw table; exact mode still being separated by feature trace. */

void __cdecl raster_emit_span_callback_mode_00483cc0(int *param_1,int *param_2)

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
  uint uVar11;
  int iVar12;
  int *piVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  undefined1 auStack_12c [256];
  int local_2c;
  uint *local_28;
  int local_24;
  uint local_20;
  uint *local_1c;
  int *local_18;
  uint local_14;
  byte *local_10;
  int *local_c;
  int *local_8;
  
  local_2c = *param_2;
  iVar19 = param_2[8] * *param_2 + param_2[5] + param_2[7];
  iVar12 = 0;
  local_24 = iVar19;
  puVar8 = &DAT_0060b09f;
  do {
    uVar2 = *puVar8;
    *puVar8 = (char)iVar12;
    auStack_12c[iVar12] = uVar2;
    puVar8 = puVar8 + 0x100;
    iVar12 = iVar12 + 1;
  } while ((int)puVar8 < 0x61b09f);
  local_8 = (int *)*param_1;
  if (local_8 != DAT_006439c0) {
    iVar12 = *local_8;
    piVar9 = local_8 + 2;
    uVar14 = (local_8[1] << 3) >> 3;
    local_18 = (int *)(uVar14 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = local_8;
    if (local_18 != (int *)0x0) {
      local_10 = (byte *)&DAT_006439d8;
      local_c = local_18;
      do {
        *(int **)local_10 = piVar9;
        local_10 = (byte *)((int)local_10 + 4);
        piVar9 = (int *)((int)piVar9 + iVar12);
        local_c = (int *)((int)local_c - 1);
        param_2 = local_18;
      } while (local_c != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar14) {
      piVar13 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar14 - (int)param_2) + 3 >> 2);
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
  local_28 = (uint *)(piVar9 + 1);
  local_1c = (uint *)(param_1[0xb] + 4);
  while (local_1c != local_28) {
    uVar14 = *local_1c;
    local_1c = local_1c + 1;
    fVar6 = (float)(uVar14 >> 0x15);
    fVar3 = (float)param_1[0x10];
    fVar7 = (float)(uVar14 & 0x3ff);
    fVar4 = (float)param_1[0x12];
    local_10 = (byte *)((uVar14 & 0x3ff) * local_2c + (uVar14 >> 0x15) + iVar19);
    fVar5 = fVar3 * fVar6 + fVar7 * (float)param_1[0x11] + (float)param_1[3];
    local_20 = (uVar14 >> 10 & 0x7ff) - 1;
    uVar14 = local_20 & 0xf;
    local_14 = uVar14;
    fVar6 = fVar4 * fVar6 + fVar7 * (float)param_1[0x13] + (float)param_1[4];
    _DAT_0059bc00 = (double)(fVar3 + (float)_DAT_004faf18);
    _DAT_0059bc08 = (double)(fVar4 + (float)_DAT_004faf18);
    _DAT_0059bc80 = (double)(fVar5 + (float)_DAT_004faf18);
    _DAT_0059bc40 = (double)(fVar6 + (float)_DAT_004faf18);
    DAT_0059bd38 = local_10 + uVar14 + 1;
    local_18 = (int *)((float)uVar14 * fVar4 + fVar6);
    fVar4 = fVar4 * _DAT_004be774;
    iVar19 = DAT_0059bc80;
    iVar12 = DAT_0059bc40;
    if (local_10 != DAT_0059bd38) {
      do {
        uVar11 = iVar12 >> 0x10;
        uVar15 = iVar19 >> 0x10;
        iVar12 = iVar12 + DAT_0059bc08;
        iVar19 = iVar19 + DAT_0059bc00;
        *local_10 = *(byte *)((int)&g_palette_blend_table_a +
                             (uint)*local_10 +
                             (uint)*(byte *)((&DAT_006439d8)[uVar11 & DAT_0059bcb0] +
                                            (uVar15 & DAT_0059bc38)) * 0x100);
        local_10 = local_10 + 1;
      } while (local_10 != DAT_0059bd38);
    }
    _DAT_0059bc80 = (double)CONCAT44(DAT_0059bc80_4,iVar19);
    _DAT_0059bc40 = (double)CONCAT44(DAT_0059bc40_4,iVar12);
    local_14 = (int)local_20 >> 4;
    iVar19 = local_24;
    if (-1 < (int)(local_14 + -1)) {
      do {
        _DAT_0059bc80 = (double)((float)uVar14 * fVar3 + fVar5 + (float)_DAT_004faf18);
        _DAT_0059bc40 = (double)((float)local_18 + (float)_DAT_004faf18);
        local_18 = (int *)((float)local_18 + fVar4);
        iVar12 = DAT_0059bc08;
        iVar10 = DAT_0059bc40 + DAT_0059bc08 + DAT_0059bc08;
        iVar17 = DAT_0059bc80 + DAT_0059bc00 + DAT_0059bc00;
        uVar11 = iVar10 >> 0x10 & DAT_0059bcb0;
        *local_10 = *(byte *)((int)&g_palette_blend_table_a +
                             (uint)CONCAT11(*(undefined1 *)
                                             ((&DAT_006439d8)
                                              [DAT_0059bc40 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                                             (DAT_0059bc80 + DAT_0059bc00 >> 0x10 & DAT_0059bc38)),
                                            *local_10));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[1] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar11] +
                                               (iVar17 >> 0x10 & DAT_0059bc38)),local_10[1]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar11 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[2] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar15] +
                                               (iVar18 >> 0x10 & DAT_0059bc38)),local_10[2]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[3] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar11] +
                                               (iVar17 >> 0x10 & DAT_0059bc38)),local_10[3]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar16 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[4] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar15] +
                                               (iVar18 >> 0x10 & DAT_0059bc38)),local_10[4]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar11 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[5] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar16] +
                                               (iVar17 >> 0x10 & DAT_0059bc38)),local_10[5]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[6] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar11] +
                                               (iVar18 >> 0x10 & DAT_0059bc38)),local_10[6]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar16 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[7] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar15] +
                                               (iVar17 >> 0x10 & DAT_0059bc38)),local_10[7]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar11 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[8] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar16] +
                                               (iVar18 >> 0x10 & DAT_0059bc38)),local_10[8]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[9] = *(byte *)((int)&g_palette_blend_table_a +
                               (uint)CONCAT11(*(undefined1 *)
                                               ((&DAT_006439d8)[uVar11] +
                                               (iVar17 >> 0x10 & DAT_0059bc38)),local_10[9]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar16 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[10] = *(byte *)((int)&g_palette_blend_table_a +
                                (uint)CONCAT11(*(undefined1 *)
                                                ((&DAT_006439d8)[uVar15] +
                                                (iVar18 >> 0x10 & DAT_0059bc38)),local_10[10]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar11 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[0xb] =
             *(byte *)((int)&g_palette_blend_table_a +
                      (uint)CONCAT11(*(undefined1 *)
                                      ((&DAT_006439d8)[uVar16] + (iVar17 >> 0x10 & DAT_0059bc38)),
                                     local_10[0xb]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar15 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[0xc] =
             *(byte *)((int)&g_palette_blend_table_a +
                      (uint)CONCAT11(*(undefined1 *)
                                      ((&DAT_006439d8)[uVar11] + (iVar18 >> 0x10 & DAT_0059bc38)),
                                     local_10[0xc]));
        iVar10 = iVar10 + iVar12;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar16 = iVar10 >> 0x10 & DAT_0059bcb0;
        iVar12 = DAT_0059bc08;
        local_10[0xd] =
             *(byte *)((int)&g_palette_blend_table_a +
                      (uint)CONCAT11(*(undefined1 *)
                                      ((&DAT_006439d8)[uVar15] + (iVar17 >> 0x10 & DAT_0059bc38)),
                                     local_10[0xd]));
        iVar10 = iVar10 + iVar12;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar11 = iVar17 >> 0x10 & DAT_0059bc38;
        iVar12 = (&DAT_006439d8)[iVar10 >> 0x10 & DAT_0059bcb0];
        local_10[0xe] =
             *(byte *)((int)&g_palette_blend_table_a +
                      (uint)CONCAT11(*(undefined1 *)
                                      ((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38)),
                                     local_10[0xe]));
        local_10[0xf] =
             *(byte *)((int)&g_palette_blend_table_a +
                      (uint)CONCAT11(*(undefined1 *)(iVar12 + uVar11),local_10[0xf]));
        _DAT_0059bc80 = (double)CONCAT44(DAT_0059bc80_4,iVar17);
        _DAT_0059bc40 = (double)CONCAT44(DAT_0059bc40_4,iVar10);
        local_14 = local_14 + -1;
        local_10 = local_10 + 0x10;
      } while (local_14 != 0);
    }
  }
  iVar19 = 0;
  puVar8 = &DAT_0060b09f;
  do {
    puVar1 = auStack_12c + iVar19;
    iVar19 = iVar19 + 1;
    *puVar8 = *puVar1;
    puVar8 = puVar8 + 0x100;
  } while ((int)puVar8 < 0x61b09f);
  return;
}


