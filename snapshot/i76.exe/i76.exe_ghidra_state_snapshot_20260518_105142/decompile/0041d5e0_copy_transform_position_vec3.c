/*
 * Program: i76.exe
 * Function: copy_transform_position_vec3
 * Entry: 0041d5e0
 * Signature: undefined __cdecl copy_transform_position_vec3(float * param_1, int param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Copies a transform/world-object position vector from
   offsets +0x28/+0x30/+0x38 into a float[3]. */

void __cdecl copy_transform_position_vec3(float *param_1,int param_2)

{
  double dVar1;
  double dVar2;
  
  dVar1 = *(double *)(param_2 + 0x30);
  dVar2 = *(double *)(param_2 + 0x38);
  *param_1 = (float)*(double *)(param_2 + 0x28);
  param_1[1] = (float)dVar1;
  param_1[2] = (float)dVar2;
  return;
}


