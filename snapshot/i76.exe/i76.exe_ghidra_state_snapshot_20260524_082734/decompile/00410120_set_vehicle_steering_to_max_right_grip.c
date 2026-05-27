/*
 * Program: i76.exe
 * Function: set_vehicle_steering_to_max_right_grip
 * Entry: 00410120
 * Signature: undefined __cdecl set_vehicle_steering_to_max_right_grip(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Sets vehicle steering command to the negative maximum grip-limited value. */

void __cdecl set_vehicle_steering_to_max_right_grip(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  fVar2 = compute_vehicle_tire_grip_control_scalar(param_1);
  *(float *)(iVar1 + 0xe0) = (float)-(fVar2 * (float10)_DAT_004bc750);
  return;
}


