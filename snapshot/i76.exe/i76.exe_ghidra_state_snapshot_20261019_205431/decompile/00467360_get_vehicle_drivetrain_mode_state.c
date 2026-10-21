/*
 * Program: i76.exe
 * Function: get_vehicle_drivetrain_mode_state
 * Entry: 00467360
 * Signature: undefined4 __cdecl get_vehicle_drivetrain_mode_state(int param_1)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Returns vehicle
   drivetrain/gear/mode state used by drivetrain and contact calculations. */

undefined4 __cdecl get_vehicle_drivetrain_mode_state(int param_1)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x104);
}


