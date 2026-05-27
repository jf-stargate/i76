/*
 * Program: i76.exe
 * Function: hud_bitmap_render_context_helper_0045dcc0
 * Entry: 0045dcc0
 * Signature: undefined __cdecl hud_bitmap_render_context_helper_0045dcc0(int * param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was cockpit_hud_ui_hud_bitmap_render_helper_0045dcc0. Remove
   duplicated HUD wording. */

void __cdecl hud_bitmap_render_context_helper_0045dcc0(int *param_1,float *param_2)

{
  float fVar1;
  byte bVar2;
  uint uVar3;
  bool bVar4;
  float *pfVar5;
  undefined3 extraout_var;
  uint *puVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  float *pfVar10;
  int iVar11;
  float local_480 [16];
  float local_440 [16];
  int local_400 [256];
  
  iVar9 = *param_1;
  if (*(int *)(iVar9 + 100) != 0) {
    g_geo_render_matrix_or_context = param_2;
    g_geo_render_geometry_variant_index = param_1[5] & 7;
    g_geo_render_global_flag_mask = param_1[6];
    g_geo_render_transformed_positions_scratch = g_runtime_terrain_vertex_xyz_buffer;
    g_geo_render_next_record_scratch = DAT_005dd324;
    g_geo_render_depth_tree_root = 0;
    prepare_world_object_render_state_candidate(iVar9);
    iVar11 = *(int *)(iVar9 + 100);
    if (iVar11 != 0) {
      do {
        pfVar5 = compose_matrix_or_transform_a
                           (local_440,(float *)(iVar11 + 0x18),(float *)(iVar9 + 0x18));
        bVar2 = *(byte *)(iVar11 + 0x10);
        pfVar10 = local_480;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar10 = *pfVar5;
          pfVar5 = pfVar5 + 1;
          pfVar10 = pfVar10 + 1;
        }
        if (((((bVar2 & 1) == 0) &&
             (bVar4 = ensure_world_object_geometry_variant_binding
                                (iVar11,g_geo_render_geometry_variant_index),
             CONCAT31(extraout_var,bVar4) == 1)) && (*(int *)(iVar11 + 0x5c) != 0)) &&
           (*(int *)(*(int *)(iVar11 + 0x5c) + 4) != 0)) {
          build_lit_geo_render_records_from_sections
                    (iVar11,local_480,(int)g_geo_render_matrix_or_context);
        }
        if (*(int *)(iVar11 + 100) != 0) {
          render_world_object_child_geometry_branch_primary(*(int *)(iVar11 + 100),local_480);
        }
        iVar11 = *(int *)(iVar11 + 0x60);
      } while (iVar11 != 0);
    }
    if (g_geo_render_depth_tree_root != 0) {
      iVar11 = 0;
      iVar9 = g_geo_render_depth_tree_root;
      do {
        piVar8 = local_400 + iVar11;
        do {
          fVar1 = *(float *)(iVar9 + 0x3c);
          *piVar8 = iVar9;
          iVar11 = iVar11 + 1;
          piVar8 = piVar8 + 1;
          if (_DAT_004be0d8 <= fVar1) {
            iVar9 = *(int *)(iVar9 + 0x44);
          }
          else {
            iVar9 = *(int *)(iVar9 + 0x40);
          }
        } while (iVar9 != 0);
        piVar8 = local_400 + iVar11;
        do {
          if (iVar11 == 0) {
            return;
          }
          iVar9 = piVar8[-1];
          piVar8 = piVar8 + -1;
          iVar11 = iVar11 + -1;
          if (*(int *)(iVar9 + 4) != 0) {
            uVar3 = *(uint *)(iVar9 + 0x20);
            puVar6 = *(uint **)(iVar9 + 0x1c);
            pfVar5 = (float *)(uVar3 | 0x10);
            if (((uVar3 & 4) != 0) &&
               ((*(char *)(iVar9 + 0xc) == '\0' ||
                (puVar6 = (uint *)bind_or_load_texture_set_for_object
                                            (*(uint *)(iVar9 + 8),(byte *)(iVar9 + 0xc),
                                             (int)g_geo_render_matrix_or_context),
                puVar6 == (uint *)0x0)))) {
              pfVar5 = (float *)(uVar3 & 0xffffffeb);
            }
            if (*(int *)((int)g_geo_render_matrix_or_context[0xf] + 8) == 1) {
              log_cache_memory_status
                        (g_geo_render_matrix_or_context,(float *)(iVar9 + 0x48),
                         *(float **)(iVar9 + 4),puVar6,pfVar5);
            }
            else {
              submit_lit_textured_polygon_to_renderer
                        (g_geo_render_matrix_or_context,(float *)(iVar9 + 0x48),
                         (int)*(float **)(iVar9 + 4),puVar6,(uint)pfVar5);
            }
          }
          if (_DAT_004be0d8 <= *(float *)(iVar9 + 0x3c)) {
            iVar9 = *(int *)(iVar9 + 0x40);
          }
          else {
            iVar9 = *(int *)(iVar9 + 0x44);
          }
        } while (iVar9 == 0);
      } while( true );
    }
  }
  return;
}


