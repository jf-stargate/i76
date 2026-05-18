/*
 * Program: i76.exe
 * Function: update_world_object_bounds_from_geometry
 * Entry: 004591d0
 * Signature: undefined __cdecl update_world_object_bounds_from_geometry(int param_1, float * param_2, float * param_3, float * param_4)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium] Likely updates world-object
   bounds from attached geometry data; candidate downstream geometry consumer. */

void __cdecl
update_world_object_bounds_from_geometry(int param_1,float *param_2,float *param_3,float *param_4)

{
  bool bVar1;
  float *pfVar2;
  undefined3 extraout_var;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float local_8c;
  float local_88;
  float local_84;
  float local_80 [16];
  float local_40 [16];
  
  do {
    pfVar2 = compose_matrix_or_transform_a(local_40,(float *)(param_1 + 0x18),param_2);
    pfVar5 = local_80;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar5 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar5 = pfVar5 + 1;
    }
    if (((*(byte *)(param_1 + 0x10) & 1) == 0) &&
       (bVar1 = ensure_world_object_geometry_variant_binding(param_1,0),
       CONCAT31(extraout_var,bVar1) == 1)) {
      iVar3 = *(int *)(param_1 + 0x5c);
      iVar4 = 0;
      if (0 < *(int *)(iVar3 + 4)) {
        iVar6 = 0;
        do {
          transform_vec3_array_by_matrix
                    (&local_8c,(float *)(*(int *)(iVar3 + 0xc) + iVar6),1,local_80);
          if (local_8c < *param_3) {
            *param_3 = local_8c;
          }
          if (local_88 < param_3[1]) {
            param_3[1] = local_88;
          }
          if (local_84 < param_3[2]) {
            param_3[2] = local_84;
          }
          if (*param_4 < local_8c) {
            *param_4 = local_8c;
          }
          if (param_4[1] < local_88) {
            param_4[1] = local_88;
          }
          if (param_4[2] < local_84) {
            param_4[2] = local_84;
          }
          iVar4 = iVar4 + 1;
          iVar6 = iVar6 + 0xc;
        } while (iVar4 < *(int *)(iVar3 + 4));
      }
    }
    if (*(int *)(param_1 + 100) != 0) {
      update_world_object_bounds_from_geometry(*(int *)(param_1 + 100),local_80,param_3,param_4);
    }
    param_1 = *(int *)(param_1 + 0x60);
  } while (param_1 != 0);
  return;
}


