/*
 * Program: i76.exe
 * Function: update_ai_vehicle_reverse_turnaround_state
 * Entry: 0041cff0
 * Signature: undefined __cdecl update_ai_vehicle_reverse_turnaround_state(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Updates reverse-turnaround behavior using heading
   delta, forward alignment, braking, and steering helper calls. */

void __cdecl update_ai_vehicle_reverse_turnaround_state(float param_1)

{
  float *pfVar1;
  float10 fVar2;
  undefined4 local_34 [3];
  int local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  int local_c;
  float local_8;
  
  local_28 = 0;
  local_c = 0;
  local_28 = get_vehicle_runtime_context((int)param_1);
  pfVar1 = (float *)copy_object_local_translation_vec3(local_34,(int)param_1 + 0x18);
  local_18 = *pfVar1;
  local_14 = pfVar1[1];
  local_10 = pfVar1[2];
  fVar2 = dot_product_vec3(&local_18,(float *)(local_28 + 0xbc));
  local_20 = (float)fVar2;
  local_c = get_ai_vehicle_behavior_state_block((int)param_1);
  fVar2 = compute_ai_vehicle_forward_heading_angle((int)param_1);
  local_1c = (float)fVar2;
  fVar2 = normalize_angle_delta_signed_pi(local_1c,*(float *)(local_c + 0x9d38));
  local_8 = (float)ABS(fVar2);
  if (local_8 < _DAT_004bcb04) {
    if (local_20 <= _DAT_004bcadc) {
      if (local_20 <= _DAT_004bcb08) {
        fVar2 = compute_vehicle_tire_grip_control_scalar((int)param_1);
        local_24 = (float)ABS(fVar2);
        if (*(float *)(*(int *)(local_28 + 0x108) + 0x9d20) <= (float)_DAT_004bcaf8) {
          *(float *)(local_28 + 0xe0) = _DAT_004bcb10 * local_24;
        }
        else {
          *(float *)(local_28 + 0xe0) = _DAT_004bcb0c * local_24;
        }
        fVar2 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
        set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar2);
      }
      else {
        set_vehicle_throttle_to_max_safe_drive(param_1);
        clear_vehicle_throttle_brake_command((int)param_1);
      }
    }
    else {
      set_vehicle_brake_to_max_safe_value(param_1);
      clear_vehicle_throttle_brake_command((int)param_1);
    }
  }
  else {
    set_vehicle_brake_to_max_safe_value(param_1);
  }
  return;
}


