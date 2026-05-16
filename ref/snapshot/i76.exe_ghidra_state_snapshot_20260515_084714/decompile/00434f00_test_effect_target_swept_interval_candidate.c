/*
 * Program: i76.exe
 * Function: test_effect_target_swept_interval_candidate
 * Entry: 00434f00
 * Signature: undefined4 __cdecl test_effect_target_swept_interval_candidate(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9, float param_10, float param_11, float param_12, float param_13, float param_14, float * param_15, float * param_16)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Effect-target swept interval/collision helper used by
   projectile and vehicle effect scans. */

undefined4 __cdecl
test_effect_target_swept_interval_candidate
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7,float param_8,float param_9,float param_10,float param_11,float param_12,
          float param_13,float param_14,float *param_15,float *param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  if (((((param_4 * param_4 < _DAT_004bcff0) && (param_5 * param_5 < _DAT_004bcff0)) &&
       (param_6 * param_6 < _DAT_004bcff0)) &&
      ((param_10 * param_10 < _DAT_004bcff0 && (param_11 * param_11 < _DAT_004bcff0)))) &&
     (param_12 * param_12 < _DAT_004bcff0)) {
    return 0;
  }
  fVar5 = param_4 - param_10;
  fVar1 = param_5 - param_11;
  fVar4 = param_6 - param_12;
  fVar2 = fVar4 * fVar4 + fVar1 * fVar1 + fVar5 * fVar5;
  param_1 = param_7 - param_1;
  param_2 = param_8 - param_2;
  param_3 = param_9 - param_3;
  if ((fVar2 < _DAT_004bcff4) ||
     (fVar2 = (fVar4 * param_3 + fVar1 * param_2 + fVar5 * param_1) / fVar2, param_14 < fVar2)) {
    fVar2 = param_14;
  }
  fVar3 = _DAT_004bcfe0;
  if (_DAT_004bcfe0 < fVar2) {
    fVar3 = -fVar2;
    param_1 = fVar3 * fVar5 + param_1;
    param_2 = fVar3 * fVar1 + param_2;
    param_3 = fVar3 * fVar4 + param_3;
    fVar3 = fVar2;
  }
  *param_15 = fVar3;
  if (param_3 * param_3 + param_2 * param_2 + param_1 * param_1 <= param_13 * param_13) {
    *param_16 = param_1;
    param_16[1] = param_2;
    param_16[2] = param_3;
    return 1;
  }
  return 0;
}


