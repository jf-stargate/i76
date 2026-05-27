/*
 * Program: i76.exe
 * Function: initialize_horizon_ring_vertex_table
 * Entry: 00401410
 * Signature: undefined __stdcall initialize_horizon_ring_vertex_table(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Builds a circular/ring vertex table with radius 6000 and duplicated distance
   entries for horizon/sky-style rendering. */

void initialize_horizon_ring_vertex_table(void)

{
  float10 fVar1;
  float10 fVar2;
  float fVar3;
  undefined4 *puVar4;
  float *pfVar5;
  undefined4 *puVar6;
  int iVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  
  fVar8 = (float10)_DAT_004bc418;
  _DAT_00501820 = 0x60000000;
  _DAT_00501824 = 0x3fd921fb;
  iVar7 = 0;
  pfVar5 = &DAT_00503040;
  do {
    fVar9 = fVar8 - (float10)_DAT_004bc41c;
    fVar8 = fVar8 - (float10)_DAT_004bc424;
    iVar7 = iVar7 + 1;
    fVar10 = (float10)fcos(fVar9);
    fVar11 = (float10)fsin(fVar9);
    fVar2 = (float10)_DAT_004bc428;
    fVar1 = (float10)_DAT_004bc420;
    fVar9 = (float10)_DAT_004bc42c;
    pfVar5[-2] = (float)(fVar10 * (float10)_DAT_004bc420);
    *pfVar5 = (float)(fVar11 * fVar1);
    pfVar5[-1] = 0.0;
    pfVar5 = pfVar5 + 6;
  } while (fVar9 < fVar8 - fVar2);
  fVar3 = SQRT((DAT_00503038 - DAT_00503050) * (DAT_00503038 - DAT_00503050) +
               (DAT_00503040 - DAT_00503058) * (DAT_00503040 - DAT_00503058)) * _DAT_004bc430;
  DAT_00503034 = iVar7;
  if (iVar7 < iVar7 * 2) {
    DAT_00503034 = iVar7 * 2;
    puVar4 = &DAT_00503040 + iVar7 * 6;
    puVar6 = &DAT_00503040;
    do {
      puVar4[-2] = puVar6[-2];
      *puVar4 = *puVar6;
      iVar7 = iVar7 + -1;
      puVar4[-1] = (float)puVar6[-1] + fVar3;
      puVar4 = puVar4 + 6;
      puVar6 = puVar6 + 6;
    } while (iVar7 != 0);
  }
  return;
}


