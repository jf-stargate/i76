/*
 * Program: i76.exe
 * Function: world_object_bounds_context_helper_00458790
 * Entry: 00458790
 * Signature: undefined __cdecl world_object_bounds_context_helper_00458790(int param_1, uint param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: world object bounds context helper
   based on prior focused closure context. */

void __cdecl world_object_bounds_context_helper_00458790(int param_1,uint param_2)

{
  if (*(int *)(param_1 + 0x60) != 0) {
    world_object_bounds_context_helper_00458790(*(int *)(param_1 + 0x60),param_2);
  }
  if (*(int *)(param_1 + 100) != 0) {
    world_object_bounds_context_helper_00458790(*(int *)(param_1 + 100),param_2);
  }
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | param_2;
  return;
}


