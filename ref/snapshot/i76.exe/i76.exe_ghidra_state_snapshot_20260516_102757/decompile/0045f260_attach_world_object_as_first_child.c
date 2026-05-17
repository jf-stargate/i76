/*
 * Program: i76.exe
 * Function: attach_world_object_as_first_child
 * Entry: 0045f260
 * Signature: undefined __cdecl attach_world_object_as_first_child(int param_1, int param_2)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Attaches an object under a
   parent as the first child, updates sibling/parent links, and propagates parent refcount/state to
   descendants. */

void __cdecl attach_world_object_as_first_child(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 != 0) {
    *(int *)(param_1 + 0x68) = param_2;
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 100);
    if (*(int *)(param_2 + 100) != 0) {
      *(int *)(*(int *)(param_2 + 100) + 0x68) = param_1;
    }
    *(int *)(param_2 + 100) = param_1;
    iVar1 = *(int *)(param_1 + 100);
    *(undefined2 *)(param_1 + 8) = *(undefined2 *)(param_2 + 8);
    iVar3 = *(int *)(param_2 + 0xc) + -1;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + iVar3;
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      iVar2 = *(int *)(iVar1 + 100);
      *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + iVar3;
      for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x60)) {
        propagate_world_object_refcount_delta_to_children(iVar2,iVar3,param_2);
      }
    }
  }
  return;
}


