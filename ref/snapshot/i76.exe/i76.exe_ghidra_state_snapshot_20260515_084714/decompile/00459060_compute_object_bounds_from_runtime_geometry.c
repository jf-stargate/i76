/*
 * Program: i76.exe
 * Function: compute_object_bounds_from_runtime_geometry
 * Entry: 00459060
 * Signature: float10 __cdecl compute_object_bounds_from_runtime_geometry(int param_1, float * param_2, float param_3)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium] Likely computes object bounds
   from runtime geometry records; candidate downstream geometry consumer. */

float10 __cdecl
compute_object_bounds_from_runtime_geometry(int param_1,float *param_2,float param_3)

{
  float fVar1;
  bool bVar2;
  float *pfVar3;
  undefined3 extraout_var;
  int iVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  float10 fVar8;
  float local_8c;
  float local_88;
  float local_84;
  float local_80 [16];
  float local_40 [16];
  
  do {
    pfVar3 = compose_matrix_or_transform_a(local_40,(float *)(param_1 + 0x18),param_2);
    pfVar6 = local_80;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar6 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar6 = pfVar6 + 1;
    }
    if (((*(byte *)(param_1 + 0x10) & 1) == 0) &&
       (bVar2 = ensure_world_object_geometry_variant_binding(param_1,0),
       CONCAT31(extraout_var,bVar2) == 1)) {
      iVar4 = *(int *)(param_1 + 0x5c);
      iVar7 = 0;
      if (0 < *(int *)(iVar4 + 4)) {
        iVar5 = 0;
        do {
          transform_vec3_array_by_matrix
                    (&local_8c,(float *)(*(int *)(iVar4 + 0xc) + iVar5),1,local_80);
          fVar1 = local_84 * local_84 + local_88 * local_88 + local_8c * local_8c;
          if (param_3 < fVar1) {
            param_3 = fVar1;
          }
          iVar7 = iVar7 + 1;
          iVar5 = iVar5 + 0xc;
        } while (iVar7 < *(int *)(iVar4 + 4));
      }
    }
    if (*(int *)(param_1 + 100) != 0) {
      fVar8 = compute_object_bounds_from_runtime_geometry(*(int *)(param_1 + 100),local_80,param_3);
      param_3 = (float)fVar8;
    }
    param_1 = *(int *)(param_1 + 0x60);
  } while (param_1 != 0);
  return (float10)param_3;
}


