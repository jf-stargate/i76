/*
 * Program: i76.exe
 * Function: is_gameplay_input_update_paused
 * Entry: 0044e010
 * Signature: bool __stdcall is_gameplay_input_update_paused(void)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium] Pause/update gate checked
   before running the direct vehicle frame update branch. */

bool is_gameplay_input_update_paused(void)

{
                    /* I76 semantic baseline: is_gameplay_input_update_paused
                       Returns whether runtime input/simulation update is paused/gated. */
  return DAT_004f4ca4 != DAT_005dd360;
}


