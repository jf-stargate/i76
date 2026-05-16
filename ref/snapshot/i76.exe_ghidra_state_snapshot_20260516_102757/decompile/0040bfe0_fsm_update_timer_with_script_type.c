/*
 * Program: i76.exe
 * Function: fsm_update_timer_with_script_type
 * Entry: 0040bfe0
 * Signature: undefined __cdecl fsm_update_timer_with_script_type(char * param_1, int * param_2)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action wrapper around
   update_timer_or_frame_delta using a script-provided update type. */

void __cdecl fsm_update_timer_with_script_type(char *param_1,int *param_2)

{
  update_timer_or_frame_delta(param_1,0,*param_2);
  return;
}


