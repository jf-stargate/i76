/*
 * Program: i76.exe
 * Function: highlight_system_log_tag
 * Entry: 0048f2b0
 * Signature: undefined __cdecl highlight_system_log_tag(int param_1, int param_2, float param_3)
 */


/* cgpt whole-binary semantic rename v1: string evidence hlight */

void __cdecl highlight_system_log_tag(int param_1,int param_2,float param_3)

{
  int iVar1;
  int iVar2;
  LPVOID pvVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float *pfVar6;
  int iVar7;
  float *pfVar8;
  undefined4 *puVar9;
  undefined4 local_bc [4];
  undefined4 local_ac;
  undefined4 uStack_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98 [16];
  float local_58 [6];
  float local_40 [16];
  
  pvVar3 = release_world_object_tree_reference(*(LPVOID *)(param_1 + 0x68),s_hlight_004fac9c);
  if (pvVar3 == (LPVOID)0x0) {
    if (param_1 != DAT_00644200) {
      iVar2 = *(int *)(DAT_00644200 + 0x60);
      iVar7 = DAT_00644200;
      while (iVar1 = iVar2, iVar1 != param_1) {
        iVar7 = iVar1;
        iVar2 = *(int *)(iVar1 + 0x60);
      }
      *(undefined4 *)(iVar7 + 0x60) = *(undefined4 *)(param_1 + 0x60);
      return;
    }
    DAT_00644200 = *(undefined4 *)(DAT_00644200 + 0x60);
    return;
  }
  pfVar4 = compose_matrix_or_transform_a
                     (local_40,(float *)(param_1 + 0x18),(float *)((int)pvVar3 + 0x18));
  pfVar6 = local_98;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar6 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar6 = pfVar6 + 1;
  }
  pfVar4 = (float *)(param_1 + 0x84);
  puVar5 = (undefined4 *)zone_satellite_map_context_helper_00494be0(pfVar4,local_98,local_bc);
  puVar9 = local_bc;
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar9 = puVar9 + 1;
  }
  pfVar6 = (float *)raster_scratch_arena_context_helper_00472d30
                              (local_58,param_2,(double)CONCAT44(local_bc[1],local_bc[0]),
                               (double)CONCAT44(local_bc[3],local_bc[2]),
                               (double)CONCAT44(uStack_a8,local_ac));
  local_a4 = *pfVar6;
  local_a0 = pfVar6[1];
  local_9c = pfVar6[2];
  iVar7 = software_raster_queue_context_helper_00472c10
                    (param_2,&local_a4,*(float *)(param_1 + 0x90));
  if ((((iVar7 < 1) && (iVar7 = *(int *)(param_1 + 0x5c), iVar7 != 0)) && (2 < *(int *)(iVar7 + 4)))
     && (*(int *)(iVar7 + 0x14) != 0)) {
    pfVar6 = compose_matrix_or_transform_a(local_40,local_98,(float *)(param_2 + 0x40));
    pfVar8 = local_98;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar8 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar8 = pfVar8 + 1;
    }
    puVar5 = (undefined4 *)zone_satellite_map_context_helper_00494be0(pfVar4,local_98,local_58);
    puVar9 = local_bc;
    for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar9 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar9 = puVar9 + 1;
    }
    puVar5 = i76_runtime_prepare_terrain_polygon_material_or_light();
    puVar5[3] = 10;
    puVar5[7] = param_1;
    puVar5[8] = *pfVar4;
    puVar5[9] = *(undefined4 *)(param_1 + 0x88);
    puVar5[10] = *(undefined4 *)(param_1 + 0x8c);
    puVar5[0xb] = *(undefined4 *)(param_1 + 0x90);
    puVar5[0xc] = 0;
    pfVar4 = local_98;
    pfVar6 = (float *)(puVar5 + 0xd);
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar6 = *pfVar4;
      pfVar4 = pfVar4 + 1;
      pfVar6 = pfVar6 + 1;
    }
    if (param_3 < (float)(double)CONCAT44(uStack_a8,local_ac)) {
      i76_runtime_bin_terrain_primitive_for_scan_or_span_render(param_3);
      return;
    }
    i76_runtime_bin_terrain_primitive_for_scan_or_span_render
              ((float)(double)CONCAT44(uStack_a8,local_ac) - *(float *)(param_1 + 0x90));
  }
  return;
}


