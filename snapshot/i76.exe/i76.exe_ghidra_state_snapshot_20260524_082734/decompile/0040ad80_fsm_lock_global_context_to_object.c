/*
 * Program: i76.exe
 * Function: fsm_lock_global_context_to_object
 * Entry: 0040ad80
 * Signature: undefined __cdecl fsm_lock_global_context_to_object(undefined4 param_1)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Locks global FSM context to a specific world object
   and marks the lock active for this frame. */

void __cdecl fsm_lock_global_context_to_object(undefined4 param_1)

{
  DAT_00508da0 = 1;
  DAT_0051f5b0 = param_1;
  return;
}


