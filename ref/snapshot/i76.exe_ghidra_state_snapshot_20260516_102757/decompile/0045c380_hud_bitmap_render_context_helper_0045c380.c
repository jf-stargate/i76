/*
 * Program: i76.exe
 * Function: hud_bitmap_render_context_helper_0045c380
 * Entry: 0045c380
 * Signature: undefined __cdecl hud_bitmap_render_context_helper_0045c380(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was cockpit_hud_ui_hud_bitmap_render_helper_0045c380. Remove
   duplicated HUD wording. */

void __cdecl hud_bitmap_render_context_helper_0045c380(int param_1)

{
  bool bVar1;
  ushort uVar2;
  undefined2 extraout_var_00;
  undefined3 extraout_var;
  float *pfVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  float fVar11;
  float *pfVar12;
  undefined4 *puVar13;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float local_104 [16];
  undefined4 local_c4 [16];
  float local_84 [3];
  float local_78 [16];
  double local_38;
  float local_30;
  undefined4 local_2c;
  float local_28;
  float *local_24;
  int local_20;
  float local_1c;
  float local_18;
  float local_14;
  undefined4 *local_10;
  float *local_c;
  float local_8;
  
  if (DAT_00654b82 != '\0') {
    if (((((float)*(double *)(param_1 + 0x160) - DAT_004f7180 < (float)_DAT_004be0b0) ||
         ((float)_DAT_004be0b0 <
          (float)*(double *)(param_1 + 0x160) - (DAT_004f7180 - _DAT_004be0b8))) ||
        ((float)*(double *)(param_1 + 0x170) - DAT_004f7188 < (float)_DAT_004be0b0)) ||
       ((float)_DAT_004be0b0 < (float)*(double *)(param_1 + 0x170) - (DAT_004f7188 - _DAT_004be0b8))
       ) {
      fVar11 = (float)*(double *)(param_1 + 0x160) -
               ((float)*(double *)(param_1 + 0x160) / 100.0) * 100.0;
      if (fVar11 < _DAT_004be0c0) {
        fVar11 = fVar11 - _DAT_004be0b8;
      }
      DAT_004f7180 = (float)*(double *)(param_1 + 0x160) - fVar11;
      local_8 = (float)*(double *)(param_1 + 0x170) -
                ((float)*(double *)(param_1 + 0x170) / 100.0) * 100.0;
      local_c = (float *)0x42c80000;
      fVar11 = local_8;
      if (local_8 < _DAT_004be0c0) {
        fVar11 = local_8 - _DAT_004be0b8;
      }
      DAT_004f7188 = (float)*(double *)(param_1 + 0x170) - fVar11;
    }
    local_30 = DAT_004f7180;
    local_2c = DAT_004f7184;
    local_28 = DAT_004f7188;
    apply_world_object_transform_to_bounds_or_geometry
              (*(double *)(param_1 + 0x160),*(double *)(param_1 + 0x170));
    local_38 = (double)extraout_ST0;
    local_8 = (float)DAT_0054ac70;
    if (DAT_0054ac70 != 0) {
      local_c = (float *)&DAT_004f7194;
      fVar11 = (float)DAT_0054ac70;
      while( true ) {
        _DAT_005dd3a8 = (double)(local_c[-1] + local_30 + (float)*(double *)((int)fVar11 + 0x40));
        _DAT_005dd3b8 = (double)(local_28 + *local_c + (float)*(double *)((int)fVar11 + 0x50));
        uVar2 = lookup_terrain_material_index_at_world_xz(_DAT_005dd3a8,_DAT_005dd3b8);
        bVar1 = ensure_world_object_geometry_variant_binding
                          ((int)fVar11,*(int *)(&DAT_004be074 + CONCAT22(extraout_var_00,uVar2) * 8)
                          );
        if (CONCAT31(extraout_var,bVar1) != 1) break;
        if (((*(int *)((int)fVar11 + 0x5c) != 0) && (2 < *(int *)(*(int *)((int)fVar11 + 0x5c) + 4))
            ) && (*(int *)(&DAT_004be070 + CONCAT22(extraout_var_00,uVar2) * 8) != 0)) {
          apply_world_object_transform_to_bounds_or_geometry(_DAT_005dd3a8,_DAT_005dd3b8);
          _DAT_005dd3b0 = (double)extraout_ST0_00;
          if (extraout_ST0_00 - (float10)local_38 <= (float10)_DAT_004be0c8) {
            pfVar3 = (float *)raster_scratch_arena_context_helper_00472d30
                                        (local_84,param_1,_DAT_005dd3a8,_DAT_005dd3b0,_DAT_005dd3b8)
            ;
            local_1c = *pfVar3;
            local_18 = pfVar3[1];
            local_14 = pfVar3[2];
            if ((local_14 <= _DAT_004be0d0) &&
               (iVar4 = software_raster_queue_context_helper_00472c10(param_1,&local_1c,2.0),
               iVar4 < 1)) {
              iVar4 = *(int *)((int)fVar11 + 0x5c);
              pfVar3 = compose_matrix_or_transform_a
                                 (local_104,(float *)&DAT_005dd380,(float *)(param_1 + 0x40));
              pfVar12 = local_78;
              for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
                *pfVar12 = *pfVar3;
                pfVar3 = pfVar3 + 1;
                pfVar12 = pfVar12 + 1;
              }
              transform_vec3_array_by_matrix
                        (DAT_005dd320,*(float **)(iVar4 + 0xc),*(int *)(iVar4 + 4),local_78);
              fVar11 = local_8;
              local_10 = (undefined4 *)((int)local_8 + 0x18);
              puVar10 = local_10;
              puVar13 = local_c4;
              for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
                *puVar13 = *puVar10;
                puVar10 = puVar10 + 1;
                puVar13 = puVar13 + 1;
              }
              puVar10 = &DAT_005dd380;
              puVar13 = local_10;
              for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
                *puVar13 = *puVar10;
                puVar10 = puVar10 + 1;
                puVar13 = puVar13 + 1;
              }
              prepare_world_object_render_state_candidate((int)fVar11);
              puVar10 = local_c4;
              puVar13 = local_10;
              for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
                *puVar13 = *puVar10;
                puVar10 = puVar10 + 1;
                puVar13 = puVar13 + 1;
              }
              local_24 = DAT_005dd320 + *(int *)(iVar4 + 4) * 3;
              compute_geo_vertex_lighting_from_normals
                        (local_24,DAT_005dd320,*(int *)(iVar4 + 0x10),(float *)&DAT_005dd380,
                         local_78,*(float *)(iVar4 + 8));
              fVar11 = local_8;
              for (iVar4 = *(int *)(iVar4 + 0x14); local_8 = fVar11, iVar4 != 0;
                  iVar4 = *(int *)(iVar4 + 0x30)) {
                piVar5 = terrain_map_context_helper_00490590();
                local_10 = (undefined4 *)0x0;
                piVar5[3] = 4;
                iVar8 = *(int *)(iVar4 + 4);
                *piVar5 = iVar8;
                if (0 < iVar8) {
                  piVar9 = piVar5 + 0xb;
                  do {
                    iVar6 = (iVar8 - (int)local_10) + -1;
                    local_20 = iVar6 * 0x10 + iVar4;
                    iVar8 = *(int *)(((iVar8 - (int)local_10) + 3) * 0x10 + iVar4);
                    piVar9[-1] = *(int *)(local_20 + 0x48);
                    *piVar9 = *(int *)(local_20 + 0x4c);
                    piVar9[1] = (int)local_24[iVar6];
                    pfVar3 = DAT_005dd320 + iVar8 * 3;
                    piVar9[-4] = (int)*pfVar3;
                    piVar9[-3] = (int)pfVar3[1];
                    piVar9[-2] = (int)pfVar3[2];
                    iVar8 = *piVar5;
                    local_10 = (undefined4 *)((int)local_10 + 1);
                    piVar9 = piVar9 + 6;
                  } while ((int)local_10 < iVar8);
                }
                fVar11 = (float)piVar5[9];
                if (1 < *piVar5) {
                  pfVar3 = (float *)(piVar5 + 0xf);
                  iVar8 = *piVar5 + -1;
                  do {
                    if (_DAT_004be0c0 < *pfVar3 - fVar11) {
                      fVar11 = *pfVar3;
                    }
                    pfVar3 = pfVar3 + 6;
                    iVar8 = iVar8 + -1;
                  } while (iVar8 != 0);
                }
                piVar5[4] = (int)fVar11;
                uVar7 = *(uint *)(&DAT_004f71b8 +
                                 ((uint)*(byte *)(iVar4 + 0x1d) + (uint)*(byte *)(iVar4 + 0x1c) * 8)
                                 * 4);
                piVar5[2] = uVar7;
                piVar5[2] = *(uint *)((int)local_8 + 0x14) & uVar7 & 0xff;
                piVar5[1] = (uint)*(byte *)(iVar4 + 8);
                if ((*(byte *)(piVar5 + 2) & 4) != 0) {
                  if (*(char *)(iVar4 + 0x20) != '\0') {
                    uVar7 = bind_or_load_texture_set_for_object
                                      ((uint)local_8,(byte *)(iVar4 + 0x20),param_1);
                    piVar5[1] = uVar7;
                    if (uVar7 != 0) goto LAB_0045c802;
                  }
                  piVar5[2] = piVar5[2] & 0xffffffeb;
                }
LAB_0045c802:
                terrain_map_context_helper_0048fe10((float)piVar5[4]);
                fVar11 = local_8;
              }
            }
          }
        }
        local_c = local_c + 2;
        if (0x4f71db < (int)local_c) {
          fVar11 = *(float *)((int)fVar11 + 0x60);
          if (fVar11 == 0.0) {
            return;
          }
          local_c = (float *)&DAT_004f7194;
          local_8 = fVar11;
        }
      }
    }
  }
  return;
}


