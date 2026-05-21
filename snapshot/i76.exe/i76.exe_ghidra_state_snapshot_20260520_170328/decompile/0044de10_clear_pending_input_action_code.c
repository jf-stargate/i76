/*
 * Program: i76.exe
 * Function: clear_pending_input_action_code
 * Entry: 0044de10
 * Signature: undefined __stdcall clear_pending_input_action_code(void)
 */


/* cgpt rename v2: Clears a pending input/action global used by the input dispatcher and player
   death path. */

void clear_pending_input_action_code(void)

{
                    /* I76 semantic baseline: clear_pending_input_action_code
                       Clears global pending input action code. */
  DAT_004f2848 = 0;
  return;
}


