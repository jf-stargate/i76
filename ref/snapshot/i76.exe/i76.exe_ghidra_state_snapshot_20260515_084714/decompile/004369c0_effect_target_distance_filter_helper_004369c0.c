/*
 * Program: i76.exe
 * Function: effect_target_distance_filter_helper_004369c0
 * Entry: 004369c0
 * Signature: undefined __cdecl effect_target_distance_filter_helper_004369c0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: effect target distance filter helper
   based on prior focused closure context. */

void __cdecl effect_target_distance_filter_helper_004369c0(int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  undefined3 extraout_var;
  float *pfVar7;
  int iVar8;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x60)) {
    if (((*(byte *)(param_1 + 0x10) & 1) == 0) &&
       (bVar6 = ensure_world_object_geometry_variant_binding(param_1,0),
       CONCAT31(extraout_var,bVar6) == 1)) {
      local_50 = 1e+30;
      local_54 = 1e+30;
      local_5c = -1e+30;
      iVar1 = *(int *)(param_1 + 0x5c);
      local_60 = -1e+30;
      iVar8 = *(int *)(iVar1 + 4);
      local_4c = 1e+30;
      local_58 = -1e+30;
      if (0 < iVar8) {
        pfVar7 = *(float **)(iVar1 + 0xc);
        do {
          fVar2 = *pfVar7;
          fVar3 = pfVar7[1];
          fVar4 = pfVar7[2];
          if (fVar2 < local_54) {
            local_54 = fVar2;
          }
          if (fVar3 < local_50) {
            local_50 = fVar3;
          }
          if (fVar4 < local_4c) {
            local_4c = fVar4;
          }
          if (local_60 < fVar2) {
            local_60 = fVar2;
          }
          if (local_5c < fVar3) {
            local_5c = fVar3;
          }
          if (local_58 < fVar4) {
            local_58 = fVar4;
          }
          pfVar7 = pfVar7 + 3;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      fVar2 = (local_60 + local_54) * _DAT_004bd020;
      *(float *)(param_1 + 0x94) = local_54;
      *(float *)(param_1 + 0x98) = local_50;
      *(float *)(param_1 + 0x9c) = local_4c;
      fVar3 = (local_5c + local_50) * _DAT_004bd020;
      *(float *)(param_1 + 0xa0) = local_60;
      *(float *)(param_1 + 0xa4) = local_5c;
      *(float *)(param_1 + 0xa8) = local_58;
      fVar4 = (local_58 + local_4c) * _DAT_004bd020;
      *(float *)(param_1 + 0x84) = fVar2;
      *(float *)(param_1 + 0x88) = fVar3;
      fVar2 = _DAT_004bd028;
      *(float *)(param_1 + 0x8c) = fVar4;
      iVar8 = *(int *)(iVar1 + 4);
      if (0 < iVar8) {
        pfVar7 = *(float **)(iVar1 + 0xc);
        do {
          fVar3 = *pfVar7 - *(float *)(param_1 + 0x84);
          fVar4 = pfVar7[1] - *(float *)(param_1 + 0x88);
          fVar5 = pfVar7[2] - *(float *)(param_1 + 0x8c);
          fVar3 = fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3;
          if (fVar2 < fVar3) {
            fVar2 = fVar3;
          }
          pfVar7 = pfVar7 + 3;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      *(float *)(param_1 + 0x90) = SQRT(fVar2);
    }
    if (*(int *)(param_1 + 100) != 0) {
      effect_target_distance_filter_helper_004369c0(*(int *)(param_1 + 100));
    }
  }
  return;
}


