/*
 * Program: i76.exe
 * Function: set_fsm_registered_instance_count
 * Entry: 0040aeb0
 * Signature: undefined __cdecl set_fsm_registered_instance_count(undefined4 param_1)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Stores the registered FSM instance count/global
   loaded from mission registration. */

void __cdecl set_fsm_registered_instance_count(undefined4 param_1)

{
  DAT_0051f5c4 = param_1;
  return;
}


