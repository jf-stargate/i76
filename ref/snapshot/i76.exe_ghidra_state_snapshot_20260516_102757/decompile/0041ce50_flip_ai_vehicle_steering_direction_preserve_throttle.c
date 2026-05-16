/*
 * Program: i76.exe
 * Function: flip_ai_vehicle_steering_direction_preserve_throttle
 * Entry: 0041ce50
 * Signature: undefined __cdecl flip_ai_vehicle_steering_direction_preserve_throttle(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Flips steering sign using tire-grip scalar while
   clearing behavior override. */

void __cdecl flip_ai_vehicle_steering_direction_preserve_throttle(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar1 + 0xf0) = 0;
  if ((float)_DAT_004bcaf8 <= *(float *)(iVar1 + 0xe0)) {
    fVar2 = compute_vehicle_tire_grip_control_scalar(param_1);
    *(float *)(iVar1 + 0xe0) = (float)-fVar2;
  }
  else {
    fVar2 = compute_vehicle_tire_grip_control_scalar(param_1);
    *(float *)(iVar1 + 0xe0) = (float)fVar2;
  }
  return;
}


