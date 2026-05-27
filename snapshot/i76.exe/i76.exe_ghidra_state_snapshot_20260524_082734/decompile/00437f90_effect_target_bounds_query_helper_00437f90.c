/*
 * Program: i76.exe
 * Function: effect_target_bounds_query_helper_00437f90
 * Entry: 00437f90
 * Signature: undefined __cdecl effect_target_bounds_query_helper_00437f90(undefined4 * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: effect target bounds query helper
   based on prior focused closure context. */

void __cdecl effect_target_bounds_query_helper_00437f90(undefined4 *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  undefined4 *puVar8;
  int iVar9;
  float10 fVar10;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70 [4];
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40 [16];
  
  local_70[0] = 0.0;
  local_70[1] = 0.0;
  local_70[2] = 1.0;
  fVar10 = get_runtime_update_delta_seconds();
  if (*(int *)(param_2 + 0x6c) != 1) {
    puVar8 = &DAT_004faed8;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *param_1 = *puVar8;
      puVar8 = puVar8 + 1;
      param_1 = param_1 + 1;
    }
    return;
  }
  iVar9 = get_vehicle_runtime_context(param_2);
  local_4c = *(float *)(iVar9 + 0x114) * _DAT_004bd074;
  local_44 = *(float *)(iVar9 + 0x118) + *(float *)(iVar9 + 0x118);
  fVar1 = *(float *)(param_2 + 0x30);
  fVar2 = *(float *)(param_2 + 0x34);
  local_88 = *(float *)(iVar9 + 0x114) + *(float *)(iVar9 + 0x114);
  fVar3 = *(float *)(param_2 + 0x38);
  local_80 = *(float *)(iVar9 + 0x118) + *(float *)(iVar9 + 0x118);
  local_70[3] = _DAT_004bd03c;
  local_5c = *(float *)(iVar9 + 0x118) * _DAT_004bd074;
  fVar4 = *(float *)(param_2 + 0x18);
  fVar5 = *(float *)(param_2 + 0x1c);
  fVar6 = *(float *)(param_2 + 0x20);
  zone_satellite_map_context_helper_00493ca0
            (*(float *)(iVar9 + 0xd4),*(float *)(iVar9 + 0xd8),*(float *)(iVar9 + 0xdc),fVar1,fVar2,
             fVar3,&local_7c,&local_94);
  fVar2 = (local_7c * fVar1 + local_74 * fVar3 + local_78 * fVar2) * _DAT_004bd040;
  fVar4 = (local_94 * fVar4 + local_8c * fVar6 + local_90 * fVar5) * _DAT_004bd040;
  fVar1 = (float)fVar10 + (float)fVar10;
  fVar3 = fVar2 - fVar4;
  if (((_DAT_004bd03c <= fVar1) && (fVar1 <= (float)DWORD_004bd05c)) &&
     ((float)_DWORD_004bd060 <= ABS(fVar3 - _DAT_0052b93c))) {
    fVar3 = fVar1 * (fVar3 - _DAT_0052b93c) + _DAT_0052b93c;
  }
  _DAT_0052b93c = fVar3;
  fVar4 = fVar4 + fVar2;
  if (((_DAT_004bd03c <= fVar1) && (fVar1 <= (float)DWORD_004bd05c)) &&
     ((float)_DWORD_004bd060 <= ABS(fVar4 - _DAT_0052b940))) {
    fVar4 = fVar1 * (fVar4 - _DAT_0052b940) + _DAT_0052b940;
  }
  _DAT_0052b940 = fVar4;
  fVar2 = fVar2 * _DAT_004bd078;
  if (((_DAT_004bd03c <= fVar1) && (fVar1 <= (float)DWORD_004bd05c)) &&
     ((float)_DWORD_004bd060 <= ABS(fVar2 - _DAT_0052b944))) {
    fVar2 = fVar1 * (fVar2 - _DAT_0052b944) + _DAT_0052b944;
  }
  _DAT_0052b944 = fVar2;
  local_84 = _DAT_0052b940;
  local_60 = _DAT_0052b944;
  local_48 = _DAT_0052b93c;
  pfVar7 = (float *)zone_satellite_map_context_helper_00494c80
                              (&local_94,&local_88,local_70 + 3,&local_4c);
  local_58 = *pfVar7;
  local_54 = pfVar7[1];
  local_50 = pfVar7[2];
  puVar8 = (undefined4 *)zone_satellite_map_context_helper_00494710(&local_58,local_70,local_40);
  for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
    *param_1 = *puVar8;
    puVar8 = puVar8 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


