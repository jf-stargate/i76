/*
 * Program: i76.exe
 * Function: update_vehicle_effect_collision_response
 * Entry: 0043d9e0
 * Signature: undefined __stdcall update_vehicle_effect_collision_response(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Large effect/vehicle collision response
   updater using object transforms, runtime delta, and collision state selectors. */

void update_vehicle_effect_collision_response(void)

{
  int iVar1;
  float fVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  float *pfVar9;
  undefined4 *puVar10;
  float *pfVar11;
  float10 fVar12;
  float in_stack_00000010;
  float in_stack_00000014;
  float in_stack_00000018;
  int in_stack_0000001c;
  float *in_stack_00000020;
  int *in_stack_00000024;
  float *in_stack_00000028;
  float *in_stack_0000002c;
  float in_stack_00000030;
  int in_stack_00000034;
  float in_stack_fffffe20;
  float in_stack_fffffe24;
  float in_stack_fffffe28;
  float in_stack_fffffe2c;
  float in_stack_fffffe30;
  float in_stack_fffffe34;
  float in_stack_fffffe38;
  float in_stack_fffffe3c;
  float in_stack_fffffe40;
  float in_stack_fffffe44;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float *pfVar17;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  int local_17c;
  int local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  float local_158;
  float local_154;
  float local_150;
  int local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c [4];
  float local_12c;
  float local_128;
  float local_124 [4];
  float local_114;
  float local_110;
  float local_10c [4];
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_cc [4];
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_8c [3];
  float local_80 [16];
  float local_40 [16];
  
  local_17c = 0;
  local_18c = 1e+30;
  for (iVar1 = in_stack_0000001c; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
    pfVar3 = compose_matrix_or_transform_a(local_80,(float *)(iVar1 + 0x18),in_stack_00000020);
    pfVar4 = local_10c;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar4 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar4 = pfVar4 + 1;
    }
    uVar7 = *(uint *)(iVar1 + 0x10) & 0xf000;
    if (uVar7 != 0x1000) {
      transform_vec3_array_by_matrix(local_13c,(float *)(iVar1 + 0x84),1,local_10c);
      local_164 = 0;
      local_160 = 0;
      local_15c = 0;
      pfVar3 = local_8c;
      fVar13 = 6.231413e-39;
      pfVar4 = (float *)effect_target_list_scan_context_helper_00438810(pfVar3,0.0,0.0,0.0,iVar1);
      local_13c[3] = *pfVar4;
      local_12c = pfVar4[1];
      local_128 = pfVar4[2];
      local_168 = *(float *)(iVar1 + 0x90);
      if (uVar7 == 0x5000) {
        local_168 = local_168 * _DAT_004bd204;
      }
      pfVar4 = &local_188;
      pfVar17 = &local_190;
      fVar12 = get_runtime_update_delta_seconds();
      fVar16 = (float)fVar12;
      fVar15 = local_168 + in_stack_00000030;
      pfVar9 = local_13c;
      pfVar11 = (float *)&stack0xfffffe38;
      for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
        *pfVar11 = *pfVar9;
        pfVar9 = pfVar9 + 1;
        pfVar11 = pfVar11 + 1;
      }
      puVar10 = (undefined4 *)&stack0xfffffe20;
      puVar8 = (undefined4 *)register0x00000010;
      for (iVar5 = 6; puVar8 = puVar8 + 1, iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar10 = *puVar8;
        puVar10 = puVar10 + 1;
      }
      iVar5 = test_effect_target_swept_interval_candidate
                        (in_stack_fffffe20,in_stack_fffffe24,in_stack_fffffe28,in_stack_fffffe2c,
                         in_stack_fffffe30,in_stack_fffffe34,in_stack_fffffe38,in_stack_fffffe3c,
                         in_stack_fffffe40,in_stack_fffffe44,fVar13,(float)pfVar3,fVar15,fVar16,
                         pfVar17,pfVar4);
      if (iVar5 != 0) {
        if (((uVar7 == 0x4000) || (uVar7 == 0x5000)) && (local_17c = 1, local_190 < local_18c)) {
          local_18c = local_190;
          local_174 = local_188;
          local_170 = local_184;
          local_16c = local_180;
          local_178 = iVar1;
        }
        if (((uVar7 == 0x3000) && (iVar5 = *(int *)(iVar1 + 0x80), iVar5 != 0)) &&
           (in_stack_00000034 != 0)) {
          pfVar4 = &local_188;
          pfVar17 = &local_190;
          puVar10 = (undefined4 *)&stack0xfffffe3c;
          puVar8 = (undefined4 *)register0x00000010;
          for (iVar6 = 6; puVar8 = puVar8 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar10 = *puVar8;
            puVar10 = puVar10 + 1;
          }
          in_stack_fffffe38 = 6.231811e-39;
          iVar5 = test_swept_point_against_effect_target_collision_payload
                            (in_stack_fffffe3c,in_stack_fffffe40,in_stack_fffffe44,fVar13,
                             (float)pfVar3,fVar15,iVar5,pfVar17,(int *)pfVar4);
          if ((iVar5 != 0) && (local_17c = 1, local_190 < local_18c)) {
            local_18c = local_190;
            local_174 = local_188;
            local_170 = local_184;
            local_16c = local_180;
            local_178 = iVar1;
          }
        }
        else {
          pfVar3 = (float *)compose_matrix_or_transform_b(local_10c,local_40);
          pfVar4 = local_cc;
          for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pfVar4 = *pfVar3;
            pfVar3 = pfVar3 + 1;
            pfVar4 = pfVar4 + 1;
          }
          pfVar3 = local_124;
          fVar14 = 6.232011e-39;
          transform_vec3_array_by_matrix(pfVar3,(float *)&stack0x00000004,1,local_cc);
          fVar16 = in_stack_00000010 - local_13c[3];
          fVar2 = in_stack_00000014 - local_12c;
          fVar15 = in_stack_00000018 - local_128;
          local_158 = fVar15 * local_b4 + fVar2 * local_cc[3] + fVar16 * local_cc[0];
          local_124[3] = local_158;
          local_154 = fVar15 * local_b0 + fVar2 * local_bc + fVar16 * local_cc[1];
          local_114 = local_154;
          pfVar4 = &local_188;
          local_150 = fVar15 * local_ac + fVar2 * local_b8 + fVar16 * local_cc[2];
          local_110 = local_150;
          pfVar17 = &local_190;
          puVar8 = (undefined4 *)(iVar1 + 0x94);
          puVar10 = (undefined4 *)&stack0xfffffe3c;
          fVar16 = in_stack_00000030;
          for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar10 = *puVar8;
            puVar8 = puVar8 + 1;
            puVar10 = puVar10 + 1;
          }
          pfVar9 = local_124;
          pfVar11 = (float *)&stack0xfffffe24;
          for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pfVar11 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar11 = pfVar11 + 1;
          }
          in_stack_fffffe20 = 6.232352e-39;
          iVar5 = test_swept_aabb_axis_interval_collision
                            (in_stack_fffffe24,in_stack_fffffe28,in_stack_fffffe2c,in_stack_fffffe30
                             ,in_stack_fffffe34,in_stack_fffffe38,in_stack_fffffe3c,
                             in_stack_fffffe40,in_stack_fffffe44,fVar13,fVar14,(float)pfVar3,pfVar17
                             ,pfVar4,fVar16);
          if ((iVar5 != 0) && (local_17c = 1, local_190 < local_18c)) {
            local_18c = local_190;
            local_174 = local_f4 * local_180 + local_10c[3] * local_184 + local_10c[0] * local_188;
            local_170 = local_f0 * local_180 + local_fc * local_184 + local_10c[1] * local_188;
            local_16c = local_ec * local_180 + local_f8 * local_184 + local_10c[2] * local_188;
            local_178 = iVar1;
            local_148 = local_174;
            local_144 = local_170;
            local_140 = local_16c;
          }
        }
      }
    }
    fVar13 = *(float *)(iVar1 + 100);
    if (fVar13 != 0.0) {
      puVar10 = (undefined4 *)&stack0xfffffe2c;
      puVar8 = (undefined4 *)register0x00000010;
      for (iVar5 = 6; puVar8 = puVar8 + 1, iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar10 = *puVar8;
        puVar10 = puVar10 + 1;
      }
      in_stack_fffffe28 = 6.232772e-39;
      iVar5 = update_vehicle_effect_collision_response();
      in_stack_fffffe44 = fVar13;
      if ((iVar5 != 0) && (local_17c = 1, local_190 < local_18c)) {
        local_18c = local_190;
        local_174 = local_188;
        local_170 = local_184;
        local_16c = local_180;
        local_178 = local_14c;
      }
    }
  }
  if (local_17c != 0) {
    *in_stack_00000028 = local_18c;
    *in_stack_0000002c = local_174;
    in_stack_0000002c[1] = local_170;
    in_stack_0000002c[2] = local_16c;
    *in_stack_00000024 = local_178;
  }
  return;
}


