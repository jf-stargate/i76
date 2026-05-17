/*
 * Program: i76.exe
 * Function: mat3_transform_vec3
 * Entry: 0043a320
 * Signature: undefined __cdecl mat3_transform_vec3(float * param_1, float * param_2, float * param_3)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Transforms a 3-vector by a
   3x3 matrix. */

void __cdecl mat3_transform_vec3(float *param_1,float *param_2,float *param_3)

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
  float fVar11;
  float fVar12;
  
  fVar1 = param_3[5];
  fVar2 = param_3[4];
  fVar3 = param_3[7];
  fVar4 = param_2[2];
  fVar5 = param_3[8];
  fVar6 = param_2[1];
  fVar7 = param_3[3];
  fVar8 = param_2[1];
  fVar9 = param_3[6];
  fVar10 = param_2[2];
  fVar11 = *param_2;
  fVar12 = *param_2;
  *param_1 = *param_3 * *param_2 + param_3[2] * param_2[2] + param_3[1] * param_2[1];
  param_1[1] = fVar7 * fVar11 + fVar2 * fVar6 + fVar1 * fVar4;
  param_1[2] = fVar9 * fVar12 + fVar5 * fVar10 + fVar3 * fVar8;
  return;
}


