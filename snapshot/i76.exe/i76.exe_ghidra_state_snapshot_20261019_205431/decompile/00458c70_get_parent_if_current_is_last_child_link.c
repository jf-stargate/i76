/*
 * Program: i76.exe
 * Function: get_parent_if_current_is_last_child_link
 * Entry: 00458c70
 * Signature: undefined4 __cdecl get_parent_if_current_is_last_child_link(int param_1)
 */


/* [cgpt i76.exe texture/resource-cache rename v9; confidence=medium-high] Walks parent links until
   the current node is not the +0x64 child link of its parent, then returns the parent link;
   hierarchy traversal helper. */

undefined4 __cdecl get_parent_if_current_is_last_child_link(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x68);
  while ((iVar1 = iVar2, iVar1 != 0 && (*(int *)(iVar1 + 100) != param_1))) {
    param_1 = iVar1;
    iVar2 = *(int *)(iVar1 + 0x68);
  }
  return *(undefined4 *)(param_1 + 0x68);
}


