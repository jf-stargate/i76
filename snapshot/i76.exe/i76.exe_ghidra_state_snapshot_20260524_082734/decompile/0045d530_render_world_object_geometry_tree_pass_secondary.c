/*
 * Program: i76.exe
 * Function: render_world_object_geometry_tree_pass_secondary
 * Entry: 0045d530
 * Signature: undefined __cdecl render_world_object_geometry_tree_pass_secondary(int * param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [i76 level/static/material baseline v48]
   name: render_lit_geo_world_object_pass_b
   confidence: medium
   module: geo_render_records
   Companion world/static lit GEO render pass candidate. Relevant to final material/alpha validation
   and possible renderer-specific state.
   note: Rename skipped because existing name appears user-defined. */

void __cdecl render_world_object_geometry_tree_pass_secondary(int *param_1,float *param_2)

{
  float fVar1;
  byte bVar2;
  uint uVar3;
  bool bVar4;
  float *pfVar5;
  float *pfVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint *puVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  float in_stack_fffffaa4;
  float in_stack_fffffaa8;
  float in_stack_fffffaac;
  float in_stack_fffffab0;
  float in_stack_fffffab4;
  float in_stack_fffffab8;
  float in_stack_fffffabc;
  float in_stack_fffffac0;
  float in_stack_fffffac4;
  undefined4 in_stack_fffffac8;
  undefined4 in_stack_fffffacc;
  undefined4 in_stack_fffffad0;
  undefined4 uVar14;
  float *pfVar15;
  float *pfVar16;
  int local_508;
  int local_504;
  float local_500 [16];
  float local_4c0 [16];
  float local_480 [16];
  float local_440 [16];
  undefined4 local_400 [256];
  
  if (*(int *)(*param_1 + 100) != 0) {
    g_geo_render_matrix_or_context = param_2;
    g_geo_render_geometry_variant_index = param_1[5] & 7;
    g_geo_render_global_flag_mask = param_1[6];
    g_geo_render_transformed_positions_scratch = g_runtime_terrain_vertex_xyz_buffer;
    g_geo_render_next_record_scratch = DAT_005dd324;
    g_geo_render_depth_tree_root = (float *)0x0;
    iVar13 = *param_1;
    prepare_world_object_render_state_candidate(iVar13);
    pfVar11 = (float *)(iVar13 + 0x18);
    ensure_world_object_geometry_variant_binding(iVar13,g_geo_render_geometry_variant_index);
    if ((*(int *)(iVar13 + 0x5c) != 0) &&
       (iVar9 = *(int *)(*(int *)(iVar13 + 0x5c) + 0x14), iVar9 != 0)) {
      pfVar16 = g_geo_render_matrix_or_context + 0x10;
      pfVar6 = local_4c0;
      uVar14 = 0x45d5d8;
      pfVar15 = pfVar11;
      pfVar5 = compose_matrix_or_transform_a(pfVar6,pfVar11,pfVar16);
      pfVar12 = local_500;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar12 = *pfVar5;
        pfVar5 = pfVar5 + 1;
        pfVar12 = pfVar12 + 1;
      }
      do {
        pfVar5 = local_500;
        pfVar12 = (float *)&stack0xfffffaa4;
        for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
          *pfVar12 = *pfVar5;
          pfVar5 = pfVar5 + 1;
          pfVar12 = pfVar12 + 1;
        }
        pfVar5 = (float *)mission_objective_file_context_helper_0045da70
                                    (iVar9,in_stack_fffffaa4,in_stack_fffffaa8,in_stack_fffffaac,
                                     in_stack_fffffab0,in_stack_fffffab4,in_stack_fffffab8,
                                     in_stack_fffffabc,in_stack_fffffac0,in_stack_fffffac4,
                                     in_stack_fffffac8,
                                     (double)CONCAT44(in_stack_fffffad0,in_stack_fffffacc),
                                     (double)CONCAT44(pfVar6,uVar14),
                                     (double)CONCAT44(pfVar16,pfVar15));
        if (g_geo_render_depth_tree_root == (float *)0x0) {
          g_geo_render_depth_tree_root = g_geo_render_next_record_scratch;
        }
        else {
          pfVar15 = (float *)0x45d625;
          insert_geo_render_record_into_depth_tree((int)g_geo_render_next_record_scratch);
          pfVar16 = g_geo_render_next_record_scratch;
        }
        iVar9 = *(int *)(iVar9 + 0x30);
        g_geo_render_next_record_scratch = pfVar5;
      } while (iVar9 != 0);
    }
    iVar9 = *(int *)(iVar13 + 100);
    if (iVar9 != 0) {
      bVar4 = false;
      if (param_1[5] == 0xb) {
        for (; iVar9 != 0; iVar9 = *(int *)(iVar9 + 0x60)) {
          if ((0x40 < *(int *)(iVar9 + 0x6c)) && (*(int *)(iVar9 + 0x6c) < 0x45)) {
            pfVar6 = compose_matrix_or_transform_a(local_4c0,(float *)(iVar9 + 0x18),pfVar11);
            bVar2 = *(byte *)(iVar9 + 0x10);
            pfVar5 = local_500;
            for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
              *pfVar5 = *pfVar6;
              pfVar6 = pfVar6 + 1;
              pfVar5 = pfVar5 + 1;
            }
            if (((((bVar2 & 1) == 0) &&
                 (bVar4 = ensure_world_object_geometry_variant_binding
                                    (iVar9,g_geo_render_geometry_variant_index),
                 CONCAT31(extraout_var,bVar4) == 1)) && (*(int *)(iVar9 + 0x5c) != 0)) &&
               (*(int *)(*(int *)(iVar9 + 0x5c) + 4) != 0)) {
              build_lit_geo_render_records_from_sections
                        (iVar9,local_500,(int)g_geo_render_matrix_or_context);
            }
            for (iVar8 = *(int *)(iVar9 + 100); iVar8 != 0; iVar8 = *(int *)(iVar8 + 0x60)) {
              render_world_object_child_geometry_branch_secondary(iVar8,local_500);
            }
            bVar4 = true;
          }
        }
      }
      if (!bVar4) {
        iVar13 = *(int *)(iVar13 + 100);
        do {
          pfVar6 = compose_matrix_or_transform_a(local_4c0,(float *)(iVar13 + 0x18),pfVar11);
          bVar2 = *(byte *)(iVar13 + 0x10);
          pfVar5 = local_500;
          for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
            *pfVar5 = *pfVar6;
            pfVar6 = pfVar6 + 1;
            pfVar5 = pfVar5 + 1;
          }
          if ((((bVar2 & 1) == 0) &&
              (bVar4 = ensure_world_object_geometry_variant_binding
                                 (iVar13,g_geo_render_geometry_variant_index),
              CONCAT31(extraout_var_00,bVar4) == 1)) &&
             ((*(int *)(iVar13 + 0x5c) != 0 && (*(int *)(*(int *)(iVar13 + 0x5c) + 4) != 0)))) {
            build_lit_geo_render_records_from_sections
                      (iVar13,local_500,(int)g_geo_render_matrix_or_context);
          }
          if (*(int *)(iVar13 + 100) != 0) {
            render_world_object_child_geometry_branch_primary(*(int *)(iVar13 + 100),local_500);
          }
          iVar13 = *(int *)(iVar13 + 0x60);
        } while (iVar13 != 0);
      }
    }
    iVar13 = param_1[8];
    if ((iVar13 != 0) && (local_504 = 0, 0 < *(int *)(iVar13 + 0xc))) {
      local_508 = 0x10;
      do {
        iVar13 = *(int *)(local_508 + iVar13);
        if (*(int *)(iVar13 + 0x6c) != 0x34) {
          prepare_world_object_render_state_candidate(iVar13);
          pfVar11 = (float *)(iVar13 + 0x18);
          g_geo_render_global_flag_mask = 0;
          ensure_world_object_geometry_variant_binding(iVar13,g_geo_render_geometry_variant_index);
          if ((*(int *)(iVar13 + 0x5c) != 0) &&
             (iVar9 = *(int *)(*(int *)(iVar13 + 0x5c) + 0x14), iVar9 != 0)) {
            pfVar16 = g_geo_render_matrix_or_context + 0x10;
            pfVar6 = local_480;
            uVar14 = 0x45d81a;
            pfVar15 = pfVar11;
            pfVar5 = compose_matrix_or_transform_a(pfVar6,pfVar11,pfVar16);
            pfVar12 = local_4c0;
            for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
              *pfVar12 = *pfVar5;
              pfVar5 = pfVar5 + 1;
              pfVar12 = pfVar12 + 1;
            }
            do {
              pfVar5 = local_4c0;
              pfVar12 = (float *)&stack0xfffffaa4;
              for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
                *pfVar12 = *pfVar5;
                pfVar5 = pfVar5 + 1;
                pfVar12 = pfVar12 + 1;
              }
              pfVar5 = (float *)mission_objective_file_context_helper_0045da70
                                          (iVar9,in_stack_fffffaa4,in_stack_fffffaa8,
                                           in_stack_fffffaac,in_stack_fffffab0,in_stack_fffffab4,
                                           in_stack_fffffab8,in_stack_fffffabc,in_stack_fffffac0,
                                           in_stack_fffffac4,in_stack_fffffac8,
                                           (double)CONCAT44(in_stack_fffffad0,in_stack_fffffacc),
                                           (double)CONCAT44(pfVar6,uVar14),
                                           (double)CONCAT44(pfVar16,pfVar15));
              if (g_geo_render_depth_tree_root == (float *)0x0) {
                g_geo_render_depth_tree_root = g_geo_render_next_record_scratch;
              }
              else {
                pfVar15 = (float *)0x45d86b;
                insert_geo_render_record_into_depth_tree((int)g_geo_render_next_record_scratch);
                pfVar16 = g_geo_render_next_record_scratch;
              }
              iVar9 = *(int *)(iVar9 + 0x30);
              g_geo_render_next_record_scratch = pfVar5;
            } while (iVar9 != 0);
          }
          for (iVar13 = *(int *)(iVar13 + 100); iVar13 != 0; iVar13 = *(int *)(iVar13 + 0x60)) {
            pfVar6 = compose_matrix_or_transform_a(local_440,(float *)(iVar13 + 0x18),pfVar11);
            bVar2 = *(byte *)(iVar13 + 0x10);
            pfVar5 = local_500;
            for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
              *pfVar5 = *pfVar6;
              pfVar6 = pfVar6 + 1;
              pfVar5 = pfVar5 + 1;
            }
            if (((((bVar2 & 1) == 0) &&
                 (bVar4 = ensure_world_object_geometry_variant_binding
                                    (iVar13,g_geo_render_geometry_variant_index),
                 CONCAT31(extraout_var_01,bVar4) == 1)) && (*(int *)(iVar13 + 0x5c) != 0)) &&
               (*(int *)(*(int *)(iVar13 + 0x5c) + 4) != 0)) {
              build_lit_geo_render_records_from_sections
                        (iVar13,local_500,(int)g_geo_render_matrix_or_context);
            }
            if (*(int *)(iVar13 + 100) != 0) {
              render_world_object_child_geometry_branch_primary(*(int *)(iVar13 + 100),local_500);
            }
          }
        }
        local_504 = local_504 + 1;
        iVar13 = param_1[8];
        local_508 = local_508 + 0x10;
      } while (local_504 < *(int *)(iVar13 + 0xc));
    }
    if (g_geo_render_depth_tree_root != (float *)0x0) {
      iVar13 = 0;
      pfVar11 = g_geo_render_depth_tree_root;
      do {
        puVar10 = local_400 + iVar13;
        do {
          fVar1 = pfVar11[0xf];
          *puVar10 = pfVar11;
          iVar13 = iVar13 + 1;
          puVar10 = puVar10 + 1;
          if (_DAT_004be0d8 <= fVar1) {
            pfVar11 = (float *)pfVar11[0x11];
          }
          else {
            pfVar11 = (float *)pfVar11[0x10];
          }
        } while (pfVar11 != (float *)0x0);
        puVar10 = local_400 + iVar13;
        do {
          if (iVar13 == 0) goto LAB_0045da0c;
          iVar9 = puVar10[-1];
          puVar10 = puVar10 + -1;
          iVar13 = iVar13 + -1;
          if (*(int *)(iVar9 + 4) != 0) {
            uVar3 = *(uint *)(iVar9 + 0x20);
            puVar7 = *(uint **)(iVar9 + 0x1c);
            pfVar11 = (float *)(uVar3 | 0x10);
            if (((uVar3 & 4) != 0) &&
               ((*(char *)(iVar9 + 0xc) == '\0' ||
                (puVar7 = (uint *)bind_or_load_texture_set_for_object
                                            (*(uint *)(iVar9 + 8),(byte *)(iVar9 + 0xc),
                                             (int)g_geo_render_matrix_or_context),
                puVar7 == (uint *)0x0)))) {
              pfVar11 = (float *)(uVar3 & 0xffffffeb);
            }
            if (*(int *)((int)g_geo_render_matrix_or_context[0xf] + 8) == 1) {
              log_cache_memory_status
                        (g_geo_render_matrix_or_context,(float *)(iVar9 + 0x48),
                         *(float **)(iVar9 + 4),puVar7,pfVar11);
            }
            else {
              submit_lit_textured_polygon_to_renderer
                        (g_geo_render_matrix_or_context,(float *)(iVar9 + 0x48),
                         (int)*(float **)(iVar9 + 4),puVar7,(uint)pfVar11);
            }
          }
          if (_DAT_004be0d8 <= *(float *)(iVar9 + 0x3c)) {
            pfVar11 = *(float **)(iVar9 + 0x40);
          }
          else {
            pfVar11 = *(float **)(iVar9 + 0x44);
          }
        } while (pfVar11 == (float *)0x0);
      } while( true );
    }
LAB_0045da0c:
    iVar13 = param_1[8];
    if ((iVar13 != 0) && (iVar9 = 0, 0 < *(int *)(iVar13 + 0xc))) {
      iVar8 = 0x10;
      do {
        if (*(int *)(*(int *)(iVar8 + iVar13) + 0x6c) == 0x34) {
          highlight_visibility_context_helper_0048f570
                    (*(int *)(*(int *)(*(int *)(iVar8 + iVar13) + 0x70) + 0x14),param_2);
        }
        iVar13 = param_1[8];
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 0x10;
      } while (iVar9 < *(int *)(iVar13 + 0xc));
    }
    param_1[8] = 0;
  }
  return;
}


