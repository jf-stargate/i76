/*
 * Program: i76.exe
 * Function: fsm_update_timer_default_type3
 * Entry: 0040bfc0
 * Signature: undefined __cdecl fsm_update_timer_default_type3(char * param_1, int param_2)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action wrapper around
   update_timer_or_frame_delta using timer/update type 3. */

void __cdecl fsm_update_timer_default_type3(char *param_1,int param_2)

{
  update_timer_or_frame_delta(param_1,param_2,3);
  return;
}


