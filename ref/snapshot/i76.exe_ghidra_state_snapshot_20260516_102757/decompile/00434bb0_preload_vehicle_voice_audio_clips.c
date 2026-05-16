/*
 * Program: i76.exe
 * Function: preload_vehicle_voice_audio_clips
 * Entry: 00434bb0
 * Signature: bool __cdecl preload_vehicle_voice_audio_clips(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: references vv*/vnvcs*.wav clips */

bool __cdecl preload_vehicle_voice_audio_clips(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  bool bVar6;
  float10 fVar7;
  float in_stack_fffffe8c;
  float in_stack_fffffe90;
  float in_stack_fffffe94;
  float in_stack_fffffe98;
  float in_stack_fffffe9c;
  float in_stack_fffffea0;
  float in_stack_fffffea4;
  float in_stack_fffffea8;
  float in_stack_fffffeac;
  float in_stack_fffffeb0;
  float in_stack_fffffeb4;
  float in_stack_fffffeb8;
  float fVar8;
  float fVar9;
  char *pcVar10;
  float *pfVar11;
  float *pfVar12;
  int local_124;
  float local_118;
  undefined4 local_114 [6];
  undefined4 local_fc [6];
  int local_e4;
  int local_e0;
  float local_80;
  int local_78;
  int local_74;
  float local_14;
  float local_c [3];
  
  bVar6 = false;
  if (((((float)param_1[0x14] <= (float)param_2[0x17]) &&
       ((float)param_2[0x14] <= (float)param_1[0x17])) &&
      ((float)param_1[0x16] <= (float)param_2[0x19])) &&
     ((float)param_2[0x16] <= (float)param_1[0x19])) {
    DAT_0052b924 = 1;
    fVar8 = (float)param_1[4] + (float)param_2[4];
    puVar1 = (undefined4 *)effect_target_list_scan_context_helper_004387b0(local_fc,param_1);
    puVar4 = local_fc;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar1 = (undefined4 *)effect_target_list_scan_context_helper_004387b0(local_114,param_2);
    pfVar12 = local_c;
    pfVar11 = &local_118;
    puVar4 = local_114;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar4 = puVar4 + 1;
    }
    local_124 = 0;
    fVar7 = get_runtime_update_delta_seconds();
    fVar9 = (float)fVar7;
    puVar1 = local_114;
    puVar4 = (undefined4 *)&stack0xfffffea4;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar1 = local_fc;
    puVar4 = (undefined4 *)&stack0xfffffe8c;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar4 = puVar4 + 1;
    }
    iVar2 = test_effect_target_swept_interval_candidate
                      (in_stack_fffffe8c,in_stack_fffffe90,in_stack_fffffe94,in_stack_fffffe98,
                       in_stack_fffffe9c,in_stack_fffffea0,in_stack_fffffea4,in_stack_fffffea8,
                       in_stack_fffffeac,in_stack_fffffeb0,in_stack_fffffeb4,in_stack_fffffeb8,fVar8
                       ,fVar9,pfVar11,pfVar12);
    if (iVar2 != 0) {
      bVar6 = *(int *)(*param_1 + 0x6c) != 7;
      if (param_1[5] == 1) {
        local_124 = test_effect_target_collision_pair(param_1,param_2,&local_e4,&local_78);
      }
      else if (param_2[5] == 1) {
        local_124 = test_effect_target_collision_pair(param_2,param_1,&local_78,&local_e4);
      }
    }
    if (local_124 != 0) {
      iVar2 = is_world_object_class_collision_target_candidate(local_e0);
      if (((iVar2 != 0) && (_DAT_004bcfe4 < local_80)) ||
         ((iVar2 = is_world_object_class_collision_target_candidate(local_74), iVar2 != 0 &&
          (_DAT_004bcfe4 < local_14)))) {
        if ((*(int *)(local_e0 + 0x6c) == 1) ||
           (local_e0 = local_74, *(int *)(local_74 + 0x6c) == 1)) {
          play_positional_audio_for_object_or_active_player
                    (s_vvbo1_wav_004f15a8,local_e0,(undefined4 *)0x0);
          return bVar6;
        }
      }
      else {
        iVar2 = *param_1;
        if ((*(int *)(*param_1 + 0x6c) != 8) && (iVar2 = local_74, *(int *)(*param_2 + 0x6c) == 8))
        {
          local_e0 = *param_2;
        }
        local_74 = iVar2;
        iVar2 = is_vehicle_or_actor_runtime_world_object(local_e0);
        if (iVar2 == 0) {
          piVar3 = &local_78;
          piVar5 = &local_e4;
        }
        else {
          piVar3 = &local_e4;
          piVar5 = &local_78;
        }
        iVar2 = is_vehicle_or_actor_runtime_world_object(piVar5[1]);
        if (iVar2 == 0) {
          if (*(int *)(piVar5[1] + 0x6c) == 4) {
            iVar2 = piVar3[1];
            pcVar10 = s_vnvco3_wav_004f1578;
          }
          else if (*(int *)(piVar5[1] + 0x6c) == 3) {
            iVar2 = piVar3[1];
            pcVar10 = s_vnvcs5_wav_004f156c;
          }
          else if ((float)piVar3[0x15] * (float)piVar3[0x15] +
                   (float)piVar3[0x17] * (float)piVar3[0x17] +
                   (float)piVar3[0x16] * (float)piVar3[0x16] <= _DAT_004bcfec) {
            iVar2 = piVar3[1];
            pcVar10 = s_vnvcs1_wav_004f1554;
          }
          else {
            iVar2 = piVar3[1];
            pcVar10 = s_vnvcs3_wav_004f1560;
          }
        }
        else {
          fVar8 = (float)piVar3[0x15] * (float)piVar3[0x15] +
                  (float)piVar3[0x17] * (float)piVar3[0x17] +
                  (float)piVar3[0x16] * (float)piVar3[0x16];
          if (fVar8 <= _DAT_004bcfe8) {
            if (fVar8 <= _DAT_004bcfec) {
              iVar2 = piVar3[1];
              pcVar10 = s_vvcbb3_wav_004f1584;
            }
            else {
              iVar2 = piVar3[1];
              pcVar10 = s_vvcre2_wav_004f1590;
            }
          }
          else {
            iVar2 = piVar3[1];
            pcVar10 = s_vvch2_wav_004f159c;
          }
        }
        play_positional_audio_for_object_or_active_player(pcVar10,iVar2,(undefined4 *)0x0);
        release_classifier_display(local_74,local_e0,&local_e4,&local_78);
      }
    }
    return bVar6;
  }
  return false;
}


