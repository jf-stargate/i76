/*
 * Program: i76.exe
 * Function: get_vehicle_damage_event_state_block
 * Entry: 00466e20
 * Signature: undefined4 __cdecl get_vehicle_damage_event_state_block(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Returns vehicle runtime
   damage/source-event state block pointer. */

undefined4 __cdecl get_vehicle_damage_event_state_block(int param_1)

{
  return *(undefined4 *)(param_1 + 0x108);
}


