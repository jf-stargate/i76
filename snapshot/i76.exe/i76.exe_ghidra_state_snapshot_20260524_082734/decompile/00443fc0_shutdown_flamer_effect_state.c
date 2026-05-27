/*
 * Program: i76.exe
 * Function: shutdown_flamer_effect_state
 * Entry: 00443fc0
 * Signature: undefined __cdecl shutdown_flamer_effect_state(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: flamer */

void __cdecl shutdown_flamer_effect_state(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  bool bVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float *pfVar14;
  int iVar15;
  int iVar16;
  undefined4 *puVar17;
  int iVar18;
  int iVar19;
  uint uVar20;
  undefined4 *puVar21;
  int *piVar22;
  float fVar23;
  int iVar24;
  int *piVar25;
  int *piVar26;
  float *pfVar27;
  float10 fVar28;
  uint in_stack_fffffdf4;
  float local_1dc;
  int local_1d4;
  float local_1cc;
  int local_1c8;
  float local_1c0;
  float local_1bc;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_14c [4];
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  int local_f4;
  int local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  undefined4 local_d4;
  int local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  int local_bc;
  int local_b8;
  undefined4 uStack_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  int local_a4;
  undefined2 local_a0;
  int local_94;
  float local_8c [6];
  float local_74;
  float local_70;
  float local_6c;
  double local_64;
  double local_5c;
  double local_54;
  float local_48;
  float local_40 [16];
  
  fVar28 = get_runtime_frame_delta_seconds();
  piVar22 = DAT_0052bb90;
  do {
    iVar18 = piVar22[1];
    if ((iVar18 != 0) && ((*(short *)(iVar18 + 8) != 0 || (*(short *)(piVar22[2] + 8) != 0)))) {
      release_world_object_light_runtime(iVar18);
      if ((LPVOID)piVar22[3] != (LPVOID)0x0) {
        unlink_and_release_world_object_node_refcounted((LPVOID)piVar22[3],s_flamer_004f22e0);
      }
      finalize_released_world_object_after_damage((LPVOID)piVar22[1],s_flamer_004f22e0);
      finalize_released_world_object_after_damage((LPVOID)piVar22[2],s_flamer_004f22e0);
      piVar22[1] = 0;
      piVar22[2] = 0;
      piVar22[3] = 0;
      piVar22[6] = 0;
      piVar22[7] = 0;
      piVar22[5] = 0;
      piVar22[10] = 0;
      piVar22[0xb] = 0;
      piVar22[0xc] = 0;
      piVar22[0xd] = 0;
    }
    if ((piVar22[1] != 0) && (piVar22[6] != piVar22[7])) {
      pfVar14 = (float *)compute_transform_relative_to_ancestor(local_40,piVar22[1],0);
      pfVar27 = local_8c;
      for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
        *pfVar27 = *pfVar14;
        pfVar14 = pfVar14 + 1;
        pfVar27 = pfVar27 + 1;
      }
      fVar8 = (float)piVar22[5];
      fVar23 = (float)local_64;
      iVar18 = piVar22[6];
      piVar25 = &local_a4;
      for (iVar19 = 6; fVar9 = local_70, iVar19 != 0; iVar19 = iVar19 + -1) {
        *piVar25 = 0;
        piVar25 = piVar25 + 1;
      }
      local_1d4 = 0;
      pfVar14 = (float *)&DAT_004f1ee8;
      pfVar27 = local_14c;
      for (iVar19 = 9; fVar13 = local_6c, fVar12 = local_74, iVar19 != 0; iVar19 = iVar19 + -1) {
        *pfVar27 = *pfVar14;
        pfVar14 = pfVar14 + 1;
        pfVar27 = pfVar27 + 1;
      }
      bVar10 = false;
      local_48 = fVar9;
      local_1c8 = -1;
      local_1ac = 0.0;
      local_1dc = 1.0;
      local_1c0 = (float)local_5c;
      local_1bc = (float)local_54;
      local_1cc = (fVar8 * _DAT_004bd31c * _DAT_004bd320) / fVar8;
      local_110 = _DAT_004bd318;
      local_e0 = fVar23;
      local_dc = local_1c0;
      local_d8 = local_1bc;
      do {
        transform_vec3_array_by_matrix((float *)(piVar22 + iVar18 * 9 + 0x23),local_14c,3,local_8c);
        iVar19 = 9;
        pfVar14 = (float *)&DAT_004f1f10;
        if (!bVar10) {
          pfVar14 = (float *)&DAT_004f1ee8;
        }
        pfVar27 = local_14c;
        for (; iVar19 != 0; iVar19 = iVar19 + -1) {
          *pfVar27 = *pfVar14;
          pfVar14 = pfVar14 + 1;
          pfVar27 = pfVar27 + 1;
        }
        local_1a0 = fVar13;
        local_1a8 = fVar12;
        local_1d4 = local_1d4 + 1;
        local_1a4 = local_1ac * local_1ac * _DAT_004bd324 * _DAT_004bd328 + local_48;
        local_1ac = local_1ac + (float)fVar28 / fVar8;
        local_14c[0] = local_1dc * local_14c[0];
        local_14c[1] = local_14c[1] * local_1dc;
        local_14c[2] = local_14c[2] * local_1dc;
        local_14c[3] = local_1dc * local_14c[3];
        local_13c = local_13c * local_1dc;
        local_138 = local_138 * local_1dc;
        local_134 = local_1dc * local_134;
        local_130 = local_130 * local_1dc;
        local_12c = local_12c * local_1dc;
        local_1dc = local_1cc + local_1dc;
        local_118 = local_1c0;
        local_114 = local_1bc;
        if (1 < local_1d4) {
          local_d4 = 0x3f800000;
          iVar19 = world_object_has_optional_runtime_flag(piVar22[2]);
          if (iVar19 != 0) {
            is_damage_side_effects_suppressed();
          }
          local_b8 = piVar22[0x10];
          uStack_b4 = 0;
          local_a4 = piVar22[2];
          local_a0 = 4;
          local_94 = ftol();
          fVar11 = local_c8;
          fVar9 = local_cc;
          if (local_94 == 0) {
            local_94 = 1;
          }
          piVar25 = &local_a4;
          piVar26 = (int *)&stack0xfffffdf4;
          for (iVar19 = 6; iVar19 != 0; iVar19 = iVar19 + -1) {
            *piVar26 = *piVar25;
            piVar25 = piVar25 + 1;
            piVar26 = piVar26 + 1;
          }
          iVar19 = scan_effect_targets_for_collision_response_a
                             (fVar23,local_118,local_114,local_110,fVar9,fVar11,local_c4,local_c0,
                              in_stack_fffffdf4);
          if (piVar22[0x22] == 1) {
            if ((bVar10) || (iVar19 != 0)) {
              if (local_1c8 == -1) {
                local_1c8 = iVar18;
              }
              local_1cc = (_DAT_004bd318 -
                          (float)(piVar22[5] - iVar18) / (float)(piVar22[5] - local_1c8)) *
                          _DAT_004bd338 * local_1cc;
              local_1a8 = fVar12 * _DAT_004bd33c;
              local_1a0 = fVar13 * _DAT_004bd33c;
              in_stack_fffffdf4 = piVar22[0xe];
              local_1a4 = 0.01;
              spawn_cached_explosion_runtime_object
                        (in_stack_fffffdf4,piVar22[0xf],DAT_0052bb90[2],fVar23,local_1c0,local_1bc,
                         local_f0);
              bVar10 = true;
            }
            else {
              local_108 = local_1a4 + local_1c0;
              fVar9 = (float)local_1d4 / ((float)piVar22[5] - _DAT_004bd310);
              local_104 = fVar13 + local_1bc;
              local_fc = (float)*(double *)(piVar22 + 0x1e);
              local_f8 = (float)*(double *)(piVar22 + 0x20);
              local_10c = fVar12 + fVar23;
              local_100 = (float)*(double *)(piVar22 + 0x1c);
              fVar9 = fVar9 * fVar9 * (float)fVar28 * _DAT_004bd334;
              local_124 = local_fc - local_108;
              local_120 = local_f8 - local_104;
              local_128 = local_100 - local_10c;
              local_1a8 = local_128 * fVar9 + fVar12;
              local_1a4 = local_124 * fVar9 + local_1a4;
              local_1a0 = local_120 * fVar9 + fVar13;
              local_ec = local_1a8;
              local_e8 = local_1a4;
              local_e4 = local_1a0;
            }
          }
        }
        if (local_1d4 == 1) {
          local_c8 = local_118;
          local_c4 = local_114;
          local_c0 = local_110;
          local_cc = fVar23;
        }
        fVar23 = fVar23 + local_1a8;
        local_1c0 = local_1c0 + local_1a4;
        local_1bc = local_1bc + local_1a0;
        iVar18 = (&DAT_0052bb40)[iVar18];
        local_64 = (double)fVar23;
        local_5c = (double)local_1c0;
        local_54 = (double)local_1bc;
      } while (local_1d4 < piVar22[5]);
      if (piVar22[3] != 0) {
        pfVar14 = local_8c;
        pfVar27 = (float *)(piVar22[3] + 0x18);
        for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
          *pfVar27 = *pfVar14;
          pfVar14 = pfVar14 + 1;
          pfVar27 = pfVar27 + 1;
        }
      }
      iVar18 = piVar22[5];
      pfVar14 = local_8c;
      pfVar27 = (float *)(piVar22 + 0x12);
      for (iVar19 = 0x10; iVar19 != 0; iVar19 = iVar19 + -1) {
        *pfVar27 = *pfVar14;
        pfVar14 = pfVar14 + 1;
        pfVar27 = pfVar27 + 1;
      }
      piVar22[0x22] = 1;
      transform_vec3_array_by_matrix
                (g_runtime_terrain_vertex_xyz_buffer,(float *)(piVar22 + 0x23),iVar18 * 3,
                 (float *)(param_1 + 0x40));
      iVar18 = piVar22[10];
      iVar19 = piVar22[0xd];
      iVar2 = piVar22[0xb];
      uVar1 = iVar18 + 1;
      iVar3 = piVar22[0xc];
      uVar20 = (int)uVar1 >> 0x1f;
      iVar24 = piVar22[6];
      piVar22[0xd] = 0;
      piVar22[10] = ((uVar1 ^ uVar20) - uVar20 & 3 ^ uVar20) - uVar20;
      uVar1 = iVar2 + 1;
      uVar20 = (int)uVar1 >> 0x1f;
      piVar22[0xb] = ((uVar1 ^ uVar20) - uVar20 & 3 ^ uVar20) - uVar20;
      uVar1 = iVar3 + 1;
      uVar20 = (int)uVar1 >> 0x1f;
      piVar22[0xc] = ((uVar1 ^ uVar20) - uVar20 & 3 ^ uVar20) - uVar20;
      iVar15 = piVar22[7];
      if (iVar24 != iVar15) {
        do {
          if (iVar24 == iVar15 + -1) {
            local_1d4 = (&DAT_004f1fe4)[piVar22[9] * 0x39 + iVar18];
          }
          else if (iVar24 == piVar22[6]) {
            local_1d4 = (&DAT_004f206c)[piVar22[9] * 0x39 + iVar3];
          }
          else {
            local_1d4 = (&DAT_004f2028)[piVar22[9] * 0x39 + iVar2];
          }
          iVar15 = (&DAT_0052bb40)[iVar24];
          iVar6 = iVar24 * 3;
          iVar7 = iVar15 * 3;
          pfVar14 = g_runtime_terrain_vertex_xyz_buffer + iVar24 * 9;
          local_d0 = (iVar7 + 2) * 0xc;
          local_bc = iVar15 * 0x24;
          local_b0 = (g_runtime_terrain_vertex_xyz_buffer[(iVar7 + 2) * 3] + *pfVar14) *
                     _DAT_004bd344;
          local_ac = (g_runtime_terrain_vertex_xyz_buffer[iVar15 * 9 + 7] + pfVar14[1]) *
                     _DAT_004bd344;
          local_a8 = (pfVar14[2] + g_runtime_terrain_vertex_xyz_buffer[iVar15 * 9 + 8]) *
                     _DAT_004bd344;
          local_f4 = iVar15;
          iVar16 = software_raster_queue_context_helper_00472c10(param_1,&local_b0,10.0);
          iVar24 = iVar15;
          if (iVar16 < 1) {
            piVar25 = &DAT_004f1f3c;
            do {
              puVar17 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
              puVar17[3] = 8;
              *puVar17 = 4;
              uVar4 = (&DAT_004f2090)[piVar22[9] * 0x39];
              puVar17[1] = local_1d4;
              puVar17[2] = uVar4;
              pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar6 + piVar25[-1]) * 3;
              puVar17[7] = *pfVar14;
              puVar17[8] = pfVar14[1];
              puVar17[9] = pfVar14[2];
              puVar17[10] = DAT_004f1f68;
              puVar17[0xb] = DAT_004f1f6c;
              puVar17[0xc] = DAT_004f1f70;
              pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar7 + piVar25[-1]) * 3;
              puVar17[0x19] = *pfVar14;
              puVar17[0x1a] = pfVar14[1];
              puVar17[0x1b] = pfVar14[2];
              puVar17[0x1c] = DAT_004f1f74;
              puVar17[0x1d] = DAT_004f1f78;
              puVar17[0x1e] = DAT_004f1f7c;
              pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar7 + *piVar25) * 3;
              puVar17[0x13] = *pfVar14;
              puVar17[0x14] = pfVar14[1];
              puVar17[0x15] = pfVar14[2];
              puVar17[0x16] = DAT_004f1f50;
              puVar17[0x17] = DAT_004f1f54;
              puVar17[0x18] = DAT_004f1f58;
              pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar6 + *piVar25) * 3;
              puVar17[0xd] = *pfVar14;
              puVar17[0xe] = pfVar14[1];
              iVar24 = 3;
              puVar17[0xf] = pfVar14[2];
              puVar17[0x10] = DAT_004f1f5c;
              puVar17[0x11] = DAT_004f1f60;
              puVar17[0x12] = DAT_004f1f64;
              pfVar14 = (float *)(puVar17 + 0xf);
              fVar23 = (float)puVar17[9];
              do {
                if (*pfVar14 - fVar23 < _DAT_004bd314) {
                  fVar23 = *pfVar14;
                }
                pfVar14 = pfVar14 + 6;
                iVar24 = iVar24 + -1;
              } while (iVar24 != 0);
              puVar17[4] = fVar23;
              i76_runtime_bin_terrain_polygon_work_record(fVar23);
              puVar17 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
              puVar17[3] = 8;
              *puVar17 = 4;
              puVar17[2] = (&DAT_004f2090)[piVar22[9] * 0x39];
              puVar17[1] = local_1d4;
              pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar6 + piVar25[-1]) * 3;
              puVar17[7] = *pfVar14;
              puVar17[8] = pfVar14[1];
              puVar17[9] = pfVar14[2];
              puVar17[10] = DAT_004f1f68;
              puVar17[0xb] = DAT_004f1f6c;
              puVar17[0xc] = DAT_004f1f70;
              pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar7 + piVar25[-1]) * 3;
              puVar17[0xd] = *pfVar14;
              puVar17[0xe] = pfVar14[1];
              puVar17[0xf] = pfVar14[2];
              puVar17[0x10] = DAT_004f1f74;
              puVar17[0x11] = DAT_004f1f78;
              puVar17[0x12] = DAT_004f1f7c;
              pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar7 + *piVar25) * 3;
              puVar17[0x13] = *pfVar14;
              puVar17[0x14] = pfVar14[1];
              puVar17[0x15] = pfVar14[2];
              puVar17[0x16] = DAT_004f1f50;
              puVar17[0x17] = DAT_004f1f54;
              puVar17[0x18] = DAT_004f1f58;
              pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar6 + *piVar25) * 3;
              puVar17[0x19] = *pfVar14;
              puVar17[0x1a] = pfVar14[1];
              iVar24 = 3;
              puVar17[0x1b] = pfVar14[2];
              puVar17[0x1c] = DAT_004f1f5c;
              puVar17[0x1d] = DAT_004f1f60;
              puVar17[0x1e] = DAT_004f1f64;
              pfVar14 = (float *)(puVar17 + 0xf);
              fVar23 = (float)puVar17[9];
              do {
                if (*pfVar14 - fVar23 < _DAT_004bd314) {
                  fVar23 = *pfVar14;
                }
                pfVar14 = pfVar14 + 6;
                iVar24 = iVar24 + -1;
              } while (iVar24 != 0);
              puVar17[4] = fVar23;
              i76_runtime_bin_terrain_polygon_work_record(fVar23);
              piVar25 = piVar25 + 2;
            } while ((int)piVar25 < 0x4f1f54);
            uVar4 = (&DAT_004f208c)[iVar19 + piVar22[9] * 0x39];
            puVar17 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
            puVar17[3] = 8;
            *puVar17 = 3;
            uVar5 = (&DAT_004f2090)[piVar22[9] * 0x39];
            puVar17[1] = uVar4;
            puVar17[2] = uVar5;
            puVar21 = (undefined4 *)((int)g_runtime_terrain_vertex_xyz_buffer + local_bc);
            puVar17[7] = *puVar21;
            puVar17[8] = puVar21[1];
            puVar17[9] = puVar21[2];
            puVar17[10] = DAT_004f1f50;
            puVar17[0xb] = DAT_004f1f54;
            puVar17[0xc] = DAT_004f1f58;
            pfVar14 = g_runtime_terrain_vertex_xyz_buffer + (iVar7 + 1) * 3;
            puVar17[0xd] = *pfVar14;
            puVar17[0xe] = pfVar14[1];
            puVar17[0xf] = pfVar14[2];
            puVar17[0x10] = DAT_004f1f5c;
            puVar17[0x11] = DAT_004f1f60;
            puVar17[0x12] = DAT_004f1f64;
            puVar21 = (undefined4 *)((int)g_runtime_terrain_vertex_xyz_buffer + local_d0);
            puVar17[0x13] = *puVar21;
            puVar17[0x14] = puVar21[1];
            puVar17[0x15] = puVar21[2];
            puVar17[0x16] = DAT_004f1f68;
            puVar17[0x17] = DAT_004f1f6c;
            puVar17[0x18] = DAT_004f1f70;
            pfVar14 = (float *)(puVar17 + 0xf);
            fVar23 = (float)puVar17[9];
            iVar24 = 2;
            do {
              if (*pfVar14 - fVar23 < _DAT_004bd314) {
                fVar23 = *pfVar14;
              }
              pfVar14 = pfVar14 + 6;
              iVar24 = iVar24 + -1;
            } while (iVar24 != 0);
            puVar17[4] = fVar23;
            i76_runtime_bin_terrain_polygon_work_record(fVar23);
            iVar24 = local_f4;
          }
          iVar15 = piVar22[7];
        } while (iVar24 != iVar15);
      }
    }
    piVar22 = (int *)*piVar22;
  } while (piVar22 != DAT_0052bb90);
  return;
}


