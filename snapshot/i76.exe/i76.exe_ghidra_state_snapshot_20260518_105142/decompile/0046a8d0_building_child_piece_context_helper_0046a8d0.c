/*
 * Program: i76.exe
 * Function: building_child_piece_context_helper_0046a8d0
 * Entry: 0046a8d0
 * Signature: undefined4 * __stdcall building_child_piece_context_helper_0046a8d0(void)
 */


/* cgpt label refinement v19: was building_world_object_building_child_piece_helper_0046a8d0. Remove
   duplicated building wording. */

undefined4 * building_child_piece_context_helper_0046a8d0(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = radar_context_helper_0045f3b0(0x20);
  puVar3 = puVar1;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar1[3] = 0x3f800000;
  puVar1[4] = 0x3f800000;
  puVar1[5] = 0x3f800000;
  puVar1[6] = 0x3f800000;
  puVar1[7] = 0x3f800000;
  *puVar1 = 200;
  puVar1[1] = 200;
  return puVar1;
}


