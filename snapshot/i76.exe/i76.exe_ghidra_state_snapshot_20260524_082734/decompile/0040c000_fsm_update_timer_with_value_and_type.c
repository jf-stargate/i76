/*
 * Program: i76.exe
 * Function: fsm_update_timer_with_value_and_type
 * Entry: 0040c000
 * Signature: undefined __cdecl fsm_update_timer_with_value_and_type(char * param_1, int param_2, int * param_3)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action wrapper around
   update_timer_or_frame_delta using both script-provided value and update type. */

void __cdecl fsm_update_timer_with_value_and_type(char *param_1,int param_2,int *param_3)

{
  update_timer_or_frame_delta(param_1,param_2,*param_3);
  return;
}


