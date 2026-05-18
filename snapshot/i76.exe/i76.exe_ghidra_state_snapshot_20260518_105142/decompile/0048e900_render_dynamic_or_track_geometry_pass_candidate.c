/*
 * Program: i76.exe
 * Function: render_dynamic_or_track_geometry_pass_candidate
 * Entry: 0048e900
 * Signature: undefined __cdecl render_dynamic_or_track_geometry_pass_candidate(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO lighting/render renames v33; confidence=medium-high] Separate render-side
   geometry consumer discovered near GEO render traversal; likely dynamic/track/object pass
   dispatcher. */

void __cdecl render_dynamic_or_track_geometry_pass_candidate(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  uint uVar7;
  bool bVar8;
  int iVar9;
  undefined3 extraout_var;
  int iVar10;
  undefined4 *puVar11;
  undefined3 extraout_var_00;
  float *pfVar12;
  undefined3 extraout_var_01;
  uint uVar13;
  int iVar14;
  int iVar15;
  undefined4 *puVar16;
  int iVar17;
  int iVar18;
  float *pfVar19;
  float *pfVar20;
  char cVar21;
  float10 fVar22;
  float local_15c;
  uint local_158;
  float local_154;
  int local_150;
  float local_144;
  float local_12c;
  float local_128;
  float local_124;
  float local_120 [2];
  float local_118;
  undefined *local_114;
  int local_110;
  float local_10c;
  float local_108;
  float local_104;
  undefined4 local_100 [4];
  undefined4 local_f0;
  undefined4 local_ec;
  undefined8 local_e8;
  float local_d8 [16];
  undefined4 local_98 [6];
  float local_80 [16];
  float local_40 [16];
  
  if ((DAT_0059c490 != 0) &&
     (iVar9 = world_reader_record_table_context_helper_004b8970(), iVar9 != 0)) {
    if (DAT_00654b83 == '\0') {
      local_158 = 0;
    }
    else {
      local_158 = 0xf4;
      bVar8 = is_miss16_high_color_resource_mode();
      if (CONCAT31(extraout_var,bVar8) != 0) {
        local_158 = 0x17;
      }
    }
    fVar22 = palette_dib_surface_flag_helper_00477af0();
    local_144 = (float)(fVar22 * (float10)DAT_006435f4);
    if (fVar22 * (float10)DAT_006435f4 < (float10)_DAT_004be7b0) {
      local_144 = 0.0;
    }
    fVar22 = palette_dib_surface_setter_helper_00477ae0();
    fVar1 = (float)fVar22;
    pfVar12 = g_runtime_terrain_vertex_xyz_buffer;
    do {
      dVar3 = *(double *)(param_1 + 0x80) - (double)*(float *)(iVar9 + 0x18);
      dVar6 = *(double *)(param_1 + 0x88) - (double)*(float *)(iVar9 + 0x1c);
      dVar5 = *(double *)(param_1 + 0x90) - (double)*(float *)(iVar9 + 0x20);
      dVar4 = *(double *)(param_1 + 0x98) + (double)*(float *)(iVar9 + 0x24);
      local_e8 = (dVar5 * dVar5 + dVar6 * dVar6 + dVar3 * dVar3) - dVar4 * dVar4;
      if (((uint)((longlong)local_e8 >> 0x3f) & 1) != 0) {
        iVar17 = *(int *)(iVar9 + 0x10);
        iVar18 = *(int *)(iVar9 + 0x14);
        pfVar19 = (float *)(param_1 + 0x40);
        pfVar20 = local_80;
        for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
          *pfVar20 = *pfVar19;
          pfVar19 = pfVar19 + 1;
          pfVar20 = pfVar20 + 1;
        }
        iVar18 = iVar18 * 2;
        local_114 = &DAT_004fa9a0 + (iVar17 % 3) * 0x50;
        transform_vec3_array_by_matrix(pfVar12,*(float **)(iVar9 + 0x28),iVar18,local_80);
        iVar18 = iVar18 + -2;
        local_150 = 0;
        pfVar12 = g_runtime_terrain_vertex_xyz_buffer;
        if (0 < iVar18) {
          do {
            iVar17 = local_150 + DAT_004fa920;
            iVar14 = local_150 + DAT_004fa918;
            local_10c = (pfVar12[iVar17 * 3] + pfVar12[iVar14 * 3]) * _DAT_004be7b4;
            local_108 = (pfVar12[iVar14 * 3 + 1] + pfVar12[iVar17 * 3 + 1]) * _DAT_004be7b4;
            local_104 = (pfVar12[iVar14 * 3 + 2] + pfVar12[iVar17 * 3 + 2]) * _DAT_004be7b4;
            if ((local_104 <= _DAT_004be7b8) &&
               (iVar10 = software_raster_queue_context_helper_00472c10(param_1,&local_10c,10.0),
               pfVar12 = g_runtime_terrain_vertex_xyz_buffer, iVar10 < 1)) {
              iVar10 = local_150 + DAT_004fa91c;
              local_110 = local_150 + DAT_004fa924;
              local_118 = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 3 + 2] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 2];
              local_120[0] = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 3] -
                             g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3];
              local_12c = local_118 *
                          (g_runtime_terrain_vertex_xyz_buffer[iVar17 * 3 + 1] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 1]) -
                          (g_runtime_terrain_vertex_xyz_buffer[iVar10 * 3 + 1] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 1]) *
                          (g_runtime_terrain_vertex_xyz_buffer[iVar17 * 3 + 2] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 2]);
              local_124 = (g_runtime_terrain_vertex_xyz_buffer[iVar10 * 3 + 1] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 1]) *
                          (g_runtime_terrain_vertex_xyz_buffer[iVar17 * 3] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3]) -
                          local_120[0] *
                          (g_runtime_terrain_vertex_xyz_buffer[iVar17 * 3 + 1] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 1]);
              local_128 = local_120[0] *
                          (g_runtime_terrain_vertex_xyz_buffer[iVar17 * 3 + 2] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 2]) -
                          local_118 *
                          (g_runtime_terrain_vertex_xyz_buffer[iVar17 * 3] -
                          g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3]);
              if (_DAT_004be7b0 <=
                  g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 1] * local_128 +
                  g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 2] * local_124 +
                  local_12c * g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3]) {
                puVar11 = i76_runtime_prepare_terrain_polygon_material_or_light();
                iVar15 = 10;
                puVar11[3] = 1;
                *puVar11 = 4;
                if (local_104 < _DAT_004be7bc) {
                  iVar15 = 0;
                }
                iVar15 = *(int *)(local_114 +
                                 ((int)(CONCAT44(local_150 >> 0x1f,local_150 >> 1) % 10) + iVar15) *
                                 4);
                puVar11[2] = local_158;
                iVar15 = polygon_renderer_context_helper_00471f00
                                   ((int *)(&DAT_0059c3a0 + iVar15 * 8),param_1);
                puVar11[1] = iVar15;
                pfVar12 = g_runtime_terrain_vertex_xyz_buffer + iVar14 * 3;
                puVar11[7] = *pfVar12;
                puVar11[8] = pfVar12[1];
                puVar11[9] = pfVar12[2];
                puVar11[10] = DAT_004fa8e8;
                puVar11[0xb] = DAT_004fa8ec;
                puVar11[0xc] = DAT_004fa8f0;
                fVar2 = g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 2] * _DAT_00643600 +
                        _DAT_006435fc;
                if (fVar2 < _DAT_004be7c0) {
                  fVar2 = _DAT_004be7c0;
                }
                if (_DAT_004be7c4 < fVar2) {
                  fVar2 = _DAT_004be7c4;
                }
                fVar2 = fVar2 * local_144 + fVar1;
                if (_DAT_004be7c4 < fVar2) {
                  fVar2 = _DAT_004be7c4;
                }
                puVar11[0xc] = fVar2;
                pfVar12 = g_runtime_terrain_vertex_xyz_buffer + iVar10 * 3;
                puVar11[0xd] = *pfVar12;
                puVar11[0xe] = pfVar12[1];
                puVar11[0xf] = pfVar12[2];
                puVar11[0x10] = DAT_004fa8f4;
                puVar11[0x11] = DAT_004fa8f8;
                puVar11[0x12] = DAT_004fa8fc;
                fVar2 = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 3 + 2] * _DAT_00643600 +
                        _DAT_006435fc;
                if (fVar2 < _DAT_004be7c0) {
                  fVar2 = _DAT_004be7c0;
                }
                if (_DAT_004be7c4 < fVar2) {
                  fVar2 = _DAT_004be7c4;
                }
                fVar2 = fVar2 * local_144 + fVar1;
                if (_DAT_004be7c4 < fVar2) {
                  fVar2 = _DAT_004be7c4;
                }
                puVar11[0x12] = fVar2;
                pfVar12 = g_runtime_terrain_vertex_xyz_buffer + iVar17 * 3;
                puVar11[0x13] = *pfVar12;
                puVar11[0x14] = pfVar12[1];
                puVar11[0x15] = pfVar12[2];
                puVar11[0x16] = DAT_004fa900;
                puVar11[0x17] = DAT_004fa904;
                puVar11[0x18] = DAT_004fa908;
                fVar2 = g_runtime_terrain_vertex_xyz_buffer[iVar17 * 3 + 2] * _DAT_00643600 +
                        _DAT_006435fc;
                if (fVar2 < _DAT_004be7c0) {
                  fVar2 = _DAT_004be7c0;
                }
                if (_DAT_004be7c4 < fVar2) {
                  fVar2 = _DAT_004be7c4;
                }
                fVar2 = fVar2 * local_144 + fVar1;
                if (_DAT_004be7c4 < fVar2) {
                  fVar2 = _DAT_004be7c4;
                }
                puVar11[0x18] = fVar2;
                pfVar12 = g_runtime_terrain_vertex_xyz_buffer + local_110 * 3;
                puVar11[0x19] = *pfVar12;
                puVar11[0x1a] = pfVar12[1];
                puVar11[0x1b] = pfVar12[2];
                puVar11[0x1c] = DAT_004fa90c;
                puVar11[0x1d] = DAT_004fa910;
                puVar11[0x1e] = DAT_004fa914;
                fVar2 = g_runtime_terrain_vertex_xyz_buffer[local_110 * 3 + 2] * _DAT_00643600 +
                        _DAT_006435fc;
                if (fVar2 < _DAT_004be7c0) {
                  fVar2 = _DAT_004be7c0;
                }
                if (_DAT_004be7c4 < fVar2) {
                  fVar2 = _DAT_004be7c4;
                }
                fVar2 = fVar2 * local_144 + fVar1;
                if (_DAT_004be7c4 < fVar2) {
                  fVar2 = _DAT_004be7c4;
                }
                puVar11[0x1e] = fVar2;
                fVar2 = (float)puVar11[9];
                pfVar12 = (float *)(puVar11 + 0xf);
                iVar17 = 3;
                do {
                  if (*pfVar12 - fVar2 < _DAT_004be7b0) {
                    fVar2 = *pfVar12;
                  }
                  pfVar12 = pfVar12 + 6;
                  iVar17 = iVar17 + -1;
                } while (iVar17 != 0);
                puVar11[4] = fVar2;
                i76_runtime_bin_terrain_primitive_for_scan_or_span_render(fVar2);
                pfVar12 = g_runtime_terrain_vertex_xyz_buffer;
              }
            }
            local_150 = local_150 + 2;
          } while (local_150 < iVar18);
        }
      }
      iVar9 = *(int *)(iVar9 + 4);
    } while (iVar9 != 0);
    if (DAT_00654b83 == '\0') {
      local_158 = 0;
      uVar7 = DAT_00644200;
    }
    else {
      local_158 = 0xf4;
      bVar8 = is_miss16_high_color_resource_mode();
      uVar7 = DAT_00644200;
      if (CONCAT31(extraout_var_00,bVar8) != 0) {
        local_158 = 0x17;
      }
    }
    for (; uVar7 != 0; uVar7 = *(uint *)(uVar7 + 0x60)) {
      cVar21 = *(int *)(uVar7 + 0x68) != 0;
      if (*(int *)(uVar7 + 0x6c) == 5) {
        cVar21 = '\x02';
      }
      if (cVar21 == '\0') {
        puVar11 = (undefined4 *)
                  zone_satellite_map_context_helper_00494be0
                            ((float *)(uVar7 + 0x84),(float *)(uVar7 + 0x18),local_98);
        puVar16 = local_100;
        for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar16 = *puVar11;
          puVar11 = puVar11 + 1;
          puVar16 = puVar16 + 1;
        }
        fVar22 = palette_dib_surface_flag_helper_00477af0();
        local_15c = (float)(fVar22 * (float10)DAT_006435f4);
        if (fVar22 * (float10)DAT_006435f4 < (float10)_DAT_004be7b0) {
          local_15c = 0.0;
        }
        fVar22 = palette_dib_surface_setter_helper_00477ae0();
        pfVar12 = (float *)raster_scratch_arena_context_helper_00472d30
                                     (local_120,param_1,(double)CONCAT44(local_100[1],local_100[0]),
                                      (double)CONCAT44(local_100[3],local_100[2]),
                                      (double)CONCAT44(local_ec,local_f0));
        local_12c = *pfVar12;
        local_128 = pfVar12[1];
        local_124 = pfVar12[2];
        iVar9 = software_raster_queue_context_helper_00472c10
                          (param_1,&local_12c,*(float *)(uVar7 + 0x90));
        if ((((iVar9 < 1) &&
             (bVar8 = ensure_world_object_geometry_variant_binding(uVar7,0),
             CONCAT31(extraout_var_01,bVar8) == 1)) && (iVar9 = *(int *)(uVar7 + 0x5c), iVar9 != 0))
           && ((2 < *(int *)(iVar9 + 4) && (*(int *)(iVar9 + 0x14) != 0)))) {
          pfVar12 = compose_matrix_or_transform_a
                              (local_40,(float *)(uVar7 + 0x18),(float *)(param_1 + 0x40));
          pfVar19 = local_d8;
          for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
            *pfVar19 = *pfVar12;
            pfVar12 = pfVar12 + 1;
            pfVar19 = pfVar19 + 1;
          }
          transform_vec3_array_by_matrix
                    (g_runtime_terrain_vertex_xyz_buffer,*(float **)(iVar9 + 0xc),
                     *(int *)(iVar9 + 4),local_d8);
          for (iVar9 = *(int *)(iVar9 + 0x14); iVar9 != 0; iVar9 = *(int *)(iVar9 + 0x30)) {
            iVar17 = transform_section_centroid_or_plane_by_matrix
                               ((float *)&local_e8,(float *)(iVar9 + 0xc),local_d8);
            if (*(float *)(iVar17 + 0xc) <= (float)_DAT_004be7a0) {
              puVar11 = i76_runtime_prepare_terrain_polygon_material_or_light();
              puVar11[3] = 1;
              *puVar11 = *(undefined4 *)(iVar9 + 4);
              puVar11[2] = local_158;
              if ((local_158 & 4) != 0) {
                if (*(char *)(iVar9 + 0x20) != '\0') {
                  uVar13 = bind_or_load_texture_set_for_object(uVar7,(byte *)(iVar9 + 0x20),param_1)
                  ;
                  puVar11[1] = uVar13;
                  if (uVar13 != 0) goto LAB_0048f17e;
                }
                puVar11[1] = (uint)*(byte *)(iVar9 + 8);
                puVar11[2] = puVar11[2] & 0xffffffeb;
              }
LAB_0048f17e:
              iVar17 = *(int *)(iVar9 + 4);
              iVar18 = 0;
              if (0 < iVar17) {
                puVar16 = puVar11 + 0xb;
                do {
                  iVar14 = *(int *)(((iVar17 - iVar18) + 3) * 0x10 + iVar9);
                  fVar1 = g_runtime_terrain_vertex_xyz_buffer[iVar14 * 3 + 2] * _DAT_00643600 +
                          _DAT_006435fc;
                  if (fVar1 < _DAT_004be7c0) {
                    fVar1 = _DAT_004be7c0;
                  }
                  if (_DAT_004be7c4 < fVar1) {
                    fVar1 = _DAT_004be7c4;
                  }
                  fVar1 = fVar1 * local_15c + (float)fVar22;
                  if (_DAT_004be7c4 < fVar1) {
                    fVar1 = _DAT_004be7c4;
                  }
                  iVar17 = ((iVar17 - iVar18) + -1) * 0x10 + iVar9;
                  puVar16[-1] = *(undefined4 *)(iVar17 + 0x48);
                  *puVar16 = *(undefined4 *)(iVar17 + 0x4c);
                  puVar16[1] = fVar1;
                  pfVar12 = g_runtime_terrain_vertex_xyz_buffer + iVar14 * 3;
                  iVar18 = iVar18 + 1;
                  puVar16[-4] = *pfVar12;
                  puVar16[-3] = pfVar12[1];
                  puVar16[-2] = pfVar12[2];
                  iVar17 = *(int *)(iVar9 + 4);
                  puVar16 = puVar16 + 6;
                } while (iVar18 < iVar17);
              }
              local_154 = (float)puVar11[9];
              if (1 < *(int *)(iVar9 + 4)) {
                pfVar12 = (float *)(puVar11 + 0xf);
                iVar17 = *(int *)(iVar9 + 4) + -1;
                do {
                  if (*pfVar12 - local_154 < _DAT_004be7b0) {
                    local_154 = *pfVar12;
                  }
                  pfVar12 = pfVar12 + 6;
                  iVar17 = iVar17 + -1;
                } while (iVar17 != 0);
              }
              puVar11[4] = local_154;
              i76_runtime_bin_terrain_primitive_for_scan_or_span_render(local_154);
            }
          }
        }
      }
    }
  }
  return;
}


