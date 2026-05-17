/*
 * Program: i76.exe
 * Function: weapon_ordnance_query_context_helper_004a7800
 * Entry: 004a7800
 * Signature: undefined4 __cdecl weapon_ordnance_query_context_helper_004a7800(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was ordnance_weapon_query_context_helper_004a7800. Normalize query
   label ordering. */

undefined4 __cdecl weapon_ordnance_query_context_helper_004a7800(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  int local_70;
  uint local_58;
  uint local_50;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  
  fVar4 = (float)*(double *)(param_1 + 0x40);
  fVar5 = (float)*(double *)(param_1 + 0x48);
  fVar6 = (float)*(double *)(param_1 + 0x50);
  fVar1 = *param_2 - fVar4;
  fVar3 = param_2[1] - fVar5;
  fVar2 = param_2[2] - fVar6;
  fVar7 = _DAT_004beb54 / SQRT(fVar2 * fVar2 + fVar3 * fVar3 + fVar1 * fVar1);
  iVar11 = ftol();
  local_70 = 0;
  fVar8 = fVar6;
  fVar9 = fVar4;
  fVar10 = fVar5;
  local_38 = fVar4;
  local_34 = fVar5;
  local_30 = fVar6;
  if (iVar11 + 1 < 0) {
    return 0;
  }
  while( true ) {
    local_40 = fVar10;
    local_44 = fVar9;
    local_3c = fVar8;
    local_58 = SUB84((double)(_DAT_006442c4 * local_44 + (float)_DAT_004faf18),0);
    local_50 = SUB84((double)(_DAT_006442c4 * local_3c + (float)_DAT_004faf18),0);
    if (((0x2800 - local_50 | 0x2800 - local_58 | local_50 | local_58) & 0x80000000) != 0) {
      *param_2 = fVar4;
      param_2[1] = fVar5;
      param_2[2] = fVar6;
      return 1;
    }
    apply_world_object_transform_to_bounds_or_geometry((double)local_44,(double)local_3c);
    if ((float10)local_40 <= extraout_ST0) break;
    local_70 = local_70 + 1;
    fVar8 = fVar2 * fVar7 + local_3c;
    fVar9 = fVar7 * fVar1 + local_44;
    fVar10 = fVar3 * fVar7 + local_40;
    local_38 = local_44;
    local_34 = local_40;
    local_30 = local_3c;
    if (iVar11 + 1 < local_70) {
      return 0;
    }
  }
  if (local_70 == 0) {
    *param_2 = local_44;
    param_2[1] = local_40;
    param_2[2] = local_3c;
    return 1;
  }
  iVar11 = 0;
  do {
    fVar2 = (local_3c - local_30) * _DAT_004beb60 + local_30;
    fVar1 = (local_44 - local_38) * _DAT_004beb60 + local_38;
    fVar3 = (local_40 - local_34) * _DAT_004beb60 + local_34;
    apply_world_object_transform_to_bounds_or_geometry((double)fVar1,(double)fVar2);
    if (fVar3 - (float)extraout_ST0_00 < _DAT_004beb64) {
      *param_2 = fVar1;
      param_2[1] = fVar3;
      param_2[2] = fVar2;
      return 1;
    }
    fVar4 = fVar1;
    fVar5 = fVar3;
    fVar6 = fVar2;
    if (fVar3 < (float)extraout_ST0_00) {
      local_44 = fVar1;
      local_40 = fVar3;
      local_3c = fVar2;
      fVar4 = local_38;
      fVar5 = local_34;
      fVar6 = local_30;
    }
    local_30 = fVar6;
    local_34 = fVar5;
    local_38 = fVar4;
    iVar11 = iVar11 + 1;
  } while (iVar11 < 9);
  *param_2 = fVar1;
  param_2[1] = fVar3;
  param_2[2] = fVar2;
  return 1;
}


