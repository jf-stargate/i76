/*
 * Program: i76.exe
 * Function: building_child_piece_context_helper_0046c870
 * Entry: 0046c870
 * Signature: undefined __cdecl building_child_piece_context_helper_0046c870(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was building_world_object_building_child_piece_helper_0046c870. Remove
   duplicated building wording. */

void __cdecl building_child_piece_context_helper_0046c870(int param_1,float param_2)

{
  int iVar1;
  float fVar2;
  
  fVar2 = _DAT_004be330;
  iVar1 = *(int *)(param_1 + 0x70);
  *(float *)(*(int *)(iVar1 + 0x508) + 0x14) = param_2;
  if (fVar2 < param_2) {
    *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) & 0xffffff7f;
  }
  return;
}


