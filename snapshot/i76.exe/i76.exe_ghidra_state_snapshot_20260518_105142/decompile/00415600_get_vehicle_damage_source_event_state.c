/*
 * Program: i76.exe
 * Function: get_vehicle_damage_source_event_state
 * Entry: 00415600
 * Signature: undefined4 __stdcall get_vehicle_damage_source_event_state(void)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Returns the vehicle damage-source event/global actor id
   state. */

undefined4 get_vehicle_damage_source_event_state(void)

{
  return g_vehicle_damage_source_event_state;
}


