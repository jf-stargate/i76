/*
 * Program: i76.exe
 * Function: select_ai_target_candidate_and_maybe_play_engine_event
 * Entry: 0041d8b0
 * Signature: int __cdecl select_ai_target_candidate_and_maybe_play_engine_event(float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Selects a candidate target, applies route/heading
   gating, and may play a vehicle engine event sound. */

int __cdecl select_ai_target_candidate_and_maybe_play_engine_event(float *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float10 fVar5;
  float10 fVar6;
  uint local_38;
  uint local_2c;
  undefined4 local_10;
  int local_c;
  float local_8;
  
  local_c = 0;
  local_c = get_ai_vehicle_behavior_state_block((int)param_1);
  if (*(int *)(local_c + 0x9d14) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = get_vehicle_runtime_context((int)param_1);
    fVar5 = get_runtime_time_seconds();
    if ((float10)*(float *)(local_c + 0x9d00) + (float10)_DAT_004bcae4 <= fVar5) {
      if (*(int *)(local_c + 0xbc + *(int *)(local_c + 0xa8) * 0x14) == 0) {
        switch(*(undefined4 *)(iVar1 + 0x45c)) {
        case 2:
        case 3:
        case 4:
        case 7:
          local_2c = 1;
          break;
        default:
          local_2c = 0;
          break;
        case 6:
          fVar5 = (float10)world_object_geometry_context_helper_00458920((int)param_1);
          if (*(int *)(local_c + 0xa8) < 1) {
            local_2c = 0;
          }
          else {
            local_8 = *(float *)(local_c + 0xb4 + *(int *)(local_c + 0xa8) * 0x14) -
                      *(float *)(local_c + 0xb4 + (*(int *)(local_c + 0xa8) + -1) * 0x14);
            fVar6 = (float10)_CIatan2();
            fVar5 = normalize_angle_delta_signed_pi((float)fVar5,(float)fVar6);
            local_38 = (uint)(ABS(fVar5) < (float10)_DAT_004bcae4);
            local_2c = local_38;
          }
        }
      }
      else {
        local_2c = 1;
      }
    }
    else {
      local_2c = 0;
    }
    iVar1 = select_ai_vehicle_target_or_path_candidate
                      (param_1,*(undefined4 *)(iVar1 + 0xe0),*(undefined4 *)(iVar1 + 0xe4),
                       (uint *)(local_c + 0x9d2c),&local_10,(float *)(local_c + 0x9d34),local_2c,0,
                       (float *)(local_c + 0x9d28));
    if (((iVar1 != 0) && (*(int *)(local_c + 0x9d2c) != 0)) &&
       (iVar2 = is_vehicle_or_actor_runtime_world_object(*(int *)(local_c + 0x9d2c)), iVar2 != 0)) {
      uVar3 = rand();
      uVar4 = (int)uVar3 >> 0x1f;
      if (((uVar3 ^ uVar4) - uVar4 & 3 ^ uVar4) == uVar4) {
        play_vehicle_engine_event_sound((int)param_1,0);
      }
    }
  }
  return iVar1;
}


