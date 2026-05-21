/*
 * Program: i76.exe
 * Function: get_vehicle_throttle_input_scalar
 * Entry: 00466e40
 * Signature: float10 __cdecl get_vehicle_throttle_input_scalar(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Returns vehicle
   throttle/engine input scalar used by drivetrain calculations. */

float10 __cdecl get_vehicle_throttle_input_scalar(int param_1)

{
  return (float10)*(float *)(param_1 + 0xe4);
}


