/*
 * Program: i76.exe
 * Function: fsm_start_vehicle_special_behavior_mode_3
 * Entry: 0040afa0
 * Signature: undefined __cdecl fsm_start_vehicle_special_behavior_mode_3(int param_1)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: FSM action: starts vehicle special/behavior sound or
   state handler and sets vehicle runtime mode 3. */

void __cdecl fsm_start_vehicle_special_behavior_mode_3(int param_1)

{
  vehicle_specials_indicator_update_helper_00467400(param_1);
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  return;
}


