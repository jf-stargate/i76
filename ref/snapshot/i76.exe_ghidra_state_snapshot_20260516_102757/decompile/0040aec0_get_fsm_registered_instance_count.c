/*
 * Program: i76.exe
 * Function: get_fsm_registered_instance_count
 * Entry: 0040aec0
 * Signature: undefined4 __stdcall get_fsm_registered_instance_count(void)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Returns the registered FSM instance count/global
   loaded from mission registration. */

undefined4 get_fsm_registered_instance_count(void)

{
  return DAT_0051f5c4;
}


