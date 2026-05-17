/*
 * Program: i76.exe
 * Function: building_child_piece_context_helper_0046bb60
 * Entry: 0046bb60
 * Signature: undefined __cdecl building_child_piece_context_helper_0046bb60(LPVOID param_1)
 */


/* cgpt label refinement v19: was building_world_object_building_child_piece_helper_0046bb60. Remove
   duplicated building wording. */

void __cdecl building_child_piece_context_helper_0046bb60(LPVOID param_1)

{
  if (*(LPVOID *)((int)param_1 + 0x508) != (LPVOID)0x0) {
    release_vehicle_runtime_context(*(LPVOID *)((int)param_1 + 0x508));
  }
  *(undefined4 *)((int)param_1 + 0x508) = 0;
  release_vehicle_runtime_context_and_components(param_1);
  return;
}


