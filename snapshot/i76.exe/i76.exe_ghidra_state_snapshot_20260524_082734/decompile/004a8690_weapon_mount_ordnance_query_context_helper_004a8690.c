/*
 * Program: i76.exe
 * Function: weapon_mount_ordnance_query_context_helper_004a8690
 * Entry: 004a8690
 * Signature: undefined __cdecl weapon_mount_ordnance_query_context_helper_004a8690(float * param_1, float * param_2, float * param_3, float * param_4, float * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was ordnance_weapon_mount_query_context_helper_004a8690. Normalize
   query label ordering. */

void __cdecl
weapon_mount_ordnance_query_context_helper_004a8690
          (float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float10 fVar7;
  float10 extraout_ST0;
  uint local_78;
  uint local_10;
  
  *param_3 = 0.0;
  fVar7 = get_runtime_update_delta_seconds();
  *param_4 = *param_1;
  param_4[1] = param_1[1];
  param_4[2] = param_1[2];
  fVar1 = (float)fVar7;
  *param_5 = *param_2;
  param_5[1] = param_2[1];
  param_5[2] = param_2[2];
  fVar4 = _DAT_004beb88 * 0.0;
  fVar5 = fVar1 * -39.2 * _DAT_004beb88;
  fVar6 = fVar1 * 0.0 * _DAT_004beb88;
  do {
    fVar2 = param_5[1];
    fVar3 = param_5[2];
    *param_4 = (*param_5 - fVar4) * fVar1 + *param_4;
    param_4[1] = (fVar2 - fVar5) * fVar1 + param_4[1];
    param_4[2] = (fVar3 - fVar6) * fVar1 + param_4[2];
    *param_5 = *param_5 + 0.0;
    param_5[1] = param_5[1] + fVar1 * -39.2;
    param_5[2] = param_5[2] + fVar1 * 0.0;
    *param_3 = fVar1 + *param_3;
    local_78 = SUB84((double)(_DAT_006442c4 * *param_4 + (float)_DAT_004faf18),0);
    local_10 = SUB84((double)(_DAT_006442c4 * param_4[2] + (float)_DAT_004faf18),0);
    if (((0x2800 - local_10 | 0x2800 - local_78 | local_10 | local_78) & 0x80000000) == 0) {
      apply_world_object_transform_to_bounds_or_geometry((double)*param_4,(double)param_4[2]);
      fVar7 = extraout_ST0;
    }
    else {
      fVar7 = (float10)_DAT_004beb80;
    }
  } while (fVar7 < (float10)param_4[1]);
  param_4[1] = (float)(fVar7 - (float10)_DAT_004beb8c);
  return;
}


