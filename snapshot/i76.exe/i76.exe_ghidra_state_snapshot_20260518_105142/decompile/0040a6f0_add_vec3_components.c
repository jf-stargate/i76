/*
 * Program: i76.exe
 * Function: add_vec3_components
 * Entry: 0040a6f0
 * Signature: undefined __cdecl add_vec3_components(float * param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Adds two 3-component vectors and writes the result
   to the output vector. */

void __cdecl
add_vec3_components(float *param_1,float param_2,float param_3,float param_4,float param_5,
                   float param_6,float param_7)

{
  *param_1 = param_5 + param_2;
  param_1[1] = param_6 + param_3;
  param_1[2] = param_7 + param_4;
  return;
}


