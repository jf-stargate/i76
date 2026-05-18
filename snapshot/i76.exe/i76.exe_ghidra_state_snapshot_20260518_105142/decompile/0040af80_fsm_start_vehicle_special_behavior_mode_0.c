/*
 * Program: i76.exe
 * Function: fsm_start_vehicle_special_behavior_mode_0
 * Entry: 0040af80
 * Signature: undefined __cdecl fsm_start_vehicle_special_behavior_mode_0(int param_1)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: FSM action: starts vehicle special/behavior sound or
   state handler and sets vehicle runtime mode 0. */

void __cdecl fsm_start_vehicle_special_behavior_mode_0(int param_1)

{
  vehicle_specials_indicator_flag_helper_004673d0(param_1);
  vehicle_specials_state_getter_helper_00467370(param_1,0);
  return;
}


