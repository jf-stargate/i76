/*
 * Program: i76.exe
 * Function: fsm_play_or_stop_vehicle_engine_event_sound
 * Entry: 0040c060
 * Signature: undefined __cdecl fsm_play_or_stop_vehicle_engine_event_sound(int param_1, int * param_2)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action wrapper around
   play_or_stop_vehicle_engine_event_sound. */

void __cdecl fsm_play_or_stop_vehicle_engine_event_sound(int param_1,int *param_2)

{
  play_or_stop_vehicle_engine_event_sound(param_1,*param_2);
  return;
}


