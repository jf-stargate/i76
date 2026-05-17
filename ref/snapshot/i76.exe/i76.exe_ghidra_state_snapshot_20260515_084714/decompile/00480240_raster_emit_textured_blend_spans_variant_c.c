/*
 * Program: i76.exe
 * Function: raster_emit_textured_blend_spans_variant_c
 * Entry: 00480240
 * Signature: undefined __cdecl raster_emit_textured_blend_spans_variant_c(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe geo raster span family renames v38; confidence=medium] Affine textured span
   callback variant using g_palette_blend_table_c. */

void __cdecl raster_emit_textured_blend_spans_variant_c(int *param_1,int *param_2)

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
  int *piVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int local_18;
  float local_14;
  byte *local_10;
  int *local_c;
  float local_8;
  
  iVar2 = *param_2;
  iVar3 = param_2[8];
  iVar4 = param_2[5];
  iVar5 = param_2[7];
  piVar6 = (int *)*param_1;
  if (piVar6 != DAT_006439c0) {
    iVar18 = *piVar6;
    piVar11 = piVar6 + 2;
    uVar16 = (piVar6[1] << 3) >> 3;
    piVar14 = (int *)(uVar16 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar6;
    if (piVar14 != (int *)0x0) {
      local_10 = (byte *)&DAT_006439d8;
      local_c = piVar14;
      do {
        *(int **)local_10 = piVar11;
        local_10 = (byte *)((int)local_10 + 4);
        piVar11 = (int *)((int)piVar11 + iVar18);
        local_c = (int *)((int)local_c - 1);
        param_2 = piVar14;
      } while (local_c != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar16) {
      piVar14 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar16 - (int)param_2) + 3 >> 2);
      do {
        piVar14[-1] = (int)piVar11;
        *piVar14 = (int)piVar11 + iVar18;
        iVar12 = (int)piVar11 + iVar18 + iVar18;
        piVar14[1] = iVar12;
        iVar12 = iVar12 + iVar18;
        piVar14[2] = iVar12;
        piVar11 = (int *)(iVar12 + iVar18);
        piVar14 = piVar14 + 4;
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
    uVar16 = *puVar13;
    puVar13 = puVar13 + 1;
    fVar9 = (float)(uVar16 >> 0x15);
    fVar7 = (float)param_1[0x10];
    fVar10 = (float)(uVar16 & 0x3ff);
    fVar8 = (float)param_1[0x12];
    local_10 = (byte *)((uVar16 & 0x3ff) * iVar2 + (uVar16 >> 0x15) + iVar3 * iVar2 + iVar4 + iVar5)
    ;
    local_8 = fVar7 * fVar9 + fVar10 * (float)param_1[0x11] + (float)param_1[3];
    uVar16 = (uVar16 >> 10 & 0x7ff) - 1;
    uVar15 = uVar16 & 0xf;
    local_14 = fVar8 * fVar9 + fVar10 * (float)param_1[0x13] + (float)param_1[4];
    fVar9 = (float)uVar15;
    _DAT_0059bc00 = (double)(fVar7 + (float)_DAT_004faf18);
    _DAT_0059bc08 = (double)(fVar8 + (float)_DAT_004faf18);
    _DAT_0059bc58 = (double)(local_8 + (float)_DAT_004faf18);
    _DAT_0059bbb8 = (double)(local_14 + (float)_DAT_004faf18);
    DAT_0059bd38 = local_10 + uVar15 + 1;
    local_8 = fVar9 * fVar7 + local_8;
    local_14 = fVar9 * fVar8 + local_14;
    fVar7 = fVar7 * _DAT_004be774;
    fVar8 = fVar8 * _DAT_004be774;
    iVar18 = DAT_0059bc58;
    iVar12 = DAT_0059bbb8;
    if (local_10 != DAT_0059bd38) {
      do {
        uVar15 = iVar12 >> 0x10;
        uVar17 = iVar18 >> 0x10;
        iVar12 = iVar12 + DAT_0059bc08;
        iVar18 = iVar18 + DAT_0059bc00;
        *local_10 = *(byte *)((int)&g_palette_blend_table_c +
                             (uint)*local_10 +
                             (uint)*(byte *)((&DAT_006439d8)[uVar15 & DAT_0059bcb0] +
                                            (uVar17 & DAT_0059bc38)) * 0x100);
        local_10 = local_10 + 1;
      } while (local_10 != DAT_0059bd38);
    }
    _DAT_0059bc58 = (double)CONCAT44(DAT_0059bc58_4,iVar18);
    _DAT_0059bbb8 = (double)CONCAT44(DAT_0059bbb8_4,iVar12);
    local_18 = (int)uVar16 >> 4;
    if (-1 < local_18 + -1) {
      do {
        _DAT_0059bc58 = (double)(local_8 + (float)_DAT_004faf18);
        _DAT_0059bbb8 = (double)(local_14 + (float)_DAT_004faf18);
        local_8 = local_8 + fVar7;
        local_14 = local_14 + fVar8;
        iVar18 = DAT_0059bc08;
        iVar12 = DAT_0059bbb8 + DAT_0059bc08 + DAT_0059bc08;
        iVar19 = DAT_0059bc58 + DAT_0059bc00 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[DAT_0059bbb8 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                         (DAT_0059bc58 + DAT_0059bc00 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          *local_10 = bVar1;
        }
        iVar12 = iVar12 + iVar18;
        iVar18 = iVar19 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar19 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[1] = bVar1;
        }
        iVar19 = DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc08;
        iVar20 = iVar18 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[2] = bVar1;
        }
        iVar12 = iVar12 + iVar19;
        iVar18 = iVar20 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar20 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[3] = bVar1;
        }
        iVar19 = DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc08;
        iVar20 = iVar18 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[4] = bVar1;
        }
        iVar12 = iVar12 + iVar19;
        iVar18 = iVar20 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar20 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[5] = bVar1;
        }
        iVar19 = DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc08;
        iVar20 = iVar18 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[6] = bVar1;
        }
        iVar12 = iVar12 + iVar19;
        iVar18 = iVar20 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar20 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[7] = bVar1;
        }
        iVar19 = DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc08;
        iVar20 = iVar18 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[8] = bVar1;
        }
        iVar12 = iVar12 + iVar19;
        iVar18 = iVar20 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar20 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[9] = bVar1;
        }
        iVar19 = DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc08;
        iVar20 = iVar18 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[10] = bVar1;
        }
        iVar12 = iVar12 + iVar19;
        iVar18 = iVar20 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar20 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[0xb] = bVar1;
        }
        iVar19 = DAT_0059bc08;
        iVar12 = iVar12 + DAT_0059bc08;
        iVar20 = iVar18 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[0xc] = bVar1;
        }
        iVar12 = iVar12 + iVar19;
        iVar18 = iVar20 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar20 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        if (bVar1 != 0xff) {
          local_10[0xd] = bVar1;
        }
        iVar12 = iVar12 + DAT_0059bc08;
        iVar19 = iVar18 + DAT_0059bc00;
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        uVar16 = iVar12 >> 0x10 & DAT_0059bcb0;
        uVar15 = iVar19 >> 0x10 & DAT_0059bc38;
        if (bVar1 != 0xff) {
          local_10[0xe] = bVar1;
        }
        bVar1 = *(byte *)((&DAT_006439d8)[uVar16] + uVar15);
        if (bVar1 != 0xff) {
          local_10[0xf] = bVar1;
        }
        local_10 = local_10 + 0x10;
        _DAT_0059bc58 = (double)CONCAT44(DAT_0059bc58_4,iVar19);
        _DAT_0059bbb8 = (double)CONCAT44(DAT_0059bbb8_4,iVar12);
        local_18 = local_18 + -1;
      } while (local_18 != 0);
    }
  }
  return;
}


