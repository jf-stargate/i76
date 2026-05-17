/*
 * Program: i76.exe
 * Function: release_world_object_subtree_recursive
 * Entry: 0045ee80
 * Signature: undefined __cdecl release_world_object_subtree_recursive(LPVOID param_1, int param_2, uint param_3, undefined4 param_4, undefined4 param_5)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Recursive subtree release
   helper. Unlinks siblings/children, releases class, geometry, texture, and light runtime state,
   then frees nodes whose refcount reaches zero. */

void __cdecl
release_world_object_subtree_recursive
          (LPVOID param_1,int param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  
  if (*(LPVOID *)((int)param_1 + 100) != (LPVOID)0x0) {
    release_world_object_subtree_recursive
              (*(LPVOID *)((int)param_1 + 100),param_2 + 1,param_3,param_4,param_5);
  }
  if ((*(LPVOID *)((int)param_1 + 0x60) != (LPVOID)0x0) && (1 < param_2)) {
    release_world_object_subtree_recursive
              (*(LPVOID *)((int)param_1 + 0x60),param_2 + 1,param_3,param_4,param_5);
  }
  iVar1 = *(int *)((int)param_1 + 0xc) - (param_3 & 0xffff);
  *(undefined2 *)((int)param_1 + 8) = 1;
  *(int *)((int)param_1 + 0xc) = iVar1;
  if ((iVar1 == 0) && (param_1 != (LPVOID)0x0)) {
    iVar1 = *(int *)((int)param_1 + 0x68);
    if (iVar1 != 0) {
      if (*(LPVOID *)(iVar1 + 100) == param_1) {
        *(undefined4 *)(iVar1 + 100) = *(undefined4 *)((int)param_1 + 0x60);
      }
      else {
        *(undefined4 *)(iVar1 + 0x60) = *(undefined4 *)((int)param_1 + 0x60);
      }
    }
    if (*(int *)((int)param_1 + 100) != 0) {
      *(undefined4 *)(*(int *)((int)param_1 + 100) + 0x68) = 0;
    }
    if (*(int *)((int)param_1 + 0x60) != 0) {
      *(undefined4 *)(*(int *)((int)param_1 + 0x60) + 0x68) = *(undefined4 *)((int)param_1 + 0x68);
    }
    release_world_object_class_runtime(*(int *)((int)param_1 + 0x6c),*(int *)((int)param_1 + 0x70));
    *(undefined4 *)((int)param_1 + 0x6c) = 0;
    *(undefined4 *)((int)param_1 + 0x70) = 0;
    release_world_object_geometry_binding((int)param_1);
    release_world_object_texture_bindings((int)param_1);
    if ((*(uint *)((int)param_1 + 0x10) & 0x800) != 0) {
      release_world_object_light_runtime((int)param_1);
    }
    HeapFree(g_world_object_node_heap,0,param_1);
  }
  return;
}


