/*
 * Program: i76.exe
 * Function: predict_ai_target_lead_position_for_weapon_fire
 * Entry: 00419600
 * Signature: undefined __cdecl predict_ai_target_lead_position_for_weapon_fire(float * param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Computes a lead/predicted target position from target
   distance, projectile/vehicle vectors, and predict_world_object_position_at_time. */

void __cdecl
predict_ai_target_lead_position_for_weapon_fire(float *param_1,float param_2,float param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float local_30;
  float local_2c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  fVar7 = param_3;
  dVar1 = *(double *)((int)param_2 + 0x40);
  dVar2 = *(double *)((int)param_2 + 0x48);
  dVar3 = *(double *)((int)param_2 + 0x50);
  fVar4 = (float)*(double *)((int)param_3 + 0x40) - (float)dVar1;
  fVar5 = (float)*(double *)((int)param_3 + 0x48) - (float)dVar2;
  fVar6 = (float)*(double *)((int)param_3 + 0x50) - (float)dVar3;
  get_world_object_damage_or_target_vectors((int)param_2,&local_c,&param_2);
  param_3 = SQRT(fVar6 * fVar6 + fVar5 * fVar5 + fVar4 * fVar4) / (param_2 - _DAT_004bca00);
  if (_DAT_004bc9d4 <= param_3) {
    if (_DAT_004bca04 < param_3) {
      param_3 = 1.75;
    }
  }
  else {
    param_3 = 0.4;
  }
  predict_world_object_position_at_time((int)fVar7,param_3,&local_18);
  fVar4 = _DAT_004bc91c / param_3;
  fVar5 = (local_14 - (float)dVar2) * fVar4;
  fVar6 = fVar4 * (local_18 - (float)dVar1);
  fVar4 = (local_10 - (float)dVar3) * fVar4;
  fVar7 = SQRT(fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6);
  if (fVar7 <= _DAT_004bca08) {
    if ((fVar7 <= _DAT_004bc934) || (_DAT_004bc938 <= fVar7)) {
      fVar7 = (param_2 * _DAT_004bca0c) / fVar7;
      local_30 = fVar7 * fVar6;
      local_2c = fVar5 * fVar7;
      fVar7 = fVar4 * fVar7;
    }
    else {
      local_30 = fVar6 * _DAT_004bc92c;
      local_2c = fVar5 * _DAT_004bc92c;
      fVar7 = fVar4 * _DAT_004bc92c;
    }
  }
  else {
    fVar7 = _DAT_004bc91c - _DAT_004bca08 / fVar7;
    local_30 = fVar7 * fVar6;
    local_2c = fVar5 * fVar7;
    fVar7 = fVar4 * fVar7;
  }
  if (_DAT_004bc914 < local_4 * fVar7 + local_8 * local_2c + local_c * local_30) {
    *param_1 = local_30;
    param_1[1] = local_2c;
    param_1[2] = fVar7;
    return;
  }
  *param_1 = fVar6;
  param_1[1] = fVar5;
  param_1[2] = fVar4;
  return;
}


