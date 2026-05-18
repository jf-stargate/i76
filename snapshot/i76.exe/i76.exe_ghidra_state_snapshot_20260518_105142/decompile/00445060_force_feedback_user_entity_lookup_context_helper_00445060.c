/*
 * Program: i76.exe
 * Function: force_feedback_user_entity_lookup_context_helper_00445060
 * Entry: 00445060
 * Signature: undefined __cdecl force_feedback_user_entity_lookup_context_helper_00445060(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was player_force_feedback_user_entity_lookup_helper_00445060. Shorten
   readability label; force-feedback/user entity context is sufficient. */

void __cdecl force_feedback_user_entity_lookup_context_helper_00445060(int param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  undefined4 *puVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  int *local_40;
  int local_34;
  float local_c;
  float local_8;
  float local_4;
  
  local_40 = DAT_0052bb98;
  do {
    fVar9 = get_network_or_session_runtime_seconds();
    if ((float10)(float)local_40[3] < fVar9) {
      local_40[2] = 0;
      local_40[4] = 0;
    }
    if (1 < local_40[4]) {
      iVar7 = local_40[4] * 2;
      transform_vec3_array_by_matrix
                (g_runtime_terrain_vertex_xyz_buffer,(float *)(local_40 + 5),iVar7,
                 (float *)(param_1 + 0x40));
      iVar7 = iVar7 + -2;
      local_34 = 0;
      pfVar6 = g_runtime_terrain_vertex_xyz_buffer;
      if (0 < iVar7) {
        do {
          iVar8 = local_34 + DAT_004f22e8;
          iVar1 = local_34 + DAT_004f22f0;
          local_c = (pfVar6[iVar8 * 3] + pfVar6[iVar1 * 3]) * _DAT_004bd350;
          local_8 = (pfVar6[iVar1 * 3 + 1] + pfVar6[iVar8 * 3 + 1]) * _DAT_004bd350;
          local_4 = (pfVar6[iVar8 * 3 + 2] + pfVar6[iVar1 * 3 + 2]) * _DAT_004bd350;
          if ((local_4 < _DAT_004bd354) &&
             (iVar4 = software_raster_queue_context_helper_00472c10(param_1,&local_c,10.0),
             pfVar6 = g_runtime_terrain_vertex_xyz_buffer, iVar4 < 1)) {
            iVar4 = local_34 + DAT_004f22ec;
            iVar2 = local_34 + DAT_004f22f4;
            if (_DAT_004bd358 <=
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 1] *
                ((g_runtime_terrain_vertex_xyz_buffer[iVar4 * 3] -
                 g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3]) *
                 (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 3 + 2] -
                 g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 2]) -
                (g_runtime_terrain_vertex_xyz_buffer[iVar4 * 3 + 2] -
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 2]) *
                (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 3] -
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3])) +
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 2] *
                ((g_runtime_terrain_vertex_xyz_buffer[iVar4 * 3 + 1] -
                 g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 1]) *
                 (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 3] -
                 g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3]) -
                (g_runtime_terrain_vertex_xyz_buffer[iVar4 * 3] -
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3]) *
                (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 3 + 1] -
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 1])) +
                ((g_runtime_terrain_vertex_xyz_buffer[iVar4 * 3 + 2] -
                 g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 2]) *
                 (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 3 + 1] -
                 g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 1]) -
                (g_runtime_terrain_vertex_xyz_buffer[iVar4 * 3 + 1] -
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 1]) *
                (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 3 + 2] -
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3 + 2])) *
                g_runtime_terrain_vertex_xyz_buffer[iVar8 * 3]) {
              puVar5 = i76_runtime_prepare_terrain_polygon_material_or_light();
              puVar5[3] = 2;
              *puVar5 = 4;
              puVar5[2] = 0xc0;
              puVar5[1] = 0xfe;
              pfVar6 = g_runtime_terrain_vertex_xyz_buffer + iVar8 * 3;
              puVar5[7] = *pfVar6;
              puVar5[8] = pfVar6[1];
              puVar5[9] = pfVar6[2];
              puVar5[0xc] = 0;
              pfVar6 = g_runtime_terrain_vertex_xyz_buffer + iVar4 * 3;
              puVar5[0xd] = *pfVar6;
              puVar5[0xe] = pfVar6[1];
              fVar3 = pfVar6[2];
              puVar5[0x12] = 0;
              puVar5[0xf] = fVar3;
              pfVar6 = g_runtime_terrain_vertex_xyz_buffer + iVar1 * 3;
              puVar5[0x13] = *pfVar6;
              puVar5[0x14] = pfVar6[1];
              fVar3 = pfVar6[2];
              puVar5[0x18] = 0;
              puVar5[0x15] = fVar3;
              pfVar6 = g_runtime_terrain_vertex_xyz_buffer + iVar2 * 3;
              puVar5[0x19] = *pfVar6;
              puVar5[0x1a] = pfVar6[1];
              fVar3 = pfVar6[2];
              puVar5[0x1e] = 0;
              puVar5[0x1b] = fVar3;
              pfVar6 = (float *)(puVar5 + 0xf);
              fVar3 = (float)puVar5[9];
              iVar8 = 3;
              do {
                if (*pfVar6 - fVar3 < _DAT_004bd358) {
                  fVar3 = *pfVar6;
                }
                pfVar6 = pfVar6 + 6;
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              puVar5[4] = fVar3;
              i76_runtime_bin_terrain_primitive_for_scan_or_span_render(fVar3);
              pfVar6 = g_runtime_terrain_vertex_xyz_buffer;
            }
          }
          local_34 = local_34 + 2;
        } while (local_34 < iVar7);
      }
    }
    local_40 = (int *)*local_40;
  } while (local_40 != DAT_0052bb98);
  return;
}


