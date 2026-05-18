/*
 * Program: i76.exe
 * Function: update_ai_vehicle_pursuit_intercept_state
 * Entry: 0041a040
 * Signature: undefined4 __cdecl update_ai_vehicle_pursuit_intercept_state(int param_1, undefined4 * param_2, undefined4 * param_3, undefined4 param_4, undefined4 * param_5, float * param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Large AI behavior helper for pursuit/intercept
   steering using runtime delta, target vectors, vehicle context, and transformed heading vectors.
    */

undefined4 __cdecl
update_ai_vehicle_pursuit_intercept_state
          (int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4,
          undefined4 *param_5,float *param_6)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  float10 fVar9;
  float in_stack_ffffff5c;
  float in_stack_ffffff60;
  float in_stack_ffffff64;
  float in_stack_ffffff68;
  float in_stack_ffffff6c;
  float in_stack_ffffff70;
  float in_stack_ffffff74;
  float in_stack_ffffff78;
  float in_stack_ffffff7c;
  float fVar10;
  int *piVar11;
  float fVar12;
  float fVar13;
  float *pfVar14;
  float *pfVar15;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24 [3];
  undefined4 local_18 [6];
  
  fVar9 = get_runtime_update_delta_seconds();
  iVar4 = param_1;
  get_vehicle_runtime_context(param_1);
  local_48 = *(float *)(iVar4 + 0x30);
  iVar1 = *(int *)(*(int *)(iVar4 + 0x70) + 0x108);
  local_44 = *(float *)(iVar4 + 0x34);
  local_40 = *(float *)(iVar4 + 0x38);
  piVar3 = (int *)get_current_effect_target_scan_object();
  puVar2 = param_5;
  if (piVar3 == (int *)0x0) {
    *param_2 = 0;
    return 0;
  }
  do {
    iVar4 = is_vehicle_or_actor_runtime_world_object(*piVar3);
    if (((iVar4 == 0) && (*(int *)(*piVar3 + 0x6c) != 4)) &&
       (iVar4 = test_bounds_overlap_xz_ranges((float *)(iVar1 + 0x9d40),(int)piVar3), iVar4 != 0)) {
      pfVar15 = local_24;
      fVar12 = (float)piVar3[4] - _DAT_004bc8f0;
      pfVar14 = &local_4c;
      puVar7 = local_18;
      fVar10 = 6.027046e-39;
      piVar11 = piVar3;
      fVar13 = (float)fVar9;
      puVar5 = (undefined4 *)effect_target_list_scan_context_helper_004387b0(puVar7,piVar3);
      puVar8 = (undefined4 *)&stack0xffffff74;
      for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar8 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar8 = puVar8 + 1;
      }
      puVar5 = puVar2;
      puVar8 = (undefined4 *)&stack0xffffff5c;
      for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar8 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar8 = puVar8 + 1;
      }
      iVar4 = test_effect_target_swept_interval_candidate
                        (in_stack_ffffff5c,in_stack_ffffff60,in_stack_ffffff64,in_stack_ffffff68,
                         in_stack_ffffff6c,in_stack_ffffff70,in_stack_ffffff74,in_stack_ffffff78,
                         in_stack_ffffff7c,fVar10,(float)puVar7,(float)piVar11,fVar12,fVar13,pfVar14
                         ,pfVar15);
      if (iVar4 != 0) {
        iVar4 = *piVar3;
        if (*(int *)(iVar4 + 0x6c) == 0xb) {
          local_38 = *(float *)(iVar4 + 0x34);
          local_34 = *(float *)(iVar4 + 0x38);
          if (_DAT_004bca28 <
              local_34 * local_40 + local_38 * local_44 + *(float *)(iVar4 + 0x30) * local_48)
          goto LAB_0041a1d4;
        }
        else if (*(int *)(iVar4 + 0x6c) == 0xc) {
          local_2c = *(float *)(iVar4 + 0x34);
          local_28 = *(float *)(iVar4 + 0x38);
          if ((float)_DAT_004bca30 <
              ABS(local_28 * local_40 + local_2c * local_44 + *(float *)(iVar4 + 0x30) * local_48))
          goto LAB_0041a1d4;
        }
        puVar7 = puVar2;
        puVar5 = (undefined4 *)&stack0xffffff6c;
        for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar5 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar5 = puVar5 + 1;
        }
        in_stack_ffffff68 = 6.02735e-39;
        iVar6 = query_vehicle_effect_collision_response_state();
        iVar4 = param_1;
        if (iVar6 != 0) {
          *param_2 = 0x3f800000;
          iVar1 = *piVar3;
          get_world_object_damage_or_target_vectors(param_1,&local_3c,&param_1);
          get_world_object_damage_or_target_vectors(iVar1,&local_30,&param_2);
          local_30 = local_30 - local_3c;
          local_2c = local_2c - local_38;
          local_28 = local_28 - local_34;
          fVar13 = local_28 * local_28 + local_2c * local_2c + local_30 * local_30;
          fVar12 = _DAT_004bc928;
          if (_DAT_004bc924 <= ABS(fVar13)) {
            fVar12 = (local_28 *
                      ((float)*(double *)(iVar4 + 0x50) - (float)*(double *)(iVar1 + 0x50)) +
                     local_2c *
                     ((float)*(double *)(iVar4 + 0x48) - (float)*(double *)(iVar1 + 0x48)) +
                     local_30 *
                     ((float)*(double *)(iVar4 + 0x40) - (float)*(double *)(iVar1 + 0x40))) / fVar13
            ;
          }
          *param_6 = fVar12;
          *param_3 = 0x3fa00000;
          return 1;
        }
      }
    }
LAB_0041a1d4:
    piVar3 = (int *)effect_target_scan_query_context_helper_00436790();
    if (piVar3 == (int *)0x0) {
      *param_2 = 0;
      return 0;
    }
  } while( true );
}


