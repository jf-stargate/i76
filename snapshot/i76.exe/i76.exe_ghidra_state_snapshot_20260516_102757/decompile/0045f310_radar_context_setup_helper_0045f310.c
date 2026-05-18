/*
 * Program: i76.exe
 * Function: radar_context_setup_helper_0045f310
 * Entry: 0045f310
 * Signature: undefined __cdecl radar_context_setup_helper_0045f310(int param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: radar context setup helper based on
   prior focused closure context. */

void __cdecl radar_context_setup_helper_0045f310(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 != 0) {
    iVar2 = get_parent_if_current_is_last_child_link(param_1);
    if (iVar2 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(iVar2 + 0xc) + -1;
    }
    iVar4 = *(int *)(param_1 + 0x68);
    if (iVar4 != 0) {
      if (*(int *)(iVar4 + 100) == param_1) {
        *(undefined4 *)(iVar4 + 100) = *(undefined4 *)(param_1 + 0x60);
      }
      else {
        *(undefined4 *)(iVar4 + 0x60) = *(undefined4 *)(param_1 + 0x60);
      }
    }
    if (*(int *)(param_1 + 0x60) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x60) + 0x68) = *(undefined4 *)(param_1 + 0x68);
    }
    iVar4 = *(int *)(param_1 + 100);
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - iVar3;
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined4 *)(param_1 + 0x60) = 0;
    if (iVar4 != 0) {
      if (iVar4 == 0) goto LAB_0045f39d;
      do {
        iVar1 = *(int *)(iVar4 + 100);
        *(int *)(iVar4 + 0xc) = *(int *)(iVar4 + 0xc) + -iVar3;
        for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
          propagate_world_object_refcount_delta_to_children(iVar1,-iVar3,iVar2);
        }
LAB_0045f39d:
        iVar4 = *(int *)(iVar4 + 0x60);
      } while (iVar4 != 0);
    }
  }
  return;
}


