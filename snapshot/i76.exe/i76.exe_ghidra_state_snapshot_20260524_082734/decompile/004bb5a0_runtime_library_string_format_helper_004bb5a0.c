/*
 * Program: i76.exe
 * Function: runtime_library_string_format_helper_004bb5a0
 * Entry: 004bb5a0
 * Signature: undefined __cdecl runtime_library_string_format_helper_004bb5a0(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: runtime library string format helper
   based on adjacent named subsystem context. */

void __cdecl runtime_library_string_format_helper_004bb5a0(int param_1,float *param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  float *pfVar14;
  float *pfVar15;
  float *local_350;
  float local_340 [16];
  float local_300 [5];
  undefined4 auStack_2ec [187];
  
  iVar11 = runtime_library_string_scan_helper_004bb370(local_340,param_1,param_2);
  if (iVar11 != 0) {
    fVar2 = param_2[1] * _DAT_005dbb0c;
    fVar4 = param_2[2] * _DAT_005dbb10;
    iVar11 = *(int *)(param_1 + 0x5c);
    fVar3 = _DAT_005dbb08 * *param_2;
    fVar5 = param_2[5] * _DAT_005dbb10;
    fVar7 = param_2[4] * _DAT_005dbb0c;
    fVar8 = param_2[8] * _DAT_005dbb10;
    fVar10 = param_2[7] * _DAT_005dbb0c;
    fVar6 = param_2[3] * _DAT_005dbb08;
    fVar9 = param_2[6] * _DAT_005dbb08;
    transform_vec3_array_by_matrix
              (g_runtime_terrain_vertex_xyz_buffer,*(float **)(iVar11 + 0xc),*(int *)(iVar11 + 4),
               local_340);
    for (iVar11 = *(int *)(iVar11 + 0x14); iVar11 != 0; iVar11 = *(int *)(iVar11 + 0x30)) {
      if (_DAT_004bff98 <=
          *(float *)(iVar11 + 0x10) * (fVar6 + fVar7 + fVar5) +
          *(float *)(iVar11 + 0x14) * (fVar9 + fVar10 + fVar8) +
          *(float *)(iVar11 + 0xc) * (fVar3 + fVar4 + fVar2)) {
        pfVar14 = (float *)0x0;
        local_350 = (float *)0x0;
        if (*(char *)(iVar11 + 0x1e) != '\0') {
          pfVar14 = (float *)0xc0;
          local_350 = (float *)0xc0;
        }
        iVar12 = *(int *)(iVar11 + 4);
        iVar13 = 0;
        if (0 < iVar12) {
          pfVar15 = local_300;
          do {
            iVar12 = iVar12 - iVar13;
            iVar13 = iVar13 + 1;
            iVar1 = *(int *)((iVar12 + 3) * 0x10 + iVar11);
            auStack_2ec[(iVar12 + -1) * 6] = 0;
            pfVar14 = g_runtime_terrain_vertex_xyz_buffer + iVar1 * 3;
            *pfVar15 = *pfVar14;
            pfVar15[1] = pfVar14[1];
            pfVar15[2] = pfVar14[2];
            iVar12 = *(int *)(iVar11 + 4);
            pfVar14 = local_350;
            pfVar15 = pfVar15 + 6;
          } while (iVar13 < iVar12);
        }
        if (*(int *)((int)DAT_005dbac4[0xf] + 8) == 1) {
          log_cache_memory_status
                    (DAT_005dbac4,local_300,*(float **)(iVar11 + 4),(uint *)0xfe,pfVar14);
        }
        else {
          submit_lit_textured_polygon_to_renderer
                    (DAT_005dbac4,local_300,(int)*(float **)(iVar11 + 4),(uint *)0xfe,(uint)pfVar14)
          ;
        }
      }
    }
  }
  return;
}


