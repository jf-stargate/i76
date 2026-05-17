/*
 * Program: i76.exe
 * Function: create_chunk_manager_geometry_runtime
 * Entry: 004a12f0
 * Signature: undefined4 __cdecl create_chunk_manager_geometry_runtime(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Chunk-manager geometry helper
   referencing chnkmgr and .geo resources. */

undefined4 __cdecl create_chunk_manager_geometry_runtime(int param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  float fVar4;
  LPVOID pvVar5;
  int iVar6;
  int iVar7;
  double *pdVar8;
  char *pcVar9;
  undefined4 *puVar10;
  int *piVar11;
  int *lpMem;
  int *piVar12;
  double *pdVar13;
  undefined4 *puVar14;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  int *local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  int local_16c;
  float local_168;
  float local_164;
  float local_160;
  uint local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  float local_148;
  float local_144;
  undefined4 local_140 [10];
  double local_118;
  double local_110;
  double local_108;
  float local_100 [16];
  float local_c0 [16];
  float local_80 [16];
  float local_40 [16];
  
  local_15c = (param_1 * 0x6cd + 0xaabU) % 0x71;
  if (local_15c < 0x71) {
    for (local_1a0 = (int *)(&DAT_005a8118)[local_15c]; local_1a0 != (int *)0x0;
        local_1a0 = (int *)local_1a0[0x11b]) {
      if (*local_1a0 == param_1) goto LAB_004a1355;
    }
    local_1a0 = (int *)0x0;
  }
  else {
    local_1a0 = (int *)0x0;
  }
LAB_004a1355:
  if (local_1a0 == (int *)0x0) {
    return 0;
  }
  local_16c = 0;
  if ((short)local_1a0[1] != 0) {
    pdVar13 = (double *)(local_1a0 + 0x10);
    do {
      pvVar5 = (LPVOID)create_vehicle_child_object_and_copy_ids(0,(undefined4 *)(pdVar13 + -7));
      iVar6 = get_root_ancestor_world_object(param_1);
      iVar7 = is_transform_composed_world_object_class(iVar6);
      if ((iVar7 == 0) && (*(int *)(iVar6 + 0x6c) != 8)) {
        compute_transform_relative_to_ancestor(local_80,iVar6,0);
        pdVar8 = (double *)compose_matrix_or_transform_a(local_c0,(float *)(pdVar13 + -6),local_100)
        ;
        iVar6 = 0x10;
        puVar10 = (undefined4 *)((int)pvVar5 + 0x18);
      }
      else {
        pdVar8 = pdVar13 + -6;
        puVar10 = (undefined4 *)((int)pvVar5 + 0x18);
        iVar6 = 0x10;
      }
      for (; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar10 = *(undefined4 *)pdVar8;
        pdVar8 = (double *)((int)pdVar8 + 4);
        puVar10 = puVar10 + 1;
      }
      *(undefined4 *)((int)pvVar5 + 0x84) = *(undefined4 *)(pdVar13 + 2);
      *(undefined4 *)((int)pvVar5 + 0x88) = *(undefined4 *)((int)pdVar13 + 0x14);
      *(undefined4 *)((int)pvVar5 + 0x8c) = *(undefined4 *)(pdVar13 + 3);
      *(undefined4 *)((int)pvVar5 + 0x90) = *(undefined4 *)((int)pdVar13 + 0x1c);
      pdVar8 = pdVar13 + 4;
      puVar10 = (undefined4 *)((int)pvVar5 + 0x94);
      for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar10 = *(undefined4 *)pdVar8;
        pdVar8 = (double *)((int)pdVar8 + 4);
        puVar10 = puVar10 + 1;
      }
      *(undefined4 *)((int)pvVar5 + 0x10) = 0;
      set_world_object_class_and_register_runtime((int)pvVar5,0x35);
      if (*(int *)((int)pvVar5 + 0x70) == 0) {
        unlink_and_release_world_object_node_refcounted(pvVar5,s_chnkmgr_004fe71c);
      }
      else {
        iVar7 = 0;
        iVar6 = 0;
        pcVar9 = format_8char_resource_basename_with_suffix
                           (*(undefined4 *)(pdVar13 + -7),*(undefined4 *)((int)pdVar13 + -0x34),
                            s__geo_004fe724);
        cache_add_entry((int)pvVar5,pcVar9,iVar6,iVar7);
        iVar6 = local_1a0[0x11a];
        if (iVar6 != 0) {
          ensure_world_object_geometry_variant_binding((int)pvVar5,0);
          if (*(int *)((int)pvVar5 + 0x5c) != 0) {
            bind_chunk_texture_slot_from_material
                      ((uint)pvVar5,*(int *)(*(int *)((int)pvVar5 + 0x5c) + 0x14),iVar6);
          }
        }
        attach_world_object_as_first_child((int)pvVar5,DAT_005aaac4);
        if (DAT_005aaac8 == (LPVOID)0x0) {
          _DAT_005aaacc = *(undefined4 *)((int)pvVar5 + 0x70);
          DAT_005aaac8 = pvVar5;
        }
        puVar10 = (undefined4 *)compute_transform_relative_to_ancestor(local_40,param_1,0);
        dVar1 = pdVar13[-1];
        dVar2 = *pdVar13;
        dVar3 = pdVar13[1];
        puVar14 = local_140;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar14 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar14 = puVar14 + 1;
        }
        local_168 = (float)local_118;
        local_164 = (float)local_110;
        local_160 = (float)local_108;
        local_184 = (float)dVar1 - local_168;
        local_148 = (float)dVar2;
        local_180 = (float)dVar2 - local_164;
        local_144 = (float)dVar3;
        local_17c = (float)dVar3 - local_160;
        if (SQRT(local_17c * local_17c + local_180 * local_180 + local_184 * local_184) ==
            _DAT_004bea80) {
          local_158 = 0;
          local_154 = 0x41200000;
          local_150 = 0;
          local_1a4 = 0.0;
          local_1ac = 0.0;
          local_1a8 = 10.0;
        }
        else {
          local_1ac = local_184 * _DAT_004bea88;
          local_1a8 = local_180 * _DAT_004bea88;
          local_1a4 = local_17c * _DAT_004bea88;
          local_178 = local_1ac;
          local_174 = local_1a8;
          local_170 = local_1a4;
        }
        fVar4 = local_1a4 * local_1a4 + local_1a8 * local_1a8 + local_1ac * local_1ac;
        while (_DAT_004bea8c < SQRT(fVar4)) {
          local_1ac = local_1ac * _DAT_004bea88;
          local_1a8 = local_1a8 * _DAT_004bea88;
          local_1a4 = local_1a4 * _DAT_004bea88;
          local_19c = local_1ac;
          local_198 = local_1a8;
          local_194 = local_1a4;
          fVar4 = local_1a4 * local_1a4 + local_1a8 * local_1a8 + local_1ac * local_1ac;
        }
        fVar4 = local_1a4 * local_1a4 + local_1a8 * local_1a8 + local_1ac * local_1ac;
        while (SQRT(fVar4) < _DAT_004bea90) {
          local_190 = local_1ac * _DAT_004bea94;
          local_18c = local_1a8 * _DAT_004bea94;
          local_188 = local_1a4 * _DAT_004bea94;
          local_1a4 = local_188;
          local_1ac = local_190;
          local_1a8 = local_18c;
          fVar4 = local_188 * local_188 + local_18c * local_18c + local_190 * local_190;
        }
        world_instance_id_lookup_context_helper_004ad2e0((int)pvVar5,&local_1ac);
      }
      local_16c = local_16c + 1;
      pdVar13 = pdVar13 + 0xe;
    } while (local_16c < (int)(uint)*(ushort *)(local_1a0 + 1));
  }
  if (((param_1 != 0) && (local_15c < 0x71)) &&
     (piVar12 = (int *)(&DAT_005a8118)[local_15c], piVar12 != (int *)0x0)) {
    if (*piVar12 == param_1) {
      (&DAT_005a8118)[local_15c] = piVar12[0x11b];
      lpMem = piVar12;
    }
    else {
      lpMem = (int *)piVar12[0x11b];
      if ((int *)piVar12[0x11b] == (int *)0x0) goto LAB_004a17e4;
      do {
        piVar11 = lpMem;
        if (*piVar11 == param_1) {
          piVar12[0x11b] = piVar11[0x11b];
          lpMem = piVar11;
          break;
        }
        lpMem = (int *)piVar11[0x11b];
        piVar12 = piVar11;
      } while (lpMem != (int *)0x0);
    }
    if (lpMem != (int *)0x0) {
      HeapFree(DAT_005aaac0,0,lpMem);
    }
  }
LAB_004a17e4:
  dispatch_queued_world_object_class_callbacks();
  return 1;
}


