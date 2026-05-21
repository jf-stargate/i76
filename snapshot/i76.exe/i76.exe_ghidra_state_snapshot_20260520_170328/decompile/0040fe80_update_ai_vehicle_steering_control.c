/*
 * Program: i76.exe
 * Function: update_ai_vehicle_steering_control
 * Entry: 0040fe80
 * Signature: undefined __cdecl update_ai_vehicle_steering_control(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Updates AI vehicle steering command from target heading, traction, tire contact,
   and frame delta. */

void __cdecl update_ai_vehicle_steering_control(int param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float10 fVar11;
  float10 fVar12;
  
  if (*(int *)(param_1 + 0x6c) == 9) {
    set_ai_vehicle_steering_toward_heading(param_1,param_2);
    return;
  }
  iVar7 = get_vehicle_runtime_context(param_1);
  iVar8 = get_vehicle_suspension_runtime_component(iVar7);
  if ((*(byte *)(iVar7 + 0x454) & 4) != 0) {
    *(undefined4 *)(iVar7 + 0xe0) = 0;
    return;
  }
  fVar11 = get_runtime_update_delta_seconds();
  if (fVar11 < (float10)_DAT_004bc780) {
    *(undefined4 *)(iVar7 + 0xe0) = 0;
  }
  fVar4 = *(float *)(iVar7 + 0xac);
  if ((_DAT_004bc740 < fVar4) && (fVar4 < _DAT_004bc744)) {
    *(undefined4 *)(iVar7 + 0xe0) = 0;
    return;
  }
  fVar12 = (float10)world_object_geometry_context_helper_00458920(param_1);
  fVar12 = normalize_angle_delta_signed_pi((float)fVar12,param_2);
  iVar9 = get_vehicle_damage_event_state_block(iVar7);
  fVar6 = *(float *)(iVar9 + 0xa820) * (float)-fVar12;
  fVar5 = *(float *)(iVar7 + 0x110);
  iVar9 = get_vehicle_front_left_tire_runtime_component(iVar7);
  iVar10 = get_vehicle_front_right_tire_runtime_component(iVar7);
  fVar1 = *(float *)(iVar9 + 0xc);
  fVar2 = *(float *)(iVar10 + 0xc);
  iVar9 = get_vehicle_rear_left_tire_runtime_component(iVar7);
  fVar3 = *(float *)(iVar9 + 0xc);
  iVar9 = get_vehicle_rear_right_tire_runtime_component(iVar7);
  fVar1 = fVar1 + fVar2 + fVar3 + *(float *)(iVar9 + 0xc);
  fVar12 = get_vehicle_effective_terrain_friction_scalar(iVar7);
  fVar12 = fVar12 * (float10)*(float *)(iVar7 + 0x46c) * (float10)*(float *)(iVar8 + 0x14) *
           (float10)fVar1 * (float10)_DAT_004bc718;
  if ((*(uint *)(iVar7 + 0x454) & 0x10000) == 0) {
    fVar12 = (float10)fVar1 * (float10)_DAT_004bc738;
  }
  if (fVar12 < (float10)_DAT_004bc784) {
    *(undefined4 *)(iVar7 + 0xe0) = 0;
    return;
  }
  if ((float10)fVar5 * (float10)fVar4 * (float10)fVar4 <= fVar12) {
    fVar11 = (float10)fVar6 / ((float10)(float)fVar11 * (float10)fVar5 * (float10)fVar4);
  }
  else {
    fVar11 = ((float10)fVar6 * (float10)fVar4) / (fVar12 * (float10)(float)fVar11);
  }
  fVar4 = (float)fVar11;
  fVar11 = compute_vehicle_tire_grip_control_scalar(param_1);
  fVar1 = (float)fVar11;
  if ((float)_DAT_004bc788 <= fVar4) {
    if (fVar1 < fVar4) {
      fVar4 = fVar1;
    }
    if (_DAT_004bc750 < fVar4) {
      fVar4 = _DAT_004bc750;
    }
  }
  else {
    if (fVar4 < -fVar1) {
      fVar4 = -fVar1;
    }
    if (fVar4 < _DAT_004bc790) {
      fVar4 = _DAT_004bc790;
    }
  }
  *(float *)(iVar7 + 0xe0) = *(float *)(iVar7 + 0xe8) * fVar4;
  return;
}


