/*
 * Program: i76.exe
 * Function: runtime_library_string_compare_helper_004bb1c0
 * Entry: 004bb1c0
 * Signature: undefined __cdecl runtime_library_string_compare_helper_004bb1c0(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: runtime library string compare helper
   based on adjacent named subsystem context. */

void __cdecl runtime_library_string_compare_helper_004bb1c0(int param_1,float *param_2)

{
  float *pfVar1;
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
  int iVar14;
  float local_340 [16];
  float local_300 [192];
  
  iVar11 = runtime_library_string_scan_helper_004bb370(local_340,param_1,param_2);
  if (iVar11 != 0) {
    fVar2 = param_2[2] * _DAT_005dbb10;
    fVar4 = param_2[1] * _DAT_005dbb0c;
    iVar11 = *(int *)(param_1 + 0x5c);
    fVar3 = _DAT_005dbb08 * *param_2;
    fVar5 = param_2[4] * _DAT_005dbb0c;
    fVar7 = param_2[5] * _DAT_005dbb10;
    fVar8 = param_2[6] * _DAT_005dbb08;
    fVar10 = param_2[7] * _DAT_005dbb0c;
    fVar6 = param_2[3] * _DAT_005dbb08;
    fVar9 = param_2[8] * _DAT_005dbb10;
    transform_vec3_array_by_matrix
              (DAT_005dd320,*(float **)(iVar11 + 0xc),*(int *)(iVar11 + 4),local_340);
    for (iVar11 = *(int *)(iVar11 + 0x14); iVar11 != 0; iVar11 = *(int *)(iVar11 + 0x30)) {
      if ((_DAT_004bff98 <=
           *(float *)(iVar11 + 0x10) * (fVar6 + fVar7 + fVar5) +
           *(float *)(iVar11 + 0x14) * (fVar9 + fVar10 + fVar8) +
           *(float *)(iVar11 + 0xc) * (fVar3 + fVar4 + fVar2)) &&
         ((*(byte *)(iVar11 + 0x1d) & 4) == 0)) {
        iVar12 = *(int *)(iVar11 + 4);
        iVar14 = 0;
        if (0 < iVar12) {
          do {
            iVar13 = (iVar12 - iVar14) + -1;
            iVar12 = *(int *)(((iVar12 - iVar14) + 3) * 0x10 + iVar11);
            iVar14 = iVar14 + 1;
            local_300[iVar13 * 6 + 5] = 0.0;
            pfVar1 = DAT_005dd320 + iVar12 * 3;
            local_300[iVar13 * 6] = *pfVar1;
            local_300[iVar13 * 6 + 1] = pfVar1[1];
            local_300[iVar13 * 6 + 2] = pfVar1[2];
            iVar12 = *(int *)(iVar11 + 4);
          } while (iVar14 < iVar12);
        }
        if (*(int *)((int)DAT_005dbac4[0xf] + 8) == 1) {
          log_cache_memory_status
                    (DAT_005dbac4,local_300,*(float **)(iVar11 + 4),(uint *)0xfe,(float *)0xc0);
        }
        else {
          submit_lit_textured_polygon_to_renderer
                    (DAT_005dbac4,local_300,(int)*(float **)(iVar11 + 4),(uint *)0xfe,0xc0);
        }
      }
    }
  }
  return;
}


