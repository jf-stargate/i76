/*
 * Program: i76.exe
 * Function: is_runtime_input_or_update_paused
 * Entry: 0044e010
 * Signature: bool __stdcall is_runtime_input_or_update_paused(void)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Pause/update gate checked
   before running the direct vehicle frame update branch. */

bool is_runtime_input_or_update_paused(void)

{
  return DAT_004f4ca4 != DAT_005dd360;
}


