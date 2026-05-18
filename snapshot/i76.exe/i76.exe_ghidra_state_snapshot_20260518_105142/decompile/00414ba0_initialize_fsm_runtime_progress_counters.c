/*
 * Program: i76.exe
 * Function: initialize_fsm_runtime_progress_counters
 * Entry: 00414ba0
 * Signature: undefined __stdcall initialize_fsm_runtime_progress_counters(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Initializes FSM/runtime progress counter globals
   DAT_00524540/44/48/4c to their default state. */

void initialize_fsm_runtime_progress_counters(void)

{
  _DAT_0052454c = 0;
  DAT_00524540 = 0;
  DAT_00524544 = 1;
  _DAT_00524548 = 1;
  return;
}


