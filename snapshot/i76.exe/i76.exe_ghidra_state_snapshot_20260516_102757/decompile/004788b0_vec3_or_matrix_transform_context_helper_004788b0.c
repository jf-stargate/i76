/*
 * Program: i76.exe
 * Function: vec3_or_matrix_transform_context_helper_004788b0
 * Entry: 004788b0
 * Signature: undefined __cdecl vec3_or_matrix_transform_context_helper_004788b0(float * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: vec3 or matrix transform context
   helper based on adjacent named subsystem context. */

void __cdecl vec3_or_matrix_transform_context_helper_004788b0(float *param_1,int *param_2)

{
  double dVar1;
  int iVar2;
  int *piVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int *piVar11;
  int iVar12;
  int *piVar13;
  float10 fVar14;
  float10 fVar15;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  double local_20;
  float local_18;
  float local_14;
  undefined8 local_10;
  int *local_8;
  
  if (*(int *)(&DAT_004fa0b0 + DAT_0058db00 * 0x14) == 1) {
    *param_1 = DAT_006435f0;
    param_1[1] = DAT_006435f4;
    param_1[2] = DAT_006435f8;
    return;
  }
  iVar2 = *param_2;
  piVar13 = (int *)0x0;
  local_8 = (int *)0x0;
  local_14 = 0.0;
  transform_vec3_array_by_matrix(&local_38,(float *)(param_2 + 1),1,(float *)(iVar2 + 0x18));
  fVar10 = DAT_006435f8;
  fVar9 = DAT_006435f4;
  iVar12 = 0;
  local_18 = *(float *)(&DAT_004fa0bc + DAT_0058db00 * 0x14) * _DAT_004be680;
  if (0 < DAT_0058db08) {
    piVar11 = &DAT_0058db24;
    do {
      piVar3 = (int *)*piVar11;
      if ((*piVar3 != 0) && (*piVar3 != iVar2)) {
        fVar4 = (float)piVar3[0x18] - local_38;
        fVar5 = (float)piVar3[0x19] - local_34;
        fVar6 = (float)piVar3[0x1a] - local_30;
        fVar7 = fVar6 * fVar6 + fVar5 * fVar5 + fVar4 * fVar4;
        local_10 = (double)CONCAT44(fVar7,(int)local_10);
        param_2 = (int *)(_DAT_004be638 / ((float)piVar3[3] * fVar7 - _DAT_004be670));
        fVar8 = _DAT_004be638;
        if ((*(byte *)(piVar3 + 1) & 1) != 0) {
          local_20 = (double)((float)piVar3[2] * (float)_DAT_004be688);
          fVar4 = (((float)piVar3[0xe] * fVar6 +
                   (float)piVar3[0xc] * fVar4 + (fVar5 + (float)piVar3[0xb]) * (float)piVar3[0xd]) /
                   SQRT(((float)piVar3[0xb] - fVar5 * _DAT_004be684) * (float)piVar3[0xb] + fVar7) -
                  (float)_DAT_004be620) * (float)_DAT_004be628;
          local_10 = (double)fVar4;
          fVar8 = _DAT_004be610;
          if ((float)_DAT_004be668 < fVar4) {
            fVar15 = (float10)((float)piVar3[2] * (float)_DAT_004be688) * (float10)fVar4;
            local_10._0_4_ = SUB84((double)(fVar15 + (float10)_DAT_004faf18),0);
            fVar14 = (float10)fscale((float10)1,(float10)(int)local_10);
            fVar15 = (float10)f2xm1(fVar15 - (float10)(int)local_10);
            fVar14 = fVar14 * (fVar15 + (float10)1);
            local_10 = (double)fVar14;
            fVar8 = (float)fVar14;
          }
          param_2 = (int *)(fVar8 * (float)param_2);
        }
        if ((float)local_8 < (float)param_2) {
          local_8 = param_2;
          piVar13 = piVar3;
          local_14 = fVar8;
        }
      }
      iVar12 = iVar12 + 1;
      piVar11 = piVar11 + 1;
    } while (iVar12 < DAT_0058db08);
  }
  if ((piVar13 != (int *)0x0) && (local_18 < (float)local_8)) {
    local_2c = (float)piVar13[0x18] - local_38;
    local_28 = ((float)piVar13[0x19] - local_14 * _DAT_004be690) - local_34;
    local_24 = (float)piVar13[0x1a] - local_30;
    dVar1 = (double)(local_24 * local_24 + local_28 * local_28 + local_2c * local_2c);
    fVar14 = zone_satellite_map_context_helper_00495000
                       (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
    *param_1 = (float)((float10)local_2c * fVar14);
    param_1[1] = (float)((float10)local_28 * fVar14);
    param_1[2] = (float)((float10)local_24 * fVar14);
    return;
  }
  *param_1 = DAT_006435f0;
  param_1[1] = fVar9;
  param_1[2] = fVar10;
  return;
}


