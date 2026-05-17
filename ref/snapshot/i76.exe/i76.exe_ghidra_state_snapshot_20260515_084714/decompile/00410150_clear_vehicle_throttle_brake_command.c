/*
 * Program: i76.exe
 * Function: clear_vehicle_throttle_brake_command
 * Entry: 00410150
 * Signature: undefined __cdecl clear_vehicle_throttle_brake_command(int param_1)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Clears the vehicle runtime throttle/brake command
   field at +0xe0. */

void __cdecl clear_vehicle_throttle_brake_command(int param_1)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar1 + 0xe0) = 0;
  return;
}


