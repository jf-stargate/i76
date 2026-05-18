/*
 * Program: i76.exe
 * Function: update_ai_vehicle_pursuit_attack_drive_state
 * Entry: 0041db10
 * Signature: undefined __cdecl update_ai_vehicle_pursuit_attack_drive_state(float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Updates pursuit/attack driving state, candidate
   steering, throttle, and timing around a selected target. */

void __cdecl update_ai_vehicle_pursuit_attack_drive_state(float *param_1)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  
  pfVar1 = (float *)get_vehicle_runtime_context((int)param_1);
  pfVar1[0x3c] = 0.0;
  vehicle_specials_state_getter_helper_00467370((int)param_1,3);
  pfVar1[0x3a] = 1.0;
  fVar2 = (float)get_ai_vehicle_behavior_state_block((int)param_1);
  *(undefined4 *)((int)fVar2 + 0xa998) = 0;
  if (_DAT_004bcae4 <= *(float *)((int)fVar2 + 0x9d28)) {
    update_ai_vehicle_pursuit_path_control
              (param_1,(int)pfVar1,fVar2,*(float *)((int)fVar2 + 0x9d2c),
               (float *)((int)fVar2 + 0x9d34),0,1.4013e-45);
    fVar5 = get_gameplay_runtime_seconds();
    *(float *)((int)fVar2 + 0x9d34) =
         (float)(((float10)_DAT_004bcae4 - (float10)*(float *)((int)fVar2 + 0xa820)) *
                 (float10)_DAT_004bcb30 + fVar5 + (float10)*(float *)((int)fVar2 + 0x9d34));
    *(undefined4 *)((int)fVar2 + 0x9d18) = 1;
  }
  else {
    if (_DAT_004bcae8 <= pfVar1[0x38]) {
      set_vehicle_steering_to_max_right_grip((int)param_1);
    }
    else {
      set_vehicle_steering_to_max_left_grip((int)param_1);
    }
    if ((*(int *)((int)fVar2 + 0x9d2c) != 0) &&
       (*(int *)(*(int *)((int)fVar2 + 0x9d2c) + 0x6c) == 1)) {
      if (_DAT_004bcad0 <= pfVar1[0x2b]) {
        if (pfVar1[0x2b] <= _DAT_004bcb2c) {
          fVar5 = (float10)world_object_geometry_context_helper_00458920((int)param_1);
          fVar4 = (float10)world_object_geometry_context_helper_004589d0
                                     ((uint)param_1,*(uint *)((int)fVar2 + 0x9d2c));
          iVar3 = world_object_geometry_context_helper_00458a30((float)fVar5,(float)fVar4);
          if ((-1 < iVar3) && ((iVar3 < 2 || (iVar3 == 7)))) {
            fVar5 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
            set_ai_vehicle_throttle_brake_toward_speed((float)param_1,(float)fVar5);
          }
          increase_vehicle_throttle_toward_max_safe_drive((float)param_1);
          pfVar1 = param_1;
        }
        else {
          fVar5 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
          set_ai_vehicle_throttle_brake_toward_speed((float)param_1,(float)fVar5);
        }
      }
      else {
        increase_vehicle_throttle_toward_max_safe_drive((float)param_1);
      }
    }
    fVar5 = get_gameplay_runtime_seconds();
    *(float *)((int)fVar2 + 0x9d34) =
         (float)(((float10)_DAT_004bcae4 - (float10)*(float *)((int)fVar2 + 0xa820)) *
                 (float10)_DAT_004bcb30 + fVar5 + (float10)_DAT_004bcad4);
    *(undefined4 *)((int)fVar2 + 0x9d18) = 1;
  }
  *(float *)((int)fVar2 + 0x9d1c) = pfVar1[0x2b];
  fVar5 = get_gameplay_runtime_seconds();
  *(float *)((int)fVar2 + 0x9d24) = (float)fVar5;
  return;
}


