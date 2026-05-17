/*
 * Program: i76.exe
 * Function: update_fsm_runtime_progress_compare_state
 * Entry: 00414b60
 * Signature: undefined __stdcall update_fsm_runtime_progress_compare_state(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Compares FSM/runtime progress counter globals and
   stores compare state 1/2 into DAT_00524548. */

void update_fsm_runtime_progress_compare_state(void)

{
  if (DAT_00524540 < DAT_00524544) {
    _DAT_00524548 = 1;
    return;
  }
  _DAT_00524548 = -(uint)(DAT_00524540 != DAT_00524544) & 2;
  return;
}


