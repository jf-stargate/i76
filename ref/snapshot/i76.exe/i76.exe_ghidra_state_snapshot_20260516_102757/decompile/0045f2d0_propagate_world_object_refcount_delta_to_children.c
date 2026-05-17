/*
 * Program: i76.exe
 * Function: propagate_world_object_refcount_delta_to_children
 * Entry: 0045f2d0
 * Signature: undefined __cdecl propagate_world_object_refcount_delta_to_children(int param_1, int param_2, undefined4 param_3)
 */


/* [cgpt i76.exe world/runtime table rename v17; confidence=HIGH] Adds a signed delta to a world
   object tree node's refcount at +0x0c and recurses through child links at +0x64/+0x60. */

void __cdecl
propagate_world_object_refcount_delta_to_children(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 100);
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_2;
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      propagate_world_object_refcount_delta_to_children(iVar1,param_2,param_3);
    }
  }
  return;
}


