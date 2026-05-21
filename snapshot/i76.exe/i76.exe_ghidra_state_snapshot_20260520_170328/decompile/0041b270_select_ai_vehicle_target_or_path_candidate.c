/*
 * Program: i76.exe
 * Function: select_ai_vehicle_target_or_path_candidate
 * Entry: 0041b270
 * Signature: undefined4 __cdecl select_ai_vehicle_target_or_path_candidate(float * param_1, undefined4 param_2, undefined4 param_3, uint * param_4, undefined4 * param_5, float * param_6, int param_7, int param_8, float * param_9)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Misnamed earlier as get_tick_count_wrapper_a;
   actually searches/selects an AI target/path candidate and writes candidate/timer/progress
   outputs. */

undefined4 __cdecl
select_ai_vehicle_target_or_path_candidate
          (float *param_1,undefined4 param_2,undefined4 param_3,uint *param_4,undefined4 *param_5,
          float *param_6,int param_7,int param_8,float *param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float10 fVar7;
  float local_a4;
  float local_a0;
  float local_9c;
  int local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  uint local_5c;
  float local_58 [3];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  double local_30;
  double local_28;
  double local_20;
  float local_18 [3];
  float local_c [3];
  
  GetTickCount();
  iVar4 = get_vehicle_runtime_context((int)param_1);
  local_94 = *(float *)(iVar4 + 0xe0);
  local_98 = *(undefined4 *)(iVar4 + 0xe4);
  *(undefined4 *)(iVar4 + 0xe0) = param_2;
  *(undefined4 *)(iVar4 + 0xe4) = param_3;
  integrate_vehicle_dynamics_with_contact_mode
            (param_1,&local_5c,&local_78,&local_60,local_c,local_18,local_58);
  *(float *)(iVar4 + 0xe0) = local_94;
  *(int *)(iVar4 + 0xe4) = local_98;
  local_a4 = (float)local_30;
  local_a0 = (float)local_28;
  local_9c = (float)local_20;
  local_90 = local_a4;
  local_8c = local_a0;
  local_88 = local_9c;
  if ((param_7 == 0) &&
     (iVar5 = probe_ai_vehicle_path_clearance_along_heading
                        (local_58,&local_90,&local_78,
                         SQRT(local_70 * local_70 + local_74 * local_74 + local_78 * local_78),
                         param_6,*(float *)(iVar4 + 0xe8),0,param_9), iVar5 != 0)) {
    *param_4 = 0;
    return 1;
  }
  iVar5 = compute_ai_vehicle_intercept_or_avoidance_solution
                    ((uint)param_1,&local_90,&local_78,param_4,param_5,param_6,param_8,param_9,
                     param_7);
  if (iVar5 != 0) {
    return 1;
  }
  if (param_7 == 0) {
    local_88 = local_88 - local_44 * _DAT_004bc9cc;
    local_90 = local_90 - local_4c * _DAT_004bc9cc;
    local_8c = local_8c - local_48 * _DAT_004bc9cc;
    pfVar6 = (float *)sample_runtime_terrain_packed_word
                                (&local_a4,(double)local_90,SUB84((double)local_88,0),
                                 (int)((ulonglong)(double)local_88 >> 0x20));
    fVar1 = *pfVar6;
    fVar2 = pfVar6[1];
    fVar3 = pfVar6[2];
    local_6c = local_38 * fVar2 - local_3c * fVar3;
    local_68 = local_40 * fVar3 - local_38 * fVar1;
    local_64 = (local_3c * fVar1 - local_40 * fVar2) * _DAT_004bc918;
    local_a4 = local_64 * fVar2 - local_68 * _DAT_004bc918 * fVar3;
    local_a0 = local_6c * _DAT_004bc918 * fVar3 - local_64 * fVar1;
    local_9c = local_68 * _DAT_004bc918 * fVar1 - local_6c * _DAT_004bc918 * fVar2;
    local_84 = local_a4;
    local_80 = local_a0;
    local_7c = local_9c;
    fVar7 = mission_flow_map_context_helper_0049c7b0();
    if (fVar7 <= (float10)_DAT_004bc9a8) {
      fVar7 = mission_flow_map_context_helper_0049c7b0();
    }
    else {
      fVar7 = (float10)_DAT_004bc9a8;
    }
    fVar7 = fVar7 * (float10)_DAT_004bca6c * (float10)*(float *)(iVar4 + 0xe8);
    local_84 = (float)(fVar7 * (float10)local_84);
    local_80 = (float)((float10)local_80 * fVar7);
    local_7c = (float)((float10)local_7c * fVar7);
    iVar4 = update_ai_vehicle_pursuit_intercept_state
                      ((int)param_1,param_5,param_6,param_4,&local_90,param_9);
    if (iVar4 != 0) {
      return 1;
    }
  }
  local_94 = _DAT_004bca74 -
             (_DAT_004bc91c - *(float *)(*(int *)((int)param_1[0x1c] + 0x108) + 0xa820)) *
             _DAT_004bca70;
  local_98 = rand();
  local_98 = local_98 % 1000;
  if ((local_94 < (float)local_98) &&
     (iVar4 = compute_ai_vehicle_relative_target_vector_state((int)param_1,param_5,param_6,param_9),
     iVar4 != 0)) {
    *param_4 = 0;
    return 1;
  }
  *param_5 = 0;
  *param_6 = 0.5;
  return 0;
}


