/*
 * Program: i76.exe
 * Function: sample_runtime_terrain_packed_word
 * Entry: 004931c0
 * Signature: undefined __cdecl sample_runtime_terrain_packed_word(float * param_1, double param_2, undefined4 param_3, undefined4 param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004931c0. Remove
   duplicated terrain wording.
   
   I76 rename v43: sample_runtime_terrain_packed_word
   Samples raw packed TER word through runtime page grid. */

void __cdecl
sample_runtime_terrain_packed_word
          (float *param_1,double param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  double dVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  float10 fVar11;
  uint local_14;
  uint local_c;
  
  local_14 = SUB84((double)(_DAT_006442c4 * (float)param_2 + (float)_DAT_004faf18),0);
  local_c = SUB84((double)(_DAT_006442c4 * (float)(double)CONCAT44(param_4,param_3) +
                          (float)_DAT_004faf18),0);
  if (((0x2800 - local_c | 0x2800 - local_14 | local_c | local_14) & 0x80000000) == 0) {
    iVar5 = ftol();
    iVar6 = ftol();
    if ((double)CONCAT44(param_4,param_3) - (double)iVar6 <= param_2 - (double)iVar5) {
      uVar10 = iVar6 + 0xc00;
      uVar1 = iVar5 + 0xc01;
      uVar9 = (uVar1 & 0x7f) + (uVar10 & 0x7f) * 0x80;
      iVar8 = (uVar10 & 0xffffff80) + ((int)uVar1 >> 7);
      if ((iVar8 < 0x4000) && (uVar9 < 0x4000)) {
        uVar7 = *(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar8] + uVar9 * 2) & 0xfff;
      }
      else {
        uVar7 = 0;
      }
      param_2._0_4_ = (float)uVar7;
      iVar8 = ((int)(iVar5 + 0xc00U) >> 7) + (uVar10 & 0xffffff80);
      uVar10 = (iVar5 + 0xc00U & 0x7f) + (uVar10 & 0x7f) * 0x80;
      if ((iVar8 < 0x4000) && (uVar10 < 0x4000)) {
        uVar7 = *(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar8] + uVar10 * 2) & 0xfff;
      }
      else {
        uVar7 = 0;
      }
      fVar3 = param_2._0_4_ - (float)uVar7;
      iVar5 = ((int)uVar1 >> 7) + (iVar6 + 0xc01U & 0xffffff80);
      uVar10 = (uVar1 & 0x7f) + (iVar6 + 0xc01U & 0x7f) * 0x80;
      if ((iVar5 < 0x4000) && (uVar10 < 0x4000)) {
        uVar7 = *(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar5] + uVar10 * 2) & 0xfff;
      }
      else {
        uVar7 = 0;
      }
      fVar4 = (float)uVar7;
    }
    else {
      uVar10 = iVar6 + 0xc01;
      uVar1 = iVar5 + 0xc00;
      uVar9 = (uVar1 & 0x7f) + (uVar10 & 0x7f) * 0x80;
      iVar8 = (uVar10 & 0xffffff80) + ((int)uVar1 >> 7);
      if ((iVar8 < 0x4000) && (uVar9 < 0x4000)) {
        uVar7 = *(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar8] + uVar9 * 2) & 0xfff;
      }
      else {
        uVar7 = 0;
      }
      param_2._0_4_ = (float)uVar7;
      iVar8 = (uVar10 & 0xffffff80) + ((int)(iVar5 + 0xc01U) >> 7);
      uVar10 = (iVar5 + 0xc01U & 0x7f) + (uVar10 & 0x7f) * 0x80;
      if ((iVar8 < 0x4000) && (uVar10 < 0x4000)) {
        uVar7 = *(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar8] + uVar10 * 2) & 0xfff;
      }
      else {
        uVar7 = 0;
      }
      fVar3 = param_2._0_4_ - (float)uVar7;
      iVar5 = (iVar6 + 0xc00U & 0xffffff80) + ((int)uVar1 >> 7);
      uVar10 = (uVar1 & 0x7f) + (iVar6 + 0xc00U & 0x7f) * 0x80;
      if ((iVar5 < 0x4000) && (uVar10 < 0x4000)) {
        fVar4 = (float)(*(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar5] + uVar10 * 2) &
                       0xfff);
      }
      else {
        fVar4 = 0.0;
      }
    }
    fVar3 = _DAT_006442c4 * _DAT_004be8a8 * fVar3;
    fVar4 = _DAT_006442c4 * _DAT_004be8a8 * (fVar4 - param_2._0_4_);
    dVar2 = (double)((fVar4 * fVar4 + fVar3 * fVar3) - _DAT_004be8ac);
    fVar11 = zone_satellite_map_context_helper_00495000
                       (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
    *param_1 = fVar3 * (float)fVar11;
    param_1[1] = (float)fVar11;
    param_1[2] = fVar4 * (float)fVar11;
    return;
  }
  *param_1 = 0.0;
  param_1[1] = 1.0;
  param_1[2] = 0.0;
  return;
}


