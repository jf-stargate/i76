/*
 * Program: i76.exe
 * Function: store_vec3_as_double_triplet
 * Entry: 0043a300
 * Signature: undefined __cdecl store_vec3_as_double_triplet(int param_1, float * param_2)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Stores a 3-float
   vector into three double fields. */

void __cdecl store_vec3_as_double_triplet(int param_1,float *param_2)

{
  *(double *)(param_1 + 0x28) = (double)*param_2;
  *(double *)(param_1 + 0x30) = (double)param_2[1];
  *(double *)(param_1 + 0x38) = (double)param_2[2];
  return;
}


