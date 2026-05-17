/*
 * Program: i76.exe
 * Function: update_ai_vehicle_target_approach_control
 * Entry: 004203a0
 * Signature: undefined __cdecl update_ai_vehicle_target_approach_control(float param_1, float param_2, float param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Computes relative target approach and selects AI steering/throttle behavior. */

void __cdecl
update_ai_vehicle_target_approach_control(float param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  float10 fVar4;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18 [3];
  undefined4 local_c [3];
  
  fVar1 = param_1;
  iVar2 = get_vehicle_runtime_context((int)param_1);
  pfVar3 = (float *)predict_ai_target_lead_position_for_weapon_fire(local_18,param_1,param_2);
  local_24 = *pfVar3;
  local_20 = pfVar3[1];
  local_1c = pfVar3[2];
  if (((float)_DAT_004bcc18 <= ABS(local_24)) || ((float)_DAT_004bcc18 <= ABS(local_1c))) {
    fVar4 = (float10)fpatan((float10)local_24,(float10)local_1c);
    param_1 = (float)fVar4;
  }
  else {
    param_1 = param_3;
  }
  update_ai_vehicle_steering_control((int)fVar1,param_1);
  get_world_object_damage_or_target_vectors((int)param_2,local_c,&local_28);
  if (_DAT_004bcbc8 <= local_28) {
    if (ABS(*(float *)(iVar2 + 0xe4)) <= (float)_DAT_004bcbd0) {
      set_ai_vehicle_throttle_brake_toward_speed
                (fVar1,SQRT(local_1c * local_1c + local_20 * local_20 + local_24 * local_24));
      return;
    }
  }
  else {
    fVar4 = normalize_angle_delta_signed_pi(param_3,param_1);
    if (ABS(fVar4) < (float10)_DAT_004bcc20) {
      if (param_4 < _DAT_004bcc24) {
        set_vehicle_brake_to_max_safe_value(fVar1);
        return;
      }
      set_ai_vehicle_throttle_brake_toward_speed(fVar1,(param_4 - _DAT_004bcc24) * _DAT_004bcc28);
      return;
    }
  }
  fVar4 = get_ai_vehicle_damage_state_speed_scalar((int)fVar1);
  set_ai_vehicle_throttle_brake_toward_speed(fVar1,(float)fVar4);
  return;
}


