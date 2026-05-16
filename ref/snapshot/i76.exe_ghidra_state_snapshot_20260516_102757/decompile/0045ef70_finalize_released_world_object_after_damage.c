/*
 * Program: i76.exe
 * Function: finalize_released_world_object_after_damage
 * Entry: 0045ef70
 * Signature: undefined __cdecl finalize_released_world_object_after_damage(LPVOID param_1, undefined4 param_2)
 */


/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] Post-damage release/unlink cleanup.
   Recursively releases children and frees class/geometry/texture/light state when the object
   refcount reaches zero. */

void __cdecl finalize_released_world_object_after_damage(LPVOID param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (param_1 != (LPVOID)0x0) {
    if (*(int *)((int)param_1 + 0xc) < 2) {
      iVar2 = 0;
      uVar3 = 1;
      if (*(int *)((int)param_1 + 0x68) != 0) {
        iVar2 = get_parent_if_current_is_last_child_link((int)param_1);
        if (iVar2 != 0) {
          uVar3 = (uint)*(ushort *)(iVar2 + 0xc);
        }
        iVar1 = *(int *)((int)param_1 + 0x68);
        if (*(LPVOID *)(iVar1 + 100) == param_1) {
          *(undefined4 *)(iVar1 + 100) = *(undefined4 *)((int)param_1 + 0x60);
        }
        else if (*(LPVOID *)(iVar1 + 0x60) == param_1) {
          *(undefined4 *)(iVar1 + 0x60) = *(undefined4 *)((int)param_1 + 0x60);
        }
      }
      if (*(int *)((int)param_1 + 0x60) != 0) {
        *(undefined4 *)(*(int *)((int)param_1 + 0x60) + 0x68) = *(undefined4 *)((int)param_1 + 0x68)
        ;
      }
      *(undefined4 *)((int)param_1 + 0x68) = 0;
      *(undefined4 *)((int)param_1 + 0x60) = 0;
      if (*(LPVOID *)((int)param_1 + 100) != (LPVOID)0x0) {
        release_world_object_subtree_recursive
                  (*(LPVOID *)((int)param_1 + 100),2,uVar3,iVar2,param_2);
      }
      iVar2 = *(int *)((int)param_1 + 0xc) - uVar3;
      *(undefined2 *)((int)param_1 + 8) = 1;
      *(int *)((int)param_1 + 0xc) = iVar2;
      if (iVar2 == 0) {
        iVar2 = *(int *)((int)param_1 + 0x68);
        if (iVar2 != 0) {
          if (*(LPVOID *)(iVar2 + 100) == param_1) {
            *(undefined4 *)(iVar2 + 100) = *(undefined4 *)((int)param_1 + 0x60);
          }
          else {
            *(undefined4 *)(iVar2 + 0x60) = *(undefined4 *)((int)param_1 + 0x60);
          }
        }
        if (*(int *)((int)param_1 + 100) != 0) {
          *(undefined4 *)(*(int *)((int)param_1 + 100) + 0x68) = 0;
        }
        if (*(int *)((int)param_1 + 0x60) != 0) {
          *(undefined4 *)(*(int *)((int)param_1 + 0x60) + 0x68) =
               *(undefined4 *)((int)param_1 + 0x68);
        }
        release_world_object_class_runtime
                  (*(int *)((int)param_1 + 0x6c),*(int *)((int)param_1 + 0x70));
        *(undefined4 *)((int)param_1 + 0x6c) = 0;
        *(undefined4 *)((int)param_1 + 0x70) = 0;
        release_world_object_geometry_binding((int)param_1);
        release_world_object_texture_bindings((int)param_1);
        if ((*(uint *)((int)param_1 + 0x10) & 0x800) != 0) {
          release_world_object_light_runtime((int)param_1);
        }
        HeapFree(g_world_object_node_heap,0,param_1);
        return;
      }
    }
    else {
      *(int *)((int)param_1 + 0xc) = *(int *)((int)param_1 + 0xc) + -1;
      for (iVar2 = *(int *)((int)param_1 + 100); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x60)) {
        *(int *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc) + -1;
        if (*(int *)(iVar2 + 100) != 0) {
          decrement_world_object_subtree_refcounts(*(int *)(iVar2 + 100),param_2);
        }
      }
    }
  }
  return;
}


