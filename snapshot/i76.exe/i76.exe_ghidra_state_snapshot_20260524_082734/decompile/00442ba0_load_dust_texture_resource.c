/*
 * Program: i76.exe
 * Function: load_dust_texture_resource
 * Entry: 00442ba0
 * Signature: undefined __cdecl load_dust_texture_resource(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: references xdu1_101.map */

void __cdecl load_dust_texture_resource(int param_1)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  float *pfVar12;
  int *piVar13;
  int *piVar14;
  float10 fVar15;
  float local_c;
  float local_8;
  float local_4;
  
  piVar13 = DAT_0052bae8;
  do {
    fVar15 = get_network_or_session_runtime_seconds();
    if ((float10)(float)piVar13[3] < fVar15) {
      piVar13[2] = 0;
      piVar13[6] = 0;
      piVar13[7] = 0;
    }
    fVar15 = get_network_or_session_runtime_seconds();
    if ((float10)(float)piVar13[3] < fVar15 - (float10)_DAT_004bd2c8) {
      if (piVar13[6] != piVar13[7]) {
        piVar13[6] = (&DAT_0052ba88)[piVar13[6]];
      }
      if (piVar13[6] != piVar13[7]) {
        piVar13[6] = (&DAT_0052ba88)[piVar13[6]];
      }
      if (piVar13[6] != piVar13[7]) {
        piVar13[6] = (&DAT_0052ba88)[piVar13[6]];
      }
      if (piVar13[6] != piVar13[7]) {
        piVar13[6] = (&DAT_0052ba88)[piVar13[6]];
      }
    }
    if (piVar13[6] != piVar13[7]) {
      transform_vec3_array_by_matrix
                (g_runtime_terrain_vertex_xyz_buffer,(float *)(piVar13 + 0x16),0x45,
                 (float *)(param_1 + 0x40));
      iVar3 = piVar13[0xb];
      iVar4 = piVar13[0xc];
      iVar5 = piVar13[10];
      piVar13[10] = 0;
      piVar13[0xb] = 0;
      piVar13[0xc] = 0;
      iVar11 = piVar13[7];
      iVar8 = piVar13[6];
      if (piVar13[6] != iVar11) {
        do {
          iVar6 = (&DAT_0052ba88)[iVar8];
          if (iVar8 == iVar11 + -1) {
            iVar11 = (&DAT_004f1d08)[piVar13[9] * 0x10 + iVar5];
          }
          else if (iVar8 == piVar13[6]) {
            iVar11 = (&DAT_004f1d30)[piVar13[9] * 0x10 + iVar4];
          }
          else {
            iVar11 = (&DAT_004f1d1c)[piVar13[9] * 0x10 + iVar3];
          }
          if (iVar11 != 0) {
            iVar7 = iVar6 * 3;
            pfVar1 = g_runtime_terrain_vertex_xyz_buffer + iVar8 * 9;
            local_c = (g_runtime_terrain_vertex_xyz_buffer[(iVar7 + 2) * 3] + *pfVar1) *
                      _DAT_004bd2cc;
            local_8 = (g_runtime_terrain_vertex_xyz_buffer[iVar6 * 9 + 7] + pfVar1[1]) *
                      _DAT_004bd2cc;
            local_4 = (pfVar1[2] + g_runtime_terrain_vertex_xyz_buffer[iVar6 * 9 + 8]) *
                      _DAT_004bd2cc;
            iVar9 = software_raster_queue_context_helper_00472c10(param_1,&local_c,12.0);
            if (iVar9 < 1) {
              piVar14 = &DAT_004f1ce0;
              do {
                puVar10 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
                puVar10[3] = 8;
                *puVar10 = 4;
                puVar10[2] = (&DAT_004f1d34)[piVar13[9] * 0x10];
                puVar10[1] = iVar11;
                pfVar1 = g_runtime_terrain_vertex_xyz_buffer + (iVar8 * 3 + *piVar14) * 3;
                puVar10[7] = *pfVar1;
                puVar10[8] = pfVar1[1];
                puVar10[9] = pfVar1[2];
                puVar10[10] = DAT_004f1cd4;
                puVar10[0xb] = DAT_004f1cd8;
                puVar10[0xc] = DAT_004f1cdc;
                pfVar1 = g_runtime_terrain_vertex_xyz_buffer + (iVar8 * 3 + piVar14[1]) * 3;
                puVar10[0xd] = *pfVar1;
                puVar10[0xe] = pfVar1[1];
                puVar10[0xf] = pfVar1[2];
                puVar10[0x10] = DAT_004f1cb0;
                puVar10[0x11] = DAT_004f1cb4;
                puVar10[0x12] = DAT_004f1cb8;
                pfVar1 = g_runtime_terrain_vertex_xyz_buffer + (iVar7 + piVar14[1]) * 3;
                puVar10[0x13] = *pfVar1;
                puVar10[0x14] = pfVar1[1];
                puVar10[0x15] = pfVar1[2];
                puVar10[0x16] = DAT_004f1cbc;
                puVar10[0x17] = DAT_004f1cc0;
                puVar10[0x18] = DAT_004f1cc4;
                pfVar1 = g_runtime_terrain_vertex_xyz_buffer + (iVar7 + *piVar14) * 3;
                puVar10[0x19] = *pfVar1;
                puVar10[0x1a] = pfVar1[1];
                pfVar12 = (float *)(puVar10 + 0xf);
                puVar10[0x1b] = pfVar1[2];
                puVar10[0x1c] = DAT_004f1cc8;
                puVar10[0x1d] = DAT_004f1ccc;
                puVar10[0x1e] = DAT_004f1cd0;
                iVar9 = 3;
                fVar2 = (float)puVar10[9];
                do {
                  if (*pfVar12 - fVar2 < _DAT_004bd2c0) {
                    fVar2 = *pfVar12;
                  }
                  pfVar12 = pfVar12 + 6;
                  iVar9 = iVar9 + -1;
                } while (iVar9 != 0);
                puVar10[4] = fVar2;
                i76_runtime_bin_terrain_polygon_work_record(fVar2);
                piVar14 = piVar14 + 2;
              } while ((int)piVar14 < 0x4f1cf8);
            }
          }
          iVar11 = piVar13[7];
          iVar8 = iVar6;
        } while (iVar6 != iVar11);
      }
    }
    piVar13 = (int *)*piVar13;
  } while (piVar13 != DAT_0052bae8);
  return;
}


