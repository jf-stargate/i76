/*
 * Program: i76.exe
 * Function: update_ai_vehicle_pursuit_path_control
 * Entry: 0041b6e0
 * Signature: undefined __cdecl update_ai_vehicle_pursuit_path_control(float * param_1, int param_2, float param_3, float param_4, float * param_5, int param_6, float param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: High-level AI pursuit/path-control update that uses
   target selection, tire grip, drive/brake limits, and steering/throttle helpers. */

void __cdecl
update_ai_vehicle_pursuit_path_control
          (float *param_1,int param_2,float param_3,float param_4,float *param_5,int param_6,
          float param_7)

{
  float fVar1;
  bool bVar2;
  float *pfVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float10 fVar8;
  float local_5c;
  float local_58;
  float local_54;
  float *local_50;
  float local_4c;
  uint local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_20;
  float local_1c;
  undefined4 local_18 [3];
  undefined4 local_c [3];
  
  iVar5 = param_2;
  pfVar3 = param_1;
  fVar1 = *(float *)(param_2 + 0xe0);
  local_3c = *(float *)(param_2 + 0xe0);
  local_50 = (float *)0x7f7fffff;
  local_38 = fVar1;
  fVar8 = compute_vehicle_tire_grip_control_scalar((int)param_1);
  local_44 = (float)fVar8;
  local_58 = 0.5;
  get_world_object_damage_or_target_vectors((int)pfVar3,local_c,&local_34);
  fVar4 = param_4;
  if (param_4 == 0.0) {
    if (local_34 <= _DAT_004bca7c) goto LAB_0041b7f1;
    param_4 = 1.4013e-45;
  }
  else {
    iVar6 = is_vehicle_or_actor_runtime_world_object((int)param_4);
    if (iVar6 == 0) {
      if (local_34 <= _DAT_004bca7c) goto LAB_0041b7f1;
      param_4 = 1.4013e-45;
    }
    else {
      local_20 = *(float *)((int)fVar4 + 0x34);
      local_2c = pfVar3[0xd];
      local_1c = *(float *)((int)fVar4 + 0x38);
      local_30 = pfVar3[0xc];
      local_28 = pfVar3[0xe];
      if (local_1c * local_28 + local_20 * local_2c + *(float *)((int)fVar4 + 0x30) * local_30 <=
          (float)_DAT_004bca80) {
LAB_0041b7f1:
        param_4 = 0.0;
      }
      else {
        param_4 = 1.4013e-45;
      }
    }
  }
  fVar8 = get_gameplay_runtime_seconds();
  if ((float10)*(float *)((int)param_3 + 0x9d34) <= fVar8) {
    if ((float)_DAT_004bc970 <= local_3c) goto LAB_0041b82f;
    bVar2 = true;
  }
  else if (local_3c <= (float)_DAT_004bc970) {
LAB_0041b82f:
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (ABS(local_3c) < (float)_DAT_004bca88) {
    fVar8 = get_ai_vehicle_damage_state_speed_scalar((int)pfVar3);
    set_ai_vehicle_throttle_brake_toward_speed
              ((float)pfVar3,
               (float)(fVar8 * (float10)_DAT_004bca90 -
                      (float10)*(float *)(iVar5 + 0xac) * (float10)_DAT_004bca94));
    fVar4 = param_7;
    iVar6 = param_6;
    fVar1 = *(float *)(iVar5 + 0xe4);
    local_5c = 0.25;
    param_4 = fVar1;
    if (_DAT_004bc9d0 <= local_44) {
      do {
        iVar5 = select_ai_vehicle_target_or_path_candidate
                          (pfVar3,local_5c,fVar1,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                           &local_4c);
        param_1 = (float *)(_DAT_004bca98 - local_54);
        fVar7 = local_5c;
        if (iVar5 == 0) goto LAB_0041c065;
        if ((float)param_1 <= (float)local_50) {
          local_38 = local_5c;
          local_58 = local_54;
          local_50 = param_1;
        }
        param_7 = -local_5c;
        iVar5 = select_ai_vehicle_target_or_path_candidate
                          (pfVar3,param_7,fVar1,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                           &local_4c);
        param_1 = (float *)(_DAT_004bca98 - local_54);
        if (iVar5 == 0) {
          *(float *)(param_2 + 0xe0) = -local_5c;
          param_7 = param_4;
          goto LAB_0041c0a0;
        }
        if ((float)param_1 <= (float)local_50) {
          local_38 = param_7;
          local_58 = local_54;
          local_50 = param_1;
        }
        local_5c = local_5c - _DAT_004bca9c;
        iVar5 = param_2;
      } while (local_5c <= local_44);
    }
    *param_5 = local_58;
    *(float *)(iVar5 + 0xe0) = local_38;
    return;
  }
  if (bVar2) {
    if (fVar4 == 0.0) {
      local_40 = 0.0;
    }
    else {
      iVar6 = is_vehicle_or_actor_runtime_world_object((int)fVar4);
      if (iVar6 == 0) {
        local_40 = 0.0;
      }
      else {
        get_world_object_damage_or_target_vectors((int)fVar4,local_18,&local_40);
      }
    }
    fVar4 = param_7;
    iVar6 = param_6;
    if ((local_40 <= _DAT_004bc9b4) || (param_4 != 0.0)) {
      fVar8 = get_ai_vehicle_damage_state_speed_scalar((int)pfVar3);
      fVar1 = _DAT_004bc9f8;
      fVar7 = _DAT_004bca0c;
      if (fVar8 < (float10)*(float *)(iVar5 + 0xac)) {
        fVar1 = _DAT_004bca94;
        fVar7 = _DAT_004bca90;
      }
      set_ai_vehicle_throttle_brake_toward_speed
                ((float)pfVar3,
                 (float)(fVar8 * (float10)fVar7 - (float10)*(float *)(iVar5 + 0xac) * (float10)fVar1
                        ));
      param_4 = *(float *)(iVar5 + 0xe4);
    }
    else {
      param_7 = 0.0;
      do {
        iVar5 = select_ai_vehicle_target_or_path_candidate
                          (pfVar3,fVar1,param_7,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                           &local_4c);
        if (iVar5 == 0) goto LAB_0041bb7b;
        if ((float)param_1 < (float)local_50) {
          local_50 = param_1;
          param_4 = param_7;
          local_58 = local_54;
        }
        param_7 = param_7 - _DAT_004bcaa0;
      } while (param_7 <= _DAT_004bc91c);
      fVar8 = solve_vehicle_max_drive_brake_delta((float)pfVar3,-1.0);
      param_3 = (float)fVar8;
      param_7 = -0.2;
      if (fVar8 <= (float10)_DAT_004bcaa0) {
        do {
          iVar5 = select_ai_vehicle_target_or_path_candidate
                            (pfVar3,fVar1,param_7,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                             &local_4c);
          if (iVar5 == 0) goto LAB_0041bb7b;
          if ((float)param_1 < (float)local_50) {
            local_50 = param_1;
            param_4 = param_7;
            local_58 = local_54;
          }
          param_7 = param_7 - _DAT_004bc9c8;
        } while (param_3 <= param_7);
      }
    }
    fVar1 = param_4;
    local_5c = local_3c - _DAT_004bca9c;
    if (local_5c <= local_44) {
      do {
        iVar5 = select_ai_vehicle_target_or_path_candidate
                          (pfVar3,local_5c,fVar1,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                           &local_4c);
        fVar7 = local_5c;
        if (iVar5 == 0) goto LAB_0041c065;
        if ((float)param_1 <= (float)local_50) {
          local_50 = param_1;
          local_58 = local_54;
        }
        local_5c = local_5c - _DAT_004bca9c;
      } while (local_5c <= local_44);
    }
    local_5c = local_3c - _DAT_004bc9d0;
    param_7 = -local_44;
    fVar7 = local_44;
    if (param_7 <= local_5c) {
      do {
        iVar5 = select_ai_vehicle_target_or_path_candidate
                          (pfVar3,local_5c,fVar1,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                           &local_4c);
        if (iVar5 == 0) goto LAB_0041c08e;
        if ((float)param_1 <= (float)local_50) {
          local_50 = param_1;
          local_58 = local_54;
        }
        local_5c = local_5c - _DAT_004bc9d0;
        fVar7 = local_44;
      } while (param_7 <= local_5c);
    }
  }
  else {
    if (fVar4 == 0.0) {
      local_40 = 0.0;
    }
    else {
      iVar6 = is_vehicle_or_actor_runtime_world_object((int)fVar4);
      if (iVar6 == 0) {
        local_40 = 0.0;
      }
      else {
        get_world_object_damage_or_target_vectors((int)fVar4,local_18,&local_40);
      }
    }
    fVar8 = solve_vehicle_max_drive_brake_delta((float)pfVar3,1.0);
    fVar4 = param_7;
    iVar6 = param_6;
    param_3 = (float)fVar8;
    if ((local_40 <= _DAT_004bc9b4) || (param_4 != 0.0)) {
      fVar8 = get_ai_vehicle_damage_state_speed_scalar((int)pfVar3);
      fVar1 = _DAT_004bc9f8;
      fVar7 = _DAT_004bca0c;
      if (fVar8 < (float10)*(float *)(iVar5 + 0xac)) {
        fVar1 = _DAT_004bca94;
        fVar7 = _DAT_004bca90;
      }
      set_ai_vehicle_throttle_brake_toward_speed
                ((float)pfVar3,
                 (float)(fVar8 * (float10)fVar7 - (float10)*(float *)(iVar5 + 0xac) * (float10)fVar1
                        ));
      param_4 = *(float *)(iVar5 + 0xe4);
    }
    else {
      param_7 = 0.0;
      if (_DAT_004bc914 <= param_3) {
        do {
          iVar5 = select_ai_vehicle_target_or_path_candidate
                            (pfVar3,fVar1,param_7,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                             &local_4c);
          if (iVar5 == 0) goto LAB_0041bed0;
          if ((float)param_1 < (float)local_50) {
            local_50 = param_1;
            param_4 = param_7;
            local_58 = local_54;
          }
          param_7 = param_7 - _DAT_004bcaa0;
        } while (param_7 <= param_3);
      }
      fVar8 = solve_vehicle_max_drive_brake_delta((float)pfVar3,-1.0);
      param_3 = (float)fVar8;
      param_7 = -0.2;
      if (fVar8 <= (float10)_DAT_004bcaa0) {
        do {
          iVar5 = select_ai_vehicle_target_or_path_candidate
                            (pfVar3,fVar1,param_7,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                             &local_4c);
          if (iVar5 == 0) goto LAB_0041bed0;
          if ((float)param_1 < (float)local_50) {
            local_50 = param_1;
            param_4 = param_7;
            local_58 = local_54;
          }
          param_7 = param_7 - _DAT_004bc9c8;
        } while (param_3 <= param_7);
      }
    }
    fVar1 = param_4;
    local_5c = local_3c - _DAT_004bc9d0;
    param_7 = -local_44;
    if (param_7 <= local_5c) {
      do {
        iVar5 = select_ai_vehicle_target_or_path_candidate
                          (pfVar3,local_5c,fVar1,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                           &local_4c);
        if (iVar5 == 0) goto LAB_0041c08e;
        if ((float)param_1 <= (float)local_50) {
          local_50 = param_1;
          local_58 = local_54;
        }
        local_5c = local_5c - _DAT_004bc9d0;
      } while (param_7 <= local_5c);
    }
    local_5c = local_3c - _DAT_004bca9c;
    fVar7 = param_7;
    if (local_5c <= local_44) {
      do {
        iVar5 = select_ai_vehicle_target_or_path_candidate
                          (pfVar3,local_5c,fVar1,&local_48,&param_1,&local_54,iVar6,(int)fVar4,
                           &local_4c);
        fVar7 = local_5c;
        if (iVar5 == 0) break;
        if ((float)param_1 <= (float)local_50) {
          local_50 = param_1;
          local_58 = local_54;
        }
        local_5c = local_5c - _DAT_004bca9c;
        fVar7 = param_7;
      } while (local_5c <= local_44);
    }
  }
LAB_0041c065:
  *(float *)(param_2 + 0xe0) = fVar7;
LAB_0041c073:
  *(float *)(param_2 + 0xe4) = param_4;
  *param_5 = local_58;
  return;
LAB_0041bed0:
  *(float *)(param_2 + 0xe0) = fVar1;
  goto LAB_0041c0a0;
LAB_0041bb7b:
  *(float *)(param_2 + 0xe0) = fVar1;
  param_4 = param_7;
  goto LAB_0041c073;
LAB_0041c08e:
  *(float *)(param_2 + 0xe0) = local_5c;
  param_7 = param_4;
LAB_0041c0a0:
  *(float *)(param_2 + 0xe4) = param_7;
  *param_5 = local_58;
  return;
}


