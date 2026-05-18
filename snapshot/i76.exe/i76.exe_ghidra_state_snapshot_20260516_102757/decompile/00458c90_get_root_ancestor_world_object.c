/*
 * Program: i76.exe
 * Function: get_root_ancestor_world_object
 * Entry: 00458c90
 * Signature: undefined __cdecl get_root_ancestor_world_object(int param_1)
 */


/* [cgpt i76.exe geometry/texture rename v8; confidence=high] Walks +0x68 parent links until the
   root ancestor and returns it in EAX. */

void __cdecl get_root_ancestor_world_object(int param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_1 + 0x68); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x68)) {
  }
  return;
}


