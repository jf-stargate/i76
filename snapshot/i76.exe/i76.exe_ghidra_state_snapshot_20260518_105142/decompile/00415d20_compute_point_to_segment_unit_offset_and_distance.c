/*
 * Program: i76.exe
 * Function: compute_point_to_segment_unit_offset_and_distance
 * Entry: 00415d20
 * Signature: undefined __cdecl compute_point_to_segment_unit_offset_and_distance(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9, float * param_10, float * param_11)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Computes the closest offset from a point to a segment,
   returning unit offset vector and distance. */

void __cdecl
compute_point_to_segment_unit_offset_and_distance
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7,float param_8,float param_9,float *param_10,float *param_11)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar8 = _DAT_004bc844;
  fVar1 = param_7 - param_4;
  fVar4 = param_8 - param_5;
  fVar3 = param_9 - param_6;
  fVar2 = (fVar3 * (param_3 - param_6) + fVar4 * (param_2 - param_5) + fVar1 * (param_1 - param_4))
          / (fVar3 * fVar3 + fVar4 * fVar4 + fVar1 * fVar1);
  fVar5 = param_1 - (fVar2 * fVar1 + param_4);
  fVar7 = param_2 - (fVar4 * fVar2 + param_5);
  fVar6 = param_3 - (fVar3 * fVar2 + param_6);
  fVar2 = SQRT(fVar6 * fVar6 + fVar7 * fVar7 + fVar5 * fVar5);
  *param_11 = fVar2;
  if ((fVar8 < fVar2) && (fVar2 < _DAT_004bc848)) {
    *param_10 = -fVar3;
    param_10[1] = fVar4;
    param_10[2] = fVar1;
    return;
  }
  fVar2 = _DAT_004bc84c / fVar2;
  *param_10 = fVar2 * fVar5;
  param_10[1] = fVar7 * fVar2;
  param_10[2] = fVar6 * fVar2;
  return;
}


