/*
 * Program: i76.exe
 * Function: building_child_piece_context_helper_0046a890
 * Entry: 0046a890
 * Signature: undefined __cdecl building_child_piece_context_helper_0046a890(int param_1, float param_2)
 */


/* cgpt label refinement v19: was building_world_object_building_child_piece_helper_0046a890. Remove
   duplicated building wording. */

void __cdecl building_child_piece_context_helper_0046a890(int param_1,float param_2)

{
  int iVar1;
  float fVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x70);
  iVar3 = is_damage_side_effects_suppressed();
  if (iVar3 == 0) {
    iVar3 = is_network_or_trip_runtime_mode();
    if (iVar3 == 0) {
      *(float *)(iVar1 + 0x10) = param_2;
      *(float *)(iVar1 + 0xc) = param_2;
      return;
    }
  }
  fVar2 = param_2 * *(float *)(iVar1 + 0xc);
  *(float *)(iVar1 + 0xc) = fVar2;
  *(float *)(iVar1 + 0x10) = fVar2;
  return;
}


