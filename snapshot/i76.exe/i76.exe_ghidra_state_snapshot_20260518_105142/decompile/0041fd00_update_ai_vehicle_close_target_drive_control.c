/*
 * Program: i76.exe
 * Function: update_ai_vehicle_close_target_drive_control
 * Entry: 0041fd00
 * Signature: undefined __cdecl update_ai_vehicle_close_target_drive_control(float param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: AI drive-control helper that steers and throttles toward a
   target using predicted target vectors and close-range speed rules. */

void __cdecl update_ai_vehicle_close_target_drive_control(float param_1,float param_2)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  float10 fVar6;
  float local_6c;
  float local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
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
  float local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c [3];
  
  fVar3 = param_2;
  local_54 = (float)*(double *)((int)param_1 + 0x40);
  local_50 = (float)*(double *)((int)param_1 + 0x48);
  local_4c = (float)*(double *)((int)param_1 + 0x50);
  local_30 = local_54;
  local_2c = local_50;
  local_28 = local_4c;
  pfVar4 = (float *)get_cached_world_object_aim_position(&local_18,(int)param_2);
  local_30 = *pfVar4;
  local_2c = pfVar4[1];
  local_28 = pfVar4[2];
  iVar5 = is_vehicle_or_actor_runtime_world_object((int)param_2);
  if (iVar5 == 0) {
    local_44 = local_2c - local_50;
    local_48 = (float)((float10)local_30 - (float10)local_54);
    local_40 = (float)((float10)local_28 - (float10)local_4c);
    fVar6 = (float10)fpatan((float10)local_30 - (float10)local_54,
                            (float10)local_28 - (float10)local_4c);
  }
  else {
    get_world_object_damage_or_target_vectors((int)param_1,&local_3c,&local_64);
    iVar5 = *(int *)(*(int *)((int)param_1 + 0x70) + 0x108);
    if (*(int *)(iVar5 + 0xa6f4) != 0) {
      local_60 = *(float *)(*(int *)(iVar5 + 0xa6f8) * 0x20 + 0xa74c + iVar5);
      local_5c = *(float *)((int)param_1 + 0x34) * local_60;
      local_58 = *(float *)((int)param_1 + 0x38) * local_60;
      local_60 = local_60 * *(float *)((int)param_1 + 0x30);
      local_44 = local_5c + local_38;
      local_48 = local_60 + local_3c;
      local_40 = local_58 + local_34;
      local_3c = local_48;
      local_38 = local_44;
      local_34 = local_40;
    }
    get_world_object_damage_or_target_vectors((int)param_2,local_c,&local_6c);
    fVar6 = compute_line_closest_approach_parameter(&local_54,&local_3c,&local_30,local_c);
    param_2 = (float)fVar6;
    if ((float10)_DAT_004bcbb0 <= fVar6) {
      if (_DAT_004bcbb4 < param_2) {
        param_2 = 5.0;
      }
    }
    else {
      param_2 = 0.01;
    }
    predict_world_object_position_at_time((int)fVar3,param_2,&local_24);
    local_48 = local_24 - local_54;
    local_44 = local_20 - local_50;
    local_40 = local_1c - local_4c;
    fVar6 = (float10)fpatan((float10)local_48,(float10)local_40);
  }
  local_68 = (float)fVar6;
  fVar2 = SQRT(local_40 * local_40 + local_44 * local_44 + local_48 * local_48) -
          (float)_DAT_004bcbb8;
  if (fVar2 < (float)_DAT_004bcbc0) {
    fVar2 = (float)_DAT_004bcbc0;
  }
  local_60 = local_48;
  local_5c = local_44;
  local_58 = local_40;
  update_ai_vehicle_steering_control((int)param_1,local_68);
  iVar5 = get_vehicle_runtime_context((int)param_1);
  bVar1 = ABS(*(float *)(iVar5 + 0xe0)) < (float)_DAT_004bcbd0;
  if (_DAT_004bcbc8 <= local_6c) {
    if (bVar1) {
      if (_DAT_004bcbe4 < fVar2) {
        set_ai_vehicle_throttle_brake_toward_speed(param_1,1000.0);
        return;
      }
      if (fVar2 < _DAT_004bcbc8) {
        set_ai_vehicle_throttle_brake_toward_speed(param_1,local_6c * _DAT_004bcbe8);
        return;
      }
      if ((float)_DAT_004bcbf0 < fVar2) {
        fVar3 = (fVar2 - _DAT_004bcbf8) * _DAT_004bcbfc;
        if (fVar3 < _DAT_004bcbe0) {
          fVar3 = _DAT_004bcbe0;
        }
        set_ai_vehicle_throttle_brake_toward_speed(param_1,local_6c + fVar3);
        return;
      }
      fVar3 = fVar2 - _DAT_004bcbc8;
      if (fVar2 - _DAT_004bcbc8 < _DAT_004bcbe0) {
        fVar3 = _DAT_004bcbe0;
      }
      set_ai_vehicle_throttle_brake_toward_speed(param_1,local_6c - fVar3 * _DAT_004bcc00);
      return;
    }
    if (fVar2 < _DAT_004bcc04) {
      local_44 = *(float *)((int)param_1 + 0x34);
      local_14 = *(float *)((int)fVar3 + 0x34);
      local_10 = *(float *)((int)fVar3 + 0x38);
      local_48 = *(float *)((int)param_1 + 0x30);
      local_40 = *(float *)((int)param_1 + 0x38);
      if ((_DAT_004bcbfc <
           local_10 * local_40 + local_14 * local_44 + *(float *)((int)fVar3 + 0x30) * local_48) &&
         (local_40 * local_58 + local_44 * local_5c + local_48 * local_60 < _DAT_004bcbe0)) {
        set_ai_vehicle_throttle_brake_toward_speed(param_1,local_6c * _DAT_004bcc08);
        return;
      }
      if (_DAT_004bcbe0 < param_2) {
        set_ai_vehicle_throttle_brake_toward_speed(param_1,local_6c - _DAT_004bcbb4);
        return;
      }
    }
  }
  else if (bVar1) {
    if (fVar2 < _DAT_004bcbd8) {
      set_vehicle_brake_to_max_safe_value(param_1);
      return;
    }
    fVar3 = (fVar2 - _DAT_004bcbc8) * _DAT_004bcbdc;
    if (fVar3 < _DAT_004bcbe0) {
      set_ai_vehicle_throttle_brake_toward_speed(param_1,0.0);
      return;
    }
    set_ai_vehicle_throttle_brake_toward_speed(param_1,fVar3);
    return;
  }
  fVar6 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
  set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar6);
  return;
}


