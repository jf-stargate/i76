/*
 * Program: i76.exe
 * Function: test_collision_between_effect_target_bounds
 * Entry: 0043ff80
 * Signature: undefined4 __cdecl test_collision_between_effect_target_bounds(int param_1, int param_2, int * param_3, int * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Tests collision between two transformed
   effect-target bounds/collision payloads. */

undefined4 __cdecl
test_collision_between_effect_target_bounds(int param_1,int param_2,int *param_3,int *param_4)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  float *pfVar9;
  undefined4 *puVar10;
  float *pfVar11;
  float *pfVar12;
  int *piVar13;
  float in_stack_fffffd10;
  float in_stack_fffffd14;
  float in_stack_fffffd18;
  float in_stack_fffffd1c;
  float in_stack_fffffd20;
  float in_stack_fffffd24;
  float in_stack_fffffd28;
  float in_stack_fffffd2c;
  float in_stack_fffffd30;
  float fVar14;
  float fVar15;
  float *pfVar16;
  float fVar17;
  int local_28c;
  float local_27c;
  float *local_278;
  float local_274;
  float local_270;
  float local_26c;
  float *local_268;
  undefined4 *local_264;
  int local_260 [17];
  float local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8 [4];
  float local_1d8;
  float local_1d4;
  float local_1d0 [4];
  float local_1c0;
  float local_1bc;
  float local_1b8 [6];
  float local_1a0;
  float local_19c;
  undefined4 local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  undefined4 local_180;
  float local_17c;
  float local_178;
  undefined4 local_174;
  float local_170;
  float local_16c;
  undefined4 local_168;
  float local_164;
  float local_160;
  float local_15c;
  int local_158 [17];
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec [3];
  float local_e0 [16];
  float local_a0 [16];
  float local_60 [24];
  
  pfVar1 = (float *)(param_1 + 0x2c);
  pfVar5 = (float *)(param_1 + 0x20);
  local_1b8[0] = *pfVar5;
  local_1b8[1] = (*(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x24)) * _DAT_004bd258;
  local_1b8[3] = (*pfVar1 + *pfVar5) * _DAT_004bd258;
  local_18c = (*(float *)(param_1 + 0x34) + *(float *)(param_1 + 0x28)) * _DAT_004bd258;
  local_1b8[2] = *(float *)(param_1 + 0x28);
  local_1b8[5] = *(float *)(param_1 + 0x28);
  local_1a0 = *pfVar1;
  local_198 = *(undefined4 *)(param_1 + 0x28);
  local_194 = *pfVar1;
  local_188 = *pfVar1;
  local_180 = *(undefined4 *)(param_1 + 0x34);
  local_174 = *(undefined4 *)(param_1 + 0x34);
  local_170 = *pfVar5;
  local_168 = *(undefined4 *)(param_1 + 0x34);
  local_164 = *pfVar5;
  pfVar1 = (float *)(param_2 + 0x38);
  local_1b8[4] = local_1b8[1];
  local_19c = local_1b8[1];
  local_190 = local_1b8[1];
  local_184 = local_1b8[1];
  local_17c = local_1b8[3];
  local_178 = local_1b8[1];
  local_16c = local_1b8[1];
  local_160 = local_1b8[1];
  local_15c = local_18c;
  pfVar5 = (float *)compose_matrix_or_transform_b(pfVar1,local_a0);
  pfVar12 = local_e0;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar12 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar12 = pfVar12 + 1;
  }
  pfVar5 = compose_matrix_or_transform_a(local_a0,(float *)(param_1 + 0x38),local_e0);
  pfVar12 = local_e0;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar12 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar12 = pfVar12 + 1;
  }
  transform_vec3_array_by_matrix(local_60,local_1b8,8,local_e0);
  local_21c = 1e+30;
  local_268 = (float *)(param_2 + 0xc);
  local_264 = (undefined4 *)(param_2 + 0x20);
  local_28c = 0;
  do {
    local_278 = (float *)((int)local_1b8 + local_28c);
    local_274 = *local_268;
    local_270 = local_268[1];
    local_26c = local_268[2];
    fVar15 = *local_278;
    pfVar12 = local_ec;
    fVar14 = 6.245544e-39;
    pfVar5 = (float *)effect_target_list_scan_context_helper_00438810
                                (pfVar12,fVar15,*(float *)((int)local_1b8 + local_28c + 4),
                                 *(float *)((int)local_1b8 + local_28c + 8),*(int *)(param_1 + 0x1c)
                                );
    fVar2 = *pfVar5 - local_274;
    fVar17 = 0.0;
    fVar3 = pfVar5[1] - local_270;
    fVar4 = pfVar5[2] - local_26c;
    local_1e8[3] = fVar2 * *pfVar1 +
                   fVar4 * *(float *)(param_2 + 0x40) + fVar3 * *(float *)(param_2 + 0x3c);
    local_1d8 = fVar2 * *(float *)(param_2 + 0x44) +
                fVar4 * *(float *)(param_2 + 0x4c) + fVar3 * *(float *)(param_2 + 0x48);
    local_1e8[0] = *(float *)((int)local_60 + local_28c);
    pfVar16 = &local_1f4;
    local_1d4 = fVar3 * *(float *)(param_2 + 0x54) +
                fVar2 * *(float *)(param_2 + 0x50) + fVar4 * *(float *)(param_2 + 0x58);
    local_1e8[1] = (float)*(undefined4 *)((int)local_60 + local_28c + 4);
    local_1e8[2] = (float)*(undefined4 *)((int)local_60 + local_28c + 8);
    pfVar5 = &local_27c;
    puVar8 = local_264;
    puVar10 = (undefined4 *)&stack0xfffffd28;
    for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar10 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar10 = puVar10 + 1;
    }
    pfVar9 = local_1e8;
    pfVar11 = (float *)&stack0xfffffd10;
    for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar11 = *pfVar9;
      pfVar9 = pfVar9 + 1;
      pfVar11 = pfVar11 + 1;
    }
    iVar7 = test_swept_aabb_axis_interval_collision
                      (in_stack_fffffd10,in_stack_fffffd14,in_stack_fffffd18,in_stack_fffffd1c,
                       in_stack_fffffd20,in_stack_fffffd24,in_stack_fffffd28,in_stack_fffffd2c,
                       in_stack_fffffd30,fVar14,(float)pfVar12,fVar15,pfVar5,pfVar16,fVar17);
    if ((iVar7 != 0) && (local_27c < local_21c)) {
      local_218 = *local_278;
      local_214 = local_278[1];
      local_20c = fVar2;
      local_210 = local_278[2];
      local_21c = local_27c;
      local_208 = fVar3;
      local_204 = fVar4;
      local_1f8 = local_1ec;
      local_200 = local_1f4;
      local_1fc = local_1f0;
      pfVar5 = local_1e8;
      pfVar12 = local_1d0;
      for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
        *pfVar12 = *pfVar5;
        pfVar5 = pfVar5 + 1;
        pfVar12 = pfVar12 + 1;
      }
    }
    local_28c = local_28c + 0xc;
  } while (local_28c < 0x60);
  if (_DAT_004bd25c <= local_21c) {
    return 0;
  }
  local_260[0] = 1;
  local_260[1] = *(int *)(param_2 + 0x1c);
  piVar6 = (int *)build_world_object_class_damage_transform(local_a0,local_260[1]);
  local_158[1] = *(int *)(param_1 + 0x1c);
  local_158[0] = 1;
  piVar13 = local_260 + 2;
  for (iVar7 = 0xf; iVar7 != 0; iVar7 = iVar7 + -1) {
    *piVar13 = *piVar6;
    piVar6 = piVar6 + 1;
    piVar13 = piVar13 + 1;
  }
  piVar6 = (int *)build_world_object_class_damage_transform(local_a0,local_158[1]);
  piVar13 = local_158 + 2;
  for (iVar7 = 0xf; iVar7 != 0; iVar7 = iVar7 + -1) {
    *piVar13 = *piVar6;
    piVar6 = piVar6 + 1;
    piVar13 = piVar13 + 1;
  }
  local_110 = local_1d0[3] * local_21c + local_1d0[0];
  local_10c = local_1c0 * local_21c + local_1d0[1];
  local_114 = local_21c;
  local_104 = local_20c;
  local_100 = local_208;
  local_108 = local_1bc * local_21c + local_1d0[2];
  local_fc = local_204;
  local_20c = -local_20c;
  local_208 = -local_208;
  local_204 = -local_204;
  fVar15 = *pfVar1 * local_200 +
           *(float *)(param_2 + 0x44) * local_1fc + *(float *)(param_2 + 0x50) * local_1f8;
  fVar2 = *(float *)(param_2 + 0x3c) * local_200 +
          *(float *)(param_2 + 0x54) * local_1f8 + *(float *)(param_2 + 0x48) * local_1fc;
  fVar4 = *(float *)(param_2 + 0x4c) * local_1fc;
  local_1fc = fVar2;
  fVar3 = *(float *)(param_2 + 0x40) * local_200;
  local_200 = fVar15;
  local_1f8 = fVar3 + fVar4 + *(float *)(param_2 + 0x58) * local_1f8;
  local_f4 = -fVar2;
  local_f8 = -fVar15;
  piVar6 = local_260;
  for (iVar7 = 0x1b; iVar7 != 0; iVar7 = iVar7 + -1) {
    *param_3 = *piVar6;
    piVar6 = piVar6 + 1;
    param_3 = param_3 + 1;
  }
  local_f0 = -local_1f8;
  piVar6 = local_158;
  for (iVar7 = 0x1b; iVar7 != 0; iVar7 = iVar7 + -1) {
    *param_4 = *piVar6;
    piVar6 = piVar6 + 1;
    param_4 = param_4 + 1;
  }
  return 1;
}


