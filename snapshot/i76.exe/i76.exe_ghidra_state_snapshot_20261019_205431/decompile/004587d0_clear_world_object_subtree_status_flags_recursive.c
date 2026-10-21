/*
 * Program: i76.exe
 * Function: clear_world_object_subtree_status_flags_recursive
 * Entry: 004587d0
 * Signature: undefined __cdecl clear_world_object_subtree_status_flags_recursive(int param_1, uint param_2)
 */


/* cgpt label refinement v19: was world_object_geometry_world_object_geometry_helper_004587d0.
   Remove duplicated world_object_geometry wording. */

void __cdecl clear_world_object_subtree_status_flags_recursive(int param_1,uint param_2)

{
  if (*(int *)(param_1 + 0x60) != 0) {
    clear_world_object_subtree_status_flags_recursive(*(int *)(param_1 + 0x60),param_2);
  }
  if (*(int *)(param_1 + 100) != 0) {
    clear_world_object_subtree_status_flags_recursive(*(int *)(param_1 + 100),param_2);
  }
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & ~param_2;
  return;
}


