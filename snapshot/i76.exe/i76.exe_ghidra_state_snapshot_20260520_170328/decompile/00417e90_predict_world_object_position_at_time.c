/*
 * Program: i76.exe
 * Function: predict_world_object_position_at_time
 * Entry: 00417e90
 * Signature: undefined __cdecl predict_world_object_position_at_time(int param_1, float param_2, float * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe weapon/projectile v27; confidence=high] Predicts a world-object position at a
   future time with special vehicle motion handling. */

void __cdecl predict_world_object_position_at_time(int param_1,float param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  float *pfVar6;
  float10 fVar7;
  float10 fVar8;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40 [10];
  double local_18;
  double local_10;
  double local_8;
  
  iVar3 = is_vehicle_or_actor_runtime_world_object(param_1);
  if (iVar3 == 0) {
    pfVar4 = (float *)get_cached_world_object_aim_position(&local_64,param_1);
    *param_3 = *pfVar4;
    param_3[1] = pfVar4[1];
    param_3[2] = pfVar4[2];
    return;
  }
  iVar3 = get_vehicle_runtime_context(param_1);
  fVar2 = *(float *)(iVar3 + 0xcc);
  pfVar4 = (float *)(param_1 + 0x18);
  pfVar6 = local_40;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar6 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar6 = pfVar6 + 1;
  }
  local_70 = (float)local_18;
  local_6c = (float)local_10;
  local_68 = (float)local_8;
  get_world_object_damage_or_target_vectors(param_1,&local_58,&local_74);
  if ((float)_DAT_004bc908 <= ABS(fVar2)) {
    fVar1 = _DAT_004bc91c;
    if (_DAT_004bc914 < fVar2) {
      fVar1 = _DAT_004bc918;
    }
    fVar7 = (float10)*(float *)(iVar3 + 0xe8) * (float10)fVar1;
    fVar1 = (float)fVar7;
    local_74 = local_74 / ABS(fVar2);
    fVar8 = ((float10)param_2 - (float10)_DAT_004bc910) * (float10)fVar1 * (float10)fVar2 -
            fVar7 * (float10)_DAT_004bc920;
    fVar7 = (float10)fsin(fVar8);
    fVar8 = (float10)fcos((float10)(float)fVar8);
    fVar1 = fVar1 * local_74;
    local_64 = fVar1 * local_40[0] + local_70;
    local_5c = fVar1 * local_40[2] + local_68;
    local_4c = (float)(fVar7 * (float10)local_74);
    local_60 = local_6c;
    local_48 = _DAT_004bc914;
    local_44 = (float)(fVar8 * (float10)local_74);
    local_18 = (double)local_64;
    local_10 = (double)local_6c;
    local_8 = (double)local_5c;
    transform_vec3_array_by_matrix(param_3,&local_4c,1,local_40);
    return;
  }
  fVar2 = param_2 - _DAT_004bc910;
  *param_3 = fVar2 * local_58 + local_70;
  param_3[1] = fVar2 * local_54 + local_6c;
  param_3[2] = fVar2 * local_50 + local_68;
  return;
}


