/*
 * Program: i76.exe
 * Function: raster_emit_span_callback_mode_0048b690
 * Entry: 0048b690
 * Signature: undefined __cdecl raster_emit_span_callback_mode_0048b690(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Raster span callback target from
   draw table; exact mode still being separated by feature trace. */

void __cdecl raster_emit_span_callback_mode_0048b690(int *param_1,int *param_2)

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
  float fVar10;
  float fVar11;
  ulonglong uVar12;
  int *piVar13;
  int iVar14;
  uint *puVar15;
  uint uVar16;
  int iVar17;
  int *piVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  int local_20;
  undefined4 *local_1c;
  int *local_18;
  float local_14;
  float local_c;
  
  iVar2 = *param_2;
  iVar3 = param_2[8];
  iVar4 = param_2[7];
  iVar5 = param_2[5];
  piVar6 = (int *)*param_1;
  if (piVar6 != DAT_006439c0) {
    iVar17 = *piVar6;
    piVar13 = piVar6 + 2;
    uVar20 = (piVar6[1] << 3) >> 3;
    piVar18 = (int *)(uVar20 & 3);
    param_2 = (int *)0x0;
    DAT_006439c0 = piVar6;
    if (piVar18 != (int *)0x0) {
      local_1c = &DAT_006439d8;
      local_18 = piVar18;
      do {
        *local_1c = piVar13;
        local_1c = local_1c + 1;
        piVar13 = (int *)((int)piVar13 + iVar17);
        local_18 = (int *)((int)local_18 - 1);
        param_2 = piVar18;
      } while (local_18 != (int *)0x0);
    }
    if ((int)param_2 < (int)uVar20) {
      piVar18 = &DAT_006439dc + (int)param_2;
      param_2 = (int *)((uVar20 - (int)param_2) + 3 >> 2);
      do {
        piVar18[-1] = (int)piVar13;
        *piVar18 = (int)piVar13 + iVar17;
        iVar14 = (int)piVar13 + iVar17 + iVar17;
        piVar18[1] = iVar14;
        iVar14 = iVar14 + iVar17;
        piVar18[2] = iVar14;
        piVar13 = (int *)(iVar14 + iVar17);
        piVar18 = piVar18 + 4;
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
    uVar20 = *puVar15;
    puVar15 = puVar15 + 1;
    fVar10 = (float)(uVar20 >> 0x15);
    fVar7 = (float)param_1[0x10];
    fVar11 = (float)(uVar20 & 0x3ff);
    fVar8 = (float)param_1[0x12];
    fVar9 = (float)param_1[0x16];
    local_c = fVar7 * fVar10 + fVar11 * (float)param_1[0x11] + (float)param_1[3];
    local_18 = (int *)((uVar20 & 0x3ff) * iVar2 + (uVar20 >> 0x15) + iVar3 * iVar2 + iVar4 + iVar5);
    local_14 = fVar8 * fVar10 + fVar11 * (float)param_1[0x13] + (float)param_1[4];
    fVar11 = fVar9 * fVar10 + fVar11 * (float)param_1[0x17] + (float)param_1[6];
    uVar20 = (uVar20 >> 10 & 0x7ff) - 1;
    fVar10 = (float)(uVar20 & 0xf);
    local_20 = (int)uVar20 >> 4;
    _DAT_0059bc50 = (double)(fVar11 + (float)_DAT_004faf18);
    local_1c = (undefined4 *)(fVar10 * fVar9 + fVar11);
    _DAT_0059bba0 = (double)(fVar9 + (float)_DAT_004faf18);
    param_2 = (int *)(fVar9 * _DAT_004be774);
    uVar19 = DAT_0059bc50;
    if (((ulonglong)_DAT_0059bc50 & 0xffffe000) != 0) {
      uVar19 = ~DAT_0059bc50 >> 0x13;
      _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar19);
      local_1c = (undefined4 *)(float)uVar19;
    }
    uVar16 = DAT_0059bba0 * uVar20 + uVar19;
    if ((uVar16 & 0xffffe000) != 0) {
      iVar17 = (int)((~uVar16 >> 0x13) - uVar19) / (int)uVar20;
      _DAT_0059bba0 = (double)CONCAT44(DAT_0059bba0_4,iVar17);
      param_2 = (int *)(float)(iVar17 << 4);
    }
    DAT_0059bd38 = (undefined1 *)((int)local_18 + (uVar20 & 0xf) + 1);
    _DAT_0059bc00 = (double)(fVar7 + (float)_DAT_004faf18);
    _DAT_0059bc08 = (double)(fVar8 + (float)_DAT_004faf18);
    _DAT_0059bd40 = (double)(local_c + (float)_DAT_004faf18);
    _DAT_0059bcf0 = (double)(local_14 + (float)_DAT_004faf18);
    local_c = fVar10 * fVar7 + local_c;
    local_14 = fVar10 * fVar8 + local_14;
    fVar7 = fVar7 * _DAT_004be774;
    fVar8 = fVar8 * _DAT_004be774;
    iVar17 = DAT_0059bd40;
    iVar14 = DAT_0059bcf0;
    if (local_18 != (int *)DAT_0059bd38) {
      do {
        uVar20 = iVar14 >> 0x10;
        uVar19 = iVar17 >> 0x10;
        iVar14 = iVar14 + DAT_0059bc08;
        iVar17 = iVar17 + DAT_0059bc00;
        uVar19 = (uint)*(byte *)((&DAT_006439d8)[uVar20 & DAT_0059bcb0] + (uVar19 & DAT_0059bc38));
        uVar20 = DAT_0059bc50;
        if (uVar19 != 0xff) {
          *(undefined1 *)local_18 = (&DAT_0061b2a0)[(DAT_0059bc50 & 0x1f00) + uVar19];
        }
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,uVar20 + DAT_0059bba0);
        local_18 = (int *)((int)local_18 + 1);
      } while (local_18 != (int *)DAT_0059bd38);
    }
    _DAT_0059bd40 = (double)CONCAT44(DAT_0059bd40_4,iVar17);
    _DAT_0059bcf0 = (double)CONCAT44(DAT_0059bcf0_4,iVar14);
    if (-1 < local_20 + -1) {
      do {
        _DAT_0059bc50 = (double)((float)local_1c + (float)_DAT_004faf18);
        local_1c = (undefined4 *)((float)local_1c + (float)param_2);
        _DAT_0059bd40 = (double)(local_c + (float)_DAT_004faf18);
        _DAT_0059bcf0 = (double)(local_14 + (float)_DAT_004faf18);
        local_c = local_c + fVar7;
        local_14 = local_14 + fVar8;
        iVar17 = DAT_0059bc08;
        iVar14 = DAT_0059bcf0 + DAT_0059bc08 + DAT_0059bc08;
        iVar22 = DAT_0059bd40 + DAT_0059bc00 + DAT_0059bc00;
        uVar20 = DAT_0059bba0 + DAT_0059bc50;
        uVar12 = (ulonglong)_DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[DAT_0059bcf0 + DAT_0059bc08 >> 0x10 & DAT_0059bcb0] +
                         (DAT_0059bd40 + DAT_0059bc00 >> 0x10 & DAT_0059bc38));
        uVar19 = iVar14 >> 0x10 & DAT_0059bcb0;
        DAT_0059bc50 = uVar20;
        if (cVar1 != -1) {
          *(undefined1 *)local_18 = (&DAT_0061b2a0)[CONCAT31((int3)uVar12,cVar1) & 0x1fff];
        }
        iVar14 = iVar14 + iVar17;
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar19] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar21 = iVar14 + DAT_0059bc08;
        iVar17 = (&DAT_006439d8)[iVar14 >> 0x10 & DAT_0059bcb0];
        uVar19 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 1) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar17 + uVar19);
        uVar19 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar17 = DAT_0059bc08;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 2) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        iVar21 = iVar21 + iVar17;
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar19] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar14 = iVar21 + DAT_0059bc08;
        iVar17 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar19 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 3) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar17 + uVar19);
        uVar19 = iVar14 >> 0x10 & DAT_0059bcb0;
        iVar17 = DAT_0059bc08;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 4) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        iVar14 = iVar14 + iVar17;
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar19] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar21 = iVar14 + DAT_0059bc08;
        iVar17 = (&DAT_006439d8)[iVar14 >> 0x10 & DAT_0059bcb0];
        uVar19 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 5) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar17 + uVar19);
        uVar19 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar17 = DAT_0059bc08;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 6) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        iVar21 = iVar21 + iVar17;
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar19] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar14 = iVar21 + DAT_0059bc08;
        iVar17 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar19 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 7) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar17 + uVar19);
        uVar19 = iVar14 >> 0x10 & DAT_0059bcb0;
        iVar17 = DAT_0059bc08;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 8) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        iVar14 = iVar14 + iVar17;
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar19] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar21 = iVar14 + DAT_0059bc08;
        iVar17 = (&DAT_006439d8)[iVar14 >> 0x10 & DAT_0059bcb0];
        uVar19 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 9) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar17 + uVar19);
        uVar19 = iVar21 >> 0x10 & DAT_0059bcb0;
        iVar17 = DAT_0059bc08;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 10) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        iVar21 = iVar21 + iVar17;
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar19] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar14 = iVar21 + DAT_0059bc08;
        iVar17 = (&DAT_006439d8)[iVar21 >> 0x10 & DAT_0059bcb0];
        uVar19 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 0xb) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar17 + uVar19);
        uVar19 = iVar14 >> 0x10 & DAT_0059bcb0;
        iVar17 = DAT_0059bc08;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 0xc) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        iVar14 = iVar14 + iVar17;
        uVar16 = DAT_0059bba0 + DAT_0059bc50;
        uVar20 = DAT_0059bc50 >> 8;
        cVar1 = *(char *)((&DAT_006439d8)[uVar19] + (iVar22 >> 0x10 & DAT_0059bc38));
        iVar22 = iVar22 + DAT_0059bc00;
        iVar21 = iVar14 + DAT_0059bc08;
        iVar17 = (&DAT_006439d8)[iVar14 >> 0x10 & DAT_0059bcb0];
        uVar19 = iVar22 >> 0x10 & DAT_0059bc38;
        DAT_0059bc50 = uVar16;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 0xd) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        uVar20 = DAT_0059bc50 >> 8;
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,DAT_0059bba0 + DAT_0059bc50);
        iVar22 = iVar22 + DAT_0059bc00;
        cVar1 = *(char *)(iVar17 + uVar19);
        uVar19 = iVar21 >> 0x10 & DAT_0059bcb0;
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 0xe) =
               (&DAT_0061b2a0)[CONCAT31((int3)uVar20,cVar1) & 0x1fff];
        }
        iVar17 = DAT_0059bba0 + DAT_0059bc50;
        cVar1 = *(char *)((&DAT_006439d8)[uVar19] + (iVar22 >> 0x10 & DAT_0059bc38));
        if (cVar1 != -1) {
          *(undefined1 *)((int)local_18 + 0xf) =
               (&DAT_0061b2a0)[CONCAT31((int3)((ulonglong)_DAT_0059bc50 >> 8),cVar1) & 0x1fff];
        }
        _DAT_0059bc50 = (double)CONCAT44(DAT_0059bc50_4,iVar17);
        local_18 = (int *)((int)local_18 + 0x10);
        _DAT_0059bd40 = (double)CONCAT44(DAT_0059bd40_4,iVar22);
        _DAT_0059bcf0 = (double)CONCAT44(DAT_0059bcf0_4,iVar21);
        local_20 = local_20 + -1;
      } while (local_20 != 0);
    }
  }
  return;
}


