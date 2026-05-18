/*
 * Program: i76.exe
 * Function: world_object_geometry_context_helper_00458860
 * Entry: 00458860
 * Signature: undefined __cdecl world_object_geometry_context_helper_00458860(int param_1, uint param_2)
 */


/* cgpt label refinement v19: was world_object_geometry_world_object_geometry_helper_00458860.
   Remove duplicated world_object_geometry wording. */

void __cdecl world_object_geometry_context_helper_00458860(int param_1,uint param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 100);
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & ~param_2;
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 0x60) != 0) {
        world_object_geometry_context_helper_004587d0(*(int *)(iVar1 + 0x60),param_2);
      }
      if (*(int *)(iVar1 + 100) != 0) {
        world_object_geometry_context_helper_004587d0(*(int *)(iVar1 + 100),param_2);
      }
      *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & ~param_2;
    }
  }
  return;
}


