/*
 * Program: i76.exe
 * Function: copy_vehicle_runtime_velocity_and_speed
 * Entry: 00464360
 * Signature: undefined __cdecl copy_vehicle_runtime_velocity_and_speed(int param_1, undefined4 * param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=medium] Class-id 1 callback that
   copies a 3-float vector from runtime +0xbc and a scalar from +0xac to caller buffers. */

void __cdecl
copy_vehicle_runtime_velocity_and_speed(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x70);
  *param_2 = *(undefined4 *)(iVar1 + 0xbc);
  param_2[1] = *(undefined4 *)(iVar1 + 0xc0);
  param_2[2] = *(undefined4 *)(iVar1 + 0xc4);
  *param_3 = *(undefined4 *)(iVar1 + 0xac);
  return;
}


