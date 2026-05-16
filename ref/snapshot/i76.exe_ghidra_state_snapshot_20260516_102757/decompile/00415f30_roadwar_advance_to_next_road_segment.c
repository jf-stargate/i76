/*
 * Program: i76.exe
 * Function: roadwar_advance_to_next_road_segment
 * Entry: 00415f30
 * Signature: undefined4 __cdecl roadwar_advance_to_next_road_segment(int param_1, float param_2, float param_3, float param_4, int * param_5, float param_6, float param_7, float * param_8)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Roadwar helper that advances to the next road index/segment. */

undefined4 __cdecl
roadwar_advance_to_next_road_segment
          (int param_1,float param_2,float param_3,float param_4,int *param_5,float param_6,
          float param_7,float *param_8)

{
  int *piVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int *piVar6;
  int iVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  int local_48;
  int local_44;
  int local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  piVar6 = param_5;
  local_40 = param_5[7];
  piVar1 = param_5 + 1;
  local_48 = 0;
  param_5 = (int *)*param_5;
  iVar7 = roadwar_get_next_road_index(&local_40,*piVar1,(int *)&param_5);
  if (iVar7 == 0) {
    fVar8 = (float10)fpatan((float10)*(float *)(param_1 + 0x30),(float10)*(float *)(param_1 + 0x38))
    ;
    *param_8 = (float)fVar8;
    return 0;
  }
  pfVar2 = (float *)(*(int *)(local_40 + 0x28) + 0xc + (int)param_5 * 0x18);
  local_24 = *pfVar2;
  local_44 = *piVar6;
  local_20 = pfVar2[1];
  local_48 = piVar6[7];
  local_1c = pfVar2[2];
  iVar7 = *(int *)(local_48 + 0x28) + 0xc + local_44 * 0x18;
  local_3c = *(float *)(*(int *)(local_48 + 0x28) + 0xc + local_44 * 0x18);
  local_18 = local_24 - local_3c;
  local_38 = *(float *)(iVar7 + 4);
  local_34 = *(float *)(iVar7 + 8);
  fVar3 = local_20 - local_38;
  local_10 = local_1c - local_34;
  param_5 = (int *)((float)piVar6[1] * param_7);
  local_14 = fVar3;
  local_c = local_18;
  local_4 = local_10;
  fVar8 = vec3_length(local_18,fVar3,local_10);
  local_30 = -local_10;
  if ((fVar8 <= (float10)_DAT_004bc844) || ((float10)_DAT_004bc848 <= fVar8)) {
    fVar8 = (float10)(float)param_5 / fVar8;
    local_30 = (float)((float10)local_30 * fVar8);
    local_2c = (float)((float10)fVar3 * fVar8);
    local_28 = (float)((float10)local_18 * fVar8);
    local_14 = local_2c;
  }
  else {
    local_28 = local_18;
    local_2c = fVar3;
  }
  fVar5 = local_30 + local_3c;
  fVar3 = local_2c + local_38;
  fVar4 = local_28 + local_34;
  local_18 = fVar5 - param_2;
  local_10 = fVar4 - param_4;
  param_5 = (int *)SQRT(local_10 * local_10 +
                        (fVar3 - param_3) * (fVar3 - param_3) + local_18 * local_18);
  if (param_6 < (float)param_5) {
    fVar8 = (float10)fpatan((float10)local_18,(float10)local_10);
    *param_8 = (float)fVar8;
    return 1;
  }
  local_c = fVar5;
  local_8 = fVar3;
  local_4 = fVar4;
  iVar7 = roadwar_get_next_road_index(&local_48,piVar6[1],&local_44);
  if (iVar7 == 0) {
    fVar8 = (float10)fpatan((float10)local_18,(float10)local_10);
    *param_8 = (float)fVar8;
    return 0;
  }
  param_6 = param_6 - (float)param_5;
  local_1c = fVar4;
  local_24 = fVar5;
  local_20 = fVar3;
  while( true ) {
    pfVar2 = (float *)(*(int *)(local_48 + 0x28) + 0xc + local_44 * 0x18);
    local_3c = *pfVar2;
    local_38 = pfVar2[1];
    local_34 = pfVar2[2];
    fVar3 = (float)((float10)local_30 + (float10)local_3c);
    fVar8 = ((float10)local_30 + (float10)local_3c) - (float10)local_24;
    fVar4 = (float)((float10)local_2c + (float10)local_38);
    fVar9 = ((float10)local_2c + (float10)local_38) - (float10)local_20;
    fVar5 = (float)((float10)local_28 + (float10)local_34);
    fVar10 = ((float10)local_28 + (float10)local_34) - (float10)local_1c;
    local_8 = (float)fVar9;
    param_5 = (int *)(float)SQRT(fVar10 * fVar10 + fVar9 * (float10)local_8 + fVar8 * fVar8);
    if (param_6 <= (float)param_5) {
      fVar8 = (float10)fpatan((((float10)param_6 / (float10)(float)param_5) * fVar8 + (float10)fVar3
                              ) - (float10)param_2,
                              (((float10)param_6 / (float10)(float)param_5) * fVar10 +
                              (float10)fVar5) - (float10)param_4);
      *param_8 = (float)fVar8;
      return 1;
    }
    local_18 = fVar3;
    local_14 = fVar4;
    local_10 = fVar5;
    iVar7 = roadwar_get_next_road_index(&local_48,piVar6[1],&local_44);
    if (iVar7 == 0) break;
    param_6 = param_6 - (float)param_5;
    local_1c = fVar5;
    local_24 = fVar3;
    local_20 = fVar4;
  }
  fVar8 = (float10)fpatan((float10)param_2,(float10)param_4);
  *param_8 = (float)fVar8;
  return 0;
}


