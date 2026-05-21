/*
 * Program: i76.exe
 * Function: decode_ai_maneuver_direction_code_to_vector
 * Entry: 0041a330
 * Signature: undefined __cdecl decode_ai_maneuver_direction_code_to_vector(float param_1, float * param_2, float * param_3, float * param_4, float * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Maps small maneuver/direction selector codes into
   signed direction/scalar components used by AI steering helpers. */

void __cdecl
decode_ai_maneuver_direction_code_to_vector
          (float param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar6 = param_1;
  switch(param_1) {
  case 0.0:
    param_1 = 1.0;
    fVar6 = _DAT_004bc9b4;
    break;
  case 1.4013e-45:
    param_1 = -1.0;
    fVar6 = _DAT_004bc9b4;
    break;
  case 2.8026e-45:
    param_1 = 1.0;
    fVar6 = _DAT_004bc91c;
    break;
  case 4.2039e-45:
    param_1 = -1.0;
    fVar6 = _DAT_004bc91c;
    break;
  case 5.60519e-45:
    param_1 = 1.0;
    fVar6 = _DAT_004bc914;
    break;
  case 7.00649e-45:
    param_1 = -1.0;
    fVar6 = _DAT_004bc914;
    break;
  case 8.40779e-45:
    param_1 = 1.0;
    fVar6 = _DAT_004bc918;
    break;
  case 9.80909e-45:
    param_1 = -1.0;
    fVar6 = _DAT_004bc918;
    break;
  case 1.12104e-44:
    param_1 = 1.0;
    fVar6 = _DAT_004bca38;
    break;
  case 1.26117e-44:
    param_1 = -1.0;
    fVar6 = _DAT_004bca38;
  }
  fVar6 = fVar6 * _DAT_004bca20;
  fVar1 = *param_4;
  fVar2 = param_4[1];
  fVar3 = param_4[2];
  *param_5 = fVar1 * fVar6;
  param_5[1] = fVar2 * fVar6;
  param_5[2] = fVar3 * fVar6;
  fVar7 = param_1 * _DAT_004bca3c;
  fVar4 = param_3[1];
  fVar5 = param_3[2];
  fVar8 = *param_3 * fVar7 + fVar1 * fVar6;
  *param_5 = fVar8;
  fVar4 = fVar4 * fVar7 + fVar2 * fVar6;
  param_5[1] = fVar4;
  fVar2 = fVar5 * fVar7 + fVar3 * fVar6;
  param_5[2] = fVar2;
  fVar6 = param_2[1];
  fVar1 = param_2[2];
  *param_5 = *param_2 + fVar8;
  param_5[1] = fVar6 + fVar4;
  param_5[2] = fVar1 + fVar2;
  return;
}


