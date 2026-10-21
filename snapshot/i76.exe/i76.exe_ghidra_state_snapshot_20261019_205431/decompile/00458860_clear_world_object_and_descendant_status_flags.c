/*
 * Program: i76.exe
 * Function: clear_world_object_and_descendant_status_flags
 * Entry: 00458860
 * Signature: undefined __cdecl clear_world_object_and_descendant_status_flags(int param_1, uint param_2)
 */


/* cgpt label refinement v19: was world_object_geometry_world_object_geometry_helper_00458860.
   Remove duplicated world_object_geometry wording. */

void __cdecl clear_world_object_and_descendant_status_flags(int param_1,uint param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 100);
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & ~param_2;
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 0x60) != 0) {
        clear_world_object_subtree_status_flags_recursive(*(int *)(iVar1 + 0x60),param_2);
      }
      if (*(int *)(iVar1 + 100) != 0) {
        clear_world_object_subtree_status_flags_recursive(*(int *)(iVar1 + 100),param_2);
      }
      *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & ~param_2;
    }
  }
  return;
}


