/*
 * Program: i76.exe
 * Function: find_nearest_primary_effect_target_in_forward_cone
 * Entry: 00436450
 * Signature: int __cdecl find_nearest_primary_effect_target_in_forward_cone(float param_1, float param_2, float param_3, int param_4, float param_5, float param_6, float param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Scans primary effect targets and returns the nearest vehicle target inside a
   forward cone. */

int __cdecl
find_nearest_primary_effect_target_in_forward_cone
          (float param_1,float param_2,float param_3,int param_4,float param_5,float param_6,
          float param_7)

{
  int *piVar1;
  undefined4 *puVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  int iVar9;
  float local_10 [4];
  
  if (param_4 == 0) {
    return 0;
  }
  iVar9 = 0;
  fVar7 = 422500.0;
  for (puVar2 = g_effect_target_primary_list; puVar2 != (undefined4 *)0x0;
      puVar2 = (undefined4 *)*puVar2) {
    piVar1 = (int *)puVar2[2];
    if ((*piVar1 != param_4) && (*(int *)(*piVar1 + 0x6c) == 1)) {
      pfVar8 = (float *)get_effect_target_transformed_position_radius(local_10,piVar1);
      fVar3 = *pfVar8 - param_1;
      fVar5 = pfVar8[1] - param_2;
      fVar6 = pfVar8[2] - param_3;
      fVar4 = fVar6 * param_7 + fVar5 * param_6 + fVar3 * param_5;
      if ((_DAT_004bcfe0 <= fVar4) &&
         ((fVar3 = fVar6 * fVar6 + fVar5 * fVar5 + fVar3 * fVar3,
          fVar3 * (float)_DAT_004bd018 < fVar4 * fVar4 && (fVar3 < fVar7)))) {
        iVar9 = *piVar1;
        fVar7 = fVar3;
      }
    }
  }
  return iVar9;
}


