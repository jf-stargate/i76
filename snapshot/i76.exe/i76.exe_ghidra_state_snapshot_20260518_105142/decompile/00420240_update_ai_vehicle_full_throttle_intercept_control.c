/*
 * Program: i76.exe
 * Function: update_ai_vehicle_full_throttle_intercept_control
 * Entry: 00420240
 * Signature: undefined __cdecl update_ai_vehicle_full_throttle_intercept_control(float param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: AI drive-control helper that steers toward a
   predicted/intercept target and commands high throttle. */

void __cdecl update_ai_vehicle_full_throttle_intercept_control(float param_1,int param_2)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  undefined4 local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30 [2];
  float local_28;
  float local_24 [3];
  float local_18 [3];
  undefined4 local_c [2];
  float local_4;
  
  iVar2 = param_2;
  fVar1 = param_1;
  local_48 = (float)*(double *)((int)param_1 + 0x40);
  local_44 = (float)*(double *)((int)param_1 + 0x48);
  local_40 = (float)*(double *)((int)param_1 + 0x50);
  local_3c = local_48;
  local_38 = local_44;
  local_34 = local_40;
  pfVar3 = (float *)get_cached_world_object_aim_position(local_c,param_2);
  local_3c = *pfVar3;
  local_38 = pfVar3[1];
  local_34 = pfVar3[2];
  iVar4 = is_vehicle_or_actor_runtime_world_object(iVar2);
  if (iVar4 == 0) {
    fVar5 = (float10)local_3c - (float10)local_48;
    fVar6 = (float10)local_34 - (float10)local_40;
  }
  else {
    get_world_object_damage_or_target_vectors((int)param_1,local_18,&param_2);
    get_world_object_damage_or_target_vectors(iVar2,local_24,&local_4c);
    fVar5 = compute_line_closest_approach_parameter(&local_48,local_18,&local_3c,local_24);
    param_1 = (float)fVar5;
    if ((float10)_DAT_004bcbb0 <= fVar5) {
      if (_DAT_004bcbb4 < param_1) {
        param_1 = 5.0;
      }
    }
    else {
      param_1 = 0.01;
    }
    predict_world_object_position_at_time(iVar2,param_1,local_30);
    fVar5 = (float10)local_30[0] - (float10)local_48;
    fVar6 = (float10)local_28 - (float10)local_40;
  }
  local_4 = (float)fVar6;
  fVar5 = (float10)fpatan(fVar5,fVar6);
  get_vehicle_runtime_context((int)fVar1);
  set_ai_vehicle_throttle_brake_toward_speed(fVar1,1000.0);
  update_ai_vehicle_steering_control((int)fVar1,(float)fVar5);
  return;
}


