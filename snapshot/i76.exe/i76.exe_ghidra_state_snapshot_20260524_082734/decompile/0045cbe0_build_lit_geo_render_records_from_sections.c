/*
 * Program: i76.exe
 * Function: build_lit_geo_render_records_from_sections
 * Entry: 0045cbe0
 * Signature: undefined __cdecl build_lit_geo_render_records_from_sections(int param_1, float * param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [i76 level/static/material baseline v48]
   name: build_lit_geo_render_records_from_sections
   confidence: medium_high
   module: geo_render_records
   Builds lit textured render records from GEO sections. Prior tracing suggests reverse corner walk,
   per-corner UV copy, and lighting/normal index handling. Relevant to static GEO UV/material
   fidelity.
   note: Name already matches baseline. */

void __cdecl build_lit_geo_render_records_from_sections(int param_1,float *param_2,int param_3)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  float local_90 [4];
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  double local_68;
  double local_60;
  double local_58;
  float local_50 [16];
  float local_10 [4];
  
  iVar7 = *(int *)(param_1 + 0x5c);
  iVar9 = *(int *)(iVar7 + 0x14);
  if (iVar9 != 0) {
    pfVar1 = g_geo_render_transformed_positions_scratch + *(int *)(iVar7 + 4) * 3;
    pfVar3 = param_2;
    if ((*(byte *)(param_1 + 0x10) & 0x40) != 0) {
      DAT_005dd3a8 = param_2[10];
      DAT_005dd3ac = param_2[0xb];
      DAT_005dd3b4 = param_2[0xd];
      DAT_005dd3b0 = param_2[0xc];
      DAT_005dd3b8 = param_2[0xe];
      DAT_005dd3bc = param_2[0xf];
      pfVar3 = (float *)&DAT_005dd380;
    }
    pfVar3 = compose_matrix_or_transform_a(local_90,pfVar3,(float *)(param_3 + 0x40));
    pfVar10 = local_50;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar10 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar10 = pfVar10 + 1;
    }
    transform_vec3_array_by_matrix
              (g_geo_render_transformed_positions_scratch,*(float **)(iVar7 + 0xc),
               *(int *)(iVar7 + 4),local_50);
    compute_geo_vertex_lighting_from_normals
              (pfVar1,g_geo_render_transformed_positions_scratch,*(int *)(iVar7 + 0x10),param_2,
               local_50,*(float *)(iVar7 + 8));
    do {
      pfVar3 = local_50;
      pfVar10 = local_90;
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        *pfVar10 = *pfVar3;
        pfVar3 = pfVar3 + 1;
        pfVar10 = pfVar10 + 1;
      }
      iVar7 = 0;
      *(undefined4 *)(g_geo_render_next_record_scratch + 0x40) = 0;
      *(undefined4 *)(g_geo_render_next_record_scratch + 0x44) = 0;
      *(undefined4 *)(g_geo_render_next_record_scratch + 4) = 0;
      if (*(int *)(iVar9 + 4) < 3) {
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x24) = 0;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x28) = 0;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x2c) = 0;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x30) = 0;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x34) = 0;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x38) = 0;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x3c) = 0;
LAB_0045ce35:
        *(int *)(g_geo_render_next_record_scratch + 8) = param_1;
        strncpy((char *)(g_geo_render_next_record_scratch + 0xc),(char *)(iVar9 + 0x20),0xf);
        *(uint *)(g_geo_render_next_record_scratch + 0x1c) = (uint)*(byte *)(iVar9 + 8);
        if (*(char *)(iVar9 + 0x1c) == '\0') {
          *(undefined1 *)(iVar9 + 0x1c) = 4;
        }
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x20) =
             *(undefined4 *)
              (&DAT_004f71b8 +
              ((uint)*(byte *)(iVar9 + 0x1d) + (uint)*(byte *)(iVar9 + 0x1c) * 8) * 4);
        if (*(char *)(iVar9 + 0x1e) != '\0') {
          *(uint *)(g_geo_render_next_record_scratch + 0x20) =
               *(uint *)(g_geo_render_next_record_scratch + 0x20) | 0x80;
        }
        *(uint *)(g_geo_render_next_record_scratch + 0x20) =
             *(uint *)(g_geo_render_next_record_scratch + 0x20) & *(uint *)(param_1 + 0x14);
        *(uint *)(g_geo_render_next_record_scratch + 0x20) =
             *(uint *)(g_geo_render_next_record_scratch + 0x20) | g_geo_render_global_flag_mask;
        *(undefined4 *)(g_geo_render_next_record_scratch + 4) = *(undefined4 *)(iVar9 + 4);
        iVar6 = *(int *)(iVar9 + 4);
        if (0 < iVar6) {
          iVar8 = 0;
          do {
            iVar5 = ((iVar6 - iVar7) + -1) * 0x10 + iVar9;
            iVar6 = *(int *)(((iVar6 - iVar7) + 3) * 0x10 + iVar9);
            iVar2 = *(int *)(iVar5 + 0x44);
            *(undefined4 *)(g_geo_render_next_record_scratch + 0x54 + iVar8) =
                 *(undefined4 *)(iVar5 + 0x48);
            *(undefined4 *)(g_geo_render_next_record_scratch + 0x58 + iVar8) =
                 *(undefined4 *)(iVar5 + 0x4c);
            if (*(float *)(g_geo_render_next_record_scratch + 0x54 + iVar8) < _DAT_004be0e8) {
              *(undefined4 *)(g_geo_render_next_record_scratch + 0x20) = 0;
            }
            if (_DAT_004be0ec < *(float *)(g_geo_render_next_record_scratch + 0x54 + iVar8)) {
              *(undefined4 *)(g_geo_render_next_record_scratch + 0x20) = 0;
            }
            if (*(float *)(g_geo_render_next_record_scratch + 0x58 + iVar8) < _DAT_004be0e8) {
              *(undefined4 *)(g_geo_render_next_record_scratch + 0x20) = 0;
            }
            if (_DAT_004be0ec < *(float *)(g_geo_render_next_record_scratch + 0x58 + iVar8)) {
              *(undefined4 *)(g_geo_render_next_record_scratch + 0x20) = 0;
            }
            iVar7 = iVar7 + 1;
            *(float *)(g_geo_render_next_record_scratch + 0x5c + iVar8) = pfVar1[iVar2];
            pfVar3 = g_geo_render_transformed_positions_scratch + iVar6 * 3;
            pfVar10 = (float *)(g_geo_render_next_record_scratch + 0x48 + iVar8);
            iVar8 = iVar8 + 0x18;
            *pfVar10 = *pfVar3;
            pfVar10[1] = pfVar3[1];
            pfVar10[2] = pfVar3[2];
            iVar6 = *(int *)(iVar9 + 4);
          } while (iVar7 < iVar6);
        }
        iVar7 = g_geo_render_next_record_scratch + (*(int *)(iVar9 + 4) + 3) * 0x18;
      }
      else {
        *(float *)(g_geo_render_next_record_scratch + 0x24) =
             local_90[0] * *(float *)(iVar9 + 0x34) +
             local_90[3] * *(float *)(iVar9 + 0x38) + local_78 * *(float *)(iVar9 + 0x3c) +
             (float)local_68;
        *(float *)(g_geo_render_next_record_scratch + 0x28) =
             local_90[1] * *(float *)(iVar9 + 0x34) +
             local_80 * *(float *)(iVar9 + 0x38) + local_74 * *(float *)(iVar9 + 0x3c) +
             (float)local_60;
        *(float *)(g_geo_render_next_record_scratch + 0x2c) =
             local_90[2] * *(float *)(iVar9 + 0x34) +
             local_7c * *(float *)(iVar9 + 0x38) + local_70 * *(float *)(iVar9 + 0x3c) +
             (float)local_58;
        puVar4 = (undefined4 *)
                 transform_section_centroid_or_plane_by_matrix
                           (local_10,(float *)(iVar9 + 0xc),local_90);
        iVar6 = g_geo_render_next_record_scratch;
        *(undefined4 *)(g_geo_render_next_record_scratch + 0x30) = *puVar4;
        *(undefined4 *)(iVar6 + 0x34) = puVar4[1];
        *(undefined4 *)(iVar6 + 0x38) = puVar4[2];
        *(undefined4 *)(iVar6 + 0x3c) = puVar4[3];
        if (*(float *)(g_geo_render_next_record_scratch + 0x3c) <= _DAT_004be0d8) goto LAB_0045ce35;
        iVar7 = g_geo_render_next_record_scratch + 0x48;
      }
      iVar6 = g_geo_render_depth_tree_root;
      iVar8 = g_geo_render_next_record_scratch;
      if (g_geo_render_depth_tree_root != 0) {
        do {
          while (iVar8 = iVar6,
                *(float *)(iVar8 + 0x34) * *(float *)(g_geo_render_next_record_scratch + 0x28) +
                *(float *)(iVar8 + 0x30) * *(float *)(g_geo_render_next_record_scratch + 0x24) +
                *(float *)(iVar8 + 0x38) * *(float *)(g_geo_render_next_record_scratch + 0x2c) +
                *(float *)(iVar8 + 0x3c) < (float)_DAT_004be0e0) {
            iVar6 = *(int *)(iVar8 + 0x44);
            if (*(int *)(iVar8 + 0x44) == 0) {
              *(int *)(iVar8 + 0x44) = g_geo_render_next_record_scratch;
              iVar8 = g_geo_render_depth_tree_root;
              goto LAB_0045d037;
            }
          }
          iVar6 = *(int *)(iVar8 + 0x40);
        } while (*(int *)(iVar8 + 0x40) != 0);
        *(int *)(iVar8 + 0x40) = g_geo_render_next_record_scratch;
        iVar8 = g_geo_render_depth_tree_root;
      }
LAB_0045d037:
      g_geo_render_depth_tree_root = iVar8;
      iVar9 = *(int *)(iVar9 + 0x30);
      g_geo_render_next_record_scratch = iVar7;
    } while (iVar9 != 0);
  }
  return;
}


