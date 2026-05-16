/*
 * Program: i76.exe
 * Function: classify_roadwar_next_turn_direction
 * Entry: 00415b30
 * Signature: undefined4 __cdecl classify_roadwar_next_turn_direction(uint param_1, int * param_2, int param_3, uint param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Classifies next Roadwar turn/heading direction from
   current vehicle heading and route node progression. */

undefined4 __cdecl
classify_roadwar_next_turn_direction(uint param_1,int *param_2,int param_3,uint param_4)

{
  int *piVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  undefined4 uVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  
  piVar5 = param_2;
  if (param_3 < 1) {
    fVar8 = (float10)world_object_geometry_context_helper_00458920(param_1);
    fVar9 = (float10)world_object_geometry_context_helper_004589d0(param_1,param_4);
    fVar10 = fVar9 - (float10)(float)fVar8;
    if (fVar9 < (float10)(float)fVar8) {
      fVar10 = fVar10 - (float10)_DAT_004bc834;
    }
    if (fVar10 <= (float10)_DAT_004bc838) {
      floor((double)((fVar10 - (float10)_DAT_004bc83c) * (float10)_DAT_004bc840));
      uVar7 = ftol();
      return uVar7;
    }
    return 0;
  }
  param_3 = *param_2;
  piVar1 = param_2 + 1;
  param_2 = (int *)param_2[7];
  iVar6 = roadwar_get_next_road_index((int *)&param_2,*piVar1,&param_3);
  if (iVar6 != 0) {
    pfVar2 = (float *)(param_2[10] + 0xc + param_3 * 0x18);
    pfVar3 = (float *)(*(int *)(piVar5[7] + 0x28) + 0xc + *piVar5 * 0x18);
    fVar4 = *(float *)(param_1 + 0x38) * (pfVar2[2] - pfVar3[2]) +
            *(float *)(param_1 + 0x34) * (pfVar2[1] - pfVar3[1]) +
            *(float *)(param_1 + 0x30) * (*pfVar2 - *pfVar3);
    if (_DAT_004bc828 <= fVar4) {
      if (_DAT_004bc82c < fVar4) {
        return 0;
      }
      if (*(float *)(param_1 + 0x34) * (pfVar2[1] - pfVar3[1]) +
          (*(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x38)) * -(*pfVar2 - *pfVar3) <=
          _DAT_004bc830) {
        return 1;
      }
      return 3;
    }
  }
  return 2;
}


