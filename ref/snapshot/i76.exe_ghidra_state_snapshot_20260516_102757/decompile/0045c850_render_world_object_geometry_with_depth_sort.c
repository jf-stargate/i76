/*
 * Program: i76.exe
 * Function: render_world_object_geometry_with_depth_sort
 * Entry: 0045c850
 * Signature: undefined __cdecl render_world_object_geometry_with_depth_sort(int * param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO lighting/render renames v33; confidence=medium-high] Leaf/fallback world-object
   render traversal. Builds depth-sorted section records, binds texture slots, and submits lit
   textured polygons. */

void __cdecl render_world_object_geometry_with_depth_sort(int *param_1,float *param_2)

{
  float fVar1;
  byte bVar2;
  uint uVar3;
  bool bVar4;
  float *pfVar5;
  undefined4 *puVar6;
  undefined3 extraout_var;
  uint *puVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  float *pfVar11;
  int iVar12;
  float local_490 [4];
  float local_480;
  float local_47c;
  float local_478;
  float local_474;
  float local_470;
  double local_468;
  double local_460;
  double local_458;
  float local_450 [16];
  float local_410 [4];
  int local_400 [256];
  
  iVar12 = *param_1;
  if (*(int *)(iVar12 + 100) != 0) {
    g_geo_render_matrix_or_context = param_2;
    g_geo_render_geometry_variant_index = param_1[5] & 7;
    g_geo_render_global_flag_mask = param_1[6];
    g_geo_render_transformed_positions_scratch = DAT_005dd320;
    g_geo_render_next_record_scratch = DAT_005dd324;
    g_geo_render_depth_tree_root = 0;
    prepare_world_object_render_state_candidate(iVar12);
    ensure_world_object_geometry_variant_binding(iVar12,g_geo_render_geometry_variant_index);
    if ((*(int *)(iVar12 + 0x5c) != 0) &&
       (iVar10 = *(int *)(*(int *)(iVar12 + 0x5c) + 0x14), iVar10 != 0)) {
      pfVar5 = compose_matrix_or_transform_a
                         (local_450,(float *)(iVar12 + 0x18),g_geo_render_matrix_or_context + 0x10);
      pfVar11 = local_450;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar11 = *pfVar5;
        pfVar5 = pfVar5 + 1;
        pfVar11 = pfVar11 + 1;
      }
      do {
        pfVar5 = local_450;
        pfVar11 = local_490;
        for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
          *pfVar11 = *pfVar5;
          pfVar5 = pfVar5 + 1;
          pfVar11 = pfVar11 + 1;
        }
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x40) = 0;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x44) = 0;
        *(undefined4 *)(g_geo_render_next_record_scratch + 4) = 0;
        *(float *)(g_geo_render_next_record_scratch + 0x24) =
             local_490[0] * *(float *)(iVar10 + 0x34) +
             local_478 * *(float *)(iVar10 + 0x3c) + local_490[3] * *(float *)(iVar10 + 0x38) +
             (float)local_468;
        *(float *)(g_geo_render_next_record_scratch + 0x28) =
             local_490[1] * *(float *)(iVar10 + 0x34) +
             local_474 * *(float *)(iVar10 + 0x3c) + local_480 * *(float *)(iVar10 + 0x38) +
             (float)local_460;
        *(float *)(g_geo_render_next_record_scratch + 0x2c) =
             local_490[2] * *(float *)(iVar10 + 0x34) +
             local_470 * *(float *)(iVar10 + 0x3c) + local_47c * *(float *)(iVar10 + 0x38) +
             (float)local_458;
        puVar6 = (undefined4 *)
                 transform_section_centroid_or_plane_by_matrix
                           (local_410,(float *)(iVar10 + 0xc),local_490);
        iVar8 = g_geo_render_next_record_scratch;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x30) = *puVar6;
        *(undefined4 *)(iVar8 + 0x34) = puVar6[1];
        *(undefined4 *)(iVar8 + 0x38) = puVar6[2];
        *(undefined4 *)(iVar8 + 0x3c) = puVar6[3];
        *(undefined4 *)(g_geo_render_next_record_scratch + 4) = 0;
        iVar8 = g_geo_render_next_record_scratch + 0x48;
        if (g_geo_render_depth_tree_root == 0) {
          g_geo_render_depth_tree_root = g_geo_render_next_record_scratch;
        }
        else {
          insert_geo_render_record_into_depth_tree(g_geo_render_next_record_scratch);
        }
        iVar10 = *(int *)(iVar10 + 0x30);
        g_geo_render_next_record_scratch = iVar8;
      } while (iVar10 != 0);
    }
    iVar8 = g_geo_render_depth_tree_root;
    for (iVar10 = *(int *)(iVar12 + 100); g_geo_render_depth_tree_root = iVar8, iVar10 != 0;
        iVar10 = *(int *)(iVar10 + 0x60)) {
      pfVar5 = compose_matrix_or_transform_a
                         (local_450,(float *)(iVar10 + 0x18),(float *)(iVar12 + 0x18));
      bVar2 = *(byte *)(iVar10 + 0x10);
      pfVar11 = local_490;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar11 = *pfVar5;
        pfVar5 = pfVar5 + 1;
        pfVar11 = pfVar11 + 1;
      }
      if (((((bVar2 & 1) == 0) &&
           (bVar4 = ensure_world_object_geometry_variant_binding
                              (iVar10,g_geo_render_geometry_variant_index),
           CONCAT31(extraout_var,bVar4) == 1)) && (*(int *)(iVar10 + 0x5c) != 0)) &&
         (*(int *)(*(int *)(iVar10 + 0x5c) + 4) != 0)) {
        build_lit_geo_render_records_from_sections
                  (iVar10,local_490,(int)g_geo_render_matrix_or_context);
      }
      if (*(int *)(iVar10 + 100) != 0) {
        render_world_object_child_geometry_branch_primary(*(int *)(iVar10 + 100),local_490);
      }
      iVar8 = g_geo_render_depth_tree_root;
    }
    if (iVar8 != 0) {
      iVar12 = 0;
      do {
        piVar9 = local_400 + iVar12;
        do {
          fVar1 = *(float *)(iVar8 + 0x3c);
          *piVar9 = iVar8;
          iVar12 = iVar12 + 1;
          piVar9 = piVar9 + 1;
          if (_DAT_004be0d8 <= fVar1) {
            iVar8 = *(int *)(iVar8 + 0x44);
          }
          else {
            iVar8 = *(int *)(iVar8 + 0x40);
          }
        } while (iVar8 != 0);
        piVar9 = local_400 + iVar12;
        do {
          if (iVar12 == 0) {
            return;
          }
          iVar10 = piVar9[-1];
          piVar9 = piVar9 + -1;
          iVar12 = iVar12 + -1;
          if (*(int *)(iVar10 + 4) != 0) {
            uVar3 = *(uint *)(iVar10 + 0x20);
            puVar7 = *(uint **)(iVar10 + 0x1c);
            pfVar5 = (float *)(uVar3 | 0x10);
            if (((uVar3 & 4) != 0) &&
               ((*(char *)(iVar10 + 0xc) == '\0' ||
                (puVar7 = (uint *)bind_or_load_texture_set_for_object
                                            (*(uint *)(iVar10 + 8),(byte *)(iVar10 + 0xc),
                                             (int)g_geo_render_matrix_or_context),
                puVar7 == (uint *)0x0)))) {
              pfVar5 = (float *)(uVar3 & 0xffffffeb);
            }
            if (*(int *)((int)g_geo_render_matrix_or_context[0xf] + 8) == 1) {
              log_cache_memory_status
                        (g_geo_render_matrix_or_context,(float *)(iVar10 + 0x48),
                         *(float **)(iVar10 + 4),puVar7,pfVar5);
            }
            else {
              submit_lit_textured_polygon_to_renderer
                        (g_geo_render_matrix_or_context,(float *)(iVar10 + 0x48),
                         (int)*(float **)(iVar10 + 4),puVar7,(uint)pfVar5);
            }
          }
          if (_DAT_004be0d8 <= *(float *)(iVar10 + 0x3c)) {
            iVar8 = *(int *)(iVar10 + 0x40);
          }
          else {
            iVar8 = *(int *)(iVar10 + 0x44);
          }
        } while (iVar8 == 0);
      } while( true );
    }
  }
  return;
}


