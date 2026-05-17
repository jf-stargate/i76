/*
 * Program: i76.exe
 * Function: vec3_subtract_xyz
 * Entry: 00419550
 * Signature: undefined __cdecl vec3_subtract_xyz(float * param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Computes dst = a - b from
   scalar xyz inputs. */

void __cdecl
vec3_subtract_xyz(float *param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,float param_7)

{
  *param_1 = param_2 - param_5;
  param_1[1] = param_3 - param_6;
  param_1[2] = param_4 - param_7;
  return;
}


