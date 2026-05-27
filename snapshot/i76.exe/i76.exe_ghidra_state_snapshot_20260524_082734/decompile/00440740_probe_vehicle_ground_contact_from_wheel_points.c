/*
 * Program: i76.exe
 * Function: probe_vehicle_ground_contact_from_wheel_points
 * Entry: 00440740
 * Signature: undefined4 __cdecl probe_vehicle_ground_contact_from_wheel_points(int param_1, undefined4 * param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Transforms wheel/contact
   sample points and probes downward against terrain/height data to fill contact records. */

undefined4 __cdecl
probe_vehicle_ground_contact_from_wheel_points(int param_1,undefined4 *param_2,float param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  float *pfVar9;
  undefined4 *puVar10;
  float *pfVar11;
  int iVar12;
  float *pfVar13;
  float10 extraout_ST0;
  float10 fVar14;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float local_120;
  float local_11c;
  float local_118;
  int local_110;
  int local_10c;
  int local_104;
  int local_100;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  int *local_bc;
  int local_b8 [4];
  float local_a8 [12];
  float local_78 [12];
  float afStack_48 [4];
  float local_38 [13];
  
                    /* I76 semantic baseline: probe_vehicle_ground_contact_from_wheel_points
                       Probes vehicle ground contact from wheel points. */
  iVar8 = get_vehicle_runtime_context(param_1);
  pfVar13 = (float *)(iVar8 + 4);
  transform_vec3_array_by_matrix(local_a8,pfVar13,4,(float *)(param_1 + 0x18));
  local_b8[0] = 0;
  local_b8[1] = 0;
  iVar12 = 0;
  local_b8[2] = 0;
  local_b8[3] = 0;
  pfVar11 = local_78;
  do {
    *(undefined4 *)((int)local_38 + iVar12) = *(undefined4 *)((int)local_a8 + iVar12);
    *(undefined4 *)((int)local_38 + iVar12 + 4) = *(undefined4 *)((int)local_a8 + iVar12 + 4);
    *(undefined4 *)((int)local_38 + iVar12 + 8) = *(undefined4 *)((int)local_a8 + iVar12 + 8);
    pfVar9 = (float *)effect_target_list_scan_context_helper_00438810
                                (&local_ec,*pfVar13,pfVar13[1],pfVar13[2],param_1);
    iVar12 = iVar12 + 0xc;
    *pfVar11 = *pfVar9;
    pfVar13 = pfVar13 + 3;
    fVar2 = pfVar9[2];
    pfVar11[1] = pfVar9[1];
    pfVar11[2] = fVar2;
    pfVar11 = pfVar11 + 3;
  } while (iVar12 < 0x30);
  local_104 = ftol();
  local_104 = local_104 + 1;
  if (7 < local_104) {
    local_104 = 7;
  }
  local_10c = 0;
  fVar2 = *(float *)(&DAT_004bd234 + local_104 * 4) * param_3;
  if (local_104 + 1 < 1) {
    return 0;
  }
  do {
    pfVar13 = local_a8;
    local_110 = 0;
    pfVar11 = local_78;
    local_100 = 0;
    do {
      local_bc = local_b8 + local_110;
      if (local_b8[local_110] == 0) {
        apply_world_object_transform_to_bounds_or_geometry
                  ((double)*pfVar13,(double)*(float *)((int)local_a8 + local_100 + 8));
        fVar14 = extraout_ST0 - (float10)*(float *)((int)local_a8 + local_100 + 4);
        fVar1 = (float)fVar14;
        if ((float10)_DAT_004bd254 <= fVar14) {
          local_f8 = *pfVar13;
          local_f4 = pfVar13[1];
          local_f0 = pfVar13[2];
          if (local_10c == 0) {
            iVar12 = 0;
            fVar14 = (float10)fVar1;
            local_120 = *pfVar13;
            local_11c = pfVar13[1];
            local_118 = pfVar13[2];
            do {
              if ((fVar14 < (float10)_DAT_004bd254) || ((float10)fVar1 < fVar14)) break;
              local_c8 = *pfVar11;
              local_c4 = pfVar11[1];
              fVar3 = -fVar2;
              local_c0 = pfVar11[2];
              local_118 = local_c0 * fVar3 + local_118;
              local_120 = local_c8 * fVar3 + local_120;
              local_11c = local_c4 * fVar3 + local_11c;
              apply_world_object_transform_to_bounds_or_geometry
                        ((double)local_120,(double)local_118);
              fVar14 = extraout_ST0_00 - (float10)local_11c;
              iVar12 = iVar12 + 1;
            } while (iVar12 < 0x32);
            if ((float10)_DAT_004bd254 < fVar14) {
              *local_bc = 1;
              goto LAB_00440a83;
            }
            if ((float10)_DAT_004bd260 <= fVar14) {
              *param_2 = 1;
              param_2[1] = 0;
              effect_target_list_scan_context_helper_004382e0(param_2 + 2);
              param_2[0x11] = 0;
              fVar2 = local_78[local_110 * 3 + 2];
              fVar1 = local_78[local_110 * 3 + 1] * _DAT_004bd264;
              param_2[0x15] = local_78[local_110 * 3] * _DAT_004bd264;
              fVar2 = fVar2 * _DAT_004bd264;
              param_2[0x16] = fVar1;
              param_2[0x17] = fVar2;
              puVar10 = (undefined4 *)(iVar8 + 4 + local_110 * 0xc);
              param_2[0x12] = *puVar10;
              param_2[0x13] = puVar10[1];
              param_2[0x14] = puVar10[2];
              puVar10 = (undefined4 *)
                        sample_runtime_terrain_packed_word
                                  (&local_ec,(double)local_120,SUB84((double)local_118,0),
                                   (int)((ulonglong)(double)local_118 >> 0x20));
              param_2[0x18] = *puVar10;
              param_2[0x19] = puVar10[1];
              param_2[0x1a] = puVar10[2];
              return 1;
            }
          }
          else {
            local_120 = local_38[local_110 * 3];
            local_11c = local_38[local_110 * 3 + 1];
            local_118 = local_38[local_110 * 3 + 2];
          }
          iVar12 = 0;
          goto LAB_00440be0;
        }
        fVar3 = *pfVar13;
        afStack_48[local_110] = fVar1;
        *(float *)((int)local_38 + local_100) = fVar3;
        fVar1 = pfVar13[2];
        *(float *)((int)local_38 + local_100 + 4) = pfVar13[1];
        *(float *)((int)local_38 + local_100 + 8) = fVar1;
        local_e0 = *pfVar11;
        local_dc = pfVar11[1];
        local_d4 = *pfVar13;
        local_d8 = pfVar11[2];
        local_ec = local_e0 * fVar2 + local_d4;
        local_d0 = pfVar13[1];
        local_cc = pfVar13[2];
        *pfVar13 = local_ec;
        local_e8 = local_dc * fVar2 + local_d0;
        pfVar13[1] = local_e8;
        local_e4 = local_d8 * fVar2 + local_cc;
        pfVar13[2] = local_e4;
      }
LAB_00440a83:
      local_110 = local_110 + 1;
      local_100 = local_100 + 0xc;
      pfVar11 = pfVar11 + 3;
      pfVar13 = pfVar13 + 3;
    } while (local_110 < 4);
    local_10c = local_10c + 1;
    if (local_104 + 1 <= local_10c) {
      return 0;
    }
  } while( true );
  while( true ) {
    fVar5 = fVar3;
    fVar6 = fVar4;
    fVar7 = fVar1;
    if ((float10)_DAT_004bd254 < fVar14) {
      fVar5 = local_120;
      fVar6 = local_11c;
      fVar7 = local_118;
      local_f8 = fVar3;
      local_f4 = fVar4;
      local_f0 = fVar1;
    }
    local_118 = fVar7;
    local_11c = fVar6;
    local_120 = fVar5;
    iVar12 = iVar12 + 1;
    if (0x31 < iVar12) break;
LAB_00440be0:
    fVar1 = (local_f0 + local_118) * _DAT_004bd258;
    fVar3 = (local_f8 + local_120) * _DAT_004bd258;
    fVar4 = (local_f4 + local_11c) * _DAT_004bd258;
    apply_world_object_transform_to_bounds_or_geometry((double)fVar3,(double)fVar1);
    fVar14 = extraout_ST0_01 - (float10)fVar4;
    if ((fVar14 < (float10)_DAT_004bd254) && ((float10)_DAT_004bd260 < fVar14)) break;
  }
  *param_2 = 1;
  param_2[1] = 0;
  effect_target_list_scan_context_helper_004382e0(param_2 + 2);
  fVar4 = local_78[local_110 * 3];
  param_2[0x11] = (float)local_10c * fVar2;
  fVar2 = local_78[local_110 * 3 + 2];
  fVar5 = local_78[local_110 * 3 + 1] * _DAT_004bd264;
  param_2[0x15] = fVar4 * _DAT_004bd264;
  fVar2 = fVar2 * _DAT_004bd264;
  param_2[0x16] = fVar5;
  param_2[0x17] = fVar2;
  puVar10 = (undefined4 *)(iVar8 + 4 + local_110 * 0xc);
  param_2[0x12] = *puVar10;
  param_2[0x13] = puVar10[1];
  param_2[0x14] = puVar10[2];
  puVar10 = (undefined4 *)
            sample_runtime_terrain_packed_word
                      (&local_ec,(double)fVar3,SUB84((double)fVar1,0),
                       (int)((ulonglong)(double)fVar1 >> 0x20));
  param_2[0x18] = *puVar10;
  param_2[0x19] = puVar10[1];
  param_2[0x1a] = puVar10[2];
  return 1;
}


