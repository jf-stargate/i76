/*
 * Program: i76.exe
 * Function: fsm_append_salvage_resource_reference
 * Entry: 0040c040
 * Signature: undefined __cdecl fsm_append_salvage_resource_reference(char * param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action wrapper around
   append_salvage_resource_reference_for_mission with default id -1 and enabled flag. */

void __cdecl fsm_append_salvage_resource_reference(char *param_1)

{
  append_salvage_resource_reference_for_mission(param_1,0xffffffff,1);
  return;
}


