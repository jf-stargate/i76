/*
 * Program: i76.exe
 * Function: set_ai_vehicle_throttle_brake_toward_speed
 * Entry: 0040f9c0
 * Signature: undefined __cdecl set_ai_vehicle_throttle_brake_toward_speed(float param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Computes AI throttle/brake command toward target speed using wheel traction,
   engine force, brake force, and safe drive/brake limits. */

void __cdecl set_ai_vehicle_throttle_brake_toward_speed(float param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  float10 fVar12;
  undefined4 local_c [3];
  
  fVar8 = param_1;
  if (param_1 == DAT_005244c8) {
    DAT_005244c4 = 1;
  }
  if (*(int *)((int)param_1 + 0x6c) == 9) {
    get_world_object_damage_or_target_vectors((int)param_1,local_c,&param_1);
    get_runtime_update_delta_seconds();
    fVar6 = param_1 * param_1 * _DAT_004bc720;
    fVar12 = mission_flow_map_context_helper_0049c7b0();
    fVar12 = (((float10)param_2 - (float10)param_1) * fVar12 * (float10)_DAT_004bc724 +
             (float10)fVar6) * (float10)_DAT_004bc728;
    param_2 = (float)fVar12;
    if ((float10)_DAT_004bc72c <= fVar12) {
      if (_DAT_004bc714 < param_2) {
        param_2 = 0.999;
      }
    }
    else {
      param_2 = -0.999;
    }
    iVar9 = get_vehicle_runtime_context((int)fVar8);
    *(float *)(iVar9 + 0xe4) = param_2;
    return;
  }
  iVar9 = get_vehicle_runtime_context((int)param_1);
  fVar12 = mission_flow_map_context_helper_0049c7b0();
  param_1 = *(float *)(iVar9 + 0xac);
  param_2 = (param_2 - param_1) * (float)fVar12;
  iVar10 = get_vehicle_damage_event_state_block(iVar9);
  fVar6 = *(float *)(iVar10 + 0xa81c);
  if (_DAT_004bc710 <= param_2) {
    param_2 = fVar6 * param_2;
  }
  fVar5 = _DAT_004bc710;
  if (_DAT_004bc714 <= *(float *)(iVar9 + 0xac)) {
    fVar7 = *(float *)(iVar9 + 0x46c) * _DAT_004bc718;
    fVar5 = *(float *)(iVar9 + 0x120) * *(float *)(iVar9 + 0xac) * *(float *)(iVar9 + 0xac) *
            _DAT_004bc71c;
    iVar10 = get_vehicle_rear_right_tire_runtime_component(iVar9);
    iVar11 = get_vehicle_rear_left_tire_runtime_component(iVar9);
    fVar1 = *(float *)(iVar10 + 0x14);
    fVar2 = *(float *)(iVar11 + 0x14);
    iVar10 = get_vehicle_front_right_tire_runtime_component(iVar9);
    fVar3 = *(float *)(iVar10 + 0x14);
    iVar10 = get_vehicle_front_left_tire_runtime_component(iVar9);
    fVar4 = *(float *)(iVar10 + 0x14);
    fVar12 = get_terrain_material_primary_scalar(*(int *)(iVar9 + 0x45c));
    fVar5 = fVar5 - (float)(fVar12 * (float10)(fVar1 + fVar2 + fVar3 + fVar4) * (float10)fVar7);
  }
  param_2 = param_2 - fVar5;
  if (_DAT_004bc710 < param_2) {
    fVar12 = get_engine_component_drive_force_scalar(*(int *)(*(int *)(iVar9 + 0x3c4) + 0x70));
    fVar5 = *(float *)(iVar9 + 0x128) * (float)(fVar12 * (float10)*(float *)(iVar9 + 0xa8));
    if ((*(uint *)(iVar9 + 0x454) & 0x800) != 0) {
      fVar5 = fVar5 * _DAT_004bc74c;
    }
    if (_DAT_004bc714 < param_1) {
      fVar5 = fVar5 * *(float *)(iVar9 + 0xb0);
    }
    if (fVar5 < _DAT_004bc744) {
      fVar5 = _DAT_004bc744;
    }
    param_2 = param_2 / fVar5;
  }
  else {
    iVar10 = get_vehicle_brake_runtime_component(iVar9);
    fVar5 = *(float *)(iVar10 + 0x10);
    if ((fVar5 <= _DAT_004bc740) || (_DAT_004bc744 <= fVar5)) {
      param_2 = param_2 / (fVar5 * _DAT_004bc748);
    }
    else {
      param_2 = 1.0;
    }
  }
  if (_DAT_004bc710 <= param_2) {
    fVar6 = _DAT_004bc758 - fVar6 * _DAT_004bc754;
    if (fVar6 < param_2) {
      param_2 = fVar6;
    }
    fVar12 = solve_vehicle_max_drive_brake_delta(fVar8,1.0);
    if (fVar12 * (float10)_DAT_004bc750 < (float10)param_2) {
      *(float *)(iVar9 + 0xe4) = (float)(fVar12 * (float10)_DAT_004bc750);
      return;
    }
  }
  else {
    fVar12 = solve_vehicle_max_drive_brake_delta(fVar8,-1.0);
    if ((float10)param_2 < fVar12 * (float10)_DAT_004bc750) {
      *(float *)(iVar9 + 0xe4) = (float)(fVar12 * (float10)_DAT_004bc750);
      return;
    }
  }
  *(float *)(iVar9 + 0xe4) = param_2;
  return;
}


