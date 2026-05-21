/*
 * Program: i76.exe
 * Function: set_vehicle_brake_to_max_safe_value
 * Entry: 00410260
 * Signature: undefined __cdecl set_vehicle_brake_to_max_safe_value(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v4: Sets vehicle brake/reverse command to the safe maximum braking delta. */

void __cdecl set_vehicle_brake_to_max_safe_value(float param_1)

{
  float10 fVar1;
  int iVar2;
  float10 fVar3;
  
  if (DAT_005244c8 == param_1) {
    DAT_005244c4 = 1;
  }
  fVar3 = solve_vehicle_max_drive_brake_delta(param_1,-1.0);
  fVar1 = (float10)_DAT_004bc750;
  iVar2 = get_vehicle_runtime_context((int)param_1);
  *(float *)(iVar2 + 0xe4) = (float)(fVar3 * fVar1);
  return;
}


