/*
 * Program: i76.exe
 * Function: scale_vec3_components
 * Entry: 0041cd50
 * Signature: undefined __cdecl scale_vec3_components(float * param_1, float param_2, float param_3, float param_4, float param_5)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Writes a 3-component vector scaled by a scalar. */

void __cdecl
scale_vec3_components(float *param_1,float param_2,float param_3,float param_4,float param_5)

{
  *param_1 = param_3 * param_2;
  param_1[1] = param_4 * param_2;
  param_1[2] = param_5 * param_2;
  return;
}


