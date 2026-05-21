/*
 * Program: i76.exe
 * Function: decrement_world_object_subtree_refcounts
 * Entry: 0045f0c0
 * Signature: undefined __cdecl decrement_world_object_subtree_refcounts(int param_1, undefined4 param_2)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Recursively decrements
   child/sibling world-object refcounts without performing full runtime release. */

void __cdecl decrement_world_object_subtree_refcounts(int param_1,undefined4 param_2)

{
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x60)) {
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
    if (*(int *)(param_1 + 100) != 0) {
      decrement_world_object_subtree_refcounts(*(int *)(param_1 + 100),param_2);
    }
  }
  return;
}


