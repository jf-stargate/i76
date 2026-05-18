/*
 * Program: i76.exe
 * Function: vec3_length
 * Entry: 004162f0
 * Signature: float10 __cdecl vec3_length(float param_1, float param_2, float param_3)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Returns Euclidean length of a 3-component vector
   supplied as separate floats. */

float10 __cdecl vec3_length(float param_1,float param_2,float param_3)

{
  return SQRT((float10)param_3 * (float10)param_3 +
              (float10)param_2 * (float10)param_2 + (float10)param_1 * (float10)param_1);
}


