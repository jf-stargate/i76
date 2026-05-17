/*
 * Program: i76.exe
 * Function: compute_geo_vertex_lighting_from_normals
 * Entry: 00478430
 * Signature: undefined __cdecl compute_geo_vertex_lighting_from_normals(float * param_1, float * param_2, int param_3, float * param_4, float * param_5, float param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO lighting/render renames v33; confidence=high] Consumes runtime_geometry +0x10
   normal/secondary vector table and transformed positions to produce one lighting/shade scalar per
   normal index. Handles ambient/directional and dynamic light contributions. */

void __cdecl
compute_geo_vertex_lighting_from_normals
          (float *param_1,float *param_2,int param_3,float *param_4,float *param_5,float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  int *piVar10;
  float *pfVar11;
  float10 fVar12;
  float10 fVar13;
  float local_80 [2];
  float local_78 [10];
  float local_50;
  float local_4c;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  double local_2c;
  double local_24;
  int local_1c;
  float local_18;
  float local_14;
  float local_10;
  float *local_c;
  float *local_8;
  
  iVar7 = DAT_0058db00 * 0x14;
  local_18 = *(float *)(&DAT_004fa0c0 + iVar7);
  local_44 = *param_4 * DAT_006435f0 + DAT_006435f4 * param_4[1] + DAT_006435f8 * param_4[2];
  local_8 = DAT_0058db0c;
  local_40 = DAT_006435f4 * param_4[4] + DAT_006435f8 * param_4[5] + DAT_006435f0 * param_4[3];
  local_3c = DAT_006435f8 * param_4[8] + DAT_006435f0 * param_4[6] + DAT_006435f4 * param_4[7];
  fVar1 = *(float *)(&DAT_004fa0bc + iVar7);
  local_14 = -fVar1;
  if (*(int *)(&DAT_004fa0b0 + iVar7) == 1) {
    if (0 < (int)param_6) {
      pfVar9 = (float *)(param_3 + 8);
      do {
        fVar2 = (pfVar9[-2] * local_44 + pfVar9[-1] * local_40 + local_3c * *pfVar9) * -fVar1;
        if (fVar2 < _DAT_004be610) {
          fVar2 = _DAT_004be610;
        }
        fVar3 = *(float *)((int)pfVar9 + ((int)param_2 - param_3)) * _DAT_00643600 + _DAT_006435fc;
        if (fVar3 < _DAT_004be67c) {
          fVar3 = _DAT_004be67c;
        }
        if (_DAT_004be638 < fVar3) {
          fVar3 = _DAT_004be638;
        }
        fVar2 = fVar3 * fVar2 + local_18;
        if (_DAT_004be638 <= fVar2) {
          fVar2 = _DAT_004be638;
        }
        *param_1 = fVar2;
        pfVar9 = pfVar9 + 3;
        param_1 = param_1 + 1;
        param_6 = (float)((int)param_6 + -1);
      } while (param_6 != 0.0);
    }
  }
  else {
    if (0 < (int)DAT_0058db0c) {
      piVar10 = &DAT_0058db10;
      pfVar9 = local_80;
      pfVar11 = DAT_0058db0c;
      do {
        iVar7 = *piVar10;
        piVar10 = piVar10 + 1;
        pfVar8 = (float *)(iVar7 + 0x30);
        local_38 = *(float *)(iVar7 + 0x38) * param_4[2] +
                   *(float *)(iVar7 + 0x34) * param_4[1] + *pfVar8 * *param_4;
        local_34 = *(float *)(iVar7 + 0x38) * param_4[5] +
                   *(float *)(iVar7 + 0x34) * param_4[4] + *pfVar8 * param_4[3];
        fVar1 = *pfVar8;
        fVar2 = param_4[6];
        fVar3 = *(float *)(iVar7 + 0x38);
        fVar4 = param_4[8];
        fVar5 = *(float *)(iVar7 + 0x34);
        fVar6 = param_4[7];
        pfVar11 = (float *)((int)pfVar11 + -1);
        *pfVar9 = local_38;
        local_30 = fVar5 * fVar6 + fVar3 * fVar4 + fVar1 * fVar2;
        pfVar9[1] = local_34;
        pfVar9[2] = local_30;
        pfVar9 = pfVar9 + 3;
      } while (pfVar11 != (float *)0x0);
    }
    if (0 < (int)param_6) {
      local_c = param_1;
      local_1c = (int)param_2 - param_3;
      local_10 = param_6;
      pfVar9 = (float *)(param_3 + 8);
      do {
        param_6 = (local_3c * *pfVar9 + local_44 * pfVar9[-2] + local_40 * pfVar9[-1]) * local_14;
        if (param_6 < _DAT_004be610) {
          param_6 = 0.0;
        }
        if (0 < (int)local_8) {
          piVar10 = &DAT_0058db10;
          pfVar11 = local_78;
          param_4 = local_8;
          do {
            iVar7 = *piVar10;
            local_38 = *param_2 - *(float *)(iVar7 + 0x48);
            local_34 = *(float *)(local_1c + -4 + (int)pfVar9) - *(float *)(iVar7 + 0x4c);
            fVar1 = *(float *)(local_1c + (int)pfVar9) - *(float *)(iVar7 + 0x50);
            fVar2 = fVar1 * fVar1 + local_34 * local_34 + local_38 * local_38;
            fVar3 = _DAT_004be638 / (*(float *)(iVar7 + 0xc) * fVar2 - _DAT_004be670);
            if ((*(byte *)(iVar7 + 4) & 1) == 0) {
              fVar2 = _DAT_004be638 / (SQRT(fVar2) - _DAT_004be674);
              local_38 = local_38 * fVar2;
              local_34 = local_34 * fVar2;
              fVar1 = fVar1 * fVar2;
              local_50 = param_5[2] * fVar1 + param_5[1] * local_34 + local_38 * *param_5;
              local_4c = param_5[3] * local_38 + param_5[5] * fVar1 + param_5[4] * local_34;
              fVar1 = ((param_5[7] * local_34 + param_5[6] * local_38 + fVar1 * param_5[8]) *
                       *pfVar9 + local_4c * pfVar9[-1] + local_50 * pfVar9[-2]) * fVar3 *
                      _DAT_004be67c;
              if (fVar1 < _DAT_004be610) {
                fVar1 = _DAT_004be610;
              }
            }
            else {
              fVar4 = -(pfVar11[-2] * pfVar9[-2] + pfVar11[-1] * pfVar9[-1] + *pfVar9 * *pfVar11);
              if (fVar4 <= _DAT_004be610) {
                fVar1 = fVar3 * 0.0 * _DAT_004be678;
              }
              else {
                fVar2 = _DAT_004be638 / (SQRT(fVar2) - _DAT_004be674);
                local_2c = (double)*(float *)(iVar7 + 8);
                fVar1 = (_DAT_004be638 -
                        (local_38 * fVar2 * *(float *)(iVar7 + 0x3c) +
                        local_34 * fVar2 * *(float *)(iVar7 + 0x40) +
                        fVar1 * fVar2 * *(float *)(iVar7 + 0x44))) * _DAT_004be660;
                local_24 = (double)fVar1;
                if ((float)_DAT_004be668 < fVar1) {
                  fVar13 = (float10)*(float *)(iVar7 + 8) * (float10)fVar1;
                  local_24._0_4_ = SUB84((double)(fVar13 + (float10)_DAT_004faf18),0);
                  fVar12 = (float10)fscale((float10)1,(float10)local_24._0_4_);
                  fVar13 = (float10)f2xm1(fVar13 - (float10)local_24._0_4_);
                  fVar12 = fVar12 * (fVar13 + (float10)1);
                  local_24 = (double)fVar12;
                  fVar1 = (float)fVar12 * fVar3 * fVar4 * _DAT_004be678;
                }
                else {
                  fVar1 = _DAT_004be610 * fVar3 * fVar4 * _DAT_004be678;
                }
              }
            }
            param_6 = fVar1 + param_6;
            piVar10 = piVar10 + 1;
            pfVar11 = pfVar11 + 3;
            param_4 = (float *)((int)param_4 + -1);
          } while (param_4 != (float *)0x0);
        }
        fVar1 = local_18 + param_6;
        if (_DAT_004be638 <= local_18 + param_6) {
          fVar1 = _DAT_004be638;
        }
        param_2 = param_2 + 3;
        pfVar9 = pfVar9 + 3;
        *local_c = fVar1;
        local_c = local_c + 1;
        local_10 = (float)((int)local_10 + -1);
      } while (local_10 != 0.0);
      return;
    }
  }
  return;
}


