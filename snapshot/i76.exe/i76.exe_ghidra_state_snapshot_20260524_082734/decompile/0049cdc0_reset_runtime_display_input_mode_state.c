/*
 * Program: i76.exe
 * Function: reset_runtime_display_input_mode_state
 * Entry: 0049cdc0
 * Signature: undefined __stdcall reset_runtime_display_input_mode_state(void)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=HIGH] Sets both current and requested
   runtime display/input mode globals to 1.
   old_name: FUN_0049cdc0 */

void reset_runtime_display_input_mode_state(void)

{
  g_requested_runtime_display_input_mode = 1;
  g_runtime_display_input_mode = 1;
  return;
}


