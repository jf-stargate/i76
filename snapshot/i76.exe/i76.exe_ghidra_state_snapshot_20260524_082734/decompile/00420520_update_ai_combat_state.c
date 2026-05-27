/*
 * Program: i76.exe
 * Function: update_ai_combat_state
 * Entry: 00420520
 * Signature: undefined __cdecl update_ai_combat_state(float param_1, float param_2, float param_3, undefined4 param_4, int param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: Unknown ai combat state */

void __cdecl
update_ai_combat_state(float param_1,float param_2,float param_3,float param_4,int param_5)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fStack_18;
  float fStack_14;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar2 = get_vehicle_runtime_context((int)param_1);
  get_vehicle_damage_event_state_block(iVar2);
  fVar5 = (float10)world_object_geometry_context_helper_00458920((int)param_1);
  fVar7 = (float)fVar5;
  fVar5 = (float10)world_object_geometry_context_helper_004589d0((uint)param_1,(uint)param_2);
  iVar2 = world_object_geometry_context_helper_00458a30(fVar7,(float)fVar5);
  get_world_object_damage_or_target_vectors((int)param_2,&uStack_4,&uStack_8);
  iVar3 = is_vehicle_or_actor_runtime_world_object((int)param_2);
  if (iVar3 == 0) {
    fStack_18 = 0.0;
    param_4 = 0.0;
LAB_004205e8:
    iVar3 = 4;
  }
  else {
    iVar3 = get_vehicle_runtime_context((int)param_2);
    fVar5 = (float10)world_object_geometry_context_helper_00458920((int)param_2);
    fStack_18 = (float)fVar5;
    fVar5 = (float10)world_object_geometry_context_helper_004589d0((uint)param_2,(uint)param_1);
    param_4 = (float)fVar5;
    if ((*(byte *)(iVar3 + 0x454) & 2) != 0) goto LAB_004205e8;
    iVar3 = world_object_geometry_context_helper_00458a30(fStack_18,param_4);
  }
  fVar5 = (float10)world_object_geometry_context_helper_004589f0((uint)param_1,(uint)param_2);
  fVar6 = (float)fVar5;
  if ((float10)_DAT_004bcc38 <= fVar5) {
    if ((float10)_DAT_004bcc5c <= fVar5) {
      iVar4 = 4;
    }
    else if ((float10)_DAT_004bcc24 <= fVar5) {
      iVar4 = 3;
    }
    else {
      iVar4 = 2;
    }
  }
  else if ((float10)_DAT_004bcc58 <= fVar5) {
    iVar4 = 1;
  }
  else {
    iVar4 = 0;
  }
  switch((&DAT_004ed020)[(iVar2 + (iVar4 + param_5 * 5) * 8) * 8 + iVar3]) {
  case 0:
    fVar5 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    fVar7 = (float)fVar5;
    break;
  case 1:
    fVar7 = 1000.0;
    break;
  case 2:
    fVar5 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    fVar7 = (float)fVar5;
    goto LAB_0042069b;
  case 3:
    fVar7 = 1000.0;
LAB_0042069b:
    set_ai_vehicle_throttle_brake_toward_speed(param_1,fVar7);
    update_ai_vehicle_steering_control((int)param_1,param_3 - _DAT_004bcc10);
    return;
  case 4:
    update_ai_vehicle_close_target_drive_control(param_1,param_2);
    return;
  case 5:
    update_ai_vehicle_full_throttle_intercept_control(param_1,(int)param_2);
    return;
  case 6:
    update_ai_vehicle_target_approach_control(param_1,param_2,fVar7,fVar6);
    return;
  case 7:
    fVar5 = normalize_angle_delta_signed_pi(fVar7,fStack_14);
    if ((float10)_DAT_004bcc30 <= ABS(fVar5)) {
      fVar5 = normalize_angle_delta_signed_pi(fStack_18,param_4);
      fVar7 = 1000.0;
      if ((float10)_DAT_004bcbe0 <= fVar5) goto LAB_0042069b;
    }
    else {
      fVar5 = normalize_angle_delta_signed_pi(fStack_18,param_4);
      fVar7 = 1000.0;
      if (fVar5 <= (float10)_DAT_004bcbe0) goto LAB_0042069b;
    }
    break;
  case 8:
    fVar5 = normalize_angle_delta_signed_pi(fVar7,fStack_14);
    update_ai_vehicle_close_target_drive_control(param_1,param_2);
    if (_DAT_004bcc38 <= fVar6) {
      return;
    }
    bVar1 = (float)ABS(fVar5) < (float)_DAT_004bcc40;
    goto LAB_00420736;
  default:
    report_error();
    return;
  case 10:
    fVar6 = 1000.0;
    goto LAB_004207a2;
  case 0xb:
    fVar5 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    fVar6 = (float)fVar5;
LAB_004207a2:
    set_ai_vehicle_throttle_brake_toward_speed(param_1,fVar6);
    update_ai_vehicle_steering_control((int)param_1,fVar7);
    return;
  case 0xc:
  case 0xd:
    goto switchD_00420670_caseD_c;
  case 0xe:
    fVar5 = normalize_angle_delta_signed_pi(fVar7,fStack_14);
    update_ai_vehicle_close_target_drive_control(param_1,param_2);
    if (_DAT_004bcc4c <= fVar6) {
      return;
    }
    bVar1 = (float)ABS(fVar5) < (float)_DAT_004bcc50;
LAB_00420736:
    if (bVar1) {
      set_vehicle_brake_to_max_safe_value(param_1);
      return;
    }
switchD_00420670_caseD_c:
    return;
  }
  set_ai_vehicle_throttle_brake_toward_speed(param_1,fVar7);
  update_ai_vehicle_steering_control((int)param_1,param_3 - _DAT_004bcc0c);
  return;
}


