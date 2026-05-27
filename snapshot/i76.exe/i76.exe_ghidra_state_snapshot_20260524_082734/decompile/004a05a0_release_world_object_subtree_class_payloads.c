/*
 * Program: i76.exe
 * Function: release_world_object_subtree_class_payloads
 * Entry: 004a05a0
 * Signature: undefined __cdecl release_world_object_subtree_class_payloads(HANDLE param_1, int param_2)
 */


/* cgpt rename v2: Recursively frees per-object class/runtime payloads from a supplied heap over
   child/sibling links. */

void __cdecl release_world_object_subtree_class_payloads(HANDLE param_1,int param_2)

{
  if (param_2 != 0) {
    if (*(int *)(param_2 + 100) != 0) {
      release_world_object_subtree_class_payloads(param_1,*(int *)(param_2 + 100));
    }
    if (*(int *)(param_2 + 0x60) != 0) {
      release_world_object_subtree_class_payloads(param_1,*(int *)(param_2 + 0x60));
    }
    HeapFree(param_1,0,*(LPVOID *)(param_2 + 0x70));
    *(undefined4 *)(param_2 + 0x70) = 0;
    *(undefined4 *)(param_2 + 0x5c) = 0;
  }
  return;
}


