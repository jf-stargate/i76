/*
 * Program: i76.exe
 * Function: building_child_piece_context_helper_0046b200
 * Entry: 0046b200
 * Signature: undefined __cdecl building_child_piece_context_helper_0046b200(int param_1, undefined4 param_2)
 */


/* cgpt label refinement v19: was building_world_object_building_child_piece_helper_0046b200. Remove
   duplicated building wording. */

void __cdecl building_child_piece_context_helper_0046b200(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x70);
  puVar1[1] = param_2;
  *puVar1 = param_2;
  return;
}


