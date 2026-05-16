/*
 * Program: i76.exe
 * Function: effect_target_scan_target_query_helper_00436d90
 * Entry: 00436d90
 * Signature: undefined __cdecl effect_target_scan_target_query_helper_00436d90(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: likely effect_target_scan /
   target_query_helper based on address neighborhood and prior focused closure context. */

void __cdecl effect_target_scan_target_query_helper_00436d90(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  int iVar9;
  float local_7c;
  float local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  piVar4 = *(int **)(param_1 + 0x18);
  local_60 = (float)piVar4[3];
  local_5c = piVar4[8];
  local_58 = piVar4[0xb];
  piVar1 = piVar4 + *piVar4 + 2;
  local_54 = piVar4[*piVar4 + 2];
  local_50 = piVar4[8];
  local_4c = piVar4[0xb];
  piVar2 = piVar4 + piVar4[2] + 10;
  local_48 = *piVar1;
  local_44 = piVar4[8];
  local_40 = piVar4[piVar4[2] + 10];
  local_3c = piVar4[3];
  local_38 = piVar4[8];
  local_34 = *piVar2;
  piVar3 = piVar4 + piVar4[1] + 6;
  local_30 = piVar4[3];
  local_2c = piVar4[piVar4[1] + 6];
  local_28 = piVar4[0xb];
  local_24 = *piVar1;
  local_20 = *piVar3;
  local_18 = *piVar1;
  local_1c = piVar4[0xb];
  local_14 = *piVar3;
  local_c = piVar4[3];
  local_10 = *piVar2;
  local_8 = *piVar3;
  local_4 = *piVar2;
  local_7c = -1e+30;
  pfVar8 = &local_60;
  iVar9 = 8;
  do {
    fVar5 = *pfVar8 - *(float *)(param_1 + 4);
    fVar7 = pfVar8[1] - *(float *)(param_1 + 8);
    fVar6 = pfVar8[2] - *(float *)(param_1 + 0xc);
    fVar5 = fVar6 * fVar6 + fVar7 * fVar7 + fVar5 * fVar5;
    if (local_7c < fVar5) {
      local_7c = fVar5;
    }
    pfVar8 = pfVar8 + 3;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  if (SQRT(local_7c) - _DAT_004bd02c <= *(float *)(param_1 + 0x10)) {
    return;
  }
  *(float *)(param_1 + 0x10) = SQRT(local_7c) - _DAT_004bd02c;
  return;
}


