/*
 * Program: i76.exe
 * Function: render_world_object_geometry_tree_pass_primary
 * Entry: 0045d100
 * Signature: undefined __cdecl render_world_object_geometry_tree_pass_primary(int * param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [i76 level/static/material baseline v48]
   name: render_lit_geo_world_object_pass_a
   confidence: medium
   module: geo_render_records
   World/static lit GEO render pass candidate. Kept as medium confidence pending deeper render-path
   trace for material/alpha/road handling.
   note: Rename skipped because existing name appears user-defined. */

void __cdecl render_world_object_geometry_tree_pass_primary(int *param_1,float *param_2)

{
  float fVar1;
  byte bVar2;
  uint uVar3;
  bool bVar4;
  float *pfVar5;
  undefined4 *puVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint *puVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  float *pfVar11;
  int iVar12;
  int local_55c;
  int local_558;
  float local_550 [4];
  float local_540;
  float local_53c;
  float local_538;
  float local_534;
  float local_530;
  double local_528;
  double local_520;
  double local_518;
  float local_510 [4];
  float local_500 [16];
  float local_4c0 [16];
  float local_480 [16];
  float local_440 [16];
  int local_400 [256];
  
  g_geo_render_matrix_or_context = param_2;
  g_geo_render_next_record_scratch = DAT_005dd324;
  g_geo_render_geometry_variant_index = param_1[5] & 7;
  g_geo_render_transformed_positions_scratch = g_runtime_terrain_vertex_xyz_buffer;
  g_geo_render_depth_tree_root = 0;
  iVar8 = param_1[8];
  if ((iVar8 != 0) && (local_558 = 0, 0 < *(int *)(iVar8 + 0xc))) {
    local_55c = 0x10;
    do {
      iVar8 = *(int *)(local_55c + iVar8);
      if (*(int *)(iVar8 + 0x6c) != 0x34) {
        prepare_world_object_render_state_candidate(iVar8);
        g_geo_render_global_flag_mask = 0;
        ensure_world_object_geometry_variant_binding(iVar8,g_geo_render_geometry_variant_index);
        if ((*(int *)(iVar8 + 0x5c) != 0) &&
           (iVar12 = *(int *)(*(int *)(iVar8 + 0x5c) + 0x14), iVar12 != 0)) {
          pfVar5 = compose_matrix_or_transform_a
                             (local_440,(float *)(iVar8 + 0x18),
                              g_geo_render_matrix_or_context + 0x10);
          pfVar11 = local_4c0;
          for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
            *pfVar11 = *pfVar5;
            pfVar5 = pfVar5 + 1;
            pfVar11 = pfVar11 + 1;
          }
          do {
            pfVar5 = local_4c0;
            pfVar11 = local_550;
            for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
              *pfVar11 = *pfVar5;
              pfVar5 = pfVar5 + 1;
              pfVar11 = pfVar11 + 1;
            }
            *(undefined4 *)(g_geo_render_next_record_scratch + 0x40) = 0;
            *(undefined4 *)(g_geo_render_next_record_scratch + 0x44) = 0;
            *(undefined4 *)(g_geo_render_next_record_scratch + 4) = 0;
            *(float *)(g_geo_render_next_record_scratch + 0x24) =
                 local_550[3] * *(float *)(iVar12 + 0x38) +
                 local_550[0] * *(float *)(iVar12 + 0x34) + local_538 * *(float *)(iVar12 + 0x3c) +
                 (float)local_528;
            *(float *)(g_geo_render_next_record_scratch + 0x28) =
                 local_540 * *(float *)(iVar12 + 0x38) +
                 local_550[1] * *(float *)(iVar12 + 0x34) + local_534 * *(float *)(iVar12 + 0x3c) +
                 (float)local_520;
            *(float *)(g_geo_render_next_record_scratch + 0x2c) =
                 local_53c * *(float *)(iVar12 + 0x38) +
                 local_550[2] * *(float *)(iVar12 + 0x34) + local_530 * *(float *)(iVar12 + 0x3c) +
                 (float)local_518;
            puVar6 = (undefined4 *)
                     transform_section_centroid_or_plane_by_matrix
                               (local_510,(float *)(iVar12 + 0xc),local_550);
            iVar9 = g_geo_render_next_record_scratch;
            *(undefined4 *)(g_geo_render_next_record_scratch + 0x30) = *puVar6;
            *(undefined4 *)(iVar9 + 0x34) = puVar6[1];
            *(undefined4 *)(iVar9 + 0x38) = puVar6[2];
            *(undefined4 *)(iVar9 + 0x3c) = puVar6[3];
            *(undefined4 *)(g_geo_render_next_record_scratch + 4) = 0;
            iVar9 = g_geo_render_next_record_scratch + 0x48;
            if (g_geo_render_depth_tree_root == 0) {
              g_geo_render_depth_tree_root = g_geo_render_next_record_scratch;
            }
            else {
              insert_geo_render_record_into_depth_tree(g_geo_render_next_record_scratch);
            }
            iVar12 = *(int *)(iVar12 + 0x30);
            g_geo_render_next_record_scratch = iVar9;
          } while (iVar12 != 0);
        }
        for (iVar12 = *(int *)(iVar8 + 100); iVar12 != 0; iVar12 = *(int *)(iVar12 + 0x60)) {
          pfVar5 = compose_matrix_or_transform_a
                             (local_480,(float *)(iVar12 + 0x18),(float *)(iVar8 + 0x18));
          bVar2 = *(byte *)(iVar12 + 0x10);
          pfVar11 = local_500;
          for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
            *pfVar11 = *pfVar5;
            pfVar5 = pfVar5 + 1;
            pfVar11 = pfVar11 + 1;
          }
          if (((((bVar2 & 1) == 0) &&
               (bVar4 = ensure_world_object_geometry_variant_binding
                                  (iVar12,g_geo_render_geometry_variant_index),
               CONCAT31(extraout_var,bVar4) == 1)) && (*(int *)(iVar12 + 0x5c) != 0)) &&
             (*(int *)(*(int *)(iVar12 + 0x5c) + 4) != 0)) {
            build_lit_geo_render_records_from_sections
                      (iVar12,local_500,(int)g_geo_render_matrix_or_context);
          }
          if (*(int *)(iVar12 + 100) != 0) {
            render_world_object_child_geometry_branch_primary(*(int *)(iVar12 + 100),local_500);
          }
        }
      }
      iVar8 = param_1[8];
      local_558 = local_558 + 1;
      local_55c = local_55c + 0x10;
    } while (local_558 < *(int *)(iVar8 + 0xc));
  }
  g_geo_render_global_flag_mask = param_1[6];
  iVar8 = *param_1;
  if ((((*(byte *)(iVar8 + 0x10) & 1) == 0) &&
      (bVar4 = ensure_world_object_geometry_variant_binding
                         (iVar8,g_geo_render_geometry_variant_index),
      CONCAT31(extraout_var_00,bVar4) == 1)) &&
     ((*(int *)(iVar8 + 0x5c) != 0 && (*(int *)(*(int *)(iVar8 + 0x5c) + 4) != 0)))) {
    build_lit_geo_render_records_from_sections
              (iVar8,(float *)(iVar8 + 0x18),(int)g_geo_render_matrix_or_context);
  }
  if (g_geo_render_depth_tree_root == 0) {
LAB_0045d4e4:
    iVar8 = param_1[8];
    if ((iVar8 != 0) && (iVar12 = 0, 0 < *(int *)(iVar8 + 0xc))) {
      iVar9 = 0x10;
      do {
        if (*(int *)(*(int *)(iVar9 + iVar8) + 0x6c) == 0x34) {
          highlight_visibility_context_helper_0048f570
                    (*(int *)(*(int *)(*(int *)(iVar9 + iVar8) + 0x70) + 0x14),param_2);
        }
        iVar8 = param_1[8];
        iVar12 = iVar12 + 1;
        iVar9 = iVar9 + 0x10;
      } while (iVar12 < *(int *)(iVar8 + 0xc));
    }
    param_1[8] = 0;
    return;
  }
  iVar12 = 0;
  iVar8 = g_geo_render_depth_tree_root;
  do {
    piVar10 = local_400 + iVar12;
    do {
      fVar1 = *(float *)(iVar8 + 0x3c);
      *piVar10 = iVar8;
      iVar12 = iVar12 + 1;
      piVar10 = piVar10 + 1;
      if (_DAT_004be0d8 <= fVar1) {
        iVar8 = *(int *)(iVar8 + 0x44);
      }
      else {
        iVar8 = *(int *)(iVar8 + 0x40);
      }
    } while (iVar8 != 0);
    piVar10 = local_400 + iVar12;
    do {
      if (iVar12 == 0) goto LAB_0045d4e4;
      iVar8 = piVar10[-1];
      piVar10 = piVar10 + -1;
      iVar12 = iVar12 + -1;
      if (*(int *)(iVar8 + 4) != 0) {
        uVar3 = *(uint *)(iVar8 + 0x20);
        puVar7 = *(uint **)(iVar8 + 0x1c);
        pfVar5 = (float *)(uVar3 | 0x10);
        if (((uVar3 & 4) != 0) &&
           ((*(char *)(iVar8 + 0xc) == '\0' ||
            (puVar7 = (uint *)bind_or_load_texture_set_for_object
                                        (*(uint *)(iVar8 + 8),(byte *)(iVar8 + 0xc),
                                         (int)g_geo_render_matrix_or_context), puVar7 == (uint *)0x0
            )))) {
          pfVar5 = (float *)(uVar3 & 0xffffffeb);
        }
        if (*(int *)((int)g_geo_render_matrix_or_context[0xf] + 8) == 1) {
          log_cache_memory_status
                    (g_geo_render_matrix_or_context,(float *)(iVar8 + 0x48),*(float **)(iVar8 + 4),
                     puVar7,pfVar5);
        }
        else {
          submit_lit_textured_polygon_to_renderer
                    (g_geo_render_matrix_or_context,(float *)(iVar8 + 0x48),
                     (int)*(float **)(iVar8 + 4),puVar7,(uint)pfVar5);
        }
      }
      if (_DAT_004be0d8 <= *(float *)(iVar8 + 0x3c)) {
        iVar8 = *(int *)(iVar8 + 0x40);
      }
      else {
        iVar8 = *(int *)(iVar8 + 0x44);
      }
    } while (iVar8 == 0);
  } while( true );
}


