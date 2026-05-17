/*
 * Program: i76.exe
 * Function: update_ai_vehicle_target_seek_drive_state
 * Entry: 0041dd80
 * Signature: undefined __cdecl update_ai_vehicle_target_seek_drive_state(float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Updates target-seeking drive behavior using candidate
   selection, steering, throttle, and timers. */

void __cdecl update_ai_vehicle_target_seek_drive_state(float *param_1)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  undefined4 local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar1 = get_vehicle_runtime_context((int)param_1);
  local_10 = (float)get_ai_vehicle_behavior_state_block((int)param_1);
  if (*(int *)((int)local_10 + 0x9d18) == 0) {
    iVar2 = select_ai_vehicle_target_or_path_candidate
                      (param_1,*(undefined4 *)(iVar1 + 0xe0),*(undefined4 *)(iVar1 + 0xe4),
                       (uint *)((int)local_10 + 0x9d2c),&local_14,&local_8,0,1,
                       (float *)((int)local_10 + 0x9d28));
    if (iVar2 == 0) {
      clear_vehicle_throttle_brake_command((int)param_1);
      set_ai_vehicle_throttle_brake_toward_speed((float)param_1,*(float *)((int)local_10 + 0x80));
    }
    else if (_DAT_004bcae4 <= *(float *)((int)local_10 + 0x9d28)) {
      update_ai_vehicle_pursuit_path_control
                (param_1,iVar1,local_10,*(float *)((int)local_10 + 0x9d2c),&local_8,0,1.4013e-45);
      fVar4 = get_runtime_time_seconds();
      *(float *)((int)local_10 + 0x9d34) =
           (float)(((float10)_DAT_004bcae4 - (float10)*(float *)((int)local_10 + 0xa820)) *
                   (float10)_DAT_004bcb30 + fVar4 + (float10)local_8);
      *(undefined4 *)((int)local_10 + 0x9d18) = 0;
      fVar4 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
      set_ai_vehicle_throttle_brake_toward_speed((float)param_1,(float)fVar4);
    }
    else {
      if (_DAT_004bcae8 <= *(float *)(iVar1 + 0xe0)) {
        set_vehicle_steering_to_max_right_grip((int)param_1);
      }
      else {
        set_vehicle_steering_to_max_left_grip((int)param_1);
      }
      if ((*(int *)((int)local_10 + 0x9d2c) != 0) &&
         (*(int *)(*(int *)((int)local_10 + 0x9d2c) + 0x6c) == 1)) {
        if (_DAT_004bcad0 <= *(float *)(iVar1 + 0xac)) {
          if (*(float *)(iVar1 + 0xac) <= _DAT_004bcb2c) {
            fVar4 = (float10)world_object_geometry_context_helper_00458920((int)param_1);
            fVar3 = (float10)world_object_geometry_context_helper_004589d0
                                       ((uint)param_1,*(uint *)((int)local_10 + 0x9d2c));
            local_c = (float)fVar3;
            iVar1 = world_object_geometry_context_helper_00458a30((float)fVar4,local_c);
            if ((-1 < iVar1) && ((iVar1 < 2 || (iVar1 == 7)))) {
              fVar4 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
              set_ai_vehicle_throttle_brake_toward_speed((float)param_1,(float)fVar4);
            }
            increase_vehicle_throttle_toward_max_safe_drive((float)param_1);
          }
          else {
            fVar4 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
            set_ai_vehicle_throttle_brake_toward_speed((float)param_1,(float)fVar4);
          }
        }
        else {
          increase_vehicle_throttle_toward_max_safe_drive((float)param_1);
        }
      }
      fVar4 = get_runtime_time_seconds();
      *(float *)((int)local_10 + 0x9d34) =
           (float)(((float10)_DAT_004bcae4 - (float10)*(float *)((int)local_10 + 0xa820)) *
                   (float10)_DAT_004bcb30 + fVar4 + (float10)_DAT_004bcad4);
      *(undefined4 *)((int)local_10 + 0x9d18) = 1;
    }
  }
  else {
    *(undefined4 *)((int)local_10 + 0x9d18) = 0;
  }
  return;
}


