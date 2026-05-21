/*
 * Program: i76.exe
 * Function: compute_world_object_bounding_radius_from_point
 * Entry: 00458fc0
 * Signature: float10 __cdecl compute_world_object_bounding_radius_from_point(int param_1, float param_2, float param_3, float param_4)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium] Computes world-object bounding
   radius/distance from point data; appears in geometry/object bounds path. */

float10 __cdecl
compute_world_object_bounding_radius_from_point
          (int param_1,float param_2,float param_3,float param_4)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float10 fVar4;
  float local_80 [10];
  double local_58;
  double local_50;
  double local_48;
  float local_40 [16];
  
  pfVar1 = (float *)&DAT_004faed8;
  pfVar3 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  local_58 = (double)param_2;
  local_50 = (double)param_3;
  local_48 = (double)param_4;
  pfVar1 = compose_matrix_or_transform_a(local_40,local_80,(float *)(param_1 + 0x18));
  pfVar3 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  pfVar1 = (float *)compose_matrix_or_transform_b(local_80,local_40);
  pfVar3 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  fVar4 = compute_object_bounds_from_runtime_geometry(param_1,local_80,0.0);
  return SQRT(fVar4);
}


