/*
 * Program: i76.exe
 * Function: or_world_object_subtree_status_flags_recursive
 * Entry: 00458790
 * Signature: undefined __cdecl or_world_object_subtree_status_flags_recursive(int param_1, uint param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: world object bounds context helper
   based on prior focused closure context.
   [I76 v67] Recursively traverses child and sibling links and ORs mask into node+10 */

void __cdecl or_world_object_subtree_status_flags_recursive(int param_1,uint param_2)

{
  if (*(int *)(param_1 + 0x60) != 0) {
    or_world_object_subtree_status_flags_recursive(*(int *)(param_1 + 0x60),param_2);
  }
  if (*(int *)(param_1 + 100) != 0) {
    or_world_object_subtree_status_flags_recursive(*(int *)(param_1 + 100),param_2);
  }
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | param_2;
  return;
}


