/*
 * Program: i76.exe
 * Function: vec3_madd_xyz
 * Entry: 004195a0
 * Signature: undefined __cdecl vec3_madd_xyz(float * param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7, float param_8)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Computes dst = base +
   scale * vector from scalar xyz inputs. */

void __cdecl
vec3_madd_xyz(float *param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
             float param_7,float param_8)

{
  *param_1 = param_6 * param_5 + param_2;
  param_1[1] = param_7 * param_5 + param_3;
  param_1[2] = param_8 * param_5 + param_4;
  return;
}


