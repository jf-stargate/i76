/*
 * Program: i76.exe
 * Function: transform_vec3_array_by_matrix
 * Entry: 00494da0
 * Signature: undefined __cdecl transform_vec3_array_by_matrix(float * param_1, float * param_2, int param_3, float * param_4)
 */


/* [cgpt i76.exe GEO lighting/render renames v33; confidence=high] Transforms an array of vec3
   positions by a matrix; used for runtime_geometry +0x0c position table. */

void __cdecl
transform_vec3_array_by_matrix(float *param_1,float *param_2,int param_3,float *param_4)

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
  double dVar13;
  double dVar14;
  bool bVar15;
  
  bVar15 = false;
  for (; param_3 != 0 && bVar15 == param_3 < 0; param_3 = param_3 + -1) {
    fVar1 = param_4[1];
    fVar2 = *param_2;
    fVar3 = param_4[2];
    fVar4 = *param_2;
    fVar5 = param_4[4];
    fVar6 = param_2[1];
    fVar7 = param_4[5];
    fVar8 = param_2[1];
    fVar9 = param_4[7];
    fVar10 = param_2[2];
    fVar11 = param_4[8];
    fVar12 = param_2[2];
    dVar13 = *(double *)(param_4 + 0xc);
    dVar14 = *(double *)(param_4 + 0xe);
    *param_1 = param_4[6] * param_2[2] + param_4[3] * param_2[1] + *param_4 * *param_2 +
               (float)*(double *)(param_4 + 10);
    param_1[2] = fVar11 * fVar12 + fVar7 * fVar8 + fVar3 * fVar4 + (float)dVar14;
    param_1[1] = fVar9 * fVar10 + fVar5 * fVar6 + fVar1 * fVar2 + (float)dVar13;
    param_1 = param_1 + 3;
    param_2 = param_2 + 3;
    bVar15 = SBORROW4(param_3,1);
  }
  return;
}


