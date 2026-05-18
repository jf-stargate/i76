/*
 * Program: i76.exe
 * Function: increment_vehicle_damage_source_event_state
 * Entry: 004155f0
 * Signature: undefined __stdcall increment_vehicle_damage_source_event_state(void)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Increments the vehicle damage-source event/global actor
   id state. */

void increment_vehicle_damage_source_event_state(void)

{
  g_vehicle_damage_source_event_state = g_vehicle_damage_source_event_state + 1;
  return;
}


