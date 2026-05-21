/*
 * Program: i76.exe
 * Function: reset_vehicle_damage_source_event_state
 * Entry: 004155e0
 * Signature: undefined __stdcall reset_vehicle_damage_source_event_state(void)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Clears the vehicle damage-source event/global actor id
   state. */

void reset_vehicle_damage_source_event_state(void)

{
  g_vehicle_damage_source_event_state = 0;
  return;
}


