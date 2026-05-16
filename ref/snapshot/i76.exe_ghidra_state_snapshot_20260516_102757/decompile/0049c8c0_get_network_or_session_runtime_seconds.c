/*
 * Program: i76.exe
 * Function: get_network_or_session_runtime_seconds
 * Entry: 0049c8c0
 * Signature: float10 __stdcall get_network_or_session_runtime_seconds(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe main runtime/FSM rename v21; confidence=MEDIUM] Returns the float runtime/network
   timer at 005a7e74; heavily used in multiplayer timing gates.
   old_name: FUN_0049c8c0 */

float10 get_network_or_session_runtime_seconds(void)

{
                    /* I76 semantic baseline: get_network_or_session_runtime_seconds
                       Returns secondary/session runtime clock, heavily used by multiplayer gates.
                        */
  return (float10)_DAT_005a7e74;
}


