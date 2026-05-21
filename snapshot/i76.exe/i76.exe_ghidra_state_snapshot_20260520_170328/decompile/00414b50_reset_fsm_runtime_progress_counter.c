/*
 * Program: i76.exe
 * Function: reset_fsm_runtime_progress_counter
 * Entry: 00414b50
 * Signature: undefined __stdcall reset_fsm_runtime_progress_counter(void)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Clears global FSM/runtime progress counter
   DAT_00524540. */

void reset_fsm_runtime_progress_counter(void)

{
  DAT_00524540 = 0;
  return;
}


