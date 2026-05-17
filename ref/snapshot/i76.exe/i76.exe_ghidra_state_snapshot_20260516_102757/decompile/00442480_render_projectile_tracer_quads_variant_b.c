/*
 * Program: i76.exe
 * Function: render_projectile_tracer_quads_variant_b
 * Entry: 00442480
 * Signature: undefined __cdecl render_projectile_tracer_quads_variant_b(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Builds alternate/clipped render quads
   for projectile tracer/beam records using transformed vertex arrays and a visibility probe. */

void __cdecl render_projectile_tracer_quads_variant_b(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  float fVar6;
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
    if (piVar9[2] == 0) {
      piVar9[1] = 0;
      piVar9[3] = 0;
      piVar9[4] = 0;
    }
    if (piVar9[3] != piVar9[4]) {
      transform_vec3_array_by_matrix(DAT_005dd320,(float *)(piVar9 + 7),6,(float *)(param_1 + 0x40))
      ;
      iVar10 = piVar9[3];
      if (piVar9[3] != piVar9[4]) {
        do {
          iVar1 = (&DAT_0052ba38)[iVar10];
          iVar3 = iVar1 * 3;
          uVar2 = *(undefined4 *)(&DAT_004f1c38 + piVar9[5] * 0x18);
          if (piVar9[5] == 2) {
            local_18 = DAT_005dd320[iVar10 * 9] + DAT_005dd320[iVar1 * 9];
            local_14 = DAT_005dd320[iVar1 * 9 + 1] + DAT_005dd320[iVar10 * 9 + 1];
            fVar6 = DAT_005dd320[iVar1 * 9 + 2];
          }
          else {
            local_18 = DAT_005dd320[(iVar3 + 2) * 3] + DAT_005dd320[iVar10 * 9];
            local_14 = DAT_005dd320[iVar1 * 9 + 7] + DAT_005dd320[iVar10 * 9 + 1];
            fVar6 = DAT_005dd320[iVar1 * 9 + 8];
          }
          local_14 = local_14 * _DAT_004bd2b0;
          local_18 = local_18 * _DAT_004bd2b0;
          local_10 = (fVar6 + DAT_005dd320[iVar10 * 9 + 2]) * _DAT_004bd2b0;
          iVar4 = software_raster_queue_context_helper_00472c10(param_1,&local_18,10.0);
          if (iVar4 < 1) {
            if (piVar9[5] == 2) {
              puVar5 = terrain_map_context_helper_00490590();
              puVar5[3] = 8;
              *puVar5 = 2;
              puVar5[2] = 0;
              puVar5[1] = piVar9[6];
              local_c = DAT_005dd320[iVar10 * 9] -
                        (DAT_005dd320[iVar1 * 9] - DAT_005dd320[iVar10 * 9]) * _DAT_004bd2b4;
              local_8 = DAT_005dd320[iVar10 * 9 + 1] -
                        (DAT_005dd320[iVar1 * 9 + 1] - DAT_005dd320[iVar10 * 9 + 1]) * _DAT_004bd2b4
              ;
              local_4 = DAT_005dd320[iVar10 * 9 + 2] -
                        (DAT_005dd320[iVar1 * 9 + 2] - DAT_005dd320[iVar10 * 9 + 2]) * _DAT_004bd2b4
              ;
              puVar5[7] = local_c;
              puVar5[8] = local_8;
              puVar5[9] = local_4;
              puVar5[0xc] = 0x3f800000;
              pfVar8 = DAT_005dd320 + iVar1 * 9;
              puVar5[0xd] = *pfVar8;
              puVar5[0xe] = pfVar8[1];
              fVar6 = pfVar8[2];
              puVar5[0x12] = 0x3f800000;
              puVar5[0xf] = fVar6;
              pfVar8 = (float *)(puVar5 + 0xf);
              fVar6 = (float)puVar5[9];
              iVar10 = 1;
              do {
                if (*pfVar8 - fVar6 < _DAT_004bd2b8) {
                  fVar6 = *pfVar8;
                }
                pfVar8 = pfVar8 + 6;
                iVar10 = iVar10 + -1;
              } while (iVar10 != 0);
              puVar5[4] = fVar6;
            }
            else {
              piVar11 = &DAT_004f1bbc;
              do {
                puVar5 = terrain_map_context_helper_00490590();
                puVar5[3] = 8;
                *puVar5 = 4;
                puVar5[2] = *(undefined4 *)(&DAT_004f1c3c + piVar9[5] * 0x18);
                puVar5[1] = uVar2;
                pfVar8 = DAT_005dd320 + (iVar3 + piVar11[-1]) * 3;
                puVar5[7] = *pfVar8;
                puVar5[8] = pfVar8[1];
                puVar5[9] = pfVar8[2];
                puVar5[10] = DAT_004f1bd0;
                puVar5[0xb] = DAT_004f1bd4;
                puVar5[0xc] = DAT_004f1bd8;
                pfVar8 = DAT_005dd320 + (iVar10 * 3 + piVar11[-1]) * 3;
                puVar5[0xd] = *pfVar8;
                puVar5[0xe] = pfVar8[1];
                puVar5[0xf] = pfVar8[2];
                puVar5[0x10] = DAT_004f1bdc;
                puVar5[0x11] = DAT_004f1be0;
                puVar5[0x12] = DAT_004f1be4;
                pfVar8 = DAT_005dd320 + (iVar10 * 3 + *piVar11) * 3;
                puVar5[0x13] = *pfVar8;
                puVar5[0x14] = pfVar8[1];
                puVar5[0x15] = pfVar8[2];
                puVar5[0x16] = DAT_004f1be8;
                puVar5[0x17] = DAT_004f1bec;
                puVar5[0x18] = DAT_004f1bf0;
                pfVar8 = DAT_005dd320 + (iVar3 + *piVar11) * 3;
                puVar5[0x19] = *pfVar8;
                puVar5[0x1a] = pfVar8[1];
                pfVar7 = (float *)(puVar5 + 0xf);
                puVar5[0x1b] = pfVar8[2];
                puVar5[0x1c] = DAT_004f1bf4;
                puVar5[0x1d] = DAT_004f1bf8;
                puVar5[0x1e] = DAT_004f1bfc;
                iVar4 = 3;
                fVar6 = (float)puVar5[9];
                do {
                  if (*pfVar7 - fVar6 < _DAT_004bd2b8) {
                    fVar6 = *pfVar7;
                  }
                  pfVar7 = pfVar7 + 6;
                  iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
                puVar5[4] = fVar6;
                terrain_map_context_helper_0048fe10(fVar6);
                piVar11 = piVar11 + 2;
              } while ((int)piVar11 < 0x4f1bd4);
              puVar5 = terrain_map_context_helper_00490590();
              puVar5[3] = 8;
              *puVar5 = 3;
              puVar5[2] = 0;
              puVar5[1] = piVar9[6];
              pfVar8 = DAT_005dd320 + iVar1 * 9;
              puVar5[7] = *pfVar8;
              puVar5[8] = pfVar8[1];
              fVar6 = pfVar8[2];
              puVar5[0xc] = 0x3f800000;
              puVar5[9] = fVar6;
              pfVar8 = DAT_005dd320 + (iVar3 + 1) * 3;
              puVar5[0xd] = *pfVar8;
              puVar5[0xe] = pfVar8[1];
              puVar5[0xf] = pfVar8[2];
              puVar5[0x12] = 0x3f800000;
              pfVar8 = DAT_005dd320 + (iVar3 + 2) * 3;
              puVar5[0x13] = *pfVar8;
              puVar5[0x14] = pfVar8[1];
              fVar6 = pfVar8[2];
              puVar5[0x18] = 0x3f800000;
              puVar5[0x15] = fVar6;
              pfVar8 = (float *)(puVar5 + 0xf);
              fVar6 = (float)puVar5[9];
              iVar10 = 2;
              do {
                if (*pfVar8 - fVar6 < _DAT_004bd2b8) {
                  fVar6 = *pfVar8;
                }
                pfVar8 = pfVar8 + 6;
                iVar10 = iVar10 + -1;
              } while (iVar10 != 0);
              puVar5[4] = fVar6;
            }
            terrain_map_context_helper_0048fe10(fVar6);
          }
          iVar10 = iVar1;
        } while (iVar1 != piVar9[4]);
      }
    }
    piVar9[2] = 0;
    piVar9 = (int *)*piVar9;
  } while (piVar9 != DAT_0052ba48);
  return;
}


