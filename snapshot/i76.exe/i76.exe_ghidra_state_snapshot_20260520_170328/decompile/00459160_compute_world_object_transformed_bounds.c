/*
 * Program: i76.exe
 * Function: compute_world_object_transformed_bounds
 * Entry: 00459160
 * Signature: undefined __cdecl compute_world_object_transformed_bounds(int param_1, float * param_2, float * param_3)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Computes transformed
   world-object bounds using object geometry/transform state. */

void __cdecl compute_world_object_transformed_bounds(int param_1,float *param_2,float *param_3)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float local_80 [16];
  float local_40 [16];
  
  pfVar1 = (float *)compose_matrix_or_transform_b((void *)(param_1 + 0x18),local_40);
  pfVar3 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  *param_2 = 1e+07;
  param_2[1] = 1e+07;
  param_2[2] = 1e+07;
  *param_3 = -1e+07;
  param_3[1] = -1e+07;
  param_3[2] = -1e+07;
  update_world_object_bounds_from_geometry(param_1,local_80,param_2,param_3);
  return;
}


