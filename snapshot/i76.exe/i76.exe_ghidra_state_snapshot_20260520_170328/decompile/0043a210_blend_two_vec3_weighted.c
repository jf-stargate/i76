/*
 * Program: i76.exe
 * Function: blend_two_vec3_weighted
 * Entry: 0043a210
 * Signature: undefined __cdecl blend_two_vec3_weighted(float * param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9)
 */


/* [cgpt i76.exe vehicle physics integrator rename v31; confidence=high] Simple vector helper
   computing dst = a * weightA + b * weightB. */

void __cdecl
blend_two_vec3_weighted
          (float *param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7,float param_8,float param_9)

{
  *param_1 = param_7 * param_6 + param_3 * param_2;
  param_1[1] = param_8 * param_6 + param_4 * param_2;
  param_1[2] = param_9 * param_6 + param_5 * param_2;
  return;
}


