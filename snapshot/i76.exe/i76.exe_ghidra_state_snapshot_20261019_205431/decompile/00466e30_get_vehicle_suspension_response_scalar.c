/*
 * Program: i76.exe
 * Function: get_vehicle_suspension_response_scalar
 * Entry: 00466e30
 * Signature: float10 __cdecl get_vehicle_suspension_response_scalar(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Returns vehicle suspension
   response/travel scalar used by traction calculations. */

float10 __cdecl get_vehicle_suspension_response_scalar(int param_1)

{
  return (float10)*(float *)(param_1 + 0xe0);
}


