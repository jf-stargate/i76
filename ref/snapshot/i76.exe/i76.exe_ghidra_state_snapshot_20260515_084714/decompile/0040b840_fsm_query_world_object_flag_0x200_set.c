/*
 * Program: i76.exe
 * Function: fsm_query_world_object_flag_0x200_set
 * Entry: 0040b840
 * Signature: undefined4 __cdecl fsm_query_world_object_flag_0x200_set(int param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: returns true when world-object flag
   0x200 is set. */

undefined4 __cdecl fsm_query_world_object_flag_0x200_set(int param_1)

{
  if ((param_1 != 0) && ((*(uint *)(param_1 + 0x10) & 0x200) != 0)) {
    return 1;
  }
  return 0;
}


