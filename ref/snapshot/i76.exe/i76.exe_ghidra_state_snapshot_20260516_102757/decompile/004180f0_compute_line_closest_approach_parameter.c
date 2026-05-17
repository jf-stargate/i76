/*
 * Program: i76.exe
 * Function: compute_line_closest_approach_parameter
 * Entry: 004180f0
 * Signature: float10 __cdecl compute_line_closest_approach_parameter(float * param_1, float * param_2, float * param_3, float * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe weapon/projectile v27; confidence=high] Math helper computing closest-approach
   parameter between moving/line vectors. */

float10 __cdecl
compute_line_closest_approach_parameter(float *param_1,float *param_2,float *param_3,float *param_4)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  
  fVar1 = (float10)*param_4 - (float10)*param_2;
  fVar2 = (float10)param_4[1] - (float10)param_2[1];
  fVar3 = (float10)param_4[2] - (float10)param_2[2];
  fVar4 = fVar3 * fVar3 + fVar2 * fVar2 + fVar1 * fVar1;
  if (ABS(fVar4) < (float10)_DAT_004bc924) {
    return (float10)_DAT_004bc928;
  }
  return (fVar3 * (float10)(param_1[2] - param_3[2]) +
         fVar2 * (float10)(param_1[1] - param_3[1]) +
         fVar1 * ((float10)*param_1 - (float10)*param_3)) / fVar4;
}


