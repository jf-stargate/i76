/*
 * Program: i76.exe
 * Function: fsm_mark_global_context_suppressed_this_frame
 * Entry: 0040ad70
 * Signature: undefined __stdcall fsm_mark_global_context_suppressed_this_frame(void)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Sets the global one-frame FSM context suppression
   flag. */

void fsm_mark_global_context_suppressed_this_frame(void)

{
  DAT_0051f604 = 1;
  return;
}


