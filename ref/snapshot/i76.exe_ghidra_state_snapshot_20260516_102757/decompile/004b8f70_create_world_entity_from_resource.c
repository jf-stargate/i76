/*
 * Program: i76.exe
 * Function: create_world_entity_from_resource
 * Entry: 004b8f70
 * Signature: undefined4 __cdecl create_world_entity_from_resource(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_004b8f70
   suggested_name: create_world_entity_from_resource
   basis: References wrldr and world-full entity creation diagnostic; adds indexed cache entry. */

undefined4 __cdecl create_world_entity_from_resource(int param_1)

{
  float fVar1;
  LPVOID pvVar2;
  double dVar3;
  LPVOID pvVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  char *pcVar12;
  float *pfVar13;
  undefined4 **ppuVar14;
  float *pfVar15;
  undefined4 *puVar16;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 fVar17;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float *local_1c4;
  float *local_1c0;
  char *local_1bc;
  double local_1b8;
  float local_1b0;
  undefined8 local_1a8;
  float local_1a0;
  float local_198;
  int local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  undefined4 *local_154 [2];
  int local_14c;
  undefined4 local_148 [12];
  undefined1 local_118 [20];
  int local_104;
  undefined4 local_100 [6];
  float local_e8;
  float local_e4;
  float local_e0;
  double local_d8;
  double local_d0;
  double local_c8;
  undefined4 local_c0 [30];
  float local_48 [17];
  
  pcVar12 = (char *)(param_1 + 8);
  ppuVar14 = local_154;
  for (iVar9 = 0x15; iVar9 != 0; iVar9 = iVar9 + -1) {
    *ppuVar14 = (undefined4 *)0x0;
    ppuVar14 = ppuVar14 + 1;
  }
  local_1bc = pcVar12;
  local_154[0] = (undefined4 *)
                 create_child_object_from_part_transform_record(0,(int)pcVar12,pcVar12,1,1);
  if (local_154[0] == (undefined4 *)0x0) {
    return 0;
  }
  iVar9 = *(int *)(param_1 + 0x6c);
  puVar8 = local_c0;
  for (iVar10 = 0x1e; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar8 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    puVar8 = puVar8 + 1;
  }
  pfVar13 = (float *)(local_1bc + 0x68);
  pfVar15 = DAT_005dd320;
  for (uVar11 = iVar9 * 3 & 0x3fffffff; uVar11 != 0; uVar11 = uVar11 - 1) {
    *pfVar15 = *pfVar13;
    pfVar13 = pfVar13 + 1;
    pfVar15 = pfVar15 + 1;
  }
  for (iVar10 = 0; iVar10 != 0; iVar10 = iVar10 + -1) {
    *(undefined1 *)pfVar15 = *(undefined1 *)pfVar13;
    pfVar13 = (float *)((int)pfVar13 + 1);
    pfVar15 = (float *)((int)pfVar15 + 1);
  }
  local_1c0 = DAT_005dd320;
  local_1c4 = DAT_005dd320 + 3;
  local_1d0 = *DAT_005dd320;
  local_1cc = DAT_005dd320[1];
  local_1c8 = DAT_005dd320[2];
  apply_world_object_transform_to_bounds_or_geometry((double)local_1d0,(double)local_1c8);
  local_1cc = (float)extraout_ST0;
  puVar8 = &DAT_004faed8;
  puVar6 = local_154[0] + 6;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar6 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar6 = puVar6 + 1;
  }
  *(double *)(local_154[0] + 0x10) = (double)local_1d0;
  *(double *)(local_154[0] + 0x12) = (double)extraout_ST0;
  *(double *)(local_154[0] + 0x14) = (double)local_1c8;
  pfVar13 = local_1c0;
  iVar10 = iVar9;
  if (0 < iVar9) {
    do {
      apply_world_object_transform_to_bounds_or_geometry((double)*pfVar13,(double)pfVar13[2]);
      pfVar13[1] = (float)extraout_ST0_00;
      fVar1 = *pfVar13;
      local_1b8 = *(double *)pfVar13;
      iVar10 = iVar10 + -1;
      local_1b0 = pfVar13[2];
      *pfVar13 = fVar1 - local_1d0;
      local_1a8 = (double)CONCAT44(pfVar13[1] - local_1cc,fVar1 - local_1d0);
      local_1a0 = local_1b0 - local_1c8;
      pfVar13[1] = pfVar13[1] - local_1cc;
      pfVar13[2] = local_1a0;
      pfVar13 = pfVar13 + 3;
    } while (iVar10 != 0);
  }
  local_194 = 0;
  local_1b8 = (double)CONCAT44(local_1b8._4_4_,iVar9 + -1);
  if (0 < iVar9 + -1) {
    do {
      pcVar12 = local_1bc;
      if (local_194 == 0) {
        pbVar5 = (byte *)format_8char_resource_basename_with_suffix
                                   (*(undefined4 *)local_1bc,*(undefined4 *)(local_1bc + 4),
                                    &DAT_00500640);
        iVar9 = parse_scene_object_descriptor_resource(pcVar12,(byte *)local_154,pbVar5);
        if (iVar9 == 0) {
          draw_classifier_display(local_154[0]);
          unlink_and_release_world_object_node_refcounted(local_154[0],s_wrldr_004ffd3c);
          return 0;
        }
        puVar8 = (undefined4 *)local_154[0][0x19];
        local_1a8 = (double)CONCAT44(local_1a8._4_4_,puVar8);
      }
      else {
        puVar8 = allocate_world_object_node((int)local_154[0]);
        if (puVar8 == (undefined4 *)0x0) break;
        set_world_object_class_and_register_runtime((int)puVar8,3);
        cache_add_indexed_entry((int)local_1a8,(int)puVar8);
      }
      *puVar8 = *local_154[0];
      puVar8[1] = local_154[0][1];
      local_16c = *local_1c0;
      local_168 = local_1c0[1];
      local_164 = local_1c0[2];
      local_184 = *local_1c4;
      local_1d0 = local_184 - local_16c;
      local_180 = local_1c4[1];
      local_17c = local_1c4[2];
      local_1cc = local_180 - local_168;
      local_1c8 = local_17c - local_164;
      local_198 = SQRT(local_1c8 * local_1c8 + local_1cc * local_1cc + local_1d0 * local_1d0) *
                  _DAT_004beca0;
      local_160 = local_1d0;
      local_15c = local_1cc;
      local_158 = local_1c8;
      puVar6 = (undefined4 *)
               zone_satellite_map_context_helper_00494880(local_1c0,&local_160,local_48);
      puVar16 = local_100;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar16 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar16 = puVar16 + 1;
      }
      local_178 = *local_1c0;
      local_174 = local_1c0[1];
      local_18c = local_198 * local_e4 + local_174;
      local_170 = local_1c0[2];
      local_188 = local_198 * local_e0 + local_170;
      local_d8 = (double)(local_198 * local_e8 + local_178);
      local_d0 = (double)(local_18c - (float)puVar8[0x26]);
      local_c8 = (double)local_188;
      local_1c0 = local_1c0 + 3;
      local_194 = local_194 + 1;
      puVar6 = local_100;
      puVar8 = puVar8 + 6;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar8 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar8 = puVar8 + 1;
      }
      local_1c4 = local_1c4 + 3;
    } while (local_194 < local_1b8._0_4_);
  }
  while( true ) {
    iVar9 = 0;
    local_1c4 = (float *)0x0;
    if (local_14c != 0) {
      iVar9 = vehicle_geometry_part_binding_context_helper_004b81c0(local_148);
    }
    piVar7 = register_active_world_object_entry
                       ((int)local_154[0],iVar9,(int *)(-(uint)(local_104 != 0) & (uint)local_118));
    if (piVar7 == (int *)0x0) {
      report_chunk_parse_error();
      return 0;
    }
    entity_instance_table_context_helper_00457560();
    piVar7 = (int *)entity_instance_id_table_context_helper_004574e0();
    if ((undefined4 *)*piVar7 != local_154[0]) {
      do {
        piVar7 = (int *)entity_instance_id_table_context_helper_004574e0();
      } while ((undefined4 *)*piVar7 != local_154[0]);
    }
    iVar9 = *(int *)(*piVar7 + 100);
    for (iVar10 = *(int *)(*(int *)(*piVar7 + 100) + 0x60); iVar10 != 0;
        iVar10 = *(int *)(iVar10 + 0x60)) {
      iVar9 = iVar10;
    }
    if (_DAT_004beca4 < (float)piVar7[4]) {
      local_1c4 = (float *)0x1;
      do {
        puVar8 = *(undefined4 **)(iVar9 + 0x68);
        if (puVar8 == local_154[0]) {
          return 1;
        }
        puVar8[0x18] = 0;
        compute_world_object_transformed_bounds(*piVar7,&local_1d0,&local_190);
        local_1d0 = (local_190 + local_1d0) * _DAT_004beca0;
        piVar7[1] = (int)local_1d0;
        local_1cc = (local_18c + local_1cc) * _DAT_004beca0;
        piVar7[2] = (int)local_1cc;
        local_1c8 = (local_188 + local_1c8) * _DAT_004beca0;
        piVar7[3] = (int)local_1c8;
        fVar17 = compute_world_object_bounding_radius_from_point
                           (*piVar7,local_1d0,local_1cc,local_1c8);
        piVar7[4] = (int)(float)fVar17;
        puVar8[0x18] = iVar9;
        iVar9 = *(int *)(iVar9 + 0x68);
      } while (_DAT_004beca4 < (float)piVar7[4]);
    }
    if (local_1c4 == (float *)0x0) break;
    iVar9 = *(int *)(iVar9 + 0x60);
    *(undefined4 *)(*(int *)(iVar9 + 0x68) + 0x60) = 0;
    *(undefined4 *)(iVar9 + 0x68) = 0;
    puVar8 = (undefined4 *)
             create_child_object_from_part_transform_record(0,(int)local_c0,local_1bc,1,1);
    if (puVar8 == (undefined4 *)0x0) {
      pvVar4 = *(LPVOID *)(iVar9 + 0x60);
      for (pvVar2 = *(LPVOID *)((int)*(LPVOID *)(iVar9 + 0x60) + 0x60); pvVar2 != (LPVOID)0x0;
          pvVar2 = *(LPVOID *)((int)pvVar2 + 0x60)) {
        pvVar4 = pvVar2;
      }
      while (pvVar4 != (LPVOID)0x0) {
        pvVar2 = *(LPVOID *)((int)pvVar4 + 0x68);
        unlink_and_release_world_object_node_refcounted(pvVar4,s_wrldr_004ffd3c);
        pvVar4 = pvVar2;
      }
      return 0;
    }
    puVar6 = local_154[0] + 6;
    puVar16 = puVar8 + 6;
    for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
      *puVar16 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar16 = puVar16 + 1;
    }
    puVar8[0x19] = iVar9;
    *(undefined4 **)(iVar9 + 0x68) = puVar8;
    dVar3 = *(double *)(iVar9 + 0x40) + *(double *)(puVar8 + 0x10);
    local_1b8 = *(double *)(iVar9 + 0x48) + *(double *)(puVar8 + 0x12);
    local_1a8 = *(double *)(iVar9 + 0x50) + *(double *)(puVar8 + 0x14);
    for (; iVar9 != 0; iVar9 = *(int *)(iVar9 + 0x60)) {
      *(double *)(iVar9 + 0x40) = (*(double *)(iVar9 + 0x40) + *(double *)(puVar8 + 0x10)) - dVar3;
      *(double *)(iVar9 + 0x48) =
           (*(double *)(iVar9 + 0x48) + *(double *)(puVar8 + 0x12)) - local_1b8;
      *(double *)(iVar9 + 0x50) =
           (*(double *)(puVar8 + 0x14) + *(double *)(iVar9 + 0x50)) - local_1a8;
    }
    *(double *)(puVar8 + 0x10) = dVar3;
    *(double *)(puVar8 + 0x12) = local_1b8;
    *(double *)(puVar8 + 0x14) = local_1a8;
    local_154[0] = puVar8;
    if (local_1c4 == (float *)0x0) {
      return 1;
    }
  }
  return 1;
}


