/*
 * Program: i76.exe
 * Function: find_nearest_effect_target_in_weapon_cone
 * Entry: 004361e0
 * Signature: int __cdecl find_nearest_effect_target_in_weapon_cone(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6, int param_7, int param_8)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Searches effect targets and returns the nearest target lying inside the
   weapon/fire cone. */

int __cdecl
find_nearest_effect_target_in_weapon_cone
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          int param_7,int param_8)

{
  int *piVar1;
  undefined4 *puVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  float *pfVar12;
  undefined4 *puVar13;
  int local_168;
  float local_140 [6];
  float local_128 [4];
  undefined4 local_118 [6];
  float local_100;
  float local_fc;
  float local_f8;
  undefined4 local_d8 [6];
  float local_c0;
  float local_bc;
  float local_b8;
  undefined4 local_98 [6];
  float local_80 [16];
  float local_40 [16];
  
  fVar7 = 422500.0;
  local_168 = 0;
  for (puVar2 = g_effect_target_primary_list; puVar2 != (undefined4 *)0x0;
      puVar2 = (undefined4 *)*puVar2) {
    piVar1 = (int *)puVar2[2];
    if (*piVar1 != param_8) {
      pfVar8 = (float *)effect_target_list_scan_context_helper_004387b0(local_98,piVar1);
      pfVar12 = local_140;
      for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
        *pfVar12 = *pfVar8;
        pfVar8 = pfVar8 + 1;
        pfVar12 = pfVar12 + 1;
      }
      if (((((param_3 - local_140[2]) * (param_3 - local_140[2]) +
             (param_2 - local_140[1]) * (param_2 - local_140[1]) +
             (param_1 - local_140[0]) * (param_1 - local_140[0]) <= (float)_DAT_004bd008) &&
           (iVar10 = *piVar1, iVar10 != 0)) && (*(int *)(iVar10 + 0x70) != 0)) &&
         ((*(int *)(iVar10 + 0x6c) != 1 || ((*(byte *)(*(int *)(iVar10 + 0x70) + 0x454) & 1) != 0)))
         ) {
        puVar9 = (undefined4 *)compute_transform_relative_to_ancestor(local_80,param_7,0);
        puVar13 = local_118;
        for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
          *puVar13 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar13 = puVar13 + 1;
        }
        puVar9 = (undefined4 *)compute_transform_relative_to_ancestor(local_40,iVar10,0);
        puVar13 = local_d8;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          *puVar13 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar13 = puVar13 + 1;
        }
        if ((float)_DAT_004bd000 <
            ABS(local_b8 * local_f8 + local_bc * local_fc + local_c0 * local_100)) {
          pfVar8 = (float *)get_effect_target_transformed_position_radius(local_128,piVar1);
          fVar3 = *pfVar8 - param_1;
          fVar5 = pfVar8[1] - param_2;
          fVar6 = pfVar8[2] - param_3;
          fVar4 = fVar6 * param_6 + fVar5 * param_5 + fVar3 * param_4;
          if (((_DAT_004bcfe0 <= fVar4) &&
              (fVar3 = fVar6 * fVar6 + fVar5 * fVar5 + fVar3 * fVar3,
              fVar3 * (float)_DAT_004bd010 < fVar4 * fVar4)) && (fVar3 < fVar7)) {
            local_168 = *piVar1;
            fVar7 = fVar3;
          }
        }
      }
    }
  }
  return local_168;
}


