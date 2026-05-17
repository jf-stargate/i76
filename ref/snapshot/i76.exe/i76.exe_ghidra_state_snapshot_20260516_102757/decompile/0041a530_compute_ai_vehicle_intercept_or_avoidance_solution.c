/*
 * Program: i76.exe
 * Function: compute_ai_vehicle_intercept_or_avoidance_solution
 * Entry: 0041a530
 * Signature: undefined4 __cdecl compute_ai_vehicle_intercept_or_avoidance_solution(uint param_1, float * param_2, float * param_3, uint * param_4, undefined4 * param_5, float * param_6, int param_7, float * param_8, int param_9)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Computes a vehicle AI intercept/avoidance solution
   using target vectors, runtime delta, transform composition, and projected positions. */

undefined4 __cdecl
compute_ai_vehicle_intercept_or_avoidance_solution
          (uint param_1,float *param_2,float *param_3,uint *param_4,undefined4 *param_5,
          float *param_6,int param_7,float *param_8,int param_9)

{
  float fVar1;
  uint uVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  uint *puVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  float fVar14;
  float *pfVar15;
  float10 fVar16;
  float10 fVar17;
  float local_204;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  int local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  undefined4 local_17c;
  undefined4 local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  undefined4 local_164;
  undefined4 local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  undefined4 local_124;
  undefined4 local_120;
  float local_11c;
  undefined4 local_118;
  undefined4 local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_fc;
  float local_f8 [10];
  double local_d0;
  double local_c0;
  float local_b8 [30];
  float local_40 [16];
  
  iVar12 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  local_1b4 = iVar12;
  fVar16 = get_runtime_update_delta_seconds();
  fVar1 = (float)fVar16;
  puVar10 = (uint *)get_current_effect_target_scan_object();
  if (puVar10 == (uint *)0x0) {
    return 0;
  }
  do {
    uVar2 = *puVar10;
    if (uVar2 != param_1) {
      iVar13 = *(int *)(uVar2 + 0x6c);
      if (param_9 == 0) {
        if ((iVar13 == 1) || (iVar13 == 8)) goto LAB_0041a59c;
      }
      else if (iVar13 == 1) {
LAB_0041a59c:
        iVar13 = *(int *)(*(int *)(uVar2 + 0x70) + 0x108);
        if ((((*(float *)(iVar13 + 0x9d40) <= *(float *)(iVar12 + 0x9d4c)) &&
             (*(float *)(iVar12 + 0x9d40) <= *(float *)(iVar13 + 0x9d4c))) &&
            (*(float *)(iVar13 + 0x9d48) <= *(float *)(iVar12 + 0x9d54))) &&
           ((*(float *)(iVar12 + 0x9d48) <= *(float *)(iVar13 + 0x9d54) &&
            (fVar16 = (float10)world_object_geometry_context_helper_004589f0(uVar2,param_1),
            fVar16 < (float10)_DAT_004bca40)))) {
          local_158 = (float)*(double *)(uVar2 + 0x40);
          local_154 = (float)*(double *)(uVar2 + 0x48);
          local_150 = (float)*(double *)(uVar2 + 0x50);
          get_world_object_damage_or_target_vectors(uVar2,&local_1dc,&local_15c);
          fVar14 = fVar1 * local_1dc + local_158;
          fVar4 = fVar1 * local_1d8 + local_154;
          fVar5 = fVar1 * local_1d4 + local_150;
          if (param_7 == 0) {
            local_1a4 = *param_2;
            local_1a0 = param_2[1];
            local_19c = param_2[2];
            fVar6 = fVar4 - local_1a0;
            fVar9 = fVar5 - local_19c;
            fVar8 = fVar14 - local_1a4;
            fVar7 = fVar8 * *param_3 + fVar9 * param_3[2] + fVar6 * param_3[1];
            if ((fVar7 < _DAT_004bc914) ||
               (local_1d0 = param_3[1],
               fVar7 * fVar7 <
               (fVar9 * fVar9 + fVar6 * fVar6 + fVar8 * fVar8) *
               (*param_3 * *param_3 + param_3[2] * param_3[2] + local_1d0 * local_1d0) *
               _DAT_004bc9d0)) goto LAB_0041ab20;
          }
          local_174 = *param_2;
          local_18c = local_174 - fVar14;
          local_170 = param_2[1];
          local_16c = param_2[2];
          local_188 = local_170 - fVar4;
          local_184 = local_16c - fVar5;
          local_1cc = *param_3;
          local_1b0 = local_1dc - local_1cc;
          local_1c8 = param_3[1];
          local_1ac = local_1d8 - local_1c8;
          local_1c4 = param_3[2];
          local_1a8 = local_1d4 - local_1c4;
          local_198 = local_1b0;
          local_194 = local_1ac;
          local_190 = local_1a8;
          local_110 = local_18c;
          local_10c = local_188;
          local_108 = local_184;
          fVar16 = dot_product_vec3(&local_198,&local_198);
          if ((float10)_DAT_004bc924 <= ABS(fVar16)) {
            fVar17 = dot_product_vec3(&local_198,&local_110);
            local_204 = (float)(fVar17 / (float10)(float)fVar16);
          }
          else {
            local_204 = 1e+07;
          }
          bVar3 = _DAT_004bc914 <= local_204;
          *param_8 = local_204;
          if (bVar3) {
            if (_DAT_004bc988 < local_204) {
              local_204 = 3.0;
            }
          }
          else {
            local_204 = 0.0;
          }
          local_17c = *(undefined4 *)(uVar2 + 0x34);
          local_178 = *(undefined4 *)(uVar2 + 0x38);
          local_1c0 = local_204 * local_1dc + fVar14;
          local_1bc = local_204 * local_1d8 + fVar4;
          local_180 = *(float *)(uVar2 + 0x30);
          local_1b8 = local_204 * local_1d4 + fVar5;
          local_168 = *(float *)(uVar2 + 0x18);
          local_164 = *(undefined4 *)(uVar2 + 0x1c);
          local_160 = *(undefined4 *)(uVar2 + 0x20);
          fVar14 = 0.0;
          pfVar11 = local_b8;
          local_134 = local_1c0;
          local_130 = local_1bc;
          local_12c = local_1b8;
          local_128 = local_168;
          local_124 = local_164;
          local_120 = local_160;
          local_11c = local_180;
          local_118 = local_17c;
          local_114 = local_178;
          do {
            decode_ai_maneuver_direction_code_to_vector
                      (fVar14,&local_134,&local_128,&local_11c,pfVar11);
            fVar14 = (float)((int)fVar14 + 1);
            pfVar11 = pfVar11 + 3;
          } while ((int)fVar14 < 10);
          local_14c = *param_3;
          local_148 = param_3[1];
          local_144 = param_3[2];
          local_140 = *param_2;
          local_13c = param_2[1];
          local_138 = param_2[2];
          local_fc = local_144 * local_204 + local_138;
          pfVar11 = (float *)(param_1 + 0x18);
          pfVar15 = local_f8;
          for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
            *pfVar15 = *pfVar11;
            pfVar11 = pfVar11 + 1;
            pfVar15 = pfVar15 + 1;
          }
          local_d0 = (double)(local_14c * local_204 + local_140);
          local_c0 = (double)local_fc;
          pfVar11 = (float *)compose_matrix_or_transform_b(local_f8,local_40);
          pfVar15 = local_f8;
          for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
            *pfVar15 = *pfVar11;
            pfVar11 = pfVar11 + 1;
            pfVar15 = pfVar15 + 1;
          }
          transform_vec3_array_by_matrix(local_b8,local_b8,10,local_f8);
          iVar13 = 0;
          pfVar11 = local_b8;
          do {
            if ((ABS(pfVar11[2]) < (float)_DAT_004bca48) && (ABS(*pfVar11) < (float)_DAT_004bca50))
            {
              bVar3 = _DAT_004bca58 <= local_15c;
              *param_5 = 0x3f800000;
              if (bVar3) {
                *param_6 = 0.3;
                *param_4 = uVar2;
                return 1;
              }
              if (local_204 <= _DAT_004bca1c) {
                *param_6 = local_204;
                *param_4 = uVar2;
                return 1;
              }
              *param_6 = _DAT_004bca1c;
              *param_4 = uVar2;
              return 1;
            }
            iVar13 = iVar13 + 1;
            pfVar11 = pfVar11 + 3;
            iVar12 = local_1b4;
          } while (iVar13 < 10);
        }
      }
    }
LAB_0041ab20:
    puVar10 = (uint *)effect_target_scan_query_context_helper_00436790();
    if (puVar10 == (uint *)0x0) {
      return 0;
    }
  } while( true );
}


