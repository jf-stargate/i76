/*
 * Program: i76.exe
 * Function: render_projectile_tracer_quads_variant_a
 * Entry: 004420b0
 * Signature: undefined __cdecl render_projectile_tracer_quads_variant_a(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Builds render quads for active
   projectile tracer/beam records using transformed vertex arrays and palette/material constants. */

void __cdecl render_projectile_tracer_quads_variant_a(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  float *pfVar7;
  float *pfVar8;
  int *piVar9;
  int iVar10;
  int *piVar11;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  piVar9 = DAT_0052ba48;
  do {
    if (piVar9[3] != piVar9[4]) {
      transform_vec3_array_by_matrix
                (g_runtime_terrain_vertex_xyz_buffer,(float *)(piVar9 + 7),6,
                 (float *)(param_1 + 0x40));
      iVar10 = piVar9[3];
      if (piVar9[3] != piVar9[4]) {
        do {
          iVar1 = (&DAT_0052ba38)[iVar10];
          iVar4 = iVar1 * 3;
          uVar2 = *(undefined4 *)(&DAT_004f1c38 + piVar9[5] * 0x18);
          if (piVar9[5] == 2) {
            local_18 = g_runtime_terrain_vertex_xyz_buffer[iVar1 * 9] +
                       g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9];
            local_14 = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9 + 1] +
                       g_runtime_terrain_vertex_xyz_buffer[iVar1 * 9 + 1];
            local_10 = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9 + 2] +
                       g_runtime_terrain_vertex_xyz_buffer[iVar1 * 9 + 2];
          }
          else {
            local_18 = g_runtime_terrain_vertex_xyz_buffer[(iVar4 + 2) * 3] +
                       g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9];
            local_14 = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9 + 1] +
                       g_runtime_terrain_vertex_xyz_buffer[iVar1 * 9 + 7];
            local_10 = g_runtime_terrain_vertex_xyz_buffer[iVar1 * 9 + 8] +
                       g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9 + 2];
          }
          local_14 = local_14 * _DAT_004bd2b0;
          local_18 = local_18 * _DAT_004bd2b0;
          local_10 = local_10 * _DAT_004bd2b0;
          iVar5 = software_raster_queue_context_helper_00472c10(param_1,&local_18,10.0);
          if (iVar5 < 1) {
            if (piVar9[5] == 2) {
              puVar6 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
              puVar6[3] = 8;
              *puVar6 = 2;
              puVar6[2] = 0;
              puVar6[1] = piVar9[6];
              local_c = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9] -
                        (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 9] -
                        g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9]) * _DAT_004bd2b4;
              local_8 = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9 + 1] -
                        (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 9 + 1] -
                        g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9 + 1]) * _DAT_004bd2b4;
              local_4 = g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9 + 2] -
                        (g_runtime_terrain_vertex_xyz_buffer[iVar1 * 9 + 2] -
                        g_runtime_terrain_vertex_xyz_buffer[iVar10 * 9 + 2]) * _DAT_004bd2b4;
              puVar6[7] = local_c;
              puVar6[8] = local_8;
              puVar6[9] = local_4;
              puVar6[0xc] = 0x3f800000;
              pfVar7 = g_runtime_terrain_vertex_xyz_buffer + iVar1 * 9;
              puVar6[0xd] = *pfVar7;
              puVar6[0xe] = pfVar7[1];
              fVar3 = pfVar7[2];
              puVar6[0x12] = 0x3f800000;
              puVar6[0xf] = fVar3;
              pfVar7 = (float *)(puVar6 + 0xf);
              fVar3 = (float)puVar6[9];
              iVar10 = 1;
              do {
                if (*pfVar7 - fVar3 < _DAT_004bd2b8) {
                  fVar3 = *pfVar7;
                }
                pfVar7 = pfVar7 + 6;
                iVar10 = iVar10 + -1;
              } while (iVar10 != 0);
              puVar6[4] = fVar3;
              i76_runtime_bin_terrain_polygon_work_record(fVar3);
            }
            else {
              piVar11 = &DAT_004f1bbc;
              do {
                puVar6 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
                puVar6[3] = 8;
                *puVar6 = 4;
                puVar6[2] = *(undefined4 *)(&DAT_004f1c3c + piVar9[5] * 0x18);
                puVar6[1] = uVar2;
                pfVar7 = g_runtime_terrain_vertex_xyz_buffer + (iVar4 + piVar11[-1]) * 3;
                puVar6[7] = *pfVar7;
                puVar6[8] = pfVar7[1];
                puVar6[9] = pfVar7[2];
                puVar6[10] = DAT_004f1bd0;
                puVar6[0xb] = DAT_004f1bd4;
                puVar6[0xc] = DAT_004f1bd8;
                pfVar7 = g_runtime_terrain_vertex_xyz_buffer + (iVar10 * 3 + piVar11[-1]) * 3;
                puVar6[0xd] = *pfVar7;
                puVar6[0xe] = pfVar7[1];
                puVar6[0xf] = pfVar7[2];
                puVar6[0x10] = DAT_004f1bdc;
                puVar6[0x11] = DAT_004f1be0;
                puVar6[0x12] = DAT_004f1be4;
                pfVar7 = g_runtime_terrain_vertex_xyz_buffer + (iVar10 * 3 + *piVar11) * 3;
                puVar6[0x13] = *pfVar7;
                puVar6[0x14] = pfVar7[1];
                puVar6[0x15] = pfVar7[2];
                puVar6[0x16] = DAT_004f1be8;
                puVar6[0x17] = DAT_004f1bec;
                puVar6[0x18] = DAT_004f1bf0;
                pfVar7 = g_runtime_terrain_vertex_xyz_buffer + (iVar4 + *piVar11) * 3;
                puVar6[0x19] = *pfVar7;
                puVar6[0x1a] = pfVar7[1];
                pfVar8 = (float *)(puVar6 + 0xf);
                puVar6[0x1b] = pfVar7[2];
                puVar6[0x1c] = DAT_004f1bf4;
                puVar6[0x1d] = DAT_004f1bf8;
                puVar6[0x1e] = DAT_004f1bfc;
                iVar5 = 3;
                fVar3 = (float)puVar6[9];
                do {
                  if (*pfVar8 - fVar3 < _DAT_004bd2b8) {
                    fVar3 = *pfVar8;
                  }
                  pfVar8 = pfVar8 + 6;
                  iVar5 = iVar5 + -1;
                } while (iVar5 != 0);
                puVar6[4] = fVar3;
                i76_runtime_bin_terrain_polygon_work_record(fVar3);
                piVar11 = piVar11 + 2;
              } while ((int)piVar11 < 0x4f1bd4);
            }
          }
          iVar10 = iVar1;
        } while (iVar1 != piVar9[4]);
      }
    }
    piVar9 = (int *)*piVar9;
  } while (piVar9 != DAT_0052ba48);
  return;
}


