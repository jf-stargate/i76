/*
 * Program: i76.exe
 * Function: log_cache_memory_status
 * Entry: 004260d0
 * Signature: float * __cdecl log_cache_memory_status(float * param_1, float * param_2, float * param_3, uint * param_4, float * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_004260d0
   suggested_name: log_cache_memory_status
   basis: Diagnostic/cache status logging candidate; related to cache/video free messages. */

float * __cdecl
log_cache_memory_status(float *param_1,float *param_2,float *param_3,uint *param_4,float *param_5)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float *in_EAX;
  float fVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  float *pfVar13;
  float *pfVar14;
  ushort in_FPUControlWord;
  float local_338;
  float *local_334;
  float local_330;
  undefined4 local_324;
  float local_320;
  float *local_31c;
  float local_318;
  undefined4 local_30c;
  float local_308;
  float *local_304;
  float local_300;
  undefined4 local_2f4;
  float local_2f0;
  float *local_2ec;
  float local_2e8;
  undefined4 local_2dc;
  float local_2d8 [168];
  double local_38;
  double local_30;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined8 local_18;
  float local_10;
  undefined8 local_c;
  
  pfVar13 = (float *)((uint)param_5 & 0x1ff);
  if (param_3 == (float *)0x1) {
    return in_EAX;
  }
  if (param_3 != (float *)0x2) {
    if (((uint)param_5 & 4) != 0) {
      if (((int)(param_4[1] << 3) >> 3 | *param_4) == 1) {
        pfVar13 = (float *)((uint)param_5 & 0x1fb);
        param_4 = (uint *)(uint)(byte)param_4[2];
      }
      if (((*param_4 & *param_4 - 1) != 0) ||
         (uVar7 = (int)(param_4[1] << 3) >> 3, (uVar7 & uVar7 - 1) != 0)) {
        write_texture_buffer_to_pcx_file(s_BAD_pcx_004edd48,(int *)param_4,&DAT_005dcfa8);
        report_error();
      }
    }
    param_5 = pfVar13;
    iVar9 = (*(code *)(&g_geo_raster_clip_prepare_table)[(int)param_5])
                      (param_1,&local_338,param_2,param_3,param_5);
    if (iVar9 == 0) {
      return (float *)0x0;
    }
    if ((char)((uint)param_5 >> 8) != '\0') {
      param_5 = (float *)((uint)param_5 & 0xff);
      iVar8 = 0;
      if (0 < iVar9) {
        pfVar13 = &local_338;
        do {
          local_28 = (float)*(int *)param_1[0xf] - *pfVar13;
          local_24 = (float)((((int *)param_1[0xf])[1] << 3) >> 3) - pfVar13[1];
          if ((int)((uint)local_24 | (uint)local_28 | (uint)pfVar13[1] | (uint)*pfVar13) < 0) {
            iVar9 = (*(code *)(&g_geo_raster_clip_prepare_table)[(int)param_5])
                              (param_1,&local_338,param_2,iVar9,param_5);
            if (iVar9 == 0) {
              return (float *)0x0;
            }
            break;
          }
          iVar8 = iVar8 + 1;
          pfVar13 = pfVar13 + 6;
        } while (iVar8 < iVar9);
      }
    }
    param_1._0_2_ = in_FPUControlWord & 0xf3ff;
    (*(code *)(&PTR_submit_d3d_lit_indexed_primitive_batch_a_004ed930)[(uint)param_5 & 0xff])
              (&local_338,iVar9,param_4);
    param_2 = (float *)CONCAT22(param_2._2_2_,(ushort)param_1);
    return param_2;
  }
  local_10 = *param_2;
  local_c._0_4_ = param_2[1];
  local_1c = param_2[6];
  local_c._4_4_ = param_2[2];
  fVar6 = param_2[7];
  local_18._4_4_ = param_2[8];
  uVar7 = ((uint)(local_18._4_4_ - param_1[0x42]) >> 1 |
          (uint)(local_c._4_4_ - param_1[0x42]) & 0xbfffffff) >> 0x1e;
  if (uVar7 == 3) {
    return param_1;
  }
  if (uVar7 != 0) {
    fVar1 = (param_1[0x42] - local_c._4_4_) / (local_18._4_4_ - local_c._4_4_);
    if (((uint)(local_c._4_4_ - param_1[0x42]) & 0x80000000) == 0) {
      local_18._4_4_ = param_1[0x42];
      local_1c = (local_1c - local_10) * fVar1 + local_10;
      fVar6 = (fVar6 - (float)local_c) * fVar1 + (float)local_c;
    }
    else {
      local_c._4_4_ = param_1[0x42];
      local_10 = (local_1c - local_10) * fVar1 + local_10;
      local_c._0_4_ = (fVar6 - (float)local_c) * fVar1 + (float)local_c;
    }
  }
  local_20 = param_1[0x4e] - local_c._4_4_;
  uVar7 = ((uint)(param_1[0x4e] - local_18._4_4_) >> 1 | (uint)local_20 & 0xbfffffff) >> 0x1e;
  if (uVar7 == 3) {
    return param_1;
  }
  if (uVar7 != 0) {
    fVar1 = local_20 / (local_18._4_4_ - local_c._4_4_);
    if (((uint)local_20 & 0x80000000) == 0) {
      local_18._4_4_ = param_1[0x4e];
      local_1c = (local_1c - local_10) * fVar1 + local_10;
      fVar6 = (fVar6 - (float)local_c) * fVar1 + (float)local_c;
    }
    else {
      local_c._4_4_ = param_1[0x4e];
      local_10 = (local_1c - local_10) * fVar1 + local_10;
      local_c._0_4_ = (fVar6 - (float)local_c) * fVar1 + (float)local_c;
    }
  }
  local_30 = (double)(local_10 * (_DAT_004bcd0c / local_c._4_4_) * param_1[2] + *param_1 +
                     (float)_DAT_004faf18);
  dVar3 = local_30;
  local_38 = (double)((float)local_c * (_DAT_004bcd0c / local_c._4_4_) * param_1[3] + param_1[1] +
                     (float)_DAT_004faf18);
  dVar2 = local_38;
  fVar1 = _DAT_004bcd0c / local_18._4_4_;
  local_18 = (double)(local_1c * fVar1 * param_1[2] + *param_1 + (float)_DAT_004faf18);
  dVar4 = local_18;
  pfVar13 = (float *)param_1[0xf];
  local_c = (double)(fVar6 * fVar1 * param_1[3] + param_1[1] + (float)_DAT_004faf18);
  dVar5 = local_c;
  if (pfVar13[0xb] == 0.0) {
    return pfVar13;
  }
  uVar7 = (local_30._0_4_ + -1) - (int)pfVar13[9];
  uVar10 = (local_38._0_4_ + -1) - (int)pfVar13[10];
  param_5 = (float *)((((uint)CARRY4(local_30._0_4_ - (int)pfVar13[7],
                                     local_30._0_4_ - (int)pfVar13[7]) * 2 +
                       (uint)CARRY4(uVar7,uVar7)) * 2 +
                      (uint)CARRY4(local_38._0_4_ - (int)pfVar13[8],local_38._0_4_ - (int)pfVar13[8]
                                  )) * 2 + (uint)CARRY4(uVar10,uVar10) ^ 5);
  fVar6 = param_1[0xf];
  uVar7 = (int)local_18 - *(int *)((int)fVar6 + 0x1c);
  uVar11 = ((int)local_18 + -1) - *(int *)((int)fVar6 + 0x24);
  uVar10 = (int)(float)local_c - *(int *)((int)fVar6 + 0x20);
  uVar12 = ((int)(float)local_c + -1) - *(int *)((int)fVar6 + 0x28);
  param_3 = (float *)((((uint)CARRY4(uVar7,uVar7) * 2 + (uint)CARRY4(uVar11,uVar11)) * 2 +
                      (uint)CARRY4(uVar10,uVar10)) * 2 + (uint)CARRY4(uVar12,uVar12) ^ 5);
  local_38 = dVar2;
  local_30 = dVar3;
  local_18 = dVar4;
  local_c = dVar5;
  if (param_3 != (float *)0x0 || param_5 != (float *)0x0) {
    do {
      if (((uint)param_5 & (uint)param_3) != 0) {
        return param_3;
      }
      pfVar13 = param_5;
      if (param_5 == (float *)0x0) {
        pfVar13 = param_3;
      }
      if (((uint)pfVar13 & 8) == 0) {
        if (((uint)pfVar13 & 4) == 0) {
          if (((uint)pfVar13 & 2) == 0) {
            local_24 = (float)((int)(float)local_c - local_38._0_4_);
            local_28 = (float)(*(int *)((int)param_1[0xf] + 0x28) - local_38._0_4_);
            local_20 = (float)((int)local_18 - local_30._0_4_);
            iVar8 = local_30._0_4_ +
                    (int)(((longlong)((int)local_18 - local_30._0_4_) * (longlong)(int)local_28) /
                         (longlong)((int)(float)local_c - local_38._0_4_));
            fVar6 = param_1[0xf];
            iVar9 = *(int *)((int)fVar6 + 0x28);
          }
          else {
            local_24 = (float)((int)(float)local_c - local_38._0_4_);
            local_28 = (float)(*(int *)((int)param_1[0xf] + 0x20) - local_38._0_4_);
            local_20 = (float)((int)local_18 - local_30._0_4_);
            iVar8 = local_30._0_4_ +
                    (int)(((longlong)((int)local_18 - local_30._0_4_) * (longlong)(int)local_28) /
                         (longlong)((int)(float)local_c - local_38._0_4_));
            fVar6 = param_1[0xf];
            iVar9 = *(int *)((int)fVar6 + 0x20);
          }
        }
        else {
          local_24 = (float)((int)local_18 - local_30._0_4_);
          local_28 = (float)(*(int *)((int)param_1[0xf] + 0x24) - local_30._0_4_);
          local_20 = (float)((int)(float)local_c - local_38._0_4_);
          iVar9 = (int)(((longlong)((int)(float)local_c - local_38._0_4_) * (longlong)(int)local_28)
                       / (longlong)((int)local_18 - local_30._0_4_)) + local_38._0_4_;
          fVar6 = param_1[0xf];
          iVar8 = *(int *)((int)fVar6 + 0x24);
        }
      }
      else {
        local_20 = (float)((int)local_18 - local_30._0_4_);
        local_28 = (float)(*(int *)((int)param_1[0xf] + 0x1c) - local_30._0_4_);
        local_24 = (float)((int)(float)local_c - local_38._0_4_);
        iVar9 = (int)(((longlong)((int)(float)local_c - local_38._0_4_) * (longlong)(int)local_28) /
                     (longlong)((int)local_18 - local_30._0_4_)) + local_38._0_4_;
        fVar6 = param_1[0xf];
        iVar8 = *(int *)((int)fVar6 + 0x1c);
      }
      if (pfVar13 == param_5) {
        local_30 = (double)CONCAT44(local_30._4_4_,iVar8);
        local_38 = (double)CONCAT44(local_38._4_4_,iVar9);
        uVar7 = iVar8 - *(int *)((int)fVar6 + 0x1c);
        uVar11 = (iVar8 + -1) - *(int *)((int)fVar6 + 0x24);
        uVar10 = iVar9 - *(int *)((int)fVar6 + 0x20);
        uVar12 = (iVar9 + -1) - *(int *)((int)fVar6 + 0x28);
        param_5 = (float *)((((uint)CARRY4(uVar7,uVar7) * 2 + (uint)CARRY4(uVar11,uVar11)) * 2 +
                            (uint)CARRY4(uVar10,uVar10)) * 2 + (uint)CARRY4(uVar12,uVar12) ^ 5);
      }
      else {
        local_18 = (double)CONCAT44(local_18._4_4_,iVar8);
        local_c = (double)CONCAT44(local_c._4_4_,iVar9);
        uVar7 = iVar8 - *(int *)((int)fVar6 + 0x1c);
        uVar11 = (iVar8 + -1) - *(int *)((int)fVar6 + 0x24);
        uVar10 = iVar9 - *(int *)((int)fVar6 + 0x20);
        uVar12 = (iVar9 + -1) - *(int *)((int)fVar6 + 0x28);
        param_3 = (float *)((((uint)CARRY4(uVar7,uVar7) * 2 + (uint)CARRY4(uVar11,uVar11)) * 2 +
                            (uint)CARRY4(uVar10,uVar10)) * 2 + (uint)CARRY4(uVar12,uVar12) ^ 5);
      }
    } while (param_3 != (float *)0x0 || param_5 != (float *)0x0);
  }
  uVar7 = (int)local_18 - local_30._0_4_ >> 0x1f;
  if ((float10)(int)(((int)local_18 - local_30._0_4_ ^ uVar7) - uVar7) <=
      ABS((float10)((int)(float)local_c - local_38._0_4_))) {
    local_338 = (float)local_30._0_4_;
    local_334 = (float *)(float)local_38._0_4_;
    local_330 = param_2[2];
    if (local_38._0_4_ < (int)(float)local_c) {
      local_318 = param_2[8];
      local_320 = (float)(int)local_18;
      local_300 = param_2[8];
      local_2e8 = param_2[2];
      local_31c = (float *)(float)(int)(float)local_c;
      local_308 = (float)(int)local_18 - _DAT_004bcd10;
      local_304 = (float *)(float)(int)(float)local_c;
      local_2f0 = (float)local_30._0_4_ - _DAT_004bcd10;
      local_2ec = local_334;
      goto LAB_004266a7;
    }
    local_318 = param_2[2];
    local_320 = (float)local_30._0_4_ - _DAT_004bcd10;
    local_31c = local_334;
    local_308 = (float)(int)local_18 - _DAT_004bcd10;
    local_304 = (float *)(float)(int)(float)local_c;
  }
  else {
    local_338 = (float)local_30._0_4_;
    local_334 = (float *)(float)local_38._0_4_;
    local_330 = param_2[2];
    if ((int)local_18 <= local_30._0_4_) {
      local_318 = param_2[8];
      local_320 = (float)(int)local_18;
      local_300 = param_2[8];
      local_2e8 = param_2[2];
      local_31c = (float *)(float)(int)(float)local_c;
      local_308 = (float)(int)local_18;
      local_304 = (float *)((float)(int)(float)local_c - _DAT_004bcd10);
      local_2f0 = local_338;
      local_2ec = (float *)((float)local_334 - _DAT_004bcd10);
      goto LAB_004266a7;
    }
    local_320 = local_338;
    local_318 = param_2[2];
    local_31c = (float *)((float)local_334 - _DAT_004bcd10);
    local_308 = (float)(int)local_18;
    local_304 = (float *)((float)(int)(float)local_c - _DAT_004bcd10);
  }
  param_1 = (float *)(float)(int)(float)local_c;
  local_300 = param_2[8];
  local_2f0 = (float)(int)local_18;
  local_2ec = param_1;
  local_2e8 = param_2[8];
LAB_004266a7:
  pfVar13 = &local_338;
  pfVar14 = local_2d8;
  for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar14 = *pfVar13;
    pfVar13 = pfVar13 + 1;
    pfVar14 = pfVar14 + 1;
  }
  pfVar13 = &local_2f0;
  pfVar14 = &local_338;
  for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar14 = *pfVar13;
    pfVar13 = pfVar13 + 1;
    pfVar14 = pfVar14 + 1;
  }
  pfVar13 = local_2d8;
  pfVar14 = &local_2f0;
  for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar14 = *pfVar13;
    pfVar13 = pfVar13 + 1;
    pfVar14 = pfVar14 + 1;
  }
  pfVar13 = &local_320;
  pfVar14 = local_2d8;
  for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar14 = *pfVar13;
    pfVar13 = pfVar13 + 1;
    pfVar14 = pfVar14 + 1;
  }
  pfVar13 = &local_308;
  pfVar14 = &local_320;
  for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar14 = *pfVar13;
    pfVar13 = pfVar13 + 1;
    pfVar14 = pfVar14 + 1;
  }
  pfVar13 = local_2d8;
  pfVar14 = &local_308;
  for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar14 = *pfVar13;
    pfVar13 = pfVar13 + 1;
    pfVar14 = pfVar14 + 1;
  }
  local_324 = 0x3f800000;
  local_30c = 0x3f800000;
  local_2f4 = 0x3f800000;
  local_2dc = 0x3f800000;
  pfVar13 = (float *)submit_d3d_lit_indexed_primitive_batch_b(&local_338,4,(int)param_4);
  return pfVar13;
}


