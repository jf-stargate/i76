/*
 * Program: i76.exe
 * Function: raster_emit_textured_spans_variant_b
 * Entry: 0047efe0
 * Signature: undefined __cdecl raster_emit_textured_spans_variant_b(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe geo raster span family renames v38; confidence=medium] Affine textured span
   callback variant with alternate texture row/coordinate behavior. */

void __cdecl raster_emit_textured_spans_variant_b(int *param_1,int *param_2)

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
  int *piVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int local_18;
  float local_14;
  undefined4 *local_10;
  int *local_c;
  float local_8;
  
  iVar1 = *param_2;
  iVar2 = param_2[8];
  iVar3 = param_2[5];
  iVar4 = param_2[7];
  piVar5 = (int *)*param_1;
  if (piVar5 != DAT_006439c0) {
    iVar17 = *piVar5;
    piVar10 = piVar5 + 2;
    uVar15 = (piVar5[1] << 3) >> 3;
    piVar13 = (int *)(uVar15 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar5;
    if (piVar13 != (int *)0x0) {
      local_10 = &DAT_006439d8;
      local_c = piVar13;
      do {
        *local_10 = piVar10;
        local_10 = local_10 + 1;
        piVar10 = (int *)((int)piVar10 + iVar17);
        local_c = (int *)((int)local_c - 1);
        param_2 = piVar13;
      } while (local_c != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar15) {
      piVar13 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar15 - (int)param_2) + 3 >> 2);
      do {
        piVar13[-1] = (int)piVar10;
        *piVar13 = (int)piVar10 + iVar17;
        iVar11 = (int)piVar10 + iVar17 + iVar17;
        piVar13[1] = iVar11;
        iVar11 = iVar11 + iVar17;
        piVar13[2] = iVar11;
        piVar10 = (int *)(iVar11 + iVar17);
        piVar13 = piVar13 + 4;
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
    uVar15 = *puVar12;
    puVar12 = puVar12 + 1;
    fVar8 = (float)(uVar15 >> 0x15);
    fVar6 = (float)param_1[0x10];
    fVar9 = (float)(uVar15 & 0x3ff);
    fVar7 = (float)param_1[0x12];
    local_10 = (undefined4 *)
               ((uVar15 & 0x3ff) * iVar1 + (uVar15 >> 0x15) + iVar2 * iVar1 + iVar3 + iVar4);
    local_8 = fVar6 * fVar8 + fVar9 * (float)param_1[0x11] + (float)param_1[3];
    uVar15 = (uVar15 >> 10 & 0x7ff) - 1;
    uVar14 = uVar15 & 0xf;
    local_14 = fVar7 * fVar8 + fVar9 * (float)param_1[0x13] + (float)param_1[4];
    fVar8 = (float)uVar14;
    _DAT_0059bc00 = (double)(fVar6 + (float)_DAT_004faf18);
    _DAT_0059bc08 = (double)(fVar7 + (float)_DAT_004faf18);
    _DAT_0059bc10 = (double)(local_8 + (float)_DAT_004faf18);
    _DAT_0059bcf8 = (double)(local_14 + (float)_DAT_004faf18);
    DAT_0059bd38 = (undefined1 *)((int)local_10 + uVar14 + 1);
    local_8 = fVar8 * fVar6 + local_8;
    local_14 = fVar8 * fVar7 + local_14;
    fVar6 = fVar6 * _DAT_004be774;
    fVar7 = fVar7 * _DAT_004be774;
    iVar17 = DAT_0059bc10;
    iVar11 = DAT_0059bcf8;
    if (local_10 != (undefined4 *)DAT_0059bd38) {
      do {
        uVar14 = iVar11 >> 0x10;
        uVar16 = iVar17 >> 0x10;
        iVar11 = iVar11 + DAT_0059bc08;
        iVar17 = iVar17 + DAT_0059bc00;
        *(undefined1 *)local_10 =
             *(undefined1 *)((&DAT_006439d8)[uVar14 & DAT_0059bcb0] + (uVar16 & DAT_0059bc38));
        local_10 = (undefined4 *)((int)local_10 + 1);
      } while (local_10 != (undefined4 *)DAT_0059bd38);
    }
    _DAT_0059bc10 = (double)CONCAT44(DAT_0059bc10_4,iVar17);
    _DAT_0059bcf8 = (double)CONCAT44(DAT_0059bcf8_4,iVar11);
    local_18 = (int)uVar15 >> 4;
    if (-1 < local_18 + -1) {
      do {
        _DAT_0059bc10 = (double)(local_8 + (float)_DAT_004faf18);
        _DAT_0059bcf8 = (double)(local_14 + (float)_DAT_004faf18);
        local_8 = local_8 + fVar6;
        local_14 = local_14 + fVar7;
        iVar17 = DAT_0059bc08;
        iVar11 = DAT_0059bcf8 + DAT_0059bc08 + DAT_0059bc08;
        iVar18 = DAT_0059bc10 + DAT_0059bc00 + DAT_0059bc00;
        uVar15 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)local_10 =
             *(undefined1 *)
              ((&DAT_006439d8)[DAT_0059bcf8 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
              (DAT_0059bc10 + DAT_0059bc00 >> 0x10 & DAT_0059bc38));
        iVar11 = iVar11 + iVar17;
        iVar19 = iVar18 + DAT_0059bc00;
        uVar14 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 1) =
             *(undefined1 *)((&DAT_006439d8)[uVar15] + (iVar18 >> 0x10 & DAT_0059bc38));
        iVar17 = DAT_0059bc08;
        iVar11 = iVar11 + DAT_0059bc08;
        iVar18 = iVar19 + DAT_0059bc00;
        uVar15 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 2) =
             *(undefined1 *)((&DAT_006439d8)[uVar14] + (iVar19 >> 0x10 & DAT_0059bc38));
        iVar11 = iVar11 + iVar17;
        iVar19 = iVar18 + DAT_0059bc00;
        uVar14 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 3) =
             *(undefined1 *)((&DAT_006439d8)[uVar15] + (iVar18 >> 0x10 & DAT_0059bc38));
        iVar17 = DAT_0059bc08;
        iVar11 = iVar11 + DAT_0059bc08;
        iVar18 = iVar19 + DAT_0059bc00;
        uVar16 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 4) =
             *(undefined1 *)((&DAT_006439d8)[uVar14] + (iVar19 >> 0x10 & DAT_0059bc38));
        iVar11 = iVar11 + iVar17;
        iVar19 = iVar18 + DAT_0059bc00;
        uVar15 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 5) =
             *(undefined1 *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        iVar17 = DAT_0059bc08;
        iVar11 = iVar11 + DAT_0059bc08;
        iVar18 = iVar19 + DAT_0059bc00;
        uVar14 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 6) =
             *(undefined1 *)((&DAT_006439d8)[uVar15] + (iVar19 >> 0x10 & DAT_0059bc38));
        iVar11 = iVar11 + iVar17;
        iVar19 = iVar18 + DAT_0059bc00;
        uVar16 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 7) =
             *(undefined1 *)((&DAT_006439d8)[uVar14] + (iVar18 >> 0x10 & DAT_0059bc38));
        iVar17 = DAT_0059bc08;
        iVar11 = iVar11 + DAT_0059bc08;
        iVar18 = iVar19 + DAT_0059bc00;
        uVar15 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 8) =
             *(undefined1 *)((&DAT_006439d8)[uVar16] + (iVar19 >> 0x10 & DAT_0059bc38));
        iVar11 = iVar11 + iVar17;
        iVar19 = iVar18 + DAT_0059bc00;
        uVar14 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 9) =
             *(undefined1 *)((&DAT_006439d8)[uVar15] + (iVar18 >> 0x10 & DAT_0059bc38));
        iVar17 = DAT_0059bc08;
        iVar11 = iVar11 + DAT_0059bc08;
        iVar18 = iVar19 + DAT_0059bc00;
        uVar16 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 10) =
             *(undefined1 *)((&DAT_006439d8)[uVar14] + (iVar19 >> 0x10 & DAT_0059bc38));
        iVar11 = iVar11 + iVar17;
        iVar19 = iVar18 + DAT_0059bc00;
        uVar15 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 0xb) =
             *(undefined1 *)((&DAT_006439d8)[uVar16] + (iVar18 >> 0x10 & DAT_0059bc38));
        iVar17 = DAT_0059bc08;
        iVar11 = iVar11 + DAT_0059bc08;
        iVar18 = iVar19 + DAT_0059bc00;
        uVar14 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 0xc) =
             *(undefined1 *)((&DAT_006439d8)[uVar15] + (iVar19 >> 0x10 & DAT_0059bc38));
        iVar11 = iVar11 + iVar17;
        iVar17 = iVar18 + DAT_0059bc00;
        uVar16 = iVar11 >> 0x10 & DAT_0059bcb0;
        *(undefined1 *)((int)local_10 + 0xd) =
             *(undefined1 *)((&DAT_006439d8)[uVar14] + (iVar18 >> 0x10 & DAT_0059bc38));
        iVar11 = iVar11 + DAT_0059bc08;
        iVar18 = iVar17 + DAT_0059bc00;
        uVar15 = iVar11 >> 0x10 & DAT_0059bcb0;
        uVar14 = iVar18 >> 0x10 & DAT_0059bc38;
        *(undefined1 *)((int)local_10 + 0xe) =
             *(undefined1 *)((&DAT_006439d8)[uVar16] + (iVar17 >> 0x10 & DAT_0059bc38));
        *(undefined1 *)((int)local_10 + 0xf) = *(undefined1 *)((&DAT_006439d8)[uVar15] + uVar14);
        local_10 = (undefined4 *)((int)local_10 + 0x10);
        _DAT_0059bc10 = (double)CONCAT44(DAT_0059bc10_4,iVar18);
        _DAT_0059bcf8 = (double)CONCAT44(DAT_0059bcf8_4,iVar11);
        local_18 = local_18 + -1;
      } while (local_18 != 0);
    }
  }
  return;
}


