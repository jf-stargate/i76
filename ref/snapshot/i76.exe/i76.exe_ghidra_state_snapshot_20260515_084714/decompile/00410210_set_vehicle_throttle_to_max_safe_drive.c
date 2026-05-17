/*
 * Program: i76.exe
 * Function: set_vehicle_throttle_to_max_safe_drive
 * Entry: 00410210
 * Signature: undefined __cdecl set_vehicle_throttle_to_max_safe_drive(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Sets vehicle drive/throttle command to just below
   the max safe drive delta and marks active-player control changed. */

void __cdecl set_vehicle_throttle_to_max_safe_drive(float param_1)

{
  int iVar1;
  float10 fVar2;
  
  if (DAT_005244c8 == param_1) {
    DAT_005244c4 = 1;
  }
  iVar1 = get_vehicle_runtime_context((int)param_1);
  fVar2 = solve_vehicle_max_drive_brake_delta(param_1,1.0);
  *(float *)(iVar1 + 0xe4) = (float)(fVar2 * (float10)_DAT_004bc750);
  return;
}


