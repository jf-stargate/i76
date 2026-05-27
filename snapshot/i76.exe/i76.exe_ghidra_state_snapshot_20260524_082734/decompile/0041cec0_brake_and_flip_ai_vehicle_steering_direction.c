/*
 * Program: i76.exe
 * Function: brake_and_flip_ai_vehicle_steering_direction
 * Entry: 0041cec0
 * Signature: undefined __cdecl brake_and_flip_ai_vehicle_steering_direction(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Applies max braking and flips steering sign based on
   tire-grip scalar. */

void __cdecl brake_and_flip_ai_vehicle_steering_direction(float param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = get_vehicle_runtime_context((int)param_1);
  set_vehicle_brake_to_max_safe_value(param_1);
  if (*(float *)(iVar1 + 0xe0) <= (float)_DAT_004bcaf8) {
    fVar2 = compute_vehicle_tire_grip_control_scalar((int)param_1);
    *(float *)(iVar1 + 0xe0) = (float)-fVar2;
  }
  else {
    fVar2 = compute_vehicle_tire_grip_control_scalar((int)param_1);
    *(float *)(iVar1 + 0xe0) = (float)fVar2;
  }
  return;
}


