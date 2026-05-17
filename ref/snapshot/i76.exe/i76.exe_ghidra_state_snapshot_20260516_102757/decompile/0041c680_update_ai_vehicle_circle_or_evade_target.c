/*
 * Program: i76.exe
 * Function: update_ai_vehicle_circle_or_evade_target
 * Entry: 0041c680
 * Signature: undefined __cdecl update_ai_vehicle_circle_or_evade_target(float param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Steers toward/away from target based on range and
   heading, switching between throttle, braking, and reverse steering. */

void __cdecl update_ai_vehicle_circle_or_evade_target(float param_1,uint param_2)

{
  int iVar1;
  float10 fVar2;
  float10 fVar3;
  undefined4 local_8;
  
  iVar1 = get_ai_vehicle_behavior_state_block((int)param_1);
  fVar2 = (float10)world_object_geometry_context_helper_00458920((int)param_1);
  world_object_geometry_context_helper_004589d0((uint)param_1,param_2);
  fVar3 = (float10)world_object_geometry_context_helper_004589f0((uint)param_1,param_2);
  if (*(int *)(iVar1 + 0xa97c) == 0) {
    *(undefined4 *)(iVar1 + 0xa97c) = 0;
    fVar3 = (float10)world_object_geometry_context_helper_004589d0((uint)param_1,param_2);
    update_ai_vehicle_steering_control((int)param_1,(float)fVar3);
    fVar2 = normalize_angle_delta_signed_pi((float)fVar2,(float)fVar3);
    if ((float10)_DAT_004bcac8 <= ABS(fVar2)) {
      fVar2 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
      set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar2);
    }
    else {
      set_vehicle_brake_to_max_safe_value(param_1);
    }
  }
  else if (_DAT_004bcab8 <= (float)fVar3) {
    *(undefined4 *)(iVar1 + 0xa97c) = 0;
    fVar3 = (float10)world_object_geometry_context_helper_004589d0((uint)param_1,param_2);
    update_ai_vehicle_steering_control((int)param_1,(float)fVar3);
    fVar2 = normalize_angle_delta_signed_pi((float)fVar2,(float)fVar3);
    if ((float10)_DAT_004bcac8 <= ABS(fVar2)) {
      fVar2 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
      set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar2);
    }
    else {
      set_vehicle_brake_to_max_safe_value(param_1);
    }
  }
  else {
    fVar2 = (float10)world_object_geometry_context_helper_004589d0((uint)param_1,param_2);
    local_8 = (float)(fVar2 + (float10)_DAT_004bcabc);
    if (_DAT_004bcabc < local_8) {
      local_8 = _DAT_004bcac0 - local_8;
    }
    update_ai_vehicle_steering_control((int)param_1,local_8);
    increase_vehicle_throttle_toward_max_safe_drive(param_1);
  }
  return;
}


