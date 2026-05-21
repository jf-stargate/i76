/*
 * Program: i76.exe
 * Function: highlight_visibility_context_helper_0048f570
 * Entry: 0048f570
 * Signature: undefined __cdecl highlight_visibility_context_helper_0048f570(int param_1, float * param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: highlight visibility context helper
   based on adjacent named subsystem context. */

void __cdecl highlight_visibility_context_helper_0048f570(int param_1,float *param_2)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  undefined3 extraout_var;
  float *pfVar6;
  undefined4 *puVar7;
  uint *puVar8;
  int iVar9;
  uint uVar10;
  float *pfVar11;
  float local_380 [16];
  float local_340 [16];
  float local_300 [4];
  undefined4 local_2f0 [188];
  
  uVar2 = *(uint *)(param_1 + 0x1c);
  bVar5 = ensure_world_object_geometry_variant_binding(uVar2,0);
  if (((CONCAT31(extraout_var,bVar5) == 1) && (*(int *)(uVar2 + 0x5c) != 0)) &&
     (2 < *(int *)(*(int *)(uVar2 + 0x5c) + 4))) {
    DAT_005dd3a8 = *(undefined4 *)(uVar2 + 0x40);
    DAT_005dd3ac = *(undefined4 *)(uVar2 + 0x44);
    DAT_005dd3b4 = *(undefined4 *)(uVar2 + 0x4c);
    DAT_005dd3b0 = *(undefined4 *)(uVar2 + 0x48);
    DAT_005dd3b8 = *(undefined4 *)(uVar2 + 0x50);
    DAT_005dd3bc = *(undefined4 *)(uVar2 + 0x54);
    iVar3 = *(int *)(uVar2 + 0x5c);
    pfVar6 = compose_matrix_or_transform_a(local_340,(float *)&DAT_005dd380,param_2 + 0x10);
    pfVar11 = local_380;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *pfVar11 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar11 = pfVar11 + 1;
    }
    transform_vec3_array_by_matrix
              (g_runtime_terrain_vertex_xyz_buffer,*(float **)(iVar3 + 0xc),*(int *)(iVar3 + 4),
               local_380);
    for (iVar3 = *(int *)(iVar3 + 0x14); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x30)) {
      pfVar6 = *(float **)(iVar3 + 4);
      if (0 < (int)pfVar6) {
        iVar9 = (int)pfVar6 << 4;
        puVar7 = local_2f0;
        pfVar11 = pfVar6;
        do {
          iVar4 = *(int *)(iVar3 + 0x30 + iVar9);
          puVar7[-1] = *(undefined4 *)(iVar3 + 0x38 + iVar9);
          *puVar7 = *(undefined4 *)(iVar3 + 0x3c + iVar9);
          puVar7[1] = 0x3f666666;
          iVar9 = iVar9 + -0x10;
          pfVar1 = g_runtime_terrain_vertex_xyz_buffer + iVar4 * 3;
          pfVar11 = (float *)((int)pfVar11 + -1);
          puVar7[-4] = *pfVar1;
          puVar7[-3] = pfVar1[1];
          puVar7[-2] = pfVar1[2];
          puVar7 = puVar7 + 6;
        } while (pfVar11 != (float *)0x0);
      }
      uVar10 = *(uint *)(&DAT_004f71b8 +
                        ((uint)*(byte *)(iVar3 + 0x1d) + (uint)*(byte *)(iVar3 + 0x1c) * 8) * 4);
      if (*(char *)(iVar3 + 0x1e) != '\0') {
        uVar10 = uVar10 & 0xffffffbf | 0xa0;
      }
      pfVar11 = (float *)(uVar10 & *(uint *)(uVar2 + 0x14) & 0xff);
      puVar8 = (uint *)(uint)*(byte *)(iVar3 + 8);
      if (((uint)pfVar11 & 4) != 0) {
        if ((*(char *)(iVar3 + 0x20) == '\0') ||
           (puVar8 = (uint *)bind_or_load_texture_set_for_object
                                       (uVar2,(byte *)(iVar3 + 0x20),(int)param_2),
           puVar8 == (uint *)0x0)) {
          bVar5 = false;
        }
        else {
          bVar5 = true;
        }
        if (!bVar5) {
          pfVar11 = (float *)((uint)pfVar11 & 0xffffffeb);
        }
      }
      if (*(int *)((int)param_2[0xf] + 8) == 1) {
        log_cache_memory_status(param_2,local_300,pfVar6,puVar8,pfVar11);
      }
      else {
        submit_lit_textured_polygon_to_renderer(param_2,local_300,(int)pfVar6,puVar8,(uint)pfVar11);
      }
    }
  }
  return;
}


