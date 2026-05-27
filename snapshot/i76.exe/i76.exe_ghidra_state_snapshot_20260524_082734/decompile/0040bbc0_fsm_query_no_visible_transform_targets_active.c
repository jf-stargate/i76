/*
 * Program: i76.exe
 * Function: fsm_query_no_visible_transform_targets_active
 * Entry: 0040bbc0
 * Signature: undefined4 __stdcall fsm_query_no_visible_transform_targets_active(void)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: iterates target/object list entries
   and returns false if any transform-composed object lacks world-object flag 0x200. */

undefined4 fsm_query_no_visible_transform_targets_active(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)get_current_effect_target_scan_object();
  if (piVar2 == (int *)0x0) {
    return 1;
  }
  while( true ) {
    iVar1 = *piVar2;
    iVar3 = is_transform_composed_world_object_class(iVar1);
    if ((iVar3 != 0) && ((*(uint *)(iVar1 + 0x10) & 0x200) == 0)) break;
    piVar2 = (int *)effect_target_scan_query_context_helper_00436790();
    if (piVar2 == (int *)0x0) {
      return 1;
    }
  }
  return 0;
}


