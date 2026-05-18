/*
 * Program: i76.exe
 * Function: compute_ai_vehicle_relative_target_vector_state
 * Entry: 0041abf0
 * Signature: undefined4 __cdecl compute_ai_vehicle_relative_target_vector_state(int param_1, undefined4 * param_2, float * param_3, float * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Computes relative target vectors and intermediate
   pursuit/avoidance state using vec3 subtract/add-scaled helpers. */

undefined4 __cdecl
compute_ai_vehicle_relative_target_vector_state
          (int param_1,undefined4 *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  bool bVar7;
  undefined4 *puVar8;
  int *piVar9;
  float *pfVar10;
  int iVar11;
  int *piVar12;
  float10 fVar13;
  float10 fVar14;
  float local_108;
  float local_104;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  int local_dc;
  float local_d8;
  int *local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
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
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  int local_70 [7];
  float local_54 [3];
  float local_48 [3];
  float local_3c [3];
  float local_30 [3];
  float local_24 [3];
  float local_18 [3];
  float local_c [3];
  
  local_70[0] = 0xc;
  local_70[1] = 0xe;
  local_70[2] = 0xf;
  local_70[3] = 0x10;
  local_70[4] = 0x11;
  local_70[5] = 0x13;
  puVar8 = ordnance_runtime_flag_context_helper_004a0f50();
  fVar4 = (float)*(double *)(param_1 + 0x40);
  fVar5 = (float)*(double *)(param_1 + 0x48);
  fVar6 = (float)*(double *)(param_1 + 0x50);
  get_world_object_damage_or_target_vectors(param_1,&local_f4,local_70 + 6);
  piVar12 = puVar8 + 3;
  local_dc = 0;
  do {
    bVar7 = false;
    piVar9 = local_70;
    iVar11 = 6;
    do {
      if (piVar12[-3] == *piVar9) {
        bVar7 = true;
      }
      piVar9 = piVar9 + 1;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    if (bVar7) {
      local_d4 = piVar12;
      if (*piVar12 != 0) {
        fVar1 = local_94;
        fVar2 = local_8c;
        for (iVar11 = *(int *)(*piVar12 + 100); local_94 = fVar1, local_8c = fVar2, iVar11 != 0;
            iVar11 = *(int *)(iVar11 + 0x60)) {
          local_d0 = (float)*(double *)(iVar11 + 0x40);
          local_94 = fVar4 - local_d0;
          local_cc = (float)*(double *)(iVar11 + 0x48);
          local_c8 = (float)*(double *)(iVar11 + 0x50);
          if ((ABS(local_94) <= (float)_DAT_004bca60) &&
             (local_8c = fVar6 - local_c8, ABS(local_8c) <= (float)_DAT_004bca60)) {
            local_90 = fVar5 - local_cc;
            local_c4 = DAT_00524558 - local_f4;
            local_c0 = DAT_0052455c - local_f0;
            local_bc = DAT_00524560 - local_ec;
            local_a0 = local_c4;
            local_9c = local_c0;
            local_98 = local_bc;
            local_88 = local_94;
            local_84 = local_90;
            local_80 = local_8c;
            fVar13 = dot_product_vec3(&local_a0,&local_a0);
            if ((float10)_DAT_004bc924 <= ABS(fVar13)) {
              fVar14 = dot_product_vec3(&local_a0,&local_88);
              local_108 = (float)(fVar14 / (float10)(float)fVar13);
            }
            else {
              local_108 = 1e+07;
            }
            fVar3 = (float)_DAT_004bc9e0;
            *param_4 = local_108;
            fVar1 = local_94;
            fVar2 = local_8c;
            if ((fVar3 <= local_108) && (local_108 <= _DAT_004bc988)) {
              local_b8 = local_108 * local_f4 + fVar4;
              local_b4 = local_108 * local_f0 + fVar5;
              local_b0 = local_108 * local_ec + fVar6;
              pfVar10 = (float *)vec3_madd_xyz(local_54,local_d0,local_cc,local_c8,local_108,
                                               DAT_00524558,DAT_0052455c,DAT_00524560);
              pfVar10 = (float *)vec3_subtract_xyz(local_c,local_b8,local_b4,local_b0,*pfVar10,
                                                   pfVar10[1],pfVar10[2]);
              fVar13 = vec3_length(*pfVar10,pfVar10[1],pfVar10[2]);
              fVar1 = local_94;
              fVar2 = local_8c;
              if (fVar13 < (float10)_DAT_004bca58) {
                *param_3 = local_108 - _DAT_004bca68;
                *param_2 = 0x3f800000;
                return 1;
              }
            }
          }
          local_8c = fVar2;
          local_94 = fVar1;
          fVar1 = local_94;
          fVar2 = local_8c;
        }
      }
      for (iVar11 = piVar12[1]; iVar11 != 0; iVar11 = *(int *)(iVar11 + 0x60)) {
        local_e8 = (float)*(double *)(iVar11 + 0x40);
        local_e4 = (float)*(double *)(iVar11 + 0x48);
        local_e0 = (float)*(double *)(iVar11 + 0x50);
        if ((ABS(fVar4 - local_e8) <= (float)_DAT_004bca60) &&
           (ABS(fVar6 - local_e0) <= (float)_DAT_004bca60)) {
          pfVar10 = (float *)vec3_subtract_xyz(local_18,fVar4,fVar5,fVar6,local_e8,local_e4,local_e0
                                              );
          local_7c = *pfVar10;
          local_78 = pfVar10[1];
          local_74 = pfVar10[2];
          pfVar10 = (float *)vec3_subtract_xyz(local_30,DAT_00524558,DAT_0052455c,DAT_00524560,
                                               local_f4,local_f0,local_ec);
          local_ac = *pfVar10;
          local_a8 = pfVar10[1];
          local_a4 = pfVar10[2];
          fVar13 = dot_product_vec3(&local_ac,&local_ac);
          local_d8 = (float)fVar13;
          if ((float10)_DAT_004bc924 <= ABS(fVar13)) {
            fVar13 = dot_product_vec3(&local_ac,&local_7c);
            local_104 = (float)(fVar13 / (float10)local_d8);
          }
          else {
            local_104 = 1e+07;
          }
          fVar1 = (float)_DAT_004bc9e0;
          *param_4 = local_104;
          piVar12 = local_d4;
          if ((fVar1 <= local_104) && (local_104 <= _DAT_004bc988)) {
            pfVar10 = (float *)vec3_madd_xyz(local_48,fVar4,fVar5,fVar6,local_104,local_f4,local_f0,
                                             local_ec);
            fVar1 = *pfVar10;
            fVar2 = pfVar10[1];
            fVar3 = pfVar10[2];
            pfVar10 = (float *)vec3_madd_xyz(local_3c,local_e8,local_e4,local_e0,local_104,
                                             DAT_00524558,DAT_0052455c,DAT_00524560);
            pfVar10 = (float *)vec3_subtract_xyz(local_24,fVar1,fVar2,fVar3,*pfVar10,pfVar10[1],
                                                 pfVar10[2]);
            fVar13 = vec3_length(*pfVar10,pfVar10[1],pfVar10[2]);
            piVar12 = local_d4;
            if (fVar13 < (float10)_DAT_004bca58) {
              *param_3 = local_104 - _DAT_004bca68;
              *param_2 = 0x3f800000;
              return 1;
            }
          }
        }
      }
    }
    piVar12 = piVar12 + 0x34;
    local_dc = local_dc + 1;
  } while (local_dc < 0x14);
  return 0;
}


