/*
 * Program: i76.exe
 * Function: test_effect_target_swept_collision_against_object
 * Entry: 0043f8c0
 * Signature: undefined4 __cdecl test_effect_target_swept_collision_against_object(undefined4 * param_1, int param_2, float * param_3, int * param_4, int * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Large swept collision test between an
   effect-target collision payload and a world object, composing transforms and producing contact
   outputs. */

undefined4 __cdecl
test_effect_target_swept_collision_against_object
          (undefined4 *param_1,int param_2,float *param_3,int *param_4,int *param_5)

{
  float *pfVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  undefined4 *puVar10;
  float *pfVar11;
  int *piVar12;
  float *pfVar13;
  float10 fVar14;
  float in_stack_fffffce0;
  float in_stack_fffffce4;
  float in_stack_fffffce8;
  float in_stack_fffffcec;
  float in_stack_fffffcf0;
  float in_stack_fffffcf4;
  float in_stack_fffffcf8;
  float in_stack_fffffcfc;
  float in_stack_fffffd00;
  float in_stack_fffffd04;
  float fVar15;
  float fVar16;
  float fVar17;
  float local_2c4;
  int local_2c0;
  float local_2b8;
  int local_2b4;
  int local_2b0;
  float local_2ac;
  float local_2a8;
  float local_2a4;
  float local_2a0;
  float local_29c [4];
  float local_28c;
  float local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  float local_278 [6];
  undefined4 local_260;
  float local_25c;
  undefined4 local_258;
  undefined4 local_254;
  float local_250;
  undefined4 local_24c;
  float local_248;
  float local_244;
  float local_240;
  float local_23c [4];
  undefined4 local_22c;
  undefined4 local_228;
  float local_224 [4];
  undefined4 local_214;
  undefined4 local_210;
  float local_20c;
  float local_208 [10];
  double local_1e0;
  double local_1d8;
  double local_1d0;
  float local_1c8 [3];
  float local_1bc [3];
  float local_1b0 [3];
  float local_1a4 [6];
  undefined4 local_18c;
  int local_188;
  undefined4 local_184 [6];
  float local_16c [16];
  float local_12c [12];
  float local_fc [16];
  float local_bc [16];
  undefined4 local_7c [15];
  float local_40 [16];
  
  do {
    if (param_2 == 0) {
      return 0;
    }
    pfVar1 = compose_matrix_or_transform_a(local_fc,(float *)(param_2 + 0x18),param_3);
    pfVar6 = local_208;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar6 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar6 = pfVar6 + 1;
    }
    uVar2 = *(uint *)(param_2 + 0x10) & 0xf000;
    if (uVar2 != 0x1000) {
      local_23c[0] = (float)local_1e0;
      local_284 = 0;
      local_23c[1] = (float)local_1d8;
      local_23c[2] = (float)local_1d0;
      local_280 = 0;
      local_27c = 0;
      pfVar1 = local_1b0;
      fVar15 = 6.242532e-39;
      puVar3 = (undefined4 *)
               effect_target_list_scan_context_helper_00438810(pfVar1,0.0,0.0,0.0,param_2);
      local_23c[3] = (float)*puVar3;
      local_22c = puVar3[1];
      fVar16 = (float)param_1[6] + *(float *)(param_2 + 0x90);
      local_228 = puVar3[2];
      pfVar6 = local_1c8;
      pfVar13 = &local_20c;
      fVar14 = get_runtime_update_delta_seconds();
      fVar17 = (float)fVar14;
      pfVar9 = local_23c;
      pfVar11 = (float *)&stack0xfffffcf8;
      for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
        *pfVar11 = *pfVar9;
        pfVar9 = pfVar9 + 1;
        pfVar11 = pfVar11 + 1;
      }
      puVar3 = param_1;
      puVar10 = (undefined4 *)&stack0xfffffce0;
      for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar10 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar10 = puVar10 + 1;
      }
      iVar7 = test_effect_target_swept_interval_candidate
                        (in_stack_fffffce0,in_stack_fffffce4,in_stack_fffffce8,in_stack_fffffcec,
                         in_stack_fffffcf0,in_stack_fffffcf4,in_stack_fffffcf8,in_stack_fffffcfc,
                         in_stack_fffffd00,in_stack_fffffd04,fVar15,(float)pfVar1,fVar16,fVar17,
                         pfVar13,pfVar6);
      if (iVar7 != 0) {
        if (uVar2 < 0x3001) {
          if (uVar2 == 0x3000) {
            local_278[0] = (float)param_1[8];
            local_278[1] = ((float)param_1[9] + (float)param_1[0xc]) * _DAT_004bd258;
            local_254 = param_1[8];
            local_278[3] = (float)param_1[0xb];
            local_278[5] = (float)param_1[10];
            local_260 = param_1[0xb];
            local_258 = param_1[0xd];
            local_24c = param_1[0xd];
            local_278[2] = (float)param_1[10];
            iVar7 = *(int *)(param_2 + 0x80);
            local_278[4] = local_278[1];
            local_25c = local_278[1];
            local_250 = local_278[1];
            transform_vec3_array_by_matrix(local_12c,local_278,4,(float *)(param_1 + 0xe));
            local_2c4 = 1e+30;
            local_2c0 = 0;
            do {
              fVar17 = *(float *)((int)local_278 + local_2c0);
              pfVar6 = local_1bc;
              fVar16 = 6.243303e-39;
              puVar3 = (undefined4 *)
                       effect_target_list_scan_context_helper_00438810
                                 (pfVar6,fVar17,*(float *)((int)local_278 + local_2c0 + 4),
                                  *(float *)((int)local_278 + local_2c0 + 8),param_1[7]);
              local_224[3] = (float)*puVar3;
              local_214 = puVar3[1];
              local_224[0] = *(float *)((int)local_12c + local_2c0);
              local_210 = puVar3[2];
              local_224[1] = (float)*(undefined4 *)((int)local_12c + local_2c0 + 4);
              pfVar13 = &local_248;
              pfVar1 = &local_2a0;
              local_224[2] = (float)*(undefined4 *)((int)local_12c + local_2c0 + 8);
              pfVar9 = local_224;
              pfVar11 = (float *)&stack0xfffffcfc;
              iVar4 = iVar7;
              for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
                *pfVar11 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar11 = pfVar11 + 1;
              }
              in_stack_fffffcf8 = 6.243457e-39;
              iVar4 = test_swept_point_against_effect_target_collision_payload
                                (in_stack_fffffcfc,in_stack_fffffd00,in_stack_fffffd04,fVar16,
                                 (float)pfVar6,fVar17,iVar4,pfVar1,(int *)pfVar13);
              if ((iVar4 != 0) && (local_2a0 < local_2c4)) {
                local_2b8 = *(float *)((int)local_278 + local_2c0);
                local_2b0 = *(int *)((int)local_278 + local_2c0 + 8);
                local_2b4 = *(int *)((int)local_278 + local_2c0 + 4);
                local_2c4 = local_2a0;
                local_2a8 = local_244;
                local_2ac = local_248;
                local_2a4 = local_240;
                pfVar1 = local_224;
                pfVar6 = local_29c;
                for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
                  *pfVar6 = *pfVar1;
                  pfVar1 = pfVar1 + 1;
                  pfVar6 = pfVar6 + 1;
                }
              }
              local_2c0 = local_2c0 + 0xc;
            } while (local_2c0 < 0x30);
            if (local_2c4 < _DAT_004bd25c) {
              *param_4 = 1;
              param_4[1] = param_2;
              piVar5 = (int *)build_world_object_class_damage_transform(local_7c,param_2);
              piVar12 = param_4 + 2;
              for (iVar7 = 0xf; iVar7 != 0; iVar7 = iVar7 + -1) {
                *piVar12 = *piVar5;
                piVar5 = piVar5 + 1;
                piVar12 = piVar12 + 1;
              }
              param_4[0x11] = (int)local_2c4;
              param_4[0x12] = (int)local_2b8;
              param_4[0x13] = local_2b4;
              param_4[0x14] = local_2b0;
              param_4[0x15] = (int)-local_29c[3];
              param_4[0x16] = (int)-local_28c;
              param_4[0x17] = (int)-local_288;
              param_4[0x18] = (int)local_2ac;
              param_4[0x19] = (int)local_2a8;
              param_4[0x1a] = (int)local_2a4;
              *param_5 = 1;
              param_5[1] = param_1[7];
              piVar5 = (int *)build_world_object_class_damage_transform(local_fc,param_1[7]);
              pfVar1 = (float *)(param_5 + 0x12);
              piVar12 = param_5 + 2;
              for (iVar7 = 0xf; iVar7 != 0; iVar7 = iVar7 + -1) {
                *piVar12 = *piVar5;
                piVar5 = piVar5 + 1;
                piVar12 = piVar12 + 1;
              }
              param_5[0x11] = (int)local_2c4;
              *pfVar1 = local_2c4 * local_29c[3] + local_29c[0];
              param_5[0x13] = (int)(local_2c4 * local_28c + local_29c[1]);
              param_5[0x14] = (int)(local_2c4 * local_288 + local_29c[2]);
              pfVar6 = (float *)compose_matrix_or_transform_b(local_208,local_40);
              pfVar13 = local_bc;
              for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                *pfVar13 = *pfVar6;
                pfVar6 = pfVar6 + 1;
                pfVar13 = pfVar13 + 1;
              }
              transform_vec3_array_by_matrix(pfVar1,pfVar1,1,local_bc);
              param_5[0x15] = (int)local_29c[3];
              param_5[0x16] = (int)local_28c;
              param_5[0x17] = (int)local_288;
              param_5[0x18] = (int)-local_2ac;
              param_5[0x19] = (int)-local_2a8;
              param_5[0x1a] = (int)-local_2a4;
              return 1;
            }
          }
          else if (uVar2 == 0x2000) {
            pfVar1 = local_23c;
            pfVar6 = local_1a4;
            for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
              *pfVar6 = *pfVar1;
              pfVar1 = pfVar1 + 1;
              pfVar6 = pfVar6 + 1;
            }
            local_18c = *(undefined4 *)(param_2 + 0x90);
            local_188 = param_2;
            puVar3 = (undefined4 *)(param_2 + 0x94);
            puVar10 = local_184;
            for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
              *puVar10 = *puVar3;
              puVar3 = puVar3 + 1;
              puVar10 = puVar10 + 1;
            }
            pfVar1 = local_208;
            pfVar6 = local_16c;
            for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
              *pfVar6 = *pfVar1;
              pfVar1 = pfVar1 + 1;
              pfVar6 = pfVar6 + 1;
            }
            iVar7 = test_collision_between_effect_target_bounds
                              ((int)param_1,(int)local_1a4,param_4,param_5);
            if (iVar7 != 0) {
              return 1;
            }
            iVar7 = test_collision_between_effect_target_bounds
                              ((int)local_1a4,(int)param_1,param_4,param_5);
            goto joined_r0x0043fd07;
          }
        }
        else {
          if (uVar2 == 0x4000) {
            in_stack_fffffd04 = 6.243809e-39;
            iVar7 = test_vehicle_damage_volume_against_effect_target
                              ((int)param_1,param_2,1.0,local_208,param_4,param_5);
          }
          else {
            if (uVar2 != 0x5000) goto LAB_0043fd3e;
            in_stack_fffffd04 = 6.24374e-39;
            iVar7 = test_vehicle_damage_volume_against_effect_target
                              ((int)param_1,param_2,0.75,local_208,param_4,param_5);
          }
joined_r0x0043fd07:
          if (iVar7 != 0) {
            return 1;
          }
        }
      }
    }
LAB_0043fd3e:
    if ((*(int *)(param_2 + 100) != 0) &&
       (iVar7 = test_effect_target_swept_collision_against_object
                          (param_1,*(int *)(param_2 + 100),local_208,param_4,param_5), iVar7 != 0))
    {
      return 1;
    }
    param_2 = *(int *)(param_2 + 0x60);
  } while( true );
}


