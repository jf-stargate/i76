/*
 * Program: i76.exe
 * Function: render_world_object_child_geometry_branch_primary
 * Entry: 0045d060
 * Signature: undefined __cdecl render_world_object_child_geometry_branch_primary(int param_1, float * param_2)
 */


/* [cgpt i76.exe GEO lighting/render renames v33; confidence=medium-high] Recursive/helper branch
   used by primary traversal for object child/sibling geometry lists. */

void __cdecl render_world_object_child_geometry_branch_primary(int param_1,float *param_2)

{
  byte bVar1;
  bool bVar2;
  float *pfVar3;
  undefined3 extraout_var;
  int iVar4;
  float *pfVar5;
  float local_80 [16];
  float local_40 [16];
  
  do {
    pfVar3 = compose_matrix_or_transform_a(local_40,(float *)(param_1 + 0x18),param_2);
    bVar1 = *(byte *)(param_1 + 0x10);
    pfVar5 = local_80;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar5 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar5 = pfVar5 + 1;
    }
    if ((bVar1 & 1) == 0) {
      bVar2 = ensure_world_object_geometry_variant_binding
                        (param_1,g_geo_render_geometry_variant_index);
      if (((CONCAT31(extraout_var,bVar2) == 1) && (*(int *)(param_1 + 0x5c) != 0)) &&
         (*(int *)(*(int *)(param_1 + 0x5c) + 4) != 0)) {
        build_lit_geo_render_records_from_sections(param_1,local_80,g_geo_render_matrix_or_context);
      }
    }
    if (*(int *)(param_1 + 100) != 0) {
      render_world_object_child_geometry_branch_primary(*(int *)(param_1 + 100),local_80);
    }
    param_1 = *(int *)(param_1 + 0x60);
  } while (param_1 != 0);
  return;
}


