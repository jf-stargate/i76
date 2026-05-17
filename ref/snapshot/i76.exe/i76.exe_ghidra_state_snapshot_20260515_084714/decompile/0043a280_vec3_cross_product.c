/*
 * Program: i76.exe
 * Function: vec3_cross_product
 * Entry: 0043a280
 * Signature: undefined __cdecl vec3_cross_product(float * param_1, float * param_2, float * param_3)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Computes dst = cross(a,b).
    */

void __cdecl vec3_cross_product(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar1 = *param_3;
  fVar2 = *param_2;
  fVar3 = *param_2;
  fVar4 = *param_3;
  fVar5 = param_2[2];
  fVar6 = param_3[2];
  fVar7 = param_3[1];
  fVar8 = param_2[1];
  *param_1 = param_3[2] * param_2[1] - param_2[2] * param_3[1];
  param_1[1] = fVar1 * fVar5 - fVar2 * fVar6;
  param_1[2] = fVar3 * fVar7 - fVar4 * fVar8;
  return;
}


