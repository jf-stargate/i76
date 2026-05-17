/*
 * Program: i76.exe
 * Function: clear_ai_vehicle_throttle_brake_command
 * Entry: 0041d6d0
 * Signature: undefined __cdecl clear_ai_vehicle_throttle_brake_command(float param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Wrapper that clears or reduces AI throttle/brake
   command via FUN_00410210. */

void __cdecl clear_ai_vehicle_throttle_brake_command(float param_1)

{
  set_vehicle_throttle_to_max_safe_drive(param_1);
  return;
}


