/*
 * Program: i76.exe
 * Function: set_shell_return_launch_requested
 * Entry: 00401270
 * Signature: undefined __cdecl set_shell_return_launch_requested(undefined4 param_1)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=MEDIUM] Called when shell return state is 3
   before copying shell path to selected mission resource path.
   old_name: FUN_00401270 */

void __cdecl set_shell_return_launch_requested(undefined4 param_1)

{
  DAT_00501818 = param_1;
  return;
}


