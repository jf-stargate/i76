/*
 * Program: i76.exe
 * Function: dot_product_vec3
 * Entry: 00414fb0
 * Signature: float10 __cdecl dot_product_vec3(float * param_1, float * param_2)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Returns the dot product of two 3-component float
   vectors. */

float10 __cdecl dot_product_vec3(float *param_1,float *param_2)

{
  return (float10)*param_2 * (float10)*param_1 +
         (float10)param_1[2] * (float10)param_2[2] + (float10)param_1[1] * (float10)param_2[1];
}


