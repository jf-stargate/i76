/*
 * Program: i76.exe
 * Function: increment_refcount_recursive_for_object_tree
 * Entry: 0045ed00
 * Signature: undefined __cdecl increment_refcount_recursive_for_object_tree(int param_1, undefined4 param_2)
 */


/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] Recursively increments world-object
   refcounts before temporary damage dispatch. */

void __cdecl increment_refcount_recursive_for_object_tree(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    if (g_world_object_refcount_recursion_guard != 0) {
      do {
        *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
        increment_refcount_recursive_for_object_tree(*(int *)(param_1 + 100),param_2);
        param_1 = *(int *)(param_1 + 0x60);
      } while (param_1 != 0);
      return;
    }
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
    g_world_object_refcount_recursion_guard = 1;
    increment_refcount_recursive_for_object_tree(*(int *)(param_1 + 100),param_2);
    g_world_object_refcount_recursion_guard = 0;
  }
  return;
}


