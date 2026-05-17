/*
 * Program: i76.exe
 * Function: update_ai_vehicle_intercept_or_avoidance_drive
 * Entry: 0041ef40
 * Signature: undefined __cdecl update_ai_vehicle_intercept_or_avoidance_drive(float param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Large drive update using target vectors,
   closest-approach parameter, steering control, braking, and throttle helpers. */

void __cdecl update_ai_vehicle_intercept_or_avoidance_drive(float param_1,int param_2)

{
  float *pfVar1;
  float10 fVar2;
  float local_154;
  float local_150;
  float local_14c;
  uint local_148;
  float local_f0 [3];
  float local_e4 [3];
  float local_d8 [3];
  undefined4 local_cc [3];
  undefined4 local_c0 [3];
  float local_b4 [3];
  float local_a8 [3];
  undefined4 local_9c [3];
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  undefined4 local_74;
  int local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  float local_54;
  undefined4 local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34 [3];
  float local_28;
  float local_24;
  int local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10 [3];
  
  local_70 = 0;
  local_20 = get_ai_vehicle_behavior_state_block((int)param_1);
  local_50 = *(undefined4 *)(local_20 + 0xa980);
  local_58 = *(undefined4 *)(local_20 + 0xa984);
  fVar2 = (float10)world_object_geometry_context_helper_00458920((int)param_1);
  local_54 = (float)fVar2;
  fVar2 = (float10)world_object_geometry_context_helper_00458920(param_2);
  local_44 = (float)fVar2;
  get_world_object_damage_or_target_vectors((int)param_1,local_10,&local_74);
  get_world_object_damage_or_target_vectors(param_2,local_34,&local_48);
  pfVar1 = (float *)set_vec3_components(local_9c,local_50,0,local_58);
  local_6c = *pfVar1;
  local_68 = pfVar1[1];
  local_64 = pfVar1[2];
  transform_vec3_array_by_matrix(&local_6c,&local_6c,1,(float *)(param_2 + 0x18));
  pfVar1 = (float *)copy_transform_position_vec3(local_a8,(int)param_1 + 0x18);
  local_40 = *pfVar1;
  local_3c = pfVar1[1];
  local_38 = pfVar1[2];
  pfVar1 = (float *)vec3_subtract_xyz(local_b4,local_6c,local_68,local_64,local_40,local_3c,local_38
                                     );
  local_1c = *pfVar1;
  local_18 = pfVar1[1];
  local_14 = pfVar1[2];
  fVar2 = vec3_length(local_1c,local_18,local_14);
  local_28 = (float)fVar2;
  local_148 = (uint)(fVar2 < (float10)_DAT_004bcb68);
  *(uint *)(local_20 + 0xa988) = local_148;
  if (_DAT_004bcb6c <= local_28) {
    fVar2 = (float10)_CIatan2();
    local_78 = (float)fVar2;
  }
  else {
    local_78 = local_54;
  }
  local_70 = get_vehicle_runtime_context((int)param_1);
  update_ai_vehicle_steering_control((int)param_1,local_78);
  fVar2 = normalize_angle_delta_signed_pi(local_54,local_78);
  local_4c = (float)fVar2;
  if (_DAT_004bcae4 <= local_48) {
    if ((float)_DAT_004bcb78 <= ABS(*(float *)(local_70 + 0xe0))) {
      if ((_DAT_004bcb94 <= local_28) || (local_48 <= _DAT_004bcb28)) {
        fVar2 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
        set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar2);
      }
      else {
        pfVar1 = (float *)copy_object_local_translation_vec3(local_c0,(int)param_1 + 0x18);
        local_84 = *pfVar1;
        local_80 = pfVar1[1];
        local_7c = pfVar1[2];
        pfVar1 = (float *)copy_object_local_translation_vec3(local_cc,param_2 + 0x18);
        local_90 = *pfVar1;
        local_8c = pfVar1[1];
        local_88 = pfVar1[2];
        fVar2 = dot_product_vec3(&local_84,&local_90);
        local_5c = (float)fVar2;
        fVar2 = dot_product_vec3(&local_1c,&local_84);
        local_60 = (float)fVar2;
        if ((local_5c <= _DAT_004bcb90) || (_DAT_004bcae8 <= local_60)) {
          fVar2 = compute_line_closest_approach_parameter(&local_40,local_10,&local_6c,local_34);
          local_24 = (float)fVar2;
          if (local_24 <= _DAT_004bcae8) {
            fVar2 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
            set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar2);
          }
          else {
            set_ai_vehicle_throttle_brake_toward_speed(param_1,local_48 - _DAT_004bcb28);
          }
        }
        else {
          pfVar1 = (float *)scale_vec3_components
                                      (local_d8,_DAT_004bcb00 * local_28,local_90,local_8c,local_88)
          ;
          local_90 = *pfVar1;
          local_8c = pfVar1[1];
          local_88 = pfVar1[2];
          pfVar1 = (float *)add_vec3_components(local_e4,local_6c,local_68,local_64,local_90,
                                                local_8c,local_88);
          local_6c = *pfVar1;
          local_68 = pfVar1[1];
          local_64 = pfVar1[2];
          pfVar1 = (float *)vec3_subtract_xyz(local_f0,local_6c,local_68,local_64,local_40,local_3c,
                                              local_38);
          local_6c = *pfVar1;
          local_68 = pfVar1[1];
          local_64 = pfVar1[2];
          fVar2 = (float10)_CIatan2();
          local_78 = (float)fVar2;
          update_ai_vehicle_steering_control((int)param_1,local_78);
          set_ai_vehicle_throttle_brake_toward_speed(param_1,_DAT_004bcb98 * local_48);
        }
      }
    }
    else if (local_28 <= _DAT_004bcb80) {
      if (local_28 <= (float)_DAT_004bcb88) {
        if (_DAT_004bcae8 <= local_28 - _DAT_004bcae4) {
          local_154 = local_28 - _DAT_004bcae4;
        }
        else {
          local_154 = 0.0;
        }
        set_ai_vehicle_throttle_brake_toward_speed(param_1,local_154 * _DAT_004bcb70 + local_48);
      }
      else {
        if (_DAT_004bcae8 <= (local_28 - _DAT_004bcb30) * _DAT_004bcb90) {
          local_150 = (local_28 - _DAT_004bcb30) * _DAT_004bcb90;
        }
        else {
          local_150 = 0.0;
        }
        set_ai_vehicle_throttle_brake_toward_speed(param_1,local_48 + local_150);
      }
    }
    else {
      set_ai_vehicle_throttle_brake_toward_speed(param_1,1000.0);
    }
  }
  else if (_DAT_004bcb70 <= *(float *)(local_70 + 0xe0)) {
    fVar2 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar2);
  }
  else if (_DAT_004bcb00 <= local_28) {
    if (_DAT_004bcae8 <= (local_28 - _DAT_004bcae4) * _DAT_004bcad8) {
      local_14c = (local_28 - _DAT_004bcae4) * _DAT_004bcad8;
    }
    else {
      local_14c = 0.0;
    }
    set_ai_vehicle_throttle_brake_toward_speed(param_1,local_14c);
  }
  else {
    set_vehicle_brake_to_max_safe_value(param_1);
  }
  return;
}


