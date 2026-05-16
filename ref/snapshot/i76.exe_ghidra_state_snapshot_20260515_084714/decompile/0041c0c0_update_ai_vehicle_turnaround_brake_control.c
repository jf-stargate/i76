/*
 * Program: i76.exe
 * Function: update_ai_vehicle_turnaround_brake_control
 * Entry: 0041c0c0
 * Signature: undefined __cdecl update_ai_vehicle_turnaround_brake_control(float param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Updates steering sign, braking, and timed turnaround
   state using tire grip and current speed. */

void __cdecl update_ai_vehicle_turnaround_brake_control(float param_1,int param_2,int param_3)

{
  bool bVar1;
  float fVar2;
  float10 fVar3;
  undefined4 uVar4;
  
  fVar3 = compute_vehicle_tire_grip_control_scalar((int)param_1);
  bVar1 = _DAT_004bc914 <= *(float *)(param_2 + 0xe0);
  if (_DAT_004bc914 <= *(float *)(param_2 + 0xe8)) {
    if (!bVar1) {
      fVar3 = fVar3 * (float10)_DAT_004bc940;
      goto LAB_0041c114;
    }
  }
  else if (bVar1) {
    fVar3 = fVar3 * (float10)_DAT_004bc940;
    goto LAB_0041c114;
  }
  fVar3 = fVar3 * (float10)_DAT_004bcaa4;
LAB_0041c114:
  *(float *)(param_2 + 0xe0) = (float)fVar3;
  if (*(float *)(param_2 + 0xac) <= (float)_DAT_004bcaa8) {
    fVar3 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar3);
  }
  else {
    set_vehicle_brake_to_max_safe_value(param_1);
  }
  fVar2 = *(float *)(param_2 + 0xe8) - _DAT_004bc91c;
  if ((fVar2 <= _DAT_004bc934) || (_DAT_004bc938 <= fVar2)) {
    *(undefined4 *)(param_2 + 0xe8) = 0x3f800000;
    uVar4 = 3;
  }
  else {
    *(undefined4 *)(param_2 + 0xe8) = 0xbf800000;
    uVar4 = 1;
  }
  vehicle_specials_state_getter_helper_00467370((int)param_1,uVar4);
  fVar3 = get_runtime_time_seconds();
  *(float *)(param_3 + 0x9d34) = (float)(fVar3 - (float10)_DAT_004bca38);
  fVar3 = compute_ai_vehicle_forward_heading_angle((int)param_1);
  *(float *)(param_3 + 0x9d38) = (float)fVar3;
  return;
}


