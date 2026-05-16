/*
 * Program: i76.exe
 * Function: test_vehicle_damage_volume_against_effect_target
 * Entry: 00440d90
 * Signature: undefined4 __cdecl test_vehicle_damage_volume_against_effect_target(int param_1, int param_2, float param_3, float * param_4, undefined4 * param_5, undefined4 * param_6)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Builds vehicle damage/collision
   transforms, expands a damage volume, and tests it against an effect target. */

undefined4 __cdecl
test_vehicle_damage_volume_against_effect_target
          (int param_1,int param_2,float param_3,float *param_4,undefined4 *param_5,
          undefined4 *param_6)

{
  float *this;
  float fVar1;
  float fVar2;
  float *pfVar3;
  undefined4 *puVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  undefined4 *puVar9;
  float in_stack_fffffee4;
  float in_stack_fffffee8;
  float in_stack_fffffeec;
  float in_stack_fffffef0;
  float in_stack_fffffef4;
  float in_stack_fffffef8;
  float in_stack_fffffefc;
  float in_stack_ffffff00;
  float in_stack_ffffff04;
  float in_stack_ffffff08;
  float fVar10;
  float fVar11;
  float fVar12;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  undefined4 local_9c;
  float local_98 [4];
  float local_88;
  float local_84;
  float local_80 [16];
  float local_40 [16];
  
  this = (float *)(param_1 + 0x38);
  pfVar3 = (float *)compose_matrix_or_transform_b(this,local_80);
  pfVar7 = local_40;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar7 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar7 = pfVar7 + 1;
  }
  pfVar3 = compose_matrix_or_transform_a(local_80,param_4,local_40);
  pfVar7 = local_40;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar7 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar7 = pfVar7 + 1;
  }
  fVar10 = 6.249857e-39;
  transform_vec3_array_by_matrix(local_98,(float *)(param_2 + 0x84),1,local_40);
  fVar11 = 6.249888e-39;
  get_world_object_damage_or_target_vectors(*(int *)(param_1 + 0x1c),&local_c4,&local_9c);
  local_b8 = *this * local_c4 +
             *(float *)(param_1 + 0x40) * local_bc + *(float *)(param_1 + 0x3c) * local_c0;
  local_b4 = *(float *)(param_1 + 0x4c) * local_bc +
             *(float *)(param_1 + 0x48) * local_c0 + *(float *)(param_1 + 0x44) * local_c4;
  local_b0 = *(float *)(param_1 + 0x54) * local_c0 +
             *(float *)(param_1 + 0x50) * local_c4 + *(float *)(param_1 + 0x58) * local_bc;
  fVar1 = *(float *)(param_2 + 0x90) * param_3;
  local_98[3] = -local_b8;
  local_88 = -local_b4;
  pfVar3 = &local_ac;
  fVar12 = 0.0;
  pfVar7 = &local_a0;
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) - fVar1;
  local_84 = -local_b0;
  *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) - fVar1;
  *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) - fVar1;
  *(float *)(param_1 + 0x2c) = fVar1 + *(float *)(param_1 + 0x2c);
  *(float *)(param_1 + 0x30) = fVar1 + *(float *)(param_1 + 0x30);
  *(float *)(param_1 + 0x34) = fVar1 + *(float *)(param_1 + 0x34);
  pfVar6 = (float *)(param_1 + 0x20);
  pfVar8 = (float *)&stack0xfffffefc;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar8 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    pfVar8 = pfVar8 + 1;
  }
  pfVar6 = local_98;
  pfVar8 = (float *)&stack0xfffffee4;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar8 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    pfVar8 = pfVar8 + 1;
  }
  iVar5 = test_swept_aabb_axis_interval_collision
                    (in_stack_fffffee4,in_stack_fffffee8,in_stack_fffffeec,in_stack_fffffef0,
                     in_stack_fffffef4,in_stack_fffffef8,in_stack_fffffefc,in_stack_ffffff00,
                     in_stack_ffffff04,in_stack_ffffff08,fVar10,fVar11,pfVar7,pfVar3,fVar12);
  if (iVar5 != 0) {
    param_5[0x12] = local_ac;
    param_5[0x13] = local_a8;
    param_5[0x14] = local_a4;
    param_6[0x12] = -local_ac;
    param_6[0x13] = -local_a8;
    param_6[0x14] = -local_a4;
    param_5[0x15] = -local_c4;
    param_5[0x16] = -local_c0;
    param_5[0x17] = -local_bc;
    param_6[0x15] = local_c4;
    param_6[0x16] = local_c0;
    param_6[0x17] = local_bc;
    param_6[0x11] = local_a0;
    param_5[0x11] = local_a0;
    *param_6 = 1;
    *param_5 = 1;
    param_5[1] = param_2;
    param_6[1] = *(undefined4 *)(param_1 + 0x1c);
    puVar4 = (undefined4 *)build_world_object_class_damage_transform(local_80,param_2);
    puVar9 = param_5 + 2;
    for (iVar5 = 0xf; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar9 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar9 = puVar9 + 1;
    }
    puVar4 = (undefined4 *)
             build_world_object_class_damage_transform(local_80,*(int *)(param_1 + 0x1c));
    puVar9 = param_6 + 2;
    for (iVar5 = 0xf; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar9 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar9 = puVar9 + 1;
    }
    fVar12 = *this * local_ac +
             *(float *)(param_1 + 0x44) * local_a8 + *(float *)(param_1 + 0x50) * local_a4;
    fVar2 = *(float *)(param_1 + 0x3c) * local_ac +
            *(float *)(param_1 + 0x54) * local_a4 + *(float *)(param_1 + 0x48) * local_a8;
    fVar1 = *(float *)(param_1 + 0x58);
    fVar10 = *(float *)(param_1 + 0x4c);
    fVar11 = *(float *)(param_1 + 0x40);
    param_6[0x18] = fVar12;
    fVar1 = fVar11 * local_ac + fVar10 * local_a8 + fVar1 * local_a4;
    param_6[0x19] = fVar2;
    param_6[0x1a] = fVar1;
    param_5[0x18] = -fVar12;
    param_5[0x19] = -fVar2;
    param_5[0x1a] = -fVar1;
    return 1;
  }
  return 0;
}


